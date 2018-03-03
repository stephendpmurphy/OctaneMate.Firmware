/* Auto-generated config file hpl_crccu_config.h */
#ifndef HPL_CRCCU_CONFIG_H
#define HPL_CRCCU_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <h> Basic configuration

// <o> Request Divider <0-7>
// <i> CRCCU DMA performs successive transfers. It is possible to reduce
// <i> the bandwidth drained by the CRCCU DMA by programming the DIVIDER
// <i> field. The transfer request frequency is divided by 2^(DIVIDER+1).
// <id> crccu_mr_divider
#ifndef CONF_CRCCU_MR_DIVIDER
#define CONF_CRCCU_MR_DIVIDER 0
#endif

// </h>

// <<< end of configuration section >>>

#endif // HPL_CRCCU_CONFIG_H
