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
    uint32_reg_t DR;
    union {
        uint32_reg_t RSR;
        uint32_reg_t ECR;
    };
    uint32_reg_t __reserved1[4];
    uint32_reg_t FR;
    uint32_reg_t __reserved2[2];
    uint32_reg_t IBRD;
    uint32_reg_t FBRD;
    uint32_reg_t LCRH;
    uint32_reg_t CTL;
    uint32_reg_t IFLS;
    uint32_reg_t IMSC;
    uint32_reg_t RIS;
    uint32_reg_t MIS;
    uint32_reg_t ICR;
    uint32_reg_t DMACTL;
} UART_REGS_t;

#define UART (*((UART_REGS_t *) (UART_BASE)))

#ifdef __cplusplus
} /* end extern "C" */
#endif

#endif /* CC26x8_UART_H */
/** @} */
