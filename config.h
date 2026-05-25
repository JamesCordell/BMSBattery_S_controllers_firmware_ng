/*
 * config.h
 *
 *  Automatically created by OSEC Parameter Configurator
 *  Author: stancecoke
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#define NUMBER_OF_PAS_MAGS 12                   # The number of magnets on the crank used by the PAS sensor.
#define limit 15                                # Overall maximum speed limit
#define limit_with_throttle_override 40
#define limit_without_pas 80                    # The speed limit without pedal asssit.
#define timeout 3125        
#define wheel_circumference 2040L               # The distance in mm the wheel covers in one revolution. 

#define ADC_THROTTLE_MIN_VALUE 46               # The Miinimum throttle value
#define ADC_THROTTLE_MAX_VALUE 180              # The Maximum throttle value

#define BATTERY_VOLTAGE_MIN_VALUE 300           # Used to calibrate how full the battery is.
#define BATTERY_VOLTAGE_MAX_VALUE 650

#define BATTERY_CURRENT_MAX_VALUE 220L          # Limits the maximum current.
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
//#define BLUOSEC                               # Bluetooth on the serial port and phone app.
//#define DISPLAY_TYPE DISPLAY_TYPE_KINGMETER_618U
//#define DISPLAY_TYPE DISPLAY_TYPE_KINGMETER_901U
#define DIAGNOSTICS                             # Serial 9600 8N1 

#define ANGLE_4_0 1
<<<<<<< Updated upstream
#define ANGLE_6_60 41
#define ANGLE_2_120 84
#define ANGLE_3_180 129
#define DISPLAY_TYPE_KT_LCD3
#define ANGLE_1_240 167
#define ANGLE_5_300 212
=======
#define ANGLE_6_60 43
#define ANGLE_2_120 86
#define ANGLE_3_180 128
#define ANGLE_1_240 171
#define ANGLE_5_300 213


>>>>>>> Stashed changes
#define TQS_CALIB 0.0
#define ACA 128 + 4096 + 512 + 8192

// AssistLevelInfluencesThrottle	+ 1
// OffroadEnabled	+ 2
// BrakeDisablesOffroad	+ 4
// DigitalRegen	+ 8
// SpeedInfluencesRegen	+ 16
// SpeedInfluencesTqSensor	+ 32
// PasInverted	+ 64
// Default Baseline Flag	+ 128
// BypassLowSpeedRegenPiControl	+ 256
// DynAssist	+ 512
// PowerBasedControlEnabled	+ 1024
// TorqueSensor	+ 2048
// CorrectionEnabled	+ 4096
// IdleDisablesOffroad	+ 16384
// ExternalSpeedSensor	+ 8192

#define EEPROM_INIT_MAGIC_BYTE 240 // makes sure (chance of fail 1/255) eeprom is invalidated after flashing new config
#define ADC_BATTERY_VOLTAGE_K 80
#define ACA_EXPERIMENTAL 128 + 8

// cbDcNull + 1 
// AntiJitter + 2
// DisableInterpolation + 4
// Disable60DegInterpolation + 8
// Switch360 + 16
// default + 128;
// HighSpeedMotor + 256
// PwmOff + 1024

#endif /* CONFIG_H_ */
