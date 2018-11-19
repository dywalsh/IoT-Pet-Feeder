/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file Sample app to demonstrate PWM.
 *
 * This app uses PWM[0].
 */

#include <zephyr.h>
//#include <misc/printk.h>
#include <device.h>
#include <pwm.h>
#include <gpio.h>
#include <nrf_gpio.h>

#include <board.h>
#define PWM_DRIVER CONFIG_PWM_NRF5_SW_0_DEV_NAME
#define PWM_CHANNEL LED0_GPIO_PIN
#define YOUR_PIN	NRF_GPIO_PIN_MAP(0,22)
#define PORT	CONFIG_GPIO_NRF5_P0_DEV_NAME
#define PIN		11

#define BTN_PORT	SW0_GPIO_NAME
#define BTN			SW0_GPIO_PIN

/*
 * 50 is flicker fusion threshold. Modulated light will be perceived
 * as steady by our eyes when blinking rate is at least 50.
 */
#define PERIOD (USEC_PER_SEC / 50)

void turn_clockwise (struct device *pwm_dev){
		u32_t pulse_width = PERIOD;
		if (pwm_pin_set_usec(pwm_dev, YOUR_PIN, PERIOD, pulse_width)) {
			printk("pwm pin set fails\n");
			return;
		}
		pulse_width -=200;
		k_sleep(90);
		if (pwm_pin_set_usec(pwm_dev, YOUR_PIN, PERIOD, pulse_width)) {
			printk("pwm pin set fails\n");
			return;
		}
		pulse_width = -200;
		k_sleep(90);
		if (pwm_pin_set_usec(pwm_dev, YOUR_PIN, PERIOD, pulse_width)) {
			printk("pwm pin set fails\n");
			return;
		}
}

void turn_anticlockwise (struct device *pwm_dev){
		u32_t pulse_width = 0;
		if (pwm_pin_set_usec(pwm_dev, YOUR_PIN, PERIOD, pulse_width)) {
			printk("pwm pin set fails\n");
			return;
		}
		pulse_width +=200;
		k_sleep(90);
		if (pwm_pin_set_usec(pwm_dev, YOUR_PIN, PERIOD, pulse_width)) {
			printk("pwm pin set fails\n");
			return;
		}
		pulse_width += 200;
		k_sleep(90);
		if (pwm_pin_set_usec(pwm_dev, YOUR_PIN, PERIOD, pulse_width)) {
			printk("pwm pin set fails\n");
			return;
		}
}

void fill_up(struct device *pwm_dev){
	turn_clockwise(pwm_dev);
	pwm_pin_set_usec(pwm_dev, YOUR_PIN, 0, 0);
	k_sleep(MSEC_PER_SEC);
	turn_anticlockwise(pwm_dev);
	pwm_pin_set_usec(pwm_dev, YOUR_PIN, 0, 0);
}

void main(void)
{
	//setup
	struct device *pwm_dev;
	struct device *btn_dev;
	u32_t cur_val;
	u32_t last_val = 1;
	btn_dev = device_get_binding(BTN_PORT);
	gpio_pin_configure(btn_dev, BTN, GPIO_DIR_IN | GPIO_PUD_PULL_UP);
	printk("PWM servo control 90degree clockwise -> 90degree anticlockwise\n");
	pwm_dev = device_get_binding(PWM_DRIVER);
	if (!pwm_dev) {
		printk("Cannot find %s!\n", PWM_DRIVER);
		return;
	}

	while (1) {
		//Turn motor on button press
		gpio_pin_read(btn_dev, BTN, &cur_val);
		if (cur_val == 0 && last_val == 1) {
			printk("Button press detected ");
			fill_up(pwm_dev);
		}
		last_val = cur_val;		
	}
}
