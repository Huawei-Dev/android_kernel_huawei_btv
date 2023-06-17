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

#ifndef __TAF_APP_MMA_H__
#define __TAF_APP_MMA_H__

#include "TafTypeDef.h"
/*#include "NasCommDef.h" */
#include "UsimPsInterface.h"

#include  "AtMnInterface.h"
/* Added by s00217060 for VoLTE_PhaseI  ????, 2013-07-27, begin */
#include "TafNvInterface.h"
/* Added by s00217060 for VoLTE_PhaseI  ????, 2013-07-27, end */

#include "AppVcApi.h"

#include "MnCallApi.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 ??????
*****************************************************************************/

#define TAF_MMA_PNN_INFO_MAX_NUM                           (16)                /* AT????????MMA??????????PNN???? */

/* Added by f62575 for SS FDN&Call Control, 2013-05-06, begin */
#define TAF_MMA_PLMN_MNC_TWO_BYTES                          (2)                 /* MNC????????????3??????????????2????3???????? */

/* ????????????TAF_PH_OPER_NAME_LONG??40??????100??A??????????????????????????????????????*/
#define TAF_MMA_COPN_PLMN_MAX_NUM                           (16)                /* AT????????MMA???????????????????? */

#define TAF_MMA_NET_SCAN_MAX_FREQ_NUM                       (20)

/* Added by s00246516 for L-C??????????, 2014-01-24, Begin */
#define TAF_MMA_REG_MAX_PLMN_NUM                            (8)
#define TAF_MMA_REG_MAX_CELL_NUM                            (8)
/* Added by s00246516 for L-C??????????, 2014-01-24, End */

#define TAF_MMA_MAX_CDMA_PN_NUM                             (511)
#define TAF_MMA_WILDCARD_CDMA_PN_NUM                        (0xFFFF)
#define TAF_MMA_MAX_EVDO_PN_NUM                             (511)
#define TAF_MMA_WILDCARD_EVDO_PN_NUM                        (0xFFFF)

#define TAF_MMA_SRV_ACQ_RAT_NUM_MAX                         (3)

#define TAF_MMA_MAX_WHITE_LOCK_SID_NUM                      (5)
#define TAF_MMA_MAX_ANT_NUM                                 (4)

#define TAF_MMA_VERSION_INFO_LEN                            (9)
#define TAF_MMA_MAX_EHPLMN_NUM                              (17)
#define TAF_MMA_MAX_DPLMN_NUM                               (256)
#define TAF_MMA_SIM_FORMAT_PLMN_LEN                         (3)
#define TAF_MMA_MAX_STR_LEN                                 (1600)
#define TAF_MMA_MAX_EHPLMN_STR                              (128)


/* CSG list????????????8??????csg??????????2k */
#define TAF_MMA_MAX_CSG_ID_LIST_NUM                         (8)

#if (FEATURE_ON == FEATURE_CSG)
#define TAF_MMA_MAX_HOME_NODEB_NAME_LEN                     (48)
#define TAF_MMA_MAX_CSG_TYPE_LEN                            (12)
#else
#define TAF_MMA_MAX_HOME_NODEB_NAME_LEN                     (4)
#define TAF_MMA_MAX_CSG_TYPE_LEN                            (4)
#endif

#define TAF_MMA_INVALID_CSG_ID_VALUE                        (0xFFFFFFFF)
#define TAF_MMA_INVALID_MCC                                 (0xFFFFFFFF)
#define TAF_MMA_INVALID_MNC                                 (0xFFFFFFFF)
/*****************************************************************************
 ??????    : TAF_MMA_PLMN_MNC_DIGIT_MASK_ENUM
 ????????  : ??????????PLMN??????????MNC????????????
             0: DRV_AGENT_TSELRF_SET_ERROR_NO_ERROR ??????????????
             1: DRV_AGENT_TSELRF_SET_ERROR_LOADDSP  ??????????????
*****************************************************************************/
enum TAF_MMA_PLMN_MNC_DIGIT_MASK_ENUM
{
    TAF_MMA_PLMN_MNC_DIGIT1_MASK = 0x00f,
    TAF_MMA_PLMN_MNC_DIGIT2_MASK = 0x0f0,
    TAF_MMA_PLMN_MNC_DIGIT3_MASK = 0xf00,
    TAF_MMA_PLMN_MNC_DIGIT_MASK_BUTT
};

enum TAF_MMA_PLMN_MNC_DIGIT_OFFSET_ENUM
{
    TAF_MMA_PLMN_MNC_DIGIT1_OFFSET = 0,
    TAF_MMA_PLMN_MNC_DIGIT2_OFFSET = 4,
    TAF_MMA_PLMN_MNC_DIGIT3_OFFSET = 8,
    TAF_MMA_PLMN_MNC_DIGIT_OFFSET_BUTT
};

enum TAF_MMA_PLMN_MCC_DIGIT_MASK_ENUM
{
    TAF_MMA_PLMN_MCC_DIGIT1_MASK = 0x00f,
    TAF_MMA_PLMN_MCC_DIGIT2_MASK = 0x0f0,
    TAF_MMA_PLMN_MCC_DIGIT3_MASK = 0xf00,
    TAF_MMA_PLMN_MCC_DIGIT_MASK_BUTT
};

enum TAF_MMA_PLMN_MCC_DIGIT_OFFSET_ENUM
{
    TAF_MMA_PLMN_MCC_DIGIT1_OFFSET = 0,
    TAF_MMA_PLMN_MCC_DIGIT2_OFFSET = 4,
    TAF_MMA_PLMN_MCC_DIGIT3_OFFSET = 8,
    TAF_MMA_PLMN_MCC_DIGIT_OFFSET_BUTT
};
/* Added by f62575 for SS FDN&Call Control, 2013-05-06, end */

/** ****************************************************************************
 * Name        : TAF_MMA_CDMA_CALL_TYPE_ENUM_UINT8
 *
 * Description :
 *******************************************************************************/
enum TAF_MMA_CDMA_CALL_TYPE_ENUM
{
    TAF_MMA_1X_EMERGENCY_VOICE_CALL     = 0x00,
    TAF_MMA_1X_NORMAL_VOICE_CALL        = 0x01,
    TAF_MMA_1X_NORMAL_DATA_CALL         = 0x02,
    TAF_MMA_DO_NORMAL_DATA_CALL         = 0x03,
    TAF_MMA_CDMA_CALL_TYPE_BUTT         = 0x04
};
typedef VOS_UINT8 TAF_MMA_CDMA_CALL_TYPE_ENUM_UINT8;

#define NAS_MM_INFO_IE_NULL             (0x00)
#define NAS_MM_INFO_IE_LTZ              0x01        /* Local time zone */
#define NAS_MM_INFO_IE_UTLTZ            0x02        /* Universal time and local time zone */
#define NAS_MM_INFO_IE_LSA              0x04        /* LSA Identity */
#define NAS_MM_INFO_IE_DST              0x08        /* Network Daylight Saving Time */
#define NAS_MM_INFO_IE_NETWORKFULLNAME  0x10        /* Full name for network */
#define NAS_MM_INFO_IE_NETWORKSHORTNAME 0x20        /* Short name for network */

/* ????IMSI???????? */
#define   NAS_MAX_IMSI_LENGTH           (9)
#define   NAS_VERSION_LEN               (9)
#define   NAS_IMSI_STR_LEN              (15)

/* Added by f62575 for AT Project??2011-10-04,  Begin*/
/* +CSQLVL ???????????? */
#define AT_CSQLVL_MAX_NUM               (3)
#define AT_CSQLVL_LEVEL_0               (0)
#define AT_CSQLVL_LEVEL_1               (20)
#define AT_CSQLVL_LEVEL_2               (40)
#define AT_CSQLVL_LEVEL_3               (60)
/* Added by f62575 for AT Project??2011-10-04,  End*/

#define DRVAGENT_GPIOPL_MAX_LEN          (20)

#define TAF_CDROM_VERSION_LEN         128

/*??????????????????*/
#define DRV_AGENT_MAX_HARDWARE_LEN            (31)

#define TAF_MAX_REVISION_ID_LEN     (31)

#define TAF_MAX_MODEL_ID_LEN     (31)

#define TAF_MAX_HARDWARE_LEN            (31)


#define PRODUCTION_CARD_TYPE   "WCDMA"

#define TAF_UTRANCTRL_UTRAN_MODE_FDD    (0)
#define TAF_UTRANCTRL_UTRAN_MODE_TDD    (1)

/* Modified by l60609 for DSDA Phase III, 2013-3-4, Begin */
/* Added by L60609 for AT Project??2011-10-05,  Begin*/
#define AT_HS_PARA_MAX_LENGTH           (9)
/* Added by L60609 for AT Project??2011-10-05,  End*/
/* Modified by l60609 for DSDA Phase III, 2013-3-4, End */

#define TAF_MMA_UTRA_BLER_INVALID       (99)
#define TAF_MMA_RSSI_LOWER_LIMIT        (-114)
#define TAF_MMA_UTRA_RSCP_UNVALID       (-140)

/* Added by s00217060 for ????????AT??????????????C??, 2013-4-3, begin */
#define TAF_MMA_RPT_CFG_MAX_SIZE         (8)
/* Added by s00217060 for ????????AT??????????????C??, 2013-4-3, end */

#define TAF_MMA_MSG_ID_BASE             (0x1000)

#define TAF_MMA_MAX_SRCHED_LAI_NUM     (18)

/*****************************************************************************
  6 ????????
*****************************************************************************/


/*****************************************************************************
 ??????    : TAF_MMA_MSG_TYPE_ENUM
 ????????  : MMA????????????
*****************************************************************************/
enum TAF_MMA_MSG_TYPE_ENUM
{
    ID_TAF_MMA_MSG_TYPE_BEGIN = TAF_MMA_MSG_ID_BASE,

    ID_TAF_MMA_OM_MAINTAIN_INFO_IND     ,                                           /* _H2ASN_MsgChoice ATMMA_OM_MAINTAIN_INFO_IND_STRU*/ /**< @sa ATMMA_OM_MAINTAIN_INFO_IND_STRU */
    ID_TAF_MMA_USIM_STATUS_IND          ,                                           /* _H2ASN_MsgChoice AT_MMA_USIM_STATUS_IND_STRU*/
    ID_TAF_MMA_SIMLOCK_STAUS_QUERY_CNF  ,                                           /* _H2ASN_MsgChoice AT_MMA_SIMLOCK_STATUS_STRU*/

    ID_TAF_MMA_PHONE_MODE_SET_REQ       ,                                           /* _H2ASN_MsgChoice TAF_MMA_PHONE_MODE_SET_REQ_STRU*/
    ID_TAF_MMA_PHONE_MODE_SET_CNF       ,                                           /* _H2ASN_MsgChoice TAF_MMA_PHONE_MODE_SET_CNF_STRU*/
    ID_TAF_MMA_SYS_CFG_SET_REQ          ,                                           /* _H2ASN_MsgChoice TAF_MMA_SYS_CFG_REQ_STRU*/
    ID_TAF_MMA_SYS_CFG_SET_CNF          ,                                           /* _H2ASN_MsgChoice TAF_MMA_SYS_CFG_CNF_STRU*/
    ID_TAF_MMA_ACQ_BEST_NETWORK_REQ     ,                                           /* _H2ASN_MsgChoice TAF_MMA_ACQ_REQ_STRU*/
    ID_TAF_MMA_ACQ_BEST_NETWORK_CNF     ,                                           /* _H2ASN_MsgChoice TAF_MMA_ACQ_CNF_STRU*/
    ID_TAF_MMA_REG_REQ                  ,                                           /* _H2ASN_MsgChoice TAF_MMA_REG_REQ_STRU*/
    ID_TAF_MMA_REG_CNF                  ,                                           /* _H2ASN_MsgChoice TAF_MMA_REG_CNF_STRU*/
    ID_TAF_MMA_DETACH_REQ               ,                                           /* _H2ASN_MsgChoice TAF_MMA_DETACH_REQ_STRU*/
    ID_TAF_MMA_DETACH_CNF               ,                                           /* _H2ASN_MsgChoice TAF_MMA_DETACH_CNF_STRU*/
    ID_TAF_MMA_POWER_SAVE_REQ           ,                                           /* _H2ASN_MsgChoice TAF_MMA_POWER_SAVE_REQ_STRU*/
    ID_TAF_MMA_POWER_SAVE_CNF           ,                                           /* _H2ASN_MsgChoice TAF_MMA_POWER_SAVE_CNF_STRU*/
    ID_TAF_MMA_SERVICE_STATUS_IND       ,                                           /* _H2ASN_MsgChoice TAF_MMA_SERVICE_STATUS_IND_STRU*/
    ID_TAF_MMA_ACQ_IND                  ,                                           /* _H2ASN_MsgChoice TAF_MMA_ACQ_IND_STRU*/
    ID_TAF_MMA_SYS_INFO_IND             ,                                           /* _H2ASN_MsgChoice TAF_MMA_SYS_INFO_IND_STRU*/
    ID_TAF_MMA_SIM_STATUS_IND           ,                                           /* _H2ASN_MsgChoice TAF_MMA_SIM_STATUS_IND_STRU*/

    ID_TAF_MMA_SRV_ACQ_REQ,                                                         /* _H2ASN_MsgChoice TAF_MMA_SRV_ACQ_REQ_STRU*/
    ID_TAF_MMA_SRV_ACQ_CNF,                                                         /* _H2ASN_MsgChoice TAF_MMA_SRV_ACQ_CNF_STRU*/
    ID_TAF_MMA_IMS_SRV_INFO_NOTIFY      ,                                           /* _H2ASN_MsgChoice TAF_MMA_IMS_SRV_INFO_NOTIFY_STRU*/

    ID_TAF_MMA_CDMA_MO_CALL_START_NTF,                                               /* _H2ASN_MsgChoice TAF_MMA_CDMA_MO_CALL_START_NTF_STRU*/ /**< @sa TAF_MMA_CDMA_MO_CALL_START_NTF_STRU */
    ID_TAF_MMA_CDMA_MO_CALL_SUCCESS_NTF,                                             /* _H2ASN_MsgChoice TAF_MMA_CDMA_MO_CALL_SUCCESS_NTF_STRU*/ /**< @sa TAF_MMA_CDMA_MO_CALL_SUCCESS_NTF_STRU */
    ID_TAF_MMA_CDMA_CALL_REDIAL_SYSTEM_ACQUIRE_NTF,                                  /* _H2ASN_MsgChoice TAF_MMA_CDMA_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU*/ /**< @sa TAF_MMA_CDMA_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU */
    ID_TAF_MMA_CDMA_MO_CALL_END_NTF,                                                 /* _H2ASN_MsgChoice TAF_MMA_CDMA_MO_CALL_END_NTF_STRU*/ /**< @sa TAF_MMA_CDMA_MO_CALL_END_NTF_STRU */

    ID_TAF_MMA_CDMA_FREQ_LOCK_SET_REQ,                                               /* _H2ASN_MsgChoice TAF_MMA_CFREQ_LOCK_SET_REQ_STRU*/
    ID_TAF_MMA_CDMA_FREQ_LOCK_SET_CNF,                                               /* _H2ASN_MsgChoice TAF_MMA_CFREQ_LOCK_SET_CNF_STRU*/
    ID_TAF_MMA_CDMA_FREQ_LOCK_QRY_REQ,                                               /* _H2ASN_MsgChoice TAF_MMA_CFREQ_LOCK_QUERY_REQ_STRU*/
    ID_TAF_MMA_CDMA_FREQ_LOCK_QRY_CNF,                                               /* _H2ASN_MsgChoice TAF_MMA_CFREQ_LOCK_QUERY_CNF_STRU*/

    ID_TAF_MMA_CDMACSQ_SET_REQ,                                                      /* _H2ASN_MsgChoice TAF_MMA_CDMACSQ_SET_REQ_STRU*/
    ID_TAF_MMA_CDMACSQ_SET_CNF,                                                      /* _H2ASN_MsgChoice TAF_MMA_CDMACSQ_SET_CNF_STRU*/
    ID_TAF_MMA_CDMACSQ_QRY_REQ,                                                      /* _H2ASN_MsgChoice TAF_MMA_CDMACSQ_QRY_REQ_STRU*/
    ID_TAF_MMA_CDMACSQ_QRY_CNF,                                                      /* _H2ASN_MsgChoice TAF_MMA_CDMACSQ_QUERY_CNF_STRU*/
    ID_TAF_MMA_CDMACSQ_IND,                                                          /* _H2ASN_MsgChoice TAF_MMA_CDMACSQ_IND_STRU*/

    ID_TAF_MMA_CTIME_IND,                                                             /* _H2ASN_MsgChoice TAF_MMA_CTIME_IND_STRU*/

    ID_TAF_MMA_CFPLMN_SET_REQ,                                                        /* _H2ASN_MsgChoice TAF_MMA_CFPLMN_SET_REQ_STRU*/
    ID_TAF_MMA_CFPLMN_QUERY_REQ,                                                      /* _H2ASN_MsgChoice TAF_MMA_CFPLMN_QUERY_REQ_STRU*/
    ID_TAF_MMA_CFPLMN_SET_CNF,                                                        /* _H2ASN_MsgChoice TAF_MMA_CFPLMN_SET_CNF_STRU*/
    ID_TAF_MMA_CFPLMN_QUERY_CNF,                                                      /* _H2ASN_MsgChoice TAF_MMA_CFPLMN_QUERY_CNF_STRU*/

    ID_TAF_MMA_PREF_PLMN_SET_REQ,                                                      /* _H2ASN_MsgChoice TAF_MMA_PREF_PLMN_SET_REQ_STRU*/
    ID_TAF_MMA_PREF_PLMN_SET_CNF,                                                      /* _H2ASN_MsgChoice TAF_MMA_PREF_PLMN_SET_CNF_STRU*/
    ID_TAF_MMA_PREF_PLMN_QUERY_REQ,                                                      /* _H2ASN_MsgChoice TAF_MMA_PREF_PLMN_QUERY_REQ_STRU*/
    ID_TAF_MMA_PREF_PLMN_QUERY_CNF,                                                      /* _H2ASN_MsgChoice TAF_MMA_PREF_PLMN_QUERY_CNF_STRU*/
    ID_TAF_MMA_PREF_PLMN_TEST_REQ,                                                      /* _H2ASN_MsgChoice TAF_MMA_PREF_PLMN_TEST_REQ_STRU*/
    ID_TAF_MMA_PREF_PLMN_TEST_CNF,                                                      /* _H2ASN_MsgChoice TAF_MMA_PREF_PLMN_TEST_CNF_STRU*/

    ID_TAF_MMA_PHONE_MODE_QRY_REQ,                                              /* _H2ASN_MsgChoice TAF_MMA_PHONE_MODE_QRY_REQ_STRU */
    ID_TAF_MMA_PHONE_MODE_QRY_CNF,                                              /* _H2ASN_MsgChoice TAF_MMA_PHONE_MODE_QRY_CNF_STRU */

    ID_TAF_MMA_QUICKSTART_SET_REQ,                                              /* _H2ASN_MsgChoice TAF_MMA_QUICKSTART_SET_REQ_STRU */
    ID_TAF_MMA_QUICKSTART_SET_CNF,                                              /* _H2ASN_MsgChoice TAF_MMA_QUICKSTART_SET_CNF_STRU */
    ID_TAF_MMA_QUICKSTART_QRY_REQ,                                              /* _H2ASN_MsgChoice TAF_MMA_QUICKSTART_QRY_REQ_STRU */
    ID_TAF_MMA_QUICKSTART_QRY_CNF,                                              /* _H2ASN_MsgChoice TAF_MMA_QUICKSTART_QRY_CNF_STRU */

    ID_TAF_MMA_AUTO_ATTACH_SET_REQ,                                             /* _H2ASN_MsgChoice TAF_MMA_AUTO_ATTACH_SET_REQ_STRU */
    ID_TAF_MMA_AUTO_ATTACH_SET_CNF,                                             /* _H2ASN_MsgChoice TAF_MMA_AUTO_ATTACH_SET_CNF_STRU */
    ID_TAF_MMA_AUTO_ATTACH_QRY_REQ,                                             /* _H2ASN_MsgChoice TAF_MMA_AUTO_ATTACH_QRY_REQ_STRU */
    ID_TAF_MMA_AUTO_ATTACH_QRY_CNF,                                             /* _H2ASN_MsgChoice TAF_MMA_AUTO_ATTACH_QRY_CNF_STRU */

    ID_TAF_MMA_SYSCFG_QRY_REQ,                                                  /* _H2ASN_MsgChoice TAF_MMA_SYSCFG_QRY_REQ_STRU */
    ID_TAF_MMA_SYSCFG_QRY_CNF,                                                  /* _H2ASN_MsgChoice TAF_MMA_SYSCFG_QRY_CNF_STRU */
    ID_TAF_MMA_SYSCFG_TEST_REQ,                                                 /* _H2ASN_MsgChoice TAF_MMA_SYSCFG_TEST_REQ_STRU */
    ID_TAF_MMA_SYSCFG_TEST_CNF,                                                 /* _H2ASN_MsgChoice TAF_MMA_SYSCFG_TEST_CNF_STRU */

    ID_TAF_MMA_CRPN_QRY_REQ,                                                    /* _H2ASN_MsgChoice TAF_MMA_CRPN_QRY_REQ_STRU */
    ID_TAF_MMA_CRPN_QRY_CNF,                                                    /* _H2ASN_MsgChoice TAF_MMA_CRPN_QRY_CNF_STRU */

    ID_TAF_MMA_CMM_SET_REQ,                                                     /* _H2ASN_MsgChoice TAF_MMA_CMM_SET_REQ_STRU */
    ID_TAF_MMA_CMM_SET_CNF,                                                     /* _H2ASN_MsgChoice TAF_MMA_CMM_SET_CNF_STRU */

    ID_TAF_MMA_PLMN_AUTO_RESEL_REQ,                                             /* _H2ASN_MsgChoice TAF_MMA_PLMN_AUTO_RESEL_REQ_STRU */
    ID_TAF_MMA_PLMN_AUTO_RESEL_CNF,                                             /* _H2ASN_MsgChoice TAF_MMA_PLMN_AUTO_RESEL_CNF_STRU */
    ID_TAF_MMA_PLMN_SPECIAL_SEL_REQ,                                            /* _H2ASN_MsgChoice TAF_MMA_PLMN_SPECIAL_SEL_REQ_STRU */
    ID_TAF_MMA_PLMN_SPECIAL_SEL_CNF,                                            /* _H2ASN_MsgChoice TAF_MMA_PLMN_SPECIAL_SEL_CNF_STRU */
    ID_TAF_MMA_PLMN_LIST_ABORT_REQ,                                             /* _H2ASN_MsgChoice TAF_MMA_PLMN_LIST_ABORT_REQ_STRU */
    ID_TAF_MMA_PLMN_LIST_ABORT_CNF,                                             /* _H2ASN_MsgChoice TAF_MMA_PLMN_LIST_ABORT_CNF_STRU */

    ID_TAF_MMA_CERSSI_SET_REQ,                                                  /* _H2ASN_MsgChoice TAF_MMA_CERSSI_SET_REQ_STRU */
    ID_TAF_MMA_CERSSI_SET_CNF,                                                  /* _H2ASN_MsgChoice TAF_MMA_CERSSI_SET_CNF_STRU */
    ID_TAF_MMA_CERSSI_QRY_REQ,                                                  /* _H2ASN_MsgChoice TAF_MMA_CERSSI_INFO_QRY_REQ_STRU */
    ID_TAF_MMA_CERSSI_QRY_CNF,                                                  /* _H2ASN_MsgChoice TAF_MMA_CERSSI_INFO_QRY_CNF_STRU */
    ID_TAF_MMA_RSSI_INFO_IND,                                                   /* _H2ASN_MsgChoice TAF_MMA_RSSI_INFO_IND_STRU */

    ID_TAF_MMA_MT_POWER_DOWN_REQ,                                               /* _H2ASN_MsgChoice TAF_MMA_MT_POWER_DOWN_REQ_STRU */
    ID_TAF_MMA_MT_POWER_DOWN_CNF,                                               /* _H2ASN_MsgChoice TAF_MMA_MT_POWER_DOWN_CNF_STRU */

    ID_TAF_MMA_PREF_PLMN_TYPE_SET_REQ,                                          /* _H2ASN_MsgChoice TAF_MMA_PREF_PLMN_TYPE_SET_REQ_STRU */
    ID_TAF_MMA_PREF_PLMN_TYPE_SET_CNF,                                          /* _H2ASN_MsgChoice TAF_MMA_PREF_PLMN_TYPE_SET_CNF_STRU */

    ID_TAF_MMA_CIPHER_QRY_REQ,                                                  /* _H2ASN_MsgChoice TAF_MMA_CIPHER_QRY_REQ_STRU */
    ID_TAF_MMA_CIPHER_QRY_CNF,                                                  /* _H2ASN_MsgChoice TAF_MMA_CIPHER_QRY_CNF_STRU */

    ID_TAF_MMA_LOCATION_INFO_QRY_REQ,                                           /* _H2ASN_MsgChoice TAF_MMA_LOCATION_INFO_QRY_REQ_STRU */
    ID_TAF_MMA_LOCATION_INFO_QRY_CNF,                                           /* _H2ASN_MsgChoice TAF_MMA_LOCATION_INFO_QRY_CNF_STRU */
    ID_TAF_MMA_CDMA_LOCINFO_QRY_REQ,                                            /* _H2ASN_MsgChoice TAF_MMA_CDMA_LOCINFO_QRY_REQ_STRU */
    ID_TAF_MMA_CDMA_LOCINFO_QRY_CNF,                                            /* _H2ASN_MsgChoice TAF_MMA_CDMA_LOCINFO_QRY_CNF_STRU */
    ID_TAF_MMA_CSID_IND,                                                        /* _H2ASN_MsgChoice TAF_MMA_CSIDNID_IND_STRU */

    /* Added by k902809 for Iteration 11, 2015-3-20, begin */
    ID_TAF_MMA_AC_INFO_QRY_REQ,                                                 /* _H2ASN_MsgChoice TAF_MMA_AC_INFO_QRY_REQ_STRU */
    ID_TAF_MMA_AC_INFO_QRY_CNF,                                                 /* _H2ASN_MsgChoice TAF_MMA_AC_INFO_QRY_CNF_STRU */
    ID_TAF_MMA_AC_INFO_CHANGE_IND,                                              /* _H2ASN_MsgChoice TAF_MMA_AC_INFO_CHANGE_IND_STRU */

    ID_TAF_MMA_COPN_INFO_QRY_REQ,                                               /* _H2ASN_MsgChoice TAF_MMA_COPN_INFO_QRY_REQ_STRU */
    ID_TAF_MMA_COPN_INFO_QRY_CNF,                                               /* _H2ASN_MsgChoice TAF_MMA_COPN_INFO_QRY_CNF_STRU */

    ID_TAF_MMA_SIM_INSERT_REQ,                                                  /* _H2ASN_MsgChoice TAF_MMA_SIM_INSERT_REQ_STRU */
    ID_TAF_MMA_SIM_INSERT_CNF,                                                  /* _H2ASN_MsgChoice TAF_MMA_SIM_INSERT_CNF_STRU */

    ID_TAF_MMA_EOPLMN_SET_REQ,                                                  /* _H2ASN_MsgChoice TAF_MMA_EOPLMN_SET_REQ_STRU */
    ID_TAF_MMA_EOPLMN_SET_CNF,                                                  /* _H2ASN_MsgChoice TAF_MMA_EOPLMN_SET_CNF_STRU */
    ID_TAF_MMA_EOPLMN_QRY_REQ,                                                  /* _H2ASN_MsgChoice TAF_MMA_EOPLMN_QRY_REQ_STRU */
    ID_TAF_MMA_EOPLMN_QRY_CNF,                                                  /* _H2ASN_MsgChoice TAF_MMA_EOPLMN_QRY_CNF_STRU */

    ID_TAF_MMA_NET_SCAN_REQ,                                                    /* _H2ASN_MsgChoice TAF_MMA_NET_SCAN_REQ_STRU */
    ID_TAF_MMA_NET_SCAN_CNF,                                                    /* _H2ASN_MsgChoice TAF_MMA_NET_SCAN_CNF_STRU */
    ID_TAF_MMA_NET_SCAN_ABORT_REQ,                                              /* _H2ASN_MsgChoice TAF_MMA_NET_SCAN_ABORT_REQ_STRU */
    /* Added by k902809 for Iteration 11, Iteration 11 2015-3-20, end */

    ID_TAF_MMA_ACCESS_MODE_QRY_REQ,                                             /* _H2ASN_MsgChoice TAF_MMA_ACCESS_MODE_QRY_REQ_STRU */
    ID_TAF_MMA_ACCESS_MODE_QRY_CNF,                                             /* _H2ASN_MsgChoice TAF_MMA_ACCESS_MODE_QRY_CNF_STRU */

    ID_TAF_MMA_COPS_QRY_REQ,                                                    /* _H2ASN_MsgChoice TAF_MMA_COPS_QRY_REQ_STRU */
    ID_TAF_MMA_COPS_QRY_CNF,                                                    /* _H2ASN_MsgChoice TAF_MMA_COPS_QRY_CNF_STRU */

    ID_TAF_MMA_REG_STATE_QRY_REQ,                                               /* _H2ASN_MsgChoice TAF_MMA_REG_STATE_QRY_REQ_STRU */
    ID_TAF_MMA_REG_STATE_QRY_CNF,                                               /* _H2ASN_MsgChoice TAF_MMA_REG_STATE_QRY_CNF_STRU */

    ID_TAF_MMA_SYSINFO_QRY_REQ,                                                 /* _H2ASN_MsgChoice TAF_MMA_SYSINFO_QRY_REQ_STRU */
    ID_TAF_MMA_SYSINFO_QRY_CNF,                                                 /* _H2ASN_MsgChoice TAF_MMA_SYSINFO_QRY_CNF_STRU */

    ID_TAF_MMA_CSNR_QRY_REQ,                                                    /* _H2ASN_MsgChoice TAF_MMA_CSNR_QRY_REQ_STRU */
    ID_TAF_MMA_CSNR_QRY_CNF,                                                    /* _H2ASN_MsgChoice TAF_MMA_CSNR_QRY_CNF_STRU */

    ID_TAF_MMA_CSQ_QRY_REQ,                                                     /* _H2ASN_MsgChoice TAF_MMA_CSQ_QRY_REQ_STRU */
    ID_TAF_MMA_CSQ_QRY_CNF,                                                     /* _H2ASN_MsgChoice TAF_MMA_CSQ_QRY_CNF_STRU */

    ID_TAF_MMA_CSQLVL_QRY_REQ,                                                  /* _H2ASN_MsgChoice TAF_MMA_CSQLVL_QRY_REQ_STRU */
    ID_TAF_MMA_CSQLVL_QRY_CNF,                                                  /* _H2ASN_MsgChoice TAF_MMA_CSQLVL_QRY_CNF_STRU */

    ID_TAF_MMA_ANTENNA_INFO_QRY_REQ,                                            /* _H2ASN_MsgChoice TAF_MMA_ANTENNA_INFO_QRY_REQ_STRU */
    ID_TAF_MMA_ANTENNA_INFO_QRY_CNF,                                            /* _H2ASN_MsgChoice TAF_MMA_ANTENNA_INFO_QRY_CNF_STRU */

    ID_TAF_MMA_HOME_PLMN_QRY_REQ,                                               /* _H2ASN_MsgChoice TAF_MMA_HOME_PLMN_QRY_REQ_STRU */
    ID_TAF_MMA_HOME_PLMN_QRY_CNF,                                               /* _H2ASN_MsgChoice TAF_MMA_HOME_PLMN_QRY_CNF_STRU */

    ID_TAF_MMA_SPN_QRY_REQ,                                                     /* _H2ASN_MsgChoice TAF_MMA_SPN_QRY_REQ_STRU */
    ID_TAF_MMA_SPN_QRY_CNF,                                                     /* _H2ASN_MsgChoice TAF_MMA_SPN_QRY_CNF_STRU */

    ID_TAF_MMA_MMPLMNINFO_QRY_REQ,                                              /* _H2ASN_MsgChoice TAF_MMA_MMPLMNINFO_QRY_REQ_STRU */
    ID_TAF_MMA_MMPLMNINFO_QRY_CNF,                                              /* _H2ASN_MsgChoice TAF_MMA_MMPLMNINFO_QRY_CNF_STRU */

    ID_TAF_MMA_LAST_CAMP_PLMN_QRY_REQ,                                          /* _H2ASN_MsgChoice TAF_MMA_LAST_CAMP_PLMN_QRY_REQ_STRU */
    ID_TAF_MMA_LAST_CAMP_PLMN_QRY_CNF,                                          /* _H2ASN_MsgChoice TAF_MMA_LAST_CAMP_PLMN_QRY_CNF_STRU */

    ID_TAF_MMA_USER_SRV_STATE_QRY_REQ,                                          /* _H2ASN_MsgChoice TAF_MMA_USER_SRV_STATE_QRY_REQ_STRU */
    ID_TAF_MMA_USER_SRV_STATE_QRY_CNF,                                          /* _H2ASN_MsgChoice TAF_MMA_USER_SRV_STATE_QRY_CNF_STRU */

    ID_TAF_MMA_POWER_ON_AND_REG_TIME_QRY_REQ,                                   /* _H2ASN_MsgChoice TAF_MMA_POWER_ON_AND_REG_TIME_QRY_REQ_STRU */
    ID_TAF_MMA_POWER_ON_AND_REG_TIME_QRY_CNF,                                   /* _H2ASN_MsgChoice TAF_MMA_POWER_ON_AND_REG_TIME_QRY_CNF_STRU */

    ID_TAF_MMA_BATTERY_CAPACITY_QRY_REQ,                                        /* _H2ASN_MsgChoice TAF_MMA_BATTERY_CAPACITY_QRY_REQ_STRU */
    ID_TAF_MMA_BATTERY_CAPACITY_QRY_CNF,                                        /* _H2ASN_MsgChoice TAF_MMA_BATTERY_CAPACITY_QRY_CNF_STRU */

    ID_TAF_MMA_HAND_SHAKE_QRY_REQ,                                              /* _H2ASN_MsgChoice TAF_MMA_HAND_SHAKE_QRY_REQ_STRU */
    ID_TAF_MMA_HAND_SHAKE_QRY_CNF,                                              /* _H2ASN_MsgChoice TAF_MMA_HAND_SHAKE_QRY_CNF_STRU */

    ID_TAF_MMA_TIME_CHANGE_IND,                                                 /* _H2ASN_MsgChoice TAF_MMA_TIME_CHANGE_IND_STRU */
    ID_TAF_MMA_MODE_CHANGE_IND,                                                 /* _H2ASN_MsgChoice TAF_MMA_MODE_CHANGE_IND_STRU */
    ID_TAF_MMA_PLMN_CHANGE_IND,                                                 /* _H2ASN_MsgChoice TAF_MMA_PLMN_CHANGE_IND_STRU */

    ID_TAF_MMA_SRV_STATUS_IND,                                                  /* _H2ASN_MsgChoice TAF_MMA_SRV_STATUS_IND_STRU */
    ID_TAF_MMA_REG_STATUS_IND,                                                  /* _H2ASN_MsgChoice TAF_MMA_REG_STATUS_IND_STRU */
    ID_TAF_MMA_REG_REJ_INFO_IND,                                                /* _H2ASN_MsgChoice TAF_MMA_REG_REJ_INFO_IND_STRU */
    ID_TAF_MMA_PLMN_SELECTION_INFO_IND,                                         /* _H2ASN_MsgChoice TAF_MMA_PLMN_SElECTION_INFO_IND_STRU */

    ID_TAF_MMA_PLMN_LIST_REQ,
    ID_TAF_MMA_PLMN_LIST_CNF,
    ID_TAF_MSG_MMA_EONS_UCS2_REQ,
    ID_TAF_MSG_MMA_EONS_UCS2_CNF,

    ID_TAF_MMA_IMS_SWITCH_SET_REQ, /* _H2ASN_MsgChoice TAF_MMA_IMS_SWITCH_SET_REQ_STRU */
    ID_TAF_MMA_IMS_SWITCH_SET_CNF, /* _H2ASN_MsgChoice TAF_MMA_IMS_SWITCH_SET_CNF_STRU */
    ID_TAF_MMA_IMS_SWITCH_QRY_REQ, /* _H2ASN_MsgChoice TAF_MMA_IMS_SWITCH_QRY_REQ_STRU */
    ID_TAF_MMA_IMS_SWITCH_QRY_CNF, /* _H2ASN_MsgChoice TAF_MMA_IMS_SWITCH_QRY_CNF_STRU */
    ID_TAF_MMA_VOICE_DOMAIN_SET_REQ, /* _H2ASN_MsgChoice TAF_MMA_VOICE_DOMAIN_SET_REQ_STRU */
    ID_TAF_MMA_VOICE_DOMAIN_SET_CNF, /* _H2ASN_MsgChoice TAF_MMA_VOICE_DOMAIN_SET_CNF_STRU */
    ID_TAF_MMA_VOICE_DOMAIN_QRY_REQ, /* _H2ASN_MsgChoice TAF_MMA_VOICE_DOMAIN_QRY_REQ_STRU */
    ID_TAF_MMA_VOICE_DOMAIN_QRY_CNF, /* _H2ASN_MsgChoice TAF_MMA_VOICE_DOMAIN_QRY_CNF_STRU */

    ID_TAF_MMA_ATTACH_REQ               ,                                       /* _H2ASN_MsgChoice TAF_MMA_ATTACH_REQ_STRU */
    ID_TAF_MMA_ATTACH_CNF               ,                                       /* _H2ASN_MsgChoice TAF_MMA_ATTACH_CNF_STRU */
    ID_TAF_MMA_ATTACH_STATUS_QRY_REQ,                                           /* _H2ASN_MsgChoice TAF_MMA_ATTACH_STATUS_QRY_REQ_STRU */
    ID_TAF_MMA_ATTACH_STATUS_QRY_CNF,                                           /* _H2ASN_MsgChoice TAF_MMA_ATTACH_STATUS_QRY_CNF_STRU */

    ID_TAF_MMA_PS_RAT_TYPE_NTF,  /* _H2ASN_MsgChoice TAF_MMA_PS_RAT_TYPE_NTF_STRU */

    ID_TAF_MMA_1XCHAN_SET_REQ,
    ID_TAF_MMA_1XCHAN_SET_CNF,
    ID_TAF_MMA_1XCHAN_QUERY_REQ,
    ID_TAF_MMA_1XCHAN_QUERY_CNF,
    ID_TAF_MMA_CVER_QUERY_REQ,
    ID_TAF_MMA_CVER_QUERY_CNF,
    ID_TAF_MMA_GETSTA_QUERY_REQ,
    ID_TAF_MMA_GETSTA_QUERY_CNF,
    ID_TAF_MMA_CHIGHVER_QUERY_REQ,
    ID_TAF_MMA_CHIGHVER_QUERY_CNF,

    ID_TAF_MMA_QUIT_CALLBACK_SET_REQ,                                               /* _H2ASN_MsgChoice TAF_MMA_QUIT_CALLBACK_SET_REQ_STRU */
    ID_TAF_MMA_QUIT_CALLBACK_SET_CNF,                                               /* _H2ASN_MsgChoice TAF_MMA_QUIT_CALLBACK_SET_CNF_STRU */
    ID_TAF_MMA_CSIDLIST_SET_REQ,                                                    /* _H2ASN_MsgChoice TAF_MMA_CSIDLIST_SET_REQ_STRU */
    ID_TAF_MMA_CSIDLIST_SET_CNF,                                                    /* _H2ASN_MsgChoice TAF_MMA_CSIDLIST_SET_CNF_STRU */
    ID_TAF_MMA_1X_EMC_CALL_BACK_QRY_REQ,                                            /* _H2ASN_MsgChoice TAF_MMA_1X_EMC_CALL_BACK_QRY_REQ_STRU */
    ID_TAF_MMA_1X_EMC_CALL_BACK_QRY_CNF,                                            /* _H2ASN_MsgChoice TAF_MMA_1X_EMC_CALL_BACK_QRY_CNF_STRU */
    ID_TAF_MMA_1X_EMC_CALL_BACK_NTF,                                                /* _H2ASN_MsgChoice TAF_MMA_1X_EMC_CALL_BACK_NTF_STRU */

    ID_TAF_MMA_SRCHED_PLMN_INFO_IND,                                                /* _H2ASN_MsgChoice TAF_MMA_SRCHED_PLMN_INFO_IND_STRU */

    ID_TAF_MMA_HDR_CSQ_SET_REQ,                                                     /* _H2ASN_MsgChoice TAF_MMA_HDR_CSQ_SET_REQ_STRU              */
    ID_MMA_TAF_HDR_CSQ_SET_CNF,                                                     /* _H2ASN_MsgChoice MMA_TAF_HDR_CSQ_SET_CNF_STRU              */
    ID_TAF_MMA_HDR_CSQ_QRY_SETTING_REQ,                                             /* _H2ASN_MsgChoice TAF_MMA_HDR_CSQ_QRY_SETTING_REQ_STRU      */
    ID_MMA_TAF_HDR_CSQ_QRY_SETTING_CNF,                                             /* _H2ASN_MsgChoice MMA_TAF_HDR_CSQ_QRY_SETTING_CNF_STRU      */
    ID_MMA_TAF_HDR_CSQ_VALUE_IND,                                                   /* _H2ASN_MsgChoice MMA_TAF_HDR_CSQ_VALUE_IND_STRU            */
    ID_TAF_MMA_DPLMN_QRY_REQ,                                                       /* _H2ASN_MsgChoice TAF_MMA_DPLMN_QRY_REQ_STRU */
    ID_TAF_MMA_DPLMN_QRY_CNF,                                                       /* _H2ASN_MsgChoice TAF_MMA_DPLMN_QRY_CNF_STRU */
    ID_TAF_MMA_DPLMN_SET_REQ,                                                       /* _H2ASN_MsgChoice TAF_MMA_DPLMN_SET_REQ_STRU */
    ID_TAF_MMA_DPLMN_SET_CNF,                                                       /* _H2ASN_MsgChoice TAF_MMA_DPLMN_SET_CNF_STRU */


    ID_TAF_MMA_CLMODE_IND,                                                          /* _H2ASN_MsgChoice TAF_MMA_CLMODE_IND_STRU*/
    ID_TAF_MMA_CURR_SID_NID_QRY_REQ,                                                /* _H2ASN_MsgChoice TAF_MMA_CURR_SID_NID_QRY_REQ_STRU*/
    ID_TAF_MMA_CURR_SID_NID_QRY_CNF,                                                /* _H2ASN_MsgChoice TAF_MMA_CURR_SID_NID_QRY_CNF_STRU*/

    ID_TAF_MMA_CSG_LIST_SEARCH_REQ,       /* _H2ASN_MsgChoice TAF_MMA_CSG_LIST_SEARCH_REQ_STRU */
    ID_TAF_MMA_CSG_LIST_SEARCH_CNF,       /* _H2ASN_MsgChoice TAF_MMA_CSG_LIST_SEARCH_CNF_STRU */
    ID_TAF_MMA_CSG_LIST_ABORT_REQ,        /* _H2ASN_MsgChoice TAF_MMA_CSG_LIST_ABORT_REQ_STRU */
    ID_TAF_MMA_CSG_LIST_ABORT_CNF,        /* _H2ASN_MsgChoice TAF_MMA_CSG_LIST_ABORT_CNF_STRU */

    ID_TAF_MMA_CLOCINFO_IND,                                                        /* _H2ASN_MsgChoice TAF_MMA_CLOCINFO_IND_STRU */

    ID_TAF_MMA_INIT_LOC_INFO_IND,                                                   /* _H2ASN_MsgChoice TAF_MMA_INIT_LOC_INFO_IND_STRU*/

    ID_TAF_MMA_ROAMING_MODE_SWITCH_IND,                                             /* _H2ASN_MsgChoice TAF_MMA_ROAMING_MODE_SWITCH_IND_STRU */

    ID_TAF_MMA_CTCC_ROAMING_NW_INFO_REPORT_IND,                                     /* _H2ASN_MsgChoice TAF_MMA_CTCC_ROAMING_NW_INFO_REPORT_IND_STRU */

    ID_TAF_MMA_CTCC_ROAMING_NW_INFO_QRY_REQ,                                        /* _H2ASN_MsgChoice TAF_MMA_CTCC_ROAMING_NW_INFO_QRY_REQ_STRU */

    ID_TAF_MMA_CTCC_ROAMING_NW_INFO_QRY_CNF,                                        /* _H2ASN_MsgChoice TAF_MMA_CTCC_ROAMING_NW_INFO_QRY_CNF_STRU */

    ID_TAF_MMA_CTCC_OOS_COUNT_SET_REQ,                                              /* _H2ASN_MsgChoice TAF_MMA_CTCC_OOS_COUNT_SET_REQ_STRU */
    ID_TAF_MMA_CTCC_OOS_COUNT_SET_CNF,                                              /* _H2ASN_MsgChoice TAF_MMA_CTCC_OOS_COUNT_SET_CNF_STRU */
    ID_TAF_MMA_CSG_SPEC_SEARCH_REQ,       /* _H2ASN_MsgChoice TAF_MMA_CSG_SPEC_SEARCH_REQ_STRU */
    ID_TAF_MMA_CSG_SPEC_SEARCH_CNF,       /* _H2ASN_MsgChoice TAF_MMA_CSG_SPEC_SEARCH_CNF_STRU */
    ID_TAF_MMA_QRY_CAMP_CSG_ID_INFO_REQ,  /* _H2ASN_MsgChoice TAF_MMA_QRY_CAMP_CSG_ID_INFO_REQ_STRU */
    ID_TAF_MMA_QRY_CAMP_CSG_ID_INFO_CNF,  /* _H2ASN_MsgChoice TAF_MMA_QRY_CAMP_CSG_ID_INFO_CNF_STRU */

    ID_TAF_MMA_IMS_DOMAIN_CFG_SET_REQ,
    ID_TAF_MMA_IMS_DOMAIN_CFG_QRY_REQ,
    ID_TAF_MMA_IMS_DOMAIN_CFG_SET_CNF,
    ID_TAF_MMA_IMS_DOMAIN_CFG_QRY_CNF,

    ID_TAF_MMA_ROAM_IMS_SUPPORT_SET_REQ,                                           /* _H2ASN_MsgChoice TAF_MMA_ROAM_IMS_SUPPORT_SET_REQ_STRU*/
    ID_TAF_MMA_ROAM_IMS_SUPPORT_SET_CNF,                                           /* _H2ASN_MsgChoice TAF_MMA_ROAM_IMS_SUPPORT_SET_CNF_STRU*/

    ID_TAF_MMA_CTCC_ROAMING_NW_INFO_RTP_CFG_SET_REQ,        /* _H2ASN_MsgChoice TAF_MMA_CTCC_ROAMING_NW_INFO_RTP_CFG_SET_REQ_STRU */
    ID_TAF_MMA_CTCC_ROAMING_NW_INFO_RTP_CFG_SET_CNF,        /* _H2ASN_MsgChoice TAF_MMA_CTCC_ROAMING_NW_INFO_RTP_CFG_SET_CNF_STRU */

    ID_TAF_MMA_PRLID_QRY_REQ,                                              /* _H2ASN_MsgChoice TAF_MMA_PRLID_QRY_REQ_STRU */
    ID_TAF_MMA_PRLID_QRY_CNF,                                              /* _H2ASN_MsgChoice TAF_MMA_PRLID_QRY_CNF_STRU */
    ID_TAF_MMA_MSG_TYPE_BUTT
};
typedef VOS_UINT32 TAF_MMA_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 ??????    : TAF_PH_RAT_TYPE_ENUM_U8
 ????????  : AT^syscfgex ??acqorder??????
 1.??    ?? : 2011??06??9??
   ??    ?? : l00130025
   ???????? : ????????
  2.??    ??   : 2015??4??10??
    ??    ??   : h00313353
    ????????   : SysCfg????
*****************************************************************************/
enum TAF_MMA_RAT_TYPE_ENUM
{
    TAF_MMA_RAT_GSM,                                                             /* GSM???????? */
    TAF_MMA_RAT_WCDMA,                                                           /* WCDMA???????? */
    TAF_MMA_RAT_LTE,                                                             /* LTE???????? */
    TAF_MMA_RAT_1X,                                                             /* 1X???????? */
    TAF_MMA_RAT_HRPD,                                                           /* HRPD???????? */
    TAF_MMA_RAT_BUTT

};
typedef VOS_UINT8 TAF_MMA_RAT_TYPE_ENUM_UINT8;

/*****************************************************************************
 ??????    : TAF_MMA_APP_CFPLMN_OPER_RESULT_ENUM
 ????????  : APP????????????????
 1.??    ??   : 2015??02??13??
   ??    ??   : f00279542
   ????????   : ????????
*****************************************************************************/
enum TAF_MMA_APP_CFPLMN_OPER_RESULT_ENUM
{
    TAF_MMA_APP_CFPLMN_OPER_RESULT_SUCCESS               = 0,/* ???????? */
    TAF_MMA_APP_CFPLMN_OPER_RESULT_FAILURE               = 1,/* ???????? */
    TAF_MMA_APP_CFPLMN_OPER_RESULT_NO_USIM               = 2,/* USIM???????? */
    TAF_MMA_APP_CFPLMN_OPER_RESULT_NULL_PTR              = 3,/* ?????? */
    TAF_MMA_APP_CFPLMN_OPER_RESULT_TIME_OUT              = 4,/* ???? */
    TAF_MMA_APP_CFPLMN_OPER_RESULT_BUTT
};
typedef VOS_UINT32 TAF_MMA_APP_CFPLMN_OPER_RESULT_ENUM_UINT32;
/*****************************************************************************
  7 STRUCT????
*****************************************************************************/
/* Modified by l60609 for DSDA Phase III, 2013-3-4, Begin */
/* Added by L60609 for AT Project??2011-10-05,  Begin*/
/* AT????MN_CALLBACK_CMD_CNF?????????????????????? */
typedef struct
{
    MN_CLIENT_ID_T              clientId;
    MN_OPERATION_ID_T           opId;
    TAF_UINT8                   ucRsv;
    TAF_UINT32                  ulErrorCode;
}AT_CMD_CNF_EVENT;
/* Added by L60609 for AT Project??2011-10-05,  End*/
/* Modified by l60609 for DSDA Phase III, 2013-3-4, End */



/*****************************************************************************
 ??????    : AT_MMA_USIM_STATUS_IND_STRU
 ????????  : AT??MMA AT_MMA_USIM_STATUS_IND????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                      ulMsgName;                                  /*_H2ASN_Skip*/
    USIMM_CARD_TYPE_ENUM_UINT32     enCardType;                     /* ??????:SIM??USIM??ROM-SIM  */
    USIMM_CARD_SERVIC_ENUM_UINT32   enCardStatus;                   /* ??????*/
    USIMM_PHYCARD_TYPE_ENUM_UINT32  enPhyCardType;                  /* ???????? */
    VOS_UINT8                       aucIMSI[NAS_MAX_IMSI_LENGTH];   /* IMSI??*/
    VOS_UINT8                       ucIMSILen;                      /* IMSI???? */
    VOS_UINT8                       ucRsv[2];
}AT_MMA_USIM_STATUS_IND_STRU;

/* Added by f62575 for B050 Project, 2012-2-3, Begin   */
/*****************************************************************************
 ??????    : AT_MMA_SIMLOCK_STATUS_STRU
 ????????  : AT??MMA AT_MMA_SIMLOCK_STATUS_STRU????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                      ulMsgName;                                  /*_H2ASN_Skip*/
    AT_APPCTRL_STRU                 stAtAppCtrl;
    VOS_BOOL                        bSimlockEnableFlg;
}AT_MMA_SIMLOCK_STATUS_STRU;
/* Added by f62575 for B050 Project, 2012-2-3, end   */

/* Added by w00176964 for V7R1C50_DCM????????????????????, 2012-12-10, begin */
/******************************************************************************
??????    : TAF_MMA_CELL_RESTRICTION_TYPE_ENUM
????????  : ????????????????????????
1. ??    ??: 2012??12??08??
   ??    ??: w00176964
   ????????: ????
******************************************************************************/
enum  TAF_MMA_CELL_RESTRICTION_TYPE_ENUM
{
    TAF_MMA_CELL_RESTRICTION_TYPE_NONE                   = 0,                           /* ?????????????????????? */
    TAF_MMA_CELL_RESTRICTION_TYPE_NORMAL_SERVICE         = 1,                           /* ???????????????????? */
    TAF_MMA_CELL_RESTRICTION_TYPE_EMERGENCY_SERVICE      = 2,                           /* ???????????????????? */
    TAF_MMA_CELL_RESTRICTION_TYPE_ALL_SERVICE            = 3,                           /* ?????????????????????????????? */
    TAF_MMA_CELL_RESTRICTION_TYPE_BUTT
};
typedef VOS_UINT8   TAF_MMA_CELL_RESTRICTION_TYPE_ENUM_UINT8;

/* Deleted by k902809 for Iteration 11, 2015-3-26, begin */

/* Deleted by k902809 for Iteration 11, Iteration 11 2015-3-26, end */
/* Deleted by k902809 for Iteration 11, 2015-3-26, begin */

/* Deleted by k902809 for Iteration 11, Iteration 11 2015-3-26, end */
/* Added by w00176964 for V7R1C50_DCM????????????????????, 2012-12-10, end */

/*****************************************************************************
 ??????    : MN_PH_CSQLVLEXT_BER_VALUE_ENUM
 ????????  :
 ASN.1???? :
 ????????  : CSQLVLEXT????BER??????????????????????????????BER??????????????????99
*****************************************************************************/
enum MN_PH_CSQLVLEXT_BER_VALUE_ENUM
{
    MN_PH_CSQLVLEXT_BER_VALUE_99        = 99,
    MN_PH_CSQLVLEXT_BER_VALUE_BUTT
};
typedef VOS_UINT8 MN_PH_CSQLVLEXT_BER_VALUE_ENUM_UINT8;


/*****************************************************************************
 ??????    : MN_PH_CSQLVLEXT_RSSILV_ENUM
 ????????  :
 ASN.1???? :
 ????????  : CSQLVLEXT????RSSILV??????????????????????
*****************************************************************************/
enum MN_PH_CSQLVLEXT_RSSILV_ENUM
{
    MN_PH_CSQLVLEXT_RSSILV_0,
    MN_PH_CSQLVLEXT_RSSILV_1,
    MN_PH_CSQLVLEXT_RSSILV_2,
    MN_PH_CSQLVLEXT_RSSILV_3,
    MN_PH_CSQLVLEXT_RSSILV_4,
    MN_PH_CSQLVLEXT_RSSILV_5,
    MN_PH_CSQLVLEXT_RSSILV_BUTT
};
typedef VOS_UINT8 MN_PH_CSQLVLEXT_RSSILV_ENUM_UINT8;

/*****************************************************************************
 ??????    : MN_PH_CSQLVLEXT_RSSILV_VALUE_ENUM
 ????????  :
 ASN.1???? :
 ????????  : CSQLVLEXT????RSSILV??????????????????????
*****************************************************************************/
enum MN_PH_CSQLVLEXT_RSSILV_VALUE_ENUM
{
    MN_PH_CSQLVLEXT_RSSILV_VALUE_0      = 0,
    MN_PH_CSQLVLEXT_RSSILV_VALUE_20     = 20,
    MN_PH_CSQLVLEXT_RSSILV_VALUE_40     = 40,
    MN_PH_CSQLVLEXT_RSSILV_VALUE_60     = 60,
    MN_PH_CSQLVLEXT_RSSILV_VALUE_80     = 80,
    MN_PH_CSQLVLEXT_RSSILV_VALUE_99     = 99,
    MN_PH_CSQLVLEXT_RSSILV_VALUE_BUTT
};
typedef VOS_UINT8 MN_PH_CSQLVLEXT_RSSILV_VALUE_ENUM_UINT8;

/*****************************************************************************
 ??????    : TAF_SYS_SUBMODE_ENUM
 ????????  :
 ASN.1???? :
 ????????  : ????????????????????????

  1.??    ??   : 2012??6??1??
    ??    ??   : z40661
    ????????   : DTS2012053006110,????DC-HSPA+
  2.??    ??   : 2015??2??11??
    ??    ??   : w00208541
    ????????   : CDMA Iteration 8 ????EVDO ????????
*****************************************************************************/
enum TAF_SYS_SUBMODE_ENUM
{
    TAF_SYS_SUBMODE_NONE                = 0,                /* ?????? */
    TAF_SYS_SUBMODE_GSM                 = 1,                /* GSM???? */
    TAF_SYS_SUBMODE_GPRS                = 2,                /* GPRS???? */
    TAF_SYS_SUBMODE_EDGE                = 3,                /* EDGE???? */
    TAF_SYS_SUBMODE_WCDMA               = 4,                /* WCDMA???? */
    TAF_SYS_SUBMODE_HSDPA               = 5,                /* HSDPA???? */
    TAF_SYS_SUBMODE_HSUPA               = 6,                /* HSUPA???? */
    TAF_SYS_SUBMODE_HSDPA_HSUPA         = 7,                /* HSDPA+HSUPA???? */
    TAF_SYS_SUBMODE_TD_SCDMA            = 8,                /* TD_SCDMA???? */
    TAF_SYS_SUBMODE_HSPA_PLUS           = 9,                /* HSPA+???? */
    TAF_SYS_SUBMODE_LTE                 = 10,               /* LTE???? */
    TAF_SYS_SUBMODE_DC_HSPA_PLUS        = 17,               /* DC-HSPA+???? */
    TAF_SYS_SUBMODE_DC_MIMO             = 18,               /* MIMO-HSPA+???? */

    TAF_SYS_SUBMODE_CDMA_1X             = 23,               /* CDMA 1X???? */
    TAF_SYS_SUBMODE_EVDO_REL_0          = 24,                               /* EVDO Rel0*/
    TAF_SYS_SUBMODE_EVDO_REL_A          = 25,               /* EVDO RelA*/

    TAF_SYS_SUBMODE_HYBRID_EVDO_REL_0   = 28,                               /* Hybrid(EVDO Rel0)*/

    TAF_SYS_SUBMODE_HYBRID_EVDO_REL_A   = 29,               /* Hybrid(EVDO RelA)*/

    TAF_SYS_SUBMODE_EHRPD               = 31,               /* EHRPD*/

    TAF_SYS_SUBMODE_BUTT
};
typedef VOS_UINT8  TAF_SYS_SUBMODE_ENUM_UINT8;

/*ucSysModeEx??????????*/
enum MN_PH_SYS_MODE_EX_ENUM
{
    MN_PH_SYS_MODE_EX_NONE_RAT  ,                                               /*??????*/
    MN_PH_SYS_MODE_EX_GSM_RAT   ,                                               /*GSM????*/
    MN_PH_SYS_MODE_EX_CDMA_RAT  ,                                               /*CDMA????*/
    MN_PH_SYS_MODE_EX_WCDMA_RAT ,                                               /*WCDMA????*/
    MN_PH_SYS_MODE_EX_TDCDMA_RAT,                                               /*TD-SCDMA????*/
    MN_PH_SYS_MODE_EX_WIMAX_RAT ,                                               /*Wimax????*/
    MN_PH_SYS_MODE_EX_LTE_RAT   ,                                               /*LTE????*/

    MN_PH_SYS_MODE_EX_EVDO_RAT  ,                                               /*EVDO????*/
    MN_PH_SYS_MODE_EX_HYBRID_RAT,                                               /*CDMA 1X+EVDO????*/
    MN_PH_SYS_MODE_EX_SVLTE_RAT ,                                               /*CDMA 1X+LTE????*/

    MN_PH_SYS_MODE_EX_BUTT_RAT
};
typedef VOS_UINT8  MN_PH_SYS_MODE_EX_ENUM_U8;

/*ucSubSysModeEx??????????*/
enum MN_PH_SUB_SYS_MODE_EX_ENUM
{
    MN_PH_SUB_SYS_MODE_EX_NONE_RAT              ,                               /*??????*/
    MN_PH_SUB_SYS_MODE_EX_GSM_RAT               ,                               /*GSM????*/
    MN_PH_SUB_SYS_MODE_EX_GPRS_RAT              ,                               /*GPRS????*/
    MN_PH_SUB_SYS_MODE_EX_EDGE_RAT              ,                               /*EDGE????*/

    MN_PH_SUB_SYS_MODE_EX_IS95A_RAT     = 21    ,                               /*IS95A????*/
    MN_PH_SUB_SYS_MODE_EX_IS95B_RAT             ,                               /*IS95B????*/
    MN_PH_SUB_SYS_MODE_EX_CDMA20001X_RAT        ,                               /*CDMA20001X????*/
    MN_PH_SUB_SYS_MODE_EX_EVDOREL0_RAT          ,                               /*EVDORel0????*/
    MN_PH_SUB_SYS_MODE_EX_EVDORELA_RAT          ,                               /*EVDORelA????*/
    MN_PH_SUB_SYS_MODE_EX_EVDORELB_RAT          ,                               /*EVDORelB????*/
    MN_PH_SUB_SYS_MODE_EX_HYBIRD_CDMA20001X_RAT ,                               /*HYBIRD CDMA20001X????*/
    MN_PH_SUB_SYS_MODE_EX_HYBIRD_EVDOREL0_RAT   ,                               /*HYBIRD EVDORel0????*/
    MN_PH_SUB_SYS_MODE_EX_HYBIRD_EVDORELA_RAT   ,                               /*HYBIRD EVDORelA????*/
    MN_PH_SUB_SYS_MODE_EX_HYBIRD_EVDORELB_RAT   ,                               /*HYBIRD EVDORelA????*/

    MN_PH_SUB_SYS_MODE_EX_EHRPD_RAT    = 31     ,                               /*EHRPD????*/

    MN_PH_SUB_SYS_MODE_EX_WCDMA_RAT     = 41    ,                               /*WCDMA????*/
    MN_PH_SUB_SYS_MODE_EX_HSDPA_RAT     = 42    ,                               /*HSDPA????*/
    MN_PH_SUB_SYS_MODE_EX_HSUPA_RAT     = 43    ,                               /*HSUPA????*/
    MN_PH_SUB_SYS_MODE_EX_HSPA_RAT      = 44    ,                               /*HSPA????*/
    MN_PH_SUB_SYS_MODE_EX_HSPA_PLUS_RAT = 45    ,                               /*HSPA+????*/
    MN_PH_SUB_SYS_MODE_EX_DCHSPA_PLUS_RAT = 46  ,                               /*DCHSPA+????*/

    MN_PH_SUB_SYS_MODE_EX_TDCDMA_RAT    = 61    ,                               /*TD-SCDMA????*/

    MN_PH_SUB_SYS_MODE_EX_TD_HSDPA_RAT                      = 62,               /*HSDPA????*/
    MN_PH_SUB_SYS_MODE_EX_TD_HSUPA_RAT                      = 63,               /*HSUPA????*/
    MN_PH_SUB_SYS_MODE_EX_TD_HSPA_RAT                       = 64,               /*HSPA????*/
    MN_PH_SUB_SYS_MODE_EX_TD_HSPA_PLUS_RAT                  = 65,               /*HSPA+????*/

    MN_PH_SUB_SYS_MODE_EX_LTE_RAT       = 101   ,                               /*LTE????*/
    MN_PH_SUB_SYS_MODE_EX_BUTT_RAT
};
typedef VOS_UINT8  MN_PH_SUB_SYS_MODE_EX_ENUM_U8;

/*****************************************************************************
 ??????    : TAF_PH_ACCESS_TECH_ENUM
 ????????  :
 ASN.1???? :
 ????????  : ????????????????????????????CREG/CGREG??ACT????
 1.??    ??   : 2015??2??11??
   ??    ??   : w00208541
   ????????   : CDMA Iteration 8 ????EVDO ????????
*****************************************************************************/
enum TAF_PH_ACCESS_TECH_ENUM
{
    TAF_PH_ACCESS_TECH_GSM              = 0,                /* GSM */
    TAF_PH_ACCESS_TECH_GSM_COMPACT      = 1,                /* GSM Compact,?????? */
    TAF_PH_ACCESS_TECH_UTRAN            = 2,                /* UTRAN */
    TAF_PH_ACCESS_TECH_EGPRS            = 3,                /* EGPRS */
    TAF_PH_ACCESS_TECH_HSDPA            = 4,                /* HSDPA */
    TAF_PH_ACCESS_TECH_HSUPA            = 5,                /* HSUPA */
    TAF_PH_ACCESS_TECH_HSDPA_HSUPA      = 6,                /* HSDPA+HSUPA */
    TAF_PH_ACCESS_TECH_E_UTRAN          = 7,                /* E-UTRAN*/

    TAF_PH_ACCESS_TECH_CDMA_1X          = 20,               /* CDMA 1X */
    TAF_PH_ACCESS_TECH_EVDO             = 21,               /* EVDO */
    TAF_PH_ACCESS_TECH_BUTT
};
typedef VOS_UINT8  TAF_PH_ACCESS_TECH_ENUM_UINT8;


/*****************************************************************************
 ??????    : TAF_SIM_INSERT_STATE_ENUM
 ????????  :
 ASN.1???? :
 ????????  : ????????SIM????????:??????????
*****************************************************************************/
enum TAF_SIM_INSERT_STATE_ENUM
{
    TAF_SIM_INSERT_STATE_REMOVE              = 0,                /* ???? */
    TAF_SIM_INSERT_STATE_INSERT              = 1,                /* ???? */
    TAF_SIM_INSERT_STATE_BUTT

};
typedef VOS_UINT32  TAF_SIM_INSERT_STATE_ENUM_UINT32;


/*****************************************************************************
 ??????    : TAF_MMA_PLMN_LIST_ABORT_CAUSE_ENUM
 ????????  :
 ASN.1???? :
 ????????  : PLMN LIST??????????????????

   1.??    ??   : 2012??9??19??
     ??    ??   : s00217060
     ????????   : ???? for V7R1C50_At_Abort
*****************************************************************************/
enum TAF_MMA_PLMN_LIST_ABORT_PROC_ENUM
{
    TAF_MMA_PLMN_LIST_ABORT_PROCESSING_TIMEOUT                   = 0,           /* ???????????????????????????? */
    TAF_MMA_PLMN_LIST_ABORT_PROCESSING_USER_ABORT                = 1,           /* ?????????????????????? */
    TAF_MMA_PLMN_LIST_ABORT_BUTT
};
typedef VOS_UINT8  TAF_MMA_PLMN_LIST_ABORT_PROC_ENUM_UINT8;


enum TAF_MMA_PS_INIT_RSLT_ENUM
{
    TAF_MMA_PS_INIT_FAIL                = 0,           /* ???????????????????? */
    TAF_MMA_PS_INIT_SUCC                = 1,           /* ?????????? */
    TAF_MMA_PS_INIT_PHY_FAIL            = 2,           /* ???????????????? */
    TAF_MMA_PS_INIT_PHY_TIMEOUT         = 3,           /* ???????????????? */
    TAF_MMA_PS_INIT_PLATCAP_CFG_FAIL    = 4,           /* ?????????????????? */
    TAF_PS_INIT_BUTT
};
typedef VOS_UINT32  TAF_MMA_PS_INIT_RSLT_ENUM_UINT32;
/* Added by s00246516 for L-C??????????, 2014-01-24, Begin */
/*****************************************************************************
 ??????    : TAF_MMA_ACQ_REASON_ENUM
 ????????  : ????????????????
 1.??    ??   : 2014??01??23??
   ??    ??   : s00246516
   ????????   : ????????
*****************************************************************************/
enum TAF_MMA_ACQ_REASON_ENUM
{
    TAF_MMA_ACQ_REASON_POWER_UP         = 0,    /* ???????????? */
    TAF_MMA_ACQ_REASON_OOS              = 1,    /* ???????????????? */
    TAF_MMA_ACQ_REASON_HIGH_PRIO        = 2,    /* ?????????????????? */
    TAF_MMA_ACQ_REASON_BUTT
};
typedef VOS_UINT8  TAF_MMA_ACQ_REASON_ENUM_UINT8;

/*****************************************************************************
 ??????    : TAF_MMA_EPS_ATTACH_REASON_ENUM
 ????????  : Attach????????
 1.??    ??   : 2014??01??23??
   ??    ??   : s00246516
   ????????   : ????????
*****************************************************************************/
enum TAF_MMA_EPS_ATTACH_REASON_ENUM
{
    TAF_MMA_ATTACH_REASON_INITIAL          = 0,    /* ??C->L?????????????????? */
    TAF_MMA_ATTACH_REASON_HANDOVER         = 1,    /* C->L???????????????? */
    TAF_MMA_ATTACH_REASON_BUTT
};
typedef VOS_UINT8 TAF_MMA_EPS_ATTACH_REASON_ENUM_UINT8;

/*****************************************************************************
 ??????    : TAF_MMA_PLMN_PRIORITY_CLASS_ENUM
 ????????  : ??????????????????
 1.??    ??   : 2014??01??23??
   ??    ??   : s00246516
   ????????   : ????????
*****************************************************************************/
enum TAF_MMA_PLMN_PRIORITY_CLASS_ENUM
{
    TAF_MMA_PLMN_PRIORITY_HOME               = 0,/* home or ehome plmn */
    TAF_MMA_PLMN_PRIORITY_PREF               = 1,/* UPLMN or OPLMN */
    TAF_MMA_PLMN_PRIORITY_ANY                = 2,/* Acceptable PLMN */
    TAF_MMA_PLMN_PRIORITY_BUTT
};
typedef VOS_UINT8 TAF_MMA_PLMN_PRIORITY_CLASS_ENUM_UINT8;

/*****************************************************************************
 ??????    : TAF_MMA_CL_REG_STATUS_ENUM
 ????????  :
 ASN.1???? :
 ????????  : CL??VIA??????????ATTACH????????????????????????
*****************************************************************************/
enum TAF_MMA_CL_REG_STATUS_ENUM
{
    TAF_MMA_CL_REG_STATUS_ATTACH_NOT_SEND            = 0x00,
    TAF_MMA_CL_REG_STATUS_ATTACH_SEND_WAIT_CN_RSP    = 0x01,
    TAF_MMA_CL_REG_STATUS_ATTACH_RCV_CN_REJ          = 0x02,
    TAF_MMA_CL_REG_STATUS_ATTACH_RCV_CN_ACP          = 0x03,
    TAF_MMA_CL_REG_STATUS_ATTACH_T3410_EXP           = 0x04,
    TAF_MMA_CL_REG_STATUS_ATTACH_CMP_SEND            = 0x05,

    TAF_MMA_CL_REG_STATUS_BUTT
};
typedef VOS_UINT8 TAF_MMA_ATTACH_CL_REG_STATUS_ENUM8;

/*****************************************************************************
 ??????    : TAF_MMA_APP_OPER_RESULT_ENUM
 ????????  : APP????????????????
 1.??    ??   : 2014??01??23??
   ??    ??   : s00246516
   ????????   : ????????
*****************************************************************************/
enum TAF_MMA_APP_OPER_RESULT_ENUM
{
    TAF_MMA_APP_OPER_RESULT_SUCCESS               = 0,/* ???????? */
    TAF_MMA_APP_OPER_RESULT_FAILURE               = 1,/* ???????? */
    TAF_MMA_APP_OPER_RESULT_ACQUIRED_FAIL         = 2,/* ACQ???? */
    TAF_MMA_APP_OPER_RESULT_REJECT                = 3,/* ???????????????? */
    TAF_MMA_APP_OPER_RESULT_BUTT
};
typedef VOS_UINT32 TAF_MMA_APP_OPER_RESULT_ENUM_UINT32;

/*****************************************************************************
 ??????    : TAF_MMA_DETACH_CAUSE_ENUM
 ????????  : Detach????????
 1.??    ??   : 2014??01??23??
   ??    ??   : s00246516
   ????????   : ????????
 2.??    ??   : 2015??4??13??
   ??    ??   : y00245242
   ????????   : iteration 13????
*****************************************************************************/
enum TAF_MMA_DETACH_CAUSE_ENUM
{
    TAF_MMA_DETACH_CAUSE_USER_DETACH            = 0,/* ??????????detach???? */
    TAF_MMA_DETACH_CAUSE_RAT_OR_BAND_DETACH     = 1,/* system configure??RAT??band??????detach */
    TAF_MMA_DETACH_CAUSE_SRV_DOMAIN_DETACH      = 2,/* system configure??????????????detach */
    TAF_MMA_DETACH_CAUSE_3GPP2_ATTACHED         = 3,/* ??3GPP2?????????? */
    TAF_MMA_DETACH_CAUSE_BUTT
};
typedef VOS_UINT8 TAF_MMA_DETACH_CAUSE_ENUM_UINT8;

/* Added by s00246516 for L-C??????????, 2014-01-24, End */

/*****************************************************************************
 ??????    : TAF_MMA_PLMN_WITH_CSG_ID_TYPE_ENUM_UINT8
 ????????  : CSG ID????
1.??    ??   : 2015??9??6??
  ??    ??   : z00161729
  ????????   : ????LTE CSG????????
*****************************************************************************/
enum TAF_MMA_PLMN_WITH_CSG_ID_TYPE_ENUM
{
    TAF_MMA_CSG_ID_TYPE_IN_ALLOWED_CSG_LIST                  = 1,  /* CSG ID??Allowed CSG List??*/
    TAF_MMA_CSG_ID_TYPE_IN_OPERATOR_CSG_LIST_NOT_FOBIDDEN    = 2,  /* CSG ID??Operator CSG List??????????CSG ID?????? */
    TAF_MMA_CSG_ID_TYPE_IN_OPERATOR_CSG_LIST_FOBIDDEN        = 3,  /* CSG ID??Operator CSG List????????????CSG ID??????*/
    TAF_MMA_CSG_ID_TYPE_NOT_IN_ALLOWED_AND_OPERATOR_CSG_LIST = 4,  /* CSG ID????Allowed CSG List??Operator CSG List??*/
    TAF_MMA_CSG_ID_TYPE_BUTT
};
typedef VOS_UINT8 TAF_MMA_PLMN_WITH_CSG_ID_TYPE_ENUM_UINT8;


/*****************************************************************************
 ??????    : TAF_MMA_APP_PREF_PLMN_OPER_RESULT_ENUM
 ????????  : ????plmn????????????????
 1.??    ??   : 2015??02??13??
   ??    ??   : y00307564
   ????????   : ????????
*****************************************************************************/
enum TAF_MMA_APP_PREF_PLMN_OPER_RESULT_ENUM
{
    TAF_MMA_APP_PREF_PLMN_OPER_RESULT_SUCCESS               = 0, /* ???????? */
    TAF_MMA_APP_PREF_PLMN_OPER_RESULT_FAILURE               = 1, /* ???????? */
    TAF_MMA_APP_PREF_PLMN_OPER_RESULT_USIM_ABSENT           = 2, /* ???? */
    TAF_MMA_APP_PREF_PLMN_OPER_RESULT_NULL_PTR              = 3, /* ?????? */
    TAF_MMA_APP_PREF_PLMN_OPER_RESULT_CHECK_PARA_ERR        = 4, /* ????????????cpol?????????? */
    TAF_MMA_APP_PREF_PLMN_OPER_RESULT_TIMEOUT               = 5, /* ?????????? */
    TAF_MMA_APP_PREF_PLMN_OPER_RESULT_INVALID_PLMN          = 6, /* plmn???? */
    TAF_MMA_APP_PREF_PLMN_OPER_RESULT_BUTT
};
typedef VOS_UINT32 TAF_MMA_APP_PREF_PLMN_OPER_RESULT_ENUM_UINT32;

/*****************************************************************************
 ??????    : TAF_MMA_VOICE_DOMAIN_ENUM
 ????????  : VOICE DOMAIN????
  1.??    ??   : 2015??02??03??
    ??    ??   : f00179208
    ????????   : IMS????????????????
*****************************************************************************/
enum TAF_MMA_VOICE_DOMAIN_ENUM
{
    TAF_MMA_VOICE_DOMAIN_CS_ONLY            = 0,    /* CS voice only */
    TAF_MMA_VOICE_DOMAIN_IMS_PS_ONLY        = 1,    /* IMS PS voice only */
    TAF_MMA_VOICE_DOMAIN_CS_PREFERRED       = 2,    /* CS vocie preferred, IMS PS voice as secondary */
    TAF_MMA_VOICE_DOMAIN_IMS_PS_PREFERRED   = 3,    /* IMS PS voice preferred, CS vocie as secondary */

    TAF_MMA_VOICE_DOMAIN_BUTT
};
typedef VOS_UINT32 TAF_MMA_VOICE_DOMAIN_ENUM_UINT32;

/*****************************************************************************
 ??????    : TAF_MMA_IMS_SWITCH_SET_ENUM_UINT8
 ????????  : IMS????????????????????????????
 1.??    ??   : 2015??02??04??
   ??    ??   : f00179208
   ????????   : ????
*****************************************************************************/
enum TAF_MMA_IMS_SWITCH_SET_ENUM
{
    TAF_MMA_IMS_SWITCH_SET_OFF          = 0,
    TAF_MMA_IMS_SWITCH_SET_ON           = 1,
    TAF_MMA_IMS_SWITCH_STATE_BUTT
};
typedef VOS_UINT8 TAF_MMA_IMS_SWITCH_SET_ENUM_UINT8;

/** ****************************************************************************
 * Name        : TAF_MMA_1X_CAS_P_REV_ENUM_UINT8
 *
 * Description :
 *******************************************************************************/
enum TAF_MMA_1X_CAS_P_REV_ENUM
{
    TAF_MMA_1X_CAS_P_REV_JST_008       = 0x01,
    TAF_MMA_1X_CAS_P_REV_IS_95         = 0x02,
    TAF_MMA_1X_CAS_P_REV_IS_95A        = 0x03,
    TAF_MMA_1X_CAS_P_REV_IS_95B_CUSTOM = 0x04,
    TAF_MMA_1X_CAS_P_REV_IS_95B        = 0x05,
    TAF_MMA_1X_CAS_P_REV_IS_2000       = 0x06,
    TAF_MMA_1X_CAS_P_REV_IS_2000A      = 0x07,
    TAF_MMA_1X_CAS_P_REV_ENUM_BUTT     = 0x08
};
typedef VOS_UINT8 TAF_MMA_1X_CAS_P_REV_ENUM_UINT8;


/*****************************************************************************
 ??????    : TAF_MMA_RAT_TYPE_ENUM_UINT32
 ????????  : ??????????????
 1.??    ??   : 2015??05??15??
   ??    ??   : y00314741
   ????????   : ????
*****************************************************************************/
enum TAF_MMA_PS_RAT_TYPE_ENUM
{
    TAF_MMA_PS_RAT_TYPE_NULL,          /* ?????????????????????? */
    TAF_MMA_PS_RAT_TYPE_GSM,           /* GSM???????? */
    TAF_MMA_PS_RAT_TYPE_WCDMA,         /* WCDMA???????? */
    TAF_MMA_PS_RAT_TYPE_LTE,           /* LTE???????? */
    TAF_MMA_PS_RAT_TYPE_1X,            /* CDMA-1X???????? */
    TAF_MMA_PS_RAT_TYPE_HRPD,          /* CDMA-HRPD???????? */
    TAF_MMA_PS_RAT_TYPE_EHRPD,         /* CDMA-EHRPD???????? */
    TAF_MMA_PS_RAT_TYPE_BUTT           /* ?????????????? */
};
typedef VOS_UINT32 TAF_MMA_PS_RAT_TYPE_ENUM_UINT32;

/*****************************************************************************
 ??????    : TAF_MMA_QRY_REG_STATUS_TYPE_ENUM_UINT32
 ????????  : ??????????????????
 1.??    ??   : 2015??08??19??
   ??    ??   : w00176964
   ????????   : ????
*****************************************************************************/
enum TAF_MMA_QRY_REG_STATUS_TYPE_ENUM
{
    TAF_MMA_QRY_REG_STATUS_TYPE_CS,          /* CREG????CS???????? */
    TAF_MMA_QRY_REG_STATUS_TYPE_PS,          /* CREG????PS???????? */
    TAF_MMA_QRY_REG_STATUS_TYPE_EPS,         /* CREG????EPS???????? */
    TAF_MMA_QRY_REG_STATUS_TYPE_BUTT         /* ?????????????? */
};
typedef VOS_UINT32 TAF_MMA_QRY_REG_STATUS_TYPE_ENUM_UINT32;


/*****************************************************************************
 ??????    : TAF_MMA_IMS_DOMAIN_CFG_TYPE_ENUM_UINT32
 ????????  : IMS??????
 1.??    ??   : 2015??10??26??
   ??    ??   : h00360002
   ????????   : ????
*****************************************************************************/
enum TAF_MMA_IMS_DOMAIN_CFG_TYPE_ENUM
{
    TAF_MMA_IMS_DOMAIN_CFG_TYPE_WIFI_PREFER     = 0,      /* WIFI prefer */
    TAF_MMA_IMS_DOMAIN_CFG_TYPE_LTE_PREFER      = 1,      /* LTE prefer */
    TAF_MMA_IMS_DOMAIN_CFG_TYPE_WIFI_ONLY       = 2,      /* WIFI only */
    TAF_MMA_IMS_DOMAIN_CFG_TYPE_BUTT            /* ?????????????? */
};
typedef VOS_UINT32 TAF_MMA_IMS_DOMAIN_CFG_TYPE_ENUM_UINT32;

/*****************************************************************************
 ??????    : TAF_MMA_IMS_DOMAIN_CFG_RESULT_ENUM_UINT32
 ????????  : IMS??????????????????
 1.??    ??   : 2015??10??26??
   ??    ??   : h00360002
   ????????   : ????
*****************************************************************************/
enum TAF_MMA_IMS_DOMAIN_CFG_RESULT_ENUM
{
    TAF_MMA_IMS_DOMAIN_CFG_RESULT_SUCCESS       = 0,
    TAF_MMA_IMS_DOMAIN_CFG_RESULT_FAILED        = 1,
    TAF_MMA_IMS_DOMAIN_CFG_RESULT_BUTT
};
typedef VOS_UINT32 TAF_MMA_IMS_DOMAIN_CFG_RESULT_ENUM_UINT32;

/*****************************************************************************
 ??????    : TAF_MMA_ROAM_IMS_SUPPORT_ENUM_UINT32
 ????????  : ??????IMS????????
 1.??    ??   : 2016??3??10??
   ??    ??   : W00316404
   ????????   : ????
*****************************************************************************/
enum TAF_MMA_ROAM_IMS_SUPPORT_ENUM
{
    TAF_MMA_ROAM_IMS_UNSUPPORT                   = 0,
    TAF_MMA_ROAM_IMS_SUPPORT                     = 1,

    TAF_MMA_ROAM_IMS_BUTT
};
typedef VOS_UINT32 TAF_MMA_ROAM_IMS_SUPPORT_ENUM_UINT32;

/*****************************************************************************
 ??????    : TAF_MMA_ROAM_IMS_SUPPORT_RESULT_ENUM_UINT32
 ????????  : ??????IMS????????????????????
 1.??    ??   : 2016??3??10??
   ??    ??   : w00316404
   ????????   : ????
*****************************************************************************/
enum TAF_MMA_ROAM_IMS_SUPPORT_RESULT_ENUM
{
    TAF_MMA_ROAM_IMS_SUPPORT_RESULT_SUCCESS    = 0,
    TAF_MMA_ROAM_IMS_SUPPORT_RESULT_FAILED     = 1,
    TAF_MMA_ROAM_IMS_SUPPORT_RESULT_BUTT
};
typedef VOS_UINT32 TAF_MMA_ROAM_IMS_SUPPORT_RESULT_ENUM_UINT32;


#define  TAF_INVALID_TAB_INDEX          0
/*TAF??????ID*/
#ifndef SUBMOD_NULL
#define  SUBMOD_NULL                    0
#endif
#define  TAF_CCA                        1
#define  TAF_APS                        2
#define  TAF_SMA                        3
#define  TAF_SSA                        4
#define  TAF_MMA                        5
#define  TAF_ALL_SUBMODULE              0xFF    /*??????????*/
#define  TAF_TAFM                       0



/* IMEI????????????: IMEI??????IMEI(TAC8??,SNR6??)??????????????????*/
#define TAF_IMEI_DATA_LENGTH            (15)

typedef struct
{
    TAF_UINT32    Mcc;
    TAF_UINT32    Mnc;
}TAF_PLMN_ID_STRU;



/*****************************************************************************
 ??????    : TAF_MMA_HPLMN_WITH_MNC_LEN_STRU
 ????????  : ????MNC????HPLMN??
 1.??    ??   : 2012??04??18??
   ??    ??   : w00166186
   ????????   : ????
*****************************************************************************/
typedef struct
{
    TAF_PLMN_ID_STRU    stHplmn;
    VOS_UINT8           ucHplmnMncLen;
    VOS_UINT8           aucReserved[3];
}TAF_MMA_HPLMN_WITH_MNC_LEN_STRU;


#define TAF_PH_RELEASEDATE_LEN            10
typedef struct
{

    TAF_UINT8     aucReleaseDate[TAF_PH_RELEASEDATE_LEN+1];         /*????????*/
}TAF_PH_RELEASE_DATE_STRU;

#define TAF_PH_RELEASETIME_LEN             8
typedef struct
{

    TAF_UINT8     aucReleaseTime[TAF_PH_RELEASETIME_LEN+1];         /*????????*/
}TAF_PH_RELEASE_TIME_STRU;


#define TAF_PH_CAPLITYCLASS1               1
#define TAF_PH_CAPLITYCLASS2               4
#define TAF_PH_CAPLITYCLASS3              16
#define TAF_PH_COMPLETECAPILITYLIST_LEN   16
#define TAF_PH_CAPILITYLIST_TYPE           3
typedef struct
{
/*??????????????*/
    TAF_UINT8       aucCompleteCapilityList[TAF_PH_CAPILITYLIST_TYPE][TAF_PH_COMPLETECAPILITYLIST_LEN];
}TAF_PH_COMPCAPLIST_STRU;


/*****************************************************************************
 ??????    : MN_MMA_CPAM_RAT_TYPE_ENUM_UINT8
 ????????  : at^cpam??????????????????
 1.??    ??   : 2011??8??03??
   ??    ??   : z00161729
   ????????   : ????
*****************************************************************************/
enum MN_MMA_CPAM_RAT_TYPE_ENUM
{
    MN_MMA_CPAM_RAT_TYPE_WCDMA,          /* WCDMA????**/
    MN_MMA_CPAM_RAT_TYPE_WCDMA_GSM,      /* WCDMA/GSM???? */
    MN_MMA_CPAM_RAT_TYPE_GSM,            /* GSM???? */
    MN_MMA_CPAM_RAT_TYPE_NOCHANGE,       /* ??????*/
    MN_MMA_CPAM_RAT_TYPE_BUTT
};
typedef VOS_UINT8 MN_MMA_CPAM_RAT_TYPE_ENUM_UINT8;

#define  TAF_PHONE_ACCESS_MODE_LEN        (2)

/*Taf_USIM_RAT*/
typedef TAF_UINT16 TAF_MMC_USIM_RAT;
#define TAF_MMC_USIM_UTRN_RAT             0x8000
#define TAF_MMC_USIM_GSM_RAT              0x0080
#define TAF_MMC_USIM_UTRN_GSM_RAT         0x8080
#define TAF_MMC_USIM_GSM_COMPACT_RAT      0x0040
#define TAF_MMC_USIM_NO_RAT               0x0000
#define TAF_MMC_USIM_E_UTRN_RAT            0x4000
#define MMC_MS_LTE                          2

typedef TAF_UINT8 TAF_PHONE_SERVICE_STATUS;

typedef TAF_UINT8 TAF_PHONE_CHANGED_SERVICE_STATUS;                      /* ????????????????????(^SRVST) */
#define TAF_REPORT_SRVSTA_NO_SERVICE                   0                        /* ??????????       */
#define TAF_REPORT_SRVSTA_LIMITED_SERVICE              1                        /* ????????????     */
#define TAF_REPORT_SRVSTA_NORMAL_SERVICE               2                        /* ????????????     */
#define TAF_REPORT_SRVSTA_REGIONAL_LIMITED_SERVICE     3                        /* ???????????????? */
#define TAF_REPORT_SRVSTA_DEEP_SLEEP                   4                        /* ???????????????? */

/* typedef TAF_UINT16 TAF_PHONE_ERROR; */

typedef struct
{
    TAF_PHONE_SERVICE_STATUS            CsSrvSta; /*CS????????*/
    TAF_PHONE_SERVICE_STATUS            PsSrvSta; /*PS????????*/
    VOS_UINT8                           aucReserved[2];
}TAF_PH_SRV_STA_STRU;

typedef TAF_UINT8 TAF_PH_PLMN_PRIO;
#define TAF_PLMN_PRIO_AUTO    0         /*????????????*/
#define TAF_PLMN_GSM_PRIO     1         /*????2G????*/
#define TAF_PLMN_WCDMA_PRIO   2         /*????3G????*/
#define TAF_PLMN_PRIO_NOCHANGE  3

#define TAF_PLMN_PRIO_DIST_BTWN_CPAM_SYSCFG  1 /*CPAM??SYSCFG?????????????????????? 1 */

typedef TAF_UINT8 TAF_PH_MS_CLASS_TYPE;
#define TAF_PH_MS_CLASS_CC        0     /*??????CS????????????MMC??D_MMC_MODE_CC*/
#define TAF_PH_MS_CLASS_CG        1     /*??????PS????????????MMC??D_MMC_MODE_CG*/
#define TAF_PH_MS_CLASS_A         2

#define TAF_PH_MS_CLASS_ANY       3     /* ????????????CS?? */

#define TAF_PH_MS_CLASS_NULL      5
#define TAF_PH_MS_CLASS_B         6     /*??????GSM??B??????*/

/* ????????????(TAF_PH_SERVICE_DOMAIN)???????? */
/*****************************************************************************
 ??????    : TAF_MMA_SERVICE_DOMAIN_ENUM_UINT8
 ????????  : ????????????????????
 1.??    ??   : 2015??04??09??
   ??    ??   : h00313353
   ????????   : ????????
*****************************************************************************/
enum TAF_MMA_SERVICE_DOMAIN_ENUM
{
    TAF_MMA_SERVICE_DOMAIN_CS                   = 0,   /* CS?? */
    TAF_MMA_SERVICE_DOMAIN_PS                   = 1,   /* PS?? */
    TAF_MMA_SERVICE_DOMAIN_CS_PS                = 2,   /* CS??PS?? */
    TAF_MMA_SERVICE_DOMAIN_ANY                  = 3,   /* CS??PS?? */
    TAF_MMA_SERVICE_DOMAIN_NOCHANGE             = 4,   /* ?????????? */
    TAF_MMA_SERVICE_DOMAIN_NULL                 = 5,   /* ???????? */

    TAF_MMA_SERVICE_DOMAIN_BUTT
};
typedef TAF_UINT8 TAF_MMA_SERVICE_DOMAIN_ENUM_UINT8;

/*****************************************************************************
 ??????    : TAF_MMA_ATTACH_TYPE_ENUM_UINT8
 ????????  : ATTACH????????
 1.??    ??   : 2015??04??09??
   ??    ??   : h00313353
   ????????   : ????????
*****************************************************************************/
enum TAF_MMA_ATTACH_TYPE_ENUM
{
    TAF_MMA_ATTACH_TYPE_NULL            = 0,
    TAF_MMA_ATTACH_TYPE_GPRS            = 1, /* PS */
    TAF_MMA_ATTACH_TYPE_IMSI            = 2, /* CS */
    TAF_MMA_ATTACH_TYPE_GPRS_IMSI       = 3, /* PS & CS */

    TAF_MMA_ATTACH_TYPE_BUTT
};
typedef TAF_UINT8 TAF_MMA_ATTACH_TYPE_ENUM_UINT8;

/*****************************************************************************
 ??????    : TAF_MMA_DETACH_TYPE_ENUM_UINT8
 ????????  : DETACH????????
 1.??    ??   : 2015??04??09??
   ??    ??   : h00313353
   ????????   : ????????
*****************************************************************************/
enum TAF_MMA_DETACH_TYPE_ENUM
{
    TAF_MMA_DETACH_TYPE_NULL            = 0,
    TAF_MMA_DETACH_TYPE_GPRS            = 1, /* PS */
    TAF_MMA_DETACH_TYPE_IMSI            = 2, /* CS */
    TAF_MMA_DETACH_TYPE_GPRS_IMSI       = 3, /* PS & CS */

    TAF_MMA_DETACH_TYPE_BUTT
};
typedef TAF_UINT8 TAF_MMA_DETACH_TYPE_ENUM_UINT8;


/*****************************************************************************
 ??????    : TAF_MMA_ATTACH_STATUS_ENUM_UINT8
 ????????  : ????????????????
 1.??    ??   : 2015??04??09??
   ??    ??   : h00313353
   ????????   : ????????
*****************************************************************************/
enum TAF_MMA_ATTACH_STATUS_ENUM
{
    TAF_MMA_ATTACH_STATUS_DETACHED       = 0,
    TAF_MMA_ATTACH_STATUS_ATTACHED       = 1,

    TAF_MMA_ATTACH_STATUS_BUTT
};
typedef TAF_UINT8 TAF_MMA_ATTACH_STATUS_ENUM_UINT8;

typedef TAF_UINT8 TAF_PH_IMSI_LOCK_STATUS;
#define TAF_PH_IMSI_LOCK_ENABLED             1
#define TAF_PH_IMSI_LOCK_DISABLED            0

/* ????????????*/
#define TAF_MAX_PORT_INFO_LEN     100
typedef struct
{
    TAF_UINT8 aucPortInfo[TAF_MAX_PORT_INFO_LEN + 1];
    TAF_UINT8 aucRsv[3];
}TAF_PH_PORT_INFO_STRU;


/*****************************************************************************
 ??????    : TAF_PH_CREATION_TIME_STRU
 ????????  :
 ASN.1???? :
 ????????  : ????????????
*****************************************************************************/
#define TAF_MAX_CREATION_TIME_LEN       31
typedef struct
{
    TAF_UINT8 aucCreationTime[TAF_MAX_CREATION_TIME_LEN + 1];
}TAF_PH_CREATION_TIME_STRU;

#define TAF_CFG_VERSION                 (1004)

/*+CGMR - ??????????????????*/
typedef struct
{
    TAF_UINT8 aucRevisionId[TAF_MAX_REVISION_ID_LEN + 1];
}TAF_PH_REVISION_ID_STRU;

/*****************************************************************************
 ??????    : TAF_PH_HW_VER_STRU
 ????????  :
 ASN.1???? :
 ????????  : ????????
*****************************************************************************/
typedef struct
{
    TAF_UINT8 aucHwVer[TAF_MAX_HARDWARE_LEN+1];
}TAF_PH_HW_VER_STRU;

/*+CGMM - ????????????*/
typedef struct
{
    TAF_UINT8 aucModelId[TAF_MAX_MODEL_ID_LEN + 1];
}TAF_PH_MODEL_ID_STRU;

/*****************************************************************************
 ??????    : TAF_PH_CDROM_VER_STRU
 ????????  :
 ASN.1???? :
 ????????  : ??????????????
*****************************************************************************/


typedef struct
{
    TAF_UINT8 aucIsoInfo[TAF_CDROM_VERSION_LEN];
}TAF_PH_CDROM_VER_STRU;

/*+CGSN - ????IMEI*/
typedef TAF_UINT8 TAF_PH_IMEI_TYPE;
#define TAF_PH_IMEI_LEN     16
#define TAF_PH_IMEIV_Mode   1
#define TAF_PH_IMEI_Mode    0

typedef struct
{
    TAF_PH_IMEI_TYPE                    ImeiMode;
    TAF_UINT8                           aucImei[TAF_PH_IMEI_LEN + 1];
    VOS_UINT8                           aucReserved[2];
}TAF_PH_IMEI_STRU;


 /*+CIMI - ????IMSI*/
#define TAF_PH_IMSI_LEN     15
typedef struct
{
    TAF_UINT8  aucImsi[TAF_PH_IMSI_LEN + 1];
}TAF_PH_IMSI_STRU;



/*+CREG - ????????????????????????*/
#define TAF_PH_LAC_LENGTH       4
#define TAF_PH_CI_LENGTH        4
#define TAF_PH_RAC_LENGTH       2


/*????????*/
typedef TAF_UINT8 TAF_PH_REG_STATE_TYPE;
#define TAF_PH_REG_NOT_REGISTERED_NOT_SEARCH   0 /*??????????MS??????????????????????????????????*/
#define TAF_PH_REG_REGISTERED_HOME_NETWORK     1 /*??????????????*/
#define TAF_PH_REG_NOT_REGISTERED_SEARCHING    2 /*????????????MS??????????????????????????*/
#define TAF_PH_REG_REGISTERED_DENIED           3 /*??????????*/
#define TAF_PH_REG_UNKNOWN                     4 /*????????*/
#define TAF_PH_REG_REGISTERED_ROAM             5 /*??????????????*/

#define TAF_MMC_NORMAL_SERVICE                0

#define TAF_MMC_LIMITED_SERVICE                 (1)                             /* ???????? */
#define TAF_MMC_LIMITED_SERVICE_REGION          (2)                             /* ?????????????? */
#define TAF_MMC_NO_IMSI                         (3)                             /* ??imsi */
#define TAF_MMC_NO_SERVICE                      (4)                             /* ?????? */



/*????????????????+CFUN  */
typedef TAF_UINT8 TAF_PH_MODE;
#define TAF_PH_MODE_MINI                0   /* minimum functionality*/
#define TAF_PH_MODE_FULL                1   /* full functionality */
#define TAF_PH_MODE_TXOFF               2   /* disable phone transmit RF circuits only */
#define TAF_PH_MODE_RXOFF               3   /* disable phone receive RF circuits only */
#define TAF_PH_MODE_RFOFF               4   /* disable phone both transmit and receive RF circuits */
#define TAF_PH_MODE_FT                  5   /* factory-test functionality */
#define TAF_PH_MODE_RESET               6   /* reset */
#define TAF_PH_MODE_VDFMINI             7   /* mini mode required by VDF*/
#define TAF_PH_MODE_POWEROFF            8   /* ???????????? */
#define TAF_PH_MODE_LOWPOWER            9
#define TAF_PH_MODE_NUM_MAX             10

typedef TAF_UINT8   TAF_PH_RESET_FLG;
#define TAF_PH_OP_MODE_UNRESET       0
#define TAF_PH_OP_MODE_RESET         1

typedef TAF_UINT8   TAF_PH_CMD_TYPE;
#define TAF_PH_CMD_SET                  0   /* set cmd */
#define TAF_PH_CMD_QUERY                1   /* query cmd */

typedef struct
{
     TAF_PH_CMD_TYPE                    CmdType; /* ???????? */
     TAF_PH_MODE                        PrePhMode;
     TAF_PH_MODE                        PhMode;  /* ???? */
     TAF_PH_RESET_FLG                   PhReset; /* ???????????? */
}TAF_PH_OP_MODE_STRU;
typedef struct
{
     TAF_PH_CMD_TYPE                    CmdType; /* ???????? */
     TAF_PH_MODE                        PhMode;  /* ???? */
     VOS_UINT8                          aucReserved[2];
}TAF_PH_OP_MODE_CNF_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_W_CELL_SIGN_INFO_STRU
 ????????  : ????????????????
 1.??    ??   : 2012??11??21??
   ??    ??   : z00161729
   ????????   : ????cerssi??nmr
*****************************************************************************/
typedef struct
{
    VOS_INT16                       sRscpValue;  /* ????????????????3g??^cerssi????????*/
    VOS_INT16                       sEcioValue;  /* ??????????????3g??^cerssi????????*/
} TAF_MMA_W_CELL_SIGN_INFO_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_G_CELL_SIGN_INFO_STRU
 ????????  : ????????????????
 1.??    ??   : 2012??11??21??
   ??    ??   : z00161729
   ????????   : ????cerssi??nmr
*****************************************************************************/
typedef struct
{
    VOS_INT16                       sRssiValue;   /* ????????????????2g??^cerssi????????,2g????rscp????????????rssi */
    VOS_UINT8                       aucReserve1[2];
} TAF_MMA_G_CELL_SIGN_INFO_STRU;

/*****************************************************************************
 ??????    : TAF_SDC_4G_CELL_SIGN_INFO_STRU
 ????????  : 4G????????????????
 1.??    ??   : 2014??10??17??
   ??    ??   : z00234330
   ????????   : ????????????
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usRI;                                   /* RI*/
    VOS_UINT8                           aucRes[2];
    VOS_UINT16                          ausCQI[2];                              /* CQI???????? */

}TAF_MMA_CQI_INFO_STRU;

typedef struct
{
    VOS_UINT8                           ucRxANTNum;                    /*????????*/
    VOS_UINT8                           aucRev[3];
    VOS_INT16                           asRsrpRx[TAF_MMA_MAX_ANT_NUM]; /*????????rsrp??*/
    VOS_INT32                           alSINRRx[TAF_MMA_MAX_ANT_NUM]; /*????????sinr??*/
}TAF_MMA_RX_ANT_INFO_STRU;

typedef struct
{
    VOS_INT16                           sRssi;              /* Rssi*/
    VOS_INT16                           sRsd;               /* ????????*/
    VOS_INT16                           sRsrp;              /* ??????(-141,-44), 99?????? */
    VOS_INT16                           sRsrq;              /* ??????(-40, -6) , 99?????? */
    VOS_INT32                           lSINR;              /* SINR RS_SNR */
    TAF_MMA_CQI_INFO_STRU               stCQI;              /*Channle Quality Indicator*/
    TAF_MMA_RX_ANT_INFO_STRU            stRxAntInfo;        /*????????????????????*/
}TAF_MMA_L_CELL_SIGN_INFO_STRU;



/*RSSI????????????+CSQ*/
/*
  0       ????0?????? -113 dBm
  1                -111 dBm
  2...30           -109...  -53 dBm
  31     ?????????? -51 dBm
  99     ??????????????
*/
#define TAF_PH_RSSIUNKNOW        99
#define TAF_PH_RSSIZERO          0
#define TAF_PH_RSSI_LOW                             (-113)
#define TAF_PH_RSSI_HIGH                            (-51)
#define TAF_PH_CSQ_RSSI_LOW                         (0)
#define TAF_PH_CSQ_RSSI_HIGH                        (31)
#define TAF_PH_BER_UNKNOWN                          (99)

typedef struct
{
    TAF_UINT8                           ucRssiValue;       /*??????????????????????????*/
    TAF_UINT8                           ucChannalQual;     /*??????,??????????????????????,????????99*/
    VOS_UINT8                           aucReserved1[2];

    union
    {
        TAF_MMA_W_CELL_SIGN_INFO_STRU   stWCellSignInfo;
        TAF_MMA_G_CELL_SIGN_INFO_STRU   stGCellSignInfo;
        TAF_MMA_L_CELL_SIGN_INFO_STRU   stLCellSignInfo;
    }u;


}TAF_PH_RSSI_VALUE_STRU;


#define TAF_PH_RSSI_MAX_NUM         8

typedef struct
{
    TAF_UINT8                           ucRssiNum;                    /*??????????????????????*/

    TAF_MMA_RAT_TYPE_ENUM_UINT8         enRatType;                    /* ????????0:G;1:W */
    VOS_UINT8                           ucCurrentUtranMode;
    VOS_UINT8                           aucReserv1;

    /* Modified by z00161729 for ????????AT??????????????C??, 2013-4-7, begin */
    VOS_UINT16                          usCellDlFreq;                           /*????????(????)*/
    VOS_UINT16                          usCellUlFreq;                           /*????????(????)*/
    VOS_INT16                           sUeRfPower;                             /*????????*/
    VOS_UINT8                           aucReserved[2];
    /* Modified by z00161729 for ????????AT??????????????C??, 2013-4-7, end */

    TAF_PH_RSSI_VALUE_STRU              aRssi[TAF_PH_RSSI_MAX_NUM];   /*??????????????????????????*/
}TAF_PH_RSSI_STRU;

typedef struct
{
    TAF_INT32                           lRscpValue;
    TAF_INT32                           lEcioValue;
    TAF_UINT8                           ucRssiValue;       /*??????????????????????????*/
    TAF_UINT8                           ucAnlevelValue;
    TAF_UINT8                           ucChannalQual;     /*??????,??????????????????????,????????99*/
    VOS_UINT8                           aucReserved[1];
}TAF_PH_ANLEVEL_VALUE_STRU;

#define TAF_PH_ANLEVEL_MAX_NUM         8

typedef struct
{
    TAF_UINT8                           ucAnlevelNum;                    /*??????????????????????*/
    VOS_UINT8                           aucReserved[3];
    TAF_PH_ANLEVEL_VALUE_STRU           aAnlevel[TAF_PH_ANLEVEL_MAX_NUM];   /*??????????????????????????*/
}TAF_PH_ANLEVEL_STRU;

#define TAF_UE_RFPOWER_INVALID      0x1fff
#define TAF_FREQ_INVALID            0xffff
typedef struct
{
    TAF_UINT32                          CellId;
    TAF_INT16                           CellRSCP;
    VOS_UINT8                           aucReserved[2];
} TAF_PH_CELL_RSCP_ST;

typedef struct
{
    TAF_UINT16                          CellNum;
    VOS_UINT8                           aucReserved1[2];
    TAF_PH_CELL_RSCP_ST                 CellRscp[TAF_PH_RSSI_MAX_NUM];
    TAF_UINT16                          CellDlFreq;       /*????????(????)*/
    VOS_UINT8                           aucReserved2[2];
} TAF_PH_CELL_RSSI_STRU;

typedef struct
{
    TAF_UINT16              CellUlFreq;       /*????????(????)*/
    TAF_INT16               UeRfPower;        /*????????*/
} TAF_PH_UE_RFPOWER_FREQ_STRU;

/*????????????+CBC*/
 /*
 ??????????
 0 ????????????
 1 ??????????????????????????
 2 ??????????????
 3 ????????, ????????
*/
#define TAF_PH_BATTERYCHARGING             0
#define TAF_PH_BATTERYNOSUPPLY             1
#define TAF_PH_NOBATTERYFIXED              2
#define TAF_PH_POWERSOURCEERROR            3
typedef TAF_UINT8 TAF_PH_BATTERYPOWER_STA;

/*
0????????????????????????
1...100 ????????????????????
*/
typedef TAF_UINT8 TAF_PH_BATTERY_REMAINS;
typedef struct
{
   TAF_PH_BATTERYPOWER_STA              BatteryPowerStatus;
   TAF_PH_BATTERY_REMAINS               BatteryRemains;
   VOS_UINT8                            aucReserved[2];
}TAF_MMA_BATTERYPOWER_STRU;


typedef TAF_UINT8 TAF_ME_PERSONALISATION_CMD_TYPE;
#define TAF_ME_PERSONALISATION_SET             0x01   /*????????????????????*/
#define TAF_ME_PERSONALISATION_VERIFY          0x02   /*????????????????????*/
#define TAF_ME_PERSONALISATION_PWD_CHANGE      0x03   /*????????????????????*/
#define TAF_ME_PERSONALISATION_ACTIVE          0x04   /*????????????????????*/
#define TAF_ME_PERSONALISATION_DEACTIVE        0x05   /*??????????????????????*/
#define TAF_ME_PERSONALISATION_RETRIEVE        0x06   /*????????????????????????????*/
#define TAF_ME_PERSONALISATION_QUERY           0x07   /*????????????????????????????*/

/*??????????????????????*/
typedef TAF_UINT8 TAF_ME_PERSONALISATION_TYPE;
#define TAF_SIM_PERSONALISATION                 0x01   /*????*/
#define TAF_NETWORK_PERSONALISATION             0x02   /*??????*/
#define TAF_NETWORK_SUBSET_PERSONALISATION      0x03   /*??????????*/
#define TAF_SERVICE_PROVIDE_PERSONALISATION     0x04   /*????????????*/
#define TAF_CORPORATE_PERSONALISATION           0x05   /*??????**/
#define TAF_OPERATOR_PERSONALISATION            0x06   /*??????:??????,???????????????? */

/*????????????????*/
typedef TAF_UINT8 TAF_ME_PERSONALISATION_STATUS_FLAG;
#define TAF_ME_PERSONALISATION_ACTIVE_STATUS       0
#define TAF_ME_PERSONALISATION_DEACTIVE_STATUS     1

/*??????:???????????????????????? */
#define TAF_OPERATOR_LOCK_STATUS_NOT_UNLOCK        TAF_ME_PERSONALISATION_ACTIVE_STATUS
#define TAF_OPERATOR_LOCK_STATUS_UNLOCKED          TAF_ME_PERSONALISATION_DEACTIVE_STATUS

/* ??????????????????*/
typedef enum
{
    TAF_OPERATOR_LOCK_NEED_UNLOCK_CODE             = 1,/* ?????????????? */
    TAF_OPERATOR_LOCK_NONEED_UNLOCK_CODE           = 2,/* ???????????????? */
    TAF_OPERATOR_LOCK_LOCKED                       = 3,/* ???????????? */
    TAF_OPERATOR_LOCK_BUTT
}TAF_OPERATOR_LOCK_STATUS_ENUM;
typedef TAF_UINT32 TAF_OPERATOR_LOCK_STATUS_ENUM_U32;

#define TAF_OPERATOR_UNLOCK_TIMES_MAX                   10  /* ?????????????????????? */
#define TAF_OPERATOR_UNLOCK_TIMES_MIN                   0   /* ?????????????????????? */
#define TAF_PH_ME_LOCK_OPER_LEN_MAX                     15  /* ???????????????????????????????? */
#define TAF_PH_ME_LOCK_OPER_LEN_MIN                     5   /* ???????????????????????????????? */

typedef struct
{
    TAF_UINT32                          RemainTimes;
    TAF_OPERATOR_LOCK_STATUS_ENUM_U32   OperatorLockStatus;
    TAF_UINT8                           OperatorLen;
    TAF_UINT8                           Operator[TAF_PH_ME_LOCK_OPER_LEN_MAX];
}TAF_OPERATOR_LOCK_INFO_STRU;

#define TAF_MAX_IMSI_LEN                        15
typedef struct
{
    TAF_UINT8   DataLen;
    TAF_UINT8   aucSimPersonalisationStr[TAF_MAX_IMSI_LEN];       /* ??????????????   */
}TAF_SIM_PERSIONALISATION_STR_STRU;

typedef union
{
    /*????????,CmdType??TAF_ME_PERSONALISATION_RETRIEVE??MePersonalType??TAF_SIM_PERSONALISATION??????*/
    TAF_SIM_PERSIONALISATION_STR_STRU  SimPersionalisationStr;
}TAF_ME_PERSONALISATION_SET_UN;

typedef union
{
    /*????????,CmdType??TAF_ME_PERSONALISATION_RETRIEVE??MePersonalType??TAF_SIM_PERSONALISATION??????*/
    TAF_SIM_PERSIONALISATION_STR_STRU  SimPersionalisationStr;

    /*????????????,CmdType??TAF_ME_PERSONALISATION_QUERY??MePersonalType??TAF_OPERATOR_PERSONALISATION??????*/
    TAF_OPERATOR_LOCK_INFO_STRU        OperatorLockInfo;
}TAF_ME_PERSONALISATION_REPORT_CONTENT_UN;

#define TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX   8
typedef struct
{
    TAF_ME_PERSONALISATION_CMD_TYPE     CmdType;
    TAF_ME_PERSONALISATION_TYPE         MePersonalType;
    TAF_UINT8                           aucOldPwd[TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX +1];
    TAF_UINT8                           aucNewPwd[TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX +1];
    TAF_ME_PERSONALISATION_SET_UN       unMePersonalisationSet;
}TAF_ME_PERSONALISATION_DATA_STRU;

typedef TAF_UINT8   TAF_OP_ME_PERSONALISATION_RESULT;
#define TAF_PH_ME_PERSONALISATION_OK                    0
#define TAF_PH_ME_PERSONALISATION_IMST_STR_NOT_EXIST    1
#define TAF_PH_ME_PERSONALISATION_ERROR                 2
#define TAF_PH_ME_PERSONALISATION_WRONG_PARA            3
#define TAF_PH_ME_PERSONALISATION_WRONG_PWD             4
#define TAF_PH_ME_PERSONALISATION_LOCK_PHONE_TO_SIM     5
#define TAF_PH_ME_PERSONALISATION_NO_SIM                6
#define TAF_PH_ME_PERSONALISATION_OP_NOT_ALLOW          7

#define TAF_PH_CARDLOCK_DEFAULT_MAXTIME    10

typedef struct
{
    TAF_OP_ME_PERSONALISATION_RESULT                    OpRslt;                 /*????????????????????*/
    TAF_ME_PERSONALISATION_CMD_TYPE                     CmdType;                /*????????????????????????*/
    TAF_ME_PERSONALISATION_STATUS_FLAG                  ActiveStatus;           /*???????????????????????? */
    TAF_ME_PERSONALISATION_TYPE                         MePersonalisatonType;   /*????????????????*/
    TAF_ME_PERSONALISATION_REPORT_CONTENT_UN            unReportContent;        /*????????????????????????*/
}TAF_PH_ME_PERSONLISATION_CNF_STRU;


typedef struct
{
    TAF_UINT8                           ucLen;
    TAF_UINT8                           ucSW1;
    TAF_UINT8                           ucSW2;
    VOS_UINT8                           aucReserved[1];
    TAF_UINT8                           aucContent[USIMM_T0_APDU_MAX_LEN];
} TAF_PH_RESTRICTED_ACCESS_CNF_STRU;
/*PIN????????????+CPIN,+CPWD,+CLCK*/
/*
????API????????????????????????
TAF_UINT8 ucCmdType, TAF_UINT8 ucPINType, TAF_UINT8 *pucOldPIN, TAF_UINT8 *pucNewPIN
*/

#define TAF_PH_PINCODELENMAX     8
#define TAF_PH_PINCODELENMIN     4
#define TAF_PH_UNLOCKCODELEN     16

#define TAF_SIM_PIN              0      /*PIN1*/
#define TAF_SIM_PUK              1      /*PUK1*/
#define TAF_SIM_PIN2             6      /*PIN2*/
#define TAF_SIM_PUK2             7      /*PUK2*/
/* Modified by L47619 for AP-Modem Personalisation Project, 2012/04/11, begin */
#define TAF_PHSIM_PIN            8      /*PH-SIM PIN*/
#define TAF_PHNET_PIN            9      /*PH-NET PIN*/
#define TAF_PHNET_PUK            10     /*PH-NET PUK*/
#define TAF_PHNETSUB_PIN         11     /*PH-NETSUB PIN*/
#define TAF_PHNETSUB_PUK         12     /*PH-NETSUB PUK*/
#define TAF_PHSP_PIN             13     /*PH-SP PIN*/
#define TAF_PHSP_PUK             14     /*PH-SP PUK*/
/* Modified by L47619 for AP-Modem Personalisation Project, 2012/04/11, end */
#define TAF_SIM_NON              255    /*??????????PIN????????????????*/
typedef TAF_UINT8 TAF_PH_PIN_TYPE;


typedef TAF_UINT8 TAF_PH_PIN_CMD_TYPE;
#define TAF_PIN_VERIFY          0x20   /*????PIN??*/
#define TAF_PIN_CHANGE          0x24   /*????PIN????????*/
#define TAF_PIN_DISABLE         0x26   /*????????PIN??*/
#define TAF_PIN_ENABLE          0x28   /*????PIN??*/
#define TAF_PIN_UNBLOCK         0x2c   /*????????PIN??*/

/*????PIN??????????*/
#define TAF_PIN_QUERY           0x30   /*????PIN??????*/
#define TAF_PIN_RemainTime      0x31
/* Added by L47619 for AP-Modem Personalisation Project, 2012/04/12, begin */
#define TAF_PIN2_QUERY          0x32   /*????PIN2??????*/
/* Added by L47619 for AP-Modem Personalisation Project, 2012/04/12, end */
#define TAF_PIN_CMD_NULL        0x00

typedef struct
{
    TAF_PH_PIN_CMD_TYPE               CmdType;
    TAF_PH_PIN_TYPE                   PinType;
    TAF_UINT8                         aucOldPin[TAF_PH_PINCODELENMAX +1];
    TAF_UINT8                         aucNewPin[TAF_PH_PINCODELENMAX +1];
}TAF_PH_PIN_DATA_STRU;


/*??????????,PIN????????????????????????*/
typedef TAF_UINT8 TAF_PH_USIMM_NEED_TYPE;

#define TAF_PH_USIMM_NONEED     0   /*??????????*/
#define TAF_PH_USIMM_NEED       1   /*????????*/
#define TAF_PH_USIMM_PUK        2   /* need verifer puk */
#define TAF_PH_USIMM_ADM        3   /* puk block */

typedef TAF_UINT8 TAF_PH_USIMM_ENABLE_FLG;
#define TAF_PH_USIMM_ENABLE     1   /*????????*/
#define TAF_PH_USIMM_UNENABLE   0   /*??????*/

/*????USIM????API????????*/
/*??????????PIN????*/
typedef TAF_UINT8   TAF_OP_PIN_RESULT;
#define TAF_PH_OP_PIN_OK    0
#define TAF_PH_PIN_ERROR                    1
#define TAF_PH_QUERY_USIMM_WRONG_PARA       2
#define TAF_PH_QUERY_USIMM_NOAPP            3
#define TAF_PH_QUERY_USIMM_NOINITIAL        4
#define TAF_PH_QUERY_USIMM_ALLOCMEM_FAILED  5
#define TAF_PH_QUERY_USIMM_SENDMSG_FAILED   6
#define TAF_PH_OP_PIN_NEED_PIN1             7
#define TAF_PH_OP_PIN_NEED_PUK1             8
#define TAF_PH_OP_PIN_NEED_PIN2             9
#define TAF_PH_OP_PIN_NEED_PUK2             10
#define TAF_PH_OP_PIN_INCORRECT_PASSWORD    11
#define TAF_PH_OP_PIN_OPERATION_NOT_ALLOW   12
#define TAF_PH_OP_PIN_SIM_FAIL              13


typedef struct
{
    TAF_PH_USIMM_NEED_TYPE              UsimmNeedType;
    TAF_PH_USIMM_ENABLE_FLG             UsimmEnableFlg;
    VOS_UINT8                           aucReserved[2];
}TAF_PH_PIN_QUERY_CNF_STRU;

typedef struct
{
    TAF_UINT8                   ucResult;
}TAF_PH_PIN_OPERATION_CNF_STRU;

typedef struct
{
    TAF_UINT8 ucPin1RemainTime;    /* PIN1?????????? */
    TAF_UINT8 ucPin2RemainTime;    /* PIN2?????????? */
    TAF_UINT8 ucPuk1RemainTime;    /* PUK1?????????? */
    TAF_UINT8 ucPuk2RemainTime;    /* PUK2?????????? */
}TAF_PH_PIN_REMAIN;
/*????????????????????255*/
#define MMA_PIN_REMAINS_UNINIT             255

typedef struct
{
    TAF_OP_PIN_RESULT               OpPinResult;  /*PIN??????????*/
    TAF_PH_PIN_CMD_TYPE             CmdType;      /*??PIN??????????*/
    TAF_PH_PIN_TYPE                 PinType;      /*??????????PIN????*/
    TAF_UINT8                       ucRemain;     /*??PIN????????????*/
    TAF_PH_PIN_QUERY_CNF_STRU       QueryResult;  /*????PIN????????*/
    TAF_PH_PIN_REMAIN               RemainTime;   /*????PIN????????????*/
}TAF_PH_PIN_CNF_STRU;

typedef struct
{
    TAF_OP_PIN_RESULT                   OpPinResult;  /*PIN??????????*/
    TAF_PH_PIN_CMD_TYPE                 CmdType;      /*??PIN??????????*/
    TAF_PH_PIN_TYPE                     PinType;              /*??????????PIN????*/
    TAF_UINT8                           ucPIN1Remain;     /*??PIN????????????*/
    TAF_UINT8                           ucPUK1Remain;
    TAF_UINT8                           ucPIN2Remain;
    TAF_UINT8                           ucPUK2Remain;
    VOS_UINT8                           aucReserved2[1];
    TAF_PH_PIN_QUERY_CNF_STRU           QueryResult;  /*????PIN????????*/
}TAF_PH_PIN_TIMECNF_STRU;


typedef TAF_UINT32   TAF_FPLMN_OPERATE_TYPE;
#define TAF_PH_FPLMN_QUREY      0
#define TAF_PH_FPLMN_DEL_ALL    1
#define TAF_PH_FPLMN_DEL_ONE    2
#define TAF_PH_FPLMN_ADD_ONE    3

typedef struct
{
    TAF_FPLMN_OPERATE_TYPE  ulCmdType;
    TAF_PLMN_ID_STRU        stPlmn;
}TAF_PH_FPLMN_OPERATE_STRU;

/*
USIM??????????
AT????????MMA????USIM??????
??MMA??????????USIM????
*/
/*
0??     USIM??????????
1:      USIM??????????
2??     USIM??CS??????
3??     USIM??PS??????
4??     USIM??PS+CS????????
255??   USIM????????
*/
typedef TAF_UINT8 TAF_USIM_STATUS;
#define TAF_PH_USIM_STATUS_UNAVAIL         0
#define TAF_PH_USIM_STATUS_AVAIL           1


#define TAF_PH_USIM_STATUS_CS_UNVAIL      2
#define TAF_PH_USIM_STATUS_PS_UNVAIL      3
#define TAF_PH_USIM_STATUS_CSPS_UNVAIL    4

#define TAF_PH_USIM_ROMSIM                240
#define TAF_PH_USIM_NON                   255
typedef struct
{
    /* Modified by z00161729 for ????????AT??????????????C??, 2013-4-4, begin */
    /* Added by z40661 for V7R1 phase I , 2011-04-17, begin */
    VOS_UINT8                           aucImsi[NAS_MAX_IMSI_LENGTH];
    VOS_UINT8                           aucReserve[3];
    /* Added by z40661 for V7R1 phase I , 2011-04-17, end */
   /* Modified by z00161729 for ????????AT??????????????C??, 2013-4-4, end */
}TAF_USIM_STATUS_ST;


/*??????????????????????AT????????COPS??*/
typedef TAF_UINT8 TAF_PH_NETWORKNAME_FORMAT;
#define TAF_PH_NETWORKNAME_LONG          0
#define TAF_PH_NETWORKNAME_SHORT         1
#define TAF_PH_NETWORKNAME_NUMBER        2
#define TAF_PH_NETWORKNAME_ALL           4
/*
????????????????????
  0:??????
  1:??????
  2:????????
  3:????
*/
typedef TAF_UINT8 TAF_PH_NETWORK_STATUS_FLAG;
#define TAF_PH_NETWORK_STATUS_UNKNOW       0
#define TAF_PH_NETWORK_STATUS_AVAILIBLE    1
#define TAF_PH_NETWORK_STATUS_CURRENT      2
#define TAF_PH_NETWORK_STATUS_FORBIDDEN    3


typedef TAF_UINT8 TAF_PH_RA_MODE;           /*????????*/
#define TAF_PH_RA_GSM                      0
#define TAF_PH_RA_WCDMA                    1
#define TAF_PH_RA_LTE                      2
#define TAF_PH_RA_MODE_DEFAULT             3
#define TAF_NAMELENGTH_MAX                 32

/* STK???? Access Technology Change Event ?????????? */
#define TAF_STK_ACC_TECH_GSM               0
#define TAF_STK_ACC_TECH_TIA_EIA_553       1
#define TAF_STK_ACC_TECH_TIA_EIA_136       2
#define TAF_STK_ACC_TECH_UTRAN             3
#define TAF_STK_ACC_TECH_TETRA             4
#define TAF_STK_ACC_TECH_TIA_EIA_95        5
#define TAF_STK_ACC_TECH_TIA_EIA_IS_2000   6

/* NV?????????????? */
#define NV_ITEM_DEACTIVE           0
#define NV_ITEM_ACTIVE             1



/*??????????PLMN??????????*/
#define TAF_PH_OPER_NAME_LONG                   (100)
#define TAF_PH_OPER_NAME_SHORT                  (100)
#define TAF_PH_OPER_NAME                        (100)

/*#define TAF_PH_OPER_NAME_PLMN_ID_LENGTH         8*/

#define TAF_PH_MAX_PLMN_ADDITIONAL_INFO_LEN                 (50)

typedef struct
{
    TAF_PLMN_ID_STRU            PlmnId;
    TAF_CHAR                    aucOperatorNameShort[TAF_PH_OPER_NAME_SHORT ];
    TAF_CHAR                    aucOperatorNameLong[TAF_PH_OPER_NAME_LONG ];
}TAF_PH_OPERATOR_NAME_STRU;


typedef TAF_UINT8    TAF_PH_GET_OPERATOR_INFO_OP;
#define TAF_PH_OPER_NAME_PLMN2ALPHANUMERICNAME         0
#define TAF_PH_OPER_NAME_SHORTNAME2OTHERS              1
#define TAF_PH_OPER_NAME_LONGNAME2OTERS                2
#define TAF_PH_OPER_NAME_ERROROP                       3

typedef struct
{
    TAF_PH_OPERATOR_NAME_STRU           OperName;
    TAF_PH_GET_OPERATOR_INFO_OP         ListOp;
    VOS_UINT8                           aucReserved[3];
}TAF_PH_OPERATOR_NAME_FORMAT_OP_STRU;

typedef TAF_UINT8 TAF_PH_PLMN_SEL_MODE;               /*PLMN selection mode     */
#define TAF_PH_PLMN_SEL_MODE_AUTO                   0   /*automatic selection mode*/
#define TAF_PH_PLMN_SEL_MODE_MANUAL                 1   /*manual selection mode   */
#define TAF_PH_PLMN_SEL_MODE_BUTT                   (0xFF)


typedef struct
{
    TAF_PH_OPERATOR_NAME_STRU       Name;
    TAF_PH_NETWORKNAME_FORMAT       NameFormat;  /*??????????????????*/
    TAF_PH_RA_MODE                  RaMode;      /*????????????,3G/2G*/
    TAF_PH_PLMN_SEL_MODE            PlmnSelMode; /*PLMN selection mode*/
    VOS_UINT8                       aucReserved[1];
}TAF_PH_NETWORKNAME_STRU;

typedef struct
{
    TAF_PH_NETWORK_STATUS_FLAG   Status;
    VOS_UINT8                    aucReserved1[3];
    TAF_PLMN_ID_STRU             Plmn;
    TAF_PH_RA_MODE               RaMode;
    VOS_UINT8                    aucReserved2[3];
}TAF_PLMN_INFO_STRU;



/*????band??????MS??RACIEZ??????*/
/*
  80??CM_BAND_PREF_GSM_DCS_1800??              GSM DCS systems
  100??CM_BAND_PREF_GSM_EGSM_900??             Extended GSM 900
  200??CM_BAND_PREF_GSM_PGSM_900??             Primary GSM 900
  100000??CM_BAND_PREF_GSM_RGSM_900??          GSM Railway GSM 900
  200000??CM_BAND_PREF_GSM_PCS_1900??          GSM PCS
  400000??CM_BAND_PREF_WCDMA_I_IMT_2000??      WCDMA IMT 2000
  3FFFFFFF??CM_BAND_PREF_ANY??                 ????????
  40000000??CM_BAND_PREF_NO_CHANGE??           ??????????
*/
typedef struct
{
    TAF_UINT32 ulBandLow; /*??32??*/
    TAF_UINT32 ulBandHigh;/*??32??*/
} TAF_USER_SET_PREF_BAND64;

#if 0
typedef TAF_UINT32 TAF_PH_PREF_BAND;
#endif

#define TAF_PH_BAND_GSM_DCS_1800                             0x00000080
#define TAF_PH_BAND_GSM_EGSM_900                             0x00000100
#define TAF_PH_BAND_GSM_PGSM_900                             0x00000200
#define TAF_PH_BAND_WCDMA_VII_2600                           0x00010000
#define TAF_PH_BAND_WCDMA_VIII_900                           0x00020000
#define TAF_PH_BAND_WCDMA_IX_1700                            0x00040000
#define TAF_PH_BAND_GSM_850                                  0x00080000
#define TAF_PH_BAND_GSM_RGSM_900                             0x00100000
#define TAF_PH_BAND_GSM_PCS_1900                             0x00200000
#define TAF_PH_BAND_WCDMA_I_IMT_2100                         0x00400000
#define TAF_PH_BAND_WCDMA_II_PCS_1900                        0x00800000
#define TAF_PH_BAND_WCDMA_III_1800                           0x01000000
#define TAF_PH_BAND_WCDMA_IV_1700                            0x02000000
#define TAF_PH_BAND_WCDMA_V_850                              0x04000000
#define TAF_PH_BAND_WCDMA_VI_800                             0x08000000
#define TAF_PH_BAND_WCDMA_XI_1500                            0x20000000
/* ??????BAND19?????? */
#define TAF_PH_BAND_WCDMA_XIX_850                            0x10000000
#define TAF_PH_BAND_ANY                                      0x3FFFFFFF
#define TAF_PH_BAND_NO_CHANGE                                0x40000000

#define MN_MMA_LTE_HIGH_BAND_ANY        (0x7FFFFFFF)
#define MN_MMA_LTE_LOW_BAND_ANY         (0xFFFFFFFF)
#define MN_MMA_LTE_EUTRAN_BAND1         (0x1)
#define MN_MMA_LTE_EUTRAN_BAND7         (0x40)
#define MN_MMA_LTE_EUTRAN_BAND13        (0x1000)
#define MN_MMA_LTE_EUTRAN_BAND17        (0x10000)
#define MN_MMA_LTE_EUTRAN_BAND40        (0x80)

#define MN_MMA_LTE_LOW_BAND_ALL         (MN_MMA_LTE_EUTRAN_BAND1 | MN_MMA_LTE_EUTRAN_BAND7 \
                                         | MN_MMA_LTE_EUTRAN_BAND13 | MN_MMA_LTE_EUTRAN_BAND17)

#define MN_MMA_LTE_HIGH_BAND_ALL        (MN_MMA_LTE_EUTRAN_BAND40)


/* ????BAND6,BAND19?????? */
#define TAF_PH_BAND_WCDMA_BAND_ALL           ( TAF_PH_BAND_WCDMA_I_IMT_2100 \
                                              | TAF_PH_BAND_WCDMA_II_PCS_1900 | TAF_PH_BAND_WCDMA_IV_1700 \
                                              | TAF_PH_BAND_WCDMA_V_850 | TAF_PH_BAND_WCDMA_VI_800 \
                                              | TAF_PH_BAND_WCDMA_VIII_900 | TAF_PH_BAND_WCDMA_XI_1500 \
                                              | TAF_PH_BAND_WCDMA_XIX_850)
#define TAF_PH_BAND_GSM_BAND_ALL             ( TAF_PH_BAND_GSM_DCS_1800  | TAF_PH_BAND_GSM_EGSM_900  \
                                               |TAF_PH_BAND_GSM_PGSM_900 | TAF_PH_BAND_GSM_850       \
                                               | TAF_PH_BAND_GSM_PCS_1900 )

#define TAF_PH_BAND_ALL                       (TAF_PH_BAND_WCDMA_BAND_ALL | TAF_PH_BAND_GSM_BAND_ALL)



/*????????SYSCFG=???????????1??????*/

#define TAF_PH_BAND_GSM_900   ( TAF_PH_BAND_GSM_EGSM_900 | TAF_PH_BAND_GSM_PGSM_900 )

/* ??????BAND19?????? */
#define TAF_PH_BAND_GROUP1_FOR_SYSCFG    ( TAF_PH_BAND_WCDMA_I_IMT_2100 | TAF_PH_BAND_WCDMA_VIII_900 \
                                          | TAF_PH_BAND_WCDMA_IX_1700 | TAF_PH_BAND_WCDMA_VI_800     \
                                          | TAF_PH_BAND_GSM_DCS_1800 | TAF_PH_BAND_GSM_EGSM_900      \
                                          | TAF_PH_BAND_GSM_PGSM_900 | TAF_PH_BAND_WCDMA_XI_1500     \
                                          | TAF_PH_BAND_WCDMA_XIX_850 )
/*????????SYSCFG=???????????2??????*/
#define TAF_PH_BAND_GROUP2_FOR_SYSCFG    ( TAF_PH_BAND_WCDMA_II_PCS_1900  \
                                          | TAF_PH_BAND_WCDMA_IV_1700 | TAF_PH_BAND_WCDMA_V_850 \
                                          | TAF_PH_BAND_GSM_PCS_1900 | TAF_PH_BAND_GSM_850 )

/* ??????64????32???????????? */
#define TAF_PH_BAND_NEED_CHANGE_TO_64BIT    ( TAF_PH_BAND_WCDMA_VIII_900 | TAF_PH_BAND_WCDMA_IX_1700 | TAF_PH_BAND_WCDMA_XI_1500 | TAF_PH_BAND_WCDMA_XIX_850)

/*lint -e958 -e959 ??????:l60609;????:64bit*/
typedef struct
{
     VOS_UINT32                                   BandMask;             /*????????*/
     TAF_CHAR*                                    BandStr;              /*??????????*/
}TAF_PH_BAND_NAME_STRU;
/*lint +e958 +e959 ??????:l60609;????:64bit*/

#define TAF_DEVICE_AT_MAX_W_BAND_NUM   9  /*????????????????W??????????*/

/*????????????0??1??????????????????????2??*/
/*****************************************************************************
 ??????    : MN_MMA_ROAM_MODE_ENUM
 ????????  : ????????????????????????????
 1.??    ??  : 2011??07??15??
   ??    ??  : z00161729
   ????????  : ????????
 2.??    ??   : 2015??4??15??
   ??    ??   : h00313353
   ????????   : SysCfg????
*****************************************************************************/
enum TAF_MMA_ROAM_MODE_ENUM
{
    TAF_MMA_ROAM_NATIONAL_ON_INTERNATIONAL_ON,                                   /* ???????????????? */
    TAF_MMA_ROAM_NATIONAL_ON_INTERNATIONAL_OFF,                                  /* ?????????????????????????? */
    TAF_MMA_ROAM_NATIONAL_OFF_INTERNATIONAL_ON,                                  /* ?????????????????????????? */
    TAF_MMA_ROAM_NATIONAL_OFF_INTERNATIONAL_OFF,                                 /* ???????????????? */
    TAF_MMA_ROAM_UNCHANGE,                                                       /* ?????????????? */

    TAF_MMA_ROAM_BUTT
};
typedef VOS_UINT8 TAF_MMA_ROAM_MODE_ENUM_UINT8;

/*????????*/
typedef TAF_UINT8 TAF_PH_ROAM_STA;
#define TAF_PH_ROAMING               0
#define TAF_PH_NO_ROAM               1
#define TAF_PH_ROAM_UNKNOW           2

/* Add by w00199382 for V7????????, 2012-04-07, Begin   */
#if(FEATURE_ON == FEATURE_LTE)

#define TAF_PH_DOMESTIC_5776        1
#define TAF_PH_FOREIGN_5776         2
#define TAF_PH_ROAM_UNKNOW_5776     0
typedef struct
{
    TAF_PH_RA_MODE                  RaMode;                                     /*????????????,3G/2G*/
    TAF_PH_ROAM_STA                 RoamMode;                                   /*ROAM mode*/
}TAF_PH_CELLROAM_STRU;

#endif

/* Add by w00199382 for V7????????, 2012-04-07, End   */


/*------------    ????????????     ------------*/
/*??????????????????*/
/*
  0??    ??????
  1??    ??CS????
  2??    ??PS????
  3??    PS+CS????
  4??    CS??PS????????????????????????
*/
typedef TAF_UINT8 TAF_PH_DOMAIN_FLAG;

typedef struct
{
     VOS_UINT32                         ulBand;              /*????????*/
     TAF_PH_DOMAIN_FLAG                 DomainFlag;           /*??????????*/
     TAF_MMA_ROAM_MODE_ENUM_UINT8       enRoamMode;          /*????????*/
     /*????,??????,????????????????*/
     TAF_PH_ROAM_STA                    RoamSta;
     VOS_UINT8                          aucReserved[1];
}TAF_PH_SYSTEM_MODE_STRU;


#define TAF_SPDI_PLMN_LIST_IEI          (0x80)


typedef TAF_UINT8 TAF_PH_SPN_DISP_MODE;

typedef TAF_UINT8 TAF_PH_SPN_CODING;
#define TAF_PH_GSM_7BIT_DEFAULT       0
#define TAF_PH_RAW_MODE               1
#define TAF_PH_SPN_CODING_UNKNOW      255


/*????????????TAF_SDC_MAX_OPER_NAME_NUM ??????????????*/
#define TAF_PH_SPN_NAME_MAXLEN        100

/*??????AT????????SPN????????*/
typedef struct
{
    TAF_PH_SPN_DISP_MODE              ucDispRplmnMode;
    TAF_UINT8                         ucLength;
    TAF_UINT8                         ucCoding;
    TAF_UINT8                         ucSpareBit;
    TAF_UINT8                         aucSpnName[TAF_PH_SPN_NAME_MAXLEN];
}TAF_PH_USIM_SPN_STRU;

/*USIM??SPN????????*/
typedef struct
{
    TAF_UINT8         ucDispRplmnMode;
    TAF_UINT8         aucSpnName[TAF_PH_SPN_NAME_MAXLEN];
}TAF_PH_USIM_SPN_CNF_STRU;

/* ??????????????SPN???? */
typedef struct
{
    TAF_PH_SPN_DISP_MODE                DispRplmnMode;
    TAF_PH_ROAM_STA                     PhRoam;
    TAF_UINT8                           aucSpnName[TAF_PH_SPN_NAME_MAXLEN];
    VOS_UINT8                           aucReserved[2];
}TAF_PH_SPN_INFO_STRU;

#define FULL_NAME_IEI       0x43
#define SHORT_NAME_IEI      0x45
#define PLMN_ADDITIONAL_INFO_IEI      0x80

typedef struct
{
    VOS_BOOL                            bCPHSOperNameValid;
    VOS_UINT8                           aucCPHSOperNameStr[TAF_PH_OPER_NAME_LONG + 1];
    VOS_UINT8                           aucReserved[3];
}TAF_PH_SIM_CPHS_OPER_NAME_STRU;

/*****************************************************************************
 ??????    : TAF_PH_OPER_NAME_STRU
 ????????  : ??????????????
 1.??    ??   : 2015??3??29??
   ??    ??   : b00269685
   ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           bitExt    : 1;
    VOS_UINT8                           bitCoding : 3;    /* ???????? */
    VOS_UINT8                           bitAddCi  : 1;
    VOS_UINT8                           bitSpare  : 3;    /* spare bit */
    VOS_UINT8                           ucLength;         /* ?????????????? */
    VOS_UINT8                           aucReserved[2];
    VOS_UINT8                           aucOperatorName[TAF_PH_OPER_NAME];/* ???????????? */
} TAF_PH_OPER_NAME_STRU;

typedef struct
{
    TAF_PH_OPER_NAME_STRU               stOperNameLong;
    TAF_PH_OPER_NAME_STRU               stOperNameShort;
    VOS_UINT8                           ucPlmnAdditionalInfoLen;       /*PLMN Additional Information ???? */
    VOS_UINT8                           aucPlmnAdditionalInfo[TAF_PH_MAX_PLMN_ADDITIONAL_INFO_LEN]; /*PLMN Additional Information ????,??????V */
    VOS_UINT8                           aucReserve[1];
} TAF_PH_USIM_PNN_RECORD;

typedef TAF_UINT8 TAF_PH_ICC_TYPE;
#define TAF_PH_ICC_UNKNOW   0
#define TAF_PH_ICC_SIM      1
#define TAF_PH_ICC_USIM     2

typedef struct
{
    TAF_UINT32              CardType;
    TAF_UINT32              TotalRecordNum;
    VOS_UINT16              usPnnCurrIndex; /* ????PNN?????????? */
    TAF_PH_ICC_TYPE         Icctype;
    VOS_UINT8               aucReserve[1];
    TAF_PH_USIM_PNN_RECORD  PNNRecord[1];
}TAF_PH_USIM_PNN_CNF_STRU;

typedef struct
{
    TAF_UINT16              PlmnLen;
    TAF_UINT8               PLMN[6];
    TAF_UINT16              LACLow;
    TAF_UINT16              LACHigh;
    TAF_UINT16              PNNIndex;
    VOS_UINT8               aucReserved[2];
}TAF_PH_USIM_OPL_RECORD;

typedef struct
{
    TAF_UINT32              CardType;
    TAF_UINT32              TotalRecordNum;
    VOS_CHAR                cWildCard;
    VOS_UINT8               aucReserved[3];
    TAF_PH_USIM_OPL_RECORD  OPLRecord[1];
}TAF_PH_USIM_OPL_CNF_STRU;

typedef struct
{
    TAF_PH_USIM_PNN_CNF_STRU *pstPnnCnf;
    TAF_PH_USIM_OPL_CNF_STRU *pstOplCnf;
}TAF_PH_USIM_CPNN_CNF_STRU;


/*????????*/
#define TAFMMA_CELL_MAX_NUM    8
typedef struct
{
    TAF_UINT8                           ucCellNum;
    VOS_UINT8                           aucReserved[3];
    TAF_UINT32                          aulCellId[TAFMMA_CELL_MAX_NUM];
}TAF_CELL_INFO_STRU;

typedef struct
{
    TAF_UINT32                          OP_CsRegState      : 1;
    TAF_UINT32                          OP_PsRegState      : 1;
    TAF_UINT32                          OP_ucAct           : 1;
    TAF_UINT32                          OP_Lac             : 1;
    TAF_UINT32                          OP_CellId          : 1;
    TAF_UINT32                          OP_Rac             : 1;
    TAF_UINT32                          OP_Plmn            : 1;
    TAF_UINT32                          OP_Spare           : 25;

    TAF_PH_REG_STATE_TYPE               RegState;               /*MM????????*/
    TAF_PH_REG_STATE_TYPE               ucPsRegState;           /*PS????????*/
    TAF_PH_ACCESS_TECH_ENUM_UINT8       ucAct;                  /*??????????????????????*/
    TAF_UINT8                           ucRac;                  /*RAC*/
    TAF_UINT16                          usLac;                  /*??????????*/
    VOS_UINT8                           ucRatType;
    VOS_UINT8                           aucReserved[1];
    TAF_CELL_INFO_STRU                  CellId;                 /*????ID*/
    TAF_PLMN_ID_STRU                    Plmn;                   /*????PLMN??????????????????*/
}TAF_PH_REG_STATE_STRU;

/*??????????????NVIM??????*/
typedef struct
{
    TAF_PH_IMEI_STRU                ImeisV;                 /*IMEISV*/
    TAF_PH_FMR_ID_STRU              FmrId;                  /*????????????????*/
    TAF_PH_PRODUCT_NAME_STRU        ProductName;            /*????????*/
    TAF_PH_MODEL_ID_STRU            ModelId;                /*????????????????*/
    TAF_PH_REVISION_ID_STRU         SoftVersion;            /*??????????????*/
    TAF_PH_RELEASE_DATE_STRU        ReleaseDate;            /*????????*/
    TAF_PH_RELEASE_TIME_STRU        ReleaseTime;            /*????????*/
    TAF_PH_COMPCAPLIST_STRU         CompleteCapitiyList;    /*????????????*/
    TAF_PH_COMPCAPLIST_STRU         GsmCompleteCapitiyList; /*????????????*/
}TAF_PH_MEINFO_STRU;

#define TAF_PH_SYSCFG_GROUP_BAND_LEN                256

typedef struct
{
    TAF_CHAR  strSysCfgBandGroup[TAF_PH_SYSCFG_GROUP_BAND_LEN];

}TAF_PH_SYSCFG_BAND_STR;


typedef struct
{
    TAF_PH_PRODUCT_NAME_STRU        ProductName;            /*??????????*/
    TAF_PH_FMR_ID_STRU              FmrId;                  /*????????????????*/
    TAF_PH_PORT_INFO_STRU           PortId;                 /*??????????????????*/
}TAF_PH_PORT_STRU;

/*????????????????USIM????????USIM??????????????????????*/
typedef struct
{
    TAF_USIM_STATUS_ST                UsimStatus;                               /*USIM????*/
}TAF_USIM_INFO_STRU;


/*Taf_PhoneNetworkOperate*/
typedef TAF_UINT8 TAF_AVAIL_PLMN_LIST_TYPE;
#define TAF_PLMN_LIST        0       /*????????PLMN????*/
#define TAF_PLMN_LIST_ABORT  1       /*????????PLMN????*/


typedef TAF_UINT8 TAF_PLMN_RESEL_MODE_TYPE;
#define TAF_PLMN_RESELETION_AUTO        0     /*PLMN??????????*/
#define TAF_PLMN_RESELETION_MANUAL      1     /*PLMN??????????*/

typedef struct
{
    TAF_PH_NETWORK_STATUS_FLAG          PlmnStatus;
    TAF_PH_RA_MODE                      RaMode;      /*????????????,3G/2G*/
    VOS_UINT8                           aucReserved[2];
}TAF_PLMN_STATUS_STRU;

typedef TAF_UINT8 AT_COPS_FORMAT_TYPE;
#define AT_COPS_LONG_ALPH_TYPE            0
#define AT_COPS_SHORT_ALPH_TYPE           1
#define AT_COPS_NUMERIC_TYPE              2

/*****************************************************************************
 ??????    : TAF_PLMN_USER_SEL_STRU
 ????????  : AT??MMA AT+COPS????????????????????

  ????????      :
  1.??    ??   : 2011??10??18??
    ??    ??   : c00173809
    ????????   : ??????????
*****************************************************************************/
typedef struct
{
    AT_COPS_FORMAT_TYPE         ucFormatType;
    TAF_MMA_RAT_TYPE_ENUM_UINT8 enAccessMode;
    VOS_UINT16                  usOperNameLen;
    VOS_CHAR                    ucOperName[TAF_PH_OPER_NAME_LONG];
}TAF_PLMN_USER_SEL_STRU;

/*****************************************************************************
 ??????    : TAF_PLMN_NAME_LIST_STRU
 ????????  : PLMN????????????????????????????????????????

  ????????      :
  1.??    ??   : 2011??10??21??
    ??    ??   : c00173809
    ????????   : ??????????
*****************************************************************************/
/*????????PLMN NAME??????????????100??????????????????????????????4K????????????????????PLMN NAME*/
#define TAF_MMA_MAX_PLMN_NAME_LIST_NUM   12
typedef struct
{
    TAF_UINT32                          ulPlmnNum;
    VOS_BOOL                            bPlmnSelFlg;
    TAF_PH_OPERATOR_NAME_STRU           astPlmnName[TAF_MMA_MAX_PLMN_NAME_LIST_NUM];
    TAF_MMC_USIM_RAT                    ausPlmnRat[TAF_MMA_MAX_PLMN_NAME_LIST_NUM];
}TAF_PLMN_NAME_LIST_STRU;


#define TAF_MAX_PLMN_NUM       37
typedef struct
{
    TAF_UINT8                           ucPlmnNum;
    VOS_UINT8                           aucReserved[3];
    TAF_PLMN_ID_STRU                    Plmn[TAF_MAX_PLMN_NUM];
    TAF_PLMN_STATUS_STRU                PlmnInfo[TAF_MAX_PLMN_NUM];
}TAF_PLMN_LIST_STRU;

/*   ??MMC_MAX_OPLMN_NUM  NAS_MMC_MAX_UPLMN_NUM MMC_MAX_SELPLMN_NUM
     MMC_MAX_HPLMN_WITH_ACT_NUM                           ?????????? */
#define TAF_USER_MAX_PLMN_NUM        256
typedef struct
{
    TAF_UINT16           usPlmnNum;
    TAF_UINT8            aucReserved[2];
    TAF_PLMN_ID_STRU     Plmn[TAF_USER_MAX_PLMN_NUM];
    TAF_MMC_USIM_RAT     PlmnRat[TAF_USER_MAX_PLMN_NUM];
}TAF_USER_PLMN_LIST_STRU;

typedef struct
{
    TAF_UINT8                           ucIndex;
    VOS_UINT8                           aucReserved1[3];
    TAF_PLMN_ID_STRU                    Plmn;
    MN_MMA_CPAM_RAT_TYPE_ENUM_UINT8     PlmnRat;
    VOS_UINT8                           aucReserved2[3];
}TAF_USER_PLMN_INFO_STRU;



typedef struct
{
    TAF_UINT8                           ucLen;
    VOS_UINT8                           aucReserved[3];
    TAF_UINT8                           aucCommand[USIMM_T0_APDU_MAX_LEN];
}TAF_PH_USIM_COMMAND_STRU;


/* ucActionType?????? */
#define TAF_START_EVENT_INFO_FOREVER    0   /* ???????????????? */
#define TAF_START_EVENT_INFO_ONCE       1   /* ???????????????? */
#define TAF_START_EVENT_INFO_STOP       2   /* ???????????? */

/* ucMsgType?????? */
#define TAF_EVENT_INFO_CELL_SIGN        1   /* ???????????????????? */
#define TAF_EVENT_INFO_CELL_ID          2   /* ????????????ID */
#define TAF_EVENT_INFO_CELL_BLER        4   /* ?????????????????? */

/* ???????????????????????????? */
typedef struct
{
    TAF_UINT8              ucActionType;
    TAF_UINT8              ucRrcMsgType;

    VOS_UINT8              ucSignThreshold;    /* 1:rssi????????1db????????^cerssi; 2:rssi????????2db????????
                                        3:rssi????????3db??????????4:rssi????????4db??????????5:rssi????????5db????????;*/
    VOS_UINT8              ucMinRptTimerInterval;   /*??????????????(1-20)S*/
}TAF_START_INFO_IND_STRU;


typedef struct
{
    TAF_UINT16    usHighFreq;
    TAF_UINT16    usLowFreq;
}TAF_PH_FREQ_INFO_STRU;

/*??????????????*/
typedef struct
{
    TAF_UINT32              ulGsmFreq;
    TAF_PH_FREQ_INFO_STRU   WcdmaFrq;
}TAF_PH_FRQ_STRU;

#define TAF_PH_ICC_ID_MAX 10
typedef struct
{
    TAF_UINT8 ucLen;
    TAF_UINT8 aucIccId[TAF_PH_ICC_ID_MAX + 1];
}TAF_PH_ICC_ID_STRU;

/*    ucSrvStatus?????????? */
#define  TAF_PH_INFO_NO_SERV            0/*??????*/
#define  TAF_PH_INFO_LIMT_SERV          1/*??????????*/
#define  TAF_PH_INFO_NOMRL_SERV         2/*????????*/
#define  TAF_PH_INFO_LIMT_REGON_SERV    3/*????????????????*/
#define  TAF_PH_INFO_DEEP_SLEEP         4/*??????????????*/
/*    ucSrvDomain??????????*/
#define  TAF_PH_INFO_NO_DOMAIN          0/*??????*/
#define  TAF_PH_INFO_ONLY_CS            1/*??CS????*/
#define  TAF_PH_INFO_ONLY_PS            2/*??PS????*/
#define  TAF_PH_INFO_DUAL_DOMAIN        3/*PS+CS????*/
#define  TAF_PH_INFO_SEARCH_DOMAIN      4/*CS??PS????????????????????????  */
/*    ucRoamStatus??????????*/
#define  TAF_PH_INFO_NONE_ROMAING       0/*??????????*/
#define  TAF_PH_INFO_ROMAING            1/*????????*/
#define  TAF_PH_INFO_ROAM_UNKNOW        2/*????????*/

typedef TAF_UINT8 TAF_PH_INFO_RAT_TYPE;
/*ucSysMode??????????*/
/*****************************************************************************
 ??????    : TAF_SYS_MODE_ENUM
 ????????  : ??????????????????????
 1.??    ??   : 2015??11??17??
   ??    ??   : zwx247453
   ????????   : dallas gps????????????????
*****************************************************************************/
enum TAF_SYS_MODE_ENUM
{
    TAF_PH_INFO_NONE_RAT                = 0,        /*??????*/
    TAF_PH_INFO_CDMA_1X_RAT             = 2,        /*CDMA 1X????*/
    TAF_PH_INFO_GSM_RAT                 = 3,        /*GSM/GPRS????*/
    TAF_PH_INFO_HRPD_RAT                = 4,        /*HRPD ????*/
    TAF_PH_INFO_WCDMA_RAT               = 5,        /*WCDMA????*/
    TAF_PH_INFO_LTE_RAT                 = 7,        /*LTE????*/
    TAF_PH_INFO_HYBRID_RAT              = 8,        /*HRPD ????????*/
    TAF_PH_INFO_TD_SCDMA_RAT            = 15,       /*TD-SCDMA????*/
    TAF_PH_INFO_SVLTE_SRLTE_RAT         = 16,       /*SVLTE/SRLTE????*/
};
typedef VOS_UINT8 TAF_SYS_MODE_ENUM_UINT8;

/*    ucSimStatus???????? */
#define  TAF_PH_INFO_USIM_PIN_INVAILD   0/*USIM??????????????PIN????????????????*/
#define  TAF_PH_INFO_USIM_VAILD         1/*USIM??????????*/
#define  TAF_PH_INFO_USIM_CS_INVAILD    2/*USIM??CS??????*/
#define  TAF_PH_INFO_USIM_PS_INVAILD    3/*USIM??PS??????*/
#define  TAF_PH_INFO_USIM_INVAILD       4/*USIM??PS+CS????????*/
#define  TAF_PH_INFO_USIM_ABSENT        255/*USIM????????*/

typedef struct
{
    TAF_UINT8                           ucSrvStatus;        /*????????????????????0,1,2*/
    TAF_UINT8                           ucSrvDomain;        /*??????*/
    TAF_UINT8                           ucRoamStatus;       /*????????????????PLMN ID????????*/
    TAF_UINT8                           ucSysMode;          /*????????*/
    TAF_UINT8                           ucSimStatus;        /*SIM??????*/
    TAF_UINT8                           ucSysSubMode;       /*??????????*/
    TAF_UINT8                           ucSimLockStatus;    /*SIM????LOCK????*/
    VOS_UINT8                           aucReserved[1];
}TAF_PH_SYSINFO_STRU;

typedef struct
{
    TAF_UINT8            RatType;
    TAF_UINT8            GsmBand;
    TAF_UINT16           IndFreq;
}TAF_IND_FREQ_STRU;

#define TAF_MAX_USIM_RSP_LEN    255
typedef struct
{
    TAF_UINT8  ucLen;
    TAF_UINT8  aucResponse[TAF_MAX_USIM_RSP_LEN];
}TAF_PH_USIM_RESPONSE_STRU;

/* ???????????????? */
typedef struct
{
    TAF_PH_CMD_TYPE                     CmdType;
    MN_MMA_CPAM_RAT_TYPE_ENUM_UINT8     AccessMode;
    TAF_PH_PLMN_PRIO                    PlmnPrio;
    TAF_MMA_ROAM_MODE_ENUM_UINT8        enRoam;
    VOS_UINT32                          ulBand;
    TAF_MMA_SERVICE_DOMAIN_ENUM_UINT8   enSrvDomain;
    VOS_UINT8                           aucReserved[3];
    TAF_USER_SET_PREF_BAND64            stOrigUserSetBand;
}TAF_PH_SYS_CFG_STRU;

/*****************************************************************************
??????    : TAF_MMA_CELL_AC_INFO_STRU
????????  : ????????????????????

1.??    ??: 2012??12??10??
  ??    ??: W00176964
  ????????: ????
*******************************************************************************/
typedef struct
{
    TAF_MMA_SERVICE_DOMAIN_ENUM_UINT8           enSrvDomain; /* ?????? 0:CS,1:ps */
    TAF_MMA_CELL_RESTRICTION_TYPE_ENUM_UINT8    enCellAcType;                                   /* ???????????? */
    VOS_UINT8                                   ucRestrictRegister;                             /* ???????????? */
    VOS_UINT8                                   ucRestrictPagingRsp;                            /* ???????????????? */
}TAF_MMA_CELL_AC_INFO_STRU;
typedef TAF_UINT8 TAF_PH_PIN_STATUS;
#define TAF_PH_PIN_ENABLE   0
#define TAF_PH_PIN_DISABLE  1

typedef TAF_UINT8 TAF_PH_PIN_VERIFY_STATUS;
#define TAF_PH_PIN_NEED     0
#define TAF_PH_PIN_NONEED   1
#define TAF_PH_PIN_PUK      2
typedef TAF_UINT8 TAF_PH_ME_LOCK_STATUS;
#define TAF_PH_ME_SIM_UNLOCK    0
#define TAF_PH_ME_SIM_LOCK      1
#define TAF_PH_ME_NO_SIM        2

typedef struct
{
    TAF_PH_ICC_TYPE           MmaIccType;
    TAF_PH_PIN_STATUS         MmaIccPinStatus;
    TAF_PH_PIN_VERIFY_STATUS  MmaIccPinVerifyStatus;
    TAF_UINT8                 ucRemainTimes;
}TAF_PH_UICC_TYPE;

enum MN_PH_PREF_PLMN_TYPE_ENUM
{
    MN_PH_PREF_PLMN_UPLMN,
    MN_PH_PREF_PLMN_OPLMN,
    MN_PH_PREF_PLMN_HPLMN
};
typedef VOS_UINT8 MN_PH_PREF_PLMN_TYPE_ENUM_U8;

typedef enum
{
    MN_PH_PrefPLMN_QUREY,
    MN_PH_PrefPLMN_DEL_ONE,
    MN_PH_PrefPLMN_ADD_ONE,
    MN_PH_PrefPLMN_MODIFY_ONE
} MN_PH_PrefPLMN_OPERATE_TYPE;
typedef VOS_UINT8 MN_PH_PrefPLMN_OPERATE_TYPE_U8;

typedef struct
{
    MN_PH_PREF_PLMN_TYPE_ENUM_U8        enPrefPLMNType;
    MN_PH_PrefPLMN_OPERATE_TYPE_U8      enPrefPlmnOperType;
    TAF_MMC_USIM_RAT                    usRat;                                  /* USIM?????? ???????? */
    VOS_UINT32                          ulIndex;
    TAF_PLMN_ID_STRU                    stPlmn;
} TAF_PH_PREF_PLMN_OPERATE_STRU;

/*****************************************************************************
 ??????    : TAF_PH_SET_PREFPLMN_STRU
 ????????  : AT??MMA AT+CPOL????????????

 1.??    ?? : 2011??10??24??
   ??    ?? : c00173809
   ???????? : ????????
 2.??    ??   : 2011??12??5??
   ??    ??   : w00176964
   ????????   : V7R1 PhaseIV????:AT+CPOL??????????????LTE??????????
*****************************************************************************/
typedef struct
{
    MN_PH_PREF_PLMN_TYPE_ENUM_U8        enPrefPlmnType;                     /* ????????????????????????*/
    VOS_UINT8                           ucAtParaIndex;                      /* ???????? */
    VOS_UINT16                          usIndexLen;                         /* ??????????????*/
    VOS_UINT16                          usFormatLen;                        /* ????????????????*/
    VOS_UINT16                          usOperNameLen;                      /* ????????????????*/
    VOS_UINT16                          usGsmRatLen;                        /* GSM??????????????*/
    VOS_UINT16                          usGsmCompactRatLen;                 /* GSM COMPACT??????????????*/
    VOS_UINT16                          usUtrnLen;                          /* UTRN?????????????? */
    VOS_UINT16                          usReserve;                          /* ????????*/
    VOS_UINT32                          usIndex;                            /* ??????*/
    VOS_UINT32                          usFormat;                           /* ??????????*/
    VOS_CHAR                            ucOperName[TAF_PH_OPER_NAME_LONG];  /* ????????*/
    VOS_UINT32                          usGsmRat;                           /* GSM??????????*/
    VOS_UINT32                          usGsmCompactRat;                    /* GSM COMPACK??????????*/
    VOS_UINT32                          usUtrn;                             /* UTRN??????????*/
    VOS_UINT16                          usEutrnLen;                         /* E-UTRN?????????????? */
    VOS_UINT8                           aucReserved[2];
    VOS_UINT32                          usEutrn;                            /* E-UTRN??????????*/
} TAF_PH_SET_PREFPLMN_STRU;

/*****************************************************************************
 ??????    : MN_PH_SET_CPIN_REQ_STRU
 ????????  : AT??MMA AT^cpin????????????

 1.??    ?? : 2011??11??4??
   ??    ?? : c00173809
   ???????? : ????????

 2.??    ?? : 2012??04??21??
   ??    ?? : l00198894
   ???????? : AP-Modem????????????????????????
*****************************************************************************/
typedef struct
{
    VOS_UINT8   aucPara0[TAF_PH_UNLOCKCODELEN];         /* ?????????????????????????? */
    VOS_UINT16  usPara0Len;                             /* ?????????????????????? */
    VOS_UINT8   aucPara1[TAF_PH_PINCODELENMAX];         /* ?????????????????????????? */
    VOS_UINT16  usPara1Len;                             /* ?????????????????????? */
}MN_PH_SET_CPIN_REQ_STRU;

typedef enum
{
    TAF_PH_PNN_FILE,
    TAF_PH_OPL_FILE,
    TAF_PH_MAX_FILE
}TAF_PH_USIM_FILE_ENUM;
typedef VOS_UINT16 TAF_PH_USIM_FILE_ENUM_U16;

#define TAF_PH_INVALID_USIM_REC             0xFFFFFFFFU

/*****************************************************************************
??????    : TAF_MMA_PNN_INFO_QUERY_REQ_INDEX_STRU
????????  : AT^PNN????????????????????????????????????????????????10??

  1.??    ??   : 2013??09??05??
    ??    ??   : l00208543
    ????????   : DTS2013090309526
*******************************************************************************/
typedef struct
{
    VOS_UINT16                          usPnnCurrIndex; /* ????PNN?????????? */
    VOS_UINT16                          usPnnNum;       /* ????PNN????????????A????C????????????????????????????????????????10?????? */
}TAF_MMA_PNN_INFO_QUERY_REQ_INDEX_STRU;

typedef struct
{
    TAF_PH_ICC_TYPE                     Icctype;
    VOS_UINT8                           ucReserved;
    TAF_PH_USIM_FILE_ENUM_U16           enEfId;
    TAF_UINT32                          ulRecNum;
    TAF_MMA_PNN_INFO_QUERY_REQ_INDEX_STRU stPnnQryIndex;
}TAF_PH_QRY_USIM_INFO_STRU;

typedef struct
{
    TAF_PH_ICC_TYPE                     Icctype;
    VOS_UINT8                           aucReserved[3];
    VOS_BOOL                            bFileExist;
    TAF_UINT32                          ulTotalRecNum;
    TAF_UINT32                          ulRecordLen;
}TAF_PH_USIM_INFO_STRU;

typedef struct
{
    TAF_PH_USIM_INFO_STRU               stUsimInfo;
    TAF_PH_USIM_INFO_STRU               stSimInfo;
}TAF_PH_QRY_USIM_RANGE_INFO_STRU;

typedef TAF_UINT8 TAF_PH_ICC_STATUS;
#define TAF_PH_ICC_INVALID      0
#define TAF_PH_ICC_VALID        1
#define TAF_PH_ICC_CSINVALID    2
#define TAF_PH_ICC_PSINVALID    3
#define TAF_PH_ICC_CSPSINVALID  4
#define TAF_PH_ICC_NOTEXIT      255

/*PHONE????????*/
typedef TAF_UINT8 TAF_PHONE_EVENT;
#define TAF_PH_EVT_ERR                      0   /*????????????*/
#define TAF_PH_EVT_PLMN_LIST_ABORT_CNF      1   /*????????PLMN????????????????*/
#define TAF_PH_EVT_PLMN_LIST_IND            2   /*PLMN????????????????*/
#define TAF_PH_EVT_OPER_MODE_CNF            3  /* ???????? */
#define TAF_PH_EVT_SYS_CFG_CNF              4  /* ???????? */
#define TAF_PH_EVT_PLMN_LIST_CNF            5   /*APP????????PLMN????????????*/
#define TAF_PH_EVT_PLMN_LIST_REJ            6   /*????????????PLMN????????*/
#define TAF_PH_EVT_PLMN_SEL_CNF             7   /*APP????PLMN????????????*/
#define TAF_PH_EVT_PLMN_RESEL_CNF           8   /*APP??????PLMN????????????*/
#define TAF_PH_EVT_SERVICE_STATUS_IND       9   /*??????????????????????*/

#define TAF_PH_EVT_POWER_STA_IND            17  /*????????????*/
#define TAF_PH_EVT_OP_PIN_CNF               18  /*????PIN??????????*/
#define TAF_PH_EVT_SETUP_SYSTEM_INFO_RSP    20  /*????????????????????*/
#define TAF_PH_EVT_USIM_RESPONSE            21  /*????????USIM*/
#define TAF_PH_EVT_USIM_INFO_IND            22  /*??????????????*/
#define TAF_PH_EVT_OP_PINREMAIN_CNF         23
#define TAF_PH_EVT_ME_PERSONALISATION_CNF   24  /*????????????????????????*/
#define TAF_PH_EVT_RESTRICTED_ACCESS_CNF    25  /*????????SIM??????????????*/
#define TAF_PH_EVT_OPER_MODE_IND            26  /* ???????????????????? */


#define MN_PH_EVT_SIMLOCKED_IND             29  /* SIMLOCK???? */
#define MN_PH_EVT_ROAMING_IND               30  /* ROAMING???? */
#define TAF_PH_EVT_GET_CURRENT_ATTACH_STATUS_CNF  31 /*????????????????????????*/

/* Added by L60609 for V7R1C50 AT&T&DCM, 2012-6-13, begin */
/* MMA??AT??????????????????+PACSP1????+PACSP0*/
#define TAF_PH_EVT_NSM_STATUS_IND           (37)
/* Added by L60609 for V7R1C50 AT&T&DCM, 2012-6-13, end */


/* Added by w00176964 for VoLTE_PhaseI????, 2013-8-1, begin */
#define TAF_MMA_EVT_PS_INIT_RESULT_IND        (45)  /* ???????????????????????? */
/* Added by w00176964 for VoLTE_PhaseI????, 2013-8-1, end */

#define TAF_PH_MAX_GUL_RAT_NUM                              (3)                 /*AT^syscfgex??acqorder?????????????????? */
#define TAF_PH_MAX_GU_RAT_NUM                               (2)                 /*AT^syscfgex??acqorder?????????????????? */
#define TAF_PH_MAX_LU_RAT_NUM                               (2)                 /*AT^syscfgex??acqorder?????????????????? */


/*****************************************************************************
 ??????    : TAF_PH_RAT_STRU
 ????????  : AT^syscfgex????????acqorder??????????????
 1.??    ?? : 2011??06??9??
   ??    ?? : l00130025
   ???????? : ????????
 2.??    ?? : 2015??4??16??
   ??    ?? : y00245242
   ???????? : iteration 13????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRatOrderNum;                          /* syscfgex????????acqoder???????????? */
    TAF_MMA_RAT_TYPE_ENUM_UINT8         aenRatOrder[TAF_PH_MAX_GUL_RAT_NUM];    /* at^syscfgex????????acqoder?????? */
}TAF_MMA_RAT_ORDER_STRU;


/*****************************************************************************
 ??????    : TAF_PH_USER_SET_PRIO_RAT_ENUM
 ????????  : ????????????????????,??????????????????????,????????????????
              G??????W????,????????
 1.??    ??  : 2012??04??20??
   ??    ??  : z40661
   ????????  : ????????
*****************************************************************************/
enum TAF_MMA_USER_SET_PRIO_RAT_ENUM
{
    TAF_MMA_USER_SET_PRIO_AUTO,
    TAF_MMA_USER_SET_PRIO_GSM_PREFER,
    TAF_MMA_USER_SET_PRIO_WCDMA_PREFER,
    TAF_MMA_USER_SET_PRIO_NOCHANGE,
    TAF_MMA_USER_SET_PRIO_BUTT
};
typedef VOS_UINT8 TAF_MMA_USER_SET_PRIO_RAT_ENUM_U8;


/*****************************************************************************
 ??????    : TAF_PH_USER_SET_RAT_TYPE_ENUM_U8
 ????????  : ??????????????????,??????NVIM??
 1.??    ??  : 2012??04??20??
   ??    ??  : z40661
   ????????  : ????????
*****************************************************************************/
enum TAF_PH_USER_SET_RAT_TYPE_ENUM
{
    TAF_PH_USER_SET_RAT_WCDMA,
    TAF_PH_USER_SET_RAT_WCDMA_GSM,
    TAF_PH_USER_SET_RAT_GSM,
    TAF_PH_USER_SET_RAT_BUTT
};
typedef VOS_UINT8 TAF_PH_USER_SET_RAT_TYPE_ENUM_U8;



/* Deleted by w00167002 for L-C??????????, 2014-2-17, begin */
/* Deleted by w00167002 for L-C??????????, 2014-2-17, end */

/* Added by w00167002 for L-C??????????, 2014-2-13, begin */
/*****************************************************************************
 ??????    : TAF_MMA_SYS_CFG_PARA_STRU
 ????????  : ??????????????????????

 ????????      :
  1.??    ??   : 2014??01??23??
    ??    ??   : s00246516
    ????????   : L-C??????????????
  2.??    ??   : 2015??4??9??
    ??    ??   : h00313353
    ????????   : SrvDomain????????????
*****************************************************************************/
typedef struct
{
    TAF_MMA_ROAM_MODE_ENUM_UINT8               enRoam;                          /* ??????????0????????????????????1??????????????????????????????2??????????????????????????????3?????????????????? */
    TAF_MMA_SERVICE_DOMAIN_ENUM_UINT8          enSrvDomain;                     /* ????????0??CS ONLY; 1:PS ONLY; 2:CS_PS; 3:any??????CS ONLY??4:???????? 5????????????????*/
    TAF_MMA_USER_SET_PRIO_RAT_ENUM_U8          enUserPrio;
    VOS_UINT8                                  aucReserve[1];
    TAF_MMA_RAT_ORDER_STRU                     stRatOrder;                      /* ???????????????????????? */
    TAF_USER_SET_PREF_BAND64                   stGuBand;                        /* ????GU???? */
    TAF_USER_SET_PREF_BAND64                   stLBand;                         /* ????L???? */
}TAF_MMA_SYS_CFG_PARA_STRU;

/* Added by w00167002 for L-C??????????, 2014-2-13, end */


#define TAF_MAX_GROUP_CFG_OPLMN_NUM                  (50)            /* ??????????????OPLMN?????????? */
#define TAF_MAX_USER_CFG_OPLMN_GROUP_INDEX           (5)             /* ????????????????Index,????????(0-5)??6?? */
#define TAF_MAX_USER_CFG_OPLMN_VERSION_LEN           (8)             /* ??????????OPLMN?????????????? */
#define TAF_MAX_GROUP_CFG_OPLMN_DATA_LEN             (250)           /* ????????????OPLMN??????????????????SIM????????????5??????????1??????????????OPLMN*/
#define TAF_MAX_USER_CFG_OPLMN_DATA_LEN              (1280)          /* ??????????????????OPLMN????????????????SIM????????????5??????????1??????????????OPLMN*/
#define TAF_SIM_PLMN_WITH_RAT_LEN                    (5)             /* SIM????????????PLMN??????*/
#define TAF_AT_PLMN_WITH_RAT_LEN                     (10)            /* AT????????????????????PLMN??????*/
#define TAF_AT_EOPLMN_PARA_NUM                       (4)             /* ^EOPLMN?????????????????? */


/*****************************************************************************
 ??????    : TAF_MMA_SET_EOPLMN_LIST_STRU
 ????????  : AT??MMA??EOPLMN????????
 1.??    ??  : 2013??10??15??
   ??    ??  : s00190137
   ????????  : ????????
 2.??    ??  : 2013??11??26??
   ??    ??  : s00190137
   ????????  : ??????????????????????????????50??OPLMN
*****************************************************************************/
typedef struct
{
    TAF_UINT8                           aucVersion[TAF_MAX_USER_CFG_OPLMN_VERSION_LEN];    /* OPLMN List?????? */
    TAF_UINT8                           ucIndex;                                /* ????????????Index */
    TAF_UINT8                           ucOPlmnCount;                           /* ????????????OPLMN?????? */
    TAF_UINT8                           aucOPlmnWithRat[TAF_MAX_GROUP_CFG_OPLMN_DATA_LEN];  /* OPLMN??PDU????????EFOplmn???????? */
}TAF_MMA_SET_EOPLMN_LIST_STRU;

/*****************************************************************************
 ??????    : TAF_PHONE_EVENT_EOPLMN_SET_CNF_STRU
 ????????  : EOPLMN????????????????
  ????????      :
  1.??    ??   : 2013??10??15??
    ??    ??   : s00190137
    ????????   : ??????????
*****************************************************************************/
typedef struct
{
    TAF_PHONE_EVENT                     PhoneEvent;
    MN_OPERATION_ID_T                   OpId;
    MN_CLIENT_ID_T                      ClientId;

    VOS_UINT32                          ulResult;
}TAF_PHONE_EVENT_EOPLMN_SET_CNF_STRU;

/*****************************************************************************
 ??????    : TAF_PHONE_EVENT_EOPLMN_QRY_CNF_STRU
 ????????  : EOPLMN????????????????
  ????????      :
  1.??    ??   : 2013??10??15??
    ??    ??   : s00190137
    ????????   : ??????????
  2.??    ??    : 2013??11??26??
    ??    ??    : s00190137
    ????????    : ????????????????OPLMN??????256??
*****************************************************************************/
typedef struct
{
    TAF_PHONE_EVENT                     PhoneEvent;
    MN_OPERATION_ID_T                   OpId;
    MN_CLIENT_ID_T                      ClientId;

    VOS_UINT32                          ulResult;
    VOS_UINT8                           aucVersion[TAF_MAX_USER_CFG_OPLMN_VERSION_LEN];       /* OPLMN List?????? */
    TAF_UINT16                          usOPlmnNum;                                           /* OPLMN???? */
    TAF_UINT8                           aucReserved[2];
    TAF_UINT8                           aucOPlmnList[TAF_MAX_USER_CFG_OPLMN_DATA_LEN];        /* OPLMN??PDU????????EFOplmn???????? */
}TAF_PHONE_EVENT_EOPLMN_QRY_CNF_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_COPS_FORMAT_TYPE_SET_REQ_STRU
 ????????  : AT??MMA????cops??????????????
 1.??    ??   : 2015??3??9??
   ??    ??   : z00161729
   ????????   : AT&T ????EONS????????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCopsFormatType;
    VOS_UINT8                           aucReserved[3];
}TAF_MMA_COPS_FORMAT_TYPE_SET_REQ_STRU;

#define TAF_MMA_MAX_EF_LEN              (240)
/*****************************************************************************
 ??????    : TAF_MMA_USIM_STUB_SET_REQ_STRU
 ????????  : usim????????????????mma????
 1.??    ??   : 2015??3??31??
   ??    ??   : z00161729
   ????????   : AT&T ????EONS????????
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usEfId;
    VOS_UINT16                          usEfLen;
    VOS_UINT8                           ucTotalNum;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT32                          ulApptype;
    VOS_UINT8                           aucEf[TAF_MMA_MAX_EF_LEN];
}TAF_MMA_USIM_STUB_SET_REQ_STRU;

#define TAF_MMA_MAX_FILE_ID_NUM         (6)
/*****************************************************************************
 ??????    : TAF_MMA_REFRESH_STUB_SET_REQ_STRU
 ????????  : ????pih??????????????refresh????
 1.??    ??   : 2015??3??31??
   ??    ??   : z00161729
   ????????   : AT&T ????EONS????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulReceivePid;
    VOS_UINT16                          usRefreshFileType;
    VOS_UINT8                           ucTotalNum;
    VOS_UINT8                           aucReserved[1];
    VOS_UINT16                          ausEfId[TAF_MMA_MAX_FILE_ID_NUM];
}TAF_MMA_REFRESH_STUB_SET_REQ_STRU;


/*****************************************************************************
 ??????    : TAF_MMA_AUTO_RESEL_STUB_SET_REQ_STRU
 ????????  : ????????at+cops=0??????????????
 1.??    ??   : 2015??5??29??
   ??    ??   : b00269685
   ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActiveFlg;
    VOS_UINT8                           acuReserved[3];
}TAF_MMA_AUTO_RESEL_STUB_SET_REQ_STRU;

/* Deleted by k902809 for Iteration 11, 2015-3-25, begin */

/* Deleted by k902809 for Iteration 11, Iteration 11 2015-3-25, end */

/*****************************************************************************
 ??????    : TAF_MMA_NET_SCAN_INFO_STRU
 ????????  : ??????????????????????
 1.??    ??   : 2013??8??24??
   ??    ??   : w00242748
   ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usArfcn;                                /* ???? */
    VOS_UINT16                          usC1;                                   /* ????GSM??????????C1??(????????) */
    VOS_UINT16                          usC2;                                   /* ????GSM??????????C2??(????????) */
    VOS_UINT16                          usLac;                                  /* ???????? */
    VOS_UINT32                          ulMcc;                                  /* PLMN?????? */
    VOS_UINT32                          ulMnc;                                  /* PLMN?????? */
    VOS_UINT16                          usBsic;                                 /* GSM?????????? */
    VOS_INT16                           sRxlev;                                 /* ???????????????? */
    VOS_INT16                           sRssi;                                  /* GSM??BCCH??????RSSI??WCDMA??RSCP */
    VOS_UINT8                           aucReserve[2];
    VOS_UINT32                          ulCellId;                               /* ????ID */
    TAF_USER_SET_PREF_BAND64            stBand;                               /* ??????????????RRMM_SYS_CFG_REQ_STRU?????????? */
}TAF_MMA_NET_SCAN_INFO_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_NET_SCAN_RESULT_ENUM
 ????????  : TAF_MMA_NET_SCAN_CNF_STRU????????enResult;
*****************************************************************************/
enum TAF_MMA_NET_SCAN_RESULT_ENUM
{
    TAF_MMA_NET_SCAN_RESULT_SUCCESS     = 0,
    TAF_MMA_NET_SCAN_RESULT_FAILURE     = 1,
    TAF_MMA_NET_SCAN_RESULT_BUTT
};
typedef VOS_UINT8  TAF_MMA_NET_SCAN_RESULT_ENUM_UINT8;

/*****************************************************************************
 ??????    : TAF_MMA_NET_SCAN_CAUSE_ENUM
 ????????  : ????????????
 1.??    ??   : 2013??10??10??
   ??    ??   : w00242748
   ????????   : ????
*****************************************************************************/
enum TAF_MMA_NET_SCAN_CAUSE_ENUM
{
    TAF_MMA_NET_SCAN_CAUSE_SIGNAL_EXIST        = 0,                /* ???????????? */
    TAF_MMA_NET_SCAN_CAUSE_STATE_NOT_ALLOWED   = 1,                /* ?????????? */
    TAF_MMA_NET_SCAN_CAUSE_FREQ_LOCK           = 2,                /* ???????????? */
    TAF_MMA_NET_SCAN_CAUSE_PARA_ERROR          = 3,                /* ???????????????????????????????????????????????????????????????? */
    TAF_MMA_NET_SCAN_CAUSE_CONFLICT            = 4,                /* ?????????????? */
    TAF_MMA_NET_SCAN_CAUSE_SERVICE_EXIST       = 5,
    TAF_MMA_NET_SCAN_CAUSE_NOT_CAMPED          = 6,
    TAF_MMA_NET_SCAN_CAUSE_TIMER_EXPIRED       = 7,
    TAF_MMA_NET_SCAN_CAUSE_RAT_TYPE_ERROR      = 8,
    TAF_MMA_NET_SCAN_CAUSE_MMA_STATE_DISABLE   = 9,

    TAF_MMA_NET_SCAN_CAUSE_BUTT
};
typedef VOS_UINT8 TAF_MMA_NET_SCAN_CAUSE_ENUM_UINT8;

/* Deleted by k902809 for Iteration 11, 2015-3-25, begin */

/* Deleted by k902809 for Iteration 11, Iteration 11 2015-3-25, end */

/*****************************************************************************
 ??????    : TAF_PH_REG_REJ_INFO_STRU
 ????????  : AT??MMA??REJINFO????????
 1.??    ??  : 2013??08??15??
   ??    ??  : l00208543
   ????????  : ????????
 2.??    ??   : 2014??4??1??
   ??    ??   : z00161729
   ????????   : DTS2014040300125:service ??????????detach ind????????????^rejinfo
  3.??    ??   : 2015??4??9??
    ??    ??   : h00313353
    ????????   : SysCfg SrvDomain??????
*****************************************************************************/
typedef struct
{
    /*??????????????????????AT??????????????????????????????*/

    TAF_PLMN_ID_STRU                    stPlmnId;
    TAF_UINT32                          ulRejCause;
    TAF_MMA_RAT_TYPE_ENUM_UINT8         enRat;
    TAF_MMA_SERVICE_DOMAIN_ENUM_UINT8   enSrvDomain;

    VOS_UINT8                           ucRejType;
    VOS_UINT8                           ucRac;
    VOS_UINT16                          usLac;
    VOS_UINT8                           ucOriginalRejCause;
    VOS_UINT8                           aucReserved[1];
    VOS_UINT32                          ulCellId;

}TAF_PH_REG_REJ_INFO_STRU;


/*****************************************************************************
 ??????    : TAF_PH_PLMN_SELECTION_RESULT_ENUM_UINT32
 ????????  : ????????
 1.??    ??   : 2013??10??09??
   ??    ??   : l00208543
   ????????   : ????
*****************************************************************************/
enum TAF_PH_PLMN_SELECTION_RESULT_ENUM
{
    TAF_PH_PLMN_SELECTION_RESULT_NORMAL_SERVICE    = 0,                        /* ???????? */
    TAF_PH_PLMN_SELECTION_RESULT_LIMITED_SERVICE   = 1,                        /* ???????? */
    TAF_PH_PLMN_SELECTION_RESULT_NO_SERVICE        = 2,                        /* ?????? */
    TAF_PH_PLMN_SELECTION_RESULT_INTERRUPT         = 3,                        /* ?????????? */
    TAF_PH_PLMN_SELECTION_RESULT_BUTT
};
typedef VOS_UINT32 TAF_PH_PLMN_SELECTION_RESULT_ENUM_UINT32;

/*****************************************************************************
 ??????    : TAF_PH_PLMN_SELECTION_START_END_FLAG_ENUM
 ????????  : ????????/????????????
 1.??    ??   : 2013??10??09??
   ??    ??   : l00208543
   ????????   : ????
*****************************************************************************/
enum TAF_PH_PLMN_SELECTION_START_END_FLAG_ENUM
{
    TAF_PH_PLMN_SELECTION_START      = 0,                        /* ???????? */
    TAF_PH_PLMN_SELECTION_END        = 1,                        /* ???????? */
    TAF_PH_PLMN_SELECTION_INTERRUPT  = 2,                        /* ?????????? */
    TAF_PH_PLMN_SELECTION_BUTT
};
typedef VOS_UINT32 TAF_PH_PLMN_SELECTION_START_END_FLAG_ENUM_UINT32;

/*****************************************************************************
 ??????    : TAF_MMA_PLMN_SELECTION_INFO_STRU
 ????????  : AT??MMA??PLMN_SELECTION_INFO????
 1.??    ??  : 2013??10??9??
   ??    ??  : l00208543
   ????????  : ????????

*****************************************************************************/
typedef struct
{
    TAF_PH_PLMN_SELECTION_RESULT_ENUM_UINT32           ulPlmnSelectRlst;
    TAF_PH_PLMN_SELECTION_START_END_FLAG_ENUM_UINT32   ulPlmnSelectFlag; /* ?????????????????????? */
}TAF_MMA_PLMN_SELECTION_INFO_STRU;

/*****************************************************************************
 ??????    : TAF_PHONE_EVENT_PLMN_LIST_STRU
 ????????  : PLMN LIST??????????
  ????????      :
  1.??    ??   : 2015??3??6??
    ??    ??   : b00269685
    ????????   : ??????????????
*****************************************************************************/
typedef struct
{
    TAF_UINT8                   ucOpError;
    TAF_UINT8                   aucReserved[3];
    TAF_ERROR_CODE_ENUM_UINT32  enPhoneError;
    TAF_UINT32                  ulCurrIndex;
    TAF_UINT32                  ulPlmnNum;
    TAF_PH_OPERATOR_NAME_STRU   astPlmnName[TAF_MMA_MAX_PLMN_NAME_LIST_NUM];
    TAF_PLMN_STATUS_STRU        astPlmnInfo[TAF_MMA_MAX_PLMN_NAME_LIST_NUM];
}TAF_MMA_PLMN_LIST_CNF_PARA_STRU;

/*****************************************************************************
 ??????    : TAF_PHONE_EVENT_PLMN_LIST_STRU
 ????????  : PLMN LIST??????????
  ????????      :
  1.??    ??   : 2011??11??5??
    ??    ??   : c00173809
    ????????   : ??????????
  2.??    ??   : 2015??3??6??
    ??    ??   : b00269685
    ????????   : ??????????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    MN_OPERATION_ID_T                   ucOpId;
    TAF_UINT8                           aucReserved[1];
    MN_CLIENT_ID_T                      usClientId;
    TAF_MMA_PLMN_LIST_CNF_PARA_STRU     stPlmnListCnfPara;
}TAF_MMA_PLMN_LIST_CNF_STRU;


typedef struct
{
    /*??????????????????????AT??????????????????????????????*/
    TAF_PHONE_EVENT                    PhoneEvent;
    MN_OPERATION_ID_T                  OpId;
    MN_CLIENT_ID_T                     ClientId;

    TAF_UINT32                         OP_RegPlmn         : 1;
    TAF_UINT32                         OP_CsServiceStatus : 1;
    TAF_UINT32                         OP_PsServiceStatus : 1;

    TAF_UINT32                         OP_PlmnReselMode   : 1;
    TAF_UINT32                         OP_PhoneError      : 1;
    TAF_UINT32                         OP_CurRegSta       : 1;
    TAF_UINT32                         OP_Rssi            : 1;

    TAF_UINT32                         OP_BatteryPower    : 1;
    TAF_UINT32                         OP_Pin             : 1;
    TAF_UINT32                         OP_UsimAccessData  : 1;
    TAF_UINT32                         OP_PinRemain       : 1;

    TAF_UINT32                         OP_MeLockStatus     : 1;
    TAF_UINT32                         OP_MePersonalisation: 1;
    TAF_UINT32                         OP_OperMode         : 1;
    TAF_UINT32                         OP_SpnInfo          : 1;

    TAF_UINT32                         OP_Mode              : 1;
    TAF_UINT32                         OP_Srvst             : 1;
    TAF_UINT32                         OP_UsimRestrictAccess: 1;
    TAF_UINT32                         OP_UsimPNN           : 1;

    TAF_UINT32                         OP_SysCfg            : 1;
    TAF_UINT32                         OP_UsimOPL           : 1;
    TAF_UINT32                         OP_MmInfo            : 1;
    TAF_UINT32                         OP_PrefPlmnList      : 1;

    TAF_UINT32                         OP_DomainAttachState : 1;
    TAF_UINT32                         OP_SysCfgBandGroup   : 1;


    /* Added by L60609 for V7R1C50 AT&T&DCM, 2012-6-13, begin */
    TAF_UINT32                         OP_PlmnMode          : 1;
    /* Added by L60609 for V7R1C50 AT&T&DCM, 2012-6-13, end */

    TAF_UINT32                         OP_CurPlmn           : 1;

    /* Added by w00176964 for V7R1C50_DCM????????????????????, 2012-12-11, begin */
    TAF_UINT32                         Op_CellAcInfo        : 1;
    /* Modified by w00176964 for VoLTE_PhaseI????, 2013-8-1, begin */
    TAF_UINT32                         OP_Spare             : 3;
    TAF_UINT32                         OP_PsInitRslt        : 1;
    /* Modified by w00176964 for VoLTE_PhaseI????, 2013-8-1, end */
    /* Added by w00176964 for V7R1C50_DCM????????????????????, 2012-12-11, end */

    TAF_ERROR_CODE_ENUM_UINT32         PhoneError;

    TAF_PH_OP_MODE_CNF_STRU            OperMode;


    /* Modified by w00167002 for L-C??????????, 2014-2-13, begin */
    TAF_MMA_SYS_CFG_PARA_STRU          stSysCfg;
    /* Modified by w00167002 for L-C??????????, 2014-2-13, end */


    TAF_PLMN_ID_STRU                   RegPlmn;
    TAF_PH_INFO_RAT_TYPE               RatType;
    TAF_PHONE_SERVICE_STATUS           CsServiceStatus;
    TAF_PHONE_SERVICE_STATUS           PsServiceStatus;
    TAF_PHONE_CHANGED_SERVICE_STATUS   ServiceStatus;
    TAF_PLMN_RESEL_MODE_TYPE           PlmnReselMode;
    VOS_UINT8                          aucReserved1[3];
    TAF_PH_REG_STATE_STRU              CurRegSta;
    TAF_PH_PIN_CNF_STRU                PinCnf;
    TAF_PH_USIM_RESPONSE_STRU          UsimAccessData;
    TAF_USIM_STATUS                    SimStatus;
    TAF_PH_ME_LOCK_STATUS              MeLockStatus;
    VOS_UINT8                          aucReserved2[2];
    TAF_PH_PIN_TIMECNF_STRU            PinRemainCnf;
    TAF_PH_ME_PERSONLISATION_CNF_STRU  MePersonalisation;
    TAF_PH_SPN_INFO_STRU               PhSpnInfo;
    TAF_PH_RESTRICTED_ACCESS_CNF_STRU  RestrictedAccess;


    VOS_UINT8                          aucReserved3[2];


    VOS_UINT8                          ucRoamStatus;            /* ???????????????????? */
    /* Added by L60609 for V7R1C50 AT&T&DCM, 2012-6-13, begin */
    VOS_UINT8                          ucPlmnMode;
    /* Added by L60609 for V7R1C50 AT&T&DCM, 2012-6-13, end */


    /* Added by s00217060 for ????????AT??????????????C??, 2013-3-25, begin */
    VOS_UINT8                          aucCurcRptCfg[TAF_MMA_RPT_CFG_MAX_SIZE];         /* CURC?????????????????? */
    VOS_UINT8                          aucUnsolicitedRptCfg[TAF_MMA_RPT_CFG_MAX_SIZE];  /* ?????????????????????????? */
    /* Added by s00217060 for ????????AT??????????????C??, 2013-3-25, end */

    /* Added by w00176964 for VoLTE_PhaseI????, 2013-8-1, begin */
    TAF_MMA_PS_INIT_RSLT_ENUM_UINT32   ulPsInitRslt;                                    /* ???????????????? */
    /* Added by w00176964 for VoLTE_PhaseI????, 2013-8-1, end */
}TAF_PHONE_EVENT_INFO_STRU;

#define TAF_SIM_LOCK_MCC_LEN            (3)

/*****************************************************************************
 ??????    : TAF_CUSTOM_CARDLOCK_STATUS_STRU
 ????????  :
 ASN.1???? :
 ????????  : en_NV_Item_CardlockStatus NV????????????,
             ????????SIM LOCK??????????????????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulStatus;            /*??????????0????????1???? */
    TAF_OPERATOR_LOCK_STATUS_ENUM_U32   enCardlockStatus;    /**/
    VOS_UINT32                          ulRemainUnlockTimes; /*????????????*/
}TAF_CUSTOM_CARDLOCK_STATUS_STRU;


#define EVT_NAS_MMA_NV_CONTEXT   0xaacc          /* PC????????NV???????????? */

/*****************************************************************************
 Structure      : NAS_MMA_NV_CONTEXT_ST
 Description    : PC??????????NV????????
 Message origin :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                             auNvFileName[40];                     /* ??????????40??????*/
    VOS_UINT32                            ulNvFileLen;                          /* ????????*/
    VOS_UINT32                            ulPacketLen;                          /* ????????????????????????????????*/
    VOS_UINT8                             auNvFileData[4];                      /* ????????*/
 }NAS_MMA_NV_CONTEXT_ST;

/*****************************************************************************
 Structure      : NAS_MMA_NV_MSG_ST
 Description    : PC??????????NV????????????
 Message origin :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                           usMsgID;                               /*_H2ASN_Skip*/
    VOS_UINT16                           usReserved;                            /* ??PACK(1)??PACK(4)???????????????????? */
    NAS_MMA_NV_CONTEXT_ST                stNVCtxt;                                  /*NV????*/
}NAS_MMA_NV_MSG_ST;

/*****************************************************************************
??????     : TAF_MMA_CSQLVLEXT_PARA_STRU
 ????????  :
 ASN.1???? :
 ????????  : CSQLVLEX??????????????????????
             ????CSQLVLEX??????????????????????????????????????????????????????BER????????99
*******************************************************************************/
typedef struct
{
    MN_PH_CSQLVLEXT_RSSILV_VALUE_ENUM_UINT8   enRssilv;                         /* CSQLVLEX???????????????????? */
    MN_PH_CSQLVLEXT_BER_VALUE_ENUM_UINT8      enBer;                            /* ????????????????????????????BER????????99*/
}TAF_MMA_CSQLVLEXT_PARA_STRU;

/* Added by f62575 for AT Project, 2011-10-04,  Begin */
/*****************************************************************************
 ??????    : TAF_MMA_CSQLVL_PARA_STRU
 ????????  : CSQLVL??????????????????????
             ????RSCP ??????RSCP ????????
*******************************************************************************/
typedef struct
{
    VOS_UINT16                          usRscp;                                 /* RSCP ???? */
    VOS_UINT16                          usLevel;                                /* RSCP ???????? */
}TAF_MMA_CSQLVL_PARA_STRU;
/* Added by f62575 for AT Project, 2011-10-04,  End */

/*****************************************************************************
 ??????    : MN_MMA_CPAM_RAT_PRIO_ENUM
 ????????  : AT^CPAM ??acqorder????????????????
1.??    ??  : 2011??07??15??
  ??    ??  : z00161729
  ????????  : ????????
*****************************************************************************/
enum AT_CPAM_RAT_PRIO_ENUM
{
    MN_MMA_CPAM_RAT_PRIO_GSM            = 0,                                    /* ????????????????GSM????  */
    MN_MMA_CPAM_RAT_PRIO_WCDMA          = 1,                                    /* ????????????????WCDMA???? */
    MN_MMA_CPAM_RAT_PRIO_NO_CHANGE      = 2,                                    /* ?????????????????? */
    MN_MMA_CPAM_RAT_BUTT
};
typedef VOS_UINT8 MN_MMA_CPAM_RAT_PRIO_ENUM_UINT8;




/*****************************************************************************
??????    : MN_MMA_ANQUERY_2G_3G_PARA_STRU
????????  : AT^ANQUERY??????????2G/3G????????????
  1.??    ??   : 2014??11??29??
    ??    ??   : l00305157
    ????????   : ????
*******************************************************************************/
typedef struct
{
    VOS_INT16                           sCpichRscp;
    VOS_INT16                           sCpichEcNo;
    VOS_UINT32                          ulCellId;
    VOS_UINT8                           ucRssi;                                 /* Rssi, GU??????*/
    VOS_UINT8                           aucReserve[3];

}MN_MMA_ANQUERY_2G_3G_PARA_STRU;


/*****************************************************************************
??????    : MN_MMA_ANQUERY_4G_PARA_STRU
????????  : AT^ANQUERY??????????LTE????????????
  1.??    ??   : 2014??11??29??
    ??    ??   : l00305157
    ????????   : ????
*******************************************************************************/
typedef struct
{
    VOS_INT16                           sRsrp;                                  /* ??????(-141,-44), 99?????? */
    VOS_INT16                           sRsrq;                                  /* ??????(-40, -6) , 99?????? */
    VOS_INT16                           sRssi;                                  /* Rssi, LTE??????*/
    VOS_UINT8                           aucReserve[2];
}MN_MMA_ANQUERY_4G_PARA_STRU;


/*****************************************************************************
??????    : MN_MMA_ANQUERY_PARA_STRU
????????  : AT^ANQUERY??????????????????????

  1.??    ??   : 2011??10??17??
    ??    ??   : o00132663
    ????????   : ????
*******************************************************************************/
typedef struct
{
    TAF_MMA_RAT_TYPE_ENUM_UINT8             enServiceSysMode;                       /* ????????????*/
    VOS_UINT8                               aucReserve[3];
    union
    {
        MN_MMA_ANQUERY_2G_3G_PARA_STRU      st2G3GCellSignInfo;                     /* Rssi, GU??????*/
        MN_MMA_ANQUERY_4G_PARA_STRU         st4GCellSignInfo;                       /* Rssi, LTE??????*/
    }u;
}MN_MMA_ANQUERY_PARA_STRU;


/*****************************************************************************
??????    : TAF_MMA_CSNR_PARA_STRU
????????  : AT+CSNR??????????????????????
*******************************************************************************/
typedef struct
{
    VOS_INT16                           sCpichRscp;
    VOS_INT16                           sCpichEcNo;
}TAF_MMA_CSNR_PARA_STRU;

/*****************************************************************************
??????    : TAF_MMA_CRPN_QRY_PARA_STRU
????????  : AT^CRPN????????????

  1.??    ??   : 2011??10??17??
    ??    ??   : o00132663
    ????????   : ????
  2.??    ??   : 2015??3??5??
    ??    ??   : b00269685
    ????????   : ????????????
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCurrIndex;
    VOS_UINT8                           ucQryNum;
    VOS_UINT16                          usPlmnNameLen;
    VOS_UINT8                           ucPlmnType;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                           aucPlmnName[TAF_PH_OPER_NAME_LONG];
}TAF_MMA_CRPN_QRY_PARA_STRU;

/* NAME?????????????????????????????????? */
#define TAF_PH_CRPN_PLMN_MAX_NUM            (6)            /* AT^CRPN????????PLMN???? */
/*****************************************************************************
??????    : TAF_MMA_CRPN_QRY_INFO_STRU
????????  : AT^CRPN????????????????

  1.??    ??   : 2011??10??17??
    ??    ??   : o00132663
    ????????   : ????
  2.??    ??   : 2015??3??5??
    ??    ??   : b00269685
    ????????   : ????????????
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCurrIndex;
    VOS_UINT8                           ucTotalNum;
    VOS_UINT8                           ucMaxMncLen;
    VOS_UINT8                           aucReserved[1];
    TAF_MMA_CRPN_QRY_PARA_STRU          stMnMmaCrpnQry;
    TAF_PH_OPERATOR_NAME_STRU           stOperNameList[TAF_PH_CRPN_PLMN_MAX_NUM];
}TAF_MMA_CRPN_QRY_INFO_STRU;


/*****************************************************************************
??????    : TAF_MMA_SPN_PARA_STRU
????????  : AT^SPN????????????????????

  1.??    ??   : 2011??10??17??
    ??    ??   : o00132663
    ????????   : ????
*******************************************************************************/
typedef struct
{
    TAF_PH_USIM_SPN_STRU                stSimSpnInfo;
    TAF_PH_USIM_SPN_STRU                stUsimSpnInfo;
}TAF_MMA_SPN_PARA_STRU;

/* MM???????????????????????????? */
enum MM_TEST_AT_CMD_ENUM
{
    MM_TEST_AT_CMD_MM_STATE             = 0,    /* MM???????? */
    MM_TEST_AT_CMD_GMM_STATE            = 1,    /* GMM???????? */
    MM_TEST_AT_CMD_GPRS_STATE           = 2,    /* GPRS?????????????? */
    MM_TEST_AT_CMD_MM_REG_STATE         = 3,    /* MM???????? */
    MM_TEST_AT_CMD_GMM_REG_STATE        = 4,    /* GMM???????? */
    MM_TEST_AT_CMD_PLMN_SEARCH_MODE     = 5,    /* ????????????, ??????NV?? */
    MM_TEST_AT_CMD_SET_RAT_MODE         = 6,    /* ????????????, ??????NV?? */

    /* Added by s46746 for CS/PS mode 1, 2012-6-19, begin */
    MM_TEST_AT_CMD_SET_ADDITIONAL_UPDATE_RESULT_IE = 7,    /* ????ADDITIONAL_UPDATE_RESULT_IE */
    MM_TEST_AT_CMD_SET_LTE_UE_USAGE_SETTING        = 8,    /* ????LTE_UE_USAGE_SETTING */
    /* Added by s46746 for CS/PS mode 1, 2012-6-19, end */

    MM_TEST_AT_CMD_SET_GMM_DEALY_SUSPENDRSP        = 9,    /* ????gmm??????????????????MMC */

    /* Modified by z00234330 for ????????AT??????????????C??, 2013-4-16, begin */
    MM_TEST_AT_CMD_SET_CSFB_HIGH_PRIO_FLG         = 10,
    /* Modified by z00234330 for ????????AT??????????????C??, 2013-4-16, end */

    /* Modified by z00234330 for C50????????????V9, 2013-4-16, begin */
    MM_TEST_AT_CMD_CLEAR_USER_PLMN_                   = 11,
    /* Modified by z00234330 for C50????????????V9, 2013-4-16, end */

    MM_TEST_AT_CMD_SET_ORIGINAL_REJECT_CAUSE          = 12,
    MM_TEST_AT_CMD_BUTT,
};
typedef VOS_UINT8 MM_TEST_AT_CMD_ENUM_U8;

/* Added by w00167002 for L-C??????????, 2014-2-25, begin */
/*****************************************************************************
 ??????    : TAF_MMA_CARD_STATUS_ENUM_UINT8
 ????????  : ??????????
  1.??    ??   : 2014??02??20??
    ??    ??   : w00167002
    ????????   : L-C??????????????
*****************************************************************************/
enum TAF_MMA_CARD_STATUS_ENUM
{
    TAF_MMA_CARD_STATUS_AVAILABLE      = 0,
    TAF_MMA_CARD_STATUS_NOT_AVAILABLE  = 1,
    TAF_MMA_CARD_STATUS_BUTT
};
typedef VOS_UINT8 TAF_MMA_CARD_STATUS_ENUM_UINT8;

/*****************************************************************************
 ??????    : TAF_MMA_USIMM_CARD_TYPE_ENUM
 ????????  : ????ID_TAF_MMA_SYS_INFO_IND_IND??????

 ????????      :
  1.??    ??   : 2014??02??20??
    ??    ??   : w00167002
    ????????   : L-C??????????????
*****************************************************************************/
enum TAF_MMA_USIMM_CARD_TYPE_ENUM
{
    TAF_MMA_USIMM_CARD_SIM           = 0,
    TAF_MMA_USIMM_CARD_USIM          = 1,
    TAF_MMA_USIMM_CARD_ROM_SIM       = 2,
    TAF_MMA_USIMM_CARD_ISIM          = 3,             /*ISIM??*/
    TAF_MMA_USIMM_CARD_UIM           = 4,             /*UIM??*/
    TAF_MMA_USIMM_CARD_CSIM          = 5,             /*SCIM??*/
    TAF_MMA_USIMM_CARD_NOCARD        = 255,
    TAF_MMA_USIMM_CARD_TYPE_BUTT
};
typedef VOS_UINT32      TAF_MMA_USIMM_CARD_TYPE_ENUM_UINT32;

/* Added by w00167002 for L-C??????????, 2014-2-25, end */

/*****************************************************************************
??????    : MM_TEST_AT_CMD_STRU
????????  : AT^CMM????????????????????

  1.??    ??   : 2011??10??17??
    ??    ??   : o00132663
    ????????   : ????
*******************************************************************************/
typedef struct
{
    MM_TEST_AT_CMD_ENUM_U8              ucCmd;
    TAF_UINT8                           ucParaNum;
    TAF_UINT16                          usReserve;
    TAF_UINT32                          aulPara[10];
}MM_TEST_AT_CMD_STRU;

/*****************************************************************************
??????    : MM_TEST_AT_CMD_STRU
????????  : AT^CMM????????????API Mm_AtTest????????

  1.??    ??   : 2011??10??17??
    ??    ??   : o00132663
    ????????   : ????
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRsltNum;
    VOS_UINT32                          aulRslt[20];
}MM_TEST_AT_RSLT_STRU;


/*****************************************************************************
??????    : ATMMA_OM_MAINTAIN_INFO_IND_STRU
????????  : MMA??AT??PC??????????????????????????

  1.??    ??   : 2012??04??24??
    ??    ??   : l00171473
    ????????   : ????
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT8                           ucOmConnectFlg;                         /* UE??PC??????????????, VOS_TRUE: ??????; VOS_FALSE: ?????? */
    VOS_UINT8                           ucOmPcRecurEnableFlg;                   /* OM??????????NAS PC?????????????????? */

    VOS_UINT8                           aucRsv2[2];                             /* ????   */
}ATMMA_OM_MAINTAIN_INFO_IND_STRU;


/*****************************************************************************
??????    : TAF_MMA_MM_INFO_QUERY_CNF_STRU
????????  : MM INFO????????????

  1.??    ??   : 2013??01??10??
    ??    ??   : l65478
    ????????   : ????
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLongNameLen;
    VOS_UINT8                           aucLongName[TAF_PH_OPER_NAME_LONG];
    VOS_UINT8                           ucShortNameLen;
    VOS_UINT8                           aucShortName[TAF_PH_OPER_NAME_SHORT];
    VOS_UINT8                           aucReserved[2];                             /* ????   */
}TAF_MMA_MM_INFO_PLMN_NAME_STRU;
/*******************************************************************************
 ??????    : TAF_USER_SRV_STATE_STRU
 ????????  : ??????????????????
 1.??    ??   : 2013??06??11??
   ??    ??   : s00217060
   ????????   : ??????????
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCsSrvExistFlg;                        /* CS???????????????? */
    VOS_UINT32                          ulPsSrvExistFlg;                        /* PS???????????????? */
}TAF_USER_SRV_STATE_STRU;


/* Modified by w00167002 for L-C??????????, 2014-2-25, begin */
/*****************************************************************************
??????    : TAF_MMA_CERSSI_INFO_QUERY_REQ_STRU
????????  : AT^CERSSI????????????

  1.??    ??   : 2013??2??4??
    ??    ??   : z00161729
    ????????   : ????
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           aucRsv[4];
}TAF_MMA_CERSSI_INFO_QUERY_REQ_STRU;


/*****************************************************************************
??????    : TAF_MMA_CPOL_INFO_QUERY_REQ_STRU
????????  : AT+CPOL????????????

  1.??    ??   : 2014??01??15??
    ??    ??   : f62575
    ????????   : DTS2014011301359??+CPOL????????????37??UPLMN
*******************************************************************************/
typedef struct
{
    MN_PH_PREF_PLMN_TYPE_ENUM_U8        enPrefPLMNType;                         /* ???????????????????? */
    VOS_UINT8                           aucReserved1[3];
    VOS_UINT32                          ulFromIndex;                            /* ???????????????????????? */
    VOS_UINT32                          ulPlmnNum;                              /* ??????????????????????????A????C????????????????????????????????????????50?????? */
    VOS_UINT32                          ulValidPlmnNum;                         /* ???????????????????????? */
}TAF_MMA_CPOL_INFO_QUERY_REQ_STRU;

/* Deleted by k902809 for Iteration 11, 2015-3-30, begin */
/* Deleted by k902809 for Iteration 11, Iteration 11 2015-3-30, end */

/* Added by s00246516 for L-C??????????, 2014-01-24, Begin */
/*****************************************************************************
 ??????    : TAF_MMA_CTRL_STRU
 ????????  : MMA??????????

 ????????      :
  1.??    ??   : 2014??01??23??
    ??    ??   : s00246516
    ????????   : L-C??????????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulModuleId;         /* ????PID */
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];
}TAF_MMA_CTRL_STRU;

/*****************************************************************************
 ??????  : TAF_MMA_PLMN_LIST_CTRL_STRU
 ????????: ????AT+COPS=???????
 1.??    ??   : 2015??2??25??
   ??    ??   : b00269685
   ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usCurrIndex;                    /* ??????????????PNN list??????index */
    VOS_UINT16                          usReadNum;                      /* ??????????PNN ???? */
} TAF_MMA_PLMN_LIST_CTRL_STRU;


/*****************************************************************************
 ??????    : TAF_MMA_PHONE_MODE_STRU
 ????????  : ??????????????????????

 ????????      :
  1.??    ??   : 2014??01??23??
    ??    ??   : s00246516
    ????????   : L-C??????????????
*****************************************************************************/
typedef struct
{
    TAF_PH_MODE                        PhMode;  /* ???? */
    TAF_PH_RESET_FLG                   PhReset; /* ???????????? */
    VOS_UINT8                          aucReserve[2];
}TAF_MMA_PHONE_MODE_PARA_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_PHONE_MODE_SET_REQ_STRU
 ????????  : ??????????????????????

 ????????      :
  1.??    ??   : 2014??01??23??
    ??    ??   : s00246516
    ????????   : L-C??????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_MMA_PHONE_MODE_PARA_STRU        stPhoneModePara;
}TAF_MMA_PHONE_MODE_SET_REQ_STRU;


/*****************************************************************************
 ??????    : TAF_MMA_SYS_CFG_REQ_STRU
 ????????  : ??????????????????????

 ????????      :
  1.??    ??   : 2014??02??13??
    ??    ??   : b00269685
    ????????   : L-C??????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_MMA_SYS_CFG_PARA_STRU           stSysCfgPara;
}TAF_MMA_SYS_CFG_REQ_STRU;


/*****************************************************************************
 ??????    : TAF_MMA_EONS_UCS2_REQ_STRU
 ????????  : AT^EONSUCS2 ??????????????????

 ????????      :
  1.??    ??   : 2015??03??12??
    ??    ??   : c00318887
    ????????   : AT&T phaseII????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;
    TAF_MMA_CTRL_STRU                   stCtrl;
}TAF_MMA_EONS_UCS2_REQ_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_EONS_UCS2_PLMN_NAME_STRU
 ????????  : AT^EONSUCS2 ??????????????

 ????????      :
  1.??    ??   : 2015??03??12??
    ??    ??   : c00318887
    ????????   : AT&T phaseII????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLongNameLen;
    VOS_UINT8                           aucLongName[TAF_PH_OPER_NAME_LONG];
    VOS_UINT8                           ucShortNameLen;
    VOS_UINT8                           aucShortName[TAF_PH_OPER_NAME_SHORT];
    VOS_UINT8                           aucReserved[2];                             /* ????   */
}TAF_MMA_EONS_UCS2_PLMN_NAME_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_EONS_UCS2_HNB_NAME_STRU
 ????????  : AT^EONSUCS2 ??????????????

 ????????      :
  1.??    ??   : 2016??02??2??
    ??    ??   : y00358807
    ????????   : AT&T phaseII????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHomeNodeBNameLen;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                           aucHomeNodeBName[TAF_MMA_MAX_HOME_NODEB_NAME_LEN];
}TAF_MMA_EONS_UCS2_HNB_NAME_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_EONS_UCS2_CNF_STRU
 ????????  : AT^EONSUCS2 ??????????????????

 ????????      :
  1.??    ??   : 2015??03??12??
    ??    ??   : c00318887
    ????????   : AT&T phaseII????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserve[1];
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt;
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause;
    TAF_MMA_EONS_UCS2_PLMN_NAME_STRU    stEonsUcs2PlmnName;
    TAF_MMA_EONS_UCS2_HNB_NAME_STRU     stEonsUcs2HNBName;
}TAF_MMA_EONS_UCS2_CNF_STRU;



/*****************************************************************************
 ??????    : TAF_MMA_ACQ_PARA_STRU
 ????????  : ??????????????????????

 ????????      :
  1.??    ??   : 2014??01??23??
    ??    ??   : s00246516
    ????????   : L-C??????????????
*****************************************************************************/
typedef struct
{
    TAF_MMA_ACQ_REASON_ENUM_UINT8    enAcqReason;
    VOS_UINT8                        aucReserve[3];
}TAF_MMA_ACQ_PARA_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_ACQ_REQ_STRU
 ????????  : ??????????????????????

 ????????      :
  1.??    ??   : 2014??02??13??
    ??    ??   : b00269685
    ????????   : L-C??????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_MMA_ACQ_PARA_STRU               stAcqPara;
}TAF_MMA_ACQ_REQ_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_REG_CELL_INFO_STRU
 ????????  : ??????????????????????

 ????????      :
  1.??    ??   : 2014??01??23??
    ??    ??   : s00246516
    ????????   : L-C??????????????
  2.??    ??   : 2015??7??20??
   ??    ??   : w000316404
   ????????   : R11????????(LTE??????????????)
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulArfcn;
    VOS_UINT8                           ucPlmnNum;
    VOS_UINT8                           ucCellNum;
    VOS_UINT8                           aucReserved[2];
    TAF_PLMN_ID_STRU                    astPlmnId[TAF_MMA_REG_MAX_PLMN_NUM];
    VOS_UINT16                          ausCellId[TAF_MMA_REG_MAX_CELL_NUM];
}TAF_MMA_REG_CELL_INFO_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_REG_PARA_STRU
 ????????  : ??????????????

 ????????      :
  1.??    ??   : 2014??01??23??
    ??    ??   : s00246516
    ????????   : L-C??????????????
  2.??    ??   : 2015??4??9??
    ??    ??   : h00313353
    ????????   : SysCfg SrvDomain??????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                    bitOpPrioClass       : 1;
    VOS_UINT32                                    bitOpEpsAttachReason : 1;
    VOS_UINT32                                    bitOpCellInfo        : 1;
    VOS_UINT32                                    bitSpare             : 29;
    TAF_MMA_PLMN_PRIORITY_CLASS_ENUM_UINT8        enPrioClass;
    TAF_MMA_EPS_ATTACH_REASON_ENUM_UINT8          enEpsAttachReason;
    TAF_MMA_SERVICE_DOMAIN_ENUM_UINT8             enAttachDomain;               /* ????????0??CS ONLY; 1:PS ONLY; 2:CS_PS; 3:any??????CS ONLY??4????????????????*/
    VOS_UINT8                                     aucReserve[1];
    TAF_MMA_REG_CELL_INFO_STRU                    stCellInfo;
}TAF_MMA_REG_PARA_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_REG_REQ_STRU
 ????????  : ??????????????????????

 ????????      :
  1.??    ??   : 2014??02??13??
    ??    ??   : b00269685
    ????????   : L-C??????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_MMA_REG_PARA_STRU               stRegPara;
}TAF_MMA_REG_REQ_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_SRV_ACQ_RESULT_ENUM_UINT8
 ????????  : MMA????SPM????????????
 1.??    ??   : 2014??5??28??
   ??    ??   : h00246512
   ????????   : ????
*****************************************************************************/
enum TAF_MMA_SRV_ACQ_RESULT_ENUM
{
    TAF_MMA_SRV_ACQ_RESULT_SUCCESS = 0,                                /* ???? */
    TAF_MMA_SRV_ACQ_RESULT_FAIL    = 1,                                /* ???? */
    TAF_MMA_SRV_ACQ_RESULT_BUTT
};
typedef VOS_UINT8 TAF_MMA_SRV_ACQ_RESULT_ENUM_UINT8;

/*****************************************************************************
 ??????    : TAF_MMA_SRV_ACQ_CNF_STRU
 ????????  : ????????????????
 1.??    ??   : 2014??5??28??
   ??    ??   : h00246512
   ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                             /*_H2ASN_Skip*/
    TAF_MMA_SRV_ACQ_RESULT_ENUM_UINT8   enResult;
    VOS_UINT8                           aucReserved[3];
}TAF_MMA_SRV_ACQ_CNF_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_SRV_TYPE_ENUM_UINT8
 ????????  : CS????PS??SESSION????
 1.??    ??   : 2014??5??22??
   ??    ??   : h00246512
   ????????   : ????
 2.??    ??   : 2016??3??23??
   ??    ??   : h00360002
   ????????   : ????CS????????????????????????IMS??????
*****************************************************************************/
enum TAF_MMA_SRV_TYPE_ENUM
{
    TAF_MMA_SRV_TYPE_CS_MO_NORMAL_CALL,
    TAF_MMA_SRV_TYPE_CS_MO_EMERGENCY_CALL,
    TAF_MMA_SRV_TYPE_CS_MO_SS,
    TAF_MMA_SRV_TYPE_CS_MO_SMS,
    TAF_MMA_SRV_TYPE_PS_CONVERSAT_CALL,
    TAF_MMA_SRV_TYPE_PS_STREAM_CALL,
    TAF_MMA_SRV_TYPE_PS_INTERACT_CALL,
    TAF_MMA_SRV_TYPE_PS_BACKGROUND_CALL,
    TAF_MMA_SRV_TYPE_PS_SUBSCRIB_TRAFFIC_CALL,
    TAF_MMA_SRV_TYPE_PS_MO_EMERGENCY_CALL,
    TAF_MMA_SRV_TYPE_BUTT
};
typedef VOS_UINT8 TAF_MMA_SRV_TYPE_ENUM_UINT8;

/*****************************************************************************
 ??????    : TAF_MMA_SRV_ACQ_RAT_TYPE_ENUM_UINT8
 ????????  : ??????????????RAT????
 1.??    ??   : 2014??5??15??
   ??    ??   : l00301449
   ????????   : ????
*****************************************************************************/
enum TAF_MMA_SRV_ACQ_RAT_TYPE_ENUM
{
    TAF_MMA_SRV_ACQ_RAT_TYPE_GUL,
    TAF_MMA_SRV_ACQ_RAT_TYPE_1X,
    TAF_MMA_SRV_ACQ_RAT_TYPE_HRPD,
    TAF_MMA_SRV_ACQ_RAT_TYPE_BUTT
};

typedef VOS_UINT8 TAF_MMA_SRV_ACQ_RAT_TYPE_ENUM_UINT8;



/*****************************************************************************
 ??????    : TAF_MMA_SRV_ACQ_RAT_LIST_STRU
 ????????  : ??????????????????????????
 1.??    ??   : 2015??5??15??
   ??    ??   : L00301449
   ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRatNum;
    TAF_MMA_SRV_ACQ_RAT_TYPE_ENUM_UINT8 aenRatType[TAF_MMA_SRV_ACQ_RAT_NUM_MAX];
}TAF_MMA_SRV_ACQ_RAT_LIST_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_SRV_ACQ_REQ_STRU
 ????????  : ????????????????
 1.??    ??   : 2014??5??28??
   ??    ??   : h00246512
   ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                            /*_H2ASN_Skip*/
    TAF_MMA_SRV_TYPE_ENUM_UINT8         enSrvType;
    VOS_UINT8                           aucReserved[3];
    TAF_MMA_SRV_ACQ_RAT_LIST_STRU       stRatList;
}TAF_MMA_SRV_ACQ_REQ_STRU;


/*****************************************************************************
 ??????    : TAF_MMA_POWER_SAVE_PARA_STRU
 ????????  : Power Save??????????

 ????????      :
  1.??    ??   : 2014??01??23??
    ??    ??   : s00246516
    ????????   : L-C??????????????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve[4];
}TAF_MMA_POWER_SAVE_PARA_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_POWER_SAVE_REQ_STRU
 ????????  : ??????????????????????

 ????????      :
  1.??    ??   : 2014??02??13??
    ??    ??   : b00269685
    ????????   : L-C??????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_MMA_POWER_SAVE_PARA_STRU        stPowerSavePara;
}TAF_MMA_POWER_SAVE_REQ_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_DETACH_PARA_STRU
 ????????  : Detach??????????

 ????????      :
  1.??    ??   : 2014??01??23??
    ??    ??   : s00246516
    ????????   : L-C??????????????
  2.??    ??   : 2015??4??9??
    ??    ??   : h00313353
    ????????   : SysCfg SrvDomain????????
*****************************************************************************/
typedef struct
{
    TAF_MMA_DETACH_CAUSE_ENUM_UINT8     enDetachCause;
    TAF_MMA_SERVICE_DOMAIN_ENUM_UINT8   enDetachDomain;                         /* ????????0??CS ONLY; 1:PS ONLY; 2:CS_PS; 3:any??????CS ONLY??4????????????????*/
    VOS_UINT8                           aucReserve[2];
}TAF_MMA_DETACH_PARA_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_PLMN_LIST_PARA_STRU
 ????????  : ??????????

 ????????      :
  1.??    ??   : 2015??4??8??
    ??    ??   : b00269685
    ????????   :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usCurrIndex; /* ?????????????? */
    VOS_UINT16                          usQryNum;    /* ????????????????A????C?????????????????????? */
} TAF_MMA_PLMN_LIST_PARA_STRU;

/*****************************************************************************
??????    : TAF_MMA_CSG_LIST_ABORT_REQ_STRU
????????  : CSG List Abort????????

  1.??    ??   : 2015??9??6??
    ??    ??   : z00161729
    ????????   : ????LTE CSG????????
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        enMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    VOS_UINT32                          ulReserved;
}TAF_MMA_CSG_LIST_ABORT_REQ_STRU;

/*****************************************************************************
??????    : TAF_MMA_CSG_LIST_ABORT_CNF_STRU
????????  : CSG list Abort????????????

  1.??    ??   : 2015??9??6??
    ??    ??   : z00161729
    ????????   : ????LTE CSG????????
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        enMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause;
}TAF_MMA_CSG_LIST_ABORT_CNF_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_CSG_LIST_SEARCH_REQ_STRU
 ????????  : CSG????????????????

 ????????      :
  1.??    ??   : 2015??9??6??
    ??    ??   : z00161729
    ????????   : ????LTE CSG????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        enMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_MMA_PLMN_LIST_PARA_STRU         stPlmnListPara;
}TAF_MMA_CSG_LIST_SEARCH_REQ_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_CSG_TYPE_STRU
 ????????  : ????CSG ID????
  1.??    ??   : 2015??9??6??
    ??    ??   : z00161729
    ????????   : ????LTE CSG????????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCsgTypeLen;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                           aucCsgType[TAF_MMA_MAX_CSG_TYPE_LEN];
}TAF_MMA_CSG_TYPE_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_CSG_ID_HOME_NODEB_NAME_STRU
 ????????  : ????CSG ID??????Home eNodeB name
  1.??    ??   : 2015??9??6??
    ??    ??   : z00161729
    ????????   : ????LTE CSG????????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHomeNodeBNameLen;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                           aucHomeNodeBName[TAF_MMA_MAX_HOME_NODEB_NAME_LEN];
}TAF_MMA_CSG_ID_HOME_NODEB_NAME_STRU;


/*****************************************************************************
 ??????    : TAF_MMA_CSG_ID_LIST_INFO_STRU
 ????????  : CSG list????????????????
  ????????      :
  1.??    ??   : 2015??9??6??
    ??    ??   : z00161729
    ????????   : ????LTE CSG????????
*****************************************************************************/
typedef struct
{
    TAF_PLMN_ID_STRU                                        stPlmnId;
    VOS_UINT32                                              ulCsgId;
    TAF_MMA_CSG_TYPE_STRU                                   stCsgType;
    TAF_MMA_CSG_ID_HOME_NODEB_NAME_STRU                     stCsgIdHomeNodeBName;
    TAF_PH_RA_MODE                                          ucRaMode;               /* ????????????,4G/3G/2G */
    TAF_MMA_PLMN_WITH_CSG_ID_TYPE_ENUM_UINT8                enPlmnWithCsgIdType;
    VOS_UINT8                                               aucReserved[2];
    TAF_CHAR                                                aucOperatorNameShort[TAF_PH_OPER_NAME_SHORT];
    TAF_CHAR                                                aucOperatorNameLong[TAF_PH_OPER_NAME_LONG];
}TAF_MMA_CSG_ID_LIST_INFO_STRU;



/*****************************************************************************
 ??????    : TAF_MMA_CSG_LIST_CNF_PARA_STRU
 ????????  : CSG PLMN LIST??????????
  ????????      :
  1.??    ??   : 2015??9??6??
    ??    ??   : z00161729
    ????????   : ????LTE CSG????????
*****************************************************************************/
typedef struct
{
    TAF_ERROR_CODE_ENUM_UINT32          enPhoneError;
    VOS_UINT32                          ulCurrIndex;
    VOS_UINT8                           ucOpError;
    VOS_UINT8                           ucPlmnWithCsgIdNum;
    VOS_UINT8                           aucReserved[2];
    TAF_MMA_CSG_ID_LIST_INFO_STRU       astCsgIdListInfo[TAF_MMA_MAX_CSG_ID_LIST_NUM];
}TAF_MMA_CSG_LIST_CNF_PARA_STRU;


/*****************************************************************************
 ??????    : TAF_MMA_CSG_LIST_SEARCH_CNF_STRU
 ????????  : CSG PLMN LIST??????????
  ????????      :
  1.??    ??   : 2015??9??6??
    ??    ??   : z00161729
    ????????   : ????LTE CSG????????,CSG????????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        enMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           ucReserved;
    TAF_MMA_CSG_LIST_CNF_PARA_STRU      stCsgListCnfPara;
}TAF_MMA_CSG_LIST_SEARCH_CNF_STRU;



/*****************************************************************************
 ??????    : TAF_MMA_CSG_SPEC_SEARCH_INFO_STRU
 ????????  : AT??MMA AT^CSGIDSRCH??????????CSG ID????????

  ????????      :
  1.??    ??   : 2015??11??23??
    ??    ??   : s00193151
    ????????   : ??????????
*****************************************************************************/
typedef struct
{
    TAF_PLMN_ID_STRU            stPlmnId;
    VOS_UINT32                  ulCsgId;
    TAF_MMA_RAT_TYPE_ENUM_UINT8 enRatType;
    VOS_UINT8                   aucReserved[3];
}TAF_MMA_CSG_SPEC_SEARCH_INFO_STRU;

/*****************************************************************************
??????    : TAF_MMA_CSG_SPEC_SEARCH_REQ_STRU
????????  : ????CSG????????????

  1.??    ??   : 2015??11??6??
    ??    ??   : z00161729
    ????????   : ????LTE CSG????????
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_MMA_CSG_SPEC_SEARCH_INFO_STRU   stCsgSpecSearchInfo;
}TAF_MMA_CSG_SPEC_SEARCH_REQ_STRU;

/*****************************************************************************
??????    : TAF_MMA_QRY_CAMP_CSG_ID_INFO_REQ_STRU
????????  : ????????????csg id????????????

  1.??    ??   : 2015??11??16??
    ??    ??   : z00161729
    ????????   : ????LTE CSG????????
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    VOS_UINT32                          ulReserved;
}TAF_MMA_QRY_CAMP_CSG_ID_INFO_REQ_STRU;

/*****************************************************************************
??????    : TAF_MMA_QRY_CAMP_CSG_ID_INFO_CNF_STRU
????????  : ????????csg id????????????????
  1.??    ??   : 2015??11??16??
    ??    ??   : z00161729
    ????????   : ????LTE CSG????????
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_PLMN_ID_STRU                    stPlmnId;
    TAF_PH_RA_MODE                      ucRatType;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT32                          ulCsgId;
}TAF_MMA_QRY_CAMP_CSG_ID_INFO_CNF_STRU;


/*****************************************************************************
??????    : TAF_MMA_CSG_SPEC_SEARCH_CNF_STRU
????????  : ????CSG????????????
  1.??    ??   : 2015??11??6??
    ??    ??   : z00161729
    ????????   : ????LTE CSG????????
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause;
}TAF_MMA_CSG_SPEC_SEARCH_CNF_STRU;


/*****************************************************************************
 ??????    : TAF_MMA_DETACH_REQ_STRU
 ????????  : ??????????????????????

 ????????      :
  1.??    ??   : 2014??02??13??
    ??    ??   : b00269685
    ????????   : L-C??????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_MMA_DETACH_PARA_STRU            stDetachPara;
}TAF_MMA_DETACH_REQ_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_IMS_SWITCH_SET_REQ_STRU
 ????????  : IMS??????????????????

 ????????      :
  1.??    ??   : 2015??02??03??
    ??    ??   : f00179208
    ????????   : IMS????????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_MMA_IMS_SWITCH_SET_ENUM_UINT8   enLteImsSwitch;
    VOS_UINT8                           aucReserved[3];
}TAF_MMA_IMS_SWITCH_SET_REQ_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_IMS_SWITCH_SET_CNF_STRU
 ????????  : IMS??????????????????????

 ????????      :
  1.??    ??   : 2015??02??03??
    ??    ??   : f00179208
    ????????   : IMS????????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpid;
    VOS_UINT8                           aucReserve[1];
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enResult;
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause;
}TAF_MMA_IMS_SWITCH_SET_CNF_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_IMS_SWITCH_QRY_REQ_STRU
 ????????  : IMS??????????????????

 ????????      :
  1.??    ??   : 2015??02??03??
    ??    ??   : f00179208
    ????????   : IMS????????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;
    TAF_MMA_CTRL_STRU                   stCtrl;
}TAF_MMA_IMS_SWITCH_QRY_REQ_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_IMS_SWITCH_QRY_CNF_STRU
 ????????  : IMS??????????????????????

 ????????      :
  1.??    ??   : 2015??02??03??
    ??    ??   : f00179208
    ????????   : IMS????????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpid;
    VOS_UINT8                           ucReserved;
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enResult;
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause;
    TAF_MMA_IMS_SWITCH_SET_ENUM_UINT8   enLteImsSwitch;
    VOS_UINT8                           aucReserved1[3];
}TAF_MMA_IMS_SWITCH_QRY_CNF_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_VOICE_DOMAIN_SET_REQ_STRU
 ????????  : ????????????????????????

 ????????      :
  1.??    ??   : 2015??02??03??
    ??    ??   : f00179208
    ????????   : IMS????????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_MMA_VOICE_DOMAIN_ENUM_UINT32    enVoiceDomain;
}TAF_MMA_VOICE_DOMAIN_SET_REQ_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_VOICE_DOMAIN_SET_CNF_STRU
 ????????  : ????????????????????????

 ????????      :
  1.??    ??   : 2015??02??03??
    ??    ??   : f00179208
    ????????   : IMS????????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpid;
    VOS_UINT8                           aucReserve[1];
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enResult;
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause;
}TAF_MMA_VOICE_DOMAIN_SET_CNF_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_VOICE_DOMAIN_QRY_REQ_STRU
 ????????  : ????????????????????????

 ????????      :
  1.??    ??   : 2015??02??03??
    ??    ??   : f00179208
    ????????   : IMS????????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;
    TAF_MMA_CTRL_STRU                   stCtrl;
}TAF_MMA_VOICE_DOMAIN_QRY_REQ_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_VOICE_DOMAIN_QRY_CNF_STRU
 ????????  : ????????????????????????

 ????????      :
  1.??    ??   : 2015??02??03??
    ??    ??   : f00179208
    ????????   : IMS????????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpid;
    VOS_UINT8                           aucReserve[1];
    TAF_MMA_VOICE_DOMAIN_ENUM_UINT32    enVoiceDomain;
}TAF_MMA_VOICE_DOMAIN_QRY_CNF_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_PHONE_MODE_SET_CNF_STRU
 ????????  : ????ID_TAF_MMA_PHONE_MODE_SET_CNF??????

 ????????      :
  1.??    ??   : 2014??01??23??
    ??    ??   : s00246516
    ????????   : L-C??????????????
  2.??    ??   : 2015??2??11??
    ??    ??   : s00217060
    ????????   : VOLTE SWITCH????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpid;
    TAF_PH_MODE                         ucPhMode;  /* ???? */
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt;
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause;
}TAF_MMA_PHONE_MODE_SET_CNF_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_SYS_CFG_CNF_STRU
 ????????  : ????ID_TAF_MMA_SYS_CFG_CNF??????

 ????????      :
  1.??    ??   : 2014??01??23??
    ??    ??   : s00246516
    ????????   : L-C??????????????
  2.??    ??   : 2015??2??11??
    ??    ??   : s00217060
    ????????   : VOLTE SWITCH????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpid;
    VOS_UINT8                           aucReserve[1];
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt;
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause;
}TAF_MMA_SYS_CFG_CNF_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_ACQ_CNF_STRU
 ????????  : ????ID_TAF_ACQ_CNF??????

 ????????      :
  1.??    ??   : 2014??01??23??
    ??    ??   : s00246516
    ????????   : L-C??????????????
  2.??    ??   : 2015??7??20??
    ??    ??   : w000316404
    ????????   : R11????????(LTE??????????????)
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                                   ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                                   usClientId;
    VOS_UINT8                                    ucOpid;
    VOS_UINT8                                    aucReserve[1];
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32          enRslt;
    TAF_PLMN_ID_STRU                             stPlmnId;
    VOS_UINT32                                   ulArfcn;
    TAF_MMA_PLMN_PRIORITY_CLASS_ENUM_UINT8       enPrioClass;
    VOS_UINT8                                    aucReserve2[3];
}TAF_MMA_ACQ_CNF_STRU;

/* Modified by b00269685 for L-C??????????, 2014-2-14, begin */
/*****************************************************************************
 ??????    : TAF_MMA_REG_CNF_STRU
 ????????  : ????ID_TAF_REG_CNF??????

 ????????      :
  1.??    ??   : 2014??2??14??
    ??    ??   : b00269685
    ????????   : L-C??????????????
  2.??    ??   : 2015??7??20??
    ??    ??   : w000316404
    ????????   : R11????????(LTE??????????????)
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                                   ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                                   usClientId;
    VOS_UINT8                                    ucOpid;
    VOS_UINT8                                    aucReserve[1];
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32          enRslt;
    TAF_PLMN_ID_STRU                             stPlmnId;
    VOS_UINT32                                   ulArfcn;
    TAF_MMA_PLMN_PRIORITY_CLASS_ENUM_UINT8       enPrioClass;
    TAF_MMA_ATTACH_CL_REG_STATUS_ENUM8           enLmmAttachRegStatus;
    VOS_UINT8                                    aucReserve2[2];
}TAF_MMA_REG_CNF_STRU;
/* Modified by b00269685 for L-C??????????, 2014-2-14, end */

/*****************************************************************************
 ??????    : TAF_MMA_POWER_SAVE_CNF_STRU
 ????????  : ????ID_TAF_MMA_POWER_SAVE_CNF??????

 ????????      :
  1.??    ??   : 2014??01??23??
    ??    ??   : s00246516
    ????????   : L-C??????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpid;
    VOS_UINT8                           aucReserve[1];
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt;
}TAF_MMA_POWER_SAVE_CNF_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_ACQ_IND_STRU
 ????????  : ????ID_TAF_ACQ_IND??????

 ????????      :
  1.??    ??   : 2014??01??23??
    ??    ??   : s00246516
    ????????   : L-C??????????????
  2.??    ??   : 2015??7??20??
    ??    ??   : w000316404
    ????????   : R11????????(LTE??????????????)
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                                    ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                                    usClientId;
    VOS_UINT8                                     ucOpid;
    VOS_UINT8                                     aucReserve[1];
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32           enRslt;
    TAF_PLMN_ID_STRU                              stPlmnId;
    VOS_UINT32                                    ulArfcn;
    TAF_MMA_PLMN_PRIORITY_CLASS_ENUM_UINT8        enPrioClass;
    VOS_UINT8                                     aucReserve2[3];
}TAF_MMA_ACQ_IND_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_DETACH_CNF_STRU
 ????????  : ????ID_TAF_MMA_DETACH_CNF??????

 ????????      :
  1.??    ??   : 2014??01??23??
    ??    ??   : s00246516
    ????????   : L-C??????????????
  2.??    ??   : 2015??2??11??
    ??    ??   : s00217060
    ????????   : VOLTE SWITCH????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpid;
    VOS_UINT8                           aucReserve[1];
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt;
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause;
}TAF_MMA_DETACH_CNF_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_SERVICE_STATUS_IND_STRU
 ????????  : ????ID_TAF_MMA_SERVICE_STATUS_IND_IND??????

 ????????      :
  1.??    ??   : 2014??01??23??
    ??    ??   : s00246516
    ????????   : L-C??????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpid;
    VOS_UINT8                           aucReserve[1];
    TAF_PHONE_SERVICE_STATUS            CsSrvSta; /*CS????????*/
    TAF_PHONE_SERVICE_STATUS            PsSrvSta; /*PS????????*/
    VOS_UINT8                           ucCsSimValid; /* CS????????????VOS_TRUE:??????VOS_FALSE:???? */
    VOS_UINT8                           ucPsSimValid; /* PS????????????VOS_TRUE:??????VOS_FALSE:???? */
}TAF_MMA_SERVICE_STATUS_IND_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_SYS_INFO_IND_STRU
 ????????  : ????ID_TAF_MMA_SYS_INFO_IND_IND??????

 ????????      :
  1.??    ??   : 2014??01??23??
    ??    ??   : s00246516
    ????????   : L-C??????????????
  2.??    ??   : 2015??7??20??
   ??    ??   : w000316404
   ????????   : R11????????(LTE??????????????)
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                                    ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                                    usClientId;
    VOS_UINT8                                     ucOpid;
    VOS_UINT8                                     aucReserve[1];
    TAF_PLMN_ID_STRU                              stPlmnId;
    VOS_UINT32                                    ulArfcn;
    TAF_MMA_PLMN_PRIORITY_CLASS_ENUM_UINT8        enPrioClass;
    VOS_UINT8                                     aucReserve2[3];
}TAF_MMA_SYS_INFO_IND_STRU;
/* Added by s00246516 for L-C??????????, 2014-01-24, End */

/* Added by w00167002 for L-C??????????, 2014-2-20, begin */


/*****************************************************************************
 ??????    : TAF_MMA_SYS_INFO_IND_STRU
 ????????  : ????ID_TAF_MMA_SYS_INFO_IND_IND??????

 ????????      :
  1.??    ??   : 2014??02??20??
    ??    ??   : w00167002
    ????????   : L-C??????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                                    ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                                    usClientId;
    VOS_UINT8                                     ucOpid;
    TAF_MMA_CARD_STATUS_ENUM_UINT8                enCardStatus;                   /* ??????*/
    TAF_MMA_USIMM_CARD_TYPE_ENUM_UINT32           enCardType;                     /* ??????:SIM??USIM??ROM-SIM  */
}TAF_MMA_SIM_STATUS_IND_STRU;

/* Added by w00167002 for L-C??????????, 2014-2-20, end */

/* Modified by w00167002 for L-C??????????, 2014-2-25, end */


/*****************************************************************************
 ??????    : TAF_MMA_PLMN_LIST_REQ_STRU
 ????????  : ????ID_TAF_MMA_PLMN_LIST_REQ??????

 ????????      :
  1.??    ??   : 2015??4??8??
    ??    ??   : B00269685
    ????????   :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_MMA_PLMN_LIST_PARA_STRU         stPlmnListPara;
} TAF_MMA_PLMN_LIST_REQ_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_IMS_CALL_INFO_STRU
 ????????  : TAF_MMA_IMS_CALL_INFO_STRU??????

 ????????      :
  1.??    ??   : 2016??4??27??
    ??    ??   : n00269697
    ????????   :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucImsCallFlg;
    MN_CALL_TYPE_ENUM_U8                enCallType;
    TAF_CALL_EMC_DOMAIN_ENUM_UINT8      enImsEmcDomin;
    VOS_UINT8                           ucReserve;    
}TAF_MMA_IMS_CALL_INFO_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_IMS_SRV_INFO_NOTIFY_STRU
 ????????  : ????ID_TAF_MMA_IMS_SRV_INFO_NOTIFY??????

 ????????      :
  1.??    ??   : 2014??11??06??
    ??    ??   : s00217060
    ????????   :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_IMS_CALL_INFO_STRU          stImsCallInfo;
}TAF_MMA_IMS_SRV_INFO_NOTIFY_STRU;

/*****************************************************************************
 ??????    : TAF_LAI_STRU
 ????????  : ID_TAF_MMA_SRCHED_PLMN_INFO_IND??????lai????????
 1.??    ??   : 2015??01??15??
   ??    ??   : h00285180
   ????????   : ????
*****************************************************************************/
typedef struct
{
    TAF_PLMN_ID_STRU                           stPlmnId;
    VOS_UINT16                                 usLac;

    VOS_UINT8                                  aucReserve[2];
}TAF_LAI_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_SRCHED_PLMN_INFO_IND_STRU
 ????????  : ID_TAF_MMA_SRCHED_PLMN_INFO_IND????????
 1.??    ??   : 2015??01??15??
   ??    ??   : h00285180
   ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpid;
    VOS_UINT8                           aucReserved1[1];

    TAF_MMA_RAT_TYPE_ENUM_UINT8         enRat;
    VOS_UINT8                           aucReserved2[3];

    VOS_UINT32                          ulLaiNum;
    TAF_LAI_STRU                        astLai[TAF_MMA_MAX_SRCHED_LAI_NUM];
}TAF_MMA_SRCHED_PLMN_INFO_IND_STRU;

/** ****************************************************************************
 * Name        : TAF_MMA_CDMA_MO_CALL_START_NTF_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                      /* _H2ASN_Skip */
    TAF_MMA_MSG_TYPE_ENUM_UINT32                            enMsgId;    /*_H2ASN_Skip*/
    TAF_MMA_CDMA_CALL_TYPE_ENUM_UINT8                       enCallType;
    VOS_UINT8                                               aucReserve[3];
}TAF_MMA_CDMA_MO_CALL_START_NTF_STRU;

/** ****************************************************************************
 * Name        : TAF_MMA_CDMA_MO_CALL_SUCCESS_NTF_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                      /* _H2ASN_Skip */
    TAF_MMA_MSG_TYPE_ENUM_UINT32                            enMsgId;    /*_H2ASN_Skip*/
    TAF_MMA_CDMA_CALL_TYPE_ENUM_UINT8                       enCallType;
    VOS_UINT8                                               aucReserve[3];
}TAF_MMA_CDMA_MO_CALL_SUCCESS_NTF_STRU;

/** ****************************************************************************
 * Name        : TAF_MMA_CDMA_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                      /* _H2ASN_Skip */
    TAF_MMA_MSG_TYPE_ENUM_UINT32                            enMsgId;    /*_H2ASN_Skip*/
    TAF_MMA_CDMA_CALL_TYPE_ENUM_UINT8                       enCallType;
    VOS_UINT8                                               aucRsv[3];
    VOS_UINT32                                              ulCause;
}TAF_MMA_CDMA_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU;

/** ****************************************************************************
 * Name        : TAF_MMA_CDMA_MO_CALL_END_NTF_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                      /* _H2ASN_Skip */
    TAF_MMA_MSG_TYPE_ENUM_UINT32                            enMsgId;    /* _H2ASN_Skip */
    TAF_MMA_CDMA_CALL_TYPE_ENUM_UINT8                       enCallType;
    VOS_UINT8                                               aucReserve[3];
}TAF_MMA_CDMA_MO_CALL_END_NTF_STRU;


/* Deleted by k902809 for Iteration 11, 2015-3-25, begin */

/* Deleted by k902809 for Iteration 11, Iteration 11 2015-3-25, end */
/* Deleted by k902809 for Iteration 11, 2015-3-25, begin */

/* Deleted by k902809 for Iteration 11, Iteration 11 2015-3-25, end */

/*****************************************************************************
??????    : TAF_MMA_TIME_ZONE_CTIME_STRU
????????  : AT^CTIME????????

  1.??    ??   : 2014??12??27??
    ??    ??   : x00314862
    ????????   : ????
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucYear;
    VOS_UINT8                           ucMonth;
    VOS_UINT8                           ucDay;
    VOS_UINT8                           ucHour;
    VOS_UINT8                           ucMinute;
    VOS_UINT8                           ucSecond;
    VOS_INT8                            cTimeZone;
    VOS_UINT8                           ucDayltSavings;
}TAF_MMA_TIME_ZONE_CTIME_STRU;


/*****************************************************************************
??????    : TAF_MMA_CTIME_IND_STRU
????????  : AT^CTIME????????

  1.??    ??   : 2014??12??27??
    ??    ??   : x00314862
    ????????   : ????
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpid;
    VOS_UINT8                           aucReserve[1];
    TAF_MMA_TIME_ZONE_CTIME_STRU        stTimezoneCTime;
}TAF_MMA_CTIME_IND_STRU;



/*****************************************************************************
??????    : TAF_MMA_CFREQ_LOCK_SET_PARA_STRU
????????  : AT^CFREQLOCK????????

  1.??    ??   : 2014??12??29??
    ??    ??   : y00307564
    ????????   : ????
*******************************************************************************/
typedef TAF_NVIM_CFREQ_LOCK_CFG_STRU TAF_MMA_CFREQ_LOCK_SET_PARA_STRU;

/*****************************************************************************
??????    : TAF_MMA_CFREQ_LOCK_SET_REQ_STRU
????????  : AT^CFREQLOCK????????????????

  1.??    ??   : 2014??12??29??
    ??    ??   : y00307564
    ????????   : ????
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulModuleId;         /* ????PID */
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserve[1];
    TAF_MMA_CFREQ_LOCK_SET_PARA_STRU    stCFreqLockPara;
}TAF_MMA_CFREQ_LOCK_SET_REQ_STRU;

/*****************************************************************************
??????    : TAF_MMA_CFREQ_LOCK_SET_CNF_STRU
????????  : AT^CFREQLOCK????????????????

  1.??    ??   : 2014??12??29??
    ??    ??   : y00307564
    ????????   : ????
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                                  ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                           stCtrl;
    VOS_UINT32                                  ulRslt;
}TAF_MMA_CFREQ_LOCK_SET_CNF_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_CFREQ_LOCK_QRY_REQ_STRU
 ????????  : ??????????????????????

 ????????      :
  1.??    ??   : 2014??12??25??
    ??    ??   : m00312079
    ????????   : ??????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
}TAF_MMA_CFREQ_LOCK_QUERY_REQ_STRU;

/*****************************************************************************
??????    : TAF_MMA_CFREQ_LOCK_QUERY_CNF_STRU
????????  : AT^CFREQLOCK????????????????

  1.??    ??   : 2014??12??29??
    ??    ??   : y00307564
    ????????   : ????
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulModuleId;         /* ????PID */
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_MMA_CFREQ_LOCK_SET_PARA_STRU    stCFreqLockPara;
}TAF_MMA_CFREQ_LOCK_QUERY_CNF_STRU;


/*****************************************************************************
 ??????    : TAF_MMA_CDMA_CSQ_MODE_ENUM_UINT8
 ????????  : ??????????
  1.??    ??   : 2014??12??25??
    ??    ??   : m00312079
    ????????   : ??????
*****************************************************************************/
enum TAF_MMA_CDMA_CSQ_MODE_ENUM
{
    TAF_MMA_CDMA_CSQ_MODE_DISABLE       = 0,
    TAF_MMA_CDMA_CSQ_MODE_ENABLE        = 1,
    TAF_MMA_CDMA_CSQ_MODE_BUTT
};

typedef VOS_UINT8 TAF_MMA_CDMA_CSQ_MODE_ENUM_UINT8;

/*****************************************************************************
 ??????    : TAF_MMA_HDR_CSQ_MODE_ENUM_UINT8
 ????????  : ??????????
  1.??    ??   : 2015??10??21??
    ??    ??   : C00299064
    ????????   : ??????
*****************************************************************************/
enum TAF_MMA_HDR_CSQ_MODE_ENUM
{
    TAF_MMA_HDR_CSQ_MODE_DISABLE       = 0,
    TAF_MMA_HDR_CSQ_MODE_ENABLE        = 1,
    TAF_MMA_HDR_CSQ_MODE_BUTT
};

typedef VOS_UINT8 TAF_MMA_HDR_CSQ_MODE_ENUM_UINT8;

/*****************************************************************************
 ??????    : TAF_MMA_HDR_CSQ_PARA_STRU
 ????????  :

 ????????      :
  1.??    ??   : 2015??10??21??
    ??    ??   : C00299064
    ????????   : ??????
*****************************************************************************/
typedef struct
{
    TAF_MMA_HDR_CSQ_MODE_ENUM_UINT8               enMode;                         /*????????????*/
    VOS_UINT8                                     aucRsv[3];
    VOS_UINT8                                     ucTimeInterval;                 /*??????????????????????????????*/
    VOS_UINT8                                     ucRssiThreshold;                /*??????????????RSSI??????????????????ucRssiThreshold??????*/
    VOS_UINT8                                     ucSnrThreshold;                 /*??????????????SNR??????????????????ucSnrThreshold??????,????????*/
    VOS_UINT8                                     ucEcioThreshold;                /*??????????????ECIO??????????????????ucEcioThreshold??????,????????*/
}TAF_MMA_HDR_CSQ_PARA_STRU;



/*****************************************************************************
 ??????    : TAF_MMA_CDMA_CSQ_STRU
 ????????  : ????ID_TAF_MMA_CDMACSQ_SET_REQ??????

 ????????      :
  1.??    ??   : 2014??12??25??
    ??    ??   : m00312079
    ????????   : ????????
  2.??    ??   : 2015??10??16??
    ??    ??   : m00312079
    ????????   : DTS2015101505057:????ec/Io??????????
*****************************************************************************/
typedef struct
{
    TAF_MMA_CDMA_CSQ_MODE_ENUM_UINT8              enMode;                         /*????????????*/
    VOS_UINT8                                     ucTimeInterval;                 /*??????????????????????????????*/
    VOS_UINT8                                     ucRssiRptThreshold;             /*??????????????RSSI??????????????????ucRssiRptThreshold??????*/
    VOS_UINT8                                     ucEcIoRptThreshold;             /*??????????????ec/Io??????????????????ucEcIoRptThreshold??????*/
}TAF_MMA_CDMACSQ_PARA_STRU;


/*****************************************************************************
 ??????    : TAF_MMA_CDMACSQ_SET_REQ_STRU
 ????????  : ??????????????????????

 ????????      :
  1.??    ??   : 2014??12??25??
    ??    ??   : m00312079
    ????????   : ??????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_MMA_CDMACSQ_PARA_STRU           stCdmaCsqPara;
}TAF_MMA_CDMACSQ_SET_REQ_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_CDMACSQ_SET_CNF_STRU
 ????????  :

 ????????      :
  1.??    ??   : 2014??12??25??
    ??    ??   : m00312079
    ????????   : ??????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserve[1];
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt;
}TAF_MMA_CDMACSQ_SET_CNF_STRU;
/*****************************************************************************
??????    : TAF_MMA_SIG_QUALITY_RPT_INFO_STRU
????????  : CDMACSQ????????

  1.??    ??   : 2014??12??27??
    ??    ??   : m00312079
    ????????   : ????

  2.??    ??   : 2015??10??16??
    ??    ??   : m00312079
    ????????   : DTS2015101505057:????ec/Io??????????
*******************************************************************************/
typedef struct
{
    VOS_INT16                           sCdmaRssi;
    VOS_INT16                           sCdmaEcIo;
}TAF_MMA_SIG_QUALITY_RPT_INFO_STRU;
/*****************************************************************************
??????    : TAF_MMA_CDMACSQ_QUERY_CNF_STRU
????????  : AT^CDMACSQ????????????????

  1.??    ??   : 2014??12??27??
    ??    ??   : m00312079
    ????????   : ????
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_MMA_CDMA_CSQ_MODE_ENUM_UINT8    enMode;
    VOS_UINT8                           ucTimeInterval;
    VOS_UINT8                           ucRssiRptThreshold;
    VOS_UINT8                           ucEcIoRptThreshold;
    TAF_MMA_SIG_QUALITY_RPT_INFO_STRU   stSigQualityInfo;
}TAF_MMA_CDMACSQ_QUERY_CNF_STRU;
/*****************************************************************************
??????    : TAF_MMA_CDMACSQ_IND_STRU
????????  : CDMACSQ????????????

  1.??    ??   : 2014??12??27??
    ??    ??   : m00312079
    ????????   : ????

  2.??    ??   : 2015??10??16??
    ??    ??   : m00312079
    ????????   : DTS2015101505057:????ec/Io??????????
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpid;
    VOS_UINT8                           aucReserve[1];
    VOS_INT16                           sCdmaRssi;
    VOS_INT16                           sCdmaEcIo;
}TAF_MMA_CDMACSQ_IND_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_CDMACSQ_QRY_REQ_STRU
 ????????  : ??????????????????????

 ????????      :
  1.??    ??   : 2014??12??25??
    ??    ??   : m00312079
    ????????   : ??????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
}TAF_MMA_CDMACSQ_QRY_REQ_STRU;


/*****************************************************************************
??????    : TAF_MMA_CLMODE_IND_STRU
????????  : clmode????????????

  1.??    ??   : 2015??10??22??
    ??    ??   : f00279542
    ????????   : ????
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpid;
    VOS_UINT8                           ucIsCLMode;
}TAF_MMA_CLMODE_IND_STRU;

/*****************************************************************************
??????    : TAF_MMA_CFPLMN_SET_REQ_STRU
????????  : AT^CFPLMN????????PLMN????

  1.??    ??   : 2015??2??4??
    ??    ??   : f00279542
    ????????   : ????
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_PH_FPLMN_OPERATE_STRU           stCFPlmnPara;
}TAF_MMA_CFPLMN_SET_REQ_STRU;

/*****************************************************************************
??????    : TAF_MMA_CFPLMN_QUERY_REQ_STRU
????????  : AT^CFPLMN????????PLMN????

  1.??    ??   : 2015??2??4??
    ??    ??   : f00279542
    ????????   : ????
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
}TAF_MMA_CFPLMN_QUERY_REQ_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_CFPLMN_SET_CNF_STRU
 ????????  : mma ??????confirm????

  1.??    ??   : 2015??2??4??
    ??    ??   : f00279542
    ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32                            ulMsgName;          /*_H2ASN_Skip*/
    TAF_MMA_APP_CFPLMN_OPER_RESULT_ENUM_UINT32              enRslt;
    TAF_MMA_CTRL_STRU                                       stCtrl;
    TAF_UINT16                                              usPlmnNum;
    TAF_UINT8                                               aucReserved[2];
    TAF_PLMN_ID_STRU                                        astPlmn[TAF_USER_MAX_PLMN_NUM];
}TAF_MMA_CFPLMN_SET_CNF_STRU;
/*****************************************************************************
 ??????    : TAF_MMA_CFPLMN_QUERY_CNF_STRU
 ????????  : mma ??????confirm????

  1.??    ??   : 2015??2??4??
    ??    ??   : f00279542
    ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32                            ulMsgName;          /*_H2ASN_Skip*/
    TAF_MMA_APP_CFPLMN_OPER_RESULT_ENUM_UINT32              enRslt;
    TAF_MMA_CTRL_STRU                                       stCtrl;
    TAF_UINT16                                              usPlmnNum;
    TAF_UINT8                                               aucReserved[2];
    TAF_PLMN_ID_STRU                                        astPlmn[TAF_USER_MAX_PLMN_NUM];
}TAF_MMA_CFPLMN_QUERY_CNF_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_SIM_FORMAT_PLMN_STRU
 ????????  : Sim PLMN ID??????????
 1.??    ??   : 2015??2??17??
   ??    ??   : b00269685
   ????????   : ????
*****************************************************************************/
typedef struct {
    VOS_UINT8                           aucSimPlmn[TAF_MMA_SIM_FORMAT_PLMN_LEN];
    VOS_UINT8                           aucReserve[1];
}TAF_MMA_SIM_FORMAT_PLMN_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_SIM_PLMN_WITH_RAT_STRU
 ????????  : sim PLMN??Rat??????
  1.??    ??   : 2015??10??13??
    ??    ??   : n00355355
    ????????   : ????
*****************************************************************************/
typedef struct
{
    TAF_PLMN_ID_STRU                    stPlmnId;                               /* PLMN ID */
    VOS_UINT16                          usSimRat;                               /* SIM?????????????????? */
    VOS_UINT8                           aucReserve[2];
}TAF_MMA_SIM_PLMN_WITH_RAT_STRU;


/*****************************************************************************
 ??????    : TAF_MMA_DPLMN_INFO_SET_STRU
 ????????  : set dplmnlist??????dplmn??????????ehplmn??????????????
  1.??    ??   : 2015??10??13??
    ??    ??   : n00355355
    ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usDplmnNum;                                     /* ????DPLMN?????????? */
    VOS_UINT8                           ucEhPlmnNum;                                    /* EHPLMN??????*/
    VOS_UINT8                           ucReserve;
    TAF_PLMN_ID_STRU                    astEhPlmnInfo[TAF_MMA_MAX_EHPLMN_NUM];          /* EHPLMN ID???? */
    TAF_MMA_SIM_PLMN_WITH_RAT_STRU      astDplmnList[TAF_MMA_MAX_DPLMN_NUM];            /* DPLMN???? */
}TAF_MMA_DPLMN_INFO_SET_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_DPLMN_SET_REQ_STRU
 ????????  : AT+DPLMN????DPLMN????????????
  1.??    ??   : 2015??10??13??
    ??    ??   : n00355355
    ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    VOS_UINT8                           ucSeq;                                          /* ?????? */
    VOS_UINT8                           aucVersionId[TAF_MMA_VERSION_INFO_LEN];         /* ??????????????xx.xx.xxx */
    VOS_UINT8                           ucReserve[2];
    TAF_MMA_DPLMN_INFO_SET_STRU         stDplmnInfo;
}TAF_MMA_DPLMN_SET_REQ_STRU;


/*****************************************************************************
??????    : TAF_MMA_PREF_PLMN_SET_REQ_STRU
????????  : AT+CPOL????????????????

  1.??    ??   : 2014??2??3??
    ??    ??   : y00307564
    ????????   : ????
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_PH_SET_PREFPLMN_STRU            stPrefPlmn;
}TAF_MMA_PREF_PLMN_SET_REQ_STRU;

/*****************************************************************************
??????    : TAF_MMA_PREF_PLMN_SET_CNF_STRU
????????  : AT+CPOL????????????????

  1.??    ??   : 2014??2??3??
    ??    ??   : y00307564
    ????????   : ????
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                                              ulMsgName;          /*_H2ASN_Skip*/
    VOS_UINT16                                              usClientId;
    VOS_UINT8                                               ucOpId;
    VOS_UINT8                                               aucReserved[1];
    TAF_MMA_APP_PREF_PLMN_OPER_RESULT_ENUM_UINT32           enRslt;
}TAF_MMA_PREF_PLMN_SET_CNF_STRU;

/*****************************************************************************
??????    : TAF_MMA_PREF_PLMN_QUERY_REQ_STRU
????????  : AT+CPOL????????????????

  1.??    ??   : 2014??2??3??
    ??    ??   : y00307564
    ????????   : ????
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_MMA_CPOL_INFO_QUERY_REQ_STRU    stCpolInfo;
}TAF_MMA_PREF_PLMN_QUERY_REQ_STRU;

/*****************************************************************************
??????    : TAF_MMA_PREF_PLMN_QUERY_CNF_STRU
????????  : AT+CPOL????????????????

  1.??    ??   : 2014??2??3??
    ??    ??   : y00307564
    ????????   : ????
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                                              ulMsgName;          /*_H2ASN_Skip*/
    VOS_UINT16                                              usClientId;
    VOS_UINT8                                               ucOpId;
    VOS_UINT8                                               aucReserved[1];
    VOS_UINT32                                              ulFromIndex;
    VOS_UINT32                                              ulValidPlmnNum;   /* ???????????????????????? */
    TAF_PLMN_NAME_LIST_STRU                                 stPlmnName;
    TAF_MMA_APP_PREF_PLMN_OPER_RESULT_ENUM_UINT32           enRslt;
}TAF_MMA_PREF_PLMN_QUERY_CNF_STRU;

/*****************************************************************************
??????    : TAF_MMA_PREF_PLMN_TEST_REQ_STRU
????????  : AT+CPOL????????????????

  1.??    ??   : 2014??2??3??
    ??    ??   : y00307564
    ????????   : ????
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    MN_PH_PREF_PLMN_TYPE_ENUM_U8        enPrefPlmnType;
    VOS_UINT8                           aucReserve[3];
}TAF_MMA_PREF_PLMN_TEST_REQ_STRU;

/*****************************************************************************
??????    : TAF_MMA_PREF_PLMN_TEST_CNF_STRU
????????  : AT+CPOL????????????????

  1.??    ??   : 2014??2??3??
    ??    ??   : y00307564
    ????????   : ????
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                                              ulMsgName;          /*_H2ASN_Skip*/
    VOS_UINT16                                              usClientId;
    VOS_UINT16                                              usPlmnNum;
    VOS_UINT8                                               ucOpId;
    VOS_UINT8                                               aucReserve[3];
    TAF_MMA_APP_PREF_PLMN_OPER_RESULT_ENUM_UINT32           enRslt;
}TAF_MMA_PREF_PLMN_TEST_CNF_STRU;


/*****************************************************************************
??????    : TAF_MMA_PHONE_MODE_QRY_REQ_STRU
????????  : Phone mode qry req stru

????????         :
    1.??    ??   : 2015??3??19??
      ??    ??   : f00279542
      ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
}TAF_MMA_PHONE_MODE_QRY_REQ_STRU;

/*****************************************************************************
??????    : TAF_MMA_PHONE_MODE_QRY_CNF_STRU
????????  : Phone mode qry cnf stru

????????         :
    1.??    ??   : 2015??3??19??
      ??    ??   : f00279542
      ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause;
    TAF_PH_CMD_TYPE                     ucCmdType;                              /* ???????? */
    TAF_PH_MODE                         ucPhMode;                               /* ???? */
    VOS_UINT8                           aucReserved[2];
}TAF_MMA_PHONE_MODE_QRY_CNF_STRU;

/*****************************************************************************
??????    : TAF_MMA_QUICKSTART_SET_REQ_STRU
????????  : TAF_MMA_CQST_SET_REQ_STRU????

????????         :

    1.??    ??   : 2015??3??19??
      ??    ??   : f00279542
      ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    VOS_UINT32                          ulQuickStartMode;
}TAF_MMA_QUICKSTART_SET_REQ_STRU;
/*****************************************************************************
??????    : TAF_MMA_QUICKSTART_SET_CNF_STRU
????????  : TAF_MMA_QUICKSTART_SET_CNF_STRU????

????????         :

    1.??    ??   : 2015??3??19??
      ??    ??   : f00279542
      ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    TAF_PARA_SET_RESULT                 ucResult;
}TAF_MMA_QUICKSTART_SET_CNF_STRU;

/*****************************************************************************
??????    : TAF_MMA_AUTO_ATTACH_SET_REQ_STRU
????????  : TAF_MMA_AUTO_ATTACH_SET_REQ_STRU????

????????         :

    1.??    ??   : 2015??3??19??
      ??    ??   : f00279542
      ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    VOS_UINT32                          ulAutoAttachEnable;
}TAF_MMA_AUTO_ATTACH_SET_REQ_STRU;

/*****************************************************************************
??????    : TAF_MMA_AUTO_ATTACH_SET_CNF_STRU
????????  : TAF_MMA_AUTO_ATTACH_SET_CNF_STRU????

????????         :
1.??    ??   : 2015??3??19??
  ??    ??   : f00279542
  ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_PARA_SET_RESULT                 ucResult;
    VOS_UINT8                           aucReserved[3];
}TAF_MMA_AUTO_ATTACH_SET_CNF_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_SYSCFG_QRY_REQ_STRU
 ????????  : ??????????????????????

????????         :
    1.??    ??   : 2015??3??19??
      ??    ??   : f00279542
      ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
}TAF_MMA_SYSCFG_QRY_REQ_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_SYSCFG_QRY_CNF_STRU
 ????????  : ??????????????????????

????????         :
    1.??    ??   : 2015??3??19??
      ??    ??   : f00279542
      ????????   : ????
*****************************************************************************/
typedef struct
{

    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause;
    TAF_MMA_SYS_CFG_PARA_STRU           stSysCfg;
}TAF_MMA_SYSCFG_QRY_CNF_STRU;

/*****************************************************************************
??????    : TAF_MMA_SYSCFG_TEST_REQ_STRU
????????  : ^syscfgex ^syscfg test req stru

  1.??    ??   : 2015??3??19??
    ??    ??   : g00261581
    ????????   : ????
*****************************************************************************/
typedef struct
{

    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
}TAF_MMA_SYSCFG_TEST_REQ_STRU;

/*****************************************************************************
??????    : TAF_MMA_SYSCFG_TEST_CNF_STRU
????????  : ^syscfgex ^syscfg test cnf stru

  1.??    ??   : 2015??3??19??
    ??    ??   : g00261581
    ????????   : ????
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause;
    TAF_PH_SYSCFG_BAND_STR              stBandInfo;
}TAF_MMA_SYSCFG_TEST_CNF_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_CRPN_QRY_REQ_STRU
 ????????  : ????????????????

????????         :
    1.??    ??   : 2015??3??19??
      ??    ??   : f00279542
      ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_MMA_CRPN_QRY_PARA_STRU          stCrpnQryPara;
}TAF_MMA_CRPN_QRY_REQ_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_CRPN_QRY_CNF_STRU
 ????????  :????????????????

????????         :
    1.??    ??   : 2015??3??19??
      ??    ??   : f00279542
      ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause;
    TAF_MMA_CRPN_QRY_INFO_STRU          stCrpnQryInfo;
}TAF_MMA_CRPN_QRY_CNF_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_CMM_SET_REQ_STRU
 ????????  : ????NAS??????????????????

????????         :
    1.??    ??   : 2015??3??19??
      ??    ??   : f00279542
      ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    MM_TEST_AT_CMD_STRU                 stCmmSetReq;
}TAF_MMA_CMM_SET_REQ_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_CMM_SET_CNF_STRU
 ????????  :  ????NAS??????????????????

????????         :
    1.??    ??   : 2015??3??19??
      ??    ??   : f00279542
      ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    VOS_UINT32                          ulResult;
    MM_TEST_AT_RSLT_STRU                stAtCmdRslt;                            /* AT???????????? */
}TAF_MMA_CMM_SET_CNF_STRU;

/*****************************************************************************
??????    : TAF_MMA_CERSSI_SET_REQ_STRU
????????  : AT^CERSSI set command stru

  1.??    ??   : 2015??3??19??
    ??    ??   : g00261581
    ????????   : ????
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    VOS_UINT8                           ucActionType;
    VOS_UINT8                           ucRrcMsgType;
    VOS_UINT8                           ucSignThreshold;                        /* 1:rssi????????1db????????^cerssi; 2:rssi????????2db????????
                                                                                   3:rssi????????3db??????????4:rssi????????4db??????????5:rssi????????5db????????;*/
    VOS_UINT8                           ucMinRptTimerInterval;                  /*??????????????(1-20)S*/
}TAF_MMA_CERSSI_SET_REQ_STRU;

/*****************************************************************************
??????    : TAF_MMA_CERSSI_SET_CNF_STRU
????????  : AT^CERSSI set cnf stru

  1.??    ??   : 2015??3??19??
    ??    ??   : g00261581
    ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause;
}TAF_MMA_CERSSI_SET_CNF_STRU;

/*****************************************************************************
??????    : TAF_MMA_CERSSI_QRY_REQ_STRU
????????  : AT^CERSSI qry command stru

  1.??    ??   : 2015??3??19??
    ??    ??   : g00261581
    ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
}TAF_MMA_CERSSI_INFO_QRY_REQ_STRU;

/*****************************************************************************
??????    : TAF_MMA_CERSSI_INFO_QRY_CNF_STRU
????????  : AT^CERSSI qry Cnf stru

  1.??    ??   : 2015??3??19??
    ??    ??   : g00261581
    ????????   : ????
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_PH_RSSI_STRU                    stCerssi;                               /* ???????????????????? */
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause;
}TAF_MMA_CERSSI_INFO_QRY_CNF_STRU;

/*****************************************************************************
??????    : TAF_MMA_MT_POWER_DOWN_REQ_STRU
????????  : ^Cpdw command req stru

  1.??    ??   : 2015??3??19??
    ??    ??   : g00261581
    ????????   : ????
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
}TAF_MMA_MT_POWER_DOWN_REQ_STRU;

/*****************************************************************************
??????    : TAF_MMA_MT_POWER_DOWN_CNF_STRU
????????  : ^Cpdw command cnf stru

  1.??    ??   : 2015??3??19??
    ??    ??   : g00261581
    ????????   : ????
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause;
}TAF_MMA_MT_POWER_DOWN_CNF_STRU;

/*****************************************************************************
??????    : TAF_MMA_PREF_PLMN_TYPE_SET_REQ_STRU
????????  : +cpls command set req stru

  1.??    ??   : 2015??3??19??
    ??    ??   : g00261581
    ????????   : ????
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    MN_PH_PREF_PLMN_TYPE_ENUM_U8        enPrefPlmnType;
    VOS_UINT8                           aucReserve[3];
}TAF_MMA_PREF_PLMN_TYPE_SET_REQ_STRU;

/*****************************************************************************
??????    : TAF_MMA_PREF_PLMN_TYPE_SET_CNF_STRU
????????  : +cpls command set cnf stru

  1.??    ??   : 2015??3??19??
    ??    ??   : g00261581
    ????????   : ????
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause;
    MN_PH_PREF_PLMN_TYPE_ENUM_U8        enPrefPlmnType;
    VOS_UINT8                           aucReserved[3];
}TAF_MMA_PREF_PLMN_TYPE_SET_CNF_STRU;

/*****************************************************************************
??????    : TAF_MMA_CIPHER_QRY_REQ_STRU
????????  : AT^CIPHERQRY? req stru

  1.??    ??   : 2015??3??19??
    ??    ??   : g00261581
    ????????   : ????
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
}TAF_MMA_CIPHER_QRY_REQ_STRU;

/*****************************************************************************
??????    : TAF_MMA_CIPHER_QRY_CNF_STRU
????????  : AT^CIPHERQRY? cnf stru
  1.??    ??   : 2015??3??19??
    ??    ??   : g00261581
    ????????   : ????
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucCipherInfo;
    VOS_UINT8                           aucReserved2[3];
}TAF_MMA_CIPHER_QRY_CNF_STRU;

/*****************************************************************************
??????    : TAF_MMA_LOCATION_INFO_QRY_REQ_STRU
????????  : AT^LOCINFO? qry req stru

  1.??    ??   : 2015??3??19??
    ??    ??   : g00261581
    ????????   : ????
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
}TAF_MMA_LOCATION_INFO_QRY_REQ_STRU;

/*****************************************************************************
??????    : TAF_MMA_LOCATION_INFO_QRY_CNF_STRU
????????  : AT^LOCINFO? cnf stru
  1.??    ??   : 2015??3??19??
    ??    ??   : g00261581
    ????????   : ????
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulMcc;
    VOS_UINT32                          ulMnc;
    VOS_UINT16                          usLac;
    VOS_UINT8                           ucRac;
    VOS_UINT8                           ucRsv;
    VOS_UINT32                          ulCellid;
}TAF_MMA_LOCATION_INFO_QRY_CNF_STRU;

/*****************************************************************************
??????    : TAF_MMA_PLMN_AUTO_RESEL_REQ_STRU
????????  : plmn resel req stru

  1.??    ??   : 2015??3??19??
    ??    ??   : g00261581
    ????????   : ????
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
}TAF_MMA_PLMN_AUTO_RESEL_REQ_STRU;

/*****************************************************************************
??????    : TAF_MMA_PLMN_AUTO_RESEL_CNF_STRU
????????  : Plmn resel cnf stru
  1.??    ??   : 2015??3??19??
    ??    ??   : g00261581
    ????????   : ????
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause;
}TAF_MMA_PLMN_AUTO_RESEL_CNF_STRU;

/*****************************************************************************
??????    : TAF_MMA_PLMN_SPECIAL_SEL_REQ_STRU
????????  : plmn user sel req stru

  1.??    ??   : 2015??3??19??
    ??    ??   : g00261581
    ????????   : ????
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_PLMN_USER_SEL_STRU              stPlmnUserSel;
}TAF_MMA_PLMN_SPECIAL_SEL_REQ_STRU;

/*****************************************************************************
??????    : TAF_MMA_PLMN_SPECIAL_SEL_CNF_STRU
????????  : plmn user sel cnf stru
  1.??    ??   : 2015??3??19??
    ??    ??   : g00261581
    ????????   : ????
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause;
}TAF_MMA_PLMN_SPECIAL_SEL_CNF_STRU;

/*****************************************************************************
??????    : TAF_MMA_PLMN_LIST_ABORT_REQ_STRU
????????  : cops Abort req

  1.??    ??   : 2015??3??19??
    ??    ??   : g00261581
    ????????   : ????
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
}TAF_MMA_PLMN_LIST_ABORT_REQ_STRU;

/*****************************************************************************
??????    : TAF_MMA_PLMN_LIST_ABORT_CNF_STRU
????????  : plmn list Abort cnf

  1.??    ??   : 2015??3??19??
    ??    ??   : g00261581
    ????????   : ????
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause;
}TAF_MMA_PLMN_LIST_ABORT_CNF_STRU;


/* Added by k902809 for Iteration 11, 2015-3-20, begin */


typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
} TAF_MMA_AC_INFO_QRY_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    VOS_UINT32                          ulRslt;
    TAF_MMA_CELL_AC_INFO_STRU           stCellCsAcInfo;
    TAF_MMA_CELL_AC_INFO_STRU           stCellPsAcInfo;
} TAF_MMA_AC_INFO_QRY_CNF_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];
    TAF_MMA_CELL_AC_INFO_STRU           stCellAcInfo;
} TAF_MMA_AC_INFO_CHANGE_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    VOS_UINT16                          usFromIndex;
    VOS_UINT16                          usPlmnNum;
} TAF_MMA_COPN_INFO_QRY_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    VOS_UINT16                          usPlmnNum;
    VOS_UINT16                          usFromIndex;
    VOS_UINT8                           aucContent[4];
} TAF_MMA_COPN_INFO_QRY_CNF_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_SIM_INSERT_STATE_ENUM_UINT32    enSimInsertState;
} TAF_MMA_SIM_INSERT_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    VOS_UINT32                          ulResult;
} TAF_MMA_SIM_INSERT_CNF_STRU;

/* EOPLMN Req */

typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_MMA_SET_EOPLMN_LIST_STRU        stEOPlmnSetPara;
} TAF_MMA_EOPLMN_SET_REQ_STRU;

/* EOPLMN Cnf */

typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];
    VOS_UINT32                          ulResult;
}TAF_MMA_EOPLMN_SET_CNF_STRU;



typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
} TAF_MMA_EOPLMN_QRY_REQ_STRU;



typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           aucVersion[TAF_MAX_USER_CFG_OPLMN_VERSION_LEN];       /* OPLMN List?????? */
    TAF_UINT16                          usOPlmnNum;                                           /* OPLMN???? */
    TAF_UINT8                           aucReserved[2];
    TAF_UINT8                           aucOPlmnList[TAF_MAX_USER_CFG_OPLMN_DATA_LEN];        /* OPLMN??PDU????????EFOplmn???????? */
}TAF_MMA_EOPLMN_QRY_CNF_STRU;

/* Net SCAN request */

typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    VOS_UINT16                          usCellNum;                              /* ???????????????????????????? */
    VOS_INT16                           sCellPow;                               /* ?????????? */
    TAF_MMA_RAT_TYPE_ENUM_UINT8         enRat;                                  /* ?????????????????? */
    VOS_UINT8                           aucReserve[3];
    TAF_USER_SET_PREF_BAND64            stBand;                                 /* ????????*/
}TAF_MMA_NET_SCAN_REQ_STRU;

/* Net SCAN Confirmation */

typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    TAF_MMA_NET_SCAN_RESULT_ENUM_UINT8  enResult;
    TAF_MMA_NET_SCAN_CAUSE_ENUM_UINT8   enCause;
    VOS_UINT8                           ucFreqNum;
    VOS_UINT8                           aucReserved[2];
    TAF_MMA_NET_SCAN_INFO_STRU          astNetScanInfo[TAF_MMA_NET_SCAN_MAX_FREQ_NUM];
}TAF_MMA_NET_SCAN_CNF_STRU;


/* ABORT_NET_SCAN_REQ */

typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
} TAF_MMA_NET_SCAN_ABORT_REQ_STRU;

/** ****************************************************************************
 * Name        : TAF_MMA_CDMA_LOC_INFO_RAT_MODE_ENUM_UINT8
 *
 * Description :
 *******************************************************************************/
enum TAF_MMA_CDMA_LOC_INFO_RAT_MODE_ENUM
{
    TAF_MMA_CDMA_LOC_INFO_RAT_MODE_INVALID   = 0x00,
    TAF_MMA_CDMA_LOC_INFO_RAT_MODE_1X        = 0x01,
    TAF_MMA_CDMA_LOC_INFO_RAT_MODE_DO        = 0x02,
};
typedef VOS_UINT8 TAF_MMA_CDMA_LOC_INFO_RAT_MODE_ENUM_UINT8;

/* CLOCINFO */
/*****************************************************************************
??????    : TAF_MMA_CLOCINFO_PARA_STRU
????????  : ^CLOCINFO????????????

  1.??    ??   : 2015??11??28??
    ??    ??   : l00359089
    ????????   : ????
*******************************************************************************/
typedef struct
{
    TAF_MMA_CDMA_LOC_INFO_RAT_MODE_ENUM_UINT8               ucRatMode;
    VOS_UINT8                                               aucRsv[3];
    VOS_UINT32                                              ulMcc;
    VOS_UINT32                                              ulMnc;
    VOS_INT32                                               lSid;
    VOS_INT32                                               lNid;
    VOS_UINT16                                              usPrevInUse;
    VOS_UINT8                                               aucReserve[2];
    VOS_UINT32                                              ulBaseId;           /* Base stationidentification */
    VOS_INT32                                               lBaseLatitude;      /* Base stationlatitude */
    VOS_INT32                                               lBaseLongitude;     /* Base stationLongitude */
}TAF_MMA_CLOCINFO_PARA_STRU;

/*****************************************************************************
??????    : TAF_MMA_CLOCINFO_IND_STRU
????????  : ^CLOCINFO????????

  1.??    ??   : 2015??11??28??
    ??    ??   : l00359089
    ????????   : ????
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        enMsgId;                                /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_MMA_CLOCINFO_PARA_STRU          stClocinfoPara;
}TAF_MMA_CLOCINFO_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
} TAF_MMA_CDMA_LOCINFO_QRY_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    VOS_UINT32                          ulRslt;
    TAF_MMA_CLOCINFO_PARA_STRU          stClocinfoPara;
} TAF_MMA_CDMA_LOCINFO_QRY_CNF_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
}TAF_MMA_BATTERY_CAPACITY_QRY_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_MMA_BATTERYPOWER_STRU           stBatteryStatus;
}TAF_MMA_BATTERY_CAPACITY_QRY_CNF_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
}TAF_MMA_HAND_SHAKE_QRY_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    VOS_UINT8                           aucBuf[AT_HS_PARA_MAX_LENGTH];
    VOS_UINT8                           aucReserve[3];
}TAF_MMA_HAND_SHAKE_QRY_CNF_STRU;



/*****************************************************************************
??????    : TAF_MMA_CSIDNID_IND_STRU
????????  : AT^CSIDNID????????

  1.??    ??   : 2014??11??27??
    ??    ??   : g00261581
    ????????   : ????
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    VOS_INT32                           lSid;

}TAF_MMA_CSID_IND_STRU;

/*****************************************************************************
??????    : TAF_MMA_SRV_STATUS_IND_STRU
????????  : ????????????????

  1.??    ??   : 2015??03??30??
    ??    ??   : g00261581
    ????????   : ????
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpid;
    TAF_PHONE_CHANGED_SERVICE_STATUS    ucSrvStatus;
}TAF_MMA_SRV_STATUS_IND_STRU;

/*****************************************************************************
??????    : TAF_MMA_RSSI_INFO_IND_STRU
????????  : RSSI Info Ind Msg

  1.??    ??   : 2015??3??19??
    ??    ??   : g00261581
    ????????   : ????
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];
    VOS_UINT8                           aucCurcRptCfg[TAF_MMA_RPT_CFG_MAX_SIZE];         /* CURC?????????????????? */
    VOS_UINT8                           aucUnsolicitedRptCfg[TAF_MMA_RPT_CFG_MAX_SIZE];  /* ?????????????????????????? */
    TAF_PH_RSSI_STRU                    stRssiInfo;
}TAF_MMA_RSSI_INFO_IND_STRU;

/*****************************************************************************
??????    : TAF_MMA_REG_STATUS_IND_STRU
????????  : PS/CS Reg Status Info Ind Msg

  1.??    ??   : 2015??3??19??
    ??    ??   : g00261581
    ????????   : ????
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];
    TAF_PH_REG_STATE_STRU               stRegStatus;
}TAF_MMA_REG_STATUS_IND_STRU;

/*****************************************************************************
??????    : TAF_MMA_REG_REJ_INFO_IND_STRU
????????  : Reg Rej Info Ind

  1.??    ??   : 2015??3??19??
    ??    ??   : g00261581
    ????????   : ????
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];
    TAF_PH_REG_REJ_INFO_STRU            stRegRejInfo;
}TAF_MMA_REG_REJ_INFO_IND_STRU;

/*****************************************************************************
??????    : TAF_MMA_PLMN_SElECTION_INFO_IND_STRU
????????  : Plmn Selection Info Ind Msg

  1.??    ??   : 2015??3??19??
    ??    ??   : g00261581
    ????????   : ????
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];
    TAF_MMA_PLMN_SELECTION_INFO_STRU    stPlmnSelectInfo;
}TAF_MMA_PLMN_SElECTION_INFO_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
} TAF_MMA_SPN_QRY_REQ_STRU;



typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];
    TAF_MMA_SPN_PARA_STRU               stMnMmaSpnInfo;
} TAF_MMA_SPN_QRY_CNF_STRU;



typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
} TAF_MMA_MMPLMNINFO_QRY_REQ_STRU;



typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];
    TAF_MMA_MM_INFO_PLMN_NAME_STRU      stMmPlmnInfo;
} TAF_MMA_MMPLMNINFO_QRY_CNF_STRU;



typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
} TAF_MMA_LAST_CAMP_PLMN_QRY_REQ_STRU;



typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];
    TAF_PLMN_ID_STRU                    stPlmnId;
} TAF_MMA_LAST_CAMP_PLMN_QRY_CNF_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
} TAF_MMA_USER_SRV_STATE_QRY_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];
    VOS_UINT32                          ulCsSrvExistFlg;                        /* CS???????? */
    VOS_UINT32                          ulPsSrvExistFlg;                        /* PS???????? */
} TAF_MMA_USER_SRV_STATE_QRY_CNF_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
} TAF_MMA_POWER_ON_AND_REG_TIME_QRY_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];
    VOS_UINT32                          ulCostTime;
} TAF_MMA_POWER_ON_AND_REG_TIME_QRY_CNF_STRU;

/*****************************************************************************
??????    : TAF_MMA_ACCESS_MODE_QRY_REQ_STRU
????????  : access mode qry req stru

  1.??    ??   : 2015??3??19??
    ??    ??   : g00261581
    ????????   : ????
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
}TAF_MMA_ACCESS_MODE_QRY_REQ_STRU;

/*****************************************************************************
??????    : TAF_MMA_ACCESS_MODE_QRY_CNF_STRU
????????  : Access mode qry cnf stru

  1.??    ??   : 2015??3??19??
    ??    ??   : g00261581
    ????????   : ????
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    MN_MMA_CPAM_RAT_TYPE_ENUM_UINT8     enAccessMode;
    TAF_PH_PLMN_PRIO                    ucPlmnPrio;
    VOS_UINT8                           aucReserved[2];
}TAF_MMA_ACCESS_MODE_QRY_CNF_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_QUICKSTART_QRY_REQ_STRU
 ????????  : ????APP??????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*//* ?????? */
    TAF_MMA_CTRL_STRU                   stCtrl;
} TAF_MMA_QUICKSTART_QRY_REQ_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_QUICKSTART_QRY_CNF_STRU
 ????????  : ????APP??????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*//* ?????? */
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause;
    VOS_UINT32                          ulQuickStartMode;                       /* ???? */
} TAF_MMA_QUICKSTART_QRY_CNF_STRU;

/*****************************************************************************
??????    : TAF_MMA_CSNR_QRY_REQ_STRU
????????  : csnr qry req stru

  1.??    ??   : 2015??3??28??
    ??    ??   : y00322978
    ????????   : ????
******************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*//* ?????? */
    TAF_MMA_CTRL_STRU                   stCtrl;
}TAF_MMA_CSNR_QRY_REQ_STRU;

/*****************************************************************************
??????    : TAF_MMA_CSNR_QRY_CNF_STRU
????????  : csnr qry cnf stru

  1.??    ??   : 2015??3??28??
    ??    ??   : y00322978
    ????????   : ????
******************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*//* ?????? */
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_MMA_CSNR_PARA_STRU              stCsnrPara;
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause;
}TAF_MMA_CSNR_QRY_CNF_STRU;

/*****************************************************************************
??????    : TAF_MMA_CSQ_QRY_REQ_STRU
????????  : csq qry req stru

  1.??    ??   : 2015??3??28??
    ??    ??   : y00322978
    ????????   : ????
******************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*//* ?????? */
    TAF_MMA_CTRL_STRU                   stCtrl;
}TAF_MMA_CSQ_QRY_REQ_STRU;

/*****************************************************************************
??????    : TAF_MMA_CSQ_QRY_CNF_STRU
????????  : csq qry cnf stru

  1.??    ??   : 2015??3??28??
    ??    ??   : y00322978
    ????????   : ????
******************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*//* ?????? */
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_PH_RSSI_STRU                    stCsq;
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause;
}TAF_MMA_CSQ_QRY_CNF_STRU;


/*****************************************************************************
??????    : TAF_MMA_CSQLVL_QRY_REQ_STRU
????????  : csqlvl qry req stru

  1.??    ??   : 2015??3??28??
    ??    ??   : y00322978
    ????????   : ????
******************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*//* ?????? */
    TAF_MMA_CTRL_STRU                   stCtrl;
}TAF_MMA_CSQLVL_QRY_REQ_STRU;

/*****************************************************************************
??????    : TAF_MMA_CSQLVL_QRY_CNF_STRU
????????  : csqlvl qry cnf stru

  1.??    ??   : 2015??3??28??
    ??    ??   : y00322978
    ????????   : ????
******************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*//* ?????? */
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause;
    TAF_MMA_CSQLVL_PARA_STRU            stCsqLvlPara;
    TAF_MMA_CSQLVLEXT_PARA_STRU         stCsqLvlExtPara;
    VOS_UINT8                           aucReserved[2];
}TAF_MMA_CSQLVL_QRY_CNF_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_TIME_CHANGE_IND_STRU
 ????????  : mma????TIME change??????
 1.??    ??   : 2015??3??30??
   ??    ??   : Y00322978
   ????????   : ????
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* _H2ASN_Skip */
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];
    VOS_UINT8                           aucLSAID[3];
    VOS_UINT8                           ucIeFlg;
    VOS_INT8                            cLocalTimeZone;
    VOS_UINT8                           ucDST;
    VOS_UINT8                           aucReserve[2];
    VOS_UINT8                           aucCurcRptCfg[TAF_MMA_RPT_CFG_MAX_SIZE];
    VOS_UINT8                           aucUnsolicitedRptCfg[TAF_MMA_RPT_CFG_MAX_SIZE];
    TIME_ZONE_TIME_STRU                 stUniversalTimeandLocalTimeZone;
}TAF_MMA_TIME_CHANGE_IND_STRU;


/*****************************************************************************
 ??????    : TAF_MMA_MODE_CHANGE_IND_STRU
 ????????  : mma????MODE change??????
 1.??    ??   : 2015??3??30??
   ??    ??   : Y00322978
   ????????   : ????
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* _H2ASN_Skip */
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    TAF_PH_INFO_RAT_TYPE                RatType;
    TAF_SYS_SUBMODE_ENUM_UINT8          ucSysSubMode;
    VOS_UINT8                           aucReserve[3];
}TAF_MMA_MODE_CHANGE_IND_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_PLMN_CHANGE_IND_STRU
 ????????  : mma????MODE change??????
 1.??    ??   : 2015??3??30??
   ??    ??   : Y00322978
   ????????   : ????
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* _H2ASN_Skip */
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];
    TAF_PLMN_ID_STRU                    stCurPlmn;
}TAF_MMA_PLMN_CHANGE_IND_STRU;

/*****************************************************************************
??????    : TAF_MMA_COPS_QRY_REQ_STRU
????????  : cops qry req stru

  1.??    ??   : 2015??3??19??
    ??    ??   : g00261581
    ????????   : ????
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
}TAF_MMA_COPS_QRY_REQ_STRU;

/*****************************************************************************
??????    : TAF_MMA_COPS_QRY_CNF_STRU
????????  : Cops qry cnf stru

  1.??    ??   : 2015??3??19??
    ??    ??   : g00261581
    ????????   : ????
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];
    TAF_PH_NETWORKNAME_STRU             stCopsInfo;
}TAF_MMA_COPS_QRY_CNF_STRU;

/*****************************************************************************
??????    : TAF_MMA_DPLMN_QRY_REQ_STRU
????????  : ID_TAF_MMA_DPLMN_QRY_REQ????????????

  1.??    ??   : 2015??10??8??
    ??    ??   : n00355355
    ????????   : ????
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
}TAF_MMA_DPLMN_QRY_REQ_STRU;


/*****************************************************************************
 ??????    : TAF_MMA_DPLMN_QRY_CNF_STRU
 ????????  : ID_TAF_MMA_DPLMN_QRY_CNF????????????
  1.??    ??   : 2015??10??9??
    ??    ??   : n00355355
    ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    TAF_MMA_CTRL_STRU                   stCtrl;
    VOS_UINT8                           aucVersionId[NAS_VERSION_LEN];
    VOS_UINT8                           aucReverse[3];
}TAF_MMA_DPLMN_QRY_CNF_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_DPLMN_SET_CNF_STRU
 ????????  : ID_TAF_MMA_DLMN_SET_CNF????????
  1.??    ??   : 2015??10??12??
    ??    ??   : n00355355
    ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    TAF_MMA_CTRL_STRU                   stCtrl;
    VOS_UINT32                          ulRslt;
}TAF_MMA_DPLMN_SET_CNF_STRU;


/*****************************************************************************
??????    : TAF_MMA_REG_STATE_QRY_REQ_STRU
????????  : reg status qry req stru

  1.??    ??   : 2015??3??19??
    ??    ??   : g00261581
    ????????   : ????
  2.??    ??   : 2015??8??19??
    ??    ??   : w00176964
    ????????   : DTS2015081907463????
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32                            ulMsgName;          /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                                       stCtrl;
    TAF_MMA_QRY_REG_STATUS_TYPE_ENUM_UINT32                 enQryRegStaType;
}TAF_MMA_REG_STATE_QRY_REQ_STRU;

/*****************************************************************************
??????    : TAF_MMA_REG_STATE_QRY_CNF_STRU
????????  : Reg state qry cnf stru

  1.??    ??   : 2015??3??19??
    ??    ??   : g00261581
    ????????   : ????
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_PH_REG_STATE_STRU               stRegInfo;
}TAF_MMA_REG_STATE_QRY_CNF_STRU;

/*****************************************************************************
??????    : TAF_MMA_AUTO_ATTACH_QRY_REQ_STRU
????????  : Auto attach qry req stru

  1.??    ??   : 2015??3??19??
    ??    ??   : g00261581
    ????????   : ????
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
}TAF_MMA_AUTO_ATTACH_QRY_REQ_STRU;

/*****************************************************************************
??????    : TAF_MMA_AUTO_ATTACH_QRY_CNF_STRU
????????  : Auto attach qry cnf stru

  1.??    ??   : 2015??3??19??
    ??    ??   : g00261581
    ????????   : ????
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause;
    VOS_UINT8                           ucAutoAttachFlag;
    VOS_UINT8                           aucReserved[3];
}TAF_MMA_AUTO_ATTACH_QRY_CNF_STRU;

/*****************************************************************************
??????    : TAF_MMA_SYSINFO_QRY_REQ_STRU
????????  : System Info qry req stru

  1.??    ??   : 2015??3??19??
    ??    ??   : g00261581
    ????????   : ????
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    VOS_UINT32                          ulSysInfoExFlag;                        /* ????????^sysinfo ???? ^sysinfoex ???? */
}TAF_MMA_SYSINFO_QRY_REQ_STRU;

/*****************************************************************************
??????    : TAF_MMA_SYSINFO_QRY_CNF_STRU
????????  : System Info qry cnf stru

  1.??    ??   : 2015??3??19??
    ??    ??   : g00261581
    ????????   : ????
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           ucIsSupport;
    TAF_PH_SYSINFO_STRU                 stSysInfo;
}TAF_MMA_SYSINFO_QRY_CNF_STRU;

/*****************************************************************************
??????    : TAF_MMA_ANTENNA_INFO_QRY_REQ_STRU
????????  : Antenna Info qry req stru

  1.??    ??   : 2015??3??19??
    ??    ??   : g00261581
    ????????   : ????
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
}TAF_MMA_ANTENNA_INFO_QRY_REQ_STRU;

/*****************************************************************************
??????    : TAF_MMA_ANTENNA_INFO_QRY_CNF_STRU
????????  : Antenna Info qry cnf stru

  1.??    ??   : 2015??3??19??
    ??    ??   : g00261581
    ????????   : ????
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause;
    MN_MMA_ANQUERY_PARA_STRU            stAntennaInfo;
}TAF_MMA_ANTENNA_INFO_QRY_CNF_STRU;

/*****************************************************************************
??????    : TAF_MMA_HOME_PLMN_QRY_REQ_STRU
????????  : Aphplmn Info qry req stru

  1.??    ??   : 2015??3??19??
    ??    ??   : g00261581
    ????????   : ????
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
}TAF_MMA_HOME_PLMN_QRY_REQ_STRU;

/*****************************************************************************
??????    : TAF_MMA_EHPLMN_INFO_STRU
????????  : Aphplmn Info qry req stru

  1.??    ??   : 2015??10??23??
    ??    ??   : s00217060
    ????????   : ????
******************************************************************************/
typedef struct
{
    VOS_UINT8                           aucImsi[NAS_MAX_IMSI_LENGTH];
    VOS_UINT8                           ucHplmnMncLen;
    VOS_UINT8                           aucReserve[2];
    VOS_UINT32                          ulEHplmnNum;
    TAF_PLMN_ID_STRU                    astEHplmnList[TAF_MMA_MAX_EHPLMN_NUM];
}TAF_MMA_EHPLMN_INFO_STRU;

/*****************************************************************************
??????    : TAF_MMA_HOME_PLMN_QRY_CNF_STRU
????????  : Aphplmn Info qry cnf stru

  1.??    ??   : 2015??3??19??
    ??    ??   : g00261581
    ????????   : ????
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause;
    TAF_MMA_EHPLMN_INFO_STRU            stEHplmnInfo;
}TAF_MMA_HOME_PLMN_QRY_CNF_STRU;

/*****************************************************************************
??????    : TAF_MMA_RATTYPE_CHANGE_NTF_STRU
????????  : Aps ntf mma rattype change stru

  1.??    ??   : 2015??5??15??
    ??    ??   : y00314741
    ????????   : ????
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                     /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;     /*_H2ASN_Skip*/
    TAF_MMA_PS_RAT_TYPE_ENUM_UINT32     enRatType;
}TAF_MMA_PS_RAT_TYPE_NTF_STRU;

/*****************************************************************************
??????    : TAF_MMA_ATTACH_REQ_STRU
????????  : AT??MMA????ATTACH????????????????

  1.??    ??   : 2015??4??9??
    ??    ??   : h00313353
    ????????   : ????
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_TYPE_ENUM_UINT32        enMsgName;
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_MMA_ATTACH_TYPE_ENUM_UINT8      enAttachType;
    VOS_UINT8                           aucRsved[3];
}TAF_MMA_ATTACH_REQ_STRU;

/*****************************************************************************
??????    : TAF_MMA_ATTACH_CNF_STRU
????????  : MMA??AT????ATTACH????????????????

  1.??    ??   : 2015??4??9??
    ??    ??   : h00313353
    ????????   : ????
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_TYPE_ENUM_UINT32            enMsgName;
    TAF_MMA_CTRL_STRU                       stCtrl;
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32     enRslt;
    TAF_ERROR_CODE_ENUM_UINT32              enErrorCause;
}TAF_MMA_ATTACH_CNF_STRU;

/*****************************************************************************
??????    : TAF_MMA_ATTACH_QRY_REQ_STRU
????????  : AT??MMA????ATTACH????????????????????

  1.??    ??   : 2015??4??9??
    ??    ??   : h00313353
    ????????   : ????
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_TYPE_ENUM_UINT32            enMsgName;
    TAF_MMA_CTRL_STRU                       stCtrl;
    TAF_MMA_SERVICE_DOMAIN_ENUM_UINT8       enDomainType;
    VOS_UINT8                               aucReserved[3];
}TAF_MMA_ATTACH_STATUS_QRY_REQ_STRU;

/*****************************************************************************
??????    : TAF_MMA_ATTACH_QRY_CNF_STRU
????????  : MMA??AT????ATTACH????????????????????????

  1.??    ??   : 2015??4??9??
    ??    ??   : h00313353
    ????????   : ????
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_TYPE_ENUM_UINT32            enMsgName;
    TAF_MMA_CTRL_STRU                       stCtrl;
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32     enRslt;
    TAF_ERROR_CODE_ENUM_UINT32              enErrorCause;
    TAF_MMA_SERVICE_DOMAIN_ENUM_UINT8       enDomainType;
    TAF_MMA_ATTACH_STATUS_ENUM_UINT8        enCsStatus;
    TAF_MMA_ATTACH_STATUS_ENUM_UINT8        enPsStatus;
    VOS_UINT8                               aucReserved[1];
}TAF_MMA_ATTACH_STATUS_QRY_CNF_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_CVER_QUERY_REQ_STRU
 ????????  : AT^1XCHAN????????????

 ????????      :
  1.??    ??   : 2015??05??16??
    ??    ??   : z00316370
    ????????   : ??????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;
    TAF_MMA_CTRL_STRU                   stCtrl;
}TAF_MMA_1XCHAN_QUERY_REQ_STRU;

/*****************************************************************************
??????    : TAF_MMA_CVER_QUERY_CNF_STRU
????????  : AT^1XCHAN????????????????

  1.??    ??   : 2015??05??16??
    ??    ??   : z00316370
    ????????   : ????
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_UINT32                          ulRslt;
    VOS_UINT16                          usChannel;
    VOS_UINT8                           aucReserve[2];
}TAF_MMA_1XCHAN_QUERY_CNF_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_CVER_QUERY_REQ_STRU
 ????????  : AT^CVER????????????

 ????????      :
  1.??    ??   : 2015??05??16??
    ??    ??   : z00316370
    ????????   : ??????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;
    TAF_MMA_CTRL_STRU                   stCtrl;
}TAF_MMA_CVER_QUERY_REQ_STRU;

/*****************************************************************************
??????    : TAF_MMA_CVER_QUERY_CNF_STRU
????????  : AT^CVER????????????????

  1.??    ??   : 2015??05??16??
    ??    ??   : z00316370
    ????????   : ????
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_UINT32                          ulRslt;
    TAF_MMA_1X_CAS_P_REV_ENUM_UINT8     enPrevInUse;
    VOS_UINT8                           aucReserve[3];
}TAF_MMA_CVER_QUERY_CNF_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_STATE_QUERY_REQ_STRU
 ????????  : AT^GETST????????????

 ????????      :
  1.??    ??   : 2015??05??16??
    ??    ??   : z00316370
    ????????   : ??????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;
    TAF_MMA_CTRL_STRU                   stCtrl;
}TAF_MMA_STATE_QUERY_REQ_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_HANDSET_STATE_STRU
 ????????  : ??????????????
 1.??    ??   : 2015??5??16??
   ??    ??   : z00316370
   ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCasState;
    VOS_UINT8                           ucCasSubSta;
    VOS_UINT8                           aucReserve[2];
}TAF_MMA_HANDSET_STATE_STRU;

/*****************************************************************************
??????    : TAF_MMA_STATE_QUERY_CNF_STRU
????????  : AT^GETST????????????????

  1.??    ??   : 2015??05??16??
    ??    ??   : z00316370
    ????????   : ????
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_UINT32                          ulRslt;
    TAF_MMA_HANDSET_STATE_STRU          stHandsetSta;
}TAF_MMA_STATE_QUERY_CNF_STRU;


/*****************************************************************************
 ??????    : TAF_MMA_CHIGHVER_QUERY_REQ_STRU
 ????????  : AT^CHIGHVER????????????

 ????????      :
  1.??    ??   : 2015??05??16??
    ??    ??   : z00316370
    ????????   : ??????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;
    TAF_MMA_CTRL_STRU                   stCtrl;
}TAF_MMA_CHIGHVER_QUERY_REQ_STRU;

/*****************************************************************************
??????    : TAF_MMA_CHIGHVER_QUERY_CNF_STRU
????????  : AT^CHIGHVER????????????????

  1.??    ??   : 2015??05??16??
    ??    ??   : z00316370
    ????????   : ????
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_UINT32                          ulRslt;
    TAF_MMA_1X_CAS_P_REV_ENUM_UINT8     enHighRev;
    VOS_UINT8                           aucReserve[3];
}TAF_MMA_CHIGHVER_QUERY_CNF_STRU;


/*****************************************************************************
??????    : TAF_MMA_QUIT_CALLBACK_SET_REQ_STRU
????????  : at QCCB req??????

  1.??    ??   : 2015??05??16??
    ??    ??   : y00322978
    ????????   : ????
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;
    TAF_MMA_CTRL_STRU                   stCtrl;
}TAF_MMA_QUIT_CALLBACK_SET_REQ_STRU;
/*****************************************************************************
??????    : TAF_MMA_QUIT_CALLBACK_SET_CNF_STRU
????????  : at QCCB cnf??????

  1.??    ??   : 2015??05??16??
    ??    ??   : y00322978
    ????????   : ????
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCode;
}TAF_MMA_QUIT_CALLBACK_SET_CNF_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_SID_WHITE_LIST_STRU
 ????????  : ??????SID??MCC????

 1.??    ??   : 2015??7??2??
   ??    ??   : y00322978
   ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usStartSid;
    VOS_UINT16                          usEndSid;
    VOS_UINT32                          ulMcc;
}TAF_MMA_SID_WHITE_LIST_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_OPER_LOCK_WHITE_SID_STRU
 ????????  : ??????SID??????????
  1.??    ??   : 2015??7??2??
    ??    ??   : y00322978
    ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnable;                          /* ?????????????? */
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          usWhiteSysNum;                     /* ????????????????,??????0?????????????????? */
    TAF_MMA_SID_WHITE_LIST_STRU         astSysInfo[TAF_MMA_MAX_WHITE_LOCK_SID_NUM];
}TAF_MMA_OPER_LOCK_WHITE_SID_STRU;
/*****************************************************************************
 ??????    : TAF_MMA_CSIDLIST_SET_REQ_STRU
 ????????  : SID?????????? ??????????????
  1.??    ??   : 2015??7??2??
    ??    ??   : y00322978
    ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_MMA_OPER_LOCK_WHITE_SID_STRU    stWhiteSidInfo;

}TAF_MMA_CSIDLIST_SET_REQ_STRU;
/*****************************************************************************
 ??????    : TAF_MMA_CSIDLIST_SET_CNF_STRU
 ????????  : SID?????????? cnf??????????
  1.??    ??   : 2015??7??2??
    ??    ??   : y00322978
    ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCode;
}TAF_MMA_CSIDLIST_SET_CNF_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_1X_EMC_CALL_BACK_NTF_STRU
 ????????  : EMC CALL BACK ??????????????
  1.??    ??   : 2015??7??2??
    ??    ??   : y00322978
    ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*//* ??????    */
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;          /*_H2ASN_Skip*//* ??????    */
    TAF_MMA_CTRL_STRU                   stCtrl;
    VOS_UINT32                          ulIsInCallBack;     /* ????????CallBack?????? */
}TAF_MMA_1X_EMC_CALL_BACK_NTF_STRU;
/*****************************************************************************
 ??????    : TAF_MMA_1X_EMC_CALL_BACK_QRY_REQ_STRU
 ????????  : EMC CALL BACK ??????????????
  1.??    ??   : 2015??7??2??
    ??    ??   : y00322978
    ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;
    TAF_MMA_CTRL_STRU                   stCtrl;
}TAF_MMA_1X_EMC_CALL_BACK_QRY_REQ_STRU;
/*****************************************************************************
 ??????    : TAF_MMA_1X_EMC_CALL_BACK_QRY_CNF_STRU
 ????????  : EMC CALL BACK ??????????????
  1.??    ??   : 2015??7??2??
    ??    ??   : y00322978
    ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;
    TAF_MMA_CTRL_STRU                   stCtrl;
    VOS_UINT32                          ucIsInCallBackMode;
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCode;
}TAF_MMA_1X_EMC_CALL_BACK_QRY_CNF_STRU;



/*****************************************************************************
 ??????    : TAF_MMA_HDR_CSQ_SET_REQ_STRU
 ????????  : ????HDR??????????????
  1.??    ??   : 2015??10??20??
    ??    ??   : c00299064
    ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_MMA_HDR_CSQ_PARA_STRU           stHdrCsqSetting;

}TAF_MMA_HDR_CSQ_SET_REQ_STRU;

/*****************************************************************************
 ??????    : MMA_TAF_HDR_CSQ_SET_CNF_STRU
 ????????  : ????HDR????????????????CNF
  1.??    ??   : 2015??10??20??
    ??    ??   : c00299064
    ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt;
}MMA_TAF_HDR_CSQ_SET_CNF_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_HDR_CSQ_QRY_SETTING_REQ_STRU
 ????????  : ????HDR??????????????
  1.??    ??   : 2015??10??20??
    ??    ??   : c00299064
    ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;
    TAF_MMA_CTRL_STRU                   stCtrl;
}TAF_MMA_HDR_CSQ_QRY_SETTING_REQ_STRU;

/*****************************************************************************
 ??????    : MMA_TAF_HDR_CSQ_QRY_SETTING_CNF_STRU
 ????????  : ????HDR????????????????????
  1.??    ??   : 2015??10??20??
    ??    ??   : c00299064
    ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_MMA_HDR_CSQ_PARA_STRU           stHdrCsq;
    VOS_INT16                           sHdrRssi;
    VOS_INT16                           sHdrSnr;
    VOS_INT16                           sHdrEcio;
    VOS_UINT8                           aucRsv[2];
}MMA_TAF_HDR_CSQ_QRY_SETTING_CNF_STRU;

/*****************************************************************************
 ??????    : MMA_TAF_HDR_CSQ_VALUE_IND_STRU
 ????????  : HDR????????????
  1.??    ??   : 2015??10??20??
    ??    ??   : c00299064
    ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;
    TAF_MMA_CTRL_STRU                   stCtrl;
    VOS_INT16                           sHdrRssi;
    VOS_INT16                           sHdrSnr;
    VOS_INT16                           sHdrEcio;
    VOS_UINT8                           aucRsv[2];
}MMA_TAF_HDR_CSQ_VALUE_IND_STRU;



/*****************************************************************************
 ??????    : TAF_MMA_CURR_SID_NID_QRY_REQ_STRU
 ????????  : current system sid nid ??????????????
  1.??    ??   : 2015??10??23??
    ??    ??   : f00279542
    ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;
    TAF_MMA_CTRL_STRU                   stCtrl;
}TAF_MMA_CURR_SID_NID_QRY_REQ_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_CURR_SID_NID_QRY_CNF_STRU
 ????????  : home sid nid ??????????
  1.??    ??   : 2015??10??23??
    ??    ??   : f00279542
    ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCode;
    VOS_INT32                           lSid;             /**<  System identification */
    VOS_INT32                           lNid;             /**<  Network identification */
}TAF_MMA_CURR_SID_NID_QRY_CNF_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_INIT_LOC_INFO_IND_STRU
 ????????  : ??????????????????????
  1.??    ??   : 2015??12??10??
    ??    ??   : l00324781
    ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpid;
    VOS_UINT8                           aucReserve[1];
    VOS_UINT32                          ulMcc;  /* LTE????????????????????????Mcc??????f???????????? */
    VOS_INT32                           lSid;   /* 1x????????????????Sid?? lSid????-1???????????? */
}TAF_MMA_INIT_LOC_INFO_IND_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_ROAMING_MODE_SWITCH_IND_STRU
 ????????  : ????????????????????
 1.??    ??   : 2016??01??19??
   ??    ??   : y00245242
   ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        enMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpid;
    VOS_UINT8                           aucReserve[1];
}TAF_MMA_ROAMING_MODE_SWITCH_IND_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_CCTC_ROAMING_NW_INFO_REPORT_IND_STRU
 ????????  : ????MCC??SID????????
 1.??    ??   : 2016??01??20??
   ??    ??   : y00245242
   ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        enMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpid;
    VOS_UINT8                           aucReserve[1];
    VOS_INT32                           lSid;
    VOS_UINT32                          ul3Gpp2Mcc;
    VOS_UINT32                          ul3GppMcc;
    VOS_UINT32                          ulModeType;
}TAF_MMA_CTCC_ROAMING_NW_INFO_REPORT_IND_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_CCTC_ROAMING_NW_INFO_QRY_REQ_STRU
 ????????  : ????MCC??SID????????
 1.??    ??   : 2016??01??20??
   ??    ??   : y00245242
   ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_TYPE_ENUM_UINT32        enMsgName;
    TAF_MMA_CTRL_STRU                   stCtrl;
}TAF_MMA_CTCC_ROAMING_NW_INFO_QRY_REQ_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_CCTC_ROAMING_NW_INFO_QRY_CNF_STRU
 ????????  : ????MCC??SID????????
 1.??    ??   : 2016??01??20??
   ??    ??   : y00245242
   ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_TYPE_ENUM_UINT32        enMsgName;
    TAF_MMA_CTRL_STRU                   stCtrl;
    VOS_INT32                           lSid;             /**<  System identification */
    VOS_UINT32                          ul3Gpp2Mcc;       /**<  3GPP2 MCC */
    VOS_UINT32                          ul3GppMcc;        /**<  3GPP MCC */
    VOS_UINT32                          ulModeType;       /* ??????????CL????GUL??0????GUL??1????CL */
}TAF_MMA_CTCC_ROAMING_NW_INFO_QRY_CNF_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_CCTC_ROAMING_NW_INFO_QRY_REQ_STRU
 ????????  : ????MCC??SID????????
 1.??    ??   : 2016??01??20??
   ??    ??   : y00245242
   ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_TYPE_ENUM_UINT32        enMsgName;
    TAF_MMA_CTRL_STRU                   stCtrl;
    VOS_UINT8                           ucCtRoamRtpFlag;
    VOS_UINT8                           aucReserved[3];
}TAF_MMA_CTCC_ROAMING_NW_INFO_RTP_CFG_SET_REQ_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_CCTC_ROAMING_NW_INFO_QRY_CNF_STRU
 ????????  : ????MCC??SID????????
 1.??    ??   : 2016??01??20??
   ??    ??   : y00245242
   ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_TYPE_ENUM_UINT32        enMsgName;
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCode;
}TAF_MMA_CTCC_ROAMING_NW_INFO_RTP_CFG_SET_CNF_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_CTCC_OOS_COUNT_SET_REQ_STRU
 ????????  : ????????????OOS????????????
 1.??    ??   : 2016??02??15??
   ??    ??   : w00242748
   ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_TYPE_ENUM_UINT32        enMsgName;
    TAF_MMA_CTRL_STRU                   stCtrl;
    VOS_UINT16                          usClOosCount;
    VOS_UINT16                          usGulOosCount;
}TAF_MMA_CTCC_OOS_COUNT_SET_REQ_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_CTCC_OOS_COUNT_SET_CNF_STRU
 ????????  : ID_TAF_MMA_CTCC_OOS_COUNT_SET_CNF????????
  1.??    ??   : 2016??2??15??
    ??    ??   : w00242748
    ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_TYPE_ENUM_UINT32        enMsgName;
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCode;
}TAF_MMA_CTCC_OOS_COUNT_SET_CNF_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_IMS_DOMAIN_CFG_SET_REQ_STRU
 ????????  : IMS????????????????????????
  1.??    ??   : 2015??10??26??
    ??    ??   : h00360002
    ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_TYPE_ENUM_UINT32                  ulMsgName;
    TAF_MMA_CTRL_STRU                             stCtrl;
    TAF_MMA_IMS_DOMAIN_CFG_TYPE_ENUM_UINT32       enImsDoaminCfg;
}TAF_MMA_IMS_DOMAIN_CFG_SET_REQ_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_IMS_DOMAIN_CFG_QRY_REQ_STRU
 ????????  : IMS????????????????????????
  1.??    ??   : 2015??10??26??
    ??    ??   : h00360002
    ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;
    TAF_MMA_CTRL_STRU                   stCtrl;
}TAF_MMA_IMS_DOMAIN_CFG_QRY_REQ_STRU;


/*****************************************************************************
 ??????    : TAF_MMA_IMS_DOMAIN_CFG_SET_CNF_STRU
 ????????  : IMS????????????????????????????
  1.??    ??   : 2015??10??26??
    ??    ??   : h00360002
    ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_TYPE_ENUM_UINT32                ulMsgName;
    VOS_UINT16                                  usClientId;
    VOS_UINT8                                   ucOpid;
    VOS_UINT8                                   aucReserve[1];
    TAF_MMA_IMS_DOMAIN_CFG_RESULT_ENUM_UINT32   enImsDomainCfgResult;
}TAF_MMA_IMS_DOMAIN_CFG_SET_CNF_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_IMS_DOMAIN_CFG_QRY_CNF_STRU
 ????????  : IMS????????????????????????????
  1.??    ??   : 2015??10??26??
    ??    ??   : h00360002
    ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_TYPE_ENUM_UINT32                ulMsgName;
    VOS_UINT16                                  usClientId;
    VOS_UINT8                                   ucOpid;
    VOS_UINT8                                   aucReserve[1];
    TAF_MMA_IMS_DOMAIN_CFG_TYPE_ENUM_UINT32     enImsDomainCfgType;
}TAF_MMA_IMS_DOMAIN_CFG_QRY_CNF_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_ROAM_IMS_SUPPORT_SET_REQ_STRU
 ????????  : ??????????IMS????????????????

 ????????      :
  1.??    ??   : 2016??3??9??
    ??    ??   : w00316404
    ????????   : ??????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32                ulMsgName;                      /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                           stCtrl;
    TAF_MMA_ROAM_IMS_SUPPORT_ENUM_UINT32        enRoamingImsSupportFlag;
}TAF_MMA_ROAM_IMS_SUPPORT_SET_REQ_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_ROAM_IMS_SUPPORT_SET_CNF_STRU
 ????????  : ??????IMS??????????????????????????
  1.??    ??   : 2016??3??10??
    ??    ??   : w00316404
    ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_TYPE_ENUM_UINT32                    ulMsgName;
    VOS_UINT16                                      usClientId;
    VOS_UINT8                                       ucOpid;
    VOS_UINT8                                       aucReserve[1];
    TAF_MMA_ROAM_IMS_SUPPORT_RESULT_ENUM_UINT32     enRoamImsSupportResult;
}TAF_MMA_ROAM_IMS_SUPPORT_SET_CNF_STRU;

/*****************************************************************************
 ??????    : TAF_MMA_PRLID_QRY_REQ_STRU
 ????????  : ????PRLID ,MLPL version id, MSPL version id??????????
  1.??    ??   : 2016??3??10??
    ??    ??   : w00316404
    ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_TYPE_ENUM_UINT32                    enMsgName;
    TAF_MMA_CTRL_STRU                               stCtrl;
}TAF_MMA_PRLID_QRY_REQ_STRU;
/*****************************************************************************
 ??????    : TAF_MMA_PRLID_QRY_CNF_STRU
 ????????  : ????PRLID ,MLPL version id, MSPL version id CNF ??????????
  1.??    ??   : 2016??3??10??
    ??    ??   : w00316404
    ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_MMA_MSG_TYPE_ENUM_UINT32        enMsgName;                              /*_H2ASN_Skip*/
    TAF_MMA_CTRL_STRU                   stCtrl;
    VOS_INT32                           lPrlSrcType;
    VOS_INT32                           lPrlId;
    VOS_INT32                           lMlplMsplSrcType;
    VOS_INT32                           lMlplId;
    VOS_INT32                           lMsplId;
}TAF_MMA_PRLID_QRY_CNF_STRU;

TAF_UINT32 Taf_DefPhClassType(MN_CLIENT_ID_T        ClientId,
                                      MN_OPERATION_ID_T     OpId,
                                      TAF_PH_MS_CLASS_TYPE  MsClass);

/* Taf_PhoneAttach */
/* Deleted by w00167002 for L-C??????????, 2014-2-17, begin */
/* Deleted by w00167002 for L-C??????????, 2014-2-17, end */
TAF_UINT32 Taf_PhonePinHandle(MN_CLIENT_ID_T      ClientId,
                                      MN_OPERATION_ID_T   OpId,
                                      TAF_PH_PIN_DATA_STRU *pPinData);
TAF_UINT32 Taf_PhonePlmnList(VOS_UINT32                      ulModuleId,
                              MN_CLIENT_ID_T                  usClientId,
                              MN_OPERATION_ID_T               ucOpId,
                              TAF_MMA_PLMN_LIST_PARA_STRU        *pstPlmnListPara
);


VOS_UINT32 TAF_MMA_SetQuickStartReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT32                          ulSetValue
);
VOS_UINT32 TAF_MMA_QryQuickStartReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

VOS_UINT32 Taf_SetCopsFormatTypeReq(
    MN_CLIENT_ID_T                                          usClientId,
    MN_OPERATION_ID_T                                       ucOpId,
    TAF_MMA_COPS_FORMAT_TYPE_SET_REQ_STRU                  *pstCopsFormatType
);

VOS_UINT32 TAF_SetUsimStub(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    TAF_MMA_USIM_STUB_SET_REQ_STRU     *pstUsimStub
);

VOS_UINT32 TAF_SetRefreshStub(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    TAF_MMA_REFRESH_STUB_SET_REQ_STRU  *pstRefreshStub
);

VOS_UINT32 TAF_SetAutoReselStub(
    MN_CLIENT_ID_T                                          usClientId,
    MN_OPERATION_ID_T                                       ucOpId,
    TAF_MMA_AUTO_RESEL_STUB_SET_REQ_STRU                   *pstAutoReselStub
);
TAF_UINT32 TAF_DefLoadDefault(MN_CLIENT_ID_T ClientId, MN_OPERATION_ID_T   OpId);
VOS_BOOL Taf_IsWBandSupported(VOS_UINT16 usBandNo);

VOS_VOID  Taf_GetSyscfgBandGroupStr(TAF_PH_SYSCFG_BAND_STR* pstSysCfgBandStr);

/* MN_MMA_GetSyscfgExLteBandGroupStr */


TAF_UINT32  Taf_QueryCSNR(TAF_INT16 *psCpichRscp,TAF_INT16 *psCpichEcNo);


TAF_UINT32 Taf_UsimRestrictedAccessCommand(
                                MN_CLIENT_ID_T               ClientId,
                                MN_OPERATION_ID_T            OpId,
                                USIMM_RACCESS_REQ_STRU      *pPara);

TAF_UINT32 Taf_PhoneGetNetworkNameForListPlmn( TAF_PH_OPERATOR_NAME_FORMAT_OP_STRU *pstOperName );

VOS_UINT32 Taf_MePersonalisationHandle(
                            MN_CLIENT_ID_T                    ClientId,
                            MN_OPERATION_ID_T                 OpId,
                            TAF_ME_PERSONALISATION_DATA_STRU *pMePersonalData);


VOS_VOID   Taf_GetProductionID(VOS_CHAR *pcDest);


TAF_UINT32  TAF_SetPrefPlmnType(
    MN_PH_PREF_PLMN_TYPE_ENUM_U8        enPrefPlmnType
);


TAF_UINT32 TAF_QryUsimInfo(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    TAF_PH_QRY_USIM_INFO_STRU           *pstInfo
);

TAF_BOOL TAF_IsNormalSrvStatus(VOS_VOID);

TAF_UINT32 TAF_QryCpnnInfo(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    TAF_PH_ICC_TYPE                     IccType
);

VOS_UINT32 MN_PH_RptCostTime( VOS_VOID  );


VOS_UINT8 APP_MN_PH_AppQryPhMode (VOS_VOID);

VOS_UINT8 MN_MMA_GetServiceDomain(VOS_VOID);

TAF_UINT32  Taf_DefMmTestPara(TAF_VOID *pInput,TAF_VOID *pRslt);

/* Modified by w00167002 for L-C??????????, 2014-2-14, begin */
/* Modified by w00167002 for L-C??????????, 2014-2-14, end */


VOS_UINT32  MN_FillAndSndAppReqMsg(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    VOS_UINT16                          usMsgType,
    VOS_VOID                            *pPara,
    VOS_UINT32                          ulParaLen,
    VOS_UINT32                          ulReceiverPid
);

VOS_VOID Taf_GetCurrentAttachStatus(
    TAF_MMA_ATTACH_STATUS_ENUM_UINT8    *penCsResult,
    TAF_MMA_ATTACH_STATUS_ENUM_UINT8    *penPsResult
);

/* Modified by Y00213812 for VoLTE_PhaseI ????, 2013-07-08, begin */
TAF_UINT32 Taf_ParaQuery(
    MN_CLIENT_ID_T              ClientId,
    MN_OPERATION_ID_T           OpId,
    TAF_PARA_TYPE               ParaType,
    TAF_VOID                   *pPara
);


/* Added by s00246516 for L-C??????????, 2014-01-24, Begin */
VOS_UINT32 TAF_MMA_PhoneModeSetReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_PHONE_MODE_PARA_STRU       *pstPhoneModePara
);

VOS_UINT32 TAF_MMA_QryAutoAttachInfoReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

VOS_UINT32 TAF_MMA_QryPhoneModeReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

#if (FEATURE_ON == FEATURE_CSG)
VOS_UINT32 TAF_MMA_CsgListSearchReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_PLMN_LIST_PARA_STRU        *pstPlmnListPara
);
VOS_UINT32 TAF_MMA_AbortCsgListSearchReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

VOS_UINT32 TAF_MMA_SetCsgIdSearch(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_CSG_SPEC_SEARCH_INFO_STRU   *pstUserSelCsgId
);
VOS_UINT32 TAF_MMA_QryCampCsgIdInfoReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

#endif

VOS_UINT32 TAF_MMA_SetSysCfgReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfgPara
);

VOS_UINT32 TAF_MMA_QryEonsUcs2Req(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

VOS_UINT32 TAF_MMA_AcqBestNetworkReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_ACQ_PARA_STRU              *pstAcqPara
);

VOS_UINT32 TAF_MMA_RegReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_REG_PARA_STRU              *pstRegPara
);

VOS_UINT32 TAF_MMA_PowerSaveReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_POWER_SAVE_PARA_STRU       *pstPowerSavePara
);

VOS_UINT32 TAF_MMA_DetachReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_DETACH_PARA_STRU           *pstDetachPara
);

/* Added by s00246516 for L-C??????????, 2014-01-24, End */

VOS_UINT32 TAF_MMA_AttachReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_ATTACH_TYPE_ENUM_UINT8      enAttachType
);
VOS_UINT32 TAF_MMA_AttachStatusQryReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_SERVICE_DOMAIN_ENUM_UINT8   enDomainType
);

VOS_VOID TAF_MMA_SrvAcqReq(
    TAF_MMA_SRV_TYPE_ENUM_UINT8         enSrvType,
    TAF_MMA_SRV_ACQ_RAT_LIST_STRU      *pstRatList
);


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)


VOS_UINT32  TAF_MMA_ProcCFreqLockSetReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_CFREQ_LOCK_SET_PARA_STRU   *pstCFreqLockPara
);

VOS_UINT32 TAF_MMA_ProcCdmaCsqSetReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_CDMACSQ_PARA_STRU          *pstCdmaCsqPara
);

VOS_UINT32 TAF_MMA_ProcCdmaCsqQryReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

VOS_UINT32 TAF_MMA_ProcCFreqLockQryReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

VOS_UINT32  TAF_MMA_Proc1xChanSetReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_CFREQ_LOCK_SET_PARA_STRU   *pstCFreqLockPara
);

VOS_UINT32 TAF_MMA_Proc1xChanQryReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

VOS_UINT32 TAF_MMA_ProcProRevInUseQryReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

VOS_UINT32 TAF_MMA_ProcStateQryReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

VOS_UINT32 TAF_MMA_ProcCHVerQryReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);
VOS_UINT32 TAF_MMA_SetQuitCallBack(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);
VOS_UINT32 TAF_MMA_SetCSidList(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_OPER_LOCK_WHITE_SID_STRU   *pstWhiteSidList
);
VOS_UINT32 TAF_MMA_QryCurrEmcCallBackMode(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

VOS_UINT32 TAF_MMA_ProcHdrCsqSetReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_HDR_CSQ_PARA_STRU          *pstHdrCsqPara
);

VOS_UINT32 TAF_MMA_ProcHdrCsqQryReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);


VOS_UINT32 TAF_MMA_QryCurrSidNid(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

VOS_UINT32 TAF_MMA_QryCtRoamInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

VOS_UINT32 TAF_MMA_SetCtOosCount(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT32                          ulClOosCount,
    VOS_UINT32                          ulGulOosCount
);

VOS_UINT32 TAF_MMA_SetCtRoamInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCtRoamRtpFlag
);

VOS_UINT32 TAF_MMA_QryPrlIdInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);
#endif

extern VOS_UINT32 TAF_MMA_SetFPlmnInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_PH_FPLMN_OPERATE_STRU          *pstCFPlmnPara
);
extern VOS_UINT32 TAF_MMA_QryFPlmnInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

VOS_UINT32 TAF_MMA_SetCpolReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_PH_SET_PREFPLMN_STRU           *pstPrefPlmn
);

VOS_UINT32 TAF_MMA_QueryCpolReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_CPOL_INFO_QUERY_REQ_STRU   *pstCpolInfo
);

VOS_UINT32 TAF_MMA_TestCpolReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    MN_PH_PREF_PLMN_TYPE_ENUM_U8        enPrefPlmnType
);

extern VOS_UINT32 TAF_MMA_PlmnAutoReselReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);
VOS_UINT32  TAF_MMA_SetAutoAttachReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT32                          ulSetValue
);

extern VOS_UINT32 TAF_MMA_PlmnSpecialSelReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_PLMN_USER_SEL_STRU             *pstPlmnUserSel
);

extern VOS_UINT32 TAF_MMA_AbortPlmnListReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

extern VOS_UINT32 TAF_MMA_QryLocInfoReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

extern VOS_UINT32 TAF_MMA_QryCipherReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

extern VOS_UINT32 TAF_MMA_SetPrefPlmnTypeReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    MN_PH_PREF_PLMN_TYPE_ENUM_U8       *penPrefPlmnType
);

extern VOS_UINT32 TAF_MMA_MtPowerDownReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);
VOS_UINT32 TAF_MMA_SetCerssiReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_START_INFO_IND_STRU            *pstStartInfoInd
);

VOS_UINT32 TAF_MMA_QryCerssiReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

VOS_UINT32 TAF_MMA_QryAccessModeReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

VOS_UINT32 TAF_MMA_QryCopsInfoReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

VOS_UINT32 TAF_MMA_QryRegStateReq(
    VOS_UINT32                                              ulModuleId,
    VOS_UINT16                                              usClientId,
    VOS_UINT8                                               ucOpId,
    TAF_MMA_QRY_REG_STATUS_TYPE_ENUM_UINT32                 enRegStaType
);

VOS_UINT32 TAF_MMA_SetDplmnListReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucSeq,
    VOS_UINT8                          *pucVersion,
    TAF_MMA_DPLMN_INFO_SET_STRU        *pstDplmnInfo
);

VOS_UINT32 TAF_MMA_QryDplmnListReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);


VOS_UINT32 TAF_MMA_QrySystemInfoReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT32                          ulSysInfoExFlag
);

VOS_UINT32 TAF_MMA_QryAntennaInfoReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

VOS_UINT32 TAF_MMA_QryApHplmnInfoReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

VOS_UINT32  TAF_MMA_QryCsnrReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

VOS_UINT32 TAF_MMA_QryCsqReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);
VOS_UINT32 TAF_MMA_QryCsqlvlReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);


VOS_UINT32 TAF_MMA_QryBatteryCapacityReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);
VOS_UINT32 TAF_MMA_QryHandShakeReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

/* Added by k902809 for Iteration 11, 2015-3-23, begin */
VOS_UINT32 TAF_MMA_QryAcInfoReq(
    VOS_UINT32                          ulModuleId,
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId
);

VOS_UINT32 TAF_MMA_QryCopnInfoReq(
    VOS_UINT32                          ulModuleId,
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT16                          usFromIndex,
    MN_OPERATION_ID_T                   ucOpId
);

VOS_UINT32 TAF_MMA_SimInsertReq(
    VOS_UINT32                          ulModuleId,
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    TAF_SIM_INSERT_STATE_ENUM_UINT32    enSimInsertState
);

VOS_UINT32 TAF_MMA_SetEOPlmnReq(
    VOS_UINT32                          ulModuleId,
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    TAF_MMA_SET_EOPLMN_LIST_STRU       *pstEOPlmnCfg
);

VOS_UINT32 TAF_MMA_QryEOPlmnReq(
    VOS_UINT32                          ulModuleId,
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId
);

VOS_UINT32 TAF_MMA_QryCLocInfoReq(
    VOS_UINT32                          ulModuleId,
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId
);

VOS_UINT32 TAF_MMA_NetScanReq(
    VOS_UINT32                          ulModuleId,
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    TAF_MMA_NET_SCAN_REQ_STRU          *pstNetScanSetPara
);

VOS_UINT32 TAF_MMA_NetScanAbortReq(
    VOS_UINT32                          ulModuleId,
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId
);

VOS_UINT32 TAF_MMA_QrySpnReq(
    VOS_UINT32                          ulModuleId,
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId
);

VOS_UINT32 TAF_MMA_QryMMPlmnInfoReq(
    VOS_UINT32                          ulModuleId,
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId
);

VOS_UINT32 TAF_MMA_QryPlmnReq(
    VOS_UINT32                          ulModuleId,
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId
);

VOS_UINT32 TAF_MMA_QryUserSrvStateReq(
    VOS_UINT32                          ulModuleId,
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId
);

VOS_UINT32 TAF_MMA_QryApPwrOnAndRegTimeReq(
    VOS_UINT32                          ulModuleId,
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId
);

/* Added by k902809 for Iteration 11, Iteration 11 2015-3-23, end */
VOS_UINT32 TAF_MMA_QryCrpnReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_CRPN_QRY_PARA_STRU         *pstCrpnQryReq
);

VOS_UINT32 TAF_MMA_SetCmmReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    MM_TEST_AT_CMD_STRU                *pstTestAtCmd
);

VOS_UINT32 TAF_MMA_TestSysCfgReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

extern VOS_UINT32 TAF_MMA_QrySyscfgReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);
#if (FEATURE_ON == FEATURE_IMS)
VOS_UINT32 TAF_MMA_SetImsSwitchReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_IMS_SWITCH_SET_ENUM_UINT8   enImsSwitch
);

VOS_UINT32 TAF_MMA_QryImsSwitchReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

VOS_UINT32 TAF_MMA_SetVoiceDomainReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_VOICE_DOMAIN_ENUM_UINT32    enVoiceDomain
);

VOS_UINT32 TAF_MMA_QryVoiceDomainReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);
VOS_UINT32 TAF_MMA_SetRoamImsSupportReq(
    VOS_UINT32                           ulModuleId,
    VOS_UINT16                           usClientId,
    VOS_UINT8                            ucOpId,
    TAF_MMA_ROAM_IMS_SUPPORT_ENUM_UINT32 enRoamImsSupport
);
#endif

#if (FEATURE_ON == FEATURE_IMS)
VOS_UINT32 TAF_MMA_SetImsDomainCfgReq(
    VOS_UINT32                                   ulModuleId,
    VOS_UINT16                                   usClientId,
    VOS_UINT8                                    ucOpId,
    TAF_MMA_IMS_DOMAIN_CFG_TYPE_ENUM_UINT32      enImsDomainCfg
);

VOS_UINT32 TAF_MMA_QryImsDomainCfgReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);
#endif


#if ((VOS_OS_VER == VOS_WIN32) || (TAF_OS_VER == TAF_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of TafAppMma.h */
