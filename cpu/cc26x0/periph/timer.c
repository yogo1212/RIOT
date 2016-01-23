/**
 * @ingroup     driver_periph
 * @{
 *
 * @file
 * @brief       low-level timer driver implementation for the CC2538 CPU
 *
 * @author      Leon M. George <leon@georgemail.eu>
 *
 * @}
 */

#include <stdlib.h>
#include <stdio.h>

#include "board.h"
#include "cpu.h"
#include "sched.h"
#include "thread.h"
#include "periph/timer.h"
#include "periph_conf.h"

#include "cc26x0-prcm.h"

typedef struct {
    void (*cb)(int);
} timer_conf_t;

timer_conf_t config[TIMER_NUMOF];
#define USECS_PER_SEC        (1000 * 1000)

GPT_REG_t *select_gpt(tim_t dev)
{
    GPT_REG_t *gpt = NULL;

    switch (dev) {
#if TIMER_0_EN
        case TIMER_0:
            gpt = TIMER_0_DEV;
            break;
#endif
#if TIMER_1_EN
        case TIMER_1:
            gpt = TIMER_1_DEV;
            break;
#endif
#if TIMER_2_EN
        case TIMER_2:
            gpt = TIMER_2_DEV;
            break;
#endif
#if TIMER_3_EN
        case TIMER_3:
            gpt = TIMER_3_DEV;
            break;
#endif
        default:
            break;
    }

    return gpt;
}

int timer_init(tim_t dev, unsigned int ticks_per_us, void (*callback)(int))
{
    GPT_REG_t *gpt = select_gpt(dev);

    if (!gpt) {
        return -1;
    }

    unsigned int gpt_num = ((uintptr_t) gpt - (uintptr_t) GPT0_BASE) / 0x1000;

    config[dev].cb = callback;

    PRCM->GPTCLKGR |= (1 << gpt_num);
    PRCM->GPTCLKGS |= (1 << gpt_num);
    PRCM->CLKLOADCTL = CLKLOADCTL_LOAD;
    while (!(PRCM->CLKLOADCTL & CLKLOADCTL_LOADDONE)) ;

    gpt->CTL = 0;

    gpt->CFG  = GPT_CFG_16T;
    gpt->TAMR = GPT_TXMR_TXMR_PERIODIC | GPT_TXMR_TXCDIR_UP;
    gpt->TBMR = GPT_TXMR_TXMR_PERIODIC | GPT_TXMR_TXCDIR_UP;

    gpt->TAPR = RCOSC48M_FREQ / (ticks_per_us * USECS_PER_SEC) - 1;
    gpt->TBPR = RCOSC48M_FREQ / (ticks_per_us * USECS_PER_SEC) - 1;

    timer_irq_enable(dev);

    gpt->CTL |= GPT_CTL_TAEN | GPT_CTL_TBEN;

    return 0;
}

int timer_set(tim_t dev, int channel, unsigned int timeout)
{
    return timer_set_absolute(dev, channel, timer_read(dev) + timeout);
}

int timer_set_absolute(tim_t dev, int channel, unsigned int value)
{
    GPT_REG_t *gpt = select_gpt(dev);

    if (!gpt) {
        return -1;
    }

    switch (channel) {
        case 0:
            gpt->TAILR = value;
            gpt->IMR |= GPT_IMR_TATOIM;
            break;

        case 1:
            gpt->TBILR = value;
            gpt->IMR |= GPT_IMR_TBTOIM;
            break;

        default:
            return -1;
    }

    return 1;
}

int timer_clear(tim_t dev, int channel)
{
    GPT_REG_t *gpt = select_gpt(dev);

    if (!gpt) {
        return -1;
    }

    switch (channel) {
        case 0:
            gpt->CTL &= (~GPT_CTL_TAEN);
            break;

        case 1:
            gpt->CTL &= (~GPT_CTL_TBEN);
            break;

        default:
            return -1;
    }

    return 1;
}

unsigned int timer_read(tim_t dev)
{
    GPT_REG_t *gpt = select_gpt(dev);

    if (!gpt) {
        return 0;
    }

    return gpt->TAR;
}

void timer_stop(tim_t dev)
{
    GPT_REG_t *gpt = select_gpt(dev);

    if (!gpt) {
        return;
    }

    gpt->CTL &= (~GPT_CTL_TAEN);
    gpt->CTL &= (~GPT_CTL_TBEN);
}

void timer_start(tim_t dev)
{
    GPT_REG_t *gpt = select_gpt(dev);

    if (!gpt) {
        return;
    }

    gpt->CTL |= (GPT_CTL_TAEN | GPT_CTL_TBEN);
}

void timer_irq_enable(tim_t dev)
{
    switch (dev) {
#if TIMER_0_EN
        case TIMER_0:
            NVIC_SetPriority(TIMER_0_IRQn_1, TIMER_IRQ_PRIO);
            NVIC_SetPriority(TIMER_0_IRQn_2, TIMER_IRQ_PRIO);
            NVIC_EnableIRQ(TIMER_0_IRQn_1);
            NVIC_EnableIRQ(TIMER_0_IRQn_2);
            break;
#endif
#if TIMER_1_EN
        case TIMER_1:
            NVIC_SetPriority(TIMER_1_IRQn_1, TIMER_IRQ_PRIO);
            NVIC_SetPriority(TIMER_1_IRQn_2, TIMER_IRQ_PRIO);
            NVIC_EnableIRQ(TIMER_1_IRQn_1);
            NVIC_EnableIRQ(TIMER_1_IRQn_2);
            break;
#endif
#if TIMER_2_EN
        case TIMER_2:
            NVIC_SetPriority(TIMER_2_IRQn_1, TIMER_IRQ_PRIO);
            NVIC_SetPriority(TIMER_2_IRQn_2, TIMER_IRQ_PRIO);
            NVIC_EnableIRQ(TIMER_2_IRQn_1);
            NVIC_EnableIRQ(TIMER_2_IRQn_2);
            break;
#endif
#if TIMER_3_EN
        case TIMER_3:
            NVIC_SetPriority(TIMER_3_IRQn_1, TIMER_IRQ_PRIO);
            NVIC_SetPriority(TIMER_3_IRQn_2, TIMER_IRQ_PRIO);
            NVIC_EnableIRQ(TIMER_3_IRQn_1);
            NVIC_EnableIRQ(TIMER_3_IRQn_2);
            break;
#endif

        case TIMER_UNDEFINED:
        default:
            return;
    }
}

void timer_irq_disable(tim_t dev)
{
    switch (dev) {
#if TIMER_0_EN
        case TIMER_0:
            NVIC_DisableIRQ(TIMER_0_IRQn_1);
            NVIC_DisableIRQ(TIMER_0_IRQn_2);
            break;
#endif
#if TIMER_1_EN
        case TIMER_1:
            NVIC_DisableIRQ(TIMER_1_IRQn_1);
            NVIC_DisableIRQ(TIMER_1_IRQn_2);
            break;
#endif
#if TIMER_2_EN
        case TIMER_2:
            NVIC_DisableIRQ(TIMER_2_IRQn_1);
            NVIC_DisableIRQ(TIMER_2_IRQn_2);
            break;
#endif
#if TIMER_3_EN
        case TIMER_3:
            NVIC_DisableIRQ(TIMER_3_IRQn_1);
            NVIC_DisableIRQ(TIMER_3_IRQn_2);
            break;
#endif

        case TIMER_UNDEFINED:
        default:
            return;
    }
}

static void _interrupt(tim_t dev, int chan)
{
    LED_RED_ON;

    GPT_REG_t *gpt = select_gpt(dev);

    gpt->ICLR = gpt->RIS | gpt->MIS;

    if (config[0].cb != NULL) config[0].cb(chan);

    if (sched_context_switch_request) {
        thread_yield();
    }
}

#if TIMER_0_EN
void TIMER_0_ISR_1(void)
{
    GPT0->IMR &= ~GPT_IMR_TATOIM;
    _interrupt(TIMER_0, 0);
}

void TIMER_0_ISR_2(void)
{
    GPT0->IMR &= ~GPT_IMR_TBTOIM;
    _interrupt(TIMER_0, 1);
}
#endif /* TIMER_0_EN */

#if TIMER_1_EN
void TIMER_1_ISR_1(void)
{
    GPT1->IMR &= ~GPT_IMR_TATOIM;
    _interrupt(TIMER_1, 0);
}

void TIMER_1_ISR_2(void)
{
    GPT1->IMR &= ~GPT_IMR_TBTOIM;
    _interrupt(TIMER_1, 1);
}
#endif /* TIMER_1_EN */

#if TIMER_2_EN
void TIMER_2_ISR_1(void)
{
    GPT2->IMR &= ~GPT_IMR_TATOIM;
    _interrupt(TIMER_2, 0);
}

void TIMER_2_ISR_2(void)
{
    GPT2->IMR &= ~GPT_IMR_TBTOIM;
    _interrupt(TIMER_2, 1);
}
#endif /* TIMER_2_EN */

#if TIMER_3_EN
void TIMER_3_ISR_1(void)
{
    GPT3->IMR &= ~GPT_IMR_TATOIM;
    _interrupt(TIMER_3, 0);
}

void TIMER_3_ISR_2(void)
{
    GPT3->IMR &= ~GPT_IMR_TBTOIM;
    _interrupt(TIMER_3, 1);
}
#endif /* TIMER_3_EN */
