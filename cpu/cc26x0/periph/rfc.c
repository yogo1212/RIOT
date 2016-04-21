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
 * @brief       RFC driver implementation for the CC26x0
 *
 * @author
 *
 * @}
 */

#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "cc26x0_prcm.h"
#include "cc26x0_rfc.h"
#include "cpu_conf.h"

#include "periph_rfc.h"
#include "rfc.h"

#define BLE_ADV_STR "this is not a riot\n"

void isr_rfc_cmd_ack(void)
{
  /*checking CMDSTA too quickly in this interrupt leads to unknown CMDSTA values*/
  while(RFC_DBELL->CMDSTA < 1);
  printf("Command acknowledged. CMDSTA: 0x%" PRIu32 " \n", RFC_DBELL->CMDSTA); /*warning for rop command CMDSTA=0x1 only indicates that the command was successfully submitted*/

  /* clear ack interrupt flag */
  /*no need to clear RFCPEIFG.IRQ27 ? */
  RFC_DBELL->RFACKIFG = 0;
}

void isr_rfc_hw(void)
{
    uint32_t asdf = RFC_DBELL->RFHWIFG;
    printf("hw %lx\n", asdf);
    RFC_DBELL->RFHWIFG = ~asdf;
}

void isr_rfc_cpe0(void)
{
    uint32_t asdf = RFC_DBELL->RFCPEIFG;
    printf("cpe0 0x%" PRIu32 "\n", RFC_DBELL->RFCPEIFG);
    RFC_DBELL->RFCPEIFG = ~asdf;
}

void isr_rfc_cpe1(void)
{
    uint32_t asdf = RFC_DBELL->RFCPEIFG;
    printf("cpe1 %lx\n", asdf);
    RFC_DBELL->RFCPEIFG = ~asdf;
}

void rfc_irq_enable(void)
{
    NVIC_EnableIRQ(RF_CMD_ACK_IRQN);
    NVIC_EnableIRQ(RF_CPE0_IRQN);
    NVIC_EnableIRQ(RF_CPE1_IRQN);
    NVIC_EnableIRQ(RF_HW_IRQN);
}

void rfc_irq_disable(void)
{
    NVIC_DisableIRQ(RF_CMD_ACK_IRQN);
}

void rfc_setup_ble(void)
{
    uint8_t buf[sizeof(radio_setup_t) + 3];
    radio_setup_t *rs = (radio_setup_t *)((uintptr_t)(buf + 3) & (0xFFFFFFFC));
    memset(rs, 0, sizeof(rs));

    run_command_ptr(&rs->op);
}

/*void rfc_beacon(void)
{
    uint8_t buf[sizeof(ble_rop_cmd_t) + 3];
    ble_rop_cmd_t *rop = (ble_rop_cmd_t *)((uintptr_t)(buf + 3) & (0xFFFFFFFC));

    //rop->op.commandNo = RFC_DBELL_CMDR_CMDID_BLE_ADV_SCAN;
    rop->op.commandNo = RFC_DBELL_CMDR_CMDID_PING;
    rop->op.status = 0;
    rop->op.pNextOp = 0;
    rop->op.startTrigger = 0;
    rop->op.condition = 0;

    printf("cmdno %x\n", rop->op.commandNo);
    for (int i = 0; i < sizeof(*rop); i++)
        printf("%.2x", ((uint8_t *) rop)[i]);
    printf("\n");

    //run_command_ptr(&rop->op);
}*/

void rfc_prepare(void)
{
    printf("===> %s <===\n",__FUNCTION__);
    /* RFC POWER DOMAIN CLOCK GATE */
    PRCM->RFCCLKG = 1;

    PRCM->CLKLOADCTL = CLKLOADCTL_LOAD;
    while (!(PRCM->CLKLOADCTL & CLKLOADCTL_LOADDONE)) ;

    /* RFC POWER DOMAIN */
    PRCM->PDCTL0 |= PDCTL0_RFC_ON;
    PRCM->PDCTL1 |= PDCTL1_RFC_ON;
    while (!(PRCM->PDSTAT0 & PDSTAT0_RFC_ON)) ;
    while (!(PRCM->PDSTAT1 & PDSTAT1_RFC_ON)) ;

    /* RFC CLOCK */
    //RFC_PWR->PWMCLKEN |= RFC_PWR_PWMCLKEN_CPE;
    //RFC_PWR->PWMCLKEN |= RFC_PWR_PWMCLKEN_CPERAM;
    RFC_PWR->PWMCLKEN |= 0x7FF;
    printf("RFC_PWR->PWMCLKEN %lx\n", RFC_PWR->PWMCLKEN);

    /* RFC IRQ */
    rfc_irq_enable();

    rfc_setup_ble();

        //rfc_beacon();
        //rfc_beacon();

}
