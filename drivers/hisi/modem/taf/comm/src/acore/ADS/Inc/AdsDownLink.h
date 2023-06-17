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

#ifndef __ADSDOWNLINK_H__
#define __ADSDOWNLINK_H__

/*****************************************************************************
  1 ??????????????
*****************************************************************************/
#include "vos.h"
#include "AdsIntraMsg.h"
#include "AdsCtx.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 ??????
*****************************************************************************/

/* ????ADS????IP TYPE */
#define ADS_DL_IP_TYPE_FLAG                         (0x0200)

/* bd_cd_noeqBD??len??CD?????????????????? */
#define ADS_DL_IPF_RD_RSLT_BDCD_LEN_ERR_FLG         (0x4000)    /* 0100 0000 0000 0000 B */

/* pkt_parse_err???????????????? */
#define ADS_DL_IPF_RD_RSLT_PKT_PARSE_ERR_FLG        (0x2000)    /* 0010 0000 0000 0000 B */

/* bd_pkt_noeqBD??len??IP??????????len???????????? */
#define ADS_DL_IPF_RD_RSLT_BD_PKT_LEN_ERR_FLG       (0x1000)    /* 0001 0000 0000 0000 B */

/* head_len_err IPV4???????????????? */
#define ADS_DL_IPF_RD_RSLT_HDR_LEN_ERR_FLG          (0x0800)    /* 0000 1000 0000 0000 B */

/* version_err?????????????? */
#define ADS_DL_IPF_RD_RSLT_VER_ERR_FLG              (0x0400)    /* 0000 0100 0000 0000 B */

/* ????IPF BEARID ?????????? */
#define ADS_DL_IPF_BEARID_ERR_PKT_FLAG              (ADS_DL_IPF_RD_RSLT_BDCD_LEN_ERR_FLG \
                                                   | ADS_DL_IPF_RD_RSLT_PKT_PARSE_ERR_FLG \
                                                   | ADS_DL_IPF_RD_RSLT_BD_PKT_LEN_ERR_FLG \
                                                   | ADS_DL_IPF_RD_RSLT_HDR_LEN_ERR_FLG \
                                                   | ADS_DL_IPF_RD_RSLT_VER_ERR_FLG)

/* ??????RD Result, ??????????Packet */
#define ADS_DL_IPF_RD_RSLT_IS_ERR_PKT(usRslt)       ((usRslt) & ADS_DL_IPF_BEARID_ERR_PKT_FLAG)

/* ??????RD Result, ??????Version???? */
#define ADS_DL_IPF_RD_RSLT_IS_VER_ERR_PKT(usRslt)   ((usRslt) & ADS_DL_IPF_RD_RSLT_VER_ERR_FLG)

/*lint -emacro({717}, ADS_DL_SAVE_RD_DESC_TO_IMM)*/
#define ADS_DL_SAVE_RD_DESC_TO_IMM(pstImmZc, pstRdDesc)\
            do\
            {\
                ADS_IMM_MEM_CB(pstImmZc)->aulPriv[0] = (pstRdDesc)->u16Result;\
                ADS_IMM_MEM_CB(pstImmZc)->aulPriv[0] = ((ADS_IMM_MEM_CB(pstImmZc)->aulPriv[0]) << 16) | ((pstRdDesc)->u16UsrField1);\
            } while(0)

/* ??IPF Result????IP?????? */
#define ADS_DL_GET_IPTYPE_FROM_IPF_RESULT(usRslt)   ((ADS_PKT_TYPE_ENUM_UINT8)(((ADS_DL_IPF_RESULT_STRU *)&(usRslt))->usIpType))

/* RD??user field 1????1byte??Modem id????1byte??Rab Id */
#define ADS_DL_GET_IPF_RESULT_FORM_IMM(pstImmZc)    ((VOS_UINT16)(((ADS_IMM_MEM_CB(pstImmZc)->aulPriv[0]) & 0xFFFF0000) >> 16))
#define ADS_DL_GET_MODEMID_FROM_IMM(pstImmZc)       ((VOS_UINT16)(((ADS_IMM_MEM_CB(pstImmZc)->aulPriv[0]) & 0x0000FF00) >> 8))
#define ADS_DL_GET_RABID_FROM_IMM(pstImmZc)         ((VOS_UINT8)((ADS_IMM_MEM_CB(pstImmZc)->aulPriv[0]) & 0x000000FF))

/* ????????cache invalidate (map) */
/*lint -emacro({717}, ADS_IPF_DL_MEM_MAP)*/
#define ADS_IPF_DL_MEM_MAP(pstImmZc, ulLen)\
            do\
            {\
                if (VOS_FALSE == ADS_IPF_IsSpeMem(pstImmZc))\
                {\
                    ADS_IPF_MemMapRequset(pstImmZc, ulLen, 0);\
                }\
            } while(0)

/* ????????cache invalidate (unmap) */
/*lint -emacro({717}, ADS_IPF_DL_MEM_UNMAP)*/
#define ADS_IPF_DL_MEM_UNMAP(pstImmZc, ulLen)\
            do\
            {\
                if (VOS_FALSE == ADS_IPF_IsSpeMem(pstImmZc))\
                {\
                    ADS_IPF_MemUnmapRequset(pstImmZc, ulLen, 0);\
                }\
            } while(0)


/*****************************************************************************
  3 ????????
*****************************************************************************/


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
 ??????    : IPF_RESULT
 ????????  : ????Ip??????????????

  1.??    ??   : 2012??4??12??
    ??    ??   : A00165503
    ??    ??   : ????Ip??????????????
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usBearedId:6;
    VOS_UINT16                          usIpSegInfo:2;
    VOS_UINT16                          usUpperLayer:1;
    VOS_UINT16                          usIpType:1;
    VOS_UINT16                          usVerErr:1;
    VOS_UINT16                          usHdrLenErr:1;
    VOS_UINT16                          usPktLenNotEq:1;
    VOS_UINT16                          usPktLenErr:1;
    VOS_UINT16                          usBdCdNotEq:1;
    VOS_UINT16                          usResv:1;
} ADS_DL_IPF_RESULT_STRU;

/*****************************************************************************
??????    : ADS_DL_RD_STRU
????????  : ADS????????RD????

  1.??    ??   : 2011??12??6??
    ??    ??   : ????/l60609
    ????????   : ????ADS????????RD????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                            ucRabId;                               /* Rab Id*/
    ADS_PKT_TYPE_ENUM_UINT8              enPktType;                             /* Pkt Type*/
    VOS_UINT8                            aucRsv[6];                             /* ???? */
    CDS_ADS_DL_IPF_BEARER_ID_ENUM_UINT32 enBearId;                              /* Bear Id*/
    VOS_UINT32                           ulLen;                                 /* ?????????????????? */
    VOS_UINT8                           *pucData;                               /* ?????????????????? */
    VOS_VOID                            *pTtfMem;                               /* ????TTF????*/
} ADS_DL_RD_STRU;



/*****************************************************************************
  8 UNION????
*****************************************************************************/


/*****************************************************************************
  9 OTHERS????
*****************************************************************************/


/*****************************************************************************
  10 ????????
*****************************************************************************/

VOS_VOID ADS_DL_ProcMsg(MsgBlock* pMsg);
VOS_VOID ADS_DL_ProcTxData(IMM_ZC_STRU *pstImmZc);
VOS_UINT32 ADS_DL_RcvAtMsg(MsgBlock* pMsg);
VOS_UINT32 ADS_DL_RcvTafPdpStatusInd(MsgBlock *pMsg);
VOS_UINT32 ADS_DL_RcvCdsMsg(MsgBlock *pMsg);
VOS_INT32 ADS_DL_IpfIntCB(VOS_VOID);
VOS_VOID ADS_DL_ProcIpfResult(VOS_VOID);
VOS_UINT32 ADS_DL_IsFcAssemTuneNeeded(VOS_UINT32 ulRdNum);
VOS_INT32 ADS_DL_IpfAdqEmptyCB(IPF_ADQ_EMPTY_E eAdqEmpty);
VOS_VOID ADS_DL_RcvTiAdqEmptyExpired(VOS_UINT32 ulParam, VOS_UINT32 ulTimerName);
VOS_UINT32 ADS_DL_ConfigAdq(IPF_AD_TYPE_E enAdType, VOS_UINT ulIpfAdNum);
VOS_VOID ADS_DL_AllocMemForAdq(VOS_VOID);
VOS_INT ADS_DL_CCpuResetCallback(DRV_RESET_CB_MOMENT_E enParam, VOS_INT lUserData);
VOS_UINT32 ADS_DL_RcvCcpuResetStartInd(MsgBlock *pMsg);
VOS_UINT32 ADS_DL_RcvCcpuResetEndInd(MsgBlock *pMsg);
VOS_VOID ADS_DL_FreeIpfUsedAd0(VOS_VOID);
VOS_VOID ADS_DL_FreeIpfUsedAd1(VOS_VOID);
VOS_VOID ADS_DL_SendNdClientDataInd(IMM_ZC_STRU *pstImmZc);


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

#endif /* end of AdsDlProcData.h */
