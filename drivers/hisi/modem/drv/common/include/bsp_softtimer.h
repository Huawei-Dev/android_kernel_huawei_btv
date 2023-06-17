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
 * *	notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *	notice, this list of conditions and the following disclaimer in the
 * *	documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may 
 * *	be used to endorse or promote products derived from this software 
 * *	without specific prior written permission.
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

#ifndef __BSP_SOFTTIMER_H__
#define __BSP_SOFTTIMER_H__

#include <osl_common.h>
#include <osl_list.h>
#include <product_config.h>
#include <bsp_slice.h>
typedef void (*softtimer_func)(void*);
#define TIMER_TRUE 1
#define TIMER_FALSE 0
#define TIMER_INIT_FLAG	 0X5A5A5A5A

enum wakeup
{
	SOFTTIMER_WAKE,
	SOFTTIMER_NOWAKE
};
enum softtimer_cnt_type
{
	TYPE_MS,
	TYPE_S,
};
struct softtimer_list
{
	softtimer_func func;
	void* para;
	u32 timeout;
	enum wakeup wake_type;	
	const char* name;
	enum softtimer_cnt_type unit_type;
	bool emergency;	
	u32 run_cb_delta;
	u64 expect_cb_slice;
	struct list_head entry;
	u32 timer_id;
	u32 count_num;
	u32 is_running;
	u32 init_flags;
};

#ifdef CONFIG_MODULE_TIMER
int  bsp_softtimer_init(void);

s32 bsp_softtimer_create(struct softtimer_list *softtimer);

s32 bsp_softtimer_delete(struct softtimer_list * softtimer);

s32 bsp_softtimer_modify(struct softtimer_list * softtimer,u32 new_expire_time);

void bsp_softtimer_add(struct softtimer_list * timer);

s32 bsp_softtimer_free(struct softtimer_list *timer);

u32 check_softtimer_support_type(enum wakeup type);

#else
static inline int  bsp_softtimer_init(void) {return 0;}
static inline s32  bsp_softtimer_create(struct softtimer_list *softtimer) {return 0;}
static inline s32 bsp_softtimer_delete(struct softtimer_list * softtimer) {return 0;}
static inline s32 bsp_softtimer_modify(struct softtimer_list * softtimer,u32 new_expire_time) {return 0;}
static inline void bsp_softtimer_add(struct softtimer_list * timer) {}
static inline s32 bsp_softtimer_free(struct softtimer_list *timer) {return 0;}
static inline u32 check_softtimer_support_type(enum wakeup type){return 0;}

#endif
#endif
