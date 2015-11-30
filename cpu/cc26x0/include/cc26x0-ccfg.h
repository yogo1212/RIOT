/**
 * @ingroup         cpu_cc26x0_definitions
 * @{
 *
 * @file
 * @brief           CC26x0 MCU interrupt definitions
 */

#ifndef CC26x0_CCFG_H
#define CC26x0_CCFG_H

/** @addtogroup cpu_specific_peripheral_memory_map
  * @{
  */
#define CCFG_BASE                           0x50003000 /**<  base address of CCFG memory */
/*@}*/

#define CCFG_SIZE_AND_DIS_FLAGS             (*(uint32_reg_t *)(CCFG_BASE + 0xFB0))

/* not present in datasheet but used and explained in cc26x0ware-lds */
#define CCFG_SIZE_AND_DIS_FLAGS_DIS_GPRAM   0x00000004

#define CCFG_IEEE_MAC_0                     (*(uint32_reg_t *)(CCFG_BASE + 0xFC8))
#define CCFG_IEEE_MAC_1                     (*(uint32_reg_t *)(CCFG_BASE + 0xFCC))
#define CCFG_IEEE_BLE_0                     (*(uint32_reg_t *)(CCFG_BASE + 0xFD0))
#define CCFG_IEEE_BLE_1                     (*(uint32_reg_t *)(CCFG_BASE + 0xFD4))


#endif /* CC26x0_CCFG_H */

/*@}*/
