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
#ifndef _AT_INTERNAL_MSG_H_
#define _AT_INTERNAL_MSG_H_

/*****************************************************************************
  1 ??????????????
*****************************************************************************/
#include "vos.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*****************************************************************************
  2 ??????
*****************************************************************************/
/* ??PC?????????????????? : ????????????????????????*/
#define AT_PC_REPLAY_MSG                (0xff)

/* ??PC?????????????????? : ??????????????????????*/
#define AT_PC_REPLAY_MSG_CLIENT_TAB     (0xfe)

/* ??????????????at???????????? */
#define AT_NORMAL_TYPE_MSG              (0x00)

/* ?????????????????????????????? */
#define AT_COMBIN_BLOCK_MSG             (0xfd)

/* ????????????????, UART??????????"+++"?????? */
#define AT_SWITCH_CMD_MODE_MSG          (0x31)

/* ?????????????????????? */
#define AT_WATER_LOW_MSG                (0x32)

#define AT_NCM_CONN_STATUS_MSG          (0x33)

/* AT????????ID?????? */
#define ID_AT_CMD_BASE_ID               (0x0000)

/* AT??????????ID?????? */
#define ID_AT_COMM_BASE_ID              (0x1000)

/* AT????????????ID?????? */
#define ID_AT_MNTN_RESULT_BASE_ID       (0x2000)

#define ID_AT_MNTN_REPLAY_BASE_ID       (0x2100)

#define ID_AT_MNTN_FC_BASE_ID           (0x2200)

#define ID_AT_MNTN_PORT_BASE_ID         (0x2300)

/*****************************************************************************
  3 ????????
*****************************************************************************/
/*****************************************************************************
 ??????    : AT_INTER_MSG_ID_ENUM
 ????????  : ????AT??AT????????ID

  1.??    ??   : 2013??11??06??
    ??    ??   : j00174725
    ????????   : ????AT??AT????????ID
*****************************************************************************/
enum AT_INTER_MSG_ID_ENUM
{
    /* AT????????ID???? [0x0000, 0x0FFF]*/
    ID_AT_CMD_PCUI                      = ID_AT_CMD_BASE_ID + 0x01,             /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_CMD_CTRL                      = ID_AT_CMD_BASE_ID + 0x02,             /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_CMD_PCUI2                     = ID_AT_CMD_BASE_ID + 0x03,             /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_CMD_MODEM                     = ID_AT_CMD_BASE_ID + 0x04,             /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_CMD_NDIS                      = ID_AT_CMD_BASE_ID + 0x05,             /* _H2ASN_MsgChoice AT_MSG_STRU */

    ID_AT_CMD_UART                      = ID_AT_CMD_BASE_ID + 0x11,             /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_CMD_HSUART                    = ID_AT_CMD_BASE_ID + 0x12,             /* _H2ASN_MsgChoice AT_MSG_STRU */

    ID_AT_CMD_SOCK                      = ID_AT_CMD_BASE_ID + 0x21,             /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_CMD_APPSOCK                   = ID_AT_CMD_BASE_ID + 0x22,             /* _H2ASN_MsgChoice AT_MSG_STRU */

    ID_AT_CMD_HSIC1                     = ID_AT_CMD_BASE_ID + 0x31,             /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_CMD_HSIC2                     = ID_AT_CMD_BASE_ID + 0x32,             /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_CMD_HSIC3                     = ID_AT_CMD_BASE_ID + 0x33,             /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_CMD_HSIC4                     = ID_AT_CMD_BASE_ID + 0x34,             /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_CMD_HSIC_MODEM                = ID_AT_CMD_BASE_ID + 0x35,             /* _H2ASN_MsgChoice AT_MSG_STRU */

    ID_AT_CMD_MUX1                      = ID_AT_CMD_BASE_ID + 0x41,             /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_CMD_MUX2                      = ID_AT_CMD_BASE_ID + 0x42,             /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_CMD_MUX3                      = ID_AT_CMD_BASE_ID + 0x43,             /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_CMD_MUX4                      = ID_AT_CMD_BASE_ID + 0x44,             /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_CMD_MUX5                      = ID_AT_CMD_BASE_ID + 0x45,             /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_CMD_MUX6                      = ID_AT_CMD_BASE_ID + 0x46,             /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_CMD_MUX7                      = ID_AT_CMD_BASE_ID + 0x47,             /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_CMD_MUX8                      = ID_AT_CMD_BASE_ID + 0x48,             /* _H2ASN_MsgChoice AT_MSG_STRU */

    ID_AT_CMD_APP                       = ID_AT_CMD_BASE_ID + 0x51,             /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_CMD_APP1                      = ID_AT_CMD_BASE_ID + 0x52,             /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_CMD_APP2                      = ID_AT_CMD_BASE_ID + 0x53,             /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_CMD_APP3                      = ID_AT_CMD_BASE_ID + 0x54,             /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_CMD_APP4                      = ID_AT_CMD_BASE_ID + 0x55,             /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_CMD_APP5                      = ID_AT_CMD_BASE_ID + 0x56,             /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_CMD_APP6                      = ID_AT_CMD_BASE_ID + 0x57,             /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_CMD_APP7                      = ID_AT_CMD_BASE_ID + 0x58,             /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_CMD_APP8                      = ID_AT_CMD_BASE_ID + 0x59,             /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_CMD_APP9                      = ID_AT_CMD_BASE_ID + 0x5A,             /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_CMD_APP10                     = ID_AT_CMD_BASE_ID + 0x5B,             /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_CMD_APP11                     = ID_AT_CMD_BASE_ID + 0x5C,             /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_CMD_APP12                     = ID_AT_CMD_BASE_ID + 0x5D,             /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_CMD_APP13                     = ID_AT_CMD_BASE_ID + 0x5E,             /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_CMD_APP14                     = ID_AT_CMD_BASE_ID + 0x5F,             /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_CMD_APP15                     = ID_AT_CMD_BASE_ID + 0x60,             /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_CMD_APP16                     = ID_AT_CMD_BASE_ID + 0x61,             /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_CMD_APP17                     = ID_AT_CMD_BASE_ID + 0x62,             /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_CMD_APP18                     = ID_AT_CMD_BASE_ID + 0x63,             /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_CMD_APP19                     = ID_AT_CMD_BASE_ID + 0x64,             /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_CMD_APP20                     = ID_AT_CMD_BASE_ID + 0x65,             /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_CMD_APP21                     = ID_AT_CMD_BASE_ID + 0x66,             /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_CMD_APP22                     = ID_AT_CMD_BASE_ID + 0x67,             /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_CMD_APP23                     = ID_AT_CMD_BASE_ID + 0x68,             /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_CMD_APP24                     = ID_AT_CMD_BASE_ID + 0x69,             /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_CMD_APP25                     = ID_AT_CMD_BASE_ID + 0x6A,             /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_CMD_APP26                     = ID_AT_CMD_BASE_ID + 0x6B,             /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_CMD_APP27                     = ID_AT_CMD_BASE_ID + 0x6C,             /* _H2ASN_MsgChoice AT_MSG_STRU */

    ID_AT_NCM_CONN_STATUS_CMD           = ID_AT_CMD_BASE_ID + 0xFC,             /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_WATER_LOW_CMD                 = ID_AT_CMD_BASE_ID + 0xFD,             /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_SWITCH_CMD_MODE               = ID_AT_CMD_BASE_ID + 0xFE,             /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_COMBIN_BLOCK_CMD              = ID_AT_CMD_BASE_ID + 0xFF,             /* _H2ASN_MsgChoice AT_MSG_STRU */

    /* ???????? [0x1000, 0x1FFF] */
    ID_AT_COMM_CCPU_RESET_START         = ID_AT_COMM_BASE_ID + 0x01,            /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_COMM_CCPU_RESET_END           = ID_AT_COMM_BASE_ID + 0x02,            /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_COMM_HIFI_RESET_START         = ID_AT_COMM_BASE_ID + 0x03,            /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_COMM_HIFI_RESET_END           = ID_AT_COMM_BASE_ID + 0x04,            /* _H2ASN_MsgChoice AT_MSG_STRU */

    /* AT????????????ID???? [0x2000, 0x20FF]*/
    ID_AT_MNTN_RESULT_PCUI              = ID_AT_MNTN_RESULT_BASE_ID + 0x01,     /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_MNTN_RESULT_CTRL              = ID_AT_MNTN_RESULT_BASE_ID + 0x02,     /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_MNTN_RESULT_PCUI2             = ID_AT_MNTN_RESULT_BASE_ID + 0x03,     /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_MNTN_RESULT_MODEM             = ID_AT_MNTN_RESULT_BASE_ID + 0x04,     /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_MNTN_RESULT_NDIS              = ID_AT_MNTN_RESULT_BASE_ID + 0x05,     /* _H2ASN_MsgChoice AT_MSG_STRU */

    ID_AT_MNTN_RESULT_UART              = ID_AT_MNTN_RESULT_BASE_ID + 0x11,     /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_MNTN_RESULT_HSUART            = ID_AT_MNTN_RESULT_BASE_ID + 0x12,     /* _H2ASN_MsgChoice AT_MSG_STRU */

    ID_AT_MNTN_RESULT_SOCK              = ID_AT_MNTN_RESULT_BASE_ID + 0x21,     /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_MNTN_RESULT_APPSOCK           = ID_AT_MNTN_RESULT_BASE_ID + 0x22,     /* _H2ASN_MsgChoice AT_MSG_STRU */

    ID_AT_MNTN_RESULT_HSIC1             = ID_AT_MNTN_RESULT_BASE_ID + 0x31,     /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_MNTN_RESULT_HSIC2             = ID_AT_MNTN_RESULT_BASE_ID + 0x32,     /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_MNTN_RESULT_HSIC3             = ID_AT_MNTN_RESULT_BASE_ID + 0x33,     /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_MNTN_RESULT_HSIC4             = ID_AT_MNTN_RESULT_BASE_ID + 0x34,     /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_MNTN_RESULT_HSIC_MODEM        = ID_AT_MNTN_RESULT_BASE_ID + 0x35,     /* _H2ASN_MsgChoice AT_MSG_STRU */

    ID_AT_MNTN_RESULT_MUX1              = ID_AT_MNTN_RESULT_BASE_ID + 0x41,     /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_MNTN_RESULT_MUX2              = ID_AT_MNTN_RESULT_BASE_ID + 0x42,     /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_MNTN_RESULT_MUX3              = ID_AT_MNTN_RESULT_BASE_ID + 0x43,     /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_MNTN_RESULT_MUX4              = ID_AT_MNTN_RESULT_BASE_ID + 0x44,     /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_MNTN_RESULT_MUX5              = ID_AT_MNTN_RESULT_BASE_ID + 0x45,     /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_MNTN_RESULT_MUX6              = ID_AT_MNTN_RESULT_BASE_ID + 0x46,     /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_MNTN_RESULT_MUX7              = ID_AT_MNTN_RESULT_BASE_ID + 0x47,     /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_MNTN_RESULT_MUX8              = ID_AT_MNTN_RESULT_BASE_ID + 0x48,     /* _H2ASN_MsgChoice AT_MSG_STRU */

    ID_AT_MNTN_RESULT_APP               = ID_AT_MNTN_RESULT_BASE_ID + 0x51,     /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_MNTN_RESULT_APP1              = ID_AT_MNTN_RESULT_BASE_ID + 0x52,     /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_MNTN_RESULT_APP2              = ID_AT_MNTN_RESULT_BASE_ID + 0x53,     /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_MNTN_RESULT_APP3              = ID_AT_MNTN_RESULT_BASE_ID + 0x54,     /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_MNTN_RESULT_APP4              = ID_AT_MNTN_RESULT_BASE_ID + 0x55,     /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_MNTN_RESULT_APP5              = ID_AT_MNTN_RESULT_BASE_ID + 0x56,     /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_MNTN_RESULT_APP6              = ID_AT_MNTN_RESULT_BASE_ID + 0x57,     /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_MNTN_RESULT_APP7              = ID_AT_MNTN_RESULT_BASE_ID + 0x58,     /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_MNTN_RESULT_APP8              = ID_AT_MNTN_RESULT_BASE_ID + 0x59,     /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_MNTN_RESULT_APP9              = ID_AT_MNTN_RESULT_BASE_ID + 0x5A,     /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_MNTN_RESULT_APP10             = ID_AT_MNTN_RESULT_BASE_ID + 0x5B,     /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_MNTN_RESULT_APP11             = ID_AT_MNTN_RESULT_BASE_ID + 0x5C,     /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_MNTN_RESULT_APP12             = ID_AT_MNTN_RESULT_BASE_ID + 0x5D,     /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_MNTN_RESULT_APP13             = ID_AT_MNTN_RESULT_BASE_ID + 0x5E,     /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_MNTN_RESULT_APP14             = ID_AT_MNTN_RESULT_BASE_ID + 0x5F,     /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_MNTN_RESULT_APP15             = ID_AT_MNTN_RESULT_BASE_ID + 0x60,     /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_MNTN_RESULT_APP16             = ID_AT_MNTN_RESULT_BASE_ID + 0x61,     /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_MNTN_RESULT_APP17             = ID_AT_MNTN_RESULT_BASE_ID + 0x62,     /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_MNTN_RESULT_APP18             = ID_AT_MNTN_RESULT_BASE_ID + 0x63,     /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_MNTN_RESULT_APP19             = ID_AT_MNTN_RESULT_BASE_ID + 0x64,     /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_MNTN_RESULT_APP20             = ID_AT_MNTN_RESULT_BASE_ID + 0x65,     /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_MNTN_RESULT_APP21             = ID_AT_MNTN_RESULT_BASE_ID + 0x66,     /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_MNTN_RESULT_APP22             = ID_AT_MNTN_RESULT_BASE_ID + 0x67,     /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_MNTN_RESULT_APP23             = ID_AT_MNTN_RESULT_BASE_ID + 0x68,     /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_MNTN_RESULT_APP24             = ID_AT_MNTN_RESULT_BASE_ID + 0x69,     /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_MNTN_RESULT_APP25             = ID_AT_MNTN_RESULT_BASE_ID + 0x6A,     /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_MNTN_RESULT_APP26             = ID_AT_MNTN_RESULT_BASE_ID + 0x6B,     /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_MNTN_RESULT_APP27             = ID_AT_MNTN_RESULT_BASE_ID + 0x6C,     /* _H2ASN_MsgChoice AT_MSG_STRU */

    ID_AT_MNTN_RESULT_BROADCAST_MODEM_2 = ID_AT_MNTN_RESULT_BASE_ID + 0xFD,     /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_MNTN_RESULT_BROADCAST_MODEM_1 = ID_AT_MNTN_RESULT_BASE_ID + 0xFE,     /* _H2ASN_MsgChoice AT_MSG_STRU */
    ID_AT_MNTN_RESULT_BROADCAST_MODEM_0 = ID_AT_MNTN_RESULT_BASE_ID + 0xFF,     /* _H2ASN_MsgChoice AT_MSG_STRU */

    /* ???????????????? [0x2100, 0x21FF] */
    ID_AT_MNTN_PC_REPLAY_CLIENT_TAB     = ID_AT_MNTN_REPLAY_BASE_ID + 0x01,     /* _H2ASN_MsgChoice NAS_AT_SDT_AT_CLIENT_TABLE_STRU */
    ID_AT_MNTN_PC_REPLAY_MSG            = ID_AT_MNTN_REPLAY_BASE_ID + 0x02,     /* _H2ASN_MsgChoice NAS_AT_SDT_AT_PART_ST */

    /* ???????????????? [0x2201, 0x22FF] */
    ID_AT_MNTN_INPUT_MSC                = ID_AT_MNTN_FC_BASE_ID + 0x01,         /* _H2ASN_MsgChoice AT_MNTN_MSC_STRU */
    ID_AT_MNTN_OUTPUT_MSC               = ID_AT_MNTN_FC_BASE_ID + 0x02,         /* _H2ASN_MsgChoice AT_MNTN_MSC_STRU */
    ID_AT_MNTN_START_FLOW_CTRL          = ID_AT_MNTN_FC_BASE_ID + 0x03,         /* _H2ASN_MsgChoice AT_MNTN_FLOW_CTRL_STRU */
    ID_AT_MNTN_STOP_FLOW_CTRL           = ID_AT_MNTN_FC_BASE_ID + 0x04,         /* _H2ASN_MsgChoice AT_MNTN_FLOW_CTRL_STRU */
    ID_AT_MNTN_REG_FC_POINT             = ID_AT_MNTN_FC_BASE_ID + 0x05,         /* _H2ASN_MsgChoice AT_MNTN_FC_POINT_STRU */
    ID_AT_MNTN_DEREG_FC_POINT           = ID_AT_MNTN_FC_BASE_ID + 0x06,         /* _H2ASN_MsgChoice AT_MNTN_FC_POINT_STRU */

    /* ???????????????????? [0x2301, 0x23FF] */
    ID_AT_MNTN_RPT_PORT                 = ID_AT_MNTN_PORT_BASE_ID + 0x01,       /* _H2ASN_MsgChoice AT_MNTN_RPTPORT_STRU */

};
typedef VOS_UINT32 AT_INTER_MSG_ID_ENUM_UINT32;

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
 ??????    : AT_MSG_STRU
 ????????  : AT??????????
 1.??    ??   : 2013??11??13??
   ??    ??   : j00174725
   ????????   :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    AT_INTER_MSG_ID_ENUM_UINT32         enMsgId;            /* ????????     */  /* _H2ASN_Skip */
    VOS_UINT8                           ucType;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucUserType;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT16                          usLen;
    VOS_UINT8                           aucValue[4];
}AT_MSG_STRU;

/*****************************************************************************
  8 UNION????
*****************************************************************************/

/*****************************************************************************
  9 OTHERS????
*****************************************************************************/

/*****************************************************************************
  H2ASN????????????????
*****************************************************************************/
typedef struct
{
    AT_INTER_MSG_ID_ENUM_UINT32        enMsgId;                                /* _H2ASN_MsgChoice_Export AT_INTER_MSG_ID_ENUM_UINT32 */
    VOS_UINT8                          aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          AT_INTER_MSG_ID_ENUM_UINT32
    ****************************************************************************/
} AT_INTER_MSG_DATA;
/* _H2ASN_Length UINT32 */

typedef struct
{
    VOS_MSG_HEADER
    AT_INTER_MSG_DATA                   stMsgData;
} AtInternalMsg_MSG;


/*****************************************************************************
  10 ????????
*****************************************************************************/



#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif


#endif /* end of AtInternalMsg.h */

