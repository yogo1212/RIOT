/**
 * @ingroup         cpu_cc26x0_definitions
 * @{
 *
 * @file
 * @brief           CC26x0 FCFG register definitions
 */

#ifndef CC26x0_FCFG_H
#define CC26x0_FCFG_H

#include <cc26x0.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup cpu_specific_peripheral_memory_map
  * @{
  */
#define FCFG_BASE                           0x50001000 /**<  base address of FCFG memory */
/*@}*/

typedef struct {
	uint8_t __reserved1[0xA0];
	/* TODO does it pad here? */
	uint32_reg_t MISC_CONF_1;
	uint32_reg_t __reserved2[8];
	uint32_reg_t CONFIG_RF_FRONTEND_DIV5;
	uint32_reg_t CONFIG_RF_FRONTEND_DIV6;
	uint32_reg_t CONFIG_RF_FRONTEND_DIV10;
	uint32_reg_t CONFIG_RF_FRONTEND_DIV12;
	uint32_reg_t CONFIG_RF_FRONTEND_DIV15;
	uint32_reg_t CONFIG_RF_FRONTEND_DIV30;
	uint32_reg_t CONFIG_SYNTH_DIV5;
	uint32_reg_t CONFIG_SYNTH_DIV6;
	uint32_reg_t CONFIG_SYNTH_DIV10;
	uint32_reg_t CONFIG_SYNTH_DIV12;
	uint32_reg_t CONFIG_SYNTH_DIV15;
	uint32_reg_t CONFIG_SYNTH_DIV30;
	uint32_reg_t CONFIG_MISC_ADC_DIV5;
	uint32_reg_t CONFIG_MISC_ADC_DIV6;
	uint32_reg_t CONFIG_MISC_ADC_DIV10;
	uint32_reg_t CONFIG_MISC_ADC_DIV12;
	uint32_reg_t CONFIG_MISC_ADC_DIV15;
	uint32_reg_t CONFIG_MISC_ADC_DIV30;
	uint32_reg_t __reserved3[3];
	uint32_reg_t SHDW_DIE_ID_0;
	uint32_reg_t SHDW_DIE_ID_1;
	uint32_reg_t SHDW_DIE_ID_2;
	uint32_reg_t SHDW_DIE_ID_3;
	uint32_reg_t __reserved4[4];
	uint32_reg_t SHDW_OSC_BIAS_LDO_TRIM;
	uint32_reg_t SHDW_ANA_TRIM;
	uint32_reg_t __reserved5[9];
	uint32_reg_t FLASH_NUMBER;
	uint32_reg_t FLASH_COORDINATE;
	uint32_reg_t FLASH_E_P;
	uint32_reg_t FLASH_C_E_P_R;
	uint32_reg_t FLASH_P_R_PV;
	uint32_reg_t FLASH_EH_SEQ;
	uint32_reg_t FLASH_VHV_E;
	uint32_reg_t FLASH_PP;
	uint32_reg_t FLASH_PROG_EP;
	uint32_reg_t FLASH_ERA_PW;
	uint32_reg_t FLASH_VHV;
	uint32_reg_t FLASH_VHV_PV;
	uint32_reg_t FLASH_V;
	uint32_reg_t __reserved6[0x3E];
	uint32_reg_t USER_ID;
	uint32_reg_t __reserved7[6];
	uint32_reg_t FLASH_OTP_DATA3;
	uint32_reg_t ANA2_TRIM;
	uint32_reg_t LDO_TRIM;
	uint32_reg_t __reserved8[0xB];
	uint32_reg_t MAC_BLE_0;
	uint32_reg_t MAC_BLE_1;
	uint32_reg_t MAC_15_4_0;
	uint32_reg_t MAC_15_4_1;
	uint32_reg_t __reserved9[4];
	uint32_reg_t FLASH_OTP_DATA4;
	uint32_reg_t MISC_TRIM;
	uint32_reg_t RCOSC_HF_TEMPCOMP;
	uint32_reg_t __reserved10;
	uint32_reg_t ICEPICK_DEVICE_ID;
	uint32_reg_t FCFG1_REVISION;
	uint32_reg_t MISC_OTP_DATA;
	uint32_reg_t __reserved11[8];
	uint32_reg_t IOCONF;
	uint32_reg_t __reserved12;
	uint32_reg_t CONFIG_IF_ADC;
	uint32_reg_t CONFIG_OSC_TOP;
	uint32_reg_t CONFIG_RF_FRONTEND;
	uint32_reg_t CONFIG_SYNTH;
	uint32_reg_t SOC_ADC_ABS_GAIN;
	uint32_reg_t SOC_ADC_REL_GAIN;
	uint32_reg_t __reserved13;
	uint32_reg_t SOC_ADC_OFFSET_INT;
	uint32_reg_t SOC_ADC_REF_TRIM_AND_OFFSET_E;
	uint32_reg_t XT;
	uint32_reg_t AMPCOMP_TH1;
	uint32_reg_t AMPCOMP_TH2;
	uint32_reg_t AMPCOMP_CTRL1;
	uint32_reg_t ANABYPASS_VALUE2;
	uint32_reg_t CONFIG_MISC_ADC;
	uint32_reg_t __reserved14;
	uint32_reg_t VOLT_TRIM;
	uint32_reg_t OSC_CONF;
	uint32_reg_t __reserved15;
	uint32_reg_t VOLT_TRIM;
	uint32_reg_t CAP_TRIM;
	uint32_reg_t MISC_OTP_DATA_1;
	uint32_reg_t PWD_CURR_20C;
	uint32_reg_t PWD_CURR_35C;
	uint32_reg_t PWD_CURR_50C;
	uint32_reg_t PWD_CURR_65C;
	uint32_reg_t PWD_CURR_80C;
	uint32_reg_t PWD_CURR_95C;
	uint32_reg_t PWD_CURR_110C;
	uint32_reg_t PWD_CURR_125C;
} FCFG_REGS_t;

#define FCFG (*((FCFG_REGS_t *) (FCFG_BASE)))

#ifdef __cplusplus
} /* end extern "C" */
#endif

#endif /* CC26x0_FCFG_H */

/*@}*/
