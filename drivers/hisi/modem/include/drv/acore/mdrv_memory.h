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


#ifndef __MDRV_ACORE_MEMORY_H__
#define __MDRV_ACORE_MEMORY_H__
#ifdef __cplusplus
extern "C"
{
#endif

#include <mdrv_memory_common.h>

typedef enum tagMEM_MODE_TYPE
{
    MEM_DDR_MODE = 0,
    MEM_IPF_MODE,
    MEM_TTF_MODE,
    MEM_AXI_MODE,
    MEM_MODE_MAX
}MEM_MODE_TYPE_E;

typedef enum tagBSP_DDR_SECT_TYPE_E
{
    BSP_DDR_SECT_TYPE_TTF = 0x0,
    BSP_DDR_SECT_TYPE_ARMDSP,
    BSP_DDR_SECT_TYPE_UPA,
    BSP_DDR_SECT_TYPE_CQI,
    BSP_DDR_SECT_TYPE_APT,
    BSP_DDR_SECT_TYPE_ET,
    BSP_DDR_SECT_TYPE_BBPMASTER,
    BSP_DDR_SECT_TYPE_NV,
    BSP_DDR_SECT_TYPE_DICC,
    BSP_DDR_SECT_TYPE_WAN,
    BSP_DDR_SECT_TYPE_SHARE_MEM,
    BSP_DDR_SECT_TYPE_EXCP,
    BSP_DDR_SECT_TYPE_HIFI,
    BSP_DDR_SECT_TYPE_HARQ,
    BSP_DDR_SECT_TYPE_ZSP_UP,
    BSP_DDR_SECT_TYPE_HUTAF,
    BSP_DDR_SECT_TYPE_BBPSAMPLE,
    BSP_DDR_SECT_TYPE_TDS_LH2,
    BSP_DDR_SECT_TYPE_SOCP,
    BSP_DDR_SECT_TYPE_ECS_TEE,

    BSP_DDR_SECT_TYPE_BUTTOM
}BSP_DDR_SECT_TYPE_E;

typedef enum tagBSP_DDR_SECT_ATTR_E
{
    BSP_DDR_SECT_ATTR_CACHEABLE = 0x0,
    BSP_DDR_SECT_ATTR_NONCACHEABLE,
    BSP_DDR_SECT_ATTR_BUTTOM
}BSP_DDR_SECT_ATTR_E;

typedef enum tagBSP_DDR_SECT_PVADDR_E
{
    BSP_DDR_SECT_PVADDR_EQU = 0x0,
    BSP_DDR_SECT_PVADDR_NOT_EQU,
    BSP_DDR_SECT_PVADDR_BUTTOM
}BSP_DDR_SECT_PVADDR_E;


typedef struct tagBSP_DDR_SECT_QUERY_S
{
    BSP_DDR_SECT_TYPE_E     enSectType;
    BSP_DDR_SECT_ATTR_E     enSectAttr;
    BSP_DDR_SECT_PVADDR_E   enPVAddr;
    unsigned int                 ulSectSize;
}BSP_DDR_SECT_QUERY_S;

typedef struct tagBSP_DDR_SECT_INFO_S
{
    BSP_DDR_SECT_TYPE_E    enSectType;
    BSP_DDR_SECT_ATTR_E    enSectAttr;
    void *                 pSectVirtAddr;
    void *                 pSectPhysAddr;
    unsigned int           ulSectSize;
}BSP_DDR_SECT_INFO_S;

/*****************************************************************************
* ?? ?? ??  : mdrv_get_fix_ddr_addr
*
* ????????  :DDR????????????????
*
* ????????  : pstSectQuery: ??????????????????????????
*             pstSectInfo:  ??????????????????
*
* ????????  : ??
* ?? ?? ??  :  ??
****************************************************************************/
int mdrv_get_fix_ddr_addr (BSP_DDR_SECT_QUERY_S *pstSectQuery, BSP_DDR_SECT_INFO_S *pstSectInfo);

/*****************************************************************************
* ?? ?? ??  : mdrv_virt_to_phy
*
* ????????  :????????????????????
*
* ????????  : lPAddr: ????????????????????????????????????
*             mode:   ????????
* ????????  : ??
* ?? ?? ??  : ??????????
****************************************************************************/
void*  mdrv_virt_to_phy (MEM_MODE_TYPE_E mode, void* lPAddr);

/*****************************************************************************
* ?? ?? ??  : mdrv_phy_to_virt
*
* ????????  :??????????????????????
*
* ????????  : pMem: ??????????????????
*             mode: ????????
*
* ????????  : ??
* ?? ?? ??  : ??????????
****************************************************************************/
void*  mdrv_phy_to_virt (MEM_MODE_TYPE_E mode, void* pMem);

/*****************************************************************************
* ?? ?? ??  : mdrv_memcpy
*
* ????????  : ????????????????????????????????????????????????????memory??
*             memory??????
* ????????  :
*             ????????memory ??memory????????????????memory??????????????
*             ????4????????
*             ??A?? ARMv8 ????????????8??????????????normal memory ??????
*             ????ioremap_wc?????? uncachable ?????? ????cachable??????
*
* ????????  : dest :  ??????????????
*             src  :  ????????????
*             count:  ??????????????
* ????????  : ??
* ?? ?? ??  :  ??
****************************************************************************/
void *mdrv_memcpy(void * dest, const void * src, unsigned long count);

#ifdef __cplusplus
}
#endif
#endif
