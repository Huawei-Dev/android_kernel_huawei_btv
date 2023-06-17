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

/******************************************************************************

                  ???????? (C), 2001-2011, ????????????????

 ******************************************************************************
  ?? ?? ??   : OmApi.h
  ?? ?? ??   : ????
  ??    ??   : ???? 47350
  ????????   : 2011??9??29??
  ????????   :
  ????????   : OM??????????????
  ????????   :
  ????????   :
  1.??    ??   : 2012??1??7??
    ??    ??   : ???? 47350
    ????????   : ????????

******************************************************************************/

#ifndef __OMAPI_H__
#define __OMAPI_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ??????????????
*****************************************************************************/
#include "vos.h"
#include "phyoaminterface.h"

#pragma pack(4)

/*****************************************************************************
  2 ??????
*****************************************************************************/


/*****************************************************************************
  3 ????????
*****************************************************************************/

enum SPY_DATA_DOWNGRADE_RESULT_ENUM
{
    SPY_DATA_DOWNGRADE_CONTINUE              = 0,
    SPY_DATA_DOWNGRADE_FINISH                = 1,
    SPY_DATA_DOWNGRADE_RESULT_BUTT
};
typedef VOS_UINT32 SPY_DATA_DOWNGRADE_RESULT_ENUM_UINT32;

enum SPY_DATA_UPGRADE_RESULT_ENUM
{
    SPY_DATA_UPGRADE_CONTINUE              = 0,
    SPY_DATA_UPGRADE_FINISH                = 1,
    SPY_DATA_UPGRADE_RESULT_BUTT
};
typedef VOS_UINT32 SPY_DATA_UPGRADE_RESULT_ENUM_UINT32;

enum SPY_TEMPROTECT_SWITCH_STATE_ENUM
{
    SPY_TEMPROTECT_SWITCH_OFF              = 0,
    SPY_TEMPROTECT_SWITCH_ON               = 1,
    SPY_TEMPROTECT_SWITCHT_BUTT
};
typedef VOS_UINT32 SPY_TEMPROTECT_SWITCH_STATE_ENUM_UINT32;


/*****************************************************************************
 ??????    : TEMPPRT_AT_MSG_ID_ENUM
 ????????  : SPY??AT????????????
*****************************************************************************/
enum TEMPPRT_AT_MSG_ID_ENUM
{
    /* SPY -> AT */
    ID_TEMPPRT_AT_EVENT_IND = 0 ,   /* _H2ASN_MsgChoice TEMP_PROTECT_EVENT_AT_IND_STRU */

    ID_TEMPPRT_STATUS_AT_EVENT_IND, /* _H2ASN_MsgChoice TEMP_PROTECT_EVENT_AT_IND_STRU */

    ID_TEMPPRT_AT_MSG_ID_BUTT

};
typedef VOS_UINT32 TEMPPRT_AT_MSG_ID_ENUM_UINT32;

/*****************************************************************************
 ??????    : SLEEP_SYSTEM_STATE_ENUM
 ????????  : ????????

  1.??    ??   : 2012??07??31??
    ??    ??   : g47350
    ????????   : V900R001 MSP??????????????????????
*****************************************************************************/
enum SLEEP_SYSTEM_STATE_ENUM
{
    SLEEP_NORMAL_STATE = 0,                             /* ???????? */
    SLEEP_MASTER_TEMP_LP_STATE,                         /* ??????????????(????) */
    SLEEP_MASTER_LP_STATE,                              /* ?????????????? */
    SLEEP_TEMP_NORMAL_STATE,                            /* ????????(????) */
    SLEEP_SLAVE_LP_STATE,                               /* ?????????????? */
    SLEEP_STATE_BUTT
};
typedef VOS_UINT32 SLEEP_SYSTEM_STATE_ENUM_UINT32;

/*****************************************************************************
 ??????    : SLEEP_BBE16_SYSTEM_STATE_ENUM
 ????????  : ????????

  1.??    ??   : 2015??08??27??
    ??    ??   : s00207770
    ????????   : C????????????
*****************************************************************************/
enum SLEEP_BBE16_SYSTEM_STATE_ENUM
{
    SLEEP_BBE16_NORMAL_STATE = 0,                       /* ???????? */
    SLEEP_BBE16_MASTER_HALT_STATE,                      /* ????HALT???? */
    SLEEP_BBE16_MASTER_LP_STATE,                        /* ?????????????? */
    SLEEP_BBE16_MASTER_WAKE_STATE,                      /* ???????????? */
    SLEEP_BBE16_MASTER_TEMP_NORMAL_STATE,               /* ????????????(????) */
    SLEEP_BBE16_SLAVE_HALT_STATE,                       /* ????HALT???? */
    SLEEP_BBE16_SLAVE_LP_STATE,                         /* ?????????????? */
    SLEEP_BBE16_SLAVE_WAKE_STATE,                       /* ???????????? */
    SLEEP_BBE16_SLAVE_TEMP_NORMAL_STATE,                /* ????????????(????) */
    SLEEP_BBE16_STATE_BUTT
};
typedef VOS_UINT32 SLEEP_BBE16_SYSTEM_STATE_ENUM_UINT32;

/*****************************************************************************
 ??????    :SLEEP_MSG_ID_ENUM_UINT32
 ????????  :
 ASN.1???? :
 ????????  :SLEEP????ID????
*****************************************************************************/
enum SLEEP_MSG_ID_ENUM
{
    ID_SLEEP_NOTIFY_STATUS_IND = 0,                         /* ????????????????????????PID */

    ID_SLEEP_MSG_ID_BUTT
};
typedef VOS_UINT32 SLEEP_MSG_ID_ENUM_UINT32;

/*****************************************************************************
 ??????    :SLEEP_LOWPOWER_STATE_ENUM_UINT32
 ????????  :
 ASN.1???? :
 ????????  :??????????????
*****************************************************************************/
enum SLEEP_LOWPOWER_STATE_ENUM
{
    SLEEP_LOWPOWER_STATE_OFF = 0,
    SLEEP_LOWPOWER_STATE_ON,
    SLEEP_LOWPOWER_STATE_BUTT
};
typedef VOS_UINT32 SLEEP_LOWPOWER_STATE_ENUM_UINT32;

enum OM_PCV_CHANNEL_EUNM
{
    OM_PCV_CHANNEL_OPEN = 0,
    OM_PCV_CHANNEL_CLOSE,
    OM_PCV_CHANNEL_SWITCH,
    OM_PCV_CHANNEL_BUTT
};

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
typedef SPY_DATA_DOWNGRADE_RESULT_ENUM_UINT32 (*SPY_DOWNGRADE_PROC_FUNC)(VOS_VOID);
typedef SPY_DATA_UPGRADE_RESULT_ENUM_UINT32 (*SPY_UPGRADE_PROC_FUNC)(VOS_VOID);
typedef VOS_VOID (*SPY_RESTORE_PROC_FUNC)(VOS_VOID);

/*****************************************************************************
 ??????    : TEMP_PROTECT_EVENT_AT_IND_STRU
 ????????  :
 ASN.1???? :
 ????????  : SPY??AT??????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                  ulMsgId;
    VOS_UINT32                  ulTempProtectEvent;
    VOS_UINT32                  ulTempProtectParam;
} TEMP_PROTECT_EVENT_AT_IND_STRU;

/*****************************************************************************
 ??????    : SLEEP_NOTIFY_STATUS_MSG_STRU
 ????????  : ??
 ????????  : SLEEP??????????????????????PID????????????

 ????????      :
  1.??    ??   : 2014??3??14??
    ??    ??   : L00256032
    ????????   : V8R1 LowPower&NV_Expand????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ulSenderPid: WUEPS_PID_SLEEP */
    SLEEP_MSG_ID_ENUM_UINT32            enMsgId;
    VOS_RATMODE_ENUM_UINT32             enRatMode;
    SLEEP_SYSTEM_STATE_ENUM_UINT32      enState;            /* ????????????SLEEP_SLAVE_LP_STATE */
    SLEEP_LOWPOWER_STATE_ENUM_UINT32    enLPState;
} SLEEP_NOTIFY_STATUS_MSG_STRU;


/*****************************************************************************
  8 UNION????
*****************************************************************************/


/*****************************************************************************
  9 OTHERS????
*****************************************************************************/


/*****************************************************************************
  10 ????????
*****************************************************************************/

extern VOS_VOID Spy_DownGradeRegister(SPY_DOWNGRADE_PROC_FUNC pFnDowngradeProcFunc);

extern VOS_VOID Spy_UpGradeRegister(SPY_UPGRADE_PROC_FUNC pFnUpgradeProcFunc);

extern VOS_VOID Spy_RestoreRegister(SPY_RESTORE_PROC_FUNC pFnRestoreProcFunc);

extern VOS_VOID GUSLEEP_MasterAwakeSlave(VOS_VOID);

extern VOS_VOID TLSLEEP_MasterAwakeSlave(VOS_VOID);

extern VOS_UINT32 SLEEP_NotifyStateReg(VOS_UINT32 ulRcvPid, VOS_RATMODE_ENUM_UINT32 enRatMode);

extern VOS_UINT32 SLEEP_NotifyStateUnreg(VOS_UINT32 ulRcvPid);

extern VOS_VOID OM_SetDrxTimerWakeSrcAllVote(MODEM_ID_ENUM_UINT16 enModem);

extern VOS_VOID OM_SetDrxTimerWakeSrc(MODEM_ID_ENUM_UINT16 enModem, VOS_RATMODE_ENUM_UINT32 enMode);

extern VOS_VOID OM_DelDrxTimerWakeSrc(MODEM_ID_ENUM_UINT16 enModem, VOS_RATMODE_ENUM_UINT32 enMode);

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of OmApi.h */
