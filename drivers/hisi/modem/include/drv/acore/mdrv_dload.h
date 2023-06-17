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

#ifndef _MDRV_DLOAD_H_
#define _MDRV_DLOAD_H_

#ifdef _cplusplus
extern "C"
{
#endif


/* ???????????? */
typedef enum tagDLOAD_MODE_E
{
    DLOAD_MODE_DOWNLOAD = 0,
    DLOAD_MODE_NORMAL,
    DLOAD_MODE_DATA,
    DLOAD_MODE_MAX
}DLOAD_MODE_E;

typedef  struct  tagDLOAD_VER_INFO_S
{
        unsigned char*  productname;
        unsigned int  productnamelen;
        unsigned char*  softwarever;
        unsigned int  softwareverlen;
        unsigned char*  isover;
        unsigned int  isoverlen;
        unsigned char*  dloadver;
        unsigned int  dloadverlen;
} DLOAD_VER_INFO_S;


/*****************************************************************************
* ?? ?? ??  : mdrv_dload_set_curmode
*
* ????????  : ????????????????
*
* ????????  : void
* ????????  : DLOAD_MODE_NORMAL     :????????
*             DLOAD_MODE_DATA       :????????
*             DLOAD_MODE_DOWNLOAD   :????????
*
* ?? ?? ??  : ??
*
* ????????  : AT????????
*             ????????????????:
*                 BSP_DLOAD_GetCurMode(DLOAD_MODE_DOWNLOAD)
*             ????????????????:
*                 BSP_DLOAD_GetCurMode(DLOAD_MODE_DATA)
*
*****************************************************************************/
void mdrv_dload_set_curmode(DLOAD_MODE_E eDloadMode);
/*****************************************************************************
* ?? ?? ??  : BSP_DLOAD_GetCurMode
*
* ????????  : ????????????????
*
* ????????  : void
* ????????  : ??
*
* ?? ?? ??  : DLOAD_MODE_NORMAL     :????????
*             DLOAD_MODE_DATA       :????????
*             DLOAD_MODE_DOWNLOAD   :????????
*
* ????????  : ??
*
*****************************************************************************/
DLOAD_MODE_E mdrv_dload_get_curmode(void);
/*****************************************************************************
* ?? ?? ??  : mdrv_dload_set_softload
*
* ????????  : ????????????
*
* ????????  : BSP_BOOL bSoftLoad  :
*             BSP_FALSE :??vxWorks????
*             BSP_TRUE  :??bootrom????
* ????????  : ??
*
* ?? ?? ??  : ??
*
* ????????  : ??
*
*****************************************************************************/
void mdrv_dload_set_softload (int bSoftLoad);


/*****************************************************************************
* ?? ?? ??  : mdrv_dload_get_softload
*
* ????????  : ????????????
*
* ????????  : void
* ????????  : ??
*
* ?? ?? ??  : BSP_TRUE  :??bootrom????
*             BSP_FALSE :??vxWorks????
*
* ????????  : ??
*
*****************************************************************************/
int mdrv_dload_get_softload (void);    

/*****************************************************************************
* ?? ?? ??  : mdrv_dload_get_info
*
* ????????  : ????????????????
*
* ????????  : ??
* ????????  : ??
*
* ?? ?? ??  : ?????? ????????????????
                    ???? ????????
*
* ????????  : ??
*
*****************************************************************************/
DLOAD_VER_INFO_S * mdrv_dload_get_info(void);


#ifdef _cplusplus
}
#endif
#endif

