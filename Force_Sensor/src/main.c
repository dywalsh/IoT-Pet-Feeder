//
// Very basic photoresistor example
//

#include <zephyr.h>
#include <board.h>
#include <device.h>
#include <adc.h>
#include <hal/nrf_saadc.h>
#include <misc/printk.h>
#include <nrf_gpio.h>
#include <pwm.h>


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

#define BTN_PORT	SW0_GPIO_NAME
#define BTN			SW0_GPIO_PIN

#define LED_PORT	LED0_GPIO_PORT
#define LED			LED0_GPIO_PIN

#define PERIOD (USEC_PER_SEC / 50)
#define BUFFER_SIZE  6

static s16_t m_sample_buffer[BUFFER_SIZE];

static const struct adc_channel_cfg m_1st_channel_cfg = {
	.gain             = ADC_GAIN,
	.reference        = ADC_REFERENCE,
	.acquisition_time = ADC_ACQUISITION_TIME,
	.channel_id       = ADC_1ST_CHANNEL_ID,
#if defined(CONFIG_ADC_CONFIGURABLE_INPUTS)
	.input_positive   = ADC_1ST_CHANNEL_INPUT,
#endif
};
#if defined(ADC_2ND_CHANNEL_ID)
static const struct adc_channel_cfg m_2nd_channel_cfg = {
	.gain             = ADC_GAIN,
	.reference        = ADC_REFERENCE,
	.acquisition_time = ADC_ACQUISITION_TIME,
	.channel_id       = ADC_2ND_CHANNEL_ID,
#if defined(CONFIG_ADC_CONFIGURABLE_INPUTS)
	.input_positive   = ADC_2ND_CHANNEL_INPUT,
#endif
};
#endif /* defined(ADC_2ND_CHANNEL_ID) */


static struct device *init_adc(void)
{
	int ret;
	struct device *adc_dev = device_get_binding(ADC_DEVICE_NAME);

	if (!adc_dev) {
		printf("Cannot get ADC device");
		return;
	}

	ret = adc_channel_setup(adc_dev, &m_1st_channel_cfg);
	if (ret) {
		printf("Setting up of the first channel failed with code %d", ret);
	}

#if defined(ADC_2ND_CHANNEL_ID)
	ret = adc_channel_setup(adc_dev, &m_2nd_channel_cfg);
	if (ret) {
		printf("Setting up of the second channel failed with code %d", ret);
	}
#endif /* defined(ADC_2ND_CHANNEL_ID) */

	(void)memset(m_sample_buffer, 0, sizeof(m_sample_buffer));

	return adc_dev;
}


int sample_sensor (int channel_id)
{
	int ret;

	const struct adc_sequence sequence = {
		.channels    = BIT(channel_id),
		.buffer      = m_sample_buffer,
		.buffer_size = sizeof(m_sample_buffer),
		.resolution  = ADC_RESOLUTION,
	};

	struct device *adc_dev = init_adc();

	if (!adc_dev) {
		printf("Failed to initialise ADC");
		return -1;
	}

	ret = adc_read(adc_dev, &sequence);

	if (ret) {
		printf("Failed to read ADC with code %d", ret);
	}

	return m_sample_buffer[0];
}

//==========================================================================


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
	int sample;

	printf("Preparing ADC\n");

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



	while (true) {

		// delay between samples
		k_sleep(500);
		printk("\nSampling ... ");

		sample = sample_sensor(ADC_1ST_CHANNEL_ID);

		if(sample < 200){
			printf("Bowl is emptyish");
		} else if(sample >= 200 && sample <= 370){
			printf("Bowl is 1/4 fullish");
		} else if(sample > 370 && sample <= 500){
			printf("Bowl is 1/2 fullish");
		} else if(sample > 500 && sample <= 580){
			printf("Bowl is 3/4 fullish");
		} else{
			printf("Bowl is fullish");
		}

		printk("%d \n", sample);

		/* compute how long the work took (also updates the time stamp) */
		milliseconds_spent = k_uptime_get_32();
		if(milliseconds_spent >= (time_until) && milliseconds_spent <=(time_until+1500)){
			printf("%" PRIu32 "\n", milliseconds_spent);
			gpio_pin_write(led_dev, LED, 0);
			fill_up(pwm_dev);
			k_sleep(MSEC_PER_SEC);
			time_stamp = k_uptime_get_32();
		}
		gpio_pin_write(led_dev, LED, 1);

	}
}
