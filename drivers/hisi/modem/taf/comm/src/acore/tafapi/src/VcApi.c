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
#include "AppVcApi.h"
#include "vos.h"
#include "PsCommonDef.h"
#include "ATCmdProc.h"




/*lint -e767 -e960*/
#define    THIS_FILE_ID        PS_FILE_ID_VC_API_C
/*lint +e767 +e960*/

/*****************************************************************************
   2 ????????
*****************************************************************************/

/*****************************************************************************
?? ?? ??  : VCI_SetVoiceVolume
????????  : ????????????
????????  : ??
????????  : ??
?? ?? ??  : VOS_OK
????????  : SI_InitGlobeVariable
????????  :
????????  :
1.  ??    ??   : 2009??07??05??
    ??    ??   : h44270
    ????????   : Creat
2.  ??    ??   : 2011??11??07??
    ??    ??   : f00179208
    ????????   : AT Project, ????????WUEPS_PID_VC??WUEPS_PID_AT
3.  ??    ??   : 2012??12??21??
    ??    ??   : l00227485
    ????????   : DSDA PhaseII
*****************************************************************************/
VOS_UINT32  APP_VC_SetVoiceVolume(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    VOS_UINT8                           ucVoiceVolume
)
{
    /*??????????????????VC????*/
    VOS_UINT32                          ulRslt;
    APP_VC_REQ_MSG_STRU                *pstMsg;

    /* ???????? */
    pstMsg = (APP_VC_REQ_MSG_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT,
                  sizeof(APP_VC_REQ_MSG_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_ERR_LOG("APP_VC_SetVoiceVolume: ALLOC MSG FAIL.");
        return VOS_ERR;
    }

    pstMsg->clientId                    = ClientId;
    pstMsg->opId                        = OpId;
    pstMsg->enMsgName                   = APP_VC_MSG_REQ_SET_VOLUME;
    pstMsg->ulSenderPid                 = WUEPS_PID_AT;
    pstMsg->ulReceiverPid               = AT_GetDestPid(ClientId, I0_WUEPS_PID_VC);
    pstMsg->aucContent[0]               = ucVoiceVolume;
    pstMsg->aucContent[1]               = 0;
    pstMsg->aucContent[2]               = 0;
    pstMsg->aucContent[3]               = 0;

    ulRslt = PS_SEND_MSG(WUEPS_PID_AT, pstMsg);
    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("APP_VC_SetVoiceVolume: SEND MSG FAIL.");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
?? ?? ??  : APP_VC_SetVoiceMode
????????  : ????????????
????????  : ??
????????  : ??
?? ?? ??  : VOS_OK
????????  : SI_InitGlobeVariable
????????  :
????????  :
  1.??    ??   : 2009??07??05??
    ??    ??   : h44270
    ????????   : Creat
  2.??    ??   : 2011??11??07??
    ??    ??   : f00179208
    ????????   : AT Project, ????????WUEPS_PID_VC??WUEPS_PID_AT
  3.??    ??   : 2012??12??21??
    ??    ??   : l00227485
    ????????   : DSDA PhaseII
  4.??    ??   : 2013??9??30??
    ??    ??   : Y00213812
    ????????   : DTS2013092802198: ^VMSET & ^CVOICE????????????????
  5.??    ??   : 2015??5??28??
    ??    ??   : l00198894
    ????????   : TSTS
  6.??    ??   : 2016??6??16??
    ??    ??   : h00360002
    ????????   : DTS2016052303305
*****************************************************************************/
VOS_UINT32  APP_VC_SetVoiceMode(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    VOS_UINT8                           ucVoiceMode,
    VOS_UINT32                          ulRcvPid
)
{
    /*??????????????????VC????*/
    VOS_UINT32                          ulRslt;
    APP_VC_REQ_MSG_STRU                *pstMsg;

    /* ???????? */
    pstMsg = (APP_VC_REQ_MSG_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT,
                  sizeof(APP_VC_REQ_MSG_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_ERR_LOG("APP_VC_SetVoiceMode: ALLOC MSG FAIL.");
        return VOS_ERR;
    }

    pstMsg->clientId                    = ClientId;
    pstMsg->opId                        = OpId;
    pstMsg->enMsgName                   = APP_VC_MSG_REQ_SET_MODE;
    pstMsg->ulSenderPid                 = WUEPS_PID_AT;
    pstMsg->ulReceiverPid               = ulRcvPid;
    pstMsg->aucContent[0]               = ucVoiceMode;
    pstMsg->aucContent[1]               = 0;
    pstMsg->aucContent[2]               = 0;
    pstMsg->aucContent[3]               = 0;

    ulRslt = PS_SEND_MSG(WUEPS_PID_AT, pstMsg);
    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("APP_VC_SetVoiceMode: SEND MSG FAIL.");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
?? ?? ??  : APP_VC_SetVoicePort
????????  : ????????????
????????  : APP_VC_VOICE_PORT_ENUM_U8   ucVoicePort - ??????????????
????????  : ??
?? ?? ??  : ??????????????
????????  :
????????  :
????????  :
1.  ??    ??   : 2010??04??16??
    ??    ??   : o00132663
    ????????   : Creat
2.  ??    ??   : 2011??10??06??
    ??    ??   : f00179208
    ????????   : AT????????
3.  ??    ??   : 2012??12??21??
    ??    ??   : l00227485
    ????????   : DSDA PhaseII
*****************************************************************************/
VOS_UINT32 APP_VC_SetVoicePort(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    APP_VC_VOICE_PORT_ENUM_U8           ucVoicePort
)
{
    /*??????????????????VC????*/
    VOS_UINT32                          ulRslt;
    APP_VC_REQ_MSG_STRU                *pstMsg;


    /* ???????? */
    pstMsg = (APP_VC_REQ_MSG_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT,
                  sizeof(APP_VC_REQ_MSG_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_ERR_LOG("APP_VC_SetVoicePort: ALLOC MSG FAIL.");
        return VOS_ERR;
    }

    pstMsg->clientId                    = ClientId;
    pstMsg->opId                        = OpId;
    pstMsg->enMsgName                   = APP_VC_MSG_REQ_SET_PORT;
    pstMsg->ulSenderPid                 = WUEPS_PID_AT;
    pstMsg->ulReceiverPid               = AT_GetDestPid(ClientId, I0_WUEPS_PID_VC);
    pstMsg->aucContent[0]               = ucVoicePort;
    pstMsg->aucContent[1]               = 0;
    pstMsg->aucContent[2]               = 0;
    pstMsg->aucContent[3]               = 0;

    ulRslt = PS_SEND_MSG(WUEPS_PID_AT, pstMsg);
    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("APP_VC_GetVoiceMode: SEND MSG FAIL.");
        return VOS_ERR;
    }
    return VOS_OK;

}

/*****************************************************************************
?? ?? ??  : APP_VC_GetVoiceMode
????????  : ??????????????????
????????  : ??
????????  : ??
?? ?? ??  : TAF_SUCCESS
????????  :
????????  :
????????  :
1.  ??    ??   : 2011??10??05??
    ??    ??   : f00179208
    ????????   : Creat
2.  ??    ??   : 2011??10??06??
    ??    ??   : f00179208
    ????????   : AT????????, ??????????????C??????????????
3.  ??    ??   : 2012??12??21??
    ??    ??   : l00227485
    ????????   : DSDA PhaseII
*****************************************************************************/
VOS_UINT32 APP_VC_GetVoiceMode(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId
)
{
    /*??????????????????VC????*/
    VOS_UINT32                          ulRslt;
    APP_VC_REQ_MSG_STRU                *pstMsg;

    /* ???????? */
    pstMsg = (APP_VC_REQ_MSG_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT,
                  sizeof(APP_VC_REQ_MSG_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_ERR_LOG("APP_VC_GetVoiceMode: ALLOC MSG FAIL.");
        return VOS_ERR;
    }

    pstMsg->clientId                    = ClientId;
    pstMsg->opId                        = OpId;
    pstMsg->enMsgName                   = APP_VC_MSG_REQ_QRY_MODE;
    pstMsg->ulSenderPid                 = WUEPS_PID_AT;
    pstMsg->ulReceiverPid               = AT_GetDestPid(ClientId, I0_WUEPS_PID_VC);
    pstMsg->aucContent[0]               = 0;
    pstMsg->aucContent[1]               = 0;
    pstMsg->aucContent[2]               = 0;
    pstMsg->aucContent[3]               = 0;

    ulRslt = PS_SEND_MSG(WUEPS_PID_AT, pstMsg);
    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("APP_VC_GetVoiceMode: SEND MSG FAIL.");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
?? ?? ??  : APP_VC_GetVoicePort
????????  : ??????????????????
????????  :     MN_CLIENT_ID_T              ClientId
                MN_OPERATION_ID_T           OpId

????????  : ??
?? ?? ??  : VOS_UINT32 - VOS_OK
                         VOS_ERR
????????  :
????????  :
????????  :
1.  ??    ??   : 2010??04??16??
    ??    ??   : o00132663
    ????????   : Creat
2.  ??    ??   : 2011??10??06??
    ??    ??   : f00179208
    ????????   : AT????????
3.  ??    ??   : 2012??12??21??
    ??    ??   : l00227485
    ????????   : DSDA PhaseII
*****************************************************************************/
VOS_UINT32 APP_VC_GetVoicePort(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId
)
{
    /*??????????????????VC????*/
    VOS_UINT32                          ulRslt;
    APP_VC_REQ_MSG_STRU                *pstMsg;

    /* ???????? */
    pstMsg = (APP_VC_REQ_MSG_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT,
                  sizeof(APP_VC_REQ_MSG_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_ERR_LOG("APP_VC_GetVoicePort: ALLOC MSG FAIL.");
        return VOS_ERR;
    }

    /* ???????? */
    pstMsg->clientId                    = ClientId;
    pstMsg->opId                        = OpId;
    pstMsg->enMsgName                   = APP_VC_MSG_REQ_QRY_PORT;
    pstMsg->ulSenderPid                 = WUEPS_PID_AT;
    pstMsg->ulReceiverPid               = AT_GetDestPid(ClientId, I0_WUEPS_PID_VC);
    pstMsg->aucContent[0]               = 0;
    pstMsg->aucContent[1]               = 0;
    pstMsg->aucContent[2]               = 0;
    pstMsg->aucContent[3]               = 0;

    ulRslt = PS_SEND_MSG(WUEPS_PID_AT, pstMsg);
    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("APP_VC_GetVoicePort: SEND MSG FAIL.");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
?? ?? ??  : APP_VC_AppVcVoiceMode2VcPhyVoiceMode
????????  : ??????VC??????????????????????VC????????????????????????????
????????  : APP_VC_VOICE_MODE_ENUM_U16  usVoiceMode - ??????VC????????????????
????????  : ??
?? ?? ??  : VC_PHY_DEVICE_MODE_ENUM_U16 - VC????????????????????
????????  :
????????  :
????????  :
1.  ??    ??   : 2021??04??17??
    ??    ??   : o00132663
    ????????   : Creat
2.  ??    ??   : 2011??10??06??
    ??    ??   : f00179208
    ????????   : AT????????, ??????????C????????A??
*****************************************************************************/
VC_PHY_DEVICE_MODE_ENUM_U16  APP_VC_AppVcVoiceMode2VcPhyVoiceMode(
    APP_VC_VOICE_MODE_ENUM_U16          usVoiceMode
)
{
    switch(usVoiceMode)
    {
        case APP_VC_VOICE_MODE_PCVOICE:
            return VC_PHY_DEVICE_MODE_PCVOICE;

        case APP_VC_VOICE_MODE_EARPHONE:
            return VC_PHY_DEVICE_MODE_EARPHONE;

        case APP_VC_VOICE_MODE_HANDSET:
            return VC_PHY_DEVICE_MODE_HANDSET;

        case APP_VC_VOICE_MODE_HANDS_FREE:
            return VC_PHY_DEVICE_MODE_HANDS_FREE;

        default:
            AT_WARN_LOG1("APP_VC_AppVcVoiceMode2VcPhyVoiceMode: wrong usVoiceMode ", usVoiceMode);
            return VC_PHY_DEVICE_MODE_BUTT;
    }

}

/*****************************************************************************
?? ?? ??  : APP_VC_VcPhyVoiceMode2AppVcVoiceMode
????????  : VC????????????????????????????????????????VC????????????????
????????  : VC_PHY_DEVICE_MODE_ENUM_U16  usVoiceMode - VC????????????????????
????????  : ??
?? ?? ??  : APP_VC_VOICE_MODE_ENUM_U16 - ??????VC????????????????
????????  :
????????  :
????????  :
1.  ??    ??   : 2021??04??17??
    ??    ??   : o00132663
    ????????   : Creat
2.  ??    ??   : 2011??10??06??
    ??    ??   : f00179208
    ????????   : AT????????, ??????????C????????A??
*****************************************************************************/
APP_VC_VOICE_MODE_ENUM_U16  APP_VC_VcPhyVoiceMode2AppVcVoiceMode(
    VC_PHY_DEVICE_MODE_ENUM_U16         usVoiceMode
)
{
    switch(usVoiceMode)
    {
        case VC_PHY_DEVICE_MODE_PCVOICE:
            return APP_VC_VOICE_MODE_PCVOICE;

        case VC_PHY_DEVICE_MODE_EARPHONE:
            return APP_VC_VOICE_MODE_EARPHONE;

        case VC_PHY_DEVICE_MODE_HANDSET:
            return APP_VC_VOICE_MODE_HANDSET;

        case VC_PHY_DEVICE_MODE_HANDS_FREE:
            return APP_VC_VOICE_MODE_HANDS_FREE;

        default:
            AT_WARN_LOG1("APP_VC_VcPhyVoiceMode2AppVcVoiceMode: wrong usVoiceMode ", usVoiceMode);
            return APP_VC_VOICE_MODE_BUTT;
    }

}

/*****************************************************************************
 ?? ?? ??  : APP_VC_GetVoiceVolume
 ????????  : ????????????
 ????????  : MN_CLIENT_ID_T                      ClientId
             MN_OPERATION_ID_T                   OpId
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2012??5??10??
    ??    ??   : l60609
    ????????   : ??????????
  2.??    ??   : 2012??12??21??
    ??    ??   : l00227485
    ????????   : DSDA PhaseII
*****************************************************************************/
VOS_UINT32  APP_VC_GetVoiceVolume(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId
)
{
    /*??????????????????VC????*/
    VOS_UINT32                          ulRslt;
    APP_VC_REQ_MSG_STRU                *pstMsg;

    /* ???????? */
    pstMsg = (APP_VC_REQ_MSG_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT,
                  sizeof(APP_VC_REQ_MSG_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_ERR_LOG("APP_VC_GetVoiceVolume: ALLOC MSG FAIL.");
        return VOS_ERR;
    }

    pstMsg->clientId                    = ClientId;
    pstMsg->opId                        = OpId;
    pstMsg->enMsgName                   = APP_VC_MSG_REQ_QRY_VOLUME;
    pstMsg->ulSenderPid                 = WUEPS_PID_AT;
    pstMsg->ulReceiverPid               = AT_GetDestPid(ClientId, I0_WUEPS_PID_VC);
    pstMsg->aucContent[0]               = 0;
    pstMsg->aucContent[1]               = 0;
    pstMsg->aucContent[2]               = 0;
    pstMsg->aucContent[3]               = 0;

    ulRslt = PS_SEND_MSG(WUEPS_PID_AT, pstMsg);
    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("APP_VC_GetVoiceVolume: SEND MSG FAIL.");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 ?? ?? ??  : APP_VC_GetMuteStatus
 ????????  : ????????????
 ????????  : usClientId   - ??????ID
             ucOpId       - ??????ID
             enMuteStatus - ????????
 ????????  : ??
 ?? ?? ??  : VOS_OK       - ????
             VOS_ERR      - ????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2012??9??12??
    ??    ??   : A00165503
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 APP_VC_SetMuteStatus(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    APP_VC_MUTE_STATUS_ENUM_UINT8       enMuteStatus
)
{
    VOS_UINT32                          ulRslt;
    APP_VC_REQ_MSG_STRU                *pstMsg;

    /* ???????? */
    pstMsg = (APP_VC_REQ_MSG_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                        WUEPS_PID_AT,
                                        sizeof(APP_VC_REQ_MSG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_ERR_LOG("APP_VC_SetMuteStatus: ALLOC MSG FAIL.");
        return VOS_ERR;
    }

    /* ?????????? */
    PS_MEM_SET((VOS_CHAR *)pstMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               (VOS_SIZE_T)(sizeof(APP_VC_REQ_MSG_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ?????????? */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = AT_GetDestPid(usClientId, I0_WUEPS_PID_VC);
    pstMsg->enMsgName       = APP_VC_MSG_SET_MUTE_STATUS_REQ;

    /* ???????????? */
    pstMsg->clientId        = usClientId;
    pstMsg->opId            = ucOpId;
    pstMsg->aucContent[0]   = enMuteStatus;

    /* ???????? */
    ulRslt = PS_SEND_MSG(WUEPS_PID_AT, pstMsg);
    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("APP_VC_SetMuteStatus: SEND MSG FAIL.");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 ?? ?? ??  : APP_VC_SetMuteStatus
 ????????  : ????????????
 ????????  : usClientId   - ??????ID
             ucOpId       - ??????ID
             enMuteStatus - ????????
 ????????  : ??
 ?? ?? ??  : VOS_OK       - ????
             VOS_ERR      - ????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2012??9??12??
    ??    ??   : A00165503
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 APP_VC_GetMuteStatus(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    VOS_UINT32                          ulRslt;
    APP_VC_REQ_MSG_STRU                *pstMsg;

    /* ???????? */
    pstMsg = (APP_VC_REQ_MSG_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                        WUEPS_PID_AT,
                                        sizeof(APP_VC_REQ_MSG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_ERR_LOG("APP_VC_SetMuteStatus: ALLOC MSG FAIL.");
        return VOS_ERR;
    }

    /* ?????????? */
    PS_MEM_SET((VOS_CHAR *)pstMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               (VOS_SIZE_T)(sizeof(APP_VC_REQ_MSG_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ?????????? */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = AT_GetDestPid(usClientId, I0_WUEPS_PID_VC);
    pstMsg->enMsgName       = APP_VC_MSG_GET_MUTE_STATUS_REQ;

    /* ???????????? */
    pstMsg->clientId        = usClientId;
    pstMsg->opId            = ucOpId;

    /* ???????? */
    ulRslt = PS_SEND_MSG(WUEPS_PID_AT, pstMsg);
    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("APP_VC_SetMuteStatus: SEND MSG FAIL.");
        return VOS_ERR;
    }

    return VOS_OK;
}

/* Added by L47619 for VOICE_LOOP, 2013/07/05, begin */
/*****************************************************************************
 ?? ?? ??  : APP_VC_SetModemLoop
 ????????  : ??????????????????????
 ????????  : usClientId   - ??????ID
             ucOpId       - ??????ID
             ucModemLoop  - ??????????????????????
 ????????  : ??
 ?? ?? ??  : VOS_OK       - ????
             VOS_ERR      - ????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2013??7??8??
    ??    ??   : L47619
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 APP_VC_SetModemLoop(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucModemLoop
)
{
    VOS_UINT32                          ulRslt;
    APP_VC_REQ_MSG_STRU                *pstMsg;

    /* ???????? */
    pstMsg = (APP_VC_REQ_MSG_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                        WUEPS_PID_AT,
                                        sizeof(APP_VC_REQ_MSG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_ERR_LOG("APP_VC_SetModemLoop: ALLOC MSG FAIL.");
        return VOS_ERR;
    }

    /* ?????????? */
    PS_MEM_SET((VOS_CHAR *)pstMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               (VOS_SIZE_T)(sizeof(APP_VC_REQ_MSG_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ?????????? */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = AT_GetDestPid(usClientId, I0_WUEPS_PID_VC);
    pstMsg->enMsgName       = APP_VC_MSG_SET_MODEMLOOP_REQ;

    /* ???????????? */
    pstMsg->clientId        = usClientId;
    pstMsg->opId            = ucOpId;
    pstMsg->aucContent[0]   = ucModemLoop;

    /* ???????? */
    ulRslt = PS_SEND_MSG(WUEPS_PID_AT, pstMsg);
    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("APP_VC_SetModemLoop: SEND MSG FAIL.");
        return VOS_ERR;
    }

    return VOS_OK;
}
/* Added by L47619 for VOICE_LOOP, 2013/07/05, end */


