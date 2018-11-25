#include <zephyr.h>
#include <board.h>
#include <device.h>
#include <adc.h>
#include <hal/nrf_saadc.h>
#include <misc/printk.h>
#include <nrf_gpio.h>
#include <pwm.h>
#include <gpio.h>


#define ADC_DEVICE_NAME		CONFIG_ADC_0_NAME
#define ADC_RESOLUTION		10
#define ADC_GAIN		ADC_GAIN_1_6
#define ADC_REFERENCE		ADC_REF_INTERNAL
#define ADC_ACQUISITION_TIME	ADC_ACQ_TIME(ADC_ACQ_TIME_MICROSECONDS, 10)
#define ADC_1ST_CHANNEL_ID	0
#define ADC_1ST_CHANNEL_INPUT	NRF_SAADC_INPUT_AIN1
#define ADC_2ND_CHANNEL_ID	2
#define ADC_2ND_CHANNEL_INPUT	NRF_SAADC_INPUT_AIN2

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
	const struct adc_sequence sequence = {
		.channels    = BIT(channel_id),
		.buffer      = m_sample_buffer,
		.buffer_size = sizeof(m_sample_buffer),
		.resolution  = ADC_RESOLUTION,
	};
	struct device *adc_dev = init_adc();	
	int ret;

	if (!adc_dev) {
		printf("Failed to initialise ADC");
		return -1;
	}

	ret = adc_read(adc_dev, &sequence);

	if (ret) {
		printf("Failed to read ADC with code %d\n", ret);
		return -1;
	}

	return m_sample_buffer[0];
}

int sample_weight()
{
	int sample;
	int bowlFill;
	for(int i = 0; i < 4; i++){
		k_sleep(500);
		printk("Sampling force sensor...\n");

		sample = sample_sensor(ADC_1ST_CHANNEL_ID);

		if(sample < 200){
			printf("Bowl is emptyish\n");
			bowlFill = 0;
		} else if(sample >= 200 && sample <= 370){
			printf("Bowl is 1/4 fullish\n");
			bowlFill = 25;
		} else if(sample > 370 && sample <= 500){
			printf("Bowl is 1/2 fullish\n");
			bowlFill = 50;
		} else if(sample > 500 && sample <= 580){
			printf("Bowl is 3/4 fullish\n");
			bowlFill = 75;
		} else{
			printf("Bowl is fullish\n");
			bowlFill = 100;
		}

		printk("%d \n", sample);
	}
	return bowlFill;
}


