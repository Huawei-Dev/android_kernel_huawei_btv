/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and 
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may 
 * *    be used to endorse or promote products derived from this software 
 * *    without specific prior written permission.
 * 
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */
#ifndef _BSP_IPC_H_
#define _BSP_IPC_H_
#ifdef __ASSEMBLY__
#include <bsp_memmap.h>

#else

#include <product_config.h>
#include <osl_common.h>
#include <mdrv_ipc.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef void  (*voidfuncptr)(u32);
#define IPC_ERR_MODEM_RESETING 1
#define MODEM_RESET_HWLOCK_ID 10
#define  IPC_CPU_RAW_INT_M3   0x420

struct ipc_entry
{
 	voidfuncptr routine;
	u32	arg;
} ;

#define INTSRC_NUM                     32

#ifdef CONFIG_MODULE_IPC

int bsp_ipc_init(void);

s32 bsp_ipc_sem_create(u32 u32SignalNum);


s32 bsp_ipc_sem_delete(u32 u32SignalNum);

s32 bsp_ipc_int_enable(IPC_INT_LEV_E ulLvl);


s32 bsp_ipc_int_disable(IPC_INT_LEV_E ulLvl);

s32 bsp_ipc_int_connect(IPC_INT_LEV_E ulLvl, voidfuncptr routine, u32 parameter);

s32 bsp_ipc_int_disconnect(IPC_INT_LEV_E ulLvl,voidfuncptr routine, u32 parameter);

s32 bsp_ipc_int_send(IPC_INT_CORE_E enDstCore, IPC_INT_LEV_E ulLvl);

s32 bsp_ipc_sem_take(u32 u32SignalNum,s32 s32timeout);

s32 bsp_ipc_sem_give(u32 u32SignalNum);

s32 bsp_ipc_spin_lock (u32 u32SignalNum);

s32 bsp_ipc_spin_trylock (u32 u32SignalNum);

s32 bsp_ipc_spin_unlock (u32 u32SignalNum);

s32 bsp_ipc_spin_lock_timeout_irqsave(unsigned int u32SignalNum, unsigned int TimeoutMs, unsigned long *flags);

#define bsp_ipc_spin_lock_irqsave(u32SignalNum,flags)  \
	do{local_irq_save(flags);(void)bsp_ipc_spin_lock(u32SignalNum);}while(0)

#define bsp_ipc_spin_unlock_irqrestore(u32SignalNum,flags) \
	do{(void)bsp_ipc_spin_unlock(u32SignalNum);local_irq_restore(flags);}while(0)
#else
static inline s32 bsp_ipc_init(void) {return 0;}
static inline s32 bsp_ipc_sem_create(u32 u32SignalNum) {return 0;}
static inline s32 bsp_ipc_sem_delete(u32 u32SignalNum) {return 0;}
static inline s32 bsp_ipc_int_enable(IPC_INT_LEV_E ulLvl) {return 0;}
static inline s32 bsp_ipc_int_disable(IPC_INT_LEV_E ulLvl) {return 0;}
static inline s32 bsp_ipc_int_connect(IPC_INT_LEV_E ulLvl, voidfuncptr routine, u32 parameter) {return 0;}
static inline s32 bsp_ipc_int_disconnect(IPC_INT_LEV_E ulLvl,voidfuncptr routine, u32 parameter) {return 0;}
static inline s32 bsp_ipc_int_send(IPC_INT_CORE_E enDstCore, IPC_INT_LEV_E ulLvl) {return 0;}
static inline s32 bsp_ipc_sem_take(u32 u32SignalNum,s32 s32timeout) {return 0;}
static inline s32 bsp_ipc_sem_give(u32 u32SignalNum) {return 0;}
static inline s32 bsp_ipc_spin_lock (u32 u32SignalNum) {return 0;}
static inline s32 bsp_ipc_spin_trylock(u32 u32SignalNum) {return 0;}
static inline s32 bsp_ipc_spin_unlock (u32 u32SignalNum) {return 0;}
static inline s32 bsp_ipc_spin_lock_timeout_irqsave(unsigned int u32SignalNum, unsigned int TimeoutMs, unsigned long *flags); {return 0;}
#define bsp_ipc_spin_lock_irqsave(u32SignalNum,flags)  \
	do{flags = flags;}while(0)
#define bsp_ipc_spin_unlock_irqrestore(u32SignalNum,flags) \
	do{flags = flags;}while(0)

static inline void bsp_ipc_suspend(void){return ;}

static inline void bsp_ipc_resume(void){return ;}
#endif

void bsp_int_send_info(void);
#ifdef __CMSIS_RTOS

void bsp_ipc_suspend(void);

void bsp_ipc_resume(void);
#endif

#ifdef __cplusplus
}
#endif

#endif /*#ifdef __ASSEMBLY__*/

#endif /* end #define _BSP_IPC_H_*/
