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

#ifndef __ATCTX_H__
#define __ATCTX_H__

/*****************************************************************************
  1 ??????????????
*****************************************************************************/
#include "product_config.h"
#include "v_id.h"
#include "v_typdef.h"
#include "v_msg.h"
#include "PsCommonDef.h"
#include "PsTypeDef.h"
#include "NVIM_Interface.h"
#include "MnClient.h"
#include "TafApi.h"
#include "MnMsgApi.h"
#include "MnCallApi.h"
#include "TafTypeDef.h"
#include "TafApsApi.h"
#include "TafAppMma.h"
#include "TafAppSsa.h"
#include "Taf_Tafm_Remote.h"
#include "AtMuxInterface.h"
#include "AtCtxPacket.h"
#include "NasNvInterface.h"
#include "AtTimer.h"
#include "AtInternalMsg.h"
/* Added by wx270776 for OM????, 2015-7-24, begin */
#include "AtMntn.h"
/* Added by wx270776 for OM????, 2015-7-24, end */
#if (FEATURE_ON == FEATURE_LTE)
#include "LNasNvInterface.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 ??????
*****************************************************************************/
/* ????ClientIndex????????????2??bit??????ModemId??
   Modem0??????????Client index??00111111(0x3F)??
   Modem1??????????Client index??01111111(0x7F)
   Modem2??????????Client index??10111111(0xBF)*/

/*????Client Id??????index??*/
/* Modem 0??????Client Index */
#define AT_BROADCAST_CLIENT_INDEX_MODEM_0  (0x3F)

/* Modem 1??????Client Index */
#define AT_BROADCAST_CLIENT_INDEX_MODEM_1  (0x7F)

/* Modem 2??????Client Index */
#define AT_BROADCAST_CLIENT_INDEX_MODEM_2  (0xBF)

/* ??????????????Client Id */
#define AT_IS_BROADCAST_CLIENT_INDEX(i)    ((AT_BROADCAST_CLIENT_INDEX_MODEM_0 == (i)) \
                                         || (AT_BROADCAST_CLIENT_INDEX_MODEM_1 == (i)) \
                                         || (AT_BROADCAST_CLIENT_INDEX_MODEM_2 == (i)))

/* Modem ID??NV??????Bit?? */
#define AT_NV_CLIENT_CONFIG_MODEM_ID_OFFSET (2)


/*********************************PORT Begin*****************************/

#define AT_INVALID_SPE_PORT             (-1)

/*================================PORT NO Begin================================*/

typedef VOS_UINT8 AT_PORT_NO;
#define AT_BUTT_PORT_NO                 (0xFF)              /*????PORT NO*/

#define AT_UART_PORT_NO                 (0)

/* MODEM????????always-on??????modem????????????AT??PID??????????????????????????PORT_TYPE???????????????????????????? */
#define AT_PORT_TYPE_MODEM              (3)
#define AT_USB_MODEM_PORT_NO            (4)                 /*????????????MODEM??????B020????????????????????????????????*/
#define AT_SOCK_PORT_NO                 (5)                 /*????SOCK????*/
#define AT_APP_PORT_NO                  (6)                 /*????APP????*/
#define AT_APP_SOCK_PORT_NO             (7)                 /*????APP SOCK????*/
#if (VOS_WIN32 == VOS_OS_VER)
#define AT_USB_COM_PORT_NO              (2)
#else
#define AT_USB_COM_PORT_NO              (DMS_PHY_BEAR_USB_PCUI) /*????8*/
#endif
#define AT_CTR_PORT_NO                  (DMS_PHY_BEAR_USB_CTRL)/*????9??????????????????????control????*/
#define AT_PCUI2_PORT_NO                (DMS_PHY_BEAR_USB_PCUI2)/*????10??????????????????????PCUI2????*/

#define AT_NDIS_PORT_NO                 (DMS_PHY_BEAR_USB_NCM)     /*????11??NDIS AT????????????????????*/
#define AT_HSIC1_PORT_NO                (12)                /*HSIC AT????1????*/
#define AT_HSIC2_PORT_NO                (13)                /*HSIC AT????2????*/
#define AT_HSIC3_PORT_NO                (14)                /*HSIC AT????3????*/
#define AT_HSIC4_PORT_NO                (15)                /*HSIC AT????4????*/
#define AT_MUX1_PORT_NO                 (16)                /*MUX AT????1????*/
#define AT_MUX2_PORT_NO                 (17)                /*MUX AT????2????*/
#define AT_MUX3_PORT_NO                 (18)                /*MUX AT????3????*/
#define AT_MUX4_PORT_NO                 (19)                /*MUX AT????4????*/
#define AT_MUX5_PORT_NO                 (20)                /*MUX AT????5????*/
#define AT_MUX6_PORT_NO                 (21)                /*MUX AT????6????*/
#define AT_MUX7_PORT_NO                 (22)                /*MUX AT????7????*/
#define AT_MUX8_PORT_NO                 (23)                /*MUX AT????8????*/
#define AT_HSIC_MODEM_PORT_NO           (24)                /* HSIC MODEM???? */
#define AT_HSUART_PORT_NO               (25)                /* HSUART???? */

#define AT_MIN_ABORT_TIME_INTERNAL      (13)
#define AT_MAX_TICK_TIME_VALUE          (0xFFFFFFFFU)

/*================================PORT NO End================================*/
/*********************************PORT End*****************************/

/*********************************COMM Begin*****************************/
typedef TAF_UINT8 AT_CMEE_TYPE;
#define AT_CMEE_ONLY_ERROR                0
#define AT_CMEE_ERROR_CODE                1
#define AT_CMEE_ERROR_CONTENT             2

/* Added by L60609 for MUX??2012-08-03,  Begin */
/* AP-Modem ????????????????????8??MUX AT???? */
#define AT_MUX_AT_CHANNEL_MAX           (8)

#define AT_MUX_AT_CHANNEL_INDEX_1       (0)
#define AT_MUX_AT_CHANNEL_INDEX_2       (1)
#define AT_MUX_AT_CHANNEL_INDEX_3       (2)
#define AT_MUX_AT_CHANNEL_INDEX_4       (3)
#define AT_MUX_AT_CHANNEL_INDEX_5       (4)
#define AT_MUX_AT_CHANNEL_INDEX_6       (5)
#define AT_MUX_AT_CHANNEL_INDEX_7       (6)
#define AT_MUX_AT_CHANNEL_INDEX_8       (7)
/* Added by L60609 for MUX??2012-08-03,  End */

#define AT_OCTET_MOVE_FOUR_BITS    (0x04)  /* ??????????????4?? */
#define AT_OCTET_MOVE_EIGHT_BITS   (0x08)  /* ??????????????8?? */
#define AT_OCTET_LOW_FOUR_BITS     (0x0f)  /* ??????????????????4?? */
#define AT_OCTET_HIGH_FOUR_BITS    (0xf0)  /* ??????????????????4?? */
#define AT_MIN(n1,n2)         (((n1) > (n2)) ? (n2):(n1))
/*********************************COMM End*****************************/

/*********************************CC/SS Begin*****************************/
typedef VOS_UINT8 AT_SALS_TYPE;
#define AT_SALS_DISABLE_TYPE            0
#define AT_SALS_ENABLE_TYPE             1

typedef VOS_UINT8 AT_CLIP_TYPE;
#define AT_CLIP_DISABLE_TYPE            0
#define AT_CLIP_ENABLE_TYPE             1

typedef VOS_UINT8 AT_COLP_TYPE;
#define AT_COLP_DISABLE_TYPE            0
#define AT_COLP_ENABLE_TYPE             1

typedef VOS_UINT8 AT_CLIR_TYPE;
#define AT_CLIR_AS_SUBSCRIPT            0
#define AT_CLIR_INVOKE                  1
#define AT_CLIR_SUPPRESS                2

typedef VOS_UINT8 AT_CRC_TYPE;
#define AT_CRC_DISABLE_TYPE             0
#define AT_CRC_ENABLE_TYPE              1

typedef VOS_UINT8 AT_CCWA_TYPE;
#define AT_CCWA_DISABLE_TYPE            0
#define AT_CCWA_ENABLE_TYPE             1

/* Modified by s00217060 for ????????AT??????????????C??, 2013-4-8, begin */
#define AT_SIMST_DISABLE_TYPE          (0)
#define AT_SIMST_ENABLE_TYPE           (1)
/* Modified by s00217060 for ????????AT??????????????C??, 2013-4-8, end */


typedef VOS_UINT8 AT_CUSD_STATE_TYPE;
#define AT_CUSD_MT_IDL_STATE         0
#define AT_CUSD_MT_REQ_STATE         1
#define AT_CUSD_NT_IND_STATE         2

typedef MN_CALL_MODE_ENUM_U8     AT_CMOD_MODE_ENUM;

/*********************************CC/SS End*****************************/

/*********************************SMS Begin************************************/
#define AT_SMSMT_BUFFER_MAX             (2)

typedef VOS_UINT8 AT_CSCS_TYPE;
#define AT_CSCS_IRA_CODE            0
#define AT_CSCS_UCS2_CODE           1
#define AT_CSCS_GSM_7Bit_CODE       2

typedef VOS_UINT8 AT_CSDH_TYPE;
#define AT_CSDH_NOT_SHOW_TYPE           (0)
#define AT_CSDH_SHOW_TYPE               (1)

typedef VOS_UINT8 AT_CNMI_MODE_TYPE;
#define AT_CNMI_MODE_BUFFER_TYPE            0
#define AT_CNMI_MODE_SEND_OR_DISCARD_TYPE   1
#define AT_CNMI_MODE_SEND_OR_BUFFER_TYPE    2
#define AT_CNMI_MODE_EMBED_AND_SEND_TYPE    3

typedef VOS_UINT8 AT_CNMI_MT_TYPE;
#define AT_CNMI_MT_NO_SEND_TYPE             0
#define AT_CNMI_MT_CMTI_TYPE                1
#define AT_CNMI_MT_CMT_TYPE                 2
#define AT_CNMI_MT_CLASS3_TYPE              3
#define AT_CNMI_MT_TYPE_MAX                 4

typedef VOS_UINT8 AT_CNMI_BM_TYPE;
#define AT_CNMI_BM_NO_SEND_TYPE             0
#define AT_CNMI_BM_CBMI_TYPE                1
#define AT_CNMI_BM_CBM_TYPE                 2
#define AT_CNMI_BM_CLASS3_TYPE              3

typedef VOS_UINT8 AT_CNMI_DS_TYPE;
#define AT_CNMI_DS_NO_SEND_TYPE             0
#define AT_CNMI_DS_CDS_TYPE                 1
#define AT_CNMI_DS_CDSI_TYPE                2
#define AT_CNMI_DS_TYPE_MAX                 3

typedef VOS_UINT8 AT_CNMI_BFR_TYPE;
#define AT_CNMI_BFR_SEND_TYPE               0
#define AT_CNMI_BFR_CLEAR_TYPE              1

/* Deleted by s00217060 for ????????AT??????????????C??, 2013-4-3, end */
/* Deleted by s00217060 for ????????AT??????????????C??, 2013-4-3, end */

#define AT_BUFFER_CBM_EVENT_MAX             5
#define AT_BUFFER_SMT_EVENT_MAX             5

/*
0??CS_prefer????????????CS????????
1??PS_prefer????????????PS????????
2??CS_only??????????CS????????
3??PS_only??????????PS????????
*/
#define AT_NV_SMS_DOMAIN_CS_PREFERRED           0
#define AT_NV_SMS_DOMAIN_PS_PREFERRED           1
#define AT_NV_SMS_DOMAIN_CS_ONLY                2
#define AT_NV_SMS_DOMAIN_PS_ONLY                3

/*********************************SMS End************************************/

/*********************************NET Begin************************************/
typedef VOS_UINT8 AT_MODE_REPORT_TYPE;
#define AT_MODE_RESULT_CODE_NOT_REPORT_TYPE    0
#define AT_MODE_RESULT_CODE_REPORT_TYPE        1

typedef VOS_UINT8 AT_CREG_TYPE;
#define AT_CREG_RESULT_CODE_NOT_REPORT_TYPE    0
#define AT_CREG_RESULT_CODE_BREVITE_TYPE       1
#define AT_CREG_RESULT_CODE_ENTIRE_TYPE        2

typedef VOS_UINT8 AT_CGREG_TYPE;
#define AT_CGREG_RESULT_CODE_NOT_REPORT_TYPE   0
#define AT_CGREG_RESULT_CODE_BREVITE_TYPE      1
#define AT_CGREG_RESULT_CODE_ENTIRE_TYPE       2

/* Deleted by s00217060 for ????????AT??????????????C??, 2013-4-1, begin */
/* Deleted by s00217060 for ????????AT??????????????C??, 2013-4-1, end */

#define AT_ROAM_FEATURE_OFF                    0
#define AT_ROAM_FEATURE_ON                     1
/*********************************NET End************************************/

/*********************************CTRL Begin************************************/
/* ????????????????  */
#define AT_ANTENNA_LEVEL_MAX_NUM        3

/* Modified by s00217060 for ????????AT??????????????C??, 2013-4-1, begin */
#define AT_RSSI_RESULT_CODE_NOT_REPORT_TYPE    (0)
/* Modified by s00217060 for ????????AT??????????????C??, 2013-4-1, end */

#define AT_CURC_RPT_CFG_MAX_SIZE        (8)
#define AT_CURC_RPT_CFG_PARA_LEN        (16)

/*********************************CTRL End************************************/

/*****************************************************************************
    ??????UART??????????
*****************************************************************************/
/* ??????RING??????????????????????(ms) */
#define AT_UART_DEFAULT_SMS_RI_ON_INTERVAL      (1000)
#define AT_UART_DEFAULT_SMS_RI_OFF_INTERVAL     (1000)

/* ????RING????????????????????(ms) */
#define AT_UART_DEFAULT_VOICE_RI_ON_INTERVAL    (1000)
#define AT_UART_DEFAULT_VOICE_RI_OFF_INTERVAL   (4000)

/* ????RING?????????????? */
#define AT_UART_DEFAULT_VOICE_RI_CYCLE_TIMES    (10)

#define AT_UART_DEFAULT_BAUDRATE        (AT_UART_BAUDRATE_115200)
#define AT_UART_DEFAULT_FORMAT          (AT_UART_FORMAT_8DATA_1STOP)
/*
 * ??: ??????????????UART IP????, ????????????????????
 *
 * V3R3            --- ?????? SPACE
 *
 * V7R11(or later) --- ?????? ODD
 *
 */
#define AT_UART_DEFAULT_PARITY          (AT_UART_PARITY_ODD)

#define AT_UART_DEFAULT_DCD_MODE        (AT_UART_DCD_MODE_CONNECT_ON)
#define AT_UART_DEFAULT_DTR_MODE        (AT_UART_DTR_MODE_HANGUP_CALL)
#define AT_UART_DEFAULT_DSR_MODE        (AT_UART_DSR_MODE_ALWAYS_ON)

#define AT_UART_DEFAULT_FC_DCE_BY_DTE   (AT_UART_FC_DCE_BY_DTE_NONE)
#define AT_UART_DEFAULT_FC_DTE_BY_DCE   (AT_UART_FC_DTE_BY_DCE_NONE)



#if !defined(AT_ARRAY_SIZE)
#define AT_ARRAY_SIZE(a)                (sizeof((a)) / sizeof((a[0])))
#endif

#define AT_SET_BIT64(n)       ((VOS_UINT64)1 << (n))

/*lint -e960 -e960 ??????:f00179208;????:clean waring*/
#define AT_CLIENT_CFG_ELEMENT(port)\
            { AT_CLIENT_ID_##port, TAF_NV_CLIENT_CFG_##port, #port, AT_SET_BIT64(TAF_NV_CLIENT_CFG_##port) }
/*lint +e960 +e960 ??????:f00179208;????:clean waring*/

#define AT_GET_CLIENT_CFG_TAB_LEN()         (g_ucAtClientCfgMapTabLen)

#define AT_PORT_LEN_MAX                     (20)

/* WIFI n????WL??????????????0~7????8?? */
#define AT_WIFI_N_RATE_NUM              (8)

#define AT_RELEASE_R11                  (0x00000b00)

#define AT_MAX_MSG_NUM                  (80)

/*****************************************************************************
  3 ????????
*****************************************************************************/
/*********************************TIMER Begin*****************************/
enum AT_INTERNAL_TIMER_TYPE_ENUM
{
    AT_S0_TIMER               = 1,
    AT_HOLD_CMD_TIMER         = 2,
    /* Deleted by l00198894 for V9R1 STK????, 2013/07/11 */
    /* Add by w00199382 for V7????????, 2012-04-07, Begin   */
    AT_SHUTDOWN_TIMER         = 8,
    /* Add by w00199382 for V7????????, 2012-04-07, End   */

    AT_VOICE_RI_TIMER         = 9,
    AT_SMS_RI_TIMER           = 10,

    AT_INTERNAL_TIMER_BUTT
};
/*********************************TIMER End*****************************/

/*********************************PORT Begin*****************************/

/*****************************************************************************
 ??????    : AT_IO_LEVEL_ENUM
 ????????  : ????????????

  1.??    ??   : 2013??9??23??
    ??    ??   : A00165503
    ????????   : ????????
*****************************************************************************/
enum AT_IO_LEVEL_ENUM
{
    AT_IO_LEVEL_LOW                     = 0,
    AT_IO_LEVEL_HIGH                    = 1,

    AT_IO_LEVEL_BUTT
};
typedef VOS_UINT8 AT_IO_LEVEL_ENUM_UINT8;

/* ??AT^APRPTPORTSEL??????????????????????HSIC AT????????????AT???????????? */
typedef enum
{
    AT_HSIC_REPORT_ON,                  /* ???????????? */
    AT_HSIC_REPORT_OFF,                 /* ?????????????? */

    AT_HSIC_REPORT_BUTT
}AT_HSIC_REPORT_TYPE_ENUM;
typedef VOS_UINT32 AT_HSIC_REPORT_TYPE_ENUM_UINT32;

/*********************************PROT End*****************************/

/*********************************CTRL Begin*****************************/
/* Deleted by s00217060 for ????????AT??????????????C??, 2013-4-10, begin */
/* Deleted by s00217060 for ????????AT??????????????C??, 2013-4-10, end */


enum AT_CMD_ANTENNA_LEVEL_ENUM
{
    AT_CMD_ANTENNA_LEVEL_0,
    AT_CMD_ANTENNA_LEVEL_1,
    AT_CMD_ANTENNA_LEVEL_2,
    AT_CMD_ANTENNA_LEVEL_3,
    AT_CMD_ANTENNA_LEVEL_4,
    AT_CMD_ANTENNA_LEVEL_BUTT
};
typedef VOS_UINT8 AT_CMD_ANTENNA_LEVEL_ENUM_UINT8;
/*********************************CTRL End************************************/

/*********************************COMM Begin**********************************/
enum AT_CLCK_PARA_CLASS_ENUM
{
    AT_CLCK_PARA_CLASS_VOICE                    = 0x01,
    AT_CLCK_PARA_CLASS_DATA                     = 0x02,
    AT_CLCK_PARA_CLASS_FAX                      = 0x04,
    AT_CLCK_PARA_CLASS_VOICE_FAX                = 0x05,
    AT_CLCK_PARA_CLASS_VOICE_DATA_FAX           = 0x07,
    AT_CLCK_PARA_CLASS_SMS                      = 0x08,
    AT_CLCK_PARA_CLASS_FAX_SMS                  = 0x0C,
    AT_CLCK_PARA_CLASS_VOICE_FAX_SMS            = 0x0D,
    AT_CLCK_PARA_CLASS_VOICE_DATA_FAX_SMS       = 0x0F,
    AT_CLCK_PARA_CLASS_DATA_SYNC                = 0x10,
    AT_CLCK_PARA_CLASS_DATA_ASYNC               = 0x20,
    AT_CLCK_PARA_CLASS_DATA_PKT                 = 0x40,
    AT_CLCK_PARA_CLASS_DATA_SYNC_PKT            = 0x50,
    AT_CLCK_PARA_CLASS_DATA_PAD                 = 0x80,
    AT_CLCK_PARA_CLASS_DATA_ASYNC_PAD           = 0xA0,
    AT_CLCK_PARA_CLASS_DATA_SYNC_ASYNC_PKT_PKT  = 0xF0,
    AT_CLCK_PARA_CLASS_ALL                      = 0xFF,
};
typedef VOS_UINT8 AT_CLCK_PARA_CLASS_ENUM_UINT8;

/*********************************COMM End************************************/

/*********************************CC/SS Begin*****************************/
/* Deleted by s00217060 for ????????AT??????????????C??, 2013-4-8, begin */
/* Deleted by s00217060 for ????????AT??????????????C??, 2013-4-8, end */
/* Deleted by l00198894 for V9R1 STK????, 2013/07/11 */


/*********************************CC/SS End*****************************/

/*********************************SMS Begin************************************/
enum AT_CMGF_MSG_FORMAT_ENUM
{
    AT_CMGF_MSG_FORMAT_PDU,
    AT_CMGF_MSG_FORMAT_TEXT
};
typedef TAF_UINT8 AT_CMGF_MSG_FORMAT_ENUM_U8;

typedef MN_MSG_SEND_DOMAIN_ENUM_U8 AT_CGSMS_SEND_DOMAIN_ENUM_U8;

/*********************************SMS End************************************/

/*********************************NET Begin************************************/

/*****************************************************************************
 ??????    : AT_CEREG_TYPE_ENUM_UINT8
 ????????  : AT+CEREG??????????????????
 1.??    ??   : 2011??12??2??
   ??    ??   : z00161729
   ????????   : ????
*****************************************************************************/
enum AT_CEREG_TYPE_ENUM
{
    AT_CEREG_RESULT_CODE_NOT_REPORT_TYPE,    /* ????+CEREG ?????????? */
    AT_CEREG_RESULT_CODE_BREVITE_TYPE,       /* ????????????????????????????+CEREG: <stat>??????????????????????*/
    AT_CEREG_RESULT_CODE_ENTIRE_TYPE,        /* ????????????????????????+CEREG:<stat>[,<tac>,<ci>[,<AcT>]]??????????????????????*/
    AT_CEREG_RESULT_CODE_TYPE_BUTT
};
typedef VOS_UINT8 AT_CEREG_TYPE_ENUM_UINT8;

/*****************************************************************************
 ??????    : AT_CERSSI_REPORT_TYPE_ENUM_UINT8
 ????????  : AT^CERSSI??????????????????
 1.??    ??   : 2012??11??21??
   ??    ??   : z00161729
   ????????   : ????
*****************************************************************************/
enum AT_CERSSI_REPORT_TYPE_ENUM
{
    AT_CERSSI_REPORT_TYPE_NOT_REPORT,               /* ????^CERSSI?????????? */
    AT_CERSSI_REPORT_TYPE_1DB_CHANGE_REPORT,        /* ????????????????1db??^CERSSI?????????? */
    AT_CERSSI_REPORT_TYPE_2DB_CHANGE_REPORT,        /* ????????????????2db??^CERSSI?????????? */
    AT_CERSSI_REPORT_TYPE_3DB_CHANGE_REPORT,        /* ????????????????3db??^CERSSI?????????? */
    AT_CERSSI_REPORT_TYPE_4DB_CHANGE_REPORT,        /* ????????????????4db??^CERSSI?????????? */
    AT_CERSSI_REPORT_TYPE_5DB_CHANGE_REPORT,        /* ????????????????5db??^CERSSI?????????? */
    AT_CERSSI_REPORT_TYPE_BUTT
};
typedef VOS_UINT8 AT_CERSSI_REPORT_TYPE_ENUM_UINT8;


/*****************************************************************************
 ??????    : AT_RPT_CMD_ENUM
 ????????  : ????????????????

  1.??    ??   : 2012??09??18??
    ??    ??   : l00198894
    ????????   : STK??????????DCM????????????????????
  2.??    ??   : 2012??11??21??
    ??    ??   : z00161729
    ????????   : ????cerssi??nmr
  3.??    ??   : 2012??12??07??
    ??    ??   : w00176964
    ????????   : DTS2012120608537:??????????????????????????
*****************************************************************************/
enum AT_RPT_CMD_INDEX_ENUM
{
    AT_RPT_CMD_MODE                     = 0,
    AT_RPT_CMD_RSSI,
    AT_RPT_CMD_SRVST,
    AT_RPT_CMD_SIMST,
    AT_RPT_CMD_TIME,
    AT_RPT_CMD_SMMEMFULL,
    AT_RPT_CMD_CTZV,

    AT_RPT_CMD_CTZE,

    AT_RPT_CMD_DSFLOWRPT,
    AT_RPT_CMD_ORIG,
    AT_RPT_CMD_CONF,
    AT_RPT_CMD_CONN,
    AT_RPT_CMD_CEND,
    AT_RPT_CMD_STIN,

    AT_RPT_CMD_CERSSI,
    AT_RPT_CMD_ANLEVEL,
    AT_RPT_CMD_LWCLASH,
    AT_RPT_CMD_XLEMA,
    /* Added by w00176964 for V7R1C50_DCM????????????????????, 2012-12-12, begin */
    AT_RPT_CMD_ACINFO,
    /* Added by w00176964 for V7R1C50_DCM????????????????????, 2012-12-12, end */

    AT_RPT_CMD_PLMN,

    /* Added by s00217060 for ????????AT??????????????C??, 2013-4-8, begin */
    /* call state????????CURC???? */
    AT_RPT_CMD_CALLSTATE,

    /* ?????????????????????????????? */
    AT_RPT_CMD_CREG,
    AT_RPT_CMD_CUSD,
    AT_RPT_CMD_CSSI,
    AT_RPT_CMD_CSSU,
    AT_RPT_CMD_LWURC,
    AT_RPT_CMD_CUUS1I,
    AT_RPT_CMD_CUUS1U,
    AT_RPT_CMD_CGREG,
    AT_RPT_CMD_CEREG,
    /* Added by s00217060 for ????????AT??????????????C??, 2013-4-8, end */

    AT_RPT_CMD_BUTT
};
typedef VOS_UINT8 AT_RPT_CMD_INDEX_ENUM_UINT8;

/* Added by s00217060 for ????????AT??????????????C??, 2013-4-8, begin */
/*****************************************************************************
 ??????    : AT_CMD_RPT_CTRL_TYPE_ENUM_UINT8
 ????????  : ????????????????
 1.??    ??   : 2013??4??10??
   ??    ??   : s00217060
   ????????   : ????
*****************************************************************************/
enum AT_CMD_RPT_CTRL_TYPE_ENUM
{
    AT_CMD_RPT_CTRL_BY_CURC,               /* ??????????CURC???? */
    AT_CMD_RPT_CTRL_BY_UNSOLICITED,        /* ???????????????????????? */
    AT_CMD_RPT_CTRL_BUTT
};
typedef VOS_UINT8 AT_CMD_RPT_CTRL_TYPE_ENUM_UINT8;
/* Added by s00217060 for ????????AT??????????????C??, 2013-4-8, end */


/*****************************************************************************
 ??????    : AT_RATE_WCDMA_CATEGORY_ENUM
 ????????  : ??
 ????????  : WCDMA??????????????
*****************************************************************************/
enum AT_RATE_WCDMA_CATEGORY_ENUM
{
    AT_RATE_WCDMA_R99                   = 0,
    AT_RATE_WCDMA_CATEGORY_6            = 6,
    AT_RATE_WCDMA_CATEGORY_8            = 8,
    AT_RATE_WCDMA_CATEGORY_9            = 9,
    AT_RATE_WCDMA_CATEGORY_10           = 10,
    AT_RATE_WCDMA_CATEGORY_12           = 12,
    AT_RATE_WCDMA_CATEGORY_14           = 14,
    AT_RATE_WCDMA_CATEGORY_18           = 18,
    AT_RATE_WCDMA_CATEGORY_24           = 24,
    AT_RATE_WCDMA_CATEGORY_26           = 26,
    AT_RATE_WCDMA_CATEGORY_28           = 28
};
typedef VOS_UINT8 AT_RATE_WCDMA_CATEGORY_ENUM_UINT8;

/* VDF????: CREG/CGREG????<CI>???????????????? */
enum
{
    CREG_CGREG_CI_RPT_TWO_BYTE        = 0, /* CREG/CGREG??<CI>????2????????????*/
    CREG_CGREG_CI_RPT_FOUR_BYTE       = 1, /* CREG/CGREG??<CI>????4????????????*/
    CREG_CGREG_CI_RPT_BUTT
};
typedef VOS_UINT8   CREG_CGREG_CI_RPT_BYTE_ENUM;

/*********************************NET End************************************/

/*********************************AGPS Begin************************************/

/*****************************************************************************
 ??????    : AT_CPOSR_FLG_ENUM
 ????????  : AT+CPOSR ??????????????????
1.??    ??  : 2012??06??28??
  ??    ??  : y00213812
  ????????  : V7R1C50 A_GPS????????????
*****************************************************************************/
enum AT_CPOSR_FLG_ENUM
{
    AT_CPOSR_DISABLE        = 0,                                                /* ?????????????? */
    AT_CPOSR_ENABLE,                                                            /* ???????????? */
    AT_CPOSR_BUTT
};
typedef VOS_UINT8 AT_CPOSR_FLG_ENUM_UNIT8;

/*****************************************************************************
 ??????    : AT_XCPOSR_FLG_ENUM
 ????????  : AT^XCPOSR ??????????????????
1.??    ??  : 2012??06??28??
  ??    ??  : y00213812
  ????????  : V7R1C50 A_GPS????????????
*****************************************************************************/
enum AT_XCPOSR_FLG_ENUM
{
    AT_XCPOSR_DISABLE        = 0,                                                /* ?????????????? */
    AT_XCPOSR_ENABLE,                                                            /* ???????????? */
    AT_XCPOSR_BUTT
};
typedef VOS_UINT8 AT_XCPOSR_FLG_ENUM_UNIT8;

/*****************************************************************************
 ??????    : AT_CMOLRE_TYPE_ENUM
 ????????  : +CMOLRE????????????????????????

  1.??    ??   : 2015??9??9??
    ??    ??   : l00198894
    ????????   : ????????
 *****************************************************************************/
enum AT_CMOLRE_TYPE_ENUM
{
    AT_CMOLRE_NUMERIC        = 0,                                               /* ???????? */
    AT_CMOLRE_VERBOSE,                                                          /* ???????????? */

    AT_CMOLRE_TYPE_BUTT
};
typedef VOS_UINT8 AT_CMOLRE_TYPE_ENUM_UNIT8;

/*****************************************************************************
 ??????    : AT_XML_END_CHAR_ENUM
 ????????  : XML??????????????????????
1.??    ??  : 2012??06??28??
  ??    ??  : y00213812
  ????????  : V7R1C50 A_GPS????????????
*****************************************************************************/
enum AT_XML_END_CHAR_ENUM
{
    AT_XML_CTRL_Z        = 0,                                                   /* ????????????ctrl-Z?? */
    AT_XML_ESC,                                                                 /* ????????????ESC?? */
    AT_XML_BUTT
};
typedef VOS_UINT8 AT_XML_END_CHAR_ENUM_UNIT8;

/*****************************************************************************
 ??????    : AT_XML_PROC_TYPE_ENUM
 ????????  : XML????????????
1.??    ??  : 2012??06??28??
  ??    ??  : y00213812
  ????????  : V7R1C50 A_GPS????????????
*****************************************************************************/
enum AT_XML_PROC_TYPE_ENUM
{
    AT_XML_PROC_TYPE_FINISH             = 0,                                    /* ??????"ctrl-Z"??"ESC"    */
    AT_XML_PROC_TYPE_CONTINUE           = 1,                                    /* ????????????             */
    AT_XML_PROC_TYPE_BUTT
};
typedef VOS_UINT8 AT_XML_PROC_TYPE_ENUM_UINT8;
/*********************************AGPS End************************************/

/*****************************************************************************
 ??????    : AT_ANT_STATE_ENUM_UINT16
 ????????  : ????????
1.??    ??  : 2012??06??28??
  ??    ??  : z60575
  ????????  : DTS2013060307614, DSDA_SAR????????
*****************************************************************************/
enum AT_ANT_STATE_ENUM
{
    AT_ANT_AIRWIRE_MODE            =   0,  /* ???????? */
    AT_ANT_CONDUCTION_MODE         =   1,  /* ???????? */
    AT_ANT_MODE_BUTT
};
typedef VOS_UINT16 AT_ANT_STATE_ENUM_UINT16;

/*****************************************************************************
 ??????    : AT_UART_BAUDRATE_ENUM
 ????????  : UART????????????

  1.??    ??   : 2013??09??18??
    ??    ??   : j00174725
    ????????   : ????

  2.??    ??   : 2014??4??8??
    ??    ??   : A00165503
    ????????   : DTS2014031207569: ??????????????

  3.??    ??   : 2014??12??24??
    ??    ??   : A00165503
    ????????   : DTS2014121801836: HSUART????????
*****************************************************************************/
enum AT_UART_BAUDRATE_ENUM
{
    AT_UART_BAUDRATE_0                  = 0,                /* ???????????????? */
    AT_UART_BAUDRATE_300                = 300,              /* ????????????300 */
    AT_UART_BAUDRATE_600                = 600,              /* ????????????600 */
    AT_UART_BAUDRATE_1200               = 1200,             /* ????????????1200 */
    AT_UART_BAUDRATE_2400               = 2400,             /* ????????????2400 */
    AT_UART_BAUDRATE_4800               = 4800,             /* ????????????4800 */
    AT_UART_BAUDRATE_9600               = 9600,             /* ????????????9600 */
    AT_UART_BAUDRATE_19200              = 19200,            /* ????????????19200 */
    AT_UART_BAUDRATE_38400              = 38400,            /* ????????????38400 */
    AT_UART_BAUDRATE_57600              = 57600,            /* ????????????57600 */
    AT_UART_BAUDRATE_115200             = 115200,           /* ????????????115200 */
    AT_UART_BAUDRATE_230400             = 230400,           /* ????????????230400 */
    AT_UART_BAUDRATE_250000             = 250000,           /* ????????????250000 */
    AT_UART_BAUDRATE_300000             = 300000,           /* ????????????300000 */
    AT_UART_BAUDRATE_375000             = 375000,           /* ????????????375000 */
    AT_UART_BAUDRATE_460800             = 460800,           /* ????????????460800 */
    AT_UART_BAUDRATE_600000             = 600000,           /* ????????????600000 */
    AT_UART_BAUDRATE_750000             = 750000,           /* ????????????750000 */
    AT_UART_BAUDRATE_921600             = 921600,           /* ????????????921600 */
    AT_UART_BAUDRATE_1000000            = 1000000,          /* ????????????1000000 */
    AT_UART_BAUDRATE_1152000            = 1152000,          /* ????????????1152000 */
    AT_UART_BAUDRATE_1500000            = 1500000,          /* ????????????1500000 */
    AT_UART_BAUDRATE_2000000            = 2000000,          /* ????????????2000000 */
    AT_UART_BAUDRATE_2764800            = 2764800,          /* ????????????2764800 */
    AT_UART_BAUDRATE_3000000            = 3000000,          /* ????????????3000000 */

    AT_UART_BAUDRATE_BUTT
};
typedef VOS_UINT32 AT_UART_BAUDRATE_ENUM_UINT32;

/*****************************************************************************
 ??????    : AT_UART_FORMAT_ENUM
 ????????  : UART??????????????????????

  1.??    ??   : 2013??09??18??
    ??    ??   : j00174725
    ????????   : ????
*****************************************************************************/
enum AT_UART_FORMAT_ENUM
{
    AT_UART_FORMAT_AUTO_DETECT          = 0x00,             /* auto detect */
    AT_UART_FORMAT_8DATA_2STOP          = 0x01,             /* 8 data 2 stop */
    AT_UART_FORMAT_8DATA_1PARITY_1STOP  = 0x02,             /* 8 data 1 parity 1 stop*/
    AT_UART_FORMAT_8DATA_1STOP          = 0x03,             /* 8 data 1 stop */
    AT_UART_FORMAT_7DATA_2STOP          = 0x04,             /* 7 data 2 stop */
    AT_UART_FORMAT_7DATA_1PARITY_1STOP  = 0x05,             /* 7 data 1 parity 1 stop */
    AT_UART_FORMAT_7DATA_1STOP          = 0x06,             /* 7 data 1 stop */

    AT_UART_FORMAT_BUTT
};
typedef VOS_UINT8 AT_UART_FORMAT_ENUM_UINT8;

/*****************************************************************************
 ??????    : AT_UART_PARITY_ENUM
 ????????  : UART??????

  1.??    ??   : 2013??09??18??
    ??    ??   : j00174725
    ????????   : ????

  2.??    ??   : 2014??12??24??
    ??    ??   : A00165503
    ????????   : DTS2014121801836: HSUART????????
*****************************************************************************/
enum AT_UART_PARITY_ENUM
{
    AT_UART_PARITY_ODD                  = 0x00,             /* ODD ?? */
    AT_UART_PARITY_EVEN                 = 0x01,             /* EVEN ?? */
    AT_UART_PARITY_MARK                 = 0x02,             /* MARK */
    AT_UART_PARITY_SPACE                = 0x03,             /* SPACE */

    AT_UART_PARITY_BUTT
};
typedef VOS_UINT8 AT_UART_PARITY_ENUM_UINT8;

/*****************************************************************************
 ??????    : AT_UART_DATA_LEN_ENUM
 ????????  : UART ??????????????

  1.??    ??   : 2013??09??18??
    ??    ??   : j00174725
    ????????   : ????
*****************************************************************************/
enum AT_UART_DATA_LEN_ENUM
{
    AT_UART_DATA_LEN_5_BIT              = 5,
    AT_UART_DATA_LEN_6_BIT              = 6,
    AT_UART_DATA_LEN_7_BIT              = 7,
    AT_UART_DATA_LEN_8_BIT              = 8,

    AT_UART_DATA_LEN_BUTT
};
typedef VOS_UINT8 AT_UART_DATA_LEN_ENUM_UINT8;

/*****************************************************************************
 ??????    : AT_UART_STOP_LEN_ENUM
 ????????  : UART ??????????????

  1.??    ??   : 2013??09??18??
    ??    ??   : j00174725
    ????????   : ????
*****************************************************************************/
enum AT_UART_STOP_LEN_ENUM
{
    AT_UART_STOP_LEN_1_BIT              = 1,
    AT_UART_STOP_LEN_2_BIT              = 2,

    AT_UART_STOP_LEN_BUTT
};
typedef VOS_UINT8 AT_UART_STOP_LEN_ENUM_UINT8;

/*****************************************************************************
 ??????    : AT_UART_PARITY_LEN_ENUM
 ????????  : UART  ??????????????

  1.??    ??   : 2013??09??18??
    ??    ??   : j00174725
    ????????   : ????
*****************************************************************************/
enum AT_UART_PARITY_LEN_ENUM
{
    AT_UART_PARITY_LEN_0_BIT            = 0,
    AT_UART_PARITY_LEN_1_BIT            = 1,

    AT_UART_PARITY_LEN_BUTT
};
typedef VOS_UINT8 AT_UART_PARITY_LEN_ENUM_UINT8;

/*****************************************************************************
 ??????    : AT_UART_DCD_MODE_ENUM
 ????????  : DCD????????

  1.??    ??   : 2013??09??18??
    ??    ??   : j00174725
    ????????   : ????
*****************************************************************************/
enum AT_UART_DCD_MODE_ENUM
{
    AT_UART_DCD_MODE_ALWAYS_ON          = 0x00,
    AT_UART_DCD_MODE_CONNECT_ON         = 0x01,

    AT_UART_DCD_MODE_BUTT
};
typedef VOS_UINT8 AT_UART_DCD_MODE_ENUM_UINT8;

/*****************************************************************************
 ??????    : AT_UART_DTR_MODE_ENUM
 ????????  : DTR????????

  1.??    ??   : 2013??09??18??
    ??    ??   : j00174725
    ????????   : ????
*****************************************************************************/
enum AT_UART_DTR_MODE_ENUM
{
    AT_UART_DTR_MODE_IGNORE             = 0x00,
    AT_UART_DTR_MODE_SWITCH_CMD_MODE    = 0x01,
    AT_UART_DTR_MODE_HANGUP_CALL        = 0x02,

    AT_UART_DTR_MODE_BUTT
};
typedef VOS_UINT8 AT_UART_DTR_MODE_ENUM_UINT8;

/*****************************************************************************
 ??????    : AT_UART_DSR_MODE_ENUM
 ????????  : DSR????????

  1.??    ??   : 2013??09??18??
    ??    ??   : j00174725
    ????????   : ????
*****************************************************************************/
enum AT_UART_DSR_MODE_ENUM
{
    AT_UART_DSR_MODE_ALWAYS_ON          = 0x00,
    AT_UART_DSR_MODE_CONNECT_ON         = 0x01,

    AT_UART_DSR_MODE_BUTT
};
typedef VOS_UINT8 AT_UART_DSR_MODE_ENUM_UINT8;

/*****************************************************************************
 ??????    : AT_UART_FC_DCE_ENUM
 ????????  : ????????????

  1.??    ??   : 2013??09??18??
    ??    ??   : j00174725
    ????????   : ????
*****************************************************************************/
enum AT_UART_FC_DCE_BY_DTE_ENUM
{
    AT_UART_FC_DCE_BY_DTE_NONE                  = 0x00,
    AT_UART_FC_DCE_BY_DTE_XON_OR_XOFF_REMOVE    = 0x01,
    AT_UART_FC_DCE_BY_DTE_RTS                   = 0x02,
    AT_UART_FC_DCE_BY_DTE_XON_OR_XOFF_PASS      = 0x03,

    AT_UART_FC_DCE_BY_DTE_BUTT
};
typedef VOS_UINT8 AT_UART_FC_DCE_BY_DTE_ENUM_UINT8;

/*****************************************************************************
 ??????    : AT_UART_FC_DTE_BY_DCE_ENUM
 ????????  : ????????????

  1.??    ??   : 2013??09??18??
    ??    ??   : j00174725
    ????????   : ????
*****************************************************************************/
enum AT_UART_FC_DTE_BY_DCE_ENUM
{
    AT_UART_FC_DTE_BY_DCE_NONE                  = 0x00,
    AT_UART_FC_DTE_BY_DCE_XON_OR_XOFF_REMOVE    = 0x01,
    AT_UART_FC_DTE_BY_DCE_CTS                   = 0x02,

    AT_UART_FC_DTE_BY_DCE_BUTT
};
typedef VOS_UINT8 AT_UART_FC_DTE_BY_DCE_ENUM_UINT8;

/*****************************************************************************
 ??????    : AT_UART_RI_TYPE_ENUM
 ????????  : RI????

  1.??    ??   : 2013??09??18??
    ??    ??   : A00165503
    ????????   : ????
*****************************************************************************/
enum AT_UART_RI_TYPE_ENUM
{
    AT_UART_RI_TYPE_VOICE               = 0x00,
    AT_UART_RI_TYPE_SMS                 = 0x01,

    AT_UART_RI_TYPE_BUTT
};
typedef VOS_UINT32 AT_UART_RI_TYPE_ENUM_UINT32;

/*****************************************************************************
 ??????    : AT_UART_RI_STATUS_ENUM
 ????????  : RI????

  1.??    ??   : 2013??09??18??
    ??    ??   : A00165503
    ????????   : ????
*****************************************************************************/
enum AT_UART_RI_STATUS_ENUM
{
    AT_UART_RI_STATUS_STOP                = 0x00,
    AT_UART_RI_STATUS_RINGING             = 0x01,

    AT_UART_RI_STATUS_BUTT
};
typedef VOS_UINT8 AT_UART_RI_STATUS_ENUM_UINT8;

/*****************************************************************************
 ??????    : AT_PORT_BUFF_CFG_ENUM
 ????????  : ????

  1.??    ??   : 2013??12??28??
    ??    ??   : j00174725
    ????????   : ????
*****************************************************************************/
enum AT_PORT_BUFF_CFG_ENUM
{
    AT_PORT_BUFF_DISABLE                     = 0,
    AT_PORT_BUFF_ENABLE,

    AT_PORT_BUFF_BUTT
};

typedef VOS_UINT8 AT_PORT_BUFF_CFG_ENUM_UINT8;

typedef VOS_VOID (*AT_UART_WM_LOW_FUNC)(VOS_UINT8 ucIndex);



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

/*****************************************************************************
 ??????    : AT_MODEM_PID_TAB_STRU
 ????????  : DSDA ????modem????AT??????????PID??????

  1.??    ??   : 2012??12??17??
    ??    ??   : L60609
    ????????   : ??????

  2.??    ??   : 2015??6??16??
    ??    ??   : l00198894
    ????????   : TSTS
*****************************************************************************/
typedef struct
{
    VOS_UINT32                           ulModem0Pid;
    VOS_UINT32                           ulModem1Pid;
    VOS_UINT32                           ulModem2Pid;
    VOS_UINT32                           ulReserved;
}AT_MODEM_PID_TAB_STRU;

/*********************************Modem CTX Begin*****************************/
/*****************************************************************************
 ??????    : AT_USIM_INFO_CTX_STRU
 ????????  : AT??????USIM??????????????

  1.??    ??   : 2011??10??22??
    ??    ??   : o00132663
    ????????   : ????
  2.??    ??   : 2013??4??3??
    ??    ??   : s00217060
    ????????   : ????????AT??????????????C??
*****************************************************************************/
typedef struct
{
    USIMM_CARD_TYPE_ENUM_UINT32         enCardType;                             /* ??????:SIM??USIM??ROM-SIM  */
    USIMM_CARD_SERVIC_ENUM_UINT32       enCardStatus;                           /* ??????*/
    VOS_UINT8                           aucIMSI[9];                             /* IMSI??*/
    VOS_UINT8                           ucIMSILen;                              /* IMSI???? */
    /* Deleted by s00217060 for ????????AT??????????????C??, 2013-4-3, begin */
    /* Deleted by s00217060 for ????????AT??????????????C??, 2013-4-3, end */
    VOS_UINT8                           ucReserve[6];
}AT_USIM_INFO_CTX_STRU;

/*****************************************************************************
 ??????    : AT_MODEM_SPT_RAT_STRU
 ????????  : modem????????????

  1.??    ??   : 2012??12??27??
    ??    ??   : z00220246
    ????????   : DSDA Phase II:????????????????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPlatformSptLte;
    VOS_UINT8                           ucPlatformSptWcdma;
    VOS_UINT8                           ucPlatformSptGsm;
    VOS_UINT8                           ucPlatformSptUtralTDD;
    VOS_UINT8                           aucReserved[4];
}AT_MODEM_SPT_RAT_STRU;

/*****************************************************************************
 ??????    : AT_MODEM_SPT_CAP_STRU
 ????????  : modem ????????

  1.??    ??   : 2015??10??27??
    ??    ??   : f00279542
    ????????   : new
*****************************************************************************/
typedef struct
{
    AT_MODEM_SPT_RAT_STRU               stPlatformRatList;
    VOS_UINT8                           ucIsCLMode;
    VOS_UINT8                           aucReserved[7];
}AT_MODEM_SPT_CAP_STRU;

/*********************************CTRL CTX Begin*****************************/
typedef struct
{
    VOS_UINT8                           ucStatus;                               /* NV????????????, 0: ????????1: ???? */
    VOS_UINT8                           ucAtStatusReportGeneralControl;         /* ????????????????????????*/
}NVIM_AT_PRIVATE_CMD_STATUS_RPT_STRU;

/*****************************************************************************
??????    : AT_CLCK_CLASS_SERVICE_TBL_STRU
????????  : +CLCK????CLASS??SERVICE??????????
1.??    ??  : 2012??12??31??
  ??    ??  : l00198894
  ????????  : ??????????
*****************************************************************************/
typedef struct
{
    AT_CLCK_PARA_CLASS_ENUM_UINT8       enClass;
    TAF_BASIC_SERVICE_TYPE              enServiceType;
    TAF_BASIC_SERVICE_CODE              enServiceCode;
} AT_CLCK_CLASS_SERVICE_TBL_STRU;

/*********************************CTRL CTX Begin*****************************/

/*********************************CC/SS CTX Begin*****************************/
/* Deleted by s00217060 for ????????AT??????????????C??, 2013-4-3, begin */
/* Deleted by s00217060 for ????????AT??????????????C??, 2013-4-3, end */

typedef MN_CALL_CS_DATA_CFG_STRU AT_CBST_DATA_CFG_STRU;

/* Modified by l60609 for DSDA Phase III, 2013-2-21, Begin */
typedef struct
{
    HTIMER                              s0Timer;
    VOS_BOOL                            bTimerStart;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucS0TimerLen;
    VOS_UINT8                           ucReserved;                             /* ???? */
    VOS_UINT32                          ulTimerName;
    VOS_UINT8                           aucReserved[4];
}AT_S0_TIMER_INFO_STRU;
/* Modified by l60609 for DSDA Phase III, 2013-2-21, End */

typedef MN_CALL_CUG_CFG_STRU     AT_CCUG_CFG_STRU;

/*********************************CC/SS CTX End*****************************/

/*********************************SMS CTX Begin*****************************/
typedef struct
{
    AT_CNMI_MODE_TYPE                   CnmiModeType;
    AT_CNMI_MT_TYPE                     CnmiMtType;
    AT_CNMI_BM_TYPE                     CnmiBmType;
    AT_CNMI_DS_TYPE                     CnmiDsType;
    AT_CNMI_BFR_TYPE                    CnmiBfrType;
    AT_CNMI_MODE_TYPE                   CnmiTmpModeType;
    AT_CNMI_MT_TYPE                     CnmiTmpMtType;
    AT_CNMI_BM_TYPE                     CnmiTmpBmType;
    AT_CNMI_DS_TYPE                     CnmiTmpDsType;
    AT_CNMI_BFR_TYPE                    CnmiTmpBfrType;
    VOS_UINT8                           aucReserved[6];
}AT_CNMI_TYPE_STRU;

typedef struct
{
    MN_MSG_EVENT_INFO_STRU              astEvent[AT_BUFFER_CBM_EVENT_MAX];
    VOS_UINT8                           aucUsed[AT_BUFFER_CBM_EVENT_MAX];
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           aucReserved[2];
}AT_CBM_BUFFER_STRU;

typedef struct
{
    VOS_UINT8                           ucActFlg;
    AT_CGSMS_SEND_DOMAIN_ENUM_U8        enSendDomain;
    TAF_UINT8                           aucReserved[6];
}AT_CGSMS_SEND_DOMAIN_STRU;

typedef struct
{
    VOS_BOOL                            bUsed;
    VOS_UINT8                           ucFo;
    VOS_UINT8                           ucTmpFo;
    VOS_UINT8                           aucReserve1[2];
}AT_MSG_FO_STRU;

typedef struct
{
    VOS_BOOL                            bFoUsed;
    VOS_UINT8                           ucFo;
    VOS_UINT8                           ucTmpFo;
    VOS_UINT8                           aucReserve1[2];
    MN_MSG_VALID_PERIOD_STRU            stVp;
    MN_MSG_VALID_PERIOD_STRU            stTmpVp;
    AT_MSG_FO_STRU                      stFo;
    MN_MSG_SRV_PARAM_STRU               stParmInUsim;
}AT_CSCA_CSMP_INFO_STRU;

typedef struct
{
    MN_MSG_MEM_STORE_ENUM_U8            enMemReadorDelete;
    MN_MSG_MEM_STORE_ENUM_U8            enMemSendorWrite;
    MN_MSG_MEM_STORE_ENUM_U8            enTmpMemReadorDelete;
    MN_MSG_MEM_STORE_ENUM_U8            enTmpMemSendorWrite;
    VOS_UINT8                           aucReserved[4];
    MN_MSG_SET_RCVMSG_PATH_PARM_STRU    stRcvPath;
    MN_MSG_STORAGE_LIST_EVT_INFO_STRU   stUsimStorage;
    MN_MSG_STORAGE_LIST_EVT_INFO_STRU   stNvimStorage;
}AT_MSG_CPMS_STRU;

typedef struct
{
    TAF_BOOL                            bUsed;
    VOS_UINT8                           aucReserved[4];
    MN_MSG_EVENT_INFO_STRU             *pstEvent;
    MN_MSG_TS_DATA_INFO_STRU           *pstTsDataInfo;
}AT_SMS_MT_BUFFER_STRU;

typedef struct
{
    MN_MSG_EVENT_INFO_STRU              astEvent[AT_BUFFER_SMT_EVENT_MAX];
    VOS_UINT8                           aucUsed[AT_BUFFER_SMT_EVENT_MAX];
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           aucReserved[2];
}AT_SMT_BUFFER_STRU;

/*****************************************************************************
 ????????  : NAS_NV_SMS_FILTER_CFG_STRU
 ????????  : ????????????????

  1.??    ??   : 2015??09??17??
    ??    ??   : h00313353
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSmsFilterEnableFlg;                   /* ???????????????????????? */
    VOS_UINT8                           aucReserved[7];
} AT_SMS_FILTER_CFG_STRU;

/*********************************SMS CTX End*****************************/

/*********************************NET CTX Begin*****************************/
typedef struct
{
    AT_COPS_FORMAT_TYPE                 FormatType;
}AT_COPS_TYPE_STRU;

/*********************************NET CTX End*****************************/


/*********************************AGPS CTX Begin*****************************/
/*****************************************************************************
 ??????    : AT_XML_STRU
 ????????  : AT????XML????????
*****************************************************************************/
typedef struct
{
    VOS_CHAR                           *pcXmlTextHead;                          /* XML?????????? */
    VOS_CHAR                           *pcXmlTextCur;                           /* ????????XML???????? */
}AT_XML_STRU;

/*********************************AGPS CTX End*****************************/

/* Deleted by s00217060 for ????????AT??????????????C??, 2013-4-1, begin */
/* Deleted by s00217060 for ????????AT??????????????C??, 2013-4-1, begin */

/* Deleted by l00198894 for V9R1 STK????, 2013/07/11 */

/*****************************************************************************
 ??????    : AT_ECONF_INFO_STRU
 ????????  : ??????????????????????

  1.??    ??   : 2014??11??28??
    ??    ??   : f00179208
    ????????   : enhanced conference
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNumOfCalls;                           /* ?????????????????? */
    VOS_UINT8                           aucReserved[7];
    TAF_CALL_ECONF_INFO_PARAM_STRU      astCallInfo[TAF_CALL_MAX_ECONF_CALLED_NUM];  /* ???????????????? */
}AT_ECONF_INFO_STRU;

/*****************************************************************************
 ??????    : AT_MODEM_CC_CTX_STRU
 ????????  : CC????????????

  1.??    ??   : 2013??1??22??
    ??    ??   : l60609
    ????????   : DSDA Phase III
  2.??    ??   : 2013??6??26??
    ??    ??   : f62575
    ????????   : V9R1 STK??????????stDtmfCtrlInfo
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCurIsExistCallFlag;                   /* ???????????????????? */
    TAF_CS_CAUSE_ENUM_UINT32            enCsErrCause;                           /* ????????CS???????? */

    AT_S0_TIMER_INFO_STRU               stS0TimeInfo;                           /* ??????????????0??????????????????1~255???????????????????? */

    AT_ECONF_INFO_STRU                  stEconfInfo;

}AT_MODEM_CC_CTX_STRU;

/*****************************************************************************
 ??????    : AT_MODEM_SS_CTX_STRU
 ????????  : SS????????????

  1.??    ??   : 2013??1??22??
    ??    ??   : l60609
    ????????   : DSDA Phase III
  2.??    ??   : 2013??4??16??
    ??    ??   : s00217060
    ????????   : ????????AT??????????????C??????????
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usUssdTransMode;                        /* USSD???????? */
    /* Deleted by s00217060 for ????????AT??????????????C??, 2013-4-8, begin */
    /* Deleted by s00217060 for ????????AT??????????????C??, 2013-4-8, end */
    AT_CMOD_MODE_ENUM                   enCModType;                             /* ???????????? */
    AT_SALS_TYPE                        ucSalsType;                             /* ????/???????????? */
    AT_CLIP_TYPE                        ucClipType;                             /* ????/???????????????? */
    AT_CLIR_TYPE                        ucClirType;                             /* ????/???????????????? */
    AT_COLP_TYPE                        ucColpType;                             /* ????/???????????????? */
    AT_CRC_TYPE                         ucCrcType;                              /* ????/???????????????????????? */
    AT_CCWA_TYPE                        ucCcwaType;                             /* ????/???????????? */
    VOS_UINT8                           ucReserved[7];

    /* Deleted by s00217060 for ????????AT??????????????C??, 2013-4-3, end */
    /* Deleted by s00217060 for ????????AT??????????????C??, 2013-4-3, end */
    AT_CBST_DATA_CFG_STRU               stCbstDataCfg;                          /* ????(CBST)????*/
    AT_CCUG_CFG_STRU                    stCcugCfg;                              /* ??????????(CUG)???? */
}AT_MODEM_SS_CTX_STRU;

/*****************************************************************************
 ??????    : AT_MODEM_SMS_CTX_STRU
 ????????  : SMS????????????

  1.??    ??   : 2013??1??22??
    ??    ??   : l60609
    ????????   : DSDA Phase III
*****************************************************************************/
typedef struct
{
    AT_CMGF_MSG_FORMAT_ENUM_U8          enCmgfMsgFormat;                        /* ???????? TXT or PDU */
    AT_CSDH_TYPE                        ucCsdhType;                             /* ?????????????????????? */
    VOS_UINT8                           ucParaCmsr;                             /* ???????????? */
    VOS_UINT8                           ucSmsAutoReply;                         /* ???????????? */
    MN_MSG_CSMS_MSG_VERSION_ENUM_U8     enCsmsMsgVersion;                       /* ???????????? */
    MN_MSG_ME_STORAGE_STATUS_ENUM_UINT8 enMsgMeStorageStatus;                   /* ME???????????? */
    /* modified by l65478 for 2013-05-23 begin */
    VOS_UINT8                           ucLocalStoreFlg;
    /* modified by l65478 for 2013-05-23 begin */

    VOS_UINT8                           ucReserve2;

    AT_CNMI_TYPE_STRU                   stCnmiType;                             /* CNMI???? */
    AT_CGSMS_SEND_DOMAIN_STRU           stCgsmsSendDomain;                      /* ?????? */
    AT_CSCA_CSMP_INFO_STRU              stCscaCsmpInfo;                         /* ???????????? */
    AT_MSG_CPMS_STRU                    stCpmsInfo;                             /* ?????????? */
    AT_SMS_MT_BUFFER_STRU               astSmsMtBuffer[AT_SMSMT_BUFFER_MAX];    /* ?????????????? */
    AT_SMT_BUFFER_STRU                  stSmtBuffer;                            /* ????????????????????????????PDU???? */
    AT_SMS_FILTER_CFG_STRU              stSmsFilterCfg;                         /* AT????????Trace???????? */

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
    AT_CBM_BUFFER_STRU                  stCbmBuffer;
    TAF_CBA_CBMI_RANGE_LIST_STRU        stCbsDcssInfo;                          /* ??????????????????????AT?? */
#endif

}AT_MODEM_SMS_CTX_STRU;

/*****************************************************************************
 ??????    : AT_MODEM_NET_CTX_STRU
 ????????  : NET????????????

  1.??    ??   : 2013??1??22??
    ??    ??   : l60609
    ????????   : DSDA Phase III
  2.??    ??   : 2013??4??1??
    ??    ??   : s00217060
    ????????   : ????????AT??????????????C??
*****************************************************************************/
typedef struct
{
    /* ???????????? */
    /* Deleted by s00217060 for ????????AT??????????????C??, 2013-4-1, end */
    /* Deleted by s00217060 for ????????AT??????????????C??, 2013-4-1, end */
    AT_CERSSI_REPORT_TYPE_ENUM_UINT8    ucCerssiReportType;                     /* VOS_TRUE: ^CERSSI??????VOS_FALSE: ?????? */
    AT_CREG_TYPE                        ucCregType;                             /* VOS_TRUE: CS????????????????VOS_FALSE: ?????? */
    AT_CGREG_TYPE                       ucCgregType;                            /* VOS_TRUE: PS????????????????VOS_FALSE: ?????? */
    AT_COPS_FORMAT_TYPE                 ucCopsFormatType;                       /* COPS????PLMN?????? */

    MN_PH_PREF_PLMN_TYPE_ENUM_U8        enPrefPlmnType;                         /* CPOL????PLMN?????? */
    AT_COPS_FORMAT_TYPE                 ucCpolFormatType;                       /* CPOL????PLMN?????? */
    VOS_UINT8                           ucRoamFeature;                          /* ???????????????? */
    VOS_UINT8                           ucSpnType;                              /* ????AT^SPN??????SPN???? */

    AT_CMD_ANTENNA_LEVEL_ENUM_UINT8     enCalculateAntennaLevel;                /* ???????????????????? */
    AT_CMD_ANTENNA_LEVEL_ENUM_UINT8     aenAntennaLevel[AT_ANTENNA_LEVEL_MAX_NUM]; /* ????3?????????? */
    VOS_UINT8                           ucCerssiMinTimerInterval;               /* ?????????????????????? */
    VOS_UINT8                           ucReserve1[3];

    NAS_MM_INFO_IND_STRU                stTimeInfo;                             /* ???????? */

#if(FEATURE_ON == FEATURE_LTE)
    AT_CEREG_TYPE_ENUM_UINT8            ucCeregType;                            /* VOS_TRUE: EPS????????????????VOS_FALSE: ?????? */
    VOS_UINT8                           ucReserve2[7];
#endif

}AT_MODEM_NET_CTX_STRU;

/*****************************************************************************
 ??????    : AT_MODEM_AGPS_CTX_STRU
 ????????  : AGPS????????

  1.??    ??   : 2013??1??22??
    ??    ??   : l60609
    ????????   : DSDA Phase III
*****************************************************************************/
typedef struct
{
    AT_CPOSR_FLG_ENUM_UNIT8             enCposrReport;                          /* +CPOSR?????????????????????????????????????????????? */
    AT_XCPOSR_FLG_ENUM_UNIT8            enXcposrReport;                         /* +XCPOSR?????????????????????????????????????????????? */
    AT_CMOLRE_TYPE_ENUM_UNIT8           enCmolreType;                           /* +CMOLRE?????????????????????????????????? */
    VOS_UINT8                           aucReserve[5];

    AT_XML_STRU                         stXml;                                  /* XML??????????????AGPS?????????????? */
}AT_MODEM_AGPS_CTX_STRU;
/*********************************Modem CTX End*****************************/

/*********************************Client CTX Begin*****************************/
/*****************************************************************************
 ??????    : AT_CLIENT_BASIC_INFO_STRU
 ????????  : AT??????????????????

  1.??    ??   : 2012??12??20??
    ??    ??   : L60609
    ????????   : ??????
*****************************************************************************/
typedef struct
{
    MODEM_ID_ENUM_UINT16                enModemId;                              /* ??????????????modem */
    VOS_UINT8                           ucReportFlg;                            /* ????????????????????????VOS_TRUE????????VOS_FALSE?????????????????? */
    VOS_UINT8                           aucRsv[1];
}AT_CLIENT_CONFIGURATION_STRU;
/*********************************Client CTX End*****************************/

/*********************************COMM CTX Begin*****************************/
/* Added by L60609 for MUX??2012-08-03,  Begin */
/*****************************************************************************
 ??????    : AT_MUX_CLIENT_TAB_STRU
 ????????  : AP-MODEM????8??MUX AT??????????????????????AT????????????????????
 1.??    ??   : 2012??08??03??
   ??    ??   : L60609
   ????????   : ????????
*****************************************************************************/
typedef struct
{
    RCV_UL_DLCI_DATA_FUNC               pReadDataCB;                            /* ??????MUX????????????????MUX??????????????AT???? */

    AT_HSIC_REPORT_TYPE_ENUM_UINT32     enRptType;                              /* MUX????????????HSIC??????????HSIC AT????????????AT??????????????
                                                                                   ^APRPTPORTSEL??????????????????????????AT_HSIC_REPORT_ON*/

    AT_CLIENT_ID_ENUM_UINT16            enAtClientId;                           /* MUX AT????????????AT CLIENT ID*/

    AT_CLIENT_TAB_INDEX_UINT8           enAtClientTabIdx;                       /* MUX????????gastAtClientTab??index???? */

    AT_USER_TYPE                        ucMuxUser;                              /* MUX AT????????????AT USER type */

    AT_PORT_NO                          ucMuxPort;                              /* MUX AT????????????AT PORT NO */

    AT_MUX_DLCI_TYPE_ENUM_UINT8         enDlci;                                 /* ????MUX AT??????????????ID*/

    VOS_UINT8                           aucRsv[6];
}AT_MUX_CLIENT_TAB_STRU;

typedef struct
{
    AT_MUX_CLIENT_TAB_STRU              astMuxClientTab[AT_MUX_AT_CHANNEL_MAX]; /* MUX 8???????? */
    VOS_UINT8                           ucMuxSupportFlg;                        /* ????????MUX???? */
    VOS_UINT8                           aucRsv[7];
}AT_MUX_CTX_STRU;
/* Added by L60609 for MUX??2012-08-03,  End */

/*********************************COMM CTX End*****************************/

/*****************************************************************************
 ??????    : AT_MODEM_MT_INFO_CTX_STRU
 ????????  : MT INFO????????

  1.??    ??   : 2013??5??30??
    ??    ??   : z60575
    ????????   : DSDA_SAR????????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve1[2];
    VOS_UINT16                          usSarReduction;
}AT_MODEM_MT_INFO_CTX_STRU;
/*********************************Modem CTX End*****************************/


/*****************************************************************************
 ??????    : AT_RESET_CTX_STRU
 ????????  : AT??????????????

  1.??    ??   : 2013??04??19??
    ??    ??   : f00179208
    ????????   : ??????
*****************************************************************************/
typedef struct
{
    VOS_SEM                             hResetSem;                              /* ??????????????????????????  */
    VOS_UINT32                          ulResetingFlag;                         /* ???????? */
    VOS_UINT32                          ulReserved;
}AT_RESET_CTX_STRU;

/*****************************************************************************
 ??????    : AT_UART_FORMAT_PARAM_STRU
 ????????  : UART??????

  1.??    ??   : 2013??09??21??
    ??    ??   : j00174725
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    AT_UART_FORMAT_ENUM_UINT8           enFormat;
    AT_UART_DATA_LEN_ENUM_UINT8         enDataBitLength;
    AT_UART_STOP_LEN_ENUM_UINT8         enStopBitLength;
    AT_UART_PARITY_LEN_ENUM_UINT8       enParityBitLength;

} AT_UART_FORMAT_PARAM_STRU;

/*****************************************************************************
 ??????    : UART_FRAME_STRU
 ????????  : UART ??????

  1.??    ??   : 2013??09??18??
    ??    ??   : j00174725
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    AT_UART_FORMAT_ENUM_UINT8           enFormat;
    AT_UART_PARITY_ENUM_UINT8           enParity;
    VOS_UINT8                           aucReserved[2];

} AT_UART_FRAME_STRU;

/*****************************************************************************
 ??????    : AT_UART_PHY_CFG_STRU
 ????????  : UART ????????

  1.??    ??   : 2013??09??18??
    ??    ??   : j00174725
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    AT_UART_BAUDRATE_ENUM_UINT32        enBaudRate;
    AT_UART_FRAME_STRU                  stFrame;

} AT_UART_PHY_CFG_STRU;

/*****************************************************************************
 ??????    : AT_UART_FLOW_CTRL_STRU
 ????????  : UART ????????

  1.??    ??   : 2013??09??18??
    ??    ??   : z00189113
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    AT_UART_FC_DCE_BY_DTE_ENUM_UINT8    enDceByDte;
    AT_UART_FC_DTE_BY_DCE_ENUM_UINT8    enDteByDce;
    VOS_UINT8                           aucReserved[2];

} AT_UART_FLOW_CTRL_STRU;

/*****************************************************************************
 ??????    : AT_UART_LINE_CTRL_MODE_STRU
 ????????  : UART ????????????

  1.??    ??   : 2013??09??18??
    ??    ??   : z00189113
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    AT_UART_DCD_MODE_ENUM_UINT8         enDcdMode;
    AT_UART_DTR_MODE_ENUM_UINT8         enDtrMode;
    AT_UART_DSR_MODE_ENUM_UINT8         enDsrMode;
    VOS_UINT8                           aucReserved[1];

} AT_UART_LINE_CTRL_STRU;

/*****************************************************************************
 ??????    : AT_UART_RI_CFG_STRU
 ????????  : RING Indicator ????????

  1.??    ??   : 2013??09??18??
    ??    ??   : A00165503
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSmsRiOnInterval;      /* ????RI????????????(ms) */
    VOS_UINT32                          ulSmsRiOffInterval;     /* ????RI????????????(ms) */

    VOS_UINT32                          ulVoiceRiOnInterval;    /* ????RI????????????(ms) */
    VOS_UINT32                          ulVoiceRiOffInterval;   /* ????RI????????????(ms) */
    VOS_UINT8                           ucVoiceRiCycleTimes;    /* ????RI????????????     */
    VOS_UINT8                           aucReserved[7];

} AT_UART_RI_CFG_STRU;

/*****************************************************************************
 ??????    : AT_UART_RI_STATE_INFO_STRU
 ????????  : RING Indicator ????????

  1.??    ??   : 2013??09??18??
    ??    ??   : A00165503
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRunFlg;           /* ???????????????????????? */
    AT_UART_RI_TYPE_ENUM_UINT32         enType;             /* RI ???? */

    HTIMER                              hVoiceRiTmrHdl;     /* ????RI?????????? */
    AT_TIMER_STATUS_ENUM_UINT32         enVoiceRiTmrStatus; /* ????RI?????????? */
    VOS_UINT32                          ulVoiceRiCycleCount;/* ???????????????? */
    AT_UART_RI_STATUS_ENUM_UINT8        aenVoiceRiStatus[MN_CALL_MAX_NUM + 1];
                                                            /* ????RI????(????CALLID) */

    HTIMER                              hSmsRiTmrHdl;       /* ????RI?????????? */
    AT_TIMER_STATUS_ENUM_UINT32         enSmsRiTmrStatus;   /* ????RI?????????? */
    VOS_UINT32                          ulSmsRiOutputCount; /* ????RI???????? */

} AT_UART_RI_STATE_INFO_STRU;

/*****************************************************************************
 ??????  : AT_UART_CTX_STRU
 ????????: UART??????????????

  1.??    ??   : 2013??09??18??
    ??    ??   : j00174725
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    AT_UART_PHY_CFG_STRU                stPhyConfig;            /* UART ???????? */
    AT_UART_LINE_CTRL_STRU              stLineCtrl;             /* UART ???????????? */
    AT_UART_FLOW_CTRL_STRU              stFlowCtrl;             /* UART ???????? */
    AT_UART_RI_CFG_STRU                 stRiConfig;             /* UART RI ???? */
    AT_UART_RI_STATE_INFO_STRU          stRiStateInfo;          /* UART RI ???? */
    AT_UART_WM_LOW_FUNC                 pWmLowFunc;             /* UART TX?????????????????? */
    VOS_UINT32                          ulTxWmHighFlg;          /* UART TX?????????? */
    VOS_UINT8                           aucReserved[4];

} AT_UART_CTX_STRU;

/*****************************************************************************
 ??????    : AT_PORT_BUFF_CFG_STRU
 ????????  : ????????????clientID
 1.??    ??   : 2013??11??13??
   ??    ??   : j00174725
   ????????   :
*****************************************************************************/
typedef struct
{
    AT_PORT_BUFF_CFG_ENUM_UINT8         enSmsBuffCfg;
    VOS_UINT8                           ucNum;                                  /* ?????????????? */
    VOS_UINT8                           aucRcv[2];
    VOS_UINT32                          ulUsedClientID[AT_MAX_CLIENT_NUM];      /* ??????????client ID???? */
}AT_PORT_BUFF_CFG_STRU;

/*****************************************************************************
 ????????  : AT_COMM_PB_CTX_STRU
 ????????  : ????????????????????

  1.??    ??   : 2015??3??12??
    ??    ??   : A00165503
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usCurrIdx;          /* ?????????????????? */
    VOS_UINT16                          usLastIdx;          /* ?????????????????? */
    VOS_UINT32                          ulSingleReadFlg;    /* ?????????????????? */
} AT_COMM_PB_CTX_STRU;

/*****************************************************************************
 ????????  : AT_VMSET_CMD_CTX_STRU
 ????????  : ^vmset??????????????

  1.??    ??   : 2016??6??18??
    ??    ??   : h00360002
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulReportedModemNum;
    VOS_UINT32                          ulResult;
} AT_VMSET_CMD_CTX_STRU;

/*****************************************************************************
 ????????  : AT_CMD_PROC_CTX_STRU
 ????????  : ????????????????

  1.??    ??   : 2016??6??18??
    ??    ??   : h00360002
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    AT_VMSET_CMD_CTX_STRU               stVmSetCmdCtx;
} AT_CMD_PROC_CTX_STRU;

/*****************************************************************************
 ??????    : AT_CMD_MSG_NUM_CTRL_STRU
 ????????  : AT????????????????????????????????????????????

  1.??    ??   : 2016??09??27??
    ??    ??   : m00217266
    ????????   : DTS2016092212700
*****************************************************************************/
typedef struct
{
    VOS_SPINLOCK                        stSpinLock;
    VOS_UINT32                          ulMsgCount;
}AT_CMD_MSG_NUM_CTRL_STRU;

/*****************************************************************************
 ??????    : AT_COMM_CTX_STRU
 ????????  : AT????????????????

  1.??    ??   : 2012??12??06??
    ??    ??   : L60609
    ????????   : ??????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSystemAppConfigAddr;                  /* ???????????? */
    VOS_UINT8                           aucReserve[7];

    AT_MUX_CTX_STRU                     stMuxCtx;                               /* MUX AT?????????? */
    AT_COMM_PS_CTX_STRU                 stPsCtx;                                /* PS?????????????????? */
    AT_UART_CTX_STRU                    stUartCtx;                              /* UART?????????? */
    AT_PORT_BUFF_CFG_STRU               stPortBuffCfg;

    AT_COMM_PB_CTX_STRU                 stCommPbCtx;                            /* ???????????????????? */
    
    AT_CMD_PROC_CTX_STRU                stCmdProcCtx;

    AT_CMD_MSG_NUM_CTRL_STRU            stMsgNumCtrlCtx;
}AT_COMM_CTX_STRU;

/*****************************************************************************
 ??????    : AT_MODEM_CTX_STRU
 ????????  : AT??Modem????????????????

  1.??    ??   : 2012??12??06??
    ??    ??   : L60609
    ????????   : ??????
  2.??    ??   : 2012??12??25??
    ??    ??   : z00220246
    ????????   : DSDA Phase II:????????????????
  3.??    ??   : 2013??3??5??
    ??    ??   : l60609
    ????????   : DSDA PHASE III
  4.??    ??   : 2013??4??1??
    ??    ??   : s00217060
    ????????   : ????????AT??????????????C??
  5.??    ??   : 2013??5??30??
    ??    ??   : z60575
    ????????   : DSDA_SAR????????
*****************************************************************************/
typedef struct
{
    AT_USIM_INFO_CTX_STRU               stAtUsimInfoCtx;                      /* ?????? */
    AT_MODEM_SPT_CAP_STRU               stPlatformCapList;                      /* AT Modem???????? */
    AT_MODEM_CC_CTX_STRU                stCcCtx;                                /* ???????????????? */
    AT_MODEM_SS_CTX_STRU                stSsCtx;                                /* ???????????????????? */
    AT_MODEM_SMS_CTX_STRU               stSmsCtx;                               /* ???????????????? */
    AT_MODEM_NET_CTX_STRU               stNetCtx;                               /* ???????????????? */
    AT_MODEM_AGPS_CTX_STRU              stAgpsCtx;                              /* AGPS????????????*/
    AT_MODEM_PS_CTX_STRU                stPsCtx;                                /* PS???????????? */
    AT_MODEM_MT_INFO_CTX_STRU           stMtInfoCtx;                            /* ???????????????? */
}AT_MODEM_CTX_STRU;

/*****************************************************************************
 ??????    : AT_ClIENT_CTX_STRU
 ????????  : AT??????????????????????

  1.??    ??   : 2012??12??06??
    ??    ??   : L60609
    ????????   : ??????
*****************************************************************************/
typedef struct
{
    AT_CLIENT_CONFIGURATION_STRU        stClientConfiguration;                  /* ?????????????????? */
}AT_CLIENT_CTX_STRU;

/*********************************??????????????*************************************/
/*********************************Other Begin*****************************/

enum  AT_E5_RIGHT_FLAG_ENUM
{
    AT_E5_RIGHT_FLAG_NO,
    AT_E5_RIGHT_FLAG_YES,
    AT_E5_RIGHT_FLAG_BUTT
} ;
typedef  VOS_UINT32  AT_E5_RIGHT_FLAG_ENUM_U32;

enum AT_RIGHT_OPEN_FLAG_ENUM
{
    AT_RIGHT_OPEN_FLAG_CLOSE,
    AT_RIGHT_OPEN_FLAG_OPEN,
    AT_RIGHT_OPEN_FLAG_BUTT
};
typedef VOS_UINT32 AT_RIGHT_OPEN_FLAG_ENUM_U32;

#define AT_RIGHT_PWD_LEN                (16)

typedef struct
{
    AT_RIGHT_OPEN_FLAG_ENUM_U32         enRightOpenFlg;
    VOS_INT8                            acPassword[AT_RIGHT_PWD_LEN];
}AT_RIGHT_OPEN_FLAG_STRU;

/*****************************************************************************
 ??????    : AT_ABORT_CMD_PARA_STRU
 ????????  : ????????AT????????????????????????????????, ????????????
             ??????????????"AT"????????????????, ????"ABORT"????????????. ????????????

  1.??    ??   : 2012??09??21??
    ??    ??   : L00171473
    ????????   : for V7R1C50_At_Abort,  ????

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucAbortEnableFlg;                               /* AT????????????. VOS_TRUE: ????; VOS_FALE: ?????? */
    VOS_UINT8                           aucAbortAtCmdStr[AT_MAX_ABORT_CMD_STR_LEN+1];   /* ??NV???????????????????????????????????????? */
    VOS_UINT8                           aucAbortAtRspStr[AT_MAX_ABORT_RSP_STR_LEN+1];
    VOS_UINT8                           ucAnyAbortFlg;
}AT_ABORT_CMD_PARA_STRU;



typedef struct
{
    VOS_UINT32                          ulAtSetTick[AT_MAX_CLIENT_NUM];
}AT_CMD_ABORT_TICK_INFO;

typedef struct
{
    AT_ABORT_CMD_PARA_STRU              stAtAbortCmdPara;
    AT_CMD_ABORT_TICK_INFO              stCmdAbortTick;
}AT_ABORT_CMD_CTX_STRU;



/* ?????????????? */
enum
{
    PPP_DIAL_ERR_CODE_DISABLE         = 0, /* ??????????????*/
    PPP_DIAL_ERR_CODE_ENABLE          = 1, /* ??????????*/
    PPP_DIAL_ERR_CODE_BUTT
};
typedef VOS_UINT8   PPP_DIAL_ERR_CODE_ENUM;

typedef struct
{

    VOS_UINT8   ucGsmConnectRate;
    VOS_UINT8   ucGprsConnectRate;
    VOS_UINT8   ucEdgeConnectRate;
    VOS_UINT8   ucWcdmaConnectRate;
    VOS_UINT8   ucDpaConnectRate;
    VOS_UINT8   ucReserve1;
    VOS_UINT8   ucReserve2;
    VOS_UINT8   ucReserve3;
}AT_DIAL_CONNECT_DISPLAY_RATE_STRU;

/*****************************************************************************
 ??????    : AT_DOWNLINK_RATE_CATEGORY_STRU
 ????????  : ??
 ????????  : UE????????
*****************************************************************************/
typedef struct
{
    VOS_INT8                            cWasRelIndicator;                       /* Access Stratum Release Indicator */
    VOS_UINT8                           ucWasCategory;
    VOS_UINT8                           ucGasMultislotClass33Flg;
    VOS_UINT8                           ucLteUeCategory;

} AT_DOWNLINK_RATE_CATEGORY_STRU;

/*****************************************************************************
 ??????    : AT_TRACE_MSGID_TAB_STRU
 ????????  : AT????ID
 1.??    ??   : 2013??11??13??
   ??    ??   : j00174725
   ????????   :
*****************************************************************************/
typedef struct
{
    AT_INTER_MSG_ID_ENUM_UINT32         enCmdMsgID;
    AT_INTER_MSG_ID_ENUM_UINT32         enResultMsgID;
} AT_TRACE_MSGID_TAB_STRU;

#if (FEATURE_ON == FEATURE_LTE)
typedef struct
{
    TAF_INT16 ssLevel[4];
    TAF_INT16 ssValue[4];
}NVIM_RSRP_CFG_STRU;

typedef struct
{
    TAF_INT16 ssLevel[4];
    TAF_INT16 ssValue[4];
}NVIM_ECIO_CFG_STRU;

typedef struct
{
    TAF_INT16 ssLevel[4];
    TAF_INT16 ssValue[4];
}NVIM_RSCP_CFG_STRU;
#endif

/*****************************************************************************
 ??????    : AT_SS_CUSTOMIZE_TYPE
 ????????  : SS????????????
                AT_SS_CUSTOMIZE_CCWA_QUERY +CCWA??????????
                AT_SS_CUSTOMIZE_CLCK_QUERY +CLCK????????

  1.??    ??   : 2013??01??24??
    ??    ??   : f62575
    ????????   : ????
*****************************************************************************/
typedef enum
{
    AT_SS_CUSTOMIZE_CCWA_QUERY,
    AT_SS_CUSTOMIZE_CLCK_QUERY,
    AT_SS_CUSTOMIZE_BUTT,
}AT_SS_CUSTOMIZE_TYPE;
typedef VOS_UINT8 AT_SS_CUSTOMIZE_TYPE_UINT8;

#define AT_SS_CUSTOMIZE_SERVICE_MASK          (0x1)

/*********************************Other End*****************************/

/*lint -e958 -e959 ??????:f00179208;????:64bit*/
/*****************************************************************************
 ??????    : AT_CLINET_CONFIG_DESC_STRU
 ????????  : NV????????????

  1.??    ??   : 2014??04??26??
    ??    ??   : ????/f00179208
    ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucModemId   : 2;
    VOS_UINT8                           ucReportFlg : 1;
    VOS_UINT8                           ucReserved  : 5;
}AT_CLINET_CONFIG_DESC_STRU;
/*lint +e958 +e959 ??????:f00179208;????:64bit*/

/*****************************************************************************
 ??????    : AT_PORT_RPT_CFG_UNION
 ????????  : NV????????????

  1.??    ??   : 2014??04??26??
    ??    ??   : ????/f00179208
    ????????   : ????
*****************************************************************************/
typedef union
{
    VOS_UINT64                          ulRptCfgBit64;
    VOS_UINT32                          aulRptCfgBit32[2];
} AT_PORT_RPT_CFG_UNION;

/*****************************************************************************
 ??????    : AT_CLIENT_CFG_MAP_TAB_STRU
 ????????  : AT CLIENT ????TAB

  1.??    ??   : 2014??04??26??
    ??    ??   : ????/f00179208
    ????????   : ????
*****************************************************************************/
typedef struct
{
    AT_CLIENT_ID_ENUM_UINT16            enClientId;
    TAF_NV_CLIENT_CFG_ENUM_UINT16       enNvIndex;
    VOS_UINT8                           aucPortName[AT_PORT_LEN_MAX];
    VOS_UINT64                          ulRptCfgBit64;
}AT_CLIENT_CFG_MAP_TAB_STRU;


#if ( VOS_WIN32 == VOS_OS_VER )
/*****************************************************************************
 ??????    : AT_USIMM_FILE_NUM_TO_ID_STRU
 ????????  : USIM????????????ID????

  1.??    ??   : 2015??03??07??
    ??    ??   : y00245242
    ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulFileNum;
    USIMM_DEF_FILEID_ENUM_UINT32        enFileId;
}AT_USIMM_FILE_NUM_TO_ID_STRU;
#endif

/*****************************************************************************
  8 UNION????
*****************************************************************************/


/*****************************************************************************
  9 OTHERS????
*****************************************************************************/
extern AT_COMM_CTX_STRU                        g_stAtCommCtx;

extern AT_MODEM_CTX_STRU                       g_astAtModemCtx[];

extern AT_CLIENT_CTX_STRU                      g_astAtClientCtx[];

/*********************************??????????????*************************************/
extern AT_E5_RIGHT_FLAG_ENUM_U32               g_enATE5RightFlag;

extern VOS_INT8                                g_acATOpwordPwd[];

extern AT_RIGHT_OPEN_FLAG_STRU                 g_stAtRightOpenFlg;

extern VOS_INT8                                g_acATE5DissdPwd[];

extern VOS_UINT8                               gaucAtCmdNotSupportStr[];

extern PPP_DIAL_ERR_CODE_ENUM                  gucPppDialErrCodeRpt;

extern AT_DIAL_CONNECT_DISPLAY_RATE_STRU       g_stDialConnectDisplayRate;

extern AT_DOWNLINK_RATE_CATEGORY_STRU          g_stAtDlRateCategory;

extern VOS_UINT8                               ucAtS3;
extern VOS_UINT8                               ucAtS4;
extern VOS_UINT8                               ucAtS5;
extern VOS_UINT8                               ucAtS6;
extern VOS_UINT8                               ucAtS7;

extern AT_CMEE_TYPE                            gucAtCmeeType;                   /* ?????????????????????? */

extern TAF_UINT32                              g_ulSTKFunctionFlag;

/* Deleted by s00217060 for ????????AT??????????????C??, 2013-4-10, begin */
/* Deleted by s00217060 for ????????AT??????????????C??, 2013-4-10, end */


/*********************************SMS Begin*************************************/
extern MN_MSG_CLASS0_TAILOR_U8                 g_enClass0Tailor;
/*********************************SMS End*************************************/

/*********************************NET Begin*************************************/
extern VOS_UINT16                              g_usReportCregActParaFlg;

/*CREG/CGREG??<CI>????4????????????????(VDF????)*/
extern CREG_CGREG_CI_RPT_BYTE_ENUM             gucCiRptByte;

/*********************************NET End*************************************/
#if (FEATURE_ON == FEATURE_LTE)
extern NVIM_RSRP_CFG_STRU g_stRsrpCfg;
extern NVIM_RSCP_CFG_STRU g_stRscpCfg;
extern NVIM_ECIO_CFG_STRU g_stEcioCfg;

extern LNAS_LMM_NV_NAS_RELEASE_STRU     g_stReleaseInfo;
#endif

extern AT_SS_CUSTOMIZE_PARA_STRU           g_stAtSsCustomizePara;

extern AT_CLIENT_CFG_MAP_TAB_STRU          g_astAtClientCfgMapTbl[];
extern const VOS_UINT8                     g_ucAtClientCfgMapTabLen;
extern VOS_UINT32                          g_ulCtzuFlag;

/*****************************************************************************
  10 ????????
*****************************************************************************/
extern VOS_VOID AT_InitUsimStatus(MODEM_ID_ENUM_UINT16 enModemId);
extern VOS_VOID AT_InitPlatformRatList(MODEM_ID_ENUM_UINT16 enModemId);

extern VOS_VOID AT_InitCommPbCtx(VOS_VOID);

extern VOS_VOID AT_InitCommCtx(VOS_VOID);
extern VOS_VOID AT_InitModemCcCtx(MODEM_ID_ENUM_UINT16 enModemId);
extern VOS_VOID AT_InitModemSmsCtx(MODEM_ID_ENUM_UINT16 enModemId);
extern VOS_VOID AT_InitModemNetCtx(MODEM_ID_ENUM_UINT16 enModemId);
extern VOS_VOID AT_InitModemAgpsCtx(MODEM_ID_ENUM_UINT16 enModemId);
extern VOS_VOID AT_InitCtx(VOS_VOID);
extern VOS_VOID AT_InitModemCtx(MODEM_ID_ENUM_UINT16 enModemId);

extern VOS_VOID AT_InitClientConfiguration(VOS_VOID);
extern VOS_VOID AT_InitClientCtx(VOS_VOID);
MODEM_ID_ENUM_UINT16 AT_GetModemIDFromPid(VOS_UINT32 ulPid);
extern AT_USIM_INFO_CTX_STRU* AT_GetUsimInfoCtxFromModemId(
    MODEM_ID_ENUM_UINT16                enModemId
);
extern AT_MODEM_SPT_RAT_STRU* AT_GetSptRatFromModemId(
    MODEM_ID_ENUM_UINT16                enModemId
);
extern VOS_UINT8 AT_IsModemSupportRat(
           MODEM_ID_ENUM_UINT16                enModemId,
           TAF_MMA_RAT_TYPE_ENUM_UINT8         enRat
       );

extern VOS_UINT8 AT_IsModemSupportUtralTDDRat(
    MODEM_ID_ENUM_UINT16                enModemId
);

extern AT_COMM_CTX_STRU* AT_GetCommCtxAddr(VOS_VOID);
extern AT_COMM_PS_CTX_STRU* AT_GetCommPsCtxAddr(VOS_VOID);

extern AT_COMM_PB_CTX_STRU* AT_GetCommPbCtxAddr(VOS_VOID);

extern AT_CMD_MSG_NUM_CTRL_STRU* AT_GetMsgNumCtrlCtxAddr(VOS_VOID);

extern AT_MODEM_CC_CTX_STRU* AT_GetModemCcCtxAddrFromModemId(
           MODEM_ID_ENUM_UINT16                enModemId
       );
extern AT_MODEM_CC_CTX_STRU* AT_GetModemCcCtxAddrFromClientId(
           VOS_UINT16                          usClientId
       );
extern AT_MODEM_SS_CTX_STRU* AT_GetModemSsCtxAddrFromModemId(
    MODEM_ID_ENUM_UINT16                enModemId
);
extern AT_MODEM_SS_CTX_STRU* AT_GetModemSsCtxAddrFromClientId(
    VOS_UINT16                          usClientId
);
extern AT_MODEM_SMS_CTX_STRU* AT_GetModemSmsCtxAddrFromModemId(
           MODEM_ID_ENUM_UINT16                enModemId
       );
extern AT_MODEM_SMS_CTX_STRU* AT_GetModemSmsCtxAddrFromClientId(
           VOS_UINT16                          usClientId
       );
extern AT_MODEM_NET_CTX_STRU* AT_GetModemNetCtxAddrFromModemId(
           MODEM_ID_ENUM_UINT16                enModemId
       );
extern AT_MODEM_NET_CTX_STRU* AT_GetModemNetCtxAddrFromClientId(
           VOS_UINT16                          usClientId
       );
extern AT_MODEM_AGPS_CTX_STRU* AT_GetModemAgpsCtxAddrFromModemId(
           MODEM_ID_ENUM_UINT16                enModemId
       );
extern AT_MODEM_AGPS_CTX_STRU* AT_GetModemAgpsCtxAddrFromClientId(
           VOS_UINT16                          usClientId
       );

extern AT_MODEM_PS_CTX_STRU* AT_GetModemPsCtxAddrFromModemId(
    MODEM_ID_ENUM_UINT16                enModemId
);

extern AT_MODEM_PS_CTX_STRU* AT_GetModemPsCtxAddrFromClientId(
    VOS_UINT16                          usClientId
);

extern AT_CLIENT_CTX_STRU* AT_GetClientCtxAddr(
           AT_CLIENT_ID_ENUM_UINT16            enClientId
       );
extern AT_MODEM_CTX_STRU* AT_GetModemCtxAddr(
           MODEM_ID_ENUM_UINT16                enModemId
       );
extern VOS_UINT8* AT_GetSystemAppConfigAddr(VOS_VOID);
extern VOS_UINT32 AT_GetDestPid(
           MN_CLIENT_ID_T                      usClientId,
           VOS_UINT32                          ulRcvPid
       );
extern VOS_VOID AT_SetCsCallErrCause(
           VOS_UINT16                          usClientId,
           TAF_CS_CAUSE_ENUM_UINT32            enCsErrCause
       );

extern TAF_CS_CAUSE_ENUM_UINT32 AT_GetCsCallErrCause(
           VOS_UINT16                          usClientId
       );

extern AT_ABORT_CMD_PARA_STRU* AT_GetAbortCmdPara(VOS_VOID);
extern VOS_UINT8* AT_GetAbortRspStr(VOS_VOID);

extern VOS_UINT32 AT_GetSsCustomizePara(AT_SS_CUSTOMIZE_TYPE_UINT8 enSsCustomizeType);

extern VOS_VOID AT_InitResetCtx(VOS_VOID);
extern AT_RESET_CTX_STRU* AT_GetResetCtxAddr(VOS_VOID);
extern VOS_SEM AT_GetResetSem(VOS_VOID);
extern VOS_UINT32 AT_GetResetFlag(VOS_VOID);
extern VOS_VOID AT_SetResetFlag(VOS_UINT32 ulFlag);

/* Added by z60575 for DSDA_SAR, 2013-5-30 begin */
extern AT_MODEM_MT_INFO_CTX_STRU* AT_GetModemMtInfoCtxAddrFromModemId(
    MODEM_ID_ENUM_UINT16                enModemId
);

VOS_VOID AT_InitUartCtx(VOS_VOID);
AT_UART_CTX_STRU* AT_GetUartCtxAddr(VOS_VOID);
AT_UART_PHY_CFG_STRU* AT_GetUartPhyCfgInfo(VOS_VOID);
AT_UART_LINE_CTRL_STRU* AT_GetUartLineCtrlInfo(VOS_VOID);
AT_UART_FLOW_CTRL_STRU* AT_GetUartFlowCtrlInfo(VOS_VOID);
AT_UART_RI_CFG_STRU* AT_GetUartRiCfgInfo(VOS_VOID);
AT_UART_RI_STATE_INFO_STRU* AT_GetUartRiStateInfo(VOS_VOID);


VOS_VOID AT_InitTraceMsgTab(VOS_VOID);
AT_INTER_MSG_ID_ENUM_UINT32 AT_GetResultMsgID(VOS_UINT8 ucIndex);
AT_INTER_MSG_ID_ENUM_UINT32 AT_GetCmdMsgID(VOS_UINT8 ucIndex);

VOS_VOID AT_ConfigTraceMsg(
    VOS_UINT8                           ucIndex,
    AT_INTER_MSG_ID_ENUM_UINT32         enCmdMsgId,
    AT_INTER_MSG_ID_ENUM_UINT32         enResultMsgId
);

VOS_VOID At_SetAtCmdAbortTickInfo(
    VOS_UINT8                           ucIndex,
    VOS_UINT32                          ulTick
);
AT_CMD_ABORT_TICK_INFO* At_GetAtCmdAbortTickInfo(VOS_VOID);
VOS_UINT8 At_GetAtCmdAnyAbortFlg(VOS_VOID);
VOS_VOID At_SetAtCmdAnyAbortFlg(
    VOS_UINT8                           ucFlg
);

AT_PORT_BUFF_CFG_STRU* AT_GetPortBuffCfgInfo(VOS_VOID);

AT_PORT_BUFF_CFG_ENUM_UINT8  AT_GetPortBuffCfg(VOS_VOID);

VOS_VOID AT_InitPortBuffCfg(VOS_VOID);

VOS_VOID AT_AddUsedClientId2Tab(VOS_UINT16 usClientId);

VOS_VOID AT_RmUsedClientIdFromTab(VOS_UINT16 usClientId);

AT_CLIENT_CONFIGURATION_STRU* AT_GetClientConfig(
    AT_CLIENT_ID_ENUM_UINT16            enClientId
);
AT_CLIENT_CFG_MAP_TAB_STRU* AT_GetClientCfgMapTbl(VOS_UINT8 ucIndex);

VOS_UINT8 AT_GetSmsFilterEnableFlg(
    VOS_UINT8                           ucIndex
);

VOS_UINT8* AT_GetModemCLModeCtxAddrFromModemId(
    MODEM_ID_ENUM_UINT16                enModemId
);
VOS_UINT8 AT_IsSupportReleaseRst(VOS_UINT32 ulReleaseType);
VOS_VOID AT_InitVmSetCtx(VOS_VOID);
AT_VMSET_CMD_CTX_STRU* AT_GetCmdVmsetCtxAddr(VOS_VOID);
AT_CMD_PROC_CTX_STRU* AT_GetCmdProcCtxAddr(VOS_VOID);

VOS_VOID AT_InitMsgNumCtrlCtx(VOS_VOID);

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

#endif /* end of AtCtx.h */

