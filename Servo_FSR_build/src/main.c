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
#include "servo.h"

#define ADC_DEVICE_NAME		CONFIG_ADC_0_NAME
#define ADC_RESOLUTION		10
#define ADC_GAIN		ADC_GAIN_1_6
#define ADC_REFERENCE		ADC_REF_INTERNAL
#define ADC_ACQUISITION_TIME	ADC_ACQ_TIME(ADC_ACQ_TIME_MICROSECONDS, 10)
#define ADC_1ST_CHANNEL_ID	0
#define ADC_1ST_CHANNEL_INPUT	NRF_SAADC_INPUT_AIN1
#define ADC_2ND_CHANNEL_ID	2
#define ADC_2ND_CHANNEL_INPUT	NRF_SAADC_INPUT_AIN2

#define PWM_DRIVER CONFIG_PWM_NRF5_SW_0_DEV_NAME
#define PWM_CHANNEL LED0_GPIO_PIN
#define YOUR_PIN	NRF_GPIO_PIN_MAP(0,22)
#define PORT	CONFIG_GPIO_NRF5_P0_DEV_NAME
#define PIN		11

#define BTN_PORT	SW0_GPIO_CONTROLLER
#define BTN		SW0_GPIO_PIN


#define PERIOD (USEC_PER_SEC / 50)
#define BUFFER_SIZE  6


void main(void)
{
	int a;
	printf("Preparing ADC\n");

	//setup
	struct device *pwm_dev;
	struct device *btn_dev;
	
	u32_t time_stamp;
	u32_t milliseconds_spent;
	

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
	time_until = time_until / 6;
	printf("%" PRIu32 "\n", time_stamp);
	printf("%" PRIu32 "\n", time_until);



	while (true) {
		k_sleep(500);
		int b = sample_sensor(ADC_1ST_CHANNEL_ID);
		printf("%d \n", b);

		/* compute how long the work took (also updates the time stamp) */
		milliseconds_spent = k_uptime_get_32();
		if(milliseconds_spent >= (time_until) && milliseconds_spent <=(time_until+1000)){
			a = sampling();
			printf("%d sample \n", a);
			printf("%" PRIu32 "\n", milliseconds_spent);
			fill_up(pwm_dev, 50);
			k_sleep(MSEC_PER_SEC);
			time_stamp = k_uptime_get_32();
		}

	}
}
