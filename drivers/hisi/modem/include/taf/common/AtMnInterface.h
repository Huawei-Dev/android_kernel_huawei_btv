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

#ifndef  AT_MN_INTERFACE_H
#define  AT_MN_INTERFACE_H

/*****************************************************************************
  1 ??????????
*****************************************************************************/
#include "product_config.h"
#include "vos.h"
#include "PsTypeDef.h"
#include "PsCommonDef.h"
#include "v_msg.h"
#include "TafTypeDef.h"
#include "TafApi.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
  2 ????????
*****************************************************************************/
#define AT_MN_MSG_HEADER                VOS_MSG_HEADER\
                                        AT_MN_MSGTYPE_ENUM_UINT16 enMsgId;\
                                        VOS_UINT8 aucReserved[2];\
                                        AT_APPCTRL_STRU stAppCtrl;


/*****************************************************************************
  3 ????????
*****************************************************************************/
/* Added by f62575 for AT Project??2011-10-03,  Begin*/
/*****************************************************************************
 ??????    : MN_AT_MSGTYPE_ENUM
 ????????  : AT??MN????????????
 1.??    ??   : 2012??6??11??
   ??    ??   : w00166186
   ????????   : AT&T&DCM????
 2.??    ??   : 2013??07??22??
   ??    ??   : s00217060
   ????????   : VoLTE_PhaseI????
*****************************************************************************/
enum AT_MN_MSGTYPE_ENUM
{
    /* ???????? */                                          /*????ID*/          /* ???? */
    /* AT??CALL?????????? */
    MN_APP_MSG_CLASS_CALL                                   = TAF_CALL_APP_MSG_BASE,
    /* Added by f00179208 for AT Project??2011-10-14,  Begin*/
    /* ???????? */
    MN_CALL_APP_ORIG_REQ                                    = 0x0001,           /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */
    /* ???????? */
    MN_CALL_APP_END_REQ,                                                        /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */
    /* ???????? */
    MN_CALL_APP_ANSWER_REQ,                                                     /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */
    /* ????????DTMF */
    MN_CALL_APP_START_DTMF_REQ,                                                 /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */
    /* ????????DTMF */
    MN_CALL_APP_STOP_DTMF_REQ,                                                  /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */
    /* ???????????????????????? */
    MN_CALL_APP_SUPS_CMD_REQ,                                                   /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */
    /* ???????????? */
    MN_CALL_APP_GET_INFO_REQ,                                                   /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */
    /* ???????????? */
    MN_CALL_APP_GET_CDUR_REQ,                                                   /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */
    MN_CALL_APP_SET_UUSINFO_REQ,                                                /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */
    MN_CALL_APP_QRY_UUSINFO_REQ,                                                /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */
    MN_CALL_APP_SET_ALS_REQ,                                                    /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */
    MN_CALL_APP_QRY_ALS_REQ,                                                    /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */

    MN_CALL_APP_MAX_REQ,
    /* Added by f00179208 for AT Project??2011-10-14,  End */

    MN_CALL_APP_CUSTOM_ECC_NUM_REQ,                                             /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */

    ID_TAFAGENT_MN_GET_CALL_INFO_REQ,                                           /* TAFAGENT_>MN  ????????????????????*/

    MN_CALL_APP_CLPR_GET_REQ,                                                   /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */

    MN_CALL_APP_XLEMA_REQ,                                                      /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */

    /* Added by s00217060 for ????????AT??????????????C??, 2013-4-3, begin */
    MN_CALL_APP_SET_CSSN_REQ,                                                   /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */
    /* Added by s00217060 for ????????AT??????????????C??, 2013-4-3, end */

    /* Added by y00245242 for V3R3C60_eCall????, 2014-3-29, begin */
    MN_CALL_QRY_ECALL_INFO_REQ,                                                 /* _H2ASN_MsgChoice MN_CALL_QRY_ECALL_INFO_REQ_STRU */
    /* Added by y00245242 for V3R3C60_eCall????, 2014-3-29, end */

    /* Added by l60609 for CDMA 1X Iteration 2, 2014-9-3, begin */
    TAF_CALL_APP_SEND_FLASH_REQ,                                                /* _H2ASN_MsgChoice TAF_CALL_APP_SEND_FLASH_REQ_STRU*/
    /* Added by l60609 for CDMA 1X Iteration 2, 2014-9-3, end */

    /* Added by f279542 for CDMA 1X Iteration 4, 2014-11-10, begin */
    TAF_CALL_APP_SEND_BURST_DTMF_REQ,                                           /* _H2ASN_MsgChoice TAF_CALL_BURST_DTMF_REQ_MSG_STRU*/
    /* Added by f279542 for CDMA 1X Iteration 4, 2014-11-10, end */

    TAF_CALL_APP_SEND_CUSTOM_DIAL_REQ,

    MN_CALL_APP_CALL_MODIFY_REQ,                                                /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */
    MN_CALL_APP_CALL_ANSWER_REMOTE_MODIFY_REQ,                                  /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */

    TAF_CALL_APP_ECONF_DIAL_REQ,                                                /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */
    TAF_CALL_APP_GET_ECONF_CALLED_INFO_REQ,                                     /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */

    TAF_CALL_APP_SEND_CONT_DTMF_REQ,                                            /* _H2ASN_MsgChoice TAF_CALL_CONT_DTMF_REQ_MSG_STRU*/

    TAF_CALL_APP_SEND_CCLPR_REQ,                                                 /* _H2ASN_MsgChoice TAF_CALL_SND_CCLPR_REQ_MSG_STRU */

    TAF_CALL_APP_CCWAI_SET_REQ,

    /* AT??MSG?????????? */
    MN_APP_MSG_CLASS_MSG                                    = TAF_MSG_APP_MSG_BASE,
    MN_MSG_MSGTYPE_SEND_RPDATA_DIRECT                       = 0x1001,           /* _H2ASN_MsgChoice MN_MSG_SEND_PARM_STRU */
    MN_MSG_MSGTYPE_SEND_RPDATA_FROMMEM                      = 0x1002,           /* _H2ASN_MsgChoice MN_MSG_SEND_FROMMEM_PARM_STRU */
    MN_MSG_MSGTYPE_SEND_RPRPT                               = 0x1003,           /* _H2ASN_MsgChoice MN_MSG_SEND_ACK_PARM_STRU */
    MN_MSG_MSGTYPE_WRITE                                    = 0x1004,           /* _H2ASN_MsgChoice MN_MSG_WRITE_PARM_STRU */
    MN_MSG_MSGTYPE_READ                                     = 0x1005,           /* _H2ASN_MsgChoice MN_MSG_READ_PARM_STRU */
    MN_MSG_MSGTYPE_LIST                                     = 0x1006,           /* _H2ASN_MsgChoice MN_MSG_LIST_PARM_STRU */
    MN_MSG_MSGTYPE_DELETE                                   = 0x1007,           /* _H2ASN_MsgChoice MN_MSG_DELETE_PARAM_STRU */
    MN_MSG_MSGTYPE_DELETE_TEST                              = 0x1008,           /* _H2ASN_MsgChoice MN_MSG_MEM_STORE_ENUM_U8 */
    MN_MSG_MSGTYPE_WRITE_SRV_PARA                           = 0x1009,           /* _H2ASN_MsgChoice MN_MSG_WRITE_SRV_PARAM_STRU */
    MN_MSG_MSGTYPE_READ_SRV_PARA                            = 0x100a,           /* _H2ASN_MsgChoice MN_MSG_READ_COMM_PARAM_STRU */
    MN_MSG_MSGTYPE_DELETE_SRV_PARA                          = 0x100b,           /* _H2ASN_MsgChoice MN_MSG_DELETE_PARAM_STRU */
    MN_MSG_MSGTYPE_MODIFY_STATUS                            = 0x100c,           /* _H2ASN_MsgChoice MN_MSG_MODIFY_STATUS_PARM_STRU */
    MN_MSG_MSGTYPE_SET_RCVPATH                              = 0x100d,           /* _H2ASN_MsgChoice MN_MSG_SET_RCVMSG_PATH_PARM_STRU */
    MN_MSG_MSGTYPE_GET_RCVPATH                              = 0x100e,           /* _H2ASN_MsgChoice MN_MSG_GET_RCVMSG_PATH_PARM_STRU */
    MN_MSG_MSGTYPE_GET_STORAGESTATUS                        = 0x100f,           /* _H2ASN_MsgChoice MN_MSG_GET_STORAGE_STATUS_PARM_STRU */
    MN_MSG_MSGTYPE_READ_STARPT                              = 0x1010,           /* _H2ASN_MsgChoice MN_MSG_READ_COMM_PARAM_STRU */
    MN_MSG_MSGTYPE_DELETE_STARPT                            = 0x1011,           /* _H2ASN_MsgChoice MN_MSG_DELETE_PARAM_STRU */
    MN_MSG_MSGTYPE_GET_STARPT_FROMMOMSG                     = 0x1012,           /* _H2ASN_MsgChoice MN_MSG_SEND_PARM_STRU */
    MN_MSG_MSGTYPE_GET_MOMSG_FROMSTARPT                     = 0x1013,           /* _H2ASN_MsgChoice MN_MSG_SEND_PARM_STRU */
    MN_MSG_MSGTYPE_SET_MEMSTATUS                            = 0x1014,           /* _H2ASN_MsgChoice MN_MSG_SET_MEMSTATUS_PARM_STRU */
    MN_MSG_MSGTYPE_SET_RELAY_LINK_CTRL                      = 0x1015,           /* _H2ASN_MsgChoice MN_MSG_SET_LINK_CTRL_STRU */
    MN_MSG_MSGTYPE_GET_RELAY_LINK_CTRL                      = 0x1016,           /* _H2ASN_MsgChoice  */
    MN_MSG_MSGTYPE_STUB                                     = 0x1017,           /* _H2ASN_MsgChoice MN_MSG_STUB_MSG_STRU */
#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
    MN_MSG_MSGTYPE_GET_ALLCBMIDS                            = 0x1018,           /* _H2ASN_MsgChoice  */
    MN_MSG_MSGTYPE_ADD_CBMIDS                               = 0x1019,           /* _H2ASN_MsgChoice MN_MSG_CBMIR_LIST_STRU */
    MN_MSG_MSGTYPE_DELETE_CBMIDS                            = 0x101a,           /* _H2ASN_MsgChoice MN_MSG_CBMIR_LIST_STRU */
    MN_MSG_MSGTYPE_EMPTY_CBMIDS                             = 0x101b,           /* _H2ASN_MsgChoice  */
#endif

    MN_MSG_MSGTYPE_MAX,

    /* AT??SSA?????????? */
    MN_APP_MSG_CLASS_SSA                                    = TAF_SSA_APP_MSG_BASE,
/* Added by f62575 for SS FDN&Call Control, 2013-05-06, begin */
    /*????????????????????????????*/
    TAF_MSG_REGISTERSS_MSG,
    TAF_MSG_ERASESS_MSG,
    TAF_MSG_ACTIVATESS_MSG,
    TAF_MSG_DEACTIVATESS_MSG,
    TAF_MSG_INTERROGATESS_MSG,
    TAF_MSG_REGPWD_MSG,
    TAF_MSG_PROCESS_USS_MSG,
    TAF_MSG_ERASECCENTRY_MSG,
    /* Deleted by s00217060 for VoLTE_PhaseIII  ????, 2014-01-06, begin */
    /* Deleted by s00217060 for VoLTE_PhaseIII  ????, 2014-01-06, end */
    TAF_MSG_RLEASE_MSG,
    TAF_MSG_SET_USSDMODE_MSG,
/* Added by f62575 for SS FDN&Call Control, 2013-05-06, end */

    /* AT??MMA?????????? */
    MN_APP_MSG_CLASS_MMA                                    = TAF_MMA_APP_MSG_BASE,

    /* AT??MN???????????????????????????????????????????????? */
    MN_APP_MSG_CLASS_SET                                    = TAF_APP_SET_MSG_BASE,

    /* AT??MN???????????????????????????????????????????????? */
    MN_APP_MSG_CLASS_QRY                                    = TAF_APP_QRY_MSG_BASE,

    /* AT??PS?????????????? */
    MN_APP_MSG_CLASS_PS                                     = TAF_APS_MSG_BASE,

    /* Deleted by Y00213812 for VoLTE_PhaseI ????, 2013-6-29, begin */
    /* ??????????????????????TafAppAps.h?????? */
    /* Deleted by Y00213812 for VoLTE_PhaseI ????, 2013-6-29, end */


    MN_APP_MSG_CLASS_MASK                                   = TAF_IMSA_MSG_MASK
};
typedef VOS_UINT16 AT_MN_MSGTYPE_ENUM_UINT16;

typedef AT_MN_MSGTYPE_ENUM_UINT16 MN_MSG_MSGTYPE_ENUM_U16;

typedef VOS_UINT32  MN_CALL_APP_REQ_ENUM_UINT32;
/* Added by f62575 for AT Project??2011-10-03,  End*/

/*****************************************************************************
 ??????    : AT_CC_MSGTYPE_ENUM
 ????????  : AT??CC????????????
*****************************************************************************/
enum AT_CC_MSGTYPE_ENUM
{
    /* ???????? */                                          /*????ID*/          /* ???? */
    /* AT????CC?????? */
    AT_CC_MSG_STATE_QRY_REQ                                 = 0x0000,

    /* CC????AT?????? */
    AT_CC_MSG_STATE_QRY_CNF                                 = 0x0001,

    AT_CC_MSG_BUTT

 };
typedef VOS_UINT16 AT_CC_MSGTYPE_ENUM_UINT16;

/*****************************************************************************
  4 ??????
*****************************************************************************/
#define ECALL_MAX_DIAL_NUM_LEN               (18)

/*****************************************************************************
  5 STRUCT????
*****************************************************************************/
/*****************************************************************************
 ??????    : AT_APPCTRL_STRU
 ????????  : AT APP ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];
} AT_APPCTRL_STRU;

/* Added by f62575 for AT Project??2011-10-03,  Begin*/
/* MN????AT?????????? */
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT16                          usMsgName;                              /* _H2ASN_Skip *//* ????ID */
    VOS_UINT8                           aucReserved1[2];
    MN_CLIENT_ID_T                      clientId;
    VOS_UINT16                          usLen;
    VOS_UINT8                           aucContent[4];
}MN_AT_IND_EVT_STRU;

/*****************************************************************************
 ????????  : TAF_MNTN_LOG_PRINT_STRU
 ????????  : ????????LOG????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                           aucReserve[2];
    VOS_CHAR                            acLog[4];           /* ?????????? */
} TAF_MNTN_LOG_PRINT_STRU;


/*****************************************************************************
  H2ASN????????????????
*****************************************************************************/
typedef struct
{
    AT_MN_MSGTYPE_ENUM_UINT16           enMsgID;                                /*_H2ASN_MsgChoice_Export AT_MN_MSGTYPE_ENUM_U32*/
                                                                                /* ????????NAS??????????????????????ASN.1????AT_MN_MSGTYPE_ENUM_U32 */

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          AT_MN_MSGTYPE_ENUM_U32
    ****************************************************************************/
}AT_MN_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    AT_MN_MSG_DATA                      stMsgData;
}AtMnInterface_MSG;
/* Added by f62575 for AT Project??2011-10-03,  End*/

/*****************************************************************************
 ??????    : MN_APP_REQ_MSG_STRU
 ????????  : ????APP??????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgName;                              /* ?????? */
    VOS_UINT8                           aucReserve1[2];                             /* ???? */
    MN_CLIENT_ID_T                      clientId;                               /* Client ID */
    MN_OPERATION_ID_T                   opId;                                   /* Operation ID */
    VOS_UINT8                           aucReserve2[1];                         /* ???? */
    VOS_UINT8                           aucContent[4];                          /* ???????? */
} MN_APP_REQ_MSG_STRU;


/* Deleted by Y00213812 for VoLTE_PhaseI ????, 2013-07-08, begin */
/* Deleted by Y00213812 for VoLTE_PhaseI ????, 2013-07-08, end */



/*****************************************************************************
  6 ????????
*****************************************************************************/

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif


#endif /* end of AtMnInterface.h */
