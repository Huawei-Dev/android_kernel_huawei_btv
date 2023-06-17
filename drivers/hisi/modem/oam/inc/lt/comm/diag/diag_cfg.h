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

#ifndef __DIAG_CFG_H__
#define __DIAG_CFG_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "vos.h"
#include  "VosPidDef.h"
#include  "msp_nv_def.h"
#include  "msp_diag.h"
#include  "diag_common.h"

#pragma pack(4)

/*****************************************************************************
  2 macro
*****************************************************************************/

#define DIAG_CFG_PID_NUM                        (VOS_PID_BUTT - VOS_PID_DOPRAEND)

#define DIAG_CFG_MODULE_IS_VALID(ulModuleId)    ((ulModuleId < VOS_PID_BUTT)&&(ulModuleId >= VOS_PID_DOPRAEND))
#define DIAG_CFG_MODULE_IS_INVALID(ulModuleId)  ((ulModuleId >= VOS_PID_BUTT)||(ulModuleId < VOS_PID_DOPRAEND))

#define DIAG_CFG_LAYER_MODULE_IS_ACORE(ulModuleId) ((ulModuleId >= VOS_PID_CPU_ID_1_DOPRAEND)&&(ulModuleId < VOS_CPU_ID_1_PID_BUTT))
#define DIAG_CFG_LAYER_MODULE_IS_CCORE(ulModuleId) ((ulModuleId >= VOS_PID_CPU_ID_0_DOPRAEND)&&(ulModuleId < VOS_CPU_ID_0_PID_BUTT))

#define DIAG_CFG_LAYER_MODULE_ACORE_OFFSET(ulModuleId)  (ulModuleId - VOS_PID_CPU_ID_1_DOPRAEND)
#define DIAG_CFG_LAYER_MODULE_CCORE_OFFSET(ulModuleId)  (ulModuleId - VOS_PID_CPU_ID_0_DOPRAEND)

#define DIAG_CFG_INIT                0x00000001

#define DIAG_CFG_CONN                0x00000002

#define DIAG_CFG_LT_AIR              0x00000004

#define DIAG_CFG_GU_AIR              0x00000008

#define DIAG_CFG_EVT                 0x00000010

#define DIAG_CMD_DATA_MAX_LEN                       (4096)

#define DIAG_CFG_CAT_CFG_NUM                        (50)

#define DIAG_CMD_CFG_SWT_CLOSE                      (0x00000000)
#define DIAG_CMD_CFG_SWT_OPEN                       (0x80000000)

#define DIAG_GET_PRINT_CFG_SWT(swt)                 (swt>>24)

#define DIAG_GET_CFG_SWT(swt)   ((DIAG_CMD_CFG_SWT_OPEN == swt) ? DIAG_CFG_SWT_OPEN : DIAG_CFG_SWT_CLOSE )

#define DIAG_EVENT_MODID(id)    (id & 0x7fffffff)
#define DIAG_EVENT_SWT(id)      (id >> 31)

#define DIAG_CFG_PRINT_TOTAL_MODULE_SWT_NOT_USE     (0xFFFFFFFF)
#define DIAG_CFG_PRINT_TOTAL_MODULE                 (0xFFFFFFFF)

#define DIAG_CMD_LAYER_MOD_SRC                      (0)
#define DIAG_CMD_LAYER_MOD_DST                      (1)

#define DIAG_GET_MODEM_INFO                         (0x02000002)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
enum ENUM_DIAG_CFG_BIT
{
    DIAG_CFG_INIT_BIT     = 0,
    DIAG_CFG_CONN_BIT,
    DIAG_CFG_LT_AIR_BIT,
    DIAG_CFG_GU_AIR_BIT,
    DIAG_CFG_EVENT_BIT,
    DIAG_CFG_BIT_BUTT
};
typedef VOS_UINT32 ENUM_DIAG_CFG_BIT_U32 ;

enum ENUM_DIAG_CFG_SWT
{
    DIAG_CFG_SWT_CLOSE  = 0,
    DIAG_CFG_SWT_OPEN,
    DIAG_CFG_SWT_BUTT
};
typedef VOS_UINT8 ENUM_DIAG_CFG_SWT_U8;

typedef enum
{
    SYSVIEW_MEM_TRACE       = 1,
    SYSVIEW_CPU_INFO        = 2,
    SYSVIEW_TASK_INFO       = 3,
    SYSVIEW_INT_LOCK_INFO   = 4,
    SYSVIEW_SWT_ALL         = 0xff,
    SYSVIEW_SWT_MAX
} BSP_SYSVIEW_TYPE_E;

typedef struct
{
    VOS_UINT32 ulMajorMinorVersion;
    VOS_UINT32 ulRevisionVersion;
    VOS_UINT32 ulBuildVersion;
} DIAG_CMD_UE_SOFT_VERSION_STRU;

typedef struct
{
    VOS_UINT16 usVVerNo;
    VOS_UINT16 usRVerNo;
    VOS_UINT16 usCVerNo;
    VOS_UINT16 usBVerNo;
    VOS_UINT16 usSpcNo;
    VOS_UINT16 usHardwareVerNo;
    VOS_UINT32 ulProductNo;
} DIAG_CMD_UE_BUILD_VER_STRU;

typedef struct
{
    VOS_UINT32  ulDrxControlFlag:1;
    VOS_UINT32  ulPortFlag      :1;
    VOS_UINT32  ulOmUnifyFlag   :1;
    VOS_UINT32  ulReserved      :29;
}DIAG_CONTROLFLAG_STRU;

typedef struct
{
    VOS_UINT32 ulAuid;
    VOS_UINT32 ulSn;

    VOS_UINT32 ulRc;
    VOS_CHAR szImei[16];
    DIAG_CMD_UE_SOFT_VERSION_STRU stUeSoftVersion;
    DIAG_CMD_UE_BUILD_VER_STRU stBuildVersion;
    VOS_UINT32 ulChipBaseAddr;
    union
    {
        VOS_UINT32              UintValue;
        DIAG_CONTROLFLAG_STRU   CtrlFlag;
    } diag_cfg;
    VOS_UINT32 ulLpdMode;
    NV_ITEM_AGENT_FLAG_STRU stAgentFlag;
    VOS_CHAR szProduct[64];
} DIAG_CMD_HOST_CONNECT_CNF_STRU;

typedef struct
{
    VOS_UINT32 ulAuid;
    VOS_UINT32 ulSn;
    VOS_UINT32 ulRc;
} DIAG_CMD_HOST_DISCONNECT_CNF_STRU;

typedef struct
{
    VOS_UINT32 ulAuid;
    VOS_UINT32 ulSn;
    VOS_UINT32 ulInfo;
} DIAG_CMD_GET_MDM_INFO_REQ_STRU;

typedef struct
{
    VOS_UINT32                  ulRsv;
} DIAG_MSG_TO_OTHERCPU_DISCONN_STRU;

typedef struct
{
    VOS_UINT32 ulReserved;
} DIAG_CMD_REPLAY_SET_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulAuid;
    VOS_UINT32 ulSn;
    VOS_UINT32 ulRet;
} DIAG_CMD_REPLAY_SET_CNF_STRU;

typedef struct
{
    VOS_UINT32 ulModuleId;
    VOS_UINT32 ulLevelFilter;
} DIAG_CMD_LOG_CAT_PRINT_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulAuid;
    VOS_UINT32 ulSn;
    VOS_UINT32 ulRc;
    VOS_UINT32 ulModuleId;
} DIAG_CMD_LOG_CAT_PRINT_CNF_STRU;

typedef struct
{
    VOS_UINT32 ulModuleId;
    VOS_UINT32 ulIsDestModule;
    VOS_UINT32 ulSwitch;
} DIAG_CMD_LOG_CAT_LAYER_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulAuid;
    VOS_UINT32 ulSn;
    VOS_UINT32 ulRc;
    VOS_UINT32 ulModuleId;
} DIAG_CMD_LOG_CAT_LAYER_CNF_STRU;

typedef struct
{
    VOS_UINT32 ulSwitch;
    VOS_UINT32 ulGuSwitch;
} DIAG_CMD_LOG_CAT_AIR_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulAuid;
    VOS_UINT32 ulSn;
    VOS_UINT32 ulRc;
} DIAG_CMD_LOG_CAT_AIR_CNF_STRU;

typedef struct
{
    VOS_UINT32 ulSwt;
    VOS_UINT32 ulCount;
    VOS_UINT32 aulModuleId[0];
} DIAG_CMD_LOG_CAT_EVENT_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulAuid;
    VOS_UINT32 ulSn;
    VOS_UINT32 ulRc;
} DIAG_CMD_LOG_CAT_EVENT_CNF_STRU;

typedef struct
{
    VOS_UINT32 ulId;
    VOS_UINT32 ulCategory;
    VOS_UINT32 ulSwitch;
} DIAG_CMD_LOG_CAT_CFG_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulAuid;
    VOS_UINT32 ulSn;
    VOS_UINT32 ulRc;
    VOS_UINT32 ulId;
} DIAG_CMD_LOG_CAT_CFG_CNF_STRU;

typedef struct
{
    VOS_UINT32 ulId;
    VOS_UINT32 ulSwt;
}DIAG_CFG_LOG_CAT_MSG_CFG_STRU;

typedef struct
{
    VOS_UINT32 ulCatId;
    VOS_UINT32 ulCfgCnt;
    DIAG_CFG_LOG_CAT_MSG_CFG_STRU astMsgCfgList[DIAG_CFG_CAT_CFG_NUM];
}DIAG_CFG_LOG_CAT_CFG_STRU;

typedef struct
{
    VOS_UINT32  ulAuid;
    VOS_UINT32  ulSn;
    VOS_UINT    ulErrcode;
    VOS_UINT    ulGuTimeStampInitValue;
    VOS_UINT64  ulTLTimeStampInitValue;
}DIAG_TIMESTAMP_CNF_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern VOS_UINT32 g_ulDiagCfgInfo;

extern VOS_UINT8 g_ALayerSrcModuleCfg[VOS_CPU_ID_1_PID_BUTT - VOS_PID_CPU_ID_1_DOPRAEND];
extern VOS_UINT8 g_CLayerSrcModuleCfg[VOS_CPU_ID_0_PID_BUTT - VOS_PID_CPU_ID_0_DOPRAEND];
extern VOS_UINT8 g_ALayerDstModuleCfg[VOS_CPU_ID_1_PID_BUTT - VOS_PID_CPU_ID_1_DOPRAEND];
extern VOS_UINT8 g_CLayerDstModuleCfg[VOS_CPU_ID_0_PID_BUTT - VOS_PID_CPU_ID_0_DOPRAEND];

extern VOS_UINT8 g_PrintModuleCfg[DIAG_CFG_PID_NUM];
extern VOS_UINT32 g_PrintTotalCfg;
extern DIAG_CFG_LOG_CAT_CFG_STRU g_stMsgCfg;

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
*****************************************************************************/

extern VOS_VOID diag_CfgResetAllSwt(VOS_VOID);
extern VOS_UINT32 diag_CfgSetGlobalBitValue(VOS_UINT32* pstDiagGlobal,ENUM_DIAG_CFG_BIT_U32 enBit,ENUM_DIAG_CFG_SWT_U8 enSwtich);
extern VOS_UINT32 diag_CfgSetLayerSwt(DIAG_CMD_LOG_CAT_LAYER_REQ_STRU* pstLayerReq, VOS_UINT32 ulCfgSize);
extern VOS_UINT32 diag_CfgSetMsgSwt(DIAG_CMD_LOG_CAT_CFG_REQ_STRU *pstCatCfgReq,VOS_UINT32 ulCfgSize);
extern VOS_UINT32 diag_CfgSetPrintSwt(DIAG_CMD_LOG_CAT_PRINT_REQ_STRU* pstPrintReq, VOS_UINT32 ulCfgSize);
extern VOS_UINT32 diag_ConnProc(VOS_UINT8* pstReq);
extern VOS_UINT32 diag_GetTimeStampInitValue(VOS_UINT8* pstReq);
extern VOS_UINT32 diag_GetModemNum(VOS_UINT8* pstReq);
extern VOS_UINT32 diag_GetPidTable(VOS_UINT8* pstReq);
extern VOS_UINT32 diag_DisConnProc(VOS_UINT8* pstReq);
extern VOS_UINT32 diag_DisConnNotifyOtherCpu(VOS_VOID);
extern VOS_UINT32 diag_EventCfgProc(VOS_UINT8* pstReq);
extern VOS_UINT32 diag_LayerCfgProc (VOS_UINT8* pstReq);
extern VOS_UINT32 diag_MsgCfgProc(VOS_UINT8* pstReq);
extern VOS_UINT32 diag_PrintCfgProc(VOS_UINT8* pstReq);
extern VOS_UINT32 diag_UsrPlaneCfgProc(VOS_UINT8* pstReq);
extern VOS_UINT32 diag_AirCfgProc (VOS_UINT8* pstReq);
extern VOS_VOID diag_AppAgentTimeOutProcEntry(VOS_VOID* pstPara);
extern VOS_VOID diag_BbpEnableSocpChan(VOS_VOID);
extern VOS_VOID diag_GetModemInfo(DIAG_FRAME_INFO_STRU *pstDiagHead);

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

#endif /* end of diag_cfg.h */
