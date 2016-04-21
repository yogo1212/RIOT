/**
 * @ingroup         cpu_cc26x0_rfc_definitions
 * @{
 *
 * @file
 * @brief           CC26x0 RFC common command definitions
 *
 * @author          Leon George <leon@georgemail.eu>, Florent-Valéry Coen <florent.coen@gmail.com>
 */

#ifndef CC26x0_RFC_CMD_H
#define CC26x0_RFC_CMD_H

#include <cc26x0.h>

#ifdef __cplusplus
extern "C" {
#endif


/* direct command */
typedef struct {
    uint16_t commandID;
    uint8_t optParam;
    unsigned int optParamExt: 6;
    unsigned int commandType: 2; /*must be 01 for direct command*/
} direct_command_t;

#define DIR_CMD_CMDID_ABORT     0x0401
#define DIR_CMD_CMDID_STOP      0X0402
#define DIR_CMD_CMDID_GET_RSSI  0X0403  /*immediate command that can be used as direct*/
#define DIR_CMD_CMDID_START_RAT 0x0405
#define DIR_CMD_CMDID_PING      0X0406


/* immediate command */
#define IMM_CMD_CMDID_GET_RSSI            0x0403
#define IMM_CMD_CMDID_UPDATE_RADIO_SETUP  0x0001
#define IMM_CMD_CMDID_TRIGGER             0x0404
#define IMM_CMD_CMDID_GET_FW_INFO         0x0002
#define IMM_CMD_CMDID_READ_RFREG          0x0601
#define IMM_CMD_CMDID_SET_RAT_CMP         0x000A
#define IMM_CMD_CMDID_SET_rAT_CPT         0x0603
#define IMM_CMD_CMDID_DISABLE_RAT_CH      0x0408
#define IMM_CMD_CMDID_SET_RAT_OUTPUT      0x0604
#define IMM_CMD_CMDID_ARM_RAT_CH          0x0409
#define IMM_CMD_CMDID_DISARM_RAT_CH       0x040A
#define IMM_CMD_CMDID_SET_TX_POWER        0x0010
#define IMM_CMD_CMDID_UPDATE_FS           0x0011
#define IMM_CMD_CMDID_BUS_REQUEST         0x040E


/* radio operation command */
/*
 * R: system CPU can read a result back; the radio CPU does not read the field
 * W: system CPU writes a value, the radio CPU reads it and does not modify it
 * R/W: system CPU writes an initial value, the radio CPU may modify it
 */

typedef struct radio_op_command_s radio_op_command_t;
struct __attribute__ ((aligned(4))) radio_op_command_s {
    uint16_t commandNo; /* W */
    uint16_t status; /* R/W */
    radio_op_command_t* pNextOp; /* W */
    uint32_t startTime; /* W */
    struct {
      uint8_t triggerType:4;
      uint8_t bEnaCmd:1;
      uint8_t triggerNo:2;
      uint8_t pastTrig:1;
    } startTrigger;       /* missing from datashiet... */
    struct {
      uint8_t rule:4;
      uint8_t nSkip:4;
    } condition; /* W */
}; /* rop require 32-bit word alignement, i.e. the 2 LSB of cmd addr are 0 */

#define ROP_CMD_CMDID_NOP            0x0801
#define ROP_CMD_CMDID_SETUP          0x0802
#define ROP_CMD_CMDID_FS_POWERUP     0x080C
#define ROP_CMD_CMDID_FS_POWERDOWN   0x080D
#define ROP_CMD_CMDID_FS             0x0803
#define ROP_CMD_CMDID_FS_OFF         0x0804
#define ROP_CMD_CMDID_FS_RX_TEST     0x0807
#define ROP_CMD_CMDID_FS_TX_TEST     0x0808
#define ROP_CMD_CMDID_SYNC_STOP_RAT  0x0809
#define ROP_CMD_CMDID_SYNC_START_RAT 0x080A
#define ROP_CMD_CMDID_COUNT          0x080B
#define ROP_CMD_CMDID_SCH_IMM        0x0810
#define ROP_CMD_CMDID_COUNT_BRANCH   0x0812
#define ROP_CMD_CMDID_PATTERN_CHECK  0x0813

#define ROP_CMD_STATUS_IDLE        0x0000
#define ROP_CMD_STATUS_PENDING     0x0001
#define ROP_CMD_STATUS_ACTIVE      0x0002
#define ROP_CMD_STATUS_SKIPPED     0x0003

#define ROP_CMD_STATUS_DONE_OK         0x0400
#define ROP_CMD_STATUS_DONE_CNTDWN     0x0401
#define ROP_CMD_STATUS_DONE_RXERR      0x0402
#define ROP_CMD_STATUS_DONE_TIMEOUT    0x0403
#define ROP_CMD_STATUS_DONE_STOPPED    0x0404
#define ROP_CMD_STATUS_DONE_ABORT      0x0405

#define ROP_CMD_STATUS_ERROR_PAST_START 0x0800
#define ROP_CMD_STATUS_ERROR_START_TRIG 0x0801
#define ROP_CMD_STATUS_ERROR_CONDITION  0x0802
#define ROP_CMD_STATUS_ERROR_PAR        0x0803
#define ROP_CMD_STATUS_ERROR_POINTER    0x0804
#define ROP_CMD_STATUS_ERROR_CMDID      0x0805
#define ROP_CMD_STATUS_ERROR_NO_SETUP   0x0807
#define ROP_CMD_STATUS_ERROR_NO_FS      0x0808
#define ROP_CMD_STATUS_ERROR_SYNTH_PROG 0x0809
#define ROP_CMD_STATUS_ERROR_TXUNF      0x080a
#define ROP_CMD_STATUS_ERROR_RXOVF      0x080b
#define ROP_CMD_STATUS_ERROR_NO_RX      0x080c

#define ROP_CMD_STARTTRIG_TYPE_mask            0xF
#define ROP_CMD_STARTTRIG_TYPE_TRIG_NOW        0x0
#define ROP_CMD_STARTTRIG_TYPE_TRIG_NEVER      0x1
#define ROP_CMD_STARTTRIG_TYPE_TRIG_ABSTIME    0x2
#define ROP_CMD_STARTTRIG_TYPE_REL_SUBMIT      0x3
#define ROP_CMD_STARTTRIG_TYPE_REL_START       0x4
#define ROP_CMD_STARTTRIG_TYPE_REL_PREVSTART   0x5
#define ROP_CMD_STARTTRIG_TYPE_REL_FIRSTSTART  0x6
#define ROP_CMD_STARTTRIG_TYPE_REL_PREVEND     0x7
#define ROP_CMD_STARTTRIG_TYPE_REL_EVT1        0x8
#define ROP_CMD_STARTTRIG_TYPE_REL_EVT2        0x9
#define ROP_CMD_STARTTRIG_TYPE_EXTERNAL        0xA
#define ROP_CMD_STARTTRIG_ALT_TRIG             0x10
#define ROP_CMD_STARTTRIG_TRIG_NO_mask         0x60
#define ROP_CMD_STARTTRIG_TRIG_NO_pos          5
#define ROP_CMD_STARTTRIG_PAST_TRIG            0x80

/* for ROP_CMD_STARTTRIG_TYPE_EXTERNAL startTime describes the trigger this way: */
#define ROP_CMD_STARTTIME_INPUT_RISING         0x0
#define ROP_CMD_STARTTIME_INPUT_FALLING        0x4
#define ROP_CMD_STARTTIME_INPUT_BOTH           0x8
#define ROP_CMD_STARTTIME_SOURCE_GPI0          0xF00 /* TODO wtf does this mean? */
#define ROP_CMD_STARTTIME_SOURCE_GPI1          0xF00 /* 22: RFC_GPI0, 23: RFC_GPI1 */

#define ROP_CMD_CONDITION_RULE_mask            0x0F
#define ROP_CMD_CONDITION_RULE_ALWAYS          0x00
#define ROP_CMD_CONDITION_RULE_NEVER           0x01
#define ROP_CMD_CONDITION_RULE_STOP_ON_FALSE   0x02
#define ROP_CMD_CONDITION_RULE_STOP_ON_TRUE    0x03
#define ROP_CMD_CONDITION_RULE_SKIP_ON_FALSE   0x04
#define ROP_CMD_CONDITION_RULE_SKIP_ON_TRUE    0x05
#define ROP_CMD_CONDITION_NSKIP_pos            4
#define ROP_CMD_CONDITION_NSKIP_mask           0xF0

typedef struct {
    radio_op_command_t op;
    uint8_t mode; /* W */
    /*
     * supported values: 0 (equivalent to 2), 2, 5, 6, 10, 12, 15, and 30
     * 0 or 2 only supported for devices that support 2.4-GHz operation
     */
    uint8_t IoDivider; /* W */
    struct {
      uint16_t biasMode:1;
      uint16_t :6;
      uint16_t bNoFsPowerUp:1;
    } config; /* W */
    struct {
      uint16_t IB:6;
      uint16_t GC:2;
      uint16_t boost:1;
      uint16_t tempCoeff:7;
   } txPower; /* W */
    uint32_t* pRegOverride; /* W */
} radio_setup_cmd_t;

#define RADIO_SETUP_MODE_BLE                0x0
#define RADIO_SETUP_MODE_IEEE8021504        0x1
#define RADIO_SETUP_MODE_2MBPS_GFSK         0x2
#define RADIO_SETUP_MODE_5MBPS_CODED_8FSK   0x5
#define RADIO_SETUP_MODE_KEEP               0xFF // update overrides only

/*
 * http://processors.wiki.ti.com/images/4/45/CC26xx_HW_training_RF_Frontends_and_Antennas.pdf
*/
#define RADIO_SETUP_CONFIG_FEM_DIFF             0x0 /* front-end mode */
#define RADIO_SETUP_CONFIG_FEM_SINGLE_END_RFP   0x1
#define RADIO_SETUP_CONFIG_FEM_SINGLE_END_RFN   0x2
#define RADIO_SETUP_CONFIG_FEM_START_RFP        0x3
#define RADIO_SETUP_CONFIG_FEM_START_RFN        0x4
#define RADIO_SETUP_CONFIG_FEM_SINGLE_END_RFP_E 0x5 /* ext front end control on rf pins */
#define RADIO_SETUP_CONFIG_FEM_SINGLE_END_RFN_E 0x6

#ifdef __cplusplus
}
#endif

#endif /* CC26x0_RFC_CMD_H */

/*@}*/
