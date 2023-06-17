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

#ifndef _NV_XML_DEC_H_
#define _NV_XML_DEC_H_

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif
#pragma pack(push)
#pragma pack(4)

#include "nv_comm.h"
#include "nv_ctrl.h"
#include "msp_nv_id.h"

#define  XML_FILE_READ_BUFF_SIZE              (0x1000)
#define  XML_NODE_LABEL_BUFF_LENGTH_ORIGINAL  (0X80)
#define  XML_NODE_VALUE_BUFF_LENGTH_ORIGINAL  (0X8000)
#define  XML_MAX_HARDWARE_LEN                 (0X20)

enum XML_RESULT_ENUM
{
    XML_RESULT_SUCCEED                        = 0 ,
    XML_RESULT_SUCCEED_IGNORE_CHAR,
    XML_RESULT_FALIED_PARA_POINTER,
    XML_RESULT_FALIED_MALLOC,
    XML_RESULT_FALIED_BAD_SYNTAX,
    XML_RESULT_FALIED_BAD_CHAR,
    XML_RESULT_FALIED_READ_FILE,
    XML_RESULT_FALIED_WRITE_NV,
    XML_RESULT_FALIED_OUT_OF_BUFF_LEN,
    XML_RESULT_FALIED_OUT_OF_MAX_VALUE,
    XML_RESULT_FALIED_OUT_OF_0_9,
    XML_RESULT_FALIED_OUT_OF_0_F,
    XML_RESULT_FALIED_OUT_OF_2_CHAR,
    XML_RESULT_FALIED_NV_ID_IS_NULL,
    XML_RESULT_FALIED_NV_VALUE_IS_NULL,
    XML_RESULT_FALIED_PRODUCT_MATCH,
    XML_RESULT_BUTT
};
typedef u32 XML_RESULT_ENUM_UINT32;

enum XML_ANALYSE_STATUS_ENUM
{
    XML_ANASTT_ORIGINAL                       = 0 ,
    XML_ANASTT_ENTER_LABLE,
    XML_ANASTT_IGNORE,
    XML_ANASTT_NODE_LABLE,
    XML_ANASTT_SINGLE_ENDS_LABLE,
    XML_ANASTT_LABLE_END_MUST_RIGHT,
    XML_ANASTT_PROPERTY_START,
    XML_ANASTT_PROPERTY_NAME_START,
    XML_ANASTT_PROPERTY_NAME_END,
    XML_ANASTT_PROPERTY_VALUE_START,
    XML_ANASTT_PROPERTY_VALUE_END,
    XML_ANASTT_BUTT
};
typedef u32 XML_ANALYSE_STATUS_ENUM_UINT32;
typedef u32 (*XML_FUN)(s8 cnowchar);

enum XML_PRODUCT_STATUS_ENUM
{
    XML_PRODUCT_NODE_STATUS_INVALID           = 0 ,
    XML_PRODUCT_NODE_STATUS_VALID,
    XML_PRODUCT_NODE_BUTT
};
typedef u32 XML_PRODUCT_STATUS_ENUM_UINT32;

enum XML_DECODE_STATUS_ENUM
{
    XML_DECODE_STATUS_DECODING                = 0 ,
    XML_DECODE_STATUS_FINISHED,
    XML_DECODE_BUTT
};
typedef u32 XML_DECODE_STATE_ENUM_UINT32;

enum XML_DECODE_JUMP_FLAG_ENUM
{
    XML_DECODE_STATUS_NOJUMP    = 0,
    XML_DECODE_STATUS_JUMP ,
    XML_DECODE_STATUS_2JUMP,
    XML_DECODE_STATUS_JUMP_BUTT
};
typedef u32 XML_DECODE_JUMP_FLAG_ENUM;

typedef struct
{
    u32 product_id;              /*product id*/
    u32 productCatOff;           /*product cat offset in the file*/
    u32 productIdOff;            /*product id  offset in the file*/
}XNV_MAP_PRODUCT_INFO;

typedef struct
{
    u32 magic_num;
    u32 product_num;
    u8  md5[16];
    XNV_MAP_PRODUCT_INFO product_info[0];
}XNV_MAP_HEAD_STRU;

typedef struct
{
    u32 ulnamelength;
    u32 ulvaluelength;
    s8* pcpropertyname;
    s8* pcpropertyvalue;
}XML_NODE_PROPERTY_STRU;

#define XML_NODE_PROPERTY_NUM   (2)

typedef struct
{
    u32 ullabellength;
    u32 ullabelendlength;
    u32 ulvaluelength;
    u32  ulPropertyIndex;
    s8*  pcnodelabel;
    s8*  pcnodelabelend;
    s8*  pcnodevalue;
    XML_NODE_PROPERTY_STRU stproperty[XML_NODE_PROPERTY_NUM];
}XML_NODE_STRU;

typedef struct
{

    XML_PRODUCT_STATUS_ENUM_UINT32 envalidnode;
    XML_DECODE_STATE_ENUM_UINT32   enxmldecodestate;
    u32                     ulnodelevel;
    s8                       acproductid[XML_MAX_HARDWARE_LEN];
    XML_DECODE_JUMP_FLAG_ENUM      enxmldecodejump;
}XML_PRODUCT_STRU;

typedef struct
{
    u32 ulxmlline;
    u32 ulstatus;
    u32 ulcodeline;
    u16 usnvid;
    u16 usreserve;
    u32 ulresult;
} XML_ERROR_INFO_STRU;


typedef struct
{
    XML_NODE_STRU g_stlxmlcurrentnode;
    XML_PRODUCT_STRU g_stlxmlproductinfo;
    u8 *g_puclnvitem;
    s8  *g_pclfilereadbuff;
    u32 g_stlxml_lineno;
    s32 g_stlxmlproductid;
    XML_ERROR_INFO_STRU g_stlxmlerrorinfo;
    u32 card_type;
    XML_DECODE_JUMP_FLAG_ENUM g_stlxmljumpflag;
    XNV_MAP_PRODUCT_INFO g_stlxmljumpinfo;
}XML_DOCODE_INFO;

u32 xml_decode_main(FILE* fp,s8* map_path,u32 card_type);
void xml_help(void);
u32 xml_nv_search_byid(u32 itemid,u8* pdata,struct nv_ref_data_info_stru* ref_info,struct nv_file_list_info_stru* file_info, u8** ref_offset);
void xml_nv_write_priority(u8* ref_offset , u16 priority);
u32 xml_nv_write_to_mem(u8* pdata,u32 size,u32 file_id,u32 offset);
XML_RESULT_ENUM_UINT32 xml_analyse(s8 cnowchar);
void xml_write_error_log(u32 ulerrorline, u16 ulnvid, u32 ret);
XML_RESULT_ENUM_UINT32 xml_procinit(s8* map_path);

#pragma pack(pop)
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* _NV_XML_DEC_H_ */
