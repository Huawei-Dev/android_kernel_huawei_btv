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

#ifndef __ADSCTX_H__
#define __ADSCTX_H__

/*****************************************************************************
  1 ??????????
*****************************************************************************/
#include "vos.h"
#include "PsCommonDef.h"
#include "PsLogdef.h"
#include "PsTypeDef.h"
#include "PsLib.h"
#include "AdsInterface.h"
#include "AdsDeviceInterface.h"
#include "CdsAdsInterface.h"
#include "AdsNdInterface.h"
#include "AdsTimerMgmt.h"
#include "AdsLog.h"
#include "mdrv.h"
#include "NVIM_Interface.h"
#include "AdsFcInterface.h"
#include "NasNvInterface.h"
#include "TafNvInterface.h"

#if (VOS_OS_VER == VOS_LINUX)
#include <asm/dma-mapping.h>
#include <linux/wakelock.h>
#if (defined(CONFIG_BALONG_SPE))
#include <linux/spe/spe_interface.h>
#include "mdrv_spe_wport.h"
#endif /* CONFIG_BALONG_SPE */
#else
#include "Linuxstub.h"
#endif /* VOS_OS_VER == VOS_LINUX */


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)


/*****************************************************************************
  2 ??????
*****************************************************************************/

/* ADS??????????Modem???????????? */
#define ADS_INSTANCE_MAX_NUM            (MODEM_ID_BUTT)

/* ADS?????????? */
#define ADS_INSTANCE_INDEX_0            (0)
#define ADS_INSTANCE_INDEX_1            (1)
#define ADS_INSTANCE_INDEX_2            (2)

/*???????????????????? */
#define ADS_RAB_NUM_MAX                 (11)

/* ??????????????????5??15, ??????????5???????? */
#define ADS_RAB_ID_OFFSET               (5)

/* Rab Id???????? */
#define ADS_RAB_ID_MIN                  (5)

/* Rab Id???????? */
#define ADS_RAB_ID_MAX                  (15)

/* Rab Id???????? */
#define ADS_RAB_ID_INVALID              (0xFF)

/* ????????????????IPF?????????????????????????????????????? */
#define ADS_UL_SEND_DATA_NUM_THREDHOLD          (g_stAdsCtx.stAdsIpfCtx.ulThredHoldNum)

#define ADS_UL_SET_SEND_DATA_NUM_THREDHOLD(n)   (g_stAdsCtx.stAdsIpfCtx.ulThredHoldNum = (n))

#define ADS_UL_RX_WAKE_LOCK_TMR_LEN     (g_stAdsCtx.stAdsIpfCtx.ulRxWakeLockTmrLen)
#define ADS_DL_TX_WAKE_LOCK_TMR_LEN     (g_stAdsCtx.stAdsIpfCtx.ulTxWakeLockTmrLen)

/* ??????AD????????14????IPF RD????????????14??MAC???????? */
#define ADS_DL_AD_DATA_PTR_OFFSET       (14)

/* ?????????????????? */
#define ADS_UL_DEFAULT_PRI_WEIGHTED_NUM (0x01)

#define ADS_GET_CURR_KERNEL_TIME()      (jiffies)
#define ADS_TIME_AFTER_EQ(a, b)         time_after_eq((a), (b))

/* ADS ADQ?????? */
#define ADS_DL_ADQ_MAX_NUM              (2)

/*????ADQ????????????????????????????AD??????????????????????????????*/
#define ADS_IPF_DLAD_START_TMR_THRESHOLD (IPF_DLAD0_DESC_SIZE - 6)

/* ADS??????SPE?????? */
#define ADS_IPF_SPE_PORT_0              (SPE_PORT_MAX + 128)
#define ADS_IPF_SPE_PORT_1              (SPE_PORT_MAX + 129)

/* AD???????????? */
#define ADS_IPF_AD0_MEM_BLK_NUM         (IPF_DLAD0_DESC_SIZE * 2)
#define ADS_IPF_AD1_MEM_BLK_NUM         (IPF_DLAD1_DESC_SIZE * 3)
#define ADS_IPF_AD_MEM_RESV_BLK_NUM     (64)

/* AD???????????? */
#define ADS_IPF_AD0_MEM_BLK_SIZE        (448)
#define ADS_IPF_AD1_MEM_BLK_SIZE        (1536 + 14)

/* ADS_UL_SendPacket??ADS_DL_RegDlDataCallback??rabid????????rabid??
   ??2bit????MODEM ID????6bit????RAB ID????????????RABID????MODEM ID */
#define ADS_GET_MODEMID_FROM_EXRABID(i) ((i >> 6) & 0x03)

#define ADS_GET_RABID_FROM_EXRABID(i)   (i & 0x3F)

#define ADS_BUILD_EXRABID(i,j)          (((i << 6) & 0xC0) | (j & 0x3F))

/*******************************???????? Begin*******************************/

/* ADS???????????? */
#define ADS_UL_EVENT_BASE               (0x00000000)
#define ADS_UL_EVENT_DATA_PROC          (ADS_UL_EVENT_BASE | 0x0001)

/* ADS???????????? */
#define ADS_DL_EVENT_BASE               (0x00000000)
#define ADS_DL_EVENT_IPF_RD_INT         (ADS_DL_EVENT_BASE | 0x0001)
#define ADS_DL_EVENT_IPF_ADQ_EMPTY_INT  (ADS_DL_EVENT_BASE | 0x0002)

/*******************************???????? End*******************************/

/*******************************???????? Begin*******************************/
/* ?????????????????? */
#define ADS_GET_DSFLOW_STATS_CTX_PTR()              (&(g_stAdsCtx.stDsFlowStatsCtx))

/* ???????????????? */
#define ADS_SET_CURRENT_UL_RATE(n)                  (g_stAdsCtx.stDsFlowStatsCtx.stULDataStats.ulULCurDataRate = (n))

/* ???????????????? */
#define ADS_SET_CURRENT_DL_RATE(n)                  (g_stAdsCtx.stDsFlowStatsCtx.stDLDataStats.ulDLCurDataRate = (n))

/* ?????????????????????????? */
#define ADS_RECV_UL_PERIOD_PKT_NUM(n)               (g_stAdsCtx.stDsFlowStatsCtx.stULDataStats.ulULPeriodSndBytes += (n))

/* ?????????????????????????? */
#define ADS_RECV_DL_PERIOD_PKT_NUM(n)               (g_stAdsCtx.stDsFlowStatsCtx.stDLDataStats.ulDLPeriodRcvBytes += (n))

/* ?????????????????????????? */
#define ADS_GET_UL_PERIOD_PKT_NUM()                 (g_stAdsCtx.stDsFlowStatsCtx.stULDataStats.ulULPeriodSndBytes)

/* ?????????????????????????? */
#define ADS_GET_DL_PERIOD_PKT_NUM()                 (g_stAdsCtx.stDsFlowStatsCtx.stDLDataStats.ulDLPeriodRcvBytes)

/* ???????????????????????????? */
#define ADS_CLEAR_UL_PERIOD_PKT_NUM()               (g_stAdsCtx.stDsFlowStatsCtx.stULDataStats.ulULPeriodSndBytes = 0)

/* ???????????????????????????? */
#define ADS_CLEAR_DL_PERIOD_PKT_NUM()               (g_stAdsCtx.stDsFlowStatsCtx.stDLDataStats.ulDLPeriodRcvBytes = 0)

/*******************************???????? End*******************************/


/*******************************???? Begin*******************************/
/* ????ADS???????????? */
#define ADS_UL_GET_CTX_PTR(i)                       (&(g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx))

/* ???????????????? */
#define ADS_UL_GET_QUEUE_LINK_PTR(i, j)             (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.astAdsUlQueue[j].pstAdsUlLink)

/* ?????????????? */
#define ADS_UL_GET_QUEUE_LINK_SPINLOCK(i, j)        (&(g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.astAdsUlQueue[j].stSpinLock))

/* ????ADS????BD???????????? */
#define ADS_UL_GET_BD_CFG_PARA_PTR(index)           (&(g_stAdsCtx.stAdsIpfCtx.astIpfUlBdCfgParam[index]))

/* ????ADS????BD???????? */
#define ADS_UL_GET_BD_BUFF_PTR(index)               (&(g_stAdsCtx.stAdsIpfCtx.astIpfUlBdBuff[index]))

/* ????ADS?????????????????????? */
#define ADS_UL_GET_PROTECT_TIMER_LEN()              (g_stAdsCtx.stAdsIpfCtx.ulProtectTmrLen)

/* ???????????????????????????? */
#define ADS_UL_GET_SENDING_FLAG()                   (g_stAdsCtx.stAdsIpfCtx.ucSendingFlg)

/* ???????????????????????????? */
#define ADS_UL_SET_SENDING_FLAG(flg)                (g_stAdsCtx.stAdsIpfCtx.ucSendingFlg = flg)

/* ?????????????????? */
#define ADS_UL_GET_PRIO_QUEUE_INDEX(i, j)           (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.aucPrioIndex[j])

/* ??????????????????????*/
#define ADS_UL_GET_QUEUE_QCI(i, j)                  (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.astAdsUlQueue[ADS_UL_GET_PRIO_QUEUE_INDEX(i, j)].enPrio)

/* ???????????????? */
#define ADS_UL_GET_QUEUE_LINK_INFO(i, j)            (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.astAdsUlQueue[ADS_UL_GET_PRIO_QUEUE_INDEX(i, j)].pstAdsUlLink)

/* ????IX OR HRPD??????IPF?????????? */
#define ADS_UL_GET_1X_OR_HRPD_UL_IPF_FLAG(i, j)     (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.astAdsUlQueue[ADS_UL_GET_PRIO_QUEUE_INDEX(i, j)].uc1XorHrpdUlIpfFlag)

/* ?????????????????????????????????????????? */
#define ADS_UL_GET_RECORD_NUM_IN_WEIGHTED(i, j)     (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.astAdsUlQueue[ADS_UL_GET_PRIO_QUEUE_INDEX(i, j)].usRecordNum)

/* ?????????????????????????????????????????? */
#define ADS_UL_SET_RECORD_NUM_IN_WEIGHTED(i, j, n)  (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.astAdsUlQueue[ADS_UL_GET_PRIO_QUEUE_INDEX(i, j)].usRecordNum += n)

/* ?????????????????????????????????????????? */
#define ADS_UL_CLR_RECORD_NUM_IN_WEIGHTED(i, j)     (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.astAdsUlQueue[ADS_UL_GET_PRIO_QUEUE_INDEX(i, j)].usRecordNum = 0)

/* ?????????????????????????? */
#define ADS_UL_GET_QUEUE_PRI_WEIGHTED_NUM(i, j)     (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.stQueuePriNv.ausPriWeightedNum[ADS_UL_GET_QUEUE_QCI(i, j)])

/* ????????????????????????*/
#define ADS_UL_GET_QUEUE_PKT_TYPE(InstanceIndex, RabId) \
            (g_stAdsCtx.astAdsSpecCtx[InstanceIndex].stAdsUlCtx.astAdsUlQueue[RabId].enPktType)


/* ????ADS?????????????????????? */
#define ADS_UL_GET_STAT_TIMER_LEN()     \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stThresholdStatInfo.ulStatTmrLen)

#define ADS_UL_ADD_STAT_PKT_NUM(n)      \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stThresholdStatInfo.ulStatPktNum += (n))

#define ADS_UL_GET_STAT_PKT_NUM()       \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stThresholdStatInfo.ulStatPktNum)

#define ADS_UL_CLR_STAT_PKT_NUM()       \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stThresholdStatInfo.ulStatPktNum = 0)

/* ???????????????????? */
#define ADS_UL_GET_THRESHOLD_ACTIVE_FLAG() \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.ulActiveFlag)

/* ??????????????jiffies?????????? */
#define ADS_UL_GET_JIFFIES_TMR_CNT()     (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.ulProtectTmrCnt)

/* ??????????????jiffies?????????? */
#define ADS_UL_SET_JIFFIES_TMR_CNT(n)     (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.ulProtectTmrCnt += (n))

/* ??????????????jiffies?????????? */
#define ADS_UL_GET_JIFFIES_EXP_TMR_LEN() (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.ulProtectTmrExpCnt)

/* ?????????????????????? */
#define ADS_UL_GET_WATER_LEVEL_ONE()    \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stWaterMarkLevel.ulWaterLevel1)

#define ADS_UL_GET_WATER_LEVEL_TWO()    \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stWaterMarkLevel.ulWaterLevel2)

#define ADS_UL_GET_WATER_LEVEL_THREE()  \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stWaterMarkLevel.ulWaterLevel3)

#define ADS_UL_GET_WATER_LEVEL_FOUR()   \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stWaterMarkLevel.ulWaterLevel4)

/* ???????????????? */
#define ADS_UL_DATA_THRESHOLD_ONE       \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stThresholdLevel.ulThreshold1)

#define ADS_UL_DATA_THRESHOLD_TWO       \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stThresholdLevel.ulThreshold2)

#define ADS_UL_DATA_THRESHOLD_THREE     \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stThresholdLevel.ulThreshold3)

#define ADS_UL_DATA_THRESHOLD_FOUR      \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stThresholdLevel.ulThreshold4)


/*******************************???? End*******************************/

/* ????IPF?????????????????? */
#define ADS_UL_IPF_SRCMEM_FREE_QUE()            (&(g_stAdsCtx.stAdsIpfCtx.stUlSrcMemFreeQue))

/* IPF??????????????QUEUE????????????????IPF BD????????2?? */
#define ADS_UL_IPF_SRCMEM_FREE_QUE_SIZE         (2 * IPF_ULBD_DESC_SIZE)

/* ????????ADS??????????????????A???????????????????????????? */
#define ADS_UL_MAX_QUEUE_LENGTH                 (500)

/* ???????????????? */
#define ADS_UL_GET_MAX_QUEUE_LENGTH(i)          (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.ulUlMaxQueueLength)

/* ????ADS????IPF AD BUFFER???? */
#define ADS_DL_GET_IPF_AD_DESC_PTR(i, j)        (&(g_stAdsCtx.stAdsIpfCtx.astIpfDlAdDesc[i][j]))

/*******************************???? Begin*******************************/

/* ????ADS???????????? */
#define ADS_DL_GET_CTX_PTR(i)                   (&(g_stAdsCtx.astAdsSpecCtx[i].stAdsDlCtx))

/* ????ADS????IPF RD BUFFER???? */
#define ADS_DL_GET_IPF_RD_DESC_PTR(index)       (&(g_stAdsCtx.stAdsIpfCtx.astIpfDlRdDesc[index]))

/* ????ADS????RAB INFO???? */
#define ADS_DL_GET_RAB_INFO_PTR(i, rabid)       (&(ADS_DL_GET_CTX_PTR(i)->astAdsDlRabInfo[rabid - ADS_RAB_ID_OFFSET]))

/* ????ADS????RAB???????????????? */
#define ADS_DL_GET_PKT_TYPE(instance, rabid)    (ADS_DL_GET_CTX_PTR(instance)->astAdsDlRabInfo[rabid - ADS_RAB_ID_OFFSET].enPktType)

/* ????ADS???????????????????? */
#define ADS_DL_GET_DATA_CALLBACK_FUNC(i,j)      (ADS_DL_GET_RAB_INFO_PTR(i,j)->pRcvDlDataFunc)
#define ADS_DL_GET_DATA_EXPARAM(i,j)            (ADS_DL_GET_RAB_INFO_PTR(i,j)->ulExParam)

/* get/set the last data buff ptr */
#define ADS_DL_GET_LST_DATA_PTR(mid,rabid)          (ADS_DL_GET_RAB_INFO_PTR(mid,rabid)->pstLstPkt)
#define ADS_DL_SET_LST_DATA_PTR(mid,rabid, psPara)  (ADS_DL_GET_RAB_INFO_PTR(mid,rabid)->pstLstPkt = (psPara))

#define ADS_DL_GET_FILTER_DATA_CALLBACK_FUNC(ucInstanceIndex, ucRabId) \
            (ADS_DL_GET_RAB_INFO_PTR(ucInstanceIndex, ucRabId)->pRcvDlFilterDataFunc)

/* ????ADS???????????????????? */
#define ADS_DL_GET_FC_ASSEM_INFO_PTR(i)         (&(ADS_DL_GET_CTX_PTR(i)->stFcAssemInfo))

/* ????ADS???????????????????????????????? */
#define ADS_DL_GET_FC_ASSEM_TUNE_FUNC(i)        (ADS_DL_GET_FC_ASSEM_INFO_PTR(i)->pFcAssemTuneFunc)

/*******************************???? End*******************************/

/*******************************IPF Begin*******************************/
/* ????IPF???????????? */
#define ADS_GET_IPF_CTX_PTR()           (&(g_stAdsCtx.stAdsIpfCtx))

#define ADS_GET_IPF_DEV()               (&(g_stAdsCtx.stAdsIpfCtx.stDev))
#define ADS_IMM_MEM_CB(pstImmZc)        ((ADS_IMM_MEM_CB_STRU *)((pstImmZc)->cb))

#if (defined(CONFIG_BALONG_SPE))
#define ADS_GET_IPF_SPE_WPORT()         (g_stAdsCtx.stAdsIpfCtx.lSpeWPort)
#define ADS_GET_IPF_MEM_POOL_CFG_PTR()  (&(g_stAdsCtx.stAdsIpfCtx.stMemPoolCfg))
#define ADS_GET_IPF_MEM_POOL_PTR(id)    (&(g_stAdsCtx.stAdsIpfCtx.astMemPool[id]))
#define ADS_GET_IPF_MEM_QUE(id)         (&(g_stAdsCtx.stAdsIpfCtx.astMemPool[id].stQue))
#define ADS_SPE_MEM_CB(pstImmZc)        ((ADS_SPE_MEM_CB_STRU *)&((pstImmZc)->dma))
#endif

/*lint -emacro({717}, ADS_IPF_SPE_MEM_MAP)*/
#define ADS_IPF_SPE_MEM_MAP(pstImmZc, ulLen)\
            do\
            {\
                if (VOS_TRUE == ADS_IPF_IsSpeMem(pstImmZc))\
                {\
                    ADS_IPF_MemMapByDmaRequset(pstImmZc, ulLen, 0);\
                }\
            } while(0)

/*lint -emacro({717}, ADS_IPF_SPE_MEM_UNMAP)*/
#define ADS_IPF_SPE_MEM_UNMAP(pstImmZc, ulLen)\
            do\
            {\
                if (VOS_TRUE == ADS_IPF_IsSpeMem(pstImmZc))\
                {\
                    ADS_IPF_MemUnmapRequset(pstImmZc, ulLen, 0);\
                }\
            } while(0)


/*******************************IPF End*******************************/

/* ????MODEMID?????? */
#define ADS_IS_MODEMID_VALID(usModemId)\
            ((usModemId) < ADS_INSTANCE_MAX_NUM)

/* ????RABIID?????? */
#define ADS_IS_RABID_VALID(ucRabId)\
            (((ucRabId) >= ADS_RAB_ID_MIN) && ((ucRabId) <= ADS_RAB_ID_MAX))

#define ADS_UL_IS_REACH_THRESHOLD(ulAllUlQueueDataNum, ucSendingFlg) \
    ((0 != ulAllUlQueueDataNum) && (ulAllUlQueueDataNum >= ADS_UL_SEND_DATA_NUM_THREDHOLD) && (VOS_FALSE == ucSendingFlg))

#if !defined(ADS_ARRAY_SIZE)
#define ADS_ARRAY_SIZE(a)               (sizeof((a)) / sizeof((a[0])))
#endif


/*****************************************************************************
  3 ????????
*****************************************************************************/

/*****************************************************************************
 ????????  : ADS_IPF_MEM_POOL_ID_ENUM
 ????????  : IPF ????????
*****************************************************************************/
enum ADS_IPF_MEM_POOL_ID_ENUM
{
    ADS_IPF_MEM_POOL_ID_AD0             = 0,
    ADS_IPF_MEM_POOL_ID_AD1,

    ADS_IPF_MEM_POOL_ID_BUTT
};
typedef VOS_UINT32 ADS_IPF_MEM_POOL_ID_ENUM_UINT32;


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
 ????????  : ADS_SPE_MEM_CB_STRU
 ????????  : IPF CB????
*****************************************************************************/
typedef struct
{
    dma_addr_t                          ulDmaAddr;

} ADS_SPE_MEM_CB_STRU;

/*****************************************************************************
 ????????  : ADS_IMM_MEM_CB_STRU
 ????????  : IMM CB????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          aulPriv[2];
    dma_addr_t                          ulDmaAddr;

} ADS_IMM_MEM_CB_STRU;

/*****************************************************************************
 ????????  : ADS_IPF_BD_BUFF_STRU
 ????????  : IPF BD Buffer????
*****************************************************************************/
typedef struct
{
    IMM_ZC_STRU                        *pstPkt;

} ADS_IPF_BD_BUFF_STRU;

/*****************************************************************************
??????    : ADS_UL_QUEUE_STRU
????????  : ADS????????????

  1.??    ??   : 2011??12??6??
    ??    ??   : ????/l60609
    ????????   : ????ADS????????????
  2.??    ??   : 2012??02??20??
    ??    ??   : f00179208
    ????????   : ??????????????????
  3.??    ??   : 2012??9??12??
    ??    ??   : l60609
    ????????   : AP????????????????????
  4.??    ??   : 2012??11??27??
    ??    ??   : l60609
    ????????   : DSDA Phase II:??????
  5.??    ??   : 2013??05??22??
    ??    ??   : f00179208
    ????????   : V3R3 PPP RPOJECT:????PDP TYPE
*****************************************************************************/
typedef struct
{
    IMM_ZC_HEAD_STRU                   *pstAdsUlLink;                           /* Rab Id?????????? */
    VOS_UINT8                           ucIsQueueValid;                         /* ??????????????VOS_TRUE:??????VOS_FALSE:?????? */
    ADS_QCI_TYPE_ENUM_UINT8             enPrio;                                 /* ?????????? */
    VOS_UINT16                          usRecordNum;                            /* ???????????????????????????????????? */
    VOS_SPINLOCK                        stSpinLock;                             /* ?????? */
    ADS_CDS_IPF_PKT_TYPE_ENUM_UINT8     enPktType;                              /* ?????????? */
    VOS_UINT8                           uc1XorHrpdUlIpfFlag;                    /* 1X OR HRPD????????IPF?????? */
    VOS_UINT8                           aucRsv[6];

}ADS_UL_QUEUE_STRU;

/*****************************************************************************
??????    : ADS_DL_RAB_INFO_STRU
????????  : ADS????RAB????????

  1.??    ??   : 2011??12??6??
    ??    ??   : ????/l60609
    ????????   : ????ADS????RABID????????
  2.??    ??   : 2013??06??04??
    ??    ??   : l00198894
    ????????   : Share-PDP????????????????????????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRabId;                                /* Rab Id */
    ADS_CDS_IPF_PKT_TYPE_ENUM_UINT8     enPktType;                              /* ?????????? */
    VOS_UINT8                           aucRsv[2];                              /* ???? */
    VOS_UINT32                          ulExParam;                              /* RMNET???????????????? */
    RCV_DL_DATA_FUNC                    pRcvDlDataFunc;                         /* ?????????????????? */
    RCV_DL_DATA_FUNC                    pRcvDlFilterDataFunc;                   /* ?????????????????????? */
    IMM_ZC_STRU                        *pstLstPkt;

}ADS_DL_RAB_INFO_STRU;

/*****************************************************************************
 ??????   : ADS_DL_FC_ASSEM_STRU
 ???????? : ????????????????

 ????????      :
  1.??    ??   : 2012??11??19??
    ??    ??   : A00165503
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32              ulEnableMask;
    VOS_UINT32              ulFcActiveFlg;
    unsigned long           ulTmrCnt;
    VOS_UINT32              ulRdCnt;
    VOS_UINT32              ulRateUpLev;
    VOS_UINT32              ulRateDownLev;
    VOS_UINT32              ulExpireTmrLen;
    ADS_DRV_ASSEM_FUNC      pFcAssemTuneFunc;

} ADS_DL_FC_ASSEM_STRU;

/*****************************************************************************
??????    : ADS_DL_CTX_STRU
????????  : ADS??????????

  1.??    ??   : 2011??12??6??
    ??    ??   : ????/l60609
    ????????   : ????ADS??????????

  2.??    ??   : 2012??4??12??
    ??    ??   : A00165503
    ????????   : DTS2012020708222: ADS????????

  3.??    ??   : 2012??11??19??
    ??    ??   : A00165503
    ????????   : DTS2012112206761: ????????????????????

  4.??    ??   : 2012??11??23??
    ??    ??   : L60609
    ????????   : DSDA Phase II

*****************************************************************************/
typedef struct
{
    ADS_DL_RAB_INFO_STRU                astAdsDlRabInfo[ADS_RAB_NUM_MAX];       /*????Rab???? */
    ADS_DL_FC_ASSEM_STRU                stFcAssemInfo;

} ADS_DL_CTX_STRU;

/*****************************************************************************
??????    : ADS_UL_CTX_STRU
????????  : ADS??????????

  1.??    ??   : 2011??12??6??
    ??    ??   : ????/l60609
    ????????   : ????ADS??????????

  2.??    ??   : 2012??02??20??
    ??    ??   : f00179208
    ????????   : V7R1C50??????????????????????????????

  3.??    ??   : 2012??4??12??
    ??    ??   : A00165503
    ????????   : DTS2012020708222: ADS????????

  4.??    ??   : 2012??8??31??
    ??    ??   : l60609
    ????????   : AP??????????????????????????????

  5.??    ??   : 2012??11??23??
    ??    ??   : L60609
    ????????   : DSDA Phase II
*****************************************************************************/
typedef struct
{
    ADS_UL_QUEUE_STRU                   astAdsUlQueue[ADS_RAB_ID_MAX + 1];      /* ??????????????????5-15 */
    ADS_UL_QUEUE_SCHEDULER_PRI_NV_STRU  stQueuePriNv;                           /* ??NV?????????????????????????????????? */
    VOS_UINT8                           aucPrioIndex[ADS_RAB_NUM_MAX];          /* ???????????????????????????????? */
    VOS_UINT8                           ucAdsUlCurIndex;                        /* ?????????????????? */
    VOS_UINT8                           aucRsv[4];
    VOS_UINT32                          ulUlMaxQueueLength;                     /* ???????????? */
    VOS_UINT8                           aucReserved1[4];

}ADS_UL_CTX_STRU;

/*****************************************************************************
 ??????    : ADS_UL_DATA_STATS_STRU
 ????????  : ADS????????????
   1.??    ??   : 2012??1??10??
     ??    ??   : L60609
     ????????   : ????
*****************************************************************************/
typedef struct ADS_UL_DATA_STATS
{
    VOS_UINT32                          ulULCurDataRate;                        /* ??????????????????PDP??????2?????????????????????? */
    VOS_UINT32                          ulULPeriodSndBytes;                     /* ????????????????????????byte?? */
}ADS_UL_DATA_STATS_STRU;

/*****************************************************************************
 ??????    : ADS_DL_DATA_STATS_STRU
 ????????  : ADS????????????
   1.??    ??   : 2012??1??10??
     ??    ??   : L60609
     ????????   : ????
*****************************************************************************/
typedef struct ADS_DL_DATA_STATS
{
    VOS_UINT32                          ulDLCurDataRate;                        /* ??????????????????PDP??????2?????????????????????? */
    VOS_UINT32                          ulDLPeriodRcvBytes;                     /* ????????????????????????byte?? */
}ADS_DL_DATA_STATS_STRU;

/*****************************************************************************
 ??????    : ADS_STATS_INFO_CTX_STRU
 ????????  : ADS????????
   1.??    ??   : 2012??1??10??
     ??    ??   : L60609
     ????????   : ????
*****************************************************************************/
typedef struct
{
    ADS_UL_DATA_STATS_STRU              stULDataStats;                          /* ADS???????????? */
    ADS_DL_DATA_STATS_STRU              stDLDataStats;                          /* ADS???????????? */
}ADS_STATS_INFO_CTX_STRU;

/*****************************************************************************
 ??????    : ADS_UL_THRESHOLD_STAT_STRU
 ????????  : ADS????????????????
   1.??    ??   : 2014??06??03??
     ??    ??   : f00179208
     ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulStatTmrLen;                           /* ?????????????? */
    VOS_UINT32                          ulStatPktNum;                           /* ???????????????????????????? */
}ADS_UL_THRESHOLD_STAT_STRU;

/*****************************************************************************
 ??????    : ADS_UL_DYNAMIC_ASSEM_INFO_STRU
 ????????  : ADS????????????
   1.??    ??   : 2014??11??08??
     ??    ??   : f00179208
     ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulActiveFlag;                           /* ????????: 0??????????,1???????? */
    VOS_UINT32                          ulProtectTmrExpCnt;                     /* ?????????????????? */
    unsigned long                       ulProtectTmrCnt;                        /* ???????????????? */
    ADS_UL_WATER_MARK_LEVEL_STRU        stWaterMarkLevel;                       /* ?????????? */
    ADS_UL_THRESHOLD_LEVEL_STRU         stThresholdLevel;                       /* ?????????????? */
    ADS_UL_THRESHOLD_STAT_STRU          stThresholdStatInfo;                    /* ???????????? */
}ADS_UL_DYNAMIC_ASSEM_INFO_STRU;

/*****************************************************************************
 ????????  : ADS_IPF_MEM_CFG_STRU
 ????????  : ????????????

  1.??    ??   : 2015??10??06??
    ??    ??   : A00165503
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usBlkNum;
    VOS_UINT16                          usBlkSize;
    VOS_UINT8                           ucPort;
    VOS_UINT8                           aucReserved[3];

} ADS_IPF_MEM_CFG_STRU;

/*****************************************************************************
 ????????  : ADS_IPF_MEM_POOL_CFG_STRU
 ????????  : ??????????????

  1.??    ??   : 2015??10??06??
    ??    ??   : A00165503
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEnable;
    ADS_IPF_MEM_CFG_STRU                astMemCfg[ADS_IPF_MEM_POOL_ID_BUTT];

} ADS_IPF_MEM_POOL_CFG_STRU;

/*****************************************************************************
 ????????  : ADS_IPF_MEM_POOL_CFG_STRU
 ????????  : ????????????

  1.??    ??   : 2015??10??06??
    ??    ??   : A00165503
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usBlkSize;
    VOS_UINT16                          usBlkNum;
    VOS_UINT8                           ucPort;
    VOS_UINT8                           aucReserved[3];
    IMM_ZC_HEAD_STRU                    stQue;

} ADS_IPF_MEM_POOL_STRU;

/*****************************************************************************
 ??????    : ADS_IPF_CTX_STRU
 ????????  : ADS??IPF????????????
   1.??    ??   : 2012??11??23??
     ??    ??   : L60609
     ????????   : DSDA Phase II
*****************************************************************************/
typedef struct
{
    IPF_CONFIG_ULPARAM_S                astIpfUlBdCfgParam[IPF_ULBD_DESC_SIZE]; /* ????BD DESC */
    IPF_RD_DESC_S                       astIpfDlRdDesc[IPF_DLRD_DESC_SIZE];     /* ????RD DESC */
    /* AD */
    IPF_AD_DESC_S                       astIpfDlAdDesc[ADS_DL_ADQ_MAX_NUM][IPF_DLAD0_DESC_SIZE];   /* ????AD DESC */
    ADS_IPF_BD_BUFF_STRU                astIpfUlBdBuff[IPF_ULBD_DESC_SIZE];     /* ????BD */
    IMM_ZC_HEAD_STRU                    stUlSrcMemFreeQue;                      /* IPF????????????BUFF */
    ADS_UL_DYNAMIC_ASSEM_INFO_STRU      stUlAssemParmInfo;                      /* ???????????????? */
    VOS_UINT32                          ulThredHoldNum;                         /* ?????????????? */
    VOS_UINT32                          ulProtectTmrLen;
    VOS_UINT8                           ucSendingFlg;                           /* ???????????? */
    VOS_UINT8                           aucRsv[3];

    VOS_UINT32                          ulWakeLockEnable;                       /* wake lock ???????? */

    struct wake_lock                    stUlBdWakeLock;                         /* wake lock BD */
    struct wake_lock                    stDlRdWakeLock;                         /* wake lock RD */

    struct wake_lock                    stRxWakeLock;                           /* wake lock RX */
    struct wake_lock                    stTxWakeLock;                           /* wake lock TX */

    VOS_UINT32                          ulUlBdWakeLockCnt;                      /* wake lock BD ???? */
    VOS_UINT32                          ulDlRdWakeLockCnt;                      /* wake lock BD ???? */

    VOS_UINT32                          ulRxWakeLockTimeout;                    /* wake lock RX ???????? */
    VOS_UINT32                          ulTxWakeLockTimeout;                    /* wake lock TX ???????? */

    VOS_UINT32                          ulTxWakeLockTmrLen;                     /* wake lock TX ???????? */
    VOS_UINT32                          ulRxWakeLockTmrLen;                     /* wake lock RX ???????? */

    struct device                       stDev;
#if (defined(CONFIG_BALONG_SPE))
    VOS_INT32                           lSpeWPort;
    ADS_IPF_MEM_POOL_CFG_STRU           stMemPoolCfg;
    ADS_IPF_MEM_POOL_STRU               astMemPool[ADS_IPF_MEM_POOL_ID_BUTT];
#endif

}ADS_IPF_CTX_STRU;

/*****************************************************************************
??????    : ADS_SPEC_CTX_STRU
????????  : ADS????????????????????

  1.??    ??   : 2012??11??23??
    ??    ??   : ????/l60609
    ????????   : DSDA Phase II: ????ADS????????????????????
*****************************************************************************/
typedef struct
{
    ADS_UL_CTX_STRU                     stAdsUlCtx;                             /* ?????????? */
    ADS_DL_CTX_STRU                     stAdsDlCtx;                             /* ?????????? */

}ADS_SPEC_CTX_STRU;

/*****************************************************************************
??????    : ADS_CTX_STRU
????????  : ADS??????

  1.??    ??   : 2011??12??6??
    ??    ??   : ????/l60609
    ????????   : ????ADS??????

  2.??    ??   : 2012??11??23??
    ??    ??   : L60609
    ????????   : DSDA Phase II
*****************************************************************************/
typedef struct
{
    ADS_SPEC_CTX_STRU                   astAdsSpecCtx[ADS_INSTANCE_MAX_NUM];    /* ???????????????????? */
    ADS_STATS_INFO_CTX_STRU             stDsFlowStatsCtx;                       /* ???????? */
    ADS_IPF_CTX_STRU                    stAdsIpfCtx;                            /* ??IPF???????????? */
    ADS_TIMER_CTX_STRU                  astAdsTiCtx[ADS_MAX_TIMER_NUM];         /* ???????????? */
    VOS_UINT8                           ucAdsCurInstanceIndex;                  /* ??????????index */
    VOS_UINT8                           ucUlResetFlag;
    VOS_UINT8                           aucRsv[6];
    VOS_SEM                             hULResetSem;                            /* ??????????????????UL????????  */
    VOS_SEM                             hDLResetSem;                            /* ??????????????????DL????????  */
}ADS_CTX_STRU;


/*****************************************************************************
  8 UNION????
*****************************************************************************/


/*****************************************************************************
  9 OTHERS????
*****************************************************************************/

extern VOS_UINT32                       g_ulAdsULTaskId;
extern VOS_UINT32                       g_ulAdsDLTaskId;
extern VOS_UINT32                       g_ulAdsULTaskReadyFlag;
extern VOS_UINT32                       g_ulAdsDLTaskReadyFlag;
extern ADS_CTX_STRU                     g_stAdsCtx;


/*****************************************************************************
  10 ????????
*****************************************************************************/

VOS_UINT32 ADS_UL_IsAllRabNotSndPermitFlg(VOS_VOID);
VOS_UINT32 ADS_UL_GetSpecInstanceSndPermitFlg(VOS_UINT8 ucInstanceIndex);
VOS_VOID ADS_DL_ProcEvent(VOS_UINT32 ulEvent);
VOS_VOID ADS_DL_SndEvent(VOS_UINT32 ulEvent);
ADS_DL_CTX_STRU* ADS_GetDlCtx(VOS_UINT8 ucInstanceIndex);
ADS_TIMER_CTX_STRU* ADS_GetTiCtx(VOS_VOID);
ADS_UL_CTX_STRU* ADS_GetUlCtx(VOS_UINT8 ucInstanceIndex);
VOS_VOID ADS_InitCtx(VOS_VOID);
VOS_VOID ADS_InitDlCtx(VOS_UINT8 ucInstance);
VOS_VOID ADS_InitIpfCtx(VOS_VOID);
VOS_VOID ADS_InitSpecCtx(VOS_VOID);
VOS_VOID ADS_InitStatsInfoCtx(VOS_VOID);
VOS_VOID ADS_InitTiCtx(VOS_VOID);
VOS_VOID ADS_InitUlCtx(VOS_UINT8 ucInstanceIndex);
VOS_UINT32 ADS_UL_CheckAllQueueEmpty(VOS_UINT8 ucInstanceIndex);
VOS_VOID ADS_UL_ClearQueue(
    VOS_UINT8                           ucRabId,
    IMM_ZC_HEAD_STRU                   *pstQueue
);
VOS_UINT32 ADS_UL_CreateQueue(
    VOS_UINT8                           ucInstanceIndex,
    VOS_UINT8                           ucRabId,
    ADS_QCI_TYPE_ENUM_UINT8             enPrio,
    ADS_CDS_IPF_PKT_TYPE_ENUM_UINT8     enPdpType,
    VOS_UINT8                           uc1XorHrpdUlIpfFlag
);
VOS_VOID ADS_UL_DestroyQueue(
    VOS_UINT8                           ucInstanceIndex,
    VOS_UINT8                           ucRabId
);
VOS_UINT32 ADS_UL_GetAllQueueDataNum(VOS_VOID);
VOS_UINT32 ADS_UL_GetInsertIndex(
    VOS_UINT8                           ucInstanceIndex,
    VOS_UINT8                           ucRabId
);
VOS_UINT32 ADS_UL_GetInstanceAllQueueDataNum(VOS_UINT8 ucInstanceIndex);
VOS_UINT32 ADS_UL_InsertQueue(
    VOS_UINT8                           ucInstance,
    IMM_ZC_STRU                        *pstData,
    VOS_UINT8                           ucRabId
);
VOS_UINT32 ADS_UL_IsQueueExistent(
    VOS_UINT8                           ucInstanceIndex,
    VOS_UINT8                           ucRabId
);
VOS_VOID ADS_UL_OrderQueueIndex(
    VOS_UINT8                           ucInstanceIndex,
    VOS_UINT8                           ucIndex
);
VOS_VOID ADS_UL_ProcEvent(VOS_UINT32 ulEvent);
VOS_VOID ADS_UL_SetProtectTmrLen(VOS_UINT32 ulTimerLen);
VOS_VOID ADS_UL_SetQueue(
    VOS_UINT8                           ucInstanceIndex,
    VOS_UINT8                           ucRabId,
    VOS_UINT8                           ucIsQueueValid,
    IMM_ZC_HEAD_STRU                   *pstUlQueue,
    ADS_QCI_TYPE_ENUM_UINT8             enPrio,
    ADS_CDS_IPF_PKT_TYPE_ENUM_UINT8     enPdpType,
    VOS_UINT8                           uc1XorHrpdUlIpfFlag
);
VOS_VOID ADS_UL_SndEvent(VOS_UINT32 ulEvent);
VOS_VOID ADS_UL_UpdateQueueInPdpDeactived(
    VOS_UINT8                           ucInstanceIndex,
    VOS_UINT8                           ucRabId
);
VOS_VOID ADS_UL_UpdateQueueInPdpModified(
           VOS_UINT8                           ucInstanceIndex,
           ADS_QCI_TYPE_ENUM_UINT8             enPrio,
           VOS_UINT8                           ucRabId
);
ADS_CTX_STRU* ADS_GetAllCtx(VOS_VOID);

VOS_UINT32 ADS_UL_EnableRxWakeLockTimeout(VOS_UINT32 ulValue);
VOS_UINT32 ADS_UL_WakeLockTimeout(VOS_VOID);
VOS_UINT32 ADS_UL_WakeLock(VOS_VOID);
VOS_UINT32 ADS_UL_WakeUnLock(VOS_VOID);
VOS_UINT32 ADS_DL_EnableTxWakeLockTimeout(VOS_UINT32 ulValue);
VOS_UINT32 ADS_DL_WakeLockTimeout(VOS_VOID);
VOS_UINT32 ADS_DL_WakeLock(VOS_VOID);
VOS_UINT32 ADS_DL_WakeUnLock(VOS_VOID);

VOS_VOID ADS_DL_InitFcAssemParamInfo(VOS_VOID);
VOS_SEM ADS_GetULResetSem(VOS_VOID);
VOS_SEM ADS_GetDLResetSem(VOS_VOID);
VOS_VOID ADS_DL_ResetFcAssemParamInfo(VOS_VOID);
VOS_VOID ADS_ResetSpecUlCtx(VOS_UINT8 ucInstance);
VOS_VOID ADS_ResetUlCtx(VOS_VOID);
VOS_VOID ADS_ResetSpecDlCtx(VOS_UINT8 ucInstance);
VOS_VOID ADS_ResetDlCtx(VOS_VOID);
VOS_VOID ADS_ResetIpfCtx(VOS_VOID);

VOS_UINT32 ADS_UL_IsAnyQueueExist(VOS_VOID);

VOS_UINT8 ADS_GetUlResetFlag(VOS_VOID);
VOS_VOID  ADS_SetUlResetFlag(VOS_UINT8 ucFlag);

VOS_UINT32 ADS_IPF_IsSpeMem(IMM_ZC_STRU *pstImmZc);
IMM_ZC_STRU* ADS_IPF_AllocMem(VOS_UINT32 ulPoolId, VOS_UINT32 ulLen, VOS_UINT32 ulReserveLen);
dma_addr_t ADS_IPF_GetMemDma(IMM_ZC_STRU *pstImmZc);
VOS_VOID ADS_IPF_SetMemDma(IMM_ZC_STRU *pstImmZc, dma_addr_t ulDmaAddr);
VOS_VOID ADS_IPF_MemMapRequset(IMM_ZC_STRU *pstImmZc, VOS_UINT32 ulLen, VOS_UINT8 ucIsIn);
VOS_VOID ADS_IPF_MemMapByDmaRequset(IMM_ZC_STRU *pstImmZc, VOS_UINT32 ulLen, VOS_UINT8 ucIsIn);
VOS_VOID ADS_IPF_MemUnmapRequset(IMM_ZC_STRU *pstImmZc, VOS_UINT32 ulLen, VOS_UINT8 ucIsIn);

#if (defined(CONFIG_BALONG_SPE))
VOS_VOID ADS_IPF_InitMemPoolCfg(VOS_VOID);
VOS_VOID ADS_IPF_CreateMemPool(VOS_VOID);
#endif


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


