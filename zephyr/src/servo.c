#include <zephyr.h>
#include <board.h>
#include <device.h>
#include <adc.h>
#include <hal/nrf_saadc.h>
#include <misc/printk.h>
#include <nrf_gpio.h>
#include <pwm.h>
#include <gpio.h>
#include "config.h"
#include "fsr.h"

#define SERVO_PIN	NRF_GPIO_PIN_MAP(0,22)

#define BTN_PORT	SW0_GPIO_CONTROLLER
#define BTN		SW0_GPIO_PIN


#define PERIOD (USEC_PER_SEC / 50)

struct device *servo;


void turn_clockwise ()
{
	u32_t pulse_width = PERIOD;
	if (pwm_pin_set_usec(servo, SERVO_PIN, PERIOD, pulse_width)) {
		printk("pwm pin set fails\n");
		return;
	}
	pulse_width -=200;
	k_sleep(90);
	if (pwm_pin_set_usec(servo, SERVO_PIN, PERIOD, pulse_width)) {
		printk("pwm pin set fails\n");
		return;
	}
	pulse_width = -200;
	k_sleep(90);
	if (pwm_pin_set_usec(servo, SERVO_PIN, PERIOD, pulse_width)) {
		printk("pwm pin set fails\n");
		return;
	}
}

void turn_anticlockwise ()
{
	u32_t pulse_width = 0;
	if (pwm_pin_set_usec(servo, SERVO_PIN, PERIOD, pulse_width)) {
		printk("pwm pin set fails\n");
		return;
	}
	pulse_width +=200;
	k_sleep(90);
	if (pwm_pin_set_usec(servo, SERVO_PIN, PERIOD, pulse_width)) {
		printk("pwm pin set fails\n");
		return;
	}
	pulse_width += 200;
	k_sleep(90);
	if (pwm_pin_set_usec(servo, SERVO_PIN, PERIOD, pulse_width)) {
		printk("pwm pin set fails\n");
		return;
	}
}

void dispense_quarter()
{
	turn_clockwise(servo);
	pwm_pin_set_usec(servo, SERVO_PIN, 0, 0);
	k_sleep(MSEC_PER_SEC);
	turn_anticlockwise(servo);
	pwm_pin_set_usec(servo, SERVO_PIN, 0, 0);
}


//Fills the bowl up to max if not full
void maybe_fill_up(int sample)
{
	sample = sample_weight();
	while(sample < 100){
		dispense_quarter();
		sample = sample_weight();
	}
}

void setup_servo(struct device *servo_in)
{
	servo = servo_in;
}