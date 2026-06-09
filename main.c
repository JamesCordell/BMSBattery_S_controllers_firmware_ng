/*
 * BMSBattery S series motor controllers firmware
 *
 * Copyright (C) Casainho, 2017.
 *
 * Released under the GPL License, Version 3
 */

#include <stdint.h>
#include <stdio.h>
#include "stm8s.h"
#include "gpio.h"
#include "stm8s_itc.h"
#include "stm8s_gpio.h"
#include "interrupts.h"
#include "motor.h"
#include "main.h"
#include "uart.h"
#include "adc.h"
#include "brake.h"
#include "cruise_control.h"
#include "timers.h"
#include "pwm.h"
#include "PAS.h"
#include "SPEED.h"
//#include "update_setpoint.h"
#include "ACAsetPoint.h"
#include "config.h"
#include "display.h"
#include "display_kingmeter.h"
#include "ACAcontrollerState.h"
#include "BOdisplay.h"
#include "ACAeeprom.h"
#include "ACAcommons.h"

//uint16_t ui16_LPF_angle_adjust = 0;
//uint16_t ui16_LPF_angle_adjust_temp = 0;

uint8_t        ui8_slowloop_flag = 0;
uint8_t        ui8_veryslowloop_counter = 0;

uint8_t        ui8_ultraslowloop_counter = 0;


static int16_t i16_deziAmps;

void display_update(void);
void display_init(void);
/////////////////////////////////////////////////////////////////////////////////////////////
//// Functions prototypes

// main -- start of firmware and main loop
int main(void);

//With SDCC, interrupt service routine function prototypes must be placed in the file that contains main ()
//in order for an vector for the interrupt to be placed in the the interrupt vector space.  It's acceptable
//to place the function prototype in a header file as long as the header file is included in the file that
//contains main ().  SDCC will not generate any warnings or errors if this is not done, but the vector will
//not be in place so the ISR will not be executed when the interrupt occurs.

//Calling a function from interrupt not always works, SDCC manual says to avoid it. Maybe the best is to put
//all the code inside the interrupt

// Local VS global variables
// Sometimes I got the following error when compiling the firmware: motor.asm:750: Error: <r> relocation error
// and the solution was to avoid using local variables and define them as global instead

// Brake signal interrupt
void EXTI_PORTA_IRQHandler(void) __interrupt(EXTI_PORTA_IRQHANDLER);
// Speed signal interrupt
void EXTI_PORTC_IRQHandler(void) __interrupt(EXTI_PORTC_IRQHANDLER);
// PAS signal interrupt
void EXTI_PORTD_IRQHandler(void) __interrupt(EXTI_PORTD_IRQHANDLER);

// Timer1/PWM period interrupt
void TIM1_UPD_OVF_TRG_BRK_IRQHandler(void) __interrupt(TIM1_UPD_OVF_TRG_BRK_IRQHANDLER);

// Timer2/slow control loop
void TIM2_UPD_OVF_TRG_BRK_IRQHandler(void) __interrupt(TIM2_UPD_OVF_TRG_BRK_IRQHANDLER);


// UART2 receivce handler
void UART2_IRQHandler(void) __interrupt(UART2_IRQHANDLER);



int main(void) {
    //set clock at the max 16MHz
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);

    gpio_init();
    brake_init();
    while (brake_is_set());     // hold here while brake is pressed -- this is a protection for development
    debug_pin_init();
    light_pin_init();
    timer2_init();
	timer3_init();
    uart_init();
    eeprom_init();

    controllerstate_init();
    initErpsRatio();
    pwm_init();
    hall_sensor_init();
    adc_init();
    PAS_init();
    SPEED_init();
    aca_setpoint_init();

    #if (defined (DISPLAY_TYPE) && defined (DISPLAY_TYPE_KINGMETER)) || defined DISPLAY_TYPE_KT_LCD3 || defined BLUOSEC
    display_init();
    #endif

    //  ITC_SetSoftwarePriority (ITC_IRQ_TIM1_OVF, ITC_PRIORITYLEVEL_2);

    enableInterrupts();

    watchdog_init();     //init watchdog after enabling interrupt to have fast loop running already

    #if (SVM_TABLE == SVM)
    TIM1_SetCompare1(126 << 1);
    TIM1_SetCompare2(126 << 1);
    TIM1_SetCompare3(126 << 1);
    #elif (SVM_TABLE == SINE) || (SVM_TABLE == SINE_SVM)
    TIM1_SetCompare1(126 << 2);
    TIM1_SetCompare2(126 << 2);
    TIM1_SetCompare3(126 << 2);
    #endif

    hall_sensors_read_and_action();     // needed to start the motor

    #ifdef DIAGNOSTICS
    printf("System initialized\r\n");
    #endif

    while (1) {
		disableInterrupts();
            uart_send_if_avail();
		enableInterrupts();

        updatePasStatus();

        // scheduled update of setpoint and duty cycle (slow loop, 50 Hz)
        if (ui8_slowloop_flag) {
            ui8_slowloop_flag = 0;  //reset flag for slow loop
            #if (defined (DISPLAY_TYPE) && defined (DISPLAY_TYPE_KINGMETER)) || defined DISPLAY_TYPE_KT_LCD3 || defined BLUOSEC
            display_update();
            #endif
            //printf("MainSlowLoop\n");
            debug_pin_set();

            checkPasInActivity();
            updateRequestedTorque();
            updateSlowLoopStates();
            updateX4();
            updateLight();
            ui16_setpoint = (uint16_t) aca_setpoint(
                ui16_time_ticks_between_pas_interrupt,
                ui16_setpoint,
                brake_is_set(),
                ui16_adc_read_motor_total_current(),
                ui8_adc_read_battery_voltage()
                );         //update setpoint

            #if DO_CRUISE_CONTROL == 1
            ui16_setpoint = cruise_control(ui16_setpoint);
            #endif

            pwm_set_duty_cycle((uint8_t) ui16_setpoint);

            //pwm_set_duty_cycle ((uint8_t)ui16_sum_throttle);
            /****************************************************************************/
            //very slow loop for uart out
            ui8_veryslowloop_counter++;             // increase counter for very slow loop
            if (ui8_veryslowloop_counter > 5) { // 10 Hz
                ui8_veryslowloop_counter = 0;

                ui8_ultraslowloop_counter++;
                if (ui8_ultraslowloop_counter > 10) { // 1 Hz
                    ui8_ultraslowloop_counter = 0;
                    ui8_uptime_seconds++;


                #ifdef DIAGNOSTICS
                //uint32_torquesensorCalibration=80;
                printf("sp:%u cs:%u, ct:%u, pas:%u, bc:%u, bv:%u st:%u, tq:cal%u, mserps:%u, th:%u pBc:%u wrpms:%u wrps:%u st:%u verps:%u\r\n",
                       ui16_setpoint,
                       ui16_control_state,
                       (uint16_t) uint32_current_target,
                       PAS_is_active,
                       ui16_BatteryCurrent,
                       ui8_adc_read_battery_voltage(),
                       ui16_sum_torque,
                       (uint16_t)uint32_torquesensorCalibration,
                       ui16_motor_speed_erps,
                       ui8_adc_read_throttle(),
                       ui8_adc_read_phase_B_current(),
					   ui16_wheel_rotation_per_msec,
                       ui8_wheel_rotation_per_sec,
                       ui16_sum_throttle,
                       ui16_virtual_erps_speed
                       );

                #endif
				}
            }            //end of very slow loop

            debug_pin_reset();
        }        // end of slow loop
    }    // end of while(1) loop
}


