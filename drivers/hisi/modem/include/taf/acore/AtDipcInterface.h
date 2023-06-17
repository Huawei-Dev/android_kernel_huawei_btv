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

#ifndef __ATDIPCINTERFACE_H__
#define __ATDIPCINTERFACE_H__


/*****************************************************************************
  1 ??????????????
*****************************************************************************/
#include "vos.h"
#include "product_config.h"
#include "mdrv.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)


/*****************************************************************************
  1 ??????????
*****************************************************************************/
/*****************************************************************************
??????    : AT_DIPC_MSG_TYPE_ENUM
????????  : AT??DIPC????PDP????????

  1.??    ??   : 2012??2??23??
    ??    ??   : L47619
    ????????   : V7R1C50 IPC????????
*****************************************************************************/
enum AT_DIPC_MSG_TYPE_ENUM
{
    ID_AT_DIPC_PDP_ACT_IND  = 0x00, /* _H2ASN_MsgChoice AT_DIPC_PDP_ACT_STRU*/   /*AT??DIPC????????PDP????????????ID*/
    ID_AT_DIPC_PDP_REL_IND  = 0x01, /* _H2ASN_MsgChoice AT_DIPC_PDP_DEACT_STRU*/ /*AT??DIPC????????PDP????????????ID*/

    ID_AT_DIPC_MSG_TYPE_BUTT
};
typedef VOS_UINT32 AT_DIPC_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
??????    : DIPC_BEARER_TYPE_ENUM
????????  : ????????

  1.??    ??   : 2012??12??10??
    ??    ??   : Y00213812
    ????????   : C50 IPv6 ????????
*****************************************************************************/
enum DIPC_BEARER_TYPE_ENUM
{
    DIPC_BEARER_TYPE_IPV4               = 0x01,
    DIPC_BEARER_TYPE_IPV6               = 0x02,
    DIPC_BEARER_TYPE_IPV4V6             = 0x03,

    DIPC_BEARER_TYPE_BUTT               = 0xFF
};
typedef VOS_UINT8 DIPC_BEARER_TYPE_ENUM_UINT8;

/*****************************************************************************
  2 ??????
*****************************************************************************/
#define MIN_RAB_ID              5
#define MAX_RAB_ID              15


/*****************************************************************************
  3 ????????
*****************************************************************************/

/*****************************************************************************
  4 ????????????
*****************************************************************************/

/*****************************************************************************
  6 ????????
*****************************************************************************/
/*****************************************************************************
??????    : AT_DIPC_PDP_ACT_STRU
????????  : AT??DIPC PDP ??????????

  1.??    ??   : 2012??2??24??
    ??    ??   : x59651
    ????????   : ????AT??DIPC PDP ??????????????????

  2.??    ??   : 2012??12??10??
    ??    ??   : Y00213812
    ????????   : C50 IPv6 ????????AT_DIPC_BEARER_TYPE_ENUM_UINT8
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                          /*_H2ASN_Skip*/
    AT_DIPC_MSG_TYPE_ENUM_UINT32        enMsgType;                          /*_H2ASN_Skip*/
    VOS_UINT8                           ucRabId;                            /* RAB??????????????:[5,15] */
    DIPC_BEARER_TYPE_ENUM_UINT8         enBearerType;
    VOS_UINT8                           aucRsv[2];
    UDI_DEVICE_ID_E                     enUdiDevId;                         /* ????ID????????????UDI_ACM_HSIC_ACM1_ID??UDI_ACM_HSIC_ACM3_ID??UDI_ACM_HSIC_ACM5_ID */
} AT_DIPC_PDP_ACT_STRU;

/*****************************************************************************
??????    : AT_DIPC_PDP_DEACT_STRU
????????  : AT??DIPC PDP ????????????

  1.??    ??   : 2012??2??24??
    ??    ??   : x59651
    ????????   : ????AT??DIPC PDP ????????????????????

  2.??    ??   : 2012??12??10??
    ??    ??   : Y00213812
    ????????   : C50 IPv6 ????????AT_DIPC_BEARER_TYPE_ENUM_UINT8
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                          /*_H2ASN_Skip*/
    AT_DIPC_MSG_TYPE_ENUM_UINT32        enMsgType;                          /*_H2ASN_Skip*/
    VOS_UINT8                           ucRabId;                            /* RAB??????????????:[5,15] */
    DIPC_BEARER_TYPE_ENUM_UINT8         enBearerType;
    VOS_UINT8                           aucRsv[2];
} AT_DIPC_PDP_DEACT_STRU;

/*****************************************************************************
  7 STRUCT????
*****************************************************************************/

/*****************************************************************************
  8 UNION????
*****************************************************************************/

/*****************************************************************************
  9 OTHERS????
*****************************************************************************/

/*****************************************************************************
  H2ASN????????????????
*****************************************************************************/
typedef struct
{
    AT_DIPC_MSG_TYPE_ENUM_UINT32        enMsgId;            /* _H2ASN_MsgChoice_Export AT_DIPC_MSG_TYPE_ENUM_UINT32 */
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          AT_DIPC_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
} AT_DIPC_INTERFACE_MSG_DATA;
/* _H2ASN_Length UINT32 */

typedef struct
{
    VOS_MSG_HEADER
    AT_DIPC_INTERFACE_MSG_DATA          stMsgData;
} AtDipcInterface_MSG;

/*****************************************************************************
  10 ????????
*****************************************************************************/

/*****************************************************************************
 ?? ?? ??  : DIPC_GetDevHandleByRabId
 ????????  : ????RabId????????????
 ????????  : VOS_UINT8 ucRabId  ??????????????????Rab Id

 ????????  : ??
 ?? ?? ??  : RabId??????????,????????UDI_INVALID_HANDLE
 ????????  :
 ????????  : Dipc_DlAdsDataRcv  ????????
             AT????             ????????API ??AT????

 ????????      :
  1.??    ??   : 2012??2??15??
    ??    ??   : x59651
    ????????   : ??????????

*****************************************************************************/
UDI_HANDLE  DIPC_GetDevHandleByRabId(VOS_UINT8 ucRabId);


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

#endif



