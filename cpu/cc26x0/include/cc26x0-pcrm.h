/**
 * @ingroup         cpu_cc26x0_definitions
 * @{
 *
 * @file
 * @brief           CC26x0 PCRM register definitions
 */

#ifndef CC26x0_PCRM_H
#define CC26x0_PCRM_H

#include <cc26x0.h>

#include <cc26x0-aux.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup cpu_specific_peripheral_memory_map
  * @{
  */
#define AUX_SMPH_BASE               0x400C8000
/*@}*/

typedef struct {
    reg32_t SMPH0;
    reg32_t SMPH1;
    reg32_t SMPH2;
    reg32_t SMPH3;
    reg32_t SMPH4;
    reg32_t SMPH5;
    reg32_t SMPH6;
    reg32_t SMPH7;
    reg32_t AUTOTAKE;
} SMPH_REGS_t;

#define AUX_SMPH ((SMPH_REGS_t *) (AUX_SMPH_BASE))

#define ADDI_SEM AUX_SMPH->SMPH0

/**
 * return true if interrupts have been disabled; false if they have been already
 */
bool addi_reg_access_prepare(void)
{
    bool ie = !__get_PRIMASK();
    __disable_irq();
    while (!ADDI_SEM);
    return ie;
}

void addi_reg_acces_finish(bool ie)
{
    ADDI_SEM = 1;
    if (ie) {
        __enable_irq();
    }
}

typedef struct {
    reg32_t CTL0;
    reg32_t CTL1;
    reg32_t RADCEXTCFG;
    reg32_t AMPCOMPCTL;
    reg32_t AMPCOMPTH1;
    reg32_t AMPCOMPTH2;
    reg32_t ANABYPASSVAL1;
    reg32_t ANABYPASSVAL2;
    reg32_t ATESTCTL;
    reg32_t ADCDOUBLERNANOAMPCTL;
    reg32_t XOSCHFCTL;
    reg32_t LFOSCCTL;
    reg32_t RCOSCHFCTL;
    reg32_t STAT0;
    reg32_t STAT1;
    reg32_t STAT2;
} DDI0_OSC_REGS_t;

/** @addtogroup cpu_specific_peripheral_memory_map
  * @{
  */
#define DDI0_OSC_BASE       0x400CA000
/*@}*/

#define DDI_0_OSC ((DDI0_OSC_REGS_t *) (DDI0_OSC_BASE))

#ifdef __cplusplus
} /* end extern "C" */
#endif

#endif /* CC26x0_PCRM_H */

/*@}*/
