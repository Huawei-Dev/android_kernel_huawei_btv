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

/*****************************************************************************
  1 ??????????
*****************************************************************************/
#ifndef _ATAPPVCOMINTERFACE_H_
#define _ATAPPVCOMINTERFACE_H_


/*****************************************************************************
  1 ??????????????
*****************************************************************************/
#include "vos.h"
#include "product_config.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 ??????
*****************************************************************************/
/*??????OM ??????????*/
#if (FEATURE_ON == FEATURE_VCOM_EXT)
#define APP_VCOM_DEV_INDEX_CBT            (APP_VCOM_DEV_INDEX_27)
#define APP_VCOM_DEV_INDEX_TLLOG          (APP_VCOM_DEV_INDEX_28)
#define APP_VCOM_DEV_INDEX_ERRLOG         (APP_VCOM_DEV_INDEX_29)
#define APP_VCOM_DEV_INDEX_LOG            (APP_VCOM_DEV_INDEX_30)
#define APP_VCOM_DEV_INDEX_LOG1           (APP_VCOM_DEV_INDEX_31)
#else
#define APP_VCOM_DEV_INDEX_CBT            (APP_VCOM_DEV_INDEX_BUTT)
#define APP_VCOM_DEV_INDEX_TLLOG          (APP_VCOM_DEV_INDEX_BUTT)
#define APP_VCOM_DEV_INDEX_ERRLOG         (APP_VCOM_DEV_INDEX_BUTT)
#define APP_VCOM_DEV_INDEX_LOG            (APP_VCOM_DEV_INDEX_BUTT)
#define APP_VCOM_DEV_INDEX_LOG1           (APP_VCOM_DEV_INDEX_BUTT)
#endif
/*****************************************************************************
  3 ????????
*****************************************************************************/

/*****************************************************************************
 ??????    : APP_VCOM_DEV_INDEX
 ????????  : APP VCOM ??????????????

 1.??    ??   : 2012??11??23??
   ??    ??   : z00220246
   ????????   : DSDA Phase I:
*****************************************************************************/
enum APP_VCOM_DEV_INDEX
{
    APP_VCOM_DEV_INDEX_0                 = 0,
    APP_VCOM_DEV_INDEX_1                 = 1,
#if (FEATURE_ON == FEATURE_VCOM_EXT)
    APP_VCOM_DEV_INDEX_2                 = 2,
    APP_VCOM_DEV_INDEX_3                 = 3,
    APP_VCOM_DEV_INDEX_4                 = 4,
    APP_VCOM_DEV_INDEX_5                 = 5,
    APP_VCOM_DEV_INDEX_6                 = 6,
    APP_VCOM_DEV_INDEX_7                 = 7,
    APP_VCOM_DEV_INDEX_8                 = 8,
    APP_VCOM_DEV_INDEX_9                 = 9,
    APP_VCOM_DEV_INDEX_10                = 10,
    APP_VCOM_DEV_INDEX_11                = 11,
    APP_VCOM_DEV_INDEX_12                = 12,
    APP_VCOM_DEV_INDEX_13                = 13,
    APP_VCOM_DEV_INDEX_14                = 14,
    APP_VCOM_DEV_INDEX_15                = 15,
    APP_VCOM_DEV_INDEX_16                = 16,
    APP_VCOM_DEV_INDEX_17                = 17,
    APP_VCOM_DEV_INDEX_18                = 18,
    APP_VCOM_DEV_INDEX_19                = 19,
    APP_VCOM_DEV_INDEX_20                = 20,
    APP_VCOM_DEV_INDEX_21                = 21,
    APP_VCOM_DEV_INDEX_22                = 22,
    APP_VCOM_DEV_INDEX_23                = 23,
    APP_VCOM_DEV_INDEX_24                = 24,
    APP_VCOM_DEV_INDEX_25                = 25,
    APP_VCOM_DEV_INDEX_26                = 26,
    APP_VCOM_DEV_INDEX_27                = 27,
    APP_VCOM_DEV_INDEX_28                = 28,
    APP_VCOM_DEV_INDEX_29                = 29,
    APP_VCOM_DEV_INDEX_30                = 30,
    APP_VCOM_DEV_INDEX_31                = 31,
#endif
    APP_VCOM_DEV_INDEX_BUTT
};
typedef VOS_UINT8 APP_VCOM_DEV_INDEX_UINT8;

enum APP_VCOM_EVT
{
    APP_VCOM_EVT_RELEASE   = 0,     /* ???????????? */
    APP_VCOM_EVT_OPEN      = 1,     /* ???????????? */
    APP_VCOM_EVT_BUTT
};
typedef VOS_UINT32 APP_VCOM_EVT_UINT32;
/*****************************************************************************
  2 ????????????
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
  8 UNION????
*****************************************************************************/

/*****************************************************************************
  9 OTHERS????
*****************************************************************************/

/*****************************************************************************
  10 ????????
*****************************************************************************/


typedef int (*SEND_UL_AT_FUNC)(VOS_UINT8 ucDevIndex, VOS_UINT8 *pData, VOS_UINT32 uslength);
typedef int (*EVENT_FUNC)(APP_VCOM_EVT_UINT32 event);

/*****************************************************************************
 ?? ?? ??  : APP_VCOM_RegDataCallback
 ????????  : ??????????????????????????????????????????API??????????
 ????????  : uPortNo??????????????
             pCallback????????????????
 ????????  : ????
 ?? ?? ??  : 0:  ??????????
             -1????????????
*****************************************************************************/
extern VOS_UINT32 APP_VCOM_RegDataCallback(VOS_UINT8 ucDevIndex, SEND_UL_AT_FUNC pFunc);
/*****************************************************************************
 ?? ?? ??  : APP_VCOM_RegEvtCallback
 ????????  : VCOM??????????????????????????????????????????
 ????????  : uPortNo??????????????
             pCallback????????????????
 ????????  : ????
 ?? ?? ??  : 0:  ??????????
             -1????????????
*****************************************************************************/
extern VOS_UINT32 APP_VCOM_RegEvtCallback(VOS_UINT8 ucDevIndex, EVENT_FUNC pFunc);
/*****************************************************************************
 ?? ?? ??  : APP_VCOM_Send
 ????????  : ??????????????????????????????????????????????????????????
              ??????????APP??
 ????????  : uPortNo??????????????????
             pData??????????????
             uslength??????????????
 ????????  : ????
 ?? ?? ??  : 0????????????
             ????????????????

*****************************************************************************/
extern VOS_UINT32 APP_VCOM_Send (VOS_UINT8 ucDevIndex, VOS_UINT8 *pData, VOS_UINT32 uslength);
#define APP_VCOM_SEND(ucDevIndex,pData,uslength) APP_VCOM_Send(ucDevIndex,pData,uslength)


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

