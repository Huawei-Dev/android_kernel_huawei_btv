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
#include "RnicSndMsg.h"
#include "RnicLog.h"
#include "RnicCdsInterface.h"
#include "RnicDebug.h"



/*lint -e960*/
#define    THIS_FILE_ID        PS_FILE_ID_RNIC_SND_MSG_C
/*lint +e960*/

/*****************************************************************************
  2 ????????????
*****************************************************************************/


/*****************************************************************************
  3 ????????
*****************************************************************************/
/*****************************************************************************
 ?? ?? ??  : RNIC_SendDialInfoMsg
 ????????  : RNIC????????????????????????????????????
 ????????  : RNIC_DEMAND_DIAL_INFO_MSG_ID_ENUM_UINT32                enMsgId
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2012??2??1??
    ??    ??   : w00199382
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 RNIC_SendDialInfoMsg(
    RNIC_MSG_ID_ENUM_UINT32            enMsgId
)
{
    RNIC_NOTIFY_MSG_STRU               *pstDialInfo;
    RNIC_DIAL_MODE_STRU                *pstDialMode;


    /* ???????? */
    pstDialInfo = (RNIC_NOTIFY_MSG_STRU *)PS_ALLOC_MSG(ACPU_PID_RNIC,
                                                      sizeof(RNIC_NOTIFY_MSG_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstDialInfo)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_SendDialInfoMsg: Malloc failed!");
        return VOS_ERR;
    }

    pstDialMode                         = RNIC_GetDialModeAddr();

    /* ???????? */
    pstDialInfo->ulSenderCpuId          = VOS_LOCAL_CPUID;
    pstDialInfo->ulSenderPid            = ACPU_PID_RNIC;
    pstDialInfo->ulReceiverCpuId        = VOS_LOCAL_CPUID;
    pstDialInfo->ulReceiverPid          = ACPU_PID_RNIC;
    pstDialInfo->enMsgId                = enMsgId;

    PS_MEM_CPY(&(pstDialInfo->stDialInfo), pstDialMode, sizeof(RNIC_DIAL_MODE_STRU));

    if (VOS_OK != PS_SEND_MSG(ACPU_PID_RNIC, pstDialInfo))
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_SendDialInfoMsg: Send msg failed!");
        return VOS_ERR;
    }

    return VOS_OK;

}

/*****************************************************************************
 ?? ?? ??  : RNIC_SendCdsImsDataReq
 ????????  : ??CDS????ID_RNIC_CDS_IMS_DATA_REQ
 ????????  : struct sk_buff                     *pstSkb
             RNIC_SPEC_CTX_STRU                 *pstNetCntxt
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??10??26??
    ??    ??   : n00269697
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 RNIC_SendCdsImsDataReq(
    struct sk_buff                     *pstSkb,
    RNIC_SPEC_CTX_STRU                 *pstNetCntxt
)
{
    RNIC_CDS_IMS_DATA_REQ_STRU         *pstSndMsg = VOS_NULL_PTR;

    /* ???????? */
    pstSndMsg = (RNIC_CDS_IMS_DATA_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ACPU_PID_RNIC,
                                    sizeof(RNIC_CDS_IMS_DATA_REQ_STRU) - 4 + pstSkb->len);

    if (VOS_NULL_PTR == pstSndMsg)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_SendCdsImsDataReq: Malloc failed!");
        RNIC_DEV_ERR_PRINTK("RNIC_SendCdsImsDataReq: Malloc failed!");
        return VOS_ERR;
    }

    /* ?????????? */
    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = ACPU_PID_RNIC;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = UEPS_PID_CDS;
    pstSndMsg->ulMsgId                  = ID_RNIC_CDS_IMS_DATA_REQ;

    /* ???????? */
    pstSndMsg->usModemId                = pstNetCntxt->enModemId;
    pstSndMsg->usDataLen                = (VOS_UINT16)pstSkb->len;

    PS_MEM_CPY(pstSndMsg->aucData, pstSkb->data, pstSkb->len);

    /* ???????? */
    if (VOS_OK != PS_SEND_MSG(ACPU_PID_RNIC, pstSndMsg))
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_SendCdsImsDataReq: Send msg failed!");
        RNIC_DEV_ERR_PRINTK("RNIC_SendCdsImsDataReq: Send msg failed!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 ?? ?? ??  : RNIC_TrigImsDataProcEvent
 ????????  :
 ????????  : RNIC_RMNET_ID_ENUM_UINT8 enRmNetId
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??11??26??
    ??    ??   : n00269697
    ????????   : ??????????

*****************************************************************************/
VOS_VOID RNIC_TrigImsDataProcEvent(RNIC_RMNET_ID_ENUM_UINT8 enRmNetId)
{
    RNIC_IMS_DATA_PROC_IND_STRU         *pstSndMsg = VOS_NULL_PTR;

    /* ???????? */
    pstSndMsg = (RNIC_IMS_DATA_PROC_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ACPU_PID_RNIC,
                                    sizeof(RNIC_IMS_DATA_PROC_IND_STRU));

    if (VOS_NULL_PTR == pstSndMsg)
    {
        RNIC_DEV_ERR_PRINTK("RNIC_TrigImsDataProcEvent: Malloc failed!");
        return;
    }

    /* ?????????? */
    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = ACPU_PID_RNIC;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = ACPU_PID_RNIC;
    pstSndMsg->enMsgId                  = ID_RNIC_IMS_DATA_PROC_IND;
    pstSndMsg->enRmNetId                = enRmNetId;

    /* ???????? */
    if (VOS_OK != PS_SEND_MSG(ACPU_PID_RNIC, pstSndMsg))
    {
        RNIC_DEV_ERR_PRINTK("RNIC_TrigImsDataProcEvent: Send msg failed!");
    }

    return;
}

/* Modified by m00217266 for L-C??????????, 2014-01-06, Begin */
/*****************************************************************************
 ?? ?? ??  : RNIC_SndRnicRmnetConfigReq
 ????????  : RNIC????????PDP ????????
 ????????  :
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2014??1??18??
    ??    ??   : m00217266
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 RNIC_SndRnicRmnetConfigReq(
    RNIC_RMNET_CONFIG_STRU             *pstConfigInfo
)
{
    RNIC_RMNET_CONFIG_REQ_STRU         *pstSndMsg = VOS_NULL_PTR;

    /* ???????? */
    pstSndMsg = (RNIC_RMNET_CONFIG_REQ_STRU *)PS_ALLOC_MSG(ACPU_PID_RNIC,
                        sizeof(RNIC_RMNET_CONFIG_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstSndMsg)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_SndRnicRmnetConfigMsg: Malloc failed!");
        return VOS_ERR;
    }

    /* ?????????? */
    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = ACPU_PID_RNIC;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = ACPU_PID_RNIC;
    pstSndMsg->enMsgId                  = ID_RNIC_RMNET_CONFIG_REQ;

    /* ???????? */
    pstSndMsg->enModemType              = pstConfigInfo->enModemType;
    pstSndMsg->enRmnetStatus            = pstConfigInfo->enRmnetStatus;
    pstSndMsg->enIpType                 = pstConfigInfo->enIpType;
    pstSndMsg->ucPdnId                  = pstConfigInfo->ucPdnId;
    pstSndMsg->ucRabId                  = pstConfigInfo->ucRabId;
    pstSndMsg->ucRmNetId                = pstConfigInfo->ucRmNetId;
    pstSndMsg->usModemId                = pstConfigInfo->usModemId;

    /* ???????? */
    if (VOS_OK != PS_SEND_MSG(ACPU_PID_RNIC, pstSndMsg))
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_SndRnicRmnetConfigMsg: Send msg failed!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 ?? ?? ??  : RNIC_SendConfigInfoMsg
 ????????  : ??????????????????????????????????
 ????????  : ??
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2014??1??28??
    ??    ??   : m00217266
    ????????   : ??????????

*****************************************************************************/
VOS_VOID RNIC_MNTN_SndRmnetConfigInfoMsg(
    RNIC_RMNET_CONFIG_STRU             *pstConfigInfo
)
{
    RNIC_RMNET_CONFIG_REQ_STRU          *pstSndMsg = VOS_NULL_PTR;

    /* ???????? */
    pstSndMsg = (RNIC_RMNET_CONFIG_REQ_STRU *)PS_ALLOC_MSG(ACPU_PID_RNIC,
                        sizeof(RNIC_RMNET_CONFIG_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstSndMsg)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_SndRnicRmnetConfigMsg: Malloc failed!");
        return;
    }

    /* ???????? */
    pstSndMsg->enModemType              = pstConfigInfo->enModemType;
    pstSndMsg->enRmnetStatus            = pstConfigInfo->enRmnetStatus;
    pstSndMsg->enIpType                 = pstConfigInfo->enIpType;
    pstSndMsg->ucPdnId                  = pstConfigInfo->ucPdnId;
    pstSndMsg->ucRabId                  = pstConfigInfo->ucRabId;
    pstSndMsg->ucRmNetId                = pstConfigInfo->ucRmNetId;
    pstSndMsg->usModemId                = pstConfigInfo->usModemId;

    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = ACPU_PID_RNIC;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = ACPU_PID_RNIC;
    pstSndMsg->enMsgId                  = ID_RNIC_MNTN_RMNET_CONFIG_INFO;

    /* ???????? */
    if (VOS_OK != PS_SEND_MSG(ACPU_PID_RNIC, pstSndMsg))
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_SndRnicRmnetConfigMsg: Send msg failed!");
        return;
    }

    return;
}

/* Modified by m00217266 for L-C??????????, 2014-01-06, End */

