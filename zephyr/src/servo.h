#ifndef __SERVO_H__
#define __SERVO_H__

#include <device.h>

extern struct device *servo;

void setup_servo();
void maybe_fill_up(int sample);
void dispense_quarter();

#endif
