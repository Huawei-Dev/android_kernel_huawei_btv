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

#ifndef __PPP_INTERFACE_H__
#define __PPP_INTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/******************************************************************************
  1 ??????????????
******************************************************************************/
#include "vos.h"
#include "product_config.h"
#include "PsTypeDef.h"
#if (VOS_WIN32 == VOS_OS_VER) || (OSA_CPU_ACPU == VOS_OSA_CPU)
#include "ImmInterface.h"
#include "AdsDeviceInterface.h"
#endif
/******************************************************************************
  2 ??????
******************************************************************************/
/*??????????????PPP ID?????? */
#define PPP_MAX_ID_NUM                      (1)

/*RABID????*/
#define PPP_INVALID_RABID                   (0xFF)

/*PPPID*/
#define PPP_INVLAID_PPP_ID                  (0)


/*fanzhibin f49086 add it begin*/
#define AUTHLEN                             (100)    /* Size of authname/authkey(porting from BSD, not alter) */
#define PASSWORDLEN                         (100)    /* Size of authname/authkey(define by fanzhibin) */
#define CHAPCHALLENGELEN                    (48)     /* Maximum chap challenge(porting from BSD, not alter) */
#define MD5DIGESTSIZE                       (16)     /* MD5 (Message-Digest) hash size */
/*fanzhibin f49086 add it end*/

#define PPP_PAP_REQ_BUF_MAX_LEN             (PASSWORDLEN + AUTHLEN)

/* code(1B)+id(1B)+length(2B)+challenge_size(1B)+challenge+name */
#define PPP_CHAP_CHALLENGE_BUF_MAX_LEN      (1 + 1 + 2 + 1 + CHAPCHALLENGELEN + AUTHLEN)

/* code(1B)+id(1B)+length(2B)+response_size(1B)+response+name */
#define PPP_CHAP_RESPONSE_BUF_MAX_LEN       (1 + 1 + 2 + 1 + PASSWORDLEN + AUTHLEN)

#define PPP_AUTH_FRAME_BUF_MAX_LEN          (256)
#define PPP_IPCP_FRAME_BUF_MAX_LEN          (256)

/*??????????IP??????????????"."??16??????*/
#define PPP_IPV4_ADDR_STR_MAX_LEN           (16)

#ifndef IPV4_ADDR_LEN
#define   IPV4_ADDR_LEN                     (4)       /*IPV4????????*/
#endif

#ifndef IPV6_ADDR_LEN
#define   IPV6_ADDR_LEN                     (16)      /*IPV6????????*/
#endif

/******************************************************************************
  3 ????????
******************************************************************************/
enum PPP_AT_CTRL_OPER_TYPE_ENUM
{
    PPP_AT_CTRL_REL_PPP_REQ = 0,              /* ????IP????PPP???????? */
    PPP_AT_CTRL_REL_PPP_RAW_REQ = 1,          /* ????PPP????PPP???????? */
    PPP_AT_CTRL_HDLC_DISABLE = 2,             /* HDLC?????????????????? */
    PPP_AT_CTRL_CONFIG_INFO_IND = 3,          /* PDP???????? */

    PPP_AT_CTRL_BUTT
};
typedef VOS_UINT32  PPP_AT_CTRL_OPER_TYPE_ENUM_UINT32;

/******************************************************************************
  4 ????????????
******************************************************************************/


/******************************************************************************
  5 ??????????
******************************************************************************/


/******************************************************************************
  6 ????????
******************************************************************************/


/******************************************************************************
  7 STRUCT????
******************************************************************************/
#pragma pack(4)

typedef VOS_UINT16 PPP_ID;

/* ???????? */
enum PPP_AUTH_TYPE_ENUM
{
    PPP_NO_AUTH_TYPE                     = 0,
    PPP_PAP_AUTH_TYPE                    = 1,
    PPP_CHAP_AUTH_TYPE                   = 2,
    PPP_MS_CHAPV2_AUTH_TYPE              = 3,
    PPP_AUTH_TYPE_BUTT
};
typedef VOS_UINT8 PPP_AUTH_TYPE_ENUM_UINT8;

typedef struct
{
    VOS_UINT16  usPapReqLen;                    /*request????: 24.008??????[3,253]????*/
    VOS_UINT8   aucReserve[2];                  /* ???????? */
    VOS_UINT8  *pPapReq;                        /*request*/
} PPP_AUTH_PAP_CONTENT_STRU;

typedef struct
{
    VOS_UINT16  usChapChallengeLen;             /*challenge????: 24.008??????[3,253]????*/
    VOS_UINT16  usChapResponseLen;              /*response????: 24.008??????[3,253]????*/
    VOS_UINT8  *pChapChallenge;                 /*challenge*/
    VOS_UINT8  *pChapResponse;                  /*response*/
} PPP_AUTH_CHAP_CONTENT_STRU;

typedef struct
{
    PPP_AUTH_TYPE_ENUM_UINT8  ucAuthType;
    VOS_UINT8                 aucReserve[3];

    union
    {
        PPP_AUTH_PAP_CONTENT_STRU  PapContent;
        PPP_AUTH_CHAP_CONTENT_STRU ChapContent;
    } AuthContent;
} PPP_REQ_AUTH_CONFIG_INFO_STRU;

typedef struct
{
    VOS_UINT16  usIpcpLen;                      /*Ipcp??????*/
    VOS_UINT8   aucReserve[2];                  /* ???????? */
    VOS_UINT8  *pIpcp;                          /*Ipcp??*/
} PPP_REQ_IPCP_CONFIG_INFO_STRU;

typedef struct
{
    PPP_REQ_AUTH_CONFIG_INFO_STRU stAuth;
    PPP_REQ_IPCP_CONFIG_INFO_STRU stIPCP;
} PPP_REQ_CONFIG_INFO_STRU;

typedef struct
{
    VOS_UINT16  usAuthLen;                      /*??????????*/
    VOS_UINT16  usIpcpLen;                      /*Ipcp??????*/
    VOS_UINT8  *pAuth;                          /*??????*/
    VOS_UINT8  *pIpcp;                          /*Ipcp??*/
    VOS_UINT8   aucIpAddr[PPP_IPV4_ADDR_STR_MAX_LEN]; /*Ip????*/
} PPP_IND_CONFIG_INFO_STRU;


/* PPP??AT?????????????????? */
#define AT_PPP_RELEASE_IND_MSG          0x00    /* ????PDP?????????? */
#define AT_PPP_MODEM_MSC_IND_MSG        0x01    /* ??AT????????????????(??????????????????
                                                         ????????????AT????????????,??????PPP??AT??????????.) */
#define AT_PPP_PROTOCOL_REL_IND_MSG     0x02    /* PPP?????????????????? */

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucReserve[3];
}AT_PPP_RELEASE_IND_MSG_STRU;


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucDlci;
    VOS_UINT8                           aucMscInd[2];  /* ???????????? */
}AT_PPP_MODEM_MSC_IND_MSG_STRU;


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;
    VOS_UINT16                          usPppId;
    VOS_UINT8                           ucReserve[2];
}AT_PPP_PROTOCOL_REL_IND_MSG_STRU;


typedef VOS_VOID (*PPP_PULL_MSG_EVENT_CALLBACK)(VOS_UINT32 ulMsgCnt);

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

/******************************************************************************
  8 UNION????
******************************************************************************/


/******************************************************************************
  9 OTHERS????
******************************************************************************/


/******************************************************************************
  10 ????????
******************************************************************************/
/* PPP??????AT?????? */
extern VOS_UINT32 Ppp_CreatePppReq ( PPP_ID *pusPppId);
extern VOS_UINT32 Ppp_CreateRawDataPppReq ( PPP_ID *pusPppId);
extern VOS_UINT32 Ppp_ReleasePppReq ( PPP_ID usPppId);
extern VOS_UINT32 Ppp_ReleaseRawDataPppReq ( PPP_ID usPppId);
extern VOS_UINT32 PPP_RcvAtCtrlOperEvent(VOS_UINT16 usPppId, PPP_AT_CTRL_OPER_TYPE_ENUM_UINT32 ulCtrlOperType);
extern VOS_VOID   PPP_UpdateWinsConfig(VOS_UINT8 ucWins);
extern VOS_VOID   PPP_SetRawDataByPassMode(VOS_UINT32 ulRawDataByPassMode);

#if (VOS_WIN32 == VOS_OS_VER) || (OSA_CPU_ACPU == VOS_OSA_CPU)
/* IP???????????????????????????? */
extern VOS_UINT32 PPP_PullPacketEvent(VOS_UINT16 usPppId, IMM_ZC_STRU *pstImmZc);

/* IP???????????????????????????? */
extern VOS_UINT32 PPP_PushPacketEvent(VOS_UINT8 ucRabId, IMM_ZC_STRU *pstImmZc, ADS_PKT_TYPE_ENUM_UINT8 enPktType, VOS_UINT32 ulExParam);

/* PPP???????????????????????????? */
extern VOS_UINT32 PPP_PullRawDataEvent(VOS_UINT16 usPppId, IMM_ZC_STRU *pstImmZc);

/* PPP???????????????????????????? */
extern VOS_UINT32 PPP_PushRawDataEvent(VOS_UINT8 ucRabId, IMM_ZC_STRU *pstImmZc, ADS_PKT_TYPE_ENUM_UINT8 enPktType, VOS_UINT32 ulExParam);
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* PppInterface.h */

