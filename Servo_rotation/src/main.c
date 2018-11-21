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


#define LED_PORT	LED0_GPIO_PORT
#define LED			LED0_GPIO_PIN

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

//given the current time, calculate the length of time until the next feeding time.
//next feeding time must be the next 
u32_t get_time_to(u32_t start_time, u32_t end_time)
{
    u32_t time_diff_in_mins = 0;
    u32_t start_min = start_time % 100;
    u32_t start_hour = start_time / 100;
    u32_t end_min = end_time % 100;
    u32_t end_hour = end_time / 100;

    if (end_time < start_time)
    {
        end_hour += 12;
        time_diff_in_mins += 12*60;
    }
    if (end_min > start_min)
    {
        time_diff_in_mins += end_min - start_min;
        time_diff_in_mins += 60*(end_hour - start_hour); 
    }
    else
    {
        time_diff_in_mins += 60 - start_min + end_min;
        start_hour += 1;
        time_diff_in_mins += 60*(end_hour - start_hour);
    }
    
    
    return time_diff_in_mins * 60000;
}

void main(void)
{
	//setup
	struct device *pwm_dev;
	struct device *btn_dev;
	struct device *led_dev;
	u32_t time_stamp;
	u32_t milliseconds_spent;
	
	led_dev = device_get_binding(LED_PORT);
	gpio_pin_configure(led_dev, LED, GPIO_DIR_OUT);

	btn_dev = device_get_binding(BTN_PORT);
	gpio_pin_configure(btn_dev, BTN, GPIO_DIR_IN | GPIO_PUD_PULL_UP);
	printk("PWM servo control 90degree clockwise -> 90degree anticlockwise\n");
	pwm_dev = device_get_binding(PWM_DRIVER);
	if (!pwm_dev) {
		printk("Cannot find %s!\n", PWM_DRIVER);
		return;
	}

	/* capture initial time stamp */
	time_stamp = k_uptime_get_32();
	u32_t time_until = get_time_to(1501, 1502) + time_stamp;
	printf("%" PRIu32 "\n", time_stamp);
	printf("%" PRIu32 "\n", time_until);

	while (1) {
		/* compute how long the work took (also updates the time stamp) */
		milliseconds_spent = k_uptime_get_32();
		if(milliseconds_spent >= (time_until) && milliseconds_spent <=(time_until+1000)){
			printf("%" PRIu32 "\n", milliseconds_spent);
			gpio_pin_write(led_dev, LED, 0);
			fill_up(pwm_dev);
			k_sleep(MSEC_PER_SEC);
			time_stamp = k_uptime_get_32();
		}
		gpio_pin_write(led_dev, LED, 1);
	}
}
