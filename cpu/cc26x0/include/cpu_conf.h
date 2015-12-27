/**
 * @addtogroup      cpu_cc26x0
 * @{
 *
 * @file
 * @brief           Implementation specific CPU configuration options
 *
 */

#ifndef __CPU_CONF_H
#define __CPU_CONF_H

#include <cc26x0.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   ARM Cortex-M specific CPU configuration
 * @{
 */
#define CPU_DEFAULT_IRQ_PRIO            (1U)
#define CPU_IRQ_NUMOF                   PERIPH_COUNT_IRQn
#define CPU_FLASH_BASE                  FLASH_BASE
/** @} */

#ifdef __cplusplus
} /* end extern "C" */
#endif

#endif /* __CPU_CONF_H */
/** @} */
