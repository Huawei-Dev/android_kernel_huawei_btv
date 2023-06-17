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
#ifndef __TAFSSAAPI_H__
#define __TAFSSAAPI_H__

/*****************************************************************************
  1 ??????????????
*****************************************************************************/
#include "vos.h"
#include "TafTypeDef.h"
#include "PsTypeDef.h"
#include "TafApi.h"
#include "LcsCommInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 ??????
*****************************************************************************/
#define TAF_SSA_MSG_ID_BASE             (0x5000)                                /* ID_TAF_SSA_INTERNAL_BASE */
#define TAF_SSA_EVT_ID_BASE             (TAF_SSA_MSG_ID_BASE + 0x800)

#define TAF_SSA_LCS_THIRD_PARTY_ADDR_MAX_LEN    (20)
#define TAF_SSA_LCS_MTLR_MAX_NUM                (7)

/* ????OSA???????????? */
#define TAF_SSA_ALLOC_MSG_WITH_HDR(ulMsgLen)\
            PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF, (ulMsgLen))

/* ????OSA?????? */
#define TAF_SSA_CFG_MSG_HDR(pstMsg, ulRecvPid, ulMsgId)\
           { \
            ((MSG_HEADER_STRU *)(pstMsg))->ulSenderCpuId   = VOS_LOCAL_CPUID;\
            ((MSG_HEADER_STRU *)(pstMsg))->ulSenderPid     = WUEPS_PID_TAF;\
            ((MSG_HEADER_STRU *)(pstMsg))->ulReceiverCpuId = VOS_LOCAL_CPUID;\
            ((MSG_HEADER_STRU *)(pstMsg))->ulReceiverPid   = (ulRecvPid);\
            ((MSG_HEADER_STRU *)(pstMsg))->ulMsgName       = (ulMsgId); \
           }

/* ????OSA??????(SSA????????) */
#define TAF_SSA_CFG_INTRA_MSG_HDR(pstMsg, ulMsgId)\
            TAF_SSA_CFG_MSG_HDR(pstMsg, WUEPS_PID_TAF, ulMsgId)

/* ????OSA???????? */
#define TAF_SSA_GET_MSG_ENTITY(pstMsg)\
            ((VOS_VOID *)&(((MSG_HEADER_STRU *)(pstMsg))->ulMsgName))

/* ????OSA???????? */
#define TAF_SSA_GET_MSG_LENGTH(pstMsg)\
            (((MSG_HEADER_STRU *)(pstMsg))->ulLength)

/* ????OSA?????????????????????? */
#define TAF_SSA_CLR_MSG_ENTITY(pstMsg)\
            PS_MEM_SET(TAF_SSA_GET_MSG_ENTITY(pstMsg), 0x0, TAF_SSA_GET_MSG_LENGTH(pstMsg))

/* ????OSA???????????? */
#define TAF_SSA_SEND_MSG(pstMsg)\
            PS_SEND_MSG(WUEPS_PID_TAF, pstMsg)

/*****************************************************************************
  3 ????????
*****************************************************************************/
/*****************************************************************************
 ????????: TAF_SSA_MSG_ID_ENUM
 ????????: ????????????????ID

 ????????      :
  1.??    ??   : 2015??09??09??
    ??    ??   : l00198894
    ????????   : ????????
*****************************************************************************/
enum TAF_SSA_MSG_ID_ENUM
{
    /* ????????[0x5000, 0x50FF] */
    /* ???????????????????????????????????????????????? */

    /* +CMOLR */
    ID_TAF_SSA_SET_LCS_MOLR_REQ         = TAF_SSA_MSG_ID_BASE + 0x0001,         /* _H2ASN_MsgChoice TAF_SSA_SET_LCS_MOLR_REQ_STRU */
    ID_TAF_SSA_GET_LCS_MOLR_REQ         = TAF_SSA_MSG_ID_BASE + 0x0002,         /* _H2ASN_MsgChoice TAF_SSA_GET_LCS_MOLR_REQ_STRU */

    /* +CMTLR */
    ID_TAF_SSA_SET_LCS_MTLR_REQ         = TAF_SSA_MSG_ID_BASE + 0x0003,         /* _H2ASN_MsgChoice TAF_SSA_SET_LCS_MTLR_REQ_STRU */
    ID_TAF_SSA_GET_LCS_MTLR_REQ         = TAF_SSA_MSG_ID_BASE + 0x0004,         /* _H2ASN_MsgChoice TAF_SSA_GET_LCS_MTLR_REQ_STRU */

    /* +CMTLRA */
    ID_TAF_SSA_SET_LCS_MTLRA_REQ        = TAF_SSA_MSG_ID_BASE + 0x0005,         /* _H2ASN_MsgChoice TAF_SSA_SET_LCS_MTLRA_REQ_STRU */
    ID_TAF_SSA_GET_LCS_MTLRA_REQ        = TAF_SSA_MSG_ID_BASE + 0x0006,         /* _H2ASN_MsgChoice TAF_SSA_GET_LCS_MTLRA_REQ_STRU */

    /* ????????[0x5100, 0x51FF] */

    ID_TAF_SSA_MSG_ID_BUTT
};
typedef VOS_UINT32 TAF_SSA_MSG_ID_ENUM_UINT32;

/*****************************************************************************
 ????????: TAF_SSA_EVT_ID_ENUM
 ????????: TAF SSA????????????????

 ????????      :
  1.??    ??   : 2015??09??09??
    ??    ??   : l00198894
    ????????   : ????????
*****************************************************************************/
enum TAF_SSA_EVT_ID_ENUM
{
    /* ????????[0x5800, 0x58FF] */
    /* ???????????????????????????????????????????????? */

    /* +CMOLR */
    ID_TAF_SSA_SET_LCS_MOLR_CNF         = TAF_SSA_EVT_ID_BASE + 0x0001,         /* _H2ASN_MsgChoice TAF_SSA_SET_LCS_MOLR_CNF_STRU */
    ID_TAF_SSA_GET_LCS_MOLR_CNF         = TAF_SSA_EVT_ID_BASE + 0x0002,         /* _H2ASN_MsgChoice TAF_SSA_GET_LCS_MOLR_CNF_STRU */

    /* +CMOLRG/+CMOLRN/+CMOLRE */
    ID_TAF_SSA_LCS_MOLR_NTF             = TAF_SSA_EVT_ID_BASE + 0x0003,         /* _H2ASN_MsgChoice TAF_SSA_LCS_MOLR_NTF_STRU */

    /* +CMTLR */
    ID_TAF_SSA_SET_LCS_MTLR_CNF         = TAF_SSA_EVT_ID_BASE + 0x0004,         /* _H2ASN_MsgChoice TAF_SSA_SET_LCS_MTLR_CNF_STRU */
    ID_TAF_SSA_GET_LCS_MTLR_CNF         = TAF_SSA_EVT_ID_BASE + 0x0005,         /* _H2ASN_MsgChoice TAF_SSA_GET_LCS_MTLR_CNF_STRU */
    ID_TAF_SSA_LCS_MTLR_NTF             = TAF_SSA_EVT_ID_BASE + 0x0006,         /* _H2ASN_MsgChoice TAF_SSA_LCS_MTLR_NTF_STRU */

    /* +CMTLRA */
    ID_TAF_SSA_SET_LCS_MTLRA_CNF        = TAF_SSA_EVT_ID_BASE + 0x0007,         /* _H2ASN_MsgChoice TAF_SSA_SET_LCS_MTLRA_CNF_STRU */
    ID_TAF_SSA_GET_LCS_MTLRA_CNF        = TAF_SSA_EVT_ID_BASE + 0x0008,         /* _H2ASN_MsgChoice TAF_SSA_GET_LCS_MTLRA_CNF_STRU */

    /* ????????[0x5900, 0x59FF] */

    ID_TAF_SSA_EVT_ID_BUTT
};
typedef VOS_UINT32 TAF_SSA_EVT_ID_ENUM_UINT32;


/*******************************************************************************
 ??????    : TAF_SSA_LCS_MOLR_ENABLE_TYPE_ENUM
 ????????  : LCS????MO-LR????????????????????
  1.??    ??   : 2015??8??25??
    ??    ??   : l00198894
    ????????   : ????????
*******************************************************************************/
enum TAF_SSA_LCS_MOLR_ENABLE_TYPE_ENUM
{
    TAF_SSA_LCS_MOLR_ENABLE_TYPE_DISABLE    = 0,
    TAF_SSA_LCS_MOLR_ENABLE_TYPE_NMEA,
    TAF_SSA_LCS_MOLR_ENABLE_TYPE_GAD,
    TAF_SSA_LCS_MOLR_ENABLE_TYPE_NMEA_GAD,

    TAF_SSA_LCS_MOLR_ENABLE_TYPE_BUTT
};
typedef VOS_UINT8 TAF_SSA_LCS_MOLR_ENABLE_TYPE_ENUM_UINT8;

/*******************************************************************************
 ??????    : TAF_SSA_LCS_MOLR_RPT_TYPE_ENUM
 ????????  : LCS????MO-LR????????????????????
  1.??    ??   : 2015??8??25??
    ??    ??   : l00198894
    ????????   : ????????
*******************************************************************************/
enum TAF_SSA_LCS_MOLR_RPT_ENUM
{
    TAF_SSA_LCS_MOLR_RPT_NMEA           = 0,
    TAF_SSA_LCS_MOLR_RPT_GAD,

    TAF_SSA_LCS_MOLR_RPT_BUTT
};
typedef VOS_UINT8 TAF_SSA_LCS_MOLR_RPT_ENUM_UINT8;

/*******************************************************************************
 ??????    : TAF_SSA_LCS_MTLR_SUBSCRIBE_ENUM
 ????????  : LCS????MT-LR????????????????????
  1.??    ??   : 2015??8??25??
    ??    ??   : l00198894
    ????????   : ????????
*******************************************************************************/
enum TAF_SSA_LCS_MTLR_SUBSCRIBE_ENUM
{
    TAF_SSA_LCS_MTLR_SUBSCRIBE_OFF          = 0,
    TAF_SSA_LCS_MTLR_SUBSCRIBE_CONTRL,
    TAF_SSA_LCS_MTLR_SUBSCRIBE_SUPL,
    TAF_SSA_LCS_MTLR_SUBSCRIBE_CONTRL_SUPL,

    TAF_SSA_LCS_MTLR_SUBSCRIBE_BUTT
};
typedef VOS_UINT8 TAF_SSA_LCS_MTLR_SUBSCRIBE_ENUM_UINT8;



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
/*******************************************************************************
 ??????    : TAF_SSA_LCS_NMEA_REP_STRU
 ????????  : LCS????MO-LR????????NMEA-rep??????????
  1.??    ??   : 2015??8??25??
    ??    ??   : l00198894
    ????????   : ??????????
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           bitGPGSA    : 1;
    VOS_UINT8                           bitGPGGA    : 1;
    VOS_UINT8                           bitGPGSV    : 1;
    VOS_UINT8                           bitGPRMC    : 1;
    VOS_UINT8                           bitGPVTG    : 1;
    VOS_UINT8                           bitGPGLL    : 1;
    VOS_UINT8                           bitSpare    : 2;
} TAF_SSA_LCS_NMEA_REP_STRU;

/*****************************************************************************
 ??????    : TAF_SSA_LCS_MOLR_PARA_SET_STRU
 ????????  : LCS????MO-LR??????????
  1.??    ??   : 2015??8??25??
    ??    ??   : l00198894
    ????????   : ??????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  bitOpMethod             : 1;
    VOS_UINT32                                  bitOpHorAccSet          : 1;
    VOS_UINT32                                  bitOpVerReq             : 1;
    VOS_UINT32                                  bitOpVerAccSet          : 1;
    VOS_UINT32                                  bitOpVelReq             : 1;
    VOS_UINT32                                  bitOpRepMode            : 1;
    VOS_UINT32                                  bitOpTimeout            : 1;
    VOS_UINT32                                  bitOpInterval           : 1;
    VOS_UINT32                                  bitOpShapeRep           : 1;
    VOS_UINT32                                  bitOpPlane              : 1;
    VOS_UINT32                                  bitOpNmeaRep            : 1;
    VOS_UINT32                                  bitOpThirdPartyAddr     : 1;
    VOS_UINT32                                  bitOpSpare              : 20;

    TAF_SSA_LCS_MOLR_ENABLE_TYPE_ENUM_UINT8     enEnable;
    LCS_MOLR_METHOD_ENUM_UINT8                  enMethod;
    LCS_HOR_ACC_SET_ENUM_UINT8                  enHorAccSet;
    VOS_UINT8                                   ucHorAcc;

    LCS_VER_REQ_ENUM_UINT8                      enVerReq;
    LCS_VER_ACC_SET_ENUM_UINT8                  enVerAccSet;
    VOS_UINT8                                   ucVerAcc;
    LCS_VEL_REQ_ENUM_UINT8                      enVelReq;

    VOS_UINT8                                   aucReserved1[3];
    LCS_REP_MODE_ENUM_UINT8                     enRepMode;
    VOS_UINT16                                  usTimeOut;
    VOS_UINT16                                  usInterval;

    VOS_UINT8                                   ucShapeRep;
    LCS_PLANE_ENUM_UINT8                        enPlane;
    TAF_SSA_LCS_NMEA_REP_STRU                   stNmeaRep;

    VOS_CHAR                                    acThirdPartyAddr[TAF_SSA_LCS_THIRD_PARTY_ADDR_MAX_LEN + 1];
    /***************************************************************************
            _H2ASN_Array2String
    ***************************************************************************/
}TAF_SSA_LCS_MOLR_PARA_SET_STRU;

/*****************************************************************************
 ??????    : TAF_SSA_SET_LCS_MOLR_REQ_STRU
 ????????  : LCS????MO-LR??????????????????
  1.??    ??   : 2015??8??25??
    ??    ??   : l00198894
    ????????   : ??????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
    TAF_SSA_LCS_MOLR_PARA_SET_STRU      stMolrPara;
}TAF_SSA_SET_LCS_MOLR_REQ_STRU;

/*****************************************************************************
 ??????    : TAF_SSA_SET_LCS_MOLR_CNF_STRU
 ????????  : LCS????MO-LR??????????????????
  1.??    ??   : 2015??8??25??
    ??    ??   : l00198894
    ????????   : ??????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
    TAF_ERROR_CODE_ENUM_UINT32          enResult;
}TAF_SSA_SET_LCS_MOLR_CNF_STRU;

/*****************************************************************************
 ??????    : TAF_SSA_GET_LCS_MOLR_REQ_STRU
 ????????  : LCS????MO-LR??????????????????
  1.??    ??   : 2015??8??25??
    ??    ??   : l00198894
    ????????   : ??????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
    VOS_UINT8                           aucReserved1[4];
}TAF_SSA_GET_LCS_MOLR_REQ_STRU;

/*****************************************************************************
 ??????    : TAF_SSA_GET_LCS_MOLR_CNF_STRU
 ????????  : LCS????MO-LR??????????????????
  1.??    ??   : 2015??8??25??
    ??    ??   : l00198894
    ????????   : ??????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                           stCtrl;
    TAF_ERROR_CODE_ENUM_UINT32              enResult;
    LCS_MOLR_PARA_STRU                      stMolrPara;
    TAF_SSA_LCS_MOLR_ENABLE_TYPE_ENUM_UINT8 enEnable;                           /* MO-LR???????? */
    LCS_PLANE_ENUM_UINT8                    enPlane;
    TAF_SSA_LCS_NMEA_REP_STRU               stNmeaRep;
    VOS_UINT8                               aucReserved[1];
}TAF_SSA_GET_LCS_MOLR_CNF_STRU;

/*****************************************************************************
 ??????    : TAF_SSA_LCS_MOLR_NTF_STRU
 ????????  : LCS????MO-LR??????????????????????????
  1.??    ??   : 2015??8??25??
    ??    ??   : l00198894
    ????????   : ??????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
    TAF_ERROR_CODE_ENUM_UINT32          enResult;
    TAF_SSA_LCS_MOLR_RPT_ENUM_UINT8     enRptTypeChoice;
    VOS_UINT8                           aucReserved1[1];
    VOS_UINT16                          usLocationStrLen;
    VOS_CHAR                            acLocationStr[8];
}TAF_SSA_LCS_MOLR_NTF_STRU;

/*****************************************************************************
 ??????    : TAF_SSA_SET_LCS_MTLR_REQ_STRU
 ????????  : LCS????MT-LR??????????????????????????
  1.??    ??   : 2015??8??25??
    ??    ??   : l00198894
    ????????   : ??????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                           stCtrl;
    TAF_SSA_LCS_MTLR_SUBSCRIBE_ENUM_UINT8   enSubscribe;
    VOS_UINT8                               aucReserved1[3];
}TAF_SSA_SET_LCS_MTLR_REQ_STRU;

/*****************************************************************************
 ??????    : TAF_SSA_SET_LCS_MTLR_CNF_STRU
 ????????  : LCS????MT-LR??????????????????????????????
  1.??    ??   : 2015??8??25??
    ??    ??   : l00198894
    ????????   : ??????????
*****************************************************************************/
typedef TAF_SSA_SET_LCS_MOLR_CNF_STRU   TAF_SSA_SET_LCS_MTLR_CNF_STRU;

/*****************************************************************************
 ??????    : TAF_SSA_GET_LCS_MTLR_REQ_STRU
 ????????  : LCS????MT-LR??????????????????????????
  1.??    ??   : 2015??8??25??
    ??    ??   : l00198894
    ????????   : ??????????
*****************************************************************************/
typedef TAF_SSA_GET_LCS_MOLR_REQ_STRU   TAF_SSA_GET_LCS_MTLR_REQ_STRU;

/*****************************************************************************
 ??????    : TAF_SSA_GET_LCS_MTLR_CNF_STRU
 ????????  : LCS????MT-LR??????????????????????????????
  1.??    ??   : 2015??8??25??
    ??    ??   : l00198894
    ????????   : ??????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                           stCtrl;
    TAF_ERROR_CODE_ENUM_UINT32              enResult;
    TAF_SSA_LCS_MTLR_SUBSCRIBE_ENUM_UINT8   enSubscribe;
    VOS_UINT8                               aucReserved1[3];
}TAF_SSA_GET_LCS_MTLR_CNF_STRU;

/*****************************************************************************
 ??????    : TAF_SSA_LCS_MTLR_NTF_STRU
 ????????  : LCS????MT-LR??????????????????????????
  1.??    ??   : 2015??8??25??
    ??    ??   : l00198894
    ????????   : ??????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
    LCS_MTLR_PARA_STRU                  stMtlrPara;
}TAF_SSA_LCS_MTLR_NTF_STRU;

/*****************************************************************************
 ??????    : TAF_SSA_LCS_MTLRA_PARA_SET_STRU
 ????????  : LCS????MT-LR ??????????????????
  1.??    ??   : 2015??8??25??
    ??    ??   : l00198894
    ????????   : ??????????
*****************************************************************************/
typedef struct
{
    LCS_MTLRA_OP_ENUM_UINT8             enAllow;
    VOS_UINT8                           ucHandleId;
    VOS_UINT8                           aucReserved1[2];
}TAF_SSA_LCS_MTLRA_PARA_SET_STRU;

/*****************************************************************************
 ??????    : TAF_SSA_SET_LCS_MTLRA_REQ_STRU
 ????????  : LCS????MT-LR??????????????????????????
  1.??    ??   : 2015??8??25??
    ??    ??   : l00198894
    ????????   : ??????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
    TAF_SSA_LCS_MTLRA_PARA_SET_STRU     stCmtlraPara;
}TAF_SSA_SET_LCS_MTLRA_REQ_STRU;

/*****************************************************************************
 ??????    : TAF_SSA_SET_LCS_MTLRA_CNF_STRU
 ????????  : LCS????MT-LR??????????????????????????????
  1.??    ??   : 2015??8??25??
    ??    ??   : l00198894
    ????????   : ??????????
*****************************************************************************/
typedef TAF_SSA_SET_LCS_MOLR_CNF_STRU   TAF_SSA_SET_LCS_MTLRA_CNF_STRU;

/*****************************************************************************
 ??????    : TAF_SSA_GET_LCS_MTLRA_REQ_STRU
 ????????  : LCS????MT-LR??????????????????????????????????
  1.??    ??   : 2015??8??25??
    ??    ??   : l00198894
    ????????   : ??????????
*****************************************************************************/
typedef TAF_SSA_GET_LCS_MOLR_REQ_STRU   TAF_SSA_GET_LCS_MTLRA_REQ_STRU;

/*****************************************************************************
 ??????    : TAF_SSA_GET_LCS_MTLRA_CNF_STRU
 ????????  : LCS????MT-LR??????????????????????????????????????
  1.??    ??   : 2015??8??25??
    ??    ??   : l00198894
    ????????   : ??????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
    TAF_ERROR_CODE_ENUM_UINT32          enResult;
    VOS_UINT8                           ucCnt;
    LCS_MTLRA_OP_ENUM_UINT8             aenAllow[TAF_SSA_LCS_MTLR_MAX_NUM];
    VOS_UINT8                           aucHandleId[TAF_SSA_LCS_MTLR_MAX_NUM];
    VOS_UINT8                           aucReserved1[1];
}TAF_SSA_GET_LCS_MTLRA_CNF_STRU;

/*****************************************************************************
 ????????: TAF_SSA_EVT_STRU
 ????????: SS????????????????

 ????????      :
  1.??    ??   : 2015??10??19??
    ??    ??   : l00198894
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stHeader;                               /*_H2ASN_Skip*/
    VOS_UINT32                          ulEvtExt;
    TAF_SSA_EVT_ID_ENUM_UINT32          enEvtId;
    VOS_UINT8                           aucContent[4];
}TAF_SSA_EVT_STRU;






/*****************************************************************************
  H2ASN????????????????
*****************************************************************************/
typedef struct
{
    TAF_SSA_MSG_ID_ENUM_UINT32          ulMsgId;                                /*_H2ASN_MsgChoice_Export TAF_SSA_MSG_ID_ENUM_UINT32*/
    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          TAF_SSA_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}TAF_SSA_MSG_REQ;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    TAF_SSA_MSG_REQ                     stMsgReq;
}TafSsaApi_MSG;

typedef struct
{
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulEvtExt;
    TAF_SSA_EVT_ID_ENUM_UINT32          ulEvtId;                                /*_H2ASN_MsgChoice_Export TAF_SSA_EVT_ID_ENUM_UINT32*/
    VOS_UINT8                           aucEvtBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          TAF_SSA_EVT_ID_ENUM_UINT32
    ****************************************************************************/
}TAF_SSA_EVT_CNF;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    TAF_SSA_EVT_CNF                     stEvtCnf;
}TafSsaEvt_MSG;

/*****************************************************************************
  8 UNION????
*****************************************************************************/


/*****************************************************************************
  9 OTHERS????
*****************************************************************************/


/*****************************************************************************
  10 ????????
*****************************************************************************/

extern VOS_VOID TAF_SSA_SndTafMsg(
           TAF_SSA_MSG_ID_ENUM_UINT32          enMsgId,
           VOS_VOID                           *pData,
           VOS_UINT32                          ulLength
       );
extern VOS_VOID TAF_SSA_GetCmolrInfo(
           VOS_UINT32                          ulModuleId,
           VOS_UINT16                          usClientId,
           VOS_UINT8                           ucOpId
       );
extern VOS_VOID TAF_SSA_GetCmtlraInfo(
           VOS_UINT32                          ulModuleId,
           VOS_UINT16                          usClientId,
           VOS_UINT8                           ucOpId
       );
extern VOS_VOID TAF_SSA_GetCmtlrInfo(
           VOS_UINT32                          ulModuleId,
           VOS_UINT16                          usClientId,
           VOS_UINT8                           ucOpId
       );
extern VOS_VOID TAF_SSA_SetCmolrInfo(
           VOS_UINT32                          ulModuleId,
           VOS_UINT16                          usClientId,
           VOS_UINT8                           ucOpId,
           TAF_SSA_LCS_MOLR_PARA_SET_STRU     *pstMolrPara
       );
extern VOS_VOID TAF_SSA_SetCmtlraInfo(
           VOS_UINT32                          ulModuleId,
           VOS_UINT16                          usClientId,
           VOS_UINT8                           ucOpId,
           TAF_SSA_LCS_MTLRA_PARA_SET_STRU     *pstCmtlraPara
       );
extern VOS_VOID TAF_SSA_SetCmtlrInfo(
           VOS_UINT32                              ulModuleId,
           VOS_UINT16                              usClientId,
           VOS_UINT8                               ucOpId,
           TAF_SSA_LCS_MTLR_SUBSCRIBE_ENUM_UINT8   enSubscribe
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

#endif /* end of TafSsaApi.h */

