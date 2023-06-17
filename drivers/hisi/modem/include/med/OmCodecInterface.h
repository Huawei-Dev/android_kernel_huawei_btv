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

#ifndef __OMCODECINTERFACE_H__
#define __OMCODECINTERFACE_H__

#include  "vos.h"
#include  "CodecInterface.h"
#include  "CodecNvInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

#define MSG_CODEC_OM_HOOK_IND_STRU        MSG_OM_VOICE_HOOK_REQ_STRU

#define VOICE_OM_TRANS_REPLICATED_BYTES (4)

enum CODEC_OM_MSG_ID_ENUM
{
    ID_VOICE_OM_SET_HOOK_CNF              = 0x491C,
    ID_VOICE_OM_SET_LOOP_CNF              = 0x491E,

    ID_VOICE_OM_QUERY_STATUS_CNF          = 0x491F,
    ID_VOICE_OM_SET_NV_CNF                = 0x4918,
    ID_VOICE_OM_GET_NV_CNF                = 0x4919,
    ID_AUDIO_OM_SET_HOOK_CNF              = 0x491A,
    ID_AUDIO_OM_QUERY_STATUS_CNF          = 0x491B,

    ID_VOICE_OM_SET_HOOK_IND              = 0x4922,
    ID_VOICE_OM_HOOK_IND                  = 0x4811,
    ID_AUDIO_OM_HOOK_IND                  = 0x4812,

    ID_OM_VOICE_SET_HOOK_REQ              = 0x941C,
    ID_OM_VOICE_SET_LOOP_REQ              = 0x941E,
    ID_OM_VOICE_QUERY_STATUS_REQ          = 0x941F,
    ID_OM_VOICE_SET_NV_REQ                = 0x9418,
    ID_OM_VOICE_GET_NV_REQ                = 0x9419,

    ID_OM_AUDIO_SET_HOOK_REQ              = 0x941A,
    ID_OM_AUDIO_QUERY_STATUS_REQ          = 0x941B,

    ID_AUDIO_OM_SET_NV_REQ                = 0x941C,
    ID_AUDIO_OM_GET_NV_REQ                = 0x941D,

    CODEC_OM_MSG_ID_BUTT
};
typedef VOS_UINT16 CODEC_OM_MSG_ID_ENUM_UINT16;

enum CODEC_ERRLOG_EVENT_MODE_ENUM
{
    CODEC_ERRLOG_EVENT_MODE_GSM                               = 0,
    CODEC_ERRLOG_EVENT_MODE_WCDMA,
    CODEC_ERRLOG_EVENT_MODE_ALL,
    CODEC_ERRLOG_EVENT_MODE_ENUM_BUTT
};
typedef VOS_UINT16 CODEC_ERRLOG_EVENT_MODE_ENUM_UINT16;

enum CODEC_ERRLOG_EVENTS_ENUM
{
    CODEC_ERRLOG_EVENTS_DMA_MIC_RESET                          = 0,
    CODEC_ERRLOG_EVENTS_DMA_SPK_RESET,

    CODEC_ERRLOG_EVENTS_WCDMA_DEC_INT_LOST,
    CODEC_ERRLOG_EVENTS_WCDMA_BBP_DATA_NONE,
    CODEC_ERRLOG_EVENTS_WCDMA_BBP_DATA_BAD,
    CODEC_ERRLOG_EVENTS_WCDMA_DECIPHER_LOST,

    CODEC_ERRLOG_EVENTS_GSM_BFI_FRAME,

    CODEC_ERRLOG_EVENTS_CODEC_SID_FRAME,

    CODEC_ERRLOG_EVENTS_PCVOICE_INTERPOLATE,
    CODEC_ERRLOG_EVENTS_PCVOICE_RINGBUF_FULL,

    CODEC_ERRLOG_EVENTS_ENUM_BUTT
};
typedef VOS_UINT16 CODEC_ERRLOG_EVENTS_ENUM_UINT16;

enum CODEC_ERRLOG_ENV_CODEC_ENUM
{
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR_475                      = 0,
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR_515,
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR_590,
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR_670,
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR_740,
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR_795,
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR_102,
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR_122,

    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR2_475,
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR2_515,
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR2_590,
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR2_670,
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR2_740,
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR2_795,
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR2_102,
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR2_122,

    CODEC_ERRLOG_ENV_CODEC_GSM_AMR_475,
    CODEC_ERRLOG_ENV_CODEC_GSM_AMR_515,
    CODEC_ERRLOG_ENV_CODEC_GSM_AMR_590,
    CODEC_ERRLOG_ENV_CODEC_GSM_AMR_670,
    CODEC_ERRLOG_ENV_CODEC_GSM_AMR_740,
    CODEC_ERRLOG_ENV_CODEC_GSM_AMR_795,
    CODEC_ERRLOG_ENV_CODEC_GSM_AMR_102,
    CODEC_ERRLOG_ENV_CODEC_GSM_AMR_122,

    CODEC_ERRLOG_ENV_CODEC_GSM_EFR,

    CODEC_ERRLOG_ENV_CODEC_GSM_FR,

    CODEC_ERRLOG_ENV_CODEC_GSM_HR,

    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMRWB_660,
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMRWB_885,
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMRWB_1265,
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMRWB_1425,
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMRWB_1585,
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMRWB_1825,
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMRWB_1985,
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMRWB_2305,
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMRWB_2385,

    CODEC_ERRLOG_ENV_CODEC_GSM_AMRWB_660,
    CODEC_ERRLOG_ENV_CODEC_GSM_AMRWB_885,
    CODEC_ERRLOG_ENV_CODEC_GSM_AMRWB_1265,

    CODEC_ERRLOG_ENV_CODEC_ENUM_BUTT
};
typedef VOS_UINT16 CODEC_ERRLOG_ENV_CODEC_ENUM_UINT16;

enum CODEC_ERRLOG_EVENT_TYPE_ENUM
{
    CODEC_ERRLOG_EVENT_TYPE_TOTAL                             = 0,
    CODEC_ERRLOG_EVENT_TYPE_REPEAT,
    CODEC_ERRLOG_EVENT_TYPE_LOST,
    CODEC_ERRLOG_EVENT_TYPE_ENUM_BUTT
};
typedef VOS_UINT16 CODEC_ERRLOG_EVENT_TYPE_ENUM_UINT16;

enum CODEC_LOOP_ENUM
{
    CODEC_LOOP_DMA                        = 0,
    CODEC_LOOP_BEFORE_CODEC,
    CODEC_LOOP_CODEC,
    CODEC_LOOP_BUTT
};
typedef VOS_UINT16  CODEC_LOOP_ENUM_UINT16;

typedef struct
{
    VOS_UINT16                                              usTransPrimId;
    VOS_UINT16                                              usReserved;

} MSG_CODEC_OM_ERRLOG_HEAD_STRU;

typedef struct
{
    VOS_UINT32                                              ulInfoLen;
    VOS_UINT32                                              ulErrNo;
    VOS_UINT32                                              ulBoardtime;
    VOS_UINT32                                              ulSliceTime;
}MNTN_HEAD_INFO_STRU;

typedef struct
{
    VOS_UINT32                                              uwSN;
    VOS_UINT32                                              uwTimeStamp;
} VOICE_TOOL_EX_HEAD_STRU;

typedef struct
{

    VOS_UINT8                           ucFuncType;
    VOS_UINT8                           ucCpuId;
    VOS_UINT16                          usLength;
    VOICE_TOOL_EX_HEAD_STRU             stToolExHead;
    VOS_UINT8                           aucHookData[VOICE_OM_TRANS_REPLICATED_BYTES];
} VOICE_OM_TRANS_STRU;

typedef struct
{
    CODEC_SWITCH_ENUM_UINT16              enLoopEnable;
    CODEC_LOOP_ENUM_UINT16                enLoopType;
}CODEC_LOOP_STRU;

typedef struct
{
    CODEC_INOUT_ENUM_UINT16               usTxIn;
    CODEC_INOUT_ENUM_UINT16               usTxOut;
    CODEC_INOUT_ENUM_UINT16               usRxIn;
    CODEC_INOUT_ENUM_UINT16               usRxOut;
} CODEC_INOUT_STRU;

typedef struct
{
    VOS_UINT16                          uhwTxIn;
    VOS_UINT16                          uhwRxOut;
} CODEC_ERRLOG_INOUT_STRU;

typedef struct
{
    CODEC_ERRLOG_ENV_CODEC_ENUM_UINT16    enCodecEnv;
    VOS_UINT16                          auhwRes[1];
    CODEC_ERRLOG_INOUT_STRU               stInout;
} CODEC_ERRLOG_ENV_STRU;

typedef struct
{
    CODEC_ERRLOG_ENV_STRU                 stErrEnv;
    VOS_UINT16                          uhwErrCnt;
    CODEC_ERRLOG_EVENT_TYPE_ENUM_UINT16   enErrType;
} CODEC_OM_ERRLOG_EVENT_RPT_STRU;

typedef struct
{
    MSG_CODEC_OM_ERRLOG_HEAD_STRU         stOmHead;
    MNTN_HEAD_INFO_STRU                 stRecordHead;
    CODEC_OM_ERRLOG_EVENT_RPT_STRU        stEventRpt;
} MSG_CODEC_ERRLOG_STRU;

typedef struct
{
    VOS_UINT32                          uwProtectWord1;
    VOS_UINT32                          uwProtectWord2;
    VOS_UINT32                          uwWriteAddr;
    VOS_UINT32                          uwReadAddr;
    VOS_UINT32                          uwBufSize;
    VOS_UINT32                          uwReserve;
    VOS_UINT32                          uwBufAddr;
    VOS_UINT32                          uwProtectWord3;
    VOS_UINT32                          uwProtectWord4;
}OMMED_RING_BUFFER_CONTROL_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgId;
    VOS_UINT16                          uwReserve;
}MSG_OM_VOICE_REQ_STRU;

typedef struct
{
    VOS_UINT16                          usDeviceMode;
    VOS_UINT16                          usNetMode;
    VOS_UINT16                          usSampleRate;
    VOS_UINT16                          usIndex;
    VOS_INT16                           ashwNv[CODEC_PP_NV_ARRAY_ID_LEN];
}OM_VOICE_NV_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgName;
    VOS_UINT16                          usReserve;
    VOS_UINT32                          uwPathID;
    VOS_UINT32                          uwModuleID;
    VOS_UINT32                          uwSize;
    VOS_UINT8                           aucData[4];

}MSG_OM_MLIB_PARA_SET_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgName;
    VOS_UINT16                          usReserve;
    VOS_UINT32                          uwPathID;
    VOS_UINT32                          uwModuleID;
    VOS_UINT32                          uwSize;
    VOS_UINT8                           aucData[4];

}MSG_OM_MLIB_PARA_GET_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgId;
    VOS_UINT16                          usReserve;
    CODEC_SWITCH_ENUM_UINT16            enHookEnable;
    VOS_UINT16                          usHookTarget;
}MSG_OM_VOICE_HOOK_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgId;
    VOS_UINT16                          usReserve;
    CODEC_SWITCH_ENUM_UINT16            enHookEnable;
    VOS_UINT16                          usHookTarget;
}MSG_OM_AUDIO_HOOK_REQ_STRU;

typedef struct
{
    VOS_UINT16                          usMsgId;
    VOS_UINT16                          usReserve;
    VOS_UINT32                          ulFrameTick;
    VOS_UINT32                          ulTimeStamp;
    VOS_UINT16                          usHookTarget;
    VOS_UINT16                          usHookLength;
}MSG_VOICE_OM_HOOK_STRU;

typedef struct
{
    VOS_UINT16                          usMsgId;
    VOS_UINT16                          usReserve;
    VOS_UINT32                          ulTimeStamp;
    VOS_UINT16                          usHookTarget;
    VOS_UINT16                          usHookLength;
}MSG_AUDIO_OM_HOOK_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgId;
    VOS_UINT16                          usReserved;
    CODEC_LOOP_STRU                     stLoop;
}MSG_OM_VOICE_LOOP_REQ_STRU;

typedef struct
{
    VOS_UINT16                          usMsgId;
    VOS_UINT16                          usReserved1;
    CODEC_NET_MODE_ENUM_UINT16          enNetMode;
    CODEC_ENUM_UINT16                   enCodecType;
    CODEC_SWITCH_ENUM_UINT16            enDtxMode;
    VOS_UINT16                          enAmrMode;
    CODEC_INOUT_STRU                    stInout;
    VOS_UINT16                          usState;
    VOS_UINT16                          usReserve2;
}MSG_VOICE_OM_QUERY_RSP_STRU;

typedef struct
{
    VOS_UINT16                          usMsgId;
    VOS_UINT16                          usReserved1;
    AUDIO_PCM_STATUS_ENUM_UINT16        enPlayBackStatus;
    VOS_UINT16                          usReserved2;
    VOS_UINT32                          uwPlayBackSampleRate;
    VOS_UINT32                          uwPlayBackChannelNum;
    AUDIO_PCM_STATUS_ENUM_UINT16        enCaptureStatus;
    AUDIO_CAPTURE_MODE_ENUM_UINT16      enCaptureMode;
    VOS_UINT32                          uwCaptureSampleRate;
    VOS_UINT32                          uwCaptureChannelNum;
    VOS_UINT32                          uwEnhanceModule;
}MSG_AUDIO_OM_QUERY_RSP_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgName;
    VOS_UINT16                          usDeviceMode;
    VOS_UINT32                          usSampleRate;
    VOS_UINT16                          usIndex;
    VOS_INT16                           ashwNv[AUDIO_PP_NV_ARRAY_ID_LEN];
    VOS_INT16                           shwReserved;
}MSG_OM_AUDIO_NV_REQ_STRU;

#if 0
typedef struct
{
    CODEC_OM_MSG_ID_ENUM_UINT16           enMsgID;

    VOS_UINT8                           aucMsgBlock[2];

}VOICE_OM_TRANS_MSG_DATA;

typedef struct
{
    VOICE_OM_TRANS_MSG_DATA                     stMsgData;
}VoiceOmTrans_MSG;

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

#endif /* end of VcCodecInterface.h */
