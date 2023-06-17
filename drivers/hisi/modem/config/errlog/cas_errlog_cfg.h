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

#ifndef __CAS_ERRLOG_CFG_H__
#define __CAS_ERRLOG_CFG_H__

#include "vos.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

enum CAS_1X_ERR_LOG_ALARM_ENUM
{
    ID_CAS_1X_ERR_LOG_ALARM_ABNORMAL_REL                    = 0x01,
    ID_CAS_1X_ERR_LOG_ALARM_EST_CNF_FAIL                    = 0x02,
    ID_CAS_1X_ERR_LOG_ALARM_SYS_DETERMIN                    = 0x03,
    ID_CAS_1X_ERR_LOG_ALARM_HANDOFF_FAIL_REVERT             = 0x04,
    ID_CAS_1X_ERR_LOG_ALARM_REJECT                          = 0x05,
    ID_CAS_1X_ERR_LOG_ALARM_OTA_DECODE_FAIL                 = 0x06,
    ID_CAS_1X_ERR_LOG_ALARM_OHM_UPDATE_FAIL                 = 0x07,
    ID_CAS_1X_ERR_LOG_ALARM_HANDOFF_SYNC_FAIL               = 0x08,
    ID_CAS_1X_ERR_LOG_ALARM_TCH_HANDOFF_FAIL                = 0x09,
    ID_CAS_1X_ERR_LOG_ALARM_NEGOTIATION_FAIL                = 0x0a,
    ID_CAS_1X_ERR_LOG_ALARM_MULTI_HANDOFF                   = 0x0b,
    ID_CAS_1X_ERR_LOG_ALARM_AUTHENTICATION_FAIL             = 0x0c,
    ID_CAS_1X_ERR_LOG_ALARM_OTA_ENCODE_FAIL                 = 0x0d,
    ID_CAS_1X_ERR_LOG_ALARM_COMMON_INFO                     = 0x0e,

    ID_CAS_1X_ERR_LOG_ALARM_BUTT                            = 0x9F
};
typedef VOS_UINT8 CAS_1X_ERR_LOG_ALARM_ENUM_UINT8;

enum CAS_HRPD_ERR_LOG_ALARM_ENUM
{
    ID_CAS_HRPD_ERR_LOG_REPORT_IND                          = 0xA0,
    ID_CAS_HRPD_ERR_LOG_CONN_OPEN_FAIL                      = 0xA1,
    ID_CAS_HRPD_ERR_LOG_SESSION_NEG_FAIL                    = 0xA2,
    ID_CAS_HRPD_ERR_LOG_NETWORK_LOST                        = 0xA3,
    ID_CAS_HRPD_ERR_LOG_RESEL_TO_LTE_FAIL                   = 0xA4,
    ID_CAS_HRPD_ERR_LOG_L2C_RESEL_FAIL                      = 0xA5,
    ID_CAS_HRPD_ERR_LOG_L2C_REDIRECT_FAIL                   = 0xA6,
    ID_CAS_HRPD_ERR_LOG_CODEC_FAIL                          = 0xA7,
    ID_CAS_HRPD_ERR_LOG_NETWORK_SEARCH_FAIL                 = 0xA8,
    ID_CAS_HRPD_ERR_LOG_COMMON_INFO                         = 0xA9,
    ID_CAS_HRPD_ERR_LOG_TCA_RCV_FAIL                        = 0xAA,

    ID_CAS_HRPD_ERR_LOG_BUTT                                = 0xFF
};
typedef VOS_UINT8 CAS_HRPD_ERR_LOG_ALARM_ENUM_UINT8;

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

#endif /* end of cas_errlog_cfg.h */
