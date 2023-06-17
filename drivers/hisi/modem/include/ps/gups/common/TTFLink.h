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

#ifndef __TTF_LINK_H_
#define __TTF_LINK_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "vos.h"
#include "PsTypeDef.h"
#include "PsLib.h"
#include "TtfLinkInterface.h"

#define TTF_LINK_CNT(pLink)           ((pLink)->ulCnt)

#define TTF_LINK_INIT_NODE(pstNode)     \
{\
    (pstNode)->pPrev    = VOS_NULL_PTR; \
    (pstNode)->pNext    = VOS_NULL_PTR; \
}

#pragma pack(4)

typedef struct
{
    TTF_NODE_ST             stHead;
    VOS_UINT32              ulCnt;
} TTF_LINK_ST;

typedef struct
{
    VOS_VOID*              *ppNode;
    VOS_UINT32              ulFront;
    VOS_UINT32              ulRear;
    VOS_UINT32              ulMaxSize;
}TTF_RING_Q_ST;

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#define TTF_LINK_IS_EMPTY(pLink) (0 == (pLink)->ulCnt)
#define TTF_LINK_IS_NOT_EMPTY(pLink) (0 != (pLink)->ulCnt)

#define TTF_LINK_INIT(pLink)    \
{   \
    (pLink)->stHead.pNext = &((pLink)->stHead); \
    (pLink)->stHead.pPrev = &((pLink)->stHead); \
    (pLink)->ulCnt        = 0;  \
}

#define TTF_LINK_INSERT_TAIL(pLink, pInsert) \
{   \
    (pInsert)->pNext              = (TTF_NODE_ST *)(&((pLink)->stHead));  \
    (pInsert)->pPrev              = (pLink)->stHead.pPrev;  \
    (pLink)->stHead.pPrev->pNext  = (pInsert);  \
    (pLink)->stHead.pPrev         = (pInsert);  \
    (pLink)->ulCnt++; \
}

#define TTF_LINK_PEEK_HEAD(pLink, pNode, PtrType) \
{   \
    if ( 0 == (pLink)->ulCnt )    \
    {   \
        (pNode) = (PtrType)VOS_NULL_PTR;   \
    }   \
    else    \
    {   \
        (pNode) = (PtrType)((pLink)->stHead.pNext);    \
    }   \
}

#define TTF_LINK_REMOVE_NODE(pLink, pRemoveNode) \
{   \
    (pRemoveNode)->pNext->pPrev = (pRemoveNode)->pPrev; \
    (pRemoveNode)->pPrev->pNext = (pRemoveNode)->pNext; \
    (pRemoveNode)->pPrev        = VOS_NULL_PTR; \
    (pRemoveNode)->pNext        = VOS_NULL_PTR; \
    (pLink)->ulCnt--;   \
}

extern VOS_VOID     TTF_LinkInit(VOS_UINT32 ulPid, TTF_LINK_ST *pLink);
extern VOS_VOID     TTF_NodeInit(TTF_NODE_ST *pNode);
extern VOS_VOID     TTF_LinkFree(VOS_UINT32 ulPid, TTF_LINK_ST *pLink);
extern VOS_UINT32   TTF_LinkCheckNodeInLink(VOS_UINT32 ulPid, TTF_LINK_ST *pLink, TTF_NODE_ST *pCurr);

#ifdef _lint

#ifdef  TTF_LinkInsertHead
#undef  TTF_LinkInsertHead
#endif
#define TTF_LinkInsertHead(ulPid, pLink, pInsert)          {(VOS_VOID)(pLink); free(pInsert);}

#ifdef  TTF_LinkInsertTail
#undef  TTF_LinkInsertTail
#endif
#define TTF_LinkInsertTail(ulPid, pLink, pInsert)           {(VOS_VOID)(pLink); free(pInsert);}

#ifdef  TTF_LinkInsertNext
#undef  TTF_LinkInsertNext
#endif
#define TTF_LinkInsertNext(ulPid, pLink, pCurr, pInsert)   {(VOS_VOID)(pLink); (VOS_VOID)(pCurr); free(pInsert);}
#else
extern VOS_UINT32   TTF_LinkInsertHead(VOS_UINT32 ulPid, TTF_LINK_ST * pLink, TTF_NODE_ST *pInsert);
extern VOS_UINT32   TTF_LinkInsertPrev(VOS_UINT32 ulPid, TTF_LINK_ST * pLink, TTF_NODE_ST *pCurr, TTF_NODE_ST *pInsert);
extern VOS_UINT32   TTF_LinkInsertNext(VOS_UINT32 ulPid, TTF_LINK_ST * pLink, TTF_NODE_ST *pCurr, TTF_NODE_ST *pInsert);
extern VOS_UINT32   TTF_LinkInsertTail(VOS_UINT32 ulPid, TTF_LINK_ST * pLink, TTF_NODE_ST *pInsert);
#endif

extern VOS_UINT32   TTF_LinkSafeInsertTail(VOS_UINT32 ulPid, TTF_LINK_ST * pLink, TTF_NODE_ST *pInsert, VOS_UINT32 *pulNonEmptyEvent);
extern TTF_NODE_ST* TTF_LinkSafeRemoveHead(VOS_UINT32 ulPid, TTF_LINK_ST * pLink, VOS_UINT32 *pulRemainCnt);

extern VOS_VOID     TTF_LinkRemoveNode(VOS_UINT32 ulPid, TTF_LINK_ST * pLink, TTF_NODE_ST *pRemoveNode);
extern TTF_NODE_ST* TTF_LinkRemoveTail(VOS_UINT32 ulPid, TTF_LINK_ST * pLink);

extern VOS_UINT32   TTF_LinkPeekNext(VOS_UINT32 ulPid, const TTF_LINK_ST * pLink,
                                     TTF_NODE_ST *pCurr, TTF_NODE_ST **ppCurrNext);
extern VOS_UINT32   TTF_LinkPeekPrev(VOS_UINT32 ulPid, TTF_LINK_ST * pLink,
                                     TTF_NODE_ST *pCurr, TTF_NODE_ST **ppCurrPrev);
extern TTF_NODE_ST* TTF_LinkPeekTail(VOS_UINT32 ulPid, const TTF_LINK_ST * pLink);
extern VOS_UINT32   TTF_LinkStick(VOS_UINT32 ulPid, TTF_LINK_ST *pLink1,
                                  TTF_LINK_ST *pLink2);
extern TTF_NODE_ST* TTF_LinkRemoveHead(VOS_UINT32 ulPid, TTF_LINK_ST * pLink);
extern VOS_UINT32   TTF_LinkCnt(VOS_UINT32 ulPid, const TTF_LINK_ST *pLink);
extern VOS_UINT32   TTF_LinkIsEmpty(VOS_UINT32 ulPid, const TTF_LINK_ST *pLink);
extern TTF_NODE_ST* TTF_LinkPeekHead(VOS_UINT32 ulPid, const TTF_LINK_ST * pLink);

extern VOS_UINT32   TTF_RING_Q_Init(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ, VOS_UINT32 ulMaxSize );
extern VOS_UINT32  TTF_RING_Q_InitAndNodeAddrSet(VOS_UINT32 ulPid,
                                                                TTF_RING_Q_ST *pstRingQ,
                                                                VOS_VOID **ppNode,
                                                                VOS_VOID *pQueueNode,
                                                                VOS_UINT32 ulBlkSize,
                                                                VOS_UINT32 ulMaxSize );
extern VOS_UINT32  TTF_RING_Q_NodeAddrInit(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ, VOS_VOID **ppNodeAddr,VOS_UINT32 ulNodeCnt,VOS_UINT8 ucSize);
extern VOS_UINT32   TTF_RING_Q_NodeAddrSet(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ, VOS_VOID **ppNodeAddr,VOS_UINT32 ulNodeCnt);
extern VOS_VOID*    TTF_RING_Q_Front(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ);
extern VOS_VOID*    TTF_RING_Q_Rear(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ);
extern VOS_UINT32   TTF_RING_Q_In(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ );
extern VOS_VOID*    TTF_RING_Q_Out(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ);
extern VOS_UINT32   TTF_RING_Q_IsFull(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ);
extern VOS_UINT32   TTF_RING_Q_IsEmpty(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ);
extern VOS_UINT32   TTF_RING_Q_GetCnt(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ);
extern VOS_UINT32   TTF_RING_Q_Flush(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ);
extern VOS_UINT32   TTF_RING_Q_Free(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* TTFLINK.h */
