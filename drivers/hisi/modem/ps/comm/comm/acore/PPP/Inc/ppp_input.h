/*
 *
 * All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses. You may choose this file to be licensed under the terms
 * of the GNU General Public License (GPL) Version 2 or the 2-clause
 * BSD license listed below:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

#ifndef __PPP_INPUT_H__
#define __PPP_INPUT_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "PPP/Inc/ppp_public.h"

#pragma pack(4)

enum PPP_MSG_TYPE_ENUM
{
#if (PPP_FEATURE == PPP_FEATURE_PPP)
    PPP_DATA_PROC_NOTIFY = 1,
    PPP_AT_CTRL_OPERATION,
    PPP_PACKET_FROM_GGSN,
    PPP_RECV_PROTO_PACKET_TYPE,
    PPP_SEND_PROTO_PACKET_TYPE,
    AT_PPP_CREATE_PPP_REQ,
    AT_PPP_RELEASE_PPP_REQ,
    AT_PPP_CREATE_RAW_PPP_REQ,
    AT_PPP_RELEASE_RAW_PPP_REQ,
    AT_PPP_RECV_RELEASE_IND,
    AT_PPP_RECV_CONFIG_INFO_IND,
    PPP_AT_RECV_CONFIG_INFO_REQ,
    PPP_CONFIG_INFO_PROC_NOTIFY,
    PPP_PROTOCOL_RELEASED_IND,
    PPP_RECV_PCO_IPCP_REJ_IND,
    PPP_RECV_PCO_IPCP_ACK_IND,
    PPP_RECV_PCO_IPCP_NAK_IND,
#endif
#ifdef WTTF_PC_ST_SWITCH
    AT_PPP_UL_DATA_REQ,
    PPP_AT_DL_DATA_IND
#endif

};
typedef VOS_UINT32  PPP_MSG_TYPE_ENUM_UINT32;

#define PPP_SEND_OUT_PROTOCOL_FRAME 0
#define PPP_RECV_IN_PROTOCOL_FRAME  1

#define PPP_RECV_QUEUE_MAX_LEN      (2000)

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32  ulMsgname;
    VOS_UINT32  ulPppPhase;
    VOS_INT32   ulLcpState;
    VOS_INT32   ulIpcpState;
    VOS_UINT16  usPppId;
    VOS_UINT16  ulDataLen;
} PPP_FRAME_MNTN_INFO_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32  ulMsgname;
    VOS_UINT16  usPppId;
    VOS_UINT16  usReserved;
    VOS_UINT32  ulPppPhase;
    VOS_INT32   ulLcpState;
    VOS_INT32   ulIpcpState;
} PPP_EVENT_MNTN_INFO_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32     ulMsgType;
    union
    {
        PPP_ID        m_PppId;
    }u ;
}PPP_MSG;


typedef struct
{
    VOS_MSG_HEADER
    PPP_MSG_TYPE_ENUM_UINT32    ulMsgType;
}PPP_DATA_PROC_NOTIFY_MSG;

typedef struct
{
    VOS_MSG_HEADER
    PPP_MSG_TYPE_ENUM_UINT32            ulMsgType;
    PPP_ID                              usPppId;
    VOS_UINT8                           aucRsv[2];
    PPP_AT_CTRL_OPER_TYPE_ENUM_UINT32   ulCtrlOpType;
} PPP_AT_CTRL_OPERATION_MSG;

#ifdef WTTF_PC_ST_SWITCH

typedef struct
{
    VOS_UINT32  ulAccm;
    VOS_UINT32  ulProtoComp;
    VOS_UINT32  ulAcfComp;
} PPP_HDLC_CTRL_STRU;

typedef struct
{
    VOS_UINT16                          usDataLen;
    VOS_UINT16                          aucData[PPP_ZC_MAX_DATA_LEN];
}PPP_STUB_ZC_UL_DATA_REQ_STRU;

typedef struct
{
    VOS_UINT16                          usDataLen;
    VOS_UINT16                          aucData[PPP_ZC_MAX_DATA_LEN];
}PPP_STUB_ZC_DL_DATA_IND_STRU;

typedef struct
{
    VOS_MSG_HEADER
    PPP_MSG_TYPE_ENUM_UINT32      ulMsgType;
    union
    {
        PPP_STUB_ZC_UL_DATA_REQ_STRU    stUlDataReq;
        PPP_STUB_ZC_DL_DATA_IND_STRU    stDlDataInd;
    }u;
}PPP_STUB_ZC_DATA_MSG_STRU;

#endif

extern PPP_DATA_Q_CTRL_ST       g_PppDataQCtrl;

typedef struct
{
    PPP_MSG_TYPE_ENUM_UINT32            enMsgID;

    VOS_UINT8                           aucMsgBlock[4];
}PPP_MSG_DATA;

typedef struct
{
    VOS_MSG_HEADER
    PPP_MSG_DATA                    stMsgData;
}PppInterface_MSG;

extern VOS_UINT32 PPP_ProcAtCtrlOper(struct MsgCB * pMsg);

extern VOS_VOID Ppp_MBufFrameMntnInfo(struct ppp_mbuf *bp, VOS_UINT16 usProto, VOS_UINT32 ulDir);
extern VOS_VOID Ppp_TtfMemFrameMntnInfo(PPP_ZC_STRU *pstMem, VOS_UINT16 usProto, VOS_UINT32 ulDir);
extern VOS_VOID Ppp_FrameMntnInfo(PPP_FRAME_MNTN_INFO_STRU *ptrPppMntnSt, VOS_UINT32 ulDir, VOS_UINT16 ulDataLen);
extern VOS_VOID Ppp_EventMntnInfo(VOS_UINT16 usPppID, VOS_UINT32 ulEvent);
extern VOS_VOID Ppp_RcvConfigInfoIndMntnInfo(VOS_UINT16 usPppID, AT_PPP_IND_CONFIG_INFO_STRU *ptrIndConfigInfo);
extern VOS_VOID Ppp_RcvConfigInfoReqMntnInfo(VOS_UINT16 usPppID, PPP_REQ_CONFIG_INFO_STRU *ptrReqConfigInfo);

extern VOS_UINT32 PPP_SendPulledData(VOS_UINT16 usPppId, PPP_ZC_STRU *pstMem);
extern VOS_UINT32 PPP_SendPushedData(VOS_UINT16 usPppId, VOS_UINT8 * pucHdlcFrameBuf, VOS_UINT16 usLen);

extern VOS_VOID PPP_InitSpinLock(VOS_VOID);

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif /*end of __PPP_INPUT_H__*/
