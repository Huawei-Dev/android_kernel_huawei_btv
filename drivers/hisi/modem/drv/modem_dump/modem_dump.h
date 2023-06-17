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
#ifndef __MDM_DUMP_H__
#define __MDM_DUMP_H__

#ifdef BSP_CONFIG_PHONE_TYPE
#include "../../adrv/adrv.h"
#else
#include <linux/hisi/rdr_pub.h>
#endif

#include <linux/semaphore.h>

#define RDR_MODEM_CP_DRV_MOD_ID_START           0x00000000  
#define RDR_MODEM_CP_DRV_MOD_ID_END             0x0fffffff  
#define RDR_MODEM_CP_OSA_MOD_ID_START           0x10000000  
#define RDR_MODEM_CP_OSA_MOD_ID_END             0x1fffffff  
#define RDR_MODEM_CP_OAM_MOD_ID_START           0x20000000  
#define RDR_MODEM_CP_OAM_MOD_ID_END             0x2fffffff  
#define RDR_MODEM_CP_GUL2_MOD_ID_START          0x30000000  
#define RDR_MODEM_CP_GUL2_MOD_ID_END            0x3fffffff  
#define RDR_MODEM_CP_GUWAS_MOD_ID_START         0x40000000                  
#define RDR_MODEM_CP_GUWAS_MOD_ID_END           0x4fffffff              
#define RDR_MODEM_CP_GUGAS_MOD_ID_START         0x50000000              
#define RDR_MODEM_CP_GUGAS_MOD_ID_END           0x5fffffff              
#define RDR_MODEM_CP_GUNAS_MOD_ID_START         0x60000000              
#define RDR_MODEM_CP_GUNAS_MOD_ID_END           0x600020ff              
#define RDR_MODEM_CP_GUDSP_MOD_ID_START         0x70000000              
#define RDR_MODEM_CP_GUDSP_MOD_ID_END           0x7fffffff              
#define RDR_MODEM_CP_LPS_MOD_ID_START           0xa0000000               
#define RDR_MODEM_CP_LPS_MOD_ID_END             0xafffffff              
#define RDR_MODEM_CP_LMSP_MOD_ID_START          0xb0000000              
#define RDR_MODEM_CP_LMSP_MOD_ID_END            0xbfffffff              
#define RDR_MODEM_CP_TLDSP_MOD_ID_START         0xc0000000              
#define RDR_MODEM_CP_TLDSP_MOD_ID_END           0xc00020ff 


#define RDR_MODEM_AP_MOD_ID                     0x82000000
#define RDR_MODEM_CP_MOD_ID                     0x82000001
#define RDR_MODEM_CP_WDT_MOD_ID                 0x82000003
#define RDR_MODEM_CP_RESET_SIM_SWITCH_MOD_ID    0x82000005
#define RDR_MODEM_CP_RESET_FAIL_MOD_ID          0x82000006
#define RDR_MODEM_CP_RESET_RILD_MOD_ID          0x82000007
#define RDR_MODEM_CP_RESET_3RD_MOD_ID           0x82000008
#define RDR_MODEM_CP_RESET_REBOOT_REQ_MOD_ID    0x82000009
#define RDR_MODEM_CP_RESET_USER_RESET_MOD_ID    0x82000010
#define RDR_MODEM_NOC_MOD_ID                    0x82000030
#define RDR_MODEM_DMSS_MOD_ID                   0x82000031
#define RDR_DUMP_FILE_PATH_LEN                128
#define RDR_DUMP_FILE_CP_PATH                 "cp_log/"
#define MODEM_DUMP_FILE_NAME_LENGTH           300
#define RDR_MODEM_CP_RESET_TIMEOUT            (30000)

typedef struct
{
    u32     modid;
    u32     product_type;
    u64     coreid;
    char    log_path[RDR_DUMP_FILE_PATH_LEN];
    pfn_cb_dump_done    dump_done;
    struct rdr_register_module_result soc_rst;
}modem_exc_info_s;
                                     
#endif
