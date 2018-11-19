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

#define BTN_PORT1	SW1_GPIO_NAME
#define BTN1		SW1_GPIO_PIN

/*
 * 50 is flicker fusion threshold. Modulated light will be perceived
 * as steady by our eyes when blinking rate is at least 50.
 */
#define PERIOD (USEC_PER_SEC / 50)

/* in micro second */
#define FADESTEP	3000

void turn_clockwise (struct device *pwm_dev, u32_t pulse_width){
		pulse_width = PERIOD;
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
void turn_anticlockwise (struct device *pwm_dev, u32_t pulse_width){
		pulse_width = 0;
		if (pwm_pin_set_usec(pwm_dev, YOUR_PIN, PERIOD, pulse_width)) {
			printk("pwm pin set fails\n");
			return;
		}
		pulse_width +=200;
		k_sleep(180);
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
void main(void)
{
	struct device *pwm_dev;
	struct device *btn_dev;
	struct device *btn_dev1;
	u32_t cur_val;
	u32_t last_val = 1;

	u32_t cur_val1;
	u32_t last_val1 = 1;

	btn_dev = device_get_binding(BTN_PORT);
	gpio_pin_configure(btn_dev, BTN, GPIO_DIR_IN | GPIO_PUD_PULL_UP);

	btn_dev1 = device_get_binding(BTN_PORT1);
	gpio_pin_configure(btn_dev1, BTN1, GPIO_DIR_IN | GPIO_PUD_PULL_UP);

	//struct device *pwm_dev2;
	u32_t pulse_width = PERIOD;
	u8_t dir = 0;

	printk("PWM demo app-fade LED\n");
	//nrf_gpio_cfg_output(YOUR_PIN);

	pwm_dev = device_get_binding(PWM_DRIVER);
	
	if (!pwm_dev) {
		printk("Cannot find %s!\n", PWM_DRIVER);
		return;
	}


	while (1) {

		gpio_pin_read(btn_dev, BTN, &cur_val);
		gpio_pin_read(btn_dev1, BTN1, &cur_val1);
		if (cur_val == 0 && last_val == 1) {
			printk("Button press detected ");
			turn_clockwise(pwm_dev, pulse_width);
		}
		if (cur_val1 == 0 && last_val1 == 1) {
			printk("Button press detected ");
			turn_anticlockwise(pwm_dev, pulse_width);
		}
		if (pwm_pin_set_usec(pwm_dev, YOUR_PIN, 0, 0)) {
			printk("pwm pin set fails\n");
			return;
		}
		last_val = cur_val;
		last_val1 = cur_val1;
		//k_sleep(MSEC_PER_SEC);
		
	}
}
