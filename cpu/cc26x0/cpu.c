/**
 * @ingroup     cpu_cc26x0
 * @{
 *
 * @file
 * @brief       implementation of the CPU initialization
 *
 * @author      Leon M. George <leon@georgemail.eu>
 * @}
 */

#include "cpu.h"


/**
 * @brief Initialize the CPU, set IRQ priorities
 */
void cpu_init(void)
{
    /* initialize the Cortex-M core */
    cortexm_init();
}
