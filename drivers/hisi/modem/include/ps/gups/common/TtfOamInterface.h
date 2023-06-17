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

#ifndef __TTFOAMINTERFACE_H__
#define __TTFOAMINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "vos.h"
#include "TTFLink.h"
#include "PsTypeDef.h"

#pragma pack(4)

#define GRM_MNTN_TS_TOTAL                           (8)
#define GRLC_MNTN_MAX_TBF_NUM                       (1)
#define  WTTF_MNTN_MAX_AM_RB_NUM                    (8)
#define  WTTF_MNTN_MAX_TM_RB_NUM                    (4)
#define  WTTF_MNTN_MAX_UM_RB_NUM                    (6)

#define  WTTF_MNTN_MAX_RB_ID                        (32)
#define  WTTF_MNTN_MAX_FLX_RLC_SIZE_LEVEL_CNT       (10)
#define  WTTF_MNTN_RLC_AM_MAX_SN_NUM                (4096)

#define CTTF_HRPD_MNTN_DEFAULT_RLP_MAX_NUM   (2)

#define CTTF_HRPD_MNTN_MF_RLP_MAX_NUM        (6)

#define CTTF_HRPD_MNTN_EMF_RLP_MAX_NUM       (6)

#define   CTTF_1X_MAC_MNTN_MAX_REPORT_NUM    (64)

#define    CTTF_1X_RLP_MNTN_MAX_NUM    (6)

#define   CTTF_HRPD_RTC3MAC_MNTN_FLOW_MAX_NUM   (8)

#define   CTTF_HRPD_RTC3MAC_MNTN_MAX_RECORD_PACKET_PER_FLOW     (96)
#define   CTTF_HRPD_RTC3MAC_MNTN_MAX_RECORD_T2P_PER_FLOW        (96)
#define   CTTF_HRPD_RTC3MAC_MNTN_MAX_RECORD_HARQ                (96)

#define CTTF_HRPD_MNTN_NUM_SUBFRAME_INFO_INSTANCES              (3)

#define CTTF_HRPD_MNTN_RTC3MAC_INTERLACE_MAX_NUM       (3)

#define IS_WUEPS_PID_RABM(x)            ((I0_WUEPS_PID_RABM == x) || (I1_WUEPS_PID_RABM == x) || (I2_WUEPS_PID_RABM == x))
#define IS_WUEPS_PID_PDCP(x)            (WUEPS_PID_PDCP == x)
#define IS_WUEPS_PID_RLC(x)             (WUEPS_PID_RLC == x)
#define IS_WUEPS_PID_MAC(x)             (WUEPS_PID_MAC == x)
#define IS_WUEPS_PID_WAS(x)             ((WUEPS_PID_WRR == x) || (WUEPS_PID_WCOM == x))
#define IS_UEPS_PID_SN(x)               ((I0_UEPS_PID_SN == x) || (I1_UEPS_PID_SN == x) || (I2_UEPS_PID_SN == x))
#define IS_UEPS_PID_LL(x)               ((I0_UEPS_PID_LL == x) || (I1_UEPS_PID_LL == x) || (I2_UEPS_PID_LL == x))
#define IS_UEPS_PID_GRM(x)              ((I0_UEPS_PID_GRM == x) || (I1_UEPS_PID_GRM == x) || (I2_UEPS_PID_GRM == x))
#define IS_UEPS_PID_DL(x)               ((I0_UEPS_PID_DL == x) || (I1_UEPS_PID_DL == x) || (I2_UEPS_PID_DL == x))
#define IS_UEPS_PID_MM(x)               ((I0_WUEPS_PID_MM == x) || (I1_WUEPS_PID_MM == x) || (I2_WUEPS_PID_MM == x))
#define IS_UEPS_PID_SMS(x)              ((I0_WUEPS_PID_SMS == x) || (I1_WUEPS_PID_SMS == x) || (I2_WUEPS_PID_SMS == x))
#define IS_UEPS_PID_GAS(x)              ((I0_UEPS_PID_GAS == x) || (I1_UEPS_PID_GAS == x) || (I2_UEPS_PID_GAS == x))
#define IS_UEPS_PID_GPHY(x)             ((I0_DSP_PID_GPHY == x) || (I1_DSP_PID_GPHY == x) || (I2_DSP_PID_GPHY == x))

enum TTF_MNTN_MSG_TYPE_ENUM
{
    ID_OM_WTTF_RLC_DATA_TRANS_INFO_REQ          = 0xD001,
    ID_WTTF_OM_RLC_DATA_TRANS_INFO_CNF          = 0xD002,
    ID_WTTF_OM_RLC_DATA_TRANS_INFO_IND          = 0xD003,
    ID_OM_WTTF_ADVANCED_TRACE_CONFIG_REQ        = 0xD004,
    ID_WTTF_OM_ADVANCED_TRACE_CONFIG_CNF        = 0xD005,
    ID_OM_WTTF_RLC_PDU_SIZE_TRANS_INFO_REQ      = 0xD006,
    ID_WTTF_OM_RLC_PDU_SIZE_TRANS_INFO_CNF      = 0xD007,
    ID_WTTF_OM_RLC_PDU_SIZE_TRANS_INFO_IND      = 0xD008,
    ID_OM_WTTF_UPA_DATA_STATUS_G_INFO_REQ       = 0xD009,
    ID_WTTF_OM_UPA_DATA_STATUS_G_INFO_CNF       = 0xD00a,
    ID_WTTF_OM_UPA_DATA_STATUS_G_INFO_IND       = 0xD00b,
    ID_OM_TTF_MNTN_MSG_CTTF_OM_XXX_REQ          = 0xD00c,
    ID_OM_TTF_MNTN_MSG_CTTF_OM_YYY_REQ          = 0xD00d,
    ID_TTF_OM_MNTN_MSG_OM_CTTF_XXX_DATA_IND     = 0xD00e,
    ID_TTF_OM_MNTN_MSG_OM_CTTF_ZZZ_DATA_IND     = 0xD00f,

    ID_GRM_MNTN_OM_GRM_INFO_CFG_REQ             = 0xD104,
    ID_GRM_MNTN_GRM_OM_INFO_CFG_CNF             = 0xD105,
    ID_GRM_MNTN_GRM_OM_INFO                     = 0xD106,
    ID_GRM_MNTN_OM_GRM_THROUGHPUT_CFG_REQ       = 0xD107,
    ID_GRM_MNTN_GRM_OM_THROUGHPUT_CFG_CNF       = 0xD108,
    ID_GRM_MNTN_GRM_OM_THROUGHPUT_INFO          = 0xD109,
    ID_GRM_MNTN_OM_GTTF_ADV_TRACE_SWITCH_REQ    = 0xD10a,
    ID_GRM_MNTN_GTTF_OM_ADV_TRACE_SWITCH_CNF    = 0xD10b,

    ID_RRM_OM_RESOURCE_STATE_INFO_IND           = 0xD210,

    ID_OM_IPS_ADVANCED_TRACE_CONFIG_REQ         = 0xD313,
    ID_IPS_OM_ADVANCED_TRACE_CONFIG_CNF         = 0xD314,
    ID_OM_IPS_MNTN_INFO_CONFIG_REQ              = 0xD315,
    ID_IPS_OM_MNTN_INFO_CONFIG_CNF              = 0xD316,
    ID_IPS_TRACE_INPUT_DATA_INFO                = 0xD317,
    ID_IPS_TRACE_OUTPUT_DATA_INFO               = 0xD318,
    ID_IPS_TRACE_BRIDGE_DATA_INFO               = 0xD319,
    ID_IPS_TRACE_RECV_ARP_PKT                   = 0xD31A,
    ID_IPS_TRACE_SEND_ARP_PKT                   = 0xD31B,
    ID_IPS_TRACE_RECV_DHCPC_PKT                 = 0xD31C,
    ID_IPS_TRACE_SEND_DHCPC_PKT                 = 0xD31D,
    ID_IPS_TRACE_RECV_DHCPS_PKT                 = 0xD31E,
    ID_IPS_TRACE_SEND_DHCPS_PKT                 = 0xD31F,
    ID_IPS_TRACE_APP_CMD                        = 0xD320,
    ID_IPS_TRACE_MNTN_INFO                      = 0xD321,
    ID_IPS_TRACE_BRIDGE_PRE_ROUTING_INFO        = 0xD322,
    ID_IPS_TRACE_BRIDGE_POST_ROUTING_INFO       = 0xD323,
    ID_IPS_TRACE_BRIDGE_LOCAL_IN_INFO           = 0xD324,
    ID_IPS_TRACE_BRIDGE_LOCAL_OUT_INFO          = 0xD325,
    ID_IPS_TRACE_IP4_FORWARD_INFO               = 0xD326,
    ID_IPS_TRACE_IP4_LOCAL_IN_INFO              = 0xD327,
    ID_IPS_TRACE_IP4_LOCAL_OUT_INFO             = 0xD328,
    ID_IPS_TRACE_IP6_FORWARD_INFO               = 0xD329,
    ID_IPS_TRACE_IP6_LOCAL_IN_INFO              = 0xD32A,
    ID_IPS_TRACE_IP6_LOCAL_OUT_INFO             = 0xD32B,
    ID_IPS_TRACE_BR_FORWARD_FLOW_CTRL_START     = 0xD32C,
    ID_IPS_TRACE_BR_FORWARD_FLOW_CTRL_STOP      = 0xD32D,
    ID_IPS_TRACE_ADS_UL                         = 0xD330,
    ID_IPS_TRACE_ADS_DL                         = 0xD331,

    ID_OM_CTTF_1X_MNTN_CONFIG_REQ               = 0xD400,
    ID_CTTF_OM_1X_MNTN_CONFIG_CNF               = 0xD400,
    ID_CTTF_OM_1X_MNTN_FWD_LINK_IND             = 0xD402,
    ID_CTTF_OM_1X_MNTN_REV_LINK_IND             = 0xD403,
    ID_CTTF_OM_1X_MNTN_RLP_STATISTICS_IND       = 0xD404,
    ID_CTTF_OM_1X_MNTN_COMMON_CHANNEL_STATISTICS_IND       = 0xD405,

    ID_OM_IPS_CCORE_ADVANCED_TRACE_CONFIG_REQ   = 0xD513,
    ID_IPS_CCORE_OM_ADVANCED_TRACE_CONFIG_CNF   = 0xD514,
    ID_OM_IPS_CCORE_MNTN_INFO_CONFIG_REQ        = 0xD515,
    ID_IPS_CCORE_OM_MNTN_INFO_CONFIG_CNF        = 0xD516,
    ID_IPS_CCORE_TRACE_INPUT_DATA_INFO          = 0xD517,
    ID_IPS_CCORE_TRACE_OUTPUT_DATA_INFO         = 0xD518,
    ID_IPS_CCORE_TRACE_BRIDGE_DATA_INFO         = 0xD519,
    ID_IPS_CCORE_TRACE_RECV_ARP_PKT             = 0xD51A,
    ID_IPS_CCORE_TRACE_SEND_ARP_PKT             = 0xD51B,
    ID_IPS_CCORE_TRACE_RECV_DHCPC_PKT           = 0xD51C,
    ID_IPS_CCORE_TRACE_SEND_DHCPC_PKT           = 0xD51D,
    ID_IPS_CCORE_TRACE_RECV_DHCPS_PKT           = 0xD51E,
    ID_IPS_CCORE_TRACE_SEND_DHCPS_PKT           = 0xD51F,
    ID_IPS_CCORE_TRACE_APP_CMD                  = 0xD520,
    ID_IPS_CCORE_TRACE_MNTN_INFO                = 0xD521,
    ID_IPS_MNTN_CCORE_IMS_NIC_INFO              = 0xD522,
    ID_IPS_CCORE_TRACE_NIC_DATA_IND             = 0xD523,
    ID_IPS_CCORE_TRACE_NIC_DATA_REQ             = 0xD524,

    ID_OM_PPP_MNTN_CONFIG_REQ                   = 0xD560,
    ID_PPP_OM_MNTN_CONFIG_CNF                   = 0xD561,
    ID_PPP_OM_MNTN_STATISTIC_INFO               = 0xD562,
    ID_OM_PPP_MNTN_TRACE_CONFIG_REQ         = 0xD563,


    ID_IMS_NIC_MNTN_TRACE_RCV_CONFIG_INFO       = 0xD5F1,
    ID_IMS_NIC_MNTN_TRACE_CONFIG_PROC_RSLT      = 0xD5F2,
    ID_IMS_NIC_MNTN_TRACE_RCV_CONFIG_DEL        = 0xD5F3,
    ID_IMS_NIC_MNTN_TRACE_RCV_CONFIG_DEL_RSLT   = 0xD5F4,
    ID_IMS_NIC_MNTN_TRACE_RUN_CMD               = 0xD5F5,
    ID_IMS_NIC_MNTN_TRACE_DNS_CFG               = 0xD5F6,
    ID_IMS_NIC_MNTN_TRACE_DNS_DEL               = 0xD5F7,
    ID_IMS_NIC_MNTN_TRACE_LOG_MSG               = 0xD5F8,
    ID_IMS_NIC_MNTN_TRACE_TCPIP_INPUT_LOG       = 0xD5F9,

    ID_OM_CTTF_HRPD_MNTN_CONFIG_REQ                     = 0xD600,
    ID_CTTF_OM_HRPD_MNTN_CONFIG_CNF                     = 0xD601,
    ID_CTTF_OM_HRPD_MNTN_MODULE_PROTOCOL_STATE_IND      = 0xD602,
    ID_CTTF_OM_HRPD_MNTN_MAC_PROTOCOL_STATISTICS_IND    = 0xD603,
    ID_CTTF_OM_HRPD_MNTN_RLP_STATISTICS_IND             = 0xD604,
    ID_CTTF_OM_HRPD_MNTN_MFPA_RLP_STATISTICS_IND        = 0xD605,
    ID_CTTF_OM_HRPD_MNTN_EMPA_RLP_STATISTICS_IND        = 0xD606,
    ID_CTTF_OM_HRPD_MNTN_REV_LINK_PACKET_INFO_IND       = 0xD607,
    ID_CTTF_OM_HRPD_MNTN_REV_LINK_T2P_STATISTICS_IND    = 0xD608,
    ID_CTTF_OM_HRPD_MNTN_HARQ_INFO_IND                  = 0xD609,
    ID_CTTF_OM_HRPD_MNTN_RTC3MAC_ACK_INFO_IND           = 0xD60A,
    ID_CTTF_OM_HRPD_MNTN_TRACE_MSG_CONFIG_REQ           =0xD60B,

    TTF_MNTN_MSG_TYPE_BUTT                      = 0xFFFF
};
typedef VOS_UINT16 TTF_MNTN_MSG_TYPE_ENUM_UINT16;

enum TTF_MNTN_RPT_CMD_ENUM
{
    TTF_MNTN_RPT_CMD_STOP     = 0x00,
    TTF_MNTN_RPT_CMD_START    = 0x01
};
typedef VOS_UINT8 TTF_MNTN_RPT_CMD_ENUM_UINT8;

enum TTF_MNTN_RLP_RPT_CMD_ENUM
{
    TTF_MNTN_RLP_RPT_CMD_STOP   = 0x00,
    TTF_MNTN_RLP_RPT_CMD_START  = 0x01,
    TTF_MNTN_RLP_RPT_CMD_CLEAR  = 0x02
};
typedef VOS_UINT8 TTF_MNTN_RLP_RPT_CMD_ENUM_UINT8;

enum TTF_MNTN_COMM_RPT_CMD_ENUM
{
    TTF_MNTN_COMM_RPT_CMD_STOP  = 0x00,
    TTF_MNTN_COMM_RPT_CMD_START = 0x01,
    TTF_MNTN_COMM_RPT_CMD_CLEAR = 0x02
};
typedef VOS_UINT8 TTF_MNTN_COMM_RPT_CMD_ENUM_UINT8;

enum IPS_MNTN_INFO_ACTION_ENUM
{
    IPS_MNTN_INFO_REPORT_STOP           = 0, 
    IPS_MNTN_INFO_REPORT_START          = 1
};
typedef VOS_UINT16 IPS_MNTN_INFO_ACTION_ENUM_UINT16;

enum IPS_MNTN_RESULT_TYPE_ENUM
{
    IPS_MNTN_RESULT_OK                  = 0,
    IPS_MNTN_RESULT_START_TIMER_FAIL    = 1,
    IPS_MNTN_RESULT_ALLOC_MEM_FAIL      = 2,
    IPS_MNTN_RESULT_ALLOC_MSG_FAIL      = 3,
    IPS_MNTN_RESULT_INPUT_PARAM_ERR     = 4,
    IPS_MNTN_RESULT_LOCAL_PARAM_ERR     = 5
};
typedef VOS_UINT32  IPS_MNTN_RESULT_TYPE_ENUM_UINT32;

enum GRM_MNTN_OM_REPORT_ACTION_ENUM
{
    GRM_MNTN_OM_REPORT_STOP     = 0,
    GRM_MNTN_OM_REPORT_START    = 1
};

typedef VOS_UINT16 GRM_MNTN_OM_REPORT_ACTION_ENUM_UINT16;

enum GRM_RESULT_TYPE_ENUM
{
    GRM_RESULT_OK                   = 0,
    GRM_RESULT_START_TIMER_FAIL     = 1,
    GRM_RESULT_ALLOC_MEM_FAIL       = 2,
    GRM_RESULT_ALLOC_MSG_FAIL       = 3,
    GRM_RESULT_INPUT_PARAM_ERR      = 4,
    GRM_RESULT_LOCAL_PARAM_ERR      = 5
};
typedef VOS_UINT32  GRM_RESULT_TYPE_ENUM_UINT32;

enum TOOL_GTTF_CFG_SWITCH_ENUM
{
    TOOL_GTTF_CFG_SWITCH_OFF = 0,
    TOOL_GTTF_CFG_SWITCH_ON  = 1
};
typedef VOS_UINT32 TOOL_GTTF_CFG_SWITCH_ENUM_UINT32;

enum GRM_TBF_INFO_TBF_MODE_ENUM
{
    Non_Extend_TBF = 0,
    Extend_TBF    = 1
};
typedef VOS_UINT8 GRM_TBF_INFO_TBF_MODE_ENUM_UINT8;

enum GRM_TBF_INFO_RLC_MODE_ENUM
{
    AM    = 0,
    UM    = 1
};
typedef VOS_UINT8 GRM_TBF_INFO_RLC_MODE_ENUM_UINT8;

enum GRM_TBF_INFO_COUNTDOWN_FLAG_ENUM
{
    No_Start_CV    = 0,
    Start_CV       = 1
};
typedef VOS_UINT8 GRM_TBF_INFO_COUNTDOWN_FLAG_ENUM_UINT8;

enum GRM_TBF_INFO_TI_ENUM
{
    TLLI_Absent           = 0,
    TLLI_Not_Absent       = 1
};
typedef VOS_UINT8 GRM_TBF_INFO_TI_ENUM_UINT8;

enum GRM_TBF_INFO_FINALBLKRXED_ENUM
{
    Not_received    = 0,
    Received        = 1
};
typedef VOS_UINT8 GRM_TBF_INFO_FINALBLKRXED_ENUM_UINT8;

enum GRM_TBF_INFO_EDGE_CODE_SCHEME_ENUM
{
    CS_1       = 0x0000,
    CS_2       = 0x0001,
    CS_3       = 0x0002,
    CS_4       = 0x0003,
    MCS_1      = 0x1000,
    MCS_2      = 0x1001,
    MCS_3      = 0x1002,
    MCS_4      = 0x1003,
    MCS_5      = 0x1004,
    MCS_6      = 0x1005,
    MCS_7      = 0x1006,
    MCS_8      = 0x1007,
    MCS_9      = 0x1008,
    MCS_5_7    = 0x1009,
    MCS_6_9    = 0x100a
};
typedef VOS_UINT16 GRM_TBF_INFO_EDGE_CODE_SCHEME_ENUM_UINT16;

enum GRM_TBF_INFO_TEST_MODE_ENUM
{
    Test_Mode_A_Infinite      = 0,
    Test_Mode_A_Normal        = 1,
    Test_Mode_B               = 2,
    Test_Mode_SRB_LoopBack    = 3
};
typedef VOS_UINT8 GRM_TBF_INFO_TEST_MODE_ENUM_UINT8;

enum GRM_TBF_INFO_TIMESLOT_FLAG_ENUM
{
    Not_Existed           = 0,
    Existed               = 1
};
typedef VOS_UINT8 GRM_TBF_INFO_TIMESLOT_FLAG_ENUM_UINT8;

enum IPS_MNTN_CCORE_INFO_ACTION_ENUM
{
    IPS_MNTN_CCORE_INFO_REPORT_STOP           = 0,
    IPS_MNTN_CCORE_INFO_REPORT_START          = 1
};
typedef VOS_UINT16 IPS_MNTN_CCORE_INFO_ACTION_ENUM_UINT16;

enum IPS_MNTN_CCORE_RESULT_TYPE_ENUM
{
    IPS_MNTN_CCORE_RESULT_OK                  = 0,
    IPS_MNTN_CCORE_RESULT_START_TIMER_FAIL    = 1,
    IPS_MNTN_CCORE_RESULT_ALLOC_MEM_FAIL      = 2,
    IPS_MNTN_CCORE_RESULT_ALLOC_MSG_FAIL      = 3,
    IPS_MNTN_CCORE_RESULT_INPUT_PARAM_ERR     = 4,
    IPS_MNTN_CCORE_RESULT_LOCAL_PARAM_ERR     = 5
};
typedef VOS_UINT32  IPS_MNTN_CCORE_RESULT_TYPE_ENUM_UINT32;

enum WTTF_TRACE_PHY_MAC_SUB_ATTRIB_ENUM
{
    WTTF_TRACE_PHY_MAC_NULL = 0,
    WTTF_TRACE_CTRL_HEADER  = 1,
    WTTF_TRACE_WHOLE_DATA   = 2
};
typedef VOS_UINT8   WTTF_TRACE_PHY_MAC_SUB_ATTRIB_ENUM_UINT8;

enum WTTF_TRACE_MSG_SIMPLE_ATTRIB_ENUM
{
    WTTF_TRACE_MSG_NO   = 0,
    WTTF_TRACE_MSG_YES  = 1
};
typedef VOS_UINT8   WTTF_TRACE_MSG_SIMPLE_ATTRIB_ENUM_UINT8;

enum IPS_MNTN_CCORE_TRACE_CHOSEN_ENUM
{
    IPS_MNTN_CCORE_TRACE_NULL_CHOSEN               =   0,
    IPS_MNTN_CCORE_TRACE_MSG_HEADER_CHOSEN         =   1,
    IPS_MNTN_CCORE_TRACE_CONFIGURABLE_LEN_CHOSEN   =   2,
    IPS_MNTN_CCORE_TRACE_WHOLE_DATA_LEN_CHOSEN     =   3
};
typedef VOS_UINT32   IPS_MNTN_CCORE_TRACE_CHOSEN_ENUM_UINT32;

enum IPS_MNTN_TRACE_CHOSEN_ENUM
{
    IPS_MNTN_TRACE_NULL_CHOSEN               =   0,
    IPS_MNTN_TRACE_MSG_HEADER_CHOSEN         =   1,
    IPS_MNTN_TRACE_CONFIGURABLE_LEN_CHOSEN   =   2,
    IPS_MNTN_TRACE_WHOLE_DATA_LEN_CHOSEN     =   3
};
typedef VOS_UINT32   IPS_MNTN_TRACE_CHOSEN_ENUM_UINT32;

enum TTF_MNTN_TRACE_CHOSEN_ENUM
{
    TTF_MNTN_TRACE_NULL_CHOSEN               =   0,
    TTF_MNTN_TRACE_MSG_HEADER_CHOSEN         =   1,
    TTF_MNTN_TRACE_CONFIGURABLE_LEN_CHOSEN   =   2,
    TTF_MNTN_TRACE_WHOLE_DATA_LEN_CHOSEN     =   3
};
typedef VOS_UINT32   TTF_MNTN_TRACE_CHOSEN_ENUM_UINT32;

enum WTTF_RLC_MNTN_RB_CHOSEN_ENUM
{
    WTTF_RLC_MNTN_RB_NULL_CHOSEN                = 0x0,
    WTTF_RLC_MNTN_RB_SIGNALLING_CHOSEN          = 0x0000000F,
    WTTF_RLC_MNTN_RB_PS_CHOSEN                  = 0xFFFFFFF0,
    WTTF_RLC_MNTN_RB_ALL_CHOSEN                 = 0xFFFFFFFF
};
typedef VOS_UINT32   WTTF_RLC_MNTN_RB_CHOSEN_ENUM_UINT32;

enum CTTF_1X_MAC_MNTN_RATE_ENUM
{
    CTTF_1X_MAC_MNTN_RATE_BLANK    = 0,
    CTTF_1X_MAC_MNTN_RATE_EIGHTH    = 1,
    CTTF_1X_MAC_MNTN_RATE_QUARTER  = 2,
    CTTF_1X_MAC_MNTN_RATE_HALF      = 3,
    CTTF_1X_MAC_MNTN_RATE_FULL      = 4,
    CTTF_1X_MAC_MNTN_RATE_2X        = 5,
    CTTF_1X_MAC_MNTN_RATE_4X        = 6,
    CTTF_1X_MAC_MNTN_RATE_8X        = 7,
    CTTF_1X_MAC_MNTN_RATE_16X       = 8,
    CTTF_1X_MAC_MNTN_RATE_32X       = 9,
    CTTF_1X_MAC_MNTN_RATE_BUTT     = 10
};
typedef VOS_UINT8 CTTF_1X_MAC_MNTN_RATE_ENUM_UINT8;

enum CTTF_1X_MAC_MNTN_RESULT_TYPE_ENUM
{
    CTTF_1X_MAC_MNTN_RESULT_OK                  = 0,
    CTTF_1X_MAC_MNTN_RESULT_START_TIMER_FAIL    = 1,
    CTTF_1X_MAC_MNTN_RESULT_ALLOC_MEM_FAIL      = 2,
    CTTF_1X_MAC_MNTN_RESULT_ALLOC_MSG_FAIL      = 3,
    CTTF_1X_MAC_MNTN_RESULT_INPUT_PARAM_ERR     = 4,
    CTTF_1X_MAC_MNTN_RESULT_LOCAL_PARAM_ERR     = 5
};
typedef VOS_UINT32 CTTF_1X_MAC_MNTN_RESULT_TYPE_ENUM_UINT32;

enum CTTF_1X_MAC_MNTN_RPT_PERIOD_ENUM
{
    CTTF_1X_MAC_MNTN_RPT_PERIOD_1280          = 1280,
};
typedef VOS_UINT32 CTTF_1X_MAC_MNTN_RPT_PERIOD_ENUM_UINT32;

enum CTTF_HRPD_MNTN_RESULT_TYPE_ENUM
{
    CTTF_HRPD_MNTN_RESULT_OK                  = 0,
    CTTF_HRPD_MNTN_RESULT_START_TIMER_FAIL    = 1,
    CTTF_HRPD_MNTN_RESULT_ALLOC_MEM_FAIL      = 2,
    CTTF_HRPD_MNTN_RESULT_ALLOC_MSG_FAIL      = 3,
    CTTF_HRPD_MNTN_RESULT_INPUT_PARAM_ERR     = 4,
    CTTF_HRPD_MNTN_RESULT_LOCAL_PARAM_ERR     = 5
};
typedef VOS_UINT32 CTTF_HRPD_MNTN_RESULT_TYPE_ENUM_UINT32;

enum CTTF_HRPD_MNTN_RPT_PERIOD_ENUM
{
    CTTF_HRPD_MNTN_RPT_PERIOD_1280              = 1280
};

typedef VOS_UINT32 CTTF_HRPD_MNTN_RPT_PERIOD_ENUM_UINT32;

enum CTTF_HRPD_MNTN_RTC_RPT_PERIOD_ENUM
{
    CTTF_HRPD_MNTN_RTC_RPT_PERIOD_640           = 640
};
typedef VOS_UINT32 CTTF_HRPD_MNTN_RTC_RPT_PERIOD_ENUM_UINT32;

enum IPS_MNTN_CCORE_TCPIP_LOG_LEVEL_E_ENUM
{
    IPS_MNTN_CCORE_TCPIP_LOG_LEVEL_CRITICAL = 0,
    IPS_MNTN_CCORE_TCPIP_LOG_LEVEL_ERROR,
    IPS_MNTN_CCORE_TCPIP_LOG_LEVEL_WARNING,
    IPS_MNTN_CCORE_TCPIP_LOG_LEVEL_INFO,
    IPS_MNTN_CCORE_TCPIP_LOG_LEVEL_DEBUG,

    IPS_MNTN_CCORE_TCPIP_LOG_LEVEL_BUIT
};
typedef VOS_UINT8 IPS_MNTN_CCORE_TCPIP_LOG_LEVEL_E_ENUM_UINT8;

enum CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM
{
    CTTF_HRPD_MNTN_DEFAULT_CC_MAC_ENUM                      = 0x00,
    CTTF_HRPD_MNTN_ENHANCE_CC_MAC_ENUM                      = 0x01,
    CTTF_HRPD_MNTN_DEFAULT_AC_MAC_ENUM                      = 0x02,
    CTTF_HRPD_MNTN_ENHANCE_AC_MAC_ENUM                      = 0x03,
    CTTF_HRPD_MNTN_DEFAULT_FTC_MAC_ENUM                     = 0x04,
    CTTF_HRPD_MNTN_ENHANCE_FTC_MAC_ENUM                     = 0x05,
    CTTF_HRPD_MNTN_DEFAULT_RTC_MAC_ENUM                     = 0x06,
    CTTF_HRPD_MNTN_SUBTYPE3_RTC_MAC_ENUM                    = 0x07,
    CTTF_HRPD_MNTN_DEFAULT_AUTHENTICATION_ENUM              = 0x08,
    CTTF_HRPD_MNTN_SHA1_AUTHENTICATION_ENUM                 = 0x09,
    CTTF_HRPD_MNTN_DEFAULT_ENCRYPTION_ENUM                  = 0x0a,
    CTTF_HRPD_MNTN_AES_ENCRYPTION_ENUM                      = 0x0b,
    CTTF_HRPD_MNTN_DEFAULT_SECURITY_ENUM                    = 0x0c,
    CTTF_HRPD_MNTN_GENERIC_SECURITY_ENUM                    = 0x0d,
    CTTF_HRPD_MNTN_DEFAULT_STREAM_ENUM                      = 0x0e,
    CTTF_HRPD_MNTN_DEFAULT_SIGNALING_APP_ENUM               = 0x0f,
    CTTF_HRPD_MNTN_DEFAULT_PACKET_APP_RN_ENUM               = 0x10,
    CTTF_HRPD_MNTN_DEFAULT_PACKET_APP_SN_ENUM               = 0x11,
    CTTF_HRPD_MNTN_TEST_APP_ENUM                            = 0x12,
    CTTF_HRPD_MNTN_MULTI_FLOW_PACKET_APP_RN_ENUM            = 0x13,
    CTTF_HRPD_MNTN_MULTI_FLOW_PACKET_APP_SN_ENUM            = 0x14,
    CTTF_HRPD_MNTN_3G1X_CIRCUIT_SERVICE_NOTIFICATION_APP_ENUM   = 0x15,
    CTTF_HRPD_MNTN_RESERVED_APP_ENUM                        = 0x16,
    CTTF_HRPD_MNTN_ENHANCED_MULTI_FLOW_PACKET_APP_RN_ENUM   = 0x17,
    CTTF_HRPD_MNTN_ENHANCED_MULTI_FLOW_PACKET_APP_SN_ENUM   = 0x18,
    CTTF_HRPD_MNTN_ENHANCED_TEST_APP_ENUM                   = 0x19,
    CTTF_HRPD_MNTN_STREAM_NOT_USED_ENUM                     = 0x1a,
    CTTF_HRPD_MNTN_NO_SUB_PROTOCOL_ENUM                     = 0x1b,
    CTTF_HRPD_MNTN_SUB_PROTOCOL_BUTT
};
typedef  VOS_UINT8 CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM_UINT8;

enum CTTF_HRPD_MAC_TRANS_MODE_ENUM
{
    CTTF_HRPD_MAC_TRANS_MODE_HIGH_CAPACITY  = 0x00,
    CTTF_HRPD_MAC_TRANS_MODE_LOW_LATENCY    = 0x01,
    CTTF_HRPD_MAC_TRANS_MODE_BUTT           = 0x02
};
typedef VOS_UINT8 CTTF_HRPD_MAC_TRANS_MODE_ENUM_UINT8;

enum CSDR_HRPD_MNTN_SUBPACKET_TYPE_ENUM
{
    CSDR_HARQ_MNTN_SUBPACKET_FIRST_TIME      = 0x0000,
    CSDR_HARQ_MNTN_SUBPACKET_SECOND_TIME     = 0x0001,
    CSDR_HARQ_MNTN_SUBPACKET_THIRD_TIME      = 0x0002,
    CSDR_HARQ_MNTN_SUBPACKET_FOURTH_TIME     = 0x0003,
    CSDR_HARQ_MNTN_SUBPACKET_BUTT            = 0x0004
};
typedef VOS_UINT16 CSDR_HRPD_MNTN_SUBPACKET_TYPE_ENUM_UINT16;

enum CTTF_HRPD_MNTN_RTC3MAC_WORK_MODE_ENUM
{
    CTTF_HRPD_MNTN_RTC3MAC_MODE_NORMAL                  = 0x00,
    CTTF_HRPD_MNTN_RTC3MAC_MODE_PHY_FORBIDDEN           = 0x01,
    CTTF_HRPD_MNTN_RTC3MAC_MODE_SUPERVISION_FAILED      = 0x02,
    CTTF_HRPD_MNTN_RTC3MAC_MODE_SILENCE_DURATION        = 0x03,
    CTTF_HRPD_MNTN_RTC3MAC_MODE_TEST_LOOP               = 0x04,
    CTTF_HRPD_MNTN_RTC3MAC_MODE_PREEMPT                 = 0x05,
    CTTF_HRPD_MNTN_RTC3MAC_MODE_RTC_SETUP_STATUS        = 0x06,
    CTTF_HRPD_MNTN_RTC3MAC_MODE_ATTR_PARA_CHANGE_NEGO   = 0x07,
    CTTF_HRPD_MNTN_RTC3MAC_MODE_ATTR_PARA_CHANGE_GAUP   = 0x08,
    CTTF_HRPD_MNTN_RTC3MAC_MODE_TCH_PARA_CHANGE         = 0x09,
    CTTF_HRPD_MNTN_RTC3MAC_MODE_OTHER                   = 0x0A,
    CTTF_HRPD_MNTN_RTC3MAC_WORK_MODE_BUTT               = 0x0B
};
typedef VOS_UINT8 CTTF_HRPD_MNTN_RTC3MAC_WORK_MODE_ENUM_UINT8;

enum CTTF_HRPD_MNTN_CC_STATE_ENUM
{
    CTTF_HRPD_MNTN_CC_INACTIVE_STATE    = 0x0,
    CTTF_HRPD_MNTN_CC_ACTIVE_STATE      = 0x1,
    CTTF_HRPD_MNTN_CC_STATE_BUTT
};
typedef  VOS_UINT8 CTTF_HRPD_MNTN_CC_STATE_ENUM_UINT8;

enum CTTF_HRPD_MNTN_AC_STATE_ENUM
{
    CTTF_HRPD_MNTN_AC_INACTIVE_STATE    = 0x0,
    CTTF_HRPD_MNTN_AC_ACTIVE_STATE      = 0x1,
    CTTF_HRPD_MNTN_AC_STATE_BUTT
};
typedef  VOS_UINT8 CTTF_HRPD_MNTN_AC_STATE_ENUM_UINT8;

enum CTTF_HRPD_MNTN_FTC_STATE_ENUM
{
    CTTF_HRPD_MNTN_FTC_INACTIVE_STATE       = 0x0,
    CTTF_HRPD_MNTN_FTC_VARIABLE_RATE_STATE  = 0x1,
    CTTF_HRPD_MNTN_FTC_FIXED_RATE_STATE     = 0x2,
    CTTF_HRPD_MNTN_FTC_STATE_BUTT
};
typedef  VOS_UINT8 CTTF_HRPD_MNTN_FTC_STATE_ENUM_UINT8;

enum CTTF_HRPD_MNTN_RTC_STATE_ENUM
{
    CTTF_HRPD_MNTN_RTC_INACTIVE_STATE   = 0x0,
    CTTF_HRPD_MNTN_RTC_SETUP_STATE      = 0x1,
    CTTF_HRPD_MNTN_RTC_OPEN_STATE       = 0x2,
    CTTF_HRPD_MNTN_RTC_SUSPENDED_STATE  = 0x3,
    CTTF_HRPD_MNTN_RTC_STATE_BUTT
};
typedef  VOS_UINT8 CTTF_HRPD_MNTN_RTC_STATE_ENUM_UINT8;

enum CTTF_HRPD_MNTN_SECURITY_LAYER_PROTOCOL_STATE_ENUM
{
    CTTF_HRPD_MNTN_SECURITY_LAYER_PROTOCOL_NO_STATE     = 0x0,
    CTTF_HRPD_MNTN_SECURITY_LAYER_PROTOCOL_STATE_BUTT
};
typedef  VOS_UINT8 CTTF_HRPD_MNTN_SECURITY_LAYER_PROTOCOL_STATE_ENUM_UINT8;

enum CTTF_HRPD_MNTN_STREAM_FLOW_CTRL_PROTOCOL_STATE_ENUM
{
    CTTF_HRPD_MNTN_STREAM_FLOW_CTRL_CLOSE_STATE         = 0x0,
    CTTF_HRPD_MNTN_STREAM_FLOW_CTRL_OPEN_STATE          = 0x1,
    CTTF_HRPD_MNTN_STREAM_FLOW_CTRL_PROTOCOL_STATE_BUTT
};
typedef  VOS_UINT8 CTTF_HRPD_MNTN_STREAM_FLOW_CTRL_PROTOCOL_STATE_ENUM_UINT8;

enum CTTF_HRPD_MNTN_STREAM_APP_PROTOCOL_STATE_ENUM
{
    CTTF_HRPD_MNTN_STREAM_APP_RESERVATION_CLOSE_STATE   = 0x0,
    CTTF_HRPD_MNTN_STREAM_APP_RESERVATION_STATE         = 0x1,
    CTTF_HRPD_MNTN_STREAM_APP_NO_STATE                  = 0x2,
    CTTF_HRPD_MNTN_STREAM_APP_PROTOCOL_STATE_BUTT
};
typedef  VOS_UINT8 CTTF_HRPD_MNTN_STREAM_APP_PROTOCOL_STATE_ENUM_UINT8;

enum CTTF_HRPD_MNTN_SNP_UP_TX_STATE_ENUM
{
    CTTF_HRPD_MNTN_SNP_UP_TX_ALLOW_STATE                = 0x0,
    CTTF_HRPD_MNTN_SNP_UP_TX_NOT_ALLOW_STATE            = 0x1,
    CTTF_HRPD_MNTN_SNP_UP_TX_STATE_BUTT
};
typedef  VOS_UINT8 CTTF_HRPD_MNTN_SNP_UP_TX_STATE_ENUM_UINT8;

enum CTTF_HRPD_RTCMAC_MNTN_RATE_ENUM
{
    CTTF_HRPD_RTCMAC_MNTN_RATE_NULL              = 0,
    CTTF_HRPD_RTCMAC_MNTN_RATE_9K6               = 1,
    CTTF_HRPD_RTCMAC_MNTN_RATE_19K2              = 2,
    CTTF_HRPD_RTCMAC_MNTN_RATE_38K4              = 3,
    CTTF_HRPD_RTCMAC_MNTN_RATE_76K8              = 4,
    CTTF_HRPD_RTCMAC_MNTN_RATE_153K6             = 5,
    CTTF_HRPD_RTCMAC_MNTN_RATE_NO_LIMITATION     = 6,
    CTTF_HRPD_RTCMAC_MNTN_RATE_BUTT              = 7
};
typedef VOS_UINT8 CTTF_HRPD_RTCMAC_MNTN_RATE_ENUM_UINT8;

enum PPP_MNTN_OM_RESULT_TYPE_ENUM
{
    PPP_MNTN_OM_RESULT_OK                  = 0,
    PPP_MNTN_OM_RESULT_INPUT_PARAM_ERR     = 1,
    PPP_MNTN_OM_RESULT_BUTT
};
typedef VOS_UINT8 PPP_MNTN_OM_RESULT_TYPE_ENUM_UINT8;

enum CTTF_HRPD_PA_MNTN_FLOW_PROTOCOL_ENUM
{
    CTTF_HRPD_PA_MNTN_FLOW_PROTOCOL_NULL                            = 0x00,
    CTTF_HRPD_PA_MNTN_HDLC_LIKE_FRMAING_WITH_PPP                    = 0x01,
    CTTF_HRPD_PA_MNTN_IPV4                                          = 0x02,
    CTTF_HRPD_PA_MNTN_IPV6                                          = 0x03,
    CTTF_HRPD_PA_MNTN_ROHC                                          = 0x04,
    CTTF_HRPD_PA_MNTN_IPV4_AND_IPV6                                 = 0x05,
    CTTF_HRPD_PA_MNTN_HDLC_LIKE_FRMAING_WITH_ALTPPP                 = 0x06,
    CTTF_HRPD_PA_MNTN_HDLC_LIKE_FRMAING_SUPPORTING_MULTIPLE_PDNS    = 0x07,
    CTTF_HRPD_PA_MNTN_PDN_MUX_FOR_IP_PDNS                           = 0x08,
    CTTF_HRPD_PA_MNTN_BCMCS_OVER_UNICAST_WITH_HDLC_LIKE_FRAMING     = 0x09,
    CTTF_HRPD_PA_MNTN_BCMCS_OVER_UNICAST_WITH_SEG_BASED_FRAMING     = 0x0A,
    CTTF_HRPD_PA_MNTN_FLOW_PROTOCOL_BUTT
};
typedef VOS_UINT8 CTTF_HRPD_PA_MNTN_FLOW_PROTOCOL_ENUM_UINT8;

enum CTTF_HRPD_PA_MNTN_ROUTE_PROTOCOL_ENUM
{
    CTTF_HRPD_PA_MNTN_ROUTE_PROTOCOL_NULL                           = 0x00,
    CTTF_HRPD_PA_MNTN_ROUTE_PROTOCOL_ROHC                           = 0x04,
    CTTF_HRPD_PA_MNTN_ROUTE_PROTOCOL_BUTT
};
typedef VOS_UINT8 CTTF_HRPD_PA_MNTN_ROUTE_PROTOCOL_ENUM_UINT8;

enum CTTF_HRPD_MNTN_RTC3MAC_PAKETSIZE_INDEX_ENUM
{
    CTTF_HRPD_MNTN_RTC3MAC_PS_0         = 0x00,
    CTTF_HRPD_MNTN_RTC3MAC_PS_128       = 0x01,
    CTTF_HRPD_MNTN_RTC3MAC_PS_256       = 0x02,
    CTTF_HRPD_MNTN_RTC3MAC_PS_512       = 0x03,
    CTTF_HRPD_MNTN_RTC3MAC_PS_768       = 0x04,
    CTTF_HRPD_MNTN_RTC3MAC_PS_1024      = 0x05,
    CTTF_HRPD_MNTN_RTC3MAC_PS_1536      = 0x06,
    CTTF_HRPD_MNTN_RTC3MAC_PS_2048      = 0x07,
    CTTF_HRPD_MNTN_RTC3MAC_PS_3072      = 0x08,
    CTTF_HRPD_MNTN_RTC3MAC_PS_4096      = 0x09,
    CTTF_HRPD_MNTN_RTC3MAC_PS_6144      = 0x0A,
    CTTF_HRPD_MNTN_RTC3MAC_PS_8192      = 0x0B,
    CTTF_HRPD_MNTN_RTC3MAC_PS_12288     = 0x0C,
    CTTF_HRPD_MNTN_RTC3MAC_PS_BUTT      = 0x0D
};
typedef  VOS_UINT8 CTTF_HRPD_MNTN_RTC3MAC_PAKETSIZE_INDEX_ENUM_UINT8;

extern VOS_UINT32  g_aulR99MailboxVtbAddr[];

typedef struct
{
    VOS_MSG_HEADER

    VOS_UINT32  ulMsgId;

    VOS_UINT16  usOriginalId;
    VOS_UINT16  usTerminalId;
    VOS_UINT32  ulTimeStamp;
    VOS_UINT32  ulSN;
}DIAG_TRANS_MSG_HDR_STRU;

typedef struct
{
    WTTF_RLC_MNTN_RB_CHOSEN_ENUM_UINT32     enConfig;
    VOS_UINT16                              usTracePduSize;
    VOS_UINT16                              usTraceCipherPduSize;
    VOS_UINT16                              usTracePduCnt;
    VOS_UINT8                               aucRsv[2];
}WTTF_TRACE_MAC_RLC_DATA_IND_CONFIG_STRU;
typedef WTTF_TRACE_MAC_RLC_DATA_IND_CONFIG_STRU WTTF_TRACE_RLC_MAC_DATA_REQ_CONFIG_STRU;

typedef struct
{
    WTTF_TRACE_PHY_MAC_SUB_ATTRIB_ENUM_UINT8    enConfig;
    VOS_UINT8                                   aucRsv[3];
}WTTF_TRACE_PHY_MAC_DATA_IND_CONFIG_STRU;

typedef WTTF_TRACE_PHY_MAC_DATA_IND_CONFIG_STRU  WTTF_TRACE_MAC_PHY_DATA_REQ_CONFIG_STRU;
typedef WTTF_TRACE_PHY_MAC_DATA_IND_CONFIG_STRU  WTTF_TRACE_PHY_MAC_HS_PDU_DATA_IND_CONFIG_STRU;
typedef WTTF_TRACE_PHY_MAC_DATA_IND_CONFIG_STRU  WTTF_TRACE_UPA_PHY_DATA_REQ_CONFIG_STRU;

typedef struct
{
    WTTF_TRACE_MSG_SIMPLE_ATTRIB_ENUM_UINT8     enConfig;
    VOS_UINT8                                   aucRsv[3];
}WTTF_TRACE_MSG_SIMPLE_CONFIG_STRU;

typedef struct
{
    TTF_MNTN_TRACE_CHOSEN_ENUM_UINT32           enChoice;
    VOS_UINT32                                  ulTraceDataLen;
}TTF_MNTN_TRACE_DATA_CONFIG_STRU;

typedef TTF_MNTN_TRACE_DATA_CONFIG_STRU WTTF_TRACE_PDCP_RABM_DATA_IND_CONFIG_STRU;
typedef TTF_MNTN_TRACE_DATA_CONFIG_STRU WTTF_TRACE_RABM_PDCP_DATA_REQ_CONFIG_STRU;

typedef struct
{
    IPS_MNTN_TRACE_CHOSEN_ENUM_UINT32   ulChoice;
    VOS_UINT32                          ulTraceDataLen;
}IPS_MNTN_TRACE_CONFIG_STRU;

typedef IPS_MNTN_TRACE_CONFIG_STRU  IPS_MNTN_BRIDGE_TRACE_CFG_STRU;
typedef IPS_MNTN_TRACE_CONFIG_STRU  IPS_MNTN_INPUT_TRACE_CFG_STRU;
typedef IPS_MNTN_TRACE_CONFIG_STRU  IPS_MNTN_OUTPUT_TRACE_CFG_STRU;
typedef IPS_MNTN_TRACE_CONFIG_STRU  IPS_MNTN_LOCAL_TRACE_CFG_STRU;

typedef struct
{
    IPS_MNTN_CCORE_TRACE_CHOSEN_ENUM_UINT32   ulChoice;
    VOS_UINT32                                ulTraceDataLen;
}IPS_MNTN_CCORE_TRACE_CONFIG_STRU;

typedef IPS_MNTN_CCORE_TRACE_CONFIG_STRU  IPS_MNTN_CCORE_BRIDGE_TRACE_CFG_STRU;
typedef IPS_MNTN_CCORE_TRACE_CONFIG_STRU  IPS_MNTN_CCORE_INPUT_TRACE_CFG_STRU;
typedef IPS_MNTN_CCORE_TRACE_CONFIG_STRU  IPS_MNTN_CCORE_OUTPUT_TRACE_CFG_STRU;

typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU                     stTransHdr;
    TTF_MNTN_RPT_CMD_ENUM_UINT8                 enCommand;
    WTTF_TRACE_MSG_SIMPLE_ATTRIB_ENUM_UINT8     enRptAM;
    WTTF_TRACE_MSG_SIMPLE_ATTRIB_ENUM_UINT8     enRptUM;
    WTTF_TRACE_MSG_SIMPLE_ATTRIB_ENUM_UINT8     enRptTM;
    VOS_UINT32                                  ulRptPeriod;
} OM_TTF_WCDMA_RLC_DATA_TRANS_INFO_REQ_STRU;

typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU           stTransHdr;
    PS_RSLT_CODE_ENUM_UINT32          enRslt;
} TTF_OM_WCDMA_RLC_DATA_TRANS_INFO_CNF_STRU;

typedef TTF_OM_WCDMA_RLC_DATA_TRANS_INFO_CNF_STRU TTF_OM_RLC_PDU_SIZE_TRANS_INFO_CNF_STRU;
typedef TTF_OM_WCDMA_RLC_DATA_TRANS_INFO_CNF_STRU TTF_OM_UPA_DATA_STATUS_G_INFO_CNF_STRU;

typedef struct
{
    WTTF_TRACE_MAC_RLC_DATA_IND_CONFIG_STRU         stTraceMacRlcDataIndCfg;
    WTTF_TRACE_RLC_MAC_DATA_REQ_CONFIG_STRU         stTraceRlcMacDataReqCfg;

    WTTF_TRACE_PHY_MAC_DATA_IND_CONFIG_STRU         stTracePhyMacDataIndCfg;
    WTTF_TRACE_MAC_PHY_DATA_REQ_CONFIG_STRU         stTraceMacPhyDataReqCfg;

    WTTF_TRACE_PHY_MAC_HS_PDU_DATA_IND_CONFIG_STRU  stTracePhyMacHsPduDataIndCfg;
    WTTF_TRACE_UPA_PHY_DATA_REQ_CONFIG_STRU         stTraceUpaPhyDataReqCfg;

    WTTF_TRACE_MSG_SIMPLE_CONFIG_STRU               stTracePhyMacInfoIndCfg;
    WTTF_TRACE_MSG_SIMPLE_CONFIG_STRU               stTraceUpaStatusIndCfg;
    WTTF_TRACE_MSG_SIMPLE_CONFIG_STRU               stTraceUpaSchedStausIndCfg;

    WTTF_TRACE_MSG_SIMPLE_CONFIG_STRU               stTraceMacPhyAmrDataIndCfg;
    WTTF_TRACE_MSG_SIMPLE_CONFIG_STRU               stTracePhyRlcAmrDataReqCfg;

    WTTF_TRACE_PDCP_RABM_DATA_IND_CONFIG_STRU       stTracePdcpRabmDataIndCfg;
    WTTF_TRACE_RABM_PDCP_DATA_REQ_CONFIG_STRU       stTraceRabmPdcpDataReqCfg;

    WTTF_TRACE_MSG_SIMPLE_CONFIG_STRU               stTraceRlcMacIPDataCfg;
    WTTF_TRACE_MSG_SIMPLE_CONFIG_STRU               stTraceMacRlcIPDataCfg;
}WTTF_TRACE_MSG_CONFIG_STRU;

typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU           stTransHdr;
    WTTF_TRACE_MSG_CONFIG_STRU        stAdvancedConfig;
}OM_TTF_WCDMA_ADVANCED_TRACE_CONFIG_REQ_STRU;

typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU           stTransHdr;
    PS_RSLT_CODE_ENUM_UINT32          enRslt;

} TTF_OM_WCDMA_ADVANCED_TRACE_CONFIG_CNF_STRU;

typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU             stTransHdr;
    TTF_MNTN_RPT_CMD_ENUM_UINT8         enCommand;
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                          ulRptPeriod;
} OM_TTF_WCDMA_RLC_PDU_SIZE_TRANS_INFO_REQ_STRU;

typedef struct
{
    VOS_UINT16                          usPduSize;
    VOS_UINT8                           aucReserve[2];
    VOS_UINT32                          ulPduCount;
}WTTF_MNTN_RLC_PDU_SIZE_INFO_STRU;

typedef struct
{
    VOS_UINT8                           ucRbId;
    PS_BOOL_ENUM_UINT8                  enExist;
    VOS_UINT8                           ucRlcSizeLevelCnt;
    VOS_UINT8                           aucReserve1[1];
    WTTF_MNTN_RLC_PDU_SIZE_INFO_STRU    astMntnRlcPduSizeInfo[WTTF_MNTN_MAX_FLX_RLC_SIZE_LEVEL_CNT];
} TTF_OM_WCDMA_RLC_PDU_SIZE_TRANS_INFO_STRU;

typedef struct{
    VOS_UINT32                                          ulSimuClock;
    OM_TTF_WCDMA_RLC_PDU_SIZE_TRANS_INFO_REQ_STRU       stOmRlcPduSizeReq;
    TTF_OM_WCDMA_RLC_PDU_SIZE_TRANS_INFO_STRU           astMntnRlCPduSizeTransInfo[WTTF_MNTN_MAX_RB_ID + 1];
} WTTF_MNTN_RLC_PDU_SIZE_TRANS_INFO_OBJ_STRU;

typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU           stTransHdr;
    PS_RSLT_CODE_ENUM_UINT32          enRslt;
} TTF_OM_WCDMA_RLC_PDU_SIZE_TRANS_INFO_CNF_STRU;

typedef OM_TTF_WCDMA_RLC_PDU_SIZE_TRANS_INFO_REQ_STRU OM_TTF_WCDMA_UPA_DATA_STATUS_G_INFO_REQ_STRU;

typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU           stTransHdr;
    PS_RSLT_CODE_ENUM_UINT32          enRslt;

} TTF_OM_WCDMA_UPA_DATA_STATUS_G_INFO_CNF_STRU;

typedef struct
{
    VOS_UINT32                          ulRlcResetNum;
    VOS_UINT32                          ulLowRlcPduTxBytes;
    VOS_UINT32                          ulHighRlcPduTxBytes;
    VOS_UINT32                          ulLowRlcSduTxBytes;
    VOS_UINT32                          ulHighRlcSduTxBytes;
    VOS_UINT32                          ulCurPrdRlcSduTxBytes;
    VOS_UINT32                          ulRlcDataPduTxNum;
    VOS_UINT32                          ulRlcDataPduRetxNum;
    VOS_UINT32                          ulRlcNackedPduNum;
    VOS_UINT32                          ulRlcCtrlPduTxNum;
    VOS_UINT16                          usRlcLastTxPduSn;
    VOS_UINT16                          usRlcLastAckInseqPduSn;
    VOS_UINT16                          usRlcVacantTxWinSize;
    VOS_UINT8                           aucReserve2[2];
    VOS_UINT32                          ulRlcBo;
    VOS_UINT32                          ulRlcDataPdu3ReTxNum;
    VOS_UINT32                          ulRlcDataPdu4ReTxNum;
    VOS_UINT32                          ulRlcDataPdu5ReTxNum;
    VOS_UINT32                          ulRlcDataPdu6ReTxNum;
    VOS_UINT32                          ulRlcDataPduMore7ReTxNum;
} WTTF_MNTN_RLC_AM_UL_DATA_TRANS_INFO_STRU;

typedef struct
{
    VOS_UINT32                          ulRlcResetNum;
    VOS_UINT32                          ulLowRlcPduRxBytes;
    VOS_UINT32                          ulHighRlcPduRxBytes;
    VOS_UINT32                          ulLowRlcSduRxBytes;
    VOS_UINT32                          ulHighRlcSduRxBytes;
    VOS_UINT32                          ulCurPrdRlcSduRxBytes;
    VOS_UINT32                          ulRlcCrcErrPduRxNum;
    VOS_UINT32                          ulRlcInvalidDataPduRxNum;
    VOS_UINT32                          ulRlcDataPduRxNum;
    VOS_UINT32                          ulRlcCtrlPduRxNum;
    VOS_UINT32                          ulRlcNackedPduNum;
    VOS_UINT16                          usRlcLastRxInseqPduSn;
    VOS_UINT16                          usRlcHighestPduSn;
} WTTF_MNTN_RLC_AM_DL_DATA_TRANS_INFO_STRU;

typedef struct
{
    PS_BOOL_ENUM_UINT8                          enExist;
    VOS_UINT8                                   ucRbId;
    VOS_UINT8                                   aucReserve2[2];
    WTTF_MNTN_RLC_AM_UL_DATA_TRANS_INFO_STRU    stRlcMntnAmUlDataTransInfo;
    WTTF_MNTN_RLC_AM_DL_DATA_TRANS_INFO_STRU    stRlcMntnAmDlDataTransInfo;
} WTTF_MNTN_RLC_AM_DATA_TRANS_INFO_STRU;

typedef struct
{
    VOS_UINT32                          ulLowRlcPduTxBytes;
    VOS_UINT32                          ulHighRlcPduTxBytes;
    VOS_UINT32                          ulLowRlcSduTxBytes;
    VOS_UINT32                          ulHighRlcSduTxBytes;
    VOS_UINT32                          ulRlcPduTxNum;
    VOS_UINT16                          usRlcLastTxPduSn;
    VOS_UINT8                           aucReserve[2];
    VOS_UINT32                          ulRlcBo;
} WTTF_MNTN_RLC_UM_UL_DATA_TRANS_INFO_STRU;

typedef struct
{
    VOS_UINT32                          ulLowRlcPduRxBytes;
    VOS_UINT32                          ulHighRlcPduRxBytes;
    VOS_UINT32                          ulLowRlcSduRxBytes;
    VOS_UINT32                          ulHighRlcSduRxBytes;
    VOS_UINT32                          ulRlcCrcErrPduRxNum;
    VOS_UINT32                          ulRlcInvalidPduRxNum;
    VOS_UINT32                          ulRlcValidPduRxNum;
    VOS_UINT16                          usRlcLastRxInseqPduSn;
    VOS_UINT8                           aucReserve1[2];
} WTTF_MNTN_RLC_UM_DL_DATA_TRANS_INFO_STRU;

typedef struct
{
    PS_BOOL_ENUM_UINT8                          enExist;
    VOS_UINT8                                   ucRbId;
    VOS_UINT8                                   aucReserve2[2];
    WTTF_MNTN_RLC_UM_UL_DATA_TRANS_INFO_STRU    stRlcMntnUmUlDataTransInfo;
    WTTF_MNTN_RLC_UM_DL_DATA_TRANS_INFO_STRU    stRlcMntnUmDlDataTransInfo;
} WTTF_MNTN_RLC_UM_DATA_TRANS_INFO_STRU;

typedef struct
{
    VOS_UINT32                          ulLowRlcSduTxBytes;
    VOS_UINT32                          ulHighRlcSduTxBytes;
    VOS_UINT32                          ulLowRlcDiscardSduTxBytes;
    VOS_UINT32                          ulHightRlcDiscardSduTxBytes;
    VOS_UINT32                          ulRlcPduTxNum;
} WTTF_MNTN_RLC_TM_UL_DATA_TRANS_INFO_STRU;

typedef struct
{
    VOS_UINT32                          ulLowRlcSduRxBytes;
    VOS_UINT32                          ulHighRlcSduRxBytes;
    VOS_UINT32                          ulLowRlcPduRxBytes;
    VOS_UINT32                          ulHighRlcPduRxBytes;
    VOS_UINT32                          ulRlcCrcErrPduRxNum;
    VOS_UINT32                          ulRlcValidPduRxNum;
} WTTF_MNTN_RLC_TM_DL_DATA_TRANS_INFO_STRU;

typedef struct
{
    PS_BOOL_ENUM_UINT8                          enExist;
    VOS_UINT8                                   ucRbId;
    VOS_UINT8                                   aucReserve2[2];
    WTTF_MNTN_RLC_TM_UL_DATA_TRANS_INFO_STRU    stRlcMntnTmUlDataTransInfo;
    WTTF_MNTN_RLC_TM_DL_DATA_TRANS_INFO_STRU    stRlcMntnTmDlDataTransInfo;
} WTTF_MNTN_RLC_TM_DATA_TRANS_INFO_STRU;

typedef struct
{
    VOS_UINT32                              ulCurPrdRlcSduTxRate;
    VOS_UINT32                              ulCurPrdRlcSduRxRate;
    WTTF_MNTN_RLC_AM_DATA_TRANS_INFO_STRU   astMntnRlcAmDataTransInfo[WTTF_MNTN_MAX_AM_RB_NUM];
    WTTF_MNTN_RLC_UM_DATA_TRANS_INFO_STRU   astMntnRlcUmDataTransInfo[WTTF_MNTN_MAX_UM_RB_NUM];
    WTTF_MNTN_RLC_TM_DATA_TRANS_INFO_STRU   astMntnRlcTmDataTransInfo[WTTF_MNTN_MAX_TM_RB_NUM];
} TTF_OM_WCDMA_RLC_DATA_TRANS_INFO_IND_STRU;

typedef struct{
    VOS_UINT32                                     ulSimuClock;
    OM_TTF_WCDMA_RLC_DATA_TRANS_INFO_REQ_STRU      stOmRlcReq;
    TTF_OM_WCDMA_RLC_DATA_TRANS_INFO_IND_STRU      stRlcOmInd;
    VOS_UINT8                                      aucAmReTxNumPerDataPdu[WTTF_MNTN_MAX_AM_RB_NUM][WTTF_MNTN_RLC_AM_MAX_SN_NUM];
} WTTF_MNTN_RLC_DATA_TRANS_INFO_OBJ_STRU;

typedef struct
{
    IPS_MNTN_BRIDGE_TRACE_CFG_STRU              stBridgeArpTraceCfg;
    IPS_MNTN_INPUT_TRACE_CFG_STRU               stPreRoutingTraceCfg;
    IPS_MNTN_OUTPUT_TRACE_CFG_STRU              stPostRoutingTraceCfg;
    IPS_MNTN_LOCAL_TRACE_CFG_STRU               stLocalTraceCfg;
    WTTF_TRACE_MSG_SIMPLE_ATTRIB_ENUM_UINT8     enAdsIPConfig;
    VOS_UINT8                                   aucRsv[3];
}IPS_MNTN_TRACE_CONFIG_REQ_STRU;

typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU            stDiagHdr;
    IPS_MNTN_TRACE_CONFIG_REQ_STRU     stIpsAdvanceCfgReq;
}OM_IPS_ADVANCED_TRACE_CONFIG_REQ_STRU;

typedef struct
{
    PS_RSLT_CODE_ENUM_UINT32           enRslt;
}IPS_MNTN_TRACE_CONFIG_CNF_STRU;

typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU         stDiagHdr;
    IPS_MNTN_TRACE_CONFIG_CNF_STRU  stIpsAdvanceCfgCnf;
}IPS_OM_ADVANCED_TRACE_CONFIG_CNF_STRU;

typedef struct
{
    IPS_MNTN_INFO_ACTION_ENUM_UINT16    enCommand;
    VOS_UINT16                          usTimeLen;
}IPS_MNTN_INFO_CFG_REQ_STRU;

typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU             stDiagHdr;
    IPS_MNTN_INFO_CFG_REQ_STRU          stIpsMntnCfgReq;
}OM_IPS_MNTN_INFO_CONFIG_REQ_STRU;

typedef struct
{
    IPS_MNTN_RESULT_TYPE_ENUM_UINT32    enRslt;
    IPS_MNTN_INFO_ACTION_ENUM_UINT16    enCommand;
    VOS_UINT8                           aucRsv[2];
}IPS_MNTN_INFO_CFG_CNF_STRU;

typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU    stDiagHdr;
    IPS_MNTN_INFO_CFG_CNF_STRU stIpsMntnCfgCnf;
}IPS_OM_MNTN_INFO_CONFIG_CNF_STRU;

typedef struct
{
    VOS_UINT32                           ulTlli;
    GRM_TBF_INFO_TEST_MODE_ENUM_UINT8    ucTestMode;
    VOS_UINT8                            aucRsv[1];
    VOS_UINT16                           usLlcPduNum;
}GRM_MNTN_COM_INFO_STRU;

typedef struct
{
    GRM_TBF_INFO_RLC_MODE_ENUM_UINT8              ucUlRlcMode;
    GRM_TBF_INFO_COUNTDOWN_FLAG_ENUM_UINT8        ucCountdownFlag;
    GRM_TBF_INFO_EDGE_CODE_SCHEME_ENUM_UINT16     usUlCodeType;
    VOS_UINT8                                     ucUlTfi;
    GRM_TBF_INFO_TI_ENUM_UINT8                    ucTi;
    VOS_UINT8                                     aucRsv[2];
}GRM_MNTN_UL_TBF_STRU;

typedef struct
{
    GRM_TBF_INFO_TBF_MODE_ENUM_UINT8         ucUlTbfMode;
    VOS_UINT8                                ucBsCvMax;
    GRM_TBF_INFO_TIMESLOT_FLAG_ENUM_UINT8    aucUlTsFlag[GRM_MNTN_TS_TOTAL];
    VOS_UINT8                                aucRsv[2];
    GRM_MNTN_UL_TBF_STRU                     astTbf[GRLC_MNTN_MAX_TBF_NUM];
}GRM_MNTN_UL_ENTITY_INFO_STRU;

typedef struct
{
    GRM_TBF_INFO_EDGE_CODE_SCHEME_ENUM_UINT16     usDlCodeType;
    GRM_TBF_INFO_FINALBLKRXED_ENUM_UINT8          ucFinalBlkRxed;
    GRM_TBF_INFO_RLC_MODE_ENUM_UINT8              ucDlRlcMode;
    VOS_UINT8                                     ucDlTfi;
    VOS_UINT8                                     aucRsv[3];
}GRM_MNTN_DL_TBF_STRU;

typedef struct
{
	GRM_TBF_INFO_TIMESLOT_FLAG_ENUM_UINT8    aucDlTsFlag[GRM_MNTN_TS_TOTAL];
    GRM_MNTN_DL_TBF_STRU                     astTbf[GRLC_MNTN_MAX_TBF_NUM];
}GRM_MNTN_DL_ENTITY_INFO_STRU;

typedef struct
{
    GRM_MNTN_COM_INFO_STRU          stGrmMntnComInfo;
    GRM_MNTN_UL_ENTITY_INFO_STRU    stGrmMntnUlInfo;
    GRM_MNTN_DL_ENTITY_INFO_STRU    stGrmMntnDlInfo;
}GRM_MNTN_GRM_OM_INFO_STRU;

typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU                 stDiagHdr;

    GRM_MNTN_OM_REPORT_ACTION_ENUM_UINT16   enStartOrStop;
    VOS_UINT16                              usRptPeriod;
}GRM_MNTN_OM_GRM_INFO_CFG_REQ_STRU;

typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU                 stDiagHdr;

    GRM_RESULT_TYPE_ENUM_UINT32             enRslt;
    GRM_MNTN_OM_REPORT_ACTION_ENUM_UINT16   enStartOrStop;
    VOS_UINT16                              usRptPeriod;
}GRM_MNTN_GRM_OM_INFO_CFG_CNF_STRU;

typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU                 stDiagHdr;

    GRM_MNTN_OM_REPORT_ACTION_ENUM_UINT16   enStartOrStop;
    VOS_UINT8                               aucRsv[2];
}GRM_MNTN_OM_GRM_THROUGHPUT_CFG_REQ_STRU;

typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU                 stDiagHdr;

    GRM_RESULT_TYPE_ENUM_UINT32             enRslt;
    GRM_MNTN_OM_REPORT_ACTION_ENUM_UINT16   enStartOrStop;
    VOS_UINT8                               aucRsv[2];
}GRM_MNTN_GRM_OM_THROUGHPUT_CFG_CNF_STRU;

typedef TTF_MNTN_TRACE_DATA_CONFIG_STRU GTTF_MNTN_LL_GRM_TRACE_CONFIG_STRU;
typedef TTF_MNTN_TRACE_DATA_CONFIG_STRU GTTF_MNTN_SN_LL_TRACE_CONFIG_STRU;
typedef TTF_MNTN_TRACE_DATA_CONFIG_STRU GTTF_MNTN_RABM_SN_TRACE_CONFIG_STRU;

typedef struct
{
    GTTF_MNTN_LL_GRM_TRACE_CONFIG_STRU          stllGrmCfg;
    GTTF_MNTN_SN_LL_TRACE_CONFIG_STRU           stSnllCfg;
    GTTF_MNTN_RABM_SN_TRACE_CONFIG_STRU         stRabmSnCfg;
}GTTF_TRACE_MSG_CONFIG_STRU;

typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU                     stTransHdr;
    TOOL_GTTF_CFG_SWITCH_ENUM_UINT32            enL2CfgSwitch;
    GTTF_TRACE_MSG_CONFIG_STRU                  stAdvancedConfig;
}GRM_MNTN_OM_GTTF_ADV_TRACE_SWITCH_REQ_STRU;

typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU           stTransHdr;
    PS_RSLT_CODE_ENUM_UINT32          enRslt;
}GRM_MNTN_GTTF_OM_ADV_TRACE_SWITCH_CNF_STRU;

typedef struct
{
    WTTF_TRACE_MSG_SIMPLE_ATTRIB_ENUM_UINT8         enVISPLogOutConfig;
    IPS_MNTN_CCORE_TCPIP_LOG_LEVEL_E_ENUM_UINT8     enVISPRunLogLevelConfig;
    WTTF_TRACE_MSG_SIMPLE_ATTRIB_ENUM_UINT8         enVISPUnEncryptPktCapConfig;
    WTTF_TRACE_MSG_SIMPLE_ATTRIB_ENUM_UINT8         enVISPEncryptPktCapConfig;
}IPS_MNTN_CCORE_VISP_LOG_CONFIG_REQ_STRU;

typedef struct
{
    IPS_MNTN_CCORE_BRIDGE_TRACE_CFG_STRU        stBridgeTraceCfg;
    IPS_MNTN_CCORE_INPUT_TRACE_CFG_STRU         stInputTraceCfg;
    IPS_MNTN_CCORE_OUTPUT_TRACE_CFG_STRU        stOutputTraceCfg;
    IPS_MNTN_CCORE_VISP_LOG_CONFIG_REQ_STRU     stVispLogConfig;
}IPS_MNTN_CCORE_TRACE_CONFIG_REQ_STRU;

typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU               stDiagHdr;
    IPS_MNTN_CCORE_TRACE_CONFIG_REQ_STRU  stIpsCcoreCfgReq;
}OM_IPS_CCORE_ADVANCED_TRACE_CONFIG_REQ_STRU;

typedef struct
{
    PS_RSLT_CODE_ENUM_UINT32            enRslt;
}IPS_MNTN_CCORE_TRACE_CONFIG_CNF_STRU;

typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU              stDiagHdr;
    IPS_MNTN_CCORE_TRACE_CONFIG_CNF_STRU stIpsCcoreCfgCnf;
}IPS_CCORE_OM_ADVANCED_TRACE_CONFIG_CNF_STRU;

typedef struct
{
    IPS_MNTN_CCORE_INFO_ACTION_ENUM_UINT16    enCommand;
    VOS_UINT16                                usTimeLen;
}IPS_MNTN_CCORE_INFO_CFG_REQ_STRU;

typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU           stDiagHdr;
    IPS_MNTN_CCORE_INFO_CFG_REQ_STRU  stIpsCcoreMntnCfgReq;
}OM_IPS_CCORE_MNTN_INFO_CONFIG_REQ_STRU;

typedef struct
{
    IPS_MNTN_CCORE_RESULT_TYPE_ENUM_UINT32    enRslt;
    IPS_MNTN_CCORE_INFO_ACTION_ENUM_UINT16    enCommand;
    VOS_UINT8                                 aucRsv[2];
}IPS_MNTN_CCORE_INFO_CFG_CNF_STRU;

typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU             stDiagHdr;
    IPS_MNTN_CCORE_INFO_CFG_CNF_STRU    stIpsCcoreMntnCfgCnf;
}IPS_CCORE_OM_MNTN_INFO_CONFIG_CNF_STRU;

typedef struct
{
    TTF_MNTN_RPT_CMD_ENUM_UINT8             enCommand;
    VOS_UINT8                               aucReserve[3];
    CTTF_1X_MAC_MNTN_RPT_PERIOD_ENUM_UINT32 enRptPeriod;
} OM_CTTF_1X_MNTN_GENERIC_CONFIG_STRU;

typedef struct
{
    TTF_MNTN_RLP_RPT_CMD_ENUM_UINT8         enCommand;
    VOS_UINT8                               aucReserve[3];
    CTTF_1X_MAC_MNTN_RPT_PERIOD_ENUM_UINT32 enRptPeriod;
} OM_CTTF_1X_MNTN_RLP_GENERIC_CONFIG_STRU;

typedef struct
{
    TTF_MNTN_COMM_RPT_CMD_ENUM_UINT8        enCommand;
    VOS_UINT8                               aucReserve[3];
    CTTF_1X_MAC_MNTN_RPT_PERIOD_ENUM_UINT32 enRptPeriod;
} OM_CTTF_1X_MNTN_COMM_GENERIC_CONFIG_STRU;

typedef struct
{
    TTF_MNTN_COMM_RPT_CMD_ENUM_UINT8        enCommand;
    VOS_UINT8                               aucReserve[3];
    CTTF_HRPD_MNTN_RPT_PERIOD_ENUM_UINT32   enRptPeriod;
} OM_CTTF_HRPD_MNTN_GENERIC_CONFIG_STRU;

typedef struct
{
    TTF_MNTN_RPT_CMD_ENUM_UINT8                 enCommand;
    VOS_UINT8                                   aucReserve[3];
    CTTF_HRPD_MNTN_RTC_RPT_PERIOD_ENUM_UINT32   enRptPeriod;
} OM_CTTF_HRPD_MNTN_COMM_CONFIG_STRU;

typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU                     stTransHdr;
    OM_CTTF_1X_MNTN_GENERIC_CONFIG_STRU         stFwdLinkInfo;
    OM_CTTF_1X_MNTN_GENERIC_CONFIG_STRU         stRevLinkInfo;
    OM_CTTF_1X_MNTN_RLP_GENERIC_CONFIG_STRU     stRlpStatistics;
    OM_CTTF_1X_MNTN_COMM_GENERIC_CONFIG_STRU    stCommonStatistics;
} OM_CTTF_1X_MNTN_CONFIG_REQ_STRU;

typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU                     stTransHdr;
    OM_CTTF_HRPD_MNTN_GENERIC_CONFIG_STRU       stMacStatistics;
    OM_CTTF_HRPD_MNTN_GENERIC_CONFIG_STRU       stRlpStatistics;
    OM_CTTF_HRPD_MNTN_GENERIC_CONFIG_STRU       stMfpaStatistics;
    OM_CTTF_HRPD_MNTN_GENERIC_CONFIG_STRU       stEmpaStatistics;
    OM_CTTF_HRPD_MNTN_COMM_CONFIG_STRU          stRtc3PktInfo;
    OM_CTTF_HRPD_MNTN_COMM_CONFIG_STRU          stT2pStatistics;
    OM_CTTF_HRPD_MNTN_COMM_CONFIG_STRU          stRtc3HarqInfo;
    OM_CTTF_HRPD_MNTN_GENERIC_CONFIG_STRU       stRtc3AckInfo;
} OM_CTTF_HRPD_MNTN_CONFIG_REQ_STRU;

typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU                 stDiagHdr;

    PS_RSLT_CODE_ENUM_UINT32                enRslt;
    VOS_UINT32                              ulReason;
} CTTF_OM_HRPD_MNTN_CONFIG_CNF_STRU;

typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU                 stDiagHdr;

    PS_RSLT_CODE_ENUM_UINT32                enRslt;
    VOS_UINT32                              ulReason;
} CTTF_OM_1X_MNTN_CONFIG_CNF_STRU;

typedef struct
{
    CTTF_1X_MAC_MNTN_RATE_ENUM_UINT8       enRate;
    VOS_UINT8                              ucPercentage;
    VOS_UINT8                              aucReserved[2];
}CTTF_1X_MAC_MNTN_FWD_LINK_PER_INFO_STRU;

typedef struct
{
    VOS_UINT16                                  usPrimId;
    VOS_UINT16                                  usToolId;

    CTTF_1X_MAC_MNTN_FWD_LINK_PER_INFO_STRU     astFch[CTTF_1X_MAC_MNTN_MAX_REPORT_NUM];
    CTTF_1X_MAC_MNTN_FWD_LINK_PER_INFO_STRU     astDcch[CTTF_1X_MAC_MNTN_MAX_REPORT_NUM];
    CTTF_1X_MAC_MNTN_FWD_LINK_PER_INFO_STRU     astSch0[CTTF_1X_MAC_MNTN_MAX_REPORT_NUM];
} CTTF_OM_1X_MNTN_FWD_LINK_IND_STRU;

typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU                     stTransHdr;

    TTF_MNTN_COMM_RPT_CMD_ENUM_UINT8            enCommand;
    VOS_UINT8                                   aucReserve[3];
} CTTF_OM_PPP_MNTN_CONFIG_REQ_STRU;

typedef struct
{
    VOS_UINT32                  ulSuccCnt;
    VOS_UINT32                  ulFailCnt;
    VOS_UINT32                  ulNameOrPwdAuthFailCnt;
    VOS_UINT32                  ulInvalidIpAddrCnt;
    VOS_UINT32                  ulInvalidDnsAddrCnt;
    VOS_UINT32                  ulOtherFail;
}CTTF_HRPD_MNTN_PPP_STATISTICS_REPORT_STRU;

typedef struct
{
    VOS_UINT16                                  usPrimId;
    VOS_UINT16                                  usToolId;
    CTTF_HRPD_MNTN_PPP_STATISTICS_REPORT_STRU   stPppcStatisticInfo;
} CTTF_OM_PPPC_MNTN_STATISTICS_IND_STRU;

typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU                 stDiagHdr;

    PS_RSLT_CODE_ENUM_UINT32                enRslt;
    VOS_UINT32                              ulReason;
} CTTF_OM_PPP_MNTN_CONFIG_CNF_STRU;

#define  CTTF_OM_1X_MNTN_IND_HEAD_BYTE_SIZE     (4)

#define  CTTF_OM_HRPD_MNTN_IND_HEAD_BYTE_SIZE   (4)

typedef struct
{
    CTTF_1X_MAC_MNTN_RATE_ENUM_UINT8       enRate;
    VOS_UINT8                              aucReserved[3];
} CTTF_1X_MAC_MNTN_REV_LINK_PER_INFO_STRU;

typedef struct
{
    VOS_UINT16                                  usPrimId;
    VOS_UINT16                                  usToolId;

    CTTF_1X_MAC_MNTN_REV_LINK_PER_INFO_STRU     astFch[CTTF_1X_MAC_MNTN_MAX_REPORT_NUM];
    CTTF_1X_MAC_MNTN_REV_LINK_PER_INFO_STRU     astDcch[CTTF_1X_MAC_MNTN_MAX_REPORT_NUM];
    CTTF_1X_MAC_MNTN_REV_LINK_PER_INFO_STRU     astSch0[CTTF_1X_MAC_MNTN_MAX_REPORT_NUM];
} CTTF_OM_1X_MNTN_REV_LINK_IND_STRU;

typedef  struct
{
    VOS_UINT32    ulFrameTotalByteHigh;
    VOS_UINT32    ulFrameTotalByte;
    VOS_UINT32    ulUpperTotalByteHigh;
    VOS_UINT32    ulUpperTotalByte;
    VOS_UINT32    ulTotalFrameCnt;
    VOS_UINT32    ulIdleFrameCnt;
    VOS_UINT32    ulFchNewDataFrameCnt;
    VOS_UINT32    ulFchRetxFrameCnt;
    VOS_UINT32    ulSchNewDataFrameCnt;
    VOS_UINT32    ulSchRetxFrameCnt;
    VOS_UINT32    ulNakSingle;
    VOS_UINT32    ulNakDouble;
    VOS_UINT32    ulNakTriple;
    VOS_UINT32    ulNakAbove;
} CTTF_1X_RLP_MNTN_REV_STATISTICS_PER_ENTITY_STRU;

typedef  struct
{
    VOS_UINT32    ulFrameTotalByteHigh;
    VOS_UINT32    ulFrameTotalByte;
    VOS_UINT32    ulUpperTotalByteHigh;
    VOS_UINT32    ulUpperTotalByte;
    VOS_UINT32    ulTotalFrameCnt;
    VOS_UINT32    ulIdleFrameCnt;
    VOS_UINT32    ulFillFrameCnt;
    VOS_UINT32    ulBlankFrameCnt;
    VOS_UINT32    ulNullFrameCnt;
    VOS_UINT32    ulFchNewDataFrameCnt;
    VOS_UINT32    ulFchRetxFrameCnt;
    VOS_UINT32    ulSchNewDataFrameCnt;
    VOS_UINT32    ulSchRetxFrameCnt;
    VOS_UINT32    ulNakCtrlFrameCnt;
    VOS_UINT32    ulNakAbortTimes;
    VOS_UINT32    ulInsufficentQualityFrameCnt;
    VOS_UINT32    ulInvalidFcsFrameCnt;
    VOS_UINT32    ulInvalidTypeFieldFrameCnt;
    VOS_UINT32    ulInvalidCtlFieldFrameCnt;
} CTTF_1X_RLP_MNTN_FWD_STATISTICS_PER_ENTITY_STRU;

typedef struct
{
    VOS_UINT8            ucSrId;
    VOS_UINT8            ucMeasuredRtt;
    VOS_UINT8            aucReserved[2];
    VOS_UINT16           usBSTriggeredResetTimes;
    VOS_UINT16           usMSTriggeredResetTimes;
    VOS_UINT32           ulCurrentBo;
    CTTF_1X_RLP_MNTN_REV_STATISTICS_PER_ENTITY_STRU  stRevInfo;
    CTTF_1X_RLP_MNTN_FWD_STATISTICS_PER_ENTITY_STRU  stFwdInfo;
}CTTF_1X_RLP_MNTN_STATISTICS_PER_ENTITY_STRU;

typedef struct
{
    VOS_UINT16                                      usPrimId;
    VOS_UINT16                                      usToolId;

    CTTF_1X_RLP_MNTN_STATISTICS_PER_ENTITY_STRU     astRlpEntity[CTTF_1X_RLP_MNTN_MAX_NUM];
} CTTF_OM_1X_MNTN_RLP_STATISTICS_IND_STRU;

typedef struct
{
    VOS_UINT32    ulTotalEncapPduFragCnt;
    VOS_UINT32    ul96BitEncapPduFragCnt;
    VOS_UINT32    ul192BitEncapPduFragCnt;
    VOS_UINT32    ulTotalEncapPduCnt;
    VOS_UINT32    ulInvalidCrcEncapPduCnt;
    VOS_UINT32    ulChanLostCnt;
} CTTF_1X_MNTN_PCH_STATISTIC_STRU;

typedef struct
{
    VOS_UINT32    ulRequestTypeSduCnt;
    VOS_UINT32    ulResponseTypeSduCnt;
    VOS_UINT32    ulAccessProbe1Cnt;
    VOS_UINT32    ulAccessProbe2Cnt;
    VOS_UINT32    ulAccessProbe3Cnt;
    VOS_UINT32    ulAccessProbe4Cnt;
    VOS_UINT32    ulAccessProbe5Cnt;
    VOS_UINT32    ulAccessProbeAboveCnt;
    VOS_UINT32    ulUnsucessfulAccessAttemptCnt;
} CTTF_1X_MNTN_ACH_STATISTIC_STRU;

typedef struct
{
    VOS_UINT32    ulGpmMatchedCnt;
    VOS_UINT32    ulSlotPageMatchedCnt;
    VOS_UINT32    ulMismatchedPageCnt;
    VOS_UINT32    ulAddrMatchedOtherMsgCnt;
} CTTF_1X_MNTN_PAGE_MSG_STATISTIC_STRU;

typedef struct
{
    VOS_UINT16                          usPrimId;
    VOS_UINT16                          usToolId;

    CTTF_1X_MNTN_PCH_STATISTIC_STRU     stPch;
    CTTF_1X_MNTN_ACH_STATISTIC_STRU     stAch;
    CTTF_1X_MNTN_PAGE_MSG_STATISTIC_STRU stPage;

} CTTF_OM_1X_MNTN_COMMON_CHANNEL_STATISTICS_IND_STRU;

typedef struct
{
    VOS_UINT8       ucFlowId;
    VOS_UINT8       aucReserved[1];
    VOS_UINT16      usActualAllocation;
    VOS_UINT16      usSuggestAllocation;
    VOS_UINT16      usRequiredQueueSize;
    VOS_UINT16      usQOutflow;
    VOS_UINT8       aucReserved1[2];
}CTTF_HRPD_MNTN_RTC3MAC_LINK_PACKET_PER_MAC_FLOW_STRU;

typedef  struct
{
    CTTF_HRPD_MAC_TRANS_MODE_ENUM_UINT8                     enTransMode;
    CTTF_HRPD_MNTN_RTC3MAC_PAKETSIZE_INDEX_ENUM_UINT8       enPktSize;
    VOS_UINT16                                              usPaddingByteSize;
    VOS_INT8                                                cPacketId;
    VOS_INT8                                                cTxT2pMax;
    VOS_INT8                                                cPotentialT2p;
    VOS_UINT8                                               aucReserved[1];
    CTTF_HRPD_MNTN_RTC3MAC_LINK_PACKET_PER_MAC_FLOW_STRU    astMacFlow[CTTF_HRPD_RTC3MAC_MNTN_FLOW_MAX_NUM];
}CTTF_HRPD_MNTN_RTC3MAC_LINK_PACKET_STRU;

typedef  struct
{
    VOS_UINT16                              usPrimId;
    VOS_UINT16                              usToolId;
    CTTF_HRPD_MNTN_RTC3MAC_LINK_PACKET_STRU astLinkPktData[CTTF_HRPD_RTC3MAC_MNTN_MAX_RECORD_PACKET_PER_FLOW];
} CTTF_OM_HRPD_MNTN_RTC3MAC_LINK_PACKET_REPORT_STRU;

typedef struct
{
    VOS_UINT8       ucFlowId;
    VOS_INT8        cQrab;
    VOS_INT8        cDeltaT2p;
    VOS_INT8        cBucketFactor;
    VOS_INT16       sT2pInflow;
    VOS_INT16       sT2pOutflow;
    VOS_INT16       sBucketLevel;
    VOS_INT16       sBucketLevelSat;
} CTTF_HRPD_MNTN_RTC3MAC_LINK_T2P_PER_MAC_FLOW_STRU;

typedef struct
{
    CTTF_HRPD_MNTN_RTC3MAC_WORK_MODE_ENUM_UINT8         enWorkMode;
    VOS_INT8                                            cQRABn;
    VOS_INT16                                           sFrab;
    CTTF_HRPD_MNTN_RTC3MAC_LINK_T2P_PER_MAC_FLOW_STRU   astMacFlow[CTTF_HRPD_RTC3MAC_MNTN_FLOW_MAX_NUM];
}CTTF_HRPD_MNTN_RTC3MAC_LINK_T2P_STRU;

typedef struct
{
    VOS_UINT16                              usPrimId;
    VOS_UINT16                              usToolId;
    CTTF_HRPD_MNTN_RTC3MAC_LINK_T2P_STRU    astLinkT2pData[CTTF_HRPD_RTC3MAC_MNTN_MAX_RECORD_T2P_PER_FLOW];
}CTTF_OM_HRPD_MNTN_RTC3MAC_LINK_T2P_REPORT_STRU;

typedef struct
{
    VOS_INT8                                            cProcessId;
    VOS_INT8                                            cSubPacketId;
    VOS_INT8                                            cDataType;
    VOS_INT8                                            cPacketId;
} CTTF_HRPD_MNTN_RTC3MAC_HARQ_INFO_STRU;

typedef struct
{
    CTTF_HRPD_MNTN_RTC3MAC_HARQ_INFO_STRU   astHarqInfo[CTTF_HRPD_MNTN_NUM_SUBFRAME_INFO_INSTANCES];
} CTTF_HRPD_MNTN_RTC3MAC_SUBFRAME_HARQ_STRU;

typedef struct
{
    VOS_UINT16                                  usPrimId;
    VOS_UINT16                                  usToolId;
    CTTF_HRPD_MNTN_RTC3MAC_SUBFRAME_HARQ_STRU   astHarqData[CTTF_HRPD_RTC3MAC_MNTN_MAX_RECORD_HARQ];
} CTTF_OM_HRPD_MNTN_RTC3MAC_HARQ_REPORT_STRU;

typedef  struct
{
    VOS_UINT32    ulTotalByteCntHigh;
    VOS_UINT32    ulTotalByteCnt;
    VOS_UINT32    ulNewByteCntHigh;
    VOS_UINT32    ulNewByteCnt;
    VOS_UINT32    ulRetxByteCntHigh;
    VOS_UINT32    ulRetxByteCnt;
    VOS_UINT32    ulTotalPacketCnt;
    VOS_UINT32    ulNewPacketCnt;
    VOS_UINT32    ulRetxPacketCnt;
    VOS_UINT32    ulTxNakRequestCnt;
    VOS_UINT32    ulIgnoredAnNakCnt;
    VOS_UINT32    ulRlpFlushCnt;
} CTTF_HRPD_MNTN_PER_DEFAULT_RLP_REV_STATISTICS_STRU;

typedef  struct
{
    VOS_UINT32    ulTotalByteCntHigh;
    VOS_UINT32    ulTotalByteCnt;
    VOS_UINT32    ulNewByteCntHigh;
    VOS_UINT32    ulNewByteCnt;
    VOS_UINT32    ulRetxByteCntHigh;
    VOS_UINT32    ulRetxByteCnt;
    VOS_UINT32    ulDuplicateByteCnt;
    VOS_UINT32    ulTotalPacketCnt;
    VOS_UINT32    ulNewPacketCnt;
    VOS_UINT32    ulRetxPacketCnt;
    VOS_UINT32    ulRxedNakRequestCnt;
    VOS_UINT32    ulNakAbortCnt;
} CTTF_HRPD_MNTN_PER_DEFAULT_RLP_FWD_STATISTICS_STRU;

typedef  struct
{
    VOS_UINT8            ucStreamId;
    VOS_UINT8            aucReserved[3];
    VOS_UINT32           ulAnResetRequestCnt;
    VOS_UINT32           ulAtResetRequestCnt;
    VOS_UINT32           ulRxAnResetAckCnt;
    CTTF_HRPD_MNTN_PER_DEFAULT_RLP_REV_STATISTICS_STRU  stRevInfo;
    CTTF_HRPD_MNTN_PER_DEFAULT_RLP_FWD_STATISTICS_STRU  stFwdInfo;
}CTTF_HRPD_MNTN_PER_DEFAULT_RLP_STATISTICS_STRU;

typedef  struct
{
    VOS_UINT16                                       usPrimId;
    VOS_UINT16                                       usToolId;
    CTTF_HRPD_MNTN_PER_DEFAULT_RLP_STATISTICS_STRU   astRlpEntity[CTTF_HRPD_MNTN_DEFAULT_RLP_MAX_NUM];
} CTTF_OM_HRPD_MNTN_DEFAULT_RLP_STATISTICS_STRU;

typedef  struct
{
    VOS_UINT32    ulTotalByteCntHigh;
    VOS_UINT32    ulTotalByteCnt;
    VOS_UINT32    ulNewByteCntHigh;
    VOS_UINT32    ulNewByteCnt;
    VOS_UINT32    ulRetxByteCntHigh;
    VOS_UINT32    ulRetxByteCnt;
    VOS_UINT32    ulTotalPacketCnt;
    VOS_UINT32    ulNewPacketCnt;
    VOS_UINT32    ulRetxPacketCnt;
    VOS_UINT32    ulTxNakRequestCnt;
    VOS_UINT32    ulIgnoredAnNakCnt;
    VOS_UINT32    ulRlpFlushCnt;
    VOS_UINT32    ulAnResetRequestCnt;
    VOS_UINT32    ulAtResetRequestCnt;
    VOS_UINT32    ulRxedAnResetAckCnt;
}CTTF_HRPD_MNTN_PER_MF_RLP_REV_STATISTICS_STRU;

typedef  struct
{
    VOS_UINT32    ulTotalByteCntHigh;
    VOS_UINT32    ulTotalByteCnt;
    VOS_UINT32    ulNewByteCntHigh;
    VOS_UINT32    ulNewByteCnt;
    VOS_UINT32    ulRetxByteCntHigh;
    VOS_UINT32    ulRetxByteCnt;
    VOS_UINT32    ulDuplicateByteCnt;
    VOS_UINT32    ulTotalPacketCnt;
    VOS_UINT32    ulNewPacketCnt;
    VOS_UINT32    ulRetxPacketCnt;
    VOS_UINT32    ulRxedNakRequestCnt;
    VOS_UINT32    ulNakAbortCnt;
    VOS_UINT32    ulAnResetRequestCnt;
    VOS_UINT32    ulAtResetRequestCnt;
    VOS_UINT32    ulRxedAnResetAckCnt;
} CTTF_HRPD_MNTN_PER_MF_RLP_FWD_STATISTICS_STRU;

typedef  struct
{
    VOS_UINT8            ucRlpFlowId;
    VOS_UINT8            aucReserved[3];
    CTTF_HRPD_MNTN_PER_MF_RLP_REV_STATISTICS_STRU  stRevInfo;
    CTTF_HRPD_MNTN_PER_MF_RLP_FWD_STATISTICS_STRU  stFwdInfo;
}CTTF_HRPD_MNTN_PER_MF_RLP_STATISTICS_STRU;

typedef  struct
{
    VOS_UINT16                                  usPrimId;
    VOS_UINT16                                  usToolId;
    CTTF_HRPD_MNTN_PER_MF_RLP_STATISTICS_STRU   astRlpEntity[CTTF_HRPD_MNTN_MF_RLP_MAX_NUM];
} CTTF_OM_HRPD_MNTN_MF_RLP_STATISTICS_STRU;

typedef  struct
{
    VOS_UINT32    ulSelectRouteACnt;
    VOS_UINT32    ulSelectRouteBCnt;
    VOS_UINT32    ulTotalByteCntHigh;
    VOS_UINT32    ulTotalByteCnt;
    VOS_UINT32    ulNewByteCntHigh;
    VOS_UINT32    ulNewByteCnt;
    VOS_UINT32    ulRetxByteCntHigh;
    VOS_UINT32    ulRetxByteCnt;
    VOS_UINT32    ulTotalPacketCnt;
    VOS_UINT32    ulNewPacketCnt;
    VOS_UINT32    ulRetxPacketCnt;
    VOS_UINT32    ulTxNakReportCnt;
    VOS_UINT32    ulIgnoreAnNakCnt;
    VOS_UINT32    ulRlpFlushCnt;
    VOS_UINT32    ulAnResetRequestCnt;
    VOS_UINT32    ulAtResetRequestCnt;
    VOS_UINT32    ulRxedAnResetAckCnt;
} CTTF_HRPD_MNTN_PER_EMF_RLP_REV_STATISTICS_STRU;

typedef  struct
{
    VOS_UINT32    ulSelectRouteACnt;
    VOS_UINT32    ulSelectRouteBCnt;
    VOS_UINT32    ulTotalByteCntHigh;
    VOS_UINT32    ulTotalByteCnt;
    VOS_UINT32    ulNewByteCntHigh;
    VOS_UINT32    ulNewByteCnt;
    VOS_UINT32    ulRetxByteCntHigh;
    VOS_UINT32    ulRetxByteCnt;
    VOS_UINT32    ulDuplicateByteCnt;
    VOS_UINT32    ulTotalPacketCnt;
    VOS_UINT32    ulNewPacketCnt;
    VOS_UINT32    ulRetxPacketCnt;
    VOS_UINT32    ulRxNakReportCnt;
    VOS_UINT32    ulNakAbortCnt;
    VOS_UINT32    ulAnResetRequestCnt;
    VOS_UINT32    ulAtResetRequestCnt;
    VOS_UINT32    ulRxedAnResetAckCnt;
} CTTF_HRPD_MNTN_PER_EMF_RLP_FWD_STATISTICS_STRU;

typedef  struct
{
    VOS_UINT8                                     ucLinkFlowId;
    CTTF_HRPD_PA_MNTN_FLOW_PROTOCOL_ENUM_UINT8    enFlowProtocol;
    CTTF_HRPD_PA_MNTN_ROUTE_PROTOCOL_ENUM_UINT8   enRouteProtocol;
    VOS_UINT8                                     aucReserved[1];
    CTTF_HRPD_MNTN_PER_EMF_RLP_REV_STATISTICS_STRU   stRevInfo;
    CTTF_HRPD_MNTN_PER_EMF_RLP_FWD_STATISTICS_STRU   stFwdInfo;
} CTTF_HRPD_MNTN_PER_EMF_RLP_STATISTICS_STRU;

typedef  struct
{
    VOS_UINT16                                   usPrimId;
    VOS_UINT16                                   usToolId;
    CTTF_HRPD_MNTN_PER_EMF_RLP_STATISTICS_STRU   astRlpEntity[CTTF_HRPD_MNTN_EMF_RLP_MAX_NUM];
} CTTF_OM_HRPD_MNTN_EMF_RLP_STATISTICS_STRU;

typedef struct
{
    CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM_UINT8  enSubProtocol;
    VOS_UINT8                               aucReserve[3];
    VOS_UINT32                              ulSuccAttemptCnt;
    VOS_UINT32                              ulMaxProbeFailCnt;
    VOS_UINT32                              ulAdjacentProbeTimerExpiredCnt;
    VOS_UINT32                              ulMailboxFailCnt;
    VOS_UINT32                              ulCprocFailCnt;
    VOS_UINT32                              ulSndErrorIndCnt;
    VOS_UINT32                              ulAccessProbe1Cnt;
    VOS_UINT32                              ulAccessProbe2Cnt;
    VOS_UINT32                              ulAccessProbe3Cnt;
    VOS_UINT32                              ulAccessProbe4Cnt;
    VOS_UINT32                              ulAccessProbe5Cnt;
    VOS_UINT32                              ulAccessProbeAboveCnt;
    VOS_UINT32                              ulPhyPkt256BitCnt;
    VOS_UINT32                              ulPhyPkt512BitCnt;
    VOS_UINT32                              ulPhyPkt1024BitCnt;
}CTTF_HRPD_ACMAC_MNTN_STATISTIC_STRU;

typedef struct
{
    CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM_UINT8  enSubProtocol;
    VOS_UINT8                               aucReserve[3];
    VOS_UINT32                              ulPhyPkt128BitCnt;
    VOS_UINT32                              ulPhyPkt256BitCnt;
    VOS_UINT32                              ulPhyPkt512BitCnt;
    VOS_UINT32                              ulPhyPkt1024BitCnt;
    VOS_UINT32                              ulMacLayerPktCnt;
}CTTF_HRPD_CCMAC_MNTN_STATISTIC_STRU;

typedef struct
{
    CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM_UINT8  enSubProtocol;
    CTTF_HRPD_RTCMAC_MNTN_RATE_ENUM_UINT8   enRateLimit;
    VOS_UINT8                               aucReserve[2];
    VOS_UINT32                              ulPhyPkt128BitCnt;
    VOS_UINT32                              ulPhyPkt256BitCnt;
    VOS_UINT32                              ulPhyPkt512BitCnt;
    VOS_UINT32                              ulPhyPkt768BitCnt;
    VOS_UINT32                              ulPhyPkt1024BitCnt;
    VOS_UINT32                              ulPhyPkt1536BitCnt; 
    VOS_UINT32                              ulPhyPkt2048BitCnt;
    VOS_UINT32                              ulPhyPkt3072BitCnt;
    VOS_UINT32                              ulPhyPkt4096BitCnt;
    VOS_UINT32                              ulPhyPkt6144BitCnt;
    VOS_UINT32                              ulPhyPkt8192BitCnt;
    VOS_UINT32                              ulPhyPkt12288BitCnt;
    VOS_UINT32                              ulSndErrorIndCnt;
} CTTF_HRPD_RTCMAC_MNTN_STATISTIC_STRU;

typedef struct
{
    CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM_UINT8  enSubProtocol;
    VOS_UINT8                               aucReserve[3];
    VOS_UINT32                              ulPhyPkt128BitCnt;
    VOS_UINT32                              ulPhyPkt256BitCnt;
    VOS_UINT32                              ulPhyPkt512BitCnt;
    VOS_UINT32                              ulPhyPkt1024BitCnt;
    VOS_UINT32                              ulPhyPkt2048BitCnt;
    VOS_UINT32                              ulPhyPkt3072BitCnt;
    VOS_UINT32                              ulPhyPkt4096BitCnt;
    VOS_UINT32                              ulPhyPkt5120BitCnt;
    VOS_UINT32                              ulTotPhyPktCnt;
    VOS_UINT32                              ulTotMacLayPktCnt;
    VOS_UINT32                              ulTotSingUserPktCnt;
    VOS_UINT32                              ulTotMultiUserPktCnt;
    VOS_UINT32                              ulMaxSecLayPktNum;
    VOS_UINT32                              ulTotalMacPacketBytes;
    VOS_UINT32                              ulTotMyAtMacPayloadBytes;
    VOS_UINT32                              ulTotOtherAtMacPayloadBytes;
}CTTF_HRPD_FTCMAC_MNTN_STATISTIC_STRU;

typedef  struct
{
    VOS_UINT16                              usPrimId;
    VOS_UINT16                              usToolId;

    CTTF_HRPD_ACMAC_MNTN_STATISTIC_STRU     stAcMac;
    CTTF_HRPD_CCMAC_MNTN_STATISTIC_STRU     stCcMac;
    CTTF_HRPD_RTCMAC_MNTN_STATISTIC_STRU    stRtcMac;
    CTTF_HRPD_FTCMAC_MNTN_STATISTIC_STRU    stFtcMac;
} CTTF_OM_HRPD_MAC_MNTN_STATISTIC_STRU;

typedef struct
{
    CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM_UINT8                  enSubProtocol;
    CTTF_HRPD_MNTN_CC_STATE_ENUM_UINT8                      enState;
    VOS_UINT8                                               aucReserve[2];
}CTTF_HRPD_MNTN_MODULE_CC_MAC_PROTOCL_STATE_STRU;

typedef struct
{
    CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM_UINT8                  enSubProtocol;
    CTTF_HRPD_MNTN_AC_STATE_ENUM_UINT8                      enState;
    VOS_UINT8                                               aucReserve[2];
}CTTF_HRPD_MNTN_MODULE_AC_MAC_PROTOCL_STATE_STRU;

typedef struct
{
    CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM_UINT8                  enSubProtocol;
    CTTF_HRPD_MNTN_FTC_STATE_ENUM_UINT8                     enState;
    VOS_UINT8                                               aucReserve[2];
}CTTF_HRPD_MNTN_MODULE_FTC_MAC_PROTOCL_STATE_STRU;

typedef struct
{
    CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM_UINT8                      enSubProtocol;
    CTTF_HRPD_MNTN_RTC_STATE_ENUM_UINT8                         enState;
    VOS_UINT8                                                   aucReserve[2];
}CTTF_HRPD_MNTN_MODULE_RTC_MAC_PROTOCL_STATE_STRU;

typedef struct
{
    CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM_UINT8                      enSubProtocol;
    CTTF_HRPD_MNTN_SECURITY_LAYER_PROTOCOL_STATE_ENUM_UINT8     enState;
    VOS_UINT8                                                   aucReserve[2];
}CTTF_HRPD_MNTN_MODULE_AUTHENTICATION_PROTOCL_STATE_STRU;

typedef struct
{
    CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM_UINT8                      enSubProtocol;
    CTTF_HRPD_MNTN_SECURITY_LAYER_PROTOCOL_STATE_ENUM_UINT8     enState;
    VOS_UINT8                                                   aucReserve[2];
}CTTF_HRPD_MNTN_MODULE_ENCRYPTION_PROTOCL_STATE_STRU;

typedef struct
{
    CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM_UINT8                      enSubProtocol;
    CTTF_HRPD_MNTN_SECURITY_LAYER_PROTOCOL_STATE_ENUM_UINT8     enState;
    VOS_UINT8                                                   aucReserve[2];
}CTTF_HRPD_MNTN_MODULE_SECURITY_PROTOCL_STATE_STRU;

typedef struct
{
    CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM_UINT8                      enSubProtocol;
    CTTF_HRPD_MNTN_STREAM_FLOW_CTRL_PROTOCOL_STATE_ENUM_UINT8   enState;
    VOS_UINT8                                                   aucReserve[2];
}CTTF_HRPD_MNTN_MODULE_STREAM_FLOW_CTRL_PROTOCL_STATE_STRU;

typedef struct
{
    CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM_UINT8                      enSubProtocol;
    CTTF_HRPD_MNTN_STREAM_APP_PROTOCOL_STATE_ENUM_UINT8         enState;
    VOS_UINT8                                                   aucReserve[2];
}CTTF_HRPD_MNTN_MODULE_STREAM_APP_PROTOCL_STATE_STRU;

typedef struct
{
    CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM_UINT8                      enSubProtocol;
    CTTF_HRPD_MNTN_SNP_UP_TX_STATE_ENUM_UINT8                   enState;
    VOS_UINT8                                                   aucReserve[2];
}CTTF_HRPD_MNTN_MODULE_SNP_UP_TX_STATE_STRU;

typedef struct
{
    VOS_UINT16                                                  usPrimId;
    VOS_UINT16                                                  usToolId;

    CTTF_HRPD_MNTN_MODULE_CC_MAC_PROTOCL_STATE_STRU             stCcMac;
    CTTF_HRPD_MNTN_MODULE_AC_MAC_PROTOCL_STATE_STRU             stAcMac;
    CTTF_HRPD_MNTN_MODULE_FTC_MAC_PROTOCL_STATE_STRU            stFtcMac;
    CTTF_HRPD_MNTN_MODULE_RTC_MAC_PROTOCL_STATE_STRU            stRtcMac;
    CTTF_HRPD_MNTN_MODULE_AUTHENTICATION_PROTOCL_STATE_STRU     stAuth;
    CTTF_HRPD_MNTN_MODULE_ENCRYPTION_PROTOCL_STATE_STRU         stEncryption;
    CTTF_HRPD_MNTN_MODULE_SECURITY_PROTOCL_STATE_STRU           stSecurity;
    CTTF_HRPD_MNTN_MODULE_STREAM_FLOW_CTRL_PROTOCL_STATE_STRU   stStream0;
    CTTF_HRPD_MNTN_MODULE_STREAM_FLOW_CTRL_PROTOCL_STATE_STRU   stStream1;
    CTTF_HRPD_MNTN_MODULE_STREAM_FLOW_CTRL_PROTOCL_STATE_STRU   stStream2;
    CTTF_HRPD_MNTN_MODULE_STREAM_FLOW_CTRL_PROTOCL_STATE_STRU   stStream3;
    CTTF_HRPD_MNTN_MODULE_STREAM_APP_PROTOCL_STATE_STRU         stStream0App;
    CTTF_HRPD_MNTN_MODULE_STREAM_APP_PROTOCL_STATE_STRU         stStream1App;
    CTTF_HRPD_MNTN_MODULE_STREAM_APP_PROTOCL_STATE_STRU         stStream2App;
    CTTF_HRPD_MNTN_MODULE_STREAM_APP_PROTOCL_STATE_STRU         stStream3App;
    CTTF_HRPD_MNTN_MODULE_SNP_UP_TX_STATE_STRU                  stSnpUplinkTx;
}CTTF_OM_HRPD_MNTN_MODULE_PROTOCOL_STATE_STRU;

typedef struct
{
    VOS_UINT32      aulACKsNum[CTTF_HRPD_MAC_TRANS_MODE_BUTT];
    VOS_UINT32      aulPktNumOnInterlace[CTTF_HRPD_MNTN_RTC3MAC_INTERLACE_MAX_NUM][CTTF_HRPD_MAC_TRANS_MODE_BUTT];
}CTTF_HRPD_MNTN_RTC3MAC_ACK_INFO_STRU;

typedef struct
{
    VOS_UINT32                              ulGoodPacketNumSum;
    VOS_UINT32                              aulGoodPacketNum[CTTF_HRPD_MAC_TRANS_MODE_BUTT];
    VOS_UINT32                              ulAvgPacketTerminationSum;
    VOS_UINT32                              aulAvgPacketTermination[CTTF_HRPD_MAC_TRANS_MODE_BUTT];
    VOS_UINT32                              ulTotlPktTxTimeSum;
    VOS_UINT32                              aulTotlPktTxTime[CTTF_HRPD_MAC_TRANS_MODE_BUTT];
}CTTF_HRPD_MNTN_RTC3MAC_ACK_INFO_STATIS_STRU;

typedef struct
{
    VOS_UINT16                                      usPrimId;
    VOS_UINT16                                      usToolId;

    CTTF_HRPD_MNTN_RTC3MAC_ACK_INFO_STRU            astRtc3MacAckInfo[CTTF_HRPD_MNTN_RTC3MAC_PS_BUTT][CSDR_HARQ_MNTN_SUBPACKET_BUTT]; 
    CTTF_HRPD_MNTN_RTC3MAC_ACK_INFO_STATIS_STRU     astRtc3MacAckInfoStatis[CTTF_HRPD_MNTN_RTC3MAC_PS_BUTT];
    VOS_UINT32                                      ulTotalParqNAKsNum;
    VOS_UINT32                                      ulTotalPacketSentNum;
    VOS_UINT32                                      ulTotalPer;
}CTTF_OM_HRPD_MNTN_RTC3MAC_ACK_INFO_REPORT_STRU;

#ifndef COMM_ITT
extern VOS_VOID TTF_TraceModuleSet(VOS_UINT8 *paucModuleId);
#endif
extern VOS_VOID *TTF_FilterMsgCallBack(MsgBlock *pMsg);
extern VOS_VOID WTTF_TraceModuleCfgReq(VOS_VOID* pMsg);
extern VOS_VOID WTTF_MAC_R99MailBox_ReadForIpcHalt(VOS_VOID);
extern VOS_VOID WTTF_R99MailboxInitForCbt(VOS_VOID);

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

#endif /* end of TtfOamInterface.h */
