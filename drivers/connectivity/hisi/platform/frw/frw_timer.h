#ifndef __FRW_TIMER_H__
#define __FRW_TIMER_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "frw_ext_if.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_FRW_TIMER_H

#define FRW_TIME_UL_MAX     (0xFFFFFFFF)
#define FRW_TIMER_MAX_TIMEOUT   (FRW_TIME_UL_MAX >> 1)

extern oal_uint32  frw_timer_timeout_proc(frw_event_mem_stru *pst_timeout_event);
extern oal_void  frw_timer_init(oal_uint32 ul_delay, oal_timer_func p_func, oal_uint ui_arg);
extern oal_void  frw_timer_exit(oal_void);
extern oal_void  frw_timer_timeout_proc_event(oal_uint ui_arg);
extern oal_void  frw_timer_restart(oal_void);
extern oal_void  frw_timer_stop(oal_void);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of frw_timer.h */
