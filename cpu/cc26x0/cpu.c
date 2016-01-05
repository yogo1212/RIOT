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


#include "cc26x0-prcm.h"

#include "cpu.h"


/**
 * @brief Initialize the CPU, set IRQ priorities
 */
void cpu_init(void)
{
    /* initialize the Cortex-M core */
    cortexm_init();

    /* turn on the AUX and JTAG power domains */
    /* AON_WUC->AUXCTL = AUXCTL_AUX_FORCE_ON;
    AON_WUC->JTAGCFG = JTAGCFG_JTAG_PD_FORCE_ON;

    while (!(AON_WUC->PWRSTAT & PWRSTAT_AUX_PD_ON)) ;

    DDI_0_OSC->CTL0 = DDI_0_OSC_CTL0_SCLK_LF_SRC_SEL_LF_RCOSC; */
}
