#ifndef __PLATFORM_SPEC_1102_H__
#define __PLATFORM_SPEC_1102_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if ((_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_HOST))

#include "oal_types.h"

#if (_PRE_WLAN_CHIP_ASIC == _PRE_WLAN_CHIP_VERSION)
/* hi1151V100H */
#define WLAN_CHIP_VERSION_HI1151V100H           0x11510101
#else
/* hi1151V100H */
#define WLAN_CHIP_VERSION_HI1151V100H           0x11510100
#endif
/* hi1151V100L */
#define WLAN_CHIP_VERSION_HI1151V100L           0x11510102

#define IS_HOST ((_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE) && (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_HOST))
#define IS_DEVICE ((_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE) && (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV))

#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)||(_PRE_OS_VERSION_WIN32_RAW == _PRE_OS_VERSION)
    #define WLAN_FRW_MAX_NUM_CORES          1
#else
    #define WLAN_FRW_MAX_NUM_CORES          1
#endif

#define WLAN_SERVICE_VAP_START_ID_PER_BOARD         1
#define WLAN_CHIP_MAX_NUM_PER_BOARD         1
#define WLAN_DEVICE_MAX_NUM_PER_CHIP        1
#define WLAN_MAC_DEV_MAX_CNT                1

#define WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC    (WLAN_CHIP_MAX_NUM_PER_BOARD * WLAN_DEVICE_MAX_NUM_PER_CHIP)

#define WLAN_SERVICE_AP_MAX_NUM_PER_DEVICE      2
#define WLAN_SERVICE_STA_MAX_NUM_PER_DEVICE     3
#define WLAN_AP_STA_COEXIST_VAP_NUM             0

#define WLAN_PROXY_STA_MAX_NUM_PER_DEVICE              1
#define WLAN_REPEATER_SERVICE_VAP_MAX_NUM_PER_DEVICE  (WLAN_PROXY_STA_MAX_NUM_PER_DEVICE + 1)

#define WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE     WLAN_SERVICE_STA_MAX_NUM_PER_DEVICE
#define WLAN_CONFIG_VAP_MAX_NUM_PER_DEVICE      1

#define WLAN_VAP_MAX_NUM_PER_DEVICE_LIMIT      (WLAN_CONFIG_VAP_MAX_NUM_PER_DEVICE + WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE)
#define WLAN_VAP_SUPPORT_MAX_NUM_LIMIT      (WLAN_CHIP_MAX_NUM_PER_BOARD * WLAN_DEVICE_MAX_NUM_PER_CHIP * WLAN_VAP_MAX_NUM_PER_DEVICE_LIMIT)
//#define WLAN_VAP_SUPPOTR_MAX_NUM            (WLAN_CHIP_MAX_NUM_PER_BOARD * WLAN_DEVICE_MAX_NUM_PER_CHIP * WLAN_VAP_MAX_NUM_PER_DEVICE)

#define WLAN_SERVICE_VAP_SUPPOTR_MAX_NUM_LIMIT    (WLAN_CHIP_MAX_NUM_PER_BOARD * WLAN_DEVICE_MAX_NUM_PER_CHIP * (WLAN_VAP_MAX_NUM_PER_DEVICE_LIMIT-1))
//#define WLAN_SERVICE_VAP_SUPPOTR_MAX_NUM    (WLAN_CHIP_MAX_NUM_PER_BOARD * WLAN_DEVICE_MAX_NUM_PER_CHIP * WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE)

#define WLAN_MULTI_USER_MAX_NUM_LIMIT             (WLAN_SERVICE_VAP_SUPPOTR_MAX_NUM_LIMIT)

#define WLAN_CHIP_DBSC_DEVICE_NUM       1

#if (((_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION)||(_PRE_OS_VERSION_WIN32_RAW == _PRE_OS_VERSION)) || (_PRE_OS_VERSION_WINDOWS == _PRE_OS_VERSION))
#define WLAN_OAM_FILE_PATH      "C:\\OAM.log"
#elif ((_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION) || (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION))
#define WLAN_OAM_FILE_PATH      "\\home\\oam.log"
#endif

#define WLAN_MEM_MAX_BYTE_LEN               (32100 + 1)
#define WLAN_MAX_MAC_HDR_LEN                     36

#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION) || (_PRE_OS_VERSION_WIN32_RAW == _PRE_OS_VERSION)
#define WLAN_MEM_MAX_SUBPOOL_NUM            6
#else
#define WLAN_MEM_MAX_SUBPOOL_NUM            8
#endif
#define WLAN_MEM_MAX_USERS_NUM              4

#define WLAN_TID_MPDU_NUM_BIT               9
#define WLAN_TID_MPDU_NUM_LIMIT             (1 << WLAN_TID_MPDU_NUM_BIT)

#define WLAN_MEM_SHARED_RX_DSCR_SIZE        68
#define WLAN_MEM_SHARED_TX_DSCR_SIZE1       88
#define WLAN_MEM_SHARED_TX_DSCR_SIZE2       88

#if defined(_PRE_DEBUG_MODE)  || defined(_PRE_WLAN_CACHE_COHERENT_SUPPORT)
#define WLAN_MEM_SHARED_RX_DSCR_CNT         110
#define WLAN_MEM_SHARED_TX_DSCR_CNT1        172
#define WLAN_MEM_SHARED_TX_DSCR_CNT2        0
#else
#define WLAN_MEM_SHARED_RX_DSCR_CNT         0
#define WLAN_MEM_SHARED_TX_DSCR_CNT1        0
#define WLAN_MEM_SHARED_TX_DSCR_CNT2        0
#endif
#define TOTAL_WLAN_MEM_SHARED_DSCR_SIZE     ((WLAN_MEM_SHARED_RX_DSCR_SIZE + OAL_MEM_INFO_SIZE + OAL_DOG_TAG_SIZE)*WLAN_MEM_SHARED_RX_DSCR_CNT \
                                            + (WLAN_MEM_SHARED_TX_DSCR_SIZE1 + OAL_MEM_INFO_SIZE + OAL_DOG_TAG_SIZE)*WLAN_MEM_SHARED_TX_DSCR_CNT1 \
                                            + (WLAN_MEM_SHARED_TX_DSCR_SIZE2 + OAL_MEM_INFO_SIZE + OAL_DOG_TAG_SIZE)*WLAN_MEM_SHARED_TX_DSCR_CNT2)

#define WLAN_MEM_SHARED_MGMT_PKT_SIZE1      800
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
#define WLAN_MEM_SHARED_MGMT_PKT_CNT1       0
#else
#define WLAN_MEM_SHARED_MGMT_PKT_CNT1       1
#endif
#define TOTAL_WLAN_MEM_SHARED_MGMT_PKT_SIZE ((WLAN_MEM_SHARED_MGMT_PKT_SIZE1 + OAL_MEM_INFO_SIZE + OAL_DOG_TAG_SIZE)*WLAN_MEM_SHARED_MGMT_PKT_CNT1)

#define WLAN_MEM_SHARED_DATA_PKT_SIZE       44
#define WLAN_MEM_SHARED_DATA_PKT_CNT        200
#define TOTAL_WLAN_MEM_SHARED_DATA_PKT_SIZE ((WLAN_MEM_SHARED_DATA_PKT_SIZE + OAL_MEM_INFO_SIZE + OAL_DOG_TAG_SIZE)*WLAN_MEM_SHARED_DATA_PKT_CNT)

#define WLAN_MEM_LOCAL_SIZE1                32
#define WLAN_MEM_LOCAL_CNT1                 69

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
#define WLAN_MEM_LOCAL_SIZE2                144
#define WLAN_MEM_LOCAL_CNT2                 800
#else
#define WLAN_MEM_LOCAL_SIZE2                104
#define WLAN_MEM_LOCAL_CNT2                 50
#endif

#define WLAN_MEM_LOCAL_SIZE3                264

#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION) || (_PRE_OS_VERSION_WIN32_RAW == _PRE_OS_VERSION)
#define WLAN_MEM_LOCAL_CNT3                 (WLAN_VAP_SUPPORT_MAX_NUM_LIMIT + 60)
#else
#define WLAN_MEM_LOCAL_CNT3                 (WLAN_VAP_SUPPORT_MAX_NUM_LIMIT + 60)
#endif

#define WLAN_MEM_LOCAL_SIZE4                512
#define WLAN_MEM_LOCAL_CNT4                 20

#define WLAN_MEM_LOCAL_SIZE5                4304
#define WLAN_MEM_LOCAL_CNT5                 64

#define WLAN_MEM_LOCAL_SIZE6                16000
#define WLAN_MEM_LOCAL_CNT6                 0

#define WLAN_MEM_EVENT_SIZE1                72
#define WLAN_MEM_EVENT_SIZE2                528

#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION) || (_PRE_OS_VERSION_WIN32_RAW == _PRE_OS_VERSION)
#define WLAN_MEM_EVENT_CNT1                 180
#define WLAN_MEM_EVENT_CNT2                 4

#else
#define WLAN_MEM_EVENT_CNT1                 (180 * WLAN_FRW_MAX_NUM_CORES)
#define WLAN_MEM_EVENT_CNT2                 4
#endif

#define WLAN_WPS_IE_MAX_SIZE                WLAN_MEM_EVENT_SIZE2 - 32
#ifdef _PRE_WLAN_FEATURE_HILINK
#define WLAN_OKC_IE_MAX_SIZE                WLAN_MEM_EVENT_SIZE2 - 32
#endif

#define WLAN_MEM_MIB_SIZE1                  1184
#define WLAN_MEM_MIB_CNT1                   (WLAN_VAP_SUPPORT_MAX_NUM_LIMIT - 1)

#if ((_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)||(_PRE_OS_VERSION_WIN32_RAW == _PRE_OS_VERSION))
#define  WLAN_MEM_NETBUF_SIZE1              180
#define  WLAN_MEM_NETBUF_CNT1               70

#define  WLAN_MEM_NETBUF_SIZE2              800
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
#define  WLAN_MEM_NETBUF_CNT2               8
#elif (_PRE_OS_VERSION_WIN32_RAW == _PRE_OS_VERSION)
#define  WLAN_MEM_NETBUF_CNT2               16
#endif

#define  WLAN_MEM_NETBUF_SIZE3              1568
#define  WLAN_MEM_NETBUF_CNT3               176

#define  WLAN_MEM_NETBUF_SIZE4              512
#define  WLAN_MEM_NETBUF_CNT4               4

#define  OAL_NETBUF_MACHDR_BYTE_LEN         64

#define WLAN_LARGE_NETBUF_SIZE        WLAN_MEM_NETBUF_SIZE3
#define WLAN_MGMT_NETBUF_SIZE         WLAN_MEM_NETBUF_SIZE2
#define WLAN_SHORT_NETBUF_SIZE        WLAN_MEM_NETBUF_SIZE1
#define WLAN_SDT_NETBUF_SIZE          WLAN_MEM_NETBUF_SIZE4

#define WLAN_MAX_NETBUF_SIZE         (WLAN_LARGE_NETBUF_SIZE + WLAN_MAX_MAC_HDR_LEN)

#else
#define WLAN_MEM_NETBUF_SIZE1               0
#define WLAN_MEM_NETBUF_CNT1                192

#ifndef _PRE_WLAN_PHY_PERFORMANCE
#define WLAN_MEM_NETBUF_SIZE2               1600
#define WLAN_MEM_NETBUF_CNT2                512
#define WLAN_MEM_NETBUF_SIZE3               2500
#define WLAN_MEM_NETBUF_CNT3                32

#else
#define WLAN_MEM_NETBUF_SIZE2               5100
#define WLAN_MEM_NETBUF_CNT2                512

#define WLAN_MEM_NETBUF_SIZE3               5100
#define WLAN_MEM_NETBUF_CNT3                32
#endif

#define  WLAN_MEM_NETBUF_SIZE4              512
#define  WLAN_MEM_NETBUF_CNT4               4

#define WLAN_LARGE_NETBUF_SIZE        WLAN_MEM_NETBUF_SIZE2
#define WLAN_MGMT_NETBUF_SIZE         WLAN_MEM_NETBUF_SIZE2
#define WLAN_SHORT_NETBUF_SIZE        WLAN_MEM_NETBUF_SIZE2
#define WLAN_MAX_NETBUF_SIZE          WLAN_LARGE_NETBUF_SIZE
#define WLAN_SDT_NETBUF_SIZE          WLAN_MEM_NETBUF_SIZE4

#endif

#define WLAN_MEM_NETBUF_ALIGN               4
#define WLAN_MEM_ETH_HEADER_LEN             14

#define WLAN_SDT_SKB_HEADROOM_LEN       8
#define WLAN_SDT_SKB_TAILROOM_LEN       1
#define WLAN_SDT_SKB_RESERVE_LEN        (WLAN_SDT_SKB_HEADROOM_LEN + WLAN_SDT_SKB_TAILROOM_LEN)

#define WLAN_MEM_SDT_NETBUF_PAYLOAD1            37
#define WLAN_MEM_SDT_NETBUF_PAYLOAD2            100
#define WLAN_MEM_SDT_NETBUF_PAYLOAD3            512
#define WLAN_MEM_SDT_NETBUF_PAYLOAD4            1600

#define WLAN_SDT_NETBUF_MAX_PAYLOAD             WLAN_MEM_SDT_NETBUF_PAYLOAD4

#define WLAN_MEM_SDT_NETBUF_SIZE1       (WLAN_MEM_SDT_NETBUF_PAYLOAD1 + WLAN_SDT_SKB_RESERVE_LEN)
#define WLAN_MEM_SDT_NETBUF_SIZE1_CNT   250
#define WLAN_MEM_SDT_NETBUF_SIZE2       (WLAN_MEM_SDT_NETBUF_PAYLOAD2 + WLAN_SDT_SKB_RESERVE_LEN)
#define WLAN_MEM_SDT_NETBUF_SIZE2_CNT   250
#define WLAN_MEM_SDT_NETBUF_SIZE3       (WLAN_MEM_SDT_NETBUF_PAYLOAD3 + WLAN_SDT_SKB_RESERVE_LEN)
#define WLAN_MEM_SDT_NETBUF_SIZE3_CNT   250
#define WLAN_MEM_SDT_NETBUF_SIZE4       (WLAN_MEM_SDT_NETBUF_PAYLOAD4 + WLAN_SDT_SKB_RESERVE_LEN)
#define WLAN_MEM_SDT_NETBUF_SIZE4_CNT   256

#define WLAN_SDT_MSG_FLT_HIGH_THD           800
#define WLAN_SDT_MSG_QUEUE_MAX_LEN          (WLAN_MEM_SDT_NETBUF_SIZE1_CNT + \
                                                     WLAN_MEM_SDT_NETBUF_SIZE2_CNT + \
                                                     WLAN_MEM_SDT_NETBUF_SIZE3_CNT + \
                                                     WLAN_MEM_SDT_NETBUF_SIZE4_CNT - 6)

#define DEFAULT_TX_TCP_ACK_OPT_ENABLE (OAL_TRUE)
#define DEFAULT_RX_TCP_ACK_OPT_ENABLE (OAL_FALSE)
#define DEFAULT_TX_TCP_ACK_THRESHOLD (1)
#define DEFAULT_RX_TCP_ACK_THRESHOLD (1)

#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)||(_PRE_OS_VERSION_WIN32_RAW == _PRE_OS_VERSION)
#define FRW_EVENT_MAX_NUM_QUEUES    FRW_EVENT_TYPE_BUTT

/*Device*/
#if (_PRE_WLAN_CHIP_ASIC == _PRE_WLAN_CHIP_VERSION)
#define WLAN_FRW_EVENT_CFG_TABLE \
  { /* HIGH_PRIO */     {   1,               32,                      0, 0}, \
    /* HOST_CRX */      {   1,                8,                      1, 0}, \
    /* HOST_DRX */      {   1,               64,                      1, 0}, \
    /* HOST_CTX */      {   1,                8,                      1, 0}, \
    /* HOST_SDT */      {   1,               64,                      1, 0}, \
    /* WLAN_CRX */      {   1,                8,                      1, 0}, \
    /* WLAN_DRX */      {   1,               64,                      1, 0}, \
    /* WLAN_CTX */      {   1,                8,                      1, 0}, \
    /* WLAN_DTX */      {   1,               64,                      1, 0}, \
    /* WLAN_TX_COMP */  {   1,               64,                      1, 0}, \
    /* TBTT */          {   1,                8,                      1, 0}, \
    /* TIMEOUT */       {   1,                2,                      1, 0}, \
    /* HMAC MISC */     {   1,                0,                      1, 0}, \
    /* DMAC MISC */     {   1,               64,                      0, 0}, \
    /*HMAC_HCC_TEST*/   {   1,               64,                      1, 0},  \
  }
#else
#define WLAN_FRW_EVENT_CFG_TABLE \
  { /* HIGH_PRIO */     {   1,               32,                      0, 0}, \
    /* HOST_CRX */      {   1,                8,                      1, 0}, \
    /* HOST_DRX */      {   1,               64,                      1, 0}, \
    /* HOST_CTX */      {   1,                8,                      1, 0}, \
    /* HOST_SDT */      {   1,               64,                      1, 0}, \
    /* WLAN_CRX */      {   1,                8,                      1, 0}, \
    /* WLAN_DRX */      {   1,               64,                      1, 0}, \
    /* WLAN_CTX */      {   1,                8,                      1, 0}, \
    /* WLAN_DTX */      {   1,               64,                      1, 0}, \
    /* WLAN_TX_COMP */  {   1,               64,                      1, 0}, \
    /* TBTT */          {   1,                8,                      1, 0}, \
    /* TIMEOUT */       {   1,                2,                      1, 0}, \
    /* HMAC MISC */     {   1,                0,                      1, 0}, \
    /* DMAC MISC */     {   1,               64,                      0, 0}, \
    /*HMAC_HCC_TEST*/   {   1,               64,                      1, 0}, \
  }
#endif
#else

#define FRW_EVENT_MAX_NUM_QUEUES    (FRW_EVENT_TYPE_BUTT * WLAN_VAP_SUPPORT_MAX_NUM_LIMIT)

#define WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    /* HIGH_PRIO */     {   1,               32,                      0, 0}, \
    /* HOST_CRX */      {   1,               64,                      1, 0}, \
    /* HOST_DRX */      {   1,               64,                      1, 0}, \
    /* HOST_CTX */      {   1,               64,                      1, 0}, \
    /* HOST_SDT */      {   1,               64,                      1, 0}, \
    /* WLAN_CRX */      {   1,               64,                      1, 0}, \
    /* WLAN_DRX */      {   1,               64,                      1, 0}, \
    /* WLAN_CTX */      {   1,               64,                      1, 0}, \
    /* WLAN_DTX */      {   1,               64,                      1, 0}, \
    /* WLAN_TX_COMP */  {   1,                0,                      1, 0}, \
    /* TBTT */          {   1,                0,                      1, 0}, \
    /* TIMEOUT */       {   1,                2,                      1, 0}, \
    /* HMAC MISC */     {   1,                0,                      1, 0}, \
    /* DMAC MISC */     {   1,               64,                      0, 0}, \
    /*HMAC_HCC_TEST*/   {   1,               128,                     1, 0},

/*Host*/
#define WLAN_FRW_EVENT_CFG_TABLE \
  { \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
  }
#endif

#define WLAN_WPA_KEY_LEN                    32

#define WLAN_WPA_SEQ_LEN                    16

#define WLAN_MAC_ADDR_LEN                   6
#define WLAN_MAX_FRAME_HEADER_LEN           36
#define WLAN_MIN_FRAME_HEADER_LEN           10
#define WLAN_MAX_FRAME_LEN                  1600
#define WLAN_MGMT_FRAME_HEADER_LEN          24

typedef enum
{
    WLAN_ASSOC_REQ              = 0,    /* 0000 */
    WLAN_ASSOC_RSP              = 1,    /* 0001 */
    WLAN_REASSOC_REQ            = 2,    /* 0010 */
    WLAN_REASSOC_RSP            = 3,    /* 0011 */
    WLAN_PROBE_REQ              = 4,    /* 0100 */
    WLAN_PROBE_RSP              = 5,    /* 0101 */
    WLAN_TIMING_AD              = 6,    /* 0110 */
    WLAN_MGMT_SUBTYPE_RESV1     = 7,    /* 0111 */
    WLAN_BEACON                 = 8,    /* 1000 */
    WLAN_ATIM                   = 9,    /* 1001 */
    WLAN_DISASOC                = 10,   /* 1010 */
    WLAN_AUTH                   = 11,   /* 1011 */
    WLAN_DEAUTH                 = 12,   /* 1100 */
    WLAN_ACTION                 = 13,   /* 1101 */
    WLAN_ACTION_NO_ACK          = 14,   /* 1110 */
    WLAN_MGMT_SUBTYPE_RESV2     = 15,   /* 1111 */

    WLAN_MGMT_SUBTYPE_BUTT      = 16,
}wlan_frame_mgmt_subtype_enum;

typedef enum
{
    WLAN_WME_AC_BE = 0,    /* best effort */
    WLAN_WME_AC_BK = 1,    /* background */
    WLAN_WME_AC_VI = 2,    /* video */
    WLAN_WME_AC_VO = 3,    /* voice */

    WLAN_WME_AC_BUTT = 4,
    WLAN_WME_AC_MGMT = WLAN_WME_AC_BUTT
}wlan_wme_ac_type_enum;
typedef oal_uint8 wlan_wme_ac_type_enum_uint8;

#define WLAN_TID_MAX_NUM                    WLAN_TIDNO_BUTT

typedef enum
{
    WLAN_TIDNO_BEST_EFFORT              = 0,
    WLAN_TIDNO_BACKGROUND               = 1,
    WLAN_TIDNO_UAPSD                    = 2,
    WLAN_TIDNO_ANT_TRAINING_LOW_PRIO    = 3,
    WLAN_TIDNO_ANT_TRAINING_HIGH_PRIO   = 4,
    WLAN_TIDNO_VIDEO                    = 5,
    WLAN_TIDNO_VOICE                    = 6,
    WLAN_TIDNO_BCAST                    = 7,

    WLAN_TIDNO_BUTT
}wlan_tidno_enum;
typedef oal_uint8 wlan_tidno_enum_uint8;

#define WLAN_ACTIVE_USER_MAX_NUM            8

#endif /* #if ((_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_HOST))*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* #ifndef __PLATFORM_SPEC_1102_H__ */
