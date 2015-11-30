/**
 * @ingroup         cpu_cc26x0_definitions
 * @{
 *
 * @file
 * @brief           CC26x0 CCFG register definitions
 */

#ifndef CC26x0_CCFG_H
#define CC26x0_CCFG_H

#include <cc26x0.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup cpu_specific_peripheral_memory_map
  * @{
  */
#define CCFG_BASE                           0x50003000 /**<  base address of CCFG memory */
/*@}*/

/* TODO not present in datasheet but explained in cc26x0ware-lds */
#define CCFG_SIZE_AND_DIS_FLAGS_DIS_GPRAM   0x00000004

typedef struct {
	uint32_regs_t __reserved1[0x3EA];
	uint32_reg_t EXT_LF_CLK;
	uint32_reg_t MODE_CONF_1;
	uint32_reg_t SIZE_AND_DIS_FLAGS;
	uint32_reg_t MODE_CONF;
	uint32_reg_t VOLT_LOAD_0;
	uint32_reg_t VOLT_LOAD_1;
	uint32_reg_t RTC_OFFSET;
	uint32_reg_t FREQ_OFFSET;
	uint32_reg_t IEEE_MAC_0;
	uint32_reg_t IEEE_MAC_1;
	uint32_reg_t IEEE_BLE_0;
	uint32_reg_t IEEE_BLE_1;
	uint32_reg_t BL_CONFIG;
	uint32_reg_t ERASE_CONF;
	uint32_reg_t CCFG_TI_OPTIONS;
	uint32_reg_t CCFG_TAP_DAP_0;
	uint32_reg_t CCFG_TAP_DAP_1;
	uint32_reg_t IMAGE_VALID_CONF;
	uint32_reg_t CCFG_PROT_31_0;
	uint32_reg_t CCFG_PROT_63_32;
	uint32_reg_t CCFG_PROT_95_64;
	uint32_reg_t CCFG_PROT_127_96;
} CCFG_REGS_t;

#define CCFG (*((CCFG_REGS_t *) (CCFG_BASE)))

#ifdef __cplusplus
} /* end extern "C" */
#endif

#endif /* CC26x0_CCFG_H */

/*@}*/
