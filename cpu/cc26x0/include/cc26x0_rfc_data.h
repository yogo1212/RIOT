/**
 * @ingroup         cpu_cc26x0_rfc_definitions
 * @{
 *
 * @file
 * @brief           CC26x0 RFC data structures and commands definitions
 *
 * @author          Leon George <leon@georgemail.eu>, Florent-Valéry Coen <florent.coen@gmail.com>
 */

 #ifndef CC26x0_RFC_DATA_H
 #define CC26x0_RFC_DATA_H

 #include <cc26x0.h>

 #ifdef __cplusplus
 extern "C" {
 #endif

 typedef struct {
     uint32_t pCurrEntry; /* R/W NULL -> empty*/
     uint32_t pLastEntry; /* R/W */
 } data_entry_queue_t;


typedef struct {
    uint32_t pNextEntry; /* R/W */
    uint8_t status; /* R/W */
    uint8_t config; /* W */
    uint16_t length; /* W TODO find out what the difference between this and the value referenced by config.lensz is */
    /* maybe you think of this struct being extended like this:
     * DATA_ENTRY_CONFIG_TYPE_GENERAL:
     * uint8_t data[length];
     * DATA_ENTRY_CONFIG_TYPE_MULTIRX:
     * uint16_t dataCnt; // R
     * uint16_t nextIndex; // R
     * uint16_t data[length]; // R
     * DATA_ENTRY_CONFIG_TYPE_PTR:
     * uint32_t pData;
     */
} data_entry_t;

#define DATA_ENTRY_STATUS_PENDING       0
#define DATA_ENTRY_STATUS_ACTIVE        1
#define DATA_ENTRY_STATUS_BUSY          2
#define DATA_ENTRY_STATUS_FINISHED      3

#define DATA_ENTRY_CONFIG_TYPE_mask     0x3
#define DATA_ENTRY_CONFIG_TYPE_GENERAL  0x0
#define DATA_ENTRY_CONFIG_TYPE_MULTIRX  0x1
#define DATA_ENTRY_CONFIG_TYPE_PTR      0x2
#define DATA_ENTRY_CONFIG_LENSZ_pos     4
#define DATA_ENTRY_CONFIG_LENSZ_mask    0xC
#define DATA_ENTRY_CONFIG_LENSZ_NOLEN   0x0
#define DATA_ENTRY_CONFIG_LENSZ_1BYTE   0x1
#define DATA_ENTRY_CONFIG_LENSZ_2BYTE   0x2

/* immediate command data*/
#define IMM_CMD_CMDID_ADD_DATA_ENTRY 0x0005
#define IMM_CMD_CMDID_REM_DATA_ENTRY 0x0006
#define IMM_CMD_CMDID_FLUSH_QUEUE    0x0007
#define IMM_CMD_CMDID_CLEAR_RX       0x0008
#define IMM_CMD_CMDID_REM_PENDING_ENTRIES  0x0009 /* TODO format.... or find way to avoid long names */

#ifdef __cplusplus
}
#endif

#endif /* CC26x0_RFC_DATA_H */

/*@}*/
