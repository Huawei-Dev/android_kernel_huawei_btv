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

#ifndef ICC_BALONG_CORE_H
#define ICC_BALONG_CORE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "icc_platform.h"

extern struct icc_dbg g_icc_dbg;

#ifndef BSP_ERR_ICC_BASE
#define BSP_ERR_ICC_BASE                ((int)(0x80000000 | 0x10180000))
#endif

#ifndef BSP_ERR_ICC_CCORE_RESETTING
#define BSP_ERR_ICC_CCORE_RESETTING    (BSP_ERR_ICC_BASE + 0x12)
#endif

#define icc_safe_free(p) \
do \
{ \
	if(p) \
	{ \
		osl_free((void *)p); \
		p = NULL; \
	} \
} \
while(0)

#define ICC_MIN(x, y)             ((x) < (y) ? (x) : (y))
#define GET_CHN_ID(channel_id)    (((channel_id)>>16) & 0xffff)
#define GET_FUNC_ID(channel_id)   ((channel_id) & 0xffff)

#define ICC_CHN_MAGIC_SIGN    (0x87651234)
#define ICC_CHN_MAGIC_UNSIGN  (0xabcd8765)


#define PRIVATE_MODE          ((ICC_TASK_PRIVATE << 1) |(ICC_IPC_PRIVATE))
#define SHARED_MODE           ((ICC_TASK_SHARED << 1) |(ICC_IPC_SHARED))

#define ICC_SDDR_ADDR_MAX      (SHM_ADDR_ICC + SHM_SIZE_ICC)
#define ICC_SRAM_ADDR_MAX      (SRAM_ADDR_ICC + SRAM_SIZE_ICC)
#define ICC_SDDR_S_ADDR_MAX    (SHM_S_ADDR_ICC + SHM_S_SIZE_ICC)

#define ICC_SEM_FULL          (1)
#define ICC_SEM_EMPTY         (0)

struct icc_init_info
{
	u32        real_channel_id;
	u32        mode;
	u32        fifo_size;
	char*      recv_addr;
	char*      send_addr;	
	u32        ipc_recv_irq_id;
	u32        ipc_send_irq_id;
	u32        func_size;
	const char *name;
};

enum ICC_STATUS
{
	ICC_UNINITIALIZED = 0,
	ICC_INITIALIZED,
	ICC_STATUS_MAX
};

enum ICC_TASK_TYPE
{
	ICC_TASK_PRIVATE = 0,
	ICC_TASK_SHARED,
	ICC_TASK_TYPE_MAX
};

enum IPC_VEC_TYPE
{
	ICC_IPC_PRIVATE = 0,
	ICC_IPC_SHARED,
	IPC_VEC_TYPE_MAX
};

enum ICC_HAS_TASK
{
	ICC_HAS_TASK = 0,
	ICC_NO_TASK,
	ICC_TASK_MAX
};

enum ICC_CHN_STAT
{
	ICC_CHN_CLOSED = 0,
	ICC_CHN_OPENED,
	ICC_CHN_STAT_MAX
};

enum ICC_PACKET_RETURN
{
	ICC_PACKET_NONEED_RESPONSE = 0,
	ICC_PACKET_NEED_RESPONSE,
	ICC_PACKET_RETURN_MAX
};

union ipc_task_shared
{
	u32 val;
	struct
	{
		u32 ipc_shared :1;
		u32 task_shared:1;
		u32 no_task    :1;
		u32 reserved   :29;
	}union_stru;
};

struct icc_channel
{
	u32                       id;
	const char                *name;
	u32                       state;
	u32                       ready_recv;
	union ipc_task_shared     mode;
	icc_task_id               private_task_id;
	u32                       ipc_send_irq_id;
	u32                       ipc_recv_irq_id;
	osl_sem_id                private_task_sem;
	struct icc_channel_fifo   *fifo_recv;
	struct icc_channel_fifo   *fifo_send;
	spinlock_t                write_lock;
	spinlock_t                read_lock;
	struct icc_channel_vector *vector;
	u32                       func_size;
};

struct channel_cfg{
    unsigned int id;
	unsigned int mode;
	unsigned int size;
	unsigned int tx_ipc;
	unsigned int rx_ipc;
	unsigned int func_size;
	unsigned int rx_fifo_first;
};

struct icc_wait_data
{
	u32 channel_id;
	u32 packet_seq_num;
};

enum ICC_MSG_TYPE
{
	ICC_MSG_SEND = 0,
	ICC_MSG_RECV,
	ICC_MSG_TYPE_MAX
};

#define ICC_MSG_RECORED_DATA_LEN  40
#define ICC_STAT_MSG_NUM          10
struct icc_uni_msg_info
{
	u32 channel_id;
	u32 send_task_id;
	u32 recv_task_id;
	u32 len;
	u32 write_pos;
	u32 read_pos;
	u32 duration_prev;
	u32 duration_post;
	u8 data[ICC_MSG_RECORED_DATA_LEN];       
};

struct icc_debug_perf
{
    u32 max_readcb_consume_slice;
	u32 max_readcb_channel_id;
	u32 cnt;
	u32 sum;
	u32 avg;
};

struct icc_recv_msg_info
{
	u32 channel_id;
	u32 send_task_id;
	u32 recv_task_id;
	u32 len;
	u32 write_pos;
	u32 read_pos;
	u32 before_recv_slice;
	u32 in_read_cb_slice;
	u32 after_recv_slice;
	struct icc_debug_perf perf;
};

struct icc_msg_fifo
{
	u32 front;
	u32 rear;
	u32 size;
	struct icc_uni_msg_info msg[ICC_STAT_MSG_NUM];
};

struct icc_msg_fifo_recv
{
	u32 front;
	u32 rear;
	u32 size;
	struct icc_recv_msg_info msg[ICC_STAT_MSG_NUM];
};

struct icc_msg_info
{
	struct icc_msg_fifo send;
	struct icc_msg_fifo_recv recv;
};

struct icc_channel_stat_info
{
	u32 sum_len;
	u32 sum_num;
	u32 sum_num_prev;
	u32 task_id;
};

struct icc_uni_channel_info
{
	struct icc_channel_stat_info total;
	struct icc_channel_stat_info *sub_chn;
	u32 func_size;
};

struct icc_channel_info
{
	u32 id;
	struct icc_uni_channel_info send;
	struct icc_uni_channel_info recv;
};

struct icc_dbg
{
	u32 state;
	u32 ipc_int_cnt;
	u32 msg_print_sw;
	u32 send_cpu_id;
	u32 recv_task_id;
	u32 timestamp;
	char *dump_buf_addr;
	u32 dump_buf_size;
    u32 reserved; /* for 8byte allignment */
	struct icc_msg_info msg_stat;
	struct icc_channel_info *channel_stat[ICC_CHN_ID_MAX];
};

void icc_sleep_flag_set(void);
u32 fifo_get(struct icc_channel_fifo *fifo, u8 *data_buf, u32 data_len, u32 *read);
void icc_restore_recv_channel_flag(struct icc_channel_fifo * channel_fifo);
s32 icc_channel_has_data(void);
void icc_shared_sem_init(void);
void icc_private_sem_init(osl_sem_id *private_sem);
int icc_shared_task_init(void);
void icc_task_shared_func(void const *obj);
void icc_ipc_isr(u32 data);
struct icc_channel *icc_channel_init(struct icc_init_info *info, s32 *ret);

#ifdef __cplusplus
}
#endif

#endif
