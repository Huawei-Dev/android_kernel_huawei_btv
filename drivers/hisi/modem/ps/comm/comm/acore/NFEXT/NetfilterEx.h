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

#ifndef _NETFILTEREX_H_
#define _NETFILTEREX_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "v_id.h"
#include "vos.h"
#include "SysNvId.h"
#include "NVIM_Interface.h"
#include "NetWInterface.h"
#include "PsTypeDef.h"
#include "IpsMntn.h"
#include "omringbuffer.h"
#include "PsCommonDef.h"
#include "LinuxInterface.h"
#include "TtfNvInterface.h"

#ifndef __UT_CENTER__
#define NF_EXT_MEM_ALLOC(pid, size)                  kmalloc(size, GFP_ATOMIC)
#define NF_EXT_MEM_FREE(pid, p)                      kfree(p);
#else
#define NF_EXT_MEM_ALLOC(pid, size)                  PS_MEM_ALLOC(pid, size)
#define NF_EXT_MEM_FREE(pid, p)                      PS_MEM_FREE(pid, p);
#endif

#define NF_EXT_RING_BUF_SIZE                        (8192)
#define NF_TX_MSG_TASK_STACK_SIZE                   (32768)

#define DBG_ON                                      (1)
#define DBG_OFF                                     (0)

#define NF_EXT_DBG                                  DBG_ON

#if (FEATURE_ON == FEATURE_NFEXT)
#define NF_EXT_DEF_BR_ARP_HOOK_ON_MASK              (g_stExHookMask.ulBrArpHookValue)

#define NF_EXT_DEF_PRE_ROUTING_HOOK_ON_MASK         (g_stExHookMask.ulInHookValue)

#define NF_EXT_DEF_POST_ROUTING_HOOK_ON_MASK        (g_stExHookMask.ulOutHookValue)

#define NF_EXT_DEF_LOCAL_HOOK_ON_MASK               (g_stExHookMask.ulLocalHookValue)

#define NF_EXT_DEF_FLOW_CTRL_HOOK_ON_MASK           (g_stExHookMask.ulFlowCtrlHookValue)


#define NF_EXT_RPO_TCP                              (0x6)
#define MAC_HEADER_LENGTH                           (14)

#define NF_EXT_MAX_IP_SIZE                          (1500)

#define NF_EXT_BR_PRE_ROUTING_HOOK_ON_MASK          (1)
#define NF_EXT_BR_POST_ROUTING_HOOK_ON_MASK         (1 << 1)
#define NF_EXT_BR_FORWARD_HOOK_ON_MASK              (1 << 2)
#define NF_EXT_BR_LOCAL_IN_HOOK_ON_MASK             (1 << 3)
#define NF_EXT_BR_LOCAL_OUT_HOOK_ON_MASK            (1 << 4)
#define NF_EXT_ARP_LOCAL_IN_ON_MASK                 (1 << 5)
#define NF_EXT_ARP_LOCAL_OUT_ON_MASK                (1 << 6)
#define NF_EXT_IP4_PRE_ROUTING_HOOK_ON_MASK         (1 << 7)
#define NF_EXT_IP4_POST_ROUTING_HOOK_ON_MASK        (1 << 8)
#define NF_EXT_IP4_LOCAL_IN_HOOK_ON_MASK            (1 << 9)
#define NF_EXT_IP4_LOCAL_OUT_HOOK_ON_MASK           (1 << 10)
#define NF_EXT_IP4_FORWARD_HOOK_ON_MASK             (1 << 11)
#define NF_EXT_IP6_PRE_ROUTING_HOOK_ON_MASK         (1 << 12)
#define NF_EXT_IP6_POST_ROUTING_HOOK_ON_MASK        (1 << 13)
#define NF_EXT_IP6_LOCAL_IN_HOOK_ON_MASK            (1 << 14)
#define NF_EXT_IP6_LOCAL_OUT_HOOK_ON_MASK           (1 << 15)
#define NF_EXT_IP6_FORWARD_HOOK_ON_MASK             (1 << 16)
#define NF_EXT_BR_FORWARD_FLOW_CTRL_HOOK_ON_MASK    (1 << 17)

#define NF_EXT_BR_FORWARD_FLOW_CTRL_MASK            (1U)

#define NF_EXT_BR_NAME                              "br0"

#define NF_EXT_TX_BYTES_INC(a, b)                   (g_stExFlowCtrlEntity.aulTxBytesCnt[b] += a)
#endif

enum NF_EXT_FLAG_OM_DATA_ENUM
{
    NF_EXT_FLAG_OM_DATA                = 0,
    NF_EXT_FLAG_NOT_OM_DATA            = 1,

    NF_EXT_FLAG_OM_DATA_BUTT
};
typedef int NF_EXT_FLAG_OM_DATA_ENUM_U32;

enum NF_EXT_FLAG_BLOCK_ENUM
{
    NF_EXT_FLAG_BLOCKED                = 0,
    NF_EXT_FLAG_UNBLOCKED              = 1,

    NF_EXT_FLAG_BUTT
};

enum NF_EXT_TX_BYTES_CNT_ENUM
{
    NF_EXT_TX_BYTES_CNT_BR             = 0,
    NF_EXT_TX_BYTES_CNT_BUTT
};

#if(NF_EXT_DBG == DBG_ON)
enum NF_EXT_STATS_ENUM
{
    NF_EXT_STATS_BR_FC_DROP            = 0,
    NF_EXT_STATS_BR_FC_ENTER,
    NF_EXT_STATS_BUF_FULL_DROP,
    NF_EXT_STATS_PUT_BUF_FAIL,
    NF_EXT_STATS_ALLOC_MEM_FAIL,
    NF_EXT_STATS_GET_BUF_FAIL,

    NF_EXT_STATS_BUT
};
#endif

typedef struct
{
    VOS_UINT32                      ulIsBlkflag;
    VOS_UINT32                      ulCurHookOnMask;
    VOS_UINT32                      ulIsDeviceOpen ;
    VOS_UINT32                      ulOmIp;
    OM_RING_ID                      pRingBufferId;
    wait_queue_head_t               stWaitHeadTxTask;
    spinlock_t                      stLockTxTask;
    VOS_UINT8                       aucRsv2[4];
}NF_EXT_ENTITY_STRU;

typedef struct
{
    VOS_UINT16   usDataLen;
    VOS_UINT8    aucRsv[6];
    VOS_UINT8   *pData;
}NF_EXT_DATA_RING_BUF_STRU;

#if (FEATURE_ON == FEATURE_NFEXT)
typedef struct
{
    u_int32_t                       ulHookMask;
    VOS_UINT8                       aucRsv[4];
    struct nf_hook_ops              stNfExtOps;
} NF_EXT_MASK_OPS_STRU;

typedef struct
{
    VOS_UINT32         ulFlowCtrlMsk;
    VOS_UINT32         aulTxBytesCnt[NF_EXT_TX_BYTES_CNT_BUTT];
    struct net_device *pstBrDev;
}NF_EXT_FLOW_CTRL_ENTITY;

typedef struct
{
    VOS_UINT32          ulBrArpHookValue;
    VOS_UINT32          ulInHookValue;
    VOS_UINT32          ulOutHookValue;
    VOS_UINT32          ulFlowCtrlHookValue;
    VOS_UINT32          ulLocalHookValue;
    VOS_UINT32          ulRsv;
}NF_EXT_HOOK_MASK_NV_STRU;
#endif

#if(NF_EXT_DBG == DBG_ON)
typedef struct
{
    VOS_UINT32  aulStats[NF_EXT_STATS_BUT];
}NF_EXT_STATS_STRU;
#endif

#if(NF_EXT_DBG == DBG_ON)
extern NF_EXT_STATS_STRU g_stNfExtStats;

#define NF_EXT_STATS_INC(a, b)                      (g_stNfExtStats.aulStats[b] += a)
#else
#define NF_EXT_STATS_INC(a, b)                      do{}while(0)
#endif

#if (FEATURE_ON == FEATURE_NFEXT)
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 1, 0))
extern unsigned int NFExt_BrPreRoutingHook(const struct nf_hook_ops *ops,
                                    struct sk_buff *skb,
                                    const struct nf_hook_state *state);

extern unsigned int NFExt_BrPostRoutingHook(const struct nf_hook_ops *ops,
                                    struct sk_buff *skb,
                                    const struct nf_hook_state *state);


extern unsigned int NFExt_BrLocalInHook(const struct nf_hook_ops *ops,
                                    struct sk_buff *skb,
                                    const struct nf_hook_state *state);

extern unsigned int NFExt_BrLocalOutHook(const struct nf_hook_ops *ops,
                                    struct sk_buff *skb,
                                    const struct nf_hook_state *state);

extern unsigned int NFExt_BrForwardHook(const struct nf_hook_ops *ops,
                                    struct sk_buff *skb,
                                    const struct nf_hook_state *state);

extern unsigned int NFExt_ArpInHook(const struct nf_hook_ops *ops,
                                    struct sk_buff *skb,
                                    const struct nf_hook_state *state);

extern unsigned int NFExt_ArpOutHook(const struct nf_hook_ops *ops,
                                    struct sk_buff *skb,
                                    const struct nf_hook_state *state);

extern unsigned int NFExt_Ip4PreRoutingHook(const struct nf_hook_ops *ops,
                                    struct sk_buff *skb,
                                    const struct nf_hook_state *state);

extern unsigned int NFExt_Ip4PostRoutingHook(const struct nf_hook_ops *ops,
                                    struct sk_buff *skb,
                                    const struct nf_hook_state *state);

extern unsigned int NFExt_Ip4LocalInHook(const struct nf_hook_ops *ops,
                                    struct sk_buff *skb,
                                    const struct nf_hook_state *state);

extern unsigned int NFExt_Ip4LocalOutHook(const struct nf_hook_ops *ops,
                                    struct sk_buff *skb,
                                    const struct nf_hook_state *state);

extern unsigned int NFExt_Ip4ForwardHook(const struct nf_hook_ops *ops,
                                    struct sk_buff *skb,
                                    const struct nf_hook_state *state);

extern unsigned int NFExt_Ip6PreRoutingHook(const struct nf_hook_ops *ops,
                                    struct sk_buff *skb,
                                    const struct nf_hook_state *state);

extern unsigned int NFExt_Ip6PostRoutingHook(const struct nf_hook_ops *ops,
                                    struct sk_buff *skb,
                                    const struct nf_hook_state *state);

extern unsigned int NFExt_Ip6LocalInHook(const struct nf_hook_ops *ops,
                                    struct sk_buff *skb,
                                    const struct nf_hook_state *state);

extern unsigned int NFExt_Ip6LocalOutHook(const struct nf_hook_ops *ops,
                                    struct sk_buff *skb,
                                    const struct nf_hook_state *state);

extern unsigned int NFExt_Ip6ForwardHook(const struct nf_hook_ops *ops,
                                    struct sk_buff *skb,
                                    const struct nf_hook_state *state);

extern unsigned int NFExt_BrForwardFlowCtrlHook(const struct nf_hook_ops *ops,
                                    struct sk_buff *skb,
                                    const struct nf_hook_state *state);

#else
extern unsigned int NFExt_BrPreRoutingHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_BrPostRoutingHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));


extern unsigned int NFExt_BrLocalInHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_BrLocalOutHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_BrForwardHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_ArpInHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_ArpOutHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_Ip4PreRoutingHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_Ip4PostRoutingHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_Ip4LocalInHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_Ip4LocalOutHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_Ip4ForwardHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_Ip6PreRoutingHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_Ip6PostRoutingHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_Ip6LocalInHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_Ip6LocalOutHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_Ip6ForwardHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_BrForwardFlowCtrlHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));
#endif
extern VOS_UINT32 NFExt_SaveBrDev(VOS_VOID);

extern VOS_VOID NFExt_FlowCtrlInit(VOS_VOID);
extern NF_EXT_FLAG_OM_DATA_ENUM_U32 NFExt_IsOmData(struct sk_buff *skb);
extern VOS_VOID NFExt_BrDataExport( struct sk_buff *skb,
                                const struct net_device *device_in,
                                const struct net_device *device_out,
                                TTF_MNTN_MSG_TYPE_ENUM_UINT16 enType);
extern VOS_VOID NFExt_ArpDataExport( struct sk_buff *skb,
                                const struct net_device *device,
                                TTF_MNTN_MSG_TYPE_ENUM_UINT16 enType);
extern VOS_VOID NFExt_IpDataExport( struct sk_buff *skb,
                         const struct net_device *device,
                         TTF_MNTN_MSG_TYPE_ENUM_UINT16 enType);

extern VOS_VOID  NFExt_UnregHooks(VOS_UINT32 ulMask);
extern VOS_INT  NFExt_RegHooks(VOS_UINT32 ulMask);
extern VOS_INT  NFExt_ReRegHooks(VOS_UINT32 ulMask);
extern VOS_UINT32  NFExt_Get1stInetIpv4Addr(struct net_device *pstDev);
extern PS_BOOL_ENUM_UINT8 NFExt_ConfigEffective(IPS_MNTN_TRACE_CONFIG_REQ_STRU *pRcvMsg);
extern VOS_UINT32 NFExt_ReadNvCfg(VOS_VOID);
extern VOS_VOID NFExt_SetDefaultNvCfg(VOS_VOID);
extern VOS_VOID NFExt_EntityInit(VOS_VOID);
extern VOS_INT NFExt_Init(VOS_VOID);
extern void NFExt_Uninit(VOS_VOID);
extern VOS_VOID  NFExt_BrSetFlowCtrl(VOS_VOID);
extern VOS_VOID  NFExt_BrStopFlowCtrl(VOS_VOID);
extern VOS_UINT32 NFExt_GetBrBytesCnt(VOS_VOID);

#if(NF_EXT_DBG == DBG_ON)
extern VOS_VOID NFExt_StatsShow(VOS_VOID);
extern VOS_VOID NFExt_ResetPri(VOS_UINT32 ulHookNode, VOS_INT32 iPri);
#endif

#endif
extern VOS_UINT32 NFExt_AddDataToRingBuf(NF_EXT_DATA_RING_BUF_STRU *pstMsg);
extern VOS_VOID NFExt_RcvNfExtInfoCfgReq(VOS_VOID *pMsg);
extern VOS_VOID NFExt_SelfTaskInit(VOS_VOID);
extern VOS_INT NFExt_RingBufferPut( OM_RING_ID rngId, VOS_CHAR *buffer, VOS_INT nbytes );
extern VOS_INT NFExt_RingBufferGet( OM_RING_ID rngId, VOS_CHAR *buffer, VOS_INT maxbytes );
extern VOS_VOID NFExt_FlushRingBuffer(OM_RING_ID rngId);
extern VOS_VOID NFExt_CtrlTxMsgTask(VOS_VOID);
extern VOS_VOID NFExt_RcvOmMsg(VOS_VOID *pMsg);
extern VOS_VOID NFExt_MsgProc( struct MsgCB * pMsg );
extern VOS_UINT32 NFExt_PidInit( enum VOS_INIT_PHASE_DEFINE ip );

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
