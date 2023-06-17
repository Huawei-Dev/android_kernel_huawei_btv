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

#ifndef __MSP_AT_H__
#define __MSP_AT_H__

#include <vos.h>
#include "TafTypeDef.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define MSP_AT_SYSMODE_LTE

#define ID_MSG_AT_BASE  0x500

#define ID_MSG_AT_FW_BEGIN                 (ID_MSG_AT_BASE)
#define ID_MSG_AT_FW_CLIENT_REGISTER_REQ   (ID_MSG_AT_BASE+0x01)
#define ID_MSG_AT_FW_CLIENT_REGISTER_CNF   (ID_MSG_AT_BASE+0x02)
#define ID_MSG_AT_FW_CLIENT_CONFIG_IND     (ID_MSG_AT_BASE+0x03)
#define ID_MSG_AT_FW_CLIENT_STATUS_IND     (ID_MSG_AT_BASE+0x04)
#define ID_MSG_AT_FW_CLIENT_CONFIG_REQ     (ID_MSG_AT_BASE+0x05)
#define ID_MSG_AT_FW_CLIENT_CONFIG_CNF     (ID_MSG_AT_BASE+0x06)

#define ID_MSG_AT_FW_CMD_STREAM_REQ        (ID_MSG_AT_BASE+0x10)
#define ID_MSG_AT_FW_CMD_STREAM_CNF        (ID_MSG_AT_BASE+0x11)
#define ID_MSG_AT_FW_CMD_STREAM_IND        (ID_MSG_AT_BASE+0x12)
#define ID_MSG_AT_FW_CMD_BINARY_MSG        (ID_MSG_AT_BASE+0x13)
#define ID_MSG_AT_FW_CMD_PARAM_REQ         (ID_MSG_AT_BASE+0x14)

#define ID_MSG_MMC_MODE_IND                (ID_MSG_AT_BASE+0x20)

#define ID_MSG_AT_FW_END                   (ID_MSG_AT_BASE+0x50)

#define ID_MSG_AT_CMD_BASE                   0x0FFFFFFF
#define ID_MSG_AT_CMD_ERROR_IND              (ID_MSG_AT_CMD_BASE+0x00)
#define ID_MSG_AT_CMD_STATUS_IND             (ID_MSG_AT_CMD_BASE+0x00)

typedef struct
{
    VOS_UINT32 ulResult;
    VOS_UINT8  aucSysMode[4];
} AT_FW_MMC_SYS_MODE_IND_STRU;

#if defined(WIN32_DEMO)
#define MSP_L4_AT_FW_PID                    100 
#define MSP_L4_AT_LTE_PID                   101
#define MSP_L4_AT_GU_PID                    102
#endif

#define AT_FW_URC_RPT_DISABLE               0
#define AT_FW_URC_RPT_ENABLE                1
#define AT_FW_URC_RPT_AUTO                  2

#define AT_FW_SYS_MODE_NULL                 0x00
#define AT_FW_SYS_MODE_GSM                  0x01
#define AT_FW_SYS_MODE_WCDMA                0x02
#define AT_FW_SYS_MODE_LTE                  0x04
#define AT_FW_SYS_MODE_CDMA                 0x08
#define AT_FW_SYS_MODE_TDSCDMA              0x10
#define AT_FW_SYS_MODE_AUTO                 0xFF

#define AT_FW_PACKET_FMT_STREAM             0x01
#define AT_FW_PACKET_FMT_BINARY             0x02

#define AT_FW_CLIENT_CHANNEL_STATUS_AT      0x00
#define AT_FW_CLIENT_CHANNEL_STATUS_OM      0x01

#define AT_FW_CLIENT_NAME_LEN               16
#define AT_FW_CMD_NAME_LEN                  16

enum AT_FW_CAMPON_RESULT_ENUM
{
    EN_AT_FW_CAMPON_OVER     = 0x00,
    EN_AT_FW_CAMPON_BEING    = 0x01,
    EN_AT_FW_CAMPON_BUTT     = 0xFF
};

typedef struct
{
    VOS_UINT32 ulMsgId;
    VOS_UINT32 pMsgParam[0];
} AT_FW_MSG_STRU;

enum
{
    EN_AT_FW_CLIENT_ID_AUTO     = 0x00,
    EN_AT_FW_CLIENT_ID_PCUI1    = 0x01,
    EN_AT_FW_CLIENT_ID_PCUI2    = 0x02,
    EN_AT_FW_CLIENT_ID_NCMCTRL  = 0x03,
    EN_AT_FW_CLIENT_ID_EQU      = 0x10,
    EN_AT_FW_CLIENT_ID_PPP      = 0x11,
    EN_AT_FW_CLIENT_ID_NDIS     = 0x12,
    EN_AT_FW_CLIENT_ID_DIAG     = 0x20,
    EN_AT_FW_CLIENT_ID_OM       = 0x21,
    EN_AT_FW_CLIENT_ID_OM_AGENT = 0x22,
    EN_AT_FW_CLIENT_ID_ALL      = 0xFF
};

typedef struct
{
    const VOS_UINT8  *pszCmdName;
} AT_FW_CMD_NAME_STRU;

typedef struct
{
    VOS_UINT16 usCmdNum;
    VOS_UINT16 ausReserved[3];
    const AT_FW_CMD_NAME_STRU  *pszUrcElementTbl;
} AT_FW_CMD_URC_DISCARD_STRU;

typedef struct
{
    VOS_UINT8 ucClientId;
    VOS_UINT8 ucInterfaceCfg;
    VOS_UINT8 ucSysMode;
    VOS_UINT8 ucReserved;
    VOS_BOOL bRegister;
    VOS_CHAR szName[AT_FW_CLIENT_NAME_LEN];
    const AT_FW_CMD_URC_DISCARD_STRU* pstDiscardUrc;
} AT_FW_CLIENT_REGISTER_REQ_STRU;

typedef struct
{
    VOS_UINT8 ucClientId;
    VOS_UINT8 ucReserved[3];
    VOS_UINT32 ulRc;
} AT_FW_CLIENT_REGISTER_CNF_STRU;

typedef struct
{
    VOS_UINT8 ucClientId;
    VOS_UINT8 ucReserved[3];
    VOS_UINT8 ucConfigClientId;
    VOS_UINT8 ucInterfaceCfg;
    VOS_UINT16 usCmdNum;
    const AT_FW_CMD_NAME_STRU  *pszUrcFilterTbl;
} AT_FW_CLIENT_CONFIG_REQ_STRU;

typedef struct
{
    VOS_UINT8 ucClientId;
    VOS_UINT8 ucReserved[3];
    VOS_UINT32 ulRc;
} AT_FW_CLIENT_CONFIG_CNF_STRU;

typedef struct
{
    VOS_UINT8 ucClientId;
    VOS_UINT8 ucReserved[3];
    VOS_BOOL  bRtsCts;
    VOS_UINT16 usBaudRate;
    VOS_UINT8 ucReserved1[2];
} AT_FW_CLIENT_CONFIG_IND_STRU;

typedef struct
{
    VOS_UINT8 ucClientId;
    VOS_UINT8 ucStatus;
    VOS_UINT8 ucReserved[2];
} AT_FW_CLIENT_STATUS_IND_STRU;

typedef struct
{
    VOS_UINT8 ucClientId;
    VOS_UINT8 ucBuildPacketFmt;
    VOS_UINT16 usStreamSize;
    VOS_UINT8  pStream[0];
} AT_FW_CMD_STREAM_REQ_STRU;

typedef struct
{
    VOS_UINT8 ucClientId;
    VOS_UINT8 ucReserved;
    VOS_UINT16 usStreamSize;
    VOS_UINT8  pStream[0];
} AT_FW_CMD_STREAM_CNF_STRU;

typedef struct
{
    VOS_UINT8 ucClientId;
    VOS_UINT8 ucReserved;
    VOS_UINT16 usStreamSize;
    VOS_UINT8  pStream[0];
} AT_FW_CMD_STREAM_IND_STRU;

typedef struct
{
    VOS_UINT8 ucClientId;
    VOS_UINT8 ucSysMode;
    VOS_UINT16 usMsgSize;
    VOS_UINT32 ulMsgId;
    VOS_UINT8  pMsg[0];
} AT_FW_CMD_BINARY_MSG_STRU;

typedef struct
{
    VOS_UINT8 ucClientId;
    VOS_UINT8 ucReserved;
    VOS_UINT16 usDataSize;
    VOS_UINT8  pData[0];
} AT_FW_CMD_PARAM_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                   ulMsgId;
    VOS_UINT32                   ulClientId;
    VOS_UINT32                   ulLen;
    VOS_UINT8                    pContext[0];
}AT_FW_DATA_MSG_STRU;

#if 0
typedef struct
{
    VOS_UINT8 ucClientId;
    VOS_UINT8 ucReserved[3];
    VOS_UINT32 ulMsgId;
    VOS_UINT32 ulRc;
} AT_CMD_ERROR_IND_STRU;
#endif

#ifdef __cplusplus
}
#endif

#endif /*__MSP_AT_H__*/
