
/**
 * \file
 *
 * \brief Generic Clock Controller related functionality.
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */

#include <hpl_gclk_config.h>
#include <hpl_init.h>
#include <utils_assert.h>

/**
 * \brief Initializes generators
 */
void _gclk_init_generators(void)
{
#if CONF_GCLK_GEN_0_GENEN == 1
	hri_gclk_write_GENCTRL_reg(GCLK,
	                           0,
	                           GCLK_GENCTRL_DIV(CONF_GCLK_GEN_0_DIV)
	                               | (CONF_GCLK_GEN_0_RUNSTDBY << GCLK_GENCTRL_RUNSTDBY_Pos)
	                               | (CONF_GCLK_GEN_0_DIVSEL << GCLK_GENCTRL_DIVSEL_Pos)
	                               | (CONF_GCLK_GEN_0_OE << GCLK_GENCTRL_OE_Pos)
	                               | (CONF_GCLK_GEN_0_OOV << GCLK_GENCTRL_OOV_Pos)
	                               | (CONF_GCLK_GEN_0_IDC << GCLK_GENCTRL_IDC_Pos)
	                               | (CONF_GCLK_GEN_0_GENEN << GCLK_GENCTRL_GENEN_Pos)
	                               | CONF_GCLK_GEN_0_SOURCE);
#endif
#if CONF_GCLK_GEN_1_GENEN == 1
	hri_gclk_write_GENCTRL_reg(GCLK,
	                           1,
	                           GCLK_GENCTRL_DIV(CONF_GCLK_GEN_1_DIV)
	                               | (CONF_GCLK_GEN_1_RUNSTDBY << GCLK_GENCTRL_RUNSTDBY_Pos)
	                               | (CONF_GCLK_GEN_1_DIVSEL << GCLK_GENCTRL_DIVSEL_Pos)
	                               | (CONF_GCLK_GEN_1_OE << GCLK_GENCTRL_OE_Pos)
	                               | (CONF_GCLK_GEN_1_OOV << GCLK_GENCTRL_OOV_Pos)
	                               | (CONF_GCLK_GEN_1_IDC << GCLK_GENCTRL_IDC_Pos)
	                               | (CONF_GCLK_GEN_1_GENEN << GCLK_GENCTRL_GENEN_Pos)
	                               | CONF_GCLK_GEN_1_SOURCE);
#endif
#if CONF_GCLK_GEN_2_GENEN == 1
	hri_gclk_write_GENCTRL_reg(GCLK,
	                           2,
	                           GCLK_GENCTRL_DIV(CONF_GCLK_GEN_2_DIV)
	                               | (CONF_GCLK_GEN_2_RUNSTDBY << GCLK_GENCTRL_RUNSTDBY_Pos)
	                               | (CONF_GCLK_GEN_2_DIVSEL << GCLK_GENCTRL_DIVSEL_Pos)
	                               | (CONF_GCLK_GEN_2_OE << GCLK_GENCTRL_OE_Pos)
	                               | (CONF_GCLK_GEN_2_OOV << GCLK_GENCTRL_OOV_Pos)
	                               | (CONF_GCLK_GEN_2_IDC << GCLK_GENCTRL_IDC_Pos)
	                               | (CONF_GCLK_GEN_2_GENEN << GCLK_GENCTRL_GENEN_Pos)
	                               | CONF_GCLK_GEN_2_SOURCE);
#endif
#if CONF_GCLK_GEN_3_GENEN == 1
	hri_gclk_write_GENCTRL_reg(GCLK,
	                           3,
	                           GCLK_GENCTRL_DIV(CONF_GCLK_GEN_3_DIV)
	                               | (CONF_GCLK_GEN_3_RUNSTDBY << GCLK_GENCTRL_RUNSTDBY_Pos)
	                               | (CONF_GCLK_GEN_3_DIVSEL << GCLK_GENCTRL_DIVSEL_Pos)
	                               | (CONF_GCLK_GEN_3_OE << GCLK_GENCTRL_OE_Pos)
	                               | (CONF_GCLK_GEN_3_OOV << GCLK_GENCTRL_OOV_Pos)
	                               | (CONF_GCLK_GEN_3_IDC << GCLK_GENCTRL_IDC_Pos)
	                               | (CONF_GCLK_GEN_3_GENEN << GCLK_GENCTRL_GENEN_Pos)
	                               | CONF_GCLK_GEN_3_SOURCE);
#endif
#if CONF_GCLK_GEN_4_GENEN == 1
	hri_gclk_write_GENCTRL_reg(GCLK,
	                           4,
	                           GCLK_GENCTRL_DIV(CONF_GCLK_GEN_4_DIV)
	                               | (CONF_GCLK_GEN_4_RUNSTDBY << GCLK_GENCTRL_RUNSTDBY_Pos)
	                               | (CONF_GCLK_GEN_4_DIVSEL << GCLK_GENCTRL_DIVSEL_Pos)
	                               | (CONF_GCLK_GEN_4_OE << GCLK_GENCTRL_OE_Pos)
	                               | (CONF_GCLK_GEN_4_OOV << GCLK_GENCTRL_OOV_Pos)
	                               | (CONF_GCLK_GEN_4_IDC << GCLK_GENCTRL_IDC_Pos)
	                               | (CONF_GCLK_GEN_4_GENEN << GCLK_GENCTRL_GENEN_Pos)
	                               | CONF_GCLK_GEN_4_SOURCE);
#endif
#if CONF_GCLK_GEN_5_GENEN == 1
	hri_gclk_write_GENCTRL_reg(GCLK,
	                           5,
	                           GCLK_GENCTRL_DIV(CONF_GCLK_GEN_5_DIV)
	                               | (CONF_GCLK_GEN_5_RUNSTDBY << GCLK_GENCTRL_RUNSTDBY_Pos)
	                               | (CONF_GCLK_GEN_5_DIVSEL << GCLK_GENCTRL_DIVSEL_Pos)
	                               | (CONF_GCLK_GEN_5_OE << GCLK_GENCTRL_OE_Pos)
	                               | (CONF_GCLK_GEN_5_OOV << GCLK_GENCTRL_OOV_Pos)
	                               | (CONF_GCLK_GEN_5_IDC << GCLK_GENCTRL_IDC_Pos)
	                               | (CONF_GCLK_GEN_5_GENEN << GCLK_GENCTRL_GENEN_Pos)
	                               | CONF_GCLK_GEN_5_SOURCE);
#endif
#if CONF_GCLK_GEN_6_GENEN == 1
	hri_gclk_write_GENCTRL_reg(GCLK,
	                           6,
	                           GCLK_GENCTRL_DIV(CONF_GCLK_GEN_6_DIV)
	                               | (CONF_GCLK_GEN_6_RUNSTDBY << GCLK_GENCTRL_RUNSTDBY_Pos)
	                               | (CONF_GCLK_GEN_6_DIVSEL << GCLK_GENCTRL_DIVSEL_Pos)
	                               | (CONF_GCLK_GEN_6_OE << GCLK_GENCTRL_OE_Pos)
	                               | (CONF_GCLK_GEN_6_OOV << GCLK_GENCTRL_OOV_Pos)
	                               | (CONF_GCLK_GEN_6_IDC << GCLK_GENCTRL_IDC_Pos)
	                               | (CONF_GCLK_GEN_6_GENEN << GCLK_GENCTRL_GENEN_Pos)
	                               | CONF_GCLK_GEN_6_SOURCE);
#endif
#if CONF_GCLK_GEN_7_GENEN == 1
	hri_gclk_write_GENCTRL_reg(GCLK,
	                           7,
	                           GCLK_GENCTRL_DIV(CONF_GCLK_GEN_7_DIV)
	                               | (CONF_GCLK_GEN_7_RUNSTDBY << GCLK_GENCTRL_RUNSTDBY_Pos)
	                               | (CONF_GCLK_GEN_7_DIVSEL << GCLK_GENCTRL_DIVSEL_Pos)
	                               | (CONF_GCLK_GEN_7_OE << GCLK_GENCTRL_OE_Pos)
	                               | (CONF_GCLK_GEN_7_OOV << GCLK_GENCTRL_OOV_Pos)
	                               | (CONF_GCLK_GEN_7_IDC << GCLK_GENCTRL_IDC_Pos)
	                               | (CONF_GCLK_GEN_7_GENEN << GCLK_GENCTRL_GENEN_Pos)
	                               | CONF_GCLK_GEN_7_SOURCE);
#endif
#if CONF_GCLK_GEN_8_GENEN == 1
	hri_gclk_write_GENCTRL_reg(GCLK,
	                           8,
	                           GCLK_GENCTRL_DIV(CONF_GCLK_GEN_8_DIV)
	                               | (CONF_GCLK_GEN_8_RUNSTDBY << GCLK_GENCTRL_RUNSTDBY_Pos)
	                               | (CONF_GCLK_GEN_8_DIVSEL << GCLK_GENCTRL_DIVSEL_Pos)
	                               | (CONF_GCLK_GEN_8_OE << GCLK_GENCTRL_OE_Pos)
	                               | (CONF_GCLK_GEN_8_OOV << GCLK_GENCTRL_OOV_Pos)
	                               | (CONF_GCLK_GEN_8_IDC << GCLK_GENCTRL_IDC_Pos)
	                               | (CONF_GCLK_GEN_8_GENEN << GCLK_GENCTRL_GENEN_Pos)
	                               | CONF_GCLK_GEN_8_SOURCE);
#endif
#if CONF_GCLK_GEN_9_GENEN == 1
	hri_gclk_write_GENCTRL_reg(GCLK,
	                           9,
	                           GCLK_GENCTRL_DIV(CONF_GCLK_GEN_9_DIV)
	                               | (CONF_GCLK_GEN_9_RUNSTDBY << GCLK_GENCTRL_RUNSTDBY_Pos)
	                               | (CONF_GCLK_GEN_9_DIVSEL << GCLK_GENCTRL_DIVSEL_Pos)
	                               | (CONF_GCLK_GEN_9_OE << GCLK_GENCTRL_OE_Pos)
	                               | (CONF_GCLK_GEN_9_OOV << GCLK_GENCTRL_OOV_Pos)
	                               | (CONF_GCLK_GEN_9_IDC << GCLK_GENCTRL_IDC_Pos)
	                               | (CONF_GCLK_GEN_9_GENEN << GCLK_GENCTRL_GENEN_Pos)
	                               | CONF_GCLK_GEN_9_SOURCE);
#endif
#if CONF_GCLK_GEN_10_GENEN == 1
	hri_gclk_write_GENCTRL_reg(GCLK,
	                           10,
	                           GCLK_GENCTRL_DIV(CONF_GCLK_GEN_10_DIV)
	                               | (CONF_GCLK_GEN_10_RUNSTDBY << GCLK_GENCTRL_RUNSTDBY_Pos)
	                               | (CONF_GCLK_GEN_10_DIVSEL << GCLK_GENCTRL_DIVSEL_Pos)
	                               | (CONF_GCLK_GEN_10_OE << GCLK_GENCTRL_OE_Pos)
	                               | (CONF_GCLK_GEN_10_OOV << GCLK_GENCTRL_OOV_Pos)
	                               | (CONF_GCLK_GEN_10_IDC << GCLK_GENCTRL_IDC_Pos)
	                               | (CONF_GCLK_GEN_10_GENEN << GCLK_GENCTRL_GENEN_Pos)
	                               | CONF_GCLK_GEN_10_SOURCE);
#endif
#if CONF_GCLK_GEN_11_GENEN == 1
	hri_gclk_write_GENCTRL_reg(GCLK,
	                           11,
	                           GCLK_GENCTRL_DIV(CONF_GCLK_GEN_11_DIV)
	                               | (CONF_GCLK_GEN_11_RUNSTDBY << GCLK_GENCTRL_RUNSTDBY_Pos)
	                               | (CONF_GCLK_GEN_11_DIVSEL << GCLK_GENCTRL_DIVSEL_Pos)
	                               | (CONF_GCLK_GEN_11_OE << GCLK_GENCTRL_OE_Pos)
	                               | (CONF_GCLK_GEN_11_OOV << GCLK_GENCTRL_OOV_Pos)
	                               | (CONF_GCLK_GEN_11_IDC << GCLK_GENCTRL_IDC_Pos)
	                               | (CONF_GCLK_GEN_11_GENEN << GCLK_GENCTRL_GENEN_Pos)
	                               | CONF_GCLK_GEN_11_SOURCE);
#endif
}

void _gclk_init_generators_by_fref(uint32_t bm)
{
#if CONF_GCLK_GEN_0_GENEN == 1
	if (bm & (1ul << 0)) {
		hri_gclk_write_GENCTRL_reg(GCLK,
		                           0,
		                           GCLK_GENCTRL_DIV(CONF_GCLK_GEN_0_DIV)
		                               | (CONF_GCLK_GEN_0_RUNSTDBY << GCLK_GENCTRL_RUNSTDBY_Pos)
		                               | (CONF_GCLK_GEN_0_DIVSEL << GCLK_GENCTRL_DIVSEL_Pos)
		                               | (CONF_GCLK_GEN_0_OE << GCLK_GENCTRL_OE_Pos)
		                               | (CONF_GCLK_GEN_0_OOV << GCLK_GENCTRL_OOV_Pos)
		                               | (CONF_GCLK_GEN_0_IDC << GCLK_GENCTRL_IDC_Pos)
		                               | (CONF_GCLK_GEN_0_GENEN << GCLK_GENCTRL_GENEN_Pos)
		                               | CONF_GCLK_GEN_0_SOURCE);
	}
#endif
#if CONF_GCLK_GEN_1_GENEN == 1
	if (bm & (1ul << 1)) {
		hri_gclk_write_GENCTRL_reg(GCLK,
		                           1,
		                           GCLK_GENCTRL_DIV(CONF_GCLK_GEN_1_DIV)
		                               | (CONF_GCLK_GEN_1_RUNSTDBY << GCLK_GENCTRL_RUNSTDBY_Pos)
		                               | (CONF_GCLK_GEN_1_DIVSEL << GCLK_GENCTRL_DIVSEL_Pos)
		                               | (CONF_GCLK_GEN_1_OE << GCLK_GENCTRL_OE_Pos)
		                               | (CONF_GCLK_GEN_1_OOV << GCLK_GENCTRL_OOV_Pos)
		                               | (CONF_GCLK_GEN_1_IDC << GCLK_GENCTRL_IDC_Pos)
		                               | (CONF_GCLK_GEN_1_GENEN << GCLK_GENCTRL_GENEN_Pos)
		                               | CONF_GCLK_GEN_1_SOURCE);
	}
#endif
#if CONF_GCLK_GEN_2_GENEN == 1
	if (bm & (1ul << 2)) {
		hri_gclk_write_GENCTRL_reg(GCLK,
		                           2,
		                           GCLK_GENCTRL_DIV(CONF_GCLK_GEN_2_DIV)
		                               | (CONF_GCLK_GEN_2_RUNSTDBY << GCLK_GENCTRL_RUNSTDBY_Pos)
		                               | (CONF_GCLK_GEN_2_DIVSEL << GCLK_GENCTRL_DIVSEL_Pos)
		                               | (CONF_GCLK_GEN_2_OE << GCLK_GENCTRL_OE_Pos)
		                               | (CONF_GCLK_GEN_2_OOV << GCLK_GENCTRL_OOV_Pos)
		                               | (CONF_GCLK_GEN_2_IDC << GCLK_GENCTRL_IDC_Pos)
		                               | (CONF_GCLK_GEN_2_GENEN << GCLK_GENCTRL_GENEN_Pos)
		                               | CONF_GCLK_GEN_2_SOURCE);
	}
#endif
#if CONF_GCLK_GEN_3_GENEN == 1
	if (bm & (1ul << 3)) {
		hri_gclk_write_GENCTRL_reg(GCLK,
		                           3,
		                           GCLK_GENCTRL_DIV(CONF_GCLK_GEN_3_DIV)
		                               | (CONF_GCLK_GEN_3_RUNSTDBY << GCLK_GENCTRL_RUNSTDBY_Pos)
		                               | (CONF_GCLK_GEN_3_DIVSEL << GCLK_GENCTRL_DIVSEL_Pos)
		                               | (CONF_GCLK_GEN_3_OE << GCLK_GENCTRL_OE_Pos)
		                               | (CONF_GCLK_GEN_3_OOV << GCLK_GENCTRL_OOV_Pos)
		                               | (CONF_GCLK_GEN_3_IDC << GCLK_GENCTRL_IDC_Pos)
		                               | (CONF_GCLK_GEN_3_GENEN << GCLK_GENCTRL_GENEN_Pos)
		                               | CONF_GCLK_GEN_3_SOURCE);
	}
#endif
#if CONF_GCLK_GEN_4_GENEN == 1
	if (bm & (1ul << 4)) {
		hri_gclk_write_GENCTRL_reg(GCLK,
		                           4,
		                           GCLK_GENCTRL_DIV(CONF_GCLK_GEN_4_DIV)
		                               | (CONF_GCLK_GEN_4_RUNSTDBY << GCLK_GENCTRL_RUNSTDBY_Pos)
		                               | (CONF_GCLK_GEN_4_DIVSEL << GCLK_GENCTRL_DIVSEL_Pos)
		                               | (CONF_GCLK_GEN_4_OE << GCLK_GENCTRL_OE_Pos)
		                               | (CONF_GCLK_GEN_4_OOV << GCLK_GENCTRL_OOV_Pos)
		                               | (CONF_GCLK_GEN_4_IDC << GCLK_GENCTRL_IDC_Pos)
		                               | (CONF_GCLK_GEN_4_GENEN << GCLK_GENCTRL_GENEN_Pos)
		                               | CONF_GCLK_GEN_4_SOURCE);
	}
#endif
#if CONF_GCLK_GEN_5_GENEN == 1
	if (bm & (1ul << 5)) {
		hri_gclk_write_GENCTRL_reg(GCLK,
		                           5,
		                           GCLK_GENCTRL_DIV(CONF_GCLK_GEN_5_DIV)
		                               | (CONF_GCLK_GEN_5_RUNSTDBY << GCLK_GENCTRL_RUNSTDBY_Pos)
		                               | (CONF_GCLK_GEN_5_DIVSEL << GCLK_GENCTRL_DIVSEL_Pos)
		                               | (CONF_GCLK_GEN_5_OE << GCLK_GENCTRL_OE_Pos)
		                               | (CONF_GCLK_GEN_5_OOV << GCLK_GENCTRL_OOV_Pos)
		                               | (CONF_GCLK_GEN_5_IDC << GCLK_GENCTRL_IDC_Pos)
		                               | (CONF_GCLK_GEN_5_GENEN << GCLK_GENCTRL_GENEN_Pos)
		                               | CONF_GCLK_GEN_5_SOURCE);
	}
#endif
#if CONF_GCLK_GEN_6_GENEN == 1
	if (bm & (1ul << 6)) {
		hri_gclk_write_GENCTRL_reg(GCLK,
		                           6,
		                           GCLK_GENCTRL_DIV(CONF_GCLK_GEN_6_DIV)
		                               | (CONF_GCLK_GEN_6_RUNSTDBY << GCLK_GENCTRL_RUNSTDBY_Pos)
		                               | (CONF_GCLK_GEN_6_DIVSEL << GCLK_GENCTRL_DIVSEL_Pos)
		                               | (CONF_GCLK_GEN_6_OE << GCLK_GENCTRL_OE_Pos)
		                               | (CONF_GCLK_GEN_6_OOV << GCLK_GENCTRL_OOV_Pos)
		                               | (CONF_GCLK_GEN_6_IDC << GCLK_GENCTRL_IDC_Pos)
		                               | (CONF_GCLK_GEN_6_GENEN << GCLK_GENCTRL_GENEN_Pos)
		                               | CONF_GCLK_GEN_6_SOURCE);
	}
#endif
#if CONF_GCLK_GEN_7_GENEN == 1
	if (bm & (1ul << 7)) {
		hri_gclk_write_GENCTRL_reg(GCLK,
		                           7,
		                           GCLK_GENCTRL_DIV(CONF_GCLK_GEN_7_DIV)
		                               | (CONF_GCLK_GEN_7_RUNSTDBY << GCLK_GENCTRL_RUNSTDBY_Pos)
		                               | (CONF_GCLK_GEN_7_DIVSEL << GCLK_GENCTRL_DIVSEL_Pos)
		                               | (CONF_GCLK_GEN_7_OE << GCLK_GENCTRL_OE_Pos)
		                               | (CONF_GCLK_GEN_7_OOV << GCLK_GENCTRL_OOV_Pos)
		                               | (CONF_GCLK_GEN_7_IDC << GCLK_GENCTRL_IDC_Pos)
		                               | (CONF_GCLK_GEN_7_GENEN << GCLK_GENCTRL_GENEN_Pos)
		                               | CONF_GCLK_GEN_7_SOURCE);
	}
#endif
#if CONF_GCLK_GEN_8_GENEN == 1
	if (bm & (1ul << 8)) {
		hri_gclk_write_GENCTRL_reg(GCLK,
		                           8,
		                           GCLK_GENCTRL_DIV(CONF_GCLK_GEN_8_DIV)
		                               | (CONF_GCLK_GEN_8_RUNSTDBY << GCLK_GENCTRL_RUNSTDBY_Pos)
		                               | (CONF_GCLK_GEN_8_DIVSEL << GCLK_GENCTRL_DIVSEL_Pos)
		                               | (CONF_GCLK_GEN_8_OE << GCLK_GENCTRL_OE_Pos)
		                               | (CONF_GCLK_GEN_8_OOV << GCLK_GENCTRL_OOV_Pos)
		                               | (CONF_GCLK_GEN_8_IDC << GCLK_GENCTRL_IDC_Pos)
		                               | (CONF_GCLK_GEN_8_GENEN << GCLK_GENCTRL_GENEN_Pos)
		                               | CONF_GCLK_GEN_8_SOURCE);
	}
#endif
#if CONF_GCLK_GEN_9_GENEN == 1
	if (bm & (1ul << 9)) {
		hri_gclk_write_GENCTRL_reg(GCLK,
		                           9,
		                           GCLK_GENCTRL_DIV(CONF_GCLK_GEN_9_DIV)
		                               | (CONF_GCLK_GEN_9_RUNSTDBY << GCLK_GENCTRL_RUNSTDBY_Pos)
		                               | (CONF_GCLK_GEN_9_DIVSEL << GCLK_GENCTRL_DIVSEL_Pos)
		                               | (CONF_GCLK_GEN_9_OE << GCLK_GENCTRL_OE_Pos)
		                               | (CONF_GCLK_GEN_9_OOV << GCLK_GENCTRL_OOV_Pos)
		                               | (CONF_GCLK_GEN_9_IDC << GCLK_GENCTRL_IDC_Pos)
		                               | (CONF_GCLK_GEN_9_GENEN << GCLK_GENCTRL_GENEN_Pos)
		                               | CONF_GCLK_GEN_9_SOURCE);
	}
#endif
#if CONF_GCLK_GEN_10_GENEN == 1
	if (bm & (1ul << 10)) {
		hri_gclk_write_GENCTRL_reg(GCLK,
		                           10,
		                           GCLK_GENCTRL_DIV(CONF_GCLK_GEN_10_DIV)
		                               | (CONF_GCLK_GEN_10_RUNSTDBY << GCLK_GENCTRL_RUNSTDBY_Pos)
		                               | (CONF_GCLK_GEN_10_DIVSEL << GCLK_GENCTRL_DIVSEL_Pos)
		                               | (CONF_GCLK_GEN_10_OE << GCLK_GENCTRL_OE_Pos)
		                               | (CONF_GCLK_GEN_10_OOV << GCLK_GENCTRL_OOV_Pos)
		                               | (CONF_GCLK_GEN_10_IDC << GCLK_GENCTRL_IDC_Pos)
		                               | (CONF_GCLK_GEN_10_GENEN << GCLK_GENCTRL_GENEN_Pos)
		                               | CONF_GCLK_GEN_10_SOURCE);
	}
#endif
#if CONF_GCLK_GEN_11_GENEN == 1
	if (bm & (1ul << 11)) {
		hri_gclk_write_GENCTRL_reg(GCLK,
		                           11,
		                           GCLK_GENCTRL_DIV(CONF_GCLK_GEN_11_DIV)
		                               | (CONF_GCLK_GEN_11_RUNSTDBY << GCLK_GENCTRL_RUNSTDBY_Pos)
		                               | (CONF_GCLK_GEN_11_DIVSEL << GCLK_GENCTRL_DIVSEL_Pos)
		                               | (CONF_GCLK_GEN_11_OE << GCLK_GENCTRL_OE_Pos)
		                               | (CONF_GCLK_GEN_11_OOV << GCLK_GENCTRL_OOV_Pos)
		                               | (CONF_GCLK_GEN_11_IDC << GCLK_GENCTRL_IDC_Pos)
		                               | (CONF_GCLK_GEN_11_GENEN << GCLK_GENCTRL_GENEN_Pos)
		                               | CONF_GCLK_GEN_11_SOURCE);
	}
#endif
}
