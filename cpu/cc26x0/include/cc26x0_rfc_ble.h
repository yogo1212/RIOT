/**
 * @ingroup         cpu_cc26x0_rfc_definitions
 * @{
 *
 * @file
 * @brief           CC26x0 RFC BLE definitions
 *
 * @author          Leon George <leon@georgemail.eu>, Florent-Valéry Coen <florent.coen@gmail.com>
 */

 #ifndef CC26x0_RFC_BLE_H
 #define CC26x0_RFC_BLE_H

 #include <cc26x0.h>

 #ifdef __cplusplus
 extern "C" {
 #endif


 typedef struct {
     radio_op_command_t op;
     uint8_t channel;
     uint8_t whitening;
     uint32_t pParams;
     uint32_t pOutput;
 } ble_rop_cmd_t;

 typedef struct {
     uint16_t commandNo;
     uint8_t payloadType;
     uint8_t newLen;
     uintptr_t pNewData;
     uintptr_t pParams;// TODO type this properly once type is known (damn datashiet)
 } ble_update_adv_payload_t;


 /* ble radio operation command*/
 #define ROP_CMD_CMDID_BLE_SLAVE      0x1801
 #define ROP_CMD_CMDID_BLE_MASTER     0x1802
 #define ROP_CMD_CMDID_BLE_ADV        0x1803
 #define ROP_CMD_CMDID_BLE_ADV_DIR    0x1804
 #define ROP_CMD_CMDID_BLE_ADV_NC     0x1805
 #define ROP_CMD_CMDID_BLE_ADV_SCAN   0x1806
 #define ROP_CMD_CMDID_BLE_SCANNER    0x1807
 #define ROP_CMD_CMDID_BLE_INITIATOR  0x1808
 #define ROP_CMD_CMDID_BLE_GENERIC_RX 0x1809
 #define ROP_CMD_CMDID_BLE_TX_TEST    0x180A


 /* ble immediate command*/
 #define IMM_CMD_CMDID_BLE_ADV_PAYLOAD    0x180A0000


 #define R_OP_STATUS_BLE_DONE_OK         0x1400
 #define R_OP_STATUS_BLE_DONE_RXTIMEOUT  0x1401
 #define R_OP_STATUS_BLE_DONE_NOSYNC     0x1402
 #define R_OP_STATUS_BLE_DONE_RXERR      0x1403
 #define R_OP_STATUS_BLE_DONE_CONNECT    0x1404
 #define R_OP_STATUS_BLE_DONE_MAXNACK    0x1405
 #define R_OP_STATUS_BLE_DONE_ENDED      0x1406
 #define R_OP_STATUS_BLE_DONE_ABORT      0x1407
 #define R_OP_STATUS_BLE_DONE_STOPPED    0x1408

 #define R_OP_STATUS_BLE_ERROR_PAR           0x1800
 #define R_OP_STATUS_BLE_ERROR_RXBUF         0x1801
 #define R_OP_STATUS_BLE_ERROR_NO_SETUP      0x1802
 #define R_OP_STATUS_BLE_ERROR_NO_FS         0x1803
 #define R_OP_STATUS_BLE_ERROR_SYNTH_PROG    0x1804
 #define R_OP_STATUS_BLE_ERROR_RXOVF         0x1805
 #define R_OP_STATUS_BLE_ERROR_TXUNF         0x1806


#ifdef __cplusplus
}
#endif

#endif /* CC26x0_RFC_DATA_H */

/*@}*/
