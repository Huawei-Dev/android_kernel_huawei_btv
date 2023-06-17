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

#ifndef __IPNDSERVER_H__
#define __IPNDSERVER_H__

#include "vos.h"
#include "PsTypeDef.h"
#include "ImmInterface.h"
#include "IpComm.h"
#include "IpIpmGlobal.h"
#include "AtNdisInterface.h"
#include "LUPQueue.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

#ifdef _lint
#define NDIS_NDSERVER_PID     420
#else
#define NDIS_NDSERVER_PID     UEPS_PID_NDSERVER
#endif

#define ND_IPV6_WAIT_ADDR_RSLT_Q_LEN   (10)

#define IP_NDSERVER_ADDRINFO_MAX_NUM                    (11)

#define IP_NDSERVER_GET_ADDR_INFO_INDEX(ucExRabId)       (NdSer_GetAddrInfoIdx(ucExRabId))

#define IP_NDSERVER_GET_EPSBID(ulIndex)                 (g_astNdServerAddrInfo[ulIndex].ucEpsbId)

#define IP_NDSERVER_ADDRINFO_GET_ADDR(ulIndex)\
                (&g_astNdServerAddrInfo[ulIndex])

#define IP_NDSERVER_ADDRINFO_GET_EPSID(ulIndex)\
                (g_astNdServerAddrInfo[ulIndex].ucEpsbId)

#define IP_NDSERVER_ADDRINFO_GET_TIMER(ulIndex)\
                (&(g_astNdServerAddrInfo[ulIndex].stTimerInfo))

#define IP_NDSERVER_ADDRINFO_GET_NWPARA(ulIndex)\
                (&(g_astNdServerAddrInfo[ulIndex].stIpv6NwPara))

#define IP_NDSERVER_ADDRINFO_GET_TEINFO(ulIndex)\
                (&(g_astNdServerAddrInfo[ulIndex].stTeAddrInfo))

#define IP_NDSERVER_ADDRINFO_GET_MACADDR(ulIndex)\
                (g_astNdServerAddrInfo[ulIndex].aucUeMacAddr)

#define IP_NDSERVER_ADDRINFO_GET_MACFRAME(ulIndex)\
                (g_astNdServerAddrInfo[ulIndex].aucMacFrmHdr)

#define IP_NDSERVER_ADDRINFO_GET_DLPKTQUE(ulIndex)\
                (g_astNdServerAddrInfo[ulIndex].pstDlPktQue)

#define IP_NDSERVER_GET_NDMSGDATA_ADDR()                (&g_stNdMsgData)

#define IP_NDSERVER_GET_SENDMSG_BUFFER()                (g_aucSendMsgBuffer)

#define IP_NDSERVER_GET_STATINFO_ADDR(ulIndex)          (&g_astNdServerPktStatInfo[ulIndex])
#define IP_NDSERVER_AddRcvPktTotalNum(ulIndex)          (g_astNdServerPktStatInfo[ulIndex].ulRcvPktTotalNum++)
#define IP_NDSERVER_AddDiscPktNum(ulIndex)              (g_astNdServerPktStatInfo[ulIndex].ulDiscPktNum++)
#define IP_NDSERVER_AddRcvNsPktNum(ulIndex)             (g_astNdServerPktStatInfo[ulIndex].ulRcvNsPktNum++)
#define IP_NDSERVER_AddRcvNaPktNum(ulIndex)             (g_astNdServerPktStatInfo[ulIndex].ulRcvNaPktNum++)
#define IP_NDSERVER_AddRcvRsPktNum(ulIndex)             (g_astNdServerPktStatInfo[ulIndex].ulRcvRsPktNum++)
#define IP_NDSERVER_AddRcvEchoPktNum(ulIndex)           (g_astNdServerPktStatInfo[ulIndex].ulRcvEchoPktNum++)
#define IP_NDSERVER_AddRcvBooBigPktNum(ulIndex)         (g_astNdServerPktStatInfo[ulIndex].ulRcvTooBigPktNum++)
#define IP_NDSERVER_AddRcvDHCPV6PktNum(ulIndex)         (g_astNdServerPktStatInfo[ulIndex].ulRcvDhcpv6PktNum++)
#define IP_NDSERVER_AddErrNsPktNum(ulIndex)             (g_astNdServerPktStatInfo[ulIndex].ulErrNsPktNum++)
#define IP_NDSERVER_AddErrNaPktNum(ulIndex)             (g_astNdServerPktStatInfo[ulIndex].ulErrNaPktNum++)
#define IP_NDSERVER_AddErrRsPktNum(ulIndex)             (g_astNdServerPktStatInfo[ulIndex].ulErrRsPktNum++)
#define IP_NDSERVER_AddErrEchoPktNum(ulIndex)           (g_astNdServerPktStatInfo[ulIndex].ulErrEchoPktNum++)
#define IP_NDSERVER_AddErrTooBigPktNum(ulIndex)         (g_astNdServerPktStatInfo[ulIndex].ulErrTooBigPktNum++)
#define IP_NDSERVER_AddErrDhcpv6PktNum(ulIndex)         (g_astNdServerPktStatInfo[ulIndex].ulErrDhcpv6PktNum++)
#define IP_NDSERVER_AddTransPktTotalNum(ulIndex)        (g_astNdServerPktStatInfo[ulIndex].ulTransPktTotalNum++)
#define IP_NDSERVER_AddTransPktFailNum(ulIndex)         (g_astNdServerPktStatInfo[ulIndex].ulTransPktFailNum++)
#define IP_NDSERVER_AddTransNsPktNum(ulIndex)           (g_astNdServerPktStatInfo[ulIndex].ulTransNsPktNum++)
#define IP_NDSERVER_AddTransNaPktNum(ulIndex)           (g_astNdServerPktStatInfo[ulIndex].ulTransNaPktNum++)
#define IP_NDSERVER_AddTransRaPktNum(ulIndex)           (g_astNdServerPktStatInfo[ulIndex].ulTransRaPktNum++)
#define IP_NDSERVER_AddTransEchoPktNum(ulIndex)         (g_astNdServerPktStatInfo[ulIndex].ulTransEchoPktNum++)
#define IP_NDSERVER_AddTransTooBigPktNum(ulIndex)       (g_astNdServerPktStatInfo[ulIndex].ulTransTooBigPktNum++)
#define IP_NDSERVER_AddTransDhcpv6PktNum(ulIndex)       (g_astNdServerPktStatInfo[ulIndex].ulTransDhcpv6PktNum++)
#define IP_NDSERVER_AddMacInvalidPktNum(ulIndex)        (g_astNdServerPktStatInfo[ulIndex].ulMacInvalidPktNum++)
#define IP_NDSERVER_AddEnquePktNum(ulIndex)             (g_astNdServerPktStatInfo[ulIndex].ulEnquePktNum++)
#define IP_NDSERVER_AddSendQuePktNum(ulIndex)           (g_astNdServerPktStatInfo[ulIndex].ulSendQuePktNum++)

enum NDSER_TIMER_ENUM
{
    IP_ND_SERVER_TIMER_NS               = 0,
    IP_ND_SERVER_TIMER_PERIODIC_NS      = 1,
    IP_ND_SERVER_TIMER_FIRST_NS         = 2,
    IP_ND_SERVER_TIMER_RA               = 3,

    IP_ND_SERVER_TIMER_BUTT
};
typedef VOS_UINT32 NDSER_TIMER_ENUM_UINT32;

enum IP_NDSERVER_TE_ADDR_STATE_ENUM
{
    IP_NDSERVER_TE_ADDR_INEXISTENT          = 0,
    IP_NDSERVER_TE_ADDR_INCOMPLETE          = 1,
    IP_NDSERVER_TE_ADDR_REACHABLE           = 2,
    IP_NDSERVER_TE_ADDR_BUTT
};
typedef VOS_UINT8 IP_NDSERVER_TE_ADDR_STATE_ENUM_UINT8;

typedef struct
{
    VOS_UINT8                               aucTeLinkLocalAddr[IP_IPV6_ADDR_LEN];
    VOS_UINT8                               aucTeGlobalAddr[IP_IPV6_ADDR_LEN];
    VOS_UINT8                               aucTeLinkLayerAddr[IP_MAC_ADDR_LEN];
    IP_NDSERVER_TE_ADDR_STATE_ENUM_UINT8    enTeAddrState;
    VOS_UINT8                               aucReserved[1];
}IP_NDSERVER_TE_ADDR_INFO_STRU;

typedef struct
{
    VOS_UINT32                          ulValid;
    VOS_UINT8                           aucTeGlobalAddr[IP_IPV6_ADDR_LEN];
}IP_IPV6_ADDR_STRU;

typedef struct
{
    VOS_UINT32                          ulHead;
    VOS_UINT32                          ulTail;
    VOS_UINT32                          ulMaxNum;
    IP_IPV6_ADDR_STRU                   astTeIpBuf[2*IP_NDSERVER_ADDRINFO_MAX_NUM];
}IP_NDSERVER_TE_DETECT_BUF_STRU;

typedef struct
{
    VOS_UINT8                           ucEpsbId;
    VOS_UINT8                           ucValidFlag;
    VOS_UINT8                           aucReserved[14];
    LUP_QUEUE_STRU                     *pstDlPktQue;
    IP_SND_MSG_STRU                     stIpSndNwMsg;

    ESM_IP_IPV6_NW_PARA_STRU            stIpv6NwPara;

    IP_NDSERVER_TE_ADDR_INFO_STRU       stTeAddrInfo;

    VOS_UINT8                           aucUeLinkLocalAddr[IP_IPV6_ADDR_LEN];

    IP_TIMER_STRU                       stTimerInfo;

    VOS_UINT8                           aucUeMacAddr[IP_MAC_ADDR_LEN];
    VOS_UINT8                           aucMacFrmHdr[IP_ETH_MAC_HEADER_LEN];
}IP_NDSERVER_ADDR_INFO_STRU;

typedef struct
{
    VOS_UINT32                          ulRcvPktTotalNum;
    VOS_UINT32                          ulDiscPktNum;
    VOS_UINT32                          ulRcvNsPktNum;
    VOS_UINT32                          ulRcvNaPktNum;
    VOS_UINT32                          ulRcvRsPktNum;
    VOS_UINT32                          ulRcvEchoPktNum;
    VOS_UINT32                          ulRcvTooBigPktNum;
    VOS_UINT32                          ulRcvDhcpv6PktNum;
    VOS_UINT32                          ulErrNsPktNum;
    VOS_UINT32                          ulErrNaPktNum;
    VOS_UINT32                          ulErrRsPktNum;
    VOS_UINT32                          ulErrEchoPktNum;
    VOS_UINT32                          ulErrTooBigPktNum;
    VOS_UINT32                          ulErrDhcpv6PktNum;
    VOS_UINT32                          ulTransPktTotalNum;
    VOS_UINT32                          ulTransPktFailNum;
    VOS_UINT32                          ulTransNsPktNum;
    VOS_UINT32                          ulTransNaPktNum;
    VOS_UINT32                          ulTransRaPktNum;
    VOS_UINT32                          ulTransEchoPktNum;
    VOS_UINT32                          ulTransTooBigPktNum;
    VOS_UINT32                          ulTransDhcpv6PktNum;
    VOS_UINT32                          ulMacInvalidPktNum;
    VOS_UINT32                          ulEnquePktNum;
    VOS_UINT32                          ulSendQuePktNum;
}IP_NDSERVER_PACKET_STATISTICS_INFO_STRU;

extern IP_NDSERVER_ADDR_INFO_STRU       g_astNdServerAddrInfo[];

extern VOS_VOID IP_NDSERVER_Init( VOS_VOID );

VOS_UINT32 NdSer_CheckIpv6PdnInfo(AT_NDIS_IPV6_PDN_INFO_STRU *pstIpv6PdnInfo);
VOS_VOID NdSer_Ipv6PdnInfoCfg(VOS_UINT8 ucRabId,AT_NDIS_IPV6_PDN_INFO_STRU *pstIpv6PdnInfo);
VOS_VOID NdSer_DhcpV6PktProc(VOS_VOID *pRcvMsg);
VOS_UINT32 NdSer_GetAddrInfoIdx(VOS_UINT8 ucExRabId);
VOS_UINT8* NdSer_GetMacFrm(VOS_UINT8 ucIndex, VOS_UINT8 *enTeAddrState);
VOS_VOID NdSer_Ipv6PdnRel(VOS_UINT8 ucRabId);
VOS_UINT32 NdSer_Ipv6PdnValid(VOS_UINT8 ucRabId);
VOS_VOID NdSer_NdAndEchoPktProc(VOS_VOID *pRcvMsg);
VOS_UINT32  APP_NdServer_Pid_InitFunc( enum VOS_INIT_PHASE_DEFINE ePhase);
VOS_VOID IP_NDSERVER_ProcTooBigPkt(VOS_UINT8 ucRabId, VOS_UINT8 *pucSrcData, VOS_UINT32 ulDataLen);
VOS_VOID APP_NdServer_PidMsgProc(const MsgBlock *pRcvMsg);
VOS_UINT32 IP_NDSERVER_SendNsMsg
(
    VOS_UINT32                          ulIndex,
    const VOS_UINT8                     *pstDstAddr
);
VOS_VOID NdSer_MacAddrInvalidProc(IMM_ZC_STRU *pstImmZc, VOS_UINT8 ucIndex);

IP_NDSERVER_ADDR_INFO_STRU* NdSer_AllocAddrInfo(VOS_UINT32* pUlIndex);

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of IpNdServer.h */
