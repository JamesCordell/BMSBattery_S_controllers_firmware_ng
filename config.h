/*
 * config.h
 *
 *  Automatically created by OSEC Parameter Configurator
 *  Author: stancecoke
 */

#ifndef CONFIG_H_
#define CONFIG_H_

/* Unless there is a L in the number all values can only be a minimum of 0 through to 255*/

#define NUMBER_OF_PAS_MAGS 12                   // The number of magnets on the crank used by the PAS sensor.
#define wheel_circumference 1040L               // The distance in mm the wheel covers in one revolution.
#define limit 80                                // Overall maximum speed limit, all speeds are in k/h
#define limit_with_throttle_override 80
#define limit_without_pas 80                    // The speed limit without pedal asssit.
#define timeout 3125U

#define ADC_THROTTLE_MIN_VALUE 46               // The Miinimum throttle value
#define ADC_THROTTLE_MAX_VALUE 181              // The Maximum throttle value
#define DO_CRUISE_CONTROL 0                     // Cruise control

#define BATTERY_VOLTAGE_MIN_VALUE 0           // Used to calibrate how full the battery is.
#define BATTERY_VOLTAGE_MAX_VALUE 255

#define BATTERY_CURRENT_MAX_VALUE 420L          // Limits the maximum current.
#define PHASE_CURRENT_MAX_VALUE 100L
#define REGEN_CURRENT_MAX_VALUE 40L
#define current_cal_a 1

#define MOTOR_ROTOR_DELTA_PHASE_ANGLE_RIGHT 0

/* How much each PAS level should assist. From 0 to 100 */
#define LEVEL_1 30
#define LEVEL_2 45
#define LEVEL_3 60
#define LEVEL_4 80
#define LEVEL_5 100

#define MORSE_TIME_1 50
#define MORSE_TIME_2 50
#define MORSE_TIME_3 50

#define RAMP_START 64000
#define RAMP_END 1500

#define P_FACTOR 0.5
#define I_FACTOR 0.1
#define GEAR_RATIO 106L
#define PAS_THRESHOLD 1.9

#define CORRECTION_AT_ANGLE 127

/* Set one type of display type. */
//#define DISPLAY_TYPE_KT_LCD3
//#define BLUOSEC                               // Bluetooth on the serial port and phone app.

/* enable these lines to set this display type.
 #define DISPLAY_TYPE_KINGMETER_618U (1<<4)      // King-Meter 618U protocol (KM5s, EBS-LCD2, J-LCD, SW-LCD)
 #define DISPLAY_TYPE_KINGMETER (DISPLAY_TYPE_KINGMETER_618U|DISPLAY_TYPE_KINGMETER_901U)
 #define DISPLAY_TYPE DISPLAY_TYPE_KINGMETER     // Set your display type here. CHANGES ONLY HERE!
 */
#define DIAGNOSTICS                             // Serial 9600 8N1

#define ANGLE_4_0 1
#define ANGLE_6_60 43
#define ANGLE_2_120 86
#define ANGLE_3_180 128
#define ANGLE_1_240 171
#define ANGLE_5_300 213


#define TQS_CALIB 0.0

#define CFG_ASSIST_LEVEL_INFLUENCES_THROTTLE    1U
#define CFG_OFFROAD_ENABLED                     2U
#define CFG_BRAKE_DISABLES_OFFROAD              4U
#define CFG_DIGITAL_REGEN                       8U
#define CFG_SPEED_INFLUENCES_REGEN              16U
#define CFG_SPEED_INFLUENCES_TQ_SENSOR          32U
#define CFG_PAS_INVERTED                        64U
#define CFG_DEFAULT_BASELINE_FLAG               128U
#define CFG_BYPASS_LOW_SPEED_REGEN_PI_CONTROL   256U
#define CFG_DYN_ASSIST                          512U
#define CFG_POWER_BASED_CONTROL_ENABLED         1024U
#define CFG_TQ_SENSOR_MODE                      2048U
#define CFG_CORRECTION_ENABLED                  4096U
#define CFG_EXTERNAL_SPEED_SENSOR               8192U  // Enabling this adds throttle delay.
#define CFG_IDLE_DISABLES_OFFROAD               16384U

#define ACA (CFG_DEFAULT_BASELINE_FLAG | CFG_CORRECTION_ENABLED | CFG_DYN_ASSIST | CFG_TQ_SENSOR_MODE)


#define EEPROM_INIT_MAGIC_BYTE 240              // makes sure (chance of fail 1/255) eeprom is invalidated after flashing new config
#define ADC_BATTERY_VOLTAGE_K 80


#define CFG_DC_STATIC_ZERO                  1U      // Used to test the wheel and motor. Do not enable for normal use.
#define CFG_AVOID_MOTOR_CYCLES_JITTER       2U
#define CFG_DISABLE_INTERPOLATION           4U
#define CFG_DISABLE_60_DEG_INTERPOLATION    8U
#define CFG_SWITCH_360_DEG_INTERPOLATION    16U
#define CFG_USE_ALTERNATE_WAVETABLE         32U
#define CFG_USE_ALTERNATE_WAVETABLE_B       64U
#define CFG_DUMMY_EXP_ALWAYS_ON             128U    // The default
#define CFG_HIGH_SPEED_MOTOR                256U
#define CFG_PWM_AUTO_OFF                    1024U

#define ACA_EXPERIMENTAL (CFG_DUMMY_EXP_ALWAYS_ON)

#endif /* CONFIG_H_ */
