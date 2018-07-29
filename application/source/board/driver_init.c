//------------------------------------------------------------------------------
//  Copyright(c)2018 Murphy Technology as an unpublished work.
//
//  The information contained herein is confidential property of Murphy Technology.
//  All rights reserved.  Reproduction, adaptation, or translation without the
//  express written consent of Murphy Technology is prohibited, except as allowed
//  under the copyright laws.
//------------------------------------------------------------------------------

#include "driver_init.h"
#include <peripheral_clk_config.h>
#include <utils.h>
#include <hal_init.h>

/*! The buffer size for USART */
#define BT_UART_BUFFER_SIZE 256

/*! The buffer size for USART */
#define DEBUG_UART_BUFFER_SIZE 32

struct spi_m_sync_descriptor  EXT_FLASH_SPI;
struct usart_async_descriptor BT_UART;
struct usart_async_descriptor DEBUG_UART;
struct can_async_descriptor   CAN1_INTF;

static uint8_t BT_UART_buffer[BT_UART_BUFFER_SIZE];
static uint8_t DEBUG_UART_buffer[DEBUG_UART_BUFFER_SIZE];

void EXT_FLASH_SPI_PORT_init(void)
{

	// Set pin direction to output
	gpio_set_pin_direction(EXT_FLASH_MOSI, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(EXT_FLASH_MOSI,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_function(EXT_FLASH_MOSI, PINMUX_PA04D_SERCOM0_PAD0);

	// Set pin direction to output
	gpio_set_pin_direction(EXT_FLASH_SCK, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(EXT_FLASH_SCK,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_function(EXT_FLASH_SCK, PINMUX_PA05D_SERCOM0_PAD1);

	// Set pin direction to input
	gpio_set_pin_direction(EXT_FLASH_MISO, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(EXT_FLASH_MISO,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(EXT_FLASH_MISO, PINMUX_PA06D_SERCOM0_PAD2);
}

void EXT_FLASH_SPI_CLOCK_init(void)
{
	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM0_GCLK_ID_CORE, CONF_GCLK_SERCOM0_CORE_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM0_GCLK_ID_SLOW, CONF_GCLK_SERCOM0_SLOW_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));

	hri_mclk_set_APBAMASK_SERCOM0_bit(MCLK);
}

void EXT_FLASH_SPI_init(void)
{
	EXT_FLASH_SPI_CLOCK_init();
	spi_m_sync_init(&EXT_FLASH_SPI, SERCOM0);
	EXT_FLASH_SPI_PORT_init();
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
	gpio_set_pin_level(BT_UART_TX, false);
	gpio_set_pin_level(BT_UART_RX, false);

	gpio_set_pin_function(BT_UART_TX, PINMUX_PA12C_SERCOM2_PAD0);
	gpio_set_pin_function(BT_UART_RX, PINMUX_PA13C_SERCOM2_PAD1);
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

/**
 * \brief USART Clock initialization function
 *
 * Enables register interface and peripheral clock
 */
void DEBUG_UART_CLOCK_init()
{

	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM5_GCLK_ID_CORE, CONF_GCLK_SERCOM5_CORE_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM5_GCLK_ID_SLOW, CONF_GCLK_SERCOM5_SLOW_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));

	hri_mclk_set_APBDMASK_SERCOM5_bit(MCLK);
}

/**
 * \brief USART pinmux initialization function
 *
 * Set each required pin to USART functionality
 */
void DEBUG_UART_PORT_init()
{

	gpio_set_pin_function(DEBUG_UART_TX, PINMUX_PB31D_SERCOM5_PAD0);

	gpio_set_pin_function(DEBUG_UART_RX, PINMUX_PB30D_SERCOM5_PAD1);
}

/**
 * \brief USART initialization function
 *
 * Enables USART peripheral, clocks and initializes USART driver
 */
void DEBUG_UART_init(void)
{
	DEBUG_UART_CLOCK_init();
	usart_async_init(&DEBUG_UART, SERCOM5, DEBUG_UART_buffer, DEBUG_UART_BUFFER_SIZE, (void *)NULL);
	DEBUG_UART_PORT_init();
}

void CAN1_PORT_init(void)
{

	gpio_set_pin_function(CAN1_RX, PINMUX_PB15H_CAN1_RX);

	gpio_set_pin_function(CAN1_TX, PINMUX_PB14H_CAN1_TX);
}
/**
 * \brief CAN initialization function
 *
 * Enables CAN peripheral, clocks and initializes CAN driver
 */
void CAN1_init(void)
{
	hri_mclk_set_AHBMASK_CAN1_bit(MCLK);
	hri_gclk_write_PCHCTRL_reg(GCLK, CAN1_GCLK_ID, CONF_GCLK_CAN1_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
	can_async_init(&CAN1_INTF, CAN1);
	CAN1_PORT_init();
}

void system_init(void)
{
	init_mcu();

	// GPIO on PA07

	// Set pin direction to output
	gpio_set_pin_direction(EXT_FLASH_CS, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(EXT_FLASH_CS,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   true);

	gpio_set_pin_function(EXT_FLASH_CS, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PA14

	// Set pin direction to output
	gpio_set_pin_direction(BT_CONF, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(BT_CONF,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_function(BT_CONF, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PA15

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

	// GPIO on PA16

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

	// GPIO on PA18

	// Set pin direction to output
	gpio_set_pin_direction(BT_PAIRING_KEY, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(BT_PAIRING_KEY,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_function(BT_PAIRING_KEY, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PA19

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

	// GPIO on PA22

	// Set pin direction to output
	gpio_set_pin_direction(BT_LINK_DROP, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(BT_LINK_DROP,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_function(BT_LINK_DROP, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PA23

	// Set pin direction to output
	gpio_set_pin_direction(EXT_FLASH_NEN, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(EXT_FLASH_NEN,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   true);

	gpio_set_pin_function(EXT_FLASH_NEN, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PA25

	// Set pin direction to output
	gpio_set_pin_direction(BT_NEN, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(BT_NEN,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   true);

	gpio_set_pin_function(BT_NEN, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PA27

	// Set pin direction to output
	gpio_set_pin_direction(MCU_STATUS_LED, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(MCU_STATUS_LED,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_function(MCU_STATUS_LED, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB09

	// Set pin direction to output
	gpio_set_pin_direction(EXT_FLASH_NRST, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(EXT_FLASH_NRST,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   true);

	gpio_set_pin_function(EXT_FLASH_NRST, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB11

	// Set pin direction to output
	gpio_set_pin_direction(CAN1_STDBY, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(CAN1_STDBY,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_function(CAN1_STDBY, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB16

	// Set pin direction to output
	gpio_set_pin_direction(BT_NRST, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(BT_NRST,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   true);

	gpio_set_pin_function(BT_NRST, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB17

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

	EXT_FLASH_SPI_init();
	BT_UART_init();
	DEBUG_UART_init();
	CAN1_init();
}
