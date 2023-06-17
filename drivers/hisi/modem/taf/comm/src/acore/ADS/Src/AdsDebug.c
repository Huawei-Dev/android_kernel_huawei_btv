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
    ??????????????????????.C??????????
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID                 PS_FILE_ID_ADS_DEBUG_C
/*lint +e767*/


/*****************************************************************************
  1 ??????????
*****************************************************************************/
#include "AdsDebug.h"
#include "AdsCtx.h"


/*****************************************************************************
  2 ????????????
*****************************************************************************/

/******************************************************************************
   3 ????????
******************************************************************************/


/******************************************************************************
   4 ????????????
******************************************************************************/

ADS_STATS_INFO_STRU                     g_stAdsStats;
ADS_LOG_LEVEL_ENUM_UINT32               g_enAdsLogLevel = ADS_LOG_LEVEL_ERROR;


/******************************************************************************
   5 ????????
******************************************************************************/

/*****************************************************************************
 ?? ?? ??  : ADS_SetWakeTxTmrLen
 ????????  : ????????????????????
 ????????  : VOS_UINT32 ulValue
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??9??22??
    ??    ??   : A00165503
    ????????   : ??????????

*****************************************************************************/
VOS_VOID ADS_SetTxWakeLockTmrLen(VOS_UINT32 ulValue)
{
    g_stAdsCtx.stAdsIpfCtx.ulTxWakeLockTmrLen = ulValue;
    return;
}

/*****************************************************************************
 ?? ?? ??  : ADS_SetWakeRxTmrLen
 ????????  : ????????????????????
 ????????  : VOS_UINT32 ulValue
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??9??22??
    ??    ??   : A00165503
    ????????   : ??????????

*****************************************************************************/
VOS_VOID ADS_SetRxWakeLockTmrLen(VOS_UINT32 ulValue)
{
    g_stAdsCtx.stAdsIpfCtx.ulRxWakeLockTmrLen = ulValue;
    return;
}

/*****************************************************************************
 ?? ?? ??  : ADS_SetMaxQueueLength
 ????????  : ??????????????????????????????????????
 ????????  : VOS_UINT32                          ulLength,
             VOS_UINT8                           ucInstanceIndex
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2012??9??3??
    ??    ??   : l60609
    ????????   : ??????????

*****************************************************************************/
VOS_VOID ADS_SetMaxQueueLength(
    VOS_UINT32                          ulLength,
    VOS_UINT8                           ucInstanceIndex
)
{
    g_stAdsCtx.astAdsSpecCtx[ucInstanceIndex].stAdsUlCtx.ulUlMaxQueueLength = ulLength;
}

/*****************************************************************************
 ?? ?? ??  : ADS_ShowEntityStats
 ????????  : ????ADS????????
 ????????  :
 ????????  : ??
 ?? ?? ??  :

 ????????  :
 ????????  :

 ????????  :
    1.??    ??   : 2012??04??12??
      ??    ??   : A00165503
      ????????   : ??????????

*****************************************************************************/
VOS_VOID ADS_ShowEntityStats(VOS_VOID)
{
    VOS_UINT8                           i;
    VOS_UINT8                           j;

    for (i = 0; i < ADS_INSTANCE_MAX_NUM; i++)
    {
        PS_PRINTF("ADS Modem ID %d\n", i);

        for (j = ADS_RAB_ID_MIN; j <= ADS_RAB_ID_MAX; j++)
        {
            if (VOS_NULL_PTR != g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.astAdsUlQueue[j].pstAdsUlLink)
            {
                PS_PRINTF("ADS Queue length is %d\n", IMM_ZcQueueLen(g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.astAdsUlQueue[j].pstAdsUlLink));
            }

            PS_PRINTF("ADS DL RabId is %d\r\n", g_stAdsCtx.astAdsSpecCtx[i].stAdsDlCtx.astAdsDlRabInfo[j - ADS_RAB_ID_OFFSET].ucRabId);
            PS_PRINTF("ADS DL Rcv Func is 0x%x\r\n", g_stAdsCtx.astAdsSpecCtx[i].stAdsDlCtx.astAdsDlRabInfo[j - ADS_RAB_ID_OFFSET].pRcvDlDataFunc);
        }
    }

    PS_PRINTF("ADS????????????????              %d\n",g_stAdsCtx.stAdsIpfCtx.ucSendingFlg);
    PS_PRINTF("\r\n");

    return;
}

/*****************************************************************************
 ?? ?? ??  : ADS_ShowEventProcStats
 ????????  : ????????????????
 ????????  : VOS_VOID
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??10??06??
    ??    ??   : A00165503
    ????????   : ??????????

*****************************************************************************/
VOS_VOID ADS_ShowEventProcStats(VOS_VOID)
{
    PS_PRINTF("=============================================\n");
    PS_PRINTF("ADS EVENT PROC STATS                         \n");
    PS_PRINTF("=============================================\n");
    PS_PRINTF("ULQueNonEmptyTrigEvent           %10u\n", g_stAdsStats.stUlComStatsInfo.ulULQueNonEmptyTrigEvent);
    PS_PRINTF("ULQueFullTrigEvent               %10u\n", g_stAdsStats.stUlComStatsInfo.ulULQueFullTrigEvent);
    PS_PRINTF("ULQueHitThresTrigEvent           %10u\n", g_stAdsStats.stUlComStatsInfo.ulULQueHitThresTrigEvent);
    PS_PRINTF("ULTmrHitThresTrigEvent           %10u\n", g_stAdsStats.stUlComStatsInfo.ulULTmrHitThresTrigEvent);
    PS_PRINTF("UL10MsTmrTrigEvent               %10u\n", g_stAdsStats.stUlComStatsInfo.ulUL10MsTmrTrigEvent);
    PS_PRINTF("ULSpeIntTrigEvent                %10u\n", g_stAdsStats.stUlComStatsInfo.ulULSpeIntTrigEvent);
    PS_PRINTF("ULProcEventNum                   %10u\n", g_stAdsStats.stUlComStatsInfo.ulULProcEventNum);
    PS_PRINTF("DLRcvIpfRdIntNum                 %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLRcvIpfRdIntNum);
    PS_PRINTF("DLCCoreResetTrigRdEvent          %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLCCoreResetTrigEvent);
    PS_PRINTF("DLProcIpfRdEventNum              %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLProcIpfRdEventNum);
    PS_PRINTF("DLRcvIpfAdqEmptyIntNum           %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLRcvIpfAdqEmptyIntNum);
    PS_PRINTF("DLRecycleMemTrigAdEvent          %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLRecycleMemTrigEvent);
    PS_PRINTF("DLProcIpfAdEventNum              %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLProcIpfAdEventNum);
    PS_PRINTF("\r\n");

    return;
}

/*****************************************************************************
 ?? ?? ??  : ADS_ShowULPktProcStats
 ????????  : ????????????????????
 ????????  : VOS_VOID
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??10??06??
    ??    ??   : A00165503
    ????????   : ??????????

*****************************************************************************/
VOS_VOID ADS_ShowULPktProcStats(VOS_VOID)
{
    VOS_UINT8                           ucInstance;

    PS_PRINTF("=============================================\n");
    PS_PRINTF("ADS UL PTK PROC STATS                        \n");
    PS_PRINTF("=============================================\n");
    PS_PRINTF("ULRmnetRxPktNum                  %10u\n", g_stAdsStats.stUlComStatsInfo.ulULRmnetRxPktNum);
    PS_PRINTF("ULRmnetEnQueSuccNum              %10u\n", g_stAdsStats.stUlComStatsInfo.ulULRmnetEnQueSuccNum);
    PS_PRINTF("ULRmnetEnQueFailNum              %10u\n", g_stAdsStats.stUlComStatsInfo.ulULRmnetEnQueFailNum);
    PS_PRINTF("ULPktEnQueSuccNum                %10u\n", g_stAdsStats.stUlComStatsInfo.ulULPktEnQueSuccNum);
    PS_PRINTF("ULPktEnQueFailNum                %10u\n", g_stAdsStats.stUlComStatsInfo.ulULPktEnQueFailNum);

    for (ucInstance = 0; ucInstance < ADS_INSTANCE_MAX_NUM; ucInstance++)
    {
        PS_PRINTF("ULBuffPktNum[MDOEM:%d]            %10u\n", ucInstance, ADS_UL_GetInstanceAllQueueDataNum(ucInstance));
    }

    PS_PRINTF("ULBuffThresholdCurrent           %10u\n", g_stAdsCtx.stAdsIpfCtx.ulThredHoldNum);
    PS_PRINTF("ULBuffThreshold1                 %10u\n", g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stThresholdLevel.ulThreshold1);
    PS_PRINTF("ULBuffThreshold2                 %10u\n", g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stThresholdLevel.ulThreshold1);
    PS_PRINTF("ULBuffThreshold3                 %10u\n", g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stThresholdLevel.ulThreshold1);
    PS_PRINTF("ULBuffThreshold4                 %10u\n", g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stThresholdLevel.ulThreshold1);
    PS_PRINTF("ULWaterLevel1HitNum              %10u\n", g_stAdsStats.stUlComStatsInfo.ulULWmLevel1HitNum);
    PS_PRINTF("ULWaterLevel2HitNum              %10u\n", g_stAdsStats.stUlComStatsInfo.ulULWmLevel2HitNum);
    PS_PRINTF("ULWaterLevel3HitNum              %10u\n", g_stAdsStats.stUlComStatsInfo.ulULWmLevel3HitNum);
    PS_PRINTF("ULWaterLevel4HitNum              %10u\n", g_stAdsStats.stUlComStatsInfo.ulULWmLevel4HitNum);
    PS_PRINTF("\r\n");

    return;
}

/*****************************************************************************
 ?? ?? ??  : ADS_ShowULBdProcStats
 ????????  : ????????BD????????
 ????????  : VOS_VOID
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??10??06??
    ??    ??   : A00165503
    ????????   : ??????????

*****************************************************************************/
VOS_VOID ADS_ShowULBdProcStats(VOS_VOID)
{
    PS_PRINTF("=============================================\n");
    PS_PRINTF("ADS UL BD PROC STATS                         \n");
    PS_PRINTF("=============================================\n");
    PS_PRINTF("ULBdqCfgIpfHaveNoBd              %10u\n", g_stAdsStats.stUlComStatsInfo.ulULBdqCfgIpfHaveNoBd);
    PS_PRINTF("ULBdqCfgBdSuccNum                %10u\n", g_stAdsStats.stUlComStatsInfo.ulULBdqCfgBdSuccNum);
    PS_PRINTF("ULBdqCfgBdFailNum                %10u\n", g_stAdsStats.stUlComStatsInfo.ulULBdqCfgBdFailNum);
    PS_PRINTF("ULBdqCfgIpfSuccNum               %10u\n", g_stAdsStats.stUlComStatsInfo.ulULBdqCfgIpfSuccNum);
    PS_PRINTF("ULBdqCfgIpfFailNum               %10u\n", g_stAdsStats.stUlComStatsInfo.ulULBdqCfgIpfFailNum);
    PS_PRINTF("ULBdqSaveSrcMemNum               %10u\n", g_stAdsStats.stUlComStatsInfo.ulULBdqSaveSrcMemNum);
    PS_PRINTF("ULBdqFreeSrcMemNum               %10u\n", g_stAdsStats.stUlComStatsInfo.ulULBdqFreeSrcMemNum);
    PS_PRINTF("ULBdqFreeSrcMemErr               %10u\n", g_stAdsStats.stUlComStatsInfo.ulULBdqFreeSrcMemErr);
    PS_PRINTF("\r\n");

    return;
}

/*****************************************************************************
 ?? ?? ??  : ADS_ShowDLPktProcStats
 ????????  : ????????????????????
 ????????  : VOS_VOID
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??10??26??
    ??    ??   : A00165503
    ????????   : ??????????

*****************************************************************************/
VOS_VOID ADS_ShowDLPktProcStats(VOS_VOID)
{
    PS_PRINTF("=============================================\n");
    PS_PRINTF("ADS DL PKT PROC STATS                        \n");
    PS_PRINTF("=============================================\n");
    PS_PRINTF("DLRmnetTxPktNum                  %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLRmnetTxPktNum);
    PS_PRINTF("DLRmnetModemIdErrNum             %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLRmnetModemIdErrNum);
    PS_PRINTF("DLRmnetRabIdErrNum               %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLRmnetRabIdErrNum);
    PS_PRINTF("DLRmnetNoFuncFreePktNum          %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLRmnetNoFuncFreePktNum);
    PS_PRINTF("\r\n");

    return;
 }

/*****************************************************************************
 ?? ?? ??  : ADS_ShowDLRdProcStats
 ????????  : ????????RD????????
 ????????  : VOS_VOID
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??10??06??
    ??    ??   : A00165503
    ????????   : ??????????

*****************************************************************************/
VOS_VOID ADS_ShowDLRdProcStats(VOS_VOID)
{
    PS_PRINTF("=============================================\n");
    PS_PRINTF("ADS DL RD PROC STATS                         \n");
    PS_PRINTF("=============================================\n");
    PS_PRINTF("DLRdqRxRdNum                     %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLRdqRxRdNum);
    PS_PRINTF("DLRdqGetRd0Num                   %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLRdqGetRd0Num);
    PS_PRINTF("DLRdqTransMemFailNum             %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLRdqTransMemFailNum);
    PS_PRINTF("DLRdqRxNormPktNum                %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLRdqRxNormPktNum);
    PS_PRINTF("DLRdqRxNdPktNum                  %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLRdqRxNdPktNum);
    PS_PRINTF("DLRdqRxDhcpPktNum                %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLRdqRxDhcpPktNum);
    PS_PRINTF("DLRdqRxErrPktNum                 %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLRdqRxErrPktNum);
    PS_PRINTF("DLRdqFilterErrNum                %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLRdqFilterErrNum);
    PS_PRINTF("\r\n");

    return;
}

/*****************************************************************************
 ?? ?? ??  : ADS_ShowDLAdProcStats
 ????????  : ????????AD????????
 ????????  : VOS_VOID
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??10??06??
    ??    ??   : A00165503
    ????????   : ??????????

*****************************************************************************/
VOS_VOID ADS_ShowDLAdProcStats(VOS_VOID)
{
    PS_PRINTF("=============================================\n");
    PS_PRINTF("ADS DL ADQ PROC STATS                        \n");
    PS_PRINTF("=============================================\n");
    PS_PRINTF("DLAdqAllocSysMemSuccNum          %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLAdqAllocSysMemSuccNum);
    PS_PRINTF("DLAdqAllocSysMemFailNum          %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLAdqAllocSysMemFailNum);
    PS_PRINTF("DLAdqAllocMemSuccNum             %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLAdqAllocMemSuccNum);
    PS_PRINTF("DLAdqAllocMemFailNum             %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLAdqAllocMemFailNum);
    PS_PRINTF("DLAdqFreeMemNum                  %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLAdqFreeMemNum);
    PS_PRINTF("DLAdqRecycleMemSuccNum           %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLAdqRecycleMemSuccNum);
    PS_PRINTF("DLAdqRecycleMemFailNum           %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLAdqRecycleMemFailNum);
    PS_PRINTF("DLAdqGetFreeAdSuccNum            %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLAdqGetFreeAdSuccNum);
    PS_PRINTF("DLAdqGetFreeAdFailNum            %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLAdqGetFreeAdFailNum);
    PS_PRINTF("DLAdqCfgAdNum                    %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLAdqCfgAdNum);
    PS_PRINTF("DLAdqCfgAd0Num                   %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLAdqCfgAd0Num);
    PS_PRINTF("DLAdqCfgAd1Num                   %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLAdqCfgAd1Num);
    PS_PRINTF("DLAdqCfgIpfSuccNum               %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLAdqCfgIpfSuccNum);
    PS_PRINTF("DLAdqCfgIpfFailNum               %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLAdqCfgIpfFailNum);
    PS_PRINTF("DLAdqStartEmptyTmrNum            %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLAdqStartEmptyTmrNum);
    PS_PRINTF("DLAdqEmptyTmrTimeoutNum          %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLAdqEmptyTmrTimeoutNum);
    PS_PRINTF("DLAdqRcvAd0EmptyIntNum           %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLAdqRcvAd0EmptyIntNum);
    PS_PRINTF("DLAdqRcvAd1EmptyIntNum           %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLAdqRcvAd1EmptyIntNum);
    PS_PRINTF("\r\n");

    return;
}

/*****************************************************************************
 ?? ?? ??  : ADS_ShowResetProcStats
 ????????  : ????C??????????????
 ????????  : VOS_VOID
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??10??06??
    ??    ??   : A00165503
    ????????   : ??????????

*****************************************************************************/
VOS_VOID ADS_ShowResetProcStats(VOS_VOID)
{
    PS_PRINTF("=============================================\n");
    PS_PRINTF("ADS RESET PROC STATS                         \n");
    PS_PRINTF("=============================================\n");
    PS_PRINTF("ULResetSem                       %p\n",   g_stAdsCtx.hULResetSem);
    PS_PRINTF("ULResetCreateSemFailNum          %10u\n", g_stAdsStats.stResetStatsInfo.ulULResetCreateSemFailNum);
    PS_PRINTF("ULResetLockFailNum               %10u\n", g_stAdsStats.stResetStatsInfo.ulULResetLockFailNum);
    PS_PRINTF("ULResetSuccNum                   %10u\n", g_stAdsStats.stResetStatsInfo.ulULResetSuccNum);
    PS_PRINTF("DLResetSem                       %p\n",   g_stAdsCtx.hDLResetSem);
    PS_PRINTF("DLResetCreateSemFailNum          %10u\n", g_stAdsStats.stResetStatsInfo.ulDLResetCreateSemFailNum);
    PS_PRINTF("DLResetLockFailNum               %10u\n", g_stAdsStats.stResetStatsInfo.ulDLResetLockFailNum);
    PS_PRINTF("DLResetSuccNum                   %10u\n", g_stAdsStats.stResetStatsInfo.ulDLResetSuccNum);
    PS_PRINTF("\r\n");

    return;
}

/*****************************************************************************
 ?? ?? ??  : ADS_Help
 ????????  : ADS????????????
 ????????  : VOS_VOID
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2012??01??12??
    ??    ??   : S62952
    ????????   : ??????????

*****************************************************************************/
VOS_VOID ADS_Help(VOS_VOID)
{
    PS_PRINTF("=================================================\n");
    PS_PRINTF("ADS DEBUG ENTRY                                  \n");
    PS_PRINTF("=================================================\n");
    PS_PRINTF("ADS_ShowEntityStats          ????????????\n");
    PS_PRINTF("ADS_ShowEventProcStats       ????????????????\n");
    PS_PRINTF("ADS_ShowULPktProcStats       ????????????????????\n");
    PS_PRINTF("ADS_ShowULBdProcStats        ????????BD????????\n");
    PS_PRINTF("ADS_ShowDLPktProcStats       ????????????????????\n");
    PS_PRINTF("ADS_ShowDLRdProcStats        ????????RD????????\n");
    PS_PRINTF("ADS_ShowDLAdProcStats        ????????AD????????\n");
    PS_PRINTF("ADS_ShowResetProcStats       ????C??????????????\n");
    PS_PRINTF("ADS_ResetDebugInfo           ????????????\n");
    PS_PRINTF("\r\n");

    return;
}

/*****************************************************************************
 ?? ?? ??  : ADS_ResetDebugInfo
 ????????  : ????ADS??????????????
 ????????  : VOS_VOID
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2013??09??13??
    ??    ??   : f00179208
    ????????   : ??????????

*****************************************************************************/
VOS_VOID ADS_ResetDebugInfo(VOS_VOID)
{
    PS_MEM_SET(&g_stAdsStats.stUlComStatsInfo, 0x00, sizeof(ADS_UL_COM_STATS_INFO_STRU));
    PS_MEM_SET(&g_stAdsStats.stDlComStatsInfo, 0x00, sizeof(ADS_DL_COM_STATS_INFO_STRU));
    return;
}

/*****************************************************************************
 ?? ?? ??  : ADS_SetFlowDebugFlag
 ????????  : ????Flow Debug????

 ????????  :
 ????????  : ??
 ?? ?? ??  :
 ????????  :
 ????????  :

 ????????  :
    1.??    ??   : 2014??6??9??
      ??    ??   : c00199705
      ????????   : ??????????

*****************************************************************************/
VOS_VOID ADS_SetFlowDebugFlag(VOS_UINT32  ulFlowDebugFlag)
{
    switch (ulFlowDebugFlag)
    {
        case ADS_FLOW_DEBUG_DL_ON:
            g_stAdsStats.stDlComStatsInfo.ulDLFlowDebugFlag     = PS_TRUE;
            g_stAdsStats.stUlComStatsInfo.ulULFlowDebugFlag     = PS_FALSE;
            g_stAdsStats.stDlComStatsInfo.ulDLFlowRptThreshold  = ADS_FLOW_DL_DEFAULT_RPT_THRESHOLD;
            break;

        case ADS_FLOW_DEBUG_UL_ON:
            g_stAdsStats.stDlComStatsInfo.ulDLFlowDebugFlag     = PS_FALSE;
            g_stAdsStats.stUlComStatsInfo.ulULFlowDebugFlag     = PS_TRUE;
            g_stAdsStats.stUlComStatsInfo.ulULFlowRptThreshold  = ADS_FLOW_UL_DEFAULT_RPT_THRESHOLD;
            break;

        case ADS_FLOW_DEBUG_ALL_ON:
            g_stAdsStats.stDlComStatsInfo.ulDLFlowDebugFlag     = PS_TRUE;
            g_stAdsStats.stUlComStatsInfo.ulULFlowDebugFlag     = PS_TRUE;
            g_stAdsStats.stDlComStatsInfo.ulDLFlowRptThreshold  = ADS_FLOW_DL_DEFAULT_RPT_THRESHOLD;
            g_stAdsStats.stUlComStatsInfo.ulULFlowRptThreshold  = ADS_FLOW_UL_DEFAULT_RPT_THRESHOLD;
            break;

        default:
            g_stAdsStats.stDlComStatsInfo.ulDLFlowDebugFlag     = PS_FALSE;
            g_stAdsStats.stUlComStatsInfo.ulULFlowDebugFlag     = PS_FALSE;
            break;
    }

    return;
}

/*****************************************************************************
 ?? ?? ??  : ADS_SetFlowDLRptThreshold
 ????????  : ????????????????????

 ????????  :
 ????????  : ??
 ?? ?? ??  :
 ????????  :
 ????????  :

 ????????  :
    1.??    ??   : 2014??6??9??
      ??    ??   : c00199705
      ????????   : ??????????

*****************************************************************************/
VOS_VOID ADS_SetFlowDLRptThreshold(VOS_UINT32  ulFlowDLRptThreshold)
{
    g_stAdsStats.stDlComStatsInfo.ulDLFlowRptThreshold  = ulFlowDLRptThreshold;
    return;
}

/*****************************************************************************
 ?? ?? ??  : ADS_SetFlowUlRptThreshold
 ????????  : ????????????????????

 ????????  :
 ????????  : ??
 ?? ?? ??  :
 ????????  :
 ????????  :

 ????????  :
    1.??    ??   : 2014??6??9??
      ??    ??   : c00199705
      ????????   : ??????????

*****************************************************************************/
VOS_VOID ADS_SetFlowULRptThreshold(VOS_UINT32  ulFlowULRptThreshold)
{
    g_stAdsStats.stUlComStatsInfo.ulULFlowRptThreshold  = ulFlowULRptThreshold;
    return;
}

/*****************************************************************************
 ?? ?? ??  : ADS_DLFlowAdd
 ????????  : ADS????????????

 ????????  :
 ????????  : ??
 ?? ?? ??  :
 ????????  :
 ????????  :

 ????????  :
    1.??    ??   : 2014??6??9??
      ??    ??   : c00199705
      ????????   : ??????????

*****************************************************************************/
VOS_VOID ADS_DLFlowAdd(VOS_UINT32 ulSduLen)
{
    if (PS_TRUE == g_stAdsStats.stDlComStatsInfo.ulDLFlowDebugFlag)
    {
        /* ???????? */
        g_stAdsStats.stDlComStatsInfo.ulDLFlowInfo += ulSduLen;

        /* ???????????? */
        if (g_stAdsStats.stDlComStatsInfo.ulDLFlowInfo >= g_stAdsStats.stDlComStatsInfo.ulDLFlowRptThreshold)
        {
            g_stAdsStats.stDlComStatsInfo.ulDLEndSlice   = VOS_GetSlice();

            PS_PRINTF("ADS DL Flow Info = %10d, Pkt Num = %10d, Slice = %10d, Time = %10d\n",
                g_stAdsStats.stDlComStatsInfo.ulDLFlowInfo,
                g_stAdsStats.stDlComStatsInfo.ulDLRmnetTxPktNum, g_stAdsStats.stDlComStatsInfo.ulDLEndSlice,
                (g_stAdsStats.stDlComStatsInfo.ulDLEndSlice - g_stAdsStats.stDlComStatsInfo.ulDLStartSlice));

            g_stAdsStats.stDlComStatsInfo.ulDLStartSlice = g_stAdsStats.stDlComStatsInfo.ulDLEndSlice;
            g_stAdsStats.stDlComStatsInfo.ulDLFlowInfo   = 0;
        }
    }

    return;
}

/*****************************************************************************
 ?? ?? ??  : ADS_ULFlowAdd
 ????????  : ADS????????????

 ????????  :
 ????????  : ??
 ?? ?? ??  :
 ????????  :
 ????????  :

 ????????  :
    1.??    ??   : 2014??6??9??
      ??    ??   : c00199705
      ????????   : ??????????

*****************************************************************************/
VOS_VOID ADS_ULFlowAdd(VOS_UINT32 ulSduLen)
{
    if (PS_TRUE == g_stAdsStats.stUlComStatsInfo.ulULFlowDebugFlag)
    {
        /* ???????? */
        g_stAdsStats.stUlComStatsInfo.ulULFlowInfo += ulSduLen;

        /* ???????????? */
        if (g_stAdsStats.stUlComStatsInfo.ulULFlowInfo >= g_stAdsStats.stUlComStatsInfo.ulULFlowRptThreshold)
        {
            g_stAdsStats.stUlComStatsInfo.ulULEndSlice   = VOS_GetSlice();

            PS_PRINTF("ADS UL Flow Info = %10d, Pkt Num = %10d, Slice = %10d, Time = %10d\n",
                g_stAdsStats.stUlComStatsInfo.ulULFlowInfo,
                g_stAdsStats.stUlComStatsInfo.ulULRmnetRxPktNum, g_stAdsStats.stUlComStatsInfo.ulULEndSlice,
                (g_stAdsStats.stUlComStatsInfo.ulULEndSlice - g_stAdsStats.stUlComStatsInfo.ulULStartSlice));

            g_stAdsStats.stUlComStatsInfo.ulULStartSlice = g_stAdsStats.stUlComStatsInfo.ulULEndSlice;
            g_stAdsStats.stUlComStatsInfo.ulULFlowInfo   = 0;
        }
    }

    return;
}

/*****************************************************************************
 ?? ?? ??  : ADS_LogPrintf
 ????????  : LOG????
 ????????  : enLevel --- ????????
             pcFmt   --- ????
             ...
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??10??06??
    ??    ??   : A00165503
    ????????   : ??????????

*****************************************************************************/
/*lint -esym(960,69)*/
VOS_VOID ADS_LogPrintf(ADS_LOG_LEVEL_ENUM_UINT32 enLevel, VOS_CHAR *pcFmt, ...)
{
    VOS_CHAR                            acBuff[ADS_LOG_BUFF_LEN] = {0};
    va_list                             pArgList;
    VOS_UINT32                          ulPrintLength = 0;

    /* ???????????? */
    if (enLevel < g_enAdsLogLevel)
    {
        return;
    }

    /*lint -e586 -e713 -e438 -e507*/
    va_start(pArgList, pcFmt);
    ulPrintLength += VOS_nvsprintf(acBuff, ADS_LOG_BUFF_LEN, pcFmt, pArgList);
    va_end(pArgList);
    /*lint +e586 +e713 +e438 +e507*/

    if (ulPrintLength > (ADS_LOG_BUFF_LEN - 1))
    {
        ulPrintLength = ADS_LOG_BUFF_LEN - 1;
    }

    acBuff[ulPrintLength] = '\0';

    printk(KERN_ERR "%s", acBuff);

    return ;
}
/*lint +esym(960,69)*/





