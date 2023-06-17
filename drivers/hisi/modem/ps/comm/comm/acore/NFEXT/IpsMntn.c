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
  1 ??????????????
*****************************************************************************/
#include "v_typdef.h"
#include "IpsMntn.h"
#include "TTFComm.h"
#include "v_id.h"
#include "vos.h"
#include "NetfilterEx.h"
#include "TtfOamInterface.h"
#include "TtfIpComm.h"
#include "TTFUtil.h"

/*****************************************************************************
    ??????????????????????.C??????????
*****************************************************************************/
/*lint -e767 */
#define    THIS_FILE_ID        PS_FILE_ID_ACPU_IPS_MNTN_C
/*lint -e767 */

/*****************************************************************************
  2 ??????
*****************************************************************************/

/*******************************************************************************
  3 ????????
*******************************************************************************/

/*****************************************************************************
  2 ????????
*****************************************************************************/

/*****************************************************************************
  3 ????????????
*****************************************************************************/
IPS_MNTN_TRACE_CONFIG_REQ_STRU          g_stIpsTraceMsgCfg;     /*TCP/IP??????????????????????*/

/*****************************************************************************
  4 ??????????
*****************************************************************************/

/*****************************************************************************
  5 ????????
*****************************************************************************/


/*****************************************************************************
  6 UNION????
*****************************************************************************/

/*****************************************************************************
  7 OTHERS????
*****************************************************************************/

/*****************************************************************************
  8 ????????
*****************************************************************************/

/*****************************************************************************
 ?? ?? ??  : IPS_MNTN_SndCfgCnf2Om
 ????????  : ??OM????????????????
 ????????  : usPrimId               ????ID
             usTransMsgContentLen   ????????????
             pTransMsgContent       ????????????????
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2010??8??3??
    ??    ??   : f00166181
    ????????   : ??????????

*****************************************************************************/
VOS_VOID IPS_MNTN_SndCfgCnf2Om
(
    VOS_UINT32      ulPrimId,
    VOS_UINT32      ulTransMsgContentLen,
    VOS_VOID       *pTransMsgContent
)
{
    MsgBlock                *pSendMsg;

    /*??????????????*/
    pSendMsg = VOS_AllocMsg(ACPU_PID_NFEXT, ulTransMsgContentLen - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pSendMsg)
    {
        TTF_LOG(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_ERROR,
                                "Error: IPS_MNTN_SndCfgCnf2Om, ERROR, Call VOS_AllocMsg fail!");
        return;
    }

    mdrv_memcpy(pSendMsg, pTransMsgContent, ulTransMsgContentLen);

    if ( VOS_OK != VOS_SendMsg(ACPU_PID_NFEXT, pSendMsg) )
    {
        TTF_LOG(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_ERROR,
                                "Error: IPS_MNTN_SndCfgCnf2Om, ERROR, Call VOS_SendMsg fail!");
    }

    return;
}

/*****************************************************************************
 ?? ?? ??  : IPS_MNTN_GetPktLenByTraceCfg
 ????????  : ??????????????????????????????????
 ????????  : pstTraceCfg        ????????????
             usDataLen          ????????

 ????????  : pulTraceCfgLen     ????????????
 ?? ?? ??  : PS_TRUE        -   ????????
             PS_FALSE       -   ??????????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??8??3??
    ??    ??   : f00166181
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 IPS_MNTN_GetPktLenByTraceCfg
(
    IPS_MNTN_TRACE_CONFIG_STRU     *pstTraceCfg,
    const VOS_UINT8                *pucPktData,
    VOS_UINT16                      usPktLen,
    VOS_UINT32                     *pulDataLen
)
{
    VOS_UINT32                      ulTraceDataLen;

    *pulDataLen    =   0;

    /*??????????????????*/
    switch ( pstTraceCfg->ulChoice )
    {
        case IPS_MNTN_TRACE_NULL_CHOSEN:
            return PS_FALSE;

        case IPS_MNTN_TRACE_MSG_HEADER_CHOSEN:
            ulTraceDataLen  = TTF_GetIpDataTraceLen(ACPU_PID_NFEXT, (VOS_UINT8 *)(pucPktData + MAC_HEADER_LENGTH), (usPktLen - MAC_HEADER_LENGTH));
            *pulDataLen     = TTF_MIN((ulTraceDataLen + MAC_HEADER_LENGTH), usPktLen);
            break;

        case IPS_MNTN_TRACE_CONFIGURABLE_LEN_CHOSEN:
            *pulDataLen     = TTF_MIN(pstTraceCfg->ulTraceDataLen, usPktLen);
            break;

        case IPS_MNTN_TRACE_WHOLE_DATA_LEN_CHOSEN:
            *pulDataLen     = usPktLen;
            break;

        default:
            return PS_FALSE;
    }

    return PS_TRUE;
}


/*****************************************************************************
 ?? ?? ??  : IPS_MNTN_PktInfoCB
 ????????  : ????TCP/IP????????????????????????????
 ????????  : aucNetIfName   ????????????
             aucPktData     ????????????,??????????????
             usLen          ????????????
             usType         ????????????????

 ????????  : ??
 ?? ?? ??  : ??
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??8??3??
    ??    ??   : f00166181
    ????????   : ??????????

*****************************************************************************/
/*lint -esym( 593, pucTraceData ) */
VOS_VOID IPS_MNTN_PktInfoCB
(
    const VOS_UINT8                        *pucNetIfName,
    const VOS_UINT8                        *pucPktData,
    VOS_UINT16                              usPktLen,
    TTF_MNTN_MSG_TYPE_ENUM_UINT16           enType
)
{
    VOS_UINT8                          *pucTraceData;
    IPS_MNTN_TRACE_CONFIG_STRU         *pstTraceCfg;
    IPS_MNTN_PKT_INFO_STRU             *pstTraceMsg;
    VOS_UINT32                          ulTransDataLen;
    VOS_UINT32                          ulDataLen;
    VOS_UINT32                          ulRst;
    VOS_UINT32                          ulNeedMemLen;

    ulTransDataLen  =   0;
    ulDataLen       =   0;
    ulNeedMemLen    =   0;

    if ( VOS_NULL_PTR == pucPktData )
    {
        TTF_LOG(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "IPS, IPS_MNTN_PktInfoCB, ERROR, paucPktData is NULL ");
        return;
    }

    /* HIDS?????? */
    if (VOS_NO == DIAG_GetConnState())
    {
        return;
    }

    /*????????????????????????????*/
    if(ID_IPS_TRACE_INPUT_DATA_INFO == enType)
    {
        pstTraceCfg = &(g_stIpsTraceMsgCfg.stPreRoutingTraceCfg);
    }
    else if(ID_IPS_TRACE_OUTPUT_DATA_INFO == enType)
    {
        pstTraceCfg = &(g_stIpsTraceMsgCfg.stPostRoutingTraceCfg);
    }
    else if((enType >= ID_IPS_TRACE_BRIDGE_DATA_INFO) && (enType <= ID_IPS_TRACE_BR_FORWARD_FLOW_CTRL_STOP))
    {
        pstTraceCfg = &(g_stIpsTraceMsgCfg.stLocalTraceCfg);
    }
    else
    {
        /*????????????,??????????????*/
        TTF_LOG( ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_ERROR,
                "IPS, IPS_MNTN_PktInfoCB : ERROR : usType is not Expectes!" );
        return;
    }

    /*??????????????????????????????????*/
    ulRst = IPS_MNTN_GetPktLenByTraceCfg(pstTraceCfg, pucPktData, usPktLen, &ulDataLen);
    if(PS_FALSE == ulRst)
    {
        /*????????????*/
        return;
    }

    ulDataLen           = PS_MIN(IPS_MNTN_TRACE_MAX_BYTE_LEN, ulDataLen);
    TTF_GET_OFFSET(ulTransDataLen, IPS_MNTN_PKT_INFO_STRU, aucData);
    ulTransDataLen      += ulDataLen;
    ulNeedMemLen = ulTransDataLen + sizeof(DIAG_TRANS_IND_STRU);

    /* ??Linux???????????? */
    pucTraceData = NF_EXT_MEM_ALLOC(ACPU_PID_NFEXT, ulNeedMemLen);
    if (VOS_NULL_PTR == pucTraceData)
    {
        NF_EXT_STATS_INC(1, NF_EXT_STATS_ALLOC_MEM_FAIL);

        return;
    }

    /*????????????*/
    pstTraceMsg             = (IPS_MNTN_PKT_INFO_STRU *)(pucTraceData + sizeof(DIAG_TRANS_IND_STRU));
    pstTraceMsg->usLen      = usPktLen;
    pstTraceMsg->usPrimId   = enType;
    mdrv_memcpy(pstTraceMsg->aucNetIfName, pucNetIfName, IPS_IFNAMSIZ);

    /*lint -e669 */
    mdrv_memcpy(pstTraceMsg->aucData, pucPktData, ulDataLen);
    /*lint +e669 */

    if (VOS_OK != IPS_MNTN_TransMsg(pucTraceData, ulTransDataLen, enType))
    {
        NF_EXT_MEM_FREE(ACPU_PID_NFEXT, pucTraceData);
    }

    return;
}
/*lint +esym( 593, pucTraceData ) */

/*****************************************************************************
 ?? ?? ??  : IPS_MNTN_BridgePktInfoCB
 ????????  : ????????????????????????
 ????????  : aucSrcPort     ????????????????
             aucDestPort    ????????????????
             aucPktData     ????????????,??????????????,????14????MAC????
             usPktLen       ????????????,????14????MAC??
             usType         ????????????????

 ????????  : ??
 ?? ?? ??  : ??
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??8??3??
    ??    ??   : f00166181
    ????????   : ??????????

*****************************************************************************/
/*lint -esym( 593, pucTraceData ) */
VOS_VOID IPS_MNTN_BridgePktInfoCB
(
    const VOS_UINT8                        *pucSrcPort,
    const VOS_UINT8                        *pucDestPort,
    VOS_UINT8                              *pucPktData,
    VOS_UINT16                              usPktLen,
    TTF_MNTN_MSG_TYPE_ENUM_UINT16           enType
)
{
    VOS_UINT8                          *pucTraceData;
    IPS_MNTN_TRACE_CONFIG_STRU         *pstTraceCfg;
    IPS_MNTN_BRIDGE_PKT_INFO_STRU      *pstTraceMsg;
    VOS_UINT32                          ulTransDataLen;
    VOS_UINT32                          ulDataLen;
    VOS_UINT32                          ulRst;
    VOS_UINT32                          ulNeedMemLen;

    ulTransDataLen  =   0;
    ulDataLen       =   0;
    ulNeedMemLen    =   0;



    if ( VOS_NULL_PTR == pucPktData )
    {
        TTF_LOG(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "IPS, IPS_MNTN_BridgePktInfoCB, ERROR, paucPktData is NULL ");
        return;
    }

    /* HIDS?????? */
    if (VOS_NO == DIAG_GetConnState())
    {
        return;
    }

    /*????????????????????????????*/
    if((enType >= ID_IPS_TRACE_BRIDGE_DATA_INFO) && (enType <= ID_IPS_TRACE_BR_FORWARD_FLOW_CTRL_STOP))
    {
        pstTraceCfg = &(g_stIpsTraceMsgCfg.stBridgeArpTraceCfg);
    }
    else
    {
        /*????????????,??????????????*/
        TTF_LOG( ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_ERROR,
                "IPS, IPS_MNTN_BridgePktInfoCB : ERROR : usType is not Expectes!" );
        return;
    }

    /*??????????????????????????????????*/
    ulRst = IPS_MNTN_GetPktLenByTraceCfg(pstTraceCfg, pucPktData, usPktLen, &ulDataLen);
    if(PS_FALSE == ulRst)
    {
        /*????????????*/
        return;
    }

    ulDataLen           = PS_MIN(IPS_MNTN_TRACE_MAX_BYTE_LEN, ulDataLen);
    TTF_GET_OFFSET(ulTransDataLen, IPS_MNTN_BRIDGE_PKT_INFO_STRU, aucData);
    ulTransDataLen      += ulDataLen;
    ulNeedMemLen = ulTransDataLen + sizeof(DIAG_TRANS_IND_STRU);

    /* ??Linux???????????? */
    pucTraceData = NF_EXT_MEM_ALLOC(ACPU_PID_NFEXT, ulNeedMemLen);

    if (VOS_NULL_PTR == pucTraceData)
    {
        NF_EXT_STATS_INC(1, NF_EXT_STATS_ALLOC_MEM_FAIL);

        return;
    }

    /*????????????*/
    pstTraceMsg             = (IPS_MNTN_BRIDGE_PKT_INFO_STRU *)(pucTraceData + sizeof(DIAG_TRANS_IND_STRU));
    pstTraceMsg->usLen      = usPktLen;
    pstTraceMsg->usPrimId   = enType;

    if (VOS_NULL_PTR != pucSrcPort)
    {
        mdrv_memcpy(pstTraceMsg->aucSrcPort, pucSrcPort, IPS_END_NAME);
    }
    if (VOS_NULL_PTR != pucDestPort)
    {
        mdrv_memcpy(pstTraceMsg->aucDestPort, pucDestPort, IPS_END_NAME);
    }

    /*lint -e669 */
    mdrv_memcpy(pstTraceMsg->aucData, pucPktData, ulDataLen);
    /*lint +e669 */

    if (VOS_OK != IPS_MNTN_TransMsg(pucTraceData, ulTransDataLen, enType))
    {
        NF_EXT_MEM_FREE(ACPU_PID_NFEXT, pucTraceData);
    }

    return;

}
/*lint +esym( 593, pucTraceData ) */

/*****************************************************************************
 ?? ?? ??  : IPS_MNTN_CtrlPktInfoCB
 ????????  : ????TCP/IP??????????????????????
 ????????  : aucNetIfName   ????????????
             aucPktData     ????????????,??????????????
             usLen          ????????????
             usType         ????????????????

 ????????  : ??
 ?? ?? ??  : ??
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??8??3??
    ??    ??   : f00166181
    ????????   : ??????????

*****************************************************************************/
/*lint -esym( 593, pucTraceData ) */
VOS_VOID IPS_MNTN_CtrlPktInfoCB
(
    const VOS_UINT8                        *pucNetIfName,
    const VOS_UINT8                        *pucPktData,
    VOS_UINT16                              usPktLen,
    TTF_MNTN_MSG_TYPE_ENUM_UINT16           enType
)
{

    VOS_UINT8                          *pucTraceData;
    IPS_MNTN_PKT_INFO_STRU             *pstTraceMsg;
    VOS_UINT32                          ulTransDataLen;
    VOS_UINT32                          ulDataLen;
    VOS_UINT32                          ulNeedMemLen;

    ulTransDataLen  =   0;
    ulDataLen       =   0;
    ulNeedMemLen    =   0;

    if ( VOS_NULL_PTR == pucPktData )
    {
        TTF_LOG(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "IPS, IPS_MNTN_CtrlPktInfoCB, ERROR, pucPktData is NULL ");
        return;
    }

    /* HIDS?????? */
    if (VOS_NO == DIAG_GetConnState())
    {
        return;
    }

    ulDataLen           = PS_MIN(IPS_MNTN_TRACE_MAX_BYTE_LEN, usPktLen);
    TTF_GET_OFFSET(ulTransDataLen, IPS_MNTN_PKT_INFO_STRU, aucData);
    ulTransDataLen      += ulDataLen;
    ulNeedMemLen = ulTransDataLen + sizeof(DIAG_TRANS_IND_STRU);

    /* ??Linux???????????? */
    pucTraceData = NF_EXT_MEM_ALLOC(ACPU_PID_NFEXT, ulNeedMemLen);

    if (VOS_NULL_PTR == pucTraceData)
    {
        NF_EXT_STATS_INC(1, NF_EXT_STATS_ALLOC_MEM_FAIL);

        return;
    }

    /*????????????*/
    pstTraceMsg             = (IPS_MNTN_PKT_INFO_STRU *)(pucTraceData + sizeof(DIAG_TRANS_IND_STRU));
    pstTraceMsg->usLen      = usPktLen;
    pstTraceMsg->usPrimId   = enType;
    mdrv_memcpy(pstTraceMsg->aucNetIfName, pucNetIfName, IPS_IFNAMSIZ);
    /*lint -e669 */
    mdrv_memcpy(pstTraceMsg->aucData, pucPktData, ulDataLen);
    /*lint +e669 */

    if (VOS_OK != IPS_MNTN_TransMsg(pucTraceData, ulTransDataLen, enType))
    {
        NF_EXT_MEM_FREE(ACPU_PID_NFEXT, pucTraceData);

    }

    return;
}
/*lint +esym( 593, pucTraceData ) */

/*****************************************************************************
 ?? ?? ??  : IPS_MNTN_FlowCtrl
 ????????  : ??????????????????????
 ????????  : ulFcType ??????????????????????forward????
             usType   ????????????????
 ????????  : ??
 ?? ?? ??  : void
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2012??01??12??
    ??    ??   : t00148005
    ????????   : ??????????

*****************************************************************************/
VOS_VOID IPS_MNTN_FlowCtrl(VOS_UINT32 ulFcType, TTF_MNTN_MSG_TYPE_ENUM_UINT16  enType)
{
    DIAG_TRANS_IND_STRU                 stTransData;
    IPS_MNTN_FLOW_CTRL_STRU             stFlowCtrlMsg;

    PSACORE_MEM_SET(&stFlowCtrlMsg, sizeof(IPS_MNTN_FLOW_CTRL_STRU), 0x0, sizeof(IPS_MNTN_FLOW_CTRL_STRU));

    /* ???????? */
    stTransData.ulPid       = ACPU_PID_NFEXT;
    stTransData.ulMsgId     = enType;
    stTransData.ulModule    = DIAG_GEN_MODULE(MODEM_ID_0, DIAG_MODE_COMM);
    stTransData.ulLength    = MNTN_FLOW_CTRL_INFO_LEN;
    stTransData.pData       = &stFlowCtrlMsg;

    stFlowCtrlMsg.ulFcType  = ulFcType;
    stFlowCtrlMsg.usPrimId  = enType;

    if ( VOS_OK != DIAG_TransReport(&stTransData) )
    {
        TTF_LOG(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "IPS, DIAG_TransReport, ERROR, Call DIAG_TransReport fail!");
    }

    return;
}


/*****************************************************************************
 ?? ?? ??  : IPS_MNTN_SndTransInd2Om
 ????????  : ??OM????????????
 ????????  : pTransMsgContent       ????????????????
 ????????  : ??
 ?? ?? ??  : VOS_UINT32 ????????????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??7??30??
    ??    ??   : f00166181
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 IPS_MNTN_TransMsg
(
    VOS_UINT8                              *pucTransMsg,
    VOS_UINT32                              ulTransMsgContentLen,
    TTF_MNTN_MSG_TYPE_ENUM_UINT16           enMsgName
)
{
    NF_EXT_DATA_RING_BUF_STRU               stBufData;
    DIAG_TRANS_IND_STRU                     *pstDiagTransData;

    /*????????*/
    pstDiagTransData            = (DIAG_TRANS_IND_STRU *)pucTransMsg;

    /* ???????? */
    pstDiagTransData->ulPid     = ACPU_PID_NFEXT;
    pstDiagTransData->ulMsgId   = enMsgName;
    pstDiagTransData->ulModule  = DIAG_GEN_MODULE(MODEM_ID_0, DIAG_MODE_COMM);
    pstDiagTransData->ulLength  = ulTransMsgContentLen;
    pstDiagTransData->pData     = pucTransMsg + sizeof(DIAG_TRANS_IND_STRU);

    /* ????????????????????????????, ???????????????????? */
    if (VOS_FALSE != VOS_CheckInterrupt())
    {
        stBufData.pData         = (VOS_UINT8 *)pucTransMsg;
        stBufData.usDataLen     = (VOS_UINT16)(ulTransMsgContentLen + sizeof(DIAG_TRANS_IND_STRU));

        if (VOS_OK != NFExt_AddDataToRingBuf(&stBufData))
        {
            return VOS_ERR;
        }
    }
    else
    {
        (VOS_VOID)DIAG_TransReport(pstDiagTransData);
        NF_EXT_MEM_FREE(ACPU_PID_NFEXT, pucTransMsg);
    }

    return VOS_OK;
}

/*****************************************************************************
 ?? ?? ??  : IPS_MNTN_BridgeTraceCfgChkParam
 ????????  : ????????????????????????
 ????????  : pRcvMsg
 ????????  : ??
 ?? ?? ??  : VOS_TRUE/VOS_FALSE
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??7??30??
    ??    ??   : f00166181
    ????????   : ??????????

*****************************************************************************/
PS_BOOL_ENUM_UINT8  IPS_MNTN_BridgeTraceCfgChkParam(IPS_MNTN_TRACE_CONFIG_REQ_STRU *pRcvMsg)
{
    if ( (IPS_MNTN_TRACE_NULL_CHOSEN != pRcvMsg->stBridgeArpTraceCfg.ulChoice)
        && (IPS_MNTN_TRACE_MSG_HEADER_CHOSEN != pRcvMsg->stBridgeArpTraceCfg.ulChoice)
        && (IPS_MNTN_TRACE_CONFIGURABLE_LEN_CHOSEN != pRcvMsg->stBridgeArpTraceCfg.ulChoice)
        && (IPS_MNTN_TRACE_WHOLE_DATA_LEN_CHOSEN != pRcvMsg->stBridgeArpTraceCfg.ulChoice) )
    {
        return PS_FALSE;
    }

    return PS_TRUE;
}

/*****************************************************************************
 ?? ?? ??  : IPS_MNTN_WanTraceCfgChkParam
 ????????  : TCP/IP??????????????????????????
 ????????  : pRcvMsg
 ????????  : ??
 ?? ?? ??  : VOS_TRUE/VOS_FALSE
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??7??30??
    ??    ??   : f00166181
    ????????   : ??????????

*****************************************************************************/
PS_BOOL_ENUM_UINT8  IPS_MNTN_TraceCfgChkParam(IPS_MNTN_TRACE_CONFIG_REQ_STRU *pRcvMsg)
{
    if (IPS_MNTN_TRACE_WHOLE_DATA_LEN_CHOSEN < pRcvMsg->stPreRoutingTraceCfg.ulChoice)
    {
        return PS_FALSE;
    }

    if (IPS_MNTN_TRACE_WHOLE_DATA_LEN_CHOSEN < pRcvMsg->stPostRoutingTraceCfg.ulChoice)
    {
        return PS_FALSE;
    }

    if (IPS_MNTN_TRACE_WHOLE_DATA_LEN_CHOSEN < pRcvMsg->stLocalTraceCfg.ulChoice)
    {
        return PS_FALSE;
    }

    if (IPS_MNTN_TRACE_WHOLE_DATA_LEN_CHOSEN < pRcvMsg->stBridgeArpTraceCfg.ulChoice)
    {
        return PS_FALSE;
    }

    if (WTTF_TRACE_MSG_YES < pRcvMsg->enAdsIPConfig)
    {
        return PS_FALSE;
    }

    return PS_TRUE;
}

/*****************************************************************************
 ?? ?? ??  : IPS_MNTN_TraceAdvancedCfgChkParam
 ????????  : ????????????????
 ????????  : pRcvMsg
 ????????  : ??
 ?? ?? ??  : VOS_TRUE/VOS_FALSE
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??7??30??
    ??    ??   : f00166181
    ????????   : ??????????

*****************************************************************************/
PS_BOOL_ENUM_UINT8  IPS_MNTN_TraceAdvancedCfgChkParam(IPS_MNTN_TRACE_CONFIG_REQ_STRU *pRcvMsg)
{
    /*TCP/IP??????????????????????????*/
    if (PS_FALSE == IPS_MNTN_TraceCfgChkParam(pRcvMsg))
    {
        return PS_FALSE;
    }

    /*????????????????????????????*/
    if (PS_FALSE == IPS_MNTN_BridgeTraceCfgChkParam(pRcvMsg))
    {
        return  PS_FALSE;
    }

    if ((WTTF_TRACE_MSG_YES != pRcvMsg->enAdsIPConfig) && (WTTF_TRACE_MSG_NO != pRcvMsg->enAdsIPConfig))
    {
        return PS_FALSE;
    }

    return PS_TRUE;
}

/*****************************************************************************
 ?? ?? ??  : IPS_MNTN_TraceAdvancedCfgReq
 ????????  : ????????????
 ????????  : pMsg
 ????????  : ??
 ?? ?? ??  : void
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??7??30??
    ??    ??   : f00166181
    ????????   : ??????????

*****************************************************************************/
VOS_VOID IPS_MNTN_TraceAdvancedCfgReq(VOS_VOID *pMsg)
{
    PS_BOOL_ENUM_UINT8                       enResult;

    OM_IPS_ADVANCED_TRACE_CONFIG_REQ_STRU    *pRcvMsg;
    IPS_OM_ADVANCED_TRACE_CONFIG_CNF_STRU    stIpsTraceCfgCnf;

    pRcvMsg = (OM_IPS_ADVANCED_TRACE_CONFIG_REQ_STRU *)pMsg;

    /*????????????????????*/
    enResult = IPS_MNTN_TraceAdvancedCfgChkParam(&(pRcvMsg->stIpsAdvanceCfgReq));

    /* Fill DIAG trans msg header */
    stIpsTraceCfgCnf.stDiagHdr.ulSenderCpuId        = VOS_LOCAL_CPUID;
    stIpsTraceCfgCnf.stDiagHdr.ulSenderPid          = ACPU_PID_NFEXT;
    stIpsTraceCfgCnf.stDiagHdr.ulReceiverCpuId      = VOS_LOCAL_CPUID;
    stIpsTraceCfgCnf.stDiagHdr.ulReceiverPid        = MSP_PID_DIAG_APP_AGENT;   /* ????????????????DIAG????DIAG??????????????????????????HIDS????*/
    stIpsTraceCfgCnf.stDiagHdr.ulLength             = sizeof(IPS_OM_ADVANCED_TRACE_CONFIG_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    stIpsTraceCfgCnf.stDiagHdr.ulMsgId              = ID_IPS_OM_ADVANCED_TRACE_CONFIG_CNF;

    /* DIAG????????????????????*/
    stIpsTraceCfgCnf.stDiagHdr.usOriginalId         = pRcvMsg->stDiagHdr.usOriginalId;
    stIpsTraceCfgCnf.stDiagHdr.usTerminalId         = pRcvMsg->stDiagHdr.usTerminalId;
    stIpsTraceCfgCnf.stDiagHdr.ulTimeStamp          = pRcvMsg->stDiagHdr.ulTimeStamp;
    stIpsTraceCfgCnf.stDiagHdr.ulSN                 = pRcvMsg->stDiagHdr.ulSN;

    if ( PS_FALSE == enResult )
    {
        /*??????????????????????OM????????????*/
        stIpsTraceCfgCnf.stIpsAdvanceCfgCnf.enRslt  =   PS_FAIL;

        IPS_MNTN_SndCfgCnf2Om(ID_IPS_OM_ADVANCED_TRACE_CONFIG_CNF,
            sizeof(IPS_OM_ADVANCED_TRACE_CONFIG_CNF_STRU), &stIpsTraceCfgCnf );

        TTF_LOG(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "Warning: IPS_MNTN_TraceAdvancedCfgReq check fail");

        return;
    }

    enResult = NFExt_ConfigEffective(&(pRcvMsg->stIpsAdvanceCfgReq));
    if( PS_FALSE == enResult )
    {
        /*????????????????????????OM????????????*/
        stIpsTraceCfgCnf.stIpsAdvanceCfgCnf.enRslt =   PS_FAIL;

        IPS_MNTN_SndCfgCnf2Om(ID_IPS_OM_ADVANCED_TRACE_CONFIG_CNF,
            sizeof(IPS_OM_ADVANCED_TRACE_CONFIG_CNF_STRU), &stIpsTraceCfgCnf );

        TTF_LOG(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "Warning: IPS_MNTN_SetCallbackFunc fail");

        return;
    }

    /*????????????*/
    PSACORE_MEM_CPY(&g_stIpsTraceMsgCfg, sizeof(IPS_MNTN_TRACE_CONFIG_REQ_STRU), &(pRcvMsg->stIpsAdvanceCfgReq), sizeof(IPS_MNTN_TRACE_CONFIG_REQ_STRU));

    /*??OM????????????*/
    stIpsTraceCfgCnf.stIpsAdvanceCfgCnf.enRslt = PS_SUCC;

    IPS_MNTN_SndCfgCnf2Om(ID_IPS_OM_ADVANCED_TRACE_CONFIG_CNF,
            sizeof(IPS_OM_ADVANCED_TRACE_CONFIG_CNF_STRU), &stIpsTraceCfgCnf );

    return;

}

/*****************************************************************************
 ?? ?? ??  :IPS_MNTN_Ipv4DataParse
 ????????  :????IP??????
 ????????  :IPS_MNTN_IP_INFO_STRU *pstTraceMsg
            VOS_UINT8 *pData
 ????????  :
 ?? ?? ??  : ??
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   :  2012??10??29??
    ??    ??   :  00199705
    ????????   :  ????????
*****************************************************************************/
VOS_VOID IPS_MNTN_Ipv4DataParse(IPS_MNTN_IP_INFO_STRU *pstIpInfo,VOS_UINT8 *pData)
{
    switch (pstIpInfo->ucL4Proto)
    {
        case IP_IPV4_PROTO_TCP:
            pstIpInfo->usSrcPort      = IP_GET_VAL_NTOH_U16(pData, IP_IPV4_HEAD_LEN);
            pstIpInfo->usDstPort      = IP_GET_VAL_NTOH_U16(pData, (IP_IPV4_HEAD_LEN + IP_IPV4_DST_PORT_POS));
            pstIpInfo->ulL4Id         = IP_GET_VAL_NTOH_U32(pData, (IP_IPV4_HEAD_LEN + IP_IPV4_TCP_SEQ_POS));
            pstIpInfo->ulTcpAckSeq    = IP_GET_VAL_NTOH_U32(pData, (IP_IPV4_HEAD_LEN + IP_IPV4_TCP_ACK_POS));
            break;

        case IP_IPV4_PROTO_UDP:
            pstIpInfo->usSrcPort      = IP_GET_VAL_NTOH_U16(pData, IP_IPV4_HEAD_LEN);
            pstIpInfo->usDstPort      = IP_GET_VAL_NTOH_U16(pData, (IP_IPV4_HEAD_LEN + IP_IPV4_DST_PORT_POS));
            break;

        case IP_IPV4_PROTO_ICMP:
            pstIpInfo->ucIcmpType     = IP_GET_VAL_NTOH_U8(pData, IP_IPV4_HEAD_LEN);
            if ((IP_IPV4_ICMP_ECHO_REQUEST == pstIpInfo->ucIcmpType)
                ||(IP_IPV4_ICMP_ECHO_REPLY == pstIpInfo->ucIcmpType))
            {
                pstIpInfo->ulL4Id     = IP_GET_VAL_NTOH_U32(pData, (IP_IPV4_HEAD_LEN + IP_IPV4_ICMP_IDENTIFY_POS));
            }
            break;

        default:
            break;
    }

    return;
}

/*****************************************************************************
 ?? ?? ??  :IPS_MNTN_Ipv6DataParse
 ????????  :????IP??????
 ????????  :IPS_MNTN_IP_INFO_STRU *pstTraceMsg
            VOS_UINT8 *pData
 ????????  :
 ?? ?? ??  : ??
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   :  2012??10??29??
    ??    ??   :  00199705
    ????????   :  ????????
*****************************************************************************/
VOS_VOID IPS_MNTN_Ipv6DataParse(IPS_MNTN_IP_INFO_STRU *pstIpInfo,VOS_UINT8 *pData)
{
    switch (pstIpInfo->ucL4Proto)
    {
        case IP_IPV6_PROTO_TCP:
            pstIpInfo->usSrcPort      = IP_GET_VAL_NTOH_U16(pData, IP_IPV6_HEAD_LEN);
            pstIpInfo->usDstPort      = IP_GET_VAL_NTOH_U16(pData, (IP_IPV6_HEAD_LEN + IP_IPV6_DST_PORT_POS));
            pstIpInfo->ulL4Id         = IP_GET_VAL_NTOH_U32(pData, (IP_IPV6_HEAD_LEN + IP_IPV6_TCP_SEQ_POS));
            pstIpInfo->ulTcpAckSeq    = IP_GET_VAL_NTOH_U32(pData, (IP_IPV6_HEAD_LEN + IP_IPV6_TCP_ACK_POS));
            break;

        case IP_IPV6_PROTO_UDP:
            pstIpInfo->usSrcPort      = IP_GET_VAL_NTOH_U16(pData, IP_IPV6_HEAD_LEN);
            pstIpInfo->usDstPort      = IP_GET_VAL_NTOH_U16(pData, (IP_IPV6_HEAD_LEN + IP_IPV6_DST_PORT_POS));
            break;

        case IP_IPV6_PROTO_ICMP:
            pstIpInfo->ucIcmpType     = IP_GET_VAL_NTOH_U8(pData, IP_IPV6_HEAD_LEN);
            if ((IP_IPV6_ICMP_ECHO_REQUEST == pstIpInfo->ucIcmpType)
                ||(IP_IPV6_ICMP_ECHO_REPLY == pstIpInfo->ucIcmpType))
            {
                pstIpInfo->ulL4Id     = IP_GET_VAL_NTOH_U32(pData, (IP_IPV6_HEAD_LEN + IP_IPV4_ICMP_IDENTIFY_POS));
            }
            break;

        default:
            break;
    }

    return;
}


/*****************************************************************************
 ?? ?? ??  :IPS_MNTN_GetIPInfoCfg
 ????????  :IP??????????????
 ????????  :VOS_UINT16 usType
 ????????  :
 ?? ?? ??  : ??
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   :  2012??10??29??
    ??    ??   :  00199705
    ????????   :  ????????
*****************************************************************************/
VOS_UINT32 IPS_MNTN_GetIPInfoCfg(TTF_MNTN_MSG_TYPE_ENUM_UINT16 enType)
{
    if ((ID_IPS_TRACE_ADS_UL == enType)||(ID_IPS_TRACE_ADS_DL == enType))
    {
        if (WTTF_TRACE_MSG_YES == g_stIpsTraceMsgCfg.enAdsIPConfig)
        {
            return PS_TRUE;
        }
    }

    return PS_FALSE;
}

/*****************************************************************************
 ?? ?? ??  : IPS_MNTN_TraceIpInfo
 ????????  : ??OM????????????
 ????????  : skb_buff  IP??????
             usType    ????ID
 ????????  : ??
 ?? ?? ??  : ??
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2012??10??15??
    ??    ??   : 00199705
    ????????   : ??????????

*****************************************************************************/
/*lint -esym( 593, pucTraceData ) */
VOS_VOID IPS_MNTN_TraceIpInfo(
    struct sk_buff *skb,
    TTF_MNTN_MSG_TYPE_ENUM_UINT16 enType,
    VOS_UINT32 ulParam1,
    VOS_UINT32 ulParam2,
    VOS_UINT32 ulParam3,
    VOS_UINT32 ulParam4)
{
    VOS_UINT32                      ulRst;
    VOS_UINT8                      *pIpData;
    VOS_UINT16                      usIpDataLen;
    IPS_MNTN_IP_INFO_STRU          *pstIpInfo;
    VOS_UINT8                      *pucTraceData;

    /* HIDS?????? */
    if (VOS_NO == DIAG_GetConnState())
    {
        return;
    }

    ulRst = IPS_MNTN_GetIPInfoCfg(enType);
    if(PS_FALSE == ulRst)
    {
        /*????????????*/
        return;
    }

    if ((VOS_NULL_PTR == skb)||(VOS_NULL_PTR == skb->data))
    {
        TTF_LOG(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "IPS, IPS_MNTN_TraceIpInfo, ERROR, skb or skb->data is NULL ");
        return;
    }

    /* USB??????skb data??????IP??????????????MAC????IP??????*/
    pIpData         = skb->data;

    if (IP_IPV4_VER_AND_HEAD == *pIpData)
    {
        usIpDataLen = IP_GET_VAL_NTOH_U16(pIpData, IP_IPV4_DATA_LEN_POS);
    }
    else if (IP_IPV6_VER_AND_HEAD == *pIpData)
    {
        usIpDataLen = IP_GET_VAL_NTOH_U16(pIpData, IP_IPV6_DATA_LEN_POS) + IP_IPV6_HEAD_LEN;
    }
    else
    {
        usIpDataLen = 0;
    }

    if (usIpDataLen != skb->len)
    {
        pIpData     += MAC_HEAD_LEN;
    }

    /* ??Linux???????????? */
    pucTraceData = NF_EXT_MEM_ALLOC(ACPU_PID_NFEXT, MNTN_IP_INFO_LEN + sizeof(DIAG_TRANS_IND_STRU));
    if (VOS_NULL_PTR == pucTraceData)
    {
        NF_EXT_STATS_INC(1, NF_EXT_STATS_ALLOC_MEM_FAIL);
        return;
    }

    pstIpInfo               = (IPS_MNTN_IP_INFO_STRU *)(pucTraceData + sizeof(DIAG_TRANS_IND_STRU));
    pstIpInfo->ucIpVer      = *pIpData>>IP_PROTO_VERSION_POS;

    pstIpInfo->usPrimId     = enType;

    pstIpInfo->ulParam1     = ulParam1;
    pstIpInfo->ulParam2     = ulParam2;
    pstIpInfo->ulParam3     = ulParam3;
    pstIpInfo->ulParam4     = ulParam4;

    /* IP????????TCP,UDP,ICMP????????IP????????*/
    if (IP_IPV4_PROTO_VERSION == pstIpInfo->ucIpVer)
    {
        pstIpInfo->usDataLen  = IP_GET_VAL_NTOH_U16(pIpData, IP_IPV4_DATA_LEN_POS);
        if ((pstIpInfo->usDataLen == skb->len)||(pstIpInfo->usDataLen == (skb->len - MAC_HEAD_LEN)))
        {
            pstIpInfo->usIp4Id    = IP_GET_VAL_NTOH_U16(pIpData, IP_IPV4_IDENTIFY_POS);
            pstIpInfo->ucL4Proto  = IP_GET_VAL_NTOH_U8(pIpData, IP_IPV4_PROTO_POS);

            IPS_MNTN_Ipv4DataParse(pstIpInfo, pIpData);
        }
    }

    if (IP_IPV6_PROTO_VERSION == pstIpInfo->ucIpVer)
    {
        pstIpInfo->usDataLen  = IP_GET_VAL_NTOH_U16(pIpData, IP_IPV6_DATA_LEN_POS) + IP_IPV6_HEAD_LEN;
        if ((pstIpInfo->usDataLen == skb->len)||(pstIpInfo->usDataLen == (skb->len - MAC_HEAD_LEN)))
        {
            pstIpInfo->ucL4Proto  = IP_GET_VAL_NTOH_U8(pIpData, IP_IPV6_PROTO_POS);
            pstIpInfo->usIp4Id    = 0;

            IPS_MNTN_Ipv6DataParse(pstIpInfo, pIpData);
        }
    }

    if (VOS_OK != IPS_MNTN_TransMsg(pucTraceData, MNTN_IP_INFO_LEN, enType))
    {
        NF_EXT_MEM_FREE(ACPU_PID_NFEXT, pucTraceData);
    }

    return;
}
/*lint +esym( 593, pucTraceData ) */
