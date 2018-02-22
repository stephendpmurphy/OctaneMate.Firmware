/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_init.h"
#include <hal_init.h>
#include <hpl_pmc.h>
#include <peripheral_clk_config.h>
#include <utils.h>

#include <hpl_usart_base.h>

#include <hpl_usart_base.h>

struct usart_sync_descriptor USART_BLE;

struct usart_sync_descriptor USART_STN;

void USART_BLE_PORT_init(void)
{

	gpio_set_pin_function(PA9, MUX_PA9A_FLEXCOM0_RXD);

	gpio_set_pin_function(PA10, MUX_PA10A_FLEXCOM0_TXD);
}

void USART_BLE_CLOCK_init(void)
{
	_pmc_enable_periph_clock(ID_FLEXCOM0);
}

void USART_BLE_init(void)
{
	USART_BLE_CLOCK_init();
	USART_BLE_PORT_init();
	usart_sync_init(&USART_BLE, FLEXCOM0, _usart_get_usart_sync());
}

void USART_STN_PORT_init(void)
{

	gpio_set_pin_function(PB2, MUX_PB2A_FLEXCOM1_RXD);

	gpio_set_pin_function(PB3, MUX_PB3A_FLEXCOM1_TXD);
}

void USART_STN_CLOCK_init(void)
{
	_pmc_enable_periph_clock(ID_FLEXCOM1);
}

void USART_STN_init(void)
{
	USART_STN_CLOCK_init();
	USART_STN_PORT_init();
	usart_sync_init(&USART_STN, FLEXCOM1, _usart_get_usart_sync());
}

void system_init(void)
{
	init_mcu();

	_pmc_enable_periph_clock(ID_PIOA);

	/* Disable Watchdog */
	hri_wdt_set_MR_WDDIS_bit(WDT);

	/* GPIO on PA6 */

	// Set pin direction to output
	gpio_set_pin_direction(STN_STATUS_LED, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(STN_STATUS_LED,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_function(STN_STATUS_LED, GPIO_PIN_FUNCTION_OFF);

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
	gpio_set_pin_direction(MCU_STATUS_LED, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(MCU_STATUS_LED,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_function(MCU_STATUS_LED, GPIO_PIN_FUNCTION_OFF);

	USART_BLE_init();

	USART_STN_init();
}
