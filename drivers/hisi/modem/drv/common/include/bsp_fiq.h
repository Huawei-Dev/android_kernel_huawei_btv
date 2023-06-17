#ifndef _BSP_FIQ_H
#define _BSP_FIQ_H

#include <product_config.h>
#include <drv_comm.h>
#include <bsp_shared_ddr.h>
#include <bsp_slice.h>
#include <osl_bio.h>
#ifdef   __OS_RTOSCK__
#include <sre_exc.h>
#endif
#define SHM_FIQ_BASE_ADDR                              (SHM_OFFSET_CCORE_FIQ + (unsigned long)SHM_BASE_ADDR)
#define SHM_FIQ_BARRIER                	               (SHM_FIQ_BASE_ADDR)
#define SHM_FIQ_STATUS_ADDR                          (SHM_FIQ_BARRIER + (unsigned long)0x4)
#define SHM_FIQ_CLEAR_ADDR                             (SHM_FIQ_STATUS_ADDR + (unsigned long)0x4)
#define SHM_FIQ_CP_TIMER_ADDR                       (SHM_FIQ_CLEAR_ADDR + (unsigned long)0x4)
#define SHM_FIQ_TOTAL_SEND_CNT                    (SHM_FIQ_CP_TIMER_ADDR + (unsigned long)0x4)
#define SHM_FIQ_TOTAL_RECIVE_CNT                  (SHM_FIQ_TOTAL_SEND_CNT + (unsigned long)0x4)
#define SHM_FIQ_INFO_ADDR                               (SHM_FIQ_TOTAL_RECIVE_CNT + (unsigned long)0x4)

#define FIQ_TRIGGER_TAG                     		 (0xFFFFFFF0)

typedef enum __fiq_num
{
	FIQ_RESET = 0,
	FIQ_DUMP,
	FIQ_MAX
}fiq_num;

enum fiq_handler_return_value
{
	FIQ_RETURN_RUNNING = 0,
	FIQ_ENTER_LOOP_1_NO_RETRUN = 1,
	FIQ_ENTER_WFE_NO_RETRUN =  2
};

typedef int (* FIQ_PROC_FUNC)(void *);

#ifdef   __OS_RTOSCK__

int request_fiq(fiq_num fiq_num_t, FIQ_PROC_FUNC pfnHandler,void * uwArg);

int free_fiq(fiq_num fiq_num_t);

 UINT32 fiq_handler(EXC_INFO_S *pstExcInfo);
#elif defined __KERNEL__

int bsp_send_cp_fiq(fiq_num fiq_num_t);
#endif
#endif
