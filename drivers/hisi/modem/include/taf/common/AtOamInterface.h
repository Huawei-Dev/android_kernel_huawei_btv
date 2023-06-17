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

#ifndef __ATOAMINTERFACE_H__
#define __ATOAMINTERFACE_H__

#include "v_msg.h"
#include "siapppih.h"
#include "siapppb.h"
#include "siappstk.h"
#include "MnClient.h"
#include "MnCallApi.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

enum AT_OAM_MSG_TYPE_ENUM
{
    STK_AT_DATAPRINT_CNF,
    
    STK_AT_EVENT_CNF,

    PIH_AT_EVENT_CNF,

    PB_AT_EVENT_CNF,

    AT_OAM_MSG_TYPE_BUTT
};
typedef VOS_UINT32 AT_OAM_MSG_TYPE_ENUM_UINT32;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    SI_PIH_EVENT_INFO_STRU              stPIHAtEvent;
} MN_APP_PIH_AT_CNF_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    SI_PB_EVENT_INFO_STRU               stPBAtEvent;
} MN_APP_PB_AT_CNF_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    SI_STK_PRINTDATA_CNF_STRU           stSTKAtPrint;
} MN_APP_STK_AT_DATAPRINT_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    SI_STK_EVENT_INFO_STRU              stSTKAtCnf;
} MN_APP_STK_AT_CNF_STRU;

extern VOS_UINT32 MMA_VerifyOperatorLockPwd(VOS_UINT8 *pucPwd);
extern VOS_UINT8 MMA_GetCurrentPhoneMode(VOS_VOID);
extern VOS_UINT32 MN_MSG_Decode_UsimMsg(
    VOS_UINT8                           *pucData,
    VOS_UINT32                          ulLen,
    MN_MSG_SUBMIT_LONG_STRU             *pstLongSubmit
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

#endif /* end of AtOamInterface.h */
