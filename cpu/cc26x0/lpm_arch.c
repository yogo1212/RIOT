/**
 * @ingroup     cpu_cc26x0
 * @{
 *
 * @file
 * @brief       implementation of the kernels power management interface
 *
 * @}
 */

#include "arch/lpm_arch.h"

void lpm_arch_init(void)
{
}

enum lpm_mode lpm_arch_set(enum lpm_mode target)
{
    return 0;
}

enum lpm_mode lpm_arch_get(void)
{
    return 0;
}

void lpm_arch_awake(void)
{
}

void lpm_arch_begin_awake(void)
{
}

void lpm_arch_end_awake(void)
{
}
