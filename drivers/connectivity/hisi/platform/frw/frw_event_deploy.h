#ifndef __FRW_EVENT_DEPLOY_H__
#define __FRW_EVENT_DEPLOY_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "oal_ext_if.h"
#include "frw_event_main.h"
#include "frw_ipc_msgqueue.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_FRW_EVENT_DEPLOY_H

typedef enum
{
    FRW_IPC_CORE_ID_MASTER   = 0,
    FRW_IPC_CORE_ID_SLAVE    = 1,

    FRW_IPC_CORE_NUM_BUTT
}frw_ipc_core_id_enum;
typedef oal_uint8 frw_ipc_core_id_enum_uint8;

typedef enum
{
    FRW_IPC_CORE_TYPE_MASTER   = 0,
    FRW_IPC_CORE_TYPE_SLAVE    = 1,

    FRW_IPC_CORE_TYPE_BUTT
}frw_ipc_core_type_enum;
typedef oal_uint8 frw_ipc_core_type_enum_uint8;

typedef enum
{
    FRW_IPC_CORE_STATE_INIT      = 0,
    FRW_IPC_CORE_STATE_CONNECTED = 1,
    FRW_IPC_CORE_STATE_RESET     = 2,
    FRW_IPC_CORE_STATE_EXIT      = 3,

    FRW_IPC_CORE_STATE_BUTT
}frw_ipc_core_state_enum;
typedef OAL_VOLATILE oal_uint8 frw_ipc_core_state_enum_uint8;

typedef enum
{
    FRW_IPC_MSG_TYPE_EVENT            = 0,
    FRW_IPC_MSG_TYPE_CONNECT_REQUEST  = 1,
    FRW_IPC_MSG_TYPE_CONNECT_RESPONSE = 2,
    FRW_IPC_MSG_TYPE_CONFIG_REQUEST   = 3,
    FRW_IPC_MSG_TYPE_CONFIG_RESPONSE  = 4,
    FRW_IPC_MSG_TYPE_ERROR_NOTICE     = 5,
    FRW_IPC_MSG_TYPE_RESET_REQUEST    = 6,
    FRW_IPC_MSG_TYPE_RESET_RESPONSE   = 7,
    FRW_IPC_MSG_TYPE_OPEN_OAM         = 8,
    FRW_IPC_MSG_TYPE_CLOSE_OAM        = 9,
    FRW_IPC_MSG_TYPE_EXIT_REQUEST     = 10,
    FRW_IPC_MSG_TYPE_EXIT_RESPONSE    = 11,
    FRW_IPC_MSG_TYPE_TX_INT_ENABLE    = 12,
    FRW_IPC_MSG_TYPE_TX_INT_DISENABLE = 13,

    FRW_IPC_MSG_TYPE_BUTT
}frw_ipc_msg_type_enum;
typedef oal_uint8 frw_ipc_msg_type_enum_uint8;

#define FRW_IPC_MAX_SEQ_NUMBER   (0xFFFF)

#define FRW_IPC_GET_MSG_QUEUE(_queue, _type)     (_queue = (FRW_IPC_CORE_TYPE_MASTER == _type) ? \
                                                           &g_st_queue_master_to_slave : \
                                                           &g_st_queue_slave_to_master)

typedef struct
{
    frw_ipc_msg_header_stru st_ipc_hdr;
    oal_uint8               auc_resv[2];
    oal_uint16              ul_length;
    oal_uint8               auc_data[4];
}frw_ipc_inter_msg_stru;

typedef struct
{
    frw_ipc_core_id_enum_uint8      en_cpuid;
    frw_ipc_core_id_enum_uint8      en_target_cpuid;
    frw_ipc_core_state_enum_uint8   en_states;
    frw_ipc_tx_ctrl_enum_uint8      en_tx_int_ctl;
    frw_ipc_core_type_enum_uint8    en_cpu_type;
    oal_uint8                       uc_resv[3];
    oal_uint16                      us_seq_num_rx_expect;
    oal_uint16                      us_seq_num_tx_expect;
    frw_ipc_msg_callback_stru       st_ipc_msg_callback;
    oal_irq_dev_stru                st_irq_dev;
#ifdef _PRE_DEBUG_MODE
    frw_ipc_log_stru                st_log;
#endif
}frw_ipc_node_stru;

OAL_STATIC OAL_INLINE frw_ipc_core_type_enum frw_ipc_get_core_type(oal_void)
{
    if (FRW_IPC_CORE_ID_MASTER == OAL_GET_CORE_ID())
    {
        return FRW_IPC_CORE_TYPE_MASTER;
    }

    return FRW_IPC_CORE_TYPE_SLAVE;
}

OAL_STATIC OAL_INLINE oal_uint8 *frw_ipc_get_header(frw_ipc_msg_mem_stru *pst_ipc_mem_msg)
{
    pst_ipc_mem_msg->puc_data -= FRW_IPC_MSG_HEADER_LENGTH;
    return pst_ipc_mem_msg->puc_data;
}

extern oal_uint32  frw_event_deploy_init(oal_void);
extern oal_uint32  frw_event_deploy_exit(oal_void);


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of frw_event_deploy.h */
