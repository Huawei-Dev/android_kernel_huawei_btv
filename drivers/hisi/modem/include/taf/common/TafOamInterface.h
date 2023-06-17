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

#ifndef __TAFOAMINTERFACE_H__
#define __TAFOAMINTERFACE_H__

/*****************************************************************************
  1 ??????????????
*****************************************************************************/
#include "v_msg.h"
#include "TafAppMma.h"
#include "MnMsgApi.h"
#include "MnClient.h"
#include "omnvinterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 ??????
*****************************************************************************/
#define SAR_ANTSTATE_IND                            0x1111

/* Added by s00217060 for ????????AT??????????????C??, 2013-3-25, begin */
#define TAF_STK_CURC_RPT_CFG_MAX_SIZE               (8)
/* Added by s00217060 for ????????AT??????????????C??, 2013-3-25, end */

#define    COMM_LOG_PORT_USB                CPM_OM_PORT_TYPE_USB
#define    COMM_LOG_PORT_VCOM               CPM_OM_PORT_TYPE_VCOM

/*****************************************************************************
  3 ????????
*****************************************************************************/


/*****************************************************************************
  4 ????????????
*****************************************************************************/


/*****************************************************************************
  5 ??????????
*****************************************************************************/
/*****************************************************************************
 ??????    : TAF_OAM_MSG_TYPE_ENUM
 ????????  : TAF??OAM??????????????????ID????32????????16??????
  1.??    ??   : 2013??6??26??
    ??    ??   : f62575
    ????????   : V9R1 STK??????????????????:
                 TAF_STK_ENVELOPE_CNF
                 TAF_STK_SYS_INFO_IND
                 TAF_STK_SERVICE_STATUS_IND
  2.??    ??   : 2013??7??24??
    ??    ??   : z00161729
    ????????   : V9R1 STK????????
*****************************************************************************/
enum TAF_OAM_MSG_TYPE_ENUM
{
    /* SPY/DIAG/OM -> MMA */
    OAM_MMA_PHONE_MODE_SET_REQ          = 0x00,                                 /* _H2ASN_MsgChoice MN_APP_PHONE_MODE_SET_REQ_STRU */
    OAM_MMA_PHONE_LOADDEFAULT_REQ       = 0x01,                                 /* _H2ASN_MsgChoice MN_APP_PHONE_LOADDEFAULT_REQ_STRU */

    /* Deleted by z00161729 for V9R1 STK????, 2013-7-24, begin */
    /* taf??stk????????????????NasStkInterface.h */
    /* Deleted by z00161729 for V9R1 STK????, 2013-7-24, end */

    /* TAF  -> OAM(VC) ????OAM???????????????????????? */
    TAF_OAM_SET_TRANS_PORT_REQ          = 0x0f,                                 /* _H2ASN_MsgChoice MN_APP_CS_SET_TRANS_PORT_MSG_STRU */

    /* Deleted by z00161729 for V9R1 STK????, 2013-7-24, begin */
    /* taf??stk????????????????NasStkInterface.h */
    /* Deleted by z00161729 for V9R1 STK????, 2013-7-24, end */

    /* PHONE -> SPY/DIAG/OM OAM_MMA_PHONE_MODE_SET_REQ?????????? */
    TAF_OAM_PHONE_EVENT_IND             = 0x11,                                 /* _H2ASN_MsgChoice MN_APP_PHONE_EVENT_INFO_STRU */

    /* PHONE -> SPY/DIAG/OM OAM_MMA_PHONE_LOADDEFAULT_REQ?????????? */
    TAF_OAM_PHONE_SET_CNF               = 0x12,                                 /* _H2ASN_MsgChoice MN_APP_PHONE_SET_CNF_STRU */

    TAF_STK_USSD_DCS_DECODE_HOOK        = 0xAAA0,                               /* _H2ASN_MsgChoice SSA_USSD_DCS_DECODE_HOOK_STRU */

    MMA_EVT_OM_SDT_CONNECTED_IND        = 0xAAAA,


    /* OAM->MMA, TRACE ???????? */
    OAM_MMA_TRACE_CONFIG_REQ            = 0xAAAB,

    MMA_OAM_TRACE_CONFIG_CNF,

    /* Modified by z00161729 for ????????AT??????????????C??, 2013-4-11, begin */
    TAF_OAM_UNSOLICITED_RPT_INFO_IND,                                       /* _H2ASN_MsgChoice TAF_OAM_UNSOLICITED_RPT_INFO_STRU */
    /* Modified by z00161729 for ????????AT??????????????C??, 2013-4-11, end */

    /* Added by s00217060 for VoLTE_PhaseI  ????, 2013-07-20, begin */
    /* VC  -> OAM ????VC???????????????????????????? */
    TAF_OAM_LOG_END_CALL_REQ,                                               /* _H2ASN_MsgChoice TAF_OAM_LOG_END_CALL_REQ_STRU */
    /* Added by s00217060 for VoLTE_PhaseI  ????, 2013-07-20, end */

    /* TAF  -> OAM ?????????????????????????????? */
    TAF_OAM_EMERGENCY_CALL_STATUS_NOTIFY    = 0xBBB0,                               /* _H2ASN_MsgChoice TAF_OAM_EMERGENCY_CALL_STATUS_STRU */

    TAF_OAM_MSG_TYPE_BUTT
};
typedef VOS_UINT32 TAF_OAM_MSG_TYPE_ENUM_UINT32;

/* Modified by z00161729 for ????????AT??????????????C??, 2013-5-2, begin */
/*****************************************************************************
 ??????    : TAF_STK_RPT_CMD_INDEX_ENUM
 ????????  : ????????????????

  1.??    ??   : 2013??05??02??
    ??    ??   : z00161729
    ????????   : ????
*****************************************************************************/
enum TAF_STK_RPT_CMD_INDEX_ENUM
{
    TAF_STK_RPT_CMD_MODE                     = 0,
    TAF_STK_RPT_CMD_RSSI,
    TAF_STK_RPT_CMD_SRVST,
    TAF_STK_RPT_CMD_SIMST,
    TAF_STK_RPT_CMD_TIME,
    TAF_STK_RPT_CMD_SMMEMFULL,
    TAF_STK_RPT_CMD_CTZV,
    TAF_STK_RPT_CMD_DSFLOWRPT,
    TAF_STK_RPT_CMD_ORIG,
    TAF_STK_RPT_CMD_CONF,
    TAF_STK_RPT_CMD_CONN,
    TAF_STK_RPT_CMD_CEND,
    TAF_STK_RPT_CMD_STIN,
    TAF_STK_RPT_CMD_CERSSI,
    TAF_STK_RPT_CMD_ANLEVEL,
    TAF_STK_RPT_CMD_LWCLASH,
    TAF_STK_RPT_CMD_XLEMA,
    TAF_STK_RPT_CMD_ACINFO,
    TAF_STK_RPT_CMD_PLMN,
    TAF_STK_RPT_CMD_CALLSTATE,
    TAF_STK_RPT_CMD_CREG,
    TAF_STK_RPT_CMD_CUSD,
    TAF_STK_RPT_CMD_CSSI,
    TAF_STK_RPT_CMD_CSSU,
    TAF_STK_RPT_CMD_LWURC,
    TAF_STK_RPT_CMD_CUUS1I,
    TAF_STK_RPT_CMD_CUUS1U,
    TAF_STK_RPT_CMD_CGREG,
    TAF_STK_RPT_CMD_CEREG,
    TAF_STK_RPT_CMD_BUTT
};
typedef VOS_UINT8 TAF_STK_RPT_CMD_INDEX_ENUM_UINT8;
/* Modified by z00161729 for ????????AT??????????????C??, 2013-5-2, end */


/*****************************************************************************
 ??????    : TAF_APS_USER_CONN_STATUS_ENUM
 ????????  : ????????????????PDP????
 1.??    ??   : 2012??03??13??
   ??    ??   : f00179208
   ????????   : ????
*****************************************************************************/
enum TAF_APS_USER_CONN_STATUS_ENUM
{
    TAF_APS_USER_CONN_EXIST,
    TAF_APS_USER_CONN_NOT_EXIST,
    TAF_APS_USER_CONN_BUTT
};
typedef VOS_UINT8 TAF_APS_USER_CONN_STATUS_ENUM_UINT8;

/*****************************************************************************
 ??????    : TAF_OAM_SDT_CONNECT_STATUS_ENUM
 ????????  : SDT??????????
 1.??    ??   : 2012??04??20??
   ??    ??   : l00171473
   ????????   : ????
*****************************************************************************/
enum TAF_OAM_SDT_CONNECT_STATUS_ENUM
{
    TAF_OAM_SDT_CONNECT_STATUS_CONNECTED,                                       /* SDT???????????? */
    TAF_OAM_SDT_CONNECT_STATUS_DISCONNECTED,                                    /* SDT?????????????? */
    TAF_OAM_SDT_CONNECT_STATUS_BUTT
};
typedef VOS_UINT8 TAF_OAM_SDT_CONNECT_STATUS_ENUM_UINT8;

/*****************************************************************************
 ??????    : TAF_OAM_PC_RECUR_CFG_ENUM
 ????????  : ????????NAS??PC????????????
 1.??    ??   : 2012??04??20??
   ??    ??   : l00171473
   ????????   : ????
*****************************************************************************/
enum TAF_OAM_PC_RECUR_CFG_ENUM
{
    TAF_OAM_PC_RECUR_CFG_ENABLE,                                                /* ????????PC???????? */
    TAF_OAM_PC_RECUR_CFG_DISABLE,                                               /* ??????????PC???????? */
    TAF_OAM_PC_RECUR_CFG_BUTT
};
typedef VOS_UINT8 TAF_OAM_PC_RECUR_CFG_ENUM_UINT8;


/*****************************************************************************
 ??????    : TAF_OAM_EMERGENCY_CALL_STATUS_ENUM
 ????????  : ????????????????
 1.??    ??   : 2013??03??28??
   ??    ??   : l00198894
   ????????   : ????
*****************************************************************************/
enum TAF_OAM_EMERGENCY_CALL_STATUS_ENUM
{
    TAF_OAM_EMERGENCY_CALL_START,                                               /* ???????????? */
    TAF_OAM_EMERGENCY_CALL_END,                                                 /* ???????????? */
    TAF_OAM_EMERGENCY_CALL_STATUS_BUTT
};
typedef VOS_UINT8 TAF_OAM_EMERGENCY_CALL_STATUS_ENUM_UINT8;

/*****************************************************************************
??????    : OM_HSIC_PORT_STATUS_ENUM
????????  : OM??????HSIC????????

  1.??    ??   : 2012??4??4??
    ??    ??   : w00184875
    ????????   : V7R1C51 ????????????????
*****************************************************************************/
enum OM_HSIC_PORT_STATUS_ENUM
{
    OM_HSIC_PORT_STATUS_OFF      = 0,       /* HSIC??GU??OM?????????? */
    OM_HSIC_PORT_STATUS_ON,                 /* HSIC??GU??OM?????????? */
    OM_HSIC_PORT_STATUS_BUTT
};
typedef VOS_UINT32 OM_HSIC_PORT_STATUS_ENUM_UINT32;

/*****************************************************************************
  6 ????????
*****************************************************************************/


/*****************************************************************************
  7 STRUCT????
*****************************************************************************/

/*****************************************************************************
 ??????    : MN_APP_CS_SET_TRANS_PORT_MSG_STRU
 ????????  : VC??OM??????????, VC??OM????REQ????

  1.??    ??   : 2011??10??17??
    ??    ??   : f00179209
    ????????   : ????, AT????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                         usPrimId;                                /* ?????? */
    VOS_UINT16                         usReserve;                               /* ???? */
    VOS_UINT32                         ulStatus;                                /* ???????? */
    VOS_UINT32                         ulPort;                                  /* ?????? */
}MN_APP_CS_SET_TRANS_PORT_MSG_STRU;

/*****************************************************************************
 ??????    : MN_APP_PHONE_MODE_SET_REQ_STRU
 ????????  :
 ASN.1???? :
 ????????  : STK/SPY????MMA????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           opID;
    VOS_UINT8                           aucReserved1[1];
    TAF_PH_OP_MODE_STRU                 stPhOpMode;
} MN_APP_PHONE_MODE_SET_REQ_STRU;

/*****************************************************************************
 ??????    : MN_APP_PHONE_LOADDEFAULT_REQ_STRU
 ????????  :
 ASN.1???? :
 ????????  : STK/SPY????MMA????????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           opID;
    VOS_UINT8                           aucReserved1[1];
}MN_APP_PHONE_LOADDEFAULT_REQ_STRU;

/*****************************************************************************
 ??????    : MN_APP_PHONE_EVENT_INFO_STRU
 ????????  :
 ASN.1???? :
 ????????  : PHONE ????STK ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    TAF_PHONE_EVENT_INFO_STRU           stPhoneEvent;
}MN_APP_PHONE_EVENT_INFO_STRU;

/*****************************************************************************
 ??????    : MN_APP_PHONE_SET_CNF_STRU
 ????????  :
 ASN.1???? :
 ????????  : PHONE ????STK ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           opID;
    TAF_PARA_TYPE                       ucParaType;
    TAF_PARA_SET_RESULT                 ucResult;
    VOS_UINT8                           aucReserved[3];
}MN_APP_PHONE_SET_CNF_STRU;

/* Deleted by z00161729 for V9R1 STK????, 2013-7-24, begin */

/* Deleted by z00161729 for V9R1 STK????, 2013-7-24, end */


/*****************************************************************************
 ??????    : MN_APP_SAR_ANTENSTATUS_MSG_STRU
 ????????  :
 ASN.1???? :
 ????????  : OAM????TAF??ANTEN????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    VOS_INT32                           lAntenStatus; /* ??????????????Taf */
} MN_APP_SAR_ANTENSTATUS_MSG_STRU;

/*****************************************************************************
 ??????    : MN_APP_SAR_INFO_STRU
 ????????  :
 ASN.1???? :
 ????????  : ????DSP??Reduction????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                  ulSarType;      /* ???????????? */
    VOS_INT32                   lAntenStatus;   /* ???????? */
    VOS_UINT32                  ulSarReduction; /* ??sar???? */
}MN_APP_SAR_INFO_STRU;


/*****************************************************************************
 ??????    : TAF_OAM_TRACE_CFG_STRU
 ????????  : OAM????TAF??TRACE ????????
 1.??    ??   : 2012??04??20??
   ??    ??   : l00171473
   ????????   : ????
*****************************************************************************/
typedef struct
{
    TAF_OAM_PC_RECUR_CFG_ENUM_UINT8     enPcRecurCfgFlg;
    VOS_UINT8                           aucRsv3[3];
}TAF_OAM_TRACE_CFG_STRU;

/*****************************************************************************
 ??????    : TAF_OAM_TRACE_CFG_IND_STRU
 ????????  : OAM????TAF??TRACE ????????
 1.??    ??   : 2012??04??20??
   ??    ??   : l00171473
   ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;            /* ????ID*/

    TAF_OAM_TRACE_CFG_STRU              stTraceCfg;         /* TRACE???????? */
}TAF_OAM_TRACE_CFG_IND_STRU;


/* Deleted by z00161729 for V9R1 STK????, 2013-7-24, begin */

/* Deleted by z00161729 for V9R1 STK????, 2013-7-24, end */


/* Deleted SSA_USSD_DCS_DECODE_HOOK_STRU by f62575 for V9R1 STK????, 2013-6-26 */


/* Modified by z00161729 for ????????AT??????????????C??, 2013-4-11, begin */
/*****************************************************************************
 ??????    : TAF_OAM_UNSOLICITED_RPT_INFO_STRU
 ????????  : ????????????????????????????????????
 1.??    ??  : 2013??4??11??
   ??    ??  : z00161729
   ????????  : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    VOS_UINT32                          ulRptCmdIndex;
    VOS_UINT8                           aucCurcRptCfg[TAF_STK_CURC_RPT_CFG_MAX_SIZE];
    VOS_UINT8                           aucUnsolicitedRptCfg[TAF_STK_CURC_RPT_CFG_MAX_SIZE];
 }TAF_OAM_UNSOLICITED_RPT_INFO_STRU;

/* Modified by z00161729 for ????????AT??????????????C??, 2013-4-11, end */

/*****************************************************************************
 ??????    : TAF_OAM_EMERGENCY_CALL_STATUS_STRU
 ????????  : ????OAM????????????????
 1.??    ??  : 2013??03??28??
   ??    ??  : l00198894
   ????????  : ??????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                  ulMsgId;
    TAF_OAM_EMERGENCY_CALL_STATUS_ENUM_UINT8    enEmergencyCallStatus;
    VOS_UINT8                                   aucReserved1[3];
}TAF_OAM_EMERGENCY_CALL_STATUS_STRU;

/* Deleted by z00161729 for V9R1 STK????, 2013-7-24, begin */

/* Deleted by z00161729 for V9R1 STK????, 2013-7-24, end */


/* Added by s00217060 for VoLTE_PhaseI  ????, 2013-07-20, begin */
/*****************************************************************************
 ??????    : TAF_OAM_LOG_END_CALL_REQ_STRU
 ????????  : VC????????????????????????????????????????????
 1.??    ??  : 2013??07??20??
   ??    ??  : s00217060
   ????????  : ??????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                              ulMsgId;
    VOS_UINT32                                              ulCause;
}TAF_OAM_LOG_END_CALL_REQ_STRU;

/* Added by s00217060 for VoLTE_PhaseI  ????, 2013-07-20, end */

typedef VOS_INT (*pSockRecv)(VOS_UINT8 uPortNo, VOS_UINT8* pData, VOS_UINT16 uslength);

/*****************************************************************************
  8 UNION????
*****************************************************************************/


/*****************************************************************************
  9 OTHERS????
*****************************************************************************/


/*****************************************************************************
  10 ????????
*****************************************************************************/
extern TAF_APS_USER_CONN_STATUS_ENUM_UINT8 TAF_APS_GetUserConnStatus(VOS_VOID);

extern VOS_VOID Spy_SarSendToDsp(MODEM_ID_ENUM_UINT16 enModemID, MN_APP_SAR_INFO_STRU *pstSpyToDsp);

extern VOS_UINT16 Spy_SarGetReduction(VOS_VOID);

/* Deleted by f62575 for V9R1 STK????, 2013-6-26, begin */
/* Deleted SSA_GetDcsMsgCoding */
/* Deleted by f62575 for V9R1 STK????, 2013-6-26, end */

extern VOS_VOID SSA_UssdDcsHook(
    VOS_UINT32                          ulReceiverPid,
    VOS_UINT8                           ucDcs,
    MN_MSG_MSG_CODING_ENUM_U8           enMsgCoding
);

extern VOS_UINT32 PPM_LogPortSwitch(VOS_UINT32  ulPhyPort, VOS_BOOL ulEffect);

extern VOS_UINT32 PPM_QueryLogPort(VOS_UINT32  *pulLogPort);

extern OM_HSIC_PORT_STATUS_ENUM_UINT32 PPM_GetHsicPortStatus(VOS_VOID);

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

#endif /* end of TafOamInterface.h */

