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




/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "ImmInterface.h"
#include "NVIM_Interface.h"
#include "PsNdis.h"
#include "LUPQueue.h"
#include "Ipv4DhcpServer.h"
#include "PsCommonDef.h"
#include "msp_at.h"
#include "msp_diag.h"
#include "vos.h"
#include "IpNdServer.h"
#include "NasNvInterface.h"
#include "NdisDrv.h"
/*****************************************************************************
    ??????????????????????.C??????????
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_PSNDIS_C
/*lint +e767*/

/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
#define C2A_QUE_SIZE                512        /*????512*/
#define USB_DATAREQ_QUE_SIZE        512        /*????512*/

#define NDIS_PERIOD_ARP_TMRNAME     1
#define NDIS_ARP_REQ_TMRNAME        2

/*****************************************************************************
  3 function
*****************************************************************************/
/*????ADS????????????????*/
LUP_QUEUE_STRU  *g_pstC2ACoreQue        = VOS_NULL_PTR;
VOS_VOID        *p_aC2AQueBuf[C2A_QUE_SIZE];

/*????USB??????????????*/
LUP_QUEUE_STRU  *g_pstUsbDataReqQue     = VOS_NULL_PTR;
VOS_VOID        *p_aUsbQueBuf[USB_DATAREQ_QUE_SIZE];

/*arp????????????????????*/
VOS_UINT8       g_aucArpReqFixVal[ETH_ARP_FIXED_MSG_LEN] = {0x00,0x01,0x08,0x00,0x06,0x04,0x00,0x01 };
/*arp????????????????????*/
VOS_UINT8       g_aucArpRspFixVal[ETH_ARP_FIXED_MSG_LEN] = {0x00,0x01,0x08,0x00,0x06,0x04,0x00,0x02 };
/*????????????1*/
VOS_UINT8       g_aucBroadCastAddr[ETH_MAC_ADDR_LEN]   = {0xff,0xff,0xff,0xff,0xff,0xff };

VOS_UINT8       g_aucInvalidAddr[IPV4_ADDR_LEN] = {0};

/*ARP????*/
VOS_UINT32      g_ulPeriodicArpCyc      = 3000;   /*??????ARP????????*/


/*????????*/
NDIS_STAT_INFO_STRU        g_stNdisStatStru = {0};

NDIS_ENTITY_STRU           g_astNdisEntity[NAS_NDIS_MAX_ITEM] = {{0}};
NDIS_ENTITY_STRU          *g_pstNdisEntity = g_astNdisEntity;

VOS_UINT32                 g_ulNvMtu = 1500;              /*IPV6 MTU????????*/

VOS_UINT32 g_ulNdisLomSwitch = 0;
SPE_MAC_ETHER_HEADER_STRU g_stSpeMacHeader = {{0x58,0x02,0x03,0x04,0x05,0x06},{0x00,0x11,0x09,0x64,0x01,0x01},0x00000000};     /*mac??????????????????*/

/*****************************************************************************
  3 Function
*****************************************************************************/
/*????*/
extern VOS_VOID   PppMsgProc( struct MsgCB * pMsg );
extern VOS_UINT32 PppInit(enum VOS_INIT_PHASE_DEFINE InitPhase );
VOS_UINT32 Ndis_DlSpeSendNcm(NDIS_ENTITY_STRU *pstNdisEntity, ADS_PKT_TYPE_ENUM_UINT8 ucPktType, IMM_ZC_STRU *pstImmZc);


extern VOS_UINT32 DIPC_Pid_InitFunc( enum VOS_INIT_PHASE_DEFINE ip );
extern VOS_UINT32 DIPC_AtMsgProc( const MsgBlock *pMsgBlock );

extern VOS_UINT32 MUX_Pid_InitFunc( enum VOS_INIT_PHASE_DEFINE ip );
extern VOS_UINT32 MUX_AtMsgProc( const MsgBlock *pMsgBlock );

/* ****************************************************************************
 ?? ?? ??  : Ndis_GetMacAddr
 ????????  : ????MAC????
 ????????  : None
 ????????  : None
 ?? ?? ??  : VOS_UINT8*
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2014??10??17??
    ??    ??   : ????
    ????????   : ??????????
*****************************************************************************/
VOS_UINT8* Ndis_GetMacAddr(VOS_VOID)
{
    /*LTE??????MAC????*/
    static VOS_UINT8 g_ucMacAddressPstable[] =
    {
        0x4c, 0x54, 0x99, 0x45, 0xe5, 0xd5
    };

    return g_ucMacAddressPstable;
}

/* ****************************************************************************
 ?? ?? ??  : Ndis_DlAdsDataRcv
 ????????  : NDIS_ADS????????????????????
 ????????  : VOS_VOID *pBuf
             VOS_UINT32 ulLen
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??12??9??
    ??    ??   : ????
    ????????   : ??????????

  2.??    ??   : 2013??1??16??
    ??    ??   : h00218138
    ????????   : DSDA????????????????????????????ID

*****************************************************************************/
VOS_UINT32 Ndis_DlAdsDataRcv(VOS_UINT8 ucExRabId, IMM_ZC_STRU *pData, ADS_PKT_TYPE_ENUM_UINT8 enPktType, VOS_UINT32 ulExParam)
{
    if (VOS_NULL_PTR == pData)
    {
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_DlAdsDataRcv, recv NULL PTR!");
        return PS_FAIL;
    }

    if ((PS_SUCC != Ndis_ChkRabIdValid(ucExRabId))
             || (ADS_PKT_TYPE_BUTT <= enPktType))
    {
        /*lint -e522*/
        IMM_ZcFree(pData);
        /*lint +e522*/
        NDIS_ERROR_LOG2(NDIS_TASK_PID, "Ndis_DlAdsDataRcv, recv RabId or PktType fail!", ucExRabId, enPktType);
        NDIS_STAT_DL_DISCARD_ADSPKT(1);
        return PS_FAIL;
    }

    /*??????ADS??????????????????????*/
    NDIS_STAT_DL_RECV_ADSPKT_SUCC(1);

    Ndis_LomTraceRcvDlData();
    if (PS_SUCC != Ndis_DlSendNcm(ucExRabId, enPktType, pData))
    {
        /*lint -e522*/
        IMM_ZcFree(pData);
        /*lint +e522*/
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_DlAdsDataRcv, Ndis_DlSendNcm fail!");
        return PS_FAIL;
    }

    return PS_SUCC;
}

/*****************************************************************************
 ?? ?? ??  : AppNdis_UsbReadCb
 ????????  : App????USB????
 ????????  : VOS_VOID *pBuf
             VOS_UINT32 ulLen
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??1??31??
    ??    ??   : ????
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 AppNdis_UsbReadCb(UDI_HANDLE ulhandle, VOS_VOID *pPktNode)
{
    IMM_ZC_STRU            *pstImmZc = (IMM_ZC_STRU*)pPktNode;    /*????ImmZc??sk_buff??????????????????*/

    VOS_UINT8                   ucExRabId;
    VOS_UINT16                  usFrameType;
    ETHFRM_IPV4_PKT_STRU       *pstIpPacket;
    VOS_UINT8                  *pucData;

    if (VOS_NULL_PTR == pstImmZc)
    {
        NDIS_ERROR_LOG(NDIS_TASK_PID, "AppNdis_UsbReadCb read NULL PTR!");
        return PS_FAIL;
    }

    pucData = IMM_ZcGetDataPtr(pstImmZc);
    if (VOS_NULL_PTR == pucData)
    {
        /*lint -e522*/
        IMM_ZcFree(pstImmZc);
        /*lint +e522*/
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_UlNcmFrmProc, IMM_ZcGetDataPtr fail!");
        NDIS_STAT_UL_DISCARD_USBPKT(1);
        return PS_FAIL;
    }

    pstIpPacket = (ETHFRM_IPV4_PKT_STRU  *)(VOS_VOID*)pucData;
    usFrameType = pstIpPacket->usFrameType;

    /*????????????????RabId*/
    ucExRabId = Ndis_FindRabIdByHandle(ulhandle, usFrameType);

    if (PS_SUCC != Ndis_ChkRabIdValid(ucExRabId))
    {
        /*lint -e522*/
        IMM_ZcFree(pstImmZc);
        /*lint +e522*/
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_UlNcmFrmProc, Ndis_ChkRabIdValid fail!");
        NDIS_STAT_UL_DISCARD_USBPKT(1);
        return PS_FAIL;
    }

    NDIS_STAT_UL_RECV_USBPKT_SUCC(1);

    Ndis_LomTraceRcvUlData();
    Ndis_UlNcmFrmProc(ucExRabId, pstImmZc);

    return PS_SUCC;
}
/*****************************************************************************
 ?? ?? ??  : AppNdis_SpeReadCb
 ????????  : App????SPE????
 ????????  : VOS_VOID *pBuf
             VOS_UINT32 ulLen
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??1??31??
    ??    ??   : c00253308
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 AppNdis_SpeReadCb(VOS_INT32 lSpePort, VOS_VOID *pPktNode)
{
    IMM_ZC_STRU            *pstImmZc = (IMM_ZC_STRU*)pPktNode;    /*????ImmZc??sk_buff??????????????????*/

    VOS_UINT16                  usFrameType;
    ETHFRM_IPV4_PKT_STRU       *pstIpPacket;
    VOS_UINT8                  *pucData;
    VOS_UINT8                   ucExRabId;
    if (VOS_NULL_PTR == pstImmZc)
    {
        NDIS_ERROR_LOG(NDIS_TASK_PID, "AppNdis_UsbReadCb read NULL PTR!");
        return PS_FAIL;
    }

    pucData = IMM_ZcGetDataPtr(pstImmZc);
    if (VOS_NULL_PTR == pucData)
    {
        /*lint -e522*/
        IMM_ZcFree(pstImmZc);
        /*lint +e522*/
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_UlNcmFrmProc, IMM_ZcGetDataPtr fail!");
       // NDIS_STAT_UL_DISCARD_USBPKT(1);
        return PS_FAIL;
    }

    pstIpPacket = (ETHFRM_IPV4_PKT_STRU  *)(VOS_VOID*)pucData;
    usFrameType = pstIpPacket->usFrameType;

    /*????????????????RabId*/
    ucExRabId = Ndis_FindRabIdBySpePort(lSpePort, usFrameType);

    if (PS_SUCC != Ndis_ChkRabIdValid(ucExRabId))
    {
        /*lint -e522*/
        IMM_ZcFree(pstImmZc);
        /*lint +e522*/
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_UlNcmFrmProc, Ndis_ChkRabIdValid fail!");
        //NDIS_STAT_UL_DISCARD_USBPKT(1);
        return PS_FAIL;
    }

    //NDIS_STAT_UL_RECV_USBPKT_SUCC(1);

    Ndis_LomTraceRcvUlData();
    Ndis_UlNcmFrmProc(ucExRabId, pstImmZc);

    return PS_SUCC;
}

/*****************************************************************************
 ?? ?? ??  : Ndis_InitRegToAt
 ????????  : NDIS??AT????Client
 ????????  : VOS_VOID
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??4??28??
    ??    ??   : LPDCP_CIPHERINFO_FOR_ACC
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32  Ndis_InitRegToAt( VOS_VOID )
{
    MsgBlock                        *pMsgBlock = VOS_NULL_PTR;
    AT_FW_CLIENT_REGISTER_REQ_STRU  *pRegClient = VOS_NULL_PTR;
    AT_FW_MSG_STRU                  *pAtMsg = VOS_NULL_PTR;
    VOS_UINT32                       ulRslt;

    pMsgBlock = (MsgBlock*)PS_ALLOC_MSG(NDIS_TASK_PID, sizeof(MsgBlock)+sizeof(AT_FW_MSG_STRU)+sizeof(AT_FW_CLIENT_REGISTER_REQ_STRU));
    if (VOS_NULL_PTR == pMsgBlock)
    {
        return PS_FAIL;
    }

    pMsgBlock->ulReceiverPid = APP_AT_PID;
    pMsgBlock->ulSenderPid   = NDIS_TASK_PID;
    /*lint -e826*/
    pAtMsg                   = (AT_FW_MSG_STRU*)((VOS_VOID*)(pMsgBlock->aucValue));
    /*lint +e826*/
    pAtMsg->ulMsgId          = ID_MSG_AT_FW_CLIENT_REGISTER_REQ;

    pRegClient = (AT_FW_CLIENT_REGISTER_REQ_STRU*)((VOS_VOID*)(pAtMsg->pMsgParam));
    pRegClient->bRegister          = TRUE;
    pRegClient->pstDiscardUrc      = NULL;
    pRegClient->ucClientId         = EN_AT_FW_CLIENT_ID_NDIS;
    pRegClient->ucSysMode          = AT_FW_SYS_MODE_NULL;
    pRegClient->ucInterfaceCfg     = AT_FW_PACKET_FMT_BINARY;

    ulRslt = PS_SEND_MSG(NDIS_TASK_PID, pMsgBlock);

    if (VOS_OK != ulRslt)
    {
        return PS_FAIL;
    }

    return PS_SUCC;
}

/*****************************************************************************
 ?? ?? ??  : Ndis_NvItemInit
 ????????  : A??NDIS????NV??????????????
 ????????  : VOS_VOID
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2012??4??24??
    ??    ??   : h00159435
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 Ndis_NvItemInit(VOS_VOID)
{
    VOS_UINT32     ulRtn;
    VOS_UINT32     ulDhcpLeaseHour;
    VOS_UINT32     ulIpv6Mtu;
    NDIS_NV_DHCP_LEASE_HOUR_STRU   stNdisDhcpLeaseHour;
    NDIS_NV_IPV6_MTU_STRU          stNdisIPv6Mtu;

    /*
        DHCP Lease Time, ??????????[1, 8784]????
        Vodafone    24????
        ????        72????

        ????????DHCP Lease Time????????PC????????????????
        ????DHCP??????????????PC????NDIS??????????????????????????????????????
        ????????????DHCP Lease Time????????4S????????????????????????????????????????1????
        ????????????????8????DHCP Lease Time????????????8784????(366??)
        */

    /* ??NV???????????????? */
    /*lint -e718*/
    /*lint -e732*/
	/*lint -e746*/
    ulRtn = Ndis_NvimItem_Read(en_NV_Item_NDIS_DHCP_DEF_LEASE_TIME,\
                                    &stNdisDhcpLeaseHour,\
                                    sizeof(NDIS_NV_DHCP_LEASE_HOUR_STRU));
    if (PS_SUCC != ulRtn)
    {
        PS_PRINTF("Ndis_NvItemInit, Fail to read NV DHCP_LEASE_TIME: %d\n", ulRtn);
        return PS_FAIL;
    }
    else
    {
        /* NV???????????? */
        ulDhcpLeaseHour = stNdisDhcpLeaseHour.ulDhcpLeaseHour;
        if((0 < ulDhcpLeaseHour) && (ulDhcpLeaseHour <= TTF_NDIS_DHCP_MAX_LEASE_HOUR))
        {
            /* hour -> second */
            g_ulLeaseTime = ulDhcpLeaseHour * 3600;
        }
    }

    /* ??NV????IPV6 MTU???? */
    ulRtn = Ndis_NvimItem_Read(en_NV_Item_IPV6_ROUTER_MTU,\
                                    &stNdisIPv6Mtu,\
                                    sizeof(NDIS_NV_IPV6_MTU_STRU));
	/*lint +e746*/
    /*lint +e732*/
    /*lint +e718*/

    if (PS_SUCC != ulRtn)
    {
        PS_PRINTF( "Ndis_NvItemInit, Fail to read NV IPV6_MTU: %d\n!", ulRtn);
        return PS_FAIL;
    }
    else
    {
        /* NV???????????? */
        ulIpv6Mtu = stNdisIPv6Mtu.ulIpv6Mtu;
        if(0 == ulIpv6Mtu)
        {
            g_ulNvMtu = TTF_NDIS_IPV6_MTU_DEFAULT;
        }
        else
        {
            g_ulNvMtu = ulIpv6Mtu;
        }
    }

    return PS_SUCC;
}

/*****************************************************************************
 ?? ?? ??  : Ndis_Init
 ????????  : APP??NDIS????????????????
 ????????  : VOS_VOID
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??2??10??
    ??    ??   : h00133115
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 Ndis_Init( VOS_VOID )
{
    VOS_UINT32     ulLoop;
    VOS_UINT8     *pucMacAddr;
    VOS_UINT16     usPayLoad;
    NDIS_ARP_PERIOD_TIMER_STRU    *pstArpPeriodTimer;


    /*lint -e746*/
    pucMacAddr = (VOS_UINT8 *)Ndis_GetMacAddr();                                 /*????????MAC????*/
    /*lint -e746*/

    if (VOS_NULL_PTR == pucMacAddr)
    {
        PS_PRINTF("Ndis_Init, Ndis_GetMacAddr Fail!\n");
        return PS_FAIL;
    }

    usPayLoad = IP_PAYLOAD;
    for(ulLoop=0; ulLoop<NAS_NDIS_MAX_ITEM; ulLoop++)
    {
        g_astNdisEntity[ulLoop].ucRabType  =  NDIS_RAB_NULL;
        g_astNdisEntity[ulLoop].ulHandle   =  NDIS_INVALID_HANDLE;
        g_astNdisEntity[ulLoop].ucRabId    =  NDIS_INVALID_RABID;
        g_astNdisEntity[ulLoop].enUsed     =  PS_FALSE;
        g_astNdisEntity[ulLoop].lSpePort   =  NDIS_INVALID_SPEPORT;
        g_astNdisEntity[ulLoop].ulSpeIpfFlag = PS_FALSE;
        PS_MEM_CPY(g_astNdisEntity[ulLoop].stIpV4Info.aucMacFrmHdr+ETH_MAC_ADDR_LEN,pucMacAddr,ETH_MAC_ADDR_LEN);
        PS_MEM_CPY(g_astNdisEntity[ulLoop].stIpV4Info.aucMacFrmHdr+(2*ETH_MAC_ADDR_LEN),(VOS_UINT8*)(&usPayLoad),2);

        /*??????ARP????????????*/
        pstArpPeriodTimer = &(g_astNdisEntity[ulLoop].stIpV4Info.stArpPeriodTimer);
        pstArpPeriodTimer->hTm          = VOS_NULL_PTR;
        pstArpPeriodTimer->ulName       = NDIS_PERIOD_ARP_TMRNAME;
        pstArpPeriodTimer->ulTimerValue = g_ulPeriodicArpCyc;
    }

    if (PS_SUCC != Ndis_NvItemInit())             /*NV????????*/
    {
        PS_PRINTF("Ndis_Init, Ndis_NvItemInit Fail!\n");
        return PS_FAIL;
    }

    return PS_SUCC;
}
/*****************************************************************************
 ?? ?? ??  : Ndis_DlSendNcm
 ????????  : ??????????NCM??????????
 ????????  : ??
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??2??11??
    ??    ??   : h00133115
    ????????   : ??????????
     2.??    ??   : 2015??2??11??
    ??    ??   : c00253308
    ????????   : SPE
*****************************************************************************/
VOS_UINT32 Ndis_DlSendNcm(VOS_UINT8 ucExRabId, ADS_PKT_TYPE_ENUM_UINT8 ucPktType, IMM_ZC_STRU *pstImmZc)
{
    VOS_UINT32                     ulResult;
    NDIS_ENTITY_STRU              *pstNdisEntity;
    //UDI_HANDLE                     ulHandle;

        /*????ExRabId????NDIS????*/
    pstNdisEntity = NDIS_GetEntityByRabId(ucExRabId);
    if(IP_NULL_PTR == pstNdisEntity)
    {
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_DlSendNcm, NDIS_GetEntityByRabId fail!");
        return PS_FAIL;
    }

   // ulHandle      = pstNdisEntity->ulHandle;

    ulResult = Ndis_DlUsbSendNcm(ucExRabId, ucPktType, pstImmZc);
    return ulResult;
}

/*****************************************************************************
 ?? ?? ??  : Ndis_DlSendNcm
 ????????  : ??????????NCM??????????
 ????????  : ??
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??2??11??
    ??    ??   : h00133115
    ????????   : ??????????

  2.??    ??   : 2013??1??17??
    ??    ??   : h00218138
    ????????   : DSDA??????????ExRabId????NDIS????

  3.??    ??   : 2014??11??17??
    ??    ??   : c00253308
    ????????   : SPE????????USB??SPE????????

*****************************************************************************/
VOS_UINT32 Ndis_DlUsbSendNcm(VOS_UINT8 ucExRabId, ADS_PKT_TYPE_ENUM_UINT8 ucPktType, IMM_ZC_STRU *pstImmZc)
{
    VOS_UINT8                      ucIndex;
    VOS_UINT8                     *pucAddData = VOS_NULL_PTR;
    UDI_HANDLE                     ulHandle;
    VOS_UINT32                     ulSize;
    NDIS_ENTITY_STRU              *pstNdisEntity;
    VOS_UINT8                      enTeAddrState;
    VOS_UINT16                     usApp = 0;
    VOS_UINT16                     usTmpApp = 0;

    /*????ExRabId????NDIS????*/
    pstNdisEntity = NDIS_GetEntityByRabId(ucExRabId);
    if(IP_NULL_PTR == pstNdisEntity)
    {
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_DlSendNcm, NDIS_GetEntityByRabId fail!");
        return PS_FAIL;
    }

    ulHandle      = pstNdisEntity->ulHandle;

    /*????MAC??????????ImmZc??????MAC????????ImmZc??*/
    if ((ADS_PKT_TYPE_IPV4 == ucPktType)     /*??????????*/
           && (NDIS_ENTITY_IPV4 == (pstNdisEntity->ucRabType & NDIS_ENTITY_IPV4)))
    {
        pucAddData = pstNdisEntity->stIpV4Info.aucMacFrmHdr;
    }
    else if ((ADS_PKT_TYPE_IPV6 == ucPktType)
           && (NDIS_ENTITY_IPV6 == (pstNdisEntity->ucRabType & NDIS_ENTITY_IPV6)))
    {
        ucIndex = (VOS_UINT8)IP_NDSERVER_GET_ADDR_INFO_INDEX(ucExRabId);
        if (ucIndex >= IP_NDSERVER_ADDRINFO_MAX_NUM)
        {
            NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_DlSendNcm, IP_NDSERVER_GET_ADDR_INFO_INDEX fail!");
            return PS_FAIL;
        }

        pucAddData = NdSer_GetMacFrm(ucIndex, &enTeAddrState);
        if (VOS_NULL_PTR == pucAddData)
        {
            NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_DlSendNcm, NdSer_GetMacFrm fail!");
            NDIS_STAT_DL_GET_IPV6MAC_FAIL(1);
            return PS_FAIL;
        }

        if (IP_NDSERVER_TE_ADDR_REACHABLE != enTeAddrState)
        {
            /*??ucExRabId????????????????ImmZc??????????????*/
            usTmpApp = (ucPktType & 0xFF);
            usApp    = ((VOS_UINT16)(usTmpApp << 8)) | (ucExRabId);
            IMM_ZcSetUserApp(pstImmZc, usApp);

            NdSer_MacAddrInvalidProc(pstImmZc, ucIndex);
            return PS_SUCC;
        }
    }
    else   /*??????????????????????????????*/
    {
        NDIS_ERROR_LOG2(NDIS_TASK_PID, "Ndis_DlSendNcm, Rab is different from PktType!", pstNdisEntity->ucRabType, ucPktType);
        NDIS_STAT_DL_PKT_DIFF_RAB_NUM(1);
        return PS_FAIL;
    }

    if (VOS_OK != IMM_ZcAddMacHead(pstImmZc, pucAddData))
    {
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_DlSendNcm, IMM_ZcAddMacHead fail!");
        NDIS_STAT_DL_ADDMACFRM_FAIL(1);
        return PS_FAIL;
    }

    ulSize = IMM_ZcGetUsedLen(pstImmZc);         /*????????????????????*/

    /*lint -e718*/
    if (0 != NDIS_UDI_WRITE(ulHandle, pstImmZc, ulSize))
    {
        NDIS_STAT_DL_SEND_USBPKT_FAIL(1);
        return PS_FAIL;
    }
    /*lint +e718*/

    NDIS_STAT_DL_SEND_USBPKT_SUCC(1);
    return PS_SUCC;
}

/*****************************************************************************
 ?? ?? ??  : Ndis_ProcTmrMsg
 ????????  : ????TmerMsg
 ????????  : MsgBlock *pRcvMsg
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

  1.??    ??   : 2012??4??28??
    ??    ??   : h00159435
    ????????   : ??????????
*****************************************************************************/
VOS_VOID Ndis_ProcARPTimerExp(VOS_VOID)
{
    VOS_UINT32                   ulLoop;
    NDIS_ENTITY_STRU            *pstNdisEntity;
    NDIS_IPV4_INFO_STRU         *pstIpV4Info;
    NDIS_ARP_PERIOD_TIMER_STRU  *pstArpPeriodTimer;

    for(ulLoop=0; ulLoop<NAS_NDIS_MAX_ITEM; ulLoop++)
    {
        pstNdisEntity = &g_astNdisEntity[ulLoop];
        if (NDIS_ENTITY_IPV4 == (pstNdisEntity->ucRabType & NDIS_ENTITY_IPV4))
        {
            pstIpV4Info = &(pstNdisEntity->stIpV4Info);
            pstArpPeriodTimer = &(pstIpV4Info->stArpPeriodTimer);

            if (PS_TRUE == pstIpV4Info->ulArpInitFlg)
            {
                Ndis_StopARPTimer(pstArpPeriodTimer);
            }
            else
            {
                (VOS_VOID)Ndis_SendRequestArp(&(pstNdisEntity->stIpV4Info), pstNdisEntity->ucRabId);
            }
        }
    }

    return;
}

/*****************************************************************************
 ?? ?? ??  : Ndis_ProcTmrMsg
 ????????  : ????TmerMsg
 ????????  : MsgBlock *pRcvMsg
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????  :
  1.??    ??   : 2012??4??28??
    ??    ??   : h00159435
    ????????   : ??????????
*****************************************************************************/
VOS_VOID Ndis_ProcTmrMsg(const REL_TIMER_MSG *pRcvMsg)
{
    switch(pRcvMsg->ulName)
    {
        case NDIS_PERIOD_ARP_TMRNAME:
            Ndis_ProcARPTimerExp();
            break;
        default:
            NDIS_INFO_LOG1(NDIS_TASK_PID, "Ndis_ProcTmrMsg, Recv other Timer", pRcvMsg->ulName);
            break;
    }

    return;
}

/*****************************************************************************
 ?? ?? ??  : Ndis_DHCPPkt_Proc
 ????????  : DHCP????
 ????????  : ??
 ????????  : ??
 ?? ?? ??  : VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??2??11??
    ??    ??   : h00133115
    ????????   : ??????????

*****************************************************************************/
VOS_VOID Ndis_DHCPPkt_Proc(VOS_VOID *pRcvMsg)
{
    ADS_NDIS_DATA_IND_STRU  *pstAdsNdisMsg  = (ADS_NDIS_DATA_IND_STRU*)pRcvMsg;
    VOS_UINT8               *pucData;
    NDIS_ENTITY_STRU        *pstNdisEntity;
    VOS_UINT8                ucExRabId;
    VOS_UINT32               ulPktMemLen;

    pucData  = IMM_ZcGetDataPtr(pstAdsNdisMsg->pstSkBuff);
    if (VOS_NULL_PTR == pucData)
    {
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_DHCPPkt_Proc, IMM_ZcGetDataPtr fail!");
        return;
    }
    ulPktMemLen = IMM_ZcGetUsedLen(pstAdsNdisMsg->pstSkBuff);

    ucExRabId = NDIS_FORM_EXBID(pstAdsNdisMsg->enModemId, pstAdsNdisMsg->ucRabId);
    if (PS_SUCC != Ndis_ChkRabIdValid(ucExRabId))
    {
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_DHCPPkt_Proc, Ndis_ChkRabIdValid fail!");
        return;
    }

    pstNdisEntity = NDIS_GetEntityByRabId(ucExRabId);
    if(VOS_NULL_PTR == pstNdisEntity)
    {
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_DHCPPkt_Proc, NDIS_GetEntityByRabId fail!");
        return;
    }

    if (NDIS_ENTITY_IPV4 != (pstNdisEntity->ucRabType & NDIS_ENTITY_IPV4))
    {
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_DHCPPkt_Proc, Rab not support IPV4!");
        return;
    }

    /*DHCP????*/
    NDIS_STAT_UL_RECV_DHCPPKT(1);
    IPV4_DHCP_ProcDhcpPkt(pucData, ucExRabId,ulPktMemLen);

    return;
}
/*****************************************************************************
 ?? ?? ??  : Ndis_FindRabIdBySpePort
 ????????  : ????SpePort????RabId
 ????????  : ??
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??12??9??
    ??    ??   : c00253308
    ????????   : ??????????

*****************************************************************************/
VOS_UINT8 Ndis_FindRabIdBySpePort(VOS_INT32 lPort, VOS_UINT16 usFrameType)
{
    VOS_UINT32                      ulLoop;
    VOS_UINT8                       ucTmpRabType;
    NDIS_ENTITY_STRU               *pstNdisEntity;

    switch(usFrameType)
    {
        case ARP_PAYLOAD:
            ucTmpRabType = NDIS_ENTITY_IPV4;    /*ARP????????SPE*/
            break;
        case IP_PAYLOAD:
            ucTmpRabType = NDIS_ENTITY_IPV4;
            break;
        case IPV6_PAYLOAD:
            ucTmpRabType = NDIS_ENTITY_IPV6;
            break;
        default:
            NDIS_ERROR_LOG1(NDIS_TASK_PID, "Ndis_FindRabIdByHandle, FrameType Error!", usFrameType);
            return NDIS_INVALID_RABID;
    }
    for(ulLoop=0; ulLoop<NAS_NDIS_MAX_ITEM; ulLoop++)
    {
         pstNdisEntity = &g_astNdisEntity[ulLoop];

         if ((lPort == pstNdisEntity->lSpePort)
                && (ucTmpRabType == (pstNdisEntity->ucRabType & ucTmpRabType)))   /*????????????????????????*/
         {
             return pstNdisEntity->ucRabId;
         }
    }

    return NDIS_INVALID_RABID;

}

/*****************************************************************************
 ?? ?? ??  : Ndis_FindRabIdByHandle
 ????????  : ????Handle????RabId
 ????????  : ??
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??12??9??
    ??    ??   : h00159435
    ????????   : ??????????

*****************************************************************************/
VOS_UINT8 Ndis_FindRabIdByHandle(UDI_HANDLE ulhandle, VOS_UINT16 usFrameType)
{
    VOS_UINT32                      ulLoop;
    VOS_UINT8                       ucTmpRabType;
    NDIS_ENTITY_STRU               *pstNdisEntity;

    if ((ARP_PAYLOAD == usFrameType) || (IP_PAYLOAD == usFrameType))
    {
        ucTmpRabType = NDIS_ENTITY_IPV4;
    }
    else if (IPV6_PAYLOAD == usFrameType)
    {
        ucTmpRabType = NDIS_ENTITY_IPV6;
    }
    else
    {
        NDIS_ERROR_LOG1(NDIS_TASK_PID, "Ndis_FindRabIdByHandle, FrameType Error!", usFrameType);
        return NDIS_INVALID_RABID;
    }

    for(ulLoop=0; ulLoop<NAS_NDIS_MAX_ITEM; ulLoop++)
    {
         pstNdisEntity = &g_astNdisEntity[ulLoop];

         if ((ulhandle == pstNdisEntity->ulHandle)
              && (ucTmpRabType == (pstNdisEntity->ucRabType & ucTmpRabType)))   /*????????????????????????*/
         {
             return pstNdisEntity->ucRabId;
         }
    }

    return NDIS_INVALID_RABID;

}

/*****************************************************************************
 ?? ?? ??  : Ndis_UlNcmFrmProc
 ????????  : ??????NCM????????
 ????????  : UDI_HANDLE ulhandle, IMM_ZC_STRU *pstImmZc
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??2??11??
    ??    ??   : h00133115
    ????????   : ??????????

  2.??    ??   : 2013??1??16??
    ??    ??   : h00218138
    ????????   : DSDA????

*****************************************************************************/
VOS_VOID Ndis_UlNcmFrmProc(VOS_UINT8 ucExRabId, IMM_ZC_STRU *pstImmZc)
{
    VOS_UINT16                  usFrameType;
    ETHFRM_IPV4_PKT_STRU       *pstIpPacket;
    ETH_IPFIXHDR_STRU          *pstIpFixHdr;
    VOS_UINT8                  *pucData;
    VOS_UINT32                  ulDataLen;
    VOS_UINT32                  ulIpLen;
    VOS_UINT32                  ulIpv4Flag = 0;
    VOS_UINT32                  ulCacheLen;

    pucData = IMM_ZcGetDataPtr(pstImmZc);
    if (VOS_NULL_PTR == pucData)
    {
        /*lint -e522*/
        IMM_ZcFree(pstImmZc);
        /*lint +e522*/
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_UlNcmFrmProc, IMM_ZcGetDataPtr fail!");
        NDIS_STAT_UL_DISCARD_USBPKT(1);
        return;
    }

    pstIpPacket = (ETHFRM_IPV4_PKT_STRU  *)(VOS_VOID*)pucData;
    usFrameType = pstIpPacket->usFrameType;

    /*ARP????*/
    if(ARP_PAYLOAD == usFrameType)
    {
        /*ARP??????????????????RabId????????RabId????Ndis????????????*/
        (VOS_VOID)Ndis_ProcArpMsg((ETH_ARP_FRAME_STRU*)(VOS_VOID*)pstIpPacket, ucExRabId);

        /*??????ARP??????Imm_ZcFree????ImmZc*/
        /*lint -e522*/
        IMM_ZcFree(pstImmZc);
        /*lint +e522*/

        return;
    }
     /*IPV6??????????*/
    if (IPV6_PAYLOAD == usFrameType)
    {
        ulDataLen = IMM_ZcGetUsedLen(pstImmZc);

        if ((ulDataLen - ETH_MAC_HEADER_LEN) > g_ulNvMtu)
        {
            NDIS_SPE_MEM_UNMAP(pstImmZc, ulDataLen);

            IP_NDSERVER_ProcTooBigPkt(ucExRabId,
                                      ((VOS_UINT8*)pstIpPacket + ETH_MAC_HEADER_LEN),
                                      g_ulNvMtu);

            NDIS_SPE_MEM_MAP(pstImmZc, ulDataLen);

            /*????Imm_ZcFree????ImmZc*/
            /*lint -e522*/
            IMM_ZcFree(pstImmZc);
            /*lint +e522*/

            return;
        }
    }

    if (IP_PAYLOAD == usFrameType)
    {
        ulIpv4Flag = 1;
        ulDataLen  = IMM_ZcGetUsedLen(pstImmZc);
        ulCacheLen = (ulDataLen < NDIS_SPE_CACHE_HDR_SIZE) ?
                        ulDataLen : NDIS_SPE_CACHE_HDR_SIZE;
    }

    /*??MAC??????????????IP????????????MAC??????????ADS*/
    if (VOS_OK != IMM_ZcRemoveMacHead(pstImmZc))
    {
        /*lint -e522*/
        IMM_ZcFree(pstImmZc);
        /*lint +e522*/
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_UlNcmFrmProc, IMM_ZcRemoveMacHead fail!");
        return;
    }

    /*????IPV4????????????Skb????????????????????????Skb??????????IP??????*/
    if (1 == ulIpv4Flag)
    {
        pucData = IMM_ZcGetDataPtr(pstImmZc);
        if (VOS_NULL_PTR == pucData)
        {
            /*lint -e522*/
            IMM_ZcFree(pstImmZc);
            /*lint +e522*/
            return;
        }

        NDIS_SPE_MEM_UNMAP(pstImmZc, ulCacheLen);

        pstIpFixHdr = (ETH_IPFIXHDR_STRU *)((VOS_VOID*)pucData);
        ulIpLen = IP_NTOHS(pstIpFixHdr->usTotalLen);
        if (ulIpLen < pstImmZc->len)
        {
            pstImmZc->tail -= (pstImmZc->len - ulIpLen);
            pstImmZc->len  = ulIpLen;
        }

        NDIS_SPE_MEM_MAP(pstImmZc, ulCacheLen);
    }

    if (VOS_OK != ADS_UL_SendPacket(pstImmZc, ucExRabId))
    {
        /*lint -e522*/
        IMM_ZcFree(pstImmZc);
        /*lint +e522*/
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_UlNcmFrmProc, ADS_UL_SendPacket fail!");
        return;
    }

    NDIS_STAT_UL_SEND_ADSPKT(1);

    return;
}

/*****************************************************************************
 ?? ?? ??  : APP_Ndis_DLPid_InitFunc
 ????????  : APP NDIS????PID??????????
 ????????  : enum VOS_INIT_PHASE_DEFINE ePhase
 ????????  : ??
 ?? ?? ??  : extern VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??2??15??
    ??    ??   : h00133115
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32  APP_Ndis_Pid_InitFunc( enum VOS_INIT_PHASE_DEFINE ePhase)
{
    VOS_UINT32  ulResult = PS_FAIL;

    switch( ePhase )
    {
        case   VOS_IP_LOAD_CONFIG:

            ulResult = Ndis_Init();

            if (PS_SUCC != ulResult)
            {
                PS_PRINTF("APP_Ndis_Pid_InitFunc, Ndis_Init fail!\n");
                return VOS_ERR;
            }
            break;
        case VOS_IP_FARMALLOC:
        case VOS_IP_INITIAL:
        case VOS_IP_ENROLLMENT:
        case VOS_IP_LOAD_DATA:
        case VOS_IP_FETCH_DATA:
        case VOS_IP_STARTUP:
        case VOS_IP_RIVAL:
        case VOS_IP_KICKOFF:
        case VOS_IP_STANDBY:
        case VOS_IP_BROADCAST_STATE:
        case VOS_IP_RESTART:
        case VOS_IP_BUTT:
            break;
        default:
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
 ?? ?? ??  : Ndis_SendMacFrm
 ????????  : ????????????????
 ????????  : ??
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??2??14??
    ??    ??   : h00133115
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 Ndis_SendMacFrm(const VOS_UINT8  *pucBuf, VOS_UINT32 ulLen, VOS_UINT8 ucExRabId)
{
    IMM_ZC_STRU      *pstImmZc = VOS_NULL_PTR;
    VOS_INT32         lRtn;
    UDI_HANDLE        ulHandle;
    VOS_UINT8        *ucPdata;
    NDIS_ENTITY_STRU *pstNdisEntity;

    if (VOS_NULL_PTR == pucBuf)
    {
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_SendMacFrm, pucBuf is NULL!");
        return PS_FAIL;
    }

    pstImmZc = IMM_ZcStaticAlloc(ulLen);
    if (VOS_NULL_PTR == pstImmZc)
    {
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_SendMacFrm, IMM_ZcStaticAlloc fail!");
        return PS_FAIL;
    }

    ucPdata = (VOS_UINT8*)IMM_ZcPut(pstImmZc, ulLen);             /*??yinweidong??????*/
    if (VOS_NULL_PTR == ucPdata)
    {
        /*lint -e522*/
        IMM_ZcFree(pstImmZc);
        /*lint +e522*/
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_SendMacFrm, IMM_ZcPut fail!");
        return PS_FAIL;
    }

    PS_MEM_CPY(ucPdata,pucBuf,ulLen);

    pstNdisEntity = NDIS_GetEntityByRabId(ucExRabId);
    if (VOS_NULL_PTR == pstNdisEntity)
    {
        /*lint -e522*/
        IMM_ZcFree(pstImmZc);
        /*lint +e522*/
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_SendMacFrm, NDIS_GetEntityByRabId fail!");
        return PS_FAIL;
    }

    ulHandle      = pstNdisEntity->ulHandle;

    /*????????*/
    lRtn = NDIS_UDI_WRITE(ulHandle, pstImmZc, ulLen);

    if (0 != lRtn)
    {
        /*lint -e522*/
        IMM_ZcFree(pstImmZc);
        /*lint +e522*/
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_SendMacFrm, udi_write fail!");
        NDIS_STAT_DL_SEND_ARPDHCPPKT_FAIL(1);
        return PS_FAIL;
    }

    return PS_SUCC;
}

/*****************************************************************************
 ?? ?? ??  : Ndis_ProcReqArp
 ????????  : ????ARP Request ??
 ????????  :

 ????????  : ??
 ?? ?? ??  : ????????PS_SUCC;
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??2??11??
    ??    ??   : h00133115
    ????????   : ??????????
  2.??    ??   : 2013??1??22??
  ??    ??   : h00218138
  ????????   : DSDA

*****************************************************************************/

VOS_UINT32 Ndis_ProcReqArp(ETH_ARP_FRAME_STRU *pstReqArp, VOS_UINT8 ucRabId)
{
    VOS_UINT32                  ulTgtIpAddr  = pstReqArp->unTargetIP.ulIpAddr;
    NDIS_ENTITY_STRU           *pstNdisEntity = VOS_NULL_PTR;
    NDIS_IPV4_INFO_STRU        *pstArpV4Info  = VOS_NULL_PTR;

    pstNdisEntity = NDIS_GetEntityByRabId(ucRabId);
    if(VOS_NULL_PTR == pstNdisEntity)
    {
        NDIS_ERROR_LOG1(NDIS_TASK_PID, "Ndis_ProcReqArp,  NDIS_GetEntityByRabId Error!", ucRabId);
        NDIS_STAT_PROC_ARP_FAIL(1);
        return PS_FAIL;
    }

    pstArpV4Info  = &pstNdisEntity->stIpV4Info;

    /*???????????????????????? ??????????????????????????*/
    if ( (ulTgtIpAddr != pstArpV4Info->unGwIpInfo.ulIpAddr)
        && ((ulTgtIpAddr & pstArpV4Info->unNmIpInfo.ulIpAddr) !=
           (pstArpV4Info->unGwIpInfo.ulIpAddr & pstArpV4Info->unNmIpInfo.ulIpAddr)))  /*????????????????????????????*/
    {
        NDIS_ERROR_LOG1(NDIS_TASK_PID, "Ndis_ProcReqArp,  TargetIpaddr Error!", ulTgtIpAddr);
        NDIS_STAT_PROC_ARP_FAIL(1);
        return PS_FAIL;
    }

    if ((0 != pstReqArp->unSenderIP.ulIpAddr)     /*????MAC OS ????ARP????,??Sender IP??0*/
           && (pstArpV4Info->unUeIpInfo.ulIpAddr != pstReqArp->unSenderIP.ulIpAddr))
    {
        /*??UE IP??????????????????????????????*/
        NDIS_ERROR_LOG1(NDIS_TASK_PID, "Ndis_ProcReqArp,  SenderIP Error!", pstReqArp->unSenderIP.ulIpAddr);
        NDIS_STAT_PROC_ARP_FAIL(1);
        return PS_SUCC;
    }

    /*????PC MAC????*/
    PS_MEM_CPY(pstArpV4Info->aucUeMacAddr,pstReqArp->aucSenderAddr,ETH_MAC_ADDR_LEN);
    PS_MEM_CPY(pstArpV4Info->aucMacFrmHdr,pstReqArp->aucSenderAddr,ETH_MAC_ADDR_LEN);

    pstArpV4Info->ulArpInitFlg  = PS_TRUE;

    PS_MEM_CPY(g_stSpeMacHeader.aucSrcAddr,(pstArpV4Info->aucMacFrmHdr + ETH_MAC_ADDR_LEN),ETH_MAC_ADDR_LEN);
    PS_MEM_CPY(g_stSpeMacHeader.aucDstAddr,pstReqArp->aucSrcAddr,ETH_MAC_ADDR_LEN);


    /*????ARP??????????*/
    if ((pstReqArp->unTargetIP.ulIpAddr == pstReqArp->unSenderIP.ulIpAddr)
        || (0 == pstReqArp->unSenderIP.ulIpAddr))
    {
        return PS_SUCC;
    }

    /*????????*/
    PS_MEM_CPY(pstReqArp->aucDstAddr,pstReqArp->aucSrcAddr,ETH_MAC_ADDR_LEN);
    PS_MEM_CPY(pstReqArp->aucTargetAddr,pstReqArp->aucSrcAddr,ETH_MAC_ADDR_LEN);
    pstReqArp->unTargetIP.ulIpAddr = pstReqArp->unSenderIP.ulIpAddr;

    PS_MEM_CPY(pstReqArp->aucSrcAddr, (pstArpV4Info->aucMacFrmHdr + ETH_MAC_ADDR_LEN), ETH_MAC_ADDR_LEN);
    PS_MEM_CPY(pstReqArp->aucSenderAddr, (pstArpV4Info->aucMacFrmHdr + ETH_MAC_ADDR_LEN), ETH_MAC_ADDR_LEN);

    pstReqArp->unSenderIP.ulIpAddr = ulTgtIpAddr;

    /*opcode*/
    pstReqArp->usOpCode = ETH_ARP_RSP_TYPE;

    /*????ARP Reply*/
    NDIS_STAT_DL_SEND_ARP_REPLY(1);
    (VOS_VOID)Ndis_SendMacFrm((VOS_UINT8*)pstReqArp,sizeof(ETH_ARP_FRAME_STRU),ucRabId);

    return PS_SUCC;
}

/*****************************************************************************
 ?? ?? ??  : Ndis_ProcReplyArp
 ????????  : ????ARP Reply ??,????PC??MAC????
 ????????  :

 ????????  : ??
 ?? ?? ??  : ????????PS_SUCC;
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2009??12??31??
    ??    ??   : y00151394
    ????????   : ??????????
  2.??    ??   : 2013??1??22??
    ??    ??   : h00218138
    ????????   : DSDA
*****************************************************************************/
VOS_UINT32 Ndis_ProcReplyArp(const ETH_ARP_FRAME_STRU *pstRspArp, VOS_UINT8 ucRabId)
{
    NDIS_IPV4_INFO_STRU         *pstArpV4Info = VOS_NULL_PTR;
    VOS_UINT32                   ulTargetIP   = pstRspArp->unTargetIP.ulIpAddr;
    NDIS_ENTITY_STRU            *pstNdisEntity;

    pstNdisEntity = NDIS_GetEntityByRabId(ucRabId);
    if(VOS_NULL_PTR == pstNdisEntity)
    {
        NDIS_ERROR_LOG1(NDIS_TASK_PID, "Ndis_ProcReplyArp,  NDIS_GetEntityByRabId Error!", ucRabId);
        return PS_FAIL;
    }

    pstArpV4Info  = &pstNdisEntity->stIpV4Info;

    if (ulTargetIP == pstNdisEntity->stIpV4Info.unGwIpInfo.ulIpAddr)
    {
        /*????PC MAC????*/
        PS_MEM_CPY(pstArpV4Info->aucUeMacAddr,pstRspArp->aucSenderAddr,ETH_MAC_ADDR_LEN);
        PS_MEM_CPY(pstArpV4Info->aucMacFrmHdr,pstRspArp->aucSenderAddr,ETH_MAC_ADDR_LEN);
        pstArpV4Info->ulArpInitFlg  = PS_TRUE;

        pstArpV4Info->ulArpRepFlg = PS_TRUE;

        return PS_SUCC;
    }

    return PS_FAIL;
}

/*****************************************************************************
 ?? ?? ??  : Ndis_Ipv4PdnInfoCfg
 ????????  : IPV4 PDN????????
 ????????  : ??
 ????????  : ??
 ?? ?? ??  :
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??3??15??
    ??    ??   : h00133115
    ????????   : ??????????

*****************************************************************************/
VOS_VOID  Ndis_Ipv4PdnInfoCfg(const AT_NDIS_IPV4_PDN_INFO_STRU *pstNasNdisInfo,
                                           NDIS_ENTITY_STRU  *pstNdisEntity)
{
    NDIS_IPV4_INFO_STRU         *pstIpV4Info    = &(pstNdisEntity->stIpV4Info);

    pstIpV4Info->ulArpInitFlg = PS_FALSE;
    pstIpV4Info->ulArpRepFlg  = PS_FALSE;

    PS_MEM_CPY(pstIpV4Info->unUeIpInfo.aucIPAddr,
               pstNasNdisInfo->stPDNAddrInfo.aucIpV4Addr,
               IPV4_ADDR_LEN);

    PS_MEM_CPY(pstIpV4Info->unGwIpInfo.aucIPAddr,
               pstNasNdisInfo->stGateWayAddrInfo.aucIpV4Addr,
               IPV4_ADDR_LEN);

    PS_MEM_CPY(pstIpV4Info->unNmIpInfo.aucIPAddr,
               pstNasNdisInfo->stSubnetMask.aucIpV4Addr,
               IPV4_ADDR_LEN);

    /*??????????DNS*/
    if (PS_TRUE == pstNasNdisInfo->bitOpDnsPrim)
    {
        PS_MEM_CPY(pstIpV4Info->unPrimDnsAddr.aucIPAddr,
                   pstNasNdisInfo->stDnsPrimAddrInfo.aucIpV4Addr,
                   IPV4_ADDR_LEN);
    }
    else
    {
        pstIpV4Info->unPrimDnsAddr.ulIpAddr = 0;
    }

    /*????????????DNS*/
    if (PS_TRUE == pstNasNdisInfo->bitOpDnsSec)
    {
        PS_MEM_CPY(pstIpV4Info->unSecDnsAddr.aucIPAddr,
                   pstNasNdisInfo->stDnsSecAddrInfo.aucIpV4Addr,
                   IPV4_ADDR_LEN);
    }
    else
    {
        pstIpV4Info->unSecDnsAddr.ulIpAddr = 0;
    }

    /*????????????WINS*/
    if (PS_TRUE == pstNasNdisInfo->bitOpWinsPrim)
    {
        PS_MEM_CPY(pstIpV4Info->unPrimWinsAddr.aucIPAddr,
                   pstNasNdisInfo->stWinsPrimAddrInfo.aucIpV4Addr,
                   IPV4_ADDR_LEN);
    }
    else
    {
        pstIpV4Info->unPrimWinsAddr.ulIpAddr = 0;
    }

    /*????????????WINS*/
    if (PS_TRUE == pstNasNdisInfo->bitOpWinsSec)
    {
        PS_MEM_CPY(pstIpV4Info->unSecWinsAddr.aucIPAddr,
                   pstNasNdisInfo->stWinsSecAddrInfo.aucIpV4Addr,
                   IPV4_ADDR_LEN);
    }
    else
    {
        pstIpV4Info->unSecWinsAddr.ulIpAddr = 0;
    }

    /*PCSCF??????????,??????????*/

    pstIpV4Info->ulIpAssignStatus = IPV4_DHCP_ADDR_STATUS_FREE;

    return;
}

/*****************************************************************************
 ?? ?? ??  : Ndis_StartARPTimer
 ????????  : NDIS??????????ARP??????
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2012??4??19??
    ??    ??   : h00159435
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 Ndis_StartARPTimer(NDIS_ENTITY_STRU *pstNdisEntity)
{
    VOS_UINT32                      ulRtn;
    NDIS_ARP_PERIOD_TIMER_STRU     *pstArpPeriodTimer;

    /*????????????*/
    if (VOS_NULL_PTR == pstNdisEntity)
    {
        return PS_FAIL;
    }

    /*????????????????ARP??????*/
    if ((NDIS_ENTITY_IPV4 != (pstNdisEntity->ucRabType & NDIS_ENTITY_IPV4))
            || (PS_TRUE == pstNdisEntity->stIpV4Info.ulArpInitFlg))
    {
        return PS_SUCC;
    }

    pstArpPeriodTimer = &(pstNdisEntity->stIpV4Info.stArpPeriodTimer);

    /*????????????????????*/
    if (VOS_NULL_PTR != pstArpPeriodTimer->hTm)
    {
        Ndis_StopARPTimer(pstArpPeriodTimer);
    }

    ulRtn = VOS_StartRelTimer(&(pstArpPeriodTimer->hTm),PS_PID_APP_NDIS,pstArpPeriodTimer->ulTimerValue,
                               pstArpPeriodTimer->ulName,0, VOS_RELTIMER_LOOP, VOS_TIMER_PRECISION_0);
    if (VOS_OK != ulRtn)
    {
        pstArpPeriodTimer->hTm = VOS_NULL_PTR;
        return PS_FAIL;
    }

    return PS_SUCC;
}

/*****************************************************************************
 ?? ?? ??  : Ndis_StopARPTimer
 ????????  : NDIS??????????ARP??????
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2012??4??19??
    ??    ??   : h00159435
    ????????   : ??????????

*****************************************************************************/
VOS_VOID Ndis_StopARPTimer(NDIS_ARP_PERIOD_TIMER_STRU *pstArpPeriodTimer)
{
    if (VOS_NULL_PTR != pstArpPeriodTimer->hTm)
    {
        if (VOS_OK != VOS_StopRelTimer(&(pstArpPeriodTimer->hTm)))
        {
            NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_StopARPTimer, VOS_StopRelTimer fail!");
        }
        pstArpPeriodTimer->hTm = VOS_NULL_PTR;
    }

    return;
}

/*****************************************************************************
 ?? ?? ??  : Ndis_SndMsgToAt
 ????????  : ????Cnf??????AT
 ????????  :
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??3??16??
    ??    ??   : h00133115
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 Ndis_SndMsgToAt(const VOS_UINT8 *pucBuf,VOS_UINT16 usMsgLen,VOS_UINT32 ulMsgId)
{
    VOS_UINT32                    ulAllocSize;
    AT_FW_MSG_STRU               *pstFwMsg    = VOS_NULL_PTR;
    AT_FW_CMD_BINARY_MSG_STRU    *pstAtCnf    = VOS_NULL_PTR;
    MsgBlock                     *pstMsgBlock = VOS_NULL_PTR;

    /*??????????????????????????????*/
    ulAllocSize = sizeof(MsgBlock) + sizeof(AT_FW_MSG_STRU)
                  + sizeof(AT_FW_CMD_BINARY_MSG_STRU) + usMsgLen;

    pstMsgBlock = PS_ALLOC_MSG(NDIS_TASK_PID,ulAllocSize);
    if (VOS_NULL_PTR == pstMsgBlock)
    {
        return PS_FAIL;
    }

    /*lint -e826*/
    pstFwMsg          = (AT_FW_MSG_STRU *)(VOS_VOID*)(pstMsgBlock->aucValue);
    pstFwMsg->ulMsgId = ID_MSG_AT_FW_CMD_BINARY_MSG;

    pstAtCnf  = (AT_FW_CMD_BINARY_MSG_STRU  *)((VOS_VOID*)pstFwMsg->pMsgParam);
    /*lint +e826*/
    pstAtCnf->usMsgSize  = usMsgLen;
    pstAtCnf->ulMsgId    = ulMsgId;
    pstAtCnf->ucClientId = EN_AT_FW_CLIENT_ID_NDIS;   /*??MSP??????????*/
    pstAtCnf->ucSysMode  = AT_FW_SYS_MODE_NULL;

    pstMsgBlock->ulSenderPid   = NDIS_TASK_PID;
    pstMsgBlock->ulReceiverPid = APP_AT_PID;

    PS_MEM_CPY(pstAtCnf->pMsg,pucBuf,usMsgLen);

    if(VOS_OK != PS_SEND_MSG(NDIS_TASK_PID, pstMsgBlock))
    {
        /*????????*/
        return PS_FAIL;
    }

    return PS_SUCC;
}

/*****************************************************************************
 ?? ?? ??  : Ndis_ChkRabIdValid
 ????????  : Ndis????ExRabId????????????????????
 ????????  :

 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2012??12??7??
    ??    ??   : h00159435
    ????????   : ??????????

  2.??    ??   : 2013??1??15??
    ??    ??   : h00218138
    ????????   : DSDA????????:??ModemID??RabId????????

*****************************************************************************/
VOS_UINT32 Ndis_ChkRabIdValid(VOS_UINT8 ucExRabId)
{
    VOS_UINT16 usModemId;
    VOS_UINT8 ucRabId;

    usModemId = NDIS_GET_MODEMID_FROM_EXBID(ucExRabId);
    if (usModemId >= MODEM_ID_BUTT)
    {
        return PS_FAIL;
    }

    ucRabId = NDIS_GET_BID_FROM_EXBID(ucExRabId);
    if ((ucRabId < MIN_VAL_EPSID) || (ucRabId > MAX_VAL_EPSID))
    {
        return PS_FAIL;
    }

    return PS_SUCC;
}


/*****************************************************************************
 ?? ?? ??  : NDIS_GetEntityByRabId
 ????????  : ????ExRabId????NDIS????
 ????????  : VOS_UINT8 ucExRabId
 ????????  : ??
 ?? ?? ??  : NDIS_ENTITY_STRU*
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2013??1??15??
    ??    ??   : h00218138
    ????????   : ??????????

*****************************************************************************/
NDIS_ENTITY_STRU* NDIS_GetEntityByRabId(VOS_UINT8 ucExRabId)
{
    VOS_UINT16 i = 0;

    /* ??????????????????Entity */
    do{
        if((PS_TRUE == g_astNdisEntity[i].enUsed) && (ucExRabId == g_astNdisEntity[i].ucRabId))
        {
            /*????????????*/
            return &g_astNdisEntity[i];
        }

    }while((++i) < NAS_NDIS_MAX_ITEM);

    return VOS_NULL_PTR;
}

/*****************************************************************************
 ?? ?? ??  : NDIS_AllocEntity
 ????????  : ??????????????NDIS????
 ????????  : ??
 ????????  : ??
 ?? ?? ??  : NDIS_ENTITY_STRU*
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2013??1??15??
    ??    ??   : h00218138
    ????????   : ??????????

*****************************************************************************/
NDIS_ENTITY_STRU* NDIS_AllocEntity(VOS_VOID)
{
    VOS_UINT16 i = 0;

    /* ????????????????????*/
    do{
        if(PS_FALSE == g_astNdisEntity[i].enUsed)
        {
            /*????????????*/
            return &g_astNdisEntity[i];
        }

    }while((++i) < NAS_NDIS_MAX_ITEM);

    return VOS_NULL_PTR;
}

/*****************************************************************************
 ?? ?? ??  : Ndis_CheckIpv4PdnInfo
 ????????  : PDN IPV4????????????
 ????????  : AT_NDIS_IPV4_PDN_INFO_STRU
 ????????  :
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??12??11??
    ??    ??   : h00159435
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 Ndis_CheckIpv4PdnInfo(const AT_NDIS_IPV4_PDN_INFO_STRU *pstIpv4PdnInfo)
{
    if (PS_FALSE == pstIpv4PdnInfo->bitOpPdnAddr)
    {
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_CheckIpv4PdnInfo,  pstIpv4PdnInfo->bitOpPdnAddr is false!");
        return PS_FAIL;
    }

    /*PDN??????????????????????0??????????*/
    if (0 == VOS_MemCmp(pstIpv4PdnInfo->stPDNAddrInfo.aucIpV4Addr, g_aucInvalidAddr, IPV4_ADDR_LEN))
    {
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_CheckIpv4PdnInfo,  stPDNAddrInfo all zero!");
        return PS_FAIL;
    }

    if (0 == VOS_MemCmp(pstIpv4PdnInfo->stGateWayAddrInfo.aucIpV4Addr, g_aucInvalidAddr, IPV4_ADDR_LEN))
    {
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_CheckIpv4PdnInfo,  stGateWayAddrInfo all zero!");
        return PS_FAIL;
    }

    return PS_SUCC;
}

/*****************************************************************************
 ?? ?? ??  : Ndis_PdnCheckParaValid
 ????????  : ????????????????????????
 ????????  : ??
 ????????  : ??
 ?? ?? ??  :
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??12??23??
    ??    ??   : LPDCP_CIPHERINFO_FOR_ACC
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32  Ndis_PdnV4PdnCfg( const AT_NDIS_PDNINFO_CFG_REQ_STRU *pstNasNdisInfo,
                                     NDIS_ENTITY_STRU  *pstNdisEntity)
{
    /*IPV4????????*/
    if (PS_FALSE == pstNasNdisInfo->bitOpIpv4PdnInfo)  /*????????IPV4???????? */
    {
        NDIS_INFO_LOG(NDIS_TASK_PID, "Ndis_PdnV4PdnCfg,  bitOpIpv4PdnInfo is false!");
        return PS_FAIL;
    }

    if (PS_SUCC != Ndis_CheckIpv4PdnInfo(&(pstNasNdisInfo->stIpv4PdnInfo)))
    {
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_PdnV4PdnCfg,  Ndis_CheckIpv4PdnInfo fail!");
        return PS_FAIL;
    }

    Ndis_Ipv4PdnInfoCfg(&(pstNasNdisInfo->stIpv4PdnInfo),pstNdisEntity);

    /*????NDIS????????????*/
    pstNdisEntity->ucRabType |= NDIS_ENTITY_IPV4;

    return PS_SUCC;
}

/*****************************************************************************
 ?? ?? ??  : Ndis_PdnV6PdnCfg
 ????????  : IPV6 PDN????????
 ????????  : ??
 ????????  : ??
 ?? ?? ??  :
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??12??23??
    ??    ??   : h00159435
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32  Ndis_PdnV6PdnCfg( AT_NDIS_PDNINFO_CFG_REQ_STRU *pstNasNdisInfo,
                                     NDIS_ENTITY_STRU  *pstNdisEntity)
{
    VOS_UINT8                       ucExRabId;

    /*IPV6????????*/
    if (PS_FALSE == pstNasNdisInfo->bitOpIpv6PdnInfo)  /*????????IPV6????????*/
    {
        NDIS_INFO_LOG(NDIS_TASK_PID, "Ndis_PdnV6PdnCfg,  bitOpIpv6PdnInfo is false!");
        return PS_FAIL;
    }

    ucExRabId = NDIS_FORM_EXBID(pstNasNdisInfo->enModemId, pstNasNdisInfo->ucRabId);

    if (PS_SUCC != NdSer_CheckIpv6PdnInfo(&(pstNasNdisInfo->stIpv6PdnInfo)))
    {
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_PdnV6PdnCfg,  NdSer_CheckIpv6PdnInfo fail!");
        return PS_FAIL;
    }

    /*??ND SERVER API  ????IPV6??????????ND SERVER*/
    NdSer_Ipv6PdnInfoCfg(ucExRabId, &(pstNasNdisInfo->stIpv6PdnInfo));

    /*????NDIS????????*/
    pstNdisEntity->ucRabType |= NDIS_ENTITY_IPV6;

    return PS_SUCC;
}

/*****************************************************************************
 ?? ?? ??  : Ndis_AtCnfResultProc
 ????????  : NDIS??AT??????????????????????
 ????????  :

 ????????  : ??
 ?? ?? ??  : ????????PS_SUCC;
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2012??4??25??
    ??    ??   : h00159435
    ????????   : ??????????

*****************************************************************************/
VOS_UINT8 Ndis_AtCnfResultProc(const AT_NDIS_PDNINFO_CFG_REQ_STRU *pstNasNdisInfo, VOS_UINT32 ulV4Ret, VOS_UINT32 ulV6Ret)
{
    VOS_UINT8  enResult;

    /*??????????????AT????????CNF????*/
    if ((PS_TRUE == pstNasNdisInfo->bitOpIpv4PdnInfo) &&(PS_TRUE == pstNasNdisInfo->bitOpIpv6PdnInfo))
    {
        if ((PS_SUCC == ulV4Ret) &&(PS_SUCC == ulV6Ret))        /*IPV4??IPV6??????????*/
        {
            enResult = AT_NDIS_PDNCFG_CNF_SUCC;
        }
        else if (PS_SUCC == ulV4Ret)                             /*????IPV4????????*/
        {
            enResult = AT_NDIS_PDNCFG_CNF_IPV4ONLY_SUCC;
        }
        else                                                     /*????IPV6????????*/
        {
            enResult = AT_NDIS_PDNCFG_CNF_IPV6ONLY_SUCC;
        }
    }
    else if (PS_TRUE == pstNasNdisInfo->bitOpIpv4PdnInfo)  /*????????IPV4*/
    {
        enResult = AT_NDIS_PDNCFG_CNF_IPV4ONLY_SUCC;
    }
    else                                                   /*????????IPV6*/
    {
        enResult = AT_NDIS_PDNCFG_CNF_IPV6ONLY_SUCC;
    }

    return enResult;
}
/*****************************************************************************
 ?? ?? ??  : Ndis_PdnInfoCfgProc
 ????????  : PDN????????????????
 ????????  :

 ????????  : ??
 ?? ?? ??  : ????????PS_SUCC;
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??12??31??
    ??    ??   : h00159435
    ????????   : ??????????

  2.??    ??   : 2013??1??15??
    ??    ??   : h00218138
    ????????   : DSDA??????????????????????????ModemId??????

*****************************************************************************/
VOS_VOID Ndis_PdnInfoCfgProc(const AT_FW_CMD_BINARY_MSG_STRU *pstAtReq)
{
    VOS_UINT8                       ucExRabId;
    UDI_HANDLE                      ulHandle;
    NDIS_ENTITY_STRU               *pstNdisEntity;
    AT_NDIS_PDNINFO_CFG_CNF_STRU    stCfgCnf;
    VOS_UINT32                      ulV4Ret;
    VOS_UINT32                      ulV6Ret;
    VOS_INT32                       lSpePort;
    VOS_UINT32                      ulSpeIpfFlag;
    /*lint -e826*/
    AT_NDIS_PDNINFO_CFG_REQ_STRU   *pstNasNdisInfo = (AT_NDIS_PDNINFO_CFG_REQ_STRU *)pstAtReq->pMsg;
    /*lint +e826*/

    NDIS_INFO_LOG(NDIS_TASK_PID, "Ndis_PdnInfoCfgProc entered!");

    /*??????????RabId*/
    ucExRabId  = NDIS_FORM_EXBID(pstNasNdisInfo->enModemId, pstNasNdisInfo->ucRabId);
    ulHandle = pstNasNdisInfo->ulHandle;
    lSpePort = pstNasNdisInfo->lSpePort;
    ulSpeIpfFlag = pstNasNdisInfo->ulIpfFlag;

    stCfgCnf.enResult  = AT_NDIS_PDNCFG_CNF_FAIL;
    stCfgCnf.ucRabId   = pstNasNdisInfo->ucRabId;
    stCfgCnf.enModemId = pstNasNdisInfo->enModemId;

    /*ExRabId????????????????????????????????????????AT????????????*/
    if (PS_SUCC != Ndis_ChkRabIdValid(ucExRabId))
    {
        (VOS_VOID)Ndis_SndMsgToAt((VOS_UINT8*)&stCfgCnf,sizeof(AT_NDIS_PDNINFO_CFG_CNF_STRU),ID_AT_NDIS_PDNINFO_CFG_CNF);
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_PdnInfoCfgProc,  Ndis_ChkRabIdValid fail!");
        return;
    }

    /*????????ExRabId????????NDIS??????????????????????NDIS????*/
    pstNdisEntity = NDIS_GetEntityByRabId(ucExRabId);
    if(VOS_NULL_PTR == pstNdisEntity)
    {
        /*??????????????????NDIS????????????*/
        pstNdisEntity = NDIS_AllocEntity();
        if(VOS_NULL_PTR == pstNdisEntity)
        {
            /*??AT????PDN????????*/
            (VOS_VOID)Ndis_SndMsgToAt((VOS_UINT8*)&stCfgCnf,sizeof(AT_NDIS_PDNINFO_CFG_CNF_STRU),ID_AT_NDIS_PDNINFO_CFG_CNF);
            NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_PdnInfoCfgProc,  NDIS_AllocEntity failed!");
            return;
        }

        /*????????????????????NDIS????????????????*/
        pstNdisEntity->ucRabType= NDIS_RAB_NULL;
        pstNdisEntity->ulHandle = NDIS_INVALID_HANDLE;
        pstNdisEntity->lSpePort = NDIS_INVALID_SPEPORT;
        pstNdisEntity->ulSpeIpfFlag= PS_FALSE;
    }

    ulV4Ret = Ndis_PdnV4PdnCfg(pstNasNdisInfo,pstNdisEntity);
    ulV6Ret = Ndis_PdnV6PdnCfg(pstNasNdisInfo,pstNdisEntity);

    if ((PS_FAIL == ulV6Ret) && (PS_FAIL == ulV4Ret))   /*????IPV4??IPV6??????????????????????????????????*/
    {
        /*??AT????PDN????????*/
        (VOS_VOID)Ndis_SndMsgToAt((VOS_UINT8*)&stCfgCnf,sizeof(AT_NDIS_PDNINFO_CFG_CNF_STRU),ID_AT_NDIS_PDNINFO_CFG_CNF);
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_PdnInfoCfgProc,  Ipv4 and Ipv6 Cfg all fail!");
        return;
    }

    pstNdisEntity->enUsed = PS_TRUE;      /*??????NDIS??????????????*/
    pstNdisEntity->ucRabId  = ucExRabId;  /*??????RabId????????NDIS??????*/
    pstNdisEntity->ulHandle = ulHandle;   /*????Handle??NDIS??????*/
    pstNdisEntity->lSpePort = lSpePort;   /*????SPE Port??NDIS??????*/
    pstNdisEntity->ulSpeIpfFlag = ulSpeIpfFlag;

    stCfgCnf.enResult  = Ndis_AtCnfResultProc(pstNasNdisInfo, ulV4Ret, ulV6Ret);
    stCfgCnf.ucRabType = pstNdisEntity->ucRabType;

    /*????????????ARP????????*/
    if (PS_SUCC != Ndis_StartARPTimer(pstNdisEntity))
    {
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_ConfigArpInfo StartTmr Failed!");
        return;
    }

    pstNdisEntity->lSpePort = NDIS_INVALID_SPEPORT;
    /*??ADS????????????:??????????*/
    if (VOS_OK != (ADS_DL_RegDlDataCallback(ucExRabId, Ndis_DlAdsDataRcv, 0)))
    {
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_PdnInfoCfgProc, ADS_DL_RegDlDataCallback fail!");
        return;
    }

    /*lint -e718*/
    if (VOS_OK != NDIS_UDI_IOCTL (pstNdisEntity->ulHandle, NCM_IOCTL_REG_UPLINK_RX_FUNC, AppNdis_UsbReadCb))
    {
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_PdnInfoCfgProc, regist AppNdis_UsbReadCb fail!");
        return;
    }
    /*lint +e718*/

    (VOS_VOID)Ndis_SndMsgToAt((VOS_UINT8*)&stCfgCnf,sizeof(AT_NDIS_PDNINFO_CFG_CNF_STRU),ID_AT_NDIS_PDNINFO_CFG_CNF);

    return;
}

/*****************************************************************************
 ?? ?? ??  : Ndis_PdnRel
 ????????  : PDN????
 ????????  :

 ????????  : ??
 ?? ?? ??  : ????????PS_SUCC;
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??12??7??
    ??    ??   : h00159435
    ????????   : ??????????????

  1.??    ??   : 2013??1??15??
    ??    ??   : h00218138
    ????????   : DSDA????????:

*****************************************************************************/
VOS_VOID Ndis_PdnRel(const AT_FW_CMD_BINARY_MSG_STRU *pstAtReq)
{
    VOS_UINT8                      ucExRabId;
    NDIS_ENTITY_STRU              *pstNdisEntity;
    NDIS_ARP_PERIOD_TIMER_STRU    *pstArpPeriodTimer;
    /*lint -e826*/
    AT_NDIS_PDNINFO_REL_REQ_STRU  *pstNasNdisRel = (AT_NDIS_PDNINFO_REL_REQ_STRU  *)pstAtReq->pMsg;
    /*lint +e826*/
    AT_NDIS_PDNINFO_REL_CNF_STRU   stRelCnf;

    NDIS_INFO_LOG(NDIS_TASK_PID, "Ndis_PdnRel entered!");

    stRelCnf.enResult  = AT_NDIS_FAIL;
    stRelCnf.ucRabId   = pstNasNdisRel->ucRabId;
    stRelCnf.enModemId = pstNasNdisRel->enModemId;

    ucExRabId = NDIS_FORM_EXBID(pstNasNdisRel->enModemId, pstNasNdisRel->ucRabId);
    if (PS_FAIL == Ndis_ChkRabIdValid(ucExRabId))
    {
        (VOS_VOID)Ndis_SndMsgToAt((VOS_UINT8*)&stRelCnf,sizeof(AT_NDIS_PDNINFO_REL_CNF_STRU),ID_AT_NDIS_PDNINFO_REL_CNF);
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_PdnRel,  Ndis_ChkRabIdValid fail!");
        return;
    }

    pstNdisEntity = NDIS_GetEntityByRabId(ucExRabId);
    if(VOS_NULL_PTR == pstNdisEntity)
    {
        (VOS_VOID)Ndis_SndMsgToAt((VOS_UINT8*)&stRelCnf,sizeof(AT_NDIS_PDNINFO_REL_CNF_STRU),ID_AT_NDIS_PDNINFO_REL_CNF);
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_PdnRel,  NDIS_GetEntityByRabId failed!");
        return;
    }

    pstArpPeriodTimer = &(pstNdisEntity->stIpV4Info.stArpPeriodTimer);

    stRelCnf.ucRabType = pstNdisEntity->ucRabType;

    /*??????????ARP??????????????????????*/
    Ndis_StopARPTimer(pstArpPeriodTimer);

    /*????ND SERVER API ??????RabId????ND SERVER????*/
    if (NDIS_ENTITY_IPV6 == (pstNdisEntity->ucRabType & NDIS_ENTITY_IPV6))
    {
        NdSer_Ipv6PdnRel(ucExRabId);
    }

    /*??????RabId????NDIS????????*/
    pstNdisEntity->ucRabType = NDIS_RAB_NULL;
    pstNdisEntity->ucRabId   = NDIS_INVALID_RABID;
    pstNdisEntity->ulHandle  = NDIS_INVALID_HANDLE;
    pstNdisEntity->enUsed    = PS_FALSE;
    pstNdisEntity->lSpePort = NDIS_INVALID_SPEPORT;
    pstNdisEntity->ulSpeIpfFlag = PS_FALSE;

    /*NDIS??AT????????????????*/
    stRelCnf.enResult  = AT_NDIS_SUCC;
    (VOS_VOID)Ndis_SndMsgToAt((VOS_UINT8*)&stRelCnf,sizeof(AT_NDIS_PDNINFO_REL_CNF_STRU),ID_AT_NDIS_PDNINFO_REL_CNF);

    return;
}

/*NDIS ARP PROC Begin*/
/*****************************************************************************
 ?? ?? ??  : Ndis_SendRequestArp
 ????????  : ????ARP Request ????Ethenet??
 ????????  :

 ????????  : ??
 ?? ?? ??  : ????????PS_SUCC;
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2009??12??31??
    ??    ??   : y00151394
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32  Ndis_SendRequestArp(NDIS_IPV4_INFO_STRU  *pstArpInfoItem, VOS_UINT8 ucExRabId)
{
    ETH_ARP_FRAME_STRU  stArpReq;

    /*??????????????Req????????Reply????*/
    if (PS_FALSE == pstArpInfoItem->ulArpRepFlg)
    {
        NDIS_STAT_ARPREPLY_NOTRECV(1);
        /*??????????????*/
    }

    PS_MEM_SET((VOS_UINT8*)&stArpReq, 0, sizeof(ETH_ARP_FRAME_STRU));

    /*??ARP Request*/
    PS_MEM_CPY(stArpReq.aucDstAddr,g_aucBroadCastAddr,ETH_MAC_ADDR_LEN);
    PS_MEM_CPY(stArpReq.aucSrcAddr,pstArpInfoItem->aucMacFrmHdr+ETH_MAC_ADDR_LEN, ETH_MAC_ADDR_LEN);
    stArpReq.usFrameType = ARP_PAYLOAD;

    /*??????????????*/
    PS_MEM_CPY(((VOS_UINT8*)&stArpReq + ETH_MAC_HEADER_LEN),g_aucArpReqFixVal, ETH_ARP_FIXED_MSG_LEN);

    /*Payload??????MAC????????*/
    PS_MEM_SET(stArpReq.aucTargetAddr,0,ETH_MAC_ADDR_LEN);
    PS_MEM_CPY(stArpReq.aucSenderAddr,pstArpInfoItem->aucMacFrmHdr+ETH_MAC_ADDR_LEN,ETH_MAC_ADDR_LEN);

    /*????IP*/
    stArpReq.unSenderIP.ulIpAddr = pstArpInfoItem->unGwIpInfo.ulIpAddr;
    stArpReq.unTargetIP.ulIpAddr = pstArpInfoItem->unUeIpInfo.ulIpAddr;

    if (PS_SUCC != Ndis_SendMacFrm((VOS_UINT8*)&stArpReq,sizeof(ETH_ARP_FRAME_STRU),ucExRabId))
    {
        pstArpInfoItem->ulArpRepFlg = PS_TRUE;
        NDIS_STAT_DL_SEND_ARP_REQUEST_FAIL(1);
        return PS_FAIL;
    }

    NDIS_STAT_DL_SEND_ARP_REQUEST_SUCC(1);

    pstArpInfoItem->ulArpRepFlg = PS_FALSE;

    return PS_SUCC;
}

/*****************************************************************************
 ?? ?? ??  : Ndis_ProcArpMsg
 ????????  : ??????????????????ARP??
 ????????  :

 ????????  : ??
 ?? ?? ??  : ????????PS_SUCC;
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2009??12??31??
    ??    ??   : y00151394
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 Ndis_ProcArpMsg(ETH_ARP_FRAME_STRU* pstArpMsg, VOS_UINT8 ucRabId)
{
    /*Arp Request*/
    if(0 == VOS_MemCmp((VOS_UINT8*)pstArpMsg + ETH_MAC_HEADER_LEN,g_aucArpReqFixVal, ETH_ARP_FIXED_MSG_LEN))
    {
        NDIS_STAT_UL_RECV_ARP_REQUEST(1);
        return Ndis_ProcReqArp(pstArpMsg, ucRabId);
    }
    /*ARP Reply*/
    else if(0 == VOS_MemCmp((VOS_UINT8*)pstArpMsg + ETH_MAC_HEADER_LEN,g_aucArpRspFixVal,ETH_ARP_FIXED_MSG_LEN))
    {
        NDIS_STAT_DL_RECV_ARP_REPLY(1);
        return Ndis_ProcReplyArp(pstArpMsg, ucRabId);
    }
    else
    {
        NDIS_STAT_PROC_ARP_FAIL(1);
        return PS_FAIL;
    }
}

/*****************************************************************************
 ?? ?? ??  : Ndis_AtMsgProc
 ????????  :
 ????????  : const MsgBlock *pMsgBlock
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??3??16??
    ??    ??   : h00133115
    ????????   : ??????????

*****************************************************************************/
VOS_VOID Ndis_AtMsgProc( const MsgBlock *pMsgBlock )
{
    /*lint -e826*/
    AT_FW_MSG_STRU                   *pstAtFw  = (AT_FW_MSG_STRU *)((VOS_VOID*)(pMsgBlock->aucValue));
    /*lint +e826*/
    AT_FW_CMD_BINARY_MSG_STRU        *pstAtMsg;
    AT_NDIS_MSG_TYPE_ENUM_UINT32      ulMsgId;

    if (ID_MSG_AT_FW_CMD_BINARY_MSG != pstAtFw->ulMsgId)
    {
        PS_PRINTF("Ndis_AtMsgProc: Fw msg type Error,ID is %x!",pstAtFw->ulMsgId);
        return;
    }
    pstAtMsg  = (AT_FW_CMD_BINARY_MSG_STRU*)(VOS_VOID*)pstAtFw->pMsgParam;
    ulMsgId  = pstAtMsg->ulMsgId;

    switch (ulMsgId)
    {
        case ID_AT_NDIS_PDNINFO_CFG_REQ :/*??????????????????AT??????????*/
            Ndis_PdnInfoCfgProc(pstAtMsg);
            break;

        case ID_AT_NDIS_PDNINFO_REL_REQ :
            Ndis_PdnRel(pstAtMsg);
            break;

        default:
            NDIS_WARNING_LOG(NDIS_TASK_PID, "Ndis_AtMsgProc:Error Msg!");
            break;
    }

    return;
}

/*****************************************************************************
 ?? ?? ??  : Ndis_AdsMsgProc
 ????????  : NDIS????ADS????????????
 ????????  : MsgBlock* pMsgBlock
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??12??15??
    ??    ??   : h00159435
    ????????   : ??????????

*****************************************************************************/
VOS_VOID Ndis_AdsMsgProc(const MsgBlock* pMsgBlock )
{
    ADS_NDIS_DATA_IND_STRU  *pstAdsNdisMsg  = (ADS_NDIS_DATA_IND_STRU*)(VOS_VOID*)pMsgBlock;

    if (VOS_NULL_PTR == pstAdsNdisMsg->pstSkBuff)
    {
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_AdsMsgProc recv NULL PTR!");
        return;
    }

    if (ID_ADS_NDIS_DATA_IND != pstAdsNdisMsg->enMsgId)
    {
        /*lint -e522*/
        IMM_ZcFree(pstAdsNdisMsg->pstSkBuff);
        /*lint +e522*/
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_AdsMsgProc, MsgId error!");
        return;
    }

    switch (pstAdsNdisMsg->enIpPacketType)
    {
        case ADS_NDIS_IP_PACKET_TYPE_DHCPV4:                                     /*DHCP??*/
             Ndis_DHCPPkt_Proc(pstAdsNdisMsg);
             break;
        case ADS_NDIS_IP_PACKET_TYPE_DHCPV6:                                     /*DHCPV6??*/
             NdSer_DhcpV6PktProc(pstAdsNdisMsg);
             break;
        case ADS_NDIS_IP_PACKET_TYPE_ICMPV6:                                     /*ND??ECHO REQUEST??*/
             NdSer_NdAndEchoPktProc(pstAdsNdisMsg);
             break;

        default:
             NDIS_WARNING_LOG1(NDIS_TASK_PID, "Ndis_AdsMsgProc:Other Msg!", pstAdsNdisMsg->enIpPacketType);
             break;
    }

     /*??????????????ImmZc*/
     /*lint -e522*/
     IMM_ZcFree(pstAdsNdisMsg->pstSkBuff);
     /*lint +e522*/

    return;
}

/*****************************************************************************
 ?? ?? ??  : APP_Ndis_PidMsgProc
 ????????  : NDIS??????????????????????
 ????????  : MsgBlock* pMsgBlock
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??2??15??
    ??    ??   : h00133115
    ????????   : ??????????

*****************************************************************************/
VOS_VOID APP_Ndis_PidMsgProc(const MsgBlock* pMsgBlock )
{
    if (VOS_NULL_PTR == pMsgBlock)
    {
        PS_PRINTF("Error:APP_Ndis_DLPidMsgProc Parameter pRcvMsg is NULL!");
        return ;
    }

    switch (pMsgBlock->ulSenderPid)
    {
        case DOPRA_PID_TIMER:
            /*lint -e826*/
            Ndis_ProcTmrMsg((REL_TIMER_MSG *)pMsgBlock);
            /*lint +e826*/
            break;

        case APP_AT_PID:
            Ndis_AtMsgProc(pMsgBlock);
            break;

        case ACPU_PID_ADS_UL:          /*ADS????OSA????????DHCP??ND SERVER????NDIS????*/
            Ndis_AdsMsgProc(pMsgBlock);
            break;

        default:
            NDIS_WARNING_LOG(NDIS_TASK_PID,"Warning:APP_Ndis_PidMsgProc Recv not expected msg!");
            break;
    }

    return ;
}

/*lint -e40*/
/*****************************************************************************
 ?? ?? ??  : APP_NDIS_FidInit
 ????????  : NDIS??FID??????????
 ????????  : enum VOS_INIT_PHASE_DEFINE enPhase
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2008??9??17??
    ??    ??   : d00130305
    ????????   : ??????????
*****************************************************************************/
VOS_UINT32 APP_NDIS_FidInit(enum VOS_INIT_PHASE_DEFINE enPhase)
{
    VOS_UINT32  ulResult = PS_FAIL;

    switch (enPhase)
    {
        case   VOS_IP_LOAD_CONFIG:

            /*????NDIS PID*/
            ulResult = VOS_RegisterPIDInfo(NDIS_TASK_PID,
                                           (Init_Fun_Type)APP_Ndis_Pid_InitFunc,
                                           (Msg_Fun_Type)APP_Ndis_PidMsgProc);
            if (VOS_OK != ulResult)
            {
                PS_PRINTF("APP_NDIS_FidInit, register NDIS PID fail!\n");
                return VOS_ERR;
            }

            /*????PPP PID*/
            ulResult = VOS_RegisterPIDInfo(PS_PID_APP_PPP,
                                (Init_Fun_Type)PppInit,
                                (Msg_Fun_Type)PppMsgProc);

            if (VOS_OK != ulResult)
            {
                PS_PRINTF("APP_NDIS_FidInit, register PPP PID fail!\n");
                return VOS_ERR;
            }


            /*????ND SERVER PID*/
            ulResult = VOS_RegisterPIDInfo(NDIS_NDSERVER_PID,
                                                       (Init_Fun_Type)APP_NdServer_Pid_InitFunc,
                                                       (Msg_Fun_Type)APP_NdServer_PidMsgProc);
            if (VOS_OK != ulResult)
            {
                PS_PRINTF("APP_NDIS_FidInit, register NDSERVER PID fail!\n");
                return VOS_ERR;
            }

            /*????DIPC PID*/
            ulResult = VOS_RegisterPIDInfo(PS_PID_APP_DIPC,
                        (Init_Fun_Type)DIPC_Pid_InitFunc,
                        (Msg_Fun_Type)DIPC_AtMsgProc);

            if (VOS_OK != ulResult)
            {
                PS_PRINTF("APP_NDIS_FidInit, register DIPC PID fail!\n");
                return VOS_ERR;
            }

            /*????MUX PID*/
            ulResult = VOS_RegisterPIDInfo(PS_PID_APP_MUX,
                        (Init_Fun_Type)MUX_Pid_InitFunc,
                        (Msg_Fun_Type)MUX_AtMsgProc);

            if (VOS_OK != ulResult)
            {
                PS_PRINTF("APP_NDIS_FidInit, register MUX PID fail!\n");
                return VOS_ERR;
            }

            ulResult = VOS_RegisterMsgTaskPrio(NDIS_TASK_FID, VOS_PRIORITY_P4);
            if( VOS_OK != ulResult )
            {
                PS_PRINTF("APP_NDIS_FidInit, register priority fail!\n");
                return VOS_ERR;
            }
            break;
        case   VOS_IP_FARMALLOC:
        case   VOS_IP_INITIAL:
        case   VOS_IP_ENROLLMENT:
        case   VOS_IP_LOAD_DATA:
        case   VOS_IP_FETCH_DATA:
        case   VOS_IP_STARTUP:
        case   VOS_IP_RIVAL:
        case   VOS_IP_KICKOFF:
        case   VOS_IP_STANDBY:
        case   VOS_IP_BROADCAST_STATE:
        case   VOS_IP_RESTART:
        case   VOS_IP_BUTT:
            break;
        default:
            break;
    }

    return PS_SUCC;
}
/*lint +e40*/

/*****************************************************************************
 Function Name  : Ndis_MsgHook
 Discription    :
 Input          : None
 Output         : None
 Return         : None

 History:
      1. z0103912   2010-05-20  ????

*****************************************************************************/
VOS_UINT32 Ndis_MsgHook (VOS_UINT8 *pucData,VOS_UINT32 ulLength,
     AT_NDIS_MSG_TYPE_ENUM_UINT32 enMsgId)
{
/* OM??????????,HOOK????????????????????OSA???? */

    DIAG_TraceReport((VOS_VOID *)pucData);
    return VOS_OK;

}
VOS_UINT32 g_ulGUNdisOMSwitch = PS_FALSE;
VOS_VOID GU_NDIS_OM_SWITCH_ON(VOS_VOID)
{
    g_ulGUNdisOMSwitch = PS_TRUE;
    return;
}

VOS_VOID GU_NDIS_OM_SWITCH_OFF(VOS_VOID)
{
    g_ulGUNdisOMSwitch = PS_FALSE;
    return;
}

/*======================================????????==============================*/
/*****************************************************************************
 ?? ?? ??  : Ndis_ShowAppDataInfo
 ????????  : ??????????????????????
 ????????  : VOS_VOID
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2009??6??16??
    ??    ??   : ???? 00133115
    ????????   : ??????????
????????      :
  2.??    ??   : 2013??1??22??
    ??    ??   : h00218138
    ????????   : DSDA

*****************************************************************************/
VOS_VOID Ndis_ShowStat(VOS_VOID)
{
    PS_PRINTF("????????????????????:                %d\n", g_stNdisStatStru.ulDicardUsbFrmNum);
    PS_PRINTF("????????????USB????????:             %d\n", g_stNdisStatStru.ulRecvUsbPktSuccNum);
    PS_PRINTF("??????????ADS????????????:           %d\n", g_stNdisStatStru.ulSendPktToAdsSucNum);
    PS_PRINTF("??????????ADS??????????????:         %d\n", g_stNdisStatStru.ulDicardAdsPktNum);
    PS_PRINTF("????????????ADS??????????????:       %d\n", g_stNdisStatStru.ulRecvAdsPktSuccNum);
    PS_PRINTF("????????IPV6 MAC????????????:        %d\n", g_stNdisStatStru.ulGetIpv6MacFailNum);
    PS_PRINTF("??????????????????????????????????:  %d\n", g_stNdisStatStru.ulDlPktDiffRabNum);
    PS_PRINTF("????????MAC??????????:               %d\n", g_stNdisStatStru.ulAddMacHdrFailNum);
    PS_PRINTF("??????????????????????????:          %d\n", g_stNdisStatStru.ulDlSendPktFailNum);
    PS_PRINTF("??????????????????????????:          %d\n", g_stNdisStatStru.ulDlSendPktSuccNum);

    PS_PRINTF("\n????DHCP??????:                      %d\n", g_stNdisStatStru.ulRecvDhcpPktNum);
    PS_PRINTF("????ARP Request??????:               %d\n", g_stNdisStatStru.ulRecvArpReq);
    PS_PRINTF("????ARP Reply  ??????:               %d\n", g_stNdisStatStru.ulRecvArpReply);
    PS_PRINTF("???????? ARP   ??????:               %d\n", g_stNdisStatStru.ulProcArpError);
    PS_PRINTF("????ARP Request??????????:           %d\n", g_stNdisStatStru.ulSendArpReqSucc);
    PS_PRINTF("????ARP Request??????????:           %d\n", g_stNdisStatStru.ulSendArpReqFail);
    PS_PRINTF("????ARP Req??????ARP Reply????:      %d\n", g_stNdisStatStru.ulArpReplyNotRecv);
    PS_PRINTF("????ARP Reply?? ????:                %d\n", g_stNdisStatStru.ulSendArpReply);
    PS_PRINTF("????ARP??DHCP??ND??????????:         %d\n", g_stNdisStatStru.ulSendArpDhcpNDFailNum);

    return;
}

/*****************************************************************************
 ?? ?? ??  : Ndis_PrintIpAddr
 ????????  : ????IP????????
 ????????  : VOS_VOID
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2009??6??16??
    ??    ??   : ???? 00133115
    ????????   : ??????????

*****************************************************************************/
VOS_VOID Ndis_PrintIpv4Addr(const VOS_UINT8 *pIpaddr)
{
    if ((pIpaddr[0] == 0) && (pIpaddr[1] == 0) && (pIpaddr[2] == 0) && (pIpaddr[3] == 0) )
    {
         PS_PRINTF("                      ??????????  %d\n");
         return;
    }

    PS_PRINTF("                      IPV4????????????: %d.%d.%d.%d\n",(VOS_UINT32)pIpaddr[0],
                        (VOS_UINT32)pIpaddr[1],(VOS_UINT32)pIpaddr[2],(VOS_UINT32)pIpaddr[3]);

    return;
}

/*****************************************************************************
 ?? ?? ??  : Ndis_ShowValidEntity
 ????????  : ??????????????????
 ????????  : VOS_VOID
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??3??16??
    ??    ??   : ???? 00133115
    ????????   : ??????????

*****************************************************************************/
VOS_VOID Ndis_ShowValidEntity(VOS_UINT16 usModemId, VOS_UINT8 ucRabId)
{
    NDIS_ENTITY_STRU     *pstEntity;
    VOS_UINT8            ucExRabId;

    ucExRabId = NDIS_FORM_EXBID(usModemId, ucRabId);
    pstEntity  =  NDIS_GetEntityByRabId(ucExRabId);
    if(VOS_NULL_PTR == pstEntity)
    {
        PS_PRINTF("             ??????????NDIS????    \n");
        return;
    }

    PS_PRINTF("                 ModemID:  %d\n", NDIS_GET_MODEMID_FROM_EXBID(pstEntity->ucRabId));
    PS_PRINTF("                 EPS????ID:  %d\n", NDIS_GET_BID_FROM_EXBID(pstEntity->ucRabId));
    PS_PRINTF("             ARP??????????:  %d\n", pstEntity->stIpV4Info.ulArpInitFlg);
    PS_PRINTF(" ARP??????????????????????:  %d\n", pstEntity->stIpV4Info.ulArpRepFlg);

    PS_PRINTF("             PDN??????????:    \n");
    Ndis_PrintIpv4Addr(pstEntity->stIpV4Info.unUeIpInfo.aucIPAddr);

    PS_PRINTF("             ??????????????:    \n");
    Ndis_PrintIpv4Addr(pstEntity->stIpV4Info.unGwIpInfo.aucIPAddr);

    PS_PRINTF("             ??????????????:    \n");
    Ndis_PrintIpv4Addr(pstEntity->stIpV4Info.unNmIpInfo.aucIPAddr);

    PS_PRINTF("            ??DNS??????????:    \n");
    Ndis_PrintIpv4Addr(pstEntity->stIpV4Info.unPrimDnsAddr.aucIPAddr);

    PS_PRINTF("            ??DNS??????????:    \n");
    Ndis_PrintIpv4Addr(pstEntity->stIpV4Info.unSecDnsAddr.aucIPAddr);

    PS_PRINTF("            ??WINS??????????:    \n");
    Ndis_PrintIpv4Addr(pstEntity->stIpV4Info.unPrimWinsAddr.aucIPAddr);

    PS_PRINTF("            ??WINS??????????:    \n");
    Ndis_PrintIpv4Addr(pstEntity->stIpV4Info.unSecWinsAddr.aucIPAddr);

    PS_PRINTF("              DHCP??????????:  %d\n",pstEntity->stIpV4Info.ulIpAssignStatus);

    PS_PRINTF("               PC??MAC??????:  %x-%x-%x-%x-%x-%x\n",pstEntity->stIpV4Info.aucUeMacAddr[0],
               pstEntity->stIpV4Info.aucUeMacAddr[1],pstEntity->stIpV4Info.aucUeMacAddr[2],
               pstEntity->stIpV4Info.aucUeMacAddr[3],pstEntity->stIpV4Info.aucUeMacAddr[4],
               pstEntity->stIpV4Info.aucUeMacAddr[5]);
    PS_PRINTF("          ??????????????????:  ????MAC: %x-%x-%x-%x-%x-%x,??MAC: %x-%x-%x-%x-%x-%x,??????:0x%x\n",
               pstEntity->stIpV4Info.aucMacFrmHdr[0],pstEntity->stIpV4Info.aucMacFrmHdr[1],
               pstEntity->stIpV4Info.aucMacFrmHdr[2],pstEntity->stIpV4Info.aucMacFrmHdr[3],
               pstEntity->stIpV4Info.aucMacFrmHdr[4],pstEntity->stIpV4Info.aucMacFrmHdr[5],
               pstEntity->stIpV4Info.aucMacFrmHdr[6],pstEntity->stIpV4Info.aucMacFrmHdr[7],
               pstEntity->stIpV4Info.aucMacFrmHdr[8],pstEntity->stIpV4Info.aucMacFrmHdr[9],
               pstEntity->stIpV4Info.aucMacFrmHdr[10],pstEntity->stIpV4Info.aucMacFrmHdr[11],
               *(VOS_UINT16 *)(&pstEntity->stIpV4Info.aucMacFrmHdr[12]));

    PS_PRINTF("\n======================================================\n");

}

/*****************************************************************************
 ?? ?? ??  : Ndis_ShowAllEntity
 ????????  : ??????????????????
 ????????  : VOS_VOID
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??4??18??
    ??    ??   : h00133115
    ????????   : ??????????

  2.??    ??   : 2013??1??16??
    ??    ??   : h00218138
    ????????   : DSDA

*****************************************************************************/
VOS_VOID Ndis_ShowAllEntity(VOS_VOID)
{
    VOS_UINT32            ulLoop;
    NDIS_ENTITY_STRU     *pstEntity;

    for(ulLoop=0; ulLoop<NAS_NDIS_MAX_ITEM; ulLoop++)
    {
        pstEntity  =  &g_pstNdisEntity[ulLoop];
        if (PS_FALSE == pstEntity->enUsed)
        {
            PS_PRINTF("                 ModemID:  %d\n", NDIS_GET_MODEMID_FROM_EXBID(pstEntity->ucRabId));
            PS_PRINTF("                 EPS????ID %d ??????\n", NDIS_GET_BID_FROM_EXBID(pstEntity->ucRabId));
            continue;
        }

        PS_PRINTF("                 ModemID:  %d\n", NDIS_GET_MODEMID_FROM_EXBID(pstEntity->ucRabId));
        PS_PRINTF("                 EPS????ID:  %d\n", NDIS_GET_BID_FROM_EXBID(pstEntity->ucRabId));
        PS_PRINTF("             ARP??????????:  %d\n", pstEntity->stIpV4Info.ulArpInitFlg);
        PS_PRINTF(" ARP??????????????????????:  %d\n", pstEntity->stIpV4Info.ulArpRepFlg);

        PS_PRINTF("             PDN??????????:    \n");
        Ndis_PrintIpv4Addr(pstEntity->stIpV4Info.unUeIpInfo.aucIPAddr);

        PS_PRINTF("             ??????????????:    \n");
        Ndis_PrintIpv4Addr(pstEntity->stIpV4Info.unGwIpInfo.aucIPAddr);

        PS_PRINTF("             ??????????????:    \n");
        Ndis_PrintIpv4Addr(pstEntity->stIpV4Info.unNmIpInfo.aucIPAddr);

        PS_PRINTF("            ??DNS??????????:    \n");
        Ndis_PrintIpv4Addr(pstEntity->stIpV4Info.unPrimDnsAddr.aucIPAddr);

        PS_PRINTF("            ??DNS??????????:    \n");
        Ndis_PrintIpv4Addr(pstEntity->stIpV4Info.unSecDnsAddr.aucIPAddr);

        PS_PRINTF("            ??WINS??????????:    \n");
        Ndis_PrintIpv4Addr(pstEntity->stIpV4Info.unPrimWinsAddr.aucIPAddr);

        PS_PRINTF("            ??WINS??????????:    \n");
        Ndis_PrintIpv4Addr(pstEntity->stIpV4Info.unSecWinsAddr.aucIPAddr);

        PS_PRINTF("              DHCP??????????:  %d\n",pstEntity->stIpV4Info.ulIpAssignStatus);

        PS_PRINTF("               PC??MAC??????:  %x-%x-%x-%x-%x-%x\n",pstEntity->stIpV4Info.aucUeMacAddr[0],
                   pstEntity->stIpV4Info.aucUeMacAddr[1],pstEntity->stIpV4Info.aucUeMacAddr[2],
                   pstEntity->stIpV4Info.aucUeMacAddr[3],pstEntity->stIpV4Info.aucUeMacAddr[4],
                   pstEntity->stIpV4Info.aucUeMacAddr[5]);
        PS_PRINTF("          ??????????????????:  ????MAC: %x-%x-%x-%x-%x-%x,??MAC: %x-%x-%x-%x-%x-%x,??????:0x%x\n",
                   pstEntity->stIpV4Info.aucMacFrmHdr[0],pstEntity->stIpV4Info.aucMacFrmHdr[1],
                   pstEntity->stIpV4Info.aucMacFrmHdr[2],pstEntity->stIpV4Info.aucMacFrmHdr[3],
                   pstEntity->stIpV4Info.aucMacFrmHdr[4],pstEntity->stIpV4Info.aucMacFrmHdr[5],
                   pstEntity->stIpV4Info.aucMacFrmHdr[6],pstEntity->stIpV4Info.aucMacFrmHdr[7],
                   pstEntity->stIpV4Info.aucMacFrmHdr[8],pstEntity->stIpV4Info.aucMacFrmHdr[9],
                   pstEntity->stIpV4Info.aucMacFrmHdr[10],pstEntity->stIpV4Info.aucMacFrmHdr[11],
                   *(VOS_UINT16 *)(&pstEntity->stIpV4Info.aucMacFrmHdr[12]));

        PS_PRINTF("\n======================================================\n");
    }
}




/*****************************************************************************
 Function Name  : lpsver
 Discription    : ????????????
 Input          : None
 Output         : None
 Return         : None

 History:
      1. Lishangfeng 55206   2010-05-20  ????

*****************************************************************************/
/*VOS_VOID lpsver (VOS_VOID)
{
    PS_PRINTF("************^U^*************\r\n");
    PS_PRINTF("Version :APP PS V%dR%03dC%02dB%03d\r\n", 700,
                                                          1,
                                                          10,
                                                          60
                                    );
    PS_PRINTF("Date    : %s \r\n", (VOS_UINT8 *)__DATE__);
    PS_PRINTF("Time    : %s \r\n", (VOS_UINT8 *)__TIME__);
    PS_PRINTF("************^U^*************\r\n");
}*/

/*****************************************************************************
 Function Name  : NDIS_OpenLatency
 Discription    : UserPlane Latency
 Input          : None
 Output         : None
 Return         : None

 History:
      1. huibo 00159435   2012-06-18  ????
*****************************************************************************/
VOS_VOID NDIS_OpenLatency(VOS_VOID)
{
    g_ulNdisLomSwitch = 1;
    return;
}

/*****************************************************************************
 Function Name  : NDIS_CloseLatency
 Discription    : UserPlane Latency
 Input          : None
 Output         : None
 Return         : None

 History:
      1. huibo 00159435   2012-06-18  ????
*****************************************************************************/
VOS_VOID NDIS_CloseLatency(VOS_VOID)
{
    g_ulNdisLomSwitch = 0;
    return;
}

/*****************************************************************************
 Function Name  : Ndis_LomTraceRcvUlData
 Discription    : UserPlane Latency
 Input          : None
 Output         : None
 Return         : None

 History:
      1. huibo 00159435   2012-06-18  ????
*****************************************************************************/
VOS_VOID Ndis_LomTraceRcvUlData(VOS_VOID)
{
    if (1 == g_ulNdisLomSwitch)
    {
        NDIS_ERROR_LOG(NDIS_TASK_PID, "User plane latency trace: NDIS rcv UL data");
    }
    return;
}

/*****************************************************************************
 Function Name  : Ndis_LomTraceRcvDlData
 Discription    : UserPlane Latency
 Input          : None
 Output         : None
 Return         : None

 History:
      1. huibo 00159435   2012-06-18  ????
*****************************************************************************/
VOS_VOID Ndis_LomTraceRcvDlData(VOS_VOID)
{
    if (1 == g_ulNdisLomSwitch)
    {
        NDIS_ERROR_LOG(NDIS_TASK_PID, "User plane latency trace: NDIS rcv DL data");
    }
    return;
}

