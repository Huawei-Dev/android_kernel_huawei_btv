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

#include <linux/version.h>
#include <linux/gfp.h>
#include <linux/mm.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/kthread.h>
#include <linux/interrupt.h>
#include <linux/spinlock.h>
#include <linux/string.h>
#include <linux/mm.h>
#include <linux/mman.h>
#include <linux/delay.h>
#include <linux/errno.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/vmalloc.h>
#include "socp_balong.h"
#include <linux/clk.h>
#include "bsp_version.h"
#include "bsp_dump.h"
#include "bsp_nvim.h"
#include "drv_nv_id.h"
/* log2.0 2014-03-19 Begin:*/
#include "drv_nv_def.h"
#include "bsp_om.h"
#include "bsp_slice.h"
#include "bsp_softtimer.h"
#include "product_config.h"
/* log2.0 2014-03-19 End*/


SOCP_GBL_STATE g_strSocpStat = {0};
EXPORT_SYMBOL(g_strSocpStat);
SOCP_DEBUG_INFO_S g_stSocpDebugInfo;
EXPORT_SYMBOL(g_stSocpDebugInfo);

/* ?????????????? */
#define SOCP_ENCSRC_TASK_PRO    79
#define SOCP_ENCDST_TASK_PRO    81
#define SOCP_DECSRC_TASK_PRO    79
#define SOCP_DECDST_TASK_PRO    81
/* SOCP?????? */
u32 g_SocpRegBaseAddr = 0;
/* ???????????? */
u32 socp_app_int_handler(void);
/*lint -save -e512*/
spinlock_t lock;
/*lint -restore +e512*/
u32 g_ulThrowout = 0;

u32 socp_version = 0;

/* log2.0 2014-03-19 Begin:*/
struct socp_enc_dst_log_cfg g_stEncDstBufLogConfig = {NULL,0,0,10,false,10,false};
/* log2.0 2014-03-19 End*/


#define SOCP_MAX_ENC_DST_COUNT      100
struct socp_enc_dst_stat_s
{
    u32 ulIntStartSlice;
    u32 ulIntEndSlice;
    u32 ulTaskStartSlice;
    u32 ulTaskEndSlice;
    u32 ulReadDoneStartSlice;
    u32 ulReadDoneEndSlice;
};
u32 g_ulEncDstStatCount;

struct socp_enc_dst_stat_s g_stEncDstStat[SOCP_MAX_ENC_DST_COUNT];

/* ???????????????????? */
SOCP_VOTE_INFO_STRU g_stVoteInfo[SOCP_VOTE_ID_BUTT] = { {SOCP_VOTE_FOR_WAKE,0}, {SOCP_VOTE_FOR_WAKE,0}, \
                                                        {SOCP_VOTE_FOR_WAKE,0}, {SOCP_VOTE_FOR_WAKE,0}, \
                                                        {SOCP_VOTE_FOR_WAKE,0}};
SOCP_POWER_STATE_ENUM_U32 g_ulSocpPowerState = SOCP_POWER_ON;
u32 g_ulSocpOnDemand = BSP_TRUE;
struct semaphore g_stSocpPowerSem;
SOCP_VCC_STRU * g_stSocpVcc;
/* ????SOCP?????????????????????????? */
u32 g_ul_encdst_tran_int_mask = 0;
/* ????SOCP?????????????????????????? */
u32 g_ul_encdst_over_int_mask = 0;
/* ????SOCP?????????????????????????? */
u32 g_ul_decdst_tran_int_mask = 0;



/*****************************************************************************
* ?? ?? ??  : socp_chan_is_idle
*
* ????????  : ????????????????????????
*
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??  : s32
*****************************************************************************/
s32 socp_chan_is_idle(void)
{
    u32 i;
    u32 u32WritePtr;
    u32 u32ReadPtr;
    u32 u32EncChanState;
    u32 u32DecChanState;

    /* ???????????????????????? */
    SOCP_REG_READ(SOCP_REG_ENCSTAT, u32EncChanState);
    if(u32EncChanState != 0)
    {
        /* ???????? */
        g_ulSocpPowerState = SOCP_POWER_OFF_REQ;
        socp_printf("%s: enc src busy 0x%x, SOCP_POWER_OFF_REQ\n", __FUNCTION__, u32EncChanState);
        return BSP_ERROR;
    }

    /* ???????????????????????????????? */
    for(i = 0; i < SOCP_MAX_ENCDST_CHN; i++)
    {
        SOCP_REG_READ(SOCP_REG_ENCDEST_BUFWPTR(i), u32WritePtr);
        SOCP_REG_READ(SOCP_REG_ENCDEST_BUFRPTR(i), u32ReadPtr);
        if(u32WritePtr != u32ReadPtr)
        {
            g_ulSocpPowerState = SOCP_POWER_OFF_REQ;
            socp_printf("%s: enc dst chan 0x%x not read done, SOCP_POWER_OFF_REQ\n", __FUNCTION__, i);
            return BSP_ERROR;
        }
    }

    /* ???????????????????????? */
    SOCP_REG_READ(SOCP_REG_DECSTAT, u32DecChanState);
    if(u32DecChanState != 0)
    {
        /* ???????? */
        g_ulSocpPowerState = SOCP_POWER_OFF_REQ;
        socp_printf("%s: dec src busy 0x%x, SOCP_POWER_OFF_REQ\n", __FUNCTION__, u32DecChanState);
        return BSP_ERROR;
    }

    /* ???????????????????????????????? */
    for(i = 0; i < SOCP_MAX_DECDST_CHN; i++)
    {
        SOCP_REG_READ(SOCP_REG_DECDEST_BUFWPTR(i), u32WritePtr);
        SOCP_REG_READ(SOCP_REG_DECDEST_BUFRPTR(i), u32ReadPtr);
        if(u32WritePtr != u32ReadPtr)
        {
            g_ulSocpPowerState = SOCP_POWER_OFF_REQ;
            socp_printf("%s: dec dst chan 0x%x not read done, SOCP_POWER_OFF_REQ\n", __FUNCTION__, i);
            return BSP_ERROR;
        }
    }

    return BSP_OK;
}
/*****************************************************************************
* ?? ?? ??  : socp_get_idle_buffer
*
* ????????  : ??????????????
*
* ????????  :  pRingBuffer       ????????????buffer
                    pRWBuffer         ??????????buffer
*
* ????????  : ??
*
* ?? ?? ??  :  ??
*****************************************************************************/
void socp_get_idle_buffer(SOCP_RING_BUF_S *pRingBuffer, SOCP_BUFFER_RW_STRU *pRWBuffer)
{
    if(pRingBuffer->u32Write < pRingBuffer->u32Read)
    {
        /* ?????????????????????????? */
        pRWBuffer->pBuffer = (char *)((unsigned long)pRingBuffer->u32Write);
        pRWBuffer->u32Size = (u32)(pRingBuffer->u32Read - pRingBuffer->u32Write - 1);
        pRWBuffer->pRbBuffer = (char *)BSP_NULL;
        pRWBuffer->u32RbSize = 0;
    }
    else
    {
        /* ?????????????????????????????? */
        if(pRingBuffer->u32Read != pRingBuffer->u32Start)
        {
            pRWBuffer->pBuffer = (char *)((unsigned long)pRingBuffer->u32Write);
            pRWBuffer->u32Size = (u32)(pRingBuffer->u32End - pRingBuffer->u32Write + 1);
            pRWBuffer->pRbBuffer = (char *)((unsigned long)pRingBuffer->u32Start);
            pRWBuffer->u32RbSize = (u32)(pRingBuffer->u32Read - pRingBuffer->u32Start - 1);
        }
        else
        {
            pRWBuffer->pBuffer = (char *)((unsigned long)pRingBuffer->u32Write);
            pRWBuffer->u32Size = (u32)(pRingBuffer->u32End - pRingBuffer->u32Write);
            pRWBuffer->pRbBuffer = (char *)BSP_NULL;
            pRWBuffer->u32RbSize = 0;
        }
    }

    return;
}

/*****************************************************************************
* ?? ?? ??  : socp_get_data_buffer
*
* ????????  : ????????????????????
*
* ????????  :  pRingBuffer       ????????????buffer
                    pRWBuffer         ??????????buffer
*
* ????????  : ??
*
* ?? ?? ??  :  ??
*****************************************************************************/
void socp_get_data_buffer(SOCP_RING_BUF_S *pRingBuffer, SOCP_BUFFER_RW_STRU *pRWBuffer)
{
    if(pRingBuffer->u32Read <= pRingBuffer->u32Write)
    {
        /* ?????????????????????????? */
        pRWBuffer->pBuffer = (char *)((unsigned long)pRingBuffer->u32Read);
        pRWBuffer->u32Size = (u32)(pRingBuffer->u32Write - pRingBuffer->u32Read);
        pRWBuffer->pRbBuffer = (char *)BSP_NULL;
        pRWBuffer->u32RbSize = 0;
    }
    else
    {
        /* ?????????????????????????????? */
        pRWBuffer->pBuffer = (char *)((unsigned long)pRingBuffer->u32Read);
        pRWBuffer->u32Size = (u32)(pRingBuffer->u32End - pRingBuffer->u32Read + 1);
        pRWBuffer->pRbBuffer = (char *)((unsigned long)pRingBuffer->u32Start);
        pRWBuffer->u32RbSize = (u32)(pRingBuffer->u32Write - pRingBuffer->u32Start);
    }

    return;
}

/*****************************************************************************
* ?? ?? ??  : socp_write_done
*
* ????????  : ??????????????????
*
* ????????  :  pRingBuffer       ????????????buffer
                    u32Size          ??????????????
*
* ????????  : ??
*
* ?? ?? ??  :  ??
*****************************************************************************/
void socp_write_done(SOCP_RING_BUF_S *pRingBuffer, u32 u32Size)
{
    u32 tmp_size;

    tmp_size = pRingBuffer->u32End - pRingBuffer->u32Write + 1;
    if(tmp_size > u32Size)
    {
        /* SCM??????CACHE???? */
        (void)SOCP_FLUSH_CACHE(pRingBuffer->u32Write, u32Size);
        pRingBuffer->u32Write += u32Size;
    }
    else
    {
        u32 rb_size = u32Size - tmp_size;
        /* SCM??????CACHE???? */
        (void)SOCP_FLUSH_CACHE(pRingBuffer->u32Write, tmp_size);
        (void)SOCP_FLUSH_CACHE(pRingBuffer->u32Start, rb_size);
        pRingBuffer->u32Write = pRingBuffer->u32Start + rb_size;
    }
    return;
}
/*****************************************************************************
* ?? ?? ??  : socp_read_done
*
* ????????  : ??????????????????
*
* ????????  :  pRingBuffer       ????????????buffer
                    u32Size          ??????????????
*
* ????????  : ??
*
* ?? ?? ??  :  ??
*****************************************************************************/
void socp_read_done(SOCP_RING_BUF_S *pRingBuffer, u32 u32Size)
{
    pRingBuffer->u32Read += u32Size;
    if(pRingBuffer->u32Read > pRingBuffer->u32End)
    {
        pRingBuffer->u32Read -= pRingBuffer->u32Length;
    }
}

/*****************************************************************************
* ?? ?? ??  : bsp_socp_clean_encsrc_chan
*
* ????????  : ????????????????????V9 SOCP????
*
* ????????  : enSrcChanID       ??????????
*
* ????????  : ??
*
* ?? ?? ??  : BSP_OK
*****************************************************************************/
u32 bsp_socp_clean_encsrc_chan(SOCP_CODER_SRC_ENUM_U32 enSrcChanID)
{
    u32 ulResetFlag;
    u32 i;
    u32 ulChanID;
    u32 ulChanType;

    ulChanID    = SOCP_REAL_CHAN_ID(enSrcChanID);
    ulChanType  = SOCP_REAL_CHAN_TYPE(enSrcChanID);

    SOCP_CHECK_CHAN_TYPE(ulChanType, SOCP_CODER_SRC_CHAN);
    SOCP_CHECK_ENCSRC_CHAN_ID(ulChanID);

    /* ???????? */
    SOCP_REG_SETBITS(SOCP_REG_ENCRST, ulChanID, 1, 1);

    /* ???????????? */
    for(i=0; i< SOCP_RESET_TIME; i++)
    {
        ulResetFlag = SOCP_REG_GETBITS(SOCP_REG_ENCRST, ulChanID, 1);

        if(0 == ulResetFlag)
        {
            break;
        }
    }

    if(SOCP_RESET_TIME == i)
    {
        socp_printf("SocpCleanEncChan failed!\n");
    }

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : socp_reset_enc_chan
*
* ????????  : ????????????
*
* ????????  : u32ChanID       ??????????
*
* ????????  : ??
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/
s32 socp_reset_enc_chan(u32 u32ChanID)
{
    u32  ResetFlag;
    u32  i;
    SOCP_ENCSRC_CHAN_S *pChan;

    pChan = &g_strSocpStat.sEncSrcChan[u32ChanID];

    /* ???????? */
    SOCP_REG_SETBITS(SOCP_REG_ENCRST, u32ChanID, 1, 1);

    /* ???????????? */
    for(i=0; i<SOCP_RESET_TIME; i++)
    {
        ResetFlag = SOCP_REG_GETBITS(SOCP_REG_ENCRST, u32ChanID, 1);
        if(0 == ResetFlag)
        {
            break;
        }

        if((SOCP_RESET_TIME -1) == i)
        {
            socp_printf("socp_reset_enc_chan 0x%x failed!\n", u32ChanID);
        }
    }

    /* ????????????*/
    /* ????????????????buffer??????????????*/
    SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFADDR(u32ChanID),SOCP_VIRT_PHY(pChan->sEncSrcBuf.u32Start));
    SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFWPTR(u32ChanID),SOCP_VIRT_PHY(pChan->sEncSrcBuf.u32Start));
    SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFRPTR(u32ChanID), SOCP_VIRT_PHY(pChan->sEncSrcBuf.u32Start));
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG0(u32ChanID), 0, 27, pChan->sEncSrcBuf.u32Length);
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG0(u32ChanID), 27, 5, 0);
    /* ????????????*/
    g_strSocpStat.sEncSrcChan[u32ChanID].sEncSrcBuf.u32Read  = pChan->sEncSrcBuf.u32Start;
    g_strSocpStat.sEncSrcChan[u32ChanID].sEncSrcBuf.u32Write = pChan->sEncSrcBuf.u32Start;


    /* ??????????????????????????RDbuffer???????????????? */
    if(SOCP_ENCSRC_CHNMODE_LIST == pChan->eChnMode)
    {
        SOCP_REG_WRITE(SOCP_REG_ENCSRC_RDQADDR(u32ChanID),SOCP_VIRT_PHY(pChan->sRdBuf.u32Start));
        SOCP_REG_WRITE(SOCP_REG_ENCSRC_RDQRPTR(u32ChanID),SOCP_VIRT_PHY(pChan->sRdBuf.u32Start));
        SOCP_REG_WRITE(SOCP_REG_ENCSRC_RDQWPTR(u32ChanID), SOCP_VIRT_PHY(pChan->sRdBuf.u32Start));
        socp_printf("\r\nsocp_reset_enc_chan: ID is %d, VBuf addr is 0x%X, PBuf addr is 0x%X.\r\n", u32ChanID, pChan->sRdBuf.u32Start, SOCP_VIRT_PHY(pChan->sRdBuf.u32Start));
        SOCP_REG_SETBITS(SOCP_REG_ENCSRC_RDQCFG(u32ChanID), 0, 16, pChan->sRdBuf.u32Length);
		SOCP_REG_SETBITS(SOCP_REG_ENCSRC_RDQCFG(u32ChanID), 16, 16, 0);

        g_strSocpStat.sEncSrcChan[u32ChanID].sRdBuf.u32Read  = pChan->sRdBuf.u32Start;
        g_strSocpStat.sEncSrcChan[u32ChanID].sRdBuf.u32Write = pChan->sRdBuf.u32Start;
    }

    /*????????????*/
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(u32ChanID), 1, 2, pChan->eChnMode);
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(u32ChanID), 4, 4, pChan->u32DestChanID);
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(u32ChanID), 8, 2, pChan->ePriority);
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(u32ChanID), 10, 1, pChan->u32BypassEn);
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(u32ChanID), 16, 8, pChan->eDataType);
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(u32ChanID), 11, 1, pChan->eDataTypeEn);
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(u32ChanID), 31, 1, pChan->eDebugEn);

    /*????????????????????????????*/
    if(pChan->u32ChanEn)
    {
        SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(u32ChanID), 0, 1, 1);
    }

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : socp_reset_dec_chan
*
* ????????  : ????????????
*
* ????????  : u32ChanID       ??????????
*
* ????????  : ??
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/
s32 socp_reset_dec_chan(u32 u32ChanID)
{
    u32  u32ResetFlag;
    u32  i;
    SOCP_DECSRC_CHAN_S *pChan;

    if(u32ChanID >= SOCP_MAX_DECSRC_CHN)
    {
        return BSP_ERROR;
    }

    pChan = &g_strSocpStat.sDecSrcChan[u32ChanID];

    /* ???????? */
    SOCP_REG_SETBITS(SOCP_REG_DECRST, u32ChanID, 1, 1);

    /* ???????????? */
    for(i=0; i<SOCP_RESET_TIME; i++)
    {
        u32ResetFlag = SOCP_REG_GETBITS(SOCP_REG_DECRST, u32ChanID, 1);
        if(0 == u32ResetFlag)
        {
            break;
        }
        if((SOCP_RESET_TIME -1) == i)
        {
            socp_printf("socp_reset_dec_chan 0x%x failed!\n", u32ChanID);
        }
    }

    /* ???????????????????? */
    SOCP_REG_WRITE(SOCP_REG_DECSRC_BUFADDR(u32ChanID), SOCP_VIRT_PHY(pChan->sDecSrcBuf.u32Start));
    SOCP_REG_WRITE(SOCP_REG_DECSRC_BUFWPTR(u32ChanID), SOCP_VIRT_PHY(pChan->sDecSrcBuf.u32Start));
    SOCP_REG_WRITE(SOCP_REG_DECSRC_BUFRPTR(u32ChanID), SOCP_VIRT_PHY(pChan->sDecSrcBuf.u32Start));

    SOCP_REG_SETBITS(SOCP_REG_DECSRC_BUFCFG0(u32ChanID), 0, 16, pChan->sDecSrcBuf.u32Length);
    SOCP_REG_SETBITS(SOCP_REG_DECSRC_BUFCFG0(u32ChanID), 31, 1, pChan->eDataTypeEn);
    //SOCP_REG_SETBITS(SOCP_REG_DECSRC_RDQCFG(u32ChanID), 29, 1, 0);

    /* ??????????????????????*/
    g_strSocpStat.sDecSrcChan[u32ChanID].sDecSrcBuf.u32Read  = pChan->sDecSrcBuf.u32Start;
    g_strSocpStat.sDecSrcChan[u32ChanID].sDecSrcBuf.u32Write = pChan->sDecSrcBuf.u32Start;

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : socp_soft_free_encdst_chan
*
* ????????  : ??????????????????
*
* ????????  : u32EncDstChanId       ??????????
*
* ????????  : ??
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/
s32 socp_soft_free_encdst_chan(u32 u32EncDstChanId)
{
    u32 u32ChanID;
    u32 u32ChanType;
    SOCP_ENCDST_CHAN_S *pChan;

    u32ChanID   = SOCP_REAL_CHAN_ID(u32EncDstChanId);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32EncDstChanId);

    SOCP_CHECK_CHAN_TYPE(u32ChanType, SOCP_CODER_DEST_CHAN);
    SOCP_CHECK_CHAN_ID(u32ChanID, SOCP_MAX_ENCDST_CHN);

    pChan = &g_strSocpStat.sEncDstChan[u32ChanID];

    /* ??????????????????buffer??????????????*/
    SOCP_REG_WRITE(SOCP_REG_ENCDEST_BUFADDR(u32ChanID), SOCP_VIRT_PHY(pChan->sEncDstBuf.u32Start));
    SOCP_REG_WRITE(SOCP_REG_ENCDEST_BUFRPTR(u32ChanID), SOCP_VIRT_PHY(pChan->sEncDstBuf.u32Start));
    SOCP_REG_WRITE(SOCP_REG_ENCDEST_BUFWPTR(u32ChanID), SOCP_VIRT_PHY(pChan->sEncDstBuf.u32Start));

    g_strSocpStat.sEncDstChan[u32ChanID].u32SetStat = SOCP_CHN_UNSET;
    g_strSocpStat.sEncDstChan[u32ChanID].sEncDstBuf.u32Write = pChan->sEncDstBuf.u32Start;
    g_strSocpStat.sEncDstChan[u32ChanID].sEncDstBuf.u32Read = pChan->sEncDstBuf.u32Start;

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : socp_soft_free_decsrc_chan
*
* ????????  : ????????????????
*
* ????????  : u32DecSrcChanId       ??????????
*
* ????????  : ??
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/
s32 socp_soft_free_decsrc_chan(u32 u32DecSrcChanId)
{
    u32 u32ChanID;
    u32 u32ChanType;
    SOCP_DECSRC_CHAN_S *pDecSrcChan;

    u32ChanID   = SOCP_REAL_CHAN_ID(u32DecSrcChanId);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32DecSrcChanId);

    SOCP_CHECK_CHAN_TYPE(u32ChanType, SOCP_DECODER_SRC_CHAN);
    SOCP_CHECK_CHAN_ID(u32ChanID, SOCP_MAX_DECSRC_CHN);

    pDecSrcChan = &g_strSocpStat.sDecSrcChan[u32ChanID];

    /* ??????????????????buffer??????????????*/
    SOCP_REG_WRITE(SOCP_REG_DECSRC_BUFWPTR(u32ChanID), SOCP_VIRT_PHY(pDecSrcChan->sDecSrcBuf.u32Start));
    SOCP_REG_WRITE(SOCP_REG_DECSRC_BUFADDR(u32ChanID), SOCP_VIRT_PHY(pDecSrcChan->sDecSrcBuf.u32Start));
    SOCP_REG_WRITE(SOCP_REG_DECSRC_BUFRPTR(u32ChanID), SOCP_VIRT_PHY(pDecSrcChan->sDecSrcBuf.u32Start));

    g_strSocpStat.sDecSrcChan[u32ChanID].u32SetStat = SOCP_CHN_UNSET;
    g_strSocpStat.sDecSrcChan[u32ChanID].sDecSrcBuf.u32Write = pDecSrcChan->sDecSrcBuf.u32Start;
    g_strSocpStat.sDecSrcChan[u32ChanID].sDecSrcBuf.u32Read = pDecSrcChan->sDecSrcBuf.u32Start;

    return BSP_OK;
}


/*****************************************************************************
* ?? ?? ??  : socp_get_enc_rd_size
*
* ????????  :  ??????????????RDbuffer
*
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/
u32 socp_get_enc_rd_size(u32 u32ChanID)
{
    SOCP_BUFFER_RW_STRU Buff;
    u32          PAddr;

    SOCP_REG_READ(SOCP_REG_ENCSRC_RDQRPTR(u32ChanID), PAddr);
    g_strSocpStat.sEncSrcChan[u32ChanID].sRdBuf.u32Read = SOCP_PHY_VIRT(PAddr);
    SOCP_REG_READ(SOCP_REG_ENCSRC_RDQWPTR(u32ChanID), PAddr);
    g_strSocpStat.sEncSrcChan[u32ChanID].sRdBuf.u32Write= SOCP_PHY_VIRT(PAddr);

    socp_get_data_buffer(&g_strSocpStat.sEncSrcChan[u32ChanID].sRdBuf, &Buff);
    return (Buff.u32Size + Buff.u32RbSize);
}

/*****************************************************************************
* ?? ?? ??   : socp_encsrc_rd_handler
*
* ????????  :  ??????????RDbuffer????????????
*
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
void socp_encsrc_rd_handler(u32 RdSize, u32 i)
{
    u32 u32ChanId;

    if (RdSize == g_strSocpStat.sEncSrcChan[i].u32LastRdSize)
    {
        if (g_strSocpStat.sEncSrcChan[i].rd_cb)
        {
            u32ChanId = SOCP_CHAN_DEF(SOCP_CODER_SRC_CHAN, i);
            (void)g_strSocpStat.sEncSrcChan[i].rd_cb(u32ChanId);

            g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpEncSrcTskRdCbCnt[i]++;
        }

        g_strSocpStat.sEncSrcChan[i].u32LastRdSize = 0;
    }
    else
    {
        g_strSocpStat.sEncSrcChan[i].u32LastRdSize = RdSize;
    }

    return;
}

/*****************************************************************************
* ?? ?? ??  : socp_encsrc_task
*
* ????????  : ????????????:????????????????
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
int socp_encsrc_task(void * data)
{
    u32 i;
    u32 IntHeadState = 0;
    u32 u32ChanId;
    unsigned long lock_flag;
    /* coverity[no_escape] */
    do{
        /* ?????????????????????????? */
        if(0 != down_interruptible(&g_strSocpStat.u32EncSrcSemID))
        {
            continue;
        }

        spin_lock_irqsave(&lock, lock_flag);
        IntHeadState = g_strSocpStat.u32IntEncSrcHeader;
        g_strSocpStat.u32IntEncSrcHeader = 0;
        g_strSocpStat.u32IntEncSrcRD = 0;
        spin_unlock_irqrestore(&lock, lock_flag);

        /* ????????????'HISI'????????*/
        if (IntHeadState)
        {
            for (i = 0; i < SOCP_MAX_ENCSRC_CHN; i++)
            {
                /* ????????????????*/
                if (SOCP_CHN_ALLOCATED == g_strSocpStat.sEncSrcChan[i].u32AllocStat)
                {
                    if (IntHeadState & ((u32)1 << i))
                    {
                        if (g_strSocpStat.sEncSrcChan[i].event_cb)
                        {
                            g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpEncSrcTskHeadCbOriCnt[i]++;
                            u32ChanId = SOCP_CHAN_DEF(SOCP_CODER_SRC_CHAN, i);
                            socp_printf("\r\nsocp_encsrc_task: packet header Error Channel is %d\r\n", u32ChanId);
                            (void)g_strSocpStat.sEncSrcChan[i].event_cb(u32ChanId, SOCP_EVENT_PKT_HEADER_ERROR, 0);
                            g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpEncSrcTskHeadCbCnt[i]++;
                        }
                    }
                }
            }
        }
    } while (1);

    //return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : socp_encdst_task
*
* ????????  : ????????????:??????????App??
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
int socp_encdst_task(void * data)
{
    u32 i;
    u32 IntTfrState = 0;
    u32 IntOvfState = 0;
    u32 IntThresholdOvfState = 0;
    u32 u32ChanId;
    unsigned long lock_flag;

    /* coverity[no_escape] */
    do{
        /* ?????????????????????????? */
        if(0 != down_interruptible(&g_strSocpStat.u32EncDstSemID))
        {
            continue;
        }

        spin_lock_irqsave(&lock, lock_flag);
        IntTfrState = g_strSocpStat.u32IntEncDstTfr;
        g_strSocpStat.u32IntEncDstTfr = 0;
        IntOvfState = g_strSocpStat.u32IntEncDstOvf;
        g_strSocpStat.u32IntEncDstOvf = 0;
        IntThresholdOvfState = g_strSocpStat.u32IntEncDstThresholdOvf;
        g_strSocpStat.u32IntEncDstThresholdOvf = 0;
        spin_unlock_irqrestore(&lock, lock_flag);

        /* ????????????????????*/
        if (IntTfrState)
        {
            for (i = 0; i < SOCP_MAX_ENCDST_CHN; i++)
            {
                /* ????????????????*/
                if (SOCP_CHN_SET == g_strSocpStat.sEncDstChan[i].u32SetStat)
                {
                    if (IntTfrState & ((u32)1 << i))
                    {
                        if (g_strSocpStat.sEncDstChan[i].read_cb)
                        {
                            g_stSocpDebugInfo.sSocpDebugEncDst.u32SocpEncDstTskTrfCbOriCnt[i]++;
                            u32ChanId = SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN, i);
                            if(i == 1){
                                g_stEncDstStat[g_ulEncDstStatCount].ulTaskStartSlice = bsp_get_slice_value();
                            }
                            (void)g_strSocpStat.sEncDstChan[i].read_cb(u32ChanId);
                            if(i == 1){
                                g_stEncDstStat[g_ulEncDstStatCount].ulTaskEndSlice = bsp_get_slice_value();
                            }

                            g_stSocpDebugInfo.sSocpDebugEncDst.u32SocpEncDstTskTrfCbCnt[i]++;
                        }
                    }
                }
            }
        }

        /* ???????????? buffer ????????*/
        if (IntOvfState)
        {
            for (i = 0; i < SOCP_MAX_ENCDST_CHN; i++)
            {
                /* ????????????????*/
                if (SOCP_CHN_SET == g_strSocpStat.sEncDstChan[i].u32SetStat)
                {
                    if (IntOvfState & ((u32)1 << i))
                    {
                        if (g_strSocpStat.sEncDstChan[i].event_cb)
                        {
                            g_stSocpDebugInfo.sSocpDebugEncDst.u32SocpEncDstTskOvfCbOriCnt[i]++;
                            u32ChanId = SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN, i);
                            (void)g_strSocpStat.sEncDstChan[i].event_cb(u32ChanId, SOCP_EVENT_OUTBUFFER_OVERFLOW, 0);

                            g_stSocpDebugInfo.sSocpDebugEncDst.u32SocpEncDstTskOvfCbCnt[i]++;
                        }
                        if (g_strSocpStat.sEncDstChan[i].read_cb)
                        {
                            g_stSocpDebugInfo.sSocpDebugEncDst.u32SocpEncDstTskTrfCbOriCnt[i]++;
                            u32ChanId = SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN, i);
                            (void)g_strSocpStat.sEncDstChan[i].read_cb(u32ChanId);

                            g_stSocpDebugInfo.sSocpDebugEncDst.u32SocpEncDstTskTrfCbCnt[i]++;
                        }
                    }
                }
            }
        }

        /* ???????????? buffer ????????????*/
        if (IntThresholdOvfState)
        {
            for (i = 0; i < SOCP_MAX_ENCDST_CHN; i++)
            {
                /* ????????????????*/
                if (SOCP_CHN_SET == g_strSocpStat.sEncDstChan[i].u32SetStat)
                {
                    if (IntThresholdOvfState & ((u32)1 << (i + SOCP_ENC_DST_BUFF_THRESHOLD_OVF_BEGIN)))
                    {
                        if (g_strSocpStat.sEncDstChan[i].event_cb)
                        {
                            g_stSocpDebugInfo.sSocpDebugEncDst.u32SocpEncDstTskOvfCbOriCnt[i]++;
                            u32ChanId = SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN, i);
                            (void)g_strSocpStat.sEncDstChan[i].event_cb(u32ChanId, SOCP_EVENT_OUTBUFFER_OVERFLOW, 0);

                            g_stSocpDebugInfo.sSocpDebugEncDst.u32SocpEncDstTskOvfCbCnt[i]++;
                        }
                        if (g_strSocpStat.sEncDstChan[i].read_cb)
                        {
                            g_stSocpDebugInfo.sSocpDebugEncDst.u32SocpEncDstTskTrfCbOriCnt[i]++;
                            u32ChanId = SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN, i);
                            (void)g_strSocpStat.sEncDstChan[i].read_cb(u32ChanId);

                            g_stSocpDebugInfo.sSocpDebugEncDst.u32SocpEncDstTskTrfCbCnt[i]++;
                        }
                    }
                }
            }
        }

    } while (1);

    //return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : socp_decsrc_event_handler
*
* ????????  : ??????????????????????
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
void  socp_decsrc_event_handler(u32 id, u32 secIntState)
{
    u32 u32ChanId = SOCP_CHAN_DEF(SOCP_DECODER_SRC_CHAN, id);

    if (g_strSocpStat.sDecSrcChan[id].event_cb)
    {
        if (secIntState & 0x10)
        {
            g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpDecSrcTskErrCbOriCnt[id]++;

            (void)g_strSocpStat.sDecSrcChan[id].event_cb(u32ChanId, SOCP_EVENT_DECODER_UNDERFLOW, 0);

            g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpDecSrcTskErrCbCnt[id]++;
        }

        if (secIntState & 0x100)
        {
            g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpDecSrcTskErrCbOriCnt[id]++;

            (void)g_strSocpStat.sDecSrcChan[id].event_cb(u32ChanId, SOCP_EVENT_HDLC_HEADER_ERROR, 0);

            g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpDecSrcTskErrCbCnt[id]++;
        }

        if (secIntState & 0x1000)
        {
            g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpDecSrcTskErrCbOriCnt[id]++;

            (void)g_strSocpStat.sDecSrcChan[id].event_cb(u32ChanId, SOCP_EVENT_DATA_TYPE_ERROR, 0);

            g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpDecSrcTskErrCbCnt[id]++;
        }

        if (secIntState & 0x10000)
        {
            g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpDecSrcTskErrCbOriCnt[id]++;

            (void)g_strSocpStat.sDecSrcChan[id].event_cb(u32ChanId, SOCP_EVENT_CRC_ERROR, 0);

            g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpDecSrcTskErrCbCnt[id]++;
        }

        if (secIntState & 0x100000)
        {
            g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpDecSrcTskErrCbOriCnt[id]++;

            (void)g_strSocpStat.sDecSrcChan[id].event_cb(u32ChanId, SOCP_EVENT_PKT_LENGTH_ERROR, 0);

            g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpDecSrcTskErrCbCnt[id]++;
        }
    }
}

/*****************************************************************************
* ?? ?? ??  : socp_decsrc_handler
*
* ????????  : ??????????????????????
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
void  socp_decsrc_handler(void)
{
    u32 IntState, secIntState;
    u32 u32ChanId;
    u32 i;

    if(g_strSocpStat.u32IntDecSrcErr)
    {
        IntState = g_strSocpStat.u32IntDecSrcErr;
        g_strSocpStat.u32IntDecSrcErr = 0;

        for(i=0;i<SOCP_MAX_DECSRC_CHN;i++)
        {
            /* ????????????????*/

            if(SOCP_CHN_SET == g_strSocpStat.sDecSrcChan[i].u32SetStat)
            {
                secIntState = IntState>>i;
                u32ChanId = SOCP_CHAN_DEF(SOCP_DECODER_SRC_CHAN, i);

                if(g_strSocpStat.sDecSrcChan[i].rd_cb)
                {
                    if(secIntState & 0x1)
                    {
                        (void)g_strSocpStat.sDecSrcChan[i].rd_cb(u32ChanId);
                    }
                }

                socp_decsrc_event_handler(i, secIntState);
            }
        }
    }
}

/*****************************************************************************
* ?? ?? ??  : socp_decsrc_task
*
* ????????  : ????????????:????????A??
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
int socp_decsrc_task(void * data)
{
    unsigned long lock_flag;
    /* coverity[no_escape] */
    do{
        /* ?????????????????????????? */
        if(0 != down_interruptible(&g_strSocpStat.u32DecSrcSemID))
        {
            continue;
        }
        spin_lock_irqsave(&lock, lock_flag);
        /* ??????????????*/
        socp_decsrc_handler();
        spin_unlock_irqrestore(&lock, lock_flag);
    }while(1);

    //return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : socp_decdst_task
*
* ????????  : ????????????:??????????????
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
int socp_decdst_task(void * data)
{
    u32 i;
    u32 IntTfrState = 0;
    u32 IntOvfState = 0;
    u32 u32ChanId;
    unsigned long lock_flag;
    /* coverity[no_escape] */
    do{
        /* ?????????????????????????? */
        if(0 != down_interruptible(&g_strSocpStat.u32DecDstSemID))
        {
            continue;
        }

        spin_lock_irqsave(&lock, lock_flag);
        IntTfrState = g_strSocpStat.u32IntDecDstTfr;
        g_strSocpStat.u32IntDecDstTfr = 0;
        IntOvfState = g_strSocpStat.u32IntDecDstOvf;
        g_strSocpStat.u32IntDecDstOvf = 0;
        spin_unlock_irqrestore(&lock, lock_flag);

        /* ????????????????????*/
        if (IntTfrState)
        {
            for (i = 0; i < SOCP_MAX_DECDST_CHN; i++)
            {
                /* ????????????????*/
                if (SOCP_CHN_ALLOCATED == g_strSocpStat.sDecDstChan[i].u32AllocStat)
                {
                    if (IntTfrState & ((u32)1 << i))
                    {
                        if (g_strSocpStat.sDecDstChan[i].read_cb)
                        {
                            g_stSocpDebugInfo.sSocpDebugDecDst.u32SocpDecDstTskTrfCbOriCnt[i]++;

                            u32ChanId = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, i);
                            (void)g_strSocpStat.sDecDstChan[i].read_cb(u32ChanId);

                            g_stSocpDebugInfo.sSocpDebugDecDst.u32SocpDecDstTskTrfCbCnt[i]++;
                        }
                    }
                }
            }
        }

        /* ???????????? buffer ????????*/
        if (IntOvfState)
        {
            for (i = 0; i < SOCP_MAX_DECDST_CHN; i++)
            {
                /* ????????????????*/
                if (SOCP_CHN_ALLOCATED == g_strSocpStat.sDecDstChan[i].u32AllocStat)
                {
                    if (IntOvfState & ((u32)1 << i))
                    {
                        if (g_strSocpStat.sDecDstChan[i].event_cb)
                        {
                            g_stSocpDebugInfo.sSocpDebugDecDst.u32SocpDecDstTskOvfCbOriCnt[i]++;

                            u32ChanId = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, i);
                            socp_printf("\r\nsocp_decdst_task: Call Event Cb, Channel is %d",u32ChanId);
                            (void)g_strSocpStat.sDecDstChan[i].event_cb(u32ChanId, SOCP_EVENT_OUTBUFFER_OVERFLOW, 0);

                            g_stSocpDebugInfo.sSocpDebugDecDst.u32SocpDecDstTskOvfCbCnt[i]++;
                        }
                    }
                }
            }
        }
    } while (1);

    //return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : socp_create_task
*
* ????????  : socp????????????
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/
s32 socp_create_task( s8 * puchName,
                        unsigned long * pu32TaskID,
                        socp_task_entry pfnFunc,
                        u32 u32Priority,
                        u32 u32StackSize,
                        void * pParam)
{
    struct task_struct  *tsk;
    struct sched_param  param;

    tsk = kthread_run(pfnFunc, pParam, puchName);
    if (IS_ERR(tsk))
    {
        socp_printf("socp_create_task: create kthread failed!\n");
        return BSP_ERROR;
    }

    param.sched_priority = u32Priority;
    if (BSP_OK != sched_setscheduler(tsk, SCHED_FIFO, &param))
    {
        socp_printf("\nsocp_create_task: Creat Task %s ID %p sched_setscheduler Error", puchName, pu32TaskID);
        return BSP_ERROR;
    }

    *pu32TaskID = (unsigned long)tsk;

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : socp_init_task
*
* ????????  : ??????????????
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/
s32 socp_init_task(void)
{
    u32 aulArguments[4] = {0,0,0,0};

    /* ??????????????*/
    sema_init(&g_strSocpStat.u32EncSrcSemID, 0);
    if(!g_strSocpStat.u32EncSrcTskID)
    {
        if ( BSP_OK != socp_create_task( "EncSrc", (unsigned long *)&g_strSocpStat.u32EncSrcTskID, (socp_task_entry)socp_encsrc_task,
                            SOCP_ENCSRC_TASK_PRO, 0x1000, aulArguments) )
        {
            socp_printf("socp_init_task: create socp_encsrc_task failed.\n");
            return BSP_ERR_SOCP_TSK_CREATE;
        }
    }

    /* ????????????????*/
    sema_init(&g_strSocpStat.u32EncDstSemID, 0);
    if(!g_strSocpStat.u32EncDstTskID)
    {
        if ( BSP_OK != socp_create_task( "EncDst", (unsigned long *)&g_strSocpStat.u32EncDstTskID, (socp_task_entry)socp_encdst_task,
                            SOCP_ENCDST_TASK_PRO, 0x1000, aulArguments) )
        {
            socp_printf("socp_init_task: create socp_encdst_task failed.\n");
            return BSP_ERR_SOCP_TSK_CREATE;
        }
    }

    /* ??????????????*/
    sema_init(&g_strSocpStat.u32DecSrcSemID, 0);
    if(!g_strSocpStat.u32DecSrcTskID)
    {
        if ( BSP_OK != socp_create_task( "DecSrc", (unsigned long *)&g_strSocpStat.u32DecSrcTskID, (socp_task_entry)socp_decsrc_task,
                            SOCP_DECSRC_TASK_PRO, 0x1000, aulArguments) )
        {
            socp_printf("socp_init_task: create u32DecSrcTskID failed.\n");
            return BSP_ERR_SOCP_TSK_CREATE;
        }
    }

    /* ????????????????*/
    sema_init(&g_strSocpStat.u32DecDstSemID, 0);
    if(!g_strSocpStat.u32DecDstTskID)
    {
        if ( BSP_OK != socp_create_task( "DecDst", (unsigned long *)&g_strSocpStat.u32DecDstTskID, (socp_task_entry)socp_decdst_task,
                            SOCP_DECDST_TASK_PRO, 0x1000, aulArguments) )
        {
            socp_printf("socp_init_task: create u32DecDstTskID failed.\n");
            return BSP_ERR_SOCP_TSK_CREATE;
        }
    }

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??   : socp_handler_encsrc
*
* ????????  : ????????????????????RD????????????????????RD????????????????
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
void  socp_handler_encsrc(void)
{
    u32 IntFlag   = 0;
    u32 IntState  = 0;
    int bHandle  = BSP_FALSE;
    u32 i = 0;

    /*read and clear the interrupt flags*/
    SOCP_REG_READ(SOCP_REG_GBL_INTSTAT, IntFlag);
    /* ???????????? */
    if (IntFlag & SOCP_APP_ENC_FLAGINT_MASK)
    {
        SOCP_REG_READ(SOCP_REG_APP_INTSTAT1, IntState);
        SOCP_REG_WRITE(SOCP_REG_ENC_RAWINT1, IntState);

        g_strSocpStat.u32IntEncSrcHeader |= IntState;
        bHandle = BSP_TRUE;

        for (i = 0; i < SOCP_MAX_ENCSRC_CHN; i++)
        {
            if (IntState & ((u32)1 << i))
            {
                /* debug???????????????????? */
        		if(SOCP_REG_GETBITS(SOCP_REG_ENCSRC_BUFCFG1(i), 31, 1))
        		{
        			SOCP_REG_SETBITS(SOCP_REG_APP_MASK1, i, 1,1);
        		}
                g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpEncSrcIsrHeadIntCnt[i]++;
            }
        }
    }

    /*????????RD?????????????????????????? */

    if(bHandle)
    {
        up(&g_strSocpStat.u32EncSrcSemID);
    }

    return ;
}


/*****************************************************************************
* ?? ?? ??   : socp_handler_encdst
*
* ????????  : ????????????????????
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
/*lint -save -e550*/
void socp_handler_encdst(void)
{
    u32  IntFlag = 0;
    u32  IntState = 0;
    int  bHandle = BSP_FALSE;
    u32  i;
    u32  mask;
    u32  mask2;
    u32  write;
    unsigned long lock_flag;
    int countFlag = BSP_FALSE;
    u32  ModeState = 0;

    /*????????????????*/
    SOCP_REG_READ(SOCP_REG_GBL_INTSTAT, IntFlag);
    if (IntFlag & SOCP_APP_ENC_TFRINT_MASK)
    {
        spin_lock_irqsave(&lock, lock_flag);
        SOCP_REG_READ(SOCP_REG_ENC_INTSTAT0, IntState);
        SOCP_REG_READ(SOCP_REG_ENC_MASK0, mask);
        SOCP_REG_WRITE(SOCP_REG_ENC_MASK0, (IntState | mask));   // mask int 2011.7.27 by yangzhi
        /* ???????????? */
        SOCP_REG_READ(SOCP_REG_ENC_MASK2, mask2);
        SOCP_REG_WRITE(SOCP_REG_ENC_MASK2, ((IntState << 16) | mask2));
        SOCP_REG_WRITE(SOCP_REG_ENC_RAWINT0, IntState);

        g_strSocpStat.u32IntEncDstTfr |= IntState;
        spin_unlock_irqrestore(&lock, lock_flag);
        bHandle = BSP_TRUE;

        for (i = 0; i < SOCP_MAX_ENCDST_CHN; i++)
        {
            if (IntState & ((u32)1 << i))
            {
                if(g_ulThrowout == 0x5a5a5a5a)
                {
                    spin_lock_irqsave(&lock, lock_flag);
                    SOCP_REG_READ(SOCP_REG_ENCDEST_BUFWPTR(i), write);
                    SOCP_REG_WRITE(SOCP_REG_ENCDEST_BUFRPTR(i), write);
                    SOCP_REG_SETBITS(SOCP_REG_ENC_RAWINT0, i, 1, 1);
                    SOCP_REG_SETBITS(SOCP_REG_ENC_MASK0, i, 1, 0);
                    /* overflow int */
                    SOCP_REG_SETBITS(SOCP_REG_ENC_RAWINT2, i + 16, 1, 1);
                    SOCP_REG_SETBITS(SOCP_REG_ENC_MASK2, i + 16, 1, 0);
                    spin_unlock_irqrestore(&lock, lock_flag);

                    bHandle = BSP_FALSE;
                }
                if(i == 1)
                {
                    g_stEncDstStat[g_ulEncDstStatCount].ulIntStartSlice = bsp_get_slice_value();
                    countFlag = BSP_TRUE;
                }
                g_stSocpDebugInfo.sSocpDebugEncDst.u32SocpEncDstIsrTrfIntCnt[i]++;
            }
        }
    }
    // ????????????????????????????????
    else if (IntFlag & SOCP_APP_ENC_OUTOVFINT_MASK)
    {
        SOCP_REG_READ(SOCP_REG_ENC_INTSTAT2, IntState);
        // ????????buffer????????????
        if(0 != (IntState & SOCP_ENC_DST_BUFF_THRESHOLD_OVF_MASK))
        {
            spin_lock_irqsave(&lock, lock_flag);
            SOCP_REG_READ(SOCP_REG_ENC_MASK2, mask);
            SOCP_REG_WRITE(SOCP_REG_ENC_MASK2, (IntState | mask));
            SOCP_REG_WRITE(SOCP_REG_ENC_RAWINT2, IntState);
            g_strSocpStat.u32IntEncDstThresholdOvf |= IntState;
            spin_unlock_irqrestore(&lock, lock_flag);

            bHandle = BSP_TRUE;

            for (i = 0; i < SOCP_MAX_ENCDST_CHN; i++)
            {
                if (IntState & ((u32)1 << (i + SOCP_ENC_DST_BUFF_THRESHOLD_OVF_BEGIN)))
                {
                    g_stSocpDebugInfo.sSocpDebugEncDst.u32SocpEncDstIsrThresholdOvfIntCnt[i]++;
                }
            }

        }
        // ????????buffer????????
        if (0 != (IntState & SOCP_ENC_DST_BUFF_OVF_MASK))
        {
            spin_lock_irqsave(&lock, lock_flag);
            SOCP_REG_READ(SOCP_REG_ENC_MASK2, mask);
            SOCP_REG_WRITE(SOCP_REG_ENC_MASK2, (IntState | mask));
            SOCP_REG_WRITE(SOCP_REG_ENC_RAWINT2, IntState);
            g_strSocpStat.u32IntEncDstOvf |= IntState;
            spin_unlock_irqrestore(&lock, lock_flag);

            bHandle = BSP_TRUE;

            for (i = 0; i < SOCP_MAX_ENCDST_CHN; i++)
            {
                if (IntState & ((u32)1 << i))
                {
                    g_stSocpDebugInfo.sSocpDebugEncDst.u32SocpEncDstIsrOvfIntCnt[i]++;
                }
            }
        }
    }
	else if(g_strSocpStat.compress_isr)
    {
		g_strSocpStat.compress_isr();
        return ;
	}

    /* ????????buffer???????????? */
    else if (IntFlag & SOCP_CORE0_ENC_MODESWT_MASK)
    {
        spin_lock_irqsave(&lock, lock_flag);
        
        SOCP_REG_READ(SOCP_REG_ENC_INTSTAT0, IntState);
        SOCP_REG_READ(SOCP_REG_ENC_MASK0, mask);
        SOCP_REG_SETBITS(SOCP_REG_ENC_MASK0, 16, 7, (((IntState | mask)>>16)&0x7f));

        /* ?????????????? */
        SOCP_REG_SETBITS(SOCP_REG_ENC_RAWINT0, 16, 7, ((IntState>>16)&0x7f));

        mask = 0;
        for (i = 0; i < SOCP_MAX_ENCDST_CHN; i++)
        {
            SOCP_REG_READ(SOCP_REG_ENCDEST_SBCFG(i), ModeState);
            if(ModeState & 0x02)
            {
                mask |= (1<<i);
            }
        }
        
        /* ???????????????????????????????????????????? */
        SOCP_REG_SETBITS(SOCP_REG_ENC_MASK0, 0, 7, mask);
        SOCP_REG_SETBITS(SOCP_REG_ENC_MASK2, 0, 7, mask);
        SOCP_REG_SETBITS(SOCP_REG_ENC_MASK2, 16, 7, mask);

        spin_unlock_irqrestore(&lock, lock_flag);
    }
    else
    {
        bHandle = BSP_FALSE;
    }

    if(bHandle)
    {
        if(countFlag == BSP_TRUE){
            g_stEncDstStat[g_ulEncDstStatCount].ulIntEndSlice= bsp_get_slice_value();
        }
        up(&g_strSocpStat.u32EncDstSemID);
    }

    return ;
}
/*lint -restore +e550*/

/*****************************************************************************
* ?? ?? ??   : socp_handler_decsrc
*
* ????????  : ??????????????????????
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
void socp_handler_decsrc(void)
{
    u32 IntFlag  = 0;
    u32 IntState = 0;
    int bHandle = BSP_FALSE;
    u32 i = 0;

    /*????????????*/
    SOCP_REG_READ(SOCP_REG_GBL_INTSTAT, IntFlag);
    if (IntFlag & SOCP_DEC_INERRINT_MASK)
    {
        SOCP_REG_READ(SOCP_REG_DEC_INTSTAT1, IntState);
        SOCP_REG_WRITE(SOCP_REG_DEC_RAWINT1, IntState);

        g_strSocpStat.u32IntDecSrcErr |= IntState;
        bHandle = BSP_TRUE;

        for (i = 0; i < SOCP_MAX_DECSRC_CHN; i++)
        {
            if (IntState & 0x1)
            {
                g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpDecSrcIsrErrIntCnt[i]++;
            }
        }
    }

    if(bHandle)
    {
        up(&g_strSocpStat.u32DecSrcSemID);
    }

    return;
}


/*****************************************************************************
* ?? ?? ??   : socp_handler_decdst
*
* ????????  : ????????????????????????
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
/*lint -save -e774*/
/*lint -save -e550*/
void socp_handler_decdst(void)
{
    u32 IntFlag  = 0;
    u32 IntState = 0;
    int bHandle = BSP_FALSE;
    u32 TfMask  = 0;
    u32 TfState = 0;
    u32 OvMask    = 0;
    u32 OvState   = 0;
    u32 TfMaskReg = 0;
    u32 i = 0;

    TfMask    = SOCP_CORE0_DEC_TFRINT_MASK;
    TfState   = SOCP_REG_DEC_CORE0ISTAT0;
    TfMaskReg = SOCP_REG_DEC_CORE0MASK0;
    OvMask  = SOCP_CORE0_DEC_OUTOVFINT_MASK;
    OvState = SOCP_REG_DEC_CORE0ISTAT2;

    /*????????????*/
    SOCP_REG_READ(SOCP_REG_GBL_INTSTAT, IntFlag);
    if (IntFlag & TfMask)
    {
        u32 mask;

        SOCP_REG_READ(TfState, IntState);
        IntState = IntState & 0xffff;
        SOCP_REG_READ(TfMaskReg, mask);
        SOCP_REG_WRITE(TfMaskReg, (IntState | mask));  //added by yangzhi 2011.7.27
        SOCP_REG_WRITE(SOCP_REG_DEC_RAWINT0, IntState);

        g_strSocpStat.u32IntDecDstTfr |= IntState;
        bHandle = BSP_TRUE;

        for (i = 0; i < SOCP_MAX_DECDST_CHN; i++)
        {
            if (IntState & ((u32)1 << i))
            {
                g_stSocpDebugInfo.sSocpDebugDecDst.u32SocpDecDstIsrTrfIntCnt[i]++;
            }
        }
    }

    /*????????buffer ????*/
    SOCP_REG_READ(SOCP_REG_GBL_INTSTAT, IntFlag);
    if (IntFlag & OvMask)
    {
        SOCP_REG_READ(OvState, IntState);
        IntState = IntState & 0xffff;
        SOCP_REG_WRITE(SOCP_REG_DEC_RAWINT2, IntState);

        g_strSocpStat.u32IntDecDstOvf |= IntState;
        bHandle = BSP_TRUE;

        for (i = 0; i < SOCP_MAX_DECDST_CHN; i++)
        {
            if (IntState & ((u32)1 << i))
            {
                g_stSocpDebugInfo.sSocpDebugDecDst.u32SocpDecDstIsrOvfIntCnt[i]++;
            }
        }
    }

    if(bHandle)
    {
        up(&g_strSocpStat.u32DecDstSemID);
    }

    return;
}
/*lint -restore +e550*/
/*lint -restore +e774*/

/*****************************************************************************
* ?? ?? ??   : socp_app_int_handler
*
* ????????  : APP ??????????????
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
u32 socp_app_int_handler(void)
{
    g_stSocpDebugInfo.sSocpDebugGBl.u32SocpAppEtrIntCnt++;

    socp_handler_encsrc();

    socp_handler_encdst();
    socp_handler_decsrc();
    socp_handler_decdst();

    g_stSocpDebugInfo.sSocpDebugGBl.u32SocpAppSucIntCnt++;

    return 1;
}

/*****************************************************************************
* ?? ?? ??  : socp_init
*
* ????????  : ??????????????
*
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??  : ??????????????????
*****************************************************************************/
/*lint -save -e529*/
    extern  unsigned long SCM_CoderDstChanMemInit(void);
    extern unsigned long SCM_CoderDstChannelInit(void);
s32 socp_init(void)
{
    s32 ret;
    u32 i;
    u32 irq;
    u32 aulDstChan[SOCP_DST_CHAN_CFG_BUTT];
    struct device_node* dev = NULL;

    if(BSP_TRUE == g_strSocpStat.bInitFlag)
    {
        return BSP_OK;
    }

    spin_lock_init(&lock);

    /*Add dts begin*/
    dev = of_find_compatible_node(NULL,NULL,"hisilicon,socp_balong_app");
    if(NULL == dev)
    {
        socp_printf("socp_init: Socp dev find failed\n");
        return BSP_ERROR;
    }
    /*Add dts end*/

    g_strSocpStat.baseAddr = (unsigned long)of_iomap(dev,0);
    if(0 == g_strSocpStat.baseAddr)
    {
        socp_printf("socp_init:base addr is error!\n");
        return BSP_ERROR; /* [false alarm]:????Fortify???? */
    }

    /* bsp_memmap.h????????????BBP???????????????? */
    g_strSocpStat.armBaseAddr = (unsigned long)BBP_REG_ARM_BASEADDR;
    Socp_Memset(&g_stSocpDebugInfo, 0x0 ,sizeof(SOCP_DEBUG_INFO_S));


    /*????????????????????????????????????*/
    if(SOCP_DST_CHAN_DELAY == g_stEncDstBufLogConfig.logOnFlag)
    {
    /* ????SOCP????????????????????GLOBAL_CTRL:bit[1]??1??????????????INT_TIMEOUT(0x024)????????????????
       ??????32bit??????????????DEC_INT_TIMEOUT(0x20) */
        SOCP_REG_SETBITS(SOCP_REG_GBLRST, 1, 1, 0x1);
        SOCP_REG_WRITE(SOCP_REG_INTTIMEOUT, (g_stEncDstBufLogConfig.overTime*2289/1000));
    }

    /* ???????????????????? */
    /* ????ID?????? */
    g_strSocpStat.u32EncSrcTskID     = 0;
    g_strSocpStat.u32DecDstTskID     = 0;
    g_strSocpStat.u32EncDstTskID     = 0;
    g_strSocpStat.u32DecSrcTskID     = 0;
    /* ?????????????????? */
    g_strSocpStat.u32IntEncSrcHeader = 0;
    g_strSocpStat.u32IntEncSrcRD     = 0;
    g_strSocpStat.u32IntDecDstTfr    = 0;
    g_strSocpStat.u32IntDecDstOvf    = 0;
    g_strSocpStat.u32IntEncDstTfr    = 0;
    g_strSocpStat.u32IntEncDstOvf    = 0;
    g_strSocpStat.u32IntDecSrcErr    = 0;
    g_strSocpStat.compress_isr       = NULL;

    for(i=0; i<SOCP_MAX_ENCSRC_CHN; i++)
    {
        g_strSocpStat.sEncSrcChan[i].u32ChanID      = i;
        g_strSocpStat.sEncSrcChan[i].u32ChanEn      = SOCP_CHN_DISABLE;
        g_strSocpStat.sEncSrcChan[i].u32AllocStat   = SOCP_CHN_UNALLOCATED;
        g_strSocpStat.sEncSrcChan[i].u32LastRdSize  = 0;
        g_strSocpStat.sEncSrcChan[i].u32DestChanID  = 0xff;
        g_strSocpStat.sEncSrcChan[i].u32BypassEn    = 0;
        g_strSocpStat.sEncSrcChan[i].ePriority      = SOCP_CHAN_PRIORITY_3;
        g_strSocpStat.sEncSrcChan[i].eDataType      = SOCP_DATA_TYPE_BUTT;
        g_strSocpStat.sEncSrcChan[i].eDataTypeEn    = SOCP_DATA_TYPE_EN_BUTT;
        g_strSocpStat.sEncSrcChan[i].eDebugEn       = SOCP_ENC_DEBUG_EN_BUTT;
        g_strSocpStat.sEncSrcChan[i].event_cb       = (socp_event_cb)BSP_NULL;
        g_strSocpStat.sEncSrcChan[i].rd_cb          = (socp_rd_cb)BSP_NULL;
    }

    for(i=0; i<SOCP_MAX_ENCDST_CHN; i++)
    {
        g_strSocpStat.sEncDstChan[i].u32ChanID      = i;
        g_strSocpStat.sEncDstChan[i].u32Thrh        = 0;
        g_strSocpStat.sEncDstChan[i].u32SetStat     = SOCP_CHN_UNSET;
        g_strSocpStat.sEncDstChan[i].event_cb       = (socp_event_cb)BSP_NULL;
        g_strSocpStat.sEncDstChan[i].read_cb        = (socp_rd_cb)BSP_NULL;
        g_strSocpStat.sEncDstChan[i].eChnEvent      = (SOCP_EVENT_ENUM_UIN32)0;
        g_strSocpStat.sEncDstChan[i].struCompress.bcompress = SOCP_NO_COMPRESS;
        Socp_Memset(&g_strSocpStat.sEncDstChan[i].struCompress.ops,
              0x0,sizeof(socp_compress_ops_stru));
    }

    for(i=0; i<SOCP_MAX_DECSRC_CHN; i++)
    {
        g_strSocpStat.sDecSrcChan[i].u32ChanID      = i;
        g_strSocpStat.sDecSrcChan[i].u32ChanEn      = SOCP_CHN_DISABLE;
        g_strSocpStat.sDecSrcChan[i].eDataTypeEn    = SOCP_DATA_TYPE_EN_BUTT;
        g_strSocpStat.sDecSrcChan[i].u32SetStat     = SOCP_CHN_UNSET;
        g_strSocpStat.sDecSrcChan[i].event_cb       = (socp_event_cb)BSP_NULL;
        g_strSocpStat.sDecSrcChan[i].rd_cb          = (socp_rd_cb)BSP_NULL;
    }

    for(i=0; i<SOCP_MAX_DECDST_CHN; i++)
    {
        g_strSocpStat.sDecDstChan[i].u32ChanID      = i;
        g_strSocpStat.sDecDstChan[i].u32AllocStat   = SOCP_CHN_UNALLOCATED;
        g_strSocpStat.sDecDstChan[i].eDataType      = SOCP_DATA_TYPE_BUTT;
        g_strSocpStat.sDecDstChan[i].event_cb       = (socp_event_cb)BSP_NULL;
        g_strSocpStat.sDecDstChan[i].read_cb        = (socp_rd_cb)BSP_NULL;
    }

    /* ?????????????? */
    ret = socp_init_task();
    if (BSP_OK != ret)
    {
        socp_printf("socp_init: create task failed(0x%x).\n", ret);
        return (s32)ret;
    }

    /* ?????? */
    irq = irq_of_parse_and_map(dev,0);
    ret = request_irq(irq, (irq_handler_t)socp_app_int_handler, 0, "SOCP_APP_IRQ",  BSP_NULL);
    if (BSP_OK != ret)
    {
        socp_printf("socp_init: connect app core int failed.\n");
        return BSP_ERROR;
    }

    /* ????????????????????DTSI????????????????????buffer size */
    if(SOCP_DST_CHAN_NOT_CFG == g_stEncDstBufLogConfig.logOnFlag)
    {
        ret = of_property_read_u32_array(dev, "dst_chan_cfg", aulDstChan, SOCP_DST_CHAN_CFG_BUTT);
        if(ret)
        {
            socp_printf("socp_init:of_property_read_u32_array failed!\n");
        }
        else
        {
            socp_printf("socp_init:of_property_read_u32_array get size 0x%x!\n", aulDstChan[SOCP_DST_CHAN_CFG_SIZE]);

            /* ???????????????? */
            socp_get_dst_chan_buffer(aulDstChan[SOCP_DST_CHAN_CFG_SIZE]);
        }
    }

    /* ?????????????? */
    g_strSocpStat.bInitFlag = BSP_TRUE;

    SOCP_REG_READ(SOCP_REG_SOCP_VERSION, socp_version);

    (void)bsp_socp_vote(SOCP_VOTE_SOCP_REG,SOCP_VOTE_FOR_SLEEP);

    socp_printf("[socp_init]: succeed, base addr=0x%p, irq num:%d !\n",(void*)(g_strSocpStat.baseAddr),irq);

    ret = SCM_CoderDstChanMemInit();
    if(ret)
    {
        socp_printf("[%s]:SCM channel mem init fail\n", __FUNCTION__);
        return BSP_ERROR;
    }
    
    ret = SCM_CoderDstChannelInit();
    if(ret)
    {
        socp_printf("[%s]:SCM channel config init fail\n", __FUNCTION__);
        return BSP_ERROR;
    }

    return BSP_OK;
}

/*lint -restore +e529*/

/*****************************************************************************
* ?? ?? ??  : bsp_socp_coder_set_src_chan
*
* ????????  : ??????????????????
*
* ????????  : pSrcAttr     ??????????????????
*             ulSrcChanID  ??????????ID
*
* ????????  : ??
*
* ?? ?? ??  : ??????????????????????????
*****************************************************************************/
s32 bsp_socp_coder_set_src_chan(SOCP_CODER_SRC_ENUM_U32 enSrcChanID, SOCP_CODER_SRC_CHAN_S *pSrcAttr)
{
    u32 start;
    u32 end;
    u32 rdstart = 0;
    u32 rdend = 0;
    u32 buflength   = 0;
    u32 Rdbuflength = 0;
    u32 i;
    u32 srcChanId;
    u32 u32SrcChanType;
    u32 u32DstChanID;
    u32 u32DstChanType;
    u32 ResetFlag;
    SOCP_ENCSRC_CHAN_S *pChan;

    g_stSocpDebugInfo.sSocpDebugGBl.u32SocpAllocEncSrcCnt++;

    /* ?????????????????? */
    SOCP_CHECK_INIT();

    /* ?????????????? */
    SOCP_CHECK_PARA(pSrcAttr);
    SOCP_CHECK_CHAN_PRIORITY(pSrcAttr->ePriority);
    SOCP_CHECK_DATA_TYPE(pSrcAttr->eDataType);
    SOCP_CHECK_DATA_TYPE_EN(pSrcAttr->eDataTypeEn);
    SOCP_CHECK_ENC_DEBUG_EN(pSrcAttr->eDebugEn);

    srcChanId       = SOCP_REAL_CHAN_ID(enSrcChanID);
    u32SrcChanType  = SOCP_REAL_CHAN_TYPE(enSrcChanID);

    SOCP_CHECK_CHAN_TYPE(u32SrcChanType, SOCP_CODER_SRC_CHAN);
    SOCP_CHECK_ENCSRC_CHAN_ID(srcChanId);

    u32DstChanID   = SOCP_REAL_CHAN_ID(pSrcAttr->u32DestChanID);
    u32DstChanType = SOCP_REAL_CHAN_TYPE(pSrcAttr->u32DestChanID);
    SOCP_CHECK_CHAN_TYPE(u32DstChanType, SOCP_CODER_DEST_CHAN);
    SOCP_CHECK_CHAN_ID(u32DstChanID, SOCP_MAX_ENCDST_CHN);

    if ((SOCP_ENCSRC_CHNMODE_CTSPACKET != pSrcAttr->eMode)
        && (SOCP_ENCSRC_CHNMODE_LIST != pSrcAttr->eMode))
    {
        socp_printf("bsp_socp_coder_set_src_chan: chnnel mode is invalid %d!\n", pSrcAttr->eMode);
        return BSP_ERR_SOCP_INVALID_PARA;
    }

    /* ???????????????????? */
    /* ????????????????8???????? */
    start   = (uintptr_t)pSrcAttr->sCoderSetSrcBuf.pucInputStart;
    end     = (uintptr_t)pSrcAttr->sCoderSetSrcBuf.pucInputEnd;

    SOCP_CHECK_PARA(start);
    SOCP_CHECK_8BYTESALIGN(start);
    SOCP_CHECK_PARA(end);
    SOCP_CHECK_BUF_ADDR(start, end);
    buflength = end - start + 1;
    SOCP_CHECK_8BYTESALIGN(buflength);

    if(socp_version < SOCP_NEW_VERSION)
    {
        if(buflength > SOCP_ENC_SRC_BUFLGTH_MAX)
        {
            socp_printf("bsp_socp_coder_set_src_chan: buffer length is too large!\n");
            return BSP_ERR_SOCP_INVALID_PARA;
        }
    }

    /* ??????????????????????????RDbuffer???????????????? */
    if(SOCP_ENCSRC_CHNMODE_LIST == pSrcAttr->eMode)
    {
        /* ????RDBuffer??????????????8???????? */
        rdstart = (uintptr_t)pSrcAttr->sCoderSetSrcBuf.pucRDStart;
        rdend   = (uintptr_t)pSrcAttr->sCoderSetSrcBuf.pucRDEnd;

        SOCP_CHECK_PARA(rdstart);
        SOCP_CHECK_8BYTESALIGN(rdstart);
        SOCP_CHECK_PARA(rdend);
        SOCP_CHECK_BUF_ADDR(rdstart, rdend);
        /* RD???????????? */
        //SOCP_CHECK_PARA(pSrcAttr->sCoderSetSrcBuf.u32RDThreshold);
        Rdbuflength = rdend - rdstart + 1;
        SOCP_CHECK_8BYTESALIGN(Rdbuflength);
        if(Rdbuflength > SOCP_ENC_SRC_RDLGTH_MAX)
        {
            socp_printf("bsp_socp_coder_set_src_chan: RD buffer length is too large!\n");
            return BSP_ERR_SOCP_INVALID_PARA;
        }
    }

    /* ???????? */
    SOCP_REG_SETBITS(SOCP_REG_ENCRST, srcChanId, 1, 1);

    /* ???????????? */
    for (i = 0; i < SOCP_RESET_TIME; i++)
    {
        ResetFlag = SOCP_REG_GETBITS(SOCP_REG_ENCRST, srcChanId, 1);
        if(0 == ResetFlag)
        {
            break;
        }

        if ((SOCP_RESET_TIME - 1) == i)
        {
            socp_printf("bsp_socp_coder_set_src_chan: reset channel 0x%x failed!\n", srcChanId);
        }
    }

    /* ????????????????buffer??????????????*/
    SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFADDR(srcChanId),SOCP_VIRT_PHY(start));
    SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFWPTR(srcChanId),SOCP_VIRT_PHY(start));
    SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFRPTR(srcChanId), SOCP_VIRT_PHY(start));

    if(socp_version >= SOCP_NEW_VERSION)
    {
        SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFCFG0(srcChanId),buflength);
    }
    else
    {
        SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG0(srcChanId), 0, 27, buflength);
    	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG0(srcChanId), 27, 5, 0);
    }

    /* ??????????????????????????RDbuffer???????????????? */
    if(SOCP_ENCSRC_CHNMODE_LIST == pSrcAttr->eMode)
    {
        SOCP_REG_WRITE(SOCP_REG_ENCSRC_RDQADDR(srcChanId),SOCP_VIRT_PHY(rdstart));
        SOCP_REG_WRITE(SOCP_REG_ENCSRC_RDQRPTR(srcChanId),SOCP_VIRT_PHY(rdstart));
        SOCP_REG_WRITE(SOCP_REG_ENCSRC_RDQWPTR(srcChanId), SOCP_VIRT_PHY(rdstart));
        SOCP_REG_SETBITS(SOCP_REG_ENCSRC_RDQCFG(srcChanId), 0, 16, Rdbuflength);
		SOCP_REG_SETBITS(SOCP_REG_ENCSRC_RDQCFG(srcChanId), 16, 16, 0);
    }

    /*????????????*/
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(srcChanId), 1, 2, pSrcAttr->eMode);
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(srcChanId), 4, 4, pSrcAttr->u32DestChanID);
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(srcChanId), 8, 2, pSrcAttr->ePriority);
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(srcChanId), 10, 1, pSrcAttr->u32BypassEn);
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(srcChanId), 11, 1, pSrcAttr->eDataTypeEn);
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(srcChanId), 31, 1, pSrcAttr->eDebugEn);
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(srcChanId), 16, 8, pSrcAttr->eDataType);

    /* ??g_strSocpStat??????????*/
    pChan = &g_strSocpStat.sEncSrcChan[srcChanId];
    pChan->eChnMode               = pSrcAttr->eMode;
    pChan->ePriority              = pSrcAttr->ePriority;
    pChan->eDataType              = pSrcAttr->eDataType;
    pChan->eDataTypeEn            = pSrcAttr->eDataTypeEn;
    pChan->eDebugEn               = pSrcAttr->eDebugEn;
    pChan->u32DestChanID          = pSrcAttr->u32DestChanID;
    pChan->u32BypassEn            = pSrcAttr->u32BypassEn;
    pChan->sEncSrcBuf.u32Start    = start;
    pChan->sEncSrcBuf.u32End      = end;
    pChan->sEncSrcBuf.u32Write    = start;
    pChan->sEncSrcBuf.u32Read     = start;
    pChan->sEncSrcBuf.u32Length   = buflength;
    pChan->sEncSrcBuf.u32IdleSize = 0;

    if(SOCP_ENCSRC_CHNMODE_LIST == pSrcAttr->eMode)
    {
        pChan->sRdBuf.u32Start    = rdstart;
        pChan->sRdBuf.u32End      = rdend;
        pChan->sRdBuf.u32Write    = rdstart;
        pChan->sRdBuf.u32Read     = rdstart;
        pChan->sRdBuf.u32Length   = Rdbuflength;
        pChan->u32RdThreshold     = pSrcAttr->sCoderSetSrcBuf.u32RDThreshold;
    }

    /* ???????????? */
    g_strSocpStat.sEncSrcChan[srcChanId].u32AllocStat = SOCP_CHN_ALLOCATED;
    g_stSocpDebugInfo.sSocpDebugGBl.u32SocpAllocEncSrcSucCnt++;
    return BSP_OK;

}

/*****************************************************************************
* ?? ?? ??  : bsp_socp_decoder_set_dest_chan
*
* ????????  : ??????????????????????????
*
* ????????  : pAttr           ????????????????????
*             pDestChanID     ??????????????????ID??????????????????ID??????????
                              SrcID = DestChanID%4
*
* ????????  :
*
* ?? ?? ??  : ??????????????????????????
*****************************************************************************/

s32 bsp_socp_decoder_set_dest_chan(SOCP_DECODER_DST_ENUM_U32 enDestChanID,
                                                SOCP_DECODER_DEST_CHAN_STRU *pAttr)
{
    u32 start;
    u32 end;
    u32 bufThreshold;
    u32 buflength;
    u32 u32ChanID;
    u32 u32SrcChanID;
    u32 u32ChanType;
    SOCP_DECDST_CHAN_S *pChan;

    g_stSocpDebugInfo.sSocpDebugGBl.u32SocpAllocDecDstCnt++;

    /* ?????????????????? */
    SOCP_CHECK_INIT();

    /* ?????????????? */
    SOCP_CHECK_PARA(pAttr);
    SOCP_CHECK_DATA_TYPE(pAttr->eDataType);

    u32ChanID    = SOCP_REAL_CHAN_ID(enDestChanID);
    u32ChanType  = SOCP_REAL_CHAN_TYPE(enDestChanID);
    SOCP_CHECK_CHAN_TYPE(u32ChanType, SOCP_DECODER_DEST_CHAN);
    SOCP_CHECK_CHAN_ID(u32ChanID, SOCP_MAX_DECDST_CHN);

    u32SrcChanID = SOCP_REAL_CHAN_ID(pAttr->u32SrcChanID);
    u32ChanType = SOCP_REAL_CHAN_TYPE(pAttr->u32SrcChanID);
    SOCP_CHECK_CHAN_TYPE(u32ChanType, SOCP_DECODER_SRC_CHAN);
    SOCP_CHECK_CHAN_ID(u32SrcChanID, SOCP_MAX_DECSRC_CHN);

    /* ????????ID???????? */
    if(u32SrcChanID != u32ChanID%4)
    {
        socp_printf("bsp_socp_decoder_set_dest_chan: dest ID(%d) is not matching src ID(%d)!\n", u32ChanID, u32SrcChanID);
        return BSP_ERR_SOCP_INVALID_PARA;
    }

    /* ????????????????????????????????????*/
    start           = (uintptr_t)pAttr->sDecoderDstSetBuf.pucOutputStart;
    end             = (uintptr_t)pAttr->sDecoderDstSetBuf.pucOutputEnd;
    bufThreshold    = pAttr->sDecoderDstSetBuf.u32Threshold;
    SOCP_CHECK_PARA(start);
    SOCP_CHECK_8BYTESALIGN(start);
    SOCP_CHECK_PARA(end);
    SOCP_CHECK_BUF_ADDR(start, end);
    SOCP_CHECK_PARA(bufThreshold);
    if (bufThreshold > SOCP_DEC_DST_TH_MAX)
    {
        socp_printf("bsp_socp_decoder_set_dest_chan: buffer threshold is too large!\n");
        return BSP_ERR_SOCP_INVALID_PARA;
    }

    buflength = end - start + 1;
    SOCP_CHECK_8BYTESALIGN(buflength);
    if (buflength > SOCP_DEC_DST_BUFLGTH_MAX)
    {
        socp_printf("bsp_socp_decoder_set_dest_chan: buffer length is too large!\n");
        return BSP_ERR_SOCP_INVALID_PARA;
    }

    /* ????????????????buffer??????????????*/
    SOCP_REG_SETBITS(SOCP_REG_DECDEST_BUFCFG(u32ChanID), 24, 8, pAttr->eDataType);
    SOCP_REG_WRITE(SOCP_REG_DECDEST_BUFRPTR(u32ChanID), SOCP_VIRT_PHY(start));
    SOCP_REG_WRITE(SOCP_REG_DECDEST_BUFADDR(u32ChanID), SOCP_VIRT_PHY(start));
    SOCP_REG_WRITE(SOCP_REG_DECDEST_BUFWPTR(u32ChanID), SOCP_VIRT_PHY(start));
    SOCP_REG_SETBITS(SOCP_REG_DECDEST_BUFCFG(u32ChanID), 0, 16, buflength);
    SOCP_REG_SETBITS(SOCP_REG_DECDEST_BUFCFG(u32ChanID), 16, 8, bufThreshold);

    pChan = &g_strSocpStat.sDecDstChan[u32ChanID];
    pChan->eDataType = pAttr->eDataType;
    pChan->sDecDstBuf.u32Start    = start;
    pChan->sDecDstBuf.u32End      = end;
    pChan->sDecDstBuf.u32Length   = buflength;
    pChan->sDecDstBuf.u32Read     = start;
    pChan->sDecDstBuf.u32Write    = start;

    /* ????????????????????*/
    SOCP_REG_SETBITS(SOCP_REG_DEC_RAWINT0, u32ChanID, 1, 1);
    SOCP_REG_SETBITS(SOCP_REG_DEC_CORE0MASK0, u32ChanID, 1, 0);
    SOCP_REG_SETBITS(SOCP_REG_DEC_RAWINT2, u32ChanID, 1, 1);
    SOCP_REG_SETBITS(SOCP_REG_DEC_CORE0MASK2, u32ChanID, 1, 0);

    /* ???????????????? */
    g_strSocpStat.sDecDstChan[u32ChanID].u32AllocStat = SOCP_CHN_ALLOCATED;
    g_stSocpDebugInfo.sSocpDebugGBl.u32SocpAllocDecDstSucCnt++;

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : bsp_socp_coder_set_dest_chan_attr
*
* ????????  : ????????????????????
*
* ????????  : u32DestChanID      ????????????ID
              pDestAttr          ????????????????????
*
* ????????  : ??
* ?? ?? ??  : ????????????????????
*****************************************************************************/

s32 bsp_socp_coder_set_dest_chan_attr(u32 u32DestChanID, SOCP_CODER_DEST_CHAN_S *pDestAttr)
{
    u32 start;
    u32 end;
    u32 bufThreshold;
    u32 buflength;
    u32 u32ChanID;
    u32 u32ChanType;
    u32 u32Thrh;
    SOCP_ENCDST_CHAN_S *pChan;

    g_stSocpDebugInfo.sSocpDebugGBl.u32SocpSetEncDstCnt++;

    /* ?????????????????? */
    SOCP_CHECK_INIT();

    /* ?????????????? */
    SOCP_CHECK_PARA(pDestAttr);
    u32ChanID   = SOCP_REAL_CHAN_ID(u32DestChanID);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32DestChanID);
    SOCP_CHECK_CHAN_TYPE(u32ChanType, SOCP_CODER_DEST_CHAN);
    SOCP_CHECK_CHAN_ID(u32ChanID, SOCP_MAX_ENCDST_CHN);

    start = (uintptr_t)pDestAttr->sCoderSetDstBuf.pucOutputStart;
    end   = (uintptr_t)pDestAttr->sCoderSetDstBuf.pucOutputEnd;
    bufThreshold = pDestAttr->sCoderSetDstBuf.u32Threshold;
    u32Thrh = pDestAttr->u32EncDstThrh;

    SOCP_CHECK_PARA(start);
    SOCP_CHECK_8BYTESALIGN(start);
    SOCP_CHECK_PARA(end);
    SOCP_CHECK_BUF_ADDR(start, end);
    SOCP_CHECK_PARA(bufThreshold);
    buflength = end - start + 1;
    SOCP_CHECK_8BYTESALIGN(buflength);
    if(socp_version < SOCP_NEW_VERSION)
    {
        if (buflength > SOCP_ENC_DST_BUFLGTH_MAX)
        {
            socp_printf("CoderSetDestChanAttr: buffer length is too large!\n");
            return BSP_ERR_SOCP_INVALID_PARA;
        }

        if (bufThreshold > SOCP_ENC_DST_TH_MAX)
        {
            socp_printf("CoderSetDestChanAttr: buffer threshold is too large!\n");
            return BSP_ERR_SOCP_INVALID_PARA;
        }
    }
    /* ??????????????????????????,?????????????????????? */
    /* ???????????????????? */
    pChan = &g_strSocpStat.sEncDstChan[u32ChanID];
    if (!pChan->u32SetStat)
    {
        /* ??????????????????buffer??????????????*/
        SOCP_REG_WRITE(SOCP_REG_ENCDEST_BUFADDR(u32ChanID),SOCP_VIRT_PHY(start));
        SOCP_REG_WRITE(SOCP_REG_ENCDEST_BUFRPTR(u32ChanID),SOCP_VIRT_PHY(start));
 	    SOCP_REG_WRITE(SOCP_REG_ENCDEST_BUFWPTR(u32ChanID), SOCP_VIRT_PHY(start));

        if(socp_version >= SOCP_NEW_VERSION)
        {
            SOCP_REG_WRITE(SOCP_REG_ENCDEST_BUFCFG(u32ChanID),buflength);
            SOCP_REG_WRITE(SOCP_REG_ENCDEST_BUFTHRESHOLD(u32ChanID),(bufThreshold*1024));
        }
        else
        {
            SOCP_REG_SETBITS(SOCP_REG_ENCDEST_BUFCFG(u32ChanID), 0, 21, buflength);
            SOCP_REG_SETBITS(SOCP_REG_ENCDEST_BUFCFG(u32ChanID), 21, 11, bufThreshold);
        }

        SOCP_REG_SETBITS(SOCP_REG_ENCDEST_BUFTHRH(u32ChanID), 0, 31, u32Thrh);

        /* ??g_strSocpStat??????????*/
        pChan->u32ChanID              = u32ChanID;
        pChan->u32Thrh = u32Thrh;
        pChan->sEncDstBuf.u32Start    = start;
        pChan->sEncDstBuf.u32End      = end;
        pChan->sEncDstBuf.u32Write    = start;
        pChan->sEncDstBuf.u32Read     = start;
        pChan->sEncDstBuf.u32Length   = buflength;

        /* ?????????????????? */
        pChan->u32SetStat = SOCP_CHN_SET;

        /* ???????????????????? */
        SOCP_REG_SETBITS(SOCP_REG_ENC_RAWINT0, u32ChanID, 1, 1);
        SOCP_REG_SETBITS(SOCP_REG_ENC_MASK0, u32ChanID, 1, 0);
        SOCP_REG_SETBITS(SOCP_REG_ENC_RAWINT2, u32ChanID, 1, 1);
        SOCP_REG_SETBITS(SOCP_REG_ENC_MASK2, u32ChanID, 1, 0);
        // ????????buffer????????
        SOCP_REG_SETBITS(SOCP_REG_ENC_RAWINT2, u32ChanID+16, 1, 1);
        SOCP_REG_SETBITS(SOCP_REG_ENC_MASK2, u32ChanID+16, 1, 0);
    }
    else
    {
        socp_printf("CoderSetDestChanAttr: channel 0x%x can't be set twice!\n", u32ChanID);
        return BSP_ERR_SOCP_SET_FAIL;
    }

    g_stSocpDebugInfo.sSocpDebugGBl.u32SocpSetEncDstSucCnt++;

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : bsp_socp_decoder_set_src_chan_attr
*
* ????????  : ??????????????????
*
* ????????  : u32SrcChanID    ??????????ID
*             pInputAttr      ??????????????????
*
* ????????  :
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/
s32 bsp_socp_decoder_set_src_chan_attr(u32 u32SrcChanID, SOCP_DECODER_SRC_CHAN_STRU *pInputAttr)
{
    u32 start;
    u32 end;
    u32 buflength = 0;
    u32 u32ChanID;
    u32 u32ChanType;
    u32 i;
    u32 u32ResetFlag;
    SOCP_DECSRC_CHAN_S *pDecSrcChan;

    g_stSocpDebugInfo.sSocpDebugGBl.u32SocpSetDecSrcCnt++;

    /* ?????????????????? */
    SOCP_CHECK_INIT();

    /* ?????????????? */
    SOCP_CHECK_PARA(pInputAttr);
    u32ChanID   = SOCP_REAL_CHAN_ID(u32SrcChanID);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32SrcChanID);
    SOCP_CHECK_CHAN_TYPE(u32ChanType, SOCP_DECODER_SRC_CHAN);
    SOCP_CHECK_CHAN_ID(u32ChanID, SOCP_MAX_DECSRC_CHN);
    SOCP_CHECK_DATA_TYPE_EN(pInputAttr->eDataTypeEn);

    start     = (uintptr_t)pInputAttr->sDecoderSetSrcBuf.pucInputStart;
    end       = (uintptr_t)pInputAttr->sDecoderSetSrcBuf.pucInputEnd;
    SOCP_CHECK_PARA(start);
    SOCP_CHECK_8BYTESALIGN(start);
    SOCP_CHECK_PARA(end);
    SOCP_CHECK_BUF_ADDR(start, end);
    buflength = end - start + 1;
    SOCP_CHECK_8BYTESALIGN(buflength);
    if (buflength > SOCP_DEC_SRC_BUFLGTH_MAX)
    {
        socp_printf("DecoderSetSrcChanAttr: buffer length is too large!\n");
        return BSP_ERR_SOCP_INVALID_PARA;
    }

    pDecSrcChan = &g_strSocpStat.sDecSrcChan[u32ChanID];
    if (SOCP_CHN_SET == pDecSrcChan->u32SetStat)
    {
        socp_printf("DecoderSetSrcChanAttr: channel 0x%x has been configed!\n", u32ChanID);
        return BSP_ERR_SOCP_DECSRC_SET;
    }

    /* ???????????? */
    SOCP_REG_SETBITS(SOCP_REG_DECRST, u32ChanID, 1, 1);

    /* ???????????????????? */
    for (i = 0; i < SOCP_RESET_TIME; i++)
    {
        u32ResetFlag = SOCP_REG_GETBITS(SOCP_REG_DECRST, u32ChanID, 1);
        if (0 == u32ResetFlag)
        {
            break;
        }

        if ((SOCP_RESET_TIME - 1) == i)
        {
            socp_printf("DecoderSetSrcChanAttr: reset channel 0x%x failed!\n", u32ChanID);
        }
    }

    /* ???????????????????? */
    SOCP_REG_WRITE(SOCP_REG_DECSRC_BUFWPTR(u32ChanID),SOCP_VIRT_PHY(start));
    SOCP_REG_WRITE(SOCP_REG_DECSRC_BUFADDR(u32ChanID),SOCP_VIRT_PHY(start));
    SOCP_REG_WRITE(SOCP_REG_DECSRC_BUFRPTR(u32ChanID), SOCP_VIRT_PHY(start));
    SOCP_REG_SETBITS(SOCP_REG_DECSRC_BUFCFG0(u32ChanID), 0, 16, buflength);
    SOCP_REG_SETBITS(SOCP_REG_DECSRC_BUFCFG0(u32ChanID), 31, 1, pInputAttr->eDataTypeEn);
    //SOCP_REG_SETBITS(SOCP_REG_DECSRC_RDQCFG(u32ChanID), 29, 1, 0);

    /* ?????????????????????????? */
    pDecSrcChan->u32ChanID              = u32ChanID;
    pDecSrcChan->eDataTypeEn= pInputAttr->eDataTypeEn;
    pDecSrcChan->sDecSrcBuf.u32Start    = start;
    pDecSrcChan->sDecSrcBuf.u32End      = end;
    pDecSrcChan->sDecSrcBuf.u32Length   = buflength;
    pDecSrcChan->sDecSrcBuf.u32Read     = start;
    pDecSrcChan->sDecSrcBuf.u32Write    = start;

    pDecSrcChan->u32SetStat = SOCP_CHN_SET;

    g_stSocpDebugInfo.sSocpDebugGBl.u32SocpSetDeSrcSucCnt++;

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : bsp_socp_decoder_get_err_cnt
*
* ????????  : ??????????????????????????
*
* ????????  : u32ChanID       ????????ID

* ????????  : pErrCnt         ??????????????????????????
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/
s32 bsp_socp_decoder_get_err_cnt(u32 u32DstChanID, SOCP_DECODER_ERROR_CNT_STRU *pErrCnt)
{
    u32 u32ChanID;
    u32 u32ChanType;

    /* ?????????????????? */
    SOCP_CHECK_INIT();

    /* ????????ID???????? */
    u32ChanID   = SOCP_REAL_CHAN_ID(u32DstChanID);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32DstChanID);
    SOCP_CHECK_CHAN_TYPE(u32ChanType, SOCP_DECODER_SRC_CHAN);
    SOCP_CHECK_CHAN_ID(u32ChanID, SOCP_MAX_DECSRC_CHN);
    SOCP_CHECK_DECSRC_SET(u32ChanID);

    /* ?????????????? */
    SOCP_CHECK_PARA(pErrCnt);

    /* ??????????????????????????debug????*/
    if (g_strSocpStat.sDecSrcChan[u32ChanID].u32ChanEn)
    {
        pErrCnt->u32PktlengthCnt = SOCP_REG_GETBITS(SOCP_REG_DEC_BUFSTAT0(u32ChanID), 16, 16);
        pErrCnt->u32CrcCnt = SOCP_REG_GETBITS(SOCP_REG_DEC_BUFSTAT0(u32ChanID), 0, 16);
        pErrCnt->u32DataTypeCnt   = SOCP_REG_GETBITS(SOCP_REG_DEC_BUFSTAT1(u32ChanID), 16, 16);
        pErrCnt->u32HdlcHeaderCnt = SOCP_REG_GETBITS(SOCP_REG_DEC_BUFSTAT1(u32ChanID), 0, 16);
    }
    else
    {
        socp_printf("DecoderGetErrCnt: debug mode is closed!\n");
        return BSP_ERR_SOCP_SET_FAIL;
    }

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : bsp_socp_set_timeout
*
* ????????  : ????????????????
*
* ????????  :   eTmOutEn          ??????????????????
                u32Timeout        ????????
*
* ????????  :
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/
s32 bsp_socp_set_timeout (SOCP_TIMEOUT_EN_ENUM_UIN32 eTmOutEn, u32 u32Timeout)
{
    /* ?????????????????? */
    SOCP_CHECK_INIT();

    (void)bsp_socp_vote(SOCP_VOTE_SOCP_REG,SOCP_VOTE_FOR_WAKE);

    switch (eTmOutEn)
    {
        case SOCP_TIMEOUT_BUFOVF_DISABLE:
        {
            SOCP_REG_SETBITS(SOCP_REG_BUFTIMEOUT, 31, 1, 0);
            break;
        }
        case SOCP_TIMEOUT_BUFOVF_ENABLE:
        {
            SOCP_REG_SETBITS(SOCP_REG_BUFTIMEOUT, 31, 1, 1);
            /* ?????????????? */
            SOCP_REG_SETBITS(SOCP_REG_BUFTIMEOUT, 0, 16, u32Timeout);
            break;
        }
        case SOCP_TIMEOUT_TRF:
        {
            printk(KERN_ERR"bsp_socp_set_timeout 0x%x.\n", u32Timeout);

			SOCP_REG_WRITE(SOCP_REG_INTTIMEOUT, u32Timeout);
            break;
        }
        /*2014??2??22??15:13:46 l00258701 modify begin*/
        /*2014??2??22??15:13:46 l00258701 modify end*/
        default:
        {
            socp_printf("SetTimeout: invalid timeout choice type!\n");
            (void)bsp_socp_vote(SOCP_VOTE_SOCP_REG,SOCP_VOTE_FOR_SLEEP);
            return BSP_ERR_SOCP_SET_FAIL;
        }
    }

    (void)bsp_socp_vote(SOCP_VOTE_SOCP_REG,SOCP_VOTE_FOR_SLEEP);

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : bsp_socp_set_dec_pkt_lgth
*
* ????????  : ????????????????
*
* ????????  :   pPktlgth          ????????????????????????
*
* ????????  :
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/
s32 bsp_socp_set_dec_pkt_lgth(SOCP_DEC_PKTLGTH_STRU *pPktlgth)
{
    u32 u32PktMaxLgth;
    u32 u32PktMinLgth;

    /* ?????????????????? */
    SOCP_CHECK_INIT();

    /* ?????????????? */
    SOCP_CHECK_PARA(pPktlgth);
    u32PktMaxLgth = pPktlgth->u32PktMax;
    u32PktMinLgth = pPktlgth->u32PktMin;

    SOCP_CHECK_PARA(u32PktMaxLgth);
    if (u32PktMaxLgth*1024 > SOCP_DEC_MAXPKT_MAX)
    {
        socp_printf("SetDecPktLgth: u32PktMaxLgth 0x%x is too large!\n", u32PktMaxLgth);
        return BSP_ERR_SOCP_INVALID_PARA;
    }

    if (u32PktMinLgth > SOCP_DEC_MINPKT_MAX)
    {
        socp_printf("SetDecPktLgth: u32PktMinLgth 0x%x is too large!\n", u32PktMinLgth);
        return BSP_ERR_SOCP_INVALID_PARA;
    }

    /* ????????????????????????????*/
    SOCP_REG_SETBITS(SOCP_REG_DEC_PKTLEN, 0, 12, u32PktMaxLgth);
    SOCP_REG_SETBITS(SOCP_REG_DEC_PKTLEN, 12, 5, u32PktMinLgth);

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : bsp_socp_set_debug
*
* ????????  : ??????????????debug????????
*
* ????????  : u32DecChanID  ??????????ID
              u32DebugEn    debug????????????
*
* ????????  :
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/
s32 bsp_socp_set_debug(u32 u32DecChanID, u32 u32DebugEn)
{
    u32 u32ChanID;
    u32 u32ChanType;

    /* ?????????????????? */
    SOCP_CHECK_INIT();

    /* ????????ID???????? */
    u32ChanID = SOCP_REAL_CHAN_ID(u32DecChanID);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32DecChanID);
    SOCP_CHECK_CHAN_TYPE(u32ChanType, SOCP_DECODER_SRC_CHAN);
    SOCP_CHECK_CHAN_ID(u32ChanID, SOCP_MAX_DECSRC_CHN);
    SOCP_CHECK_DECSRC_SET(u32ChanID);

    /* ?????????????????????????????????????????? */
    if(g_strSocpStat.sDecSrcChan[u32ChanID].u32ChanEn)
    {
        socp_printf("SetDebug: decoder channel is open, can't set debug bit\n");
        return BSP_ERR_SOCP_SET_FAIL;
    }
    else
    {
        SOCP_REG_SETBITS(SOCP_REG_DECSRC_BUFCFG0(u32ChanID), 29, 1, u32DebugEn);
    }

    return BSP_OK;
}


/*****************************************************************************
* ?? ?? ??  : bsp_socp_free_channel
*
* ????????  : ????????????
*
* ????????  : u32ChanID       ??????????????
*
* ????????  : ??
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/
s32 bsp_socp_free_channel(u32 u32ChanID)
{
    u32 u32RealChanID;
    u32 u32ChanType;

    /* ?????????????????? */
    SOCP_CHECK_INIT();

    /* ????????ID???????? */
    u32RealChanID = SOCP_REAL_CHAN_ID(u32ChanID);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32ChanID);

    if (SOCP_CODER_SRC_CHAN == u32ChanType)
    {
        SOCP_ENCSRC_CHAN_S *pChan;

        SOCP_CHECK_ENCSRC_CHAN_ID(u32RealChanID);
        SOCP_CHECK_ENCSRC_ALLOC(u32RealChanID);

        pChan = &g_strSocpStat.sEncSrcChan[u32RealChanID];
        if (SOCP_CHN_ENABLE == pChan->u32ChanEn)
        {
            socp_printf("FreeChannel: chan 0x%x is running!\n", u32ChanID);
            return BSP_ERR_SOCP_CHAN_RUNNING;
        }

        (void)socp_reset_enc_chan(u32RealChanID);

        pChan->u32AllocStat = SOCP_CHN_UNALLOCATED;

        g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpFreeEncSrcCnt[u32RealChanID]++;
    }
    else if (SOCP_DECODER_DEST_CHAN == u32ChanType)
    {
        SOCP_CHECK_CHAN_ID(u32RealChanID, SOCP_MAX_DECDST_CHN);
        SOCP_CHECK_DECDST_ALLOC(u32RealChanID);

        /* ???????????????? */
        SOCP_REG_SETBITS(SOCP_REG_DECDEST_BUFCFG(u32RealChanID), 24, 8, 0xff);

        g_strSocpStat.sDecDstChan[u32RealChanID].u32AllocStat = SOCP_CHN_UNALLOCATED;

        g_stSocpDebugInfo.sSocpDebugDecDst.u32SocpFreeDecDstCnt[u32RealChanID]++;
    }
    else
    {
        socp_printf("FreeChannel: invalid chan type 0x%x!\n", u32ChanType);
        return BSP_ERR_SOCP_INVALID_CHAN;
    }

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : bsp_socp_chan_soft_reset
*
* ????????  : ??????????????
*
* ????????  : u32ChanID       ??????????ID
*
* ????????  : ??
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/
s32 bsp_socp_chan_soft_reset(u32 u32ChanID)
{
    u32 u32RealChanID;
    u32 u32ChanType;

    /* ?????????????????? */
    SOCP_CHECK_INIT();

    /* ????????ID???????? */
    u32RealChanID = SOCP_REAL_CHAN_ID(u32ChanID);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32ChanID);
    /* ????????????????????????????????LTE DSP/BBP???? */
    /* ???????????????????????????????????????????????????? */
    if (SOCP_CODER_SRC_CHAN == u32ChanType)
    {
        SOCP_CHECK_ENCSRC_CHAN_ID(u32RealChanID);
        SOCP_CHECK_ENCSRC_ALLOC(u32RealChanID);
        (void)socp_reset_enc_chan(u32ChanID);
        g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpSoftResetEncSrcCnt[u32RealChanID]++;
    }
    else if (SOCP_DECODER_SRC_CHAN == u32ChanType)
    {
        SOCP_CHECK_CHAN_ID(u32RealChanID, SOCP_MAX_DECSRC_CHN);
        SOCP_CHECK_DECSRC_SET(u32RealChanID);

        (void)socp_reset_dec_chan(u32RealChanID);

        g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpSoftResetDecSrcCnt[u32RealChanID]++;
    }
    else
    {
        socp_printf("ChnSoftReset: invalid chan type: 0x%x!\n", u32ChanType);
        return BSP_ERR_SOCP_INVALID_CHAN;
    }

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : bsp_socp_start
*
* ????????  : ????????????????????
*
* ????????  : u32SrcChanID      ????ID
* ????????  :
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/
/*lint -save -e529*/
s32 bsp_socp_start(u32 u32SrcChanID)
{
    u32 u32RealChanID;
    u32 u32ChanType;
    u32 u32Logic = (u32)1;
    u32 u32DstId;
    u32 i;
    u32 IntIDMask = 0;


    /* ?????????????????? */
    SOCP_CHECK_INIT();

    /* ????????ID???????? */
    u32RealChanID = SOCP_REAL_CHAN_ID(u32SrcChanID);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32SrcChanID);

    /* ???????? */
    if (SOCP_CODER_SRC_CHAN == u32ChanType)
    {
        if (u32RealChanID < SOCP_MAX_ENCSRC_CHN)
        {
            SOCP_CHECK_ENCSRC_CHAN_ID(u32RealChanID);
            SOCP_CHECK_ENCSRC_ALLOC(u32RealChanID);
        }
        else
        {
            socp_printf("Start: enc src 0x%x is valid!\n", u32SrcChanID);
            return BSP_ERR_SOCP_INVALID_CHAN;
        }

        u32DstId = SOCP_REG_GETBITS(SOCP_REG_ENCSRC_BUFCFG1(u32RealChanID), 4, 4);
        if (SOCP_CHN_SET != g_strSocpStat.sEncDstChan[u32DstId].u32SetStat)
        {
            socp_printf("AppStart: enc dst chan is valid!\n");
            return BSP_ERR_SOCP_DEST_CHAN;
        }

        /* ????????????????????*/
        SOCP_REG_SETBITS(SOCP_REG_ENC_RAWINT1, u32RealChanID, 1, 1);
        SOCP_REG_SETBITS(SOCP_REG_APP_MASK1, u32RealChanID, 1, 0);
        if (SOCP_ENCSRC_CHNMODE_LIST == g_strSocpStat.sEncSrcChan[u32RealChanID].eChnMode)
        {
            SOCP_REG_SETBITS(SOCP_REG_ENC_RAWINT3, u32RealChanID, 1, 1);
            /* ????RD???????? */
            //SOCP_REG_SETBITS(SOCP_REG_APP_MASK3, u32RealChanID, 1, 0);
        }

        /* ????????????*/
        SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(u32RealChanID), 0, 1, 1);
        if(u32RealChanID < SOCP_MAX_ENCSRC_CHN)
        {
            g_strSocpStat.sEncSrcChan[u32RealChanID].u32ChanEn = SOCP_CHN_ENABLE;
            g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpStartEncSrcCnt[u32RealChanID]++;
        }
    }
    else if (SOCP_DECODER_SRC_CHAN == u32ChanType)
    {
        SOCP_CHECK_CHAN_ID(u32RealChanID, SOCP_MAX_DECSRC_CHN);
        SOCP_CHECK_DECSRC_SET(u32RealChanID);

        /* ????rd????????*/
        if (SOCP_DECSRC_CHNMODE_LIST == g_strSocpStat.sDecSrcChan[u32RealChanID].eChnMode)
        {
            SOCP_REG_SETBITS(SOCP_REG_DEC_RAWINT1, u32RealChanID, 1, 1);
            SOCP_REG_SETBITS(SOCP_REG_DEC_MASK1, u32RealChanID, 1, 0);
        }

        for (i = 1; i < SOCP_DEC_SRCINT_NUM; i++)
        {
            IntIDMask  = SOCP_REG_GETBITS(SOCP_REG_DEC_RAWINT1, i * 4, 4);
            IntIDMask |= 1 << u32RealChanID;
            SOCP_REG_SETBITS(SOCP_REG_DEC_RAWINT1, i * 4, 4, IntIDMask);

            IntIDMask  = SOCP_REG_GETBITS(SOCP_REG_DEC_MASK1, i * 4, 4);
            IntIDMask &= ~(u32Logic << u32RealChanID);
            SOCP_REG_SETBITS(SOCP_REG_DEC_MASK1, i * 4, 4, IntIDMask);
        }

        /* ????????????*/
        SOCP_REG_SETBITS(SOCP_REG_DECSRC_BUFCFG0(u32RealChanID), 30, 1, 1);
        g_strSocpStat.sDecSrcChan[u32RealChanID].u32ChanEn = SOCP_CHN_ENABLE;

        g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpStartDecSrcCnt[u32RealChanID]++;
    }
    else
    {
        socp_printf("Start: invalid chan type: 0x%x!\n", u32ChanType);
        return BSP_ERR_SOCP_INVALID_CHAN;
    }

    return BSP_OK;
}

/*lint -restore +e529*/

/*****************************************************************************
* ?? ?? ??  : bsp_socp_stop
*
* ????????  : ????????????????????
*
* ????????  : u32SrcChanID      ????ID
*
* ????????  :
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/
/*lint -save -e529*/
s32 bsp_socp_stop(u32 u32SrcChanID)
{
    u32 u32RealChanID;
    u32 u32ChanType;
    u32 IntIDMask = 0;
    u32 i;


    /* ?????????????????? */
    SOCP_CHECK_INIT();

    /* ????????ID???????? */
    u32RealChanID = SOCP_REAL_CHAN_ID(u32SrcChanID);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32SrcChanID);

    /* ???????? */
    if (SOCP_CODER_SRC_CHAN == u32ChanType)
    {
        if (u32RealChanID < SOCP_MAX_ENCSRC_CHN)
        {
            SOCP_CHECK_ENCSRC_CHAN_ID(u32RealChanID);
            SOCP_CHECK_ENCSRC_ALLOC(u32RealChanID);
        }
        else
        {
            socp_printf("Stop: enc src 0x%x is valid!\n", u32SrcChanID);
            return BSP_ERR_SOCP_INVALID_CHAN;
        }

        SOCP_REG_SETBITS(SOCP_REG_APP_MASK1, u32RealChanID, 1, 1);
        if (SOCP_ENCSRC_CHNMODE_LIST == g_strSocpStat.sEncSrcChan[u32RealChanID].eChnMode)
        {
            SOCP_REG_SETBITS(SOCP_REG_APP_MASK3, u32RealChanID, 1, 1);
        }

        /* ????????????????*/
        SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(u32RealChanID), 0, 1, 0);
        if (u32RealChanID < SOCP_MAX_ENCSRC_CHN)
        {
            g_strSocpStat.sEncSrcChan[u32RealChanID].u32ChanEn = SOCP_CHN_DISABLE;
            g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpStopEncSrcCnt[u32RealChanID]++;
        }
    }
    else if (SOCP_DECODER_SRC_CHAN == u32ChanType)
    {
        SOCP_CHECK_CHAN_ID(u32RealChanID, SOCP_MAX_DECSRC_CHN);
        SOCP_CHECK_DECSRC_SET(u32RealChanID);

        /* ????????*/
        if (SOCP_DECSRC_CHNMODE_LIST == g_strSocpStat.sDecSrcChan[u32RealChanID].eChnMode)
        {
            SOCP_REG_SETBITS(SOCP_REG_DEC_CORE0MASK0, u32RealChanID, 1, 1);
        }

        for (i = 1; i < SOCP_DEC_SRCINT_NUM; i++)
        {
            IntIDMask  = SOCP_REG_GETBITS(SOCP_REG_DEC_MASK1, i * 4, 4);
            IntIDMask |= 1 << u32RealChanID;
            SOCP_REG_SETBITS(SOCP_REG_DEC_CORE0MASK0, i * 4, 4, IntIDMask);
        }

        /* ????????????????*/
        SOCP_REG_SETBITS(SOCP_REG_DECSRC_BUFCFG0(u32RealChanID), 30, 1,0);
        g_strSocpStat.sDecSrcChan[u32RealChanID].u32ChanEn = SOCP_CHN_DISABLE;

        g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpStopDecSrcCnt[u32RealChanID]++;
    }
    else
    {
        socp_printf("Stop: invalid chan type: 0x%x!\n", u32ChanType);
        return BSP_ERR_SOCP_INVALID_CHAN;
    }

    return BSP_OK;
}

/*lint -restore +e529*/
/*****************************************************************************
* ?? ?? ??  : bsp_socp_register_event_cb
*
* ????????  : ????????????????????????
*
* ????????  : u32ChanID      ????ID
*             EventCB        ??????????????????
* ????????  :
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/
s32 bsp_socp_register_event_cb(u32 u32ChanID, socp_event_cb EventCB)
{
    u32  u32RealChanID;
    u32  u32ChanType;

    /* ?????????????????? */
    SOCP_CHECK_INIT();

    /* ????????????????????????ID */
    u32RealChanID = SOCP_REAL_CHAN_ID(u32ChanID);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32ChanID);

    switch (u32ChanType)
    {
        case SOCP_CODER_SRC_CHAN:      /* ?????????? */
        {
            if (u32RealChanID < SOCP_MAX_ENCSRC_CHN)
            {
                SOCP_CHECK_ENCSRC_CHAN_ID(u32RealChanID);
                SOCP_CHECK_ENCSRC_ALLOC(u32RealChanID);
                g_strSocpStat.sEncSrcChan[u32RealChanID].event_cb = EventCB;

                g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpRegEventEncSrcCnt[u32RealChanID]++;
            }
            break;
        }
        case SOCP_CODER_DEST_CHAN:       /* ????????????*/
        {
            SOCP_CHECK_CHAN_ID(u32RealChanID, SOCP_MAX_ENCDST_CHN);
            SOCP_CHECK_ENCDST_SET(u32RealChanID);

            g_strSocpStat.sEncDstChan[u32RealChanID].event_cb = EventCB;

            g_stSocpDebugInfo.sSocpDebugEncDst.u32SocpRegEventEncDstCnt[u32RealChanID]++;
            break;
        }
        case SOCP_DECODER_SRC_CHAN:       /* ??????????*/
        {
            SOCP_CHECK_CHAN_ID(u32RealChanID, SOCP_MAX_DECSRC_CHN);
            SOCP_CHECK_DECSRC_SET(u32RealChanID);

            g_strSocpStat.sDecSrcChan[u32RealChanID].event_cb = EventCB;

            g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpRegEventDecSrcCnt[u32RealChanID]++;
            break;
        }
        case SOCP_DECODER_DEST_CHAN:       /* ????????????*/
        {
            SOCP_CHECK_CHAN_ID(u32RealChanID, SOCP_MAX_DECDST_CHN);
            SOCP_CHECK_DECDST_ALLOC(u32RealChanID);

            g_strSocpStat.sDecDstChan[u32RealChanID].event_cb = EventCB;

            g_stSocpDebugInfo.sSocpDebugDecDst.u32SocpRegEventDecDstCnt[u32RealChanID]++;
            break;
        }
        default:
        {
            socp_printf("RegisterEventCB: invalid chan type: 0x%x!\n", u32ChanType);
            return BSP_ERR_SOCP_INVALID_CHAN;
        }
    }

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : bsp_socp_get_write_buff
*
* ????????  : ??????????????buffer????
*
* ????????  : u32SrcChanID    ??????ID
* ????????  : pBuff           ??????buffer
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/
s32 bsp_socp_get_write_buff(u32 u32SrcChanID, SOCP_BUFFER_RW_STRU *pBuff)
{
    u32 u32ChanID;
    u32 u32ChanType;
    u32 uPAddr;

    /* ?????????????????? */
    SOCP_CHECK_INIT();

    /* ?????????????? */
    SOCP_CHECK_PARA(pBuff);

    /* ????????????id */
    u32ChanID   = SOCP_REAL_CHAN_ID(u32SrcChanID);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32SrcChanID);

    /* ???????? */
    if (SOCP_CODER_SRC_CHAN == u32ChanType)
    {
        g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpGetWBufEncSrcEtrCnt[u32ChanID]++;

        /* ????????id */
        SOCP_CHECK_ENCSRC_CHAN_ID(u32ChanID);
        SOCP_CHECK_ENCSRC_ALLOC(u32ChanID);

        /* ????????????????buffer */
        SOCP_REG_READ(SOCP_REG_ENCSRC_BUFRPTR(u32ChanID), uPAddr);
        g_strSocpStat.sEncSrcChan[u32ChanID].sEncSrcBuf.u32Read = SOCP_PHY_VIRT(uPAddr);
        SOCP_REG_READ(SOCP_REG_ENCSRC_BUFWPTR(u32ChanID), uPAddr);
        g_strSocpStat.sEncSrcChan[u32ChanID].sEncSrcBuf.u32Write= SOCP_PHY_VIRT(uPAddr);
        socp_get_idle_buffer(&g_strSocpStat.sEncSrcChan[u32ChanID].sEncSrcBuf, pBuff);
        g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpGetWBufEncSrcSucCnt[u32ChanID]++;
    }
    else if (SOCP_DECODER_SRC_CHAN == u32ChanType) /* ???????? */
    {
        g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpGetWBufDecSrcEtrCnt[u32ChanID]++;

        /* ????????id */
        SOCP_CHECK_CHAN_ID(u32ChanID, SOCP_MAX_DECSRC_CHN);
        SOCP_CHECK_DECSRC_SET(u32ChanID);
        SOCP_REG_READ(SOCP_REG_DECSRC_BUFRPTR(u32ChanID), uPAddr);
        g_strSocpStat.sDecSrcChan[u32ChanID].sDecSrcBuf.u32Read = SOCP_PHY_VIRT(uPAddr);
        SOCP_REG_READ(SOCP_REG_DECSRC_BUFWPTR(u32ChanID), uPAddr);
        g_strSocpStat.sDecSrcChan[u32ChanID].sDecSrcBuf.u32Write= SOCP_PHY_VIRT(uPAddr);
        socp_get_idle_buffer(&g_strSocpStat.sDecSrcChan[u32ChanID].sDecSrcBuf, pBuff);
        g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpGetWBufDecSrcSucCnt[u32ChanID]++;
    }
    else
    {
        socp_printf("GetWriteBuff: invalid chan type: 0x%x!\n", u32ChanType);
        return BSP_ERR_SOCP_INVALID_CHAN;
    }

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : bsp_socp_write_done
*
* ????????  : ??????????????
*
* ????????  : u32SrcChanID    ??????ID
              u32WrtSize      ??????????????
*
* ????????  :
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/
s32 bsp_socp_write_done(u32 u32SrcChanID, u32 u32WrtSize)
{
    u32 u32ChanID;
    u32 u32ChanType;
    u32 u32WrtPad;
    SOCP_BUFFER_RW_STRU RwBuff;
    u32  uPAddr;

    /* ?????????????????? */
    SOCP_CHECK_INIT();

    /* ?????????????? */
    SOCP_CHECK_PARA(u32WrtSize);

    /* ????????????id */
    u32ChanID   = SOCP_REAL_CHAN_ID(u32SrcChanID);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32SrcChanID);

    /* ???????? */
    if (SOCP_CODER_SRC_CHAN == u32ChanType)
    {
        SOCP_ENCSRC_CHAN_S *pChan;

        g_stSocpDebugInfo.sSocpDebugEncSrc.u32socp_write_doneEncSrcEtrCnt[u32ChanID]++;

        /* ????????id */
        SOCP_CHECK_ENCSRC_CHAN_ID(u32ChanID);
        SOCP_CHECK_ENCSRC_ALLOC(u32ChanID);

        pChan = &g_strSocpStat.sEncSrcChan[u32ChanID];
        u32WrtPad = u32WrtSize % 8;
        if (0 != u32WrtPad)
        {
            u32WrtSize += (8 - u32WrtPad);
        }

        SOCP_REG_READ(SOCP_REG_ENCSRC_BUFWPTR(u32ChanID), uPAddr);
        pChan->sEncSrcBuf.u32Write= SOCP_PHY_VIRT(uPAddr);
        SOCP_REG_READ(SOCP_REG_ENCSRC_BUFRPTR(u32ChanID), uPAddr);
        pChan->sEncSrcBuf.u32Read =SOCP_PHY_VIRT(uPAddr);

        socp_get_idle_buffer(&pChan->sEncSrcBuf, &RwBuff);

        if (RwBuff.u32Size + RwBuff.u32RbSize < u32WrtSize)
        {
            socp_printf("WriteDone: enc src, too large write size!\n");
            socp_printf("WriteDone: enc src, write ptr is 0x%x, read ptr is 0x%x\n", pChan->sEncSrcBuf.u32Write, pChan->sEncSrcBuf.u32Read);
            socp_printf("WriteDone: enc src, u32Size is 0x%x, u32RbSize is 0x%x\n", RwBuff.u32Size, RwBuff.u32RbSize);
            socp_printf("WriteDone: enc src, u32WrtSize is 0x%x, u32SrcChanID is 0x%x\n", u32WrtSize, u32SrcChanID);
            g_stSocpDebugInfo.sSocpDebugEncSrc.u32socp_write_doneEncSrcFailCnt[u32ChanID]++;
            return BSP_ERR_SOCP_INVALID_PARA;
        }

        /* ???????????? */
        socp_write_done(&pChan->sEncSrcBuf, u32WrtSize);

        /* ????????????????????????*/
        uPAddr = SOCP_VIRT_PHY(pChan->sEncSrcBuf.u32Write); /* [false alarm]:????Fortify???? */
        SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFWPTR(u32ChanID), uPAddr);
        g_stSocpDebugInfo.sSocpDebugEncSrc.u32socp_write_doneEncSrcSucCnt[u32ChanID]++;
    }
    else  if(SOCP_DECODER_SRC_CHAN == u32ChanType) /* ???????? */
    {
        SOCP_DECSRC_CHAN_S  *pChan;

        g_stSocpDebugInfo.sSocpDebugDecSrc.u32socp_write_doneDecSrcEtrCnt[u32ChanID]++;

        /* ????????id */
        SOCP_CHECK_CHAN_ID(u32ChanID, SOCP_MAX_DECSRC_CHN);
        SOCP_CHECK_DECSRC_SET(u32ChanID);
        pChan = &g_strSocpStat.sDecSrcChan[u32ChanID];
        SOCP_REG_READ(SOCP_REG_DECSRC_BUFWPTR(u32ChanID), uPAddr);
        pChan->sDecSrcBuf.u32Write= SOCP_PHY_VIRT(uPAddr);
        SOCP_REG_READ(SOCP_REG_DECSRC_BUFRPTR(u32ChanID), uPAddr);
        pChan->sDecSrcBuf.u32Read =SOCP_PHY_VIRT(uPAddr);
        socp_get_idle_buffer(&pChan->sDecSrcBuf, &RwBuff);

        if (RwBuff.u32Size + RwBuff.u32RbSize < u32WrtSize)
        {
            socp_printf("WriteDone: dec src, too large write size!\n");
            socp_printf("WriteDone: dec src, write ptr is 0x%x, read ptr is 0x%x\n", pChan->sDecSrcBuf.u32Write, pChan->sDecSrcBuf.u32Read);
            socp_printf("WriteDone: dec src, u32Size is 0x%x, u32RbSize is 0x%x\n", RwBuff.u32Size, RwBuff.u32RbSize);
            socp_printf("WriteDone: dec src, u32WrtSize is 0x%x, u32SrcChanID is 0x%x\n", u32WrtSize, u32SrcChanID);
            g_stSocpDebugInfo.sSocpDebugDecSrc.u32socp_write_doneDecSrcFailCnt[u32ChanID]++;

            return BSP_ERR_SOCP_INVALID_PARA;
        }

        /* ???????????? */
        socp_write_done(&pChan->sDecSrcBuf, u32WrtSize);

        /* ????????????????????????*/
        uPAddr = SOCP_VIRT_PHY(pChan->sDecSrcBuf.u32Write); /* [false alarm]:????Fortify???? */
        SOCP_REG_WRITE(SOCP_REG_DECSRC_BUFWPTR(u32ChanID), uPAddr);
        g_stSocpDebugInfo.sSocpDebugDecSrc.u32socp_write_doneDecSrcSucCnt[u32ChanID]++;
    }
    else
    {
        socp_printf("WriteDone: invalid chan type: 0x%x!\n", u32ChanType);
        return BSP_ERR_SOCP_INVALID_CHAN;
    }

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : bsp_socp_register_rd_cb
*
* ????????  : RDbuffer????????????????
*
* ????????  : u32SrcChanID    ??????ID
              RdCB            RDbuffer????????????
*
* ????????  :
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/
s32 bsp_socp_register_rd_cb(u32 u32SrcChanID, socp_rd_cb RdCB)
{
    u32 u32RealChanID;
    u32 u32ChanType;

    /* ?????????????????? */
    SOCP_CHECK_INIT();

    /* ????????????????????????ID */
    u32RealChanID = SOCP_REAL_CHAN_ID(u32SrcChanID);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32SrcChanID);

    /* ???????? */
    if (SOCP_CODER_SRC_CHAN == u32ChanType)
    {
        SOCP_CHECK_ENCSRC_CHAN_ID(u32RealChanID);
        SOCP_CHECK_ENCSRC_ALLOC(u32RealChanID);

        if (SOCP_ENCSRC_CHNMODE_LIST == g_strSocpStat.sEncSrcChan[u32RealChanID].eChnMode)
        {
            /* ??????????????????????*/
            g_strSocpStat.sEncSrcChan[u32RealChanID].rd_cb = RdCB;
        }
        else
        {
            socp_printf("RegisterRdCB: invalid chan mode!\n");
            return BSP_ERR_SOCP_CHAN_MODE;
        }

        g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpRegRdCBEncSrcCnt[u32RealChanID]++;
    }
    else
    {
        socp_printf("RegisterRdCB: invalid chan type: 0x%x!\n", u32ChanType);
        return BSP_ERR_SOCP_INVALID_CHAN;
    }

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : bsp_socp_get_rd_buffer
*
* ????????  : ????RDbuffer????
*
* ????????  : u32SrcChanID    ??????ID
*
* ????????  : pBuff           ??????RDbuffer
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/
s32 bsp_socp_get_rd_buffer(u32 u32SrcChanID, SOCP_BUFFER_RW_STRU *pBuff)
{
    u32 u32ChanID;
    u32 u32ChanType;
    u32 uPAddr;

    /* ?????????????????? */
    SOCP_CHECK_INIT();

    /* ?????????????? */
    SOCP_CHECK_PARA(pBuff);

    /* ????????????id */
    u32ChanID   = SOCP_REAL_CHAN_ID(u32SrcChanID);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32SrcChanID);

    /* ???????? */
    if (SOCP_CODER_SRC_CHAN == u32ChanType)
    {
        g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpGetRdBufEncSrcEtrCnt[u32ChanID]++;

        /* ????????id */
        SOCP_CHECK_ENCSRC_CHAN_ID(u32ChanID);
        SOCP_CHECK_ENCSRC_ALLOC(u32ChanID);

        /* ????????????????buffer */
        SOCP_REG_READ(SOCP_REG_ENCSRC_RDQRPTR(u32ChanID), uPAddr);
        g_strSocpStat.sEncSrcChan[u32ChanID].sRdBuf.u32Read = SOCP_PHY_VIRT(uPAddr);
        SOCP_REG_READ(SOCP_REG_ENCSRC_RDQWPTR(u32ChanID), uPAddr);
        g_strSocpStat.sEncSrcChan[u32ChanID].sRdBuf.u32Write= SOCP_PHY_VIRT(uPAddr);
        socp_get_data_buffer(&g_strSocpStat.sEncSrcChan[u32ChanID].sRdBuf, pBuff);
        g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpGetRdBufEncSrcSucCnt[u32ChanID]++;
    }
    else
    {
        socp_printf("GetRDBuffer: invalid chan type: 0x%x!\n", u32ChanType);
        return BSP_ERR_SOCP_INVALID_CHAN;
    }

    return BSP_OK;
}


/*****************************************************************************
* ?? ?? ??  : bsp_socp_read_rd_done
*
* ????????  : ????RDbuffer????????????
*
* ????????  : u32SrcChanID   ??????ID
              u32RDSize      ??????RDbuffer????????
*
* ????????  :
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/
s32 bsp_socp_read_rd_done(u32 u32SrcChanID, u32 u32RDSize)
{
    u32 u32ChanID;
    u32 u32ChanType;
    SOCP_BUFFER_RW_STRU RwBuff;
    u32  uPAddr;

    /* ?????????????????? */
    SOCP_CHECK_INIT();

    /* ?????????????? */
    SOCP_CHECK_PARA(u32RDSize);

    /* ????????????id */
    u32ChanID   = SOCP_REAL_CHAN_ID(u32SrcChanID);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32SrcChanID);

    /* ???????? */
    if (SOCP_CODER_SRC_CHAN == u32ChanType)
    {
        SOCP_ENCSRC_CHAN_S *pChan;

        g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpReadRdDoneEncSrcEtrCnt[u32ChanID]++;

        /* ????????id */
        SOCP_CHECK_ENCSRC_CHAN_ID(u32ChanID);
        SOCP_CHECK_ENCSRC_ALLOC(u32ChanID);

        pChan = &g_strSocpStat.sEncSrcChan[u32ChanID];
        g_strSocpStat.sEncSrcChan[u32ChanID].u32LastRdSize = 0;

        /* ???????????? */
        SOCP_REG_READ(SOCP_REG_ENCSRC_RDQWPTR(u32ChanID), uPAddr);
        pChan->sRdBuf.u32Write = SOCP_PHY_VIRT(uPAddr);
        SOCP_REG_READ(SOCP_REG_ENCSRC_RDQRPTR(u32ChanID), uPAddr);
        pChan->sRdBuf.u32Read  = SOCP_PHY_VIRT(uPAddr);
        socp_get_data_buffer(&pChan->sRdBuf, &RwBuff);

        if (RwBuff.u32Size + RwBuff.u32RbSize < u32RDSize)
        {
            socp_printf("ReadRDDone: enc src, too large rd size!\n");
            socp_printf("ReadRDDone: enc src, write ptr is 0x%x, read ptr is 0x%x\n", pChan->sRdBuf.u32Write, pChan->sRdBuf.u32Read);
            socp_printf("ReadRDDone: enc src, u32Size is 0x%x, u32RbSize is 0x%x\n", RwBuff.u32Size, RwBuff.u32RbSize);
            socp_printf("ReadRDDone: enc src, u32RDSize is 0x%x, u32SrcChanID is 0x%x\n", u32RDSize, u32SrcChanID);
            g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpReadRdDoneEncSrcFailCnt[u32ChanID]++;

            return BSP_ERR_SOCP_INVALID_PARA;
        }

        socp_read_done(&pChan->sRdBuf, u32RDSize);

        /* ????????????????????????*/
        uPAddr= SOCP_VIRT_PHY(pChan->sRdBuf.u32Read); /* [false alarm]:????Fortify???? */
        SOCP_REG_WRITE(SOCP_REG_ENCSRC_RDQRPTR(u32ChanID), uPAddr);
        g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpReadRdDoneEncSrcSucCnt[u32ChanID]++;
    }
    else
    {
        socp_printf("ReadRDDone: invalid chan type: 0x%x!", u32ChanType);
        return BSP_ERR_SOCP_INVALID_CHAN;
    }

    return BSP_OK;
}

//????????????????

/*****************************************************************************
* ?? ?? ??  : bsp_socp_register_read_cb
*
* ????????  : ??????????????????????
*
* ????????  : u32DestChanID  ??????????ID
              ReadCB         ??????????????
*
* ????????  :
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/
s32 bsp_socp_register_read_cb(u32 u32DestChanID, socp_read_cb ReadCB)
{
    u32 u32RealChanID;
    u32 u32ChanType;

    /* ?????????????????? */
    SOCP_CHECK_INIT();

    /* ????????????????????????ID */
    u32RealChanID = SOCP_REAL_CHAN_ID(u32DestChanID);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32DestChanID);

    if (SOCP_DECODER_DEST_CHAN == u32ChanType) /* ???????? */
    {
        SOCP_CHECK_CHAN_ID(u32RealChanID, SOCP_MAX_DECDST_CHN);
        SOCP_CHECK_DECDST_ALLOC(u32RealChanID);

        g_strSocpStat.sDecDstChan[u32RealChanID].read_cb = ReadCB;

        g_stSocpDebugInfo.sSocpDebugDecDst.u32SocpRegReadCBDecDstCnt[u32RealChanID]++;
    }
    else if (SOCP_CODER_DEST_CHAN == u32ChanType)/* ???????? */
    {
        SOCP_CHECK_CHAN_ID(u32RealChanID, SOCP_MAX_ENCDST_CHN);
        SOCP_CHECK_ENCDST_SET(u32RealChanID);

        /* ??????????????????????*/
        g_strSocpStat.sEncDstChan[u32RealChanID].read_cb = ReadCB;

        g_stSocpDebugInfo.sSocpDebugEncDst.u32SocpRegReadCBEncDstCnt[u32RealChanID]++;
    }
    else
    {
        socp_printf("RegisterReadCB: invalid chan type: 0x%x!\n", u32ChanType);
        return BSP_ERR_SOCP_INVALID_CHAN;
    }

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : bsp_socp_get_read_buff
*
* ????????  : ??????????buffer????
*
* ????????  : u32DestChanID  ????????buffer

* ????????  : pBuffer        ????????????buffer
*
* ?? ?? ??  : ????????????????????
*****************************************************************************/
s32 bsp_socp_get_read_buff(u32 u32DestChanID, SOCP_BUFFER_RW_STRU *pBuffer)
{
    u32 u32ChanID;
    u32 u32ChanType;
    u32  uPAddr;

    /* ?????????????????? */
    SOCP_CHECK_INIT();

    /* ?????????????? */
    SOCP_CHECK_PARA(pBuffer);
    if(g_ulSocpPowerState == SOCP_POWER_OFF)
    {
        return BSP_ERROR;
    }

    /* ????????????id */
    u32ChanID   = SOCP_REAL_CHAN_ID(u32DestChanID);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32DestChanID);
    pBuffer->u32Size   = 0;
    pBuffer->u32RbSize = 0;

    if (SOCP_DECODER_DEST_CHAN == u32ChanType) /* ???????? */
    {
        g_stSocpDebugInfo.sSocpDebugDecDst.u32SocpGetReadBufDecDstEtrCnt[u32ChanID]++;

        /* ????????id */
        SOCP_CHECK_CHAN_ID(u32ChanID, SOCP_MAX_DECDST_CHN);
        SOCP_CHECK_DECDST_ALLOC(u32ChanID);

        /* ????????????????buffer */
        SOCP_REG_READ(SOCP_REG_DECDEST_BUFRPTR(u32ChanID), uPAddr);
        g_strSocpStat.sDecDstChan[u32ChanID].sDecDstBuf.u32Read = SOCP_PHY_VIRT(uPAddr);
        SOCP_REG_READ(SOCP_REG_DECDEST_BUFWPTR(u32ChanID), uPAddr);
        g_strSocpStat.sDecDstChan[u32ChanID].sDecDstBuf.u32Write= SOCP_PHY_VIRT(uPAddr);
        socp_get_data_buffer(&g_strSocpStat.sDecDstChan[u32ChanID].sDecDstBuf, pBuffer);
        g_stSocpDebugInfo.sSocpDebugDecDst.u32SocpGetReadBufDecDstSucCnt[u32ChanID]++;
    }
    else if (SOCP_CODER_DEST_CHAN == u32ChanType)
    {
        g_stSocpDebugInfo.sSocpDebugEncDst.u32SocpGetReadBufEncDstEtrCnt[u32ChanID]++;
        /*deflate????????deflate buffer*/
        if((SOCP_COMPRESS == g_strSocpStat.sEncDstChan[u32ChanID].struCompress.bcompress )
            &&(g_strSocpStat.sEncDstChan[u32ChanID].struCompress.ops.getbuffer))
        {
            g_strSocpStat.sEncDstChan[u32ChanID].struCompress.ops.getbuffer(u32ChanID, pBuffer);
            return BSP_OK;
        }

        /* ????????id */
        SOCP_CHECK_CHAN_ID(u32ChanID, SOCP_MAX_ENCDST_CHN);
        SOCP_CHECK_ENCDST_SET(u32ChanID);

        /* ????????????????buffer */
        SOCP_REG_READ(SOCP_REG_ENCDEST_BUFRPTR(u32ChanID), uPAddr);
        g_strSocpStat.sEncDstChan[u32ChanID].sEncDstBuf.u32Read = SOCP_PHY_VIRT(uPAddr);
        SOCP_REG_READ(SOCP_REG_ENCDEST_BUFWPTR(u32ChanID), uPAddr);
        g_strSocpStat.sEncDstChan[u32ChanID].sEncDstBuf.u32Write= SOCP_PHY_VIRT(uPAddr);
        socp_get_data_buffer(&g_strSocpStat.sEncDstChan[u32ChanID].sEncDstBuf, pBuffer);
        g_stSocpDebugInfo.sSocpDebugEncDst.u32SocpGetReadBufEncDstSucCnt[u32ChanID]++;
    }
    else
    {
        socp_printf("GetReadBuff: invalid chan type: 0x%x!\n", u32ChanType);
        return BSP_ERR_SOCP_INVALID_CHAN;
    }

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : bsp_socp_read_data_done
*
* ????????  : ??????????????
*
* ????????  : u32DestChanID    ????????ID
*             u32ReadSize      ????????????
* ????????  : ??
*
* ?? ?? ??  : ??????????????????????
*****************************************************************************/
s32 bsp_socp_read_data_done(u32 u32DestChanID, u32 u32ReadSize)
{
    u32 u32ChanID;
    u32 u32ChanType;
    SOCP_BUFFER_RW_STRU RwBuff;
    u32  uPAddr;
    unsigned long lock_flag;

    /* ?????????????????? */
    SOCP_CHECK_INIT();
    if(g_ulSocpPowerState == SOCP_POWER_OFF)
    {
        return BSP_ERROR;
    }

    /*????MSP????????????????????????????0??????2011-04-29*/
    //SOCP_CHECK_PARA(u32ReadSize);

    /* ????????????id */
    u32ChanID   = SOCP_REAL_CHAN_ID(u32DestChanID);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32DestChanID);

    if (SOCP_DECODER_DEST_CHAN == u32ChanType) /* ???????? */
    {
        u32 TfMaskReg = 0;
        SOCP_DECDST_CHAN_S *pChan;

        g_stSocpDebugInfo.sSocpDebugDecDst.u32socp_read_doneDecDstEtrCnt[u32ChanID]++;

        /* ????????id */
        SOCP_CHECK_CHAN_ID(u32ChanID, SOCP_MAX_DECDST_CHN);
        SOCP_CHECK_DECDST_ALLOC(u32ChanID);

        //added by yangzhi 2011.7.25
        TfMaskReg = SOCP_REG_DEC_CORE0MASK0;
        pChan = &g_strSocpStat.sDecDstChan[u32ChanID];
        SOCP_REG_READ(SOCP_REG_DECDEST_BUFWPTR(u32ChanID), uPAddr);
        pChan->sDecDstBuf.u32Write= SOCP_PHY_VIRT(uPAddr);
        SOCP_REG_READ(SOCP_REG_DECDEST_BUFRPTR(u32ChanID), uPAddr);
        pChan->sDecDstBuf.u32Read = SOCP_PHY_VIRT(uPAddr);
        socp_get_data_buffer(&pChan->sDecDstBuf, &RwBuff);

        if(RwBuff.u32Size + RwBuff.u32RbSize < u32ReadSize)
        {
            socp_printf("ReadDataDone: dec dst, too large read size!\n");
            socp_printf("ReadDataDone: dec dst, write ptr is 0x%x, read ptr is 0x%x\n", pChan->sDecDstBuf.u32Write, pChan->sDecDstBuf.u32Read);
            socp_printf("ReadDataDone: dec dst, u32Size is 0x%x, u32RbSize is 0x%x\n", RwBuff.u32Size, RwBuff.u32RbSize);
            socp_printf("ReadDataDone: dec dst, u32ReadSize is 0x%x, u32DestChanID is 0x%x\n", u32ReadSize, u32DestChanID);
            spin_lock_irqsave(&lock, lock_flag);
            SOCP_REG_SETBITS(SOCP_REG_DEC_RAWINT0, u32ChanID, 1, 1);
            SOCP_REG_SETBITS(TfMaskReg, u32ChanID, 1, 0);
            spin_unlock_irqrestore(&lock, lock_flag);
            g_stSocpDebugInfo.sSocpDebugDecDst.u32socp_read_doneDecDstFailCnt[u32ChanID]++;

            return BSP_ERR_SOCP_INVALID_PARA;
        }

        /* ???????????? */
        socp_read_done(&pChan->sDecDstBuf, u32ReadSize);

        /* ????????????????????????*/
        uPAddr = SOCP_VIRT_PHY(pChan->sDecDstBuf.u32Read); /* [false alarm]:????Fortify???? */
        SOCP_REG_WRITE(SOCP_REG_DECDEST_BUFRPTR(u32ChanID), uPAddr);
        //added by yangzhi 2011.7.25
        spin_lock_irqsave(&lock, lock_flag);
        SOCP_REG_SETBITS(SOCP_REG_DEC_RAWINT0, u32ChanID, 1, 1);
        SOCP_REG_SETBITS(TfMaskReg, u32ChanID, 1, 0);
        spin_unlock_irqrestore(&lock, lock_flag);

        if (0 == u32ReadSize)
        {
            g_stSocpDebugInfo.sSocpDebugDecDst.u32socp_read_doneZeroDecDstCnt[u32ChanID]++;
        }
        else
        {
            g_stSocpDebugInfo.sSocpDebugDecDst.u32socp_read_doneValidDecDstCnt[u32ChanID]++;
        }

        g_stSocpDebugInfo.sSocpDebugDecDst.u32socp_read_doneDecDstSucCnt[u32ChanID]++;

        if(0 != down_interruptible(&g_stSocpPowerSem))
        {
            socp_printf("%s:socp sem interruptible\n", __FUNCTION__);
        }

        /* ?????????????????????????? */
        if(g_ulSocpPowerState == SOCP_POWER_OFF_REQ)
        {
            if(BSP_OK == socp_can_sleep())
            {
                /* ?????????????????????????? */
                SOCP_REG_READ(SOCP_REG_ENC_MASK0, g_ul_encdst_tran_int_mask);
                SOCP_REG_READ(SOCP_REG_ENC_MASK2, g_ul_encdst_over_int_mask);
                SOCP_REG_READ(SOCP_REG_DEC_CORE0MASK0, g_ul_decdst_tran_int_mask);
                /* ???????? */
                SOCP_REG_SETBITS(SOCP_REG_ENC_MASK0, 0, 7, 0x7f);
                SOCP_REG_SETBITS(SOCP_REG_ENC_MASK2, 0, 7, 0x7f);
                SOCP_REG_SETBITS(SOCP_REG_ENC_MASK2, 16, 7, 0x7f);
                SOCP_REG_SETBITS(SOCP_REG_DEC_CORE0MASK0, 0, 16, 0xffff);
                if(regulator_bulk_disable(1, &(g_stSocpVcc->socp_vcc)))
                {
                    socp_printf("[%s]:fetal error, regulator disable fail\n", __FUNCTION__);
                }
                else
                {
                    g_ulSocpPowerState = SOCP_POWER_OFF;
                    socp_printf("%s: socp goto power off\n", __FUNCTION__);
                }
            }
        }

        up(&g_stSocpPowerSem);

    }
    else if (SOCP_CODER_DEST_CHAN == u32ChanType)/* ???????? */
    {
        SOCP_ENCDST_CHAN_S *pChan;

        g_stSocpDebugInfo.sSocpDebugEncDst.u32socp_read_doneEncDstEtrCnt[u32ChanID]++;

        /* ????????id */
        SOCP_CHECK_CHAN_ID(u32ChanID, SOCP_MAX_ENCDST_CHN);
        SOCP_CHECK_ENCDST_SET(u32ChanID);
        if(u32ChanID == 1)
        {
            g_stEncDstStat[g_ulEncDstStatCount].ulReadDoneStartSlice = bsp_get_slice_value();
        }
        /*????deflate??????deflate readdone*/
        if(( SOCP_COMPRESS == g_strSocpStat.sEncDstChan[u32ChanID].struCompress.bcompress)
            &&(g_strSocpStat.sEncDstChan[u32ChanID].struCompress.ops.readdone))
        {
            g_strSocpStat.sEncDstChan[u32ChanID].struCompress.ops.readdone(u32ChanID, u32ReadSize);
            return BSP_OK;
        }

        if (0 == u32ReadSize)
        {
            g_stSocpDebugInfo.sSocpDebugEncDst.u32socp_read_doneZeroEncDstCnt[u32ChanID]++;
        }
        else
        {
            g_stSocpDebugInfo.sSocpDebugEncDst.u32socp_read_doneValidEncDstCnt[u32ChanID]++;
        }

        pChan = &g_strSocpStat.sEncDstChan[u32ChanID];
        SOCP_REG_READ(SOCP_REG_ENCDEST_BUFWPTR(u32ChanID), uPAddr);
        pChan->sEncDstBuf.u32Write= SOCP_PHY_VIRT(uPAddr);
        SOCP_REG_READ(SOCP_REG_ENCDEST_BUFRPTR(u32ChanID), uPAddr);
        pChan->sEncDstBuf.u32Read = SOCP_PHY_VIRT(uPAddr);
        socp_get_data_buffer(&pChan->sEncDstBuf, &RwBuff);

        if(RwBuff.u32Size + RwBuff.u32RbSize < u32ReadSize)
        {
            socp_printf("ReadDataDone: enc dst, too large read size!\n");
            socp_printf("ReadDataDone: enc dst, write ptr is 0x%x, read ptr is 0x%x\n", pChan->sEncDstBuf.u32Write, pChan->sEncDstBuf.u32Read);
            socp_printf("ReadDataDone: enc dst, u32Size is 0x%x, u32RbSize is 0x%x\n", RwBuff.u32Size, RwBuff.u32RbSize);
            socp_printf("ReadDataDone: enc dst, u32ReadSize is 0x%x, u32DestChanID is 0x%x\n", u32ReadSize, u32DestChanID);
            spin_lock_irqsave(&lock, lock_flag);
            SOCP_REG_SETBITS(SOCP_REG_ENC_RAWINT0, u32ChanID, 1, 1);
            SOCP_REG_SETBITS(SOCP_REG_ENC_MASK0, u32ChanID, 1, 0);
            /* overflow int */
            SOCP_REG_SETBITS(SOCP_REG_ENC_RAWINT2, u32ChanID + 16, 1, 1);
            SOCP_REG_SETBITS(SOCP_REG_ENC_MASK2, u32ChanID + 16, 1, 0);
            spin_unlock_irqrestore(&lock, lock_flag);
            g_stSocpDebugInfo.sSocpDebugEncDst.u32socp_read_doneEncDstFailCnt[u32ChanID]++;
            return BSP_ERR_SOCP_INVALID_PARA;
        }

        /* ???????????? */
        socp_read_done(&pChan->sEncDstBuf, u32ReadSize);

        /* ????????????????????????*/
        uPAddr = SOCP_VIRT_PHY(pChan->sEncDstBuf.u32Read); /* [false alarm]:????Fortify???? */
        SOCP_REG_WRITE(SOCP_REG_ENCDEST_BUFRPTR(u32ChanID), uPAddr);
        spin_lock_irqsave(&lock, lock_flag);
        SOCP_REG_SETBITS(SOCP_REG_ENC_RAWINT0, u32ChanID, 1, 1);
        SOCP_REG_SETBITS(SOCP_REG_ENC_MASK0, u32ChanID, 1, 0);
        /* overflow int */
        SOCP_REG_SETBITS(SOCP_REG_ENC_RAWINT2, u32ChanID + 16, 1, 1);
        SOCP_REG_SETBITS(SOCP_REG_ENC_MASK2, u32ChanID + 16, 1, 0);
        spin_unlock_irqrestore(&lock, lock_flag);
        g_stSocpDebugInfo.sSocpDebugEncDst.u32socp_read_doneEncDstSucCnt[u32ChanID]++;

        if(u32ChanID == 1)
        {
            g_stEncDstStat[g_ulEncDstStatCount].ulReadDoneEndSlice = bsp_get_slice_value();
            g_ulEncDstStatCount = (g_ulEncDstStatCount+1)%SOCP_MAX_ENC_DST_COUNT;
        }

        if(0 != down_interruptible(&g_stSocpPowerSem))
        {
            socp_printf("%s:socp sem interruptible\n", __FUNCTION__);
        }

        /* ?????????????????????????? */
        if(g_ulSocpPowerState == SOCP_POWER_OFF_REQ)
        {
            if(BSP_OK == socp_can_sleep())
            {
                /* ?????????????????????????? */
                SOCP_REG_READ(SOCP_REG_ENC_MASK0, g_ul_encdst_tran_int_mask);
                SOCP_REG_READ(SOCP_REG_ENC_MASK2, g_ul_encdst_over_int_mask);
                SOCP_REG_READ(SOCP_REG_DEC_CORE0MASK0, g_ul_decdst_tran_int_mask);
                /* ???????? */
                SOCP_REG_SETBITS(SOCP_REG_ENC_MASK0, 0, 7, 0x7f);
                SOCP_REG_SETBITS(SOCP_REG_ENC_MASK2, 0, 7, 0x7f);
                SOCP_REG_SETBITS(SOCP_REG_ENC_MASK2, 16, 7, 0x7f);
                SOCP_REG_SETBITS(SOCP_REG_DEC_CORE0MASK0, 0, 16, 0xffff);

                if(regulator_bulk_disable(1, &(g_stSocpVcc->socp_vcc)))
                {
                    socp_printf("[%s]:fetal error, regulator disable fail\n", __FUNCTION__);
                }
                else
                {
                    g_ulSocpPowerState = SOCP_POWER_OFF;
                    socp_printf("%s: socp goto power off\n", __FUNCTION__);
                }
            }
        }

        up(&g_stSocpPowerSem);
    }
    else
    {
        socp_printf("ReadDataDone: invalid chan type: 0x%x!\n", u32ChanType);
        return BSP_ERR_SOCP_INVALID_CHAN;
    }

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : bsp_socp_set_bbp_enable
*
* ????????  : ????/????BPP LOG??????
*
* ????????  : bEnable       ????????
*
* ????????  : ??
*
* ?? ?? ??  : ??????????????????????
*****************************************************************************/
s32 bsp_socp_set_bbp_enable(int bEnable)
{
    if(bEnable)
    {
        BBP_REG_SETBITS(BBP_REG_CH_EN, 0, 1, 1);
    }
    else
    {
        BBP_REG_SETBITS(BBP_REG_CH_EN, 0, 1, 0);
    }
    return BSP_OK;
}


/*****************************************************************************
* ?? ?? ??  : bsp_socp_set_bbp_ds_mode
*
* ????????  : ????BPP????????
*
* ????????  : eDsMode    ????????
*
* ????????  : ??
*
* ?? ?? ??  :
*****************************************************************************/
s32 bsp_socp_set_bbp_ds_mode(SOCP_BBP_DS_MODE_ENUM_UIN32 eDsMode)
{
    if(eDsMode >= SOCP_BBP_DS_MODE_BUTT)
    {
        socp_printf("SetBbpDsMode: invalid DS mode!\n");
        return BSP_ERR_SOCP_INVALID_PARA;
    }

    BBP_REG_SETBITS(BBP_REG_DS_CFG, 31, 1, eDsMode);
    return BSP_OK;
}
void bsp_socp_set_enc_dst_threshold(bool mode,u32 u32DestChanID)
{
    u32 bufLength;
    u32 threshold;

    u32DestChanID = SOCP_REAL_CHAN_ID(u32DestChanID);
    (void)bsp_socp_vote(SOCP_VOTE_SOCP_REG,SOCP_VOTE_FOR_WAKE);

    SOCP_REG_READ(SOCP_REG_ENCDEST_BUFCFG(u32DestChanID),bufLength);
    if(mode == true)/*true????????????????????????*/
    {
        threshold = (bufLength >> 2)*3;
    }
    else
    {
        threshold = 0x1000;
    }
    SOCP_REG_WRITE(SOCP_REG_ENCDEST_BUFTHRESHOLD(u32DestChanID),threshold);

    (void)bsp_socp_vote(SOCP_VOTE_SOCP_REG,SOCP_VOTE_FOR_SLEEP);
    return;
}

/*****************************************************************************
* ?? ?? ??   : socp_enc_dst_stat
*
* ????????  : ????socp????????
*
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
void show_socp_enc_dst_stat(void)
{
    int i = 0;
    int count = (g_ulEncDstStatCount+1)%SOCP_MAX_ENC_DST_COUNT;

    for(i=0;i<SOCP_MAX_ENC_DST_COUNT;i++)
    {
        printk("\r **********stat %d count************ \r\n",i);
        printk("Int   Start  : 0x%x,  End  : 0x%x ,Slice :0x%x\n",g_stEncDstStat[count].ulIntStartSlice,g_stEncDstStat[count].ulIntEndSlice,g_stEncDstStat[count].ulIntEndSlice-g_stEncDstStat[count].ulIntStartSlice);
        printk("Task  Start  : 0x%x,  End  : 0x%x ,Slice :0x%x\n",g_stEncDstStat[count].ulTaskStartSlice,g_stEncDstStat[count].ulTaskEndSlice,g_stEncDstStat[count].ulTaskEndSlice-g_stEncDstStat[count].ulTaskStartSlice);
        printk("Read  Start  : 0x%x,  End  : 0x%x ,Slice :0x%x\n",g_stEncDstStat[count].ulReadDoneStartSlice,g_stEncDstStat[count].ulReadDoneEndSlice,g_stEncDstStat[count].ulReadDoneEndSlice-g_stEncDstStat[count].ulReadDoneStartSlice);
        printk("Int  ==> Task 0x%x\n",g_stEncDstStat[count].ulTaskStartSlice-g_stEncDstStat[count].ulIntStartSlice);
        printk("Task  ==> Read 0x%x\n",g_stEncDstStat[count].ulReadDoneStartSlice-g_stEncDstStat[count].ulTaskEndSlice);
        count = (count+1)%SOCP_MAX_ENC_DST_COUNT;
    }
}

/*****************************************************************************
* ?? ?? ??   : socp_help
*
* ????????  : ????socp????????
*
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
void socp_help(void)
{
    socp_printf("\r |*************************************|\n");
    socp_printf("\r socp_show_debug_gbl   : ????????????????:??????????????????????????????????\n");
    socp_printf("\r socp_show_enc_src_chan_cur : ??????????????????????????????ID\n");
    socp_printf("\r socp_show_enc_src_chan_add : ????????????????????????????????????ID\n");
    socp_printf("\r socp_show_enc_src_chan_add : ??????????????????????????????????????\n");
    socp_printf("\r socp_show_enc_dst_chan_cur : ????????????????????????????????ID\n");
    socp_printf("\r socp_show_enc_dst_chan_add : ??????????????????????????????????????ID\n");
    socp_printf("\r socp_show_enc_dst_chan_all : ????????????????????????????????????????\n");
    socp_printf("\r socp_show_dec_src_chan_cur : ??????????????????????????????ID\n");
    socp_printf("\r socp_show_dec_src_chan_add : ????????????????????????????????????ID\n");
    socp_printf("\r socp_show_dec_src_chan_all : ??????????????????????????????????????\n");
    socp_printf("\r socp_show_dec_dst_chan_cur : ????????????????????????????????ID\n");
    socp_printf("\r socp_show_dec_dst_chan_add : ??????????????????????????????????????ID\n");
    socp_printf("\r socp_show_dec_dst_chan_all : ????????????????????????????????????????\n");
    socp_printf("\r socp_show_ccore_head_err_cnt : ????C??????????????????????????????????????\n");
    socp_printf("\r socp_debug_cnt_show : ????????????????????????\n");
}

/*****************************************************************************
* ?? ?? ??   : socp_show_debug_gbl
*
* ????????  : ????????debug ????????
*
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
void socp_show_debug_gbl(void)
{
    SOCP_DEBUG_GBL_S *sSocpDebugGblInfo;

    sSocpDebugGblInfo = &g_stSocpDebugInfo.sSocpDebugGBl;

    socp_printf(" SOCP????????????????:\n");
    socp_printf(" socp??????:                           : 0x%x\n", (s32)g_strSocpStat.baseAddr);
    socp_printf(" socp????????????????????              : 0x%x\n", (s32)sSocpDebugGblInfo->u32SocpAllocEncSrcCnt);
    socp_printf(" socp????????????????????????          : 0x%x\n", (s32)sSocpDebugGblInfo->u32SocpAllocEncSrcSucCnt);
    socp_printf(" socp??????????????????????            : 0x%x\n", (s32)sSocpDebugGblInfo->u32SocpSetEncDstCnt);
    socp_printf(" socp??????????????????????????        : 0x%x\n", (s32)sSocpDebugGblInfo->u32SocpSetEncDstSucCnt);
    socp_printf(" socp????????????????????              : 0x%x\n", (s32)sSocpDebugGblInfo->u32SocpSetDecSrcCnt);
    socp_printf(" socp????????????????????????          : 0x%x\n", (s32)sSocpDebugGblInfo->u32SocpSetDeSrcSucCnt);
    socp_printf(" socp??????????????????????            : 0x%x\n", (s32)sSocpDebugGblInfo->u32SocpAllocDecDstCnt);
    socp_printf(" socp??????????????????????????        : 0x%x\n", (s32)sSocpDebugGblInfo->u32SocpAllocDecDstSucCnt);
    socp_printf(" socp????APP??????????                 : 0x%x\n", (s32)sSocpDebugGblInfo->u32SocpAppEtrIntCnt);
    socp_printf(" socp????APP??????????                 : 0x%x\n", (s32)sSocpDebugGblInfo->u32SocpAppSucIntCnt);
}

/*****************************************************************************
* ?? ?? ??  : socp_show_ccore_head_err_cnt
*
* ????????  : ????C??????????????????????????
*
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
void socp_show_ccore_head_err_cnt(void)
{
    int i;
    for(i = SOCP_CCORE_ENCSRC_CHN_BASE; i < SOCP_CCORE_ENCSRC_CHN_BASE + SOCP_CCORE_ENCSRC_CHN_NUM; i++)
    {
        socp_printf("================== ?????????? 0x%x  ??????????????????:=================\n", i);
        socp_printf(" socp ISR ????????????????????????????????                  : 0x%x\n",
            (s32)g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpEncSrcIsrHeadIntCnt[i]);
    }
}

/*****************************************************************************
* ?? ?? ??   : socp_show_enc_src_chan_cur
*
* ????????  : ??????????????????????
*
* ????????  : ????ID
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/

/*lint -save -e529*/
u32 socp_show_enc_src_chan_cur(u32 u32UniqueId)
{
    u32 u32RealId   = 0;
    u32 u32ChanType = 0;

    u32RealId   = SOCP_REAL_CHAN_ID(u32UniqueId);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32UniqueId);

    SOCP_CHECK_CHAN_TYPE(u32ChanType, SOCP_CODER_SRC_CHAN);
    SOCP_CHECK_ENCSRC_CHAN_ID(u32RealId);

    socp_printf("================== ???????????????? 0x%x  ????:=================\n", u32UniqueId);
    socp_printf("????ID:\t\t%d\n", g_strSocpStat.sEncSrcChan[u32RealId].u32ChanID);
    socp_printf("????????????:\t\t%d\n", g_strSocpStat.sEncSrcChan[u32RealId].u32AllocStat);
    socp_printf("????????????:\t\t%d\n", g_strSocpStat.sEncSrcChan[u32RealId].u32ChanEn);
    socp_printf("????????ID:\t\t%d\n", g_strSocpStat.sEncSrcChan[u32RealId].u32DestChanID);
    socp_printf("??????????:\t\t%d\n", g_strSocpStat.sEncSrcChan[u32RealId].ePriority);
    socp_printf("????????????:\t\t%d\n", g_strSocpStat.sEncSrcChan[u32RealId].u32BypassEn);
    socp_printf("????????????????:\t\t%d\n", g_strSocpStat.sEncSrcChan[u32RealId].eChnMode);
    socp_printf("??????????????:\t\t%d\n", g_strSocpStat.sEncSrcChan[u32RealId].eDataType);
    socp_printf("????buffer ????????:\t\t0x%x\n", g_strSocpStat.sEncSrcChan[u32RealId].sEncSrcBuf.u32Start);
    socp_printf("????buffer ????????:\t\t0x%x\n", g_strSocpStat.sEncSrcChan[u32RealId].sEncSrcBuf.u32End);
    socp_printf("????buffer ??????:\t\t0x%x\n", g_strSocpStat.sEncSrcChan[u32RealId].sEncSrcBuf.u32Read);
    socp_printf("????buffer ??????:\t\t0x%x\n", g_strSocpStat.sEncSrcChan[u32RealId].sEncSrcBuf.u32Write);
    socp_printf("????buffer ????:\t\t0x%x\n", g_strSocpStat.sEncSrcChan[u32RealId].sEncSrcBuf.u32Length);
    if (SOCP_ENCSRC_CHNMODE_LIST == g_strSocpStat.sEncSrcChan[u32RealId].eChnMode)
    {
        socp_printf("????RD buffer ????????:\t\t0x%x\n", g_strSocpStat.sEncSrcChan[u32RealId].sRdBuf.u32Start);
        socp_printf("????RD buffer ????????:\t\t0x%x\n", g_strSocpStat.sEncSrcChan[u32RealId].sRdBuf.u32End);
        socp_printf("????RD buffer ??????:\t\t0x%x\n", g_strSocpStat.sEncSrcChan[u32RealId].sRdBuf.u32Read);
        socp_printf("????RD buffer ??????:\t\t0x%x\n", g_strSocpStat.sEncSrcChan[u32RealId].sRdBuf.u32Write);
        socp_printf("????RD buffer ????:\t\t0x%x\n", g_strSocpStat.sEncSrcChan[u32RealId].sRdBuf.u32Length);
        socp_printf("????RD buffer ????:\t\t0x%x\n", g_strSocpStat.sEncSrcChan[u32RealId].u32RdThreshold);
    }

    return BSP_OK;
}

/*lint -restore +e529*/

/*****************************************************************************
* ?? ?? ??   : socp_show_enc_src_chan_add
*
* ????????  : ????????????????????????
*
* ????????  : ????ID
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
u32 socp_show_enc_src_chan_add(u32 u32UniqueId)
{
    u32 u32ChanType;
    u32 u32RealChanID;
    SOCP_DEBUG_ENCSRC_S *sSocpAddDebugEncSrc;

    u32RealChanID = SOCP_REAL_CHAN_ID(u32UniqueId);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32UniqueId);
    SOCP_CHECK_CHAN_TYPE(u32ChanType, SOCP_CODER_SRC_CHAN);

    sSocpAddDebugEncSrc = &g_stSocpDebugInfo.sSocpDebugEncSrc;
    SOCP_CHECK_ENCSRC_CHAN_ID(u32RealChanID);

    socp_printf("================== ?????????? 0x%x  ??????????:=================\n", u32UniqueId);
    socp_printf("socp????????????????????????                           : 0x%x\n",
           (s32)sSocpAddDebugEncSrc->u32SocpFreeEncSrcCnt[u32RealChanID]);
    socp_printf("socp????????????????????????                           : 0x%x\n",
           (s32)sSocpAddDebugEncSrc->u32SocpStartEncSrcCnt[u32RealChanID]);
    socp_printf("socp????????????????????????                           : 0x%x\n",
           (s32)sSocpAddDebugEncSrc->u32SocpStopEncSrcCnt[u32RealChanID]);
    socp_printf("socp??????????????????????????                         : 0x%x\n",
           (s32)sSocpAddDebugEncSrc->u32SocpSoftResetEncSrcCnt[u32RealChanID]);
    socp_printf("socp????????????????????????????????                   : 0x%x\n",
           (s32)sSocpAddDebugEncSrc->u32SocpRegEventEncSrcCnt[u32RealChanID]);
    socp_printf("socp????????????????????buffer??????                   : 0x%x\n",
           (s32)sSocpAddDebugEncSrc->u32SocpGetWBufEncSrcEtrCnt[u32RealChanID]);
    socp_printf("socp????????????????buffer??????????                   : 0x%x\n",
           (s32)sSocpAddDebugEncSrc->u32SocpGetWBufEncSrcSucCnt[u32RealChanID]);
    socp_printf("socp????????????????????buffer??????????               : 0x%x\n",
           (s32)sSocpAddDebugEncSrc->u32socp_write_doneEncSrcEtrCnt[u32RealChanID]);
    socp_printf("socp????????????????buffer??????????????               : 0x%x\n",
           (s32)sSocpAddDebugEncSrc->u32socp_write_doneEncSrcSucCnt[u32RealChanID]);
    socp_printf("socp????????????????buffer??????????????               : 0x%x\n",
           (s32)sSocpAddDebugEncSrc->u32socp_write_doneEncSrcFailCnt[u32RealChanID]);
    socp_printf("socp??????????????RD buffer??????????????????          : 0x%x\n",
           (s32)sSocpAddDebugEncSrc->u32SocpRegRdCBEncSrcCnt[u32RealChanID]);
    socp_printf("socp??????????????????RD buffer??????                  : 0x%x\n",
           (s32)sSocpAddDebugEncSrc->u32SocpGetRdBufEncSrcEtrCnt[u32RealChanID]);
    socp_printf("socp??????????????RD buffer??????????                  : 0x%x\n",
           (s32)sSocpAddDebugEncSrc->u32SocpGetRdBufEncSrcSucCnt[u32RealChanID]);
    socp_printf("socp??????????????????RDbuffer??????????               : 0x%x\n",
           (s32)sSocpAddDebugEncSrc->u32SocpReadRdDoneEncSrcEtrCnt[u32RealChanID]);
    socp_printf("socp??????????????RDbuffer??????????????               : 0x%x\n",
           (s32)sSocpAddDebugEncSrc->u32SocpReadRdDoneEncSrcSucCnt[u32RealChanID]);
    socp_printf("socp??????????????RDbuffer??????????????               : 0x%x\n",
           (s32)sSocpAddDebugEncSrc->u32SocpReadRdDoneEncSrcFailCnt[u32RealChanID]);
    socp_printf("socp ISR ????????????????????????????????              : 0x%x\n",
           (s32)sSocpAddDebugEncSrc->u32SocpEncSrcIsrHeadIntCnt[u32RealChanID]);
    socp_printf("socp ????????????????????????????????????????????      : 0x%x\n",
           (s32)sSocpAddDebugEncSrc->u32SocpEncSrcTskHeadCbOriCnt[u32RealChanID]);
    socp_printf("socp ????????????????????????????????????????????      : 0x%x\n",
           (s32)sSocpAddDebugEncSrc->u32SocpEncSrcTskHeadCbCnt[u32RealChanID]);
    socp_printf("socp ISR ????????????????Rd ????????????               : 0x%x\n",
           (s32)sSocpAddDebugEncSrc->u32SocpEncSrcIsrRdIntCnt[u32RealChanID]);
    socp_printf("socp ????????????????????Rd ????????????????????       : 0x%x\n",
           (s32)sSocpAddDebugEncSrc->u32SocpEncSrcTskRdCbOriCnt[u32RealChanID]);
    socp_printf("socp ??????????????Rd ??????????????????????????       : 0x%x\n",
           (s32)sSocpAddDebugEncSrc->u32SocpEncSrcTskRdCbCnt[u32RealChanID]);

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??   : socp_show_enc_src_chan_add
*
* ????????  : ??????????????????????
*
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
void  socp_show_enc_src_chan_all(void)
{
    u32 i;

    for (i = 0; i < SOCP_MAX_ENCSRC_CHN; i++)
    {
        (void)socp_show_enc_src_chan_cur(i);
        (void)socp_show_enc_src_chan_add(i);
    }

    return;
}

/*****************************************************************************
* ?? ?? ??   : socp_show_enc_dst_chan_cur
*
* ????????  : ????????????????????
*
* ????????  : ????ID
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
u32 socp_show_enc_dst_chan_cur(u32 u32UniqueId)
{
    u32 u32RealId   = 0;
    u32 u32ChanType = 0;

    u32RealId   = SOCP_REAL_CHAN_ID(u32UniqueId);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32UniqueId);

    SOCP_CHECK_CHAN_TYPE(u32ChanType, SOCP_CODER_DEST_CHAN);

    socp_printf("================== ???????????? 0x%x  ????:=================\n", u32UniqueId);
    socp_printf("????ID                 :%d\n", g_strSocpStat.sEncDstChan[u32RealId].u32ChanID);
    socp_printf("????????????           :%d\n", g_strSocpStat.sEncDstChan[u32RealId].u32SetStat);
    socp_printf("????buffer ????????    :0x%x\n", g_strSocpStat.sEncDstChan[u32RealId].sEncDstBuf.u32Start);
    socp_printf("????buffer ????????    :0x%x\n", g_strSocpStat.sEncDstChan[u32RealId].sEncDstBuf.u32End);
    socp_printf("????buffer ??????      :0x%x\n", g_strSocpStat.sEncDstChan[u32RealId].sEncDstBuf.u32Read);
    socp_printf("????buffer ??????      :0x%x\n", g_strSocpStat.sEncDstChan[u32RealId].sEncDstBuf.u32Write);
    socp_printf("????buffer ????        :0x%x\n", g_strSocpStat.sEncDstChan[u32RealId].sEncDstBuf.u32Length);

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??   : socp_show_enc_dst_chan_add
*
* ????????  : ??????????????????????????
*
* ????????  : ????ID
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
u32 socp_show_enc_dst_chan_add(u32 u32UniqueId)
{
    u32 u32RealChanID;
    u32 u32ChanType = 0;
    SOCP_DEBUG_ENCDST_S *sSocpAddDebugEncDst;

    u32ChanType = SOCP_REAL_CHAN_TYPE(u32UniqueId);
    SOCP_CHECK_CHAN_TYPE(u32ChanType, SOCP_CODER_DEST_CHAN);

    u32RealChanID = SOCP_REAL_CHAN_ID(u32UniqueId);
    sSocpAddDebugEncDst = &g_stSocpDebugInfo.sSocpDebugEncDst;

    socp_printf("================== ???????????? 0x%x  ??????????:=================\n", u32UniqueId);
    socp_printf("socp??????????????????????????????????                 : 0x%x\n",
           (s32)sSocpAddDebugEncDst->u32SocpRegEventEncDstCnt[u32RealChanID]);
    socp_printf("socp????????????????????????????????????????           : 0x%x\n",
           (s32)sSocpAddDebugEncDst->u32SocpRegReadCBEncDstCnt[u32RealChanID]);
    socp_printf("socp??????????????????????buffer ??????                : 0x%x\n",
           (s32)sSocpAddDebugEncDst->u32SocpGetReadBufEncDstEtrCnt[u32RealChanID]);
    socp_printf("socp??????????????????buffer??????????                 : 0x%x\n",
           (s32)sSocpAddDebugEncDst->u32SocpGetReadBufEncDstSucCnt[u32RealChanID]);
    socp_printf("socp??????????????????????buffer??????????             : 0x%x\n",
           (s32)sSocpAddDebugEncDst->u32socp_read_doneEncDstEtrCnt[u32RealChanID]);
    socp_printf("socp??????????????????buffer??????????????             : 0x%x\n",
           (s32)sSocpAddDebugEncDst->u32socp_read_doneEncDstSucCnt[u32RealChanID]);
    socp_printf("socp??????????????????buffer??????????????             : 0x%x\n",
           (s32)sSocpAddDebugEncDst->u32socp_read_doneEncDstFailCnt[u32RealChanID]);
    socp_printf("socp??????????????????buffer????????0 ??????????????   : 0x%x\n",
           (s32)sSocpAddDebugEncDst->u32socp_read_doneZeroEncDstCnt[u32RealChanID]);
    socp_printf("socp??????????????????buffer??????????0 ?????????????? : 0x%x\n",
           (s32)sSocpAddDebugEncDst->u32socp_read_doneValidEncDstCnt[u32RealChanID]);
    socp_printf("socpISR ??????????????????????????????????             : 0x%x\n",
           (s32)sSocpAddDebugEncDst->u32SocpEncDstIsrTrfIntCnt[u32RealChanID]);
    socp_printf("socp??????????????????????????????????????????????     : 0x%x\n",
           (s32)sSocpAddDebugEncDst->u32SocpEncDstTskTrfCbOriCnt[u32RealChanID]);
    socp_printf("socp??????????????????????????????????????????????     : 0x%x\n",
           (s32)sSocpAddDebugEncDst->u32SocpEncDstTskTrfCbCnt[u32RealChanID]);
    socp_printf("socpISR ??????????????????buf ????????????             : 0x%x\n",
           (s32)sSocpAddDebugEncDst->u32SocpEncDstIsrOvfIntCnt[u32RealChanID]);
    socp_printf("socp??????????????????????buf ????????????????????    : 0x%x\n",
           (s32)sSocpAddDebugEncDst->u32SocpEncDstTskOvfCbOriCnt[u32RealChanID]);
    socp_printf("socp????????????????buf ??????????????????????????    : 0x%x\n",
           (s32)sSocpAddDebugEncDst->u32SocpEncDstTskOvfCbCnt[u32RealChanID]);
    socp_printf("socpISR ??????????????????buf????????????????          : 0x%x\n",
           (s32)sSocpAddDebugEncDst->u32SocpEncDstIsrThresholdOvfIntCnt[u32RealChanID]);
    socp_printf("socp??????????????????????buf????????????????????????  : 0x%x\n",
           (s32)sSocpAddDebugEncDst->u32SocpEncDstTskThresholdOvfCbOriCnt[u32RealChanID]);
    socp_printf("socp????????????????buf??????????????????????????????  : 0x%x\n",
           (s32)sSocpAddDebugEncDst->u32SocpEncDstTskThresholdOvfCbCnt[u32RealChanID]);

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??   : socp_show_enc_dst_chan_all
*
* ????????  : ????????????????????
*
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
void socp_show_enc_dst_chan_all(void)
{
    u32 i;
    u32 u32UniqueId = 0;

    for (i = 0; i < SOCP_MAX_ENCDST_CHN; i++)
    {
        u32UniqueId = SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN, i);
        (void)socp_show_enc_dst_chan_cur(u32UniqueId);
        (void)socp_show_enc_dst_chan_add(u32UniqueId);
    }

    return;
}

/*****************************************************************************
* ?? ?? ??   : socp_show_dec_src_chan_cur
*
* ????????  : ??????????????????
*
* ????????  : ????ID
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
u32 socp_show_dec_src_chan_cur(u32 u32UniqueId)
{
    u32 u32RealId   = 0;
    u32 u32ChanType = 0;

    u32RealId   = SOCP_REAL_CHAN_ID(u32UniqueId);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32UniqueId);

    SOCP_CHECK_CHAN_TYPE(u32ChanType, SOCP_DECODER_SRC_CHAN);

    socp_printf("================== ?????????? 0x%x  ????:=================\n", u32UniqueId);
    socp_printf("????ID                 :%d\n", g_strSocpStat.sDecSrcChan[u32RealId].u32ChanID);
    socp_printf("????????????           :%d\n", g_strSocpStat.sDecSrcChan[u32RealId].u32SetStat);
    socp_printf("????????????           :%d\n", g_strSocpStat.sDecSrcChan[u32RealId].u32ChanEn);
    socp_printf("????????               :%d\n", g_strSocpStat.sDecSrcChan[u32RealId].eChnMode);
    socp_printf("????buffer ????????    :0x%x\n", g_strSocpStat.sDecSrcChan[u32RealId].sDecSrcBuf.u32Start);
    socp_printf("????buffer ????????    :0x%x\n", g_strSocpStat.sDecSrcChan[u32RealId].sDecSrcBuf.u32End);
    socp_printf("????buffer ??????      :0x%x\n", g_strSocpStat.sDecSrcChan[u32RealId].sDecSrcBuf.u32Read);
    socp_printf("????buffer ??????      :0x%x\n", g_strSocpStat.sDecSrcChan[u32RealId].sDecSrcBuf.u32Write);
    socp_printf("????buffer ????        :0x%x\n", g_strSocpStat.sDecSrcChan[u32RealId].sDecSrcBuf.u32Length);

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??   : socp_show_dec_src_chan_add
*
* ????????  : ????????????????????????
*
* ????????  : ????ID
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
u32 socp_show_dec_src_chan_add(u32 u32UniqueId)
{
    u32 u32RealChanID;
    SOCP_DEBUG_DECSRC_S *sSocpAddDebugDecSrc;
    u32 u32ChanType = 0;

    u32ChanType = SOCP_REAL_CHAN_TYPE(u32UniqueId);
    SOCP_CHECK_CHAN_TYPE(u32ChanType, SOCP_DECODER_SRC_CHAN);

    u32RealChanID = SOCP_REAL_CHAN_ID(u32UniqueId);
    sSocpAddDebugDecSrc = &g_stSocpDebugInfo.sSocpDebugDecSrc;

    socp_printf("================== ?????????? 0x%x  ??????????:=================\n", u32UniqueId);
    socp_printf("socp??????????????????????????                     : 0x%x\n",
           (s32)sSocpAddDebugDecSrc->u32SocpSoftResetDecSrcCnt[u32RealChanID]);
    socp_printf("socp????????????????????????                       : 0x%x\n",
           (s32)sSocpAddDebugDecSrc->u32SocpStartDecSrcCnt[u32RealChanID]);
    socp_printf("socp????????????????????????                       : 0x%x\n",
           (s32)sSocpAddDebugDecSrc->u32SocpStopDecSrcCnt[u32RealChanID]);
    socp_printf("socp????????????????????????????????               : 0x%x\n",
           (s32)sSocpAddDebugDecSrc->u32SocpRegEventDecSrcCnt[u32RealChanID]);
    socp_printf("socp????????????????????buffer??????               : 0x%x\n",
           (s32)sSocpAddDebugDecSrc->u32SocpGetWBufDecSrcEtrCnt[u32RealChanID]);
    socp_printf("socp????????????????buffer??????????               : 0x%x\n",
           (s32)sSocpAddDebugDecSrc->u32SocpGetWBufDecSrcSucCnt[u32RealChanID]);
    socp_printf("socp????????????????????buffer??????????           : 0x%x\n",
           (s32)sSocpAddDebugDecSrc->u32socp_write_doneDecSrcEtrCnt[u32RealChanID]);
    socp_printf("socp????????????????buffer??????????????           : 0x%x\n",
           (s32)sSocpAddDebugDecSrc->u32socp_write_doneDecSrcSucCnt[u32RealChanID]);
    socp_printf("socp????????????????buffer??????????????           : 0x%x\n",
           (s32)sSocpAddDebugDecSrc->u32socp_write_doneDecSrcFailCnt[u32RealChanID]);
    socp_printf("socpISR ????????????????????????????               : 0x%x\n",
           (s32)sSocpAddDebugDecSrc->u32SocpDecSrcIsrErrIntCnt[u32RealChanID]);
    socp_printf("socp????????????????????????????????????????       : 0x%x\n",
           (s32)sSocpAddDebugDecSrc->u32SocpDecSrcTskErrCbOriCnt[u32RealChanID]);
    socp_printf("socp????????????????????????????????????????       : 0x%x\n",
           (s32)sSocpAddDebugDecSrc->u32SocpDecSrcTskErrCbCnt[u32RealChanID]);
    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??   : socp_show_dec_src_chan_all
*
* ????????  : ??????????????????
*
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
void socp_show_dec_src_chan_all(void)
{
    u32 i;
    u32 u32UniqueId = 0;

    for (i = 0; i < SOCP_MAX_DECSRC_CHN; i++)
    {
        u32UniqueId = SOCP_CHAN_DEF(SOCP_DECODER_SRC_CHAN, i);
        (void)socp_show_dec_src_chan_cur(u32UniqueId);
        (void)socp_show_dec_src_chan_add(u32UniqueId);
    }

    return;
}

/*****************************************************************************
* ?? ?? ??   : socp_show_dec_dst_chan_cur
*
* ????????  : ????????????????????
*
* ????????  : ????ID
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
u32 socp_show_dec_dst_chan_cur(u32 u32UniqueId)
{
    u32 u32RealId   = 0;
    u32 u32ChanType = 0;

    u32RealId   = SOCP_REAL_CHAN_ID(u32UniqueId);
    u32ChanType = SOCP_REAL_CHAN_TYPE(u32UniqueId);

    SOCP_CHECK_CHAN_TYPE(u32ChanType, SOCP_DECODER_DEST_CHAN);

    socp_printf("================== ???????????? 0x%x  ????:=================\n", u32UniqueId);
    socp_printf("????ID                 :%d\n", g_strSocpStat.sDecDstChan[u32RealId].u32ChanID);
    socp_printf("????????????           :%d\n", g_strSocpStat.sDecDstChan[u32RealId].u32AllocStat);
    socp_printf("??????????????         :%d\n", g_strSocpStat.sDecDstChan[u32RealId].eDataType);
    socp_printf("????buffer ????????    :0x%x\n", g_strSocpStat.sDecDstChan[u32RealId].sDecDstBuf.u32Start);
    socp_printf("????buffer ????????    :0x%x\n", g_strSocpStat.sDecDstChan[u32RealId].sDecDstBuf.u32End);
    socp_printf("????buffer ??????      :0x%x\n", g_strSocpStat.sDecDstChan[u32RealId].sDecDstBuf.u32Read);
    socp_printf("????buffer ??????      :0x%x\n", g_strSocpStat.sDecDstChan[u32RealId].sDecDstBuf.u32Write);
    socp_printf("????buffer ????        :0x%x\n", g_strSocpStat.sDecDstChan[u32RealId].sDecDstBuf.u32Length);

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??   : socp_show_dec_dst_chan_add
*
* ????????  : ??????????????????????????
*
* ????????  : ????ID
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
u32 socp_show_dec_dst_chan_add(u32 u32UniqueId)
{
    u32 u32RealChanID;
    SOCP_DEBUG_DECDST_S *sSocpAddDebugDecDst;
    u32 u32ChanType = 0;

    u32ChanType = SOCP_REAL_CHAN_TYPE(u32UniqueId);
    SOCP_CHECK_CHAN_TYPE(u32ChanType, SOCP_DECODER_DEST_CHAN);

    u32RealChanID = SOCP_REAL_CHAN_ID(u32UniqueId);
    sSocpAddDebugDecDst = &g_stSocpDebugInfo.sSocpDebugDecDst;

    socp_printf("================== ???????????? 0x%x  ??????????:=================\n", u32UniqueId);
    socp_printf("socp??????????????????????????                         : 0x%x\n",
           (s32)sSocpAddDebugDecDst->u32SocpFreeDecDstCnt[u32RealChanID]);
    socp_printf("socp??????????????????????????????????                 : 0x%x\n",
           (s32)sSocpAddDebugDecDst->u32SocpRegEventDecDstCnt[u32RealChanID]);
    socp_printf("socp????????????????????????????????????????           : 0x%x\n",
           (s32)sSocpAddDebugDecDst->u32SocpRegReadCBDecDstCnt[u32RealChanID]);
    socp_printf("socp??????????????????????buffer??????                 : 0x%x\n",
           (s32)sSocpAddDebugDecDst->u32SocpGetReadBufDecDstEtrCnt[u32RealChanID]);
    socp_printf("socp??????????????????buffer??????????                 : 0x%x\n",
           (s32)sSocpAddDebugDecDst->u32SocpGetReadBufDecDstSucCnt[u32RealChanID]);
    socp_printf("socp??????????????????????buffer??????????             : 0x%x\n",
           (s32)sSocpAddDebugDecDst->u32socp_read_doneDecDstEtrCnt[u32RealChanID]);
    socp_printf("socp??????????????????buffer??????????????             : 0x%x\n",
           (s32)sSocpAddDebugDecDst->u32socp_read_doneDecDstSucCnt[u32RealChanID]);
    socp_printf("socp??????????????????buffer??????????????             : 0x%x\n",
           (s32)sSocpAddDebugDecDst->u32socp_read_doneDecDstFailCnt[u32RealChanID]);
    socp_printf("socp??????????????????buffer????????0 ??????????????   : 0x%x\n",
           (s32)sSocpAddDebugDecDst->u32socp_read_doneZeroDecDstCnt[u32RealChanID]);
    socp_printf("socp??????????????????buffer??????????0 ?????????????? : 0x%x\n",
           (s32)sSocpAddDebugDecDst->u32socp_read_doneValidDecDstCnt[u32RealChanID]);
    socp_printf("socpISR ??????????????????????????????????             : 0x%x\n",
           (s32)sSocpAddDebugDecDst->u32SocpDecDstIsrTrfIntCnt[u32RealChanID]);
    socp_printf("socp?????? ??????????????????????????????????????????  : 0x%x\n",
           (s32)sSocpAddDebugDecDst->u32SocpDecDstTskTrfCbOriCnt[u32RealChanID]);
    socp_printf("socp??????????????????????????????????????????????     : 0x%x\n",
           (s32)sSocpAddDebugDecDst->u32SocpDecDstTskTrfCbCnt[u32RealChanID]);
    socp_printf("socpISR ??????????????????buf ????????????             : 0x%x\n",
           (s32)sSocpAddDebugDecDst->u32SocpDecDstIsrOvfIntCnt[u32RealChanID]);
    socp_printf("socp?????? ????????????????buf ????????????????????    : 0x%x\n",
           (s32)sSocpAddDebugDecDst->u32SocpDecDstTskOvfCbOriCnt[u32RealChanID]);
    socp_printf("socp????????????????buf ??????????????????????????     : 0x%x\n",
           (s32)sSocpAddDebugDecDst->u32SocpDecDstTskOvfCbCnt[u32RealChanID]);

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??   : socp_show_dec_dst_chan_all
*
* ????????  : ????????????????????
*
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
void socp_show_dec_dst_chan_all(void)
{
    u32 i;
    u32 u32UniqueId = 0;

    for (i = 0; i < SOCP_MAX_DECDST_CHN; i++)
    {
        u32UniqueId = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, i);
        (void)socp_show_dec_dst_chan_cur(u32UniqueId);
        (void)socp_show_dec_dst_chan_add(u32UniqueId);
    }

    return;
}

/*****************************************************************************
* ?? ?? ??   : socp_debug_cnt_show
*
* ????????  : ????debug ????????
*
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??   : ??
*****************************************************************************/
void socp_debug_cnt_show(void)
{
    socp_show_debug_gbl();
    socp_show_enc_src_chan_all();
    socp_show_enc_dst_chan_all();
    socp_show_dec_src_chan_all();
    socp_show_dec_dst_chan_all();
}

#define MALLOC_MAX_SIZE     0x100000
#define MALLOC_MAX_INDEX    8           /*page_size ??4K*/
#define SOCP_PAGE_SIZE      0x1000

//__inline
s32 socp_get_index(u32 u32Size,u32 *index)
{
    u32 i = 0;
    if(u32Size > MALLOC_MAX_SIZE)
    {
        return BSP_ERROR;
    }
    for(i=0;i<=MALLOC_MAX_INDEX;i++)
    {
        if(u32Size <= (u32)(SOCP_PAGE_SIZE * (1<<i)))
        {
            *index = i;
            break;
        }
    }
    return BSP_OK;
}

void* socp_malloc(u32 u32Size)
{
    u8 *pItem= NULL;
    u32 index = 0;

    if(BSP_OK != socp_get_index(u32Size,&index))
    {
        return BSP_NULL;
    }

    index = 4;
    /* ???????? */
    pItem = (u8*)__get_free_pages(GFP_KERNEL,index);
    if(!pItem)
    {
        socp_printf("%s: malloc failed\n", __FUNCTION__);
        return BSP_NULL;
    }

    return (void*)SOCP_VIRT_PHY(pItem);
}

s32 socp_free(void* pMem)
{
    u32 *pItem;

    pItem = SOCP_PHY_VIRT(pMem);

    free_pages((unsigned long)pItem,4);
    return BSP_OK;
}

/* ?????????? begin */
/* ?????????????????? */
void BSP_SOCP_DrxRestoreRegAppOnly(void)
{
    u32 i= 0;

    for(i=0;i<SOCP_MAX_ENCDST_CHN;i++)
    {
	    SOCP_REG_READ(SOCP_REG_ENCDEST_BUFRPTR(i),g_strSocpStat.sEncDstChan[i].sEncDstBuf.u32Read);
	    SOCP_REG_READ(SOCP_REG_ENCDEST_BUFWPTR(i),g_strSocpStat.sEncDstChan[i].sEncDstBuf.u32Write);
    }

    for(i=0;i<SOCP_MAX_DECDST_CHN;i++)
    {
    	SOCP_REG_READ(SOCP_REG_DECDEST_BUFRPTR(i),g_strSocpStat.sDecDstChan[i].sDecDstBuf.u32Read);
	    SOCP_REG_READ(SOCP_REG_DECDEST_BUFWPTR(i),g_strSocpStat.sDecDstChan[i].sDecDstBuf.u32Write);
    }

    for(i=0;i<SOCP_MAX_ENCSRC_CHN;i++)
    {
        SOCP_REG_READ(SOCP_REG_ENCSRC_BUFRPTR(i),  g_strSocpStat.sEncSrcChan[i].sEncSrcBuf.u32Read);
	    SOCP_REG_READ(SOCP_REG_ENCSRC_BUFWPTR(i),g_strSocpStat.sEncSrcChan[i].sEncSrcBuf.u32Write);

        SOCP_REG_READ(SOCP_REG_ENCSRC_RDQRPTR(i),  g_strSocpStat.sEncSrcChan[i].sRdBuf.u32Read);
	    SOCP_REG_READ(SOCP_REG_ENCSRC_RDQWPTR(i),g_strSocpStat.sEncSrcChan[i].sRdBuf.u32Write);
    }

    for(i=0;i<SOCP_MAX_DECSRC_CHN;i++)
    {
        SOCP_REG_READ(SOCP_REG_DECSRC_BUFRPTR(i),  g_strSocpStat.sDecSrcChan[i].sDecSrcBuf.u32Read);
	    SOCP_REG_READ(SOCP_REG_DECSRC_BUFWPTR(i),g_strSocpStat.sDecSrcChan[i].sDecSrcBuf.u32Write);
    }
}

/*****************************************************************************
* ?? ?? ??      : SOCP_CanSleep
*
* ????????  : ??????????
*
*
* ????????  : BSP_OK  ??????????????????
*             ??????????????????????????
*
* ?? ?? ??      : ??
*****************************************************************************/
u32 BSP_SOCP_CanSleep(void)
{
	u32 i;
	u32 u32EncBusy, u32DecBusy;
	u32 u32BufAddr, u32WritePtr, u32ReadPtr;
	u32 u32IntFlag;


	//????????????????????????????
    //??????????????????A??:0--3;C??: 4--8
    for(i = 0;i<SOCP_MAX_ENCSRC_CHN;i++)
    {
        /* C???????????? */
        if((i >= SOCP_CCORE_ENCSRC_CHN_BASE) && (i <= (SOCP_CCORE_ENCSRC_CHN_BASE + SOCP_CCORE_ENCSRC_CHN_NUM)))
        {
            continue;
        }
        SOCP_REG_READ(SOCP_REG_ENCSRC_BUFADDR(i), u32BufAddr);
        /*lint -save -e774*/
        if(0!=u32BufAddr)
        /*lint -restore +e774*/
        {
            SOCP_REG_READ(SOCP_REG_ENCSRC_BUFWPTR(i), u32WritePtr);
            SOCP_REG_READ(SOCP_REG_ENCSRC_BUFRPTR(i), u32ReadPtr);
            /*lint -save -e774*/
            if(u32WritePtr != u32ReadPtr)
            /*lint -restore +e774*/
            {
                //BSP_TRACE(BSP_LOG_LEVEL_ERROR, BSP_MODU_SOCP, "SOCP_PwDown: enc src %d is busy: !\n", i);
                    return 1;
            }
        }
    }

    //????????????0--6
    for(i = 0;i<SOCP_MAX_ENCDST_CHN;i++)
    {
        SOCP_REG_READ(SOCP_REG_ENCDEST_BUFADDR(i), u32BufAddr);
        /*lint -save -e774*/
        if(0!=u32BufAddr)
        /*lint -restore +e774*/
        {
            SOCP_REG_READ(SOCP_REG_ENCDEST_BUFWPTR(i), u32WritePtr);
            SOCP_REG_READ(SOCP_REG_ENCDEST_BUFRPTR(i), u32ReadPtr);
            /*lint -save -e774*/
            if(u32WritePtr != u32ReadPtr)
            /*lint -restore +e774*/
            {
                //BSP_TRACE(BSP_LOG_LEVEL_ERROR, BSP_MODU_SOCP, "SOCP_PwDown: enc dst %d is busy: !\n", i);
                    return 3;
            }
        }
    }
    //??????????0--3
    for(i = 0;i<SOCP_MAX_DECSRC_CHN;i++)
    {
        SOCP_REG_READ(SOCP_REG_DECSRC_BUFADDR(i), u32BufAddr);
        /*lint -save -e774*/
        if(0!=u32BufAddr)
        /*lint -restore +e774*/
        {
            SOCP_REG_READ(SOCP_REG_DECSRC_BUFWPTR(i), u32WritePtr);
            SOCP_REG_READ(SOCP_REG_DECSRC_BUFRPTR(i), u32ReadPtr);
            /*lint -save -e774*/
            if(u32WritePtr != u32ReadPtr)
            /*lint -restore +e774*/
            {
                //BSP_TRACE(BSP_LOG_LEVEL_ERROR, BSP_MODU_SOCP, "SOCP_PwDown: dec src %d is busy: !\n", i);
                return 4;
            }
        }
    }

    /* ???????????? */
    for(i = 0;i<SOCP_MAX_DECDST_CHN;i++)
    {
        SOCP_REG_READ(SOCP_REG_DECDEST_BUFADDR(i), u32BufAddr);
        /*lint -save -e774*/
        if(0!=u32BufAddr)
        /*lint -restore +e774*/
        {
            SOCP_REG_READ(SOCP_REG_DECDEST_BUFWPTR(i), u32WritePtr);
            SOCP_REG_READ(SOCP_REG_DECDEST_BUFRPTR(i), u32ReadPtr);
            /*lint -save -e774*/
            if(u32WritePtr != u32ReadPtr)
            /*lint -restore +e774*/
            {
                //BSP_TRACE(BSP_LOG_LEVEL_ERROR, BSP_MODU_SOCP, "SOCP_PwDown: dec dst %d is busy: !\n", i);
                return 5;
            }
        }
    }

    //????????????
    SOCP_REG_READ(SOCP_REG_ENCSTAT, u32EncBusy);
    SOCP_REG_READ(SOCP_REG_DECSTAT, u32DecBusy);

    /*lint -save -e774*/
    if((0 !=u32EncBusy) || (0 !=u32DecBusy) )
    /*lint -restore +e774*/
    {
        //BSP_TRACE(BSP_LOG_LEVEL_ERROR, BSP_MODU_SOCP, "SOCP_PwDown: chan is busy,enc is : 0x%x, dec is 0x%x!\n", u32EncBusy, u32DecBusy);
        return 6;
    }

    SOCP_REG_READ(SOCP_REG_GBL_INTSTAT, u32IntFlag);
    /*lint -save -e774*/
    if((0 != u32IntFlag ))
    /*lint -restore +e774*/
    {
        //BSP_TRACE(BSP_LOG_LEVEL_ERROR, BSP_MODU_SOCP, "SOCP_PwDown: chan is busy,enc is : 0x%x, dec is 0x%x!\n", u32EncBusy, u32DecBusy);
        return 7;
    }

    return BSP_OK;
}
/* ?????????? end */

/*****************************************************************************
* ?? ?? ??  : bsp_socp_get_state
*
* ????????  : ????SOCP????
*
* ?? ?? ??  : SOCP_IDLE    ????
*             SOCP_BUSY    ????
*****************************************************************************/
SOCP_STATE_ENUM_UINT32 bsp_socp_get_state(void)
{
    u32 u32EncChanState;
    u32 u32DecChanState;

    SOCP_REG_READ(SOCP_REG_ENCSTAT, u32EncChanState);
    SOCP_REG_READ(SOCP_REG_DECSTAT, u32DecChanState);
    if(u32EncChanState != 0 || u32DecChanState != 0)
    {
        return SOCP_BUSY;
    }

    return SOCP_IDLE;
}

/* log2.0 2014-03-19 Begin:*/
/*****************************************************************************
* ?? ?? ??  : bsp_socp_get_log_cfg
*
* ????????  : ????LOG2.0 SOCP??????????????????
*
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??  : SOCP_ENC_DST_BUF_LOG_CFG_STRU????
*****************************************************************************/
struct socp_enc_dst_log_cfg * bsp_socp_get_log_cfg(void)
{
    return &g_stEncDstBufLogConfig;
}

/*****************************************************************************
* ?? ?? ??  : BSP_SOCP_SetLogCfg
*
* ????????  : LOG2.0 SOCP??????????????
*
* ????????  : struct socp_enc_dst_log_cfg * cfg
*
* ????????  : ??
*
* ?? ?? ??  : BSP_S32 BSP_OK:???? BSP_ERROR:????
*****************************************************************************/
s32 bsp_socp_set_log_cfg(struct socp_enc_dst_log_cfg * cfg)
{
    return BSP_OK;
}

void set_flag(u32 flag)
{
    if(flag <= SOCP_DST_CHAN_DTS)
    {
        g_stEncDstBufLogConfig.logOnFlag = flag;
    }
}
/*****************************************************************************
* ?? ?? ??  : socp_is_encdst_chan_empty
*
* ????????  : SOCP??????????????????????
*
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??  : u32 0:?????? ??0:????????????
*****************************************************************************/
u32 socp_is_encdst_chan_empty(void)
{
    u32 chanSet = 0;
    u32 i;
    u32 u32ReadPtr;
    u32 u32WritePtr;

    /* ???????????????????????????? */
    for(i = 0; i < SOCP_MAX_ENCDST_CHN; i++)
    {
        SOCP_REG_READ(SOCP_REG_ENCDEST_BUFWPTR(i), u32WritePtr);
        SOCP_REG_READ(SOCP_REG_ENCDEST_BUFRPTR(i), u32ReadPtr);
        if(u32WritePtr != u32ReadPtr)
        {
            chanSet = chanSet | (1 << i);
        }
    }

    return chanSet;
}

/* log2.0 2014-03-19 End*/

/*lint -save -e102 -e10 -e2 -e40 -e533 -e31 -e830 -e522 -e718 -e746 -e702 -e565   -e64 -e23 -e63 -e26 -e578 -e132*/
extern unsigned long simple_strtoul(const char *cp, char **endp, unsigned int base);

/*****************************************************************************
* ?? ?? ??  : socp_logbuffer_sizeparse
*
* ????????  : ????????????????CMD LINE????BUFFER????????????????
*
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??  : ??
*****************************************************************************/
static int __init socp_logbuffer_sizeparse(char *pucChar)
{
    u32      ulBufferSize;

    /* Buffer????????Byte????????????????????200M????????1M */
    ulBufferSize = (uintptr_t)simple_strtoul(pucChar, NULL, 0);

    if ((ulBufferSize > (50 *1024 *1024))
      || (ulBufferSize < (1 *1024 *1024)))
    {
        return -1;
    }

    /* ????????ulBufferSize??????8????????,????????????8?????????????????? */
    if (0 != (ulBufferSize % 8))
    {
        return -1;
    }

    g_stEncDstBufLogConfig.BufferSize = ulBufferSize;
    g_stEncDstBufLogConfig.logOnFlag  = SOCP_DST_CHAN_DELAY;

    printk(KERN_ERR"[%s]:BufferSize   0x%x\n",__FUNCTION__,ulBufferSize);

    return 0;
}

early_param("mdmlogsize", socp_logbuffer_sizeparse);

/*****************************************************************************
* ?? ?? ??  : socp_logbuffer_timeparse
*
* ????????  : ????????????????CMD LINE????TIMEOUT????????????????
*
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??  : ??
*****************************************************************************/
static int __init socp_logbuffer_timeparse(char *pucChar)
{
    u32      ulTimeout;

    /* ??????????????????????????????????????????????1??????????20???? */
    ulTimeout = (uintptr_t)simple_strtoul(pucChar, NULL,0);

    if (1200 < ulTimeout)
    {
        ulTimeout = 1200;
    }

    ulTimeout *= 1000;

    g_stEncDstBufLogConfig.overTime = ulTimeout;
    g_stEncDstBufLogConfig.ulCurTimeout = ulTimeout;

    printk(KERN_ERR"[%s]:CurTimeout/overTime   0x%x\n",__FUNCTION__,ulTimeout);

    return 0;
}

early_param("mdmlogtime", socp_logbuffer_timeparse);


/*****************************************************************************
* ?? ?? ??  : socp_logbuffer_addrparse
*
* ????????  : ????????????????CMD LINE??????????????????????
*
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??  : ??
*****************************************************************************/
static int __init socp_logbuffer_addrparse(char *pucChar)
{
    unsigned long  ulBaseAddr;

    ulBaseAddr = simple_strtoul(pucChar, NULL, 0);

    /* ??????????32????????????????8?????????? */
    if ((0 != (ulBaseAddr % 8))
        || (0 == ulBaseAddr))
    {
        g_stEncDstBufLogConfig.logOnFlag = SOCP_DST_CHAN_DELAY;

        return -1;
    }

    g_stEncDstBufLogConfig.ulPhyBufferAddr = ulBaseAddr;

    printk(KERN_ERR"[%s]:ulPhyBufferAddr   0x%lx\n",__FUNCTION__,ulBaseAddr);

    return 0;
}
early_param("mdmlogbase", socp_logbuffer_addrparse);

/*****************************************************************************
* ?? ?? ??  : socp_logbuffer_cfgshow
*
* ????????  : ??????????????????????
*
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??  : ??
*****************************************************************************/
void socp_logbuffer_cfgshow(void)
{
    /*lint -e534*/
    socp_printf("socp_logbuffer_cfgshow: overTime           %d\n", g_stEncDstBufLogConfig.overTime);
    socp_printf("socp_logbuffer_cfgshow: Current Time Out   %d\n", g_stEncDstBufLogConfig.ulCurTimeout);
    socp_printf("socp_logbuffer_cfgshow: BufferSize         %d\n", g_stEncDstBufLogConfig.BufferSize);
    socp_printf("socp_logbuffer_cfgshow: logOnFlag          %d\n", g_stEncDstBufLogConfig.logOnFlag);
    socp_printf("socp_logbuffer_cfgshow: PhyBufferAddr      0x%lx\n", g_stEncDstBufLogConfig.ulPhyBufferAddr);
    /*lint +e534*/

    return;
}


/*****************************************************************************
 ?? ?? ??  : socp_logbuffer_memremap
 ????????  : ????LOG??????????????????SOCP??????????????????VCOM????????????????????????
             ????????????????????COMM
 ????????  : phys_addr:????REMAP??????????
             size:     ????REMAP??????????
 ????????  : ??
 ?? ?? ??  : REMAP????????????

 ????????      :
  1.??    ??   : 2014??8??11??
    ??    ??   : h59254
    ????????   : V8R1 LOG????????????
*****************************************************************************/
void *socp_logbuffer_memremap(unsigned long phys_addr, size_t size)
{
    int i;
    u8* vaddr;
    int npages = PAGE_ALIGN((phys_addr & (PAGE_SIZE - 1)) + size) >> PAGE_SHIFT;
    unsigned long offset = phys_addr & (PAGE_SIZE - 1);
    struct page **pages;

    pages = vmalloc(sizeof(struct page *) * npages);
    if (!pages)
    {
        return NULL;
    }

    pages[0] = phys_to_page(phys_addr);

    for (i = 0; i < npages - 1 ; i++)
    {
        pages[i + 1] = pages[i] + 1;
    }
    
    vaddr = (u8*)vmap(pages, npages, VM_MAP, pgprot_writecombine(PAGE_KERNEL));

    if ( NULL != vaddr )

    {
        vaddr += offset;
    }

    vfree(pages);

    return (void *)vaddr;
}

/*****************************************************************************
* ?? ?? ??  : socp_logbuffer_bufferinit
*
* ????????  : ??????????????????LOG??????????????????????????
*
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??  : ??
*****************************************************************************/
int socp_logbuffer_bufferinit(void)
{
    if (SOCP_DST_CHAN_DELAY != g_stEncDstBufLogConfig.logOnFlag)
    {
        socp_printf("[%s]:Log Delay Ind Func Not Open!\n",__FUNCTION__);
        return 0;
    }

    if (0 == g_stEncDstBufLogConfig.ulPhyBufferAddr)
    {
        g_stEncDstBufLogConfig.logOnFlag = SOCP_DST_CHAN_NOT_CFG;

        return 0;
    }

    g_stEncDstBufLogConfig.pVirBuffer = socp_logbuffer_memremap(g_stEncDstBufLogConfig.ulPhyBufferAddr,
                                                     g_stEncDstBufLogConfig.BufferSize);


    if (NULL == g_stEncDstBufLogConfig.pVirBuffer)
    {
        g_stEncDstBufLogConfig.logOnFlag = SOCP_DST_CHAN_NOT_CFG;
    }

    return 0;
}

arch_initcall(socp_logbuffer_bufferinit);

/*****************************************************************************
* ?? ?? ??  : socp_get_dst_chan_buffer
* ????????  : ????????????????buffer??????OM log????
* ????????  : buffer size
* ????????  : ??
* ?? ?? ??  : ??
*****************************************************************************/
void socp_get_dst_chan_buffer(u32 size)
{
    dma_addr_t      ulAddress = 0;
    u8              *pucBuf;

    struct device   dev;

    Socp_Memset(&dev, 0, sizeof(dev));

    pucBuf = dma_alloc_coherent(&dev, size, &ulAddress, GFP_KERNEL);

    socp_printf("dma_alloc_coherent ulAddress 0x%lx, pucBuf 0x%p.\n", ulAddress, pucBuf);

    g_stEncDstBufLogConfig.ulPhyBufferAddr  = (unsigned long)ulAddress;
    g_stEncDstBufLogConfig.pVirBuffer       = pucBuf;
    g_stEncDstBufLogConfig.ulCurTimeout     = 10; /* ?????????? */

    g_stEncDstBufLogConfig.BufferSize = size;
    g_stEncDstBufLogConfig.logOnFlag  = SOCP_DST_CHAN_DTS;
}


/*****************************************************************************
* ?? ?? ??  : socp_show_vote_info
* ????????  : ????????????
* ????????  : ??
* ????????  : ??
* ?? ?? ??  : ??
*****************************************************************************/
void socp_show_vote_info(void)
{
    u8 * power_flag;

    socp_printf("************socp vote info************\n");
    socp_printf("GU DSP      : %-5s  0x%x\n", (g_stVoteInfo[0].vote_type == 0) ? "SLEEP" : "WAKE", g_stVoteInfo[0].vote_time);
    socp_printf("DIAG APP    : %-5s  0x%x\n", (g_stVoteInfo[1].vote_type == 0) ? "SLEEP" : "WAKE", g_stVoteInfo[1].vote_time);
    socp_printf("DIAG COMM   : %-5s  0x%x\n", (g_stVoteInfo[2].vote_type == 0) ? "SLEEP" : "WAKE", g_stVoteInfo[2].vote_time);
    socp_printf("TL DSP      : %-5s  0x%x\n", (g_stVoteInfo[3].vote_type == 0) ? "SLEEP" : "WAKE", g_stVoteInfo[3].vote_time);
    socp_printf("SOCP REG    : %-5s  0x%x\n", (g_stVoteInfo[4].vote_type == 0) ? "SLEEP" : "WAKE", g_stVoteInfo[4].vote_time);
    socp_printf("************socp flag info************\n");
    socp_printf("SOCP ON DEMAND FEATUR: %s\n", (g_ulSocpOnDemand == BSP_TRUE) ? "ON" : "OFF");
    switch(g_ulSocpPowerState)
    {
        case SOCP_POWER_ON:
            power_flag = "POWER ON";
            break;

        case SOCP_POWER_OFF_REQ:
            power_flag = "POWER OFF REQ";
            break;

        case SOCP_POWER_OFF:
            power_flag = "POWER OFF";
            break;

        default:
            power_flag = "UNKNOWN";
            break;
    }
    socp_printf("SOCP POWER ON STATE  : %s\n", power_flag);
}

/*****************************************************************************
* ?? ?? ??  : socp_can_sleep
* ????????  : SOCP????????????????????????????????, ????????????????????
* ????????  : ??
* ????????  : ??
* ?? ?? ??  : BSP_S32 0 --- ??????????0xFFFFFFFF --- ??????????
*****************************************************************************/
s32 socp_can_sleep(void)
{
    u32 i;

    /* ?????????????????????????? */
    for(i=0; i<SOCP_VOTE_ID_BUTT; i++)
    {
        if(SOCP_VOTE_FOR_WAKE == g_stVoteInfo[i].vote_type)
        {
            return BSP_ERROR;
        }
    }

    /* ???????????? */
    if(BSP_OK != socp_chan_is_idle())
    {
        return BSP_ERROR;
    }

    return BSP_OK;
}

/*****************************************************************************
* ?? ?? ??  : bsp_socp_vote
* ????????  : SOCP??????????????????????????SOCP????????????????????A??????
* ????????  : id --- ????????ID??type --- ????????
* ????????  : ??
* ?? ?? ??  : BSP_S32 0 --- ??????????0xFFFFFFFF --- ????????
*****************************************************************************/
BSP_S32 bsp_socp_vote(SOCP_VOTE_ID_ENUM_U32 id, SOCP_VOTE_TYPE_ENUM_U32 type)
{
    /* ?????????????????? */
    SOCP_CHECK_INIT();

    if(id >= SOCP_VOTE_ID_BUTT || type >= SOCP_VOTE_TYPE_BUTT)
    {
        socp_printf("%s invalid param id 0x%x type 0x%x\n", __FUNCTION__, id, type);
        return BSP_ERROR;
    }

    g_stVoteInfo[id].vote_type = type;
    g_stVoteInfo[id].vote_time = bsp_get_slice_value();

    socp_printf("%s: id 0x%x vote 0x%x\n", __FUNCTION__, id, type);
    socp_show_vote_info();

    if(g_ulSocpOnDemand == BSP_FALSE)
    {
        socp_printf("%s: socp on demand feature off\n", __FUNCTION__);
        return BSP_OK;
    }

    /* ??????????SOCP???? */
    if(type == SOCP_VOTE_FOR_WAKE)
    {
        /*????regulator????????*/
        if(0 != down_interruptible(&g_stSocpPowerSem))
        {
            socp_printf("%s:socp vote wake interruptible\n", __FUNCTION__);
        }

        if(g_ulSocpPowerState == SOCP_POWER_ON)
        {
            up(&g_stSocpPowerSem);
            return BSP_OK;
        }

        /* read done?????????????????????????? */
        if(g_ulSocpPowerState == SOCP_POWER_OFF_REQ)
        {
            g_ulSocpPowerState = SOCP_POWER_ON;
            up(&g_stSocpPowerSem);
            return BSP_OK;
        }

        if(regulator_bulk_enable(1, &(g_stSocpVcc->socp_vcc)))
        {
            socp_printf("[%s]:fetal error, regulator enable fail\n", __FUNCTION__);
            up(&g_stSocpPowerSem);
            return BSP_ERROR;
        }
        else
        {
            g_ulSocpPowerState = SOCP_POWER_ON;
            socp_printf("%s: socp goto power on\n", __FUNCTION__);
        }

        /* ?????????????????????? */
        SOCP_REG_WRITE(SOCP_REG_ENC_MASK0, g_ul_encdst_tran_int_mask);
        SOCP_REG_WRITE(SOCP_REG_ENC_MASK2, g_ul_encdst_over_int_mask);
        SOCP_REG_WRITE(SOCP_REG_DEC_CORE0MASK0, g_ul_decdst_tran_int_mask);

        up(&g_stSocpPowerSem);
        return BSP_OK;
    }

    /* ???????????????????????? */
    if(0 != down_interruptible(&g_stSocpPowerSem))
    {
        socp_printf("%s:socp vote sleep interruptible\n", __FUNCTION__);
    }

    if(g_ulSocpPowerState == SOCP_POWER_OFF)
    {
        up(&g_stSocpPowerSem);
        return BSP_OK;
    }

    if(BSP_OK == socp_can_sleep())
    {
        /* ?????????????????????????? */
        SOCP_REG_READ(SOCP_REG_ENC_MASK0, g_ul_encdst_tran_int_mask);
        SOCP_REG_READ(SOCP_REG_ENC_MASK2, g_ul_encdst_over_int_mask);
        SOCP_REG_READ(SOCP_REG_DEC_CORE0MASK0, g_ul_decdst_tran_int_mask);
        /* ???????? */
        SOCP_REG_SETBITS(SOCP_REG_ENC_MASK0, 0, 7, 0x7f);
        SOCP_REG_SETBITS(SOCP_REG_ENC_MASK2, 0, 7, 0x7f);
        SOCP_REG_SETBITS(SOCP_REG_ENC_MASK2, 16, 7, 0x7f);
        SOCP_REG_SETBITS(SOCP_REG_DEC_CORE0MASK0, 0, 16, 0xffff);
        /* regulator disalbe??????????enable??????????????????enable???????????? */
        if(regulator_bulk_disable(1, &(g_stSocpVcc->socp_vcc)))
        {
            socp_printf("[%s]:fetal error, regulator disable fail\n", __FUNCTION__);
        }
        else
        {
            g_ulSocpPowerState = SOCP_POWER_OFF;
            socp_printf("%s: socp goto power off\n", __FUNCTION__);
        }
    }
    up(&g_stSocpPowerSem);

    return BSP_OK;
}

static int socp_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	int ret = 0;
    SOCP_ON_DEMAND_STRU socp_config;

    /* LPM3??????SOCP???????????? */
    g_ulSocpPowerState = BSP_TRUE;

	g_stSocpVcc = kzalloc(sizeof(*g_stSocpVcc), GFP_KERNEL);
	if (!g_stSocpVcc) {
		dev_err(dev, "cannot allocate modem_socp device info\n");
		ret = -ENOMEM;
		return ret;
	}

	g_stSocpVcc->dev = &(pdev->dev);
	platform_set_drvdata(pdev, g_stSocpVcc);
    g_stSocpVcc->socp_vcc.supply = "socp";

    sema_init(&g_stSocpPowerSem, 1);
    /* ????NV???? */
    if(BSP_OK != bsp_nvm_read(NV_ID_DRV_SOCP_ON_DEMAND, (u8*)&socp_config, sizeof(SOCP_ON_DEMAND_STRU)))
    {
        socp_printf("%s:read nv 0x%x fail\n", __FUNCTION__, NV_ID_DRV_SOCP_ON_DEMAND);
        g_ulSocpOnDemand = BSP_FALSE;
    }
    else
    {
        if(socp_config.en_flag == 1)
        {
            g_ulSocpOnDemand = BSP_TRUE;
        }
        else
        {
            g_ulSocpOnDemand = BSP_FALSE;
        }
    }

    ret = devm_regulator_bulk_get(g_stSocpVcc->dev, 1, &(g_stSocpVcc->socp_vcc));
    if(ret)
    {
        socp_printf("%s: fetal error, get regulator fail\n", __FUNCTION__);
        return ret;
    }

    if(regulator_bulk_enable(1, &(g_stSocpVcc->socp_vcc)))
    {
        socp_printf("[%s]:fetal error, regulator enable fail\n", __FUNCTION__);
        return BSP_ERROR;
    }

    g_ulSocpPowerState = SOCP_POWER_ON;

    (void)socp_init();

	return BSP_OK;
}

static const struct of_device_id socp_dev_of_match[] = {
        {.compatible = "hisilicon,socp_balong_app"},
};

static struct platform_driver socp_driver = {
        .driver = {
                   .name = "modem_socp",
                   .owner = THIS_MODULE,
                   .of_match_table = socp_dev_of_match,
        },
        .probe = socp_probe,
};

static int __init socp_drvier_init(void)
{
	return platform_driver_register(&socp_driver);
}


/*lint -save -e19*/
module_init(socp_drvier_init);
/*lint -restore*/




/*****************************************************************************
* ?? ?? ??  : socp_set_clk_autodiv_enable
* ????????  : ????clk????clk_disable_unprepare??bypass??0??????????????
* ????????  : ??
* ????????  : ??
* ?? ?? ??  : ??
* ??    ??  :
              clk_prepare_enable ?????? clk_disable_unprepare ????????????????
              clk????????????????????????????????
              ?????????? clk_prepare_enable ???????? clk_disable_unprepare ????
*****************************************************************************/
void bsp_socp_set_clk_autodiv_enable(void)
{
}


/*****************************************************************************
* ?? ?? ??  : socp_set_clk_autodiv_disable
* ????????  : ????clk????clk_prepare_enable??bypass??1??????????????
* ????????  : ??
* ????????  : ??
* ?? ?? ??  : ??
* ??    ??  :
              clk_prepare_enable ?????? clk_disable_unprepare ????????????????
              clk????????????????????????????????
              ?????????? clk_prepare_enable ???????? clk_disable_unprepare ????
*****************************************************************************/
void bsp_socp_set_clk_autodiv_disable(void)
{
}

/*****************************************************************************
* ?? ?? ??  : bsp_socp_set_decode_timeout_register
*
* ????????  :??????????????????????????????
                            1 - ????????????INT_TIMEOUT(0x024)??????????????DEC_INT_TIMEOUT(0x20);
                            0 - ????????????????INT_TIMEOUT(0x024)

*
* ?? ?? ??  :  ??
*
*
*****************************************************************************/


EXPORT_SYMBOL(socp_reset_dec_chan);
EXPORT_SYMBOL(socp_soft_free_encdst_chan);
EXPORT_SYMBOL(socp_soft_free_decsrc_chan);

EXPORT_SYMBOL(bsp_socp_clean_encsrc_chan);
EXPORT_SYMBOL(socp_init);
EXPORT_SYMBOL(bsp_socp_coder_set_src_chan);
EXPORT_SYMBOL(bsp_socp_decoder_set_dest_chan);
EXPORT_SYMBOL(bsp_socp_coder_set_dest_chan_attr);
EXPORT_SYMBOL(bsp_socp_decoder_get_err_cnt);
EXPORT_SYMBOL(bsp_socp_decoder_set_src_chan_attr);
EXPORT_SYMBOL(bsp_socp_set_timeout);
EXPORT_SYMBOL(bsp_socp_set_dec_pkt_lgth);
EXPORT_SYMBOL(bsp_socp_set_debug);
EXPORT_SYMBOL(bsp_socp_free_channel);
EXPORT_SYMBOL(bsp_socp_chan_soft_reset);
EXPORT_SYMBOL(bsp_socp_start);
EXPORT_SYMBOL(bsp_socp_stop);
EXPORT_SYMBOL(bsp_socp_register_event_cb);
EXPORT_SYMBOL(bsp_socp_get_write_buff);
EXPORT_SYMBOL(bsp_socp_write_done);
EXPORT_SYMBOL(bsp_socp_register_rd_cb);
EXPORT_SYMBOL(bsp_socp_get_rd_buffer);
EXPORT_SYMBOL(bsp_socp_read_rd_done);
EXPORT_SYMBOL(bsp_socp_register_read_cb);
EXPORT_SYMBOL(bsp_socp_get_read_buff);
EXPORT_SYMBOL(bsp_socp_read_data_done);
EXPORT_SYMBOL(bsp_socp_set_bbp_enable);
EXPORT_SYMBOL(bsp_socp_set_bbp_ds_mode);

EXPORT_SYMBOL(socp_help);
EXPORT_SYMBOL(socp_show_debug_gbl);
EXPORT_SYMBOL(socp_show_ccore_head_err_cnt);
EXPORT_SYMBOL(socp_show_enc_src_chan_cur);
EXPORT_SYMBOL(socp_show_enc_src_chan_add);
EXPORT_SYMBOL(socp_show_enc_src_chan_all);
EXPORT_SYMBOL(socp_show_enc_dst_chan_cur);
EXPORT_SYMBOL(socp_show_enc_dst_chan_add);
EXPORT_SYMBOL(socp_show_enc_dst_chan_all);
EXPORT_SYMBOL(socp_show_dec_src_chan_cur);
EXPORT_SYMBOL(socp_show_dec_src_chan_add);
EXPORT_SYMBOL(socp_show_dec_src_chan_all);
EXPORT_SYMBOL(socp_show_dec_dst_chan_cur);
EXPORT_SYMBOL(socp_show_dec_dst_chan_add);
EXPORT_SYMBOL(socp_show_dec_dst_chan_all);

EXPORT_SYMBOL(socp_debug_cnt_show);
EXPORT_SYMBOL(socp_get_index);
EXPORT_SYMBOL(BSP_SOCP_DrxRestoreRegAppOnly);
EXPORT_SYMBOL(BSP_SOCP_CanSleep);
EXPORT_SYMBOL(bsp_socp_get_state);
EXPORT_SYMBOL(bsp_socp_get_log_cfg);
EXPORT_SYMBOL(bsp_socp_set_log_cfg);
EXPORT_SYMBOL(set_flag);
EXPORT_SYMBOL(socp_is_encdst_chan_empty);



