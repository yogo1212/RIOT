/**
 * @ingroup         cpu_cc26x0_definitions
 * @{
 *
 * @file
 * @brief           CC26x0 VIMS register definitions
 */

#ifndef CC26x0_VIMS_H
#define CC26x0_VIMS_H

/** @addtogroup cpu_specific_peripheral_memory_map
  * @{
  */
#define VIMS_BASE                           0x40034000 /**< base address of VIMS memory */
/*@}*/

typedef struct {
    uint32_reg_t STAT;
    uint32_reg_t CTL;
} VIMS_REGS_t;

#define VIMS                                (*(VIMS_REGS_t *)(VIMS_BASE + 0x4))

#define VIMS_CTL_STATS_CLR                  0x80000000
#define VIMS_CTL_STATS_CLR_m                0x80000000

#define VIMS_CTL_STATS_EN                   0x40000000
#define VIMS_CTL_STATS_EN_m                 0x40000000

#define VIMS_CTL_DYN_CG_EN                  0x20000000
#define VIMS_CTL_DYN_CG_EN_m                0x20000000

#define VIMS_CTL_IDCODE_LB_DIS              0x00000020
#define VIMS_CTL_IDCODE_LB_DIS_m            0x00000020

#define VIMS_CTL_SYSBUS_LB_DIS              0x00000010
#define VIMS_CTL_SYSBUS_LB_DIS_m            0x00000010

#define VIMS_CTL_ARB_CFG                    0x00000008
#define VIMS_CTL_ARB_CFG_m                  0x00000008

#define VIMS_CTL_PREF_EN                    0x00000004
#define VIMS_CTL_PREF_EN_m                  0x00000004

#define VIMS_CTL_MODE_GPRAM                 0x00000000
#define VIMS_CTL_MODE_CACHE                 0x00000001
#define VIMS_CTL_MODE_SPLIT                 0x00000002
#define VIMS_CTL_MODE_OFF                   0x00000003
#define VIMS_CTL_MODE_m                     0x00000003

#endif /* CC26x0_VIMS_H */

/*@}*/
