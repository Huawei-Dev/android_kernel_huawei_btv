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

#ifndef __DICC_INTERFACE_H__
#define __DICC_INTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "vos.h"
#include "PsTypeDef.h"
#if (VOS_OS_VER == VOS_WIN32)
#include "MemoryMap.h"
#endif
#if( FEATURE_ON == FEATURE_CSD )

#define DICC_MEM_START_PHY_ADDR                     (ECS_TTF_DICC_ADDR)


#define DICC_MEM_INIT_MAGIC_NUM_ADDR	(ECS_TTF_DICC_SPINLOCK_ADDR)

#define DICC_QUEUE_MEM_SIZE                         (ECS_TTF_DICC_SIZE)

#define DICC_INVALID_VALUE                          (0xFFFFFFFF)

#define DICC_INFO_BLOCK_MAX_LEN                     (16)
#define DICC_MAX_CHAN_NUM                           (DICC_CHAN_ID_BUTT)
#define DICC_PER_QUEUE_MAX_NODE_NUM                 (395+1)
#define DICC_BAT_OP_CNT                             (64)

#define DICC_CHAN_ID_UL_CSD_DATA_CHAN               (DICC_CHAN_ID_0)
#define DICC_CHAN_ID_UL_REL_DATA_CHAN               (DICC_CHAN_ID_1)
#define DICC_CHAN_ID_DL_CSD_DATA_CHAN               (DICC_CHAN_ID_2)
#define DICC_CHAN_ID_DL_REL_DATA_CHAN               (DICC_CHAN_ID_3)

#define DICC_SERVICE_TYPE_CSD_DATA                  (DICC_SERVICE_TYPE_0)
#define DICC_SERVICE_TYPE_REL_MEM                   (DICC_SERVICE_TYPE_1)

enum DICC_CPU_ID_ENUM
{
    DICC_CPU_ID_CCPU = 0,
    DICC_CPU_ID_ACPU = 1,
    DICC_CPU_ID_BUTT
};
typedef VOS_UINT8 DICC_CPU_ID_ENUM_UINT8;

enum DICC_CHAN_ID_ENUM
{
    DICC_CHAN_ID_0 = 0,
    DICC_CHAN_ID_1,
    DICC_CHAN_ID_2,
    DICC_CHAN_ID_3,

    DICC_CHAN_ID_BUTT
};
typedef VOS_UINT8 DICC_CHAN_ID_ENUM_UINT8;

enum DICC_SERVICE_TYPE_ENUM
{
    DICC_SERVICE_TYPE_0 = 0,
    DICC_SERVICE_TYPE_1,

    DICC_SERVICE_TYPE_BUTT
};
typedef VOS_UINT8 DICC_SERVICE_TYPE_ENUM_UINT8;


enum DICC_GET_CHN_NODE_CNT_ENUM
{
    DICC_GET_CHN_CURR_DATA_CNT = 0,
    DICC_GET_CHN_FREE_SPACE_CNT,
    DICC_GET_CHN_NODE_CNT_BUTT
};
typedef VOS_UINT8 DICC_GET_CHN_NODE_CNT_ENUM_UINT8;

enum DICC_CHAN_ROLE_ENUM
{
    DICC_CHAN_ROLE_SENDER = 0,
    DICC_CHAN_ROLE_RECVER,

    DICC_CHAN_ROLE_BUTT
};
typedef VOS_UINT8 DICC_CHAN_ROLE_ENUM_UINT8;

enum DICC_ERROR_CODE_ENUM
{
     DICC_OK = 0,
     DICC_ERR_CHAN_BLK_NUM = 1,
     DICC_ERR_CHAN_BLK_SIZE,
     DICC_ERR_MEM_SIZE,
     DICC_ERR_RECV_ISR_NULL,
     DICC_ERR_CHAN_ID_UNDEFINED,
     DICC_ERR_INFO_PTR_NULL,
     DICC_ERR_SERVCE_UNDEFINED,
     DICC_ERR_EXISTED_CHAN_ID,
     DICC_ERR_CHAN_ID_NOT_MATCH_ROLE,
     DICC_ERR_CHAN_ALREADY_OPENED,
     DICC_ERR_INSERT_DESP_BLK_PTR_NULL,
     DICC_ERR_INSERT_DESP_BLK_DATA_CNT,
     DICC_ERR_INSERT_DESP_BLK_DATA_NULL,
     DICC_ERR_DLV_DATA_BLK_SIZE,
     DICC_ERR_CHAN_NOT_OPEN_IN_BOTH_SIDES,
     DICC_ERR_INVALID_CHAN_ID,
     DICC_ERR_GET_CNT_TYPE_UNDEFINED,
     DICC_ERR_REMOVE_DATA_PTR_NULL,
     DICC_ERR_REMOVE_DATA_CNT,
     DICC_ERR_CPU_ID_NOT_MATCH,
     DICC_ERR_CLOSE_BEFORE_SENDER_CLOSED,
     DICC_ERR_CHAN_FULL,
     DICC_ERR_CHAN_NOT_READY = 100,
     DICC_ERR_GET_NODE_FAIL,
     DICC_ERR_MAGIC_NUM_CHANGED,
     DICC_ERR_RING_QUEUE_FAIL,
     DICC_ERR_LOCAL_SEMPHORE_FAIL,
     DICC_ERR_MAGIC_MEM_TEMPERED,
     DICC_ERR_ISR_CONNECT_FAIL = 200,
     DICC_ERR_USE_HW_SEMPHORE_FAIL,
     DICC_ERR_TRIG_ISR_FAIL,
     DICC_ERR_OP_ISR_FAIL,
     DICC_ERR_BUTT
};
typedef VOS_UINT32 DICC_ERROR_CODE_ENUM_UINT32;

#pragma pack(4)

typedef struct
{
    VOS_UINT8                         aucReserve[2];
    PS_BOOL_ENUM_UINT8                enAutoTrigTx;
    VOS_UINT8                         ucDataLen;
    VOS_UINT8                        *pucUserData;
} DICC_INSERT_DSCP_BLK_STRU;

#if 0
typedef struct
{
    VOS_UINT8                         aucReserve[3];
    VOS_UINT8                         ucDataLen;
    VOS_UINT8                        *pucUserData;
} DICC_INSERT_INFO_STRU;
#endif

typedef struct
{
    VOS_UINT8                         aucReserve[2];
    VOS_UINT8                         ucInsertCnt;
    PS_BOOL_ENUM_UINT8                enAutoTrigTx;
    VOS_UINT8                         aucDataLen[DICC_BAT_OP_CNT];
    VOS_UINT8                        *apucUserData[DICC_BAT_OP_CNT];
} DICC_BAT_INSERT_DSCP_BLK_STRU;

typedef struct
{
    VOS_UINT16                        usChnBlkNum;
    VOS_UINT16                        usChnBlkSize;
} DICC_BLK_CHN_INFO_STRU;

typedef struct
{
    DICC_BLK_CHN_INFO_STRU            stSndChnInfo;
} DICC_SEND_INIT_CHN_INFO_STRU;

typedef struct
{
    VOS_VOID                          (*pfuncRecvIsr)(VOS_VOID);
} DICC_RECV_INIT_CHN_INFO_STRU;

typedef struct
{
    DICC_CHAN_ROLE_ENUM_UINT8         enUserRole;
    VOS_UINT8                         aucReserve1[3];

    union
    {
        DICC_SEND_INIT_CHN_INFO_STRU  stSndInitInfo;
        DICC_RECV_INIT_CHN_INFO_STRU  stRcvInitInfo;
    }u;
} DICC_INIT_CHN_INFO_STRU;

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

extern VOS_UINT32 DICC_TriggerChanDataTx(VOS_UINT32 ulPid, VOS_UINT8 ucChanId,
                      DICC_CPU_ID_ENUM_UINT8 enCpuId);

#if 0
extern VOS_UINT32 DICC_EnableIsr(VOS_UINT32 ulPid, DICC_SERVICE_TYPE_ENUM_UINT8 enServiceType,
                      DICC_CPU_ID_ENUM_UINT8 enCpuId);
extern VOS_UINT32 DICC_DisableIsr(VOS_UINT32 ulPid, DICC_SERVICE_TYPE_ENUM_UINT8 enServiceType,
                      DICC_CPU_ID_ENUM_UINT8 enCpuId);
#endif


extern VOS_UINT32 DICC_InsertChannelDataAction(VOS_UINT32 ulFileId, VOS_UINT32 ulLineNum,
                                               VOS_UINT32 ulPid, VOS_UINT8 ucChnId,
                                               DICC_INSERT_DSCP_BLK_STRU *pstDscpBlk,
                                               DICC_CPU_ID_ENUM_UINT8 enCpuId);
#define DICC_InsertChannelData(ulPid, ucChnId, pstDscpBlk, enCpuId)\
            DICC_InsertChannelDataAction(THIS_FILE_ID, __LINE__, (ulPid), (ucChnId), (pstDscpBlk), (enCpuId))

extern VOS_UINT32 DICC_RemoveChannelData(VOS_UINT32 ulPid, VOS_UINT8 ucChnId,
                                         VOS_UINT8 *pucUsrData,
                                         DICC_CPU_ID_ENUM_UINT8 enCpuId);

extern VOS_UINT32 DICC_OpenChannel(VOS_UINT32 ulPid, VOS_UINT8 ucChnId,
                                   DICC_CHAN_ROLE_ENUM_UINT8 enUserRole,
                                   DICC_CPU_ID_ENUM_UINT8 enCpuId);

extern VOS_UINT32 DICC_CloseChannel(VOS_UINT32 ulPid, VOS_UINT8 ucChnId,
                                    DICC_CPU_ID_ENUM_UINT8 enCpuId);

extern VOS_UINT32 DICC_SingleChnInitAction(VOS_UINT32 ulFileId, VOS_UINT32 ulLineNum,
                                     VOS_UINT32 ulPid, DICC_SERVICE_TYPE_ENUM_UINT8 enServiceType,
                                     DICC_INIT_CHN_INFO_STRU *pstInitChanInfo,
                                     DICC_CPU_ID_ENUM_UINT8 enCpuId);
#define DICC_SingleChnInit(ulPid, enServiceType, pstInitChanInfo, enCpuId)\
            DICC_SingleChnInitAction(THIS_FILE_ID, __LINE__, (ulPid), (enServiceType), (pstInitChanInfo), (enCpuId))

extern VOS_UINT32 DICC_GetChannelNodeCnt(VOS_UINT32                       ulPid,
                                         DICC_CHAN_ID_ENUM_UINT8          ucChnId,
                                         DICC_GET_CHN_NODE_CNT_ENUM_UINT8 enGetChnNodeCntType,
                                         DICC_CPU_ID_ENUM_UINT8 enCpuId);
#define  DICC_GetChannelCurrDataCnt(ulPid, ucChnId, enCpuId)   (DICC_GetChannelNodeCnt((ulPid), (ucChnId), DICC_GET_CHN_CURR_DATA_CNT, (enCpuId)))
#define  DICC_GetChannelFreeSpaceCnt(ulPid, ucChnId, enCpuId)  (DICC_GetChannelNodeCnt((ulPid), (ucChnId), DICC_GET_CHN_FREE_SPACE_CNT, (enCpuId)))

extern VOS_UINT32 DICC_BatInsertChannelDataAction(VOS_UINT32 ulFileId, VOS_UINT32 ulLineNum,
                                        VOS_UINT32 ulPid, DICC_CHAN_ID_ENUM_UINT8 ucChnId,
                                        DICC_BAT_INSERT_DSCP_BLK_STRU    *pstBatDscpBlk,
                                        DICC_CPU_ID_ENUM_UINT8 enCpuId);
#define DICC_BatInsertChannelData(ulPid, ucChnId, pstBatDscpBlk, enCpuId)\
            DICC_BatInsertChannelDataAction(THIS_FILE_ID, __LINE__, (ulPid), (ucChnId), (pstBatDscpBlk), (enCpuId))

extern VOS_UINT32 DICC_BatRemoveChannelData(VOS_UINT32            ulPid,
                                  DICC_CHAN_ID_ENUM_UINT8  ucChnId,
                                  VOS_UINT8                aucUsrData[],
                                  VOS_UINT16               usNeedRemoveCnt,
                                  VOS_UINT16              *pusActiveRemoveCnt,
                                  DICC_CPU_ID_ENUM_UINT8   enCpuId);

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* DiccInterface.h */
