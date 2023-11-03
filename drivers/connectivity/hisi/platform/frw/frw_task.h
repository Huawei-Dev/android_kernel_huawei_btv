#ifndef __FRW_TASK_H__
#define __FRW_TASK_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "oal_ext_if.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_FRW_TASK_H

typedef enum
{
    FRW_TASK_STATE_IRQ_UNBIND = 0,
    FRW_TASK_STATE_IRQ_BIND,

    FRW_TASK_BUTT
}frw_task_state_enum;

typedef oal_uint8 frw_task_state_enum_uint8;

#if (_PRE_FRW_FEATURE_PROCCESS_ENTITY_TYPE == _PRE_FRW_FEATURE_PROCCESS_ENTITY_THREAD)
typedef struct
{
    oal_task_stru               *pst_event_kthread;
    oal_wait_queue_head_stru     frw_wq;
    oal_uint8                    uc_task_state;
    oal_uint8                    auc_resv[3];
    oal_uint32                   ul_total_loop_cnt;
    oal_uint32                   ul_total_event_cnt;
    oal_uint32                   ul_max_empty_count;
    oal_void                    (*p_event_handler_func)(oal_void* _pst_bind_cpu);
}frw_task_stru;

#elif (_PRE_FRW_FEATURE_PROCCESS_ENTITY_TYPE == _PRE_FRW_FEATURE_PROCCESS_ENTITY_TASKLET)
typedef struct
{
    oal_tasklet_stru    st_event_tasklet;
    oal_void           (*p_event_handler_func)(oal_uint);
}frw_task_stru;
#endif

extern frw_task_stru g_ast_event_task[];

extern oal_uint32  frw_task_init(oal_void);
extern oal_void frw_task_exit(oal_void);
extern oal_void  frw_task_event_handler_register(oal_void (*p_func)(oal_uint));
extern oal_void frw_task_set_state(oal_uint32 ul_core_id, oal_uint8 uc_task_state);
extern oal_uint8 frw_task_get_state(oal_uint32 ul_core_id);
extern oal_void  frw_task_sched(oal_uint32 ul_core_id);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of frw_task.h */
