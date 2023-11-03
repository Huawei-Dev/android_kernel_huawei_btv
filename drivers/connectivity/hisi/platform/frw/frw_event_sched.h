#ifndef __FRW_EVENT_SCHED_H__
#define __FRW_EVENT_SCHED_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "oal_ext_if.h"
#include "frw_main.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_FRW_EVENT_SCHED_H

#define FRW_EVENT_QUEUE_GET_PENDING_EVENTS_NUM(_pst_event_queue)    oal_queue_get_length(&(_pst_event_queue)->st_queue)

typedef enum
{
    FRW_SCHED_POLICY_HI     = 0,
    FRW_SCHED_POLICY_NORMAL = 1,

    FRW_SCHED_POLICY_BUTT
}frw_sched_policy_enum;
typedef oal_uint8 frw_sched_policy_enum_uint8;

typedef enum
{
    FRW_EVENT_QUEUE_STATE_INACTIVE = 0,
    FRW_EVENT_QUEUE_STATE_ACTIVE,

    FRW_EVENT_QUEUE_STATE_BUTT
}frw_event_queue_state_enum;
typedef oal_uint8 frw_event_queue_state_enum_uint8;

typedef enum
{
    FRW_VAP_STATE_RESUME  = 0,
    FRW_VAP_STATE_PAUSE,

    FRW_VAP_STATE_BUTT
}frw_vap_state_enum;
typedef oal_uint8 frw_vap_state_enum_uint8;

typedef struct
{
    oal_spin_lock_stru                   st_lock;
    oal_uint32                           ul_total_weight_cnt;
    oal_dlist_head_stru                  st_head;
}frw_event_sched_queue_stru;

typedef struct tag_frw_event_queue_stru
{
    oal_spin_lock_stru                  st_lock;
    oal_queue_stru                      st_queue;
    frw_event_queue_state_enum_uint8    en_state;
    frw_sched_policy_enum_uint8         en_policy;

    oal_uint8                           uc_weight;
    oal_uint8                           uc_weight_cnt;

    frw_vap_state_enum_uint8            en_vap_state;
    oal_uint8                           auc_resv[3];

    oal_dlist_head_stru                 st_list;
}frw_event_queue_stru;

extern oal_uint32  frw_event_sched_init(frw_event_sched_queue_stru *pst_sched_queue);
extern oal_uint32  frw_event_queue_init(
                frw_event_queue_stru               *pst_event_queue,
                oal_uint8                           uc_weight,
                frw_sched_policy_enum_uint8         en_policy,
                frw_event_queue_state_enum_uint8    en_state,
                oal_uint8                           uc_max_events);
extern oal_void  frw_event_queue_destroy(frw_event_queue_stru *pst_event_queue);
extern oal_void* frw_event_sched_pick_next_event_queue_wrr(frw_event_sched_queue_stru *pst_sched_queue);
extern oal_uint32  frw_event_sched_deactivate_queue(
                frw_event_sched_queue_stru         *pst_sched_queue,
                frw_event_queue_stru               *pst_event_queue);

extern oal_uint32  frw_event_sched_activate_queue(
                frw_event_sched_queue_stru   *pst_sched_queue,
                frw_event_queue_stru         *pst_event_queue);

extern oal_void  frw_event_sched_pause_queue(
                frw_event_sched_queue_stru   *pst_sched_queue,
                frw_event_queue_stru         *pst_event_queue);
extern oal_void  frw_event_sched_resume_queue(
                frw_event_sched_queue_stru   *pst_sched_queue,
                frw_event_queue_stru         *pst_event_queue);

OAL_STATIC OAL_INLINE oal_void  frw_event_sched_reset_weight(frw_event_sched_queue_stru *pst_sched_queue)
{
    oal_dlist_head_stru    *pst_list;
    frw_event_queue_stru   *pst_event_queue;

    OAL_DLIST_SEARCH_FOR_EACH(pst_list, &pst_sched_queue->st_head)
    {
        pst_event_queue = OAL_DLIST_GET_ENTRY(pst_list, frw_event_queue_stru, st_list);

        if(FRW_VAP_STATE_RESUME == pst_event_queue->en_vap_state)
        {
            pst_event_queue->uc_weight_cnt = pst_event_queue->uc_weight;

            pst_sched_queue->ul_total_weight_cnt += pst_event_queue->uc_weight;
        }
    }
}

OAL_STATIC OAL_INLINE oal_void* frw_event_schedule(frw_event_sched_queue_stru *pst_sched_queue)
{
    oal_void                     *p_event;
    frw_event_sched_queue_stru   *pst_queue;

    pst_queue = &pst_sched_queue[FRW_SCHED_POLICY_HI];

    if (!oal_dlist_is_empty(&pst_queue->st_head))
    {
    	p_event = frw_event_sched_pick_next_event_queue_wrr(pst_queue);

    	if (p_event)
    	{
    	    return p_event;
    	}
    }

    pst_queue = &pst_sched_queue[FRW_SCHED_POLICY_NORMAL];

    if (!oal_dlist_is_empty(&pst_queue->st_head))
    {
    	p_event = frw_event_sched_pick_next_event_queue_wrr(pst_queue);

    	if (p_event)
    	{
    	    return p_event;
    	}
    }

    return OAL_PTR_NULL;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of frw_event_sched.h */
