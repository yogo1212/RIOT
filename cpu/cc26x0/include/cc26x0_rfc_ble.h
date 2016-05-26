/*
 * Copyright (C) 2016 Leon George, Florent-Valéry Coen
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 *
 * Part of the code is also issued from TI source code
 * Description:    CC26xx/CC13xx API for Bluetooth Low Energy commands
 *
 * Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
 * @ingroup         cpu_cc26x0_rfc_definitions
 * @{
 *
 * @file
 * @brief           CC26x0 RFC BLE definitions
 *
 * @author          Leon George <leon@georgemail.eu>
 * @author          Florent-Valéry Coen <florent.coen@gmail.com>
 */

#ifndef CC26x0_RFC_BLE_H
#define CC26x0_RFC_BLE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup cc2x0_rop_command_ids
 * @{
 */
/* BLE radio operation commands IDs*/
#define CMDR_CMDID_BLE_SLAVE      0x1801
#define CMDR_CMDID_BLE_MASTER     0x1802
#define CMDR_CMDID_BLE_ADV        0x1803
#define CMDR_CMDID_BLE_ADV_DIR    0x1804
#define CMDR_CMDID_BLE_ADV_NC     0x1805
#define CMDR_CMDID_BLE_ADV_SCAN   0x1806
#define CMDR_CMDID_BLE_SCANNER    0x1807
#define CMDR_CMDID_BLE_INITIATOR  0x1808
#define CMDR_CMDID_BLE_GENERIC_RX 0x1809
#define CMDR_CMDID_BLE_TX_TEST    0x180A
/* BLE immediate commands */
#define CMDR_CMDID_BLE_ADV_PAYLOAD    0x1001
/**@}*/

/**
 * @addtogroup cc26x0_rop_status_codes
 * @{
 */
/* operation finished normally */
#define R_OP_STATUS_BLE_DONE_OK         0x1400
#define R_OP_STATUS_BLE_DONE_RXTIMEOUT  0x1401
#define R_OP_STATUS_BLE_DONE_NOSYNC     0x1402
#define R_OP_STATUS_BLE_DONE_RXERR      0x1403
#define R_OP_STATUS_BLE_DONE_CONNECT    0x1404
#define R_OP_STATUS_BLE_DONE_MAXNACK    0x1405
#define R_OP_STATUS_BLE_DONE_ENDED      0x1406
#define R_OP_STATUS_BLE_DONE_ABORT      0x1407
#define R_OP_STATUS_BLE_DONE_STOPPED    0x1408
/* operation finished with error */
#define R_OP_STATUS_BLE_ERROR_PAR           0x1800
#define R_OP_STATUS_BLE_ERROR_RXBUF         0x1801
#define R_OP_STATUS_BLE_ERROR_NO_SETUP      0x1802
#define R_OP_STATUS_BLE_ERROR_NO_FS         0x1803
#define R_OP_STATUS_BLE_ERROR_SYNTH_PROG    0x1804
#define R_OP_STATUS_BLE_ERROR_RXOVF         0x1805
#define R_OP_STATUS_BLE_ERROR_TXUNF         0x1806
/**@}*/


/**
 * @addtogroup cc2x0_ble_command_structures
 * @{
 */
/* BLE radio operation commands structures*/
typedef struct __attribute__ ((aligned(4))) {
    radio_op_command_t ropCmd;
    uint8_t channel;
    uint8_t whitening;
    void *pParams;
    void *pOutput;
} ble_rop_cmd_t;

typedef struct __attribute__ ((aligned(4))) {
    uint16_t commandNo;
    uint8_t payloadType;
    uint8_t newLen;
    void *pNewData;
    void *pParams;// TODO type this properly once type is known (damn datashiet)
} ble_update_adv_payload_t;


/**
 * @addtogroup cc2x0_ble_parameter_structures
 * @{
 */
/* BLE parameters structures i.e. what pParams should point toward*/
typedef struct __attribute__ ((aligned (4))) {
    data_queue_t *pRxQ;                    /**<  Pointer to receive queue */
    data_queue_t *pTxQ;                    /**<  Pointer to transmit queue */
    struct {
        uint8_t bAutoFlushIgnored:1;      /**< If 1, automatically remove ignored packets from Rx queue */
        uint8_t bAutoFlushCrcErr:1;       /**< If 1, automatically remove packets with CRC error from Rx queue */
        uint8_t bAutoFlushEmpty:1;        /**< If 1, automatically remove empty packets from Rx queue */
        uint8_t bIncludeLenByte:1;        /**< If 1, include the received length byte in the stored packet; otherwise discard it */
        uint8_t bIncludeCrc:1;            /**< If 1, include the received CRC field in the stored packet; otherwise discard it */
        uint8_t bAppendRssi:1;            /**< If 1, append an RSSI byte to the packet in the Rx queue */
        uint8_t bAppendStatus:1;          /**< If 1, append a status byte to the packet in the Rx queue */
        uint8_t bAppendTimestamp:1;       /**< If 1, append a timestamp to the packet in the Rx queue */
    } rxConfig;                           /**< Configuration bits for the receive queue entries */
    struct {
        uint8_t lastRxSn:1;               /**< The SN bit of the header of the last packet received with CRC OK */
        uint8_t lastTxSn:1;               /**< The SN bit of the header of the last transmitted packet */
        uint8_t nextTxSn:1;               /**< The SN bit of the header of the next packet to transmit */
        uint8_t bFirstPkt:1;              /**< For slave: 0 if a packet has been transmitted on the connection, 1 otherwise */
        uint8_t bAutoEmpty:1;             /**< 1 if the last transmitted packet was an auto-empty packet */
        uint8_t bLlCtrlTx:1;              /**< 1 if the last transmitted packet was an LL control packet (LLID = 11) */
        uint8_t bLlCtrlAckRx:1;           /**< 1 if the last received packet was the ACK of an LL control packet */
        uint8_t bLlCtrlAckPending:1;      /**< 1 if the last successfully received packet was an LL control packet which has not yet been ACK'ed */
    } seqStat;
    uint8_t maxNack;                      /**< Maximum number of NACKs received before operation ends. 0: No limit */
    uint8_t maxPkt;                       /**< Maximum number of packets transmitted in the operation before it ends. 0: No limit */
    uint32_t accessAddress;               /**< Access address used on the connection */
    uint8_t crcInit0;                     /**< CRC initialization value used on the connection &ndash; least significant byte */
    uint8_t crcInit1;                     /**< CRC initialization value used on the connection &ndash; middle byte */
    uint8_t crcInit2;                     /**< CRC initialization value used on the connection &ndash; most significant byte */
    struct {
        uint8_t triggerType:4;            /**< The type of trigger */
        uint8_t bEnaCmd:1;                /**< 0: No alternative trigger command 1: CMD_TRIGGER can be used as an alternative trigger */
        uint8_t triggerNo:2;              /**< The trigger number of the CMD_TRIGGER command that triggers this action */
        uint8_t pastTrig:1;               /**< 0: A trigger in the past is never triggered, or for start of commands, give an error 1: A trigger in the past is triggered as soon as possible */
    } timeoutTrigger;                     /**< Trigger that defines timeout of the first receive operation */
    uint32_t timeoutTime;                 /**< Time used together with <code>timeoutTrigger that defines timeout of the first receive operation */
    uint16_t __dummy0;
    uint8_t __dummy1;
    struct {
        uint8_t triggerType:4;            /**< The type of trigger */
        uint8_t bEnaCmd:1;                /**< 0: No alternative trigger command 1: CMD_TRIGGER can be used as an alternative trigger */
        uint8_t triggerNo:2;              /**< The trigger number of the CMD_TRIGGER command that triggers this action */
        uint8_t pastTrig:1;               /**< 0: A trigger in the past is never triggered, or for start of commands, give an error 1: A trigger in the past is triggered as soon as possible */
    } endTrigger;                         /**< Trigger that causes the device to end the connection event as soon as allowed */
    uint32_t endTime;                     /**< Time used together with <code>endTrigger</code> that causes the device to end the connection event as soon as allowed */
} rfc_ble_param_slave_t;

typedef struct __attribute__ ((aligned (4))) {
    data_queue_t *pRxQ;                   /**< Pointer to receive queue */
    data_queue_t *pTxQ;                   /**< Pointer to transmit queue */
    struct {
        uint8_t bAutoFlushIgnored:1;      /**< If 1, automatically remove ignored packets from Rx queue */
        uint8_t bAutoFlushCrcErr:1;       /**< If 1, automatically remove packets with CRC error from Rx queue */
        uint8_t bAutoFlushEmpty:1;        /**< If 1, automatically remove empty packets from Rx queue */
        uint8_t bIncludeLenByte:1;        /**< If 1, include the received length byte in the stored packet; otherwise discard it */
        uint8_t bIncludeCrc:1;            /**< If 1, include the received CRC field in the stored packet; otherwise discard it */
        uint8_t bAppendRssi:1;            /**< If 1, append an RSSI byte to the packet in the Rx queue */
        uint8_t bAppendStatus:1;          /**< If 1, append a status byte to the packet in the Rx queue */
        uint8_t bAppendTimestamp:1;       /**< If 1, append a timestamp to the packet in the Rx queue */
    } rxConfig;                           /**< Configuration bits for the receive queue entries */
    struct {
        uint8_t lastRxSn:1;               /**< The SN bit of the header of the last packet received with CRC OK */
        uint8_t lastTxSn:1;               /**< The SN bit of the header of the last transmitted packet */
        uint8_t nextTxSn:1;               /**< The SN bit of the header of the next packet to transmit */
        uint8_t bFirstPkt:1;              /**< For slave: 0 if a packet has been transmitted on the connection, 1 otherwise */
        uint8_t bAutoEmpty:1;             /**< 1 if the last transmitted packet was an auto-empty packet */
        uint8_t bLlCtrlTx:1;              /**< 1 if the last transmitted packet was an LL control packet (LLID = 11) */
        uint8_t bLlCtrlAckRx:1;           /**< 1 if the last received packet was the ACK of an LL control packet */
        uint8_t bLlCtrlAckPending:1;      /**< 1 if the last successfully received packet was an LL control packet which has not yet been ACK'ed */
    } seqStat;
    uint8_t maxNack;                      /**< Maximum number of NACKs received before operation ends. 0: No limit */
    uint8_t maxPkt;                       /**< Maximum number of packets transmitted in the operation before it ends. 0: No limit */
    uint32_t accessAddress;               /**< Access address used on the connection */
    uint8_t crcInit0;                     /**< CRC initialization value used on the connection &ndash; least significant byte */
    uint8_t crcInit1;                     /**< CRC initialization value used on the connection &ndash; middle byte */
    uint8_t crcInit2;                     /**< CRC initialization value used on the connection &ndash; most significant byte */
    struct {
        uint8_t triggerType:4;            /**< The type of trigger */
        uint8_t bEnaCmd:1;                /**< 0: No alternative trigger command 1: CMD_TRIGGER can be used as an alternative trigger */
        uint8_t triggerNo:2;              /**< The trigger number of the CMD_TRIGGER command that triggers this action */
        uint8_t pastTrig:1;               /**< 0: A trigger in the past is never triggered, or for start of commands, give an error 1: A trigger in the past is triggered as soon as possible */
    } endTrigger;                         /**< Trigger that causes the device to end the connection event as soon as allowed */
    uint32_t endTime;                     /**< Time used together with endTrigger that causes the device to end the connection event as soon as allowed */
} rfc_ble_param_master_t;

typedef struct __attribute__ ((aligned (4))) {
    data_queue_t *pRxQ;                   /**< Pointer to receive queue */
    struct {
        uint8_t bAutoFlushIgnored:1;      /**< If 1, automatically remove ignored packets from Rx queue */
        uint8_t bAutoFlushCrcErr:1;       /**< If 1, automatically remove packets with CRC error from Rx queue */
        uint8_t bAutoFlushEmpty:1;        /**< If 1, automatically remove empty packets from Rx queue */
        uint8_t bIncludeLenByte:1;        /**< If 1, include the received length byte in the stored packet; otherwise discard it */
        uint8_t bIncludeCrc:1;            /**< If 1, include the received CRC field in the stored packet; otherwise discard it */
        uint8_t bAppendRssi:1;            /**< If 1, append an RSSI byte to the packet in the Rx queue */
        uint8_t bAppendStatus:1;          /**< If 1, append a status byte to the packet in the Rx queue */
        uint8_t bAppendTimestamp:1;       /**< If 1, append a timestamp to the packet in the Rx queue */
    } rxConfig;                           /**< Configuration bits for the receive queue entries */
    struct {
        uint8_t advFilterPolicy:2;        /**< The advertiser filter policy, as defined in Volume 2, Part E, Section 7.8.5 of the Bluetooth 4.0 spec */
        uint8_t deviceAddrType:1;         /**< The type of the device address &ndash; public (0) or random (1) */
        uint8_t peerAddrType:1;           /**< Directed advertiser: The type of the peer address &ndash; public (0) or random (1) */
        uint8_t bStrictLenFilter:1;       /**< 1: Discard messages with illegal length */
    } advConfig;
    uint8_t advLen;                       /**< Size of advertiser data */
    uint8_t scanRspLen;                   /**< Size of scan response data */
    uint8_t *pAdvData;                    /**< Pointer to buffer containing ADV*_IND data */
    uint8_t *pScanRspData;                /**< Pointer to buffer containing SCAN_RSP data */
    uint16_t *pDeviceAddress;             /**< Pointer to device address used for this device */
    void *pWhiteList;                     /**< Pointer to white list or peer address (directed advertiser) */
    uint16_t __dummy0;
    uint8_t __dummy1;
    struct {
        uint8_t triggerType:4;            /**< The type of trigger */
        uint8_t bEnaCmd:1;                /**< 0: No alternative trigger command 1: CMD_TRIGGER can be used as an alternative trigger */
        uint8_t triggerNo:2;              /**< The trigger number of the CMD_TRIGGER command that triggers this action */
        uint8_t pastTrig:1;               /**< 0: A trigger in the past is never triggered, or for start of commands, give an error 1: A trigger in the past is triggered as soon as possible */
    } endTrigger;                         /**< Trigger that causes the device to end the advertiser event as soon as allowed */
    uint32_t endTime;                     /**< Time used together with <code>endTrigger</code> that causes the device to end the advertiser event as soon as allowed  */
  } rfc_ble_param_advertiser_t;

typedef struct __attribute__ ((aligned (4))) {
    data_queue_t *pRxQ;                    /**< Pointer to receive queue */
    struct {
        uint8_t bAutoFlushIgnored:1;      /**< If 1, automatically remove ignored packets from Rx queue */
        uint8_t bAutoFlushCrcErr:1;       /**< If 1, automatically remove packets with CRC error from Rx queue */
        uint8_t bAutoFlushEmpty:1;        /**< If 1, automatically remove empty packets from Rx queue */
        uint8_t bIncludeLenByte:1;        /**< If 1, include the received length byte in the stored packet; otherwise discard it */
        uint8_t bIncludeCrc:1;            /**< If 1, include the received CRC field in the stored packet; otherwise discard it */
        uint8_t bAppendRssi:1;            /**< If 1, append an RSSI byte to the packet in the Rx queue */
        uint8_t bAppendStatus:1;          /**< If 1, append a status byte to the packet in the Rx queue */
        uint8_t bAppendTimestamp:1;       /**< If 1, append a timestamp to the packet in the Rx queue */
    } rxConfig;                           /**< Configuration bits for the receive queue entries */
    struct {
        uint8_t scanFilterPolicy:1;       /**< The advertiser filter policy, as defined in Volume 2, Part E, Section 7.8.10 of the Bluetooth 4.0 spec */
        uint8_t bActiveScan:1;            /**< 0: Passive scan 1: Active scan */
        uint8_t deviceAddrType:1;         /**< The type of the device address &ndash; public (0) or random (1) */
        uint8_t :1;
        uint8_t bStrictLenFilter:1;       /**< 1: Discard messages with illegal length */
        uint8_t bAutoWlIgnore:1;          /**< 1: Automatically set ignore bit in white list */
        uint8_t bEndOnRpt:1;              /**< 1: End scanner operation after each reported ADV*_IND and potentially SCAN_RSP */
    } scanConfig;
    uint16_t randomState;                 /**< State for pseudo-random number generation used in backoff procedure */
    uint16_t backoffCount;                /**< Parameter backoffCount used in backoff procedure, cf. Bluetooth 4.0 spec */
    struct {
        uint8_t logUpperLimit:4;          /**< Binary logarithm of parameter upperLimit used in scanner backoff procedure */
        uint8_t bLastSucceeded:1;         /**< 1 if the last SCAN_RSP was successfully received and upperLimit not changed */
        uint8_t bLastFailed:1;            /**< 1 if reception of the last SCAN_RSP failed and upperLimit was not changed */
    } backoffPar;
    uint8_t scanReqLen;                   /**< Size of scan request data */
    uint8_t *pScanReqData;                /**< Pointer to buffer containing SCAN_REQ data */
    uint16_t *pDeviceAddress;             /**< Pointer to device address used for this device */
    void *pWhiteList;                     /**< Pointer to white list */
    uint16_t __dummy0;
    struct {
        uint8_t triggerType:4;            /**< The type of trigger */
        uint8_t bEnaCmd:1;                /**< 0: No alternative trigger command 1: CMD_TRIGGER can be used as an alternative trigger */
        uint8_t triggerNo:2;              /**< The trigger number of the CMD_TRIGGER command that triggers this action */
        uint8_t pastTrig:1;               /**< 0: A trigger in the past is never triggered, or for start of commands, give an error 1: A trigger in the past is triggered as soon as possible */
    } timeoutTrigger;                     /**< Trigger that causes the device to stop receiving as soon as allowed */
    struct {
        uint8_t triggerType:4;            /**< The type of trigger */
        uint8_t bEnaCmd:1;                /**< 0: No alternative trigger command 1: CMD_TRIGGER can be used as an alternative trigger */
        uint8_t triggerNo:2;              /**< The trigger number of the CMD_TRIGGER command that triggers this action */
        uint8_t pastTrig:1;               /**< A trigger in the past is never triggered, or for start of commands, give an error 1: A trigger in the past is triggered as soon as possible */
    } endTrigger;                         /**< Trigger that causes the device to stop receiving as soon as allowed */
    uint32_t timeoutTime;                 /**< Time used together with timeoutTrigger that causes the device to stop receiving as soon as allowed, ending with BLE_DONE_RXTIMEOUT */
    uint32_t endTime;                     /**< Time used together with endTrigger that causes the device to stop receiving as soon as allowed, ending with BLE_DONE_ENDED */
} rfc_ble_param_scanner_t;

typedef struct __attribute__ ((aligned (4))) {
    data_queue_t* pRxQ;                    /**< Pointer to receive queue */
    struct {
        uint8_t bAutoFlushIgnored:1;      /**< If 1, automatically remove ignored packets from Rx queue */
        uint8_t bAutoFlushCrcErr:1;       /**< If 1, automatically remove packets with CRC error from Rx queue */
        uint8_t bAutoFlushEmpty:1;        /**< If 1, automatically remove empty packets from Rx queue */
        uint8_t bIncludeLenByte:1;        /**< If 1, include the received length byte in the stored packet; otherwise discard it */
        uint8_t bIncludeCrc:1;            /**< If 1, include the received CRC field in the stored packet; otherwise discard it */
        uint8_t bAppendRssi:1;            /**< If 1, append an RSSI byte to the packet in the Rx queue */
        uint8_t bAppendStatus:1;          /**< If 1, append a status byte to the packet in the Rx queue */
        uint8_t bAppendTimestamp:1;       /**< If 1, append a timestamp to the packet in the Rx queue */
    } rxConfig;                           /**< Configuration bits for the receive queue entries */
    struct {
        uint8_t bUseWhiteList:1;          /**< Initiator filter policy, 0: Use specific peer address 1: Use white list. cf. Volume 2, Part E, Section 7.8.10 of the Bluetooth 4.0 spec. */
        uint8_t bDynamicWinOffset:1;      /**< 1: Use dynamic WinOffset insertion */
        uint8_t deviceAddrType:1;         /**< The type of the device address &ndash; public (0) or random (1) */
        uint8_t peerAddrType:1;           /**< The type of the peer address &ndash; public (0) or random (1) */
        uint8_t bStrictLenFilter:1;       /**< 1: Discard messages with illegal length */
    } initConfig;
    uint8_t __dummy0;
    uint8_t connectReqLen;                /**< Size of connect request data */
    uint8_t *pConnectReqData;             /**< Pointer to buffer containing LLData to go in the CONNECT_REQ */
    uint16_t *pDeviceAddress;             /**< Pointer to device address used for this device */
    void *pWhiteList;                     /**< Pointer to white list or peer address */
    uint32_t connectTime;                 /**< Indication of timer value of the first possible start time of the first connection event. Set to the calculated value if a connection is made and to the next possible connection time if not. */
    uint16_t __dummy1;
    struct {
        uint8_t triggerType:4;            /**< The type of trigger */
        uint8_t bEnaCmd:1;                /**< 0: No alternative trigger command 1: CMD_TRIGGER can be used as an alternative trigger */
        uint8_t triggerNo:2;              /**< The trigger number of the CMD_TRIGGER command that triggers this action */
        uint8_t pastTrig:1;               /**< 0: A trigger in the past is never triggered, or for start of commands, give an error 1: A trigger in the past is triggered as soon as possible */
    } timeoutTrigger;                     /**< Trigger that causes the device to stop receiving as soon as allowed */
    struct {
        uint8_t triggerType:4;            /**< The type of trigger */
        uint8_t bEnaCmd:1;                /**< 0: No alternative trigger command 1: CMD_TRIGGER can be used as an alternative trigger */
        uint8_t triggerNo:2;              /**< The trigger number of the CMD_TRIGGER command that triggers this action */
        uint8_t pastTrig:1;               /**< 0: A trigger in the past is never triggered, or for start of commands, give an error 1: A trigger in the past is triggered as soon as possible */
    } endTrigger;                         /**< Trigger that causes the device to stop receiving as soon as allowed */
    uint32_t timeoutTime;                 /**< Time used together with <code>timeoutTrigger</code> that causes the device to stop receiving as soon as allowed, ending with BLE_DONE_RXTIMEOUT */
    uint32_t endTime;                     /**< Time used together with <code>endTrigger</code> that causes the device to stop receiving as soon as allowed, ending with BLE_DONE_ENDED */
} rfc_ble_param_initiator_t;

typedef struct __attribute__ ((aligned(4))) {
    data_queue_t *pRxQ;                   /**< Pointer to receive queue. May be NULL; if so, received packets are not stored */
    struct {
        uint8_t bAutoFlushIgnored:1;      /**< If 1, automatically remove ignored packets from Rx queue */
        uint8_t bAutoFlushCrcErr:1;       /**< If 1, automatically remove packets with CRC error from Rx queue */
        uint8_t bAutoFlushEmpty:1;        /**< If 1, automatically remove empty packets from Rx queue */
        uint8_t bIncludeLenByte:1;        /**< If 1, include the received length byte in the stored packet; otherwise discard it */
        uint8_t bIncludeCrc:1;            /**< If 1, include the received CRC field in the stored packet; otherwise discard it */
        uint8_t bAppendRssi:1;            /**< If 1, append an RSSI byte to the packet in the Rx queue */
        uint8_t bAppendStatus:1;          /**< If 1, append a status byte to the packet in the Rx queue */
        uint8_t bAppendTimestamp:1;       /**< If 1, append a timestamp to the packet in the Rx queue */
    } rxConfig;                           /**< Configuration bits for the receive queue entries */
    uint8_t bRepeat;                      /**< 0: End operation after receiving a packet 1: Restart receiver after receiving a packet */
    uint16_t __dummy0;
    uint32_t accessAddress;               /**< Access address used on the connection */
    uint8_t crcInit0;                     /**< CRC initialization value used on the connection &ndash; least significant byte */
    uint8_t crcInit1;                     /**< CRC initialization value used on the connection &ndash; middle byte */
    uint8_t crcInit2;                     /**< CRC initialization value used on the connection &ndash; most significant byte */
    struct {
        uint8_t triggerType:4;            /**< The type of trigger */
        uint8_t bEnaCmd:1;                /**< 0: No alternative trigger command 1: CMD_TRIGGER can be used as an alternative trigger */
        uint8_t triggerNo:2;              /**< The trigger number of the CMD_TRIGGER command that triggers this action */
        uint8_t pastTrig:1;               /**< 0: A trigger in the past is never triggered, or for start of commands, give an error 1: A trigger in the past is triggered as soon as possible */
    } endTrigger;                         /**< Trigger that causes the device to end the Rx operation */
    uint32_t endTime;                     /**< Time used together with endTrigger that causes the device to end the Rx operation */
} rfc_ble_param_genericRx_t;

typedef struct __attribute__ ((aligned(4))) {
    uint16_t numPackets;                  /**< Number of packets to transmit 0: Transmit unlimited number of packets */
    uint8_t payloadLength;                /**< The number of payload bytes in each packet. */
    uint8_t packetType;                   /**< The packet type to be used, encoded according to the Bluetooth 4.0 spec, Volume 2, Part E, Section 7.8.29 */
    uint32_t period;                       /**< Number of radio timer cycles between the start of each packet */
    struct {
        uint8_t bOverrideDefault:1;       /**< 0: Use default packet encoding 1: Override packet contents */
        uint8_t bUsePrbs9:1;              /**< If bOverride is 1: 1: Use PRBS9 encoding of packet */
        uint8_t bUsePrbs15:1;             /**< If bOverride is 1: 1: Use PRBS15 encoding of packet */
    } config;
    uint8_t byteVal;                      /**< If config.bOverride is 1, value of each byte to be sent */
    uint8_t __dummy0;
    struct {
        uint8_t triggerType:4;            /**< The type of trigger */
        uint8_t bEnaCmd:1;                /**< 0: No alternative trigger command 1: CMD_TRIGGER can be used as an alternative trigger */
        uint8_t triggerNo:2;              /**< The trigger number of the CMD_TRIGGER command that triggers this action */
        uint8_t pastTrig:1;               /**< 0: A trigger in the past is never triggered, or for start of commands, give an error 1: A trigger in the past is triggered as soon as possible */
    } endTrigger;                         /**< Trigger that causes the device to end the Test Tx operation */
    uint32_t endTime;                     /**< Time used together with endTrigger that causes the device to end the Test Tx operation */
} rfc_ble_param_txTest_t;


/**
 * @addtogroup cc2x0_ble_output_structures
 * @{
 */
/* BLE output structures */

typedef struct __attribute__ ((aligned(4))) {
    uint8_t nTx;                         /**< Total number of packets (including auto-empty and retransmissions) that have been transmitted */
    uint8_t nTxAck;                      /**< Total number of transmitted packets (including auto-empty) that have been ACK'ed */
    uint8_t nTxCtrl;                     /**< Number of unique LL control packets from the Tx queue that have been transmitted */
    uint8_t nTxCtrlAck;                  /**< Number of LL control packets from the Tx queue that have been finished (ACK'ed) */
    uint8_t nTxCtrlAckAck;               /**< Number of LL control packets that have been ACK'ed and where an ACK has been sent in response */
    uint8_t nTxRetrans;                  /**< Number of retransmissions that has been done */
    uint8_t nTxEntryDone;                /**< Number of packets from the Tx queue that have been finished (ACK'ed) */
    uint8_t nRxOk;                       /**< Number of packets that have been received with payload, CRC OK and not ignored */
    uint8_t nRxCtrl;                     /**< Number of LL control packets that have been received with CRC OK and not ignored */
    uint8_t nRxCtrlAck;                  /**< Number of LL control packets that have been received with CRC OK and not ignored, and then ACK'ed */
    uint8_t nRxNok;                      /**< Number of packets that have been received with CRC error */
    uint8_t nRxIgnored;                  /**< Number of packets that have been received with CRC OK and ignored due to repeated sequence number */
    uint8_t nRxEmpty;                    /**< Number of packets that have been received with CRC OK and no payload */
    uint8_t nRxBufFull;                  /**< Number of packets that have been received and discarded due to lack of buffer space */
    int8_t lastRssi;                     /**< RSSI of last received packet */
    struct {
        uint8_t bTimeStampValid:1;        /**< 1 if a valid time stamp has been written to timeStamp; 0 otherwise */
        uint8_t bLastCrcErr:1;            /**< 1 if the last received packet had CRC error; 0 otherwise */
        uint8_t bLastIgnored:1;           /**< 1 if the last received packet with CRC OK was ignored; 0 otherwise */
        uint8_t bLastEmpty:1;             /**< 1 if the last received packet with CRC OK was empty; 0 otherwise */
        uint8_t bLastCtrl:1;              /**< 1 if the last received packet with CRC OK was empty; 0 otherwise */
        uint8_t bLastMd:1;                /**< 1 if the last received packet with CRC OK had MD = 1; 0 otherwise */
        uint8_t bLastAck:1;               /**< 1 if the last received packet with CRC OK was an ACK of a transmitted packet; 0 otherwise */
    } pktStatus;
    uint32_t timeStamp;                   /**< Slave operation: Time stamp of first received packet */
} rfc_ble_output_masterSlave_t;

typedef struct __attribute__ ((aligned(4))) {
    uint16_t nTxAdvInd;                  /**< Number of ADV*_IND packets completely transmitted */
    uint8_t nTxScanRsp;                  /**< Number of  SCAN_RSP packets transmitted */
    uint8_t nRxScanReq;                  /**< Number of SCAN_REQ packets received OK and not ignored */
    uint8_t nRxConnectReq;               /**< Number of CONNECT_REQ packets received OK and not ignored */
    uint8_t __dummy0;
    uint16_t nRxNok;                     /**< Number of packets received with CRC error */
    uint16_t nRxIgnored;                 /**< Number of packets received with CRC OK, but ignored */
    uint8_t nRxBufFull;                  /**< Number of packets received that did not fit in Rx queue */
    int8_t lastRssi;                     /**< The RSSI of the last received packet */
    uint32_t timeStamp;                  /**< Time stamp of the last received packet */
} rfc_ble_output_advertiser_t;

typedef struct __attribute__ ((aligned(4))) {
    uint16_t nTxScanReq;                 /**< Number of transmitted SCAN_REQ packets */
    uint16_t nBackedOffScanReq;          /**< Number of SCAN_REQ packets not sent due to backoff procedure */
    uint16_t nRxAdvOk;                   /**< Number of ADV*_IND packets received with CRC OK and not ignored */
    uint16_t nRxAdvIgnored;              /**< Number of ADV*_IND packets received with CRC OK, but ignored */
    uint16_t nRxAdvNok;                  /**< Number of ADV*_IND packets received with CRC error */
    uint16_t nRxScanRspOk;               /**< Number of SCAN_RSP packets received with CRC OK and not ignored */
    uint16_t nRxScanRspIgnored;          /**< Number of SCAN_RSP packets received with CRC OK, but ignored */
    uint16_t nRxScanRspNok;              /**< Number of SCAN_RSP packets received with CRC error */
    uint8_t nRxAdvBufFull;               /**< Number of ADV*_IND packets received that did not fit in Rx queue */
    uint8_t nRxScanRspBufFull;           /**< Number of SCAN_RSP packets received that did not fit in Rx queue */
    int8_t lastRssi;                     /**< The RSSI of the last received packet */
    uint8_t __dummy0;
    uint32_t timeStamp;                  /**< Time stamp of the last successfully received ADV*_IND packet that was not ignored */
} rfc_ble_output_scanner_t;

typedef struct __attribute__ ((aligned(4))) {
    uint8_t nTxConnectReq;               /**< Number of transmitted CONNECT_REQ packets */
    uint8_t nRxAdvOk;                    /**< Number of ADV*_IND packets received with CRC OK and not ignored */
    uint16_t nRxAdvIgnored;              /**< Number of ADV*_IND packets received with CRC OK, but ignored */
    uint16_t nRxAdvNok;                  /**< Number of ADV*_IND packets received with CRC error */
    uint8_t nRxAdvBufFull;               /**< Number of ADV*_IND packets received that did not fit in Rx queue */
    int8_t lastRssi;                     /**< The RSSI of the last received packet */
    uint32_t timeStamp;                  /**< Time stamp of the received ADV*_IND packet that caused transmission of CONNECT_REQ */
} rfc_ble_output_initiator_t;

typedef struct __attribute__ ((aligned(4))) {
    uint16_t nRxOk;                      /**< Number of packets received with CRC OK */
    uint16_t nRxNok;                     /**< Number of packets received with CRC error */
    uint16_t nRxBufFull;                 /**< Number of packets that have been received and discarded due to lack of buffer space */
    int8_t lastRssi;                     /**< The RSSI of the last received packet */
    uint8_t __dummy0;
    uint32_t timeStamp;                  /**< Time stamp of the last received packet */
} rfc_ble_output_genericRx_t;

typedef struct __attribute__ ((aligned(4))) {
    uint16_t nTx;                        /**< Number of packets transmitted */
} rfc_ble_output_txTest_t;


/**
 * @addtogroup cc2x0_ble_other_structures
 * @{
 */
/* BLE other structures and bit fields*/

typedef struct __attribute__ ((aligned(4))) {
    uint8_t size;                        /**< Number of while list entries. Used in the first entry of the list only */
    struct {
        uint8_t bEnable:1;               /**< 1 if the entry is in use, 0 if the entry is not in use */
        uint8_t addrType:1;              /**< The type address in the entry &ndash; public (0) or random (1) */
        uint8_t bWlIgn:1;                /**< 1 if the entry is to be ignored by a scanner, 0 otherwise. Used to mask out entries that have already been scanned and reported. */
    } conf;
    uint16_t address;                    /**< Least significant 16 bits of the address contained in the entry */
    uint32_t addressHi;                  /**< Most significant 32 bits of the address contained in the entry */
} rfc_ble_other_whiteListStruct_t;

typedef struct __attribute__ ((aligned(4))) {
    struct {
        uint8_t channel:6;                /**< The channel on which the packet was received, provided channel is in the range 0-39; otherwise 0x3F */
        uint8_t bIgnore:1;                /**< 1 if the packet is marked as ignored, 0 otherwise */
        uint8_t bCrcErr:1;                /**< 1 if the packet was received with CRC error, 0 otherwise */
    } status;
} rfc_ble_other_receiveStatusByte_t;

#ifdef __cplusplus
}
#endif

#endif /* CC26x0_RFC_BLE_H */

/*@}*/
