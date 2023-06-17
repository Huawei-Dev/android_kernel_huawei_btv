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

#ifndef __FC_H__
#define __FC_H__

#include "vos.h"
#include "PsLib.h"
#include "FcInterface.h"
#include "FcIntraMsg.h"
#include "TtfNvInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
#define FC_MAX_POINT_NUM                (22)
#else
#define FC_MAX_POINT_NUM                (10)
#endif
#define FC_MEM_THRESHOLD_MAX_NUM        (4)

#define FC_PRI_LOWEST                   (FC_PRI_1)
#define FC_PRI_HIGHEST                  (FC_PRI_9)

#define FC_MAX_NUM                      (10)
#define FC_RAB_MASK_ALL                 (0x0000FFFE)

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
#define UEPS_FID_FLOWCTRL               (UEPS_FID_FLOWCTRL_C)
#else
#define UEPS_FID_FLOWCTRL               (UEPS_FID_FLOWCTRL_A)
#endif

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
#define UEPS_PID_FLOWCTRL               (UEPS_PID_FLOWCTRL_C)
#else
#define UEPS_PID_FLOWCTRL               (UEPS_PID_FLOWCTRL_A)
#endif

#define FC_MAX_BRIDGE_BYTE_CNT          (0x80000)

#define FC_GET_MSG_NAME16(pRcvMsg)      (*((VOS_UINT16 *)((VOS_UINT8 *)(pRcvMsg) + VOS_MSG_HEAD_LENGTH)))
#define FC_GET_MSG_NAME32(pRcvMsg)      (*((VOS_UINT32 *)((VOS_UINT8 *)(pRcvMsg) + VOS_MSG_HEAD_LENGTH)))

#define FC_POLICY_MASK(enPolicyId)      (((VOS_UINT32)1) << (enPolicyId))

#define FC_POLICY_GetEnableMask(enPolicyId) ((FC_POLICY_MASK(enPolicyId) & g_stFcCfg.ulFcEnbaleMask))
#define FC_POLICY_Get( enPolicyId )      (&g_astFcPolicy[enPolicyId])

#define FC_DOWN_RATE_LIMIT_MASK         (0xFFFF)


#define FC_UE_MIN_RAB_ID                (5)
#define FC_UE_MAX_RAB_ID                (15)


#define FC_ACPU_DRV_ASSEM_UE_ON_MASK    (1)
#define FC_ACPU_DRV_ASSEM_PC_ON_MASK    (1 << 1)
#define FC_ACPU_CDS_GU_ASSEM_ON_MASK    (1 << 2)


#define CPU_MAX_SET_DRV_FAIL_SMOOTH_CNT (50)
#define CPU_DRV_ASSEM_PARA_MAX_NV_LEV   (4)


#define FC_ADS_DL_RATE_UP_LEV           (200)
#define FC_ADS_DL_RATE_DOWN_LEV         (20)
#define FC_ADS_TIMER_LEN                (50)
#define FC_MODEM_ID_NUM                 (2)

#define FC_CCPU_TRACE_CPULOAD_TIMELEN   (1000)
#define TIMER_FC_CCPU_TRACE_CPULOAD     (0x1001)

#define FC_CCPU_PTR_OCTET_OCCUPIED      (1)
#define FC_ACPU_PTR_OCTET_OCCUPIED      (2)
#define FC_PTR_MAX_OCTET_OCCUPIED       (2)

enum FC_PRI_OPER_ENUM
{
    FC_PRI_CHANGE_AND_CONTINUE          = 0,
    FC_PRI_CHANGE_AND_BREAK,
    FC_PRI_KEEP_AND_BREAK,
    FC_PRI_OPER_BUTT
};
typedef VOS_UINT32 FC_PRI_OPER_ENUM_UINT32;


enum FC_MNTN_EVENT_TYPE_ENUM
{
    ID_FC_MNTN_POINT_SET_FC             = 0x8001,                   /* _H2ASN_MsgChoice FC_MNTN_POINT_FC_STRU */
    ID_FC_MNTN_POINT_CLR_FC             = 0x8002,                   /* _H2ASN_MsgChoice FC_MNTN_POINT_FC_STRU */
    ID_FC_MNTN_POLICY_UP                = 0x8003,                   /* _H2ASN_MsgChoice FC_MNTN_POLICY_STRU */
    ID_FC_MNTN_POLICY_DOWN              = 0x8004,                   /* _H2ASN_MsgChoice FC_MNTN_POLICY_STRU */
    ID_FC_MNTN_POLICY_ADD_POINT         = 0x8005,                   /* _H2ASN_MsgChoice FC_MNTN_POLICY_STRU */
    ID_FC_MNTN_POLICY_DEL_POINT         = 0x8006,                   /* _H2ASN_MsgChoice FC_MNTN_POLICY_STRU */
    ID_FC_MNTN_POLICY_CHANGE_POINT      = 0x8007,                   /* _H2ASN_MsgChoice FC_MNTN_POLICY_STRU */
    ID_FC_MNTN_CPU_A_CPULOAD            = 0x8008,                   /* _H2ASN_MsgChoice FC_MNTN_CPULOAD_STRU */
    ID_FC_MNTN_CPU_C_CPULOAD            = 0x8009,                   /* _H2ASN_MsgChoice FC_MNTN_CPULOAD_STRU */
    ID_FC_MNTN_DRV_ASSEM_PARA           = 0x800A,                   /* _H2ASN_MsgChoice FC_MNTN_DRV_ASSEM_PARA_STRU */
    ID_FC_MNTN_ACORE_CRESET_START_FC    = 0x800B,                   /* _H2ASN_MsgChoice FC_MNTN_POINT_FC_STRU */
    ID_FC_MNTN_ACORE_CRESET_END_FC      = 0x800C,                   /* _H2ASN_MsgChoice FC_MNTN_POINT_FC_STRU */

    ID_FC_MNTN_EVENT_TYPE_BUTT          = 0xFFFF
};
typedef VOS_UINT16 FC_MNTN_EVENT_TYPE_ENUM_UINT16;


enum FC_TIMER_NAME_ENUM
{
    FC_TIMER_STOP_CPU_ATTEMPT   = 0,
    FC_TIMER_NAME_BUTT
} ;
typedef VOS_UINT32 FC_TIMER_NAME_ENUM_UINT32;

enum FC_PRIVATE_POLICY_ID_ENUM
{
    FC_PRIVATE_POLICY_ID_MEM_MODEM_0                    = 0,
    FC_PRIVATE_POLICY_ID_CPU_A_MODEM_0,
    FC_PRIVATE_POLICY_ID_CDS_MODEM_0,
    FC_PRIVATE_POLICY_ID_CST_MODEM_0,
    FC_PRIVATE_POLICY_ID_GPRS_MODEM_0,
    FC_PRIVATE_POLICY_ID_TMP_MODEM_0,
    FC_PRIVATE_POLICY_ID_CPU_C_MODEM_0,
    FC_PRIVATE_POLICY_ID_CDMA_MODEM_0,
    FC_PRIVATE_POLICY_ID_MEM_MODEM_1,
    FC_PRIVATE_POLICY_ID_CPU_A_MODEM_1,
    FC_PRIVATE_POLICY_ID_CDS_MODEM_1,
    FC_PRIVATE_POLICY_ID_CST_MODEM_1,
    FC_PRIVATE_POLICY_ID_GPRS_MODEM_1,
    FC_PRIVATE_POLICY_ID_TMP_MODEM_1,
    FC_PRIVATE_POLICY_ID_CPU_C_MODEM_1,
    FC_PRIVATE_POLICY_ID_CDMA_MODEM_1,
    FC_PRIVATE_POLICY_ID_BUTT
};
typedef VOS_UINT8 FC_PRIVATE_POLICY_ID_ENUM_UINT8;

typedef struct
{
    VOS_UINT8                           ucValid;
    VOS_UINT8                           ucFcIdCnt;
    VOS_UINT8                           ucFcIdIndex;
    FC_PRI_ENUM_UINT8                   enPri;
    FC_ID_ENUM_UINT8                    aenFcId[FC_MAX_POINT_NUM];
    VOS_UINT8                           aucRsv[6];
} FC_PRI_STRU;

typedef VOS_UINT32 (*FC_POLICY_POSTPROCESS)(VOS_UINT32 ulParam1, VOS_UINT32 ulParam2);
typedef VOS_UINT32 (*FC_POLICY_ADJUST_FOR_UP_FUNC)(FC_PRI_ENUM_UINT8 enPointPri, FC_ID_ENUM_UINT8 enFcId);
typedef VOS_UINT32 (*FC_POLICY_ADJUST_FOR_DOWN_FUNC)(FC_PRI_ENUM_UINT8 enPointPri, FC_ID_ENUM_UINT8 enFcId);


typedef struct
{
    FC_PRIVATE_POLICY_ID_ENUM_UINT8     enPolicyId;
    VOS_UINT8                           ucPriCnt;
    FC_PRI_ENUM_UINT8                   enHighestPri;
    FC_PRI_ENUM_UINT8                   enDonePri;
    FC_PRI_ENUM_UINT8                   enToPri;
    VOS_UINT8                           aucRsv[3];
    FC_PRI_STRU                         astFcPri[FC_PRI_BUTT];
    FC_POLICY_ADJUST_FOR_UP_FUNC        pAdjustForUpFunc;
    FC_POLICY_ADJUST_FOR_DOWN_FUNC      pAdjustForDownFunc;
    FC_POLICY_POSTPROCESS               pPostFunc;
} FC_POLICY_STRU;

typedef struct
{
    FC_ID_ENUM_UINT8                    enFcId;
    VOS_UINT8                           aucRsv[1];
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulPolicyMask;
    VOS_UINT32                          ulFcMask;
    VOS_UINT32                          ulParam1;
    VOS_UINT32                          ulParam2;
    FC_SET_FUNC                         pSetFunc;
    FC_CLR_FUNC                         pClrFunc;
    FC_RST_FUNC                         pRstFunc;
} FC_POINT_STRU;

typedef struct
{
    VOS_UINT32                          ulPointNum;
    VOS_UINT8                           aucRsv[4];
    FC_POINT_STRU                       astFcPoint[FC_MAX_POINT_NUM];
} FC_POINT_MGR_STRU;


typedef struct
{
    VOS_UINT32                          ulLastByteCnt;
    VOS_UINT32                          ulRate;
} FC_BRIDGE_RATE_STRU;

typedef struct
{
    FC_ID_ENUM_UINT8                    enFcId;
    VOS_UINT8                           aucRsv[7];
    VOS_UINT32                          ulIncludeRabMask;
    VOS_UINT32                          ulNoFcRabMask;
} FC_RAB_MAPPING_INFO_STRU;


typedef struct
{
    FC_ID_ENUM_UINT8                    enFcIdCnt;
    VOS_UINT8                           aucRsv[3];
    FC_RAB_MAPPING_INFO_STRU            astFcRabMappingInfo[FC_MAX_NUM];
} FC_RAB_MAPPING_INFO_SET_STRU;

typedef struct
{
    FC_ID_ENUM_UINT8                    enFcId;
    VOS_UINT8                           aucRsv[5];
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulPolicyMask;
    VOS_UINT32                          ulFcMask;
    VOS_UINT32                          ulParam1;
    VOS_UINT32                          ulParam2;
    VOS_UINT32                          aulPointSetAddr[FC_PTR_MAX_OCTET_OCCUPIED];
    VOS_UINT32                          aulPointClrAddr[FC_PTR_MAX_OCTET_OCCUPIED];
    VOS_UINT32                          aulPointRstAddr[FC_PTR_MAX_OCTET_OCCUPIED];
} FC_MNTN_POINT_INFO_STRU;

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    FC_MNTN_EVENT_TYPE_ENUM_UINT16      enMsgName;                              /* _H2ASN_Skip */
    VOS_UINT8                           aucRsv[2];
    FC_MNTN_POINT_INFO_STRU             stFcPoint;
    VOS_UINT32                          ulIsFuncInvoked;
    VOS_UINT32                          ulResult;
} FC_MNTN_POINT_FC_STRU;

typedef struct
{
    FC_PRIVATE_POLICY_ID_ENUM_UINT8     enPolicyId;
    VOS_UINT8                           ucPriCnt;
    FC_PRI_ENUM_UINT8                   enHighestPri;
    FC_PRI_ENUM_UINT8                   enDonePri;
    FC_PRI_ENUM_UINT8                   enToPri;
    VOS_UINT8                           aucRsv[3];
    FC_PRI_STRU                         astFcPri[FC_PRI_BUTT];
    VOS_UINT32                          aulPolicyUpAddr[FC_PTR_MAX_OCTET_OCCUPIED];
    VOS_UINT32                          aulPolicyDownAddr[FC_PTR_MAX_OCTET_OCCUPIED];
    VOS_UINT32                          aulPolicyPostAddr[FC_PTR_MAX_OCTET_OCCUPIED];
} FC_MNTN_POLICY_INFO_STRU;

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    FC_MNTN_EVENT_TYPE_ENUM_UINT16      enMsgName;                              /* _H2ASN_Skip */
    VOS_UINT8                           aucRsv[2];
    FC_MNTN_POLICY_INFO_STRU            stPolicy;
} FC_MNTN_POLICY_STRU;

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    FC_MNTN_EVENT_TYPE_ENUM_UINT16      enMsgName;                              /* _H2ASN_Skip */
    VOS_UINT8                           aucRsv[2];
    VOS_UINT32                          ulCpuLoad;
}FC_MNTN_CPULOAD_STRU;

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    FC_MNTN_EVENT_TYPE_ENUM_UINT16      enMsgName;                              /* _H2ASN_Skip */
    VOS_UINT8                           aucRsv[2];
    FC_DRV_ASSEM_PARA_STRU              stDrvAssemPara;
}FC_MNTN_DRV_ASSEM_PARA_STRU;

typedef struct
{
    VOS_UINT32                          ulSmoothTimerLen;
    VOS_UINT8                           aucRsv[4];
    HTIMER                              pstStopAttemptTHandle;
} FC_CPU_CTRL_STRU;

typedef struct
{
    const VOS_UINT32                    ulTraceCpuLoadTimerLen;
    VOS_UINT32                          ulCpuLoadRecord;
    HTIMER                              pstTraceCpuLoadTHandle;
} FC_TRACE_CPULOAD_STRU;

typedef struct
{
    VOS_UINT32                          ulThresholdCnt;
    FC_CFG_MEM_THRESHOLD_STRU           astThreshold[FC_MEM_THRESHOLD_LEV_BUTT];
} FC_CFG_MEM_STRU;

typedef struct
{
    FC_CFG_MEM_THRESHOLD_STRU           stThresholdMemSize;
    FC_CFG_MEM_THRESHOLD_STRU           stThresholdMemCnt;
} FC_CFG_GPRS_STRU;

typedef struct
{
    FC_CFG_MEM_THRESHOLD_STRU           stThresholdMemSize;
    FC_CFG_MEM_THRESHOLD_STRU           stThresholdMemCnt;
} FC_CFG_CDMA_STRU;

typedef struct
{
    FC_CFG_MEM_THRESHOLD_STRU           stThreshold;
} FC_CFG_CST_STRU;

typedef struct
{
    VOS_UINT32                          ulFcEnbaleMask;
    FC_CFG_CPU_STRU                     stFcCfgCpuA;
    FC_CFG_MEM_STRU                     stFcCfgMem;
    FC_CFG_CST_STRU                     stFcCfgCst;
    FC_CFG_GPRS_STRU                    stFcCfgGprs;
    FC_CFG_CPU_STRU                     stFcCfgCpuC;
    FC_CFG_UM_UL_RATE_STRU              stFcCfgUmUlRateForCpu;
    FC_CFG_UM_UL_RATE_STRU              stFcCfgUmUlRateForTmp;
    FC_CFG_CDMA_STRU                    stFcCfgCdma;
} FC_CFG_STRU;

typedef struct
{
    VOS_UINT32                          ulLev;
    VOS_UINT8                           aucRsv[4];
    FC_CPU_DRV_ASSEM_PARA_STRU         *pstCpuDrvAssemPara;
}FC_CPU_DRV_ASSEM_PARA_LEV_STRU;

typedef struct
{
    VOS_UINT8                               ucSmoothCntUp;
    VOS_UINT8                               ucSmoothCntDown;
    VOS_UINT8                               ucSetDrvFailCnt;
    VOS_UINT8                               ucRsv;
    VOS_UINT32                              ulCurLev;
    VOS_UINT8                               aucRsv[4];
    FC_CPU_DRV_ASSEM_PARA_STRU              stCurAssemPara;
    FC_ACORE_DRV_ASSEMBLE_PARA_FUNC         pDrvSetAssemParaFuncUe;             /* _H2ASN_Replace VOS_UINT32  pDrvSetAssemParaFuncUe; */
    FC_ACORE_DRV_ASSEMBLE_PARA_FUNC         pDrvSetAssemParaFuncPc;             /* _H2ASN_Replace VOS_UINT32  pDrvSetAssemParaFuncPc; */
}FC_CPU_DRV_ASSEM_PARA_ENTITY_STRU;

typedef struct
{
    VOS_UINT8                              ucEnableMask;
    VOS_UINT8                              ucSmoothCntUpLev;
    VOS_UINT8                              ucSmoothCntDownLev;
    VOS_UINT8                              ucRsv;
    FC_CPU_DRV_ASSEM_PARA_STRU             stCpuDrvAssemPara[FC_ACPU_DRV_ASSEM_LEV_BUTT];
}FC_CPU_DRV_ASSEM_CONFIG_PARA_STRU;

extern FC_POLICY_STRU                          g_astFcPolicy[];
extern FC_POINT_MGR_STRU                       g_stFcPointMgr;
extern FC_CFG_STRU                             g_stFcCfg;
extern FC_PRIVATE_POLICY_ID_ENUM_UINT8         g_aenPrivatePolicyTbl[FC_MODEM_ID_NUM][FC_POLICY_ID_BUTT];

typedef struct
{
    FC_MNTN_EVENT_TYPE_ENUM_UINT16      enMsgID;
    VOS_UINT8                           aucMsgBlock[2];
}FC_MSG_DATA;

typedef struct
{
    VOS_MSG_HEADER
    FC_MSG_DATA                   stMsgData;
}Fc_MSG;

extern VOS_VOID     FC_LOG
(
    VOS_UINT32          ulLevel,
    const VOS_CHAR     *pcString
);

extern VOS_VOID     FC_LOG1
(
    VOS_UINT32          ulLevel,
    const VOS_CHAR     *pcString,
    VOS_INT32           lPara1
);

extern VOS_VOID     FC_LOG2
(
    VOS_UINT32          ulLevel,
    const VOS_CHAR     *pcString,
    VOS_INT32           lPara1,
    VOS_INT32           lPara2
);

extern VOS_VOID     FC_LOG3
(
    VOS_UINT32          ulLevel,
    const VOS_CHAR     *pcString,
    VOS_INT32           lPara1,
    VOS_INT32           lPara2,
    VOS_INT32           lPara3
);

extern VOS_VOID     FC_LOG4
(
    VOS_UINT32          ulLevel,
    const VOS_CHAR     *pcString,
    VOS_INT32           lPara1,
    VOS_INT32           lPara2,
    VOS_INT32           lPara3,
    VOS_INT32           lPara4
);

extern VOS_UINT32  FC_POLICY_AddPoint
(
    FC_PRIVATE_POLICY_ID_ENUM_UINT8     enPolicyId,
    FC_ID_ENUM_UINT8                    enFcId,
    FC_PRI_ENUM_UINT8                   enPointPri
);

extern VOS_UINT32  FC_POLICY_DelPoint
(
    FC_PRIVATE_POLICY_ID_ENUM_UINT8     enPolicyId,
    FC_ID_ENUM_UINT8                    enFcId
);

extern VOS_UINT32  FC_POLICY_ChangePoint
(
    FC_PRIVATE_POLICY_ID_ENUM_UINT8     enPolicyId,
    FC_ID_ENUM_UINT8                    enFcId,
    FC_PRI_ENUM_UINT8                   enPointOldPri,
    FC_PRI_ENUM_UINT8                   enPointNewPri
);

extern VOS_UINT32 FC_SndTemperatureMsg
(
    FC_MSG_TYPE_ENUM_UINT16 usMsgName
);

extern VOS_UINT32 FC_SndCpuMsg
(
    FC_MSG_TYPE_ENUM_UINT16 usMsgName,
    VOS_UINT32              ulCpuLoad,
    VOS_UINT32              ulUlRate,
    VOS_UINT32              ulDlRate
);

extern VOS_UINT32 FC_SndRegPointMsg
(
    FC_REG_POINT_STRU                  *pstFcRegPoint
);

extern VOS_UINT32 FC_SndDeRegPointMsg
(
    FC_ID_ENUM_UINT8                    enFcId,
    MODEM_ID_ENUM_UINT16                enModemId
);

extern VOS_UINT32 FC_SndChangePointMsg
(
    FC_ID_ENUM_UINT8                    enFcId,
    FC_POLICY_ID_ENUM_UINT8             enPolicyId,
    FC_PRI_ENUM_UINT8                   enPri,
    MODEM_ID_ENUM_UINT16                enModemId
);

extern FC_PRI_ENUM_UINT8  FC_POLICY_GetPriWithFcId
(
    FC_PRIVATE_POLICY_ID_ENUM_UINT8             enPolicyId,
    FC_ID_ENUM_UINT8                            enFcId
);

extern VOS_UINT32 FC_POLICY_Up
(
    FC_POLICY_STRU *pPolicy
);

extern VOS_UINT32 FC_POLICY_Down
(
    FC_POLICY_STRU *pFcPolicy
);

extern VOS_UINT32  FC_POLICY_UpToTargetPri
(
    FC_POLICY_STRU                     *pFcPolicy,
    FC_PRI_ENUM_UINT8                   enTargetPri
);

extern VOS_UINT32  FC_POLICY_DownToTargetPri
(
    FC_POLICY_STRU                     *pFcPolicy,
    FC_PRI_ENUM_UINT8                   enTargetPri
);

extern FC_PRI_OPER_ENUM_UINT32 FC_POINT_SetFc
(
    VOS_UINT32                          ulPolicyMask,
    FC_ID_ENUM_UINT8                    enFcId
);

extern FC_PRI_OPER_ENUM_UINT32 FC_POINT_ClrFc
(
    VOS_UINT32                          ulPolicyMask,
    FC_ID_ENUM_UINT8                    enFcId
);

extern VOS_UINT32  FC_POINT_Reg
(
    FC_REG_POINT_STRU                  *pstFcRegPoint
);

extern VOS_UINT32  FC_POINT_DeReg(FC_ID_ENUM_UINT8 enFcId, MODEM_ID_ENUM_UINT16  enModemId);

extern VOS_UINT32  FC_POINT_Change
(
    FC_ID_ENUM_UINT8                    enFcId,
    FC_POLICY_ID_ENUM_UINT8             enPolicyId,
    FC_PRI_ENUM_UINT8                   enNewPri,
    MODEM_ID_ENUM_UINT16                enModemId
);

extern FC_POINT_STRU *FC_POINT_Get(FC_ID_ENUM_UINT8 enFcId);

extern VOS_UINT32  FC_CommInit( VOS_VOID );

extern VOS_UINT32  FC_CFG_CheckCpuParam( FC_CFG_CPU_STRU *pstFcCfgCpu );
extern VOS_UINT32  FC_CFG_CheckMemParam( FC_CFG_MEM_STRU *pstFcCfgMem );
extern VOS_UINT32  FC_CFG_CheckUlRateParam( FC_CFG_UM_UL_RATE_STRU *pstFcCfgUmUlRate );
extern VOS_UINT32  FC_CFG_CheckParam( FC_CFG_STRU *pstFcCfg );
extern VOS_UINT32  FC_MNTN_TraceCpuLoad(FC_MNTN_EVENT_TYPE_ENUM_UINT16 enMsgName, VOS_UINT32  ulCpuLoad );
extern VOS_UINT32  FC_MNTN_TraceDrvAssemPara(FC_DRV_ASSEM_PARA_STRU *pstDrvAssenPara);
extern VOS_VOID FC_MNTN_TracePointFcEvent
(
    FC_MNTN_EVENT_TYPE_ENUM_UINT16      enMsgName,
    FC_POINT_STRU                      *pstFcPoint,
    VOS_UINT32                          ulIsFuncInvoked,
    VOS_UINT32                          ulResult
);
extern VOS_VOID FC_MNTN_TraceEvent(VOS_VOID *pMsg);
extern VOS_UINT32  FC_MNTN_TracePolicy(FC_MNTN_EVENT_TYPE_ENUM_UINT16 enMsgName, FC_POLICY_STRU *pPolicy );
extern VOS_UINT32 FC_IsPolicyEnable(VOS_UINT32 ulPointPolicyMask, MODEM_ID_ENUM_UINT16 enModemId);
extern VOS_UINT32  FC_POINT_Add
(
    FC_REG_POINT_STRU                  *pstFcRegPoint
);
extern VOS_UINT32  FC_POINT_Del(FC_ID_ENUM_UINT8 enFcId );
extern VOS_VOID  FC_POINT_Init( VOS_VOID );
extern VOS_VOID  FC_POLICY_TrimInvalidPri( FC_POLICY_STRU *pFcPolicy );
extern FC_PRI_OPER_ENUM_UINT32 FC_POLICY_UpWithOnePri
(
    FC_POLICY_STRU                     *pFcPolicy,
    FC_PRI_STRU                        *pstPri
);
extern FC_PRI_OPER_ENUM_UINT32  FC_POLICY_DownWithOnePri
(
    FC_POLICY_STRU                     *pPolicy,
    FC_PRI_STRU                        *pstPri
);
extern VOS_VOID  FC_POLICY_UpdateHighestPri( FC_POLICY_STRU *pPolicy );
extern VOS_UINT32  FC_POLICY_AddPointForPri
(
    FC_POLICY_STRU                     *pPolicy,
    FC_ID_ENUM_UINT8                    enFcId,
    FC_PRI_ENUM_UINT8                   enPointPri
);
extern VOS_UINT32  FC_POLICY_DelPointForPri
(
    FC_POLICY_STRU                     *pPolicy,
    FC_ID_ENUM_UINT8                    enFcId,
    FC_PRI_ENUM_UINT8                   enPointPri
);
extern VOS_UINT32  FC_POLICY_GetPriCnt(FC_POLICY_STRU *pFcPolicy);
extern VOS_UINT32  FC_POLICY_Init( VOS_VOID );
extern VOS_UINT32  FC_CFG_SetDefaultValue( FC_CFG_STRU *pstFcCfg );
extern VOS_UINT32  FC_CFG_SetNvValue( FC_CFG_NV_STRU  *pstFcCfgNv );
extern VOS_UINT32  FC_CFG_Init( VOS_VOID );
extern VOS_UINT32  FC_SetDebugLev( VOS_UINT32 ulLev );
extern VOS_UINT32  FC_SetFcEnableMask( VOS_UINT32 ulEnableMask );
extern VOS_UINT32  FC_SetThreshold
(
    VOS_UINT32                          ulPolicyId,
    VOS_UINT32                          ulParam1,
    VOS_UINT32                          ulSetThreshold,
    VOS_UINT32                          ulStopThreshold
);
extern VOS_UINT32  FC_Help( VOS_VOID );

extern VOS_VOID  FC_BRIDGE_CalcRate( VOS_UINT32 ulPeriod );
extern VOS_VOID  FC_BRIDGE_ResetRate( VOS_VOID );
extern VOS_UINT32  FC_BRIDGE_GetRate( VOS_VOID );
extern VOS_UINT32  FC_RmRateJudge( VOS_VOID );
extern VOS_VOID FC_ShowDrvAssemPara(VOS_VOID);
extern VOS_VOID FC_DrvAssemInit(VOS_VOID);
extern VOS_VOID FC_JudgeAssemSmoothFactor(FC_CPU_DRV_ASSEM_PARA_STRU *pstDrvAssemPara);
extern FC_CPU_DRV_ASSEM_PARA_STRU *FC_GetCpuDrvAssemPara(VOS_UINT32 ulLev);
extern VOS_UINT32 FC_JudgeCdsDlThres(VOS_UINT8 ucThres);
extern FC_CPU_DRV_ASSEM_PARA_STRU* FC_GetCurrentAssemPara(VOS_UINT32 ulAssemLev);
extern VOS_VOID FC_DoJudgeDrvAssem(FC_CPU_DRV_ASSEM_PARA_STRU *pstDrvAssemPara);
extern VOS_VOID FC_JudgeDrvAssemAction(VOS_UINT32 ulAssemLev);
extern VOS_VOID FC_JudgeDrvToMaxPara(VOS_VOID);
extern FC_CPU_DRV_ASSEM_PARA_STRU* FC_SelectDrvAssemParaRule(VOS_UINT32 ulCpuLoad, VOS_UINT32 *pulAssemLev);
extern VOS_VOID FC_JudgeDrvAssemPara(VOS_UINT32 ulCpuLoad);
extern VOS_UINT32  FC_UmRateOverThreshold( VOS_VOID );
extern VOS_UINT32  FC_PsRateJudge( VOS_VOID );
extern VOS_VOID  FC_GetPsRate( VOS_UINT32 *pulUlRate, VOS_UINT32 *pulDlRate );
extern VOS_UINT32 FC_CPUA_UpJudge
(
    VOS_UINT32       ulCpuLoad,
    FC_CFG_CPU_STRU *pstFcCfgCpu,
    FC_POLICY_STRU  *pstFcPolicy
);
extern VOS_UINT32 FC_CPUA_DownJudge
(
    VOS_UINT32       ulCpuLoad,
    FC_CFG_CPU_STRU *pstFcCfgCpu,
    FC_POLICY_STRU  *pstFcPolicy
);
extern VOS_VOID FC_CPUA_RcvCpuLoad(VOS_UINT32  ulCpuLoad);
extern VOS_UINT32  FC_CPUA_StopFcAttempt( VOS_UINT32 ulParam1, VOS_UINT32 ulParam2 );
extern VOS_UINT32  FC_CPUA_UpProcess( VOS_VOID );
extern VOS_UINT32  FC_CPUA_DownProcess( VOS_VOID );
extern VOS_UINT32  FC_CPUA_StopFlowCtrl( VOS_VOID );
extern VOS_UINT32  FC_CPUA_Init( VOS_VOID );
extern FC_PRI_ENUM_UINT8  FC_MEM_CalcUpTargetFcPri
(
    FC_POLICY_STRU                     *pPolicy,
    VOS_UINT32                          ulMemValue
);
extern FC_PRI_ENUM_UINT8  FC_MEM_CalcDownTargetFcPri
(
    FC_POLICY_STRU                     *pPolicy,
    VOS_UINT32                          ulMemValue
);
extern VOS_UINT32  FC_MEM_AdjustPriForUp
(
    FC_PRI_ENUM_UINT8                  enPointPri,
    FC_ID_ENUM_UINT8                   enFcId
);
extern VOS_UINT32  FC_MEM_AdjustPriForDown
(
    FC_PRI_ENUM_UINT8                  enPointPri,
    FC_ID_ENUM_UINT8                   enFcId
);
extern VOS_UINT32  FC_MEM_SndUpToTargetPriIndMsg(FC_PRI_ENUM_UINT8 enTargetPri, VOS_UINT16 usMemFreeCnt);
extern VOS_UINT32  FC_MEM_SndDownToTargetPriIndMsg( FC_PRI_ENUM_UINT8 enTargetPri, VOS_UINT16 usMemFreeCnt);
extern VOS_VOID    FC_MEM_UpProcess( VOS_UINT32 ulMemValue  );
extern VOS_VOID    FC_MEM_DownProcess( VOS_UINT32 ulMemValue );
extern VOS_UINT32  FC_MEM_Init( VOS_VOID );
extern VOS_UINT32  FC_CST_UpProcess( VOS_UINT8 ucRabId );
extern VOS_UINT32  FC_CST_DownProcess( VOS_UINT8 ucRabId );
extern FC_RAB_MAPPING_INFO_STRU  *FC_CDS_GetFcInfo( VOS_UINT8 ucRabId, MODEM_ID_ENUM_UINT16 enModemId );
extern VOS_UINT32  FC_CDS_DelFcId( FC_ID_ENUM_UINT8 enFcId, MODEM_ID_ENUM_UINT16 enModemId );
extern VOS_UINT32  FC_CDS_AddRab(FC_ID_ENUM_UINT8 enFcId, VOS_UINT8 ucRabId, MODEM_ID_ENUM_UINT16 enModemId );
extern VOS_UINT32  FC_CDS_DelRab( VOS_UINT8 ucRabId, MODEM_ID_ENUM_UINT16 enModemId );
extern VOS_UINT32  FC_CDS_Init( VOS_VOID );
extern VOS_UINT32  FC_CDS_UpProcess( VOS_UINT8 ucRabId, MODEM_ID_ENUM_UINT16 enModemId );
extern VOS_UINT32  FC_CDS_DownProcess( VOS_UINT8 ucRabId, MODEM_ID_ENUM_UINT16 enModemId );
extern VOS_UINT32  FC_GPRS_UpProcess( VOS_VOID );
extern VOS_UINT32  FC_GPRS_DownProcess( VOS_VOID );
extern VOS_UINT32  FC_RcvCstMsg( MsgBlock * pMsg );
extern VOS_UINT32  FC_RcvCdsMsg( MsgBlock * pMsg );
extern VOS_UINT32  FC_ACORE_RegPoint( VOS_VOID );
extern VOS_UINT32  FC_ACORE_RcvTimerMsg(REL_TIMER_MSG *pTimerMsg);
extern VOS_UINT32  FC_ACORE_RcvIntraMsg( MsgBlock * pMsg );
extern VOS_UINT32  FC_ACORE_MsgProc( MsgBlock * pMsg );
extern VOS_UINT32  FC_ACORE_Init( VOS_VOID );
extern VOS_UINT32  FC_CDMA_UpProcess( VOS_VOID );
extern VOS_UINT32  FC_CDMA_DownProcess( VOS_VOID );
extern VOS_VOID    FC_UpProcess(VOS_RATMODE_ENUM_UINT32 enRateMode);
extern VOS_VOID    FC_DownProcess(VOS_RATMODE_ENUM_UINT32 enRateMode);

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

#endif /* end of Fc.h */
