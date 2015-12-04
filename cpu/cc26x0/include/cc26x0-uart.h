/**
 * @addtogroup      cpu_cc26x0
 * @{
 *
 * @file
 * @brief           CC26x0 UART interface
 *
 */

#ifndef CC26x0_UART_H
#define CC26x0_UART_H

#include "cc26x0.h"

#ifdef __cplusplus
extern "C" {
#endif

#define UART_BASE       (PERIPH_BASE + 0x1000)

/**
 * @brief UART component registers
 */
typedef struct {
    reg32_t DR;
    union {
        reg32_t RSR;
        reg32_t ECR;
    };
    reg32_t __reserved1[4];
    reg32_t FR;
    reg32_t __reserved2[2];
    reg32_t IBRD;
    reg32_t FBRD;
    reg32_t LCRH;
    reg32_t CTL;
    reg32_t IFLS;
    reg32_t IMSC;
    reg32_t RIS;
    reg32_t MIS;
    reg32_t ICR;
    reg32_t DMACTL;
} UART_REGS_t;

#define UART (*((UART_REGS_t *) (UART_BASE)))

#ifdef __cplusplus
} /* end extern "C" */
#endif

#endif /* CC26x8_UART_H */
/** @} */
