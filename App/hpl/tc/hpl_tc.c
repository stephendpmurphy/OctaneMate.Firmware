/**
 * \file
 *
 * \brief SAM TC
 *
 * Copyright (C) 2016 -2107 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */

#include <utils_assert.h>
#include <hpl_tc_config.h>
#include <hpl_timer.h>
#include <hpl_pwm.h>
#include <utils.h>
#include <hpl_tc.h>

#ifndef CONF_TC0_ENABLE
#define CONF_TC0_ENABLE 0
#endif
#ifndef CONF_TC1_ENABLE
#define CONF_TC1_ENABLE 0
#endif
#ifndef CONF_TC2_ENABLE
#define CONF_TC2_ENABLE 0
#endif
#ifndef CONF_TC3_ENABLE
#define CONF_TC3_ENABLE 0
#endif
#ifndef CONF_TC4_ENABLE
#define CONF_TC4_ENABLE 0
#endif

/**
 * \brief Macro is used to fill usart configuration structure based on its
 * number
 *
 * \param[in] n The number of structures
 */
#define TC_CONFIGURATION(n, m)                                                                                         \
	{                                                                                                                  \
		TC##n, TC##m##_IRQn, CONF_TC##n##_CMR_REG_VAL, TC_RA_RA(CONF_TC##n##_RA), TC_RB_RB(CONF_TC##n##_RB),           \
		    TC_RC_RC(CONF_TC##n##_RC), CONF_TC##n##_TICKS_PER_US,                                                      \
	}

/**
 * \brief TC configuration type
 */
struct tc_configuration {
	void *           hw;
	IRQn_Type        irq;
	hri_tc_cmr_reg_t channel_mode;
	hri_tc_ra_reg_t  ra;
	hri_tc_rb_reg_t  rb;
	hri_tc_rc_reg_t  rc;
	uint32_t         tick_us;
};

#define TC_AMOUNT (CONF_TC0_ENABLE + CONF_TC1_ENABLE + CONF_TC2_ENABLE + CONF_TC3_ENABLE)

#if TC_AMOUNT < 1
/** Dummy array for compiling. */
static const struct tc_configuration _tcs[1] = {{0}};
#else
/**
 * \brief Array of TC configurations
 */
static struct tc_configuration _tcs[] = {
#if CONF_TC0_ENABLE == 1
    TC_CONFIGURATION(0, 0),
#endif
#if CONF_TC1_ENABLE == 1
    TC_CONFIGURATION(1, 3),
#endif
#if CONF_TC2_ENABLE == 1
    TC_CONFIGURATION(2, 6),
#endif
#if CONF_TC3_ENABLE == 1
    TC_CONFIGURATION(3, 9),
#endif
};
#endif

static struct _pwm_device *_tc0_dev = NULL;

static struct tc_configuration *get_cfg(void *hw)
{
	uint8_t i;

	for (i = 0; i < ARRAY_SIZE(_tcs); i++) {
		if (_tcs[i].hw == hw) {
			return &(_tcs[i]);
		}
	}

	return NULL;
}

/**
 * \brief Init irq param with the given tc hardware instance
 */
static void _tc_init_irq_param(const void *const hw, void *dev)
{
	if (hw == TC0) {
		_tc0_dev = (struct _pwm_device *)dev;
	}
}

/**
 * \brief Retrieve timer helper functions
 */
struct _timer_hpl_interface *_tc_get_timer(void)
{
	return NULL;
}

/**
 * \brief Initialize TC
 */
int32_t _pwm_init(struct _pwm_device *const device, void *const hw)
{
	struct tc_configuration *cfg = get_cfg(hw);

	device->hw = hw;
	ASSERT(ARRAY_SIZE(_tcs));

	hri_tc_write_CMR_reg(hw, 0, cfg->channel_mode);
	hri_tc_write_RA_reg(hw, 0, cfg->ra);
	hri_tc_write_RB_reg(hw, 0, cfg->rb);
	hri_tc_write_RC_reg(hw, 0, cfg->rc);

	_tc_init_irq_param(hw, device);
	NVIC_DisableIRQ(cfg->irq);
	NVIC_ClearPendingIRQ(cfg->irq);
	NVIC_EnableIRQ(cfg->irq);

	return ERR_NONE;
}

/**
 * \brief De-initialize TC
 */
void _pwm_deinit(struct _pwm_device *const device)
{
	struct tc_configuration *cfg = get_cfg(device->hw);
	NVIC_DisableIRQ(cfg->irq);
	hri_tc_write_CCR_reg(device->hw, 0, TC_CCR_CLKDIS);
}

/**
 * \brief Start hardware PWM
 */
void _pwm_enable(struct _pwm_device *const device)
{
	hri_tc_write_CCR_reg(device->hw, 0, TC_CCR_CLKEN | TC_CCR_SWTRG);
}

/**
 * \brief Stop hardware PWM
 */
void _pwm_disable(struct _pwm_device *const device)
{
	hri_tc_write_CCR_reg(device->hw, 0, TC_CCR_CLKDIS);
}

/**
 * \brief Set PWM parameter
 */
void _pwm_set_param(struct _pwm_device *const device, const pwm_period_t period, const pwm_period_t duty_cycle)
{
	struct tc_configuration *cfg = get_cfg(device->hw);

	hri_tc_write_RC_reg(device->hw, 0, TC_RC_RC(cfg->tick_us * period));
	hri_tc_write_RA_reg(device->hw, 0, TC_RA_RA(cfg->tick_us * duty_cycle));
	hri_tc_write_RB_reg(device->hw, 0, TC_RB_RB(cfg->tick_us * duty_cycle));
}

/**
 * \brief Check if PWM is working
 */
bool _pwm_is_enabled(const struct _pwm_device *const device)
{
	return hri_tc_get_SR_CLKSTA_bit(device->hw, 0);
}

/**
 * \brief Get pwm waveform period value
 */
uint32_t _pwm_get_period(const struct _pwm_device *const device)
{
	return hri_tc_read_RC_reg(device->hw, 0);
}

/**
 * \brief Get pwm waveform duty cycle value
 */
uint32_t _pwm_get_duty(const struct _pwm_device *const device)
{
	return hri_tc_read_RA_reg(device->hw, 0);
}

/**
 * \brief Set PWM IRQ
 *
 * \param[in] hw The pointer to hardware instance
 */
void _pwm_set_irq_state(struct _pwm_device *const device, const enum _pwm_callback_type type, const bool enabled)
{
	switch (type) {
	case PWM_DEVICE_PERIOD_CB:
		hri_tc_write_IMR_CPCS_bit(device->hw, 0, enabled);
		break;
	case PWM_DEVICE_ERROR_CB:
		break;
	default:
		break;
	}
}

/**
 * \internal TC interrupt handler
 *
 * \param[in] instance TC instance number
 */
static void tc_pwm_interrupt_handler(struct _pwm_device *device)
{
	if (hri_tc_get_SR_CPCS_bit(device->hw, 0)) {
		device->callback.pwm_period_cb(device);
	}
}

/**
* \brief TC interrupt handler
*/
void TC0_Handler(void)
{
	tc_pwm_interrupt_handler(_tc0_dev);
}

/**
 * \brief Retrieve PWM helper functions
 */
struct _pwm_hpl_interface *_tc_get_pwm(void)
{
	return NULL;
}
