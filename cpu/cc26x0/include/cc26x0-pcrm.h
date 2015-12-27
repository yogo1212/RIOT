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


typedef struct {
    reg32_t PWRCTL;
    reg32_t RESETCTL;
    reg32_t SLEEPCTL;
} AON_SYSCTL_REGS_t;

/** @addtogroup cpu_specific_peripheral_memory_map
  * @{
  */
#define AON_SYSCTL_BASE       0x40090000
/*@}*/

#define AON_SYSCTL ((AON_SYSCTL_REGS_t *) (AON_SYSCTL_BASE))


typedef struct {
    reg32_t MCUCLK;
    reg32_t AUXCLK;
    reg32_t MCUCFG;
    reg32_t AUXCFG;
    reg32_t AUXCTL;
    reg32_t PWRSTAT;
    reg32_t __reserved1;
    reg32_t SHUTDOWN;
    reg32_t CTL0;
    reg32_t CTL1;
    reg32_t __reserved2[2];
    reg32_t RECHARGECFG;
    reg32_t RECHARGESTAT;
    reg32_t __reserved3;
    reg32_t OSCCFG;
    reg32_t JTAGCFG;
    reg32_t JTAGUSERCODE;
} AON_WUC_REGS_t;

/** @addtogroup cpu_specific_peripheral_memory_map
  * @{
  */
#define AON_WUC_BASE       0x40091000
/*@}*/

#define AON_WUC ((AON_WUC_REGS_t *) (AON_WUC_BASE))


typedef struct {
    reg32_t INFRCLKDIVR;
    reg32_t INFRCLKDIVS;
    reg32_t INFRCLKDIVDS;
    reg32_t VDCTL;
    reg32_t __reserved1[6];
    reg32_t CLKLOADCTL;
    reg32_t RFCCLKG;
    reg32_t VIMSCLKG;
    reg32_t __reserved2[2];
    reg32_t SECDMACLKGR;
    reg32_t SECDMACLKGS;
    reg32_t SECDMACLKGDS;
    reg32_t GPIOCLKGR;
    reg32_t GPIOCLKGS;
    reg32_t GPIOCLKGDS;
    reg32_t GPTCLKGR;
    reg32_t GPTCLKGS;
    reg32_t GPTCLKGDS;
    reg32_t I2CCLKGR;
    reg32_t I2CCLKGS;
    reg32_t I2CCLKGDS;
    reg32_t UARTCLKGR;
    reg32_t UARTCLKGS;
    reg32_t UARTCLKGDS;
    reg32_t SSICLKGR;
    reg32_t SSICLKGS;
    reg32_t SSICLKGDS;
    reg32_t I2SCLKGR;
    reg32_t I2SCLKGS;
    reg32_t I2SCLKGDS;
    reg32_t __reserved3[10];
    reg32_t CPUCLKDIV;
    reg32_t I2SBCLKSEL;
    reg32_t GPTCLKDIV;
    reg32_t I2SCLKCTL;
    reg32_t I2SMCLKDIV;
    reg32_t I2SBCLKDIV;
    reg32_t I2SWCLKDIV;
    reg32_t __reserved4[11];
    reg32_t SWRESET;
    reg32_t WARMRESET;
    reg32_t __reserved5[6];
    reg32_t PDCTL0;
    reg32_t PDCTL0RFC;
    reg32_t PDCTL0SERIAL;
    reg32_t PDCTL0PERIPH;
    reg32_t __reserved6;
    reg32_t PDSTAT0;
    reg32_t PDSTAT0RFC;
    reg32_t PDSTAT0SERIAL;
    reg32_t PDSTAT0PERIPH;
    reg32_t __reserved7[11];
    reg32_t PDCTL1;
    reg32_t __reserved8;
    reg32_t PDCTL1CPU;
    reg32_t PDCTL1RFC;
    reg32_t PDCTL1VIMS;
    reg32_t __reserved9;
    reg32_t PDSTAT1;
    reg32_t PDSTAT1BUS;
    reg32_t PDSTAT1RFC;
    reg32_t PDSTAT1CPU;
    reg32_t PDSTAT1VIMS;
    reg32_t __reserved10[10];
    reg32_t RFCMODESEL;
    reg32_t __reserved11[20];
    reg32_t RAMRETEN;
} PCRM_REGS_t;

/** @addtogroup cpu_specific_peripheral_memory_map
  * @{
  */
#define PCRM_BASE       0x40082000
/*@}*/

#define PCRM ((PCRM_REGS_t *) (PCRM_BASE))

#define PCRM_CLKLOADCTL_LOAD        0x1
#define PCRM_CLKLOADCTL_LOADDONE    0x2

#ifdef __cplusplus
} /* end extern "C" */
#endif

#endif /* CC26x0_PCRM_H */

/*@}*/
