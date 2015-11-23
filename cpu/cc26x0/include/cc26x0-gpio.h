/**
 * @addtogroup cpu_cc26x0
 * @{
 *
 * @file
 * @brief           Driver for the cc26x0 GPIO controller
 *
 * @author          Leon George <leon@georgemail.eu>
 *
 * @defgroup cc26x0-gpio CC26x0 General-Purpose I/O
 * @{
 */

#ifndef CC26x0_GPIO_H
#define CC26x0_GPIO_H

#include "cc26x0.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup cpu_specific_peripheral_memory_map
  * @{
  */
#define GPIO_BASE                   (PERIPH_BASE + 0x22000)
/** @} */

#define GPIO_DOUT                   (*((uint32_reg_t *)(GPIO_BASE + 0x80)))
#define GPIO_DOUT_SET               (*((uint32_reg_t *)(GPIO_BASE + 0x90)))
#define GPIO_DOUT_SET_n(n)          (GPIO_DOUT_SET = (1 << n))
#define GPIO_DOUT_CLR               (*((uint32_reg_t *)(GPIO_BASE + 0xA0)))
#define GPIO_DOUT_CLR_n(n)          (GPIO_DOUT_CLR = (1 << n))
#define GPIO_DOUT_TGL               (*((uint32_reg_t *)(GPIO_BASE + 0xB0)))
#define GPIO_DOUT_TGL_n(n)          (GPIO_DOUT_TGL = (1 << n))

#define GPIO_DIN                    (*((uint32_reg_t *)(GPIO_BASE + 0xC0)))
#define GPIO_DIN_n(n)               ((GPIO_DIN >> n) & 1)

#define GPIO_DOE                    (*((uint32_reg_t *)(GPIO_BASE + 0xD0)))
/* TODO */

#define GPIO_EVFLAGS                (*((uint32_reg_t *)(GPIO_BASE + 0xE0)))
/* TODO */


#ifdef __cplusplus
} /* end extern "C" */
#endif

#endif /* CC26x0_GPIO_H */

/** @} */
