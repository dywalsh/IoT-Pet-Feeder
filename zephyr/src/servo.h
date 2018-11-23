#ifndef __SERVO_H__
#define __SERVO_H__

#include <device.h>

extern struct device *servo;
void fill_up(int sample);

void setup_servo();
#endif
