#ifndef __FRW_IPC_MSGQUEUE_H__
#define __FRW_IPC_MSGQUEUE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "oal_ext_if.h"
#include "oam_ext_if.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_FRW_IPC_MSGQUEUE_H

#define FRW_IPC_MASTER_TO_SLAVE_QUEUE_MAX_NUM   (1 << 7)
#define FRW_IPC_SLAVE_TO_MASTER_QUEUE_MAX_NUM   (1 << 8)

#define FRW_IPC_RING_FULL(_head, _tail, _length) (((_tail) + 1) % (_length) == (_head))

#define FRW_IPC_RING_EMPTY(_head, _tail)  ((_head) == (_tail))

#define FRW_IPC_RING_INCR(_val, _lim)       ((_val) = (((_val) + 1) & ((_lim) - 1)))

#define FRW_IPC_RING_TX_INCR(_val)          (FRW_IPC_RING_INCR((_val), (FRW_IPC_MASTER_TO_SLAVE_QUEUE_MAX_NUM)))

#define FRW_IPC_RING_RX_INCR(_val)          (FRW_IPC_RING_INCR((_val), (FRW_IPC_SLAVE_TO_MASTER_QUEUE_MAX_NUM)))

#define FRW_IPC_LOST_WARNING_LOG1(_uc_vap_id, _puc_string, _l_para1)
#define FRW_IPC_LOST_WARNING_LOG2(_uc_vap_id, _puc_string, _l_para1, _l_para2)

#define FRW_IPC_LOG_INFO_PRINT1(_uc_vap_id, _puc_string, _l_para1)
#define FRW_IPC_LOG_INFO_PRINT4(_uc_vap_id, _puc_string, _l_para1, _l_para2, _l_para3, _l_para4)
#define MAX_LOG_RECORD              100

typedef enum
{
    FRW_IPC_TX_CTRL_ENABLED   = 0,
    FRW_IPC_TX_CTRL_DISABLED  = 1,

    FRW_IPC_TX_BUTT
}frw_ipc_tx_ctrl_enum;
typedef OAL_VOLATILE oal_uint8 frw_ipc_tx_ctrl_enum_uint8;

typedef oal_mem_stru frw_ipc_msg_mem_stru;

typedef struct
{
    frw_ipc_msg_mem_stru     *pst_msg_mem;
}frw_ipc_msg_dscr_stru;

typedef struct
{
    OAL_VOLATILE oal_uint32         ul_tail;
    OAL_VOLATILE oal_uint32         ul_head;
    oal_uint32                      ul_max_num;
    frw_ipc_msg_dscr_stru          *pst_dscr;
}frw_ipc_msg_queue_stru;

typedef struct
{
    oal_void        (*p_tx_complete_func)(frw_ipc_msg_mem_stru *);
    oal_void        (*p_rx_complete_func)(frw_ipc_msg_mem_stru *);
}frw_ipc_msg_callback_stru;

typedef struct
{
    oal_uint16          us_seq_num;
    oal_uint8           uc_target_cpuid;
    oal_uint8           uc_msg_type;
    oal_int32           l_time_stamp;
}frw_ipc_log_record_stru;

typedef struct
{
    OAL_VOLATILE oal_uint32     ul_stats_recv_lost;
    OAL_VOLATILE oal_uint32     ul_stats_send_lost;
    OAL_VOLATILE oal_uint32     ul_stats_assert;
    OAL_VOLATILE oal_uint32     ul_stats_send;
    OAL_VOLATILE oal_uint32     ul_stats_recv;
    OAL_VOLATILE oal_uint32     ul_tx_index;
    OAL_VOLATILE oal_uint32     ul_rx_index;
    frw_ipc_log_record_stru     st_tx_stats_record[MAX_LOG_RECORD];
    frw_ipc_log_record_stru     st_rx_stats_record[MAX_LOG_RECORD];
}frw_ipc_log_stru;

extern oal_uint32  frw_ipc_msg_queue_init(frw_ipc_msg_queue_stru *pst_msg_queue, oal_uint32 ul_queue_len);
extern oal_uint32  frw_ipc_msg_queue_destroy(frw_ipc_msg_queue_stru *pst_msg_queue);
extern oal_uint32  frw_ipc_msg_queue_recv(oal_void *p_arg);
extern oal_uint32  frw_ipc_msg_queue_send(frw_ipc_msg_queue_stru *pst_ipc_tx_msg_queue, frw_ipc_msg_mem_stru *pst_msg_input, oal_uint8 uc_flags, oal_uint8 uc_cpuid);
extern oal_uint32  frw_ipc_msg_queue_register_callback(frw_ipc_msg_callback_stru *p_ipc_msg_handler);
extern oal_uint32  frw_ipc_log_exit(frw_ipc_log_stru *pst_log);
extern oal_uint32  frw_ipc_log_init(frw_ipc_log_stru *pst_log);
extern oal_uint32  frw_ipc_log_recv_alarm(frw_ipc_log_stru *pst_log, oal_uint32 ul_lost);
extern oal_uint32  frw_ipc_log_send_alarm(frw_ipc_log_stru *pst_log);
extern oal_uint32  frw_ipc_log_send(frw_ipc_log_stru *pst_log, oal_uint16 us_seq_num, oal_uint8 uc_target_cpuid, oal_uint8 uc_msg_type);
extern oal_uint32  frw_ipc_log_recv(frw_ipc_log_stru *pst_log, oal_uint16 us_seq_num, oal_uint8 uc_target_cpuid, oal_uint8 uc_msg_type);
extern oal_uint32  frw_ipc_log_tx_print(frw_ipc_log_stru *pst_log);
extern oal_uint32  frw_ipc_log_rx_print(frw_ipc_log_stru *pst_log);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of frw_ipc_msgqueue.h */
