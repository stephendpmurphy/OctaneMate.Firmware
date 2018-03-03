/**
 * \file
 *
 * \brief SAM Cyclic Redundancy Check Calculation Unit (CRCCU)
 *
 * Copyright (C) 2016 Atmel Corporation. All rights reserved.
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
 * DAMAGES (INCLUDING, BUT NOT LIMIT ED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */

#include <compiler.h>
#include <hpl_crc_sync.h>
#include <hpl_crccu_config.h>
#include <utils.h>

/** CRCCU descriptor type */
struct _crccu_descr {
	uint32_t tr_addr; /* TR_ADDR */
	uint32_t tr_ctrl; /* TR_CTRL */
	uint32_t res[2];  /* Reserved register */
	uint32_t tr_crc;  /* TR_CRC */
};

COMPILER_ALIGNED(512)
static struct _crccu_descr _tr_descr;

/**
 * \brief Initialize CRC.
 */
int32_t _crc_sync_init(struct _crc_sync_device *const device, void *const hw)
{
	device->hw = hw;

	hri_crccu_write_DSCR_reg(device->hw, (uint32_t)(&_tr_descr));

	return ERR_NONE;
}

/**
 * \brief De-initialize CRC.
 */
int32_t _crc_sync_deinit(struct _crc_sync_device *const device)
{
	device->hw = NULL;

	return ERR_NONE;
}

/**
 * \brief Enable CRC
 */
int32_t _crc_sync_enable(struct _crc_sync_device *const device)
{
	(void)device;

	return ERR_NONE;
}

/**
 * \brief Disable CRC
 */
int32_t _crc_sync_disable(struct _crc_sync_device *const device)
{
	(void)device;

	return ERR_NONE;
}

/**
 * \brief Calculate CRC value of the buffer
 */
int32_t _crc_sync_crc32(struct _crc_sync_device *const device, uint32_t *const data, const uint32_t len, uint32_t *pcrc)
{
	if (*pcrc == ~0) {
		hri_crccu_write_CR_reg(device->hw, CRCCU_CR_RESET);
	}

	if (*pcrc != hri_crccu_read_SR_reg(device->hw)) {
		return ERR_INVALID_DATA;
	}

	hri_crccu_write_MR_reg(device->hw,
	                       CRCCU_MR_ENABLE | CRCCU_MR_PTYPE_CCITT8023_Val | CRCCU_MR_DIVIDER(CONF_CRCCU_MR_DIVIDER));
	_tr_descr.tr_addr = (uint32_t)data;
	_tr_descr.tr_ctrl = (uint32_t)len | (2 << 24);
	hri_crccu_write_DMA_EN_reg(device->hw, CRCCU_DMA_EN_DMAEN);

	while (hri_crccu_read_DMA_SR_reg(device->hw)) {
	}

	*pcrc = hri_crccu_read_SR_reg(device->hw);

	return ERR_NONE;
}

/**
 * \brief Compute CRC16 value of the buffer
 */
int32_t _crc_sync_crc16(struct _crc_sync_device *const device, uint16_t *const data, const uint32_t len, uint16_t *pcrc)
{

	if (*pcrc == ~0) {
		hri_crccu_write_CR_reg(device->hw, CRCCU_CR_RESET);
	}

	if (*pcrc != hri_crccu_read_SR_reg(device->hw)) {
		return ERR_INVALID_DATA;
	}

	hri_crccu_write_MR_reg(device->hw,
	                       CRCCU_MR_ENABLE | CRCCU_MR_PTYPE_CCITT16_Val | CRCCU_MR_DIVIDER(CONF_CRCCU_MR_DIVIDER));
	_tr_descr.tr_addr = (uint32_t)data;
	_tr_descr.tr_ctrl = (uint32_t)len | (1 << 24);
	hri_crccu_write_DMA_EN_reg(device->hw, CRCCU_DMA_EN_DMAEN);

	while (hri_crccu_read_DMA_SR_reg(device->hw)) {
	}

	*pcrc = hri_crccu_read_SR_reg(device->hw);

	return ERR_NONE;
}
