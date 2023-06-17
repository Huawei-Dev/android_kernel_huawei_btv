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

#ifndef __ADSNDINTERFACE_H__
#define __ADSNDINTERFACE_H__

/*****************************************************************************
  1 ??????????
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
/* !!!!!!!!!!!???????????????????????????? */
#define ADS_NDCLIENT_MSG_HDR            (0x00)
#define NDCLIENT_ADS_MSG_HDR            (0x00)


/*****************************************************************************
  3 ????????
*****************************************************************************/
/*****************************************************************************
??????    : ADS_NDCLIENT_ERR_TYPE_ENUM
????????  : ADS??NDCLIENT??????????

  1.??    ??   : 2011??12??6??
    ??    ??   : ????/l60609
    ????????   : ????ADS??NDCLIENT??????
*****************************************************************************/
enum ADS_NDCLIENT_MSG_ID_ENUM
{
    ID_ADS_NDCLIENT_DATA_IND                  =   ADS_NDCLIENT_MSG_HDR + 0x00,  /* ADS->NDCLIENT DATA IND */
    ID_ADS_NDCLIENT_ERR_IND                   =   ADS_NDCLIENT_MSG_HDR + 0x01,  /* ADS->NDCLIENT ERR IND */
    ID_ADS_NDCLIENT_MSG_ID_ENUM_BUTT
};
typedef VOS_UINT32  ADS_NDCLIENT_MSG_ID_ENUM_UINT32;

/*****************************************************************************
??????    : ADS_NDCLIENT_ERR_TYPE_ENUM
????????  : ADS??NDCLIENT??????????????

  1.??    ??   : 2011??12??6??
    ??    ??   : ????/l60609
    ????????   : ????ADS??NDCLIENT????????????????
*****************************************************************************/
enum ADS_NDCLIENT_ERR_TYPE_ENUM
{
    ADS_NDCLIENT_ERR_TYPE_MTU_OVERLONG      = 0x00,                             /* ??????????????MTU */
    ADS_NDCLIENT_ERR_TYPE_BUTT
};
typedef VOS_UINT8 ADS_NDCLIENT_ERR_TYPE_ENUM_UINT8;


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
??????    : ADS_NDCLIENT_ERR_IND_STRU
????????  : ADS??NDCLIENT??????????????????????
            ADS????????????????MTU????????????????????????IPv6????????
            ????????????????MTU??????ADS????ND CLIENT????????????
            ??ND CLIENT??????????????????????

  1.??    ??   : 2011??12??6??
    ??    ??   : ????/l60609
    ????????   : ????ADS??NDCLIENT??????????????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    ADS_NDCLIENT_MSG_ID_ENUM_UINT32     enMsgId;                                /*_H2ASN_Skip*/
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                           ucRabId;                                /* RAB??????????????:[5,15] */
    ADS_NDCLIENT_ERR_TYPE_ENUM_UINT8    enErrType;                              /*????????*/
    VOS_UINT16                          usLen;                                  /*??????????*/
    VOS_UINT8                           aucData[2];                             /*??????????*/ 
}ADS_NDCLIENT_ERR_IND_STRU;

/*****************************************************************************
??????    : ADS_NDCLIENT_DATA_IND_STRU
????????  : ADS??NDCLIENT??????????????????
            ????????????NDCLIENT??RA????ECHO REQUEST????????????IPF??????A CPU????
            ??ADS????????????????ND CLIENT??

  1.??    ??   : 2011??12??6??
    ??    ??   : ????/l60609
    ????????   : ????ADS??NDCLIENT??????????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    ADS_NDCLIENT_MSG_ID_ENUM_UINT32     enMsgId;                                /*_H2ASN_Skip*/
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                           ucRabId;                                /* RAB??????????????:[5,15] */
    VOS_UINT8                           aucRsv[1];                              /*??????*/
    VOS_UINT16                          usLen;                                  /*??????????*/
    VOS_UINT8                           aucData[2];                             /*??????????*/ 
}ADS_NDCLIENT_DATA_IND_STRU;


/*****************************************************************************
  8 UNION????
*****************************************************************************/


/*****************************************************************************
  9 OTHERS????
*****************************************************************************/

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

#endif

