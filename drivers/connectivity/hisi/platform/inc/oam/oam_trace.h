#ifndef __OAM_TRACE_H__
#define __OAM_TRACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "oal_ext_if.h"
#include "oam_ext_if.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_OAM_TRACE_H

#define OAM_PROFILING_TX_PACKET_MAX_COUNT       2
#define OAM_PROFILING_RX_PACKET_MAX_COUNT       20
#define OAM_PROFILING_ALG_PACKET_MAX_COUNT       2

#define OAM_PROFILING_PACKET_INVALID_VALUE      1010
#define OAM_PROFILING_PACKET_ABNORMAL_GAP       2000

#define OAM_PROFILING_STATISTIC_RX_DEBUG        0x01
#define OAM_PROFILING_STATISTIC_TX_DEBUG        0x02
#define OAM_PROFILING_STATISTIC_ALG_DEBUG       0x04

#define OAM_TRACE_PRINT_DATA_LENGTH     128
#define OAM_TRACE_PRINT_FORMAT_LENGTH   128

typedef enum
{
    OAM_PROFILING_SWITCH_DEBUG_CONFIG = 1,

    OAM_PROFILING_SWITCH_CONFIG_BUTT
}oam_profiling_switch_config_enum;
typedef oal_uint8  oam_profiling_switch_config_enum_uint8;

typedef struct
{
    oal_spin_lock_stru  st_spin_lock;
    oal_uint16          us_abnormal_index;
    oal_uint8           uc_idx_for_array;
    oal_uint8           uc_skb_id_idx;

    oal_uint16          aus_tx_skb_id_list[OAM_PROFILING_TX_PACKET_MAX_COUNT];
    oal_uint16          aus_tx_pass_count[OAM_PROFILING_TX_PACKET_MAX_COUNT][OAM_PROFILING_TX_FUNC_BUTT];
    oal_uint32          ast_tx_func_stand_time[OAM_PROFILING_TX_PACKET_MAX_COUNT][OAM_PROFILING_TX_FUNC_BUTT];
    oal_uint32          ast_tx_func_time_offset[OAM_PROFILING_TX_PACKET_MAX_COUNT][OAM_PROFILING_TX_FUNC_BUTT];
}oam_profiling_tx_statistic_stru;

typedef struct
{
    oal_spin_lock_stru  st_spin_lock;
    oal_uint16          us_abnormal_index;
    oal_uint8           uc_idx_for_array;
    oal_uint8           uc_skb_id_idx;

    oal_uint16          aus_rx_skb_id_list[OAM_PROFILING_RX_PACKET_MAX_COUNT];
    oal_uint16          aus_rx_pass_count[OAM_PROFILING_RX_PACKET_MAX_COUNT][OAM_PROFILING_RX_FUNC_BUTT];
    oal_uint32          ast_rx_func_stand_time[OAM_PROFILING_RX_PACKET_MAX_COUNT][OAM_PROFILING_RX_FUNC_BUTT];
    oal_uint32          ast_rx_func_time_offset[OAM_PROFILING_RX_PACKET_MAX_COUNT][OAM_PROFILING_RX_FUNC_BUTT];
}oam_profiling_rx_statistic_stru;

typedef struct
{
    oal_spin_lock_stru  st_spin_lock;
    oal_uint16          us_abnormal_index;
    oal_uint8           uc_idx_for_array;
    oal_uint8           uc_skb_id_idx;

    oal_uint16          aus_alg_skb_id_list[OAM_PROFILING_ALG_PACKET_MAX_COUNT];
    oal_uint16          aus_alg_pass_count[OAM_PROFILING_ALG_PACKET_MAX_COUNT][OAM_PROFILING_ALG_FUNC_BUTT];
    oal_uint32          ast_alg_func_stand_time[OAM_PROFILING_ALG_PACKET_MAX_COUNT][OAM_PROFILING_ALG_FUNC_BUTT];
    oal_uint32          ast_alg_func_time_offset[OAM_PROFILING_ALG_PACKET_MAX_COUNT][OAM_PROFILING_ALG_FUNC_BUTT];
}oam_profiling_alg_statistic_stru;

typedef struct
{
    oal_uint32          aul_timestamp[OAM_PROFILING_STARTTIME_FUNC_BUTT];
}oam_profiling_starttime_statistic_stru;

typedef struct
{
    oal_uint32          aul_timestamp[OAM_PROFILING_CHSWITCH_FUNC_BUTT];
}oam_profiling_chswitch_statistic_stru;

typedef struct
{
    oal_int     i_profiling_tx_debuging_enable;
    oal_int     i_profiling_rx_debuging_enable;
    oal_int     i_profiling_alg_debuging_enable;
}oam_profiling_statistic_debug_stru;

typedef struct
{
    oal_uint8   auc_resv[44];

    oal_uint16  us_skb_id;
    oal_uint8   uc_is_broad_cast;
    oal_uint8   uc_is_used;
}oam_profiling_skb_cb_stru;

extern oal_uint32  oam_trace_init(oal_void);
extern oal_uint32  oam_trace_set_switch(oal_switch_enum_uint8 en_switch);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oam_trace.h */
