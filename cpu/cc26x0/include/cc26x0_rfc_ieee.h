/**
 * @ingroup         cpu_cc26x0_rfc_definitions
 * @{
 *
 * @file
 * @brief           CC26x0 RFC ble definitions
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


 /* ieee 802.15.04 radio operation command*/
 /* ieee 802.15.04 background */
 #define ROP_CMD_CMDID_IEEE_RX        0x2801
 #define ROP_CMD_CMDID_IEEE_ED_SCAN   0x2802
 /* ieee 802.15.04 foreground */
 #define ROP_CMD_CMDID_IEEE_TX        0x2C01
 #define ROP_CMD_CMDID_IEEE_CSMA      0x2C02
 #define ROP_CMD_CMDID_IEEE_RX_ACK    0x2C03
 #define ROP_CMD_CMDID_IEEE_ABORT_BG  0x2C04


 /* ieee 802.15.04 immediate */
 #define IMM_CMD_CMDID_IEEE_MOD_CCA       0x2001
 #define IMM_CMD_CMDID_IEEE_MOD_FILT      0x2002
 #define IMM_CMD_CMDID_IEEE_MOD_SRC_MATCH 0x2003
 #define IMM_CMD_CMDID_IEEE_ABORT_FG      0x2401
 #define IMM_CMD_CMDID_IEEE_STOP_FG       0x2402
 #define IMM_CMD_CMDID_IEEE_CCA_REQ       0x24030


#ifdef __cplusplus
}
#endif

#endif /* CC26x0_RFC_DATA_H */

/*@}*/
