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

#ifndef _NV_FACTORY_CHECK_H_
#define _NV_FACTORY_CHECK_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

enum
{
    SINGAL_NV_DISABLE = 0,
    SINGAL_NV_ENABLE = 1,
    SINGAL_NV_BUTT
};

typedef struct factory_crc_check_info_stru
{
    u32 list_nvid;
    u32 modem_num;
    u32 valild_band_count;
    u32 valild_nvid_count;
    u32 singal_group_size;
    u32 old_crc_value;
}factory_crc_check_info_t;

typedef struct
{
    UINT16   uhwTransmitMode;
    UINT16   uhwBand;
    UINT16   uhwEnable;
    UINT16   uhwValidCount;
    UINT16  auhwNeedCheckID[0];
}singal_band_nvid_t;

u32  nv_check_mode_crc(factory_crc_check_info_t check_info);
u32  nv_check_factory_nv_status(u32 mode);
u32  nv_make_single_band_nv_crc(singal_band_nvid_t* check_item_temp, u32 modem_num, u32 valild_nvid_count, u32 *last_crc_value, u32 *gen_crc_value);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /*_NV_CRC_H_*/
