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

void board_init(void)
{
    cpu_init();

    led_init();
}

/** @} */
