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


#ifndef __ATEVENTREPORT_H__
#define __ATEVENTREPORT_H__


/*****************************************************************************
  1 ??????????????
*****************************************************************************/
#include "vos.h"
#include "TafApsApi.h"
#include "siappstk.h"
#include "MnCallApi.h"
#include "AtParse.h"
#include "AtCtx.h"
#include "siapppb.h"

#include "TafAppCall.h"
#include "ATCmdProc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 ??????
*****************************************************************************/
#define AT_UNKNOWN_CLCK_CLASS  (0)


#define AT_GET_CURC_RPT_CTRL_STATUS_MAP_TBL_PTR()    (&g_aenAtCurcRptCmdTable[0])
#define AT_GET_CURC_RPT_CTRL_STATUS_MAP_TBL_SIZE()   (sizeof(g_aenAtCurcRptCmdTable)/sizeof(AT_RPT_CMD_INDEX_ENUM_UINT8))

/* Added by s00217060 for ????????AT??????????????C??, 2013-4-8, begin */
#define AT_GET_UNSOLICITED_RPT_CTRL_STATUS_MAP_TBL_PTR()    (&g_aenAtUnsolicitedRptCmdTable[0])
#define AT_GET_UNSOLICITED_RPT_CTRL_STATUS_MAP_TBL_SIZE()   (sizeof(g_aenAtUnsolicitedRptCmdTable)/sizeof(AT_RPT_CMD_INDEX_ENUM_UINT8))
/* Added by s00217060 for ????????AT??????????????C??, 2013-4-8, end */

#define AT_GET_CME_CALL_ERR_CODE_MAP_TBL_PTR()  (g_astAtCmeCallErrCodeMapTbl)
#define AT_GET_CME_CALL_ERR_CODE_MAP_TBL_SIZE() (sizeof(g_astAtCmeCallErrCodeMapTbl)/sizeof(AT_CME_CALL_ERR_CODE_MAP_STRU))

#define AT_GET_CMS_SMS_ERR_CODE_MAP_TBL_PTR()  (g_astAtCmsSmsErrCodeMapTbl)
#define AT_GET_CMS_SMS_ERR_CODE_MAP_TBL_SIZE() (sizeof(g_astAtCmsSmsErrCodeMapTbl)/sizeof(AT_CMS_SMS_ERR_CODE_MAP_STRU))


#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA)&&(FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT))
#define AT_GET_ENC_VOICE_ERR_CODE_MAP_TBL_PTR()  (g_astAtEncVoiceErrCodeMapTbl)
#define AT_GET_ENC_VOICE_ERR_CODE_MAP_TBL_SIZE() (sizeof(g_astAtEncVoiceErrCodeMapTbl)/sizeof(AT_ENCRYPT_VOICE_ERR_CODE_MAP_STRU))
#endif

#define AT_EVT_IS_VIDEO_CALL(enCallType)            \
           ((MN_CALL_TYPE_VIDEO_TX == enCallType)   \
         || (MN_CALL_TYPE_VIDEO_RX == enCallType)   \
         || (MN_CALL_TYPE_VIDEO    == enCallType))

#define AT_EVT_IS_CS_VIDEO_CALL(enCallType, enVoiceDomain)  \
           ((MN_CALL_TYPE_VIDEO         == enCallType)      \
         && (TAF_CALL_VOICE_DOMAIN_3GPP == enVoiceDomain))

#define AT_EVT_IS_PS_VIDEO_CALL(enCallType, enVoiceDomain)  \
           (((MN_CALL_TYPE_VIDEO        == enCallType)      \
          || (MN_CALL_TYPE_VIDEO_TX     == enCallType)      \
          || (MN_CALL_TYPE_VIDEO_RX     == enCallType))     \
         && (TAF_CALL_VOICE_DOMAIN_IMS  == enVoiceDomain))

#define AT_EVT_REL_IS_NEED_CLR_TIMER_STATUS_CMD(CmdCurrentOpt)  \
           ((AT_CMD_D_CS_VOICE_CALL_SET == CmdCurrentOpt)       \
         || (AT_CMD_D_CS_DATA_CALL_SET  == CmdCurrentOpt)       \
         || (AT_CMD_APDS_SET            == CmdCurrentOpt)       \
         || (AT_CMD_CHLD_EX_SET         == CmdCurrentOpt)       \
         || (AT_CMD_A_SET               == CmdCurrentOpt)       \
         || (AT_CMD_END_SET             == CmdCurrentOpt))

/*****************************************************************************
  3 ????????
*****************************************************************************/
/*****************************************************************************
 ??????    : AT_CS_CALL_STATE_ENUM
 ????????  : CS??????????????

  1.??    ??   : 2012??09??18??
    ??    ??   : l00198894
    ????????   : STK??????????DCM????????????????????

*****************************************************************************/
enum AT_CS_CALL_STATE_ENUM
{
    AT_CS_CALL_STATE_ORIG               = 0,                                    /* originate a MO Call */
    AT_CS_CALL_STATE_CALL_PROC,                                                 /* Call is Proceeding */
    AT_CS_CALL_STATE_ALERTING,                                                  /* Alerting,MO Call */
    AT_CS_CALL_STATE_CONNECT,                                                   /* Call Connect */
    AT_CS_CALL_STATE_RELEASED,                                                  /* Call Released */
    AT_CS_CALL_STATE_INCOMMING,                                                 /* Incoming Call */
    AT_CS_CALL_STATE_WAITING,                                                   /* Waiting Call */
    AT_CS_CALL_STATE_HOLD,                                                      /* Hold Call */
    AT_CS_CALL_STATE_RETRIEVE,                                                  /* Call Retrieved */

    AT_CS_CALL_STATE_BUTT
};
typedef VOS_UINT8 AT_CS_CALL_STATE_ENUM_UINT8;

/* Added by n00269697 for V3R3C60_eCall????, 2014-3-29, begin */
enum AT_ECALL_TYPE_ENUM
{
    AT_ECALL_TYPE_TEST                  = 0,                                    /* test ecall */
    AT_ECALL_TYPE_RECFGURATION,                                                 /* reconfiguration call */
    AT_ECALL_TYPE_MIEC,                                                         /* manually initiated ecall */
    AT_ECALL_TYPE_AIEC,                                                         /* automatic initiated ecall */

    AT_ECALL_TYPE_BUTT
};
typedef VOS_UINT8  AT_ECALL_TYPE_ENUM_U8;
/* Added by n00269697 for V3R3C60_eCall????, 2014-3-29, end */

/*****************************************************************************
  4 ????????????
*****************************************************************************/
extern VOS_UINT32                       g_ulAtAppDialModeCnf;

extern VOS_UINT32                       g_ulLcStartTime;


/*****************************************************************************
  5 ??????????
*****************************************************************************/


/*****************************************************************************
  6 ????????
*****************************************************************************/


/*****************************************************************************
  7 STRUCT????
*****************************************************************************/
typedef TAF_VOID (*AT_SMS_RSP_PROC_FUN)(
    TAF_UINT8                           ucIndex,
    MN_MSG_EVENT_INFO_STRU              *pstEvent
);

typedef TAF_VOID (*AT_QRY_PARA_PROC_FUNC)(TAF_UINT8   ucIndex,
                                          TAF_UINT8   OpId,
                                          TAF_VOID    *pPara);

/*lint -e958 -e959 ??????:l60609;????:64bit*/
typedef struct
{
    VOS_UINT32                          QueryType;                              /* ???????? */
    AT_QRY_PARA_PROC_FUNC               AtQryParaProcFunc;                      /* ?????????????????????? */
}AT_QUERY_TYPE_FUNC_STRU;
/*lint +e958 +e959 ??????:l60609;????:64bit*/

/* Added by f62575 for V9R1 STK????, 2013-6-26, begin */
/*****************************************************************************
 ??????  : AT_SMS_ERROR_CODE_MAP_STRU
 ????????: ????????????????????????????????AT??????????????????

 ????????      :
  1.??    ??   : 2012??9??25??
    ??    ??   : A00165503
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_MSG_ERROR_ENUM_UINT32           enMsgErrorCode;
    AT_RRETURN_CODE_ENUM_UINT32         enAtErrorCode;
}AT_SMS_ERROR_CODE_MAP_STRU;
/* Added by f62575 for V9R1 STK????, 2013-6-26, end */

/*****************************************************************************
 ??????  : AT_CME_CALL_ERR_CODE_MAP_STRU
 ????????: CS??????????CME??????????????

 ????????      :
  1.??    ??   : 2012??9??25??
    ??    ??   : A00165503
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCmeCode;
    TAF_CS_CAUSE_ENUM_UINT32            enCsCause;

} AT_CME_CALL_ERR_CODE_MAP_STRU;

/*****************************************************************************
 ??????  : AT_CMS_SMS_ERR_CODE_MAP_STRU
 ????????: SMS??????????CMS??????????????

 ????????      :
  1.??    ??   : 2013??5??17??
    ??    ??   : w00176964
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCmsCode;
    VOS_UINT32                          ulSmsCause;

} AT_CMS_SMS_ERR_CODE_MAP_STRU;


#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA)&&(FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT))
/*****************************************************************************
 ??????  : AT_ENCRYPT_VOICE_ERR_CODE_MAP_STRU
 ????????: ??????????????????

 ????????      :
  1.??    ??   : 2013??5??17??
    ??    ??   : w00176964
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    AT_ENCRYPT_VOICE_ERROR_ENUM_UINT32                      enAtEncErr;
    TAF_CALL_APP_ENCRYPT_VOICE_TYPE_ENUM_UINT32             enTafEncErr;

} AT_ENCRYPT_VOICE_ERR_CODE_MAP_STRU;
#endif

/*****************************************************************************
  8 UNION????
*****************************************************************************/


/*****************************************************************************
  9 OTHERS????
*****************************************************************************/


/*****************************************************************************
  10 ????????
*****************************************************************************/
extern TAF_UINT32 At_ChangeSTKCmdNo(TAF_UINT32 ulCmdType, TAF_UINT8 *ucCmdNo );

VOS_VOID AT_CsUus1InfoEvtIndProc(
    VOS_UINT8                           ucIndex,
    MN_CALL_EVENT_ENUM_U32              enEvent,
    MN_CALL_INFO_STRU                   *pstCallInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_LogPrintMsgProc
 ????????  : LOG????????????
 ????????  : pstMsg --- ????????
 ????????  : ??
 ?? ?? ??  : VOS_VOID
*****************************************************************************/
VOS_VOID AT_LogPrintMsgProc(TAF_MNTN_LOG_PRINT_STRU *pstMsg);


/*****************************************************************************
 ?? ?? ??  : AT_CsClccInfoEvtIndProc
 ????????  : ????CALL??????CLCC??????????
 ????????  : ??
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??10??08??
    ??    ??   : f00179208
    ????????   : ??????????

*****************************************************************************/
VOS_VOID At_CsAllCallInfoEvtCnfProc(
    MN_AT_IND_EVT_STRU *pstData,
    TAF_UINT16 usLen
);


/*****************************************************************************
 ?? ?? ??  : AT_MnPsEvtProc
 ????????  : PS??????????????
 ????????  : pstEvt                     - PS??????
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :
*****************************************************************************/
VOS_VOID AT_RcvTafPsEvt(
    TAF_PS_EVT_STRU                     *pstEvt
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsCallEvtPdpErrorInd
 ????????  :
 ????????  : pEvtInfo                   - ????????(??????EvtId)
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsCallEvtPdpErrorInd(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsCallEvtPdpActivateCnf
 ????????  :
 ????????  : pEvtInfo                   - ????????(??????EvtId)
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsCallEvtPdpActivateCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsCallEvtPdpActivateRej
 ????????  :
 ????????  : pEvtInfo                   - ????????(??????EvtId)
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsCallEvtPdpActivateRej(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsCallEvtPdpManageInd
 ????????  :
 ????????  : VOS_VOID                           *pEvtInfo
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsCallEvtPdpManageInd(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsCallEvtPdpActivateInd
 ????????  :
 ????????  : VOS_VOID                           *pEvtInfo
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsCallEvtPdpActivateInd(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsEvtPdpModifyCnf
 ????????  :
 ????????  : VOS_VOID                           *pEvtInfo
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsCallEvtPdpModifyCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsCallEvtPdpModifyRej
 ????????  :
 ????????  : VOS_VOID                           *pEvtInfo
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsCallEvtPdpModifyRej(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsCallEvtPdpModifiedInd
 ????????  :
 ????????  : VOS_VOID                           *pEvtInfo
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsCallEvtPdpModifiedInd(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsCallEvtPdpDeactivateCnf
 ????????  :
 ????????  : VOS_VOID                           *pEvtInfo
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsCallEvtPdpDeactivateCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsCallEvtPdpDeactivatedInd
 ????????  :
 ????????  : VOS_VOID                           *pEvtInfo
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsCallEvtPdpDeactivatedInd(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/* Deleted by Y00213812 for VoLTE_PhaseI ????, 2013-07-08, begin */
/* Deleted by Y00213812 for VoLTE_PhaseI ????, 2013-07-08, end */

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsCallEvtCallOrigCnf
 ????????  :
 ????????  : VOS_VOID                           *pEvtInfo
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsCallEvtCallOrigCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsCallEvtCallEndCnf
 ????????  :
 ????????  : VOS_VOID                           *pEvtInfo
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsCallEvtCallEndCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsCallEvtCallEndCnf
 ????????  :
 ????????  : VOS_VOID                           *pEvtInfo
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsCallEvtCallModifyCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsCallEvtCallAnswerCnf
 ????????  :
 ????????  : VOS_VOID                           *pEvtInfo
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsCallEvtCallAnswerCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsCallEvtCallHangupCnf
 ????????  :
 ????????  : VOS_VOID                           *pEvtInfo
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsCallEvtCallHangupCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsEvtSetPrimPdpContextInfoCnf
 ????????  :
 ????????  : VOS_VOID                           *pEvtInfo
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtSetPrimPdpContextInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsEvtGetPrimPdpContextInfoCnf
 ????????  :
 ????????  : VOS_VOID                           *pEvtInfo
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtGetPrimPdpContextInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);


/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsEvtSetSecPdpContextInfoCnf
 ????????  :
 ????????  : VOS_VOID                           *pEvtInfo
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtSetSecPdpContextInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsEvtGetSecPdpContextInfoCnf
 ????????  :
 ????????  : VOS_VOID                           *pEvtInfo
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtGetSecPdpContextInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvPsSetPdpTftInfoCnf
 ????????  :
 ????????  : VOS_VOID                           *pEvtInfo
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtSetTftInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsEvtGetTftInfoCnf
 ????????  :
 ????????  : VOS_VOID                           *pEvtInfo
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtGetTftInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsEvtSetUmtsQosInfoCnf
 ????????  :
 ????????  : VOS_VOID                           *pEvtInfo
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtSetUmtsQosInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsEvtGetUmtsQosInfoCnf
 ????????  :
 ????????  : VOS_VOID                           *pEvtInfo
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtGetUmtsQosInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsEvtSetUmtsQosMinInfoCnf
 ????????  :
 ????????  : VOS_VOID                           *pEvtInfo
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtSetUmtsQosMinInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsEvtGetUmtsQosMinInfoCnf
 ????????  :
 ????????  : VOS_VOID                           *pEvtInfo
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtGetUmtsQosMinInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsEvtGetDynamicUmtsQosInfoCnf
 ????????  :
 ????????  : VOS_VOID                           *pEvtInfo
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtGetDynamicUmtsQosInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsEvtSetPdpStateCnf
 ????????  :
 ????????  : VOS_VOID                           *pEvtInfo
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtSetPdpStateCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsEvtCgactQryCnf
 ????????  : Cgact????????????
 ????????  : pEvtInfo                   - ????????, MN_PS_EVT_STRU????EvtId
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtCgactQryCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsEvtCgeqnegTestCnf
 ????????  : Cgeqneg????????????
 ????????  : pEvtInfo - ????????, MN_PS_EVT_STRU????EvtId
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :
*****************************************************************************/

VOS_UINT32 AT_RcvTafPsEvtCgeqnegTestCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsEvtGetPdpStateCnf
 ????????  :
 ????????  : VOS_VOID                           *pEvtInfo
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtGetPdpStateCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsEvtGetPdpIpAddrInfoCnf
 ????????  :
 ????????  : VOS_VOID                           *pEvtInfo
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtGetPdpIpAddrInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsEvtGetPdpContextInfoCnf
 ????????  :
 ????????  : VOS_VOID                           *pEvtInfo
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtGetPdpContextInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsEvtSetAnsModeInfoCnf
 ????????  :
 ????????  : VOS_VOID                           *pEvtInfo
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtSetAnsModeInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsEvtGetAnsModeInfoCnf
 ????????  :
 ????????  : VOS_VOID                           *pEvtInfo
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtGetAnsModeInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsEvtGetDynamicPrimPdpContextInfoCnf
 ????????  :
 ????????  : VOS_VOID                           *pEvtInfo
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtGetDynamicPrimPdpContextInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsEvtGetDynamicSecPdpContextInfoCnf
 ????????  :
 ????????  : VOS_VOID                           *pEvtInfo
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtGetDynamicSecPdpContextInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsEvtGetDynamicTftInfoCnf
 ????????  :
 ????????  : VOS_VOID                           *pEvtInfo
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtGetDynamicTftInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsEvtSetEpsQosInfoCnf
 ????????  :
 ????????  : VOS_VOID                           *pEvtInfo
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtSetEpsQosInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsEvtGetEpsQosInfoCnf
 ????????  :
 ????????  : VOS_VOID                           *pEvtInfo
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtGetEpsQosInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsEvtGetDynamicEpsQosInfoCnf
 ????????  :
 ????????  : VOS_VOID                           *pEvtInfo
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtGetDynamicEpsQosInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsEvtGetDsFlowInfoCnf
 ????????  :
 ????????  : VOS_VOID                           *pEvtInfo
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtGetDsFlowInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsEvtClearDsFlowInfoCnf
 ????????  :
 ????????  : VOS_VOID                           *pEvtInfo
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtClearDsFlowInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsEvtConfigDsFlowRptCnf
 ????????  :
 ????????  : VOS_VOID                           *pEvtInfo
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtConfigDsFlowRptCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsEvtReportDsFlowInd
 ????????  :
 ????????  : VOS_VOID                           *pEvtInfo
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtReportDsFlowInd(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

VOS_UINT32 AT_RcvTafPsEvtSetApDsFlowRptCfgCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

VOS_UINT32 AT_RcvTafPsEvtGetApDsFlowRptCfgCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

VOS_UINT32 AT_RcvTafPsEvtApDsFlowReportInd(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

VOS_UINT32 AT_RcvTafPsEvtSetDsFlowNvWriteCfgCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

VOS_UINT32 AT_RcvTafPsEvtGetDsFlowNvWriteCfgCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsEvtSetPdpDnsInfoCnf
 ????????  :
 ????????  : VOS_VOID                           *pEvtInfo
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtSetPdpDnsInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsEvtGetPdpDnsInfoCnf
 ????????  :
 ????????  : VOS_VOID                           *pEvtInfo
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtGetPdpDnsInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsEvtSetAuthDataInfoCnf
 ????????  :
 ????????  : VOS_VOID                           *pEvtInfo
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtSetAuthDataInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsEvtGetAuthDataInfoCnf
 ????????  :
 ????????  : VOS_VOID                           *pEvtInfo
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtGetAuthDataInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsEvtGetGprsActiveTypeCnf
 ????????  : ID_EVT_TAF_PS_GET_D_GPRS_ACTIVE_TYPE_CNF????????????, ????PPP????
 ????????  : pEvtInfo                   - ????????, MN_PS_EVT_STRU????EvtId
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtGetGprsActiveTypeCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsEvtPppDialOrigCnf
 ????????  : ID_EVT_TAF_PS_PPP_DIAL_ORIG_CNF????????????, ????PPP????
 ????????  : pEvtInfo                   - ????????, MN_PS_EVT_STRU????EvtId
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtPppDialOrigCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

VOS_UINT32 AT_RcvTafPsEvtSetCqosPriCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

VOS_UINT32 At_RcvTafPsEvtSetDialModeCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

VOS_UINT32 AT_RcvTafPsEvtGetCgmtuValueCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

VOS_UINT32 AT_RcvTafPsEvtCgmtuValueChgInd(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);
#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsEvtReportDsFlowInd
 ????????  : ID_EVT_TAF_PS_IPV6_INFO_IND????????????, ????????IPV6??RA????
 ????????  : pEvtInfo                   - ????????,
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtReportRaInfo(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);
#endif

/* Added by l60609 for PS Project,2012-12-21,Begin */
VOS_UINT32 AT_RcvTafPsEvtPdpDisconnectInd(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);
/* Added by l60609 for PS Project,2012-12-21,End */

VOS_VOID AT_QryParaRspCeregProc(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           ucOpId,
    VOS_VOID                           *pPara
);

VOS_UINT32 AT_RcvTafPsEvtGetDynamicDnsInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);


/* Deleted by l00198894 for V9R1 STK????, 2013/07/11 */

TAF_VOID  At_StkCsinIndPrint(TAF_UINT8 ucIndex,SI_STK_EVENT_INFO_STRU *pEvent);

/* Add by w00199382 for V7????????, 2012-04-07, Begin   */
#if (FEATURE_ON==FEATURE_LTE)
VOS_UINT32 atReadLtecsCnfProc(VOS_UINT8   ucIndex,VOS_VOID    *pEvtInfo);

VOS_UINT32 atReadCemodeCnfProc(VOS_UINT8   ucIndex,VOS_VOID    *pEvtInfo);

VOS_UINT32 AT_RcvTafPsEvtSetPdprofInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);
#endif

/* Add by w00199382 for V7????????, 2012-04-07, End   */

VOS_VOID At_RcvMnCallEccNumIndProc(
    MN_AT_IND_EVT_STRU                 *pstData,
    VOS_UINT16                          usLen
);


VOS_VOID AT_ConvertNasMccToBcdType(
    VOS_UINT32                          ulNasMcc,
    VOS_UINT32                         *pulMcc
);


/* Added by L60609 for V7R1C50 AT&T&DCM, 2012-6-19, begin */
VOS_VOID AT_RcvMmaNsmStatusInd(
    TAF_UINT8                           ucIndex,
    TAF_PHONE_EVENT_INFO_STRU          *pEvent
);
/* Added by L60609 for V7R1C50 AT&T&DCM, 2012-6-19, end */

/* Modified by l60609 for DSDA Phase III, 2013-3-5, Begin */
VOS_UINT32 AT_CheckRptCmdStatus(
    VOS_UINT8                          *pucRptCfg,
    AT_CMD_RPT_CTRL_TYPE_ENUM_UINT8     enRptCtrlType,
    AT_RPT_CMD_INDEX_ENUM_UINT8         enRptCmdIndex
);
/* Modified by l60609 for DSDA Phase III, 2013-3-5, End */

VOS_VOID AT_ReportCCallstateResult(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    VOS_UINT8                          *pucRptCfg,
    AT_CS_CALL_STATE_ENUM_UINT8         enCallState,
    TAF_CALL_VOICE_DOMAIN_ENUM_UINT8    enVoiceDomain
);

/* Modified by s00217060 for ????????AT??????????????C??, 2013-4-17, begin */
VOS_VOID AT_ReportCCallstateHoldList(
    MN_CALL_EVT_HOLD_STRU              *pstHoldEvt,
    AT_CS_CALL_STATE_ENUM_UINT8         enCallState
);
VOS_VOID AT_ReportCCallstateRetrieveList(
    MN_CALL_EVT_RETRIEVE_STRU          *pstRetrieveEvt,
    AT_CS_CALL_STATE_ENUM_UINT8         enCallState
);
/* Modified by s00217060 for ????????AT??????????????C??, 2013-4-17, end */


VOS_VOID AT_ReportCendResult(
    VOS_UINT8                           ucIndex,
    MN_CALL_INFO_STRU                  *pstCallInfo );

VOS_VOID AT_CSCallStateReportProc(
    MN_AT_IND_EVT_STRU                 *pstData );

VOS_VOID At_SetClprCnf(MN_AT_IND_EVT_STRU *pstData);


VOS_VOID  At_StkCcinIndPrint(TAF_UINT8 ucIndex, SI_STK_EVENT_INFO_STRU *pstEvent);

VOS_VOID At_StkHvsmrIndPrint(VOS_UINT8 ucIndex, SI_STK_EVENT_INFO_STRU *pstEvent);

VOS_VOID AT_RcvMmaRssiChangeInd(
    TAF_UINT8                           ucIndex,
    TAF_MMA_RSSI_INFO_IND_STRU         *pstRssiInfoInd
);

/* Deleted by l00198894 for V9R1 STK????, 2013/07/11 */

/* Added by w00176964 for V7R1C50_DCM????????????????????, 2012-12-11, begin */

/* Added by k902809 for Iteration 11, 2015-3-26, begin */
VOS_VOID AT_PhNetScanReportSuccess(
    VOS_UINT8                           ucIndex,
    TAF_MMA_NET_SCAN_CNF_STRU          *pstNetScanCnf
);
VOS_VOID AT_PhNetScanReportFailure(
    VOS_UINT8                           ucIndex,
    TAF_MMA_NET_SCAN_CAUSE_ENUM_UINT8   enNetScanCause
);

TAF_UINT32 AT_ProcOperModeWhenLteOn(VOS_UINT8 ucIndex);

/* Added by l00171473 for DTS2013010800120 ????????????????, 2013-1-5, begin */

VOS_VOID AT_RcvMnCallChannelInfoInd(VOS_VOID *pEvtInfo);

/* Added by l00171473 for DTS2013010800120 ????????????????, 2013-1-5, end */

/* Deleted by k902809 for Iteration 11, 2015-3-30, begin */

/* Deleted by k902809 for Iteration 11, Iteration 11 2015-3-30, end */

/*****************************************************************************
 ?? ?? ??  : At_RcvXlemaQryCnf
 ????????  : ????CALL????????????????????
 ????????  : MN_AT_IND_EVT_STRU   pstData
             VOS_UINT16           usLen
 ????????  : ??
 ?? ?? ??  : VOS_VOID
*****************************************************************************/
VOS_VOID At_RcvXlemaQryCnf(
    MN_AT_IND_EVT_STRU                 *pstData,
    VOS_UINT16                          usLen
);

/*****************************************************************************
 ?? ?? ??  : AT_GetSsEventErrorCode
 ????????  : ??SS Event??????AT??????????
 ????????  : VOS_UINT8                           ucIndex -- AT??????????
             TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pEvent  -- SS Event????
 ????????  : ??
 ?? ?? ??  : AT_RRETURN_CODE_ENUM_UINT32   -- AT??????????
*****************************************************************************/
VOS_UINT32 AT_GetSsEventErrorCode(
    VOS_UINT8                           ucIndex,
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pEvent);

/* Deleted by k902809 for Iteration 11, 2015-3-27, begin */

/* Deleted by k902809 for Iteration 11, Iteration 11 2015-3-27, end */

VOS_UINT32 At_QryParaPlmnListProc(
    VOS_VOID                           *pMsg
);

#if (FEATURE_ON == FEATURE_CSG)
VOS_UINT32 AT_RcvMmaCsgListSearchCnfProc(
    VOS_VOID                           *pMsg
);

VOS_UINT32 AT_RcvMmaCsgListAbortCnf(
    VOS_VOID                           *pMsg
);

VOS_UINT32 AT_RcvMmaCsgSpecSearchCnfProc(
    VOS_VOID                           *pstMsg
);
VOS_UINT32 AT_RcvMmaQryCampCsgIdInfoCnfProc(
    VOS_VOID                           *pstMsg
);

#endif

extern TAF_UINT8 At_GetClckClassFromBsCode(TAF_SS_BASIC_SERVICE_STRU *pstBs);

/* Added by l00198894 for V9R1 STK????, 2013/07/11, begin */
VOS_VOID AT_RcvTafCallStartDtmfCnf(
    MN_AT_IND_EVT_STRU                 *pstData
);

VOS_VOID AT_RcvTafCallStopDtmfCnf(
    MN_AT_IND_EVT_STRU                 *pstData
);

VOS_VOID AT_RcvTafCallStartDtmfRslt(
    MN_AT_IND_EVT_STRU                 *pstData
);

VOS_VOID AT_RcvTafCallStopDtmfRslt(
    MN_AT_IND_EVT_STRU                 *pstData
);
/* Added by l00198894 for V9R1 STK????, 2013/07/11, end */

/* Added by x65241 for ACC&SPLMN, 2013-10-15 Begin */
VOS_VOID AT_PhEOPlmnQueryCnfProc(TAF_UINT8 *pData);
/* Deleted by k902809 for Iteration 11, 2015-3-24, begin */

/* Deleted by k902809 for Iteration 11, Iteration 11 2015-3-24, end */
/* Added by x65241 for ACC&SPLMN, 2013-10-15 End */

extern VOS_VOID AtBase64Encode(const VOS_VOID* pdata,const VOS_UINT32 data_size,VOS_VOID* out_pcode);

VOS_VOID AT_FlushSmsIndication(VOS_VOID);
VOS_UINT32  AT_IsClientBlock(VOS_VOID);


/* Added by s00217060 for VoLTE_PhaseI  ????, 2013-07-09, begin */
VOS_VOID At_RcvTafCallOrigCnf(
    MN_AT_IND_EVT_STRU                 *pstData,
    TAF_UINT16                          usLen
);
VOS_VOID At_RcvTafCallSupsCmdCnf(
    MN_AT_IND_EVT_STRU                 *pstData,
    TAF_UINT16                          usLen
);

/* Added by s00217060 for VoLTE_PhaseI  ????, 2013-07-09, end */

/* Added by Y00213812 for VoLTE_PhaseI ????, 2013-07-08, begin */
/*****************************************************************************
 ?? ?? ??  : AT_RcvTafPsEvtGetCidSdfInfoCnf
 ????????  : ID_MSG_TAF_GET_CID_SDF_CNF????????????
 ????????  : VOS_UINT8                  ucIndex,
             VOS_VOID                  *pEvtInfo       - ????????, MN_PS_EVT_STRU????EvtId
 ????????  : ??
 ?? ?? ??  : VOS_UINT32

*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtGetCidSdfInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);
/* Added by Y00213812 for VoLTE_PhaseI ????, 2013-07-08, end */

/* Added by s00217060 for VoLTE_PhaseI  ????, 2013-08-16, begin */
VOS_UINT32 AT_ConvertCallError(TAF_CS_CAUSE_ENUM_UINT32 enCause);
/* Added by s00217060 for VoLTE_PhaseI  ????, 2013-08-16, end */

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA)&&(FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT))
AT_ENCRYPT_VOICE_ERROR_ENUM_UINT32  AT_MapEncVoiceErr(
    TAF_CALL_APP_ENCRYPT_VOICE_STATUS_ENUM_UINT32           enTafEncVoiceErr
);
#endif

VOS_VOID At_ProcQryClccResult(
    VOS_UINT8                           ucNumOfCalls,
    MN_CALL_INFO_QRY_CNF_STRU          *pstCallInfos,
    VOS_UINT8                           ucIndex
);

#if (FEATURE_ON == FEATURE_IMS)
VOS_VOID At_RcvTafCallModifyCnf(
    MN_AT_IND_EVT_STRU                 *pstData,
    VOS_UINT16                          usLen
);
VOS_VOID At_RcvTafCallAnswerRemoteModifyCnf(
    MN_AT_IND_EVT_STRU                 *pstData,
    VOS_UINT16                          usLen
);
VOS_VOID At_RcvTafCallModifyStatusInd(
    MN_AT_IND_EVT_STRU                 *pstData,
    VOS_UINT16                          usLen
);

VOS_VOID AT_RcvTafEconfDialCnf(
    MN_AT_IND_EVT_STRU                 *pstData,
    VOS_UINT16                          usLen
);

VOS_VOID AT_RcvTafEconfNotifyInd(
    MN_AT_IND_EVT_STRU                 *pstData,
    VOS_UINT16                          usLen
);

VOS_VOID AT_RcvTafGetEconfInfoCnf(
    MN_AT_IND_EVT_STRU                 *pstData,
    VOS_UINT16                          usLen
);

VOS_VOID AT_RcvTafCallCcwaiSetCnf(
    MN_AT_IND_EVT_STRU                 *pstData
);
#endif

#if (FEATURE_ON == FEATURE_ECALL)
/* Added by j00174725 for V3R3C60_eCall????, 2014-3-29, begin */
VOS_UINT32 At_ProcVcReportEcallStateEvent(
    VOS_UINT8                           ucIndex,
    APP_VC_EVENT_INFO_STRU             *pstVcEvtInfo
);

VOS_UINT32 At_ProcVcSetEcallCfgEvent(
    VOS_UINT8                           ucIndex,
    APP_VC_EVENT_INFO_STRU             *pstVcEvtInfo
);
/* Added by j00174725 for V3R3C60_eCall????, 2014-3-29, end */

/* Added by n00269697 for V3R3C60_eCall????, 2014-3-29, begin */
VOS_UINT32 At_RcvTafCallQryEcallInfoCnf(MN_AT_IND_EVT_STRU *pEvtInfo);
/* Added by n00269697 for V3R3C60_eCall????, 2014-3-29, end */
#endif

/* Added by n00269697 for V3R3C60_eCall????, 2014-3-29, begin */
VOS_VOID At_ChangeEcallTypeToCallType(
    MN_CALL_TYPE_ENUM_U8                enEcallType,
    MN_CALL_TYPE_ENUM_U8               *enCallType
);

PS_BOOL_ENUM_UINT8 At_CheckReportCendCallType(
    MN_CALL_TYPE_ENUM_U8                enCallType
);

PS_BOOL_ENUM_UINT8 At_CheckReportOrigCallType(
    MN_CALL_TYPE_ENUM_U8                enCallType
);

PS_BOOL_ENUM_UINT8 At_CheckReportConfCallType(
    MN_CALL_TYPE_ENUM_U8                enCallType
);

PS_BOOL_ENUM_UINT8 At_CheckUartRingTeCallType(
    MN_CALL_TYPE_ENUM_U8                enCallType
);
/* Added by n00269697 for V3R3C60_eCall????, 2014-3-29, end */

TAF_UINT32 At_HexText2AsciiStringSimple(
    TAF_UINT32                          MaxLength,
    TAF_INT8                           *headaddr,
    TAF_UINT8                          *pucDst,
    TAF_UINT32                          ulLen,
    TAF_UINT8                          *pucStr
);

PS_BOOL_ENUM_UINT8 At_CheckOrigCnfCallType(
    MN_CALL_INFO_STRU                  *pstCallInfo,
    VOS_UINT8                           ucIndex
);
VOS_UINT32 At_IsCmdCurrentOptSendedOrigReq(AT_CMD_CURRENT_OPT_ENUM CmdCurrentOpt);

VOS_VOID AT_PB_ReadContinueProc(VOS_UINT8 ucIndex);
VOS_VOID AT_PB_ReadRspProc(
    VOS_UINT8                           ucIndex,
    SI_PB_EVENT_INFO_STRU              *pstEvent
);

VOS_UINT32 AT_RcvTafPsEvtSetPktCdataInactivityTimeLenCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

VOS_UINT32 AT_RcvTafPsEvtGetPktCdataInactivityTimeLenCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);


VOS_VOID AT_ReportSysCfgQryCmdResult(
    TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfg,
    VOS_UINT8                           ucIndex,
    VOS_UINT16                         *pusLength
);

VOS_VOID AT_ReportSysCfgExQryCmdResult(
    TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfg,
    VOS_UINT8                           ucIndex,
    VOS_UINT16                         *pusLength
);

VOS_VOID AT_ProcRegStatusInfoInd(
    VOS_UINT8                           ucIndex,
    TAF_MMA_REG_STATUS_IND_STRU        *pstRegInfo
);

VOS_UINT32 AT_RcvTafPsEvtSetImsPdpCfgCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

VOS_UINT32 AT_RcvTafPsEvtSet1xDormTimerCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

VOS_UINT32 AT_RcvTafPsEvtGet1xDormTimerCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

VOS_UINT32 AT_RcvTafPsCallEvtPdpRabidChanged(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);


#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


#endif


