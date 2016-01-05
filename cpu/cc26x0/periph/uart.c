/**
 * @ingroup     driver_periph
 * @{
 *
 * @file
 * @brief       low-level UART driver implementation
 *
 * @author      Leon M. George <leon@georgemail.eu>
 *
 * @}
 */

#include <stddef.h>

#include "board.h"
#include "cpu.h"
#include "sched.h"
#include "thread.h"
#include "periph/uart.h"
#include "periph_conf.h"

#include "cc26x0-prcm.h"
#include "cc26x0-uart.h"
#include "cc26x0-ioc.h"


#define DIVFRAC_NUM_BITS      6
#define DIVFRAC_MASK          ((1 << DIVFRAC_NUM_BITS) - 1)

/*---------------------------------------------------------------------------*/

/**
 * @brief allocate memory to store callback functions
 */
static uart_isr_ctx_t uart_config[UART_NUMOF];

/*---------------------------------------------------------------------------*/
static void stop(void)
{
    UART->CTL &= ~UART_CTL_UARTEN;

    UART->CTL |= UART_CTL_RXE;
    UART->CTL |= UART_CTL_TXE;

    while(UART->FR & UART_FR_BUSY) ;
    UART->LCRH &= ~UART_LCRH_FEN;
}
static void start(void)
{
    UART->ECR = 0xF;

    UART->LCRH |= UART_LCRH_FEN;

    UART->CTL |= UART_CTL_UARTEN;
}
static void reset(void)
{
    stop();
    start();
}
/*---------------------------------------------------------------------------*/

#if UART_0_EN
void isr_uart(void)
{
    uint_fast16_t mis;

    mis = UART->MIS;

    UART->ICR = 0x7F3;

    while (!(UART->FR & UART_FR_RXFE)) {
        uart_config[0].rx_cb(uart_config[0].arg, UART->DR);
    }

    if (mis & (UART_MIS_OEMIS | UART_MIS_BEMIS | UART_MIS_PEMIS | UART_MIS_FEMIS)) {
        reset();
    }

    if (sched_context_switch_request) {
        thread_yield();
    }
}
#endif /* UART_0_EN */

static int init_base(uart_t uart, uint32_t baudrate);

int uart_init(uart_t uart, uint32_t baudrate, uart_rx_cb_t rx_cb, void *arg)
{
    int res = init_base(uart, baudrate);

    if (res != 0) {
        return res;
    }

    uart_config[0].rx_cb = rx_cb;
    uart_config[0].arg = arg;

#if UART_0_EN
    NVIC_SetPriority(UART0_IRQN, UART_IRQ_PRIO);
    NVIC_EnableIRQ(UART0_IRQN);
#endif

    return 0;
}

static int init_base(uart_t uart, uint32_t baudrate)
{
    if (uart != 0)
        return -1;

#if UART_0_EN
    IOC->CFG[UART_0_TX_DIO] = IOCFG_PORTID_UART0_TX | IOCFG_INPUT_ENABLE;
    IOC->CFG[UART_0_RX_DIO] = IOCFG_PORTID_UART0_RX;

    /*
     * TODO so do we still need to enable input driver?
     * When IOC is configured as UART-specific I/Os,
     * IOC sets static output driver enable to the pad
     * (enable = 1 for TXD and RTS and enable = 0 for RXD and CTS)
     */

    uart_poweron(uart);

    UART->CTL = 0;


    /* TODO */
    uint32_t ref_clock = 48000000;
    /* chose which code to use
     * uint32_t divisor = ref_clock << 2;
     * divisor += baudrate / 2; // potentially avoid rounding error
     * divisor /= baudrate;
     * UART->IBRD = divisor >> DIVFRAC_NUM_BITS;
     * UART->FBRD = divisor & DIVFRAC_MASK;
     */
    const float brd = (float) ref_clock / (16 * baudrate);
    UART->IBRD = brd;
    UART->FBRD = (uint16_t)((brd - (long) brd) * 64 + 0.5) & DIVFRAC_MASK;

    UART->LCRH = UART_LCRH_WLEN_8 | UART_LCRH_FEN;

#ifdef UART_0_RTS_DIO
    IOCFG_n(UART_0_RTS_DIO_num) = IOCFG_PORTID_UART0_RTS;
    UART->CTL |= UART_CTL_RTSEN;
#endif

#ifdef UART_0_CTS_DIO
    IOCFG_n(UART_0_CTS_DIO_num) = IOCFG_PORTID_UART0_CTS | IOCFG_INPUT_ENABLE;
    UART->CTL |= UART_CTL_CTSEN;
#endif

    UART->IMSC = 0;
    UART->IMSC |= UART_IMSC_RXIM; /* receive */
    UART->IMSC |= UART_IMSC_RTIM; /* receive time-out */
    UART->IMSC |= UART_IMSC_OEIM; /* overrun error */
    UART->IMSC |= UART_IMSC_BEIM; /* break error */
    UART->IMSC |= UART_IMSC_FEIM; /* framing error */

    UART->IFLS = UART_IFLS_RXSEL_1_8;
    UART->IFLS = UART_IFLS_TXSEL_4_8;

    UART->CTL = UART_CTL_RXE;
    UART->CTL = UART_CTL_TXE;

    while (!(PRCM->CLKLOADCTL & CLKLOADCTL_LOADDONE))
        ;

    start();
#endif // UART_0_EN
    return 0;
}

void uart_write(uart_t uart, const uint8_t *data, size_t len)
{
    if (uart != 0)
        return;
    for (size_t i = 0; i < len; i++) {
        while (UART->FR == UART_FR_TXFF)
            ;
        UART->DR = data[i];
    }
}

static void uart_power(uint32_t on)
{
    PRCM->UARTCLKGR = on;
    PRCM->UARTCLKGS = on;
    PRCM->UARTCLKGDS = on;

    PRCM->CLKLOADCTL = CLKLOADCTL_LOAD;
}

void uart_poweron(uart_t uart)
{
    if (uart != 0)
        return;
#ifdef UART_0_EN
    uart_power(1);
#endif
}

void uart_poweroff(uart_t uart)
{
    if (uart != 0)
        return;
#ifdef UART_0_EN
    uart_power(0);
#endif
}
