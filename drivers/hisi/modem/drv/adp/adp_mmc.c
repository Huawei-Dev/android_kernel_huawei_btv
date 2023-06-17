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
 /*lint -save -e18 -e26 -e64 -e115 -e119 -e123 -e529 -e537 -e569 -e570 -e713 -e718 -e732 -e746 -e747 -e958 -e715 -e818*/
/*****************************************************************************
* ?? ?? ??  : mdrv_sd_get_capacity
* ????????  : ??????????
* ????????  : ??
* ????????  : ??
* ?? ?? ??  : 0 : ??????>0: ??????
*****************************************************************************/
unsigned int mdrv_sd_get_capacity(void)
{
	return 0;
}

/*****************************************************************************
* ?? ?? ??  : mdrv_sd_get_status
* ????????  : ??????????
* ????????  : ??
* ????????  : ??
* ?? ?? ??  : 0 : ??????-1: ??????
*****************************************************************************/

int mdrv_sd_get_status(void)
{
	return 0;
}

unsigned long mdrv_sd_get_opptstatus(void)
{
	return 0;
}

unsigned int mdrv_sd_at_process(unsigned int type,
                unsigned int addr,  unsigned int data,
                unsigned char *buf, unsigned int *err)
{
	return 0;
}

/*****************************************************************************
* ?? ?? ??  : DRV_SD_SG_INIT_TABLE
*
* ????????  : SD????????????sg list??????
*
* ????????  : const void *buf		????????buffer????
				  unsigned int buflen	????????buffer??????????32K, ??????512B????????
				  					????32K, ??????32KB??????????????buffer??128K
* ????????  : NA
*
* ?? ?? ??  :  0 : ????;  ????:????
* ????????  : NA
*
*****************************************************************************/
int mdrv_sd_sg_init_table(const void *buf,unsigned int buflen)
{
    return 0;
}


/*****************************************************************************
* ?? ?? ??  : mdrv_sd_multi_transfer
*
* ????????  : SD????????????
*
* ????????  : unsigned dev_addr	????????SD block????
				  unsigned blocks		????????block ????
				  unsigned blksz		????block ????????????????
				  int write			??????????????:1;	??:0
* ????????  : NA
*
* ?? ?? ??  :  0 : ????;  ????:????
* ????????  : NA
*
*****************************************************************************/
int mdrv_sd_multi_transfer(unsigned int dev_addr, unsigned int blocks,
						   unsigned int blksz,int write)
{
    return 0;
}

/*lint -restore*/

