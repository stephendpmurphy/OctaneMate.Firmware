/* Auto-generated config file peripheral_clk_config.h */
#ifndef PERIPHERAL_CLK_CONFIG_H
#define PERIPHERAL_CLK_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

/**
 * \def CONF_CPU_FREQUENCY
 * \brief CPU's Clock frequency
 */
#ifndef CONF_CPU_FREQUENCY
#define CONF_CPU_FREQUENCY 96000000
#endif

// <y> RTC Clock Source
// <id> rtc_clk_selection
// <RTC_CLOCK_SOURCE"> RTC source
// <i> Select the clock source for RTC.
#ifndef CONF_GCLK_RTC_SRC
#define CONF_GCLK_RTC_SRC RTC_CLOCK_SOURCE
#endif

/**
 * \def CONF_GCLK_RTC_FREQUENCY
 * \brief RTC's Clock frequency
 */
#ifndef CONF_GCLK_RTC_FREQUENCY
#define CONF_GCLK_RTC_FREQUENCY 32768
#endif

// <y> Core Clock Source
// <id> core_gclk_selection

// <GCLK_PCHCTRL_GEN_GCLK0_Val"> Generic clock generator 0

// <GCLK_PCHCTRL_GEN_GCLK1_Val"> Generic clock generator 1

// <GCLK_PCHCTRL_GEN_GCLK2_Val"> Generic clock generator 2

// <GCLK_PCHCTRL_GEN_GCLK3_Val"> Generic clock generator 3

// <GCLK_PCHCTRL_GEN_GCLK4_Val"> Generic clock generator 4

// <GCLK_PCHCTRL_GEN_GCLK5_Val"> Generic clock generator 5

// <GCLK_PCHCTRL_GEN_GCLK6_Val"> Generic clock generator 6

// <GCLK_PCHCTRL_GEN_GCLK7_Val"> Generic clock generator 7

// <GCLK_PCHCTRL_GEN_GCLK8_Val"> Generic clock generator 8

// <GCLK_PCHCTRL_GEN_GCLK9_Val"> Generic clock generator 9

// <GCLK_PCHCTRL_GEN_GCLK10_Val"> Generic clock generator 10

// <GCLK_PCHCTRL_GEN_GCLK11_Val"> Generic clock generator 11

// <i> Select the clock source for CORE.
#ifndef CONF_GCLK_SERCOM0_CORE_SRC
#define CONF_GCLK_SERCOM0_CORE_SRC GCLK_PCHCTRL_GEN_GCLK0_Val
#endif

// <y> Slow Clock Source
// <id> slow_gclk_selection

// <GCLK_PCHCTRL_GEN_GCLK0_Val"> Generic clock generator 0

// <GCLK_PCHCTRL_GEN_GCLK1_Val"> Generic clock generator 1

// <GCLK_PCHCTRL_GEN_GCLK2_Val"> Generic clock generator 2

// <GCLK_PCHCTRL_GEN_GCLK3_Val"> Generic clock generator 3

// <GCLK_PCHCTRL_GEN_GCLK4_Val"> Generic clock generator 4

// <GCLK_PCHCTRL_GEN_GCLK5_Val"> Generic clock generator 5

// <GCLK_PCHCTRL_GEN_GCLK6_Val"> Generic clock generator 6

// <GCLK_PCHCTRL_GEN_GCLK7_Val"> Generic clock generator 7

// <GCLK_PCHCTRL_GEN_GCLK8_Val"> Generic clock generator 8

// <GCLK_PCHCTRL_GEN_GCLK9_Val"> Generic clock generator 9

// <GCLK_PCHCTRL_GEN_GCLK10_Val"> Generic clock generator 10

// <GCLK_PCHCTRL_GEN_GCLK11_Val"> Generic clock generator 11

// <i> Select the slow clock source.
#ifndef CONF_GCLK_SERCOM0_SLOW_SRC
#define CONF_GCLK_SERCOM0_SLOW_SRC GCLK_PCHCTRL_GEN_GCLK3_Val
#endif

/**
 * \def CONF_GCLK_SERCOM0_CORE_FREQUENCY
 * \brief SERCOM0's Core Clock frequency
 */
#ifndef CONF_GCLK_SERCOM0_CORE_FREQUENCY
#define CONF_GCLK_SERCOM0_CORE_FREQUENCY 96000000
#endif

/**
 * \def CONF_GCLK_SERCOM0_SLOW_FREQUENCY
 * \brief SERCOM0's Slow Clock frequency
 */
#ifndef CONF_GCLK_SERCOM0_SLOW_FREQUENCY
#define CONF_GCLK_SERCOM0_SLOW_FREQUENCY 32768
#endif

// <y> Core Clock Source
// <id> core_gclk_selection

// <GCLK_PCHCTRL_GEN_GCLK0_Val"> Generic clock generator 0

// <GCLK_PCHCTRL_GEN_GCLK1_Val"> Generic clock generator 1

// <GCLK_PCHCTRL_GEN_GCLK2_Val"> Generic clock generator 2

// <GCLK_PCHCTRL_GEN_GCLK3_Val"> Generic clock generator 3

// <GCLK_PCHCTRL_GEN_GCLK4_Val"> Generic clock generator 4

// <GCLK_PCHCTRL_GEN_GCLK5_Val"> Generic clock generator 5

// <GCLK_PCHCTRL_GEN_GCLK6_Val"> Generic clock generator 6

// <GCLK_PCHCTRL_GEN_GCLK7_Val"> Generic clock generator 7

// <GCLK_PCHCTRL_GEN_GCLK8_Val"> Generic clock generator 8

// <GCLK_PCHCTRL_GEN_GCLK9_Val"> Generic clock generator 9

// <GCLK_PCHCTRL_GEN_GCLK10_Val"> Generic clock generator 10

// <GCLK_PCHCTRL_GEN_GCLK11_Val"> Generic clock generator 11

// <i> Select the clock source for CORE.
#ifndef CONF_GCLK_SERCOM2_CORE_SRC
#define CONF_GCLK_SERCOM2_CORE_SRC GCLK_PCHCTRL_GEN_GCLK0_Val
#endif

// <y> Slow Clock Source
// <id> slow_gclk_selection

// <GCLK_PCHCTRL_GEN_GCLK0_Val"> Generic clock generator 0

// <GCLK_PCHCTRL_GEN_GCLK1_Val"> Generic clock generator 1

// <GCLK_PCHCTRL_GEN_GCLK2_Val"> Generic clock generator 2

// <GCLK_PCHCTRL_GEN_GCLK3_Val"> Generic clock generator 3

// <GCLK_PCHCTRL_GEN_GCLK4_Val"> Generic clock generator 4

// <GCLK_PCHCTRL_GEN_GCLK5_Val"> Generic clock generator 5

// <GCLK_PCHCTRL_GEN_GCLK6_Val"> Generic clock generator 6

// <GCLK_PCHCTRL_GEN_GCLK7_Val"> Generic clock generator 7

// <GCLK_PCHCTRL_GEN_GCLK8_Val"> Generic clock generator 8

// <GCLK_PCHCTRL_GEN_GCLK9_Val"> Generic clock generator 9

// <GCLK_PCHCTRL_GEN_GCLK10_Val"> Generic clock generator 10

// <GCLK_PCHCTRL_GEN_GCLK11_Val"> Generic clock generator 11

// <i> Select the slow clock source.
#ifndef CONF_GCLK_SERCOM2_SLOW_SRC
#define CONF_GCLK_SERCOM2_SLOW_SRC GCLK_PCHCTRL_GEN_GCLK3_Val
#endif

/**
 * \def CONF_GCLK_SERCOM2_CORE_FREQUENCY
 * \brief SERCOM2's Core Clock frequency
 */
#ifndef CONF_GCLK_SERCOM2_CORE_FREQUENCY
#define CONF_GCLK_SERCOM2_CORE_FREQUENCY 96000000
#endif

/**
 * \def CONF_GCLK_SERCOM2_SLOW_FREQUENCY
 * \brief SERCOM2's Slow Clock frequency
 */
#ifndef CONF_GCLK_SERCOM2_SLOW_FREQUENCY
#define CONF_GCLK_SERCOM2_SLOW_FREQUENCY 32768
#endif

// <y> Core Clock Source
// <id> core_gclk_selection

// <GCLK_PCHCTRL_GEN_GCLK0_Val"> Generic clock generator 0

// <GCLK_PCHCTRL_GEN_GCLK1_Val"> Generic clock generator 1

// <GCLK_PCHCTRL_GEN_GCLK2_Val"> Generic clock generator 2

// <GCLK_PCHCTRL_GEN_GCLK3_Val"> Generic clock generator 3

// <GCLK_PCHCTRL_GEN_GCLK4_Val"> Generic clock generator 4

// <GCLK_PCHCTRL_GEN_GCLK5_Val"> Generic clock generator 5

// <GCLK_PCHCTRL_GEN_GCLK6_Val"> Generic clock generator 6

// <GCLK_PCHCTRL_GEN_GCLK7_Val"> Generic clock generator 7

// <GCLK_PCHCTRL_GEN_GCLK8_Val"> Generic clock generator 8

// <GCLK_PCHCTRL_GEN_GCLK9_Val"> Generic clock generator 9

// <GCLK_PCHCTRL_GEN_GCLK10_Val"> Generic clock generator 10

// <GCLK_PCHCTRL_GEN_GCLK11_Val"> Generic clock generator 11

// <i> Select the clock source for CORE.
#ifndef CONF_GCLK_SERCOM5_CORE_SRC
#define CONF_GCLK_SERCOM5_CORE_SRC GCLK_PCHCTRL_GEN_GCLK0_Val
#endif

// <y> Slow Clock Source
// <id> slow_gclk_selection

// <GCLK_PCHCTRL_GEN_GCLK0_Val"> Generic clock generator 0

// <GCLK_PCHCTRL_GEN_GCLK1_Val"> Generic clock generator 1

// <GCLK_PCHCTRL_GEN_GCLK2_Val"> Generic clock generator 2

// <GCLK_PCHCTRL_GEN_GCLK3_Val"> Generic clock generator 3

// <GCLK_PCHCTRL_GEN_GCLK4_Val"> Generic clock generator 4

// <GCLK_PCHCTRL_GEN_GCLK5_Val"> Generic clock generator 5

// <GCLK_PCHCTRL_GEN_GCLK6_Val"> Generic clock generator 6

// <GCLK_PCHCTRL_GEN_GCLK7_Val"> Generic clock generator 7

// <GCLK_PCHCTRL_GEN_GCLK8_Val"> Generic clock generator 8

// <GCLK_PCHCTRL_GEN_GCLK9_Val"> Generic clock generator 9

// <GCLK_PCHCTRL_GEN_GCLK10_Val"> Generic clock generator 10

// <GCLK_PCHCTRL_GEN_GCLK11_Val"> Generic clock generator 11

// <i> Select the slow clock source.
#ifndef CONF_GCLK_SERCOM5_SLOW_SRC
#define CONF_GCLK_SERCOM5_SLOW_SRC GCLK_PCHCTRL_GEN_GCLK3_Val
#endif

/**
 * \def CONF_GCLK_SERCOM5_CORE_FREQUENCY
 * \brief SERCOM5's Core Clock frequency
 */
#ifndef CONF_GCLK_SERCOM5_CORE_FREQUENCY
#define CONF_GCLK_SERCOM5_CORE_FREQUENCY 96000000
#endif

/**
 * \def CONF_GCLK_SERCOM5_SLOW_FREQUENCY
 * \brief SERCOM5's Slow Clock frequency
 */
#ifndef CONF_GCLK_SERCOM5_SLOW_FREQUENCY
#define CONF_GCLK_SERCOM5_SLOW_FREQUENCY 32768
#endif

// <y> CAN1 Clock Source
// <id> can_gclk_selection

// <GCLK_PCHCTRL_GEN_GCLK0_Val"> Generic clock generator 0

// <GCLK_PCHCTRL_GEN_GCLK1_Val"> Generic clock generator 1

// <GCLK_PCHCTRL_GEN_GCLK2_Val"> Generic clock generator 2

// <GCLK_PCHCTRL_GEN_GCLK3_Val"> Generic clock generator 3

// <GCLK_PCHCTRL_GEN_GCLK4_Val"> Generic clock generator 4

// <GCLK_PCHCTRL_GEN_GCLK5_Val"> Generic clock generator 5

// <GCLK_PCHCTRL_GEN_GCLK6_Val"> Generic clock generator 6

// <GCLK_PCHCTRL_GEN_GCLK7_Val"> Generic clock generator 7

// <GCLK_PCHCTRL_GEN_GCLK8_Val"> Generic clock generator 8

// <GCLK_PCHCTRL_GEN_GCLK9_Val"> Generic clock generator 9

// <GCLK_PCHCTRL_GEN_GCLK10_Val"> Generic clock generator 10

// <GCLK_PCHCTRL_GEN_GCLK11_Val"> Generic clock generator 11

// <i> Select the clock source for CAN1.
#ifndef CONF_GCLK_CAN1_SRC
#define CONF_GCLK_CAN1_SRC GCLK_PCHCTRL_GEN_GCLK4_Val
#endif

/**
 * \def CONF_GCLK_CAN1_FREQUENCY
 * \brief CAN1's Clock frequency
 */
#ifndef CONF_GCLK_CAN1_FREQUENCY
#define CONF_GCLK_CAN1_FREQUENCY 48000000
#endif

// <<< end of configuration section >>>

#endif // PERIPHERAL_CLK_CONFIG_H
