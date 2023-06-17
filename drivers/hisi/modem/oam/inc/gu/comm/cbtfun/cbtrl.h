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

#ifndef __CBTRL_H__
#define __CBTRL_H__

#include "vos.h"
#include "phyoaminterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

#define APP_OM_NON_SIG_BT_TRAN_REQ      (0x1601)
#define OM_APP_NON_SIG_BT_TRAN_CNF      (0x1602)

/*OM<->APP : Get the WCDMA SYNC Status.*/
#define APP_OM_W_SYNC_STATUS_REQ        (0x1603)
#define OM_APP_W_SYNC_STATUS_CNF        (0x1604)

/*OM<->APP : Get the GMSK/EDGE DownLink Status.*/
#define APP_OM_GE_DL_STATUS_REQ         (0x1605)
#define OM_APP_GE_DL_STATUS_CNF         (0x1606)

/*OM<->APP : Get the EDGE BLER.*/
#define APP_OM_EDGE_BLER_REQ            (0x1607)
#define OM_APP_EDGE_BLER_CNF            (0x1608)

/*OM<->APP : Get the EDGE BLER.*/
#define APP_OM_W_BER_DATA_REQ           (0x1609)
#define OM_APP_W_BER_DATA_CNF           (0x160a)
#define OM_APP_W_BER_DATA_IND           (0x160b)

#define APP_OM_LISTMODE_BT_GETMSG_REQ   (0x1611)
#define OM_APP_LISTMODE_BT_GETMSG_CNF   (0x1612)

#define APP_OM_LISTMODE_BT_TRAN_REQ     (0x1613)
#define OM_APP_LISTMODE_BT_TRAN_CNF     (0x1614)

#define APP_OM_LISTMODE_BT_TEST_REQ     (0x1615)
#define OM_APP_LISTMODE_BT_TEST_CNF     (0x1616)
#define OM_APP_LISTMODE_BT_BER_IND      (0x1617)

#define APP_OM_NON_SIG_BT_C_SYNC_REQ    (0x1701)
#define OM_APP_NON_SIG_BT_C_SYNC_CNF    (0x1702)
#define APP_OM_NON_SIG_BT_C_FER_REQ     (0x1703)
#define OM_APP_NON_SIG_BT_C_FER_CNF     (0x1704)

#define APP_OM_BT_C_TX_SET_POWER_REQ        (0x1705)
#define OM_APP_BT_C_TX_SET_POWER_CNF        (0x1706)

#define APP_OM_SWITCH_RF_ANT_REQ         0x0068
#define OM_APP_SWITCH_RF_ANT_CNF         0x0068


#define CBT_STATE_IDLE                          0
#define CBT_STATE_ACTIVE                        1

#define CBT_MSG_ID_COMP_LENGTH                  (4U)

#define CBT_MSG_HEADER_LENGTH                   (16U)
#define CBT_MSG_IDLEN_LENGTH                    (8U)
#define CBT_MSG_HEAD_EX_LENGTH                  ((CBT_MSG_HEADER_LENGTH) + (CBT_MSG_IDLEN_LENGTH))

#define CBT_MSG_SEGMENT_LEN                     (4U*1024U)
#define CBT_MSG_CONTEXT_MAX_LENGTH              (CBT_MSG_SEGMENT_LEN - CBT_MSG_HEADER_LENGTH)

#define CBT_CCPU_TO_ACPU_SEND_DATA_REQ          (0x030d)

#define CBT_GET_COMPMODE_COMPID(COMPMODE)       ((COMPMODE>>12)& 0xF)
#define CBT_GET_COMPMODE_MODE(COMPMODE)         ((COMPMODE>>8) & 0xF)

#define CBT_MODEM_SSID_COMBINE(modem, ssid)     (((modem) & 0x0F) | ((ssid<<4) & 0xF0))

#define OM_BER_DATA_MAX_SIZE                    (1024)

#define OM_STATE_IDLE                               0
#define OM_STATE_ACTIVE                             1

/*OM<->APP : Just for LMT.*/
#define APP_OM_HANDLE_LMT_REQ                     0x80a1
#define OM_APP_HANDLE_LMT_CNF                     0x80a2
/*OM<->APP : Just for LMT.*/
#define APP_OM_ACTIVE_PHY_REQ                     0x80a3
#define OM_APP_ACTIVE_PHY_CNF                     0x80a4

#define APP_OM_PA_ATTRIBUTE_REQ                   0x80c1
#define OM_APP_PA_ATTRIBUTE_IND                   0x80c2

#define APP_OM_PA_TEMP_PHY_CHAN_REQ               0x80c7
#define OM_APP_PA_TEMP_PHY_CHAN_IND               0x80c8

#define APP_OM_SET_FTM_REQ                        0x80e5
#define OM_APP_SET_FTM_CNF                        0x80e6

#define APP_OM_QUERY_MODEM_NUM_REQ                0x8211
#define OM_APP_QUERY_MODEM_NUM_CNF                0x8212

#define APP_OM_AT_TMODE_REQ                       0x0065
#define OM_APP_AT_TMODE_CNF                       0x0065

#define APP_OM_AT_BANDSW_REQ                      0x0066
#define OM_APP_AT_BANDSW_CNF                      0x0066

#define APP_OM_AT_FCHAN_REQ                       0x0067
#define OM_APP_AT_FCHAN_CNF                       0x0067

/*OM<->APP : Restablish link*/
#define APP_OM_ESTABLISH_REQ                      0x80b1
#define OM_APP_ESTABLISH_CNF                      0x80b2

/*OM<->APP : Release link*/
#define APP_OM_RELEASE_REQ                        0x80b3
#define OM_APP_RELEASE_CNF                        0x80b4

#define OM_TRANS_PRIMID                           0x5001

enum OM_W_SNYC_STATUS
{
    OM_W_SYNC_STATUS_SYNC = 0,
    OM_W_SYNC_STATUS_OUT_OF_SYNC,
    OM_W_SYNC_STATUS_UNKNOWN,
    OM_W_SYNC_STATUS_BUTT
};

typedef VOS_UINT16 OM_W_SNYC_STATUS_ENUM_UINT16;

enum OM_GE_SNYC_STATUS
{
    OM_GE_SYNC_STATUS_NORMAL,
    OM_GE_SYNC_STATUS_DISNORMAL,
    OM_GE_SYNC_STATUS_UNKNOWN,
    OM_GE_SYNC_STATUS_BUTT
};

enum CBT_C_SYNC_STATUS
{
    CBT_C_SYNC_STATUS_SYNC = 0,
    CBT_C_SYNC_STATUS_OUT_OF_SYNC,
    CBT_C_SYNC_STATUS_UNKNOWN,
    CBT_C_SYNC_STATUS_BUTT
};

enum LMT_RAT_MODE
{
    LMT_RAT_WCDMA = 0,
    LMT_RAT_GSM,
    LMT_RAT_CDMA,
    LMT_RAT_BUTT
};

typedef enum
{
    CBT_MODE_LTE = 0,
    CBT_MODE_TDS,
    CBT_MODE_GSM,
    CBT_MODE_UMTS,
    CBT_MODE_CDMA,
    CBT_MODE_COMM = 0xf,
    CBT_MODE_BUTT

} CBT_COMPONENT_MODE_ENUM;

typedef enum
{
    CBT_MT_REQ = 1,
    CBT_MT_CNF,
    CBT_MT_IND,
    CBT_MT_BUTT

} CBT_MSG_TYPE_ENUM;

typedef enum
{
    CBT_SSID_NOAPPOINT = 0,
    CBT_SSID_APP_CPU,
    CBT_SSID_MODEM_CPU,
    CBT_SSID_LTE_DSP,
    CBT_SSID_LTE_BBP,
    CBT_SSID_GU_DSP,
    CBT_SSID_HIFI,
    CBT_SSID_TDS_DSP,
    CBT_SSID_TDS_BBP,
    CBT_SSID_MCU,
    CBT_SSID_GPU,
    CBT_SSID_GU_BBP,
    CBT_SSID_IOM3,
    CBT_SSID_ISP,
    CBT_SSID_X_DSP,
    CBT_SSID_RESERVE,
    CBT_SSID_BUTT
} CBT_SSID_ENUM;

typedef enum
{
    CBT_COMP_FUNC = 1,
    CBT_COMP_NOSIG,
    CBT_COMP_PHY,
    CBT_COMP_PS,
    CBT_COMP_TRANS,
    CBT_COMP_BUTT
} CBT_COMPONET_ID_ENUM;

typedef struct
{
    VOS_UINT8 ucModem  : 3;
    VOS_UINT8 ucResv   : 1;
    VOS_UINT8 ucSsid   : 4;
} CBT_MODEM_SSID_STRU;

typedef struct
{
    VOS_UINT8 ucMsgType    : 2;
    VOS_UINT8 ucFragIndex  : 4;
    VOS_UINT8 ucEof        : 1;
    VOS_UINT8 ucFragFlag   : 1;
} CBT_FRAGMENT_INFO_STRU;

typedef struct
{
    VOS_UINT32 ulTimestampL;
    VOS_UINT16 usTimestampH;
    VOS_UINT16 usRsv;
} CBT_TIME_STAMP_STRU;

typedef struct
{
    VOS_UINT8 ucRsv;
    VOS_UINT8 ucMode     : 4;
    VOS_UINT8 ucCompID   : 4;
} CBT_COMPONENT_MODE_STRU;

typedef struct
{
    VOS_UINT8               ucSid;
    CBT_MODEM_SSID_STRU     stModemSsid;
    VOS_UINT8               ucSessionID;
    CBT_FRAGMENT_INFO_STRU  stMsgSegment;
    VOS_UINT32              ulTransId;
    CBT_TIME_STAMP_STRU     stTimeStamp;
} CBT_MSG_HEAD_STRU;

typedef struct
{
    CBT_MSG_HEAD_STRU               stMsgHeader;
    VOS_UINT16                      usMsgId;
    CBT_COMPONENT_MODE_STRU         stCompMode;
    VOS_UINT32                      ulMsgLength;
    VOS_UINT8                       aucPara[4];
} CBT_UNIFORM_MSG_STRU;

typedef struct
{
    CBT_MSG_HEAD_STRU               stMsgHeader;
    VOS_UINT16                      usMsgId;
    VOS_UINT16                      usCompMode;
    VOS_UINT32                      ulMsgLength;
    VOS_UINT32                      ulReceiverPid;
    VOS_UINT8                       aucPara[4];
} CBT_TRANS_MSG_STRU;

typedef struct
{
    VOS_UINT16                          usPrimId;
    VOS_UINT16                          usReserve;
    VOS_UINT8                           aucPara[4];
} CBT_HOOK_MSG_STRU;

typedef struct
{
    VOS_UINT16                          usTransPrimId;
    VOS_UINT16                          usRsv;
    VOS_UINT16                          usMsgId;
    VOS_UINT16                          usCompMode;
    VOS_UINT8                           aucPara[4];
}CBT_RCV_TRANS_MSG_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgId;
    VOS_UINT16                          usCompMode;
    VOS_UINT8                           aucPara[4];
}CBT_SEND_COMM_MSG_STRU;

typedef struct
{
    VOS_UINT16                          usMsgId;
    VOS_UINT16                          usCompMode;
    VOS_UINT8                           aucPara[4];
}PS_TO_CBT_MSG_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                      usPrimId;
    VOS_UINT16                      usLen;
    VOS_UINT8                       aucData[4];
}CBT_CTOA_MSG_STRU;


typedef VOS_UINT32 (*CBT_FUN)(CBT_UNIFORM_MSG_STRU *pstCbtMsg, VOS_UINT16 usReturnPrimId);

typedef struct
{
    CBT_FUN     pfCbtFun;           /*Reserves the pointer of function handles current msg.*/
    VOS_UINT32  ulPrimId;           /*Indicates current msg type.*/
    VOS_UINT32  ulReturnPrimId;     /*Indicates return msg type.*/
} CBT_MSG_FUN_STRU;

typedef struct
{
    CBT_MODEM_SSID_STRU         stModemSsid;            /* Modem */
    VOS_UINT8                   ucReserve;
    CBT_COMPONENT_MODE_STRU     stCompMode;

    VOS_UINT32                  ulBand;
    VOS_UINT16                  usTxChan;
    VOS_UINT16                  usRxChan;
    VOS_UINT16                  usPcl;
    VOS_UINT16                  usRsv1;

    VOS_UINT16                  usWSyncStatus;
    VOS_UINT16                  usCSyncStatus;
    VOS_UINT16                  usCReportFlag;
    VOS_UINT16                  usGeReportFlag;

    VOS_UINT16                  usRecvPrimId;
    VOS_UINT16                  usEnableReport;

    VOS_UINT16                  usTotalFrameNum;
    VOS_UINT16                  usCurFrameNum;
    VOS_UINT16                  usReportFrameNum;
    VOS_UINT16                  usCurReportFrameNum;

    VOS_UINT16                  usTxTotalFrameNum;
    VOS_UINT16                  usTxCurFrameNum;

    VOS_SEM                     ulCbtTotalFrameSem;
    VOS_SEM                     ulCbtTxSegmentFrameSem;
    VOS_SEM                     ulCbtSyncSem;
    VOS_SEM                     ulCbtGeDlQualitySem;
}CBT_LISI_MODE_CTRL_STRU;

typedef struct
{
    CBT_MSG_HEAD_STRU      stHeader;
    VOS_UINT16             usPrimId;   /*Indicates current msg type.*/
    VOS_UINT16             usToolId;   /*Not used now.*/
    VOS_UINT32             ulMsgLength;
    VOS_UINT16             usBerValue[2];
}CBT_GE_DL_STATUS_STRU;

typedef struct
{
    CBT_MSG_HEAD_STRU       stHeader;
    VOS_UINT16              usPrimId;            /*Indicates current msg type.*/
    VOS_UINT16              usToolId;            /*Not used now.*/
    VOS_UINT32              ulMsgLength;

    VOS_UINT16              usTotalFrameNum;
    VOS_UINT16              usCurFrameNum;
    VOS_UINT16              usBand;
    VOS_UINT16              usRxChan;
    VOS_UINT16              usCrcData;
    VOS_UINT16              usRsv;
    VOS_UINT32              ulDataLen;
    VOS_UINT8               aucData[OM_BER_DATA_MAX_SIZE];
}CBT_LIST_MODE_BER_IND_STRU;

typedef struct
{
    CBT_MSG_HEAD_STRU       stHeader;
    VOS_UINT16              usPrimId;            /*Indicates current msg type.*/
    VOS_UINT16              usToolId;            /*Not used now.*/
    VOS_UINT32              ulMsgLength;

    VOS_UINT32              ulErrorCode;
    VOS_UINT16              usTotalFrameNum;
    VOS_UINT16              usBadFrameNum;

}CBT_C_FER_DATA_CNF_STRU;

typedef struct
{
    VOS_UINT16  usGpioNo;
    VOS_UINT16  usGpioLevel;
} CBT_LT_SWITCH_RF_ANT_STRU;


typedef VOS_UINT32 (* RTTAgentFunc)(VOS_VOID *pMsg);

VOS_VOID CBT_ResetMsgHead(CBT_UNIFORM_MSG_STRU * pstCbtToPcMsg);

VOS_UINT32 CBT_SendData(CBT_UNIFORM_MSG_STRU * pucMsg, VOS_UINT16 usMsgLen);

VOS_VOID CBT_SendResultChannel(CBT_MODEM_SSID_STRU stModemSsid, CBT_COMPONENT_MODE_STRU stCompMode,
                                VOS_UINT16 usReturnPrimId, VOS_UINT32 ulResult);
VOS_VOID CBT_SendContentChannel(CBT_MODEM_SSID_STRU stModemSsid, CBT_COMPONENT_MODE_STRU stCompMode,
                                       VOS_UINT16 usReturnPrimId, CBT_UNIFORM_MSG_STRU * pstCbtToPcMsg);
VOS_UINT32 CBT_GreenChannel(CBT_MODEM_SSID_STRU stModemSsid, CBT_COMPONENT_MODE_STRU stCompMode, VOS_UINT16 usPrimId,
                            VOS_UINT8 * pucData, VOS_UINT16 usLen);

VOS_VOID SLEEP_ActivateHw(SLEEP_MODE_ENUM_UINT32 enMode);

extern VOS_VOID OM_NoSigCtrlInit(VOS_UINT8 ucModemId);
extern VOS_VOID CBT_ListModeCtrlInit(VOS_UINT8 ucModemId);
extern VOS_VOID DIAG_TraceReport(VOS_VOID *);

extern VOS_UINT32 RTTAGENT_TmodeSet(VOS_VOID * pMsg);
extern VOS_UINT32 RTTAGENT_BandSWSetNoCardSig(VOS_VOID * pMsg);
extern VOS_UINT32 RTTAGENT_FchanTDSSet(VOS_VOID * pMsg);
extern VOS_UINT32 RTTAGENT_FchanLTESet(VOS_VOID * pMsg);
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
extern VOS_VOID I1_SLEEP_ActivateHw(SLEEP_MODE_ENUM_UINT32 enMode);
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
