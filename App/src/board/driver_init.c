/**********************************************************
* Copyright 2018, Murphy Technology, All rights reserved. *
***********************************************************/

#include <driver_init.h>
#include <hal_init.h>
#include <hpl_pmc.h>
#include <peripheral_clk_config.h>
#include <utils.h>
#include <hpl_usart_base.h>

/*! The buffer size for USART */
#define USART_BLE_BUFFER_SIZE 16
/*! The buffer size for USART */
#define USART_STN_BUFFER_SIZE 16
/*! The buffer size for USART */
#define USART_DEBUG_BUFFER_SIZE 16

struct usart_async_descriptor USART_BLE;
struct usart_async_descriptor USART_STN;
struct usart_async_descriptor USART_DEBUG;

static uint8_t USART_BLE_buffer[USART_BLE_BUFFER_SIZE];
static uint8_t USART_STN_buffer[USART_STN_BUFFER_SIZE];
static uint8_t USART_DEBUG_buffer[USART_DEBUG_BUFFER_SIZE];

/**
 * \brief USART Clock initialization function
 *
 * Enables register interface and peripheral clock
 */
void USART_BLE_CLOCK_init()
{
	_pmc_enable_periph_clock(ID_FLEXCOM0);
}

/**
 * \brief USART pinmux initialization function
 *
 * Set each required pin to USART functionality
 */
void USART_BLE_PORT_init()
{

	gpio_set_pin_function(PA9, MUX_PA9A_FLEXCOM0_RXD);

	gpio_set_pin_function(PA10, MUX_PA10A_FLEXCOM0_TXD);
}

/**
 * \brief USART initialization function
 *
 * Enables USART peripheral, clocks and initializes USART driver
 */
void USART_BLE_init(void)
{
	USART_BLE_CLOCK_init();
	USART_BLE_PORT_init();
	usart_async_init(&USART_BLE, FLEXCOM0, USART_BLE_buffer, USART_BLE_BUFFER_SIZE, _usart_get_usart_async());
}

/**
 * \brief USART Clock initialization function
 *
 * Enables register interface and peripheral clock
 */
void USART_STN_CLOCK_init()
{
	_pmc_enable_periph_clock(ID_FLEXCOM1);
}

/**
 * \brief USART pinmux initialization function
 *
 * Set each required pin to USART functionality
 */
void USART_STN_PORT_init()
{

	gpio_set_pin_function(PB2, MUX_PB2A_FLEXCOM1_RXD);

	gpio_set_pin_function(PB3, MUX_PB3A_FLEXCOM1_TXD);
}

/**
 * \brief USART initialization function
 *
 * Enables USART peripheral, clocks and initializes USART driver
 */
void USART_STN_init(void)
{
	USART_STN_CLOCK_init();
	USART_STN_PORT_init();
	usart_async_init(&USART_STN, FLEXCOM1, USART_STN_buffer, USART_STN_BUFFER_SIZE, _usart_get_usart_async());
}

/**
 * \brief USART Clock initialization function
 *
 * Enables register interface and peripheral clock
 */
void USART_DEBUG_CLOCK_init()
{
	_pmc_enable_periph_clock(ID_FLEXCOM6);
}

/**
 * \brief USART pinmux initialization function
 *
 * Set each required pin to USART functionality
 */
void USART_DEBUG_PORT_init()
{

	gpio_set_pin_function(PB1, MUX_PB1B_FLEXCOM6_RXD);

	gpio_set_pin_function(PB0, MUX_PB0B_FLEXCOM6_TXD);
}

/**
 * \brief USART initialization function
 *
 * Enables USART peripheral, clocks and initializes USART driver
 */
void USART_DEBUG_init(void)
{
	USART_DEBUG_CLOCK_init();
	USART_DEBUG_PORT_init();
	usart_async_init(&USART_DEBUG, FLEXCOM6, USART_DEBUG_buffer, USART_DEBUG_BUFFER_SIZE, _usart_get_usart_async());
}

void system_init(void)
{
	init_mcu();

	_pmc_enable_periph_clock(ID_PIOA);

	/* Disable Watchdog */
	hri_wdt_set_MR_WDDIS_bit(WDT);

	/* GPIO on PA6 */

	// Set pin direction to output
	gpio_set_pin_direction(MCU_STATUS_LED, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(MCU_STATUS_LED,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_function(MCU_STATUS_LED, GPIO_PIN_FUNCTION_OFF);

	/* GPIO on PA11 */

	// Set pin direction to output
	gpio_set_pin_direction(BLE_STATUS_LED, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(BLE_STATUS_LED,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_function(BLE_STATUS_LED, GPIO_PIN_FUNCTION_OFF);

	/* GPIO on PA12 */

	// Set pin direction to output
	gpio_set_pin_direction(STN_STATUS_LED, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(STN_STATUS_LED,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_function(STN_STATUS_LED, GPIO_PIN_FUNCTION_OFF);

	USART_BLE_init();
	USART_STN_init();
	USART_DEBUG_init();
}
