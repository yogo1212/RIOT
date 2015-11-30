/**
 * @ingroup         cpu_cc26x0_definitions
 * @{
 *
 * @file
 * @brief           CC26x0 FCFG register definitions
 */

#ifndef CC26x0_FCFG_H
#define CC26x0_FCFG_H

/** @addtogroup cpu_specific_peripheral_memory_map
  * @{
  */
#define FCFG_BASE                   0x50001000 /**<  base address of CCFG memory */
/*@}*/

#define FCFG_MAC_BLE_0              (*(uint32_reg_t *)(FCFG_BASE + 0x2E8))
#define FCFG_MAC_BLE_1              (*(uint32_reg_t *)(FCFG_BASE + 0x2EC))

#define FCFG_MAC_15_4_0             (*(uint32_reg_t *)(FCFG_BASE + 0x2F0))
#define FCFG_MAC_15_4_1             (*(uint32_reg_t *)(FCFG_BASE + 0x2F4))

#endif /* CC26x0_FCFG_H */

/*@}*/