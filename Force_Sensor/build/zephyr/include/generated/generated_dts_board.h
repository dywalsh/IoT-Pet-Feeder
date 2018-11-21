/**************************************************
 * Generated include file for nordic,pca10040-dk
 *               DO NOT MODIFY
 */

#ifndef DEVICE_TREE_BOARD_H
#define DEVICE_TREE_BOARD_H

/* button_0 */
#define GPIO_KEYS_BUTTON_0_GPIO_CONTROLLER	"GPIO_0"
#define GPIO_KEYS_BUTTON_0_GPIO_FLAGS		256
#define GPIO_KEYS_BUTTON_0_GPIO_PIN		13
#define GPIO_KEYS_BUTTON_0_LABEL		"Push button switch 0"
#define SW0_GPIO_CONTROLLER			GPIO_KEYS_BUTTON_0_GPIO_CONTROLLER
#define SW0_GPIO_FLAGS				GPIO_KEYS_BUTTON_0_GPIO_FLAGS
#define SW0_GPIO_PIN				GPIO_KEYS_BUTTON_0_GPIO_PIN
#define SW0_LABEL				GPIO_KEYS_BUTTON_0_LABEL

/* button_1 */
#define GPIO_KEYS_BUTTON_1_GPIO_CONTROLLER	"GPIO_0"
#define GPIO_KEYS_BUTTON_1_GPIO_FLAGS		256
#define GPIO_KEYS_BUTTON_1_GPIO_PIN		14
#define GPIO_KEYS_BUTTON_1_LABEL		"Push button switch 1"
#define SW1_GPIO_CONTROLLER			GPIO_KEYS_BUTTON_1_GPIO_CONTROLLER
#define SW1_GPIO_FLAGS				GPIO_KEYS_BUTTON_1_GPIO_FLAGS
#define SW1_GPIO_PIN				GPIO_KEYS_BUTTON_1_GPIO_PIN
#define SW1_LABEL				GPIO_KEYS_BUTTON_1_LABEL

/* button_2 */
#define GPIO_KEYS_BUTTON_2_GPIO_CONTROLLER	"GPIO_0"
#define GPIO_KEYS_BUTTON_2_GPIO_FLAGS		256
#define GPIO_KEYS_BUTTON_2_GPIO_PIN		15
#define GPIO_KEYS_BUTTON_2_LABEL		"Push button switch 2"
#define SW2_GPIO_CONTROLLER			GPIO_KEYS_BUTTON_2_GPIO_CONTROLLER
#define SW2_GPIO_FLAGS				GPIO_KEYS_BUTTON_2_GPIO_FLAGS
#define SW2_GPIO_PIN				GPIO_KEYS_BUTTON_2_GPIO_PIN
#define SW2_LABEL				GPIO_KEYS_BUTTON_2_LABEL

/* button_3 */
#define GPIO_KEYS_BUTTON_3_GPIO_CONTROLLER	"GPIO_0"
#define GPIO_KEYS_BUTTON_3_GPIO_FLAGS		256
#define GPIO_KEYS_BUTTON_3_GPIO_PIN		16
#define GPIO_KEYS_BUTTON_3_LABEL		"Push button switch 3"
#define SW3_GPIO_CONTROLLER			GPIO_KEYS_BUTTON_3_GPIO_CONTROLLER
#define SW3_GPIO_FLAGS				GPIO_KEYS_BUTTON_3_GPIO_FLAGS
#define SW3_GPIO_PIN				GPIO_KEYS_BUTTON_3_GPIO_PIN
#define SW3_LABEL				GPIO_KEYS_BUTTON_3_LABEL

/* flash-controller@4001E000 */
#define NRF_NRF52_FLASH_CONTROLLER_4001E000_BASE_ADDRESS	0x4001e000
#define NRF_NRF52_FLASH_CONTROLLER_4001E000_LABEL		"NRF_FLASH_DRV_NAME"
#define NRF_NRF52_FLASH_CONTROLLER_4001E000_SIZE		1360

/* flash@0 */
#define CONFIG_FLASH_BASE_ADDRESS		0x0
#define CONFIG_FLASH_LOAD_OFFSET		0
#define CONFIG_FLASH_LOAD_SIZE			0
#define CONFIG_FLASH_SIZE			512
#define FLASH_ERASE_BLOCK_SIZE			4096
#define FLASH_LABEL				"NRF_FLASH"
#define FLASH_WRITE_BLOCK_SIZE			4
#define SOC_NV_FLASH_0_ERASE_BLOCK_SIZE		4096
#define SOC_NV_FLASH_0_LABEL			"NRF_FLASH"
#define SOC_NV_FLASH_0_WRITE_BLOCK_SIZE		4

/* partition@0 */
#define FLASH_AREA_MCUBOOT_LABEL	"mcuboot"
#define FLASH_AREA_MCUBOOT_OFFSET_0	0
#define FLASH_AREA_MCUBOOT_READ_ONLY	0
#define FLASH_AREA_MCUBOOT_SIZE_0	49152
#define FLASH_AREA_MCUBOOT_OFFSET	FLASH_AREA_MCUBOOT_OFFSET_0
#define FLASH_AREA_MCUBOOT_SIZE		FLASH_AREA_MCUBOOT_SIZE_0

/* partition@3e000 */
#define FLASH_AREA_IMAGE_1_LABEL	"image-1"
#define FLASH_AREA_IMAGE_1_OFFSET_0	253952
#define FLASH_AREA_IMAGE_1_READ_ONLY	0
#define FLASH_AREA_IMAGE_1_SIZE_0	204800
#define FLASH_AREA_IMAGE_1_OFFSET	FLASH_AREA_IMAGE_1_OFFSET_0
#define FLASH_AREA_IMAGE_1_SIZE		FLASH_AREA_IMAGE_1_SIZE_0

/* partition@70000 */
#define FLASH_AREA_IMAGE_SCRATCH_LABEL		"image-scratch"
#define FLASH_AREA_IMAGE_SCRATCH_OFFSET_0	458752
#define FLASH_AREA_IMAGE_SCRATCH_READ_ONLY	0
#define FLASH_AREA_IMAGE_SCRATCH_SIZE_0		40960
#define FLASH_AREA_IMAGE_SCRATCH_OFFSET		FLASH_AREA_IMAGE_SCRATCH_OFFSET_0
#define FLASH_AREA_IMAGE_SCRATCH_SIZE		FLASH_AREA_IMAGE_SCRATCH_SIZE_0

/* partition@c000 */
#define FLASH_AREA_IMAGE_0_LABEL	"image-0"
#define FLASH_AREA_IMAGE_0_OFFSET_0	49152
#define FLASH_AREA_IMAGE_0_READ_ONLY	0
#define FLASH_AREA_IMAGE_0_SIZE_0	204800
#define FLASH_AREA_IMAGE_0_OFFSET	FLASH_AREA_IMAGE_0_OFFSET_0
#define FLASH_AREA_IMAGE_0_SIZE		FLASH_AREA_IMAGE_0_SIZE_0

/* led_0 */
#define GPIO_LEDS_LED_0_GPIO_CONTROLLER		"GPIO_0"
#define GPIO_LEDS_LED_0_GPIO_FLAGS		0
#define GPIO_LEDS_LED_0_GPIO_PIN		17
#define GPIO_LEDS_LED_0_LABEL			"Green LED 0"
#define LED0_GPIO_CONTROLLER			GPIO_LEDS_LED_0_GPIO_CONTROLLER
#define LED0_GPIO_FLAGS				GPIO_LEDS_LED_0_GPIO_FLAGS
#define LED0_GPIO_PIN				GPIO_LEDS_LED_0_GPIO_PIN
#define LED0_LABEL				GPIO_LEDS_LED_0_LABEL

/* led_1 */
#define GPIO_LEDS_LED_1_GPIO_CONTROLLER		"GPIO_0"
#define GPIO_LEDS_LED_1_GPIO_FLAGS		0
#define GPIO_LEDS_LED_1_GPIO_PIN		18
#define GPIO_LEDS_LED_1_LABEL			"Green LED 1"
#define LED1_GPIO_CONTROLLER			GPIO_LEDS_LED_1_GPIO_CONTROLLER
#define LED1_GPIO_FLAGS				GPIO_LEDS_LED_1_GPIO_FLAGS
#define LED1_GPIO_PIN				GPIO_LEDS_LED_1_GPIO_PIN
#define LED1_LABEL				GPIO_LEDS_LED_1_LABEL

/* led_2 */
#define GPIO_LEDS_LED_2_GPIO_CONTROLLER		"GPIO_0"
#define GPIO_LEDS_LED_2_GPIO_FLAGS		0
#define GPIO_LEDS_LED_2_GPIO_PIN		19
#define GPIO_LEDS_LED_2_LABEL			"Green LED 2"
#define LED2_GPIO_CONTROLLER			GPIO_LEDS_LED_2_GPIO_CONTROLLER
#define LED2_GPIO_FLAGS				GPIO_LEDS_LED_2_GPIO_FLAGS
#define LED2_GPIO_PIN				GPIO_LEDS_LED_2_GPIO_PIN
#define LED2_LABEL				GPIO_LEDS_LED_2_LABEL

/* led_3 */
#define GPIO_LEDS_LED_3_GPIO_CONTROLLER		"GPIO_0"
#define GPIO_LEDS_LED_3_GPIO_FLAGS		0
#define GPIO_LEDS_LED_3_GPIO_PIN		20
#define GPIO_LEDS_LED_3_LABEL			"Green LED 3"
#define LED3_GPIO_CONTROLLER			GPIO_LEDS_LED_3_GPIO_CONTROLLER
#define LED3_GPIO_FLAGS				GPIO_LEDS_LED_3_GPIO_FLAGS
#define LED3_GPIO_PIN				GPIO_LEDS_LED_3_GPIO_PIN
#define LED3_LABEL				GPIO_LEDS_LED_3_LABEL

/* memory@20000000 */
#define CONFIG_SRAM_BASE_ADDRESS	0x20000000
#define CONFIG_SRAM_SIZE		64

/* adc@40007000 */
#define NORDIC_NRF_SAADC_40007000_BASE_ADDRESS		0x40007000
#define NORDIC_NRF_SAADC_40007000_IRQ_0			7
#define NORDIC_NRF_SAADC_40007000_IRQ_0_PRIORITY	1
#define NORDIC_NRF_SAADC_40007000_LABEL			"ADC_0"
#define NORDIC_NRF_SAADC_40007000_SIZE			4096

/* gpio@50000000 */
#define NORDIC_NRF_GPIO_50000000_BASE_ADDRESS_0		0x50000000
#define NORDIC_NRF_GPIO_50000000_BASE_ADDRESS_1		0x50000500
#define NORDIC_NRF_GPIO_50000000_LABEL			"GPIO_0"
#define NORDIC_NRF_GPIO_50000000_SIZE_0			512
#define NORDIC_NRF_GPIO_50000000_SIZE_1			768

/* gpiote@40006000 */
#define NORDIC_NRF_GPIOTE_40006000_BASE_ADDRESS			0x40006000
#define NORDIC_NRF_GPIOTE_40006000_IRQ_0			6
#define NORDIC_NRF_GPIOTE_40006000_IRQ_0_PRIORITY		5
#define NORDIC_NRF_GPIOTE_40006000_LABEL			"GPIOTE_0"
#define NORDIC_NRF_GPIOTE_40006000_SIZE				4096
#define NORDIC_NRF_GPIOTE_40006000_IRQ_GPIOTE			NORDIC_NRF_GPIOTE_40006000_IRQ_0
#define NORDIC_NRF_GPIOTE_40006000_IRQ_GPIOTE_PRIORITY		NORDIC_NRF_GPIOTE_40006000_IRQ_0_PRIORITY

/* i2c@40003000 */
#define NORDIC_NRF_I2C_40003000_BASE_ADDRESS		0x40003000
#define NORDIC_NRF_I2C_40003000_CLOCK_FREQUENCY		100000
#define NORDIC_NRF_I2C_40003000_IRQ_0			3
#define NORDIC_NRF_I2C_40003000_IRQ_0_PRIORITY		1
#define NORDIC_NRF_I2C_40003000_LABEL			"I2C_0"
#define NORDIC_NRF_I2C_40003000_SCL_PIN			27
#define NORDIC_NRF_I2C_40003000_SDA_PIN			26
#define NORDIC_NRF_I2C_40003000_SIZE			4096

/* i2c@40004000 */
#define NORDIC_NRF_I2C_40004000_BASE_ADDRESS		0x40004000
#define NORDIC_NRF_I2C_40004000_CLOCK_FREQUENCY		100000
#define NORDIC_NRF_I2C_40004000_IRQ_0			4
#define NORDIC_NRF_I2C_40004000_IRQ_0_PRIORITY		1
#define NORDIC_NRF_I2C_40004000_LABEL			"I2C_1"
#define NORDIC_NRF_I2C_40004000_SCL_PIN			31
#define NORDIC_NRF_I2C_40004000_SDA_PIN			30
#define NORDIC_NRF_I2C_40004000_SIZE			4096

/* interrupt-controller@e000e100 */
#define ARM_V7M_NVIC_E000E100_ARM_NUM_IRQ_PRIORITY_BITS		3
#define ARM_V7M_NVIC_E000E100_BASE_ADDRESS			0xe000e100
#define ARM_V7M_NVIC_E000E100_SIZE				3072

/* spi@40003000 */
#define NORDIC_NRF_SPI_40003000_BASE_ADDRESS		0x40003000
#define NORDIC_NRF_SPI_40003000_IRQ_0			3
#define NORDIC_NRF_SPI_40003000_IRQ_0_PRIORITY		1
#define NORDIC_NRF_SPI_40003000_LABEL			"SPI_0"
#define NORDIC_NRF_SPI_40003000_MISO_PIN		25
#define NORDIC_NRF_SPI_40003000_MOSI_PIN		26
#define NORDIC_NRF_SPI_40003000_SCK_PIN			27
#define NORDIC_NRF_SPI_40003000_SIZE			4096

/* spi@40004000 */
#define NORDIC_NRF_SPI_40004000_BASE_ADDRESS		0x40004000
#define NORDIC_NRF_SPI_40004000_IRQ_0			4
#define NORDIC_NRF_SPI_40004000_IRQ_0_PRIORITY		1
#define NORDIC_NRF_SPI_40004000_LABEL			"SPI_1"
#define NORDIC_NRF_SPI_40004000_MISO_PIN		29
#define NORDIC_NRF_SPI_40004000_MOSI_PIN		30
#define NORDIC_NRF_SPI_40004000_SCK_PIN			31
#define NORDIC_NRF_SPI_40004000_SIZE			4096

/* spi@40023000 */
#define NORDIC_NRF_SPI_40023000_BASE_ADDRESS		0x40023000
#define NORDIC_NRF_SPI_40023000_IRQ_0			35
#define NORDIC_NRF_SPI_40023000_IRQ_0_PRIORITY		1
#define NORDIC_NRF_SPI_40023000_LABEL			"SPI_2"
#define NORDIC_NRF_SPI_40023000_MISO_PIN		24
#define NORDIC_NRF_SPI_40023000_MOSI_PIN		23
#define NORDIC_NRF_SPI_40023000_SCK_PIN			22
#define NORDIC_NRF_SPI_40023000_SIZE			4096

/* uart@40002000 */
#define CONFIG_UART_CONSOLE_ON_DEV_NAME			"UART_0"
#define CONFIG_UART_MCUMGR_ON_DEV_NAME			"UART_0"
#define NORDIC_NRF_UART_40002000_BASE_ADDRESS		0x40002000
#define NORDIC_NRF_UART_40002000_CTS_PIN		7
#define NORDIC_NRF_UART_40002000_CURRENT_SPEED		115200
#define NORDIC_NRF_UART_40002000_IRQ_0			2
#define NORDIC_NRF_UART_40002000_IRQ_0_PRIORITY		1
#define NORDIC_NRF_UART_40002000_LABEL			"UART_0"
#define NORDIC_NRF_UART_40002000_RTS_PIN		5
#define NORDIC_NRF_UART_40002000_RX_PIN			8
#define NORDIC_NRF_UART_40002000_SIZE			4096
#define NORDIC_NRF_UART_40002000_TX_PIN			6

/* watchdog@40010000 */
#define NORDIC_NRF_WATCHDOG_40010000_BASE_ADDRESS	0x40010000
#define NORDIC_NRF_WATCHDOG_40010000_IRQ_0		16
#define NORDIC_NRF_WATCHDOG_40010000_IRQ_0_PRIORITY	1
#define NORDIC_NRF_WATCHDOG_40010000_LABEL		"WDT"
#define NORDIC_NRF_WATCHDOG_40010000_SIZE		4096
#define NORDIC_NRF_WATCHDOG_40010000_IRQ_WDT		NORDIC_NRF_WATCHDOG_40010000_IRQ_0
#define NORDIC_NRF_WATCHDOG_40010000_IRQ_WDT_PRIORITY	NORDIC_NRF_WATCHDOG_40010000_IRQ_0_PRIORITY

/* compatibles */
#define DT_COMPAT_ARM_V7M_NVIC			1
#define DT_COMPAT_FIXED_PARTITIONS		1
#define DT_COMPAT_GPIO_KEYS			1
#define DT_COMPAT_GPIO_LEDS			1
#define DT_COMPAT_NORDIC_NRF_GPIO		1
#define DT_COMPAT_NORDIC_NRF_GPIOTE		1
#define DT_COMPAT_NORDIC_NRF_I2C		1
#define DT_COMPAT_NORDIC_NRF_SAADC		1
#define DT_COMPAT_NORDIC_NRF_SPI		1
#define DT_COMPAT_NORDIC_NRF_UART		1
#define DT_COMPAT_NORDIC_NRF_WATCHDOG		1
#define DT_COMPAT_NRF_NRF52_FLASH_CONTROLLER	1
#define DT_COMPAT_SOC_NV_FLASH			1


/* Following definitions fixup the generated include */
/* SoC level DTS fixup file */

#define CONFIG_NUM_IRQ_PRIO_BITS	ARM_V7M_NVIC_E000E100_ARM_NUM_IRQ_PRIORITY_BITS

#define CONFIG_ADC_0_IRQ		NORDIC_NRF_SAADC_40007000_IRQ_0
#define CONFIG_ADC_0_IRQ_PRI		NORDIC_NRF_SAADC_40007000_IRQ_0_PRIORITY
#define CONFIG_ADC_0_NAME		NORDIC_NRF_SAADC_40007000_LABEL

#if defined(NORDIC_NRF_UARTE_40002000_BASE_ADDRESS)
#define CONFIG_UART_0_BASE		NORDIC_NRF_UARTE_40002000_BASE_ADDRESS
#define CONFIG_UART_0_IRQ_PRI		NORDIC_NRF_UARTE_40002000_IRQ_0_PRIORITY
#define CONFIG_UART_0_IRQ_NUM		NORDIC_NRF_UARTE_40002000_IRQ_0
#define CONFIG_UART_0_BAUD_RATE		NORDIC_NRF_UARTE_40002000_CURRENT_SPEED
#define CONFIG_UART_0_NAME		NORDIC_NRF_UARTE_40002000_LABEL
#define CONFIG_UART_0_TX_PIN		NORDIC_NRF_UARTE_40002000_TX_PIN
#define CONFIG_UART_0_RX_PIN		NORDIC_NRF_UARTE_40002000_RX_PIN
  #if defined(NORDIC_NRF_UARTE_40002000_RTS_PIN)
  #define CONFIG_UART_0_RTS_PIN		NORDIC_NRF_UARTE_40002000_RTS_PIN
  #endif
  #if defined(NORDIC_NRF_UARTE_40002000_CTS_PIN)
  #define CONFIG_UART_0_CTS_PIN		NORDIC_NRF_UARTE_40002000_CTS_PIN
  #endif
#else
#define CONFIG_UART_0_BASE		NORDIC_NRF_UART_40002000_BASE_ADDRESS
#define CONFIG_UART_0_IRQ_PRI		NORDIC_NRF_UART_40002000_IRQ_0_PRIORITY
#define CONFIG_UART_0_IRQ_NUM		NORDIC_NRF_UART_40002000_IRQ_0
#define CONFIG_UART_0_BAUD_RATE		NORDIC_NRF_UART_40002000_CURRENT_SPEED
#define CONFIG_UART_0_NAME		NORDIC_NRF_UART_40002000_LABEL
#define CONFIG_UART_0_TX_PIN		NORDIC_NRF_UART_40002000_TX_PIN
#define CONFIG_UART_0_RX_PIN		NORDIC_NRF_UART_40002000_RX_PIN
  #if defined(NORDIC_NRF_UART_40002000_RTS_PIN)
  #define CONFIG_UART_0_RTS_PIN		NORDIC_NRF_UART_40002000_RTS_PIN
  #endif
  #if defined(NORDIC_NRF_UART_40002000_RTS_PIN)
  #define CONFIG_UART_0_CTS_PIN		NORDIC_NRF_UART_40002000_CTS_PIN
  #endif
#endif

#define CONFIG_UART_1_BASE		NORDIC_NRF_UARTE_40028000_BASE_ADDRESS
#define CONFIG_UART_1_IRQ_PRI		NORDIC_NRF_UARTE_40028000_IRQ_0_PRIORITY
#define CONFIG_UART_1_IRQ_NUM		NORDIC_NRF_UARTE_40028000_IRQ_0
#define CONFIG_UART_1_BAUD_RATE		NORDIC_NRF_UARTE_40028000_CURRENT_SPEED
#define CONFIG_UART_1_NAME		NORDIC_NRF_UARTE_40028000_LABEL
#define CONFIG_UART_1_TX_PIN		NORDIC_NRF_UARTE_40028000_TX_PIN
#define CONFIG_UART_1_RX_PIN		NORDIC_NRF_UARTE_40028000_RX_PIN
#if defined(NORDIC_NRF_UARTE_40028000_RTS_PIN)
#define CONFIG_UART_1_RTS_PIN		NORDIC_NRF_UARTE_40028000_RTS_PIN
#endif
#if defined(NORDIC_NRF_UARTE_40028000_CTS_PIN)
#define CONFIG_UART_1_CTS_PIN		NORDIC_NRF_UARTE_40028000_CTS_PIN
#endif

#define FLASH_DEV_NAME			NRF_NRF52_FLASH_CONTROLLER_4001E000_LABEL

#define CONFIG_GPIO_P0_DEV_NAME		NORDIC_NRF_GPIO_50000000_LABEL
#if CONFIG_HAS_HW_NRF_GPIO1
#define CONFIG_GPIO_P1_DEV_NAME		NORDIC_NRF_GPIO_50000300_LABEL
#endif
#define CONFIG_GPIOTE_IRQ_PRI		NORDIC_NRF_GPIOTE_40006000_IRQ_0_PRIORITY
#define CONFIG_GPIOTE_IRQ		NORDIC_NRF_GPIOTE_40006000_IRQ_0

#define CONFIG_I2C_0_BASE_ADDR		NORDIC_NRF_I2C_40003000_BASE_ADDRESS
#define CONFIG_I2C_0_NAME		NORDIC_NRF_I2C_40003000_LABEL
#define CONFIG_I2C_0_BITRATE		NORDIC_NRF_I2C_40003000_CLOCK_FREQUENCY
#define CONFIG_I2C_0_IRQ_PRI		NORDIC_NRF_I2C_40003000_IRQ_0_PRIORITY
#define CONFIG_I2C_0_IRQ		NORDIC_NRF_I2C_40003000_IRQ_0
#define CONFIG_I2C_0_SDA_PIN		NORDIC_NRF_I2C_40003000_SDA_PIN
#define CONFIG_I2C_0_SCL_PIN		NORDIC_NRF_I2C_40003000_SCL_PIN

#define CONFIG_I2C_1_BASE_ADDR		NORDIC_NRF_I2C_40004000_BASE_ADDRESS
#define CONFIG_I2C_1_NAME		NORDIC_NRF_I2C_40004000_LABEL
#define CONFIG_I2C_1_BITRATE		NORDIC_NRF_I2C_40004000_CLOCK_FREQUENCY
#define CONFIG_I2C_1_IRQ_PRI		NORDIC_NRF_I2C_40004000_IRQ_0_PRIORITY
#define CONFIG_I2C_1_IRQ		NORDIC_NRF_I2C_40004000_IRQ_0
#define CONFIG_I2C_1_SDA_PIN		NORDIC_NRF_I2C_40004000_SDA_PIN
#define CONFIG_I2C_1_SCL_PIN		NORDIC_NRF_I2C_40004000_SCL_PIN

#define CONFIG_QDEC_BASE_ADDR		NORDIC_NRF_QDEC_40012000_BASE_ADDRESS
#define CONFIG_QDEC_NAME		NORDIC_NRF_QDEC_40012000_LABEL
#define CONFIG_QDEC_IRQ_PRI		NORDIC_NRF_QDEC_40012000_IRQ_0_PRIORITY
#define CONFIG_QDEC_IRQ			NORDIC_NRF_QDEC_40012000_IRQ_0
#define CONFIG_QDEC_A_PIN		NORDIC_NRF_QDEC_40012000_A_PIN
#define CONFIG_QDEC_B_PIN		NORDIC_NRF_QDEC_40012000_B_PIN
#if defined(NORDIC_NRF_QDEC_40012000_LED_PIN)
#define CONFIG_QDEC_LED_PIN		NORDIC_NRF_QDEC_40012000_LED_PIN
#endif
#if defined(NORDIC_NRF_QDEC_40012000_ENABLE_PIN)
#define CONFIG_QDEC_ENABLE_PIN		NORDIC_NRF_QDEC_40012000_ENABLE_PIN
#endif
#define CONFIG_QDEC_LED_PRE		NORDIC_NRF_QDEC_40012000_LED_PRE
#define CONFIG_QDEC_STEPS		NORDIC_NRF_QDEC_40012000_STEPS

#define CONFIG_SPI_0_BASE_ADDRESS       NORDIC_NRF_SPI_40003000_BASE_ADDRESS
#define CONFIG_SPI_0_NAME               NORDIC_NRF_SPI_40003000_LABEL
#define CONFIG_SPI_0_IRQ_PRI            NORDIC_NRF_SPI_40003000_IRQ_0_PRIORITY
#define CONFIG_SPI_0_IRQ                NORDIC_NRF_SPI_40003000_IRQ_0
#define CONFIG_SPI_0_NRF_SCK_PIN	NORDIC_NRF_SPI_40003000_SCK_PIN
#define CONFIG_SPI_0_NRF_MOSI_PIN	NORDIC_NRF_SPI_40003000_MOSI_PIN
#define CONFIG_SPI_0_NRF_MISO_PIN	NORDIC_NRF_SPI_40003000_MISO_PIN
#define CONFIG_SPI_0_NRF_CSN_PIN	NORDIC_NRF_SPI_40003000_CSN_PIN

#define CONFIG_SPI_1_BASE_ADDRESS       NORDIC_NRF_SPI_40004000_BASE_ADDRESS
#define CONFIG_SPI_1_NAME               NORDIC_NRF_SPI_40004000_LABEL
#define CONFIG_SPI_1_IRQ_PRI            NORDIC_NRF_SPI_40004000_IRQ_0_PRIORITY
#define CONFIG_SPI_1_IRQ                NORDIC_NRF_SPI_40004000_IRQ_0
#define CONFIG_SPI_1_NRF_SCK_PIN	NORDIC_NRF_SPI_40004000_SCK_PIN
#define CONFIG_SPI_1_NRF_MOSI_PIN	NORDIC_NRF_SPI_40004000_MOSI_PIN
#define CONFIG_SPI_1_NRF_MISO_PIN	NORDIC_NRF_SPI_40004000_MISO_PIN
#define CONFIG_SPI_1_NRF_CSN_PIN	NORDIC_NRF_SPI_40004000_CSN_PIN

#define CONFIG_SPI_2_BASE_ADDRESS       NORDIC_NRF_SPI_40023000_BASE_ADDRESS
#define CONFIG_SPI_2_NAME               NORDIC_NRF_SPI_40023000_LABEL
#define CONFIG_SPI_2_IRQ_PRI            NORDIC_NRF_SPI_40023000_IRQ_0_PRIORITY
#define CONFIG_SPI_2_IRQ                NORDIC_NRF_SPI_40023000_IRQ_0
#define CONFIG_SPI_2_NRF_SCK_PIN	NORDIC_NRF_SPI_40023000_SCK_PIN
#define CONFIG_SPI_2_NRF_MOSI_PIN	NORDIC_NRF_SPI_40023000_MOSI_PIN
#define CONFIG_SPI_2_NRF_MISO_PIN	NORDIC_NRF_SPI_40023000_MISO_PIN
#define CONFIG_SPI_2_NRF_CSN_PIN	NORDIC_NRF_SPI_40023000_CSN_PIN

#define CONFIG_SPI_3_BASE_ADDRESS       NORDIC_NRF_SPI_4002B000_BASE_ADDRESS
#define CONFIG_SPI_3_NAME               NORDIC_NRF_SPI_4002B000_LABEL
#define CONFIG_SPI_3_IRQ_PRI            NORDIC_NRF_SPI_4002B000_IRQ_0_PRIORITY
#define CONFIG_SPI_3_IRQ                NORDIC_NRF_SPI_4002B000_IRQ_0
#define CONFIG_SPI_3_NRF_SCK_PIN	NORDIC_NRF_SPI_4002B000_SCK_PIN
#define CONFIG_SPI_3_NRF_MOSI_PIN	NORDIC_NRF_SPI_4002B000_MOSI_PIN
#define CONFIG_SPI_3_NRF_MISO_PIN	NORDIC_NRF_SPI_4002B000_MISO_PIN
#define CONFIG_SPI_3_NRF_CSN_PIN	NORDIC_NRF_SPI_4002B000_CSN_PIN

#define CONFIG_USBD_NRF_IRQ		NORDIC_NRF_USBD_40027000_IRQ_USBD
#define CONFIG_USBD_NRF_IRQ_PRI		NORDIC_NRF_USBD_40027000_IRQ_USBD_PRIORITY
#define CONFIG_USBD_NRF_NUM_BIDIR_EP	NORDIC_NRF_USBD_40027000_NUM_BIDIR_ENDPOINTS
#define CONFIG_USBD_NRF_NUM_IN_EP	NORDIC_NRF_USBD_40027000_NUM_IN_ENDPOINTS
#define CONFIG_USBD_NRF_NUM_OUT_EP	NORDIC_NRF_USBD_40027000_NUM_OUT_ENDPOINTS
#define CONFIG_USBD_NRF_NUM_ISOIN_EP	NORDIC_NRF_USBD_40027000_NUM_ISOIN_ENDPOINTS
#define CONFIG_USBD_NRF_NUM_ISOOUT_EP	NORDIC_NRF_USBD_40027000_NUM_ISOOUT_ENDPOINTS
#define CONFIG_USBD_NRF_NAME		NORDIC_NRF_USBD_40027000_LABEL

#define CONFIG_WDT_0_NAME		NORDIC_NRF_WATCHDOG_40010000_LABEL
#define CONFIG_WDT_NRF_IRQ		NORDIC_NRF_WATCHDOG_40010000_IRQ_WDT
#define CONFIG_WDT_NRF_IRQ_PRI		NORDIC_NRF_WATCHDOG_40010000_IRQ_WDT_PRIORITY

#if defined(NORDIC_NRF_CC310_5002A000_BASE_ADDRESS)
#define CONFIG_CC310_CTL_BASE_ADDR	NORDIC_NRF_CC310_5002A000_BASE_ADDRESS
#define CONFIG_CC310_CTL_NAME		NORDIC_NRF_CC310_5002A000_LABEL
#define CONFIG_CC310_BASE_ADDR		ARM_CRYPTOCELL_310_5002B000_BASE_ADDRESS
#define CONFIG_CC310_NAME		ARM_CRYPTOCELL_310_5002B000_LABEL
#define CONFIG_CC310_IRQ		ARM_CRYPTOCELL_310_5002B000_IRQ_0
#define CONFIG_CC310_IRQ_PRI		ARM_CRYPTOCELL_310_5002B000_IRQ_0_PRIORITY
#endif

#define CONFIG_WNCM14A2A_UART_DRV_NAME			NORDIC_NRF_UARTE_40028000_WNCM14A2A_BUS_NAME
#define CONFIG_WNCM14A2A_GPIO_MDM_BOOT_MODE_SEL_NAME	NORDIC_NRF_UARTE_40028000_WNCM14A2A_MDM_BOOT_MODE_SEL_GPIOS_CONTROLLER
#define CONFIG_WNCM14A2A_GPIO_MDM_BOOT_MODE_SEL_PIN	NORDIC_NRF_UARTE_40028000_WNCM14A2A_MDM_BOOT_MODE_SEL_GPIOS_PIN
#define CONFIG_WNCM14A2A_GPIO_MDM_POWER_NAME		NORDIC_NRF_UARTE_40028000_WNCM14A2A_MDM_POWER_GPIOS_CONTROLLER
#define CONFIG_WNCM14A2A_GPIO_MDM_POWER_PIN		NORDIC_NRF_UARTE_40028000_WNCM14A2A_MDM_POWER_GPIOS_PIN
#define CONFIG_WNCM14A2A_GPIO_MDM_KEEP_AWAKE_NAME	NORDIC_NRF_UARTE_40028000_WNCM14A2A_MDM_KEEP_AWAKE_GPIOS_CONTROLLER
#define CONFIG_WNCM14A2A_GPIO_MDM_KEEP_AWAKE_PIN	NORDIC_NRF_UARTE_40028000_WNCM14A2A_MDM_KEEP_AWAKE_GPIOS_PIN
#define CONFIG_WNCM14A2A_GPIO_MDM_RESET_NAME		NORDIC_NRF_UARTE_40028000_WNCM14A2A_MDM_RESET_GPIOS_CONTROLLER
#define CONFIG_WNCM14A2A_GPIO_MDM_RESET_PIN		NORDIC_NRF_UARTE_40028000_WNCM14A2A_MDM_RESET_GPIOS_PIN
#define CONFIG_WNCM14A2A_GPIO_MDM_SHLD_TRANS_ENA_NAME	NORDIC_NRF_UARTE_40028000_WNCM14A2A_MDM_SHLD_TRANS_ENA_GPIOS_CONTROLLER
#define CONFIG_WNCM14A2A_GPIO_MDM_SHLD_TRANS_ENA_PIN	NORDIC_NRF_UARTE_40028000_WNCM14A2A_MDM_SHLD_TRANS_ENA_GPIOS_PIN
#ifdef NORDIC_NRF_UARTE_40028000_WNCM14A2A_MDM_SEND_OK_GPIOS_PIN
#define CONFIG_WNCM14A2A_GPIO_MDM_SEND_OK_NAME		NORDIC_NRF_UARTE_40028000_WNCM14A2A_MDM_SEND_OK_GPIOS_CONTROLLER
#define CONFIG_WNCM14A2A_GPIO_MDM_SEND_OK_PIN		NORDIC_NRF_UARTE_40028000_WNCM14A2A_MDM_SEND_OK_GPIOS_PIN
#endif

/* End of SoC Level DTS fixup file */

#endif
