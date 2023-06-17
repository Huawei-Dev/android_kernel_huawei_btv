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



#ifndef __OM_ERRORLOG_H__
#define __OM_ERRORLOG_H__

/*****************************************************************************
  1 ??????????????
*****************************************************************************/
#include "vos.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 ??????
*****************************************************************************/

/* ????ERR log ???????? */
#define     ID_OM_ERR_LOG_CTRL_IND          (0x9001)
#define     ID_OM_ERR_LOG_REPORT_REQ        (0x9002)
#define     ID_OM_ERR_LOG_REPORT_CNF        (0x9003)

/* ???????????????????? */
#define     ID_OM_FTM_CTRL_IND              (0x9004)
#define     ID_OM_FTM_REPROT_IND            (0x9005)

/* ???????????????????? */
#define     ID_OM_FTM_REQUIRE_IND           (0x9006)
#define     ID_OM_FTM_REQUIRE_CNF           (0x9007)

/* ???????????????????????????? */
#define     ID_OM_FAULT_ERR_LOG_IND         (0x9009) /* haojian ???????????????????????????????????????????????? */

/* ???????????????????????????? */
#define     ID_OM_ALARM_ERR_LOG_IND         (0x900A)

/* ???????????????? */
#define     ID_OM_INFO_CLT_REPORT_REQ       (0x9010)
#define     ID_OM_INFO_CLT_REPORT_CNF       (0x9011)

#define     OM_MAX_FAULT_ID                 (40)         /* ???????????????? */
#define     OM_MAX_MODULE_ID                (32)         /* ???????????? */
#define     OM_PID_NULL                     (0)          /* OM PID???? */
#define     OM_AP_NO_MSG_SEND               (0)          /* OM??????AP???????? */
#define     OM_AP_SEND_MSG_FINISH           (0)          /* OM??????AP???????? */
//#define     OM_AP_SEND_MSG_FINISH           (0xFF)          /* OM??????AP???????? */
#define     OM_ERR_FAULT_ID                 (0xFFFFFFFF) /* ?????????????????? */
#define     OM_PAM_LENGTH                   (2*1024)     /* OM??????????PID?? */
/* Error Log ?????????? */
#define OM_ERRLOG_TIMER_LENTH               (5000)

/* Clt INFO timer */
#define OM_CLTINFO_TIMER_LENTH               (5000)

/* Send Log Tool MSG Type*/
#define OM_ERRLOG_SEND_MSG                  (0x0000DDDD)
#define OM_ERRLOG_RCV_MSG                   (0x0000EEEE)
#define OM_APP_ERRLOG_HOOK_IND              (0xBBFF)

#define OM_CLTINFO_CNF_NEED_PROCESS          0
#define OM_CLTINFO_CNF_NOT_NEED_PROCESS      1
#define OM_CLTINFO_INVALID_PID               0x5a5abeef

/*****************************************************************************
  3 ????????
*****************************************************************************/
enum OM_ERR_LOG_MSG_TYPE_ENUM
{
    OM_ERR_LOG_MSG_SET_ERR_REPORT = 0x01, /* ???????????????? */
    OM_ERR_LOG_MSG_ERR_REPORT_END = 0x02, /* ???????????? */
    OM_ERR_LOG_MSG_ON_OFF         = 0x03, /* ?????????????? */
    OM_ERR_LOG_MSG_ERR_REPORT     = 0x04, /* ???????? */
    OM_ERR_LOG_MSG_FTM_REPORT     = 0x05, /* ???????????????? */
    OM_ERR_LOG_MSG_RESULT         = 0x06, /* ????Result */
    OM_ERR_LOG_MSG_FTM_REQ        = 0x07, /* ???????????? */
    OM_ERR_LOG_MSG_FTM_CNF        = 0x08, /* ???????????? */

    OM_ERR_LOG_MSG_FAULT_REPORT   = 0x09, /* ???????????????????? */

    OM_ERR_LOG_MSG_ALARM_REPORT   = 0x0A, /* ???????????????????? */

    OM_ERR_LOG_MSG_INFO_CLT_REQ   = 0x10, /* ???????????? */
    OM_ERR_LOG_MSG_INFO_CLT_CNF   = 0x11, /* ???????????? */
    OM_ERR_LOG_MSG_INFO_CLT_END   = 0x12,

    OM_ERR_LOG_MSG_TYPE_BUTT
};
typedef VOS_UINT32    OM_ERR_LOG_MSG_TYPE_ENUM_UINT32;


enum OM_ERR_LOG_MOUDLE_ID_ENUM
{
    OM_ERR_LOG_MOUDLE_ID_GUNAS  = 0x020001,   /* GU NAS */
    OM_ERR_LOG_MOUDLE_ID_GNAS   = 0x020011,   /* G NAS */
    OM_ERR_LOG_MOUDLE_ID_UNAS   = 0x020021,   /* U NAS */
    OM_ERR_LOG_MOUDLE_ID_GAS    = 0x020002,   /* GAS */
    OM_ERR_LOG_MOUDLE_ID_WAS    = 0x020003,   /* WAS */
    OM_ERR_LOG_MOUDLE_ID_GUL2   = 0x020004,   /* GUL2 */
    OM_ERR_LOG_MOUDLE_ID_GL2    = 0x020014,   /* GL2 */
    OM_ERR_LOG_MOUDLE_ID_UL2    = 0x020024,   /* UL2 */
    OM_ERR_LOG_MOUDLE_ID_GUPHY  = 0x020005,   /* GUPHY */
    OM_ERR_LOG_MOUDLE_ID_GPHY   = 0x020015,   /* GPHY */
    OM_ERR_LOG_MOUDLE_ID_UPHY   = 0x020025,   /* UPHY */
    OM_ERR_LOG_MOUDLE_ID_USIMM  = 0x020006,   /* USIMM */
    OM_ERR_LOG_MOUDLE_ID_DRV_SCI= 0x020007,   /* SCI DRV */
    OM_ERR_LOG_MOUDLE_ID_HIFI   = 0x020008,   /* HIFI */
    OM_ERR_LOG_MOUDLE_ID_RRM    = 0x020009,   /* RRM */
    OM_ERR_LOG_MOUDLE_ID_LMM    = 0x020030,   /* LTE EMM */
    OM_ERR_LOG_MOUDLE_ID_ESM    = 0x020031,   /* LTE ESM */
    OM_ERR_LOG_MOUDLE_ID_LSMS   = 0x020032,   /* LTE SMS(????GU SMS????????????????) */
    OM_ERR_LOG_MOUDLE_ID_LPP    = 0x020033,   /* LTE LPP */
    OM_ERR_LOG_MOUDLE_ID_LRRC   = 0x020034,   /* LTE RRC */
    OM_ERR_LOG_MOUDLE_ID_LTEL2  = 0x020035,   /* LTEL2 */
    OM_ERR_LOG_MOUDLE_ID_LPHY   = 0x020036,   /* LTE PHY */

    OM_ERR_LOG_MOUDLE_ID_TDS_MM  = 0x020040,   /* TDS MM */
    OM_ERR_LOG_MOUDLE_ID_TDS_GMM = 0x020041,   /* TDS GMM */
    OM_ERR_LOG_MOUDLE_ID_TDS_CC  = 0x020042,   /* TDS CC */
    OM_ERR_LOG_MOUDLE_ID_TDS_SM  = 0x020043,   /* TDS SM */
    OM_ERR_LOG_MOUDLE_ID_TDS_SMS = 0x020044,   /* TDS SMS(????GU SMS????????????????) */
    OM_ERR_LOG_MOUDLE_ID_TDS_LPP = 0x020045,   /* TDS LPP */
    OM_ERR_LOG_MOUDLE_ID_TRRC    = 0x020046,   /* TDS RRC */
    OM_ERR_LOG_MOUDLE_ID_TDSL2   = 0x020047,   /* TDSL2 */
    OM_ERR_LOG_MOUDLE_ID_TDS_PHY = 0x020048,   /* TDS PHY */
 

    /* ??????????????????????????????????COM???????? */
    OM_ERR_LOG_MOUDLE_ID_IMS     = 0x020050,   /* IMS */
    OM_ERR_LOG_MOUDLE_ID_IMSA    = 0x020051,   /* IMSA */

    OM_ERR_LOG_MOUDLE_ID_CNAS    = 0x020060,   /* CNAS */
    OM_ERR_LOG_MOUDLE_ID_CAS     = 0x020061,   /* CAS */
    OM_ERR_LOG_MOUDLE_ID_CL2     = 0x020062,   /* CL2 */
    OM_ERR_LOG_MOUDLE_ID_CPROC   = 0x020063,   /* CPROC */
    OM_ERR_LOG_MOUDLE_ID_CSDR    = 0x020064,   /* CSDR */
    OM_ERR_LOG_MOUDLE_ID_CHIFI   = 0x020065,   /* CHIFI */
    OM_ERR_LOG_MOUDLE_ID_PPPC    = 0x020066,   /* PPPC */
    

    OM_ERR_LOG_MOUDLE_ID_BUTT
};
typedef VOS_UINT32    OM_ERR_LOG_MOUDLE_ID_ENUM_UINT32;

enum OM_APP_SWITCH_MSG_ID_ENUM
{
    OM_APP_SWITCH_MSG_ID_ERR_LOG = 0x03000001, /* Error log???????? */
    OM_APP_SWITCH_MSG_ID_FTM     = 0x03000002, /* ???????????????? */
    OM_APP_SWITCH_MSG_ID_BUTT
};

/* ?????? */
enum OM_APP_SEND_RESULT_ENUM
{
    OM_APP_MSG_OK                   = 0x00,
    OM_APP_VCOM_DEV_INDEX_ERR       = 0x01,
    OM_APP_MSG_LENGTH_ERR           = 0x02,
    OM_APP_MSG_TYPE_ERR             = 0x03,
    OM_APP_SEND_MODEM_ID_ERR        = 0x04,
    OM_APP_OMACPU_ALLOC_MSG_ERR     = 0x05,
    OM_APP_OMACPU_WRITE_NV_ERR      = 0x06,
    OM_APP_OMACPU_READ_NV_ERR       = 0x07,
    OM_APP_MSG_MODULE_ID_ERR        = 0x08,
    OM_APP_SEND_FAULT_ID_ERR        = 0x09,
    OM_APP_NO_FAULT_ID_ERR          = 0x0A,
    OM_APP_REPORT_NOT_FINISH_ERR    = 0x0B,
    OM_APP_ERRLOG_SWITCH_CLOSE_ERR  = 0x0C,
    OM_APP_ERRLOG_START_TIMER_ERR   = 0x0D,
    OM_APP_OMCCPU_ALLOC_MSG_ERR     = 0x0E,
    OM_APP_PID_ALLOC_ERR            = 0x0F,
    OM_APP_GET_PID_ERR              = 0x10,
    OM_APP_FLAG_ALLOC_ERR           = 0x11,
    
    
    
    OM_APP_SEND_RESULT_BUTT
};

/* ???????? */
enum OM_APP_SWITCH_ENUM
{
    OM_APP_STATUS_CLOSE = 0x00,
    OM_APP_STATUS_OPEN  = 0x01,

    OM_APP_STATUS_BUTT
};

enum OM_INFO_CLT_SCENE_TYPE_ENUM
{
    OM_INFO_CLT_SCENE_TYPE_FREQ_BAND                        = 0x4001,
    OM_INFO_CLT_SCENE_TYPE_NETWORK_INFO                     = 0x4002,
    OM_INFO_CLT_SCENE_TYPE_BUTT
};
typedef VOS_UINT16    OM_INFO_CLT_SCENE_TYPE_ENUM_UINT16;

/* COMM??????????API?????????????????????????? */
typedef  VOS_UINT32 (*pFuncOMGetData)(OM_ERR_LOG_MOUDLE_ID_ENUM_UINT32 enProjectModule, VOS_VOID *pData, VOS_UINT32 ulLen);

/*****************************************************************************
  4 ????????????
*****************************************************************************/


/*****************************************************************************
  5 ??????????
*****************************************************************************/


/*****************************************************************************
  6 ????????
*****************************************************************************/


/*****************************************************************************
  7 STRUCT????
*****************************************************************************/

/* OM error log ?????? */
typedef struct
{
    VOS_UINT32                          ulMsgType;
    VOS_UINT32                          ulMsgSN;
    VOS_UINT32                          ulMsgLen;
}OM_ALARM_MSG_HEAD_STRU;

typedef struct
{
    VOS_UINT16                          usMsgType;
    VOS_UINT8                           ucFaultId;
    VOS_UINT8                           ucAlarmId;
    VOS_UINT32                          ulMsgSN;
    VOS_UINT32                          ulMsgLen;
}OM_ERR_MSG_HEAD_STRU;

/* Error Log Payload header */
typedef struct
{
    VOS_UINT32                          ulMsgModuleId;
    VOS_UINT16                          usModemId;
    VOS_UINT16                          usAlmId;
    VOS_UINT16                          usAlmLevel;
    VOS_UINT16                          usAlmType;
    VOS_UINT32                          usAlmLowSlice;
    VOS_UINT32                          usAlmHighSlice;
    VOS_UINT32                          ulAlmLength;
}OM_ERR_LOG_HEADER_STRU;


/* FTM Payload header */
typedef struct
{
    VOS_UINT32                          ulMsgModuleId;
    VOS_UINT16                          usModemId;
    VOS_UINT16                          usProjectId;
    VOS_UINT32                          ulProjectLength;
}OM_FTM_HEADER_STRU;

/* Info Clt Payload header */
typedef struct
{
    VOS_UINT32                          ulMsgModuleId;
    VOS_UINT16                          usModemId;
    VOS_UINT16                          usSceneType;
    VOS_UINT32                          ulMsgLength;
}OM_INFO_CLT_HEADER_STRU;

/* Error log??????????????type=0x03 App->OM */
typedef struct
{
    OM_ALARM_MSG_HEAD_STRU              stOmHeader;
    VOS_UINT32                          ulMsgModuleID; /* Err log:0x03000001 ????????:0x03000002 */
    VOS_UINT16                          usModemID;
    VOS_UINT8                           ucAlmStatus; /* ???????? 0:close 1:open */
    VOS_UINT8                           ucAlmLevel;  /* ???????? */
}APP_OM_CTRL_STATUS_STRU;


/* APP????Error log????type=0x01 App->OM */
typedef struct
{
    OM_ALARM_MSG_HEAD_STRU              stOmHeader;
    VOS_UINT32                          ulMsgModuleID;
    VOS_UINT16                          usModemID;
    VOS_UINT16                          usFaultId; /* ???????????? */
}APP_OM_REQ_ERR_LOG_STRU;

/* APP????Info Clt????type=0x10 App->OM */
typedef struct
{
    OM_ALARM_MSG_HEAD_STRU              stOmHeader;
    VOS_UINT16                          usModemID;
    VOS_UINT16                          usInfoID;
    VOS_UINT32                          ulMsgLength;
    VOS_UINT8                           aucMsgContent[4];
}APP_OM_INFO_CLT_REQ_STRU;

/* APP????FTM????type=0x07 App->OM */
typedef struct
{
    OM_ALARM_MSG_HEAD_STRU              stOmHeader;
    VOS_UINT32                          ulMsgModuleID;
    VOS_UINT16                          usModemID;
    VOS_UINT16                          usProjectMsgID;  /* ???????????????? */
    VOS_UINT32                          ulTransID;       /* ????????????????ID????????????????????????????ID???? */
    VOS_UINT32                          ulProjectLength; /* OMPayload???????????? */
    VOS_UINT8                           aucMsgContent[4];
}APP_OM_FTM_REQ_STRU;

/* FTM????APP type=0x08 OM->App */
typedef struct
{
    OM_ALARM_MSG_HEAD_STRU              stOmHeader;
    VOS_UINT32                          ulMsgModuleID;
    VOS_UINT16                          usModemID;
    VOS_UINT16                          usProjectMsgID; /* ???????????????? */
    VOS_UINT32                          ulTransID;      /* ????????????????ID????????????????????????????ID???? */
    VOS_UINT32                          ulProjectLength;/* ??????????????????????MsgContent????????,??????????0 aucMsgContent????????????0 ?? */
    VOS_UINT8                           aucMsgContent[4];
}OM_APP_FTM_CNF_STRU;

/* ????????????????????????PID?????????? */
typedef struct
{
    VOS_UINT32                          ulMsgModuleID;
    VOS_UINT32                          ulPID;
}APP_OM_FTM_MSG_PID_STRU;

/* Result To App type=0x06  OM -> App */
typedef struct
{
    OM_ALARM_MSG_HEAD_STRU              stOmHeader;
    VOS_UINT32                          ulMsgModuleID;
    VOS_UINT16                          usModemID;
    VOS_UINT16                          usRsv;
    VOS_UINT32                          ulStatus; /* result */
}OM_APP_RESULT_CNF_STRU;

/* Error log ???????? type=0x02 OM-> APP */
typedef struct
{
    OM_ALARM_MSG_HEAD_STRU              stOmHeader;
    VOS_UINT32                          ulMsgModuleID;
    VOS_UINT16                          usModemID;
    VOS_UINT16                          usFaultID;
    VOS_UINT32                          ulReportStatus; /* result */
    VOS_UINT32                          ulTrigLowSlice; /* ?????????????????????????? */
    VOS_UINT32                          ulTrigHighSlice;
}OM_APP_REPORT_STATUS_STRU;

/* ERRLOG ???????? OM->???? */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT16                          usModemID;
    VOS_UINT8                           ucAlmStatus;  /* ????????????ERRLOG???????? 0:close 1:open */
    VOS_UINT8                           ucAlmLevel;   /* ???????? */
}OM_ERROR_LOG_CTRL_IND_STRU;


/* ??????????????????ERR log???????? OM->???? */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT16                          usModemID;
    VOS_UINT8                           ucFaultID;
    VOS_UINT8                           ucAlarmID;
}OM_ERR_LOG_REPORT_REQ_STRU;
#if 0
/*?????????? PAM->OM*/
typedef struct
{
    VOS_UINT32                            ulPid;
    VOS_UINT32                            ulAlarmID;
}OM_ERR_ALARM_STRU;
#endif
/* ????????????????ERR log ???? -> OM*/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulMsgType;
    VOS_UINT32                          ulMsgSN;
    VOS_UINT32                          ulRptlen;      /* ????????????,????ulRptlen??0,aucContent????????????0 */
    VOS_UINT8                           aucContent[4]; /* ???????? */
} OM_ERR_LOG_REPORT_CNF_STRU;

/* x??????????????????ERR log ???? -> OM*/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT16                          usMsgType;
    VOS_UINT8                           ucFaultId;                       
    VOS_UINT8                           ucAlarmId;
    VOS_UINT32                          ulMsgSN;
    VOS_UINT32                          ulRptlen;      /* ????????????,????ulRptlen??0,aucContent????????????0 */
    VOS_UINT8                           aucContent[4]; /* ???????? */
} OM_ERR_LOG_RPT_CNF_STRU;

/* ???????????????????? OM->???? */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT16                          usModemID;
    VOS_UINT8                           ucActionFlag; /* ???????????????????????????? 0:close 1:open*/
    VOS_UINT8                           aucRsv[1];
}OM_FTM_CTRL_IND_STRU;

/* ???????????????? OM->???? */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT16                          usModemID;
    VOS_UINT8                           aucContent[2];
}OM_FTM_REQUIRE_STRU;

/* ?????????????????????????? ?????? -> OM*/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulMsgType;
    VOS_UINT32                          ulMsgSN;
    VOS_UINT32                          ulRptlen;      /* ??????????????????????,????ulRptlen??0,aucContent????????????0 */
    VOS_UINT8                           aucContent[4]; /* ?????????????????? */
}OM_FTM_REPROT_IND_STRU;

/* ?????????????????????? ?????? -> OM*/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulMsgType;
    VOS_UINT32                          ulMsgSN;
    VOS_UINT32                          ulRptlen;      /* ??????????????????????,????ulRptlen??0,aucContent????????????0 */
    VOS_UINT8                           aucContent[4]; /* ?????????????????? */
}OM_FAULT_ERR_LOG_IND_STRU;
/* x?? ?????????????????????? ?????? -> OM*/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT16                          usMsgType;
    VOS_UINT8                           ucFaultId;
    VOS_UINT8                           ucAlarmId;
    VOS_UINT32                          ulMsgSN;
    VOS_UINT32                          ulRptlen;      /* ??????????????????????,????ulRptlen??0,aucContent????????????0 */
    VOS_UINT8                           aucContent[4]; /* ?????????????????? */
}OM_FAULT_ERR_LOG_CDMA_IND_STRU;

typedef struct
{
    VOS_UINT32                        ulMcc;
    VOS_UINT32                        ulMnc;
}OM_INFO_CLT_PLMN_ID_STRU;

/* ?????????????????????????????? OM->???? */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT16                          usModemID;
    OM_INFO_CLT_SCENE_TYPE_ENUM_UINT16  enSceneType;
    VOS_UINT32                          ulMsgLen;
    VOS_UINT8                           aucContent[4];
}OM_INFO_CLT_REPORT_REQ_STRU;

/* ???????????????????? ???? -> OM*/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulMsgType;
    VOS_UINT32                          ulMsgSN;
    VOS_UINT32                          ulRptLen;      /* ??????????????????????,????ulRptLen??0,aucContent????????????0 */
    VOS_UINT8                           aucContent[4]; /* ?????????????????? */
} OM_INFO_CLT_REPORT_CNF_STRU;

/* OM????????Error Log???????? */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    OM_ERR_MSG_HEAD_STRU                stOmHeader;
}OM_RCV_DATA_INFO_STRU;

/* ????????  : OM????Errlog?????????? */
typedef struct
{
    OM_ERR_LOG_MOUDLE_ID_ENUM_UINT32    enProjectModule;   /* ?????? */
    pFuncOMGetData                      pSendUlAtFunc;     /* ?????????? ???????????? */
}OM_REGISTER_PROJECT_CTX_STRU;

/*****************************************************************************
 ??????    : OM_ERRLOG_TRANS_MSG_STRU
 ????????  : Error Log ??????????????
 1.??    ??   : 2014??09??19??
   ??    ??   : d00212987
   ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_UINT8           ucFuncType;
    VOS_UINT8           ucCpuId;
    VOS_UINT16          usLength;
    VOS_UINT32          ulSn;           /*Sequence Number for Trace, Event, OTA msg.*/
    VOS_UINT32          ulTimeStamp;    /*CPU time coming from ARM.*/
    VOS_UINT16          usPrimId;
    VOS_UINT16          usToolId;
    VOS_UINT32          ulDateType;
    VOS_UINT8           aucValue[4];
}OM_ERRLOG_TRANS_MSG_STRU;


/*****************************************************************************
  8 UNION????
*****************************************************************************/


/*****************************************************************************
  9 OTHERS????
*****************************************************************************/


/*****************************************************************************
  10 ????????
*****************************************************************************/
/******************************************************************************
??????  ??OM_RegisterGetData
??????????OM Ccpu????????????????????????????APP????????????????
??????????enProjectModule        ??????????????????????OM_VOLTE_MOUDLE_PROJECT
          pFuncProjectCallbak    ??????????????
??????????NA
??????  ??VOS_OK/VOS_ERR
??????????
1.  ????    ??2014??1??2??
????    ??
????????????????????
????:
    1??????????????????????????????????Data????????????OmHeard??OMPayload
    2??????????????????????????????????Data????????????OmHeard??OMPayload
*****************************************************************************/
extern VOS_UINT32 OM_RegisterGetData(OM_ERR_LOG_MOUDLE_ID_ENUM_UINT32 enProjectModule, pFuncOMGetData pFuncProjectCallback);

/******************************************************************************
??????  ??OM_GetData
??????????OM Ccpu??????????????????????????
??????????enProjectModule    ??????????
          pData              ??????????
          ulLen              ??????????????
??????????NA
??????  ??VOS_OK/VOS_ERR
??????????
1.  ????    ??2014??1??2??
????    ??
????????????????????
??????pData??OMHeader??MsgType??????????????????????????????Header??????????Header??????SN??????COMM????
*****************************************************************************/
extern VOS_UINT32 OM_GetData(OM_ERR_LOG_MOUDLE_ID_ENUM_UINT32 enProjectModule, VOS_VOID *pData, VOS_UINT32 ulLen);

extern VOS_VOID OM_AcpuSendVComData(VOS_UINT8 *pData, VOS_UINT32 uslength);
extern VOS_INT  OM_AcpuReadVComData(VOS_UINT8 ucDevIndex, VOS_UINT8 *pucData, VOS_UINT32 ulength);

extern VOS_VOID OM_AcpuErrLogMsgProc(MsgBlock* pMsg);
extern VOS_VOID OM_AcpuErrLogReqMsgProc(MsgBlock* pMsg);
extern VOS_VOID OM_AcpuErrLogTimeoutProc(VOS_VOID);

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

#endif /* end of omerrorlog.h */


