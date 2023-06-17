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
#ifndef _TAF_MTC_API_H_
#define _TAF_MTC_API_H_


/*****************************************************************************
  1 ??????????????
*****************************************************************************/
#include "vos.h"
#include "TafTypeDef.h"
#include "PsTypeDef.h"
#include "TafApi.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 ??????
*****************************************************************************/
#define TAF_MTC_MSG_ID_BASE             (0x1000)                               /* MTC ??????????ID????, ??0x1001???????????????????????????????? */

#define MTC_NONE_CS_VALUE                (0x00)                                /* ?????? */
#define MTC_GU_CS_VALUE                  (MTC_SET_BIT(MTC_CS_TYPE_GU))          /* GU???? */
#define MTC_IMS_CS_VALUE                 (MTC_SET_BIT(MTC_CS_TYPE_IMS))         /* IMS???? */
#define MTC_CDMA_CS_VALUE                (MTC_SET_BIT(MTC_CS_TYPE_CDMA))        /* CDMA???? */

#define MTC_CS_TYPE_ALL_VALUE            (MTC_GU_CS_VALUE | MTC_IMS_CS_VALUE | MTC_CDMA_CS_VALUE)

#define MTC_NONE_PS_VALUE                (0x00)
#define MTC_GU_PS_VALUE                  (MTC_SET_BIT(MTC_PS_TYPE_GU))
#define MTC_LTE_PS_VALUE                 (MTC_SET_BIT(MTC_PS_TYPE_LTE))
#define MTC_CDMA_PS_VALUE                (MTC_SET_BIT(MTC_PS_TYPE_CDMA))
#define MTC_PS_TYPE_ALL_VALUE            (MTC_GU_PS_VALUE | MTC_LTE_PS_VALUE | MTC_CDMA_PS_VALUE)

/*****************************************************************************
  3 ????????
*****************************************************************************/

/*****************************************************************************
 ????????: TAF_MTC_MSG_ID_ENUM
 ????????: MTC????????ID

 ????????      :
  1.??    ??   : 2014??06??16??
    ??    ??   : j00174725
    ????????   : ????????
*****************************************************************************/
enum TAF_MTC_MSG_ID_ENUM
{
    /* ????CDMA???????? */
    ID_MSG_MTC_CDMA_CONN_STATE_IND      = TAF_MTC_MSG_ID_BASE + 0x0001,        /* _H2ASN_MsgChoice  TAF_MTC_CDMA_STATE_IND_STRU */
    ID_MSG_MTC_MODEM_SERVICE_CONN_STATE_IND,                                    /* _H2ASN_MsgChoice  TAF_MTC_MODEM_CONN_STATUS_IND_STRU */
    ID_MSG_MTC_USIMM_STATE_IND,                                                 /* _H2ASN_MsgChoice  TAF_MTC_USIMM_STATUS_IND_STRU */
    ID_MSG_MTC_BEGIN_SESSION_IND,                                               /* _H2ASN_MsgChoice  MTC_BEGIN_SESSION_IND_STRU */
    ID_MSG_MTC_END_SESSION_IND,                                                 /* _H2ASN_MsgChoice  MTC_END_SESSION_IND_STRU */

    ID_MSG_MTC_POWER_SAVE_IND,                                                  /* _H2ASN_MsgChoice  MTC_POWER_SAVE_IND_STRU */

    ID_MSG_MTC_BUTT
};
typedef VOS_UINT32 TAF_MTC_MSG_ID_ENUM_UINT32;

/*****************************************************************************
??????    : TAF_MTC_SRV_CONN_STATE_ENUM
????????  : ????????????????????

  1.??    ??   : 2014??06??16??
    ??    ??   : j00174725
    ????????   : ????????
*****************************************************************************/
enum TAF_MTC_SRV_CONN_STATE_ENUM
{
    TAF_MTC_SRV_NO_EXIST                = 0,                                    /* ?????? */
    TAF_MTC_SRV_EXIST,                                                          /* ?????? */

    TAF_MTC_SRV_CONN_STATE_BUTT
};
typedef VOS_UINT8 TAF_MTC_SRV_CONN_STATE_ENUM_UINT8;

/*****************************************************************************
??????    : TAF_MTC_POWER_STATE_ENUM
????????  : ????????????????

  1.??    ??   : 2014??06??16??
    ??    ??   : j00174725
    ????????   : ????????
*****************************************************************************/
enum TAF_MTC_POWER_STATE_ENUM
{
    TAF_MTC_POWER_OFF                  = 0,                                     /* ???? */
    TAF_MTC_POWER_ON,                                                           /* ???? */

    TAF_MTC_POWER_STATE_BUTT
};
typedef VOS_UINT8 TAF_MTC_POWER_STATE_ENUM_UINT8;

/*****************************************************************************
??????    : TAF_MTC_USIMM_CARD_SERVIC_ENUM
????????  : ??????

  1.??    ??   : 2014??06??16??
    ??    ??   : ??????/j00174725
    ????????   : ????????
*****************************************************************************/

enum TAF_MTC_USIMM_CARD_SERVIC_ENUM
{
    TAF_MTC_USIMM_CARD_SERVIC_ABSENT        =0,                                 /* ???? */
    TAF_MTC_USIMM_CARD_SERVIC_UNAVAILABLE   =1,                                 /* ????,?????????? */
    TAF_MTC_USIMM_CARD_SERVIC_SIM_PIN       =2,                                 /* SIM??????????PIN???????????? */
    TAF_MTC_USIMM_CARD_SERVIC_SIM_PUK       =3,                                 /* SIM??????????PUK???????????? */
    TAF_MTC_USIMM_CARD_SERVIC_NET_LCOK      =4,                                 /* SIM???????????????????????????? */
    TAF_MTC_USIMM_CARD_SERVIC_IMSI_LCOK     =5,                                 /* SIM??????????IMSI?????????????? */
    TAF_MTC_USIMM_CARD_SERVIC_AVAILABLE     =6,                                 /* ???????? */

    TAF_MTC_USIMM_CARD_SERVIC_BUTT
};
typedef VOS_UINT16      TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16;

/*****************************************************************************
??????    : TAF_MTC_CDMA_USIMM_CARD_ENUM
????????  : ??????

  1.??    ??   : 2014??06??16??
    ??    ??   : ??????/j00174725
    ????????   : ????????
*****************************************************************************/

enum TAF_MTC_CDMA_USIMM_CARD_ENUM
{
    TAF_MTC_CDMA_USIMM_CARD_UNVALID        =0,                                  /* ???? */
    TAF_MTC_CDMA_USIMM_CARD_VALID,                                              /* ???????? */

    TAF_MTC_CDMA_USIMM_CARD_BUTT
};
typedef VOS_UINT8  TAF_MTC_CDMA_USIMM_CARD_ENUM_UINT8;

/*****************************************************************************
 ??????    : MTC_SESSION_TYPE_ENUM_UINT8
 ????????  : SESSION????
 1.??    ??   : 2015??09??04??
   ??    ??   : j00174725
   ????????   : ????

   ????:??????????????????????????????32??????????????????
*****************************************************************************/
enum MTC_SESSION_TYPE_ENUM
{
    MTC_SESSION_TYPE_CS_MO_NORMAL_CALL  = 0,
    MTC_SESSION_TYPE_CS_MO_EMERGENCY_CALL,
    MTC_SESSION_TYPE_CS_MO_SS,
    MTC_SESSION_TYPE_CS_MO_SMS,
    MTC_SESSION_TYPE_CS_MT_NORMAL_CALL,
    MTC_SESSION_TYPE_CS_MT_EMERGENCY_CALLBACK,                                  /* ??????eCall?????????? */
    MTC_SESSION_TYPE_CS_MT_SS,
    MTC_SESSION_TYPE_CS_MT_SMS,
    MTC_SESSION_TYPE_CS_LAU,
    MTC_SESSION_TYPE_CS_DETACH,
    MTC_SESSION_TYPE_CS_MO_NORMAL_CSFB,
    MTC_SESSION_TYPE_CS_MO_EMERGENCY_CSFB,
    MTC_SESSION_TYPE_CS_MT_CSFB,
    MTC_SESSION_TYPE_CS_LOOP_BACK,                                              /* ???????? */

    MTC_SESSION_TYPE_TAU_COMBINED,                                           /* ????TAU */

    MTC_SESSION_TYPE_TAU_ONLY_EPS,                                              /* PS ONLY TAU */
    MTC_SESSION_TYPE_TAU_PERIODIC,                                              /* ??????TAU */

    MTC_SESSION_TYPE_CS_BUTT,                                                   /* ??????????????CS???????? */

    MTC_SESSION_TYPE_PS_CONVERSAT_CALL,
    MTC_SESSION_TYPE_PS_STREAM_CALL,
    MTC_SESSION_TYPE_PS_INTERACT_CALL,
    MTC_SESSION_TYPE_PS_BACKGROUND_CALL,
    MTC_SESSION_TYPE_PS_SUBSCRIB_TRAFFIC_CALL,
    MTC_SESSION_TYPE_PS_MO_SMS,
    MTC_SESSION_TYPE_PS_MT_SMS,
    MTC_SESSION_TYPE_PS_ATTACH,
    MTC_SESSION_TYPE_PS_RAU,
    MTC_SESSION_TYPE_PS_DETACH,
    MTC_SESSION_TYPE_1X_PS_CALL,                                                /* 1X??????PS???? */

    MTC_SESSION_TYPE_BUTT                                                       /* ??MTC_SESSION_TYPE_CS_BUTT????????????PS???????? */
};
typedef VOS_UINT8 MTC_SESSION_TYPE_ENUM_UINT8;                                  /* ??????????????????????????????32?????????????????? */

/*****************************************************************************
??????    : MTC_CS_TYPE_ENUM
????????  : CS????????????????

  1.??    ??   : 2015??09??19??
    ??    ??   : j00174725
    ????????   : ????????
*****************************************************************************/
enum MTC_CS_TYPE_ENUM
{
    MTC_CS_TYPE_GU                      = 0x00,                                 /* GU???? */
    MTC_CS_TYPE_IMS,                                                            /* IMS???? */
    MTC_CS_TYPE_CDMA,                                                           /* CDMA???? */

    MTC_CS_TYPE_BUTT
};
typedef VOS_UINT8 MTC_CS_TYPE_ENUM_UINT8;

/*****************************************************************************
??????    : MTC_PS_TYPE_ENUM
????????  : PS????????????????

  1.??    ??   : 2015??10??10??
    ??    ??   : j00174725
    ????????   : ????????

  2.??    ??   : 2015??11??23??
    ??    ??   : h00313353
    ????????   : Iteration 19
*****************************************************************************/
enum MTC_PS_TYPE_ENUM
{
    MTC_PS_TYPE_GU                      = 0x00,                                /* PS */
    MTC_PS_TYPE_LTE,                                                           /* EPS */
    MTC_PS_TYPE_CDMA,                                                          /* CDMA */

    MTC_PS_TYPE_BUTT
};
typedef VOS_UINT8 MTC_PS_TYPE_ENUM_UINT8;

/*****************************************************************************
??????    : TAF_MTC_POWER_SAVE_ENUM
????????  : Power Save????????????

  1.??    ??   : 2016??03??30??
    ??    ??   : j00174725
    ????????   : ????????
*****************************************************************************/
enum TAF_MTC_POWER_SAVE_ENUM
{
    TAF_MTC_POWER_SAVE                  = 0,                                    /* ????power save */
    TAF_MTC_POWER_SAVE_EXIT,                                                    /* ????power save */

    TAF_MTC_POWER_SAVE_BUTT
};
typedef VOS_UINT8 TAF_MTC_POWER_SAVE_ENUM_UINT8;


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
 ??????    : TAF_MTC_CDMA_STATE_INFO_STRU
 ????????  : CDMS??????????

 1.??    ??   : 2014??06??16??
   ??    ??   : j00174725
   ????????   : K3V3 ??????????????
*******************************************************************************/
typedef struct
{
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8       enCsConnSt;                         /* CS???????? */
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8       enPsConnSt;                         /* PS???????? */
    TAF_MTC_POWER_STATE_ENUM_UINT8          enPowerState;                       /* ?????????? */
    VOS_UINT8                               ucReserved1[1];
    TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16   enUsimmState;                       /* ?????? */
    VOS_UINT8                               aucReserved2[2];
}TAF_MTC_CDMA_STATE_INFO_STRU;

/*******************************************************************************
 ??????    : TAF_MTC_CDMA_STATE_IND_STRU
 ????????  : ID_MSG_MTC_CDMA_CONN_STATUS??????????

 1.??    ??   : 2014??06??16??
   ??    ??   : j00174725
   ????????   : K3V3 ??????????????
*******************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
    TAF_MTC_CDMA_STATE_INFO_STRU        stCdmaState;
}TAF_MTC_CDMA_STATE_IND_STRU;

/*******************************************************************************
 ??????    : TAF_MTC_SRV_CONN_STATE_INFO_STRU
 ????????  : ID_MMA_MTC_CONN_STATUS_INFO_IND??????????????????

 1.??    ??   : 2014??06??16??
   ??    ??   : j00174725
   ????????   : K3V3 ??????????????
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPsSrv      : 1;
    VOS_UINT32                          bitOpCsSrv      : 1;
    VOS_UINT32                          bitOpEpsSrv     : 1;
    VOS_UINT32                          bitSpare        : 29;
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enPsSrvConnState;
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enCsSrvConnState;
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enEpsSrvConnState;
    VOS_UINT8                           aucReserved[1];
}TAF_MTC_SRV_CONN_STATE_INFO_STRU;

/*******************************************************************************
 ??????    : TAF_MTC_MODEM_CONN_STATUS_IND_STRU
 ????????  : ID_MMA_MTC_CONN_STATUS_INFO_IND??????????

 1.??    ??   : 2014??06??16??
   ??    ??   : j00174725
   ????????   : K3V3 ??????????????
*******************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
    TAF_MTC_SRV_CONN_STATE_INFO_STRU    stModemConnStateInfo;
}TAF_MTC_MODEM_CONN_STATUS_IND_STRU;

/*******************************************************************************
 ??????    : TAF_MTC_USIMM_STATUS_IND_STRU
 ????????  : ID_MMA_MTC_CONN_STATUS_INFO_IND??????????

 1.??    ??   : 2014??06??16??
   ??    ??   : j00174725
   ????????   : K3V3 ??????????????
*******************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                           stCtrl;
    TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16   enUsimState;       /* Usim?????? */
    TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16   enCsimState;       /* Csim?????? */
}TAF_MTC_USIMM_STATUS_IND_STRU;

/*****************************************************************************
 ??????    : MTC_BEGIN_SESSION_IND_STRU
 ????????  : SESSION????????
 1.??    ??   : 2015??9??4??
   ??    ??   : j00174725
   ????????   : ????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
    MTC_SESSION_TYPE_ENUM_UINT8         enSessionType;
    VOS_UINT8                           aucReserved[3];
}MTC_BEGIN_SESSION_IND_STRU;

/*****************************************************************************
 ??????    : MTC_END_SESSION_IND_STRU
 ????????  : SESSION????????
 1.??    ??   : 2015??09??04??
   ??    ??   : j00174725
   ????????   : ????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
    PS_BOOL_ENUM_UINT8                  enCsRelAll;
    PS_BOOL_ENUM_UINT8                  enPsRelAll;
    MTC_SESSION_TYPE_ENUM_UINT8         enSessionType;
    VOS_UINT8                           ucReserved;
}MTC_END_SESSION_IND_STRU;

/*****************************************************************************
 ??????    : MTC_POWER_SAVE_IND_STRU
 ????????  : POWER SAVE????
 1.??    ??   : 2016??3??30??
   ??    ??   : j00174725
   ????????   : ????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
    TAF_MTC_POWER_SAVE_ENUM_UINT8       enPowerSaveStatus;
    VOS_UINT8                           aucReserved[3];
}MTC_POWER_SAVE_IND_STRU;




/*****************************************************************************
  H2ASN????????????????
*****************************************************************************/
typedef struct
{
    TAF_MTC_MSG_ID_ENUM_UINT32          ulMsgId;                                /*_H2ASN_MsgChoice_Export TAF_MTC_MSG_ID_ENUM_UINT32*/
    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          TAF_MTC_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}TAF_MTC_MSG_REQ;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    TAF_MTC_MSG_REQ                     stMsgReq;
}TafMtcApi_MSG;

/*****************************************************************************
  8 UNION????
*****************************************************************************/


/*****************************************************************************
  9 OTHERS????
*****************************************************************************/



/*****************************************************************************
  10 ????????
*****************************************************************************/
/*****************************************************************************
 ?? ?? ??  : MTC_SndMsg
 ????????  : ????MTC????
 ????????  : VOS_UINT32                          ulTaskId
             VOS_UINT32                          ulMsgId
             VOS_VOID                           *pData
             VOS_UINT32                          ulLen
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2014??06??16??
    ??    ??   : j00174725
    ????????   : ??????????
*****************************************************************************/
VOS_UINT32 MTC_SndMsg(
    VOS_UINT32                          ulTaskId,
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
);

/*****************************************************************************
 ?? ?? ??  : MTC_SetCdmaServiceConnStateInfo
 ????????  : ????????CDMA Modem??????????(PS&CS)
 ????????  : pstCtrl                    - ??????
             pstCdmsStatus              - ????????????
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????????????
             VOS_ERR                    - ????????????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2014??06??16??
    ??    ??   : j00174725
    ????????   : ??????????
*****************************************************************************/
VOS_UINT32 MTC_SetCdmaServiceConnStateInfo(
    TAF_CTRL_STRU                      *pstCtrl,
    TAF_MTC_CDMA_STATE_INFO_STRU       *pstCdmsState
);

/*****************************************************************************
 ?? ?? ??  : MTC_SetModemServiceConnState
 ????????  : ????modem????????
 ????????  : ulModuleId      ????ID
             pstModemConnSt  ????????????
 ????????  : ??
 ?? ?? ??  :
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2014??06??16??
    ??    ??   : j00174725
    ????????   : K3V3 ??????????????
*****************************************************************************/
VOS_UINT32 MTC_SetModemServiceConnState(
    TAF_CTRL_STRU                      *pstCtrl,
    TAF_MTC_SRV_CONN_STATE_INFO_STRU   *pstModemConnSt
);

/*****************************************************************************
 ?? ?? ??  : MTC_SetModemUsimmState
 ????????  : ??????????????
 ????????  : pstCtrl         ??????????
             pstModemConnSt  ????????????
 ????????  : ??
 ?? ?? ??  :
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2014??06??16??
    ??    ??   : j00174725
    ????????   : K3V3 ??????????????

  2.??    ??   : 2015??10??21??
    ??    ??   : h00313353
    ????????   : Iteration 19 TAS
*****************************************************************************/
VOS_UINT32 MTC_SetModemUsimmState(
    TAF_CTRL_STRU                           *pstCtrl,
    TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16    enUsimState,
    TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16    enCsimState
);

VOS_VOID MTC_SetBeginSessionInfo(
    TAF_CTRL_STRU                      *pstCtrl,
    MTC_SESSION_TYPE_ENUM_UINT8         enSessionType
);

VOS_VOID MTC_SetEndSessionInfo(
    TAF_CTRL_STRU                      *pstCtrl,
    MTC_SESSION_TYPE_ENUM_UINT8         enSessionType
);

VOS_VOID MTC_SetPowerSaveInfo(
    VOS_UINT32                          ulSndpid,
    TAF_MTC_POWER_SAVE_ENUM_UINT8       enPowerSaveStatus
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

