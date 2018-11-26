#include <zephyr.h>
#include <board.h>
#include <device.h>
#include <adc.h>
#include <hal/nrf_saadc.h>
#include <misc/printk.h>
#include <nrf_gpio.h>
#include <pwm.h>
#include <gpio.h>
#include "fsr.h"

#define PWM_DRIVER CONFIG_PWM_NRF5_SW_0_DEV_NAME
#define PWM_CHANNEL LED0_GPIO_PIN
#define YOUR_PIN	NRF_GPIO_PIN_MAP(0,22)
#define PORT	CONFIG_GPIO_NRF5_P0_DEV_NAME
#define PIN		11

#define BTN_PORT	SW0_GPIO_CONTROLLER
#define BTN		SW0_GPIO_PIN


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

void fill_up(struct device *pwm_dev, int sample){
	while(sample < 100){
		turn_clockwise(pwm_dev);
		pwm_pin_set_usec(pwm_dev, YOUR_PIN, 0, 0);
		k_sleep(MSEC_PER_SEC/20);
		turn_anticlockwise(pwm_dev);
		pwm_pin_set_usec(pwm_dev, YOUR_PIN, 0, 0);
		sample = sampling();
		//k_sleep(MSEC_PER_SEC);
	}
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