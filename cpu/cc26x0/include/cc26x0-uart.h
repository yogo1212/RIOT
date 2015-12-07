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

#define UART_DR_DATA_mask       0xFF
#define UART_DR_FE              0x10
#define UART_DR_PE              0x20
#define UART_DR_BE              0x40
#define UART_DR_OE              0x80

#define UART_ECR_FE             0x1
#define UART_ECR_PE             0x2
#define UART_ECR_BE             0x4
#define UART_ECR_OE             0x8

#define UART_FR_CTS             0x1
#define UART_FR_BUSY            0x4
#define UART_FR_RXFE            0x10
#define UART_FR_TXFF            0x20
#define UART_FR_RXFF            0x40
#define UART_FR_TXFE            0x80

#define UART_LCHR_PEN           0x1
#define UART_LCHR_EPS           0x2
#define UART_LCHR_RXFE          0x4
#define UART_LCHR_STP2          0x8
#define UART_LCHR_FEN           0x10
#define UART_LCHR_WLEN_mask     0x60
#define UART_LCHR_SPS           0x80

#define UART_CTL_UARTEN         0x1
#define UART_CTL_LBE            0x80
#define UART_CTL_TXE            0x100
#define UART_CTL_RXE            0x200
#define UART_CTL_RTS            0x800
#define UART_CTL_RTSEN          0x4000
#define UART_CTL_CTSEN          0x8000

#define UART ((UART_REGS_t *) (UART_BASE))

#ifdef __cplusplus
} /* end extern "C" */
#endif

#endif /* CC26x8_UART_H */
/** @} */
