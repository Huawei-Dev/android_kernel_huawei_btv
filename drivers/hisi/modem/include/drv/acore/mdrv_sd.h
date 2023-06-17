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

#ifndef __MDRV_ACORE_SD_H__
#define __MDRV_ACORE_SD_H__

#ifdef __cplusplus
extern "C"
{
#endif

    /*
       unsigned int DRV_SDMMC_GET_OPRT_STATUS(void);
       unsigned int  DRV_SDMMC_AT_PROCESS(unsigned int ulOp,
       unsigned int ulAddr,  unsigned int ulData, unsigned char *pucBuffer, unsigned int *pulErr);
       int DRV_SDMMC_GET_STATUS(void);
       int DRV_SD_GET_STATUS(void);
       int DRV_SD_GET_CAPACITY(void);
       int DRV_SD_SG_INIT_TABLE(const void *buf,unsigned int buflen);
       int DRV_SD_TRANSFER(struct scatterlist *sg,
       unsigned int dev_addr,unsigned int blocks, unsigned int blksz, int wrflags);
       int DRV_SD_MULTI_TRANSFER(unsigned int dev_addr,
       unsigned int blocks,unsigned int blksz,int write);
       static inline void DRV_SDMMC_CLEAR_WHOLE_SCREEN(void)
       {
       return;
       }
     */

#define WRFlAG     1
#define RDFlAG     0

enum SD_MMC_OPRT_ENUM
{
    SD_MMC_OPRT_FORMAT = 0,
    SD_MMC_OPRT_ERASE_ALL,
    SD_MMC_OPRT_ERASE_SPEC_ADDR,
    SD_MMC_OPRT_WRITE,
    SD_MMC_OPRT_READ,
    SD_MMC_OPRT_BUTT
};


    unsigned int mdrv_sd_get_opptstatus(void);

    /*****************************************************************************
      ?? ?? ??  : mdrv_sd_at_process
      ????????  : at^sd,SD????????????????????????????
            0:
      ????????  : ???????? ulOp:
              0  ??????SD????
              1  ????????SD????????
              2  ????????????????????????????????????????????????512????????????????????????1
              3  ????????SD????????????????????????????????????????
              4  ????????SD??????????????

              ulAddr < address >  ????????512BYTE??????????????????n????

              ulData
                     < data >            ??????????????512BYTE??????????????????????????????
                                 0       ??????????0x00
                                 1       ??????????0x55
                                 2       ??????????0xAA
                                 3       ??????????0xFF
      ????????  : pulErr
      ?? ?? ??  : 0 ??OK  ?? 0 ??Error

      ??????????????????*pulErr??
      0 ????SD????????
      1 ????SD????????????
      2 ????<opr>????????????????????????(????????AT????,??????????????)
      3 ????<address>??????????????SD??????????
      4 ????????????
     *****************************************************************************/
    unsigned int mdrv_sd_at_process(unsigned int ulOp, unsigned int ulAddr,
            unsigned int ulData, unsigned char *pucBuffer, unsigned int *pulErr);


#ifdef __cplusplus
}
#endif
#endif
