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

/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : UsimmBase.c
  Author       : zhuli 00100318
  Version      : v00R002
  Date         : 2008-5-15
  Description  : ??C??????????---Base????????
  Function List:
  History      :
************************************************************************/
#include "pamappom.h"
#include "omprivate.h"
#include "cpm.h"
#include "NVIM_Interface.h"
#include "TafNvInterface.h"
#include "SCMProc.h"
#include "SCMSoftDecode.h"
#include "CbtPpm.h"
#include "DrvNvInterface.h"
#include "ScComm.h"
#include "NasNvInterface.h"

#include "msp_nvim.h"



/*****************************************************************************
    ??????????????????????.C??????????
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID PS_FILE_ID_PAM_APP_OM_C
/*lint +e767*/


/* ??????????????????buffer?????????? */
OM_RECORD_BUF_STRU                      g_astAcpuRecordInfo[VOS_EXC_DUMP_MEM_NUM_BUTT];

VOS_UINT32                              g_ulAcpuOmFilterFlag;

/* AT<->AT????????????????GuNasLogFilter.c */

/*****************************************************************************
 Prototype       : OM_RecordInfoEnd
 Description     : A????????????
 Input           : ulNumer -- ??????
 Output          : None
 Return Value    : VOS_VOID

 History         : ---
    Date         : 2012-07-09
    Author       : s00207770
    Modification : Created function
 *****************************************************************************/
VOS_VOID OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_ENUM_UINT32 enNumber)
{
    VOS_UINT32 *pulBuf;

    if(VOS_EXC_DUMP_MEM_NUM_BUTT <= enNumber)
    {
        return;
    }

    if(VOS_NULL_PTR == g_astAcpuRecordInfo[enNumber].pucBuf)
    {
        return;
    }

    if(0 == g_astAcpuRecordInfo[enNumber].ulLen)
    {
        return;
    }

    /* ??start????????????????endslice????????????????????????????????endslice???? */
    pulBuf = (VOS_UINT32*)(g_astAcpuRecordInfo[enNumber].pucBuf + g_astAcpuRecordInfo[enNumber].ulLen - sizeof(VOS_UINT32));

    *pulBuf = VOS_GetSlice();

    return;
}

/*****************************************************************************
 Prototype       : OM_RecordInfoStart
 Description     : A????????????
 Input           : ulNumer -- ??????
                   ulSendPid -- ????PID
                   ulRcvPid -- ????PID
                   ulMsgName -- ????????
 Output          : None
 Return Value    : VOS_VOID

 History         : ---
    Date         : 2012-07-09
    Author       : s00702770
    Modification : Created function
 *****************************************************************************/
VOS_VOID OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_ENUM_UINT32 enNumber, VOS_UINT32 ulSendPid, VOS_UINT32 ulRcvPid, VOS_UINT32 ulMsgName)
{
    OM_RECORD_INFO_STRU     stRecordInfo;

    if(VOS_EXC_DUMP_MEM_NUM_BUTT <= enNumber)
    {
       return;
    }

    if(VOS_NULL_PTR == g_astAcpuRecordInfo[enNumber].pucBuf)
    {
       return;
    }

    g_astAcpuRecordInfo[enNumber].ulLen %= VOS_TASK_DUMP_INFO_SIZE;

    stRecordInfo.usSendPid      = (VOS_UINT16)ulSendPid;
    stRecordInfo.usRcvPid       = (VOS_UINT16)ulRcvPid;
    stRecordInfo.ulMsgName      = ulMsgName;
    stRecordInfo.ulSliceStart   = VOS_GetSlice();
    stRecordInfo.ulSliceEnd     = 0;

    /*lint -e534*/
    VOS_MemCpy((g_astAcpuRecordInfo[enNumber].pucBuf + g_astAcpuRecordInfo[enNumber].ulLen),
              &stRecordInfo, sizeof(OM_RECORD_INFO_STRU));
    /*lint +e534*/

    g_astAcpuRecordInfo[enNumber].ulLen += (VOS_UINT32)sizeof(OM_RECORD_INFO_STRU);

    return;
}

/*****************************************************************************
 Prototype       : OM_RecordMemInit
 Description     : ????????????????
 Input           : None
 Output          : None
 Return Value    : VOS_VOID

 History         : ---
    Date         : 2012-06-28
    Author       : j00168360
    Modification : Created function
 *****************************************************************************/
VOS_VOID OM_RecordMemInit(VOS_VOID)
{
   VOS_UINT32 i;

   /*lint -e534*/
   VOS_MemSet(g_astAcpuRecordInfo, 0, sizeof(g_astAcpuRecordInfo));
   /*lint +e534*/

   /* ?????????????????????????????????? */
   for(i = 0; i < VOS_EXC_DUMP_MEM_NUM_BUTT; i++)
   {
      g_astAcpuRecordInfo[i].pucBuf = (VOS_UINT8*)VOS_ExcDumpMemAlloc(i);

      if(VOS_NULL_PTR == g_astAcpuRecordInfo[i].pucBuf)
      {
          return;
      }
   }

   return;
}


VOS_VOID PAMOM_AcpuTimerMsgProc(MsgBlock* pMsg)
{
    return;
}


VOS_VOID PAMOM_QuereyPidInfo(VOS_VOID)
{
    PAM_VOS_QUEREY_PID_INFO_REQ_STRU    *pstMsg;

    pstMsg = (PAM_VOS_QUEREY_PID_INFO_REQ_STRU *)VOS_AllocMsg(ACPU_PID_PAM_OM,
                            sizeof(PAM_VOS_QUEREY_PID_INFO_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ???????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->ulReceiverPid  = CCPU_PID_PAM_OM;
    pstMsg->usPrimId       = PAM_VOS_QUEREY_PID_INFO_REQ;

    (VOS_VOID)VOS_SendMsg(ACPU_PID_PAM_OM, pstMsg);

    return;
}


VOS_VOID PAMOM_QuereyPidInfoMsgProc(MsgBlock* pMsg)
{
    PAM_VOS_QUEREY_PID_INFO_REQ_STRU    *pstMsg;
    PAM_VOS_QUEREY_PID_INFO_CNF_STRU    *pstCnfMsg;
    VOS_UINT32                           ulLen;

    pstMsg = (PAM_VOS_QUEREY_PID_INFO_REQ_STRU *)pMsg;

    if (PAM_VOS_QUEREY_PID_INFO_REQ == pstMsg->usPrimId)
    {
        ulLen = VOS_QueryPidInfoBufSize();

        pstCnfMsg = (PAM_VOS_QUEREY_PID_INFO_CNF_STRU *)VOS_AllocMsg(ACPU_PID_PAM_OM,
                            sizeof(PAM_VOS_QUEREY_PID_INFO_CNF_STRU) - VOS_MSG_HEAD_LENGTH + ulLen);

        /* ???????????? */
        if (VOS_NULL_PTR == pstCnfMsg)
        {
            return;
        }

        pstCnfMsg->ulReceiverPid  = CCPU_PID_PAM_OM;
        pstCnfMsg->usPrimId       = PAM_VOS_QUEREY_PID_INFO_CNF;
        pstCnfMsg->usLen          = (VOS_UINT16)ulLen;
        VOS_QueryPidInfo((VOS_VOID *)pstCnfMsg->aucValue);

        (VOS_VOID)VOS_SendMsg(ACPU_PID_PAM_OM, pstCnfMsg);
    }
    else if (PAM_VOS_QUEREY_PID_INFO_CNF == pstMsg->usPrimId)
    {
        pstCnfMsg = (PAM_VOS_QUEREY_PID_INFO_CNF_STRU *)pMsg;

        VOS_SetPidInfo((VOS_VOID *)(pstCnfMsg->aucValue), pstCnfMsg->usLen);
    }
    else
    {
        /* blank */
    }

    return;
}


 VOS_VOID PAMOM_AcpuCcpuPamMsgProc(MsgBlock* pMsg)
 {
    VOS_UINT16                          usPrimId;

    usPrimId = *(VOS_UINT16 *)(pMsg->aucValue);

    if (PAM_VOS_QUEREY_PID_INFO_REQ == usPrimId)
    {
        PAMOM_QuereyPidInfoMsgProc(pMsg);
    }
    else if (PAM_VOS_QUEREY_PID_INFO_CNF == usPrimId)
    {
        PAMOM_QuereyPidInfoMsgProc(pMsg);
    }
    else
    {
        Om_AcpuQueryDumpMsgProc(pMsg);/* GUTL ?????????????? */
    }

    return;
}

/*****************************************************************************
 Prototype       : CBT_AppMsgProc
 Description     : Handle all messages sent to OM.
 Input           : pMsg -- The pointer of the msg.
 Output          : None
 Return Value    : VOS_VOID

 History         : ---
    Date         : 2008-03-20
    Author       : g47350
    Modification : Created function
 *****************************************************************************/
VOS_VOID PAMOM_AppMsgProc(MsgBlock* pMsg)
{
    if (VOS_PID_TIMER == pMsg->ulSenderPid)
    {
        PAMOM_AcpuTimerMsgProc(pMsg);
    }
    else if (CCPU_PID_PAM_OM == pMsg->ulSenderPid)
    {
        PAMOM_AcpuCcpuPamMsgProc(pMsg);
    }
    else if ((DSP_PID_PROCSTUB == pMsg->ulSenderPid)
        || (CPROC_PID_1X_CM == pMsg->ulSenderPid)
        || (CPROC_PID_1X_SM == pMsg->ulSenderPid)
        || (CPROC_PID_1X_DSP == pMsg->ulSenderPid)
        || (CPROC_PID_HRPD_CM == pMsg->ulSenderPid)
        || (CPROC_PID_HRPD_SM == pMsg->ulSenderPid))
    {
        Om_AcpuPhyMsgProc(pMsg);
    }
    else
    {
        /* blank */
    }

    return;
}

/*****************************************************************************
 Prototype       : OM_AcpuInit
 Description     : OM' initializtion function
 Input           : None
 Output          : None
 Return Value    : VOS_UINT32

 History         : ---
    Date         : 2011-07-01
    Author       : g47350
    Modification : Created function
 *****************************************************************************/
VOS_UINT32 PAMOM_AcpuInit(VOS_VOID)
{
    NAS_NV_SMS_FILTER_CFG_STRU          stSmsFilterCfg;

    PAMOM_QuereyPidInfo();

    /* SC?????????????? */
    (VOS_VOID)SC_COMM_Restore();

    if (NV_OK != NV_ReadEx(MODEM_ID_0,
                           en_NV_Item_Sms_Log_Filter_Cfg,
                          &stSmsFilterCfg,
                           sizeof(NAS_NV_SMS_FILTER_CFG_STRU)))
    {
        stSmsFilterCfg.ucSmsFilterEnableFlg = VOS_FALSE;
    }

    if (VOS_FALSE != stSmsFilterCfg.ucSmsFilterEnableFlg)
    {
        stSmsFilterCfg.ucSmsFilterEnableFlg = VOS_TRUE;
    }

    g_ulAcpuOmFilterFlag = stSmsFilterCfg.ucSmsFilterEnableFlg;

    return VOS_OK;
}

/*****************************************************************************
 Prototype       : OM_AcpuPidInit
 Description     : ACPU OM PID' initializtion function
 Input           : None
 Output          : None
 Return Value    : VOS_UINT32

 History         : ---
    Date         : 2011-07-01
    Author       : g47350
    Modification : Created function
 *****************************************************************************/
VOS_UINT32 PAMOM_AppPidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    switch( ip )
    {
        case VOS_IP_LOAD_CONFIG:
            return PAMOM_AcpuInit();

        default:
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
 Prototype       : OM_AcpuFidInit
 Description     : ACPU OM FID' initializtion function
 Input           : None
 Output          : None
 Return Value    : VOS_UINT32

 History         : ---
    Date         : 2011-07-01
    Author       : g47350
    Modification : Created function
 *****************************************************************************/
VOS_UINT32 PAMOM_APP_FID_Init(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32                          ulRslt;

    switch( ip )
    {
        case VOS_IP_LOAD_CONFIG:
        {
            ulRslt = VOS_RegisterPIDInfo(ACPU_PID_PAM_OM,
                                        (Init_Fun_Type)PAMOM_AppPidInit,
                                        (Msg_Fun_Type)PAMOM_AppMsgProc);
            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            ulRslt = VOS_RegisterMsgTaskPrio(ACPU_FID_PAM_OM, VOS_PRIORITY_M2);
            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            /* ?????????????????? */
            if (VOS_OK != mdrv_file_access(PAM_LOG_PARTH, PAM_FILE_EXIST))
            {
                (VOS_VOID)mdrv_file_mkdir(PAM_LOG_PARTH);
            }

            break;
        }

        default:
            break;
    }
    return VOS_OK;
}

/*****************************************************************************
 ?? ?? ??  : VOS_ICCError_CB
 ????????  : ????ICC WIFI??????????????????????
 ????????  : ulChannelID:   ????????ID
             ulLen:         ????????????????
 ????????  : ??
 ?? ?? ??  : VOS_ERROR/VOS_OK
 ????????  :
 ????????  :
 ????????  :
   1.??    ??  : 2011??3??10??
     ??    ??  : l46160
     ????????  : Creat Function
*****************************************************************************/
VOS_UINT VOS_ICCError_CB(VOS_UINT ulChanID, VOS_UINT ulEvent, VOS_VOID* pParam)
{
    /*lint -e534*/
    LogPrint2("VOS_ICCError_CB: The Error Channel ID is %d,and Event is %d\n",
                (VOS_INT32)ulChanID, (VOS_INT32)ulEvent);
    /*lint +e534*/

    return VOS_OK;
}

/*****************************************************************************
 ?? ?? ??  : OM_ComRx_ICC_Init
 ????????  : ????OM??CCPU??????ICC????
 ????????  : ??
 ????????  : ??
 ?? ?? ??  : VOS_ERR/VOS_OK
 ????????  :
 ????????  :
 ????????  :
   1.??    ??  : 2011??3??10??
     ??    ??  : l46160
     ????????  : Creat Function
*****************************************************************************/
VOS_UINT32 VOS_ICC_Init(VOS_VOID)
{
    OM_ICC_UDI_CTRL_STRU                astACPUICCCtrlTable;

    /*?????? ICC????*/
    /*lint -e534*/
    VOS_MemSet((&astACPUICCCtrlTable), 0, sizeof(astACPUICCCtrlTable));
    /*lint +e534*/

    astACPUICCCtrlTable.pstICCAttr = (ICC_CHAN_ATTR_S*)VOS_MemAlloc(ACPU_PID_PAM_OM,
                                                                    STATIC_MEM_PT,
                                                                    sizeof(ICC_CHAN_ATTR_S));
    if(VOS_NULL_PTR == astACPUICCCtrlTable.pstICCAttr)
    {
        return VOS_ERR;             /*????????????????????????????????????????????????????????*/
    }

    astACPUICCCtrlTable.enICCId               = UDI_ICC_GUOM4;
    astACPUICCCtrlTable.pstICCAttr->read_cb   = V_ICC_OSAMsg_CB;
    astACPUICCCtrlTable.pstICCAttr->u32Priority    = OM_ICC_CHANNEL_PRIORITY;
    astACPUICCCtrlTable.pstICCAttr->u32TimeOut     = OM_ICC_HANDSHAKE_TIME_MAX;
    astACPUICCCtrlTable.pstICCAttr->u32FIFOInSize  = OSA_ICC_BUFFER_SIZE;
    astACPUICCCtrlTable.pstICCAttr->u32FIFOOutSize = OSA_ICC_BUFFER_SIZE;
    astACPUICCCtrlTable.pstICCAttr->enChanMode     = ICC_CHAN_MODE_PACKET;
    astACPUICCCtrlTable.pstICCAttr->event_cb       = VOS_ICCError_CB;
    astACPUICCCtrlTable.pstICCAttr->write_cb       = VOS_NULL_PTR;

    if(VOS_ERROR == DRV_ICC_OPEN(astACPUICCCtrlTable.enICCId, astACPUICCCtrlTable.pstICCAttr))
    {
        /* ??????????????????ICC???????? */
        VOS_ProtectionReboot(OM_APP_ICC_INIT_ERROR, THIS_FILE_ID, __LINE__,VOS_NULL_PTR,0);

        return VOS_ERR;
    }

    VOS_IccDebugInfoInit();

    return VOS_OK;
}

/*****************************************************************************
 ?? ?? ??  : OM_OSAEvent
 ????????  : ????OSA??????????????
 ????????  :
 ????????  : ??
 ?? ?? ??  : ??

 ????????      :
  1.??    ??   : 2013??7??27??
    ??    ??   : x51137
    ????????   : ??????????
*****************************************************************************/
VOS_VOID OM_OSAEvent(VOS_VOID *pData, VOS_UINT32 ulLength)
{
    DIAG_EVENT_IND_STRU                 stEventInd;

    stEventInd.ulModule = DIAG_GEN_MODULE(DIAG_MODEM_0, DIAG_MODE_COMM);
    stEventInd.ulPid    = ACPU_PID_PAM_OM;
    stEventInd.ulEventId= OAM_EVENT_TIMER;
    stEventInd.ulLength = ulLength;
    stEventInd.pData    = pData;

    /*lint -e534*/
    (VOS_VOID)DIAG_EventReport(&stEventInd);
    /*lint +e534*/

    return;
}

/*****************************************************************************
 ?? ?? ??  : PAM_OM_LayerMsgFilter
 ????????  : ????PAM????????????
 ????????  : const VOID *pMsg:????????
 ????????  : ??
 ?? ?? ??  : VOS_UINT32:
                ????VOS_TRUE:  ??????????????????????
                ????VOS_FALSE: ??????????????????????
 ????????  :
 ????????  :
 ????????      :
  1.??    ??   : 2015??10??28??
    ??    ??   : zhuli
    ????????   : ??????????
*****************************************************************************/
VOS_UINT32 PAM_OM_LayerMsgFilter(
    const VOS_VOID                      *pMsg
)
{
    OM_FILTER_MSG_HEAD_STRU             *pstMsgHead;

    if (VOS_FALSE == g_ulAcpuOmFilterFlag)
    {
        return VOS_FALSE;
    }

    pstMsgHead = (OM_FILTER_MSG_HEAD_STRU*)pMsg;

    /* SIM???????? */
    if (  ((I0_WUEPS_PID_USIM <= pstMsgHead->ulSenderPid)&&(I0_MAPS_PB_PID >= pstMsgHead->ulSenderPid))
        ||((I1_WUEPS_PID_USIM <= pstMsgHead->ulSenderPid)&&(I1_MAPS_PB_PID >= pstMsgHead->ulSenderPid))
        ||((I2_WUEPS_PID_USIM <= pstMsgHead->ulSenderPid)&&(I2_MAPS_PB_PID >= pstMsgHead->ulSenderPid))
       )
    {
        return VOS_TRUE;
    }

    if (((I0_WUEPS_PID_USIM <= pstMsgHead->ulReceiverPid)&&(I0_MAPS_PB_PID >= pstMsgHead->ulReceiverPid))
        ||((I1_WUEPS_PID_USIM <= pstMsgHead->ulReceiverPid)&&(I1_MAPS_PB_PID >= pstMsgHead->ulReceiverPid))
        ||((I2_WUEPS_PID_USIM <= pstMsgHead->ulReceiverPid)&&(I2_MAPS_PB_PID >= pstMsgHead->ulReceiverPid))
       )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/* AT<->AT????????????????GuNasLogFilter.c */


