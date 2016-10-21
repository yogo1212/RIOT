/*
 * Copyright (C) 2016 Leon George
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

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
#include "periph_conf.h"

#ifndef HF_CLOCK_SOURCE
#define HF_CLOCK_SOURCE DDI_0_OSC_CTL0_SCLK_HF_SRC_SEL_XOSC /* set 48MHz XOSC */
#endif
#ifndef LF_CLOCK_SOURCE
#define LF_CLOCK_SOURCE DDI_0_OSC_CTL0_SCLK_LF_SRC_SEL_HF_RCOSC /* set 31.25kHz derived from 48MHz RCOSC */
#endif

/**
 *@brief Configure the MCU system clock
 */
static void cpu_clock_init(void);

/**
 * @brief Initialize the CPU, set IRQ priorities
 */
void cpu_init(void)
{
    /* initialize the Cortex-M core */
    cortexm_init();

    /* initialize the system clock */
    cpu_clock_init();
}

/*
 * TODO use both masks for stripping
 * 0x00BC0000 = move_bits(0x4562F890, 12, 18, 6)
 * #define move_bits(value, from, to, bit_size)\
 *     (\
 *         ( (value>>from) & (~(~0 << bit_size))) << to\
 *     )
 */

#define move_field(in, from_mask, to_mask)\
    (\
        (((in\
           & from_mask)\
          >> __builtin_ctz(from_mask))\
         << __builtin_ctz(to_mask))\
        & to_mask\
    )

static void trim_ampcomp_th1(void)
{
    uint32_t trim = 0;

    trim |= move_field(FCFG->AMPCOMP_TH1,
                      FCFG_AMPCOMP_TH1_HPMRAMP1_TH_MASK,
                      DDI_0_OSC_AMPCOMPTH1_HPMRAMP1_TH_MASK);

    trim |= move_field(FCFG->AMPCOMP_TH1,
                      FCFG_AMPCOMP_TH1_IBIASCAP_LPTOHP_OL_CNT_MASK,
                      DDI_0_OSC_AMPCOMPTH1_IBIASCAP_LPTOHP_OL_CNT_MASK);

    trim |= move_field(FCFG->AMPCOMP_TH1,
                      FCFG_AMPCOMP_TH1_HPMRAMP3_HTH_MASK,
                      DDI_0_OSC_AMPCOMPTH1_HPMRAMP3_HTH_MASK);

    trim |= move_field(FCFG->AMPCOMP_TH1,
                      FCFG_AMPCOMP_TH1_HPMRAMP3_LTH_MASK,
                      DDI_0_OSC_AMPCOMPTH1_HPMRAMP3_LTH_MASK);

    DDI_0_OSC->AMPCOMPTH1 = trim;
}

static void trim_ampcomp_th2(void)
{
    uint32_t trim = 0;

    trim |= move_field(FCFG->AMPCOMP_TH2,
                      FCFG_AMPCOMP_TH2_ADC_COMP_AMPTH_HPM_MASK,
                      DDI_0_OSC_AMPCOMPTH2_COMP_AMPTH_HPM_MASK);

    trim |= move_field(FCFG->AMPCOMP_TH2,
                      FCFG_AMPCOMP_TH2_ADC_COMP_AMPTH_LPM_MASK,
                      DDI_0_OSC_AMPCOMPTH2_ADC_COMP_AMPTH_LPM_MASK);

    trim |= move_field(FCFG->AMPCOMP_TH2,
                      FCFG_AMPCOMP_TH2_LPMUPDATE_HTM_MASK,
                      DDI_0_OSC_AMPCOMPTH2_LPMUPDATE_HTH_MASK);

    trim |= move_field(FCFG->AMPCOMP_TH2,
                      FCFG_AMPCOMP_TH2_LPMUPDATE_LTH_MASK,
                      DDI_0_OSC_AMPCOMPTH2_LPMUPDATE_LTH_MASK);

    DDI_0_OSC->AMPCOMPTH2 = trim;
}

static int8_t int4_add_clamped(int8_t ui, int8_t i)
{
    if (i & 0x08) {
        i &= 0xF0;
    }
    ui += i;
    if (ui < 0) {
        ui = 0;
    }
    else if (ui > 0xF) {
        ui = 0xF;
    }
    return ui;
}

static void trim_ampcomp_ctrl(void)
{
    uint32_t trim = 0;

    trim |= move_field(FCFG->AMPCOMP_CTRL1,
                      FCFG_AMPCOMP_CTRL1_IBIASCAP_HPTOLP_OL_CNT_MASK,
                      DDI_0_OSC_AMPCOMPCTL_IBIASCAP_HPTOLP_OL_CNT_MASK);

    trim |= move_field(FCFG->AMPCOMP_CTRL1,
                      FCFG_AMPCOMP_CTRL1_CAP_STEP_MASK,
                      DDI_0_OSC_AMPCOMPCTL_CAP_STEP_MASK);

    trim |= move_field(FCFG->AMPCOMP_CTRL1,
                      FCFG_AMPCOMP_CTRL1_LPM_IBIAS_WAIT_CNT_FINAL_MASK,
                      DDI_0_OSC_AMPCOMPCTL_LPM_IBIAS_WAIT_CNT_FINAL_MASK);

    int8_t ibias_init = move_field(FCFG->AMPCOMP_CTRL1,
                                  FCFG_AMPCOMP_CTRL1_IBIAS_INIT_MASK,
                                  0xF);
    int8_t ibias_offset = move_field(FCFG->AMPCOMP_CTRL1,
                                    FCFG_AMPCOMP_CTRL1_IBIAS_OFFSET_MASK,
                                    0xF);
    /* check whether we need to apply delta from CCFG */
    if ((CCFG->SIZE_AND_DIS_FLAGS & CCFG_SIZE_AND_DIS_FLAGS_DIS_XOSC_OVR) == 0) {
        ibias_init = int4_add_clamped(ibias_init,
                                      (CCFG->MODE_CONF_1 & CCFG_MODE_CONF_1_DELTA_IBIAS_OFFSET_MASK)
                                       >> __builtin_ctz(CCFG_MODE_CONF_1_DELTA_IBIAS_OFFSET_MASK)
                                     );

        ibias_offset = int4_add_clamped(ibias_offset,
                                        (CCFG->MODE_CONF_1 & CCFG_MODE_CONF_1_DELTA_IBIAS_OFFSET_MASK)
                                         >> __builtin_ctz(CCFG_MODE_CONF_1_DELTA_IBIAS_OFFSET_MASK)
                                       );
    }

    trim |= move_field(ibias_init,
                  0xF,
                  DDI_0_OSC_AMPCOMPCTL_IBIAS_INIT_MASK);

    trim |= move_field(ibias_offset,
                  0xF,
                  DDI_0_OSC_AMPCOMPCTL_IBIAS_OFFSET_MASK);

    uint32_t chip_revision = FCFG->FCFG1_REVISION;
    if ((chip_revision != 0xFFFFFFFF) && (chip_revision >= 0x00000022)) {
        trim |= move_field(FCFG->AMPCOMP_CTRL1,
                          FCFG_AMPCOMP_CTRL1_AMPCOMP_REQ_MODE,
                          DDI_0_OSC_AMPCOMPCTL_AMPCOMP_REQ_MODE);
    }

    DDI_0_OSC->AMPCOMPCTL = trim;
}

/**
 * @brief TI configuration
 */
static void prepare_for_xoschf(void)
{
    /* request SMPH on behalf of AUX_SCE (ADI/DDI HW workaround) */
    AUX_WUC->MODCLKEN1 |= MODCLKEN1_SMPH_EN;

    /* enable AUX_ADI4 clock */
    AUX_WUC->MODCLKEN0 |= MODCLKEN0_AUX_ADI4_EN;

    /*
     * the following sequence is required for using XOSCHF,
     * if not included the device crashes when trying to switch to XOSCHF
     */

    /* trim AMPCOMP settings required before switch to XOSCHF */
    trim_ampcomp_th2();
    trim_ampcomp_th1();
    trim_ampcomp_ctrl();
}

static void cpu_clock_init(void)
{
    AON_WUC->AUXCTL |= AUXCTL_AUX_FORCE_ON; /* power on AUX_PD */
    while(!(AON_WUC->PWRSTAT & PWRSTAT_AUX_PD_ON)); /* wait for AUX_PD to be powered on */
    AUX_WUC->MODCLKEN0 |= MODCLKEN0_AUX_DDI0_OSC_EN; /* turn on oscillator interface clock */

    if (HF_CLOCK_SOURCE & DDI_0_OSC_CTL0_SCLK_HF_SRC_SEL_XOSC) {
        /* undocumented setup */
        prepare_for_xoschf();
    }

    DDI_0_OSC->CTL0 |= HF_CLOCK_SOURCE | LF_CLOCK_SOURCE /* configure HF and LF clocks */
                    | DDI_0_OSC_CTL0_SCLK_MF_SRC_SEL
                    | DDI_0_OSC_CTL0_XTAL_IS_24M;

    while ((DDI_0_OSC->STAT0 & 0x1) == 0) { }

    HAPI->HFSourceSafeSwitch();
}
