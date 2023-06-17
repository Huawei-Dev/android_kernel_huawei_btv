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


#ifndef __VCCODECINTERFACE_H__
#define __VCCODECINTERFACE_H__

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
#define VC_VOICE_MAX_MSD_LEN (140)                                              /* ECALL??????????(MSD)?????????? ????:byte */

/*****************************************************************************
  3 ????????
*****************************************************************************/
enum VC_VOICE_MSG_ID_ENUM
{
    /*  ARM->HIFI */
    ID_VC_VOICE_BASE            = 0x9400,
    ID_VC_VOICE_START_REQ       = 0x9402,       /*????????????*/                /* _H2ASN_MsgChoice VCVOICE_START_REQ_STRU */
    ID_VC_VOICE_STOP_REQ        = 0x9403,       /*????????????????*/            /* _H2ASN_MsgChoice VCVOICE_STOP_REQ_STRU */
    ID_VC_VOICE_SET_DEVICE_REQ  = 0x9404,       /*????????????????*/            /* _H2ASN_MsgChoice VCVOICE_SET_DEVICE_REQ_STRU */
    ID_VC_VOICE_SET_VOLUME_REQ  = 0x9405,       /*????????????????*/            /* _H2ASN_MsgChoice VCVOICE_SET_VOLUME_REQ_STRU */
    ID_VC_VOICE_SET_CODEC_REQ   = 0x9407,       /*??????????????????*/          /* _H2ASN_MsgChoice VCVOICE_SET_CODEC_REQ_STRU */
    ID_VC_VOICE_FOREGROUND_REQ  = 0x940A,       /*??????????????*/              /* _H2ASN_MsgChoice VCVOICE_FOREGROUND_REQ_STRU */
    ID_VC_VOICE_BACKGROUND_REQ  = 0x940B,       /*??????????????*/              /* _H2ASN_MsgChoice VCVOICE_BACKGROUND_REQ_STRU */
    ID_VC_VOICE_GROUND_QRY      = 0x940C,       /*???????????? */               /* _H2ASN_MsgChoice VCVOICE_GROUND_QRY_STRU */
    /* Added by z60575 for VOICE_LOOP, 2013-7-2 begin */
    ID_VC_VOICE_LOOP_REQ        = 0x940D,       /* ???????? */                  /* _H2ASN_MsgChoice VCVOICE_LOOP_REQ_STRU */
    /* Added by z60575 for VOICE_LOOP, 2013-7-2 end */
    ID_VC_VOICE_SET_MSD_REQ             = 0x940E,       /*ECAL????????????*/            /* _H2ASN_MsgChoice VCVOICE_SET_MSD_REQ_STRU */
    ID_VC_VOICE_SET_ECALLCFG_REQ        = 0x940F,       /*ECAL????????????*/            /* _H2ASN_MsgChoice VCVOICE_SET_ECALLCFG_REQ_STRU */
    ID_VC_VOICE_SO_CTRL_ORDER_IND   = 0x9415,       /*CDMA??????SO????????????*/    /* _H2ASN_MsgChoice VCVOICE_SO_CTRL_ORDER_IND_STRU */
    ID_VC_VOICE_SO_CTRL_MSG_IND     = 0x9416,       /*CDMA??????SO????????????*/    /* _H2ASN_MsgChoice VCVOICE_SO_CTRL_MSG_IND_STRU */
//    ID_VC_VOICE_SO_CTRL_SEND_SPECIAL_PACKETS = 0x9417,  /*VC????conversation????????????????????????????????????????????????????*/
    ID_VC_VOICE_SET_TTYMODE_IND = 0x9440,       /* ??????????????VOICE????TTY???? */    /* _H2ASN_MsgChoice VCVOICE_SET_TTYMODE_IND_STRU */

    /*  HIFI->ARM */
    ID_VOICE_VC_BASE            = 0x4900,
    ID_VOICE_VC_START_CNF       = 0x4902,       /*????VC_VOICE_START_REQ*/      /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */
    ID_VOICE_VC_STOP_CNF        = 0x4903,       /*????VC_VOICE_STOP_REQ*/       /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */
    ID_VOICE_VC_SET_DEVICE_CNF  = 0x4904,       /*????VC_VOICE_SET_DEVICE_REQ*/ /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */
    ID_VOICE_VC_SET_VOLUME_CNF  = 0x4905,       /*????VC_VOICE_SET_VOLUME_REQ*/ /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */
    ID_VOICE_VC_SET_CODEC_CNF   = 0x4907,       /*????VC_VOICE_SET_CODEC_REQ*/  /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */
    ID_VOICE_VC_FOREGROUND_CNF  = 0x490A,       /*????VC_VOICE_FOREGROUND_REQ*/ /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */
    ID_VOICE_VC_BACKGROUND_CNF  = 0x490B,       /*????VC_VOICE_BACKGROUND_REQ*/ /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */
    ID_VOICE_VC_GROUND_RSP      = 0x490C,       /*????VC_VOICE_GROUND_QRY*/     /* _H2ASN_MsgChoice VCVOICE_GROUND_RSP_STRU */
    /* Added by z60575 for VOICE_LOOP, 2013-7-2 begin */
    ID_VOICE_VC_LOOP_CNF        = 0x490D,       /* ???????????? */              /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */
    /* Added by z60575 for VOICE_LOOP, 2013-7-2 end */
    ID_VOICE_VC_SET_ECALLCFG_CNF        = 0x490F,      /*????ID_VC_VOICE_SET_ECALLCFG_REQ*/ /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */
    ID_VOICE_VC_ECALL_TRANS_STATUS_NTF  = 0x4910,      /*????ECALL????????*/           /* _H2ASN_MsgChoice VCVOICE_ECALL_TRANS_STATUS_NTF_STRU */
    ID_VOICE_VC_START_SEND_MSD_IND      = 0x4930,      /*????NAS????????MSD????*/           /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */

    ID_VOICE_VC_DTMF_IND                = 0x4911,       /* ????????DTMF???????????? */              /* _H2ASN_MsgChoice VOICEVC_DTMF_IND_STRU */
    ID_VOICE_VC_AL_ACK_REPORT_IND       = 0x4914,

    /* CODEC->CODEC */
    ID_VOICE_VOICE_ECALL_UPDATE_IND     = 0xDD0A,      /*Ecall????????*/                     /* _H2ASN_MsgChoice VOICE_VOICE_ECALL_UPDATE_IND_STRU */
    ID_VOICE_VOICE_ECALL_PULLSTART_IND  = 0xDD0B,      /*Ecall????????Ecall????????MSD????*/ /* _H2ASN_MsgChoice VOICE_VOICE_ECALL_PULLSTART_IND_STRU */

    VC_VOICE_MSG_ID_BUTT
};
typedef VOS_UINT16 VC_VOICE_MSG_ID_ENUM_UINT16;


enum VC_VOICE_DTMF_MSG_ID_ENUM
{
    ID_VC_VOICE_DTMF_BASE               = 0x9420,
    ID_VC_VOICE_START_DTMF_REQ          = 0x9421,       /* VC????VOICE????DTMF?????????? */ /* _H2ASN_MsgChoice VCVOICE_START_DTMF_REQ_STRU */
    ID_VOICE_VC_START_DTMF_CNF          = 0x4921,       /* ????VC_VOICE_START_DTMF_REQ*/      /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */
    ID_VOICE_VC_DTMF_OVER_IND           = 0x4922,       /* VOICE????VC??????DTMF????????*/    /* _H2ASN_MsgChoice VOICEVC_DTMF_OVER_IND_STRU */
    ID_VC_VOICE_STOP_DTMF_REQ           = 0x9423,       /* VC????VOICE????DTMF??????????*/    /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */
    ID_VOICE_VC_STOP_DTMF_CNF           = 0x4923,       /* ????ID_VC_VOICE_STOP_DTMF_REQ*/  /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */
    ID_VC_VOICE_SET_DTMF_DETECT_REQ     = 0x9424,       /* ????ID_VC_VOICE_SET_DTMF_DETECT_REQ*/  /* _H2ASN_MsgChoice VC_VOICE_DTMF_DETECT_REQ_STRU */
    ID_VOICE_VC_SET_DTMF_DETECT_CNF     = 0x4924,       /* ????ID_VOICE_VC_SET_DTMF_DETECT_CNF*/  /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */
    ID_VC_VOICE_DTMF_MSG_ID_MAX,
};
typedef VOS_UINT16 VC_VOICE_DTMF_MSG_ID_ENUM_UINT16;


enum VCVOICE_NET_MODE_ENUM
{
    VCVOICE_NET_MODE_GSM         = 0,
    VCVOICE_NET_MODE_WCDMA,
    VCVOICE_NET_MODE_TDSCDMA,
    VCVOICE_NET_MODE_IMS_EUTRAN,
    VCVOICE_NET_MODE_CDMA,
    VCVOICE_NET_MODE_WIFI,
    VCVOICE_NET_MODE_BUTT
};
typedef VOS_UINT16 VCVOICE_NET_MODE_ENUM_UINT16;

enum VCVOICE_TYPE_ENUM
{
    VCVOICE_TYPE_AMR      = 0,                                                  /* amr */
    VCVOICE_TYPE_EFR,                                                           /* enhanced full rate */
    VCVOICE_TYPE_FR,                                                            /* full rate */
    VCVOICE_TYPE_HR,                                                            /* half rate */
    VCVOICE_TYPE_AMR2,                                                          /* amr2 */
    VCVOICE_TYPE_AMRWB,                                                         /* AMR-WB */
    VCVOICE_TYPE_G711,                                                          /* G711 */
    VCVOICE_TYPE_EVRC,                                                          /* EVRC */
    VCVOICE_TYPE_EVRCB,                                                         /* EVRCB */
    VCVOICE_TYPE_BUTT                                                           /* invalid value */
};
typedef VOS_UINT16  VCVOICE_TYPE_ENUM_UINT16;

enum VCVOICE_EXECUTE_RSLT_ENUM
{
    VCVOICE_EXECUTE_RSLT_SUCC = 0,                                              /* 0 ???? */
    VCVOICE_EXECUTE_RSLT_FAIL,                                                  /* 1 ???? */
    VCVOICE_EXECUTE_RSLT_NULL_PTR,                                              /* 2 ?????? */
    VCVOICE_EXECUTE_RSLT_PARA_ERR,                                              /* 3 ???????? */
    VCVOICE_EXECUTE_RSLT_STATE_ERR,                                             /* 4 ???????? */
    VCVOICE_EXECUTE_RSLT_UNKNOWN_MSG,                                           /* 5 ???????? */

    VCVOICE_EXECUTE_RSLT_BUTT
};
typedef VOS_UINT16  VCVOICE_EXECUTE_RSLT_ENUM_UINT16;

enum VCVOICE_VOLUME_TARGET_ENUM
{
    VCVOICE_VOLUME_TARGET_UP = 0,                                               /* 0 ???? */
    VCVOICE_VOLUME_TARGET_DOWN,                                                 /* 1 ???? */

    VCVOICE_VOLUME_TARGET_BUTT
};
typedef VOS_UINT16  VCVOICE_VOLUME_TARGET_ENUM_UINT16;

enum VCVOICE_WORK_TYPE_ENUM
{
    VCVOICE_WORK_TYPE_NORMAL = 0,                                               /* 0 ???????????? */
    VCVOICE_WORK_TYPE_TEST,                                                     /* 1 ???????? */
    VCVOICE_WORK_TYPE_ECALL,                                                    /* 2 ECALL???? */
    VCVOICE_WORK_TYPE_TTY_FULL,                                                 /* 3 TTY FULL???? */
    VCVOICE_WORK_TYPE_TTY_VCO,                                                  /* 4 TTY VCO???? */
    VCVOICE_WORK_TYPE_TTY_HCO,                                                  /* 5 TTY HCO???? */
    VCVOICE_WORK_TYPE_BUTT
};
typedef VOS_UINT16  VCVOICE_WORK_TYPE_ENUM_UINT16;

/* ???????????? */
enum VCVOICE_DEV_MODE_ENUM
{
    VCVOICE_DEV_MODE_HANDSET                = 0,                                /* ???????? */
    VCVOICE_DEV_MODE_HANDFREE,                                                  /* ???????? */
    VCVOICE_DEV_MODE_CARFREE,                                                   /* ???????????? */
    VCVOICE_DEV_MODE_HEADSET,                                                   /* ???????? */
    VCVOICE_DEV_MODE_BLUETOOTH,                                                 /* ???????? */
    VCVOICE_DEV_MODE_PCVOICE,                                                   /* PC-VOICE???? */
    VCVOICE_DEV_MODE_HEADPHONE,                                                 /* ????????MIC?????????? */
    VCVOICE_DEV_MODE_SUPER_HANDFREE,                                            /* ???????? */
    VCVOICE_DEV_MODE_SMART_TALK,                                                /* ???????? */
    VCVOICE_DEV_MODE_USBVOICE,
    VCVOICE_DEV_MODE_BUTT
};
typedef VOS_UINT16  VCVOICE_DEV_MODE_ENUM_UINT16;

/* ???????? */
enum VCVOICE_GROUND_ENUM
{
    VCVOICE_GROUND_FOREGROUND               = 0,                                /* ???????? */
    VCVOICE_GROUND_BACKGROUND,                                                  /* ???????? */
    VCVOICE_GROUND_INVALID,                                                     /* ???? */
    VCVOICE_GROUND_BUTT
};
typedef VOS_UINT16  VCVOICE_GROUND_ENUM_UINT16;

/* Added by z60575 for VOICE_LOOP, 2013-7-2 begin */
/* ???????? */
enum VCVOICE_LOOP_ENUM
{
    VCVOICE_LOOP_STOP                       = 0,                                /* ???????????? */
    VCVOICE_LOOP_START,                                                         /* ???????????? */
    VCVOICE_LOOP_BUTT
};
typedef VOS_UINT16  VCVOICE_LOOP_ENUM_UINT16;
/* Added by z60575 for VOICE_LOOP, 2013-7-2 end */

enum VCVOICE_ECALL_TRANS_STATUS_ENUM
{
    VCVOICE_ECALL_MSD_TRANSMITTING_START,                                      /* ????MSD???????????????? */
    VCVOICE_ECALL_MSD_TRANSMITTING_SUCCESS,                                    /* ????MSD???????????????? */
    VCVOICE_ECALL_MSD_TRANSMITTING_FAIL,                                       /* ????MSD???????????????? */
    VCVOICE_ECALL_PSAP_MSD_REQUIRETRANSMITTING,                                /* PSAP????????MSD???? */
    VCVOICE_ECALL_MSD_TRANSMITTING_STOP,                                       /* ????MSD???????????????? */
    VCVOICE_ECALL_TRANS_STATUS_BUTT
};
typedef VOS_UINT8  VCVOICE_ECALL_TRANS_STATUS_ENUM_UINT8;

enum VCVOICE_ECALL_TRANS_FAIL_CAUSE_ENUM
{
    VCVOICE_ECALL_CAUSE_WAIT_PSAP_TIME_OUT,                                    /* ????PSAP?????????????? */
    VCVOICE_ECALL_CAUSE_MSD_TRANSMITTING_TIME_OUT,                             /* MSD???????????? */
    VCVOICE_ECALL_CAUSE_WAIT_AL_ACK_TIME_OUT,                                  /* ???????????????????? */
    VCVOICE_ECALL_CAUSE_UNSPECIFIC_ERROR,                                      /* ???????????? */
    VCVOICE_ECALL_CAUSE_BUTT
};
typedef VOS_UINT8  VCVOICE_ECALL_TRANS_FAIL_CAUSE_ENUM_UINT8;

enum VCVOICE_ECALL_MSD_MODE_ENUM
{
    VCVOICE_ECALL_MSD_MODE_TRANSPARENT,                                         /* MSD??????????????*/
    VCVOICE_ECALL_MSD_MODE_BUTT
};
typedef VOS_UINT16  VCVOICE_ECALL_MSD_MODE_ENUM_UINT16;

enum VCVOICE_ECALL_MSD_VOICE_ABANDON_ENUM
{
    VCVOICE_ECALL_MSD_VOICE_NOT_ABANDON,                                        /* MSD????????????????????*/
    VCVOICE_ECALL_MSD_VOICE_ABANDON,                                            /* MSD??????????????????????*/
    VCVOICE_ECALL_MSD_VOICE_BUTT
};
typedef VOS_UINT16  VCVOICE_ECALL_MSD_VOICE_ABANDON_ENUM_UINT16;

/* CDMA????????????????????ORDQ??????3??bit */
enum VCVOICE_ORDQ_3MSBS_ENUM
{
    VCVOICE_ORDQ_ZERO = 0,                              /* ?????????????? */
    VCVOICE_ORDQ_FOURTH,                                /* ????????4???????????????????????????????? */
    VCVOICE_ORDQ_HALF,                                  /* ????????2?????????????????????????????? */
    VCVOICE_ORDQ_THREE_FOURTHS,                         /* ????????4??????????????3?????????????? */
    VCVOICE_ORDQ_FULL,                                  /* ????????????????????????????*/
    VCVOICE_ORDQ_BUTT
};
typedef VOS_UINT8 VCVOICE_ORDQ_3MSBS_ENUM_UINT8;

/* CDMA?????????????????? */
enum VCVOICE_EVRC_RATE_REDUC_ENUM
{
    VCVOICE_EVRC_RATE_REDUC_ZERO = 0,                   /* ?????????????? */
    VCVOICE_EVRC_RATE_REDUC_FOURTH,                     /* ????????4???????????????????????????????? */
    VCVOICE_EVRC_RATE_REDUC_HALF,                       /* ????????2?????????????????????????????? */
    VCVOICE_EVRC_RATE_REDUC_THREE_FOURTHS,              /* ????????4??????????????3?????????????? */
    VCVOICE_EVRC_RATE_REDUC_FULL,                       /* ????????????????????????????*/
    VCVOICE_EVRC_RATE_REDUC_BUTT
};
typedef VOS_UINT8 VCVOICE_EVRC_RATE_REDUC_ENUM_UINT8;

/* CDMA?????????????????? */
enum VCVOICE_EVRCB_RATE_REDUC_ENUM
{
    VCVOICE_EVRCB_RATE_REDUC_830K = 0,                  /* ????????8.3kbps */
    VCVOICE_EVRCB_RATE_REDUC_757K = 1,
    VCVOICE_EVRCB_RATE_REDUC_664K = 2,
    VCVOICE_EVRCB_RATE_REDUC_618K = 3,
    VCVOICE_EVRCB_RATE_REDUC_582K = 4,
    VCVOICE_EVRCB_RATE_REDUC_545K = 5,
    VCVOICE_EVRCB_RATE_REDUC_508K = 6,
    VCVOICE_EVRCB_RATE_REDUC_400K = 7,
    VCVOICE_EVRCB_RATE_REDUC_BUTT
};
typedef VOS_UINT8 VCVOICE_EVRCB_RATE_REDUC_ENUM_UINT8;

enum VCVOICE_MOBILE_TO_MOBILE_ENUM
{
    VCVOICE_MOBILE_TO_MOBILE_OFF = 0,
    VCVOICE_MOBILE_TO_MOBILE_ON  = 1,                   /* ????1??????????????????????1s */
    VCVOICE_MOBILE_TO_MOBILE_BUTT
};
typedef VOS_UINT8 VCVOICE_MOBILE_TO_MOBILE_ENUM_UINT8;

enum VCVOICE_INTI_CODEC_ENUM
{
    VCVOICE_INTI_CODEC_DISABLE = 0,
    VCVOICE_INTI_CODEC_ENABLE  = 1,                     /* ????1?????????????????? */
    VCVOICE_INTI_CODEC_BUTT
};
typedef VOS_UINT8 VCVOICE_INTI_CODEC_ENUM_UINT8;

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

/*****************************************************************************
 ??????    : VCCODEC_START_REQ_STRU
 ????????  :
 ASN.1???? :
 ????????  : ????????????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* ???????? */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve1;                             /* ???? */
    VCVOICE_NET_MODE_ENUM_UINT16        enMode;                                 /* ??????????????0 G??1 W */
    VCVOICE_TYPE_ENUM_UINT16            enCodecType;                            /* ????????????0 AMR??1 EFR??2 FR??3 HR??4 AMR2?? 5 AMRWB */
    VCVOICE_WORK_TYPE_ENUM_UINT16       enWorkType;                             /* ????????:0 ???????????? 1: ???????? */
    VOS_UINT16                          usReserve2;                             /* ???? */
}VCVOICE_START_REQ_STRU;


/*****************************************************************************
 ??????    : VCCODEC_STOP_REQ_STRU
 ????????  :
 ASN.1???? :
 ????????  : ????????????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* ???????? */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve;                              /* ???? */
}VCVOICE_STOP_REQ_STRU;


/*****************************************************************************
 ??????    : VCVOICE_SET_DEVICE_REQ_STRU
 ????????  :
 ASN.1???? :
 ????????  : ??????????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* ???????? */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve;                              /* ???? */
    VCVOICE_DEV_MODE_ENUM_UINT16        usDeviceMode;                           /* ??????????0 ??????1 ??????????2 ??????????3 ??????4 ?????? 5 PC-VOICE  */
    VOS_UINT16                          usReserve2;                             /* ???? */
}VCVOICE_SET_DEVICE_REQ_STRU;

/*****************************************************************************
 ??????    : VCCODEC_SET_VOLUME_REQ_STRU
 ????????  :
 ASN.1???? :
 ????????  : ????????????????????????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* ???????? */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve;                              /* ???? */
    VCVOICE_VOLUME_TARGET_ENUM_UINT16   enVolTarget;
    VOS_INT16                           sVolValue;
}VCVOICE_SET_VOLUME_REQ_STRU;

/*****************************************************************************
 ??????    : VCCODEC_SET_CODEC_REQ_STRU
 ????????  :
 ASN.1???? :
 ????????  : ??????????????????????????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* ???????? */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve;                              /* ???? */
    VCVOICE_NET_MODE_ENUM_UINT16        enMode;                                 /* ??????????????0 G??1 W */
    VCVOICE_TYPE_ENUM_UINT16            enCodecType;                            /* ????????????0 AMR??1 EFR??2 FR??3 HR; 4 AMR2; 5 AMRWB */
}VCVOICE_SET_CODEC_REQ_STRU;

/*****************************************************************************
 ??????    : VCVOICE_FOREGROUND_REQ_STRU
 ????????  :
 ASN.1???? :
 ????????  : VC????????MED??????????????, ??????????????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* ???????? */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve;                              /* ???? */
} VCVOICE_FOREGROUND_REQ_STRU;

/*****************************************************************************
 ??????    : VCVOICE_BACKGROUND_REQ_STRU
 ????????  :
 ASN.1???? :
 ????????  : VC????????MED????????????????????????????????????????????????????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* ???????? */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve;                              /* ???? */
} VCVOICE_BACKGROUND_REQ_STRU;

/*****************************************************************************
 ??????    : VCVOICE_GROUND_QRY_STRU
 ????????  :
 ASN.1???? :
 ????????  : VC????????????????????(????/????)
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* ???????? */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve;                              /* ???? */
} VCVOICE_GROUND_QRY_STRU;

/*****************************************************************************
 ??????    : VCVOICE_GROUND_RSP_STRU
 ????????  :
 ASN.1???? :
 ????????  : ????????????????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* ???????? */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve;                              /* ???? */
    VCVOICE_GROUND_ENUM_UINT16          enState;                                /* ???????? */
    VOS_UINT16                          usReserve2;                             /* ???? */
} VCVOICE_GROUND_RSP_STRU;

/*****************************************************************************
 ??????    : VCCODEC_OP_RSLT_STRU
 ????????  :
 ASN.1???? :
 ????????  : ??VC??????????????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* ???????? */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve1;                             /* ???? */
    VCVOICE_EXECUTE_RSLT_ENUM_UINT16    enExeRslt;                              /* ???????? */
    VOS_UINT16                          usReserve2;
}VCVOICE_OP_RSLT_STRU;

/* Added by z60575 for VOICE_LOOP, 2013-7-2 begin */
/*****************************************************************************
 ??????    : VCVOICE_LOOP_REQ_STRU
 ????????  :
 ASN.1???? :
 ????????  : ????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* ???????? */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve1;                             /* ???? */
    VCVOICE_LOOP_ENUM_UINT16            enMode;                                 /* ???????? */
    VOS_UINT16                          usReserve2;
}VCVOICE_LOOP_REQ_STRU;
/* Added by z60575 for VOICE_LOOP, 2013-7-2 end */

/*****************************************************************************
 ??????    : VOICEVC_DTMF_IND_STRU
 ????????  :
 ASN.1???? :
 ????????  : ????????????????DTMF????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* ???????? */ /*_H2ASN_Skip*/
    VOS_UINT16                          usDtmfCode;                             /* DTMF?????? */
} VOICEVC_DTMF_IND_STRU;

/*****************************************************************************
 ??????    : VC_VOICE_DTMF_DETECT_REQ_STRU
 ????????  :
 ASN.1???? :
 ????????  : ????????????????DTMF????????????
*****************************************************************************/
typedef struct {
    VOS_MSG_HEADER
    VOS_UINT16 usMessageId;
    VOS_UINT16 usReserve;
    VOS_UINT32 ulDtmfDetectOn;  /*0 off, 1 on */
}VC_VOICE_DTMF_DETECT_REQ_STRU;

/*****************************************************************************
 ??????    : VCVOICE_ECALL_TRANS_STATUS_NTF_STRU
 ????????  : MED????????VC????????????????
 1.??    ??   : 2014??3??23??
   ??    ??   : y00241934
   ????????   : ????????????eCall????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                                  usMsgName;                      /* ???????? */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usReserve1;                     /* ???? */
    VCVOICE_ECALL_TRANS_STATUS_ENUM_UINT8       enEcallTransStatus ;            /* ?????????????? */
    VCVOICE_ECALL_TRANS_FAIL_CAUSE_ENUM_UINT8   enEcallTransFailCause ;         /* ECALL?????????????? */
    VOS_UINT16                                  usReserve2;                     /* ???? */
    VOS_UINT32                                  ulTimeWindow;                   /* ???????????? */
}VCVOICE_ECALL_TRANS_STATUS_NTF_STRU;

/*****************************************************************************
 ??????    : VCVOICE_SET_MSD_REQ_STRU
 ????????  : VC??????????????????MSD??????????MED
 1.??    ??   : 2014??3??23??
   ??    ??   : y00241934
   ????????   : ????????????eCall????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                                  usMsgName;                      /* ???????? */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usReserve1;                     /* ???? */
    VOS_UINT32                                  ulMsdLen ;                      /* MSD?????????? */
    VOS_UINT8                                   aucMsd[VC_VOICE_MAX_MSD_LEN];   /* MSD???????? */
} VCVOICE_SET_MSD_REQ_STRU;

/*****************************************************************************
 ??????    : VCVOICE_SET_ECALLCFG_REQ_STRU
 ????????  : VC??????????????????ECALL??????????MED
 1.??    ??   : 2014??3??24??
   ??    ??   : y00241934
   ????????   : ????????????eCall????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                                  usMsgName;                      /* ???????? */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usReserve1;                     /* ???? */
    VCVOICE_ECALL_MSD_MODE_ENUM_UINT16          enMsdMode;                      /* ????????MSD???????? 0:???? */
    VCVOICE_ECALL_MSD_VOICE_ABANDON_ENUM_UINT16 enNoVoice;                      /* MSD???????????????????????????? 0:?????? 1:?????? */
} VCVOICE_SET_ECALLCFG_REQ_STRU;

/*****************************************************************************
 ??????    : VOICE_VOICE_ECALL_UPDATE_IND_STRU
 ????????  : ECALL????????
 1.??    ??   : 2014??3??23??
   ??    ??   : y00241934
   ????????   : ????????????eCall????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                                  usMsgName;                      /* ???????? */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usReserve1;                     /* ???? */
    VCVOICE_ECALL_TRANS_STATUS_ENUM_UINT8       enEcallTransStatus ;            /* ?????????????? */
    VCVOICE_ECALL_TRANS_FAIL_CAUSE_ENUM_UINT8   enEcallTransFailCause ;         /* ECALL?????????????? */
    VOS_UINT8                                   aucReserve2[2];                 /* ???? */
}VOICE_VOICE_ECALL_UPDATE_IND_STRU;

/*****************************************************************************
 ????????  : VOICE_VOICE_ECALL_PULLSTART_IND_STRU
 ????????  : ????????MSD????????eCall
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* ???????? */ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserved;
}VOICE_VOICE_ECALL_PULLSTART_IND_STRU;

/*****************************************************************************
 ??????    : VOICEVC_AL_ACK_REPORT_IND_STRU
 ????????  : ECALL AL ACK????
 1.??    ??   : 2014??3??23??
   ??    ??   : y00241934
   ????????   : ????????????eCall????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                                  usMsgName;                      /* ???????? */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usReserve1;                     /* ???? */
    VOS_UINT32                                  ulTimeStamp;
    VOS_UINT8                                   ucAlAckValue;
    VOS_UINT8                                   aucReserve2[3];
} VOICEVC_AL_ACK_REPORT_IND_STRU;


/*****************************************************************************
 ??????    : VCVOICE_SO_CTRL_ORDER_IND_STRU
 ????????  : ????C.S0014-D_v3.0_EVRC   2.2.2.1 ????
 ASN.1???? :
 ????????  : VC????????????Service Option Control Orders,
             ????????VOICE??????????????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                      usMsgName;                                  /* ???????? */ /*_H2ASN_Skip*/
    VCVOICE_TYPE_ENUM_UINT16        enCodecType;
    VOS_UINT8                       ucORDQ;
    VOS_UINT8                       ucReserve[3];                               /* ???? */
}VCVOICE_SO_CTRL_ORDER_IND_STRU;

/*****************************************************************************
 ??????    : SO_CTRL_MSG_CODEC_STRU
 ????????  : ????C.S0014-D_v3.0_EVRC   2.2.2.2??????2.4.1.2????
 ASN.1???? :
 ????????  :  ????????Service Option Control Messages????????????????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                  ucRateReduc;          /* ??????????EVRC:????0~4    EVRCB:????0~7 */
    VOS_UINT8                                  ucReserved;           /**/
    VCVOICE_MOBILE_TO_MOBILE_ENUM_UINT8        ucMobileToMobile;     /* ????1??????????????????????????????????????1s*/
    VCVOICE_INTI_CODEC_ENUM_UINT8              ucInitCodec;          /* ?????????????????? */
}SO_CTRL_MSG_CODEC_STRU;

/*****************************************************************************
 ??????    : VCVOICE_SO_CTRL_MSG_IND_STRU
 ????????  : ????C.S0014-D_v3.0_EVRC   2.2.2.2??????2.4.1.2????
 ASN.1???? :
 ????????  :  VC????????????Service Option Control Messages, ????????
              VOICE??????????????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                      usMsgName;                                  /* ???????? */ /*_H2ASN_Skip*/
    VCVOICE_TYPE_ENUM_UINT16        enCodecType;
    SO_CTRL_MSG_CODEC_STRU          stSoCtrlMsg;
}VCVOICE_SO_CTRL_MSG_IND_STRU;

/*****************************************************************************
 ??????    : VC_VOICE_START_DTMF_REQ_STRU
 ASN.1???? :
 ????????  : VC????VOICE????DTMF??????????
*****************************************************************************/
typedef struct{
    VOS_MSG_HEADER
    VOS_UINT16                      usMsgName;
    VOS_UINT16                      usDtmfCode;                     /*??????????*/
    VOS_UINT16                      usLocalPlayOn;                  /*????????????????????*/
    VOS_UINT16                      usInBand;                       /*????????????*/
    VOS_UINT16                      usDtmfTimeOn;                   /*??????????????:ms*/
    VOS_UINT16                      usDtmfTimeOff;                  /*??????????????:ms*/
}VCVOICE_START_DTMF_REQ_STRU;

/*****************************************************************************
 ??????    : VOICEVC_STOP_DTMF_IND_STRU
 ????????  :
 ASN.1???? :
 ????????  : VOICE????VC DTMF??????????????????
*****************************************************************************/
typedef struct {
    VOS_MSG_HEADER
    VOS_UINT16                      usMsgName;
    VOS_UINT16                      usReserve;
    VOS_UINT32                      ulResult;  /*0 success, others error code */
}VOICEVC_STOP_DTMF_IND_STRU;

/*****************************************************************************
 ??????    : VCVOICE_STOP_DTMF_REQ_STRU
 ????????  :
 ASN.1???? :
 ????????  : VC????VOICE????DTMF??????????
*****************************************************************************/
typedef struct {
    VOS_MSG_HEADER
    VOS_UINT16                      usMsgName;
    VOS_UINT16                      usReserve;
}VCVOICE_STOP_DTMF_REQ_STRU;

/*****************************************************************************
 ??????    : VOICEVC_DTMF_OVER_IND_STRU
 ????????  :
 ASN.1???? :
 ????????  : VOICE????VC??????DTMF??????????
*****************************************************************************/
typedef struct {
    VOS_MSG_HEADER
    VOS_UINT16                      usMsgName;
    VOS_UINT16                      usReserve;
    VOS_UINT32                      ulResult;  /*0 success, others error code */
}VOICEVC_DTMF_OVER_IND_STRU;

/*****************************************************************************
 ??????    : VCVOICE_SET_TTYMODE_IND_STRU
 ????????  :
 ASN.1???? :
 ????????  : ??????????VC????VOICE????TTY????
*****************************************************************************/
typedef struct {
    VOS_MSG_HEADER
    VC_VOICE_MSG_ID_ENUM_UINT16     usMsgName;
    VOS_UINT16                      usReserved1;
    VCVOICE_WORK_TYPE_ENUM_UINT16   enWorkType;                                 /* TTY????, 3: FULL 4: VCO 5: HCO*/
    VOS_UINT16                      usReserved2;
}VCVOICE_SET_TTYMODE_IND_STRU;


/*****************************************************************************
  8 UNION????
*****************************************************************************/


/*****************************************************************************
  9 OTHERS????
*****************************************************************************/
#if 0                                                       /* _H2ASN_Skip */

/*****************************************************************************
  H2ASN????????????????
*****************************************************************************/
/* ??????????????ASN????,????L????,??????V???? */
typedef struct
{
    VC_VOICE_MSG_ID_ENUM_UINT16         enMsgID;            /* _H2ASN_MsgChoice_Export VC_VOICE_MSG_ID_ENUM_UINT16 */

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          VC_VOICE_MSG_ID_ENUM_UINT16
    ****************************************************************************/
}VOICE_VC_TRACE_MSG_DATA;

/* ????????????*/
typedef struct
{
    VOS_UINT32 uwSenderCpuId;
    VOS_UINT32 uwSenderPid;
    VOS_UINT32 uwReceiverCpuId;
    VOS_UINT32 uwReceiverPid;
    VOS_UINT32 uwLength;
    VOICE_VC_TRACE_MSG_DATA               stMsgData;
}VoiceVcTrace_MSG;

#endif                                                     /* _H2ASN_Skip */

/*****************************************************************************
  10 ????????
*****************************************************************************/








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

#endif /* end of VcCodecInterface.h */
