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

#ifndef __HIFIOMINTERFACE_H__
#define __HIFIOMINTERFACE_H__

#include "vos.h"
#include "CodecInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

#define OM_APP_HEADER VOS_UINT16 usFuncType;    \
                      VOS_UINT16 usLength;      \
                      VOS_UINT32 ulSn;          \
                      VOS_UINT32 ulTimeStamp;

#define OM_APP_HEADER_TAIL_LEN          (8)
#define OM_TRACE_TAIL_LEN               (4)
#define OM_TRANS_FUNC_TYPE              (4)
#define OM_TRACE_FUNC_TYPE              (1)
#define OM_TRANS_PRIM_ID                (0x5001)
#define OM_TRACE_PRIM_ID                (0x8003)

#define HIFI_SOCP_CHANNEL_START_ADDR    (0x33ffe000U)
#define HIFI_SOCP_CHANNEL_LEN           (0x2000)
#define HIFI_SOCP_FIX_CHANNEL_ID        (29)

enum HIFI_OM_MSG_ID_ENUM
{
    ID_OM_CODEC_SET_LOG_REQ               = 0x940D,
    ID_OM_CODEC_EXT_DEF_REQ               = 0x9417,

    ID_OM_CODEC_MSG_HOOK_REQ              = 0x9420,
    ID_OM_CODEC_CPU_VIEW_REQ              = 0x9421,
    ID_OM_CODEC_OM_CONNECT_CMD            = 0x9422,
    ID_OM_CODEC_OM_DISCONNECT_CMD         = 0xc001,

    ID_AUDIODSP_DIAG_CONNECT_CNF          = 0x492A,
    ID_AUDIODSP_DIAG_DISCONNECT_CNF       = 0x492B,

    ID_TIMER_CODEC_CPUVIEW_RPT_IND        = 0x9401,

    ID_CODEC_OM_SET_LOG_CNF               = 0x490D,
    ID_CODEC_OM_EXT_DEF_CNF               = 0x4917,

    ID_CODEC_OM_MSG_HOOK_CNF              = 0x4920,
    ID_CODEC_OM_CPU_VIEW_CNF              = 0x4921,

    ID_CODEC_OM_CPUVIEW_BASIC_IND         = 0x4802,
    ID_CODEC_OM_CPUVIEW_DETAIL_IND        = 0x4803,
    ID_CODEC_OM_BUTT
};
typedef VOS_UINT16 HIFI_OM_MSG_ID_ENUM_UINT16;

enum HIFI_OM_LOG_LEVEL_ENUM
{
    ID_CODEC_OM_LOG_INFO_IND              = 0x08000000,
    ID_CODEC_OM_LOG_NORMAL_IND            = 0x10000000,
    ID_CODEC_OM_LOG_WARNING_IND           = 0x20000000,
    ID_CODEC_OM_LOG_ERR_IND               = 0x40000000,
};
typedef VOS_UINT32 HIFI_OM_LOG_LEVEL_ENUM_UINT32;

enum OM_CODEC_EXT_CMD_ENUM
{
    OM_CODEC_EXT_CMD_DEFAULT  = 0,
    OM_CODEC_EXT_ENABLE_OM,
    OM_CODEC_EXT_VQM_CMD,
    OM_CODEC_EXT_HIFI_DDR_DFS,
    OM_CODEC_EXT_AUDIO_SET_SOURCE,
    OM_CODEC_EXT_UCOM_MEM_DYN_SET_OM_FLAG,
    OM_CODEC_EXT_VOICE_DIAGNOSE_START,
    OM_CODEC_EXT_VOICE_EVRC_CODEC,
    OM_CODEC_EXT_CDMA_LOOP_ENABLE,
    OM_CODEC_EXT_CDMA_LOOP_DISABLE,
    OM_CODEC_EXT_CHANGE_MIC_DMA,
    OM_CODEC_EXT_CHANGE_SPK_DMA,
    OM_CODEC_EXT_RESET_HIFI,
    OM_CODEC_EXT_CMD_BUT
};
typedef VOS_UINT16  OM_CODEC_EXT_CMD_ENUM_UINT16;

enum OM_LOG_RPT_LEVEL_ENUM
{
    OM_LOG_LEVEL_INFO                   = 0 ,
    OM_LOG_LEVEL_WARNING,
    OM_LOG_LEVEL_ERROR,
    OM_LOG_LEVEL_BUTT
};
typedef VOS_UINT16 OM_LOG_RPT_LEVEL_ENUM_UINT16;

enum OM_SWITCH_ENUM
{
    OM_SWITCH_OFF                       = 0,
    OM_SWITCH_ON,
    OM_SWITCH_BUTT
};
typedef VOS_UINT16 OM_SWITCH_ENUM_UINT16;

enum OM_CPUVIEW_TARGET_ENUM
{
    OM_CPUVIEW_TARGET_TASK              = 0,
    OM_CPUVIEW_TARGET_INT               = 1,
    OM_CPUVIEW_TARGET_REGION            = 2,
    OM_CPUVIEW_TARGET_BUTT
};
typedef VOS_UINT8 OM_CPUVIEW_TARGET_ENUM_UINT8;

enum OM_CPUVIEW_ACTION_ENUM
{
    OM_CPUVIEW_ACTION_ENTER             = 0,
    OM_CPUVIEW_ACTION_EXIT              = 1,
    OM_CPUVIEW_ACTION_BUTT
};
typedef VOS_UINT8 OM_CPUVIEW_ACTION_ENUM_UINT8;

enum IPC_STATUS_HIFI2CARM_ENUM
{
    IPC_STATUS_HIFI2CARM_MB             = 0x1,
    IPC_STATUS_HIFI2CARM_INIT           = 0x2,
    IPC_STATUS_HIFI2CARM_PD             = 0x4,
    IPC_STATUS_HIFI2CARM_BUTT           = 0x8
};
typedef VOS_UINT16 IPC_STATUS_HIFI2CARM_ENUM_UINT16;

enum COMM_VOICE_PCVOICE_DATA_DIRECTION_ENUM
{
    COMM_VOICE_PCVOICE_DATA_DIRECTION_TX = 0,
    COMM_VOICE_PCVOICE_DATA_DIRECTION_RX,
    COMM_VOICE_PCVOICE_DATA_DIRECTION_BUTT,
};
typedef VOS_UINT32 COMM_VOICE_PCVOICE_DATA_DIRECTION_ENUM_UINT32;

enum HIFI_ERR_LOG_ALARM_ID_ENUM
{
    HIFI_ERR_LOG_ONE_WAY_NO_SOUND     = 0x1000,
    HIFI_ERR_LOG_VOICE_CONTROL_FAULT,
    HIFI_ERR_LOG_VOICE_SUSPEND_SLOW,
    HIFI_ERR_LOG_VOICE_BSD_ALARM,
    HIFI_ERR_LOG_VOICE_BSD_ALARM_SUB,
    HIFI_ERR_LOG_VOICE_BSD_WRR_NOISE,
    HIFI_ERR_LOG_VOICE_BSD_VQI_ALARM,
    HIFI_ERR_LOG_ALARM_ID_BUTT,
};
typedef VOS_UINT16 HIFI_ERR_LOG_ALARM_ID_ENUM_UINT16;

enum HFII_ERR_LOG_ALARM_LEVEL_ENUM
{
    HIFI_ERR_LOG_ALARM_CRITICAL     = 0x01,
    HIFI_ERR_LOG_ALARM_MAJOR,
    HIFI_ERR_LOG_ALARM_MINOR,
    HIFI_ERR_LOG_ALARM_WARNING,
    HIFI_ERR_LOG_ALARM_LEVEL_BUTT,
};
typedef VOS_UINT16 HIFI_ERR_LOG_ALARM_LEVEL_ENUM_UINT16;

enum HIFI_ERR_LOG_ALARM_TYPE_ENUM
{
    HIFI_ERR_LOG_ALARM_COMMUNICATION = 0x00,
    HIFI_ERR_LOG_ALARM_TYPE_BUTT,
};
typedef VOS_UINT16 HIFI_ERR_LOG_ALARM_TYPE_ENUM_UINT16;

typedef struct
{
    OM_APP_HEADER
    VOS_UINT16                          usPrimId;
    VOS_UINT16                          usToolId;
}OM_TRACE_HEADER_STRU;

typedef struct
{
    OM_APP_HEADER
}OM_TRANS_HEADER_STRU;

typedef struct
{
    VOS_UINT16                          usTransPrimId;
    VOS_UINT16                          usReserve;
    OM_APP_HEADER
}OM_TRANS_PASS_HEADER_STRU;

typedef struct
{
    VOS_UCHAR       ucCpuId;
    VOS_UCHAR       aucRsv[3];
    VOS_UINT32      ulRtc;
}OM_SOCP_FRAME_HEAD_STRU;

typedef struct
{
    VOS_UINT16      uhwSegLen;
    VOS_UCHAR       ucSegNum;
    VOS_UCHAR       ucSegSn;
}OM_SOCP_FRAME_SEG_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          uhwMsgId;
    VOS_UINT16                          uhwReserve1;
    OM_SWITCH_ENUM_UINT16               enLogEnable;
    OM_LOG_RPT_LEVEL_ENUM_UINT16        enLogLevel;
}OM_CODEC_SET_LOG_REQ_STRU;

typedef struct
{
    VOS_UINT16                          uhwMsgId;
    VOS_UINT16                          uhwReserve;
    UCOM_RET_ENUM_UINT16                enReturn;
    VOS_UINT16                          uhwReserve2;
}CODEC_OM_SET_LOG_CNF_STRU;

 typedef struct
{
    VOS_UINT16                          uhwMsgId;
    VOS_UINT16                          uhwReserve;
    VOS_UINT16                          uhwFileId;
    VOS_UINT16                          uhwLineNo;
    VOS_UINT32                          uwLogId;
    VOS_INT32                           aswData[3];
} CODEC_OM_LOG_IND_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          uhwMsgId;
    VOS_UINT16                          uhwReserve1;
    OM_SWITCH_ENUM_UINT16               enEnable;
    VOS_UINT16                          uhwPeriod;
    OM_SWITCH_ENUM_UINT16               enDetailEnable;
    VOS_UINT16                          uhwReserve2;
} OM_CODEC_CPU_VIEW_REQ_STRU;

typedef struct
{
    VOS_UINT16                          uhwMsgId;
    VOS_UINT16                          uhwReserve;
    UCOM_RET_ENUM_UINT16                enReturn;
    VOS_UINT16                          uhwReserve2;
} CODEC_OM_CPU_VIEW_CNF_STRU;

 typedef struct
{
    VOS_UINT16                          uhwMsgId;
    VOS_UINT16                          usReserve;
    VOS_UINT32                          auwStackRate[HIFI_TASK_NUM];
    VOS_UINT32                          auwTaskTime[HIFI_TASK_NUM];
    VOS_UINT32                          auwIntrTime[HIFI_INTR_NUM];
} CODEC_OM_CPUVIEW_BASIC_IND_STRU;

typedef struct
{
    VOS_UINT32                          uwTarget:2;
    VOS_UINT32                          uwTargetId:5;
    VOS_UINT32                          uwAction:1;
    VOS_UINT32                          uwTimeStamp:24;
}OM_CPUVIEW_SLICE_RECORD_STRU;

typedef struct
{
    VOS_UINT16                          uhwMsgId;
    VOS_UINT16                          uhwReserve;
    VOS_UINT32                          uwRecNum;
    OM_CPUVIEW_SLICE_RECORD_STRU        astRecords[1];
} CODEC_OM_CPUVIEW_DETAIL_IND_STRU;

 typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          uhwMsgId;
    VOS_UINT16                          uhwReserve;
    OM_SWITCH_ENUM_UINT16               enHookEnable;
    VOS_UINT16                          uhwReserve2;
}OM_CODEC_MSG_HOOK_REQ_STRU;

 typedef struct
{
    VOS_UINT16                          uhwMsgId;
    VOS_UINT16                          uhwReserve;
    UCOM_RET_ENUM_UINT16                enReturn;
    VOS_UINT16                          uhwReserve2;
}CODEC_OM_MSG_HOOK_CNF_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          uhwMsgId;
    VOS_UINT16                          uhwReserve;
    OM_CODEC_EXT_CMD_ENUM_UINT16          enExtCmd;
    VOS_UINT16                          uhwExtLen;
    VOS_UINT16                          auhwExtData[2];
}OM_CODEC_EXT_DEF_REQ_STRU;

typedef struct
{
    VOS_UINT16                          uhwMsgId;
    VOS_UINT16                          uhwReserve;
    OM_CODEC_EXT_CMD_ENUM_UINT16          enExtCmd;
    VOS_UINT16                          uhwExtLen;
    VOS_UINT16                          auhwExtData[2];
}CODEC_OM_EXT_DEF_CNF_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          uhwMsgId;
    VOS_UINT16                          uhwReserve;
}OM_CODEC_OM_CONNECT_CMD_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          uhwMsgId;
    VOS_UINT16                          uhwReserve;
}OM_CODEC_OM_DISCONNECT_CMD_STRU;

struct msg_om_audiodsp_diag_confirm
{
    VOS_MSG_HEADER
    VOS_UINT16                          msg_id;
    VOS_UINT16                          reserve;
};

#define COMM_VOICE_RING_BUFFER_PROTECT1 (0x55AA55AA)
#define COMM_VOICE_RING_BUFFER_PROTECT2 (0x5A5A5A5A)

typedef struct
{
    VOS_UINT32                          uwProtectWord1;
    VOS_UINT32                          uwProtectWord2;
    VOS_UINT32                          uwWriteAddr;
    VOS_UINT32                          uwReadAddr;
    VOS_UINT32                          uwBufSize;
    VOS_UINT32                          uwBufAddr;
    VOS_UINT32                          uwProtectWord3;
    VOS_UINT32                          uwProtectWord4;
}COMM_VOICE_RING_BUFFER_CONTROL_STRU;

#if 0
typedef struct
{
    HIFI_OM_MSG_ID_ENUM_UINT16          enMsgID;

    VOS_UINT8                           aucMsgBlock[2];
}VOICEOM_OM_TRANS_MSG_DATA;

typedef struct
{
    VOICEOM_OM_TRANS_MSG_DATA             stMsgData;
}VoiceomOmTrans_MSG;
#endif

extern VOS_UINT32 COMM_VOICE_GetPcVoiceRingBuffCtrlAddr(COMM_VOICE_PCVOICE_DATA_DIRECTION_ENUM_UINT32 enDirection);

extern VOS_UINT32 COMM_VOICE_TransferPcVoiceRxData(VOS_VOID);

extern VOS_UINT32 COMM_VOICE_SetPcVoiceTransferSize(VOS_UINT32 uwSize);

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

#endif /* end of HifiOmInterface.h */
