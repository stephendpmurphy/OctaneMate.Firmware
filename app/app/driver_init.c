/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_init.h"
#include <peripheral_clk_config.h>
#include <utils.h>
#include <hal_init.h>

/*! The buffer size for USART */
#define DEBUG_UART_BUFFER_SIZE 16

/*! The buffer size for USART */
#define BT_UART_BUFFER_SIZE 16

struct crc_sync_descriptor    CRC_0;
struct spi_m_sync_descriptor  SERIAL_FLASH_SPI;
struct usart_async_descriptor DEBUG_UART;
struct usart_async_descriptor BT_UART;
struct can_async_descriptor   CAN_0;

static uint8_t DEBUG_UART_buffer[DEBUG_UART_BUFFER_SIZE];
static uint8_t BT_UART_buffer[BT_UART_BUFFER_SIZE];

struct flash_descriptor FLASH_INSTANCE;

/**
 * \brief CRC initialization function
 *
 * Enables CRC peripheral, clocks and initializes CRC driver
 */
void CRC_0_init(void)
{
	hri_mclk_set_APBBMASK_DSU_bit(MCLK);
	crc_sync_init(&CRC_0, DSU);
}

void FLASH_INSTANCE_CLOCK_init(void)
{

	hri_mclk_set_AHBMASK_NVMCTRL_bit(MCLK);
}

void FLASH_INSTANCE_init(void)
{
	FLASH_INSTANCE_CLOCK_init();
	flash_init(&FLASH_INSTANCE, NVMCTRL);
}

void SERIAL_FLASH_SPI_PORT_init(void)
{

	// Set pin direction to output
	gpio_set_pin_direction(PA04, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(PA04,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_function(PA04, PINMUX_PA04D_SERCOM0_PAD0);

	// Set pin direction to output
	gpio_set_pin_direction(PA05, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(PA05,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_function(PA05, PINMUX_PA05D_SERCOM0_PAD1);

	// Set pin direction to input
	gpio_set_pin_direction(PA06, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(PA06,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(PA06, PINMUX_PA06D_SERCOM0_PAD2);
}

void SERIAL_FLASH_SPI_CLOCK_init(void)
{
	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM0_GCLK_ID_CORE, CONF_GCLK_SERCOM0_CORE_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM0_GCLK_ID_SLOW, CONF_GCLK_SERCOM0_SLOW_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));

	hri_mclk_set_APBAMASK_SERCOM0_bit(MCLK);
}

void SERIAL_FLASH_SPI_init(void)
{
	SERIAL_FLASH_SPI_CLOCK_init();
	spi_m_sync_init(&SERIAL_FLASH_SPI, SERCOM0);
	SERIAL_FLASH_SPI_PORT_init();
}

/**
 * \brief USART Clock initialization function
 *
 * Enables register interface and peripheral clock
 */
void DEBUG_UART_CLOCK_init()
{

	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM1_GCLK_ID_CORE, CONF_GCLK_SERCOM1_CORE_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM1_GCLK_ID_SLOW, CONF_GCLK_SERCOM1_SLOW_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));

	hri_mclk_set_APBAMASK_SERCOM1_bit(MCLK);
}

/**
 * \brief USART pinmux initialization function
 *
 * Set each required pin to USART functionality
 */
void DEBUG_UART_PORT_init()
{

	gpio_set_pin_function(PA00, PINMUX_PA00D_SERCOM1_PAD0);

	gpio_set_pin_function(PA01, PINMUX_PA01D_SERCOM1_PAD1);
}

/**
 * \brief USART initialization function
 *
 * Enables USART peripheral, clocks and initializes USART driver
 */
void DEBUG_UART_init(void)
{
	DEBUG_UART_CLOCK_init();
	usart_async_init(&DEBUG_UART, SERCOM1, DEBUG_UART_buffer, DEBUG_UART_BUFFER_SIZE, (void *)NULL);
	DEBUG_UART_PORT_init();
}

/**
 * \brief USART Clock initialization function
 *
 * Enables register interface and peripheral clock
 */
void BT_UART_CLOCK_init()
{

	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM2_GCLK_ID_CORE, CONF_GCLK_SERCOM2_CORE_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM2_GCLK_ID_SLOW, CONF_GCLK_SERCOM2_SLOW_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));

	hri_mclk_set_APBBMASK_SERCOM2_bit(MCLK);
}

/**
 * \brief USART pinmux initialization function
 *
 * Set each required pin to USART functionality
 */
void BT_UART_PORT_init()
{

	gpio_set_pin_function(PA09, PINMUX_PA09D_SERCOM2_PAD0);

	gpio_set_pin_function(PA10, PINMUX_PA10D_SERCOM2_PAD2);
}

/**
 * \brief USART initialization function
 *
 * Enables USART peripheral, clocks and initializes USART driver
 */
void BT_UART_init(void)
{
	BT_UART_CLOCK_init();
	usart_async_init(&BT_UART, SERCOM2, BT_UART_buffer, BT_UART_BUFFER_SIZE, (void *)NULL);
	BT_UART_PORT_init();
}

void CAN_0_PORT_init(void)
{

	gpio_set_pin_function(PA23, PINMUX_PA23I_CAN0_RX);

	gpio_set_pin_function(PA22, PINMUX_PA22I_CAN0_TX);
}
/**
 * \brief CAN initialization function
 *
 * Enables CAN peripheral, clocks and initializes CAN driver
 */
void CAN_0_init(void)
{
	hri_mclk_set_AHBMASK_CAN0_bit(MCLK);
	hri_gclk_write_PCHCTRL_reg(GCLK, CAN0_GCLK_ID, CONF_GCLK_CAN0_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
	can_async_init(&CAN_0, CAN0);
	CAN_0_PORT_init();
}

void system_init(void)
{
	init_mcu();

	// GPIO on PA07

	// Set pin direction to output
	gpio_set_pin_direction(SERIAL_FLASH_CS, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(SERIAL_FLASH_CS,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   true);

	gpio_set_pin_function(SERIAL_FLASH_CS, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PA12

	// Set pin direction to output
	gpio_set_pin_direction(CAN_INTF_EN, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(CAN_INTF_EN,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   true);

	gpio_set_pin_function(CAN_INTF_EN, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PA13

	// Set pin direction to output
	gpio_set_pin_direction(BT_EN, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(BT_EN,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   true);

	gpio_set_pin_function(BT_EN, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PA14

	// Set pin direction to output
	gpio_set_pin_direction(SERIAL_FLASH_EN, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(SERIAL_FLASH_EN,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   true);

	gpio_set_pin_function(SERIAL_FLASH_EN, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PA16

	// Set pin direction to output
	gpio_set_pin_direction(SERIAL_FLASH_RST, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(SERIAL_FLASH_RST,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   true);

	gpio_set_pin_function(SERIAL_FLASH_RST, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PA24

	// Set pin direction to output
	gpio_set_pin_direction(CAN0_STDBY, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(CAN0_STDBY,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_function(CAN0_STDBY, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB00

	// Set pin direction to output
	gpio_set_pin_direction(BT_CONF, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(BT_CONF,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_function(BT_CONF, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB01

	// Set pin direction to input
	gpio_set_pin_direction(BT_STATUS1_IND, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(BT_STATUS1_IND,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(BT_STATUS1_IND, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB02

	// Set pin direction to input
	gpio_set_pin_direction(BT_STATUS2_IND, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(BT_STATUS2_IND,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(BT_STATUS2_IND, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB03

	// Set pin direction to input
	gpio_set_pin_direction(BT_RSSI_IND, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(BT_RSSI_IND,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(BT_RSSI_IND, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB04

	// Set pin direction to output
	gpio_set_pin_direction(BT_PAIRING_KEY, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(BT_PAIRING_KEY,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_function(BT_PAIRING_KEY, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB05

	// Set pin direction to output
	gpio_set_pin_direction(BT_LINK_DROP, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(BT_LINK_DROP,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_function(BT_LINK_DROP, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB06

	// Set pin direction to output
	gpio_set_pin_direction(BT_RESET, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(BT_RESET,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   true);

	gpio_set_pin_function(BT_RESET, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB07

	// Set pin direction to input
	gpio_set_pin_direction(BT_RF_ACTIVE_IND, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(BT_RF_ACTIVE_IND,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(BT_RF_ACTIVE_IND, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB10

	// Set pin direction to output
	gpio_set_pin_direction(MCU_STATUS_LED, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(MCU_STATUS_LED,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_function(MCU_STATUS_LED, GPIO_PIN_FUNCTION_OFF);

	CRC_0_init();

	FLASH_INSTANCE_init();

	SERIAL_FLASH_SPI_init();
	DEBUG_UART_init();
	BT_UART_init();
	CAN_0_init();
}
