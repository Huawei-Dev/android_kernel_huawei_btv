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

#ifndef _NVIM_MSG_H
#define _NVIM_MSG_H
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "osl_types.h"
#include "osl_list.h"
#include "osl_sem.h"
#include "osl_spinlock.h"
#include "bsp_nvim.h"

typedef u32 (*nv_cb_func)(u32 ret, u32 sn);

/*????????Nv????*/
typedef struct _nv_item_info_stru_
{
    u16 itemid;        /* NV ID */
    u16 modem_id;      /* NV Length */
}nv_item_info_t;

/*AP Nv??????????????*/
typedef struct _nv_cmd_req_
{
    struct list_head    stList;
    u8                 reserved[2];
    u8                 priority;
    u8                 msg_type;                   /* msg type */
    u32                 sn;                         /* ?????? */
    nv_item_info_t      nv_item_info;               /* nv?????? */
    nv_cb_func          nv_msg_callback;
}nv_cmd_req;

/* ???????? */
typedef struct _nv_cmd_reply_
{
    struct list_head    stList;     /* ???????? */
    u32                 sn;         /*sn??????????????????*/
    osl_sem_id          sem_req;    /* ?????????????? */
    u32                 ret;        /* ????????*/
}nv_cmd_reply;


enum _task_msg_type_e_
{
    NV_TASK_MSG_WRITE2FILE      = 0x1,     /*??NV????*/
    NV_TASK_MSG_FLUSH           = 0x2,     /* flush request */
    NV_TASK_MSG_RESUEM          = 0x3,     /*resume ????*/
    NV_TASK_MSG_UPDATE_BACKUP   = 0x4,     /*????????????????*/
    NV_TASK_MSG_UPDATE_FACTORY  = 0x5,     /*????????????????*/
    NV_TASK_MSG_RESET_FROM_FACTORY  = 0x6,     /*????????????*/
    NV_TASK_MSG_REVERT_FROM_BAK     = 0x7,      /*??????????????????*/
    NV_TASK_MSG_RESUEM_ITEM         = 0x8,     /*resume single nv ????*/    
    NV_TASK_MSG_BUTT,
};

/*icc msg type*/
enum _icc_msg_e_
{
    NV_ICC_REQ_PRIORITY_HIGH_FLUSH      = 0x40,             /*ccore????????????,????????????*/
    NV_ICC_REQ_PRIORITY1_FLUSH          = 0x41,         /*ccore ????????????????????????????*/
    NV_ICC_REQ_PRIORITY_MID_LOW_FLUSH   = 0x42,
    NV_ICC_REQ_SHUT_DOWN_FLUSH          = 0x43,         /*ccore ??????????????*/
    NV_ICC_REQ_RESUME                   = 0x44,         /*????????DDR????nv????*/
    NV_ICC_REQ_RESUME_ITEM              = 0x45,         /*????????DDR????nv????????*/
    NV_ICC_CNF                          = 127,
    NV_ICC_BUTT                         = 0xFF,
};

#define    HIGH_PRIORITY_MSG_QUEUE       1
#define    LOW_PRIORITY_MSG_QUEUE        2


/*ICC????NV_ICC_REQ_RESUME NV_ICC_REQ_RESUME????????*/
typedef struct _nv_icc_msg_stru_
{
    u32 send_slice;         /*????????*/
    u32 msg_type;           /*????????*/
    u32 sn;                 /*??????*/
    u32 ret;                /*??????????????????????NV????,??????????????????????*/
}nv_icc_msg_t;

/*ICC????NV_ICC_REQ_PRIORITY_HIGH_FLUSH NV_ICC_REQ_PRIORITY1_FLUSH????????*/
typedef struct _nv_icc_msg_single_stru_
{
    u32 send_slice;         /*????????*/
    u32 msg_type;           /*????????*/
    u32 sn;                 /*??????*/
    u32 ret;                /*??????????????????????NV????,??????????????????????*/
    nv_item_info_t data;    /*????????nv????????*/
}nv_icc_msg_single_t;

typedef struct _msg_queue_stru_
{
    struct list_head list;
    spinlock_t         lock;                     /*????????list????????*/
}msg_queue_t;

struct nv_global_msg_info_stru {
    msg_queue_t req_list;             /* ???????????????? */
    msg_queue_t high_task_list;     /* ????????NV???????????? */
    msg_queue_t low_task_list;      /* ????????NV???????????? */
    u32         req_sn;

    osl_sem_id           flush_sem;
    nv_flush_list       *flush_info;

    int icc_cb_count;
    int icc_cb_reply;
    int sync_wr_count;
    int sync_wr_done_count;
    int async_wr_count;
    int wr_timeout_count;
    int remote_wr_count;
};

s32 nv_handle_icc_rmsg(u32 chanid, u32 len, void* pdata);
u32 nv_send_msg_sync(u32 msgtype, u32 itemid, u32 modem_id);
u32 nv_send_msg_async(u32 msgtype, u32 itemid, u32 modem_id);
u32 nv_add_wrbuf(struct nv_global_ddr_info_stru* ddr_info, u32 itemid, u32 modem_id, u32 priority);
nv_cmd_req* nv_get_cmd_req(void);
int nv_put_cmd_req(nv_cmd_req* pNvCmdReq);
u32 nv_flush_wrbuf(struct nv_global_ddr_info_stru* ddr_info);

int nv_msg_init(void);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif

/* vim set ts=4 sw=4 */

