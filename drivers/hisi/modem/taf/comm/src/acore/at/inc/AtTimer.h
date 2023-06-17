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
#ifndef __AT_TIMER_H__
#define __AT_TIMER_H__


/*****************************************************************************
  1 ??????????
*****************************************************************************/
#include  "vos.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 ??????
*****************************************************************************/


/*****************************************************************************
  3 ????????
*****************************************************************************/

/*****************************************************************************
 ??????    : AT_TIMER_OPERATION_TYPE_ENUM
 ????????  : AT????????????????

  1.??    ??   : 2011??10??24??
    ??    ??   : ????/l60609
    ????????   : AT Project????AT TIMER????????????????
*****************************************************************************/
enum AT_TIMER_OPERATION_TYPE_ENUM
{
    AT_TIMER_OPERATION_START,
    AT_TIMER_OPERATION_STOP
};
typedef VOS_UINT32  AT_TIMER_OPERATION_TYPE_ENUM_UINT32;

/*****************************************************************************
 ??????    : AT_TIMER_STATUS_ENUM
 ????????  : AT??????????

  1.??    ??   : 2013??9??23??
    ??    ??   : A00165503
    ????????   : ????????
*****************************************************************************/
enum AT_TIMER_STATUS_ENUM
{
    AT_TIMER_STATUS_STOP,               /* ?????????????? */
    AT_TIMER_STATUS_RUNNING,            /* ?????????????? */

    AT_TIMER_STATUS_BUTT
};
typedef VOS_UINT32 AT_TIMER_STATUS_ENUM_UINT32;


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
 ??????    : AT_TIMER_OPERATION_STRU
 ????????  : AT??????????????????????SDT??????

  1.??    ??   : 2011??10??24??
    ??    ??   : ????/l60609
    ????????   : AT Project????AT TIMER????????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulTimeLen;
    AT_TIMER_OPERATION_TYPE_ENUM_UINT32 enTimeAction;
}AT_TIMER_OPERATION_STRU;


/*****************************************************************************
  8 UNION????
*****************************************************************************/


/*****************************************************************************
  9 OTHERS????
*****************************************************************************/


/*****************************************************************************
  10 ????????
*****************************************************************************/
VOS_UINT32 AT_StopRelTimer(
    VOS_UINT32                          ulName,
    HTIMER                             *phTm
);

VOS_UINT32 At_StartTimer(
    VOS_UINT32                          usLength,
    VOS_UINT8                           ucIndex
);

VOS_UINT32 AT_StartRelTimer(
    HTIMER                             *phTm,
    VOS_UINT32                          ulLength,
    VOS_UINT32                          ulName,
    VOS_UINT32                          ulParam,
    VOS_UINT8                           ucMode
);


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of AtTimer.h */

