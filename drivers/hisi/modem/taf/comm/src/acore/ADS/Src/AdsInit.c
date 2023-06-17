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
  1 ??????????
*****************************************************************************/
#include "vos.h"
#include "AdsInit.h"
#include "AdsUpLink.h"
#include "AdsDownLink.h"
#include "AdsDebug.h"
#include "AcpuReset.h"



/*****************************************************************************
    ??????????????????????.C??????????
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID                 PS_FILE_ID_ADS_INIT_C
/*lint +e767*/


/*****************************************************************************
  2 ????????????
*****************************************************************************/

/*****************************************************************************
  3 ????????
*****************************************************************************/

/*****************************************************************************
 ?? ?? ??  : ADS_UL_PidInit
 ????????  : ADS????????????PID??????
 ????????  : enum VOS_INIT_PHASE_DEFINE enPhase
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??12??6??
    ??    ??   : ????/l60609
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 ADS_UL_PidInit(enum VOS_INIT_PHASE_DEFINE enPhase)
{
    switch ( enPhase )
    {
        case VOS_IP_LOAD_CONFIG:

            /* ???????????? */
            ADS_InitCtx();

            /* ????????????????????????C???????????????? */
            mdrv_sysboot_register_reset_notify(NAS_ADS_UL_FUNC_PROC_NAME,
                                               ADS_UL_CCpuResetCallback,
                                               0,
                                               ACPU_RESET_PRIORITY_ADS_UL);

            break;

        default:
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
 ?? ?? ??  : ADS_UL_FidTask
 ????????  : ADS????????????????
 ????????  : ??
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2012??4??12??
    ??    ??   : A00165503
    ????????   : ??????????

  2.??    ??   : 2012??4??12??
    ??    ??   : A00165503
    ????????   : DTS2012020708222: ADS????????
*****************************************************************************/
VOS_VOID ADS_UL_FidTask(
    VOS_UINT32                          ulQueueID,
    VOS_UINT32                          FID_value,
    VOS_UINT32                          Para1,
    VOS_UINT32                          Para2
)
{
    MsgBlock                           *pMsg          = VOS_NULL_PTR;
    VOS_UINT32                          ulEvent       = 0;
    VOS_UINT32                          ulTaskID      = 0;
    VOS_UINT32                          ulRtn         = VOS_ERR;
    VOS_UINT32                          ulEventMask   = 0;
    VOS_UINT32                          ulExpectEvent = 0;

    ulTaskID = VOS_GetCurrentTaskID();
    if (PS_NULL_UINT32 == ulTaskID)
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_UL, "ADS_UL_FidTask: ERROR, TaskID is invalid.");
        return;
    }

    if (VOS_OK != VOS_CreateEvent(ulTaskID))
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_UL, "ADS_UL_FidTask: ERROR, create event fail.");
        return;
    }

    g_ulAdsULTaskId         = ulTaskID;
    g_ulAdsULTaskReadyFlag  = 1;

    ulExpectEvent = ADS_UL_EVENT_DATA_PROC | VOS_MSG_SYNC_EVENT;
    ulEventMask   = (VOS_EVENT_ANY | VOS_EVENT_WAIT);

    /*lint -e716*/
    while (1)
    /*lint +e716*/
    {
        ulRtn = VOS_EventRead(ulExpectEvent, ulEventMask, 0, &ulEvent);
        if (VOS_OK != ulRtn)
        {
            ADS_ERROR_LOG(ACPU_PID_ADS_UL, "ADS_UL_FidTask: ERROR, read event error.");
            continue;
        }

        /*????????*/
        if (VOS_MSG_SYNC_EVENT != ulEvent)
        {
            ADS_UL_ProcEvent(ulEvent);
            continue;
        }

        pMsg = (MsgBlock*)VOS_GetMsg(ulTaskID);
        if (VOS_NULL_PTR != pMsg)
        {
            if (ACPU_PID_ADS_UL == pMsg->ulReceiverPid)
            {
                ADS_UL_ProcMsg(pMsg);
            }

            PS_FREE_MSG(ACPU_PID_ADS_UL, pMsg);
        }
    }
}


/*****************************************************************************
 ?? ?? ??  : ADS_UL_FidInit
 ????????  : ADS??????????????????????
 ????????  : enum VOS_INIT_PHASE_DEFINE ip
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??12??6??
    ??    ??   : ????/l60609
    ????????   : ??????????

  2.??    ??   : 2012??4??12??
    ??    ??   : A00165503
    ????????   : DTS2012020708222: ADS????????
*****************************************************************************/
VOS_UINT32 ADS_UL_FidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32                          ulRslt;

    switch (ip)
    {
        case VOS_IP_LOAD_CONFIG:

            /* ????PID?????? */
            ulRslt = VOS_RegisterPIDInfo(ACPU_PID_ADS_UL,
                                         (Init_Fun_Type)ADS_UL_PidInit,
                                         (Msg_Fun_Type)ADS_UL_ProcMsg);

            if (VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            ulRslt = VOS_RegisterMsgTaskEntry(ACPU_FID_ADS_UL, (VOS_VOIDFUNCPTR)ADS_UL_FidTask);

            if (VOS_OK != ulRslt)
            {
                return ulRslt;
            }

            /* ?????????? */
            ulRslt = VOS_RegisterTaskPrio(ACPU_FID_ADS_UL, ADS_UL_TASK_PRIORITY);
            if( VOS_OK != ulRslt )
            {
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
    }

    return VOS_OK;
}

/*****************************************************************************
 ?? ?? ??  : ADS_DL_PidInit
 ????????  : ADS????????????PID??????
 ????????  : enum VOS_INIT_PHASE_DEFINE enPhase
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??12??6??
    ??    ??   : ????/l60609
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 ADS_DL_PidInit(enum VOS_INIT_PHASE_DEFINE enPhase)
{
    switch ( enPhase )
    {
        case VOS_IP_LOAD_CONFIG:


            /* ADQ?????? */
            ADS_DL_AllocMemForAdq();

            /* ????????????????????????C???????????????? */
            mdrv_sysboot_register_reset_notify(NAS_ADS_DL_FUNC_PROC_NAME,
                                               ADS_DL_CCpuResetCallback,
                                               0,
                                               ACPU_RESET_PRIORITY_ADS_DL);

            break;

        default:
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
 ?? ?? ??  : ADS_DL_FidTask
 ????????  : ADS????????????????
 ????????  : VOS_UINT32                          ulQueueID
             VOS_UINT32                          FID_value
             VOS_UINT32                          Para1
             VOS_UINT32                          Para2
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2012??2??24??
    ??    ??   : A00165503
    ????????   : ??????????

  2.??    ??   : 2012??4??12??
    ??    ??   : A00165503
    ????????   : DTS2012020708222: ADS????????
*****************************************************************************/
VOS_VOID ADS_DL_FidTask(
    VOS_UINT32                          ulQueueID,
    VOS_UINT32                          FID_value,
    VOS_UINT32                          Para1,
    VOS_UINT32                          Para2
)
{
    MsgBlock                           *pMsg          = VOS_NULL_PTR;
    VOS_UINT32                          ulEvent       = 0;
    VOS_UINT32                          ulTaskID      = 0;
    VOS_UINT32                          ulRtn         = PS_FAIL;
    VOS_UINT32                          ulEventMask   = 0;
    VOS_UINT32                          ulExpectEvent = 0;

    ulTaskID = VOS_GetCurrentTaskID();
    if (PS_NULL_UINT32 == ulTaskID)
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_FidTask: ERROR, TaskID is invalid.");
        return;
    }

    if (VOS_OK != VOS_CreateEvent(ulTaskID))
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_FidTask: ERROR, create event fail.");
        return;
    }

    g_ulAdsDLTaskId         = ulTaskID;
    g_ulAdsDLTaskReadyFlag  = 1;

    ulExpectEvent = ADS_DL_EVENT_IPF_RD_INT | ADS_DL_EVENT_IPF_ADQ_EMPTY_INT | VOS_MSG_SYNC_EVENT;
    ulEventMask   = (VOS_EVENT_ANY | VOS_EVENT_WAIT);

    /*lint -e716*/
    while (1)
    /*lint +e716*/
    {
        ulRtn = VOS_EventRead(ulExpectEvent, ulEventMask, 0, &ulEvent);

        if (VOS_OK != ulRtn)
        {
            ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_FidTask: ERROR, read event error.");
            continue;
        }

        /* ???????? */
        if (VOS_MSG_SYNC_EVENT != ulEvent)
        {
            ADS_DL_ProcEvent(ulEvent);
            continue;
        }

        pMsg = (MsgBlock*)VOS_GetMsg(ulTaskID);
        if (VOS_NULL_PTR != pMsg)
        {
            if (ACPU_PID_ADS_DL == pMsg->ulReceiverPid)
            {
                ADS_DL_ProcMsg(pMsg);
            }

            PS_FREE_MSG(ACPU_PID_ADS_DL, pMsg);
        }

    }
}

/*****************************************************************************
 ?? ?? ??  : ADS_DL_FidInit
 ????????  : ADS??????????????????????
 ????????  : enum VOS_INIT_PHASE_DEFINE ip
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??12??6??
    ??    ??   : ????/l60609
    ????????   : ??????????

  2.??    ??   : 2012??4??12??
    ??    ??   : A00165503
    ????????   : DTS2012020708222: ADS????????

  3.??    ??   : 2012??6??11??
    ??    ??   : A00165503
    ????????   : DTS2012061105876: ADS??????????????????????????????

  4.??    ??   : 2012??12??19??
    ??    ??   : l60609
    ????????   : DSDA Phase II

*****************************************************************************/
VOS_UINT32 ADS_DL_FidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32                          ulRslt;
    VOS_INT32                           lIpfRslt;
    struct mdrv_ipf_ops                 stIpfOps;

    stIpfOps.rx_complete_cb = ADS_DL_IpfIntCB;
    stIpfOps.adq_empty_cb   = ADS_DL_IpfAdqEmptyCB;

    switch (ip)
    {
        case VOS_IP_LOAD_CONFIG:

            /* ????PID?????? */
            ulRslt = VOS_RegisterPIDInfo(ACPU_PID_ADS_DL,
                                         (Init_Fun_Type)ADS_DL_PidInit,
                                         (Msg_Fun_Type)ADS_DL_ProcMsg);

            if ( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }


            ulRslt = VOS_RegisterMsgTaskEntry(ACPU_FID_ADS_DL, (VOS_VOIDFUNCPTR)ADS_DL_FidTask);

            if (VOS_OK != ulRslt)
            {
                return ulRslt;
            }

            /* ????mdrv_ipf_register_ops????????????????,????AD?????????????? */
            lIpfRslt = mdrv_ipf_register_ops(&stIpfOps);
            if (IPF_SUCCESS != lIpfRslt)
            {
                return VOS_ERR;
            }

            /* ?????????? */
            ulRslt = VOS_RegisterMsgTaskPrio(ACPU_FID_ADS_DL, VOS_PRIORITY_P6);
            if( VOS_OK != ulRslt )
            {
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
    }

    return VOS_OK;
}



