/**
 * @ingroup         cpu_cc26x0_definitions
 * @{
 *
 * @file
 * @brief           CC26x0 TIMER register definitions
 */

#ifndef CC26x0_TIMER_H
#define CC26x0_TIMER_H

#include <cc26x0.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
    reg32_t CFG;
    reg32_t TAMR;
    reg32_t TBMR;
    reg32_t CTL;
    reg32_t SYNC;
    reg32_t __reserved1;
    reg32_t IMR;
    reg32_t RIS;
    reg32_t MIS;
    reg32_t ICLR;
    reg32_t TAILR;
    reg32_t TBILR;
    reg32_t TAMATCHR;
    reg32_t TBMATCHR;
    reg32_t TAPR;
    reg32_t TBPR;
    reg32_t TAPMR;
    reg32_t TBPMR;
    reg32_t TAR;
    reg32_t TBR;
    reg32_t TAV;
    reg32_t TBV;
    reg32_t RTCPD;
    reg32_t TAPS;
    reg32_t TBPS;
    reg32_t TAPV;
    reg32_t TBPV;
    reg32_t DMAEV;
    reg32_t __reserved2[0xF94];
    reg32_t VERSION;
    reg32_t ANDCCP;
} GPT_REGS_t;

/** @addtogroup cpu_specific_peripheral_memory_map
  * @{
  */
#define GPT_BASE      0x40010000
/*@}*/

#define GPT_n(n)            ((GPT_REGS_t *) ((GPT_BASE) + (n * 0x1000)))

#define GPTIMER_NUMOF       1

#ifdef __cplusplus
} /* end extern "C" */
#endif

#endif /* CC26x0_TIMER_H */

/*@}*/
