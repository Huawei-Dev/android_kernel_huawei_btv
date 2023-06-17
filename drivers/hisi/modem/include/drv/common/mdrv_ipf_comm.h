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

#ifndef __MDRV_IPF_COMMON_H__
#define __MDRV_IPF_COMMON_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* error code definition */
#define IPF_SUCCESS             0
#define IPF_ERROR               -1
#define BSP_ERR_IPF_INVALID_PARA            BSP_DEF_ERR(BSP_MODU_IPF, 0)
#define BSP_ERR_IPF_BDQ_NOT_ENOUGH          BSP_DEF_ERR(BSP_MODU_IPF, 1)
#define BSP_ERR_IPF_CDQ_NOT_ENOUGH          BSP_DEF_ERR(BSP_MODU_IPF, 2)
#define BSP_ERR_IPF_RDQ_EMPTY               BSP_DEF_ERR(BSP_MODU_IPF, 3)
#define BSP_ERR_IPF_FILTER_NOT_ENOUGH       BSP_DEF_ERR(BSP_MODU_IPF, 4)
#define BSP_ERR_IPF_NOT_INIT                BSP_DEF_ERR(BSP_MODU_IPF, 5)
#define BSP_ERR_IPF_RESUME_TIMEOUT          BSP_DEF_ERR(BSP_MODU_IPF, 6)
#define BSP_ERR_IPF_SEMTAKE_TIMEOUT         BSP_DEF_ERR(BSP_MODU_IPF, 7)
#define BSP_ERR_IPF_ADQ0_NOT_ENOUGH         BSP_DEF_ERR(BSP_MODU_IPF, 8)
#define BSP_ERR_IPF_ADQ1_NOT_ENOUGH         BSP_DEF_ERR(BSP_MODU_IPF, 9)
#define BSP_ERR_IPF_ALLOC_MEM_FAIL          BSP_DEF_ERR(BSP_MODU_IPF, 10)
#define BSP_ERR_IPF_CCORE_RESETTING         BSP_DEF_ERR(BSP_MODU_IPF, 11)
#define BSP_ERR_IPF_INVALID_DLRD            BSP_DEF_ERR(BSP_MODU_IPF, 12)
#define BSP_ERR_IPF_INVALID_ULRD            BSP_DEF_ERR(BSP_MODU_IPF, 13)

#define IPF_ULBD_DESC_SIZE         64   /* ????BD???? */
#define IPF_ULRD_DESC_SIZE         64   /* ????BD???? */

#define IPF_DLBD_DESC_SIZE         16*(1 << CONFIG_IPF_ADQ_LEN)   /* ????BD???? */
#define IPF_DLRD_DESC_SIZE         16*(1 << CONFIG_IPF_ADQ_LEN)   /* ????BD???? */
#define IPF_ULAD0_DESC_SIZE        32*(1 << CONFIG_IPF_ADQ_LEN)   /* ????ADQ0??AD???? */
#define IPF_ULAD1_DESC_SIZE        32*(1 << CONFIG_IPF_ADQ_LEN)   /* ????ADQ1??AD???? */
#define IPF_DLAD0_DESC_SIZE        32*(1 << CONFIG_IPF_ADQ_LEN)   /* ????ADQ0??AD???? */
#define IPF_DLAD1_DESC_SIZE        32*(1 << CONFIG_IPF_ADQ_LEN)   /* ????ADQ1??AD???? */

#define IPF_DLCD_DESC_SIZE         1024 /* ???????? */
#define IPF_FILTER_CHAIN_MAX_NUM   8    /* IPF???????????????? */

/*ADQ??????????*/
typedef enum tagIPF_ADQEN_E
{
    IPF_NONE_ADQ_EN = 0,    /*??????ADQ*/
    IPF_ONLY_ADQ0_EN = 1,   /*??????ADQ0*/
    IPF_ONLY_ADQ1_EN = 2,   /*??????ADQ1*/
    IPF_BOTH_ADQ_EN = 3,    /*????ADQ0??ADQ1*/

    IPF_ADQEN_BUTT          /*??????*/
}IPF_ADQEN_E;

/*ADSize*/
typedef enum tagIPF_ADSIZE_E
{
    IPF_ADSIZE_32 = 0,  /* AD??????????32 */
    IPF_ADSIZE_64,      /* AD??????????64 */
    IPF_ADSIZE_128,     /* AD??????????128 */
    IPF_ADSIZE_256,     /* AD??????????256*/

    IPF_ADSIZE_MAX
}IPF_ADSIZE_E;

/* ???????? */
typedef enum tagIPF_MODE_E
{
	IPF_MODE_FILTERANDTRANS,
	IPF_MODE_FILTERONLY,
    IPF_MODE_TRANSONLY,
    IPF_MODE_TRANSONLY2,
    IPF_MODE_MAX
}IPF_MODE_E;

/*ADQ????????????*/
typedef enum tagIPF_ADQ_EMPTY_E
{
    IPF_EMPTY_ADQ0 = 0,
    IPF_EMPTY_ADQ1 = 1,
    IPF_EMPTY_ADQ = 2,
    IPF_EMPTY_MAX
}IPF_ADQ_EMPTY_E;

/* IPF???????? */
typedef enum tagIPF_RESTORE_STATE_E
{
    IPF_STATE_UNRESTORE = 0,   /* ?????? */
    IPF_STATE_RESTORING,       /* ?????? */
    IPF_STATE_RESTORED,        /* ?????? */

    IPF_STATE_MAX
}IPF_RESTORE_STATE_E;

/* IP???? */
typedef enum tagIPF_IP_TYPE_E
{
    IPF_IPTYPE_V4 = 0,  /* IPV4 */
    IPF_IPTYPE_V6,      /* IPV6 */

    IPF_IPTYPE_MAX      /* ?????? */
}IPF_IP_TYPE_E;

typedef enum tagIPF_AD_TYPE_E
{
    IPF_AD_0 = 0,        /* AD0 ????????AD??????????????????????????AD????????????????*/
    IPF_AD_1,            /* AD1 ????????*/
    IPF_AD_MAX           /* ?????? */
}IPF_AD_TYPE_E;

typedef enum tagIPF_CHANNEL_TYPE_E
{
    IPF_CHANNEL_UP	= 0,
    IPF_CHANNEL_DOWN,
    IPF_CHANNEL_MAX
}IPF_CHANNEL_TYPE_E;

typedef enum tagIPF_FILTER_CHAIN_TYPE_E
{
	IPF_MODEM0_ULFC = 0,
	IPF_MODEM1_ULFC,
    IPF_MODEM2_ULFC,
	IPF_MODEM0_DLFC,
	IPF_MODEM1_DLFC,
    IPF_MODEM2_DLFC,
    IPF_1XHRPD_ULFC,
	IPF_MODEM_MAX,
}IPF_FILTER_CHAIN_TYPE_E;

/*??????????V8 C??????????????IPF????*/


typedef struct
{
    unsigned short u16Len;         /* ?????????????? */
    unsigned short u16Attribute;   /* ????IP?????? */
    unsigned int   u32Data;        /* ?????????????? */
    unsigned short u16UsrField1;   /* Usr field ??1 ,???? */
    unsigned short u16Reserved;    /* ???? */
    unsigned int   u32UsrField2;   /* Usr field ??2 ,???? */
    unsigned int   u32UsrField3;   /* Usr field ??3 ,????*/
}IPF_CONFIG_PARAM_S;

struct mdrv_ipf_ops {
    int (*adq_empty_cb)(IPF_ADQ_EMPTY_E eAdqEmpty);
    int (*rx_complete_cb)(void);
};

/* RD?????? */
typedef struct
{
    unsigned short u16Attribute;
    unsigned short u16PktLen;
    unsigned int u32InPtr;
    unsigned int u32OutPtr;
    unsigned short u16Result;
    unsigned short u16UsrField1;
    unsigned int u32UsrField2;
    unsigned int u32UsrField3;
}IPF_RD_DESC_S;

/* BD?????? */
typedef struct tagIPF_BD_DESC_S
{
    unsigned short u16Attribute;
    unsigned short u16PktLen;
    unsigned int u32InPtr;
    unsigned int u32OutPtr;
    unsigned short u16Result;
    unsigned short u16UsrField1;
    unsigned int u32UsrField2;
    unsigned int u32UsrField3;
} IPF_BD_DESC_S;

/* AD?????? */
typedef struct tagIPF_AD_DESC_S
{
    unsigned int u32OutPtr0;
    unsigned int u32OutPtr1;
} IPF_AD_DESC_S;

/* CD?????? */
typedef struct tagIPF_CD_DESC_S
{
    unsigned short u16Attribute;
    unsigned short u16PktLen;
    unsigned int u32Ptr;
}IPF_CD_DESC_S;

/* ?????????????????? */
typedef struct tagIPF_FILTER_STAT_S
{
    unsigned int u32UlCnt0;
    unsigned int u32UlCnt1;
    unsigned int u32UlCnt2;
    unsigned int u32DlCnt0;
    unsigned int u32DlCnt1;
    unsigned int u32DlCnt2;
}IPF_FILTER_STAT_S;

typedef IPF_CONFIG_PARAM_S IPF_CONFIG_ULPARAM_S;
typedef IPF_CONFIG_PARAM_S IPF_CONFIG_DLPARAM_S;

/*****************************************************************************
* ?? ?? ??  : mdrv_ipf_register_ops
*
* ????????  : ????ops????????????????????/????????????????????????????ADQ??
*             ??????????????
*
* ????????  : struct mdrv_ipf_ops *ops  ??????????????????
* ????????  :
*
* ?? ?? ??  : IPF_SUCCESS ????????
*             IPF_ERROR ????????
* ????????  :
*
*****************************************************************************/
int mdrv_ipf_register_ops(struct mdrv_ipf_ops *ops);

#ifdef __cplusplus
}
#endif

#endif
