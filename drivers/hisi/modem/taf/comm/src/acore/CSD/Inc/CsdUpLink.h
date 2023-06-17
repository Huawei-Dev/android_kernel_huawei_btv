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
#ifndef _CSD_UP_LINK_H_
#define _CSD_UP_LINK_H_


/*****************************************************************************
  1 ??????????????
*****************************************************************************/
#include  "CsdCtx.h"
#include  "CsdCstInterface.h"
#include  "mdrv.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

#if(FEATURE_ON == FEATURE_CSD)
/*****************************************************************************
  2 ??????
*****************************************************************************/
/*????????DICC??????????????????*/
#define CSD_MAX_SLICE_CNT               (0xFFFFFFFF)

/*????DICC????????????*/
#define CSD_TEN_MILLISECOND             ((10) * (32))

/*??????????????????????????*/
#define CSD_UL_TASK_DELAY_TIME          (1)

/* ??????????????DICC???????????? */
#define CSD_UL_MAX_SEND_CNT             (50)

/*****************************************************************************
  3 ????????
*****************************************************************************/
/*****************************************************************************
??????   : AT_CSD_CALL_STATE_TYPE_ENUM
???????? : ????????????

  1.??    ??   : 2011??12??6??
    ??    ??   : w00199382
    ????????   : ????????
*****************************************************************************/
enum CSD_UL_SEND_DATA_STATE_ENUM
{
    CSD_UL_SEND_DATA_CONTINUE           = 0X0001,                               /*??????????????????????????????????*/
    CSD_UL_SEND_DATA_NOT_CONTINUE               ,                               /*????????????????????????????????????*/
    CSD_UL_SEND_DATA_NOT_STATE_BUTT
};
typedef VOS_UINT16 CSD_UL_SEND_DATA_STATE_ENUM_UINT16;

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

VOS_UINT32 CSD_UL_InitQueue(VOS_VOID);
VOS_UINT32 CSD_UL_InsertQueue(IMM_ZC_STRU *pstULData);
VOS_VOID CSD_UL_ProcDataTask(VOS_VOID);
VOS_VOID CSD_UL_ProcMsg(MsgBlock* pMsg);
VOS_VOID CSD_UL_RcvAtMsg(MsgBlock* pMsg);
VOS_UINT32 CSD_UL_RcvAtCallStateInd(MsgBlock* pMsg);

VOS_UINT32 CSD_UL_BuildDiccInsertData(
    IMM_ZC_HEAD_STRU                   *pstUlQueue,
    CSD_CST_DATA_REQ_STRU              *pstULData,
    DICC_INSERT_DSCP_BLK_STRU          *pstDiccInsertData
);






#endif/*FEATURE_CSD*/


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

