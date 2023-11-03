#ifndef __FRW_EXT_IF_H__
#define __FRW_EXT_IF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "oal_ext_if.h"
#include "oam_ext_if.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_FRW_EXT_IF_H

#define FRW_TIMER_RESTART_TIMER(_pst_timeout, _ul_timeout, _en_is_periodic) \
        frw_timer_restart_timer(_pst_timeout, _ul_timeout, _en_is_periodic)
#define FRW_TIMER_STOP_TIMER(_pst_timeout) \
        frw_timer_stop_timer(_pst_timeout)
#define FRW_TIMER_CREATE_TIMER(_pst_timeout, _p_timeout_func, _ul_timeout, _p_timeout_arg, _en_is_periodic, _en_module_id, _ul_core_id) \
        frw_timer_create_timer(THIS_FILE_ID, __LINE__, _pst_timeout, _p_timeout_func, _ul_timeout, _p_timeout_arg, _en_is_periodic, _en_module_id, _ul_core_id)
#define FRW_TIMER_DESTROY_TIMER(_pst_timeout)\
        frw_timer_destroy_timer(THIS_FILE_ID, __LINE__, _pst_timeout)
#define FRW_TIMER_IMMEDIATE_DESTROY_TIMER(_pst_timeout)\
        frw_timer_immediate_destroy_timer(THIS_FILE_ID, __LINE__, _pst_timeout)

#define FRW_TIMER_TRACK_NUM     256
#define FRW_TIMEOUT_TRACK_NUM   256

typedef enum
{
    FRW_INIT_STATE_START,
    FRW_INIT_STATE_FRW_SUCC,
    FRW_INIT_STATE_HAL_SUCC,
    FRW_INIT_STATE_DMAC_CONFIG_VAP_SUCC,
    FRW_INIT_STATE_HMAC_CONFIG_VAP_SUCC,
    FRW_INIT_STATE_ALL_SUCC,

    FRW_INIT_STATE_BUTT
}frw_init_enum;
typedef oal_uint16 frw_init_enum_uint16;

typedef enum
{
    FRW_EVENT_TYPE_HIGH_PRIO = 0,
    FRW_EVENT_TYPE_HOST_CRX,
    FRW_EVENT_TYPE_HOST_DRX,
    FRW_EVENT_TYPE_HOST_CTX,
    FRW_EVENT_TYPE_HOST_SDT_REG  = 4,
    FRW_EVENT_TYPE_WLAN_CRX,
    FRW_EVENT_TYPE_WLAN_DRX,
    FRW_EVENT_TYPE_WLAN_CTX,
    FRW_EVENT_TYPE_WLAN_DTX,
    FRW_EVENT_TYPE_WLAN_TX_COMP  = 9,
    FRW_EVENT_TYPE_TBTT,
    FRW_EVENT_TYPE_TIMEOUT,
    FRW_EVENT_TYPE_HMAC_MISC,
    FRW_EVENT_TYPE_DMAC_MISC     = 13,
    FRW_EVENT_TYPE_BUTT
}frw_event_type_enum;

typedef oal_uint8 frw_event_type_enum_uint8;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

typedef enum
{
    DMAC_HCC_TX_EVENT_SUB_TYPE,

    DMAC_HCC_TX_EVENT_SUB_TYPE_BUTT
}dmac_hcc_tx_event_sub_type_enum;
typedef oal_uint8 dmac_hcc_tx_event_sub_type_enum_uint8;

typedef enum
{
    DMAC_HCC_RX_EVENT_SUB_TYPE,

    DMAC_HCC_RX_EVENT_SUB_TYPE_BUTT
}dmac_hcc_rx_event_sub_type_enum;
typedef oal_uint8 dmac_hcc_rx_event_sub_type_enum_uint8;


typedef struct
{
    frw_event_type_enum_uint8  en_nest_type;
    oal_uint8                  uc_nest_sub_type;
    void                      *pst_netbuf;
    oal_uint32                 ul_buf_len;
}hcc_event_stru;

/*record the data type by the hcc*/
#pragma pack(push,1)
/*4B*/
struct frw_hcc_extend_hdr
{
    frw_event_type_enum_uint8  en_nest_type;
    oal_uint8                  uc_nest_sub_type;
    oal_uint8                  chip_id:2;             /*this is not good*/
    oal_uint8                  device_id:2;
    oal_uint8                  vap_id:4;
}__OAL_DECLARE_PACKED ;
#pragma pack(pop)

#endif

typedef oal_uint32          (*frw_timeout_func)(oal_void *);

typedef struct
{
    oal_void                   *p_timeout_arg;
    frw_timeout_func            p_func;
    oal_uint32                  ul_time_stamp;
    oal_uint32                  ul_curr_time_stamp;
    oal_uint32                  ul_timeout;
    oal_bool_enum_uint8         en_is_deleting;
    oal_bool_enum_uint8         en_is_registerd;
    oal_bool_enum_uint8         en_is_periodic;
    oal_bool_enum_uint8         en_is_enabled;
    oal_bool_enum_uint8         en_is_running;
    oal_uint8                   uc_pad;
    oam_module_id_enum_uint16   en_module_id;
    oal_uint32                  ul_core_id;
    oal_uint32                  ul_file_id;
    oal_uint32                  ul_line_num;
    oal_dlist_head_stru         st_entry;
}frw_timeout_stru;
#ifdef _PRE_DEBUG_MODE

typedef struct
{
    oal_uint32                  ul_file_id;
    oal_uint32                  ul_line_num;
    oal_uint32                  ul_execute_time;
}frw_timer_track_stru;

typedef struct
{
    oal_uint8               uc_timer_cnt;
    frw_timer_track_stru    st_timer_track[FRW_TIMER_TRACK_NUM];
    oal_uint32              ul_os_timer_interval;
}frw_timeout_track_stru;
#endif

typedef enum
{
    FRW_EVENT_PIPELINE_STAGE_0 = 0,
    FRW_EVENT_PIPELINE_STAGE_1,
#if (((_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION)||(_PRE_OS_VERSION_WIN32_RAW == _PRE_OS_VERSION)) && (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE))
    FRW_EVENT_PIPELINE_STAGE_2,
#endif
    FRW_EVENT_PIPELINE_STAGE_BUTT
}frw_event_pipeline_enum;
typedef oal_uint8 frw_event_pipeline_enum_uint8;

#define FRW_RX_EVENT_TRACK_NUM 256
#define FRW_EVENT_TRACK_NUM     128

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
    extern oal_uint8 g_tx_debug;
#endif

typedef oal_mem_stru    frw_event_mem_stru;

typedef struct
{
    frw_event_type_enum_uint8        en_type;
    oal_uint8                        uc_sub_type;
    oal_uint16                       us_length;
    frw_event_pipeline_enum_uint8    en_pipeline;
    oal_uint8                        uc_chip_id;
    oal_uint8                        uc_device_id;
    oal_uint8                        uc_vap_id;
}frw_event_hdr_stru;

typedef struct
{
    frw_event_hdr_stru    st_event_hdr;
    oal_uint8             auc_event_data[4];
}frw_event_stru;

typedef struct
{
    oal_uint32 (*p_func)(frw_event_mem_stru *);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_uint32 (*p_tx_adapt_func)(frw_event_mem_stru *);
    frw_event_mem_stru *(*p_rx_adapt_func)(frw_event_mem_stru *);
#endif
}frw_event_sub_table_item_stru;

typedef struct
{
    frw_event_sub_table_item_stru   *pst_sub_table;
}frw_event_table_item_stru;

typedef struct
{
    oal_uint16      us_seq_number;
    oal_uint8       uc_target_cpuid;
    oal_uint8       uc_msg_type;
}frw_ipc_msg_header_stru;

typedef struct
{
    oal_uint32      ul_event_cnt;
    oal_uint32      aul_event_time[FRW_EVENT_TRACK_NUM];
    oal_uint16      us_event_type[FRW_EVENT_TRACK_NUM];
    oal_uint16      us_event_sub_type[FRW_EVENT_TRACK_NUM];
}frw_event_track_time_stru;

#define FRW_IPC_MSG_HEADER_LENGTH       (OAL_SIZEOF(frw_ipc_msg_header_stru))

#define FRW_EVENT_HDR_LEN    OAL_SIZEOF(frw_event_hdr_stru)

#define FRW_EVENT_MAX_NUM_QUEUES    (FRW_EVENT_TYPE_BUTT * WLAN_VAP_SUPPORT_MAX_NUM_LIMIT)

#define FRW_FIELD_SETUP(_p, _m, _v)    ((_p)->_m = (_v))

#define FRW_EVENT_HDR_MODIFY_PIPELINE_AND_SUBTYPE(_pst_event_hdr, _uc_sub_type)      \
    do {                                                                            \
        FRW_FIELD_SETUP((_pst_event_hdr), en_pipeline, 1);             \
        FRW_FIELD_SETUP((_pst_event_hdr), uc_sub_type, (_uc_sub_type));                  \
    } while(0)

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
#define FRW_EVENT_HDR_MODIFY_PIPELINE_AND_TYPE_AND_SUBTYPE(_pst_event_hdr, _en_type, _uc_sub_type)      \
        do {                                                                            \
            FRW_FIELD_SETUP((_pst_event_hdr), en_pipeline, 1);             \
            FRW_FIELD_SETUP((_pst_event_hdr), uc_sub_type, (_uc_sub_type));                  \
            FRW_FIELD_SETUP((_pst_event_hdr), en_type, (_en_type));                  \
        } while(0)
#endif


#define FRW_EVENT_ALLOC(_us_len) \
    frw_event_alloc(THIS_FILE_ID, __LINE__, _us_len);

#define FRW_EVENT_FREE(_pst_event_mem) \
    frw_event_free(THIS_FILE_ID, __LINE__, _pst_event_mem)

#define FRW_EVENT_HDR_INIT(_pst_event_hdr, _en_type, _uc_sub_type, _us_length, _en_pipeline, _uc_chip_id, _uc_device_id, _uc_vap_id) \
    do{\
         FRW_FIELD_SETUP((_pst_event_hdr), us_length, (_us_length + FRW_EVENT_HDR_LEN));\
         FRW_FIELD_SETUP((_pst_event_hdr), en_type, (_en_type));\
         FRW_FIELD_SETUP((_pst_event_hdr), uc_sub_type, (_uc_sub_type));\
         FRW_FIELD_SETUP((_pst_event_hdr), en_pipeline, (_en_pipeline));\
         FRW_FIELD_SETUP((_pst_event_hdr), uc_chip_id, (_uc_chip_id));\
         FRW_FIELD_SETUP((_pst_event_hdr), uc_device_id, (_uc_device_id));\
         FRW_FIELD_SETUP((_pst_event_hdr), uc_vap_id, (_uc_vap_id));\
    }while(0)

#define frw_get_event_stru(pst_event_mem)   ((frw_event_stru *)(pst_event_mem)->puc_data)
#define frw_get_event_hdr(pst_event_mem)   ((frw_event_hdr_stru*)(&((frw_event_stru *)(pst_event_mem)->puc_data)->st_event_hdr))
#define frw_get_event_payload(pst_event_mem)   ((oal_uint8*)((frw_event_stru *)(pst_event_mem)->puc_data)->auc_event_data)

OAL_STATIC OAL_INLINE frw_event_mem_stru*  frw_event_alloc(oal_uint32    ul_file_id,
                                                           oal_uint32    ul_line_num,
                                                           oal_uint16    us_payload_length)
{
    frw_event_mem_stru   *pst_event_mem;

    us_payload_length += OAL_MEM_INFO_SIZE;

    pst_event_mem = oal_mem_alloc_enhanced(ul_file_id, ul_line_num, OAL_MEM_POOL_ID_EVENT, (us_payload_length + FRW_EVENT_HDR_LEN), OAL_TRUE);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
        oal_mem_print_normal_pool_info(OAL_MEM_POOL_ID_EVENT);
#endif

        return OAL_PTR_NULL;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    pst_event_mem->ul_return_addr  = oal_get_func_return_address();
#endif

#if (_PRE_MULTI_CORE_MODE_SMP == _PRE_MULTI_CORE_MODE)
    pst_event_mem->puc_data += FRW_IPC_MSG_HEADER_LENGTH;
#endif

    return pst_event_mem;
}

OAL_STATIC OAL_INLINE oal_uint32  frw_event_free(oal_uint32            ul_file_id,
                                                 oal_uint32            ul_line_num,
                                                 frw_event_mem_stru   *pst_event_mem)
{
    oal_uint32       ul_ret;
    //oal_uint     ul_irq_flag;
    frw_event_stru  *pst_frw_event;

    ul_ret = oal_mem_free_enhanced(ul_file_id, ul_line_num, pst_event_mem, OAL_TRUE);
    if(OAL_WARN_ON(OAL_SUCC != ul_ret))
    {
        pst_frw_event =  (frw_event_stru *)pst_event_mem->puc_data;
        OAL_IO_PRINT("[E]frw event free failed!, ret:%d, type:%d, subtype:%d\r\n",ul_ret, pst_frw_event->st_event_hdr.en_type, pst_frw_event->st_event_hdr.uc_sub_type);
        oal_dump_stack();
    }
    //oal_irq_restore(&ul_irq_flag, OAL_5115IRQ_FEF);

    return ul_ret;
}

#ifdef _PRE_DEBUG_MODE
extern frw_event_track_time_stru g_ast_event_time_track[FRW_RX_EVENT_TRACK_NUM];
extern oal_uint32                g_ul_rx_event_idx;
extern oal_bool_enum_uint8       g_en_event_track_switch;
extern oal_uint32                g_ul_schedule_idx;
extern oal_uint32                g_aul_schedule_time[FRW_RX_EVENT_TRACK_NUM];
extern frw_timeout_track_stru    g_st_timeout_track[FRW_TIMEOUT_TRACK_NUM];
extern oal_uint8                 g_uc_timeout_track_idx;
#endif

extern oal_uint8 g_uc_timer_pause;
extern oal_int32  frw_main_init(oal_void);
extern oal_void  frw_main_exit(oal_void);
extern oal_void  frw_set_init_state(frw_init_enum_uint16 en_init_state);
extern frw_init_enum_uint16  frw_get_init_state(oal_void);
extern oal_uint32  frw_event_exit(oal_void);
extern oal_uint32 frw_event_init(oal_void);
extern oal_uint32  frw_event_dispatch_event(frw_event_mem_stru *pst_mem);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
extern oal_uint32  frw_event_post_event(frw_event_mem_stru *pst_event_mem,oal_uint32 ul_core_id);
#endif
extern oal_void  frw_event_table_register(
                frw_event_type_enum_uint8      en_event_type,
                frw_event_pipeline_enum        en_pipeline,
                frw_event_sub_table_item_stru *pst_sub_table);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
oal_void frw_event_sub_rx_adapt_table_init(frw_event_sub_table_item_stru *pst_sub_table, oal_uint32 ul_table_nums,
                                                frw_event_mem_stru *(*p_rx_adapt_func)(frw_event_mem_stru *));
#endif
extern oal_void  frw_timer_sys_start(void);
extern oal_void  frw_timer_sys_stop(void);
extern oal_void  frw_event_dump_event(oal_uint8 *puc_event);
extern oal_uint32  frw_event_flush_event_queue(frw_event_type_enum_uint8 uc_event_type);
extern oal_void frw_event_vap_pause_event(oal_uint8 uc_vap_id);
extern oal_void frw_event_vap_resume_event(oal_uint8 uc_vap_id);
extern oal_uint32 frw_event_vap_flush_event(oal_uint8                 uc_vap_id,
                                            frw_event_type_enum_uint8 en_event_type,
                                            oal_bool_enum_uint8       en_drop);
extern oal_void  frw_timer_create_timer(
                                            oal_uint32 ul_file_id,
                                            oal_uint32 ul_line_num,
                                            frw_timeout_stru *pst_timeout,
                                            frw_timeout_func  p_timeout_func,
                                            oal_uint32 ul_timeout,
                                            oal_void *p_timeout_arg,
                                            oal_bool_enum_uint8  en_is_periodic,
                                            oam_module_id_enum_uint16   en_module_id,
                                            oal_uint32 ul_core_id);
extern oal_void  frw_timer_destroy_timer(oal_uint32 ul_file_id,
                                              oal_uint32 ul_line_num,
                                              frw_timeout_stru *pst_timeout);
extern oal_void  frw_timer_immediate_destroy_timer(oal_uint32 ul_file_id,
                                                           oal_uint32 ul_line_num,
                                                           frw_timeout_stru *pst_timeout);
extern oal_void  frw_timer_restart_timer(frw_timeout_stru *pst_timeout, oal_uint32 ul_timeout, oal_bool_enum_uint8  en_is_periodic);
extern oal_void  frw_timer_add_timer(frw_timeout_stru *pst_timeout);
extern oal_void  frw_timer_stop_timer(frw_timeout_stru *pst_timeout);
extern oal_void  frw_timer_dump_timer(oal_uint32 ul_core_id);
extern oal_void  frw_timer_delete_all_timer(oal_void);
extern oal_uint32  frw_event_queue_info(oal_void);
extern oal_void  frw_event_process_all_event(oal_uint ui_data);
extern oal_bool_enum_uint8  frw_is_event_queue_empty(frw_event_type_enum_uint8 uc_event_type);
extern oal_bool_enum_uint8  frw_is_vap_event_queue_empty(oal_uint32 ul_core_id, oal_uint8 uc_vap_id, oal_uint8 event_type);
extern oal_uint8 frw_task_thread_condition_check(oal_uint32 ul_core_id);

#ifdef _PRE_WLAN_FEATURE_OFFLOAD_FLOWCTL
extern oal_void   hcc_host_update_vi_flowctl_param(oal_uint32 be_cwmin, oal_uint32 vi_cwmin);
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of frw_ext_if.h */
