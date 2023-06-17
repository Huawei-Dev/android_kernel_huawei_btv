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
#ifndef _TAF_APS_API_H_
#define _TAF_APS_API_H_


/*****************************************************************************
  1 ??????????????
*****************************************************************************/
#include "vos.h"
#include "TafTypeDef.h"
#include "PsTypeDef.h"
#include "TafApi.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/*****************************************************************************
  2 ??????
*****************************************************************************/

#define TAF_PS_MSG_ID_BASE                  (0x0000)
#define TAF_PS_EVT_ID_BASE                  (0x0A00)

/* "a1.a2.a3.a4 " */
#define TAF_IPV4_ADDR_LEN               (4)

/* "a1...a16" */
#define TAF_IPV6_ADDR_LEN               (16)
#define TAF_MAX_PREFIX_NUM_IN_RA        (6)

/* ^AUTHDATA */
#define TAF_MAX_AUTHDATA_USERNAME_LEN   (127)
#define TAF_MAX_AUTHDATA_PASSWORD_LEN   (127)
#define TAF_MAX_AUTHDATA_PLMN_LEN       (6)

/* ^CGAUTH */
#define TAF_MAX_PDP_AUTH_USERNAME_LEN   (99)
#define TAF_MAX_PDP_AUTH_PASSCODE_LEN   (99)

#define TAF_MAX_ACCESS_NUM_LEN          (32)
#define TAF_MAX_GW_AUTH_USERNAME_LEN    (255)
#define TAF_MAX_GW_AUTH_PASSWORD_LEN    (255)

#define TAF_MAX_PDP_PROFILE_NUM         (32)
#define TAF_MAX_SDF_PF_NUM              (16)

#define TAF_MAX_APN_LEN                 (99)

/*????????????PDP????????????*/

#if (FEATURE_ON == FEATURE_LTE)
#define TAF_MAX_CID                     (31)
#else
#define TAF_MAX_CID                     (11)
#endif
#define TAF_MAX_CID_NV                  (11)

#define TAF_INVALID_CID                 (0xFF)

/* 4 x 3 char dec nums + 3 x '.' + '\0' */
#define TAF_MAX_IPV4_ADDR_STR_LEN       (16)

/* 8 x 4 ????(HEX) + 7 x ':' + '\0' */
#define TAF_MAX_IPV6_ADDR_COLON_STR_LEN (40)

/* 32 x 3 ????(DEC) + 31 x '.' + '\0' */
#define TAF_MAX_IPV6_ADDR_DOT_STR_LEN   (128)

#define TAF_IPV6_STR_MAX_TOKENS         (16)                                    /* IPV6?????????????????????????????????? */

#define TAF_IPV6_STR_RFC2373_TOKENS     (8)                                     /* RFC2373??????IPV6?????????????????????????????????? */

#define TAF_IPV4_STR_DELIMITER          '.'                                     /* RFC??????????IPV4???????????????????????? */
#define TAF_IPV6_STR_DELIMITER          ':'                                     /* RFC2373??????IPV6???????????????????????? */

#define TAF_IPV6_PREFIX_LEN             (8)                                     /* IPv6???????????? */

#define TAF_MAX_USERNAME_LEN            (99)                                    /*AUTHLEN ??100??????1????????Peer-ID Length??99??????Peer-ID??????????????99*/
#define TAF_MAX_PASSCODE_LEN            (99)                                    /*PASSWORDLEN ??100??????1????????Passwd-Length??99??????Passwd??????????????99*/

#define TAF_PS_MAX_PDPID                (11)


/* password+auth */
#define TAF_PPP_PAP_REQ_MAX_LEN             (100 + 100)

/* code(1B)+id(1B)+length(2B)+challenge_size(1B)+challenge+name */
#define TAF_PPP_CHAP_CHALLENGE_MAX_LEN      (1 + 1 + 2 + 1 + 48 + 100)

/* code(1B)+id(1B)+length(2B)+response_size(1B)+response+name */
#define TAF_PPP_CHAP_RESPONSE_MAX_LEN       (1 + 1 + 2 + 1 + 100 + 100)

#define TAF_PPP_AUTH_FRAME_BUF_MAX_LEN      (256)

#define TAF_PPP_IPCP_FRAME_BUF_MAX_LEN      (256)

#define TAF_DEFAULT_DSFLOW_NV_WR_INTERVAL   (2)             /* DSFLOW????????NV??????, ????(min) */

#define TAF_PS_CAUSE_APS_SECTION_BEGIN      (0x0000)
#define TAF_PS_CAUSE_SM_SECTION_BEGIN       (0x0080)
#define TAF_PS_CAUSE_SM_NW_SECTION_BEGIN    (0x0100)
#define TAF_PS_CAUSE_SM_NW_SECTION_END      (0x01FF)
#define TAF_PS_CAUSE_GMM_SECTION_BEGIN      (0x0200)
#define TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN   (0x0300)
#define TAF_PS_CAUSE_XCC_SECTION_BEGIN      (0x0400)
#define TAF_PS_CAUSE_XCC_AS_SECTION_BEGIN   (0x0500)
#define TAF_PS_CAUSE_HSM_AS_SECTION_BEGIN   (0x0600)
#define TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN (0X0700)
/* ??????0X0800??????????ril??????0 ~ 255????????????????????0X0800 */

#define TAF_PS_IS_SM_CAUSE_VALID(sm_cause)\
            ( (((sm_cause) + TAF_PS_CAUSE_SM_NW_SECTION_BEGIN) >= TAF_PS_CAUSE_SM_NW_OPERATOR_DETERMINED_BARRING)\
             && (((sm_cause) + TAF_PS_CAUSE_SM_NW_SECTION_BEGIN) <= TAF_PS_CAUSE_SM_NW_APN_RESTRICTION_INCOMPATIBLE) )

#define TAF_PS_CONVERT_SM_CAUSE_TO_PS_CAUSE(sm_cause)\
            ((sm_cause) + TAF_PS_CAUSE_SM_NW_SECTION_BEGIN)

#define TAF_PS_GET_MSG_CONTENT(pstMsg)\
            ((VOS_VOID *)(((TAF_PS_MSG_STRU *)(pstMsg))->aucContent))

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
#define TAF_PS_BUILD_EXCLIENTID(usModemId,usClientId)\
            ((VOS_UINT16)(((usModemId) & 0x000F) << 12) | (usClientId))

#define TAF_PS_GET_MODEMID_FROM_EXCLIENTID(usExClientId)\
            ((VOS_UINT16)(((usExClientId) & 0xF000) >> 12))

#define TAF_PS_GET_CLIENTID_FROM_EXCLIENTID(usExClientId)\
            ((VOS_UINT16)((usExClientId) & 0x0FFF))
#else
#define TAF_PS_BUILD_EXCLIENTID(usModemId,usClientId)\
            ((VOS_UINT16)(usClientId))

#define TAF_PS_GET_MODEMID_FROM_EXCLIENTID(usExClientId)\
            (MODEM_ID_BUTT)

#define TAF_PS_GET_CLIENTID_FROM_EXCLIENTID(usExClientId)\
            ((VOS_UINT16)(usExClientId))
#endif


/*****************************************************************************
  3 ????????
*****************************************************************************/

/*****************************************************************************
 ????????: TAF_PS_MSG_ID_ENUM
 ????????: PS??????????ID

 ????????      :
  1.??    ??   : 2013??06??18??
    ??    ??   : A00165503
    ????????   : ????????
*****************************************************************************/
enum TAF_PS_MSG_ID_ENUM
{
    /*----------------------------------------------------------------------
       ????????[0x0000, 0x0099]
    *---------------------------------------------------------------------*/
    /* +CGDCONT */
    ID_MSG_TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ             = TAF_PS_MSG_ID_BASE + 0x0001,  /* _H2ASN_MsgChoice TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ_STRU */
    ID_MSG_TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_REQ             = TAF_PS_MSG_ID_BASE + 0x0002,  /* _H2ASN_MsgChoice TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_REQ_STRU */

    /* +CGDSCONT */
    ID_MSG_TAF_PS_SET_SEC_PDP_CONTEXT_INFO_REQ              = TAF_PS_MSG_ID_BASE + 0x0003,  /* _H2ASN_MsgChoice TAF_PS_SET_SEC_PDP_CONTEXT_INFO_REQ_STRU */
    ID_MSG_TAF_PS_GET_SEC_PDP_CONTEXT_INFO_REQ              = TAF_PS_MSG_ID_BASE + 0x0004,  /* _H2ASN_MsgChoice TAF_PS_GET_SEC_PDP_CONTEXT_INFO_REQ_STRU */

    /* +CGTFT */
    ID_MSG_TAF_PS_SET_TFT_INFO_REQ                          = TAF_PS_MSG_ID_BASE + 0x0005,  /* _H2ASN_MsgChoice TAF_PS_SET_TFT_INFO_REQ_STRU */
    ID_MSG_TAF_PS_GET_TFT_INFO_REQ                          = TAF_PS_MSG_ID_BASE + 0x0006,  /* _H2ASN_MsgChoice TAF_PS_GET_TFT_INFO_REQ_STRU */

    /* +CGQREQ */
    ID_MSG_TAF_PS_SET_GPRS_QOS_INFO_REQ                     = TAF_PS_MSG_ID_BASE + 0x0007,  /* _H2ASN_MsgChoice */
    ID_MSG_TAF_PS_GET_GPRS_QOS_INFO_REQ                     = TAF_PS_MSG_ID_BASE + 0x0008,  /* _H2ASN_MsgChoice */

    /* +CGQMIN */
    ID_MSG_TAF_PS_SET_GPRS_QOS_MIN_INFO_REQ                 = TAF_PS_MSG_ID_BASE + 0x0009,  /* _H2ASN_MsgChoice */
    ID_MSG_TAF_PS_GET_GPRS_QOS_MIN_INFO_REQ                 = TAF_PS_MSG_ID_BASE + 0x000A,  /* _H2ASN_MsgChoice */

    /* +CGEQREQ */
    ID_MSG_TAF_PS_SET_UMTS_QOS_INFO_REQ                     = TAF_PS_MSG_ID_BASE + 0x000B,  /* _H2ASN_MsgChoice TAF_PS_SET_UMTS_QOS_INFO_REQ_STRU */
    ID_MSG_TAF_PS_GET_UMTS_QOS_INFO_REQ                     = TAF_PS_MSG_ID_BASE + 0x000C,  /* _H2ASN_MsgChoice TAF_PS_GET_UMTS_QOS_INFO_REQ_STRU */

    /* +CGEQMIN */
    ID_MSG_TAF_PS_SET_UMTS_QOS_MIN_INFO_REQ                 = TAF_PS_MSG_ID_BASE + 0x000D,  /* _H2ASN_MsgChoice TAF_PS_SET_UMTS_QOS_MIN_INFO_REQ_STRU */
    ID_MSG_TAF_PS_GET_UMTS_QOS_MIN_INFO_REQ                 = TAF_PS_MSG_ID_BASE + 0x000E,  /* _H2ASN_MsgChoice TAF_PS_GET_UMTS_QOS_MIN_INFO_REQ_STRU */

    /* +CGEQNEG */
    ID_MSG_TAF_PS_GET_DYNAMIC_UMTS_QOS_INFO_REQ             = TAF_PS_MSG_ID_BASE + 0x000F,  /* _H2ASN_MsgChoice TAF_PS_GET_DYNAMIC_UMTS_QOS_INFO_REQ_STRU */

    /* +CGACT */
    ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ                 = TAF_PS_MSG_ID_BASE + 0x0010,  /* _H2ASN_MsgChoice TAF_PS_SET_PDP_STATE_REQ_STRU */
    ID_MSG_TAF_PS_GET_PDP_CONTEXT_STATE_REQ                 = TAF_PS_MSG_ID_BASE + 0x0011,  /* _H2ASN_MsgChoice TAF_PS_GET_PDP_STATE_REQ_STRU */

    /* +CGCMOD */
    ID_MSG_TAF_PS_CALL_MODIFY_REQ                           = TAF_PS_MSG_ID_BASE + 0x0012,  /* _H2ASN_MsgChoice TAF_PS_CALL_MODIFY_REQ_STRU */

    /* +CGANS */
    ID_MSG_TAF_PS_CALL_ANSWER_REQ                           = TAF_PS_MSG_ID_BASE + 0x0013,  /* _H2ASN_MsgChoice TAF_PS_CALL_ANSWER_REQ_STRU */
    ID_MSG_TAF_PS_CALL_HANGUP_REQ                           = TAF_PS_MSG_ID_BASE + 0x0014,  /* _H2ASN_MsgChoice TAF_PS_CALL_HANGUP_REQ_STRU */

    /* +CGPADDR */
    ID_MSG_TAF_PS_GET_PDP_IP_ADDR_INFO_REQ                  = TAF_PS_MSG_ID_BASE + 0x0015,  /* _H2ASN_MsgChoice TAF_PS_GET_PDP_IP_ADDR_INFO_REQ_STRU */

    ID_MSG_TAF_PS_GET_PDPCONT_INFO_REQ                      = TAF_PS_MSG_ID_BASE + 0x0016, /* _H2ASN_MsgChoice TAF_PS_GET_PDP_CONTEXT_INFO_REQ_STRU */

    /* +CGAUTO */
    ID_MSG_TAF_PS_SET_ANSWER_MODE_INFO_REQ                  = TAF_PS_MSG_ID_BASE + 0x0017,  /* _H2ASN_MsgChoice TAF_PS_SET_ANSWER_MODE_INFO_REQ_STRU */
    ID_MSG_TAF_PS_GET_ANSWER_MODE_INFO_REQ                  = TAF_PS_MSG_ID_BASE + 0x0018,  /* _H2ASN_MsgChoice TAF_PS_GET_ANSWER_MODE_INFO_REQ_STRU */

    /* +CGCONTRDP */
    ID_MSG_TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_REQ     = TAF_PS_MSG_ID_BASE + 0x0019,  /* _H2ASN_MsgChoice TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_REQ_STRU */

    /* +CGSCONTRDP */
    ID_MSG_TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_REQ      = TAF_PS_MSG_ID_BASE + 0x001A,  /* _H2ASN_MsgChoice TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_REQ_STRU */

    /* +CGTFTRDP */
    ID_MSG_TAF_PS_GET_DYNAMIC_TFT_INFO_REQ                  = TAF_PS_MSG_ID_BASE + 0x001B,  /* _H2ASN_MsgChoice TAF_PS_GET_DYNAMIC_TFT_INFO_REQ_STRU */

    /* +CGEQOS */
    ID_MSG_TAF_PS_SET_EPS_QOS_INFO_REQ                      = TAF_PS_MSG_ID_BASE + 0x001C,  /* _H2ASN_MsgChoice TAF_PS_SET_EPS_QOS_INFO_REQ_STRU */
    ID_MSG_TAF_PS_GET_EPS_QOS_INFO_REQ                      = TAF_PS_MSG_ID_BASE + 0x001D,  /* _H2ASN_MsgChoice TAF_PS_GET_EPS_QOS_INFO_REQ_STRU */

    /* +CGEQOSRDP */
    ID_MSG_TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_REQ              = TAF_PS_MSG_ID_BASE + 0x001E,  /* _H2ASN_MsgChoice TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_REQ_STRU */

    /*----------------------------------------------------------------------
       ????????[0x0100, 0x0199]
    *---------------------------------------------------------------------*/
    /* ^NDISCONN/^NDISDUP */
    ID_MSG_TAF_PS_CALL_ORIG_REQ                             = TAF_PS_MSG_ID_BASE + 0x0101,  /* _H2ASN_MsgChoice TAF_PS_CALL_ORIG_REQ_STRU */
    ID_MSG_TAF_PS_CALL_END_REQ                              = TAF_PS_MSG_ID_BASE + 0x0102,  /* _H2ASN_MsgChoice TAF_PS_CALL_END_REQ_STRU */

    /* D */
    ID_MSG_TAF_PS_GET_D_GPRS_ACTIVE_TYPE_REQ                = TAF_PS_MSG_ID_BASE + 0x0103,  /* _H2ASN_MsgChoice TAF_PS_GET_D_GPRS_ACTIVE_TYPE_REQ_STRU */

    /* PPP */
    ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ                         = TAF_PS_MSG_ID_BASE + 0x0104,  /* _H2ASN_MsgChoice TAF_PS_PPP_DIAL_ORIG_REQ_STRU */

    /* ^DSFLOWQRY */
    ID_MSG_TAF_PS_GET_DSFLOW_INFO_REQ                       = TAF_PS_MSG_ID_BASE + 0x0105,  /* _H2ASN_MsgChoice TAF_PS_GET_DSFLOW_INFO_REQ_STRU */

    /* ^DSFLOWCLR */
    ID_MSG_TAF_PS_CLEAR_DSFLOW_REQ                          = TAF_PS_MSG_ID_BASE + 0x0106,  /* _H2ASN_MsgChoice TAF_PS_CLEAR_DSFLOW_REQ_STRU */

    /* ^DSFLOWRPT */
    ID_MSG_TAF_PS_CONFIG_DSFLOW_RPT_REQ                     = TAF_PS_MSG_ID_BASE + 0x0107,  /* _H2ASN_MsgChoice TAF_PS_CONFIG_DSFLOW_RPT_REQ_STRU */

    /* ^DWINS */
    ID_MSG_TAF_PS_CONFIG_NBNS_FUNCTION_REQ                  = TAF_PS_MSG_ID_BASE + 0x0108,  /* _H2ASN_MsgChoice TAF_PS_CONFIG_NBNS_FUNCTION_REQ_STRU */

    /* ^AUTHDATA */
    ID_MSG_TAF_PS_SET_AUTHDATA_INFO_REQ                     = TAF_PS_MSG_ID_BASE + 0x0109,  /* _H2ASN_MsgChoice TAF_PS_SET_AUTHDATA_INFO_REQ_STRU */
    ID_MSG_TAF_PS_GET_AUTHDATA_INFO_REQ                     = TAF_PS_MSG_ID_BASE + 0x010A,  /* _H2ASN_MsgChoice TAF_PS_GET_AUTHDATA_INFO_REQ_STRU */

    /* ^DNSQUERY */
    ID_MSG_TAF_PS_GET_NEGOTIATION_DNS_REQ                   = TAF_PS_MSG_ID_BASE + 0x010B,  /* _H2ASN_MsgChoice TAF_PS_GET_NEGOTIATION_DNS_REQ_STRU */

    /* ^CGAUTH */
    ID_MSG_TAF_PS_SET_PDP_AUTH_INFO_REQ                     = TAF_PS_MSG_ID_BASE + 0x010C,  /* _H2ASN_MsgChoice TAF_PS_SET_PDP_AUTH_INFO_REQ_STRU */
    ID_MSG_TAF_PS_GET_PDP_AUTH_INFO_REQ                     = TAF_PS_MSG_ID_BASE + 0x010D,  /* _H2ASN_MsgChoice TAF_PS_GET_PDP_AUTH_INFO_REQ_STRU */

    /* ^CGDNS */
    ID_MSG_TAF_PS_SET_PDP_DNS_INFO_REQ                      = TAF_PS_MSG_ID_BASE + 0x010E,  /* _H2ASN_MsgChoice TAF_PS_SET_PDP_DNS_INFO_REQ_STRU */
    ID_MSG_TAF_PS_GET_PDP_DNS_INFO_REQ                      = TAF_PS_MSG_ID_BASE + 0x010F,  /* _H2ASN_MsgChoice TAF_PS_GET_PDP_DNS_INFO_REQ_STRU */

    /* ^TRIG */
    ID_MSG_TAF_PS_TRIG_GPRS_DATA_REQ                        = TAF_PS_MSG_ID_BASE + 0x0110,  /* _H2ASN_MsgChoice TAF_PS_TRIG_GPRS_DATA_REQ_STRU */

    /*^LTECS*/
    ID_MSG_TAF_PS_GET_LTE_CS_REQ                            = TAF_PS_MSG_ID_BASE + 0x0111,  /* _H2ASN_MsgChoice TAF_PS_LTECS_REQ_STRU */

    /* ^PDPROFMOD */
    ID_MSG_TAF_PS_SET_PDPROFMOD_INFO_REQ                    = TAF_PS_MSG_ID_BASE + 0x0112,  /* _H2ASN_MsgChoice TAF_PS_SET_PROFILE_INFO_REQ_STRU */

    /* ^CEMODE */
    ID_MSG_TAF_PS_GET_CEMODE_REQ                            = TAF_PS_MSG_ID_BASE + 0x0113,  /* _H2ASN_MsgChoice TAF_PS_CEMODE_REQ_STRU */

    /* ????????????SDF???? */
    ID_MSG_TAF_PS_GET_CID_SDF_REQ                           = TAF_PS_MSG_ID_BASE + 0x0114,  /* _H2ASN_MsgChoice TAF_SDF_PARA_QUERY_INFO_STRU */

    /* ????????????CID */
    ID_MSG_TAF_PS_GET_UNUSED_CID_REQ                        = TAF_PS_MSG_ID_BASE + 0x0115,  /* _H2ASN_MsgChoice */

    ID_MSG_TAF_PS_SET_CQOS_PRI_REQ                          = TAF_PS_MSG_ID_BASE + 0x0116,  /* _H2ASN_MsgChoice TAF_PS_SET_1X_CQOS_PRI_REQ_STRU */

    /* CDMA????????DORMANT???????? */
    ID_MSG_TAF_PS_CALL_ENTER_DORMANT_IND                    = TAF_PS_MSG_ID_BASE + 0x0117,  /* _H2ASN_MsgChoice TAF_PS_CALL_ENTER_DORMANT_IND_STRU */

    ID_MSG_TAF_PS_HAI_CHANGE_IND                            = TAF_PS_MSG_ID_BASE + 0x0118,  /* _H2ASN_MsgChoice TAF_PS_HAI_CHANGE_IND_STRU */

    /* ^APDSFLOWRPT */
    ID_MSG_TAF_PS_SET_APDSFLOW_RPT_CFG_REQ                  = TAF_PS_MSG_ID_BASE + 0x0119,  /* _H2ASN_MsgChoice TAF_PS_SET_APDSFLOW_RPT_CFG_REQ_STRU */
    ID_MSG_TAF_PS_GET_APDSFLOW_RPT_CFG_REQ                  = TAF_PS_MSG_ID_BASE + 0x011A,  /* _H2ASN_MsgChoice TAF_PS_GET_APDSFLOW_RPT_CFG_REQ_STRU */

    ID_MSG_TAF_PS_SET_DSFLOW_NV_WRITE_CFG_REQ               = TAF_PS_MSG_ID_BASE + 0x011B,  /* _H2ASN_MsgChoice TAF_PS_SET_DSFLOW_NV_WRITE_CFG_REQ_STRU */
    ID_MSG_TAF_PS_GET_DSFLOW_NV_WRITE_CFG_REQ               = TAF_PS_MSG_ID_BASE + 0x011C,  /* _H2ASN_MsgChoice TAF_PS_GET_DSFLOW_NV_WRITE_CFG_REQ_STRU */

    /* +CTA*/
    ID_MSG_TAF_PS_SET_CTA_INFO_REQ                          = TAF_PS_MSG_ID_BASE + 0x011D,  /* _H2ASN_MsgChoice TAF_PS_SET_CTA_INFO_REQ_STRU */
    ID_MSG_TAF_PS_GET_CTA_INFO_REQ                          = TAF_PS_MSG_ID_BASE + 0x011E,  /* _H2ASN_MsgChoice TAF_PS_GET_1X_CTA_INFO_REQ_STRU */

    ID_MSG_TAF_PS_SET_CDMA_DIAL_MODE_REQ                    = TAF_PS_MSG_ID_BASE + 0x011F,  /* _H2ASN_MsgChoice TAF_PS_CDATA_DIAL_MODE_REQ_STRU */

    ID_MSG_TAF_PS_GET_CGMTU_VALUE_REQ                       = TAF_PS_MSG_ID_BASE + 0x0120,  /* _H2ASN_MsgChoice TAF_PS_GET_CGMTU_VALUE_REQ_STRU */

    /* ^IMSPDPCFG */
    ID_MSG_TAF_PS_SET_IMS_PDP_CFG_REQ                       = TAF_PS_MSG_ID_BASE + 0x0121,  /* _H2ASN_MsgChoice TAF_PS_SET_IMS_PDP_CFG_REQ_STRU */

    /* ^CDORMTIMER */
    ID_MSG_TAF_PS_SET_1X_DORM_TIMER_REQ                     = TAF_PS_MSG_ID_BASE + 0x0122,  /* _H2ASN_MsgChoice TAF_PS_SET_1X_DORMANT_TIMER_REQ_STRU */
    ID_MSG_TAF_PS_GET_1X_DORM_TIEMR_REQ                     = TAF_PS_MSG_ID_BASE + 0X0123,  /* _H2ASN_MsgChoice TAF_PS_GET_1X_DORMANT_TIMER_REQ_STRU */

    ID_MSG_TAF_PS_BUTT

};
typedef VOS_UINT32 TAF_PS_MSG_ID_ENUM_UINT32;

/*****************************************************************************
 ????????: TAF_PS_EVT_ID_ENUM
 ????????: TAF??APP??????????????

 ????????      :
  1.??    ??   : 2011??10??19??
    ??    ??   : A00165503
    ????????   : ????????
*****************************************************************************/
enum TAF_PS_EVT_ID_ENUM
{
    /* PS CALL */
    ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_CNF                     = TAF_PS_EVT_ID_BASE + 0x0001,           /* _H2ASN_MsgChoice TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU           */
    ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ                     = TAF_PS_EVT_ID_BASE + 0x0002,           /* _H2ASN_MsgChoice TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU           */
    ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_IND                     = TAF_PS_EVT_ID_BASE + 0x0003,           /* _H2ASN_MsgChoice TAF_PS_CALL_PDP_ACTIVATE_IND_STRU           */
    ID_EVT_TAF_PS_CALL_PDP_MANAGE_IND                       = TAF_PS_EVT_ID_BASE + 0x0004,           /* _H2ASN_MsgChoice TAF_PS_CALL_PDP_MANAGE_IND_STRU             */
    ID_EVT_TAF_PS_CALL_PDP_MODIFY_CNF                       = TAF_PS_EVT_ID_BASE + 0x0005,           /* _H2ASN_MsgChoice TAF_PS_CALL_PDP_MODIFY_CNF_STRU             */
    ID_EVT_TAF_PS_CALL_PDP_MODIFY_REJ                       = TAF_PS_EVT_ID_BASE + 0x0006,           /* _H2ASN_MsgChoice TAF_PS_CALL_PDP_MODIFY_REJ_STRU             */
    ID_EVT_TAF_PS_CALL_PDP_MODIFY_IND                       = TAF_PS_EVT_ID_BASE + 0x0007,           /* _H2ASN_MsgChoice TAF_PS_CALL_PDP_MODIFY_IND_STRU             */
    ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF                   = TAF_PS_EVT_ID_BASE + 0x0008,           /* _H2ASN_MsgChoice TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU         */
    ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND                   = TAF_PS_EVT_ID_BASE + 0x0009,           /* _H2ASN_MsgChoice TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU         */
    ID_EVT_TAF_PS_CALL_PDP_DISCONNECT_IND                   = TAF_PS_EVT_ID_BASE + 0x000A,           /* _H2ASN_MsgChoice TAF_PS_CALL_PDP_PDP_DISCONNECT_IND_STRU     */
    ID_EVT_TAF_PS_CALL_PDP_IPV6_INFO_IND                    = TAF_PS_EVT_ID_BASE + 0x000B,           /* _H2ASN_MsgChoice TAF_PS_IPV6_INFO_IND_STRU                   */
    ID_EVT_TAF_PS_CALL_PDP_RABID_CHANGE_IND                 = TAF_PS_EVT_ID_BASE + 0x000C,           /* _H2ASN_MsgChoice TAF_PS_CALL_PDP_RABID_CHANGE_IND_STRU       */

    ID_EVT_TAF_PS_CALL_ORIG_CNF                             = TAF_PS_EVT_ID_BASE + 0x0031,           /* _H2ASN_MsgChoice TAF_PS_CALL_ORIG_CNF_STRU                   */
    ID_EVT_TAF_PS_CALL_END_CNF                              = TAF_PS_EVT_ID_BASE + 0x0032,           /* _H2ASN_MsgChoice TAF_PS_CALL_END_CNF_STRU                    */
    ID_EVT_TAF_PS_CALL_MODIFY_CNF                           = TAF_PS_EVT_ID_BASE + 0x0033,           /* _H2ASN_MsgChoice TAF_PS_CALL_MODIFY_CNF_STRU                 */
    ID_EVT_TAF_PS_CALL_ANSWER_CNF                           = TAF_PS_EVT_ID_BASE + 0x0034,           /* _H2ASN_MsgChoice TAF_PS_CALL_ANSWER_CNF_STRU                 */
    ID_EVT_TAF_PS_CALL_HANGUP_CNF                           = TAF_PS_EVT_ID_BASE + 0x0035,           /* _H2ASN_MsgChoice TAF_PS_CALL_HANGUP_CNF_STRU                 */

    /* D */
    ID_EVT_TAF_PS_GET_D_GPRS_ACTIVE_TYPE_CNF                = TAF_PS_EVT_ID_BASE + 0x0100,           /* _H2ASN_MsgChoice TAF_PS_GET_D_GPRS_ACTIVE_TYPE_CNF_STRU      */

    /* PPP */
    ID_EVT_TAF_PS_PPP_DIAL_ORIG_CNF                         = TAF_PS_EVT_ID_BASE + 0x0101,           /* _H2ASN_MsgChoice TAF_PS_PPP_DIAL_ORIG_CNF_STRU               */

    /* +CGDCONT */
    ID_EVT_TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_CNF             = TAF_PS_EVT_ID_BASE + 0x0102,           /* _H2ASN_MsgChoice TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_CNF_STRU   */
    ID_EVT_TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_CNF             = TAF_PS_EVT_ID_BASE + 0x0103,           /* _H2ASN_MsgChoice TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_CNF_STRU   */

    /* +CGDSCONT */
    ID_EVT_TAF_PS_SET_SEC_PDP_CONTEXT_INFO_CNF              = TAF_PS_EVT_ID_BASE + 0x0104,           /* _H2ASN_MsgChoice TAF_PS_SET_SEC_PDP_CONTEXT_INFO_CNF_STRU    */
    ID_EVT_TAF_PS_GET_SEC_PDP_CONTEXT_INFO_CNF              = TAF_PS_EVT_ID_BASE + 0x0105,           /* _H2ASN_MsgChoice TAF_PS_GET_SEC_PDP_CONTEXT_INFO_CNF_STRU    */

    /* +CGTFT */
    ID_EVT_TAF_PS_SET_TFT_INFO_CNF                          = TAF_PS_EVT_ID_BASE + 0x0106,           /* _H2ASN_MsgChoice TAF_PS_SET_TFT_INFO_CNF_STRU                */
    ID_EVT_TAF_PS_GET_TFT_INFO_CNF                          = TAF_PS_EVT_ID_BASE + 0x0107,           /* _H2ASN_MsgChoice TAF_PS_GET_TFT_INFO_CNF_STRU                */

    /* +CGQREQ */
    ID_EVT_TAF_PS_SET_GPRS_QOS_INFO_CNF                     = TAF_PS_EVT_ID_BASE + 0x0108,           /* _H2ASN_MsgChoice */
    ID_EVT_TAF_PS_GET_GPRS_QOS_INFO_CNF                     = TAF_PS_EVT_ID_BASE + 0x0109,           /* _H2ASN_MsgChoice */

    /* +CGQMIN */
    ID_EVT_TAF_PS_SET_GPRS_QOS_MIN_INFO_CNF                 = TAF_PS_EVT_ID_BASE + 0x010A,           /* _H2ASN_MsgChoice */
    ID_EVT_TAF_PS_GET_GPRS_QOS_MIN_INFO_CNF                 = TAF_PS_EVT_ID_BASE + 0x010B,           /* _H2ASN_MsgChoice */

    /* +CGEQREQ */
    ID_EVT_TAF_PS_SET_UMTS_QOS_INFO_CNF                     = TAF_PS_EVT_ID_BASE + 0x010C,           /* _H2ASN_MsgChoice TAF_PS_SET_UMTS_QOS_INFO_CNF_STRU           */
    ID_EVT_TAF_PS_GET_UMTS_QOS_INFO_CNF                     = TAF_PS_EVT_ID_BASE + 0x010D,           /* _H2ASN_MsgChoice TAF_PS_GET_UMTS_QOS_INFO_CNF_STRU           */

    /* +CGEQMIN */
    ID_EVT_TAF_PS_SET_UMTS_QOS_MIN_INFO_CNF                 = TAF_PS_EVT_ID_BASE + 0x010E,           /* _H2ASN_MsgChoice TAF_PS_SET_UMTS_QOS_MIN_INFO_CNF_STRU       */
    ID_EVT_TAF_PS_GET_UMTS_QOS_MIN_INFO_CNF                 = TAF_PS_EVT_ID_BASE + 0x010F,           /* _H2ASN_MsgChoice TAF_PS_GET_UMTS_QOS_MIN_INFO_CNF_STRU       */

    /* +CGEQNEG */
    ID_EVT_TAF_PS_GET_DYNAMIC_UMTS_QOS_INFO_CNF             = TAF_PS_EVT_ID_BASE + 0x0110,           /* _H2ASN_MsgChoice TAF_PS_GET_DYNAMIC_UMTS_QOS_INFO_CNF_STRU   */

    /* +CGACT */
    ID_EVT_TAF_PS_SET_PDP_CONTEXT_STATE_CNF                 = TAF_PS_EVT_ID_BASE + 0x0111,           /* _H2ASN_MsgChoice TAF_PS_SET_PDP_STATE_CNF_STRU       */
    ID_EVT_TAF_PS_GET_PDP_CONTEXT_STATE_CNF                 = TAF_PS_EVT_ID_BASE + 0x0112,           /* _H2ASN_MsgChoice TAF_PS_GET_PDP_STATE_CNF_STRU       */

    /* +CGPADDR */
    ID_EVT_TAF_PS_GET_PDP_IP_ADDR_INFO_CNF                  = TAF_PS_EVT_ID_BASE + 0x0113,           /* _H2ASN_MsgChoice TAF_PS_GET_PDP_IP_ADDR_INFO_CNF_STRU        */
    ID_EVT_TAF_PS_GET_PDP_CONTEXT_INFO_CNF                  = TAF_PS_EVT_ID_BASE + 0x0114,           /* _H2ASN_MsgChoice TAF_PS_GET_PDP_CONTEXT_INFO_CNF_STRU        */

    /* +CGAUTO */
    ID_EVT_TAF_PS_SET_ANSWER_MODE_INFO_CNF                  = TAF_PS_EVT_ID_BASE + 0x0115,           /* _H2ASN_MsgChoice TAF_PS_SET_ANSWER_MODE_INFO_CNF_STRU        */
    ID_EVT_TAF_PS_GET_ANSWER_MODE_INFO_CNF                  = TAF_PS_EVT_ID_BASE + 0x0116,           /* _H2ASN_MsgChoice TAF_PS_GET_ANSWER_MODE_INFO_CNF_STRU        */

    /* +CGCONTRDP */
    ID_EVT_TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_CNF     = TAF_PS_EVT_ID_BASE + 0x0117,           /* _H2ASN_MsgChoice TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_CNF_STRU */

    /* +CGSCONTRDP */
    ID_EVT_TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_CNF      = TAF_PS_EVT_ID_BASE + 0x0118,           /* _H2ASN_MsgChoice TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_CNF_STRU */

    /* +CGTFTRDP */
    ID_EVT_TAF_PS_GET_DYNAMIC_TFT_INFO_CNF                  = TAF_PS_EVT_ID_BASE + 0x0119,           /* _H2ASN_MsgChoice TAF_PS_GET_DYNAMIC_TFT_INFO_CNF_STRU        */

    /* +CGEQOS */
    ID_EVT_TAF_PS_SET_EPS_QOS_INFO_CNF                      = TAF_PS_EVT_ID_BASE + 0x011A,           /* _H2ASN_MsgChoice TAF_PS_SET_EPS_QOS_INFO_CNF_STRU            */
    ID_EVT_TAF_PS_GET_EPS_QOS_INFO_CNF                      = TAF_PS_EVT_ID_BASE + 0x011B,           /* _H2ASN_MsgChoice TAF_PS_GET_EPS_QOS_INFO_CNF_STRU            */

    /* +CGEQOSRDP */
    ID_EVT_TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_CNF              = TAF_PS_EVT_ID_BASE + 0x011C,           /* _H2ASN_MsgChoice TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_CNF_STRU    */

    /* ^DSFLOWQRY */
    ID_EVT_TAF_PS_GET_DSFLOW_INFO_CNF                       = TAF_PS_EVT_ID_BASE + 0x011D,           /* _H2ASN_MsgChoice TAF_PS_GET_DSFLOW_INFO_CNF_STRU             */

    /* ^DSFLOWCLR */
    ID_EVT_TAF_PS_CLEAR_DSFLOW_CNF                          = TAF_PS_EVT_ID_BASE + 0x011E,           /* _H2ASN_MsgChoice TAF_PS_CLEAR_DSFLOW_CNF_STRU                */

    /* ^DSFLOWRPT */
    ID_EVT_TAF_PS_CONFIG_DSFLOW_RPT_CNF                     = TAF_PS_EVT_ID_BASE + 0x011F,           /* _H2ASN_MsgChoice TAF_PS_CONFIG_DSFLOW_RPT_CNF_STRU           */

    /* ^DSFLOWRPT */
    ID_EVT_TAF_PS_REPORT_DSFLOW_IND                         = TAF_PS_EVT_ID_BASE + 0x0120,           /* _H2ASN_MsgChoice TAF_PS_REPORT_DSFLOW_IND_STRU               */

    /* ^CGAUTH */
    ID_EVT_TAF_PS_SET_PDP_AUTH_INFO_CNF                     = TAF_PS_EVT_ID_BASE + 0x0121,           /* _H2ASN_MsgChoice TAF_PS_SET_PDP_AUTH_INFO_CNF_STRU           */
    ID_EVT_TAF_PS_GET_PDP_AUTH_INFO_CNF                     = TAF_PS_EVT_ID_BASE + 0x0122,           /* _H2ASN_MsgChoice TAF_PS_GET_PDP_AUTH_INFO_CNF_STRU           */

    /* ^CGDNS */
    ID_EVT_TAF_PS_SET_PDP_DNS_INFO_CNF                      = TAF_PS_EVT_ID_BASE + 0x0123,           /* _H2ASN_MsgChoice TAF_PS_SET_PDP_DNS_INFO_CNF_STRU            */
    ID_EVT_TAF_PS_GET_PDP_DNS_INFO_CNF                      = TAF_PS_EVT_ID_BASE + 0x0124,           /* _H2ASN_MsgChoice TAF_PS_GET_PDP_DNS_INFO_CNF_STRU            */

    /* ^TRIG */
    ID_EVT_TAF_PS_TRIG_GPRS_DATA_CNF                        = TAF_PS_EVT_ID_BASE + 0x0125,           /* _H2ASN_MsgChoice TAF_PS_TRIG_GPRS_DATA_CNF_STRU              */

    /* ^DWINS */
    ID_EVT_TAF_PS_CONFIG_NBNS_FUNCTION_CNF                  = TAF_PS_EVT_ID_BASE + 0x0126,           /* _H2ASN_MsgChoice TAF_PS_CONFIG_NBNS_FUNCTION_CNF_STRU        */

    /* ^AUTHDATA */
    ID_EVT_TAF_PS_SET_AUTHDATA_INFO_CNF                     = TAF_PS_EVT_ID_BASE + 0x0127,           /* _H2ASN_MsgChoice TAF_PS_SET_AUTHDATA_INFO_CNF_STRU           */
    ID_EVT_TAF_PS_GET_AUTHDATA_INFO_CNF                     = TAF_PS_EVT_ID_BASE + 0x0128,           /* _H2ASN_MsgChoice TAF_PS_GET_AUTHDATA_INFO_CNF_STRU           */

    /* ^DNSQUERY */
    ID_EVT_TAF_PS_GET_NEGOTIATION_DNS_CNF                   = TAF_PS_EVT_ID_BASE + 0x0129,           /* _H2ASN_MsgChoice TAF_PS_GET_NEGOTIATION_DNS_CNF_STRU         */

    /* ^LTECS */
    ID_EVT_TAF_PS_LTECS_INFO_CNF                            = TAF_PS_EVT_ID_BASE + 0x012A,           /* _H2ASN_MsgChoice TAF_PS_LTECS_CNF_STRU                       */

    /* ^PDPROFMOD */
    ID_EVT_TAF_PS_SET_PDP_PROF_INFO_CNF                     = TAF_PS_EVT_ID_BASE + 0x012B,           /* _H2ASN_MsgChoice TAF_PS_SET_PDP_PROF_INFO_CNF_STRU           */

    /* +CEMODE */
    ID_EVT_TAF_PS_CEMODE_INFO_CNF                           = TAF_PS_EVT_ID_BASE + 0x012C,           /* _H2ASN_MsgChoice TAF_PS_CEMODE_CNF_STRU                      */

    /* ????????????SDF???? */
    ID_EVT_TAF_PS_GET_CID_SDF_CNF                           = TAF_PS_EVT_ID_BASE + 0x012D,           /* _H2ASN_MsgChoice TAF_PS_SDF_INFO_CNF_STRU                    */

    /* ^CQOSPRI */
    ID_EVT_TAF_PS_SET_CQOS_PRI_CNF                          = TAF_PS_EVT_ID_BASE + 0x012E,           /* _H2ASN_MsgChoice TAF_PS_SET_CQOS_PRI_CNF_STRU                */

    /* ^APDSFLOWRPT */
    ID_EVT_TAF_PS_SET_APDSFLOW_RPT_CFG_CNF                  = TAF_PS_EVT_ID_BASE + 0x012F,           /* _H2ASN_MsgChoice TAF_PS_SET_APDSFLOW_RPT_CFG_CNF_STRU */
    ID_EVT_TAF_PS_GET_APDSFLOW_RPT_CFG_CNF                  = TAF_PS_EVT_ID_BASE + 0x0130,           /* _H2ASN_MsgChoice TAF_PS_GET_APDSFLOW_RPT_CFG_CNF_STRU */
    ID_EVT_TAF_PS_APDSFLOW_REPORT_IND                       = TAF_PS_EVT_ID_BASE + 0x0131,           /* _H2ASN_MsgChoice TAF_PS_APDSFLOW_REPORT_IND_STRU */

    ID_EVT_TAF_PS_SET_DSFLOW_NV_WRITE_CFG_CNF               = TAF_PS_EVT_ID_BASE + 0x0132,           /* _H2ASN_MsgChoice TAF_PS_SET_DSFLOW_NV_WRITE_CFG_CNF_STRU */
    ID_EVT_TAF_PS_GET_DSFLOW_NV_WRITE_CFG_CNF               = TAF_PS_EVT_ID_BASE + 0x0133,           /* _H2ASN_MsgChoice TAF_PS_GET_DSFLOW_NV_WRITE_CFG_CNF_STRU */

    /* +CTA */
    ID_EVT_TAF_PS_SET_CTA_INFO_CNF                          = TAF_PS_EVT_ID_BASE + 0x0134,           /* _H2ASN_MsgChoice TAF_PS_SET_CTA_INFO_CNF_STRU */
    ID_EVT_TAF_PS_GET_CTA_INFO_CNF                          = TAF_PS_EVT_ID_BASE + 0x0135,           /* _H2ASN_MsgChoice TAF_PS_GET_CTA_INFO_CNF_STRU */

    /* +CRM */
    ID_EVT_TAF_PS_SET_CDMA_DIAL_MODE_CNF                    = TAF_PS_EVT_ID_BASE + 0x0136,           /* _H2ASN_MsgChoice TAF_PS_CDATA_DIAL_MODE_CNF_STRU                */

    ID_EVT_TAF_PS_GET_CGMTU_VALUE_CNF                       = TAF_PS_EVT_ID_BASE + 0x0137,          /* _H2ASN_MsgChoice TAF_PS_GET_CGMTU_VALUE_CNF_STRU                */
    ID_EVT_TAF_PS_CGMTU_VALUE_CHG_IND                       = TAF_PS_EVT_ID_BASE + 0x0138,          /* _H2ASN_MsgChoice TAF_PS_CGMTU_VALUE_CHG_IND_STRU                */

    /* ???????? */
    /* APS->IMSA????SRVCC CANCEL */
    ID_EVT_TAF_PS_SRVCC_CANCEL_NOTIFY_IND                   = TAF_PS_EVT_ID_BASE + 0x0200,           /* _H2ASN_MsgChoice TAF_SRVCC_CANCEL_NOTIFY_IND_STRU */

    ID_EVT_TAF_PS_SET_IMS_PDP_CFG_CNF                       = TAF_PS_EVT_ID_BASE + 0x0201,           /* _H2ASN_MsgChoice TAF_PS_SET_IMS_PDP_CFG_CNF_STRU */

    ID_EVT_TAF_PS_SET_1X_DORM_TIMER_CNF                     = TAF_PS_EVT_ID_BASE + 0x0202,           /* _H2ASN_MsgChoice TAF_PS_SET_1X_DORM_TIMER_CNF_STRU */
    ID_EVT_TAF_PS_GET_1X_DORM_TIMER_CNF                     = TAF_PS_EVT_ID_BASE + 0x0203,           /* _H2ASN_MsgChoice TAF_PS_GET_1X_DORM_TIMER_CNF_STRU */

    ID_EVT_TAF_PS_BUTT
};
typedef VOS_UINT32 TAF_PS_EVT_ID_ENUM_UINT32;


/*****************************************************************************
 ????????: TAF_PS_CAUSE_ENUM
 ????????: TAF??????PS????????????

 ????????      :
  1.??    ??   : 2012??8??23??
    ??    ??   : A00165503
    ????????   : ????????
*****************************************************************************/
enum TAF_PS_CAUSE_ENUM
{
    /*----------------------------------------------------------------------
       TAF????????????????, ????????[0x0000, 0x007F]
    *---------------------------------------------------------------------*/
    TAF_PS_CAUSE_SUCCESS                                    = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 0),
    TAF_PS_CAUSE_INVALID_PARAMETER                          = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 1),
    TAF_PS_CAUSE_CID_INVALID                                = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 2),
    TAF_PS_CAUSE_PDP_ACTIVATE_LIMIT                         = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 3),
    TAF_PS_CAUSE_SIM_INVALID                                = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 4),
    TAF_PS_CAUSE_APS_TIME_OUT                               = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 5),
    TAF_PS_CAUSE_OPERATION_CONFLICT                         = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 6),
    TAF_PS_CAUSE_XCC_TIME_OUT                               = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 7),
    TAF_PS_CAUSE_PPP_TIME_OUT                               = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 8),
    TAF_PS_CAUSE_PPP_NEGOTIATE_FAIL                         = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 9),
    TAF_PS_CAUSE_1X_NO_SERVICE                              = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 10),
    TAF_PS_CAUSE_HRPD_NO_SERVICE                            = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 11),
    TAF_PS_CAUSE_HSM_TIME_OUT                               = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 12),
    TAF_PS_CAUSE_IP_ADDRESS_CHANGE                          = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 13),
    TAF_PS_CAUSE_EHSM_TIME_OUT                              = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 14),
    TAF_PS_CAUSE_RAT_TYPE_CHANGE                            = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 15),
    TAF_PS_CAUSE_DHCP_TIME_OUT                              = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 16),
    TAF_PS_CAUSE_PDP_TYPE_IPV4_ONLY_ALLOWED                 = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 17),
    TAF_PS_CAUSE_PDP_TYPE_IPV6_ONLY_ALLOWED                 = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 18),
    TAF_PS_CAUSE_PPP_NW_DISC                                = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 19),
    TAF_PS_CAUSE_UNSUPPORT_PCSCF                            = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 20),
    TAF_PS_CAUSE_SYSCFG_MODE_CHANGE                         = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 21),

    TAF_PS_CAUSE_L2C_HANDOVER_FAIL                          = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 22),
    TAF_PS_CAUSE_NOT_SUPPORT_CONCURRENT                     = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 23),
    TAF_PS_CAUSE_READ_3GPD_FILE                             = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 24),
    TAF_PS_CAUSE_1X_HRPD_NOT_SUPPORT_MUTI_PDN               = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 25),
    TAF_PS_CAUSE_BACKOFF_ALG_NOT_ALLOWED                    = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 26),
    TAF_PS_CAUSE_1X_DO_NO_SERVICE                           = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 27),
    TAF_PS_CAUSE_IP_TYPE_CHANGE                             = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 32),

    TAF_PS_CAUSE_UNKNOWN                                    = (TAF_PS_CAUSE_APS_SECTION_BEGIN + 127),

    /*----------------------------------------------------------------------
       TAF??????SM??????????, ????????[0x0080, 0x00FF]
    *---------------------------------------------------------------------*/
    TAF_PS_CAUSE_SM_CONN_ESTABLISH_MAX_TIME_OUT             = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 1),
    TAF_PS_CAUSE_SM_MAX_TIME_OUT                            = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 2),
    TAF_PS_CAUSE_SM_INVALID_NSAPI                           = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 3),
    TAF_PS_CAUSE_SM_MODIFY_COLLISION                        = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 4),
    TAF_PS_CAUSE_SM_DUPLICATE                               = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 5),
    TAF_PS_CAUSE_SM_RAB_SETUP_FAILURE                       = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 6),
    TAF_PS_CAUSE_SM_SGSN_VER_PRE_R99                        = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 7),
    TAF_PS_CAUSE_SM_FAILURE                                 = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 8),
    TAF_PS_CAUSE_SM_ERR_UNSPECIFIED_ERROR                   = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 9),
    TAF_PS_CAUSE_SM_ERR_INSUFFICIENT_RESOURCES              = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 10),
    TAF_PS_CAUSE_SM_CALL_CID_INVALID                        = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 11),
    TAF_PS_CAUSE_SM_CALL_CID_ACTIVE                         = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 12),
    TAF_PS_CAUSE_SM_CALL_CID_NOT_MATCH_BEARER               = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 13),
    TAF_PS_CAUSE_SM_BEARER_TYPE_NOT_DEDICATED               = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 14),
    TAF_PS_CAUSE_SM_BEARER_INACTIVE                         = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 15),
    TAF_PS_CAUSE_SM_LINK_CID_INVALID                        = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 16),
    TAF_PS_CAUSE_SM_LINK_BEARER_INACTIVE                    = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 17),
    TAF_PS_CAUSE_SM_APN_LEN_ILLEGAL                         = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 18),
    TAF_PS_CAUSE_SM_APN_SYNTACTICAL_ERROR                   = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 19),
    TAF_PS_CAUSE_SM_AUTH_TYPE_ILLEGAL                       = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 20),
    TAF_PS_CAUSE_SM_USER_NAME_TOO_LONG                      = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 21),
    TAF_PS_CAUSE_SM_USER_PASSWORD_TOO_LONG                  = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 22),
    TAF_PS_CAUSE_SM_ACCESS_NUM_TOO_LONG                     = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 23),
    TAF_PS_CAUSE_SM_CALL_CID_IN_OPERATION                   = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 24),
    TAF_PS_CAUSE_SM_BEARER_TYPE_NOT_DEFAULT                 = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 25),
    TAF_PS_CAUSE_SM_BEARER_TYPE_ILLEGAL                     = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 26),
    TAF_PS_CAUSE_SM_MUST_EXIST_DEFAULT_TYPE_CID             = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 27),
    TAF_PS_CAUSE_SM_PDN_TYPE_ILLEGAL                        = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 28),
    TAF_PS_CAUSE_SM_IPV4_ADDR_ALLOC_TYPE_ILLEGAL            = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 29),
    TAF_PS_CAUSE_SM_SUSPENDED                               = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 30),
    TAF_PS_CAUSE_SM_MULTI_EMERGENCY_NOT_ALLOWED             = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 31),
    TAF_PS_CAUSE_SM_NON_EMERGENCY_NOT_ALLOWED               = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 32),
    TAF_PS_CAUSE_SM_MODIFY_EMERGENCY_NOT_ALLOWED            = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 33),
    TAF_PS_CAUSE_SM_DEDICATED_FOR_EMERGENCY_NOT_ALLOWED     = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 34),
    TAF_PS_CAUSE_SM_BACKOFF_ALG_NOT_ALLOWED                 = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 35),

    TAF_PS_CAUSE_SM_UNKNOWN                                 = (TAF_PS_CAUSE_SM_SECTION_BEGIN + 127),

    /*----------------------------------------------------------------------
       TAF??????SM??????????, ????????[0x0100, 0x01FF]
       ????3GPP????????????????????(E)SM??????????, (E)SM????????????????
       ??????????????????????(0x100)
       (1) SM Cause : Refer to TS 24.008 section 10.5.6.6
       (2) ESM Cause: Refer to TS 24.301 section 9.9.4.4
    *---------------------------------------------------------------------*/
    TAF_PS_CAUSE_SM_NW_OPERATOR_DETERMINED_BARRING          = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 8),
    TAF_PS_CAUSE_SM_NW_MBMS_BC_INSUFFICIENT                 = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 24),
    TAF_PS_CAUSE_SM_NW_LLC_OR_SNDCP_FAILURE                 = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 25),
    TAF_PS_CAUSE_SM_NW_INSUFFICIENT_RESOURCES               = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 26),
    TAF_PS_CAUSE_SM_NW_MISSING_OR_UKNOWN_APN                = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 27),
    TAF_PS_CAUSE_SM_NW_UNKNOWN_PDP_ADDR_OR_TYPE             = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 28),
    TAF_PS_CAUSE_SM_NW_USER_AUTHENTICATION_FAIL             = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 29),
    TAF_PS_CAUSE_SM_NW_ACTIVATION_REJECTED_BY_GGSN_SGW_OR_PGW = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 30),
    TAF_PS_CAUSE_SM_NW_ACTIVATION_REJECTED_UNSPECIFIED      = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 31),
    TAF_PS_CAUSE_SM_NW_SERVICE_OPTION_NOT_SUPPORTED         = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 32),
    TAF_PS_CAUSE_SM_NW_REQUESTED_SERVICE_NOT_SUBSCRIBED     = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 33),
    TAF_PS_CAUSE_SM_NW_SERVICE_OPTION_TEMP_OUT_ORDER        = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 34),
    TAF_PS_CAUSE_SM_NW_NSAPI_ALREADY_USED                   = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 35),
    TAF_PS_CAUSE_SM_NW_REGULAR_DEACTIVATION                 = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 36),
    TAF_PS_CAUSE_SM_NW_QOS_NOT_ACCEPTED                     = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 37),
    TAF_PS_CAUSE_SM_NW_NETWORK_FAILURE                      = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 38),
    TAF_PS_CAUSE_SM_NW_REACTIVATION_REQUESTED               = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 39),
    TAF_PS_CAUSE_SM_NW_FEATURE_NOT_SUPPORT                  = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 40),
    TAF_PS_CAUSE_SM_NW_SEMANTIC_ERR_IN_TFT                  = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 41),
    TAF_PS_CAUSE_SM_NW_SYNTACTIC_ERR_IN_TFT                 = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 42),
    TAF_PS_CAUSE_SM_NW_UKNOWN_PDP_CONTEXT                   = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 43),
    TAF_PS_CAUSE_SM_NW_SEMANTIC_ERR_IN_PACKET_FILTER        = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 44),
    TAF_PS_CAUSE_SM_NW_SYNCTACTIC_ERR_IN_PACKET_FILTER      = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 45),
    TAF_PS_CAUSE_SM_NW_PDP_CONTEXT_WITHOUT_TFT_ACTIVATED    = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 46),
    TAF_PS_CAUSE_SM_NW_MULTICAST_GROUP_MEMBERHHSHIP_TIMEOUT = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 47),
    TAF_PS_CAUSE_SM_NW_REQUEST_REJECTED_BCM_VIOLATION       = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 48),
    TAF_PS_CAUSE_SM_NW_LAST_PDN_DISCONN_NOT_ALLOWED         = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 49),
    TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV4_ONLY_ALLOWED           = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 50),
    TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV6_ONLY_ALLOWED           = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 51),
    TAF_PS_CAUSE_SM_NW_SINGLE_ADDR_BEARERS_ONLY_ALLOWED     = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 52),
    TAF_PS_CAUSE_SM_NW_INFORMATION_NOT_RECEIVED             = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 53),
    TAF_PS_CAUSE_SM_NW_PDN_CONNECTION_DOES_NOT_EXIST        = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 54),
    TAF_PS_CAUSE_SM_NW_SAME_APN_MULTI_PDN_CONNECTION_NOT_ALLOWED = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 55),
    TAF_PS_CAUSE_SM_NW_COLLISION_WITH_NW_INITIATED_REQUEST  = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 56),
    TAF_PS_CAUSE_SM_NW_UNSUPPORTED_QCI_VALUE                = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 59),
    TAF_PS_CAUSE_SM_NW_BEARER_HANDLING_NOT_SUPPORTED        = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 60),
    TAF_PS_CAUSE_SM_NW_INVALID_TI                           = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 81),
    TAF_PS_CAUSE_SM_NW_SEMANTICALLY_INCORRECT_MESSAGE       = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 95),
    TAF_PS_CAUSE_SM_NW_INVALID_MANDATORY_INFO               = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 96),
    TAF_PS_CAUSE_SM_NW_MSG_TYPE_NON_EXISTENT                = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 97),
    TAF_PS_CAUSE_SM_NW_MSG_TYPE_NOT_COMPATIBLE              = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 98),
    TAF_PS_CAUSE_SM_NW_IE_NON_EXISTENT                      = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 99),
    TAF_PS_CAUSE_SM_NW_CONDITIONAL_IE_ERR                   = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 100),
    TAF_PS_CAUSE_SM_NW_MSG_NOT_COMPATIBLE                   = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 101),
    TAF_PS_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED             = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 111),
    TAF_PS_CAUSE_SM_NW_APN_RESTRICTION_INCOMPATIBLE         = (TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 112),

    /*----------------------------------------------------------------------
       TAF??????GMM??????????, ????????[0x0200, 0x02FF]
    *---------------------------------------------------------------------*/
    TAF_PS_CAUSE_GMM_GPRS_NOT_SUPPORT                       = (TAF_PS_CAUSE_GMM_SECTION_BEGIN + 1),
    TAF_PS_CAUSE_GMM_FORBID_LA                              = (TAF_PS_CAUSE_GMM_SECTION_BEGIN + 2),
    TAF_PS_CAUSE_GMM_AUTHENTICATION_FAIL                    = (TAF_PS_CAUSE_GMM_SECTION_BEGIN + 3),
    TAF_PS_CAUSE_GMM_PS_DETACH                              = (TAF_PS_CAUSE_GMM_SECTION_BEGIN + 4),
    TAF_PS_CAUSE_GMM_ACCESS_BARRED                          = (TAF_PS_CAUSE_GMM_SECTION_BEGIN + 5),
    TAF_PS_CAUSE_GMM_NO_PDP_CONTEXT                         = (TAF_PS_CAUSE_GMM_SECTION_BEGIN + 6),
    TAF_PS_CAUSE_GMM_ATTACH_MAX_TIMES                       = (TAF_PS_CAUSE_GMM_SECTION_BEGIN + 7),
    TAF_PS_CAUSE_GMM_RRC_EST_FAIL                           = (TAF_PS_CAUSE_GMM_SECTION_BEGIN + 8),
    TAF_PS_CAUSE_GMM_T3310_EXPIRED                          = (TAF_PS_CAUSE_GMM_SECTION_BEGIN + 9),
    TAF_PS_CAUSE_GMM_T3317_EXPIRED                          = (TAF_PS_CAUSE_GMM_SECTION_BEGIN + 10),
    TAF_PS_CAUSE_GMM_TIMER_SIGNALING_PROTECT_EXPIRED        = (TAF_PS_CAUSE_GMM_SECTION_BEGIN + 11),
    TAF_PS_CAUSE_GMM_NULL                                   = (TAF_PS_CAUSE_GMM_SECTION_BEGIN + 12),
    TAF_PS_CAUSE_GMM_DETACH_NOT_REATTACH                    = (TAF_PS_CAUSE_GMM_SECTION_BEGIN + 13),
    TAF_PS_CAUSE_GMM_UNKNOWN                                = (TAF_PS_CAUSE_GMM_SECTION_BEGIN + 127),

    /*----------------------------------------------------------------------
       TAF??????GMM??????????, ????????[0x0300, 0x03FF]
       ????3GPP????????????????????GMM??????????, ??????????GMM??????????
       ????????????????????????????????(0x100)
       Gmm Cause: Refer to TS 24.008 section 10.5.5.14
    *---------------------------------------------------------------------*/
    TAF_PS_CAUSE_GMM_NW_IMSI_UNKNOWN_IN_HLR                 = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 2),
    TAF_PS_CAUSE_GMM_NW_ILLEGAL_MS                          = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 3),
    TAF_PS_CAUSE_GMM_NW_IMSI_NOT_ACCEPTED                   = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 5),
    TAF_PS_CAUSE_GMM_NW_ILLEGAL_ME                          = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 6),
    TAF_PS_CAUSE_GMM_NW_GPRS_SERV_NOT_ALLOW                 = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 7),
    TAF_PS_CAUSE_GMM_NW_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 8),
    TAF_PS_CAUSE_GMM_NW_MS_ID_NOT_DERIVED                   = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 9),
    TAF_PS_CAUSE_GMM_NW_IMPLICIT_DETACHED                   = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 10),
    TAF_PS_CAUSE_GMM_NW_PLMN_NOT_ALLOW                      = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 11),
    TAF_PS_CAUSE_GMM_NW_LA_NOT_ALLOW                        = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 12),
    TAF_PS_CAUSE_GMM_NW_ROAMING_NOT_ALLOW_IN_LA             = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 13),
    TAF_PS_CAUSE_GMM_NW_GPRS_SERV_NOT_ALLOW_IN_PLMN         = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 14),
    TAF_PS_CAUSE_GMM_NW_NO_SUITABL_CELL                     = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 15),
    TAF_PS_CAUSE_GMM_NW_MSC_UNREACHABLE                     = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 16),
    TAF_PS_CAUSE_GMM_NW_NETWORK_FAILURE                     = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 17),
    TAF_PS_CAUSE_GMM_NW_MAC_FAILURE                         = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 20),
    TAF_PS_CAUSE_GMM_NW_SYNCH_FAILURE                       = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 21),
    TAF_PS_CAUSE_GMM_NW_PROCEDURE_CONGESTION                = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 22),
    TAF_PS_CAUSE_GMM_NW_GSM_AUT_UNACCEPTABLE                = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 23),
    TAF_PS_CAUSE_GMM_NW_NOT_AUTHORIZED_FOR_THIS_CSG         = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 25),
    TAF_PS_CAUSE_GMM_NW_NO_PDP_CONTEXT_ACT                  = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 40),
    TAF_PS_CAUSE_GMM_NW_RETRY_UPON_ENTRY_CELL               = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 60),
    TAF_PS_CAUSE_GMM_NW_SEMANTICALLY_INCORRECT_MSG          = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 95),
    TAF_PS_CAUSE_GMM_NW_INVALID_MANDATORY_INF               = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 96),
    TAF_PS_CAUSE_GMM_NW_MSG_NONEXIST_NOTIMPLEMENTE          = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 97),
    TAF_PS_CAUSE_GMM_NW_MSG_TYPE_NOT_COMPATIBLE             = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 98),
    TAF_PS_CAUSE_GMM_NW_IE_NONEXIST_NOTIMPLEMENTED          = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 99),
    TAF_PS_CAUSE_GMM_NW_CONDITIONAL_IE_ERROR                = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 100),
    TAF_PS_CAUSE_GMM_NW_MSG_NOT_COMPATIBLE                  = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 101),
    TAF_PS_CAUSE_GMM_NW_PROTOCOL_ERROR                      = (TAF_PS_CAUSE_GMM_NW_SECTION_BEGIN + 111),

    /*----------------------------------------------------------------------
       TAF??????CDMA 1X??????????, ????????[0x400, 0x04FF]
       ????????????????????????????????(0x400)
    *---------------------------------------------------------------------*/
    TAF_PS_CAUSE_XCC_OTHER_SERVICE_IN_TCH                   = (TAF_PS_CAUSE_XCC_SECTION_BEGIN + 1),
    TAF_PS_CAUSE_XCC_CCS_NOT_SUPPORT                        = (TAF_PS_CAUSE_XCC_SECTION_BEGIN + 2),
    TAF_PS_CAUSE_XCC_CONNECT_ORDER_ACK_FAILURE              = (TAF_PS_CAUSE_XCC_SECTION_BEGIN + 3),
    TAF_PS_CAUSE_XCC_INCOMING_RSP_TIME_OUT                  = (TAF_PS_CAUSE_XCC_SECTION_BEGIN + 4),
    TAF_PS_CAUSE_XCC_L2_ACK_TIME_OUT                        = (TAF_PS_CAUSE_XCC_SECTION_BEGIN + 5),
    TAF_PS_CAUSE_XCC_POWER_DOWN_IND                         = (TAF_PS_CAUSE_XCC_SECTION_BEGIN + 6),
    TAF_PS_CAUSE_XCC_CONNID_NOT_FOUND                       = (TAF_PS_CAUSE_XCC_SECTION_BEGIN + 7),
    TAF_PS_CAUSE_XCC_ACCESS_CNF_TIMEOUT                     = (TAF_PS_CAUSE_XCC_SECTION_BEGIN + 8),
    TAF_PS_CAUSE_XCC_ACCESS_TCH_TIMEOUT                     = (TAF_PS_CAUSE_XCC_SECTION_BEGIN + 9),
    TAF_PS_CAUSE_XCC_T53M_TIME_OUT                          = (TAF_PS_CAUSE_XCC_SECTION_BEGIN + 10),
    TAF_PS_CAUSE_XCC_XCALL_HANGUP                           = (TAF_PS_CAUSE_XCC_SECTION_BEGIN + 11),
    TAF_PS_CAUSE_XCC_CALL_NOT_ALLOWED                       = (TAF_PS_CAUSE_XCC_SECTION_BEGIN + 12),
    TAF_PS_CAUSE_XCC_ABNORMAL_STATE                         = (TAF_PS_CAUSE_XCC_SECTION_BEGIN + 13),
    TAF_PS_CAUSE_XCC_ENCODE_FAIL                            = (TAF_PS_CAUSE_XCC_SECTION_BEGIN + 14),
    TAF_PS_CAUSE_XCC_WAIT_L2_ACK_CALL_RELEASE               = (TAF_PS_CAUSE_XCC_SECTION_BEGIN + 15),
    TAF_PS_CAUSE_XCC_CANNOT_FIND_CALL_INSTANCE              = (TAF_PS_CAUSE_XCC_SECTION_BEGIN + 16),
    TAF_PS_CAUSE_XCC_ABORTED_BY_RECEIVED_MO_CALL            = (TAF_PS_CAUSE_XCC_SECTION_BEGIN + 17),
    TAF_PS_CAUSE_XCC_ABORTED_BY_RECEIVED_MT_CALL            = (TAF_PS_CAUSE_XCC_SECTION_BEGIN + 18),
    TAF_PS_CAUSE_XCC_CAUSE_L2_ACK_FAIL                      = (TAF_PS_CAUSE_XCC_SECTION_BEGIN + 19),
    TAF_PS_CAUSE_XCC_CAUSE_ALLOC_SRID_FAIL                  = (TAF_PS_CAUSE_XCC_SECTION_BEGIN + 20),
    TAF_PS_CAUSE_XCC_CAUSE_NO_RF                            = (TAF_PS_CAUSE_XCC_SECTION_BEGIN + 21),
    TAF_PS_CAUSE_XCC_CAUSE_PROTOTAL_REV_NOT_SUPPORT         = (TAF_PS_CAUSE_XCC_SECTION_BEGIN + 22),
    TAF_PS_CAUSE_XCC_MT_SMS_IN_TCH                          = (TAF_PS_CAUSE_XCC_SECTION_BEGIN + 23),
    TAF_PS_CAUSE_XCC_EMC_CALL_BACK_MODE                     = (TAF_PS_CAUSE_XCC_SECTION_BEGIN + 24),

    /*----------------------------------------------------------------------
       ??????????????????????PS????????????[0x500, 0x05FF]
       ????3GPP2????????????????????1X??????????, ??????????1X??????????
       ????????????????????????????????(0x500)
    *---------------------------------------------------------------------*/
    TAF_PS_CAUSE_XCC_AS_NO_SERVICE                          = (TAF_PS_CAUSE_XCC_AS_SECTION_BEGIN + 1),
    TAF_PS_CAUSE_XCC_AS_MAX_ACCESS_PROBES                   = (TAF_PS_CAUSE_XCC_AS_SECTION_BEGIN + 2),
    TAF_PS_CAUSE_XCC_AS_REORDER                             = (TAF_PS_CAUSE_XCC_AS_SECTION_BEGIN + 3),
    TAF_PS_CAUSE_XCC_AS_INTERCEPT                           = (TAF_PS_CAUSE_XCC_AS_SECTION_BEGIN + 4),
    TAF_PS_CAUSE_XCC_AS_ACCESS_DENIED                       = (TAF_PS_CAUSE_XCC_AS_SECTION_BEGIN + 5),
    TAF_PS_CAUSE_XCC_AS_LOCK                                = (TAF_PS_CAUSE_XCC_AS_SECTION_BEGIN + 6),
    TAF_PS_CAUSE_XCC_AS_ACCT_BLOCK                          = (TAF_PS_CAUSE_XCC_AS_SECTION_BEGIN + 7),
    TAF_PS_CAUSE_XCC_AS_NDSS                                = (TAF_PS_CAUSE_XCC_AS_SECTION_BEGIN + 8),
    TAF_PS_CAUSE_XCC_AS_REDIRECTION                         = (TAF_PS_CAUSE_XCC_AS_SECTION_BEGIN + 9),
    TAF_PS_CAUSE_XCC_AS_ACCESS_IN_PROGRESS                  = (TAF_PS_CAUSE_XCC_AS_SECTION_BEGIN + 10),
    TAF_PS_CAUSE_XCC_AS_ACCESS_FAIL                         = (TAF_PS_CAUSE_XCC_AS_SECTION_BEGIN + 11),
    TAF_PS_CAUSE_XCC_AS_ABORT                               = (TAF_PS_CAUSE_XCC_AS_SECTION_BEGIN + 12),
    TAF_PS_CAUSE_XCC_AS_SIGNAL_FADE_IN_ACH                  = (TAF_PS_CAUSE_XCC_AS_SECTION_BEGIN + 13),
    TAF_PS_CAUSE_XCC_AS_CHANNEL_ASSIGN_TIMEOUT              = (TAF_PS_CAUSE_XCC_AS_SECTION_BEGIN + 14),
    TAF_PS_CAUSE_XCC_AS_BS_RELEASE                          = (TAF_PS_CAUSE_XCC_AS_SECTION_BEGIN + 15),
    TAF_PS_CAUSE_XCC_AS_NOT_ACCEPT_BY_BS                    = (TAF_PS_CAUSE_XCC_AS_SECTION_BEGIN + 16),
    TAF_PS_CAUSE_XCC_AS_SO_REJ                              = (TAF_PS_CAUSE_XCC_AS_SECTION_BEGIN + 17),
    TAF_PS_CAUSE_XCC_AS_RELEASE_TIME_OUT                    = (TAF_PS_CAUSE_XCC_AS_SECTION_BEGIN + 18),
    TAF_PS_CAUSE_XCC_AS_MS_NORMAL_RELEASE                   = (TAF_PS_CAUSE_XCC_AS_SECTION_BEGIN + 19),
    TAF_PS_CAUSE_XCC_AS_RETRY_FAIL                          = (TAF_PS_CAUSE_XCC_AS_SECTION_BEGIN + 20),
    TAF_PS_CAUSE_XCC_AS_NW_NORMAL_RELEASE                   = (TAF_PS_CAUSE_XCC_AS_SECTION_BEGIN + 21),
    TAF_PS_CAUSE_XCC_AS_SIGNAL_FADE_IN_TCH                  = (TAF_PS_CAUSE_XCC_AS_SECTION_BEGIN + 22),
    TAF_PS_CAUSE_XCC_AS_MS_END                              = (TAF_PS_CAUSE_XCC_AS_SECTION_BEGIN + 23),

    TAF_PS_CAUSE_HSM_AS_CONN_FAIL                           = (TAF_PS_CAUSE_HSM_AS_SECTION_BEGIN + 1),
    TAF_PS_CAUSE_HSM_AS_MAX_ACCESS_PROBES                   = (TAF_PS_CAUSE_HSM_AS_SECTION_BEGIN + 2),
    TAF_PS_CAUSE_HSM_AS_CONNECTION_DENY                     = (TAF_PS_CAUSE_HSM_AS_SECTION_BEGIN + 3),
    TAF_PS_CAUSE_HSM_AS_RTC_RTCACK_FAILURE                  = (TAF_PS_CAUSE_HSM_AS_SECTION_BEGIN + 4),
    TAF_PS_CAUSE_HSM_AS_SIGNAL_FADE                         = (TAF_PS_CAUSE_HSM_AS_SECTION_BEGIN + 5),
    TAF_PS_CAUSE_HSM_AS_SESSION_NOT_EXIST                   = (TAF_PS_CAUSE_HSM_AS_SECTION_BEGIN + 6),
    TAF_PS_CAUSE_HSM_AS_CAN_NOT_EST_CONN                    = (TAF_PS_CAUSE_HSM_AS_SECTION_BEGIN + 7),
    TAF_PS_CAUSE_HSM_AS_TIMEOUT                             = (TAF_PS_CAUSE_HSM_AS_SECTION_BEGIN + 8),
    TAF_PS_CAUSE_HSM_AS_HRPD_SLAVE                          = (TAF_PS_CAUSE_HSM_AS_SECTION_BEGIN + 9),
    TAF_PS_CAUSE_HSM_AS_HANDOFF_FAIL                        = (TAF_PS_CAUSE_HSM_AS_SECTION_BEGIN + 10),
    TAF_PS_CAUSE_HSM_AS_IN_UATI_PROCEDURE                   = (TAF_PS_CAUSE_HSM_AS_SECTION_BEGIN + 11),
    TAF_PS_CAUSE_HSM_AS_IN_SCP_PROCEDURE                    = (TAF_PS_CAUSE_HSM_AS_SECTION_BEGIN + 12),
    TAF_PS_CAUSE_HSM_AS_CONNECTION_EXIST                    = (TAF_PS_CAUSE_HSM_AS_SECTION_BEGIN + 13),
    TAF_PS_CAUSE_HSM_AS_NO_RF                               = (TAF_PS_CAUSE_HSM_AS_SECTION_BEGIN + 14),
    TAF_PS_CAUSE_HSM_AS_REDIRECT                            = (TAF_PS_CAUSE_HSM_AS_SECTION_BEGIN + 15),
    TAF_PS_CAUSE_HSM_AS_HRPD_HANDOFF_TO_1X                  = (TAF_PS_CAUSE_HSM_AS_SECTION_BEGIN + 16),

    TAF_PS_CAUSE_HSM_AS_HRPD_PREFER_CH_NOT_VALID            = (TAF_PS_CAUSE_HSM_AS_SECTION_BEGIN + 17),
    TAF_PS_CAUSE_HSM_AS_OHM_NOT_CURRENT                     = (TAF_PS_CAUSE_HSM_AS_SECTION_BEGIN + 18),

    TAF_PS_CAUSE_EHSM_CTTF_NOT_SUPPORT_EHRPD                = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 1),
    TAF_PS_CAUSE_EHSM_NOT_SUPPORT_EHRPD                     = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 2),
    TAF_PS_CAUSE_EHSM_IN_SUSPEND                            = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 3),
    TAF_PS_CAUSE_EHSM_LAST_PDN                              = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 4),
    TAF_PS_CAUSE_EHSM_CONN_EST_FAIL                         = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 5),
    TAF_PS_CAUSE_EHSM_POWER_OFF                             = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 6),
    TAF_PS_CAUSE_EHSM_INVALID_PDN_ID                        = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 7),
    TAF_PS_CAUSE_EHSM_PPP_DETACH                            = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 8),
    TAF_PS_CAUSE_EHSM_HSM_CONN_FAIL                         = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 9),
    TAF_PS_CAUSE_EHSM_HSM_MAX_ACCESS_PROBES                 = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 10),
    TAF_PS_CAUSE_EHSM_HSM_CONN_DENY                         = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 11),
    TAF_PS_CAUSE_EHSM_HSM_RTCACK_RAILURE                    = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 12),
    TAF_PS_CAUSE_EHSM_HSM_SIGNAL_FADE                       = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 13),
    TAF_PS_CAUSE_EHSM_HSM_CAN_NOT_EST_CONN                  = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 14),
    TAF_PS_CAUSE_EHSM_HSM_TIME_OUT                          = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 15),
    TAF_PS_CAUSE_EHSM_HSM_HRPD_SLAVE                        = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 16),
    TAF_PS_CAUSE_EHSM_HSM_SESSION_NOT_EXSIT                 = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 17),
    TAF_PS_CAUSE_EHSM_PPP_ERROR_GENERAL_ERROR               = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 18),
    TAF_PS_CAUSE_EHSM_PPP_ERROR_UNAUTHORIZED_APN            = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 19),
    TAF_PS_CAUSE_EHSM_PPP_ERROR_PDN_LIMIT_EXCEEDED          = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 20),
    TAF_PS_CAUSE_EHSM_PPP_ERROR_NO_PGW_AVAILABLE            = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 21),
    TAF_PS_CAUSE_EHSM_PPP_ERROR_PGW_UNREACHABLE             = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 22),
    TAF_PS_CAUSE_EHSM_PPP_ERROR_PGW_REJECT                  = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 23),
    TAF_PS_CAUSE_EHSM_PPP_ERROR_INSUFFICIENT_PARAMETERS     = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 24),
    TAF_PS_CAUSE_EHSM_PPP_ERROR_RESOURCE_UNAVAILABLE        = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 25),
    TAF_PS_CAUSE_EHSM_PPP_ERROR_ADMIN_PROHIBITED            = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 26),
    TAF_PS_CAUSE_EHSM_PPP_ERROR_PDNID_ALREADY_IN_USE        = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 27),
    TAF_PS_CAUSE_EHSM_PPP_ERROR_SUBSCRIPTION_LIMITATION     = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 28),
    TAF_PS_CAUSE_EHSM_PPP_ERROR_PDN_CONNECTION_ALREADY_EXISTS_FOR_THIS_APN      = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 29),
    TAF_PS_CAUSE_EHSM_PPP_ERROR_EMERGENCY_SERVICES_NOT_SUPPORTED                = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 30),
    TAF_PS_CAUSE_EHSM_PPP_ERROR_RECONNECT_TO_THIS_APN_NOT_ALLOWED               = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 31),

    TAF_PS_CAUSE_EHSM_PPP_ERROR_CODE_AN_EAP_FAILURE         = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 32), /**< AT received EAP-Failure from AN in EAP authentication. */
    TAF_PS_CAUSE_EHSM_PPP_ERROR_CODE_AT_EAP_FAILURE         = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 33), /**< AT local EAP authentication failure in EAP authentication. */
    TAF_PS_CAUSE_EHSM_PPP_ERROR_CODE_EAP_TIMEROUT           = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 34), /**< AT hasn`t received AN EAP message in EAP authentication. */
    TAF_PS_CAUSE_EHSM_PPP_ERROR_CODE_LCP_TIMEROUT           = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 35), /**< AT hasn`t received AN ack in LCP negotiation. */
    TAF_PS_CAUSE_EHSM_PPP_ERROR_CODE_LCP_TERMINATE          = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 36), /**< LCP terminate in LCP negotiation and EAP authentication. */
    TAF_PS_CAUSE_EHSM_PPP_ERROR_CODE_UNSPECIFIC_FAILURE     = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 37), /**< All failure except above failure in LCP negotiation and EAP authentication. */
    TAF_PS_CAUSE_EHSM_PPP_ERROR_CODE_VSNCP_TIMEROUT         = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 38), /**< AT hasn`t received AN ack in VSNDCP negotiation. */
    TAF_PS_CAUSE_EHSM_PPP_ERROR_CODE_PARA_ERROR             = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 39), /**< CNAS attach req para error  */
    TAF_PS_CAUSE_EHSM_NW_DISC_IND                           = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 40),
    TAF_PS_CAUSE_EHSM_HSM_RSLT_IN_UATI_PROCEDURE            = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 41),
    TAF_PS_CAUSE_EHSM_HSM_RSLT_IN_SCP_PROCEDURE             = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 42),
    TAF_PS_CAUSE_EHSM_HSM_NO_RF                             = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 43),
    TAF_PS_CAUSE_EHSM_HSM_REDIRECT                          = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 44),
    TAF_PS_CAUSE_EHSM_ABORT                                 = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 45),
    TAF_PS_CAUSE_EHSM_HSM_NO_NETWORK                        = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 46),

    TAF_PS_CAUSE_EHSM_PPP_ERROR_CODE_LTE_DETACH             = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 47), /**< LTE DETACH  */
    TAF_PS_CAUSE_EHSM_PPP_ERROR_CODE_ACCESS_AUTH_FAILURE    = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 48), /**< ACCESS AUTH FAILURE  */

    TAF_PS_CAUSE_EHSM_OHM_NOT_CURRENT                       = (TAF_PS_CAUSE_EHSM_CTTF_SECTION_BEGIN + 49), /**< ACCESS AUTH FAILURE  */
    TAF_PS_CAUSE_BUTT                                       = 0xFFFFFFFF
};
typedef VOS_UINT32 TAF_PS_CAUSE_ENUM_UINT32;

/** ****************************************************************************
 * Name        : TAF_PS_CDATA_BEAR_STATUS_ENUM_UINT8
 *
 * Description :
 *******************************************************************************/
enum TAF_PS_CDATA_BEAR_STATUS_ENUM
{
    TAF_PS_CDATA_BEAR_STATUS_INACTIVE     = 0x00,
    TAF_PS_CDATA_BEAR_STATUS_IDLE         = 0x01,
    TAF_PS_CDATA_BEAR_STATUS_ACTIVE       = 0x02,
    TAF_PS_CDATA_BEAR_STATUS_SUSPEND      = 0x03,
    TAF_PS_CDATA_BEAR_STATUS_BUTT         = 0x04
};
typedef VOS_UINT8 TAF_PS_CDATA_BEAR_STATUS_ENUM_UINT8;


/*****************************************************************************
 ????????: TAF_PDP_TYPE_ENUM
 ????????: PDP????

 ????????      :
  1.??    ??   : 2011??10??19??
    ??    ??   : A00165503
    ????????   : ????????
*****************************************************************************/
enum TAF_PDP_TYPE_ENUM
{
    TAF_PDP_IPV4                        = 0x01,
    TAF_PDP_IPV6                        = 0x02,
    TAF_PDP_IPV4V6                      = 0x03,
    TAF_PDP_PPP                         = 0x04,

    TAF_PDP_TYPE_BUTT                   = 0xFF
};
typedef VOS_UINT8 TAF_PDP_TYPE_ENUM_UINT8;


/*****************************************************************************
 ????????: TAF_PDP_AUTH_TYPE_ENUM
 ????????: ????????

 ????????      :
  1.??    ??   : 2013??07??18??
    ??    ??   : Y00213812
    ????????   : ????????

  2.??    ??   : 2015??12??9??
    ??    ??   : y00322978
    ????????   : ??????????
*****************************************************************************/
enum TAF_PDP_AUTH_TYPE_ENUM
{
    TAF_PDP_AUTH_TYPE_NONE              = 0x00,
    TAF_PDP_AUTH_TYPE_PAP               = 0x01,
    TAF_PDP_AUTH_TYPE_CHAP              = 0x02,

    TAF_PDP_AUTH_TYPE_PAP_OR_CHAP       = 0x03,

    TAF_PDP_AUTH_TYPE_BUTT
};
typedef VOS_UINT8 TAF_PDP_AUTH_TYPE_ENUM_UINT8;


/*****************************************************************************
 ????????: TAF_AUTH_TYPE_ENUM
 ????????: PDP??????????????
 ????????      :
  1.??    ??   : 2013??07??18??
    ??    ??   : Y00213812
    ????????   : ????????
*****************************************************************************/
enum TAF_AUTH_TYPE_ENUM
{
    TAF_PDP_ACTIVATE_NO_AUTH            = 0x00,                                 /*PDP????????????????????*/
    TAF_PDP_ACTIVATE_AUTH               = 0x01,                                 /*PDP??????????????????*/

    TAF_AUTH_BUTT                       = 0xFF
};
typedef VOS_UINT8 TAF_AUTH_TYPE_ENUM_UINT8;


/*****************************************************************************
 ????????: TAF_PDP_ACTIVE_STATUS_ENUM
 ????????: PDP????/??????????
 ????????      :
  1.??    ??   : 2013??07??18??
    ??    ??   : Y00213812
    ????????   : ????????
*****************************************************************************/
enum TAF_PDP_ACTIVE_STATUS_ENUM
{
    TAF_PDP_INACTIVE                    = 0x00,                                 /*PDP??????*/
    TAF_PDP_ACTIVE                      = 0x01,                                 /*PDP??????*/

    TAF_PDP_ACTIVE_BUTT                 = 0xFF
};
typedef VOS_UINT8 TAF_PDP_ACTIVE_STATUS_ENUM_UINT8;


/*****************************************************************************
 ????????: TAF_GPRS_ACTIVE_TYPE_ENUM
 ????????: D????GPRS????????

 ????????      :
  1.??    ??   : 2011??10??19??
    ??    ??   : A00165503
    ????????   : ????????
*****************************************************************************/
enum TAF_GPRS_ACTIVE_TYPE_ENUM
{
    TAF_IP_ACTIVE_TE_PPP_MT_PPP_TYPE            = 0x00,
    TAF_PPP_ACTIVE_TE_PPP_MT_NOT_PPP_TYPE       = 0x01,
    TAF_IP_ACTIVE_TE_NOT_PPP_MT_NOT_PPP_TYPE    = 0x02,

    TAF_IP_ACTIVE_TE_BUTT
};
typedef VOS_UINT8 TAF_GPRS_ACTIVE_TYPE_UINT8;


/*****************************************************************************
 ????????: TAF_L2P_TYPE_ENUM
 ????????: L2P????

 ????????      :
 1.??    ??   : 2011??10??19??
   ??    ??   : A00165503
   ????????   : ????????
*****************************************************************************/
enum TAF_L2P_TYPE_ENUM
{
    TAF_L2P_PPP                         = 0x00,
    TAF_L2P_NULL                        = 0x01,

    TAF_L2P_BUTT
};
typedef VOS_UINT8 TAF_L2P_TYPE_ENUM_UINT8;


/*****************************************************************************
 ????????: TAF_PDP_H_COMP_ENUM
 ????????: PDP header compression type

 ????????      :
  1.??    ??   : 2013??07??18??
    ??    ??   : Y00213812
    ????????   : ????????
*****************************************************************************/
enum TAF_PDP_H_COMP_ENUM
{
    TAF_PDP_H_COMP_OFF                  = 0x00,             /* default if value is omitted */
    TAF_PDP_H_COMP_ON                   = 0x01,             /* manufacturer preferred compression */
    TAF_PDP_H_COMP_RFC1144              = 0x02,             /* RFC 1144 */
    TAF_PDP_H_COMP_RFC2507              = 0x03,             /* RFC 2507 */

    TAF_PDP_H_COMP_BUTT                 = 0xFF
};
typedef VOS_UINT8 TAF_PDP_H_COMP_ENUM_UINT8;


/*****************************************************************************
 ????????: TAF_PDP_D_COMP_ENUM
 ????????: PDP data compression type, refer to TS 44.065 (section 6.6.1.1.4)
 ????????      :
  1.??    ??   : 2013??07??18??
    ??    ??   : Y00213812
    ????????   : ????????
*****************************************************************************/
enum TAF_PDP_D_COMP_ENUM
{
    TAF_PDP_D_COMP_OFF                  = 0x00,             /* default if value is omitted */
    TAF_PDP_D_COMP_ON                   = 0x01,             /* manufacturer preferred compression */
    TAF_PDP_D_COMP_V42                  = 0x02,             /* V.42 compression */

    TAF_PDP_D_COMP_BUTT                 = 0xFF
};
typedef VOS_UINT8 TAF_PDP_D_COMP_ENUM_UINT8;


/*****************************************************************************
 ????????: TAF_UMTS_QOS_TRAFFIC_CLASS_ENUM
 ????????: QOS Traffic Class

 ????????      :
  1.??    ??   : 2011??10??19??
    ??    ??   : A00165503
    ????????   : ????????
*****************************************************************************/
enum TAF_UMTS_QOS_TRAFFIC_CLASS_ENUM
{
    TAF_UMTS_QOS_TRAFFIC_CLASS_SUBS     = 0x00,                                 /* Subscribed                  */
    TAF_UMTS_QOS_TRAFFIC_CLASS_CONV     = 0x01,                                 /* Conversational              */
    TAF_UMTS_QOS_TRAFFIC_CLASS_STRM     = 0x02,                                 /* Streaming                   */
    TAF_UMTS_QOS_TRAFFIC_CLASS_INTR     = 0x03,                                 /* Interactive                 */
    TAF_UMTS_QOS_TRAFFIC_CLASS_BACK     = 0x04,                                 /* Background                  */
    TAF_UMTS_QOS_TRAFFIC_CLASS_BUTT     = 0xff                                  /* force max to 0xff so that
                                                                                    enum is defined as a byte   */
};
typedef VOS_UINT8 TAF_UMTS_QOS_TRAFFIC_CLASS_ENUM_UINT8;


/*****************************************************************************
 ????????: TAF_PF_TRANS_DIRECTION_ENUM
 ????????: TFT??????????
 1.??    ??   : 2011??12??18??
   ??    ??   : l00198894
   ????????   : Added for PS????
*****************************************************************************/
enum TAF_PF_TRANS_DIRECTION_ENUM
{
    TAF_PF_TRANS_DIRECTION_PRE_REL7     = 0x00,             /* 0 - Pre-Release 7 TFT filter (see 3GPP TS 24.008 [8], table 10.5.162) */
    TAF_PF_TRANS_DIRECTION_UPLINK       = 0x01,             /* 1 - Uplink */
    TAF_PF_TRANS_DIRECTION_DOWNLINK     = 0x02,             /* 2 - Downlink */
    TAF_PF_TRANS_DIRECTION_BIDIRECTION  = 0x03,             /* 3 - Birectional (Up & Downlink) (default if omitted) */

    TAF_PF_TRANS_DIRECTION_BUTT         = 0xFF
};
typedef VOS_UINT8 TAF_PF_TRANS_DIRECTION_ENUM_UINT8;


/*****************************************************************************
 ??????    : TAF_DSFLOW_CLEAR_MODE_ENUM
 ????????  : DS FLOW????????????????
 1.??    ??   : 2011??12??14??
   ??    ??   : ?????? 00132663
   ????????   : ????
*****************************************************************************/
enum TAF_DSFLOW_CLEAR_MODE_ENUM
{
    TAF_DSFLOW_CLEAR_TOTAL              = 1,   /*????????RABID??????*/
    TAF_DSFLOW_CLEAR_WITH_RABID,               /*????????RABID??????*/

    TAF_DSFLOW_CLEAR_BUTT
};
typedef VOS_UINT8 TAF_DSFLOW_CLEAR_MODE_ENUM_UINT8;


/*****************************************************************************
 ????????: TAF_PDP_EMC_IND_ENUM
 ????????: PDP??????????????????
 ????????      :
  1.??    ??   : 2013??07??18??
    ??    ??   : Y00213812
    ????????   : ????????
*****************************************************************************/
enum TAF_PDP_EMC_IND_ENUM
{
    TAF_PDP_NOT_FOR_EMC                 = 0x00,
    TAF_PDP_FOR_EMC                     = 0x01,

    TAF_PDP_EMC_IND_BUTT                = 0xFF
};
typedef VOS_UINT8 TAF_PDP_EMC_IND_ENUM_UINT8;


/*****************************************************************************
 ????????: TAF_PDP_IPV4_ADDR_ALLOC_TYPE_ENUM
 ????????: IPV4????????????????
 ????????      :
  1.??    ??   : 2013??07??18??
    ??    ??   : Y00213812
    ????????   : ????????
*****************************************************************************/
enum TAF_PDP_IPV4_ADDR_ALLOC_TYPE_ENUM
{
    TAF_PDP_IPV4_ADDR_ALLOC_TYPE_NAS    = 0x00,
    TAF_PDP_IPV4_ADDR_ALLOC_TYPE_DHCP   = 0x01,

    TAF_PDP_IPV4_ADDR_ALLOC_BUTT        = 0xFF
};
typedef VOS_UINT8 TAF_PDP_IPV4_ADDR_ALLOC_TYPE_ENUM_UINT8;


/*****************************************************************************
 ??????  : TAF_PDP_PCSCF_DISCOVERY_ENUM
 ????????: P-CSCF DISCOVERY

 ????????      :
  1.??    ??   : 2013??07??18??
    ??    ??   : Y00213812
    ????????   : ????????
*****************************************************************************/
enum TAF_PDP_PCSCF_DISCOVERY_ENUM
{
    TAF_PDP_PCSCF_DISCOVERY_NOT_INFLUENCED  = 0x00,
    TAF_PDP_PCSCF_DISCOVERY_THROUGH_NAS_SIG = 0x01,
    TAF_PDP_PCSCF_DISCOVERY_THROUGH_DHCP    = 0x02,

    TAF_PDP_PCSCF_DISCOVERY_BUTT            = 0xFF
};
typedef VOS_UINT8 TAF_PDP_PCSCF_DISCOVERY_ENUM_UINT8;


/*****************************************************************************
 ??????  : TAF_PDP_IM_CN_SIG_FLAG_ENUM
 ????????: IMS????????????

 ????????      :
  1.??    ??   : 2013??07??18??
    ??    ??   : Y00213812
    ????????   : ????????
*****************************************************************************/
enum TAF_PDP_IM_CN_SIG_FLAG_ENUM
{
    TAF_PDP_NOT_FOR_IMS_CN_SIG_ONLY     = 0x00,
    TAF_PDP_FOR_IM_CN_SIG_ONLY          = 0x01,

    TAF_PDP_IM_CN_SIG_FLAG_BUTT         = 0xFF
};
typedef VOS_UINT8 TAF_PDP_IM_CN_SIG_FLAG_ENUM_UINT8;


/*****************************************************************************
 ????????: TAF_PDP_ANSWER_TYPE_ENUM
 ????????: ????????

 ????????      :
  1.??    ??   : 2013??07??18??
    ??    ??   : Y00213812
    ????????   : ????????
*****************************************************************************/
enum TAF_PDP_ANSWER_TYPE_ENUM
{
    TAF_PDP_ANSWER_TYPE_ACCEPT             = 0x00,             /* ???????? */
    TAF_PDP_ANSWER_TYPE_REJECT             = 0x01,             /* ???????? */

    TAF_PDP_ANSWER_TYPE_BUTT
};
typedef VOS_UINT8 TAF_PDP_ANSWER_TYPE_ENUM_UINT8;


/*****************************************************************************
 ????????: TAF_PDP_ANSWER_MODE_ENUM
 ????????: ????????

 ????????      :
  1.??    ??   : 2013??07??18??
    ??    ??   : Y00213812
    ????????   : ????????
*****************************************************************************/
enum TAF_PDP_ANSWER_MODE_ENUM
{
    TAF_PDP_ANSWER_MODE_MANUAL             = 0x00,             /* ???????????? */
    TAF_PDP_ANSWER_MODE_AUTO               = 0x01,             /* ???????????? */

    TAF_PDP_ANSWER_MODE_BUTT
};
typedef VOS_UINT8 TAF_PDP_ANSWER_MODE_ENUM_UINT8;

#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 ????????: TAF_SRVCC_CANCEL_NOTIFY_ENUM
 ????????: APS->IMSA????SRVCC CANECL
*****************************************************************************/
enum TAF_SRVCC_CANCEL_NOTIFY_ENUM
{
    TAF_SRVCC_CANCEL_NOTIFY_HO_CANCELLED    = 0,

    TAF_SRVCC_CANCEL_NOTIFY_IND_BUTT
};
typedef VOS_UINT32 TAF_SRVCC_CANCEL_NOTIFY_ENUM_UINT32;

#endif

/* Added by l60609 for L-C??????????, 2014-01-06, Begin */
/*****************************************************************************
 ??????   :TAF_PDP_REQUEST_TYPE_ENUM_UINT8
 ???????? :PDN????????????
 1.??    ??   : 2014??01??08??
   ??    ??   : l60609
   ????????   : ????
*****************************************************************************/
enum TAF_PDP_REQUEST_TYPE_ENUM
{
    TAF_PDP_REQUEST_TYPE_INITIAL        = 0x1,
    TAF_PDP_REQUEST_TYPE_HANDOVER       = 0x2,
    TAF_PDP_REQUEST_TYPE_UNUSED         = 0x3,
    TAF_PDP_REQUEST_TYPE_EMERGENCY      = 0x4,
    TAF_PDP_REQUEST_TYPE_BUTT
};
typedef VOS_UINT8 TAF_PDP_REQUEST_TYPE_ENUM_UINT8;
/* Added by l60609 for L-C??????????, 2014-01-06, End */

/** ****************************************************************************
 * Name        : TAF_PS_CDATA_1X_QOS_NON_ASSURED_PRI_ENUM_UINT8
 *
 * Description : User Priority Adjustment Values
 * Refer to  C.S0017-012-A_v2.0_060522 2.2.8 Table 15
 *******************************************************************************/
enum TAF_PS_CDATA_1X_QOS_NON_ASSURED_PRI_ENUM
{
    TAF_PS_CDATA_1X_QOS_DESIRED_NON_ASSURED_PRI_MIN         = 0x00, /**< min value */
    TAF_PS_CDATA_1X_QOS_DESIRED_NON_ASSURED_PRI_DEFAULT     = 0x0D, /**< default value */
    TAF_PS_CDATA_1X_QOS_DESIRED_NON_ASSURED_PRI_MAX         = 0x0F, /**< max value */
    TAF_PS_CDATA_1X_QOS_NON_ASSURED_PRI_BUTT                = 0x10
};
typedef VOS_UINT8 TAF_PS_CDATA_1X_QOS_NON_ASSURED_PRI_ENUM_UINT8;


/*****************************************************************************
 ??????    : TAF_PS_CDATA_DIAL_MODE_ENUM_UINT32
 ????????  : ??????????????
 1.??    ??   : 2015??04??02??
   ??    ??   : y00314741
   ????????   : ????
*****************************************************************************/
enum TAF_PS_CDATA_DIAL_MODE_ENUM
{
    TAF_PS_CDATA_DIAL_MODE_ASYNC_CALL   = 0x00,
    TAF_PS_CDATA_DIAL_MODE_RELAY        = 0x01,                                 /* ???????????????????? */
    TAF_PS_CDATA_DIAL_MODE_NETWORK      = 0x02,                                 /* ????????????????????  */
    TAF_PS_CDATA_DIAL_MODE_BUTT
};
typedef VOS_UINT32 TAF_PS_CDATA_DIAL_MODE_ENUM_UINT32;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 ??????    : TAF_APS_READ_SIM_FILES_CNF_ENUM
 ????????  : ????????????USIM??????????????
1.??    ??   : 2015??11??30??
  ??    ??   : Y00322978
  ????????   : AT&T ????EONS????????

*****************************************************************************/
enum  TAF_APS_READ_SIM_FILES_CNF_ENUM
{
    TAF_APS_READ_USIM_FILE_FLG_NULL                         = 0x0,

    TAF_APS_READ_USIMM_CDMA_EFSIPCAP_ID_FLG                 = 0x1,
    TAF_APS_READ_USIMM_CDMA_EFSIPUPP_ID_FLG                 = 0x2,
    TAF_APS_READ_USIMM_CDMA_EFSIPSP_ID_FLG                  = 0x4,
    TAF_APS_READ_USIMM_CDMA_EFSIPPAPSS_ID_FLG               = 0x8,


    TAF_APS_READ_USIMM_CSIM_EFSIPCAP_ID_FLG                 = 0x10,
    TAF_APS_READ_USIMM_CSIM_EFSIPUPP_ID_FLG                 = 0x20,
    TAF_APS_READ_USIMM_CSIM_EFSIPSP_ID_FLG                  = 0x40,
    TAF_APS_READ_USIMM_CSIM_EFSIPPAPSS_ID_FLG               = 0x80,


    TAF_APS_READ_USIM_FILE_CNF_BUTT
};

typedef VOS_UINT32 TAF_APS_READ_SIM_FILES_CNF_ENUM_UINT32;
#endif

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
 ????????: TAF_PS_EVT_STRU
 ????????: PS??????????

 ????????      :
  1.??    ??   : 2013??07??18??
    ??    ??   : Y00213812
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stHeader;
    VOS_UINT32                          ulEvtId;
    VOS_UINT8                           aucContent[4];

} TAF_PS_EVT_STRU;


/*****************************************************************************
 ??????    : TAF_DSFLOW_INFO_STRU
 ????????  : DS FLOW??????????????????????
 1.??    ??   : 2011??12??14??
   ??    ??   : ?????? 00132663
   ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDSLinkTime;                           /* DS???????? */
    VOS_UINT32                          ulDSSendFluxLow;                        /* DS?????????????????? */
    VOS_UINT32                          ulDSSendFluxHigh;                       /* DS?????????????????? */
    VOS_UINT32                          ulDSReceiveFluxLow;                     /* DS?????????????????? */
    VOS_UINT32                          ulDSReceiveFluxHigh;                    /* DS?????????????????? */

} TAF_DSFLOW_INFO_STRU;


/*****************************************************************************
 ??????    : TAF_DSFLOW_REPORT_STRU
 ????????  : ????????????????????
 1.??    ??   : 2011??12??17??
   ??    ??   : ?????? 00132663
   ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCurrentSendRate;                      /*????????????*/
    VOS_UINT32                          ulCurrentReceiveRate;                   /*????????????*/
    VOS_UINT32                          ulQosSendRate;                          /*QOS????????????*/
    VOS_UINT32                          ulQosReceiveRate;                       /*QOS????????????*/
    TAF_DSFLOW_INFO_STRU                stCurrentFlowInfo;                      /*????????????????*/

} TAF_DSFLOW_REPORT_STRU;


/*****************************************************************************
 ??????    : TAF_DSFLOW_QUERY_INFO_STRU
 ????????  : DS FLOW ??????????????
 1.??    ??   : 2011??12??14??
   ??    ??   : ?????? 00132663
   ????????   : ????
*****************************************************************************/
typedef struct
{
    TAF_DSFLOW_INFO_STRU                stCurrentFlowInfo;  /*????????????????*/
    TAF_DSFLOW_INFO_STRU                stTotalFlowInfo;    /*????????????*/

} TAF_DSFLOW_QUERY_INFO_STRU;


/*****************************************************************************
 ??????    : TAF_EPS_QOS_STRU
 ????????  : EPS QOS ????????, ????????LTE????
 ????????  :
 1.??    ??   : 2012??01??04??
   ??    ??   : l00198894
   ????????   : ????????
*****************************************************************************/
typedef struct
{
    /* 0 QCI is selected by network
       [1 - 4]value range for guranteed bit rate Traffic Flows
       [5 - 9]value range for non-guarenteed bit rate Traffic Flows */
    VOS_UINT8                           ucQCI;

    VOS_UINT8                           aucReserved[3];

    /* DL GBR in case of GBR QCI, The value is in kbit/s */
    VOS_UINT32                          ulDLGBR;

    /* UL GBR in case of GBR QCI, The value is in kbit/s */
    VOS_UINT32                          ulULGBR;

    /* DL MBR in case of GBR QCI, The value is in kbit/s */
    VOS_UINT32                          ulDLMBR;

    /* UL MBR in case of GBR QCI, The value is in kbit/s */
    VOS_UINT32                          ulULMBR;

}TAF_EPS_QOS_STRU;


/*****************************************************************************
 ??????    : TAF_PDP_AUTH_STRU
 ????????  : ????????????
 ????????  :
 1.??    ??   : 2012??01??04??
   ??    ??   : l00198894
   ????????   : PS Project??4????????, ??????????, ??????????????255
*****************************************************************************/
typedef struct
{
    TAF_AUTH_TYPE_ENUM_UINT8            enAuth;                                   /*??????????????????????????????????????????????*/

    VOS_UINT8                           aucReserved[3];

    /* aucUserName[0]?????????????? */
    VOS_UINT8                           aucUserName[TAF_MAX_PDP_AUTH_USERNAME_LEN + 1];

    /* aucPassword[0]???????????? */
    VOS_UINT8                           aucPassword[TAF_MAX_PDP_AUTH_PASSCODE_LEN + 1];

} TAF_PDP_AUTH_STRU;


/*****************************************************************************
 ????????: TAF_PDP_APN_STRU
 ????????: PDP????????APN????

 ????????      :
  1.??    ??   : 2013??07??18??
    ??    ??   : Y00213812
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLength;
    VOS_UINT8                           aucValue[TAF_MAX_APN_LEN];

} TAF_PDP_APN_STRU;


/*****************************************************************************
 ????????: TAF_PDP_DNS_STRU
 ????????: DNS????

 ????????      :
  1.??    ??   : 2013??07??18??
    ??    ??   : Y00213812
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPrimDnsAddr    : 1;
    VOS_UINT32                          bitOpSecDnsAddr     : 1;
    VOS_UINT32                          bitOpSpare          : 30;

    VOS_UINT8                           aucPrimDnsAddr[TAF_IPV4_ADDR_LEN];
    VOS_UINT8                           aucSecDnsAddr[TAF_IPV4_ADDR_LEN];

} TAF_PDP_DNS_STRU;


/*****************************************************************************
 ????????: TAF_PDP_NBNS_STRU
 ????????: NBNS????

 ????????      :
  1.??    ??   : 2013??07??18??
    ??    ??   : Y00213812
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPrimNbnsAddr   : 1;
    VOS_UINT32                          bitOpSecNbnsAddr    : 1;
    VOS_UINT32                          bitOpSpare          : 30;

    VOS_UINT8                           aucPrimNbnsAddr[TAF_IPV4_ADDR_LEN];
    VOS_UINT8                           aucSecNbnsAddr[TAF_IPV4_ADDR_LEN];

} TAF_PDP_NBNS_STRU;


/*****************************************************************************
 ????????: TAF_PDP_GATEWAY_STRU
 ????????: ????????????

 ????????      :
  1.??    ??   : 2013??07??18??
    ??    ??   : Y00213812
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpGateWayAddr    : 1;
    VOS_UINT32                          bitOpSpare          : 31;

    VOS_UINT8                           aucGateWayAddr[TAF_IPV4_ADDR_LEN];

} TAF_PDP_GATEWAY_STRU;


/*****************************************************************************
 ????????: TAF_PDP_PCSCF_STRU
 ????????: P-CSCF????????

 ????????      :
  1.??    ??   : 2013??07??18??
    ??    ??   : Y00213812
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPrimPcscfAddr  : 1;
    VOS_UINT32                          bitOpSecPcscfAddr   : 1;
    VOS_UINT32                          bitOpThiPcscfAddr   : 1;
    VOS_UINT32                          bitOpSpare          : 29;

    VOS_UINT8                           aucPrimPcscfAddr[TAF_IPV4_ADDR_LEN];
    VOS_UINT8                           aucSecPcscfAddr[TAF_IPV4_ADDR_LEN];
    VOS_UINT8                           aucThiPcscfAddr[TAF_IPV4_ADDR_LEN];

} TAF_PDP_PCSCF_STRU;


/*****************************************************************************
 ????????: TAF_PDP_IPV6_PCSCF_STRU
 ????????: IPv6 P-CSCF??????????

 ????????      :
  1.??    ??   : 2013??07??18??
    ??    ??   : Y00213812
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPrimPcscfAddr  : 1;
    VOS_UINT32                          bitOpSecPcscfAddr   : 1;
    VOS_UINT32                          bitOpThiPcscfAddr   : 1;
    VOS_UINT32                          bitOpSpare          : 29;

    VOS_UINT8                           aucPrimPcscfAddr[TAF_IPV6_ADDR_LEN];
    VOS_UINT8                           aucSecPcscfAddr[TAF_IPV6_ADDR_LEN];
    VOS_UINT8                           aucThiPcscfAddr[TAF_IPV6_ADDR_LEN];

} TAF_PDP_IPV6_PCSCF_STRU;


/*****************************************************************************
 ????????: TAF_PDP_IPV6_DNS_STRU
 ????????: IPv6 DNS????????

 ????????      :
  1.??    ??   : 2013??07??18??
    ??    ??   : Y00213812
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPrimDnsAddr    : 1;
    VOS_UINT32                          bitOpSecDnsAddr     : 1;
    VOS_UINT32                          bitOpSpare          : 30;

    VOS_UINT8                           aucPrimDnsAddr[TAF_IPV6_ADDR_LEN];
    VOS_UINT8                           aucSecDnsAddr[TAF_IPV6_ADDR_LEN];

} TAF_PDP_IPV6_DNS_STRU;


/*****************************************************************************
 ????????: TAF_PDP_ADDR_STRU
 ????????: IP????????

 ????????      :
  1.??    ??   : 2013??07??18??
    ??    ??   : Y00213812
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    /* IPV4:1, IPV6:2, IPV4V6:3, PPP:4 */
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                           aucIpv4Addr[TAF_IPV4_ADDR_LEN];
    VOS_UINT8                           aucIpv6Addr[TAF_IPV6_ADDR_LEN];
} TAF_PDP_ADDR_STRU;


/*****************************************************************************
 ??????    : TAF_PDP_PRIM_CONTEXT_STRU
 ????????  : ??PDP??????????
 ????????  :
 1.??    ??   : 2012??01??04??
   ??    ??   : l00198894
   ????????   : PS Project??????4????????
*****************************************************************************/
typedef struct
{
    TAF_PDP_ADDR_STRU                   stPdpAddr;
    TAF_PDP_APN_STRU                    stApn;
    TAF_PDP_D_COMP_ENUM_UINT8           enPdpDcomp;
    TAF_PDP_H_COMP_ENUM_UINT8           enPdpHcomp;

    /* 0 - IPv4 Address Allocation through NAS Signaling (default if omitted)
       1 - IPv4 Address Allocated through DHCP */
    TAF_PDP_IPV4_ADDR_ALLOC_TYPE_ENUM_UINT8 enIpv4AddrAlloc;

    /* 0 - PDP context is not for emergency bearer services
       1 - PDP context is for emergency bearer services */
    TAF_PDP_EMC_IND_ENUM_UINT8          enEmergencyInd;

    TAF_PDP_PCSCF_DISCOVERY_ENUM_UINT8  enPcscfDiscovery;

    TAF_PDP_IM_CN_SIG_FLAG_ENUM_UINT8   enImCnSignalFlg;

    VOS_UINT8                           aucReserved2[2];

}TAF_PDP_PRIM_CONTEXT_STRU;

/*****************************************************************************
 ????????: TAF_PDP_AUTHDATA_STRU
 ????????: NDIS????????????

 ????????      :
  1.??    ??   : 2013??07??18??
    ??    ??   : Y00213812
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_PDP_AUTH_TYPE_ENUM_UINT8        enAuthType;
    VOS_UINT8                           aucPlmn[TAF_MAX_AUTHDATA_PLMN_LEN + 1];
    VOS_UINT8                           aucPassword[TAF_MAX_AUTHDATA_PASSWORD_LEN + 1];
    VOS_UINT8                           aucUsername[TAF_MAX_AUTHDATA_USERNAME_LEN + 1];
}TAF_PDP_AUTHDATA_STRU;


/*****************************************************************************
 ??????    : TAF_PDP_PF_STRU
 ????????  : TFT??????????
 ????????  :
 1.??    ??   : 2012??01??04??
   ??    ??   : l00198894
   ????????   : PS Project, ????????LTE??TFT??????????
 2.??    ??   : 2015??9??28??
   ??    ??   : W00316404
   ????????   : R11 TFT ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpRmtIpv4AddrAndMask     : 1;
    VOS_UINT32                          bitOpRmtIpv6AddrAndMask     : 1;
    VOS_UINT32                          bitOpProtocolId             : 1;
    VOS_UINT32                          bitOpSingleLocalPort        : 1;
    VOS_UINT32                          bitOpLocalPortRange         : 1;
    VOS_UINT32                          bitOpSingleRemotePort       : 1;
    VOS_UINT32                          bitOpRemotePortRange        : 1;
    VOS_UINT32                          bitOpSecuParaIndex          : 1;
    VOS_UINT32                          bitOpTypeOfService          : 1;
    VOS_UINT32                          bitOpFlowLabelType          : 1;
    VOS_UINT32                          bitOpLocalIpv4AddrAndMask   : 1;
    VOS_UINT32                          bitOpLocalIpv6AddrAndMask   : 1;
    VOS_UINT32                          bitOpSpare                  : 20;

    VOS_UINT8                           ucPacketFilterId;
    VOS_UINT8                           ucNwPacketFilterId;
    TAF_PF_TRANS_DIRECTION_ENUM_UINT8   enDirection;
    VOS_UINT8                           ucPrecedence;                           /* packet filter evaluation precedence */

    VOS_UINT32                          ulSecuParaIndex;                        /* SPI */
    VOS_UINT16                          usSingleLcPort;
    VOS_UINT16                          usLcPortHighLimit;
    VOS_UINT16                          usLcPortLowLimit;
    VOS_UINT16                          usSingleRmtPort;
    VOS_UINT16                          usRmtPortHighLimit;
    VOS_UINT16                          usRmtPortLowLimit;
    VOS_UINT8                           ucProtocolId;                           /* ?????? */
    VOS_UINT8                           ucTypeOfService;                        /* TOS */
    VOS_UINT8                           ucTypeOfServiceMask;                    /* TOS Mask */
    VOS_UINT8                           aucReserved[1];

    /* aucRmtIpv4Address[0]??IP????????????
       aucRmtIpv4Address[3]?????????? */
    VOS_UINT8                           aucRmtIpv4Address[TAF_IPV4_ADDR_LEN];

    /* aucRmtIpv4Mask[0]??IP???????????? ,
       aucRmtIpv4Mask[3]??????????*/
    VOS_UINT8                           aucRmtIpv4Mask[TAF_IPV4_ADDR_LEN];

    /* ucRmtIpv6Address[0]??IPv6????????????????
       ucRmtIpv6Address[7]??IPv6???????????????? */
    VOS_UINT8                           aucRmtIpv6Address[TAF_IPV6_ADDR_LEN];

    /* ucRmtIpv6Mask[0]??????????
       ucRmtIpv6Mask[7]??????????*/
    VOS_UINT8                           aucRmtIpv6Mask[TAF_IPV6_ADDR_LEN];

    VOS_UINT32                          ulFlowLabelType;                        /*FlowLabelType*/

    VOS_UINT8                           aucLocalIpv4Addr[TAF_IPV4_ADDR_LEN];
    VOS_UINT8                           aucLocalIpv4Mask[TAF_IPV4_ADDR_LEN];
    VOS_UINT8                           aucLocalIpv6Addr[TAF_IPV6_ADDR_LEN];
    VOS_UINT8                           ucLocalIpv6Prefix;
    VOS_UINT8                           aucReserved2[3];
}TAF_PDP_PF_STRU;


/*****************************************************************************
 ??????    : TAF_UMTS_QOS_STRU
 ????????  : QOS????????
 ????????  :
 1.??    ??   : 2012??01??04??
   ??    ??   : l00198894
   ????????   : PS Project??4????????????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTrafficClass;                         /*UMTS????????????????*/
    VOS_UINT8                           ucDeliverOrder;                         /*SDU????????????UMTS????*/
    VOS_UINT8                           ucDeliverErrSdu;                        /*SDU????????????*/
    VOS_UINT8                           aucReserved1[1];
    VOS_UINT16                          usMaxSduSize;                           /*SDU??????????*/
    VOS_UINT8                           aucReserved2[2];
    VOS_UINT32                          ulMaxBitUl;                             /*???????????? kbits/s*/
    VOS_UINT32                          ulMaxBitDl;                             /*???????????? kbits/s*/
    VOS_UINT8                           ucResidualBer;
    VOS_UINT8                           ucSduErrRatio;                          /*SDU??????*/
    VOS_UINT16                          usTransDelay;                           /*????????, ????????*/
    VOS_UINT8                           ucTraffHandlePrior;                     /*????UMTS??????SDU??????????????SDU*/
    VOS_UINT8                           aucReserved3[1];
    VOS_UINT8                           ucSrcStatisticsDescriptor;
    VOS_UINT8                           ucSignallingIndication;
    VOS_UINT32                          ulGuarantBitUl;                         /*???????????????? kbits/s*/
    VOS_UINT32                          ulGuarantBitDl;                         /*???????????????? kbits/s*/
}TAF_UMTS_QOS_STRU;


/*****************************************************************************
 ????????: TAF_PRI_PDP_QUERY_INFO_STRU
 ????????: ID_EVT_TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_CNF????????

 ????????      :
  1.??    ??   : 2013??07??18??
    ??    ??   : Y00213812
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCid;
    VOS_UINT8                           aucReserved[3];
    TAF_PDP_PRIM_CONTEXT_STRU           stPriPdpInfo;

}TAF_PRI_PDP_QUERY_INFO_STRU;


/*****************************************************************************
 ????????: TAF_TFT_QUREY_INFO_STRU
 ????????: ID_EVT_TAF_PS_GET_TFT_INFO_CNF????????

 ????????      :
  1.??    ??   : 2013??07??18??
    ??    ??   : Y00213812
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucPfNum;                                /* pf???? */
    VOS_UINT8                           aucReserved[2];
    TAF_PDP_PF_STRU                     astPfInfo[TAF_MAX_SDF_PF_NUM];          /* pf?? */

}TAF_TFT_QUREY_INFO_STRU;

/*****************************************************************************
 ????????: TAF_UMTS_QOS_QUERY_INFO_STRU
 ????????: QOS????????????

 ????????      :
  1.??    ??   : 2013??07??18??
    ??    ??   : Y00213812
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCid;
    VOS_UINT8                           aucReserved[3];
    TAF_UMTS_QOS_STRU                   stQosInfo;

} TAF_UMTS_QOS_QUERY_INFO_STRU;


/*****************************************************************************
 ????????: TAF_DNS_QUERY_INFO_STRU
 ????????: DNS????????????

 ????????      :
  1.??    ??   : 2013??07??18??
    ??    ??   : Y00213812
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCid;
    VOS_UINT8                           aucReserved[3];
    TAF_PDP_DNS_STRU                    stDnsInfo;

}TAF_DNS_QUERY_INFO_STRU;

/*****************************************************************************
 ????????: TAF_AUTH_QUERY_INFO_STRU
 ????????: ????????????

 ????????      :
  1.??    ??   : 2013??07??18??
    ??    ??   : Y00213812
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCid;
    VOS_UINT8                           aucReserved[3];
    TAF_PDP_AUTH_STRU                   stAuthInfo;

}TAF_AUTH_QUERY_INFO_STRU;

/*****************************************************************************
 ????????: TAF_AUTHDATA_QUERY_INFO_STRU
 ????????: ID_EVT_TAF_PS_GET_AUTHDATA_INFO_CNF????????????????????

 ????????      :
  1.??    ??   : 2013??07??18??
    ??    ??   : Y00213812
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCid;
    VOS_UINT8                           aucReserved[3];
    TAF_PDP_AUTHDATA_STRU               stAuthDataInfo;

}TAF_AUTHDATA_QUERY_INFO_STRU;

/*****************************************************************************
 ????????: TAF_PDP_TFT_STRU
 ????????: TFT????????

 ????????      :
  1.??    ??   : 2014??06??16??
    ??    ??   : f00179208
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPfNum;                                /* pf???? */
    TAF_PDP_PF_STRU                     astPf[TAF_MAX_SDF_PF_NUM];              /* pf?? */
}TAF_PDP_TFT_STRU;

/*****************************************************************************
 ????????: TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU
 ????????: ????PDP??????????????????????

 ????????      :
  1.??    ??   : 2013??07??18??
    ??    ??   : Y00213812
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    VOS_UINT32                          bitOpLinkdRabId     : 1;
    VOS_UINT32                          bitOpPdpAddr        : 1;
    VOS_UINT32                          bitOpApn            : 1;
    VOS_UINT32                          bitOpEmergencyInd   : 1;
    VOS_UINT32                          bitOpImCnSignalFlg  : 1;
    VOS_UINT32                          bitOpCause          : 1;
    VOS_UINT32                          bitOpUmtsQos        : 1;
    VOS_UINT32                          bitOpEpsQos         : 1;
    VOS_UINT32                          bitOpTft            : 1;
    VOS_UINT32                          bitOpSpare          : 23;

    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucRabId;
    VOS_UINT8                           ucLinkdRabId;
    TAF_PDP_EMC_IND_ENUM_UINT8          enEmergencyInd;
    TAF_PDP_IM_CN_SIG_FLAG_ENUM_UINT8   enImCnSignalFlg;
    VOS_UINT8                           aucReserved[3];
    TAF_PS_CAUSE_ENUM_UINT32            enCause;

    TAF_PDP_ADDR_STRU                   stPdpAddr;
    TAF_PDP_APN_STRU                    stApn;
    TAF_UMTS_QOS_STRU                   stUmtsQos;
    TAF_EPS_QOS_STRU                    stEpsQos;

    TAF_PDP_DNS_STRU                    stDns;
    TAF_PDP_NBNS_STRU                   stNbns;
    TAF_PDP_PCSCF_STRU                  stPcscf;
    TAF_PDP_GATEWAY_STRU                stGateWay;
    TAF_PDP_IPV6_DNS_STRU               stIpv6Dns;
    TAF_PDP_IPV6_PCSCF_STRU             stIpv6Pcscf;
    TAF_PDP_TFT_STRU                    stTft;

} TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU;


/*****************************************************************************
 ????????: TAF_PS_CALL_PDP_ACTIVATE_IND_STRU
 ????????: ????PDP??????????????

 ????????      :
  1.??    ??   : 2013??07??18??
    ??    ??   : Y00213812
    ????????   : ????????
*****************************************************************************/
typedef TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU TAF_PS_CALL_PDP_ACTIVATE_IND_STRU;

/*****************************************************************************
 ????????: TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU
 ????????: PDP????????

 ????????      :
  1.??    ??   : 2013??07??18??
    ??    ??   : Y00213812
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    VOS_UINT32                          bitOpCauseEx        : 1;
    VOS_UINT32                          bitOpSpare          : 31;

    VOS_UINT8                           ucCid;
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;
    VOS_UINT8                           aucReserved[2];
    TAF_PS_CAUSE_ENUM_UINT32            enCause;

    /*----------------------------------------------------------------------
       enCauseEx????????:
       enPdpType??IPv4/IPv6/PPP.

       enCauseEx??????????:
       TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV4_ONLY_ALLOWED
       TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV6_ONLY_ALLOWED
       TAF_PS_CAUSE_SM_NW_SINGLE_ADDR_BEARERS_ONLY_ALLOWED

       enCauseEx????????:
       ????????????????????????(IPv4v6), TAF??????REJECT????, ????enPdpType
       ??????(IPv4/IPv6), ????????????enCauseEx, ????????????????????????.

       enCauseEx????????:
       ????????????????????????(IPv4v6), ????????IPv4????????, ??????????????
       TAF_PS_CAUSE_SM_NW_SINGLE_ADDR_BEARERS_ONLY_ALLOWED, ????????????????
       ????QOS, ????????????, TAF????REJECT????, IP??????IPv4, enCause??
       QOS_NOT_ACCEPT, enCauseEx??TAF_PS_CAUSE_SM_NW_SINGLE_ADDR_BEARERS_ONLY_ALLOWED,
       ????????????????IPv6????????????.
    *---------------------------------------------------------------------*/
    TAF_PS_CAUSE_ENUM_UINT32            enCauseEx;

} TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU;

/*****************************************************************************
 ????????: TAF_PS_CALL_PDP_MANAGE_IND_STRU
 ????????: ????PDP??????????????????

 ????????      :
  1.??    ??   : 2013??07??18??
    ??    ??   : Y00213812
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    VOS_UINT32                          bitOpApn            : 1;
    VOS_UINT32                          bitOpPdpAddr        : 1;
    VOS_UINT32                          bitLinkdRabId       : 1;
    VOS_UINT32                          bitEmergencyInd     : 1;
    VOS_UINT32                          bitImCnSignalFlg    : 1;
    VOS_UINT32                          bitOpSpare          : 27;

    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucRabId;
    VOS_UINT8                           ucLinkdRabId;
    TAF_PDP_EMC_IND_ENUM_UINT8          enEmergencyInd;
    TAF_PDP_IM_CN_SIG_FLAG_ENUM_UINT8   enImCnSignalFlg;
    VOS_UINT8                           aucReserved[3];

    TAF_PDP_ADDR_STRU                   stPdpAddr;
    TAF_PDP_APN_STRU                    stApn;

} TAF_PS_CALL_PDP_MANAGE_IND_STRU;


/*****************************************************************************
 ????????: TAF_PS_CALL_PDP_MODIFY_CNF_STRU
 ????????: ????MODIFY????

 ????????      :
  1.??    ??   : 2013??07??18??
    ??    ??   : Y00213812
    ????????   : ????????

*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    VOS_UINT32                          bitLinkdRabId       : 1;
    VOS_UINT32                          bitOpUmtsQos        : 1;
    VOS_UINT32                          bitOpEpsQos         : 1;
    VOS_UINT32                          bitOpTft            : 1;
    VOS_UINT32                          bitOpSpare          : 28;

    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucRabId;
    VOS_UINT8                           ucLinkdRabId;
    VOS_UINT8                           aucReserved[1];

    TAF_UMTS_QOS_STRU                   stUmtsQos;
    TAF_EPS_QOS_STRU                    stEpsQos;

    TAF_PDP_DNS_STRU                    stDns;
    TAF_PDP_NBNS_STRU                   stNbns;
    TAF_PDP_PCSCF_STRU                  stPcscf;
    TAF_PDP_IPV6_DNS_STRU               stIpv6Dns;
    TAF_PDP_IPV6_PCSCF_STRU             stIpv6Pcscf;
    TAF_PDP_TFT_STRU                    stTft;
} TAF_PS_CALL_PDP_MODIFY_CNF_STRU;

/*****************************************************************************
 ????????: TAF_PS_CALL_PDP_MODIFY_IND_STRU
 ????????: ????MODIFY????

 ????????      :
  1.??    ??   : 2013??07??18??
    ??    ??   : Y00213812
    ????????   : ????????
*****************************************************************************/
typedef TAF_PS_CALL_PDP_MODIFY_CNF_STRU TAF_PS_CALL_PDP_MODIFY_IND_STRU;

/*****************************************************************************
 ????????: TAF_PS_CALL_PDP_MODIFY_REJ_STRU
 ????????: MODIFY????

 ????????      :
  1.??    ??   : 2013??07??18??
    ??    ??   : Y00213812
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucRabId;
    VOS_UINT8                           aucReserved[2];
    TAF_PS_CAUSE_ENUM_UINT32            enCause;

} TAF_PS_CALL_PDP_MODIFY_REJ_STRU;


/*****************************************************************************
 ????????: TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU
 ????????: ??????????????

 ????????      :
  1.??    ??   : 2013??07??18??
    ??    ??   : Y00213812
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucRabId;
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;
    VOS_UINT8                           aucReserved[1];
    TAF_PS_CAUSE_ENUM_UINT32            enCause;

} TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU;


/*****************************************************************************
 ????????: TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU
 ????????: ????????????

 ????????      :
  1.??    ??   : 2013??07??18??
    ??    ??   : Y00213812
    ????????   : ????????
*****************************************************************************/
typedef TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU;


/*****************************************************************************
 ????????: TAF_PS_CALL_PDP_PDP_DISCONNECT_IND_STRU
 ????????: ????????

 ????????      :
  1.??    ??   : 2013??07??18??
    ??    ??   : Y00213812
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

} TAF_PS_CALL_PDP_PDP_DISCONNECT_IND_STRU;


/*****************************************************************************
 ??????    : TAF_PS_COMMON_CNF_STRU
 ????????  : PS????????????????
 1.??    ??   : 2011??10??19??
   ??    ??   : A00165503
   ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
} TAF_PS_COMMON_CNF_STRU;


/*****************************************************************************
 ??????    : TAF_PDP_PRIM_CONTEXT_EXT_STRU
 ????????  : +CGDCONT????????, ??TS 27.007 section 10.1.1
 1.??    ?? : 2011??10??19??
   ??    ?? : A00165503
   ???????? : ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPdpType        : 1;                /* PdpType*/
    VOS_UINT32                          bitOpApn            : 1;                /* aucApn*/
    VOS_UINT32                          bitOpPdpAddr        : 1;                /* aucPdpAddr*/
    VOS_UINT32                          bitOpPdpDcomp       : 1;                /* PdpDcomp*/
    VOS_UINT32                          bitOpPdpHcomp       : 1;                /* PdpHcomp*/
    VOS_UINT32                          bitOpIpv4AddrAlloc  : 1;                /* Ipv4AddrAlloc*/
    VOS_UINT32                          bitOpEmergencyInd   : 1;                /* Emergency Indication*/
    VOS_UINT32                          bitOpPcscfDiscovery : 1;                /* P-CSCF discovery */
    VOS_UINT32                          bitOpImCnSignalFlg  : 1;                /* IM CN Signalling Flag */
    VOS_UINT32                          bitOpSpare          : 23;

    VOS_UINT8                           ucDefined;                              /* 0:undefined, 1:defined */

    VOS_UINT8                           ucCid;

    /* 1 IP Internet Protocol (IETF STD 5) */
    /* 2 IPV6 Internet Protocol, version 6 (IETF RFC 2460) */
    /* 3 IPV4V6 Virtual <PDP_type> introduced to handle dual IP stack UE capability. (See 3GPP TS 24.301 [83]) */
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;

    VOS_UINT8                           aucReserved[1];

    /* Access Point Name*/
    VOS_UINT8                           aucApn[TAF_MAX_APN_LEN + 1];

    /* the MT in the address space applicable to the PDP.*/
    TAF_PDP_ADDR_STRU                   stPdpAddr;

    /* 0 - off  (default if value is omitted) */
    /* 1 - on (manufacturer preferred compression) */
    /* 2 - V.42bis */
    /* 3 - V.44 */
    TAF_PDP_D_COMP_ENUM_UINT8           enPdpDcomp;

    /* 0 - off (default if value is omitted) */
    /* 1 - on (manufacturer preferred compression) */
    /* 2 - RFC1144 (applicable for SNDCP only) */
    /* 3 - RFC2507*/
    /* 4 - RFC3095 (applicable for PDCP only)*/
    TAF_PDP_H_COMP_ENUM_UINT8           enPdpHcomp;

    /* 0 - IPv4 Address Allocation through NAS Signaling (default if omitted) */
    /* 1 - IPv4 Address Allocated through DHCP */
    TAF_PDP_IPV4_ADDR_ALLOC_TYPE_ENUM_UINT8 enIpv4AddrAlloc;

    /* 0 - PDP context is not for emergency bearer services */
    /* 1 - PDP context is for emergency bearer services */
    TAF_PDP_EMC_IND_ENUM_UINT8          enEmergencyFlg;

    /* 0 - Preference of P-CSCF address discovery not influenced by +CGDCONT */
    /* 1 - Preference of P-CSCF address discovery through NAS Signalling */
    /* 2 - Preference of P-CSCF address discovery through DHCP */
    TAF_PDP_PCSCF_DISCOVERY_ENUM_UINT8  enPcscfDiscovery;

    /* 0 - UE indicates that the PDP context is not for IM CN subsystem-related signalling only */
    /* 1 - UE indicates that the PDP context is for IM CN subsystem-related signalling only */
    TAF_PDP_IM_CN_SIG_FLAG_ENUM_UINT8   enImCnSignalFlg;

    VOS_UINT8                           aucReserved2[2];

}TAF_PDP_PRIM_CONTEXT_EXT_STRU;

/*****************************************************************************
 ????????: TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ_STRU
 ????????: ID_MSG_TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ??
           ID_EVT_TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_CNF????

 ????????      :
  1.??    ??   : 2013??07??18??
    ??    ??   : Y00213812
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PDP_PRIM_CONTEXT_EXT_STRU       stPdpContextInfo;
} TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ_STRU;

typedef TAF_PS_COMMON_CNF_STRU TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_CNF_STRU;

/*****************************************************************************
 ????????: TAF_SET_IMS_PDP_CFG_STRU
 ????????: ^IMSPDPCFG????????

 ????????      :
  1.??    ??   : 2015??07??30??
    ??    ??   : z00301431
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucImsFlag;
    VOS_UINT8                           aucReserved[2];
} TAF_IMS_PDP_CFG_STRU;

/*****************************************************************************
 ????????: TAF_PS_SET_IMS_PDP_CFG_REQ_STRU
 ????????: ID_MSG_TAF_PS_SET_IMS_PDP_CFG_REQ
           ID_EVT_TAF_PS_SET_IMS_PDP_CFG_CNF????

 ????????      :
  1.??    ??   : 2015??07??30??
    ??    ??   : z00301431
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_IMS_PDP_CFG_STRU                stImsPdpCfg;
} TAF_PS_SET_IMS_PDP_CFG_REQ_STRU;

typedef TAF_PS_COMMON_CNF_STRU TAF_PS_SET_IMS_PDP_CFG_CNF_STRU;

/*****************************************************************************
 ????????  : TAF_PS_SET_1X_DORMANT_TIMER_REQ_STRU
 ????????  : ID_MSG_TAF_PS_SET_1X_MAX_NO_DATA_TIME_LEN_REQ??????????

  1.??    ??   : 2015??4??20??
    ??    ??   : y00314741
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    VOS_UINT8                           ucDormantTimer;
    VOS_UINT8                           aucReserved[3];
}TAF_PS_SET_1X_DORM_TIMER_REQ_STRU;

typedef TAF_PS_COMMON_CNF_STRU TAF_PS_SET_1X_DORM_TIMER_CNF_STRU;

/*****************************************************************************
 ????????  : TAF_PS_GET_1X_DORM_TIMER_VALUE_REQ_STRU
 ????????  : ID_MSG_TAF_PS_GET_CGMTU_VALUE_REQ??????????

  1.??    ??   : 2015??4??20??
    ??    ??   : y00314741
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
}TAF_PS_GET_1X_DORM_TIMER_REQ_STRU;

/*****************************************************************************
 ????????  : TAF_PS_GET_CGMTU_VALUE_CNF_STRU
 ????????  : ID_EVT_TAF_PS_GET_CGMTU_VALUE_CNF??????????

  1.??    ??   : 2015??4??20??
    ??    ??   : y00314741
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
    VOS_UINT8                           ucSocmDormTiVal;
    VOS_UINT8                           ucUserCfgDormTival;
    VOS_UINT8                           aucReserved[2];
}TAF_PS_GET_1X_DORM_TIMER_CNF_STRU;

/*****************************************************************************
 ????????: TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_REQ_STRU
 ????????: ID_MSG_TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_REQ????

 ????????      :
  1.??    ??   : 2013??07??18??
    ??    ??   : Y00213812
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
} TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_REQ_STRU;


/*****************************************************************************
 ????????: TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_REQ_STRU
 ????????: ID_MSG_TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_CNF????

 ????????      :
  1.??    ??   : 2013??07??18??
    ??    ??   : Y00213812
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    VOS_UINT32                          ulCidNum;
    TAF_PRI_PDP_QUERY_INFO_STRU         astPdpContextQueryInfo[0];
} TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_CNF_STRU;

/*****************************************************************************
 ???? : ???????? +CGDSCONT
 ID   : ID_MSG_TAF_PS_SET_SEC_PDP_CONTEXT_INFO_REQ
        ID_MSG_TAF_PS_SET_SEC_PDP_CONTEXT_INFO_CNF
        ID_MSG_TAF_PS_GET_SEC_PDP_CONTEXT_INFO_REQ
        ID_MSG_TAF_PS_GET_SEC_PDP_CONTEXT_INFO_CNF
 REQ  : TAF_PS_SET_SEC_PDP_CONTEXT_INFO_REQ_STRU; TAF_PS_GET_SEC_PDP_CONTEXT_INFO_REQ_STRU
 CNF  : TAF_PS_SET_SEC_PDP_CONTEXT_INFO_CNF_STRU; TAF_PS_GET_SEC_PDP_CONTEXT_INFO_CNF_STRU
 IND  : -
 ???? : ...
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpLinkdCid       : 1;
    VOS_UINT32                          bitOpPdpDcomp       : 1;
    VOS_UINT32                          bitOpPdpHcomp       : 1;
    VOS_UINT32                          bitOpSpare          : 29;

    VOS_UINT8                           ucDefined;          /* 0:undefined, 1:defined */
    VOS_UINT8                           ucCid;              /* dedicated EPS Bearer context */
    VOS_UINT8                           ucLinkdCid;         /* Default EPS Bearer context */
    TAF_PDP_D_COMP_ENUM_UINT8           enPdpDcomp;         /* no used in LTE */
    TAF_PDP_H_COMP_ENUM_UINT8           enPdpHcomp;         /* no used in LTE */
    VOS_UINT8                           aucReserved[3];

} TAF_PDP_SEC_CONTEXT_EXT_STRU;


/*****************************************************************************
 ??????    : TAF_PDP_SEC_CONTEXT_STRU
 ????????  : ??PDP??????????
 ????????  :
 1.??    ??   : 2012??07??24??
   ??    ??   : Y00213812
   ????????   : ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCid;              /* [1??11] */
    VOS_UINT8                           ucLinkdCid;         /* [1??11] */
    TAF_PDP_D_COMP_ENUM_UINT8           enPdpDcomp;         /*????????????*/
    TAF_PDP_H_COMP_ENUM_UINT8           enPdpHcomp;         /*??????????*/

}TAF_PDP_SEC_CONTEXT_STRU;


/*****************************************************************************
 ??????    : TAF_PS_SET_SEC_PDP_CONTEXT_INFO_REQ_STRU
 ????????  : ??PDP??????????????
 ????????  :
 1.??    ??   : 2012??07??24??
   ??    ??   : Y00213812
   ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PDP_SEC_CONTEXT_EXT_STRU        stPdpContextInfo;

} TAF_PS_SET_SEC_PDP_CONTEXT_INFO_REQ_STRU;

typedef TAF_PS_COMMON_CNF_STRU TAF_PS_SET_SEC_PDP_CONTEXT_INFO_CNF_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
} TAF_PS_GET_SEC_PDP_CONTEXT_INFO_REQ_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    VOS_UINT32                          ulCidNum;
    TAF_PDP_SEC_CONTEXT_STRU            astPdpContextQueryInfo[0];
} TAF_PS_GET_SEC_PDP_CONTEXT_INFO_CNF_STRU;


/*****************************************************************************
 ???? : ???????? +CGACT
 ID   : ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ
        ID_MSG_TAF_PS_SET_PDP_STATE_CNF
        ID_MSG_TAF_PS_GET_PDP_CONTEXT_STATE_REQ
        ID_MSG_TAF_PS_GET_PDP_STATE_CNF
 REQ  : TAF_PS_SET_PDP_STATE_REQ_STRU     TAF_PS_GET_PDP_STATE_REQ_STRU
 CNF  : TAF_PS_SET_PDP_STATE_CNF_STRU TAF_PS_GET_PDP_STATE_CNF_STRU
 IND  : -
 ???? : ...
*****************************************************************************
*****************************************************************************
 ??????    : TAF_CID_LIST_STRU
 ????????  : CID??????????
 1.??    ??   : 2011??10??19??
   ??    ??   : A00165503
   ????????   : ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucCid[TAF_MAX_CID + 1];
} TAF_CID_LIST_STRU;

/*****************************************************************************
 ??????    : TAF_CID_STATE_STRU
 ????????  : CID??????????
 1.??    ??   : 2011??10??19??
   ??    ??   : A00165503
   ????????   : ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucState;
    VOS_UINT8                           aucReserved[2];
} TAF_CID_STATE_STRU;

/*****************************************************************************
 ??????    : TAF_CID_LIST_STATE_STRU
 ????????  : CID??????????????
 1.??    ??   : 2011??10??19??
   ??    ??   : A00165503
   ????????   : ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucState;                                /* 0 - deactivated,1 - activated */
    VOS_UINT8                           aucReserved[3];

    VOS_UINT8                           aucCid[TAF_MAX_CID + 1];
} TAF_CID_LIST_STATE_STRU;

/*****************************************************************************
 ??????    : TAF_PS_SET_PDP_STATE_REQ_STRU
 ????????  : CID??????????
 1.??    ??   : 2011??10??19??
   ??    ??   : A00165503
   ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_CID_LIST_STATE_STRU             stCidListStateInfo;
} TAF_PS_SET_PDP_STATE_REQ_STRU;

/*****************************************************************************
 ??????    : TAF_PS_CALL_END_REQ_STRU
 ????????  : ID_EVT_TAF_PS_SET_PDP_CONTEXT_STATE_CNF????????

 ????????      :
  1.??    ??   : 2011??08??22??
    ??    ??   : A00165503
    ????????   : ????????

  2.??    ??   : 2012??8??22??
    ??    ??   : A00165503
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
} TAF_PS_SET_PDP_STATE_CNF_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
} TAF_PS_GET_PDP_STATE_REQ_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    VOS_UINT32                          ulCidNum;
    TAF_CID_STATE_STRU                  astCidStateInfo[0];
} TAF_PS_GET_PDP_STATE_CNF_STRU;


/*****************************************************************************
 ???? : ???????? +CGTFT
 ID   : ID_MSG_L4A_SET_CGTFT_REQ
        ID_MSG_L4A_SET_CGTFT_CNF
        ID_MSG_L4A_READ_CGTFT_REQ
        ID_MSG_L4A_READ_CGTFT_CNF
 REQ  : L4A_SET_CGTFT_REQ_STRU;L4A_READ_CGTFT_REQ_STRU;
 CNF  : L4A_SET_CGTFT_CNF_STRU;L4A_READ_CGTFT_CNF_STRU;
 IND  : -
 ???? : ...
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPktFilterId    : 1;    /* ucPacketFilterId*/
    VOS_UINT32                          bitOpPrecedence     : 1;    /* ucPrecedence*/
    VOS_UINT32                          bitOpSrcIp          : 1;    /* aucSourceIpAddr,Mask*/
    VOS_UINT32                          bitOpProtocolId     : 1;    /* ucProtocolId*/
    VOS_UINT32                          bitOpDestPortRange  : 1;    /* destination port range*/
    VOS_UINT32                          bitOpSrcPortRange   : 1;    /* source port range*/
    VOS_UINT32                          bitOpSpi            : 1;    /* ipsec security parameter index*/
    VOS_UINT32                          bitOpTosMask        : 1;    /* type of service*/
    VOS_UINT32                          bitOpFlowLable      : 1;    /* ulFlowLable*/
    VOS_UINT32                          bitOpDirection      : 1;    /* Direction*/
    VOS_UINT32                          bitOpNwPktFilterId  : 1;    /* NWPacketFltId*/
    VOS_UINT32                          bitOpLocalIpv4AddrAndMask      : 1;
    VOS_UINT32                          bitOpLocalIpv6AddrAndMask      : 1;
    VOS_UINT32                          bitOpSpare          : 19;

    VOS_UINT8                           ucCid;

    VOS_UINT8                           ucDefined;

    VOS_UINT8                           ucPacketFilterId;       /* Packet Filter Id,value range from 1 to 16*/

    VOS_UINT8                           ucPrecedence;           /* evaluation precedence index,The value range is from 0 to 255*/

    VOS_UINT8                           ucProtocolId;           /* protocol number,value range from 0 to 255*/

    VOS_UINT8                           aucReserved[3];

    /* source address and subnet mask*/
    TAF_PDP_ADDR_STRU                   stSourceIpaddr;
    TAF_PDP_ADDR_STRU                   stSourceIpMask;

    /* destination port range*/
    VOS_UINT16                          usLowDestPort;                          /* value range from 0 to 65535*/
    VOS_UINT16                          usHighDestPort;                         /* value range from 0 to 65535*/

    /* source port range*/
    VOS_UINT16                          usLowSourcePort;                        /* value range from 0 to 65535*/
    VOS_UINT16                          usHighSourcePort;                       /* value range from 0 to 65535*/

    /* ipsec security parameter index*/
    VOS_UINT32                          ulSecuParaIndex;

    /* only for ipv6*/
    VOS_UINT32                          ulFlowLable;                            /* value range is from 00000 to FFFFF*/

    /* type of service*/
    VOS_UINT8                           ucTypeOfService;                        /* value range from 0 to 255*/
    VOS_UINT8                           ucTypeOfServiceMask;                    /* value range from 0 to 255*/

    /* 0 - Pre-Release 7 TFT filter (see 3GPP TS 24.008 [8], table 10.5.162)*/
    /* 1 - Uplink*/
    /* 2 - Downlink*/
    /* 3 - Birectional (Up & Downlink) (default if omitted)*/
    VOS_UINT8                           ucDirection;

    /* only for CGTFTRDP*/
    VOS_UINT8                           ucNwPktFilterId;                        /* value range from 1 to 16*/

    /* local address and subnet mask*/
    VOS_UINT8                           aucLocalIpv4Addr[TAF_IPV4_ADDR_LEN];
    VOS_UINT8                           aucLocalIpv4Mask[TAF_IPV4_ADDR_LEN];
    VOS_UINT8                           aucLocalIpv6Addr[TAF_IPV6_ADDR_LEN];
    VOS_UINT8                           ucLocalIpv6Prefix;
    VOS_UINT8                           aucReserved2[3];
} TAF_TFT_EXT_STRU;

typedef struct
{
    VOS_UINT32                          ulCid;
    VOS_UINT32                          ulPFNum;
    TAF_TFT_EXT_STRU                    astTftInfo[TAF_MAX_SDF_PF_NUM];
} TAF_PF_TFT_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_TFT_EXT_STRU                    stTftInfo;
} TAF_PS_SET_TFT_INFO_REQ_STRU;

typedef TAF_PS_COMMON_CNF_STRU TAF_PS_SET_TFT_INFO_CNF_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
} TAF_PS_GET_TFT_INFO_REQ_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    VOS_UINT32                          ulCidNum;
    TAF_TFT_QUREY_INFO_STRU             astTftQueryInfo[0];
} TAF_PS_GET_TFT_INFO_CNF_STRU;


/*****************************************************************************
 ???? : ???????? +CGEQREQ
 ID   :



 REQ  :
 CNF  :
 IND  : -
 ???? : ...
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpTrafficClass       : 1;
    VOS_UINT32                          bitOpDeliverOrder       : 1;
    VOS_UINT32                          bitOpDeliverErrSdu      : 1;
    VOS_UINT32                          bitOpMaxSduSize         : 1;
    VOS_UINT32                          bitOpMaxBitUl           : 1;
    VOS_UINT32                          bitOpMaxBitDl           : 1;
    VOS_UINT32                          bitOpResidualBer        : 1;
    VOS_UINT32                          bitOpSduErrRatio        : 1;
    VOS_UINT32                          bitOpTransDelay         : 1;
    VOS_UINT32                          bitOpTraffHandlePrior   : 1;
    VOS_UINT32                          bitOpGtdBitUl           : 1;
    VOS_UINT32                          bitOpGtdBitDl           : 1;
    VOS_UINT32                          bitOpSrcStatisticsDes   : 1;
    VOS_UINT32                          bitOpSignalIndication   : 1;
    VOS_UINT32                          bitOpSpare              : 18;

    VOS_UINT8                           ucDefined;

    VOS_UINT8                           ucCid;

    VOS_UINT8                           ucTrafficClass;     /* 0 : Conversational class
                                                               1 : Streaming class
                                                               2 : Interactive class
                                                               3 : Background class
                                                               4 : Subscribed value */
    VOS_UINT8                           ucSduErrRatio;      /* 0 : subscribed value
                                                               1 : 1*10-2
                                                               2 : 7*10-3
                                                               3 : 1*10-3
                                                               4 : 1*10-4
                                                               5 : 1*10-5
                                                               6 : 1*10-6
                                                               7 : 1*10-1 */
    VOS_UINT16                          usMaxSduSize;       /* 0 : Subscribed value
                                                               1~1520: 1 ~1520 octets */

    VOS_UINT8                           ucDeliverOrder;     /* 0 : Without delivery order
                                                               1 : With delivery order
                                                               2 : Subscribed value */

    VOS_UINT8                           ucDeliverErrSdu;    /* 0 : Erroneous SDUs are not delivered
                                                               1 : Erroneous SDUs are delivered
                                                               2 : No detect
                                                               3 : subscribed value */

    VOS_UINT32                          ulMaxBitUl;         /* 0 : Subscribed value
                                                               1~256000: 1kbps ~ 256000kbps*/
    VOS_UINT32                          ulMaxBitDl;         /* ??ulMaxBitUl */
    VOS_UINT32                          ulGtdBitUl;         /* ??ulMaxBitUl */
    VOS_UINT32                          ulGtdBitDl;         /* ??ulMaxBitUl */
    VOS_UINT8                           ucResidualBer;      /* 0 : subscribed value
                                                               1 : 5*10-2
                                                               2 : 1*10-2
                                                               3 : 5*10-3
                                                               4 : 4*10-3
                                                               5 : 1*10-3
                                                               6 : 1*10-4
                                                               7 : 1*10-5
                                                               8 : 1*10-6
                                                               9 : 6*10-8 */
    VOS_UINT8                           ucTraffHandlePrior; /* 0 : Subscribed value
                                                               1 : Priority level 1
                                                               2 : Priority level 2
                                                               3 : Priority level 3 */
    VOS_UINT16                          usTransDelay;       /* 0 : Subscribed value
                                                               1~4100 : 1ms~4100ms */

    VOS_UINT8                           ucSrcStatisticsDes; /* 0: Characteristics of SDUs is unknown
                                                               1: Characteristics of SDUs corresponds to a speech source */

    VOS_UINT8                           ucSignalIndication; /* 0: PDP context is not optimized for signalling
                                                               1: PDP context is optimized for signalling */

    VOS_UINT8                           aucReserved[2];

} TAF_UMTS_QOS_EXT_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_UMTS_QOS_EXT_STRU               stUmtsQosInfo;
} TAF_PS_SET_UMTS_QOS_INFO_REQ_STRU;

typedef TAF_PS_COMMON_CNF_STRU TAF_PS_SET_UMTS_QOS_INFO_CNF_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
} TAF_PS_GET_UMTS_QOS_INFO_REQ_STRU;

/*****************************************************************************
 ????????: TAF_UMTS_QOS_QUERY_INFO_STRU
 ????????: ID_EVT_TAF_PS_GET_UMTS_QOS_INFO_CNF????????

 ????????      :
  1.??    ??   : 2013??07??18??
    ??    ??   : Y00213812
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    VOS_UINT32                          ulCidNum;
    TAF_UMTS_QOS_QUERY_INFO_STRU        astUmtsQosQueryInfo[0];
} TAF_PS_GET_UMTS_QOS_INFO_CNF_STRU;


/*****************************************************************************
 ???? : ???????? +CGEQMIN
 ID   :



 REQ  :
 CNF  :
 IND  : -
 ???? : ...
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_UMTS_QOS_EXT_STRU               stUmtsQosMinInfo;
} TAF_PS_SET_UMTS_QOS_MIN_INFO_REQ_STRU;

typedef TAF_PS_COMMON_CNF_STRU TAF_PS_SET_UMTS_QOS_MIN_INFO_CNF_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
} TAF_PS_GET_UMTS_QOS_MIN_INFO_REQ_STRU;

/*****************************************************************************
 ????????: TAF_UMTS_QOS_QUERY_INFO_STRU
 ????????: ID_EVT_TAF_PS_GET_UMTS_QOS_MIN_INFO_CNF????????

 ????????      :
  1.??    ??   : 2013??07??18??
    ??    ??   : Y00213812
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    VOS_UINT32                          ulCidNum;
    TAF_UMTS_QOS_QUERY_INFO_STRU        astUmtsQosQueryInfo[0];
} TAF_PS_GET_UMTS_QOS_MIN_INFO_CNF_STRU;


/*****************************************************************************
 ???? : ???????? +CGEQNEG
 ID   :



 REQ  :
 CNF  :
 IND  : -
 ???? : ...
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_CID_LIST_STRU                   stCidListInfo;
} TAF_PS_GET_DYNAMIC_UMTS_QOS_INFO_REQ_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    VOS_UINT32                          ulCidNum;
    TAF_UMTS_QOS_QUERY_INFO_STRU        astUmtsQosQueryInfo[0];
} TAF_PS_GET_DYNAMIC_UMTS_QOS_INFO_CNF_STRU;


/*****************************************************************************
 ???? : ???????? +CGMOD
 ID   :



 REQ  :
 CNF  :
 IND  : -
 ???? : ...
*****************************************************************************/

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_CID_LIST_STRU                   stCidListInfo;
} TAF_PS_CALL_MODIFY_REQ_STRU;

typedef TAF_PS_COMMON_CNF_STRU TAF_PS_CALL_MODIFY_CNF_STRU;


/*****************************************************************************
 ???? : ???????? +CGANS
 ID   : ID_MSG_L4A_SET_CGANS_RSP
        ID_MSG_L4A_SET_CGANS_CNF
        ID_MSG_L4A_CGANS_IND
 RSP  : L4A_SET_CGANS_RSP_STRU
 CNF  : L4A_SET_CGANS_CNF_STRU
 IND  : L4A_CGANS_IND_STRU
 ???? : L4A_CGANS_IND_STRU ??????????????,??????????????????????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucL2P[20];
    VOS_UINT8                           ucCid;
    /* Added by l60609 for V3R3 PPP RPOJECT 2013-06-07, Begin */
    VOS_UINT8                           ucAnsExtFlg;                            /* ??????^CGANS????????VOS_TRUE????????VOS_FALSE */
    VOS_UINT8                           aucReserved[2];
    /* Added by l60609 for V3R3 PPP RPOJECT 2013-06-07, End */
} TAF_PS_ANSWER_STRU;


typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_ANSWER_STRU                  stAnsInfo;
} TAF_PS_CALL_ANSWER_REQ_STRU;


typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;

    VOS_UINT8                           ucCid;

    VOS_UINT8                           aucReserved[3];
}TAF_PS_CALL_ANSWER_CNF_STRU;


typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
} TAF_PS_CALL_HANGUP_REQ_STRU;

typedef TAF_PS_COMMON_CNF_STRU TAF_PS_CALL_HANGUP_CNF_STRU;


/*****************************************************************************
 ???? : ???????? +CGPADDR
 ID   :


 REQ  :
 CNF  :
 IND  : -
 ???? : ...
*****************************************************************************/
/*****************************************************************************
 ????????   : TAF_PDP_ADDR_STRU
 ????????   :
 ????????   :
*****************************************************************************/

typedef struct
{
    VOS_UINT8                           ucCid;
    VOS_UINT8                           aucReserved[3];

    /* the MT in the address space applicable to the PDP */
    TAF_PDP_ADDR_STRU                   stPdpAddr;
} TAF_PDP_ADDR_QUERY_INFO_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_CID_LIST_STRU                   stCidListInfo;
} TAF_PS_GET_PDP_IP_ADDR_INFO_REQ_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    VOS_UINT32                          ulCidNum;
    TAF_PDP_ADDR_QUERY_INFO_STRU        astPdpAddrQueryInfo[0];
} TAF_PS_GET_PDP_IP_ADDR_INFO_CNF_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    VOS_UINT32                          ulCidNum;
    VOS_UINT32                          ulCid[TAF_MAX_CID+1];
} TAF_PS_GET_PDP_CONTEXT_INFO_CNF_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
} TAF_PS_GET_PDP_CONTEXT_INFO_REQ_STRU;

/*****************************************************************************
 ???? : ???????? +CGAUTO
 ID   : ID_MSG_L4A_SET_CGAUTO_REQ
        ID_MSG_L4A_SET_CGAUTO_CNF
        ID_MSG_L4A_READ_CGAUTO_REQ
        ID_MSG_L4A_READ_CGAUTO_CNF
 REQ  : L4A_SET_CGAUTO_REQ_STRU; L4A_READ_CGAUTO_REQ_STRU
 CNF  : L4A_SET_CGAUTO_CNF_STRU; L4A_READ_CGAUTO_CNF_STRU
 IND  : -
 ???? : ...
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    VOS_UINT32                          ulAnsMode;
} TAF_PS_SET_ANSWER_MODE_INFO_REQ_STRU;

typedef TAF_PS_COMMON_CNF_STRU TAF_PS_SET_ANSWER_MODE_INFO_CNF_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
} TAF_PS_GET_ANSWER_MODE_INFO_REQ_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    VOS_UINT32                          ulAnsMode;
} TAF_PS_GET_ANSWER_MODE_INFO_CNF_STRU;


/*****************************************************************************
 ???? : ???????? +CGCONTRDP
 ID   : ID_MSG_L4A_SET_CGCONTRDP_REQ
        ID_MSG_L4A_SET_CGCONTRDP_CNF
 REQ  : L4A_SET_CGCONTRDP_REQ_STRU
 CNF  : L4A_SET_CGCONTRDP_CNF_STRU
 IND  : -
 ???? : ...
******************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpBearerId       : 1;                /* BearerId*/
    VOS_UINT32                          bitOpApn            : 1;                /* aucApn*/
    VOS_UINT32                          bitOpIpAddr         : 1;                /* aucIpaddr*/
    VOS_UINT32                          bitOpSubMask        : 1;                /* aucSubnetMask*/
    VOS_UINT32                          bitOpGwAddr         : 1;                /* aucGWAddr*/
    VOS_UINT32                          bitOpDNSPrimAddr    : 1;                /* aucDNSPrimAddr*/
    VOS_UINT32                          bitOpDNSSecAddr     : 1;                /* aucDNSSecAddr*/
    VOS_UINT32                          bitOpPCSCFPrimAddr  : 1;                /* aucPCSCFPrimAddr*/
    VOS_UINT32                          bitOpPCSCFSecAddr   : 1;                /* aucPCSCFSecAddr*/
    VOS_UINT32                          bitOpImCnSignalFlg  : 1;
    VOS_UINT32                          bitOpSpare          : 22;

    VOS_UINT8                           ucPrimayCid;                            /* default EPS bearer context*/
    VOS_UINT8                           ucBearerId;                             /* a numeric parameter which identifies the bearer*/

    /* the IM CN subsystem-related signalling flag */
    TAF_PDP_IM_CN_SIG_FLAG_ENUM_UINT8   enImCnSignalFlg;

    VOS_UINT8                           aucReserved[1];

    /* Access Pointer Name*/
    VOS_UINT8                           aucApn[TAF_MAX_APN_LEN + 1];

    /* the IP Address of the MT*/
    TAF_PDP_ADDR_STRU                   stPdpAddr;

    /* the subnet mask for the IP Address of the MT*/
    TAF_PDP_ADDR_STRU                   stSubnetMask;

    /* the Gateway Address of the MT*/
    TAF_PDP_ADDR_STRU                   stGWAddr;

    /* the IP Address of the primary DNS Server*/
    TAF_PDP_ADDR_STRU                   stDNSPrimAddr;

    /* the IP address of the secondary DNS Server*/
    TAF_PDP_ADDR_STRU                   stDNSSecAddr;

    /* the IP Address of the primary P-CSCF Server*/
    TAF_PDP_ADDR_STRU                   stPCSCFPrimAddr;

    /* the IP Address of the secondary P-CSCF Server*/
    TAF_PDP_ADDR_STRU                   stPCSCFSecAddr;

} TAF_PDP_DYNAMIC_PRIM_EXT_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    /* 0xff-if the parameter <cid> is omitted */
    VOS_UINT8                           ucCid;
    VOS_UINT8                           aucReserved[3];
} TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_REQ_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    VOS_UINT32                          ulCidNum;
    TAF_PDP_DYNAMIC_PRIM_EXT_STRU       astPdpContxtInfo[0];
} TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_CNF_STRU;


/*****************************************************************************
 ???? : ???????? +CGSCONTRDP
 ID   : ID_MSG_L4A_SET_CGSCONTRDP_REQ
        ID_MSG_L4A_SET_CGSCONTRDP_CNF
 REQ  : L4A_SET_CGSCONTRDP_REQ_STRU
 CNF  : L4A_SET_CGSCONTRDP_CNF_STRU
 IND  : -
 ???? : ...
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCid;

    /* default EPS bearer context */
    VOS_UINT8                           ucPrimaryCid;

    /* a numeric parameter which identifies the bearer */
    VOS_UINT8                           ucBearerId;

    VOS_UINT8                           ucReserved[1];
} TAF_PDP_DYNAMIC_SEC_EXT_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    /* 0xff-if the parameter <cid> is omitted */
    VOS_UINT8                           ucCid;
    VOS_UINT8                           aucReserved[3];
} TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_REQ_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    VOS_UINT32                          ulCidNum;
    TAF_PDP_DYNAMIC_SEC_EXT_STRU        astPdpContxtInfo[0];
} TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_CNF_STRU;


/*****************************************************************************
 ???? : ???????? +CGTFTRDP
 ID   : ID_MSG_L4A_SET_CGTFTRDP_REQ
        ID_MSG_L4A_SET_CGTFTRDP_CNF
 REQ  : L4A_SET_CGTFTRDP_REQ_STRU
 CNF  : L4A_SET_CGTFTRDP_CNF_STRU
 IND  : -
 ???? : ...
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    /* 0xff-if the parameter <cid> is omitted */
    VOS_UINT8                           ucCid;
    VOS_UINT8                           aucReserved[3];
} TAF_PS_GET_DYNAMIC_TFT_INFO_REQ_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    VOS_UINT32                          ulCidNum;
    TAF_PF_TFT_STRU                     astPfTftInfo[0];
} TAF_PS_GET_DYNAMIC_TFT_INFO_CNF_STRU;


/*****************************************************************************
 ???? : ???????? +CGEQOS
 ID   : ID_MSG_L4A_SET_CGEQOS_REQ
        ID_MSG_L4A_SET_CGEQOS_CNF
        ID_MSG_L4A_READ_CGEQOS_REQ
        ID_MSG_L4A_READ_CGEQOS_CNF
 REQ  : L4A_SET_CGEQOS_REQ_STRU L4A_READ_CGEQOS_REQ_STRU
 CNF  : L4A_SET_CGEQOS_CNF_STRU L4A_READ_CGEQOS_CNF_STRU
 IND  : -
 ???? : ...
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpQCI            : 1;                /* QCI*/
    VOS_UINT32                          bitOpDLGBR          : 1;                /* DLGBR*/
    VOS_UINT32                          bitOpULGBR          : 1;                /* ULGBR*/
    VOS_UINT32                          bitOpDLMBR          : 1;                /* DLMBR*/
    VOS_UINT32                          bitOpULMBR          : 1;                /* ULMBR*/
    VOS_UINT32                          bitOpSpare          : 27;

    VOS_UINT8                           ucCid;

    /* 0 QCI is selected by network*/
    /* [1 - 4]value range for guranteed bit rate Traffic Flows*/
    /* [5 - 9]value range for non-guarenteed bit rate Traffic Flows*/
    VOS_UINT8                           ucQCI;

    VOS_UINT8                           ucReserved[2];

    /* DL GBR in case of GBR QCI, The value is in kbit/s*/
    VOS_UINT32                          ulDLGBR;

    /* UL GBR in case of GBR QCI, The value is in kbit/s*/
    VOS_UINT32                          ulULGBR;

    /* DL MBR in case of GBR QCI, The value is in kbit/s*/
    VOS_UINT32                          ulDLMBR;

    /* UL MBR in case of GBR QCI, The value is in kbit/s*/
    VOS_UINT32                          ulULMBR;
}TAF_EPS_QOS_EXT_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_EPS_QOS_EXT_STRU                stEpsQosInfo;
} TAF_PS_SET_EPS_QOS_INFO_REQ_STRU;

typedef TAF_PS_COMMON_CNF_STRU TAF_PS_SET_EPS_QOS_INFO_CNF_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
} TAF_PS_GET_EPS_QOS_INFO_REQ_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    VOS_UINT32                          ulCidNum;
    TAF_EPS_QOS_EXT_STRU                astEpsQosInfo[0];
} TAF_PS_GET_EPS_QOS_INFO_CNF_STRU;


/*****************************************************************************
 ???? : ???????? +CGEQOSRDP
 ID   : ID_MSG_L4A_SET_CGEQOSRDP_REQ
        ID_MSG_L4A_SET_CGEQOSRDP_CNF
 REQ  : L4A_SET_CGEQOSRDP_REQ_STRU
 CNF  : L4A_SET_CGEQOSRDP_CNF_STRU
 IND  : -
 ???? : ...
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    /* 0xff-if the parameter <cid> is omitted */
    VOS_UINT8                           ucCid;
    VOS_UINT8                           aucReserved[3];
} TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_REQ_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    VOS_UINT32                          ulCidNum;
    TAF_EPS_QOS_EXT_STRU                astEpsQosInfo[0];
} TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_CNF_STRU;


/*****************************************************************************
 ??????    : TAF_PS_GET_DSFLOW_INFO_REQ_STRU
 ????????  : ID_MSG_TAF_PS_GET_DSFLOW_INFO_REQ??????????, ????????????
 1.??    ??   : 2011??10??19??
   ??    ??   : A00165503
   ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    VOS_UINT8                           aucReserve[4];
} TAF_PS_GET_DSFLOW_INFO_REQ_STRU;

/*****************************************************************************
 ??????    : TAF_PS_GET_DSFLOW_INFO_CNF_STRU
 ????????  : ID_MSG_TAF_PS_GET_DSFLOW_INFO_CNF??????????, ????????????
  1.??    ??   : 2011??10??19??
   ??    ??   : A00165503
   ????????   : ????????

  2.??    ??   : 2011??12??23??
    ??    ??   : o00132663
    ????????   : PS????????????????????????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    TAF_DSFLOW_QUERY_INFO_STRU          stQueryInfo;
} TAF_PS_GET_DSFLOW_INFO_CNF_STRU;


/*****************************************************************************
 ???? : ???????? ^DSFLOWCLR
 ID   :

 REQ  :
 CNF  :
 IND  : -
 ???? : ...
*****************************************************************************/
/*****************************************************************************
 ??????    : TAF_DSFLOW_CLEAR_CONFIG_STRU
 ????????  : ????????????
*****************************************************************************/
typedef struct
{
    TAF_DSFLOW_CLEAR_MODE_ENUM_UINT8    enClearMode;
    VOS_UINT8                           ucNsapi;
    VOS_UINT8                           aucReserved[2];
} TAF_DSFLOW_CLEAR_CONFIG_STRU;

/*****************************************************************************
 ??????    : TAF_PS_CLEAR_DSFLOW_REQ_STRU
 ????????  : ID_MSG_TAF_PS_CLEAR_DSFLOW_REQ??????????, ????????????
 1.??    ??   : 2011??10??19??
   ??    ??   : A00165503
   ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_DSFLOW_CLEAR_CONFIG_STRU        stClearConfigInfo;
} TAF_PS_CLEAR_DSFLOW_REQ_STRU;

/*****************************************************************************
 ??????    : TAF_PS_CLEAR_DSFLOW_CNF_STRU
 ????????  : ID_MSG_TAF_PS_CLEAR_DSFLOW_CNF??????????, ????????????
 1.??    ??   : 2011??10??19??
   ??    ??   : A00165503
   ????????   : ????????
*****************************************************************************/
typedef TAF_PS_COMMON_CNF_STRU TAF_PS_CLEAR_DSFLOW_CNF_STRU;


/*****************************************************************************
 ???? : ???????? ^DSFLOWRPT
 ID   :

 REQ  :
 CNF  :
 IND  : -
 ???? : ...
*****************************************************************************/
/*****************************************************************************
 ??????    : TAF_DSFLOW_REPORT_CONFIG_STRU
 ????????  : ??????????????????
 1.??    ??   : 2011??10??19??
   ??    ??   : A00165503
   ????????   : ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRptEnabled;       /* ????????????????   */
    VOS_UINT32                          ulTimerLength;      /* ?????????????????? */
} TAF_DSFLOW_REPORT_CONFIG_STRU;

/*****************************************************************************
 ??????    : TAF_PS_CONFIG_DSFLOW_RPT_REQ_STRU
 ????????  : ID_MSG_TAF_PS_CONFIG_DSFLOW_RPT_REQ??????????, ????????????
 1.??    ??   : 2011??10??19??
   ??    ??   : A00165503
   ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_DSFLOW_REPORT_CONFIG_STRU       stReportConfigInfo;
} TAF_PS_CONFIG_DSFLOW_RPT_REQ_STRU;

/*****************************************************************************
 ??????    : TAF_PS_CONFIG_DSFLOW_RPT_CNF_STRU
 ????????  : ID_MSG_TAF_PS_CONFIG_DSFLOW_RPT_CNF??????????, ????????????
 1.??    ??   : 2011??10??19??
   ??    ??   : A00165503
   ????????   : ????????
*****************************************************************************/
typedef TAF_PS_COMMON_CNF_STRU TAF_PS_CONFIG_DSFLOW_RPT_CNF_STRU;

/*****************************************************************************
 ??????    : TAF_PS_DSFLOW_RPT_IND_STRU
 ????????  : ID_MSG_TAF_PS_DSFLOW_RPT_IND??????????, ????????????
 1.??    ??   : 2011??10??19??
   ??    ??   : A00165503
   ????????   : ????????

  2.??    ??   : 2011??12??23??
    ??    ??   : o00132663
    ????????   : PS????????????????????????????????TAF_DSFLOW_REPORT_STRU

*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    TAF_DSFLOW_REPORT_STRU              stDsFlowRptInfo;
} TAF_PS_REPORT_DSFLOW_IND_STRU;


/*****************************************************************************
 ???? : ???????? ^APDSFLOWRPT
 ID   :

 REQ  :
 CNF  :
 IND  : -
 ???? : ...
*****************************************************************************/
/*****************************************************************************
 ????????  : TAF_APDSFLOW_RPT_CFG_STRU
 ????????  : AP??????????????????

  1.??    ??   : 2015??2??2??
    ??    ??   : A00165503
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRptEnabled;       /* ????????????????   */
    VOS_UINT32                          ulFluxThreshold;    /* ????????????, ????KByte */
} TAF_APDSFLOW_RPT_CFG_STRU;


/*****************************************************************************
 ??????    : TAF_APDSFLOW_REPORT_STRU
 ????????  : ????????????????????

  1.??    ??   : 2015??2??2??
    ??    ??   : A00165503
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCurrentTxRate;    /*????????????*/
    VOS_UINT32                          ulCurrentRxRate;    /*????????????*/
    TAF_DSFLOW_INFO_STRU                stCurrentFlowInfo;  /*????????????????*/
    TAF_DSFLOW_INFO_STRU                stTotalFlowInfo;    /*????????????*/
} TAF_APDSFLOW_REPORT_STRU;


/*****************************************************************************
 ????????  : TAF_PS_CONFIG_APDSFLOW_RPT_REQ_STRU
 ????????  : ID_MSG_TAF_PS_SET_APDSFLOW_CFG_REQ??????????

  1.??    ??   : 2015??2??2??
    ??    ??   : A00165503
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_APDSFLOW_RPT_CFG_STRU           stRptCfg;
} TAF_PS_SET_APDSFLOW_RPT_CFG_REQ_STRU;


/*****************************************************************************
 ????????  : TAF_PS_SET_APDSFLOW_RPT_CFG_CNF_STRU
 ????????  : ID_EVT_TAF_PS_SET_APDSFLOW_RPT_CFG_CNF??????????

  1.??    ??   : 2015??2??2??
    ??    ??   : A00165503
    ????????   : ????????
*****************************************************************************/
typedef TAF_PS_COMMON_CNF_STRU TAF_PS_SET_APDSFLOW_RPT_CFG_CNF_STRU;


/*****************************************************************************
 ????????  : TAF_PS_GET_APDSFLOW_RPT_CFG_REQ_STRU
 ????????  : ID_MSG_TAF_PS_GET_APDSFLOW_RPT_CFG_REQ??????????

  1.??    ??   : 2015??2??2??
    ??    ??   : A00165503
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
} TAF_PS_GET_APDSFLOW_RPT_CFG_REQ_STRU;


/*****************************************************************************
 ????????  : TAF_PS_GET_APDSFLOW_RPT_CFG_CNF_STRU
 ????????  : ID_EVT_TAF_PS_GET_APDSFLOW_RPT_CFG_CNF??????????

  1.??    ??   : 2015??2??2??
    ??    ??   : A00165503
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    TAF_APDSFLOW_RPT_CFG_STRU           stRptCfg;
} TAF_PS_GET_APDSFLOW_RPT_CFG_CNF_STRU;


/*****************************************************************************
 ????????  : TAF_PS_APDSFLOW_REPORT_IND_STRU
 ????????  : ID_EVT_TAF_PS_APDSFLOW_REPORT_IND??????????

  1.??    ??   : 2015??2??2??
    ??    ??   : A00165503
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_APDSFLOW_REPORT_STRU            stApDsFlowRptInfo;
} TAF_PS_APDSFLOW_REPORT_IND_STRU;


/*****************************************************************************
 ????????  : TAF_DSFLOW_NV_WRITE_CFG_STRU
 ????????  : ??????NV??????????

  1.??    ??   : 2015??2??2??
    ??    ??   : A00165503
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnabled;          /* ??????NV????????   */
    VOS_UINT8                           ucInterval;         /* ??????NV????, ????min */
    VOS_UINT8                           aucReserved[2];     /* ???????? */
} TAF_DSFLOW_NV_WRITE_CFG_STRU;


/*****************************************************************************
 ????????  : TAF_PS_SET_DSFLOW_NV_WRITE_CFG_REQ_STRU
 ????????  : ID_MSG_TAF_PS_SET_DSFLOW_NV_WRITE_CFG_REQ??????????

  1.??    ??   : 2015??2??12??
    ??    ??   : A00165503
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_DSFLOW_NV_WRITE_CFG_STRU        stNvWriteCfg;
} TAF_PS_SET_DSFLOW_NV_WRITE_CFG_REQ_STRU;


/*****************************************************************************
 ????????  : TAF_PS_SET_DSFLOW_NV_WRITE_CFG_CNF_STRU
 ????????  : ID_EVT_TAF_PS_SET_DSFLOW_NV_WRITE_CFG_CNF??????????

  1.??    ??   : 2015??2??12??
    ??    ??   : A00165503
    ????????   : ????????
*****************************************************************************/
typedef TAF_PS_COMMON_CNF_STRU TAF_PS_SET_DSFLOW_NV_WRITE_CFG_CNF_STRU;


/*****************************************************************************
 ????????  : TAF_PS_GET_DSFLOW_NV_WRITE_CFG_REQ_STRU
 ????????  : ID_MSG_TAF_PS_GET_DSFLOW_NV_WRITE_CFG_REQ??????????

  1.??    ??   : 2015??2??12??
    ??    ??   : A00165503
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
} TAF_PS_GET_DSFLOW_NV_WRITE_CFG_REQ_STRU;


/*****************************************************************************
 ????????  : TAF_PS_GET_DSFLOW_NV_WRITE_CFG_CNF_STRU
 ????????  : ID_EVT_TAF_PS_GET_DSFLOW_NV_WRITE_CFG_CNF??????????

  1.??    ??   : 2015??2??12??
    ??    ??   : A00165503
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    TAF_DSFLOW_NV_WRITE_CFG_STRU        stNvWriteCfg;
} TAF_PS_GET_DSFLOW_NV_WRITE_CFG_CNF_STRU;

/*****************************************************************************
 ????????  : TAF_PS_SET_CTA_INFO_REQ_STRU
 ????????  : ID_MSG_TAF_PS_SET_1X_MAX_NO_DATA_TIME_LEN_REQ??????????

  1.??    ??   : 2015??4??20??
    ??    ??   : c00299063
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    VOS_UINT8                           ucPktCdataInactivityTmrLen;
    VOS_UINT8                           aucReserved[3];
}TAF_PS_SET_CTA_INFO_REQ_STRU;

/*****************************************************************************
 ????????  : TAF_PS_GET_CTA_INFO_REQ_STRU
 ????????  : ID_MSG_TAF_PS_GET_1X_MAX_NO_DATA_TIME_LEN_REQ??????????

  1.??    ??   : 2015??4??20??
    ??    ??   : c00299063
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

}TAF_PS_GET_CTA_INFO_REQ_STRU;



/*****************************************************************************
 ????????  : TAF_PS_SET_CTA_INFO_CNF_STRU
 ????????  : ID_MSG_TAF_PS_SET_1X_MAX_NO_DATA_TIME_LEN_CNF??????????

  1.??    ??   : 2015??4??20??
    ??    ??   : c00299063
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
    VOS_UINT32                          ulRslt;

}TAF_PS_SET_CTA_INFO_CNF_STRU;

/*****************************************************************************
 ????????  : TAF_PS_GET_CTA_INFO_CNF_STRU
 ????????  : ID_MSG_TAF_PS_GET_1X_MAX_NO_DATA_TIME_LEN_CNF??????????

  1.??    ??   : 2015??4??20??
    ??    ??   : c00299063
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
    VOS_UINT32                          ulRslt;

    VOS_UINT8                           ucPktCdataInactivityTmrLen;
    VOS_UINT8                           aucReserved[3];

}TAF_PS_GET_CTA_INFO_CNF_STRU;


/*****************************************************************************
 ????????  : TAF_PS_GET_CGMTU_VALUE_REQ_STRU
 ????????  : ID_MSG_TAF_PS_GET_CGMTU_VALUE_REQ??????????

  1.??    ??   : 2015??5??24??
    ??    ??   : g00261581
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
}TAF_PS_GET_CGMTU_VALUE_REQ_STRU;

/*****************************************************************************
 ????????  : TAF_PS_GET_CGMTU_VALUE_CNF_STRU
 ????????  : ID_EVT_TAF_PS_GET_CGMTU_VALUE_CNF??????????

  1.??    ??   : 2015??5??24??
    ??    ??   : g00261581
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
    VOS_UINT32                          ulMtuValue;
}TAF_PS_GET_CGMTU_VALUE_CNF_STRU;

/*****************************************************************************
 ????????  : TAF_PS_CGMTU_VALUE_CHG_IND_STRU
 ????????  : ID_EVT_TAF_PS_CGMTU_VALUE_CHG_IND??????????

  1.??    ??   : 2015??5??24??
    ??    ??   : g00261581
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
    VOS_UINT32                          ulMtuValue;
}TAF_PS_CGMTU_VALUE_CHG_IND_STRU;


/*****************************************************************************
 ???? : ???????? ^CGAUTH
 ID   :

 REQ  :
 CNF  :
 IND  : -
 ???? : ...
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpAuth           : 1;
    VOS_UINT32                          bitOpUserName       : 1;
    VOS_UINT32                          bitOpPassword       : 1;
    VOS_UINT32                          bitOpSpare          : 29;

    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucDefined;          /* 0:undefined, 1:defined */
    VOS_UINT8                           ucAuth;             /* ??????????????????????????????????????????????*/
    VOS_UINT8                           aucReserved[1];
    VOS_UINT8                           aucUserName[TAF_MAX_PDP_AUTH_USERNAME_LEN + 1];
    VOS_UINT8                           aucPassWord[TAF_MAX_PDP_AUTH_PASSCODE_LEN + 1];
} TAF_PDP_AUTH_EXT_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PDP_AUTH_EXT_STRU               stPdpAuthInfo;
} TAF_PS_SET_PDP_AUTH_INFO_REQ_STRU;

typedef TAF_PS_COMMON_CNF_STRU TAF_PS_SET_PDP_AUTH_INFO_CNF_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
} TAF_PS_GET_PDP_AUTH_INFO_REQ_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    VOS_UINT32                          ulCidNum;
    TAF_AUTH_QUERY_INFO_STRU            astPdpAuthQueryInfo[0];
} TAF_PS_GET_PDP_AUTH_INFO_CNF_STRU;


/*****************************************************************************
 ???? : ???????? ^CGDNS
 ID   :

 REQ  :
 CNF  :
 IND  : -
 ???? : ...
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPrimDnsAddr    : 1;
    VOS_UINT32                          bitOpSecDnsAddr     : 1;
    VOS_UINT32                          bitOpSpare          : 30;

    VOS_UINT8                           ucCid;              /* [1??11] ????????????????????????????Cid??DNS */
    VOS_UINT8                           ucDefined;          /* 0:undefined, 1:defined */
    VOS_UINT8                           aucReserved[2];
    VOS_UINT8                           aucPrimDnsAddr[TAF_IPV4_ADDR_LEN];
    VOS_UINT8                           aucSecDnsAddr[TAF_IPV4_ADDR_LEN];
} TAF_PDP_DNS_EXT_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PDP_DNS_EXT_STRU                stPdpDnsInfo;
} TAF_PS_SET_PDP_DNS_INFO_REQ_STRU;

typedef TAF_PS_COMMON_CNF_STRU TAF_PS_SET_PDP_DNS_INFO_CNF_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
} TAF_PS_GET_PDP_DNS_INFO_REQ_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    VOS_UINT32                          ulCidNum;
    TAF_DNS_QUERY_INFO_STRU             astPdpDnsQueryInfo[0];
} TAF_PS_GET_PDP_DNS_INFO_CNF_STRU;


/*****************************************************************************
 ???? : ???????? ^TRIG
 ID   :

 REQ  :
 CNF  :
 IND  : -
 ???? : ...
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMode;
    VOS_UINT8                           ucNsapi;
    VOS_UINT8                           ucTimes;
    VOS_UINT8                           aucReserved[1];
    VOS_UINT32                          ulLength;
    VOS_UINT32                          ulMillisecond;
} TAF_GPRS_DATA_STRU;

typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_GPRS_DATA_STRU                  stGprsDataInfo;
} TAF_PS_TRIG_GPRS_DATA_REQ_STRU;

typedef TAF_PS_COMMON_CNF_STRU TAF_PS_TRIG_GPRS_DATA_CNF_STRU;


/*****************************************************************************
 ???? : ???????? ^DWINS
 ID   :

 REQ  :
 CNF  :
 IND  : -
 ???? : ...
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    /* 0:disabled, 1:enabled */
    VOS_UINT32                          ulEnabled;
} TAF_PS_CONFIG_NBNS_FUNCTION_REQ_STRU;

typedef TAF_PS_COMMON_CNF_STRU TAF_PS_CONFIG_NBNS_FUNCTION_CNF_STRU;


/*****************************************************************************
 ????????  : TAF_PS_DIAL_PARA_STRU
 ????????  : ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpAuthType       : 1;
    VOS_UINT32                          bitOpApn            : 1;
    VOS_UINT32                          bitOpIpAddr         : 1;
    VOS_UINT32                          bitOpUserName       : 1;
    VOS_UINT32                          bitOpPassWord       : 1;
    VOS_UINT32                          bitOpReqType        : 1;
    VOS_UINT32                          bitOpPdpDcomp       : 1;
    VOS_UINT32                          bitOpPdpHcomp       : 1;
    VOS_UINT32                          bitOpIpv4AddrAlloc  : 1;
    VOS_UINT32                          bitOpEmergencyInd   : 1;
    VOS_UINT32                          bitOpPcscfDiscovery : 1;
    VOS_UINT32                          bitOpImCnSignalFlg  : 1;
    VOS_UINT32                          bitOpDialRatType    : 1;
    VOS_UINT32                          bitOpSpare          : 19;

    /* connect id [1, 20] */
    VOS_UINT8                           ucCid;

    /* 0 - no auth */
    /* 1 - PAP */
    /* 2 - CHAP */
    /* 3 - MS_CHAP_V2 */
    TAF_PDP_AUTH_TYPE_ENUM_UINT8        enAuthType;

    /* 0 - IPv4 */
    /* 1 - IPv6 */
    /* 2 - IPv4v6 */
    /* 3 - PPP */
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;

    /* 1 - initial request */
    /* 2 - Handover */
    /* 3 - Unused. If received, the network shall interpret this as "initial request". */
    /* 4 - emergency */
    TAF_PDP_REQUEST_TYPE_ENUM_UINT8     enPdpRequestType;

    /* access point name string with '\0' end */
    VOS_UINT8                           aucApn[TAF_MAX_APN_LEN + 1];

    /* staitc address if needed */
    TAF_PDP_ADDR_STRU                   stPdpAddr;

    /* user name string with '\0' end */
    VOS_UINT8                           aucUserName[TAF_MAX_GW_AUTH_USERNAME_LEN + 1];

    /* user name string with '\0' end */
    VOS_UINT8                           aucPassWord[TAF_MAX_GW_AUTH_PASSWORD_LEN + 1];

    /* 0 - off (default if value is omitted) */
    /* 1 - on (manufacturer preferred compression) */
    /* 2 - V.42bis */
    /* 3 - V.44 */
    TAF_PDP_D_COMP_ENUM_UINT8           enPdpDcomp;

    /* 0 - off (default if value is omitted) */
    /* 1 - on (manufacturer preferred compression) */
    /* 2 - RFC1144 (applicable for SNDCP only) */
    /* 3 - RFC2507 */
    /* 4 - RFC3095 (applicable for PDCP only) */
    TAF_PDP_H_COMP_ENUM_UINT8           enPdpHcomp;

    /* 0 - IPv4 Address Allocation through NAS Signaling (default if omitted) */
    /* 1 - IPv4 Address Allocated through DHCP */
    TAF_PDP_IPV4_ADDR_ALLOC_TYPE_ENUM_UINT8 enIpv4AddrAlloc;

    /* 0 - PDP context is not for emergency bearer services */
    /* 1 - PDP context is for emergency bearer services */
    TAF_PDP_EMC_IND_ENUM_UINT8          enEmergencyInd;

    /* 0 - Preference of P-CSCF address discovery not influenced by +CGDCONT */
    /* 1 - Preference of P-CSCF address discovery through NAS Signalling */
    /* 2 - Preference of P-CSCF address discovery through DHCP */
    TAF_PDP_PCSCF_DISCOVERY_ENUM_UINT8  enPcscfDiscovery;

    /* 0 - UE indicates that the PDP context is not for IM CN subsystem-related signalling only */
    /* 1 - UE indicates that the PDP context is for IM CN subsystem-related signalling only */
    TAF_PDP_IM_CN_SIG_FLAG_ENUM_UINT8   enImCnSignalFlg;

    VOS_UINT8                           ucBitRatType;
    VOS_UINT8                           aucReserved[1];

} TAF_PS_DIAL_PARA_STRU;

/*****************************************************************************
 ??????    : TAF_PS_CALL_ORIG_REQ_STRU
 ????????  : ID_MSG_TAF_PS_CALL_ORIG_REQ????????
 1.??    ??   : 2011??10??19??
   ??    ??   : A00165503
   ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_DIAL_PARA_STRU               stDialParaInfo;
} TAF_PS_CALL_ORIG_REQ_STRU;

/*****************************************************************************
 ??????    : TAF_PS_CALL_END_REQ_STRU
 ????????  : ID_MSG_TAF_PS_GET_DIAL_PARA_INFO_CNF????????

 ????????      :
  1.??    ??   : 2011??08??22??
    ??    ??   : A00165503
    ????????   : ????????

  2.??    ??   : 2012??8??23??
    ??    ??   : A00165503
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    VOS_UINT8                           ucCid;
    VOS_UINT8                           aucReserved[3];
    TAF_PS_CAUSE_ENUM_UINT32            enCause;
} TAF_PS_CALL_ORIG_CNF_STRU;

/*****************************************************************************
 ??????    : TAF_PS_CALL_END_REQ_STRU
 ????????  : ID_MSG_TAF_PS_CALL_END_REQ????????, ????PS CALL
1.??    ??   : 2011??10??19??
   ??    ??   : A00165503
   ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    VOS_UINT8                           ucCid;
    VOS_UINT8                           aucReserved[3];
} TAF_PS_CALL_END_REQ_STRU;

/*****************************************************************************
 ????????: TAF_PS_CALL_END_CNF_STRU
 ????????: ID_MSG_TAF_PS_CALL_END_CNF????????
           ???????????? - enCause??TAF_PS_CAUSE_SUCCESS
           ???????????? - enCause??TAF_PS_CAUSE_CID_INVALID
                          ??????CID??????????????????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    VOS_UINT8                           ucCid;
    VOS_UINT8                           aucReserved[3];
    TAF_PS_CAUSE_ENUM_UINT32            enCause;

} TAF_PS_CALL_END_CNF_STRU;

/*****************************************************************************
 ???? : ???????? ^AUTHDATA
 ID   : ID_MSG_TAF_PS_SET_AUTHDATA_INFO_REQ
      : ID_MSG_TAF_PS_SET_AUTHDATA_INFO_CNF
      : ID_MSG_TAF_PS_GET_AUTHDATA_INFO_REQ
      : ID_MSG_TAF_PS_GET_AUTHDATA_INFO_CNF
 REQ  : TAF_PS_SET_AUTHDATA_INFO_REQ_STRU; TAF_PS_GET_AUTHDATA_INFO_REQ_STRU
 CNF  : TAF_PS_SET_AUTHDATA_INFO_CNF_STRU; TAF_PS_GET_AUTHDATA_INFO_CNF_STRU
 ???? : ...
*****************************************************************************/
/*****************************************************************************
 ??????    : TAF_PDP_AUTHDATA_EXT_STRU
 ????????  : ????????(NDIS)
 1.??    ??   : 2011??10??19??
   ??    ??   : A00165503
   ????????   : ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpAuthType       : 1;
    VOS_UINT32                          bitOpPlmn           : 1;
    VOS_UINT32                          bitOpPassWord       : 1;
    VOS_UINT32                          bitOpUserName       : 1;
    VOS_UINT32                          bitOpSpare          : 28;

    VOS_UINT8                           ucDefined;          /* 0:undefined, 1:defined */
    VOS_UINT8                           ucCid;
    TAF_PDP_AUTH_TYPE_ENUM_UINT8        enAuthType;
    VOS_UINT8                           aucReserved1[1];
    VOS_UINT8                           aucPlmn[TAF_MAX_AUTHDATA_PLMN_LEN + 1];
    VOS_UINT8                           aucReserved2[1];
    VOS_UINT8                           aucPassWord[TAF_MAX_AUTHDATA_USERNAME_LEN + 1];
    VOS_UINT8                           aucUserName[TAF_MAX_AUTHDATA_PASSWORD_LEN + 1];
} TAF_AUTHDATA_EXT_STRU;

/*****************************************************************************
 ??????    : TAF_PS_SET_AUTHDATA_INFO_REQ_STRU
 ????????  : ID_MSG_TAF_PS_SET_AUTHDATA_INFO_REQ??????????, ????????????(NDIS)
 1.??    ??   : 2011??10??19??
   ??    ??   : A00165503
   ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_AUTHDATA_EXT_STRU               stAuthDataInfo;
} TAF_PS_SET_AUTHDATA_INFO_REQ_STRU;

/*****************************************************************************
 ??????    : TAF_PS_SET_AUTHDATA_INFO_CNF_STRU
 ????????  : ID_MSG_TAF_PS_SET_AUTHDATA_INFO_CNF??????????, ????????????(NDIS)
 1.??    ??   : 2011??10??19??
   ??    ??   : A00165503
   ????????   : ????????
*****************************************************************************/
typedef TAF_PS_COMMON_CNF_STRU TAF_PS_SET_AUTHDATA_INFO_CNF_STRU;

/*****************************************************************************
 ??????    : TAF_PS_GET_AUTHDATA_INFO_REQ_STRU
 ????????  : ID_MSG_TAF_PS_GET_AUTHDATA_INFO_REQ??????????, ????????????(NDIS)
 1.??    ??   : 2011??10??19??
   ??    ??   : A00165503
   ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
} TAF_PS_GET_AUTHDATA_INFO_REQ_STRU;

/*****************************************************************************
 ??????    : TAF_PS_GET_AUTHDATA_INFO_CNF_STRU
 ????????  : ID_EVT_TAF_PS_GET_AUTHDATA_INFO_CNF??????????, ????????????(NDIS)
 1.??    ??   : 2011??10??19??
   ??    ??   : A00165503
   ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    VOS_UINT32                          ulCidNum;
    TAF_AUTHDATA_QUERY_INFO_STRU        astAuthDataQueryInfo[0];
} TAF_PS_GET_AUTHDATA_INFO_CNF_STRU;


/*****************************************************************************
 ???? : ???????? D
 ID   : ID_MSG_TAF_PS_GET_D_GPRS_ACTIVE_TYPE_REQ
      : ID_EVT_TAF_PS_GET_D_GPRS_ACTIVE_TYPE_CNF
      :
      :
 REQ  : TAF_PS_GET_D_GPRS_ACTIVE_TYPE_REQ_STRU
 CNF  : TAF_PS_GET_D_GPRS_ACTIVE_TYPE_CNF_STRU
 ???? : ...
*****************************************************************************/

/*****************************************************************************
 ??????    : TAF_ATD_PARA_STRU
 ????????  : D????????????
 1.??    ??   : 2011??10??19??
   ??    ??   : A00165503
   ????????   : ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpL2p            : 1;
    VOS_UINT32                          bitOpSpare          : 31;

    VOS_UINT8                           ucCid;
    TAF_L2P_TYPE_ENUM_UINT8             enL2p;
    VOS_UINT8                           aucReserved[2];
} TAF_ATD_PARA_STRU;

/*****************************************************************************
 ??????    : TAF_CID_GPRS_ACTIVE_TYPE_STRU
 ????????  : CID??????GPRS????????
 1.??    ??   : 2011??10??19??
   ??    ??   : A00165503
   ????????   : ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCid;
    TAF_GPRS_ACTIVE_TYPE_UINT8          enActiveType;
    VOS_UINT8                           aucReserved[2];
} TAF_CID_GPRS_ACTIVE_TYPE_STRU;

/*****************************************************************************
 ??????    : TAF_PS_GET_D_GPRS_ACTIVE_TYPE_REQ_STRU
 ????????  : ID_MSG_TAF_PS_GET_D_GPRS_ACTIVE_TYPE_REQ??????????, ????D????GPRS????
 1.??    ??   : 2011??10??19??
   ??    ??   : A00165503
   ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_ATD_PARA_STRU                   stAtdPara;
} TAF_PS_GET_D_GPRS_ACTIVE_TYPE_REQ_STRU;

/*****************************************************************************
 ??????    : TAF_PS_GET_D_GPRS_ACTIVE_TYPE_CNF_STRU
 ????????  : ID_EVT_TAF_PS_GET_D_GPRS_ACTIVE_TYPE_CNF??????????, ????D????GPRS????
 1.??    ??   : 2011??10??19??
   ??    ??   : A00165503
   ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    TAF_CID_GPRS_ACTIVE_TYPE_STRU       stCidGprsActiveType;
} TAF_PS_GET_D_GPRS_ACTIVE_TYPE_CNF_STRU;


/*****************************************************************************
 ????????: TAF_PPP_AUTH_PAP_CONTENT_STRU
 ????????:
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPapReqLen;                            /*request????: 24.008??????[3,253]????*/
    VOS_UINT8                           aucReserve[2];                          /* ???????? */
    VOS_UINT8                           aucPapReqBuf[TAF_PPP_PAP_REQ_MAX_LEN];  /*request*/
} TAF_PPP_AUTH_PAP_CONTENT_STRU;

/*****************************************************************************
 ????????: TAF_PPP_AUTH_CHAP_CONTENT_STRU
 ????????:
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usChapChallengeLen;                     /*challenge????: 24.008??????[3,253]????*/
    VOS_UINT16                          usChapResponseLen;                      /*response????: 24.008??????[3,253]????*/
    VOS_UINT8                           aucChapChallengeBuf[TAF_PPP_CHAP_CHALLENGE_MAX_LEN];    /*challenge,153B*/
    VOS_UINT8                           aucChapResponseBuf[TAF_PPP_CHAP_RESPONSE_MAX_LEN];      /*response,205B*/
    VOS_UINT8                           aucReserve[2];                          /* ???????? */
} TAF_PPP_AUTH_CHAP_CONTENT_STRU;

/*****************************************************************************
 ????????: TAF_PPP_REQ_AUTH_CONFIG_INFO_STRU
 ????????:
*****************************************************************************/
typedef struct
{
    TAF_PDP_AUTH_TYPE_ENUM_UINT8        enAuthType;
    VOS_UINT8                           aucReserve[3];

    union
    {
        TAF_PPP_AUTH_PAP_CONTENT_STRU   stPapContent;
        TAF_PPP_AUTH_CHAP_CONTENT_STRU  stChapContent;
    } enAuthContent;

} TAF_PPP_REQ_AUTH_CONFIG_INFO_STRU;

/*****************************************************************************
 ????????: TAF_PPP_REQ_CONFIG_INFO_STRU
 ????????:
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usIpcpLen;                              /*Ipcp??????*/
    VOS_UINT8                           aucReserve[2];                          /* ???????? */
    VOS_UINT8                           aucIpcp[TAF_PPP_IPCP_FRAME_BUF_MAX_LEN];/*Ipcp??*/
} TAF_PPP_REQ_IPCP_CONFIG_INFO_STRU;

/*****************************************************************************
 ????????: TAF_PPP_REQ_CONFIG_INFO_STRU
 ????????:
*****************************************************************************/
typedef struct
{
    TAF_PPP_REQ_AUTH_CONFIG_INFO_STRU   stAuth;
    TAF_PPP_REQ_IPCP_CONFIG_INFO_STRU   stIPCP;
} TAF_PPP_REQ_CONFIG_INFO_STRU;

/*****************************************************************************
 ???? : ????PPP????
 ID   : ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ
      : ID_EVT_TAF_PS_PPP_DIAL_ORIG_CNF
      :
      :
 REQ  : TAF_PS_PPP_DIAL_ORIG_REQ_STRU
 CNF  : TAF_PS_PPP_DIAL_ORIG_CNF_STRU
 ???? : ...
*****************************************************************************/
/*****************************************************************************
 ??????    : TAF_PS_PPP_DIAL_ORIG_REQ_STRU
 ????????  : ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ??????????, PPP????
 1.??    ??   : 2011??10??19??
   ??    ??   : A00165503
   ????????   : ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPppConfigInfo  : 1;
    VOS_UINT32                          bitOpSpare          : 31;

    VOS_UINT8                           ucCid;
    VOS_UINT8                           aucReserved[3];
    TAF_PPP_REQ_CONFIG_INFO_STRU        stPppReqConfigInfo;
} TAF_PPP_DIAL_PARA_STRU;

/*****************************************************************************
 ??????    : TAF_PS_PPP_DIAL_ORIG_REQ_STRU
 ????????  : ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ??????????, PPP????
 1.??    ??   : 2011??10??19??
   ??    ??   : A00165503
   ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PPP_DIAL_PARA_STRU              stPppDialParaInfo;
} TAF_PS_PPP_DIAL_ORIG_REQ_STRU;

/*****************************************************************************
 ??????    : TAF_PS_PPP_DIAL_ORIG_CNF_STRU
 ????????  : ID_EVT_TAF_PS_PPP_DIAL_ORIG_CNF????????

 ????????      :
  1.??    ??   : 2011??10??19??
    ??    ??   : A00165503
    ????????   : ????????

  2.??    ??   : 2012??8??23??
    ??    ??   : A00165503
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
} TAF_PS_PPP_DIAL_ORIG_CNF_STRU;

/*****************************************************************************
??????    : TAF_PDP_IPV6_PREFIX_STRU
????????  : IPV6 ????????????
  1.??    ??   : 2011??12??24??
    ??    ??   : ??????/c00173809
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulBitL          :1;                     /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          ulBitA          :1;
    VOS_UINT32                          ulBitPrefixLen  :8;
    VOS_UINT32                          ulBitRsv        :22;

    VOS_UINT32                          ulValidLifeTime;
    VOS_UINT32                          ulPreferredLifeTime;
    VOS_UINT8                           aucPrefix[TAF_IPV6_ADDR_LEN];
}TAF_PDP_IPV6_PREFIX_STRU;

/*****************************************************************************
??????    : TAF_PDP_IPV6_RA_INFO_STRU
????????  : IPV6 RA????????
  1.??    ??   : 2011??12??24??
    ??    ??   : ??????/c00173809
    ????????   : ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpMtu            :1;
    VOS_UINT32                          bitOpSpare          :31;

    VOS_UINT32                          ulBitCurHopLimit    :8;
    VOS_UINT32                          ulBitM              :1;
    VOS_UINT32                          ulBitO              :1;
    VOS_UINT32                          ulBitRsv            :22;

    VOS_UINT32                          ulMtu;                                  /* MTU???? */
    VOS_UINT32                          ulPrefixNum;                            /* IPV6???????????? */
    TAF_PDP_IPV6_PREFIX_STRU            astPrefixList[TAF_MAX_PREFIX_NUM_IN_RA];/* IPV6???????????? */

} TAF_PDP_IPV6_RA_INFO_STRU;


/*****************************************************************************
??????    : TAF_PS_IPV6_INFO_IND_STRU
????????  : ID_EVT_TAF_PS_IPV6_INFO_IND??????????
  1.??    ??   : 2011??12??24??
    ??    ??   : ??????/c00173809
    ????????   : ????????

  2.??    ??   : 2012??6??30??
    ??    ??   : A00165503
    ????????   : DTS2012062900707: IPv6????????, ????????IPv6????????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucRabId;
    VOS_UINT8                           aucReserved[2];
    TAF_PDP_IPV6_RA_INFO_STRU           stIpv6RaInfo;

} TAF_PS_IPV6_INFO_IND_STRU;

/*****************************************************************************
 ??????    : TAF_PS_GET_NEGOTIATION_DNS_REQ_STRU
 ????????  : ID_MSG_TAF_PS_GET_NEGOTIATION_DNS_REQ??????????
   1.??    ??   : 2012??02??17??
     ??    ??   : l00198894
     ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    VOS_UINT8                           ucCid;
    VOS_UINT8                           aucReserved[3];
} TAF_PS_GET_NEGOTIATION_DNS_REQ_STRU;

/*****************************************************************************
 ??????    : TAF_PS_GET_NEGOTIATION_DNS_CNF_STRU
 ????????  : ID_EVT_TAF_PS_GET_NEGOTIATION_DNS_CNF??????????
   1.??    ??   : 2012??02??17??
     ??    ??   : l00198894
     ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    TAF_DNS_QUERY_INFO_STRU             stNegotiationDns;
} TAF_PS_GET_NEGOTIATION_DNS_CNF_STRU;


#if (FEATURE_ON == FEATURE_LTE)

/*****************************************************************************
??????    : TAF_PH_LTECS_STRU
????????  : ^LTECS????LPS??????????
  1.??    ??   : 2012??04??22??
    ??    ??   : h00135900
    ????????   : AT ??????????????????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSG;
    VOS_UINT8                           ucIMS;
    VOS_UINT8                           ucCSFB;
    VOS_UINT8                           ucVCC;
    VOS_UINT8                           ucVoLGA;
    VOS_UINT8                           aucReserved[3];
}TAF_PH_LTECS_STRU;

/*****************************************************************************
??????    : TAF_PH_LTECS_STRU
????????  : ^LTECS????PS??????????
  1.??    ??   : 2012??04??22??
    ??    ??   : h00135900
    ????????   : AT ??????????????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
}TAF_PS_LTECS_REQ_STRU;

/*****************************************************************************
??????    : TAF_PS_LTECS_CNF_STRU
????????  : ^LTECS????TAF??????AT ??????????????
  1.??    ??   : 2012??04??22??
    ??    ??   : h00135900
    ????????   : AT ??????????????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    TAF_PH_LTECS_STRU                   stLteCs;
}TAF_PS_LTECS_CNF_STRU;


/*****************************************************************************
??????    : TAF_PH_CEMODE_STRU
????????  : ^CEMODE????PS??????????
  1.??    ??   : 2012??04??22??
    ??    ??   : h00135900
    ????????   : AT ??????????????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          enCurrentUeMode;                        /*????UE????*/
    VOS_UINT32                          ulSupportModeCnt;                       /*UE????????????????????*/
    VOS_UINT32                          aenSupportModeList[4];                  /*UE??????????????*/
}TAF_PH_CEMODE_STRU;

/*****************************************************************************
??????    : TAF_PS_CEMODE_REQ_STRU
????????  : ^CEMODE????????????????
  1.??    ??   : 2012??04??22??
    ??    ??   : h00135900
    ????????   : AT ??????????????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
}TAF_PS_CEMODE_REQ_STRU;

/*****************************************************************************
??????    : TAF_PS_CEMODE_CNF_STRU
????????  : ^CEMODE????????????????
  1.??    ??   : 2012??04??22??
    ??    ??   : h00135900
    ????????   : AT ??????????????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    TAF_PH_CEMODE_STRU                  stCemode;
}TAF_PS_CEMODE_CNF_STRU;



/* DTS2012031901936            : x00126983 2012-3-19 ???????? + */
/*****************************************************************************
 ??????    : TAF_PDP_PROFILE_EXT_STRU
 ????????  : ^PDPROFMOD????????
 ??    ?? : 2012??3??12??
 ??    ?? : x00126983
 ???????? : ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPdpType        : 1;                /* PdpType*/
    VOS_UINT32                          bitOpApn            : 1;                /* aucApn*/
    VOS_UINT32                          bitOpUsername       : 1;                /* AuthUsername*/
    VOS_UINT32                          bitOpPassword       : 1;                /* AuthPassword*/
    VOS_UINT32                          bitOpAuthType       : 1;                /* AuthType*/
    VOS_UINT32                          bitOpSpare          : 27;

    VOS_UINT8                           ucDefined;                              /* 0:undefined, 1:defined */

    VOS_UINT8                           ucCid;

    /* 1 IP Internet Protocol (IETF STD 5)*/
    /* 2 IPV6 Internet Protocol, version 6 (IETF RFC 2460)*/
    /* 3 IPV4V6 Virtual <PDP_type> introduced to handle dual IP stack UE capability. (See 3GPP TS 24.301 [83])*/
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;

    VOS_UINT8                           aucReserved1[1];

    /* Access Point Name*/
    VOS_UINT8                           aucApn[TAF_MAX_APN_LEN + 1];

    VOS_UINT8                           aucPassWord[TAF_MAX_AUTHDATA_PASSWORD_LEN + 1];
    VOS_UINT8                           aucUserName[TAF_MAX_AUTHDATA_USERNAME_LEN + 1];
    VOS_UINT8                           ucAuthType;
    VOS_UINT8                           aucReserved2[3];

}TAF_PDP_PROFILE_EXT_STRU;
/* DTS2012031901936            : x00126983 2012-3-19 ???????? - */

/*****************************************************************************
 ??????    : TAF_PS_SET_PROFILE_INFO_REQ_STRU
 ????????  : ID_MSG_TAF_PS_SET_AUTHDATA_INFO_REQ??????????, ????????????(NDIS)
 1.??    ??   : 2011??10??19??
   ??    ??   : A00165503
   ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_PDP_PROFILE_EXT_STRU            stPdpProfInfo;
} TAF_PS_SET_PROFILE_INFO_REQ_STRU;

typedef TAF_PS_COMMON_CNF_STRU TAF_PS_SET_PDP_PROF_INFO_CNF_STRU;

#endif

/*****************************************************************************
 ????????: TAF_GW_AUTH_STRU
 ????????: ??????????????????
*****************************************************************************/
typedef struct
{
    TAF_PDP_AUTH_TYPE_ENUM_UINT8        enAuthType;
    VOS_UINT8                           ucAccNumLen;
    VOS_UINT8                           aucReserved[2];
    VOS_UINT8                           auAccessNum[TAF_MAX_ACCESS_NUM_LEN];
    VOS_UINT8                           ucUserNameLen;
    VOS_UINT8                           aucUserName[TAF_MAX_GW_AUTH_USERNAME_LEN];
    VOS_UINT8                           ucPwdLen;
    VOS_UINT8                           aucPwd[TAF_MAX_GW_AUTH_PASSWORD_LEN];

} TAF_GW_AUTH_STRU;


/*****************************************************************************
 ????????: TAF_SDF_PARA_STRU
 ????????: SDF????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpLinkdCid       : 1;
    VOS_UINT32                          bitOpPdnType        : 1;
    VOS_UINT32                          bitOpApn            : 1;
    VOS_UINT32                          bitOpUmtsQos        : 1;
    VOS_UINT32                          bitOpEpsQos         : 1;
    VOS_UINT32                          bitOpGwAuthInfo     : 1;
    VOS_UINT32                          bitOpEmergencyInd   : 1;
    VOS_UINT32                          bitOpIpv4AddrAllocType: 1;
    VOS_UINT32                          bitOpPcscfDiscovery : 1;
    VOS_UINT32                          bitOpImCnSignalFlg  : 1;
    VOS_UINT32                          bitOpImsSuppFlg     : 1;
    VOS_UINT32                          bitOpSpare          : 21;

    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucLinkdCid;
    TAF_PDP_TYPE_ENUM_UINT8             enPdnType;
    TAF_PDP_IPV4_ADDR_ALLOC_TYPE_ENUM_UINT8 enIpv4AddrAllocType;

    TAF_PDP_EMC_IND_ENUM_UINT8          enEmergencyInd;
    TAF_PDP_PCSCF_DISCOVERY_ENUM_UINT8  enPcscfDiscovery;
    TAF_PDP_IM_CN_SIG_FLAG_ENUM_UINT8   enImCnSignalFlg;
    VOS_UINT8                           ucPfNum;
    VOS_UINT8                           ucImsSuppFlg;
    VOS_UINT8                           aucReserved[3];

    TAF_UMTS_QOS_STRU                   stUmtsQosInfo;
    TAF_EPS_QOS_STRU                    stEpsQosInfo;
    TAF_PDP_APN_STRU                    stApnInfo;
    TAF_GW_AUTH_STRU                    stGwAuthInfo;
    TAF_PDP_PF_STRU                     astCntxtTftInfo[TAF_MAX_SDF_PF_NUM];

}TAF_SDF_PARA_STRU;


/*****************************************************************************
 ????????: TAF_SDF_PARA_QUERY_INFO_STRU
 ????????: SDF??????????????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSdfNum;
    TAF_SDF_PARA_STRU                   astSdfPara[TAF_MAX_CID_NV];

} TAF_SDF_PARA_QUERY_INFO_STRU;

/*****************************************************************************
??????    : TAF_SDF_PARA_QUERY_INFO_STRU
????????  : SDF??????????????????????
  1.??    ??   : 2013??07??22??
    ??    ??   : Y00213812
    ????????   : VoLTE_PhaseI ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
}TAF_PS_SDF_INFO_REQ_STRU;


/*****************************************************************************
??????    : TAF_PS_SDF_INFO_CNF_STRU
????????  : SDF??????????????????????
  1.??    ??   : 2013??07??22??
    ??    ??   : Y00213812
    ????????   : VoLTE_PhaseI ????????
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    TAF_SDF_PARA_QUERY_INFO_STRU        stSdfInfo;
}TAF_PS_SDF_INFO_CNF_STRU;


/*****************************************************************************
 ??????    : TAF_PS_PDP_QOS_QUERY_PARA_STRU
 ????????  : QOS????????????????QOS??????MIN QOS????
 1.??    ??   : 2013??06??29??
   ??    ??   : l60609
   ????????   : ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucQosFlag;                              /* 0??Qos????????1??Qos?????? */
    VOS_UINT8                           ucMinQosFlag;                           /* 0:????????????????Qos,1:??????????????Qos */
    VOS_UINT8                           aucReserved[2];

    TAF_UMTS_QOS_STRU                   stQos;                                  /* Qos?? */
    TAF_UMTS_QOS_STRU                   stMinQos;                               /* MINQos?? */
}TAF_PS_PDP_QOS_QUERY_PARA_STRU;

/*****************************************************************************
 ??????    : TAF_PS_PDP_QOS_SET_PARA_STRU
 ????????  : QOS????????????????QOS??????MIN QOS????
 1.??    ??   : 2013??06??29??
   ??    ??   : l60609
   ????????   : ????????
*****************************************************************************/
typedef struct
{
    TAF_UMTS_QOS_EXT_STRU               stQos;                                  /* Qos?? */
    TAF_UMTS_QOS_EXT_STRU               stMinQos;                               /* MINQos?? */
}TAF_PS_PDP_QOS_SET_PARA_STRU;


#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 ????????: TAF_SRVCC_CANCEL_NOTIFY_IND_STRU
 ????????: APS->IMSA????SRVCC CANECL
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                           stCtrl;
    TAF_SRVCC_CANCEL_NOTIFY_ENUM_UINT32     enNotificationIndicator;
}TAF_SRVCC_CANCEL_NOTIFY_IND_STRU;
#endif

/******************************************************************************
 ??????    : TAF_PS_SET_1X_CQOS_PRI_REQ_STRU
 ????????  : ????CDMA QOS??????????
   1.??    ??   : 2013??10??15??
     ??    ??   : Y00213812
     ????????   : CDMA 1X ????????
 *******************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                                           stCtrl;
    TAF_PS_CDATA_1X_QOS_NON_ASSURED_PRI_ENUM_UINT8          enPri;
    VOS_UINT8                                               aucReserved[3];
}TAF_PS_SET_1X_CQOS_PRI_REQ_STRU;

/******************************************************************************
 ??????    : TAF_PS_SET_CQOS_PRI_CNF_STRU
 ????????  : ????CDMA QOS??????????
   1.??    ??   : 2013??10??15??
     ??    ??   : Y00213812
     ????????   : CDMA 1X ????????
 *******************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
    VOS_UINT32                          ulRslt;
}TAF_PS_SET_CQOS_PRI_CNF_STRU;

/** ****************************************************************************
 ??????    : TAF_PS_CALL_DORMANT_IND_STRU
 ????????  : CDMA??????????????????DORMANT??????????
   1.??    ??   : 2013??10??15??
     ??    ??   : Y00213812
     ????????   : CDMA 1X ????????
 *******************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucRabId;
    VOS_UINT8                           aucReserved[2];
}TAF_PS_CALL_DORMANT_IND_STRU;

/** ****************************************************************************
 * Name        : APS_APS_ENTER_DORMANT_IND_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* _H2ASN_Skip */
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           aucReserved[3];
}TAF_PS_CALL_ENTER_DORMANT_IND_STRU;


/** ****************************************************************************
 * Name        : TAF_PS_HAI_CHANGE_IND_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* _H2ASN_Skip */
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           aucReserved[3];
}TAF_PS_HAI_CHANGE_IND_STRU;


/** ****************************************************************************
 * Name        : TAF_PS_CDMA_DIAL_MODE_REQ_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                          stCtrl;


    TAF_PS_CDATA_DIAL_MODE_ENUM_UINT32    enDialMode;
}TAF_PS_CDATA_DIAL_MODE_REQ_STRU;

typedef TAF_PS_COMMON_CNF_STRU TAF_PS_CDATA_DIAL_MODE_CNF_STRU;

/*****************************************************************************
??????    : TAF_PS_CALL_PDP_RABID_CHANGE_IND_STRU
????????  : ID_EVT_TAF_PS_CALL_PDP_RABID_CHANGE_IND??????????

  1.??    ??   : 2016??6??01??
    ??    ??   : Y00213812
    ????????   : C2L????rabid??????????????AT
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;

    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucNewRabId;
    VOS_UINT8                           ucOldRabId;
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;

}TAF_PS_CALL_PDP_RABID_CHANGE_IND_STRU;

/*****************************************************************************
  H2ASN????????????????
*****************************************************************************/
typedef struct
{
    TAF_PS_MSG_ID_ENUM_UINT32           ulMsgId;                                /*_H2ASN_MsgChoice_Export TAF_PS_MSG_ID_ENUM_UINT32*/
    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          TAF_PS_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}TAF_PS_MSG_REQ;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    TAF_PS_MSG_REQ                      stMsgReq;
}TafApsApi_MSG;

typedef struct
{
    TAF_PS_EVT_ID_ENUM_UINT32           ulEvtId;                                /*_H2ASN_MsgChoice_Export TAF_PS_EVT_ID_ENUM_UINT32*/
    VOS_UINT8                           aucEvtBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          TAF_PS_EVT_ID_ENUM_UINT32
    ****************************************************************************/
}TAF_PS_EVT_CNF;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    TAF_PS_EVT_CNF                      stEvtCnf;
}TafApsApi_EVT;

/*****************************************************************************
  8 UNION????
*****************************************************************************/


/*****************************************************************************
  9 OTHERS????
*****************************************************************************/



/*****************************************************************************
  10 ????????
*****************************************************************************/

/*****************************************************************************
 ?? ?? ??  : TAF_PS_SetPrimPdpContextInfo
 ????????  : ????Primary PDP??????????
 ????????  : ulModuleId                 - ????PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
             pstPdpContextInfo          - Primary PDP??????????
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_SetPrimPdpContextInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId,
    TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pstPdpContextInfo
);

/*****************************************************************************
 ?? ?? ??  : TAF_PS_GetPrimPdpContextInfo
 ????????  : ????Primary PDP??????????
 ????????  : ulModuleId                 - ????PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_GetPrimPdpContextInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId
);

/*****************************************************************************
 ?? ?? ??  : TAF_PS_GetPdpContextInfo
 ????????  : ????PDP??????????
 ????????  : ulModuleId                 - ????PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_GetPdpContextInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId
);
/*****************************************************************************
 ?? ?? ??  : TAF_PS_SetSecPdpContextInfo
 ????????  : ????Secondary PDP??????????
 ????????  : ulModuleId                 - ????PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
             pstPdpContextInfo          - Secondary PDP??????????
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_SetSecPdpContextInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId,
    TAF_PDP_SEC_CONTEXT_EXT_STRU       *pstPdpContextInfo
);

/*****************************************************************************
 ?? ?? ??  : TAF_PS_GetSecPdpContextInfo
 ????????  : ????Secondary PDP??????????
 ????????  : ulModuleId                 - ????PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_GetSecPdpContextInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId
);

/*****************************************************************************
 ?? ?? ??  : TAF_PS_SetTftInfo
 ????????  : ????PDP TFT????
 ????????  : ulModuleId                 - ????PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
             pstTftInfo                 - TFT????
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_SetTftInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId,
    TAF_TFT_EXT_STRU                   *pstTftInfo
);

/*****************************************************************************
 ?? ?? ??  : TAF_PS_GetTftInfo
 ????????  : ????PDP TFT????
 ????????  : ulModuleId                 - ????PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_GetTftInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId
);

/*****************************************************************************
 ?? ?? ??  : TAF_PS_SetUmtsQosInfo
 ????????  : ????UMTS QOS????????
 ????????  : ulModuleId                 - ????PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
             pstUmtsQosInfo             - UMTS QOS????
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_SetUmtsQosInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId,
    TAF_UMTS_QOS_EXT_STRU              *pstUmtsQosInfo
);

/*****************************************************************************
 ?? ?? ??  : TAF_PS_GetUmtsQosInfo
 ????????  : ????UMTS QOS????????
 ????????  : ulModuleId                 - ????PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_GetUmtsQosInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId
);

/*****************************************************************************
 ?? ?? ??  : TAF_PS_SetUmtsQosMinInfo
 ????????  : ????UMTS MIN QOS????????
 ????????  : ulModuleId                 - ????PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
             pstUmtsQosMinInfo          - UMTS MIN QOS????
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_SetUmtsQosMinInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId,
    TAF_UMTS_QOS_EXT_STRU              *pstUmtsQosMinInfo
);

/*****************************************************************************
 ?? ?? ??  : TAF_PS_GetUmtsQosMinInfo
 ????????  : ????UMTS MIN QOS????????
 ????????  : ulModuleId                 - ????PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_GetUmtsQosMinInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId
);

/*****************************************************************************
 ?? ?? ??  : TAF_PS_GetDynamicUmtsQosInfo
 ????????  : ????????UMTS QOS????????
 ????????  : ulModuleId                 - ????PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
             pstCidListInfo             - CID????
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_GetDynamicUmtsQosInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId,
    TAF_CID_LIST_STRU                  *pstCidListInfo
);

/*****************************************************************************
 ?? ?? ??  : TAF_PS_SetPdpContextState
 ????????  : ????????CID(??)??????PDP??????
 ????????  : ulModuleId                 - ????PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
             pstCidListStateInfo        - CID????????
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_SetPdpContextState(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId,
    TAF_CID_LIST_STATE_STRU            *pstCidListStateInfo
);

/*****************************************************************************
 ?? ?? ??  : TAF_PS_GetPdpContextState
 ????????  : ??????????????CID??????PDP??????
 ????????  : ulModuleId                 - ????PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_GetPdpContextState(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId
);

/*****************************************************************************
 ?? ?? ??  : TAF_PS_CallModify
 ????????  : ????PS CALL????
 ????????  : ulModuleId                 - ????PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
             TAF_CID_LIST_STRU          - CID????
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_CallModify(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId,
    TAF_CID_LIST_STRU                  *pstCidListInfo
);

/*****************************************************************************
 ?? ?? ??  : TAF_PS_CallAnswer
 ????????  : ????PS CALL
 ????????  : ulModuleId                 - ????PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
             pstAnsInfo                 - PS CALL????????
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_CallAnswer(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId,
    TAF_PS_ANSWER_STRU                 *pstAnsInfo
);

/*****************************************************************************
 ?? ?? ??  : TAF_PS_CallHangup
 ????????  : ????PS CALL
 ????????  : ulModuleId                 - ????PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_CallHangup(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId
);

/*****************************************************************************
 ?? ?? ??  : TAF_PS_CallOrig
 ????????  : ????PS CALL
 ????????  : ulModuleId                 - ????PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
             pstDialParaInfo            - PS CALL????
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_CallOrig(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId,
    TAF_PS_DIAL_PARA_STRU              *pstDialParaInfo
);

/*****************************************************************************
 ?? ?? ??  : TAF_PS_CallEnd
 ????????  : ????PS CALL
 ????????  : ulModuleId                 - ????PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
             stCidListInfo              - CID????
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_CallEnd(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCid
);

/*****************************************************************************
 ?? ?? ??  : TAF_PS_GetPdpIpAddrInfo
 ????????  : ????????CID(??)??PDP IP????????
 ????????  : ulModuleId                 - ????PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
             pstCidListInfo             - CID????
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_GetPdpIpAddrInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId,
    TAF_CID_LIST_STRU                  *pstCidListInfo
);

/*****************************************************************************
 ?? ?? ??  : TAF_PS_SetAnsModeInfo
 ????????  : ????PS??????????????????
 ????????  : ulModuleId                 - ????PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
             ulAnsMode                  - ????????????
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_SetAnsModeInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT32                          ulAnsMode
);

/*****************************************************************************
 ?? ?? ??  : TAF_PS_GetAnsModeInfo
 ????????  : ????PS??????????????????
 ????????  : ulModuleId                 - ????PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_GetAnsModeInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId
);

/*****************************************************************************
 ?? ?? ??  : TAF_PS_GetDynamicPrimPdpContextInfo
 ????????  : ????????????????CID??????Primary PDP??????????
 ????????  : ulModuleId                 - ????PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
             ucCid                      - CID
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_GetDynamicPrimPdpContextInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCid
);

/*****************************************************************************
 ?? ?? ??  : TAF_PS_GetDynamicSecPdpContextInfo
 ????????  : ????????????????CID??????Secondary PDP??????????
 ????????  : ulModuleId                 - ????PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
             ucCid                      - CID
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_GetDynamicSecPdpContextInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCid
);

/*****************************************************************************
 ?? ?? ??  : TAF_PS_GetDynamicTftInfo
 ????????  : ????????????????CID??????TFT????
 ????????  : ulModuleId                 - ????PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
             ucCid                      - CID
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_GetDynamicTftInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCid
);

/*****************************************************************************
 ?? ?? ??  : TAF_PS_SetEpsQosInfo
 ????????  : ????????CID??EPS QOS????????
 ????????  : ulModuleId                 - ????PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
             pstEpsQosInfo              - EPS QOS????????
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_SetEpsQosInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId,
    TAF_EPS_QOS_EXT_STRU               *pstEpsQosInfo
);

/*****************************************************************************
 ?? ?? ??  : TAF_PS_GetEpsQosInfo
 ????????  : ????EPS QOS????????
 ????????  : ulModuleId                 - ????PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_GetEpsQosInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId
);

/*****************************************************************************
 ?? ?? ??  : TAF_PS_GetDynamicEpsQosInfo
 ????????  : ????????????????CID??????EPS QOS????
 ????????  : ulModuleId                 - ????PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
             ucCid                      - CID
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_GetDynamicEpsQosInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCid
);

/*****************************************************************************
 ?? ?? ??  : TAF_PS_GetDsFlowInfo
 ????????  : ????????????????
 ????????  : ulModuleId                 - ????PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
             pstQueryConfigInfo         - DSFLOW????????????
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_GetDsFlowInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId
);

/*****************************************************************************
 ?? ?? ??  : TAF_PS_ClearDsFlowInfo
 ????????  : ????????????????
 ????????  : ulModuleId                 - ????PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
             pstClearConfigInfo         - ????????????????????
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_ClearDsFlowInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId,
    TAF_DSFLOW_CLEAR_CONFIG_STRU       *pstClearConfigInfo
);

/*****************************************************************************
 ?? ?? ??  : TAF_PS_ConfigDsFlowRpt
 ????????  : ????????????????
 ????????  : ulModuleId                 - ????PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
             pstReportConfigInfo        - ????????????????????
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_ConfigDsFlowRpt(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId,
    TAF_DSFLOW_REPORT_CONFIG_STRU      *pstReportConfigInfo
);

/*****************************************************************************
 ?? ?? ??  : TAF_PS_SetPdpDnsInfo
 ????????  : ????PDP DNS????
 ????????  : ulModuleId                 - ????PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
             pstPdpDnsInfo              - PDP DNS????
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_SetPdpDnsInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId,
    TAF_PDP_DNS_EXT_STRU               *pstPdpDnsInfo
);

/*****************************************************************************
 ?? ?? ??  : TAF_PS_GetPdpDnsInfo
 ????????  : ????PDP DNS????
 ????????  : ulModuleId                 - ????PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_GetPdpDnsInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId
);

/*****************************************************************************
 ?? ?? ??  : TAF_PS_TrigGprsData
 ????????  : ????????GPRS????
 ????????  : ulModuleId                 - ????PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
             pstGprsDataInfo            - GPRS????????
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_TrigGprsData(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId,
    TAF_GPRS_DATA_STRU                 *pstGprsDataInfo
);

/*****************************************************************************
 ?? ?? ??  : TAF_PS_ConfigNbnsFunction
 ????????  : ????NBNS????
 ????????  : ulModuleId                 - ????PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
             ulEnabled                  - NBNS????????????
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_ConfigNbnsFunction(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT32                          ulEnabled
);

/*****************************************************************************
 ?? ?? ??  : TAF_PS_GetNdisStateInfo
 ????????  : ????NDIS????????
 ????????  : ulModuleId                 - ????PID
             usClientId                 - ??????ID
             ucOpId                     - ??????ID
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_GetNdisStateInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

/*****************************************************************************
 ?? ?? ??  : TAF_PS_SetAuthDataInfo
 ????????  : ????????????????(NDIS)
 ????????  : ulModuleId                 - ????PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
             pstAuthDataInfo            - ????????
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_SetAuthDataInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId,
    TAF_AUTHDATA_EXT_STRU              *pstAuthDataInfo
);

/*****************************************************************************
 ?? ?? ??  : TAF_PS_GetAuthDataInfo
 ????????  : ????????????????(NDIS)
 ????????  : ulModuleId                 - ????PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_GetAuthDataInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId
);

/*****************************************************************************
 ?? ?? ??  : TAF_PS_GetGprsActiveType
 ????????  : ????D????GPRS????(PPP????)
 ????????  : ulModuleId                 - ????PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
             pstAtdPara                 - D????????????
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_GetGprsActiveType(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId,
    TAF_ATD_PARA_STRU                  *pstAtdPara
);

/*****************************************************************************
 ?? ?? ??  : TAF_PS_PppDialOrig
 ????????  : ????PPP????
 ????????  : ulModuleId                 - ????PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
             ucCid                      - CID
             pstPppReqConfigInfo        - PPP????????
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_PppDialOrig(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCid,
    TAF_PPP_REQ_CONFIG_INFO_STRU       *pstPppReqConfigInfo
);

#if(FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 ?? ?? ??  : TAF_PS_GetLteCsInfo
 ????????  :
 ????????  : ulModuleId                 - ????PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_GetLteCsInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId
);

/*****************************************************************************
 ?? ?? ??  : TAF_PS_GetCemodeInfo
 ????????  :
 ????????  : ulModuleId                 - ????PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_GetCemodeInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId
);

/*****************************************************************************
 ?? ?? ??  : TAF_PS_SetPdpProfInfo
 ????????  :
 ????????  : ulModuleId                 - ????PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
             pstPdpProfInfo             - PdpProfile ????????
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_SetPdpProfInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId,
    TAF_PDP_PROFILE_EXT_STRU           *pstPdpProfInfo
);
#endif

/*****************************************************************************
 ?? ?? ??  : TAF_PS_GetCidSdfParaInfo
 ????????  : ????????NV??????SDF????????, ??????????????????????
             ???????????? --- ????????(??????????C??)
             ???????????? --- ????????
 ????????  : ulModuleId                 - ????PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
 ????????  : pstSdfQueryInfo            - SDF????????
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_GetCidSdfParaInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId,
    TAF_SDF_PARA_QUERY_INFO_STRU       *pstSdfQueryInfo
);


/*****************************************************************************
 ?? ?? ??  : TAF_PS_GetUnusedCid
 ????????  : ????????????????CID
             ???????????? --- ????????(??????????C??)
             ???????????? --- ????????
 ????????  : ulModuleId                 - ????PID
             usClientId                 - ??????ID
             ucOpId                     - ??????ID
 ????????  : puCid                      - ??????????CID
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_GetUnusedCid(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                          *puCid
);

/*****************************************************************************
 ?? ?? ??  : TAF_PS_GetDynamicDnsInfo
 ????????  : ????????CID??DNS????
 ????????  : ulModuleId                 - ????PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
             ucCid                      - CID
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_GetDynamicDnsInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCid
);

VOS_UINT32 TAF_PS_SetCqosPriInfo(
    VOS_UINT32                                      ulModuleId,
    VOS_UINT16                                      usExClientId,
    TAF_PS_CDATA_1X_QOS_NON_ASSURED_PRI_ENUM_UINT8  enPri
);

/*****************************************************************************
 ?? ?? ??  : TAF_PS_SetApDsFlowRptCfg
 ????????  : ????AP????????????
 ????????  : ulModuleId                 - PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
             pstRptCfg                  - ????????
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_SetApDsFlowRptCfg(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId,
    TAF_APDSFLOW_RPT_CFG_STRU          *pstRptCfg
);

/*****************************************************************************
 ?? ?? ??  : TAF_PS_GetApDsFlowRptCfg
 ????????  : ????AP????????????
 ????????  : ulModuleId                 - PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_GetApDsFlowRptCfg(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId
);

/*****************************************************************************
 ?? ?? ??  : TAF_PS_SetDsFlowNvWriteCfg
 ????????  : ??????????NV????
 ????????  : ulModuleId                 - PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
             pstNvWriteCfg              - ??????NV????
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_SetDsFlowNvWriteCfg(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId,
    TAF_DSFLOW_NV_WRITE_CFG_STRU       *pstNvWriteCfg
);

/*****************************************************************************
 ?? ?? ??  : TAF_PS_GetDsFlowNvWriteCfg
 ????????  : ??????????NV????
 ????????  : ulModuleId                 - PID
             usExClientId               - ??????????ID
                                          A?? : ModemID(????bit) + ??????ID
                                          C?? : ??????ID
             ucOpId                     - ??????ID
 ????????  : ??
 ?? ?? ??  : VOS_OK                     - ????
             VOS_ERR                    - ????
*****************************************************************************/
VOS_UINT32 TAF_PS_GetDsFlowNvWriteCfg(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId
);

VOS_UINT32 TAF_PS_SetCdataDialModeInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    TAF_PS_CDATA_DIAL_MODE_ENUM_UINT32  enDialMode
);

VOS_UINT32 TAF_PS_SetImsPdpCfg(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId,
    TAF_IMS_PDP_CFG_STRU               *pstImsPdpCfg
);

VOS_UINT32 TAF_PS_GetCtaInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId
);

VOS_UINT32 TAF_PS_SetCtaInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucTimeLen
);

VOS_UINT32 TAF_PS_GetCgmtuInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId
);

VOS_UINT32 TAF_PS_SetCdmaDormantTimer(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucDormantTimer
);

VOS_UINT32 TAF_PS_ProcCdmaDormTimerQryReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usExClientId,
    VOS_UINT8                           ucOpId
);


TAF_PS_CDATA_BEAR_STATUS_ENUM_UINT8 TAF_PS_GetCdataBearStatus(
    VOS_UINT8                                               ucPdpId
);

TAF_PS_CDATA_BEAR_STATUS_ENUM_UINT8  TAF_PS_GetPppStatus( VOS_VOID );



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

#endif

