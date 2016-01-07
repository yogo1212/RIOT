/**
 * @ingroup     boards_cc2650stk
 * @{
 *
 * @file
 * @brief       Board specific implementations for the CC2650STK board
 *
 * @author      Leon M. George <leon@georgemail.eu>
 */

#include "board.h"
#include "cpu.h"

#include "periph/uart.h"

#include "cc26x0-ioc.h"
#include "cc26x0-gpio.h"
#include "cc26x0-prcm.h"

static void led_init(void)
{
    gpio_init(LED_RED_DIO, GPIO_DIR_OUT, GPIO_NOPULL);
    gpio_init(LED_GREEN_DIO, GPIO_DIR_OUT, GPIO_NOPULL);
}

static void sleep(uint32_t s)
{
    while (s-- > 0) {
        __asm__ volatile (
            "nop\n\t"
            "nop\n\t"
            "nop\n\t"    );
    }
}

static void rx_cb(void *arg, char data)
{
    GPIO->DOUTSET = (1 << LED_GREEN_DIO);
    GPIO->DOUTTGL = (1 << LED_RED_DIO);
}

/**
 * @brief Initialize the SmartRF06 board
 */
void board_init(void)
{
    /* initialize the CPU */
    cpu_init();

    /* initialize the boards LEDs */
    led_init();

    if (uart_init(0, 115200, rx_cb, NULL)) {
        GPIO->DOUTTGL = (1 << LED_RED_DIO) | (1 << LED_GREEN_DIO);
        sleep(1000000);
        GPIO->DOUTTGL = (1 << LED_RED_DIO) | (1 << LED_GREEN_DIO);
        sleep(1000000);
        GPIO->DOUTTGL = (1 << LED_RED_DIO) | (1 << LED_GREEN_DIO);
        sleep(1000000);
        GPIO->DOUTTGL = (1 << LED_RED_DIO) | (1 << LED_GREEN_DIO);
    }

    while (true) {
        uart_write(0, (unsigned char *) "hallo\r\n", 7);
        sleep(1000000);
    }
}

/** @} */
