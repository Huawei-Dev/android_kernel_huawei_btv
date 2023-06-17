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

#include "bsp_socp.h"
#include "bsp_slice.h"

typedef struct tagSOCP_ADP_DEBUG_INFO_S
{
    unsigned int        u32TimeoutTimes;
    unsigned int        u32TimeoutSlice;
    unsigned int        u32DefaultTimes;
    unsigned int        u32DefaultSlice;
}SOCP_ADP_DEBUG_INFO_S;

SOCP_ADP_DEBUG_INFO_S g_SocpDebugInfo = {0};

void DRV_SOCP_SHOW_DEBUG_INFO(void)
{
    printk(KERN_ERR"u32TimeoutTimes %d, u32TimeoutSlice 0x%x, u32DefaultTimes %d, u32DefaultSlice 0x%x.\n", 
        g_SocpDebugInfo.u32TimeoutTimes, g_SocpDebugInfo.u32TimeoutSlice,
        g_SocpDebugInfo.u32DefaultTimes, g_SocpDebugInfo.u32DefaultSlice);
}

int DRV_SOCP_INIT()
{
    return socp_init();
}

int mdrv_socp_corder_set_src_chan(SOCP_CODER_SRC_ENUM_U32 enSrcChanID, SOCP_CODER_SRC_CHAN_S *pSrcAttr)
{
    return bsp_socp_coder_set_src_chan(enSrcChanID, pSrcAttr);
}

int mdrv_socp_coder_set_dest_chan_attr(unsigned int u32DestChanID, SOCP_CODER_DEST_CHAN_S *pDestAttr)
{
    return bsp_socp_coder_set_dest_chan_attr(u32DestChanID, pDestAttr);
}

int DRV_SOCP_DECODER_SET_DEST_CHAN(SOCP_DECODER_DST_ENUM_U32 enDestChanID, SOCP_DECODER_DEST_CHAN_STRU *pAttr)
{
    return bsp_socp_decoder_set_dest_chan(enDestChanID, pAttr);
}

int DRV_SOCP_DECODER_SET_SRC_CHAN_ATTR ( unsigned int u32SrcChanID,SOCP_DECODER_SRC_CHAN_STRU *pInputAttr)
{
    return bsp_socp_decoder_set_src_chan_attr(u32SrcChanID, pInputAttr);
}

int DRV_SOCP_DECODER_GET_ERR_CNT (unsigned int u32ChanID, SOCP_DECODER_ERROR_CNT_STRU *pErrCnt)
{
    return bsp_socp_decoder_get_err_cnt(u32ChanID, pErrCnt);
}

int DRV_SOCP_FREE_CHANNEL(unsigned int u32ChanID)
{
    return bsp_socp_free_channel(u32ChanID);
}

unsigned int DRV_SOCP_CLEAN_ENCSRC_CHAN(SOCP_CODER_SRC_ENUM_U32 enSrcChanID)
{
    return bsp_socp_clean_encsrc_chan(enSrcChanID);
}

int DRV_SOCP_REGISTER_EVENT_CB(unsigned int u32ChanID, socp_event_cb EventCB)
{
    return bsp_socp_register_event_cb(u32ChanID, EventCB);
}

int mdrv_socp_start(unsigned int u32SrcChanID)
{
    return bsp_socp_start(u32SrcChanID);
}

int mdrv_socp_stop(unsigned int u32SrcChanID)
{
    return bsp_socp_stop(u32SrcChanID);
}

int DRV_SOCP_SET_TIMEOUT (SOCP_TIMEOUT_EN_ENUM_UIN32 eTmOutEn, unsigned int u32Timeout)
{
    return bsp_socp_set_timeout(eTmOutEn, u32Timeout);
}

int DRV_SOCP_SET_DEC_PKT_LGTH(SOCP_DEC_PKTLGTH_STRU *pPktlgth)
{
    return bsp_socp_set_dec_pkt_lgth(pPktlgth);
}

int DRV_SOCP_SET_DEBUG(unsigned int u32DestChanID, unsigned int u32DebugEn)
{
    return bsp_socp_set_debug(u32DestChanID, u32DebugEn);
}

int mdrv_socp_get_write_buff( unsigned int u32SrcChanID, SOCP_BUFFER_RW_STRU *pBuff)
{
    return bsp_socp_get_write_buff(u32SrcChanID, pBuff);
}

int mdrv_socp_write_done(unsigned int u32SrcChanID, unsigned int u32WrtSize)
{
    return bsp_socp_write_done(u32SrcChanID, u32WrtSize);
}

int DRV_SOCP_REGISTER_RD_CB(unsigned int u32SrcChanID, socp_rd_cb RdCB)
{
    return bsp_socp_register_rd_cb(u32SrcChanID, RdCB);
}

int mdrv_socp_get_rd_buffer( unsigned int u32SrcChanID,SOCP_BUFFER_RW_STRU *pBuff)
{
    return bsp_socp_get_rd_buffer(u32SrcChanID, pBuff);
}

int mdrv_socp_read_rd_done(unsigned int u32SrcChanID, unsigned int u32RDSize)
{
    return bsp_socp_read_rd_done(u32SrcChanID, u32RDSize);
}

int DRV_SOCP_REGISTER_READ_CB( unsigned int u32DestChanID, socp_read_cb ReadCB)
{
    return bsp_socp_register_read_cb(u32DestChanID, ReadCB);
}

int DRV_SOCP_GET_READ_BUFF(unsigned int u32DestChanID,SOCP_BUFFER_RW_STRU *pBuffer)
{
    return bsp_socp_get_read_buff(u32DestChanID, pBuffer);
}

int DRV_SOCP_READ_DATA_DONE(unsigned int u32DestChanID,unsigned int u32ReadSize)
{
    return bsp_socp_read_data_done(u32DestChanID, u32ReadSize);
}

int DRV_SOCP_SET_BBP_ENABLE(int bEnable)
{
    return bsp_socp_set_bbp_enable(bEnable);
}

int DRV_SOCP_SET_BBP_DS_MODE(SOCP_BBP_DS_MODE_ENUM_UIN32 eDsMode)
{
    return bsp_socp_set_bbp_ds_mode(eDsMode);
}

SOCP_STATE_ENUM_UINT32 DRV_SOCP_GET_STATE()
{
    return bsp_socp_get_state();
}

int DRV_SOCP_VOTE(SOCP_VOTE_ID_ENUM_U32 id, SOCP_VOTE_TYPE_ENUM_U32 type)
{
    return bsp_socp_vote(id, type);
}

unsigned int mdrv_socp_get_sd_logcfg(SOCP_ENC_DST_BUF_LOG_CFG_STRU* cfg)
{
    struct socp_enc_dst_log_cfg* LogCfg;

    if(NULL == cfg)
        return BSP_ERR_SOCP_INVALID_PARA;

    LogCfg = bsp_socp_get_log_cfg();

    if(SOCP_DST_CHAN_NOT_CFG != LogCfg->logOnFlag)
    {
        cfg->logOnFlag = SOCP_DST_CHAN_DELAY;
        cfg->BufferSize= LogCfg->BufferSize;
        cfg->overTime  = LogCfg->overTime;
        cfg->pVirBuffer= LogCfg->pVirBuffer;
        cfg->ulCurTimeout = LogCfg->ulCurTimeout;
        cfg->ulPhyBufferAddr = LogCfg->ulPhyBufferAddr;
    }

    return 0;
}

void mdrv_socp_set_log_int_timeout(void)
{
    struct socp_enc_dst_log_cfg* LogCfg;
    unsigned int time;

    g_SocpDebugInfo.u32TimeoutTimes++;
    g_SocpDebugInfo.u32TimeoutSlice = bsp_get_slice_value();

    printk(KERN_ERR"mdrv_socp_set_log_int_timeout.\n");

    LogCfg = bsp_socp_get_log_cfg();

    if(SOCP_DST_CHAN_DELAY == LogCfg->logOnFlag)
    {
        time = (LogCfg->overTime * 2289)/1000;
        (void)bsp_socp_set_timeout(SOCP_TIMEOUT_TRF, time);
        LogCfg->ulCurTimeout = LogCfg->overTime;
        bsp_socp_set_enc_dst_threshold(TRUE,SOCP_CODER_DST_OM_IND);
    }

    return;
}

void mdrv_socp_set_log_int_default_timeout(void)
{
    struct socp_enc_dst_log_cfg* LogCfg;

    g_SocpDebugInfo.u32DefaultTimes++;
    g_SocpDebugInfo.u32DefaultTimes = bsp_get_slice_value();
    
    LogCfg = bsp_socp_get_log_cfg();

    if(SOCP_DST_CHAN_DELAY == LogCfg->logOnFlag)
    {
        (void)bsp_socp_set_timeout(SOCP_TIMEOUT_TRF, 0x17);
        LogCfg->ulCurTimeout = 10;
        bsp_socp_set_enc_dst_threshold(FALSE,SOCP_CODER_DST_OM_IND);
    }

    return;
}

void mdrv_socp_enalbe_dfs(void)
{
    return bsp_socp_set_clk_autodiv_enable();
}

void mdrv_socp_disalbe_dfs(void)
{
    return bsp_socp_set_clk_autodiv_disable();
}

int mdrv_socp_compress_enable(unsigned int u32DestChanID)
{
    return 0;
}

int mdrv_socp_compress_disable(unsigned int u32DestChanID)
{
    return 0;
}

BSP_VOID BSP_SOCP_RefreshSDLogCfg(unsigned int ulTimerLen)
{
	return;
}
