/*
 * OpenSource EBike firmware
 *
 * Copyright (C) Stancecoke 2017.
 *
 * Released under the GPL License, Version 3
 */

#ifndef _SPEED_H
#define _SPEED_H

void SPEED_init (void);

extern volatile uint16_t ui16_wheel_rotation_per_msec;
extern volatile uint8_t ui8_wheel_rotation_per_sec;

#endif /* _SPEED_H */
