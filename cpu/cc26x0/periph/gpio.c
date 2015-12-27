/**
 * @ingroup     driver_periph
 * @{
 *
 * @file
 * @brief       low-level GPIO driver implementation
 *
 * @author      Leon M. George <leon@georgemail.eu>
 *
 * @}
 */

#include <stdint.h>

#include "cpu.h"
#include "sched.h"
#include "thread.h"
#include "periph/gpio.h"
#include "periph_conf.h"

// TODO PRCM->PDCTL0 |= PDCTL0_PERIPH_ON;
// TODO PRCM->GPIOCLKGR = 1
