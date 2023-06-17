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
#ifndef __BSP_SLICE_H__
#define __BSP_SLICE_H__
#include <product_config.h>
#include <osl_bio.h>
#include <osl_types.h>

#define get_timer_slice_delta(begin,end) ((end>=begin)?(end-begin):(0xFFFFFFFF-begin+end))

#define print_stamp(addr) writel(bsp_get_slice_value(),addr)
#define print_stamp_hrt(addr) writel(bsp_get_slice_value_hrt(),addr)
#ifdef CONFIG_MODULE_TIMER
#ifndef __KERNEL__
void udelay(unsigned us);
#endif

u32 bsp_get_slice_value(void);

u32 bsp_get_slice_value_hrt(void);


u32 bsp_get_hrtimer_freq(void);

u32 bsp_get_elapse_ms(void);
void* bsp_get_stamp_addr(void);
void* bsp_get_stamp_addr_phy(void);
u32 bsp_slice_getcurtime(u64 *pcurtime);
u32 bsp_slice_getcurtime_hrt(u64 *pcurtime);
u32 bsp_get_slice_freq(void);
void slice_resume(void);
int bsp_slice_init(void);
void hrt_slice_resume(void);
#else
static inline int bsp_slice_init(void){return 0;}
static inline u32 bsp_get_slice_value(void){return 0;}
static inline u32 bsp_get_slice_value_hrt(void){return 0;}
static inline u32 bsp_get_elapse_ms(void){return 0;}
static inline void* bsp_get_stamp_addr(void){return NULL;}
static inline void* bsp_get_stamp_addr_phy(void){return NULL;}
static inline u32 bsp_slice_getcurtime(u64 *pcurtime){return 0;}
static inline u32 bsp_slice_getcurtime_hrt(u64 *pcurtime){return 0;}
static inline u32 bsp_get_slice_freq(void){return 32764;}
static inline void slice_resume(void){return;};
#ifndef __KERNEL__
static inline void udelay(unsigned us){return;}
#endif
static inline void hrt_slice_resume(void){return;}
#endif/*CONFIG_MODULE_TIMER*/
#endif/*__BSP_SLICE_H__*/
