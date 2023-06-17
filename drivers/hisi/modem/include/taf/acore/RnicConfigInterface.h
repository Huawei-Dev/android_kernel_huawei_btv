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

#ifndef __RNICCONFIGINTERFACE_H__
#define __RNICCONFIGINTERFACE_H__

/*****************************************************************************
  1 ??????????????
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 ??????
*****************************************************************************/
#define RNIC_MODEM_TYPE_IS_VALID(enModemType)\
    (((enModemType) == RNIC_MODEM_TYPE_INSIDE)\
  || ((enModemType) == RNIC_MODEM_TYPE_OUTSIDE))

#define RNIC_RMNET_STATUS_IS_VALID(enRmnetStatus)\
    (((enRmnetStatus) == RNIC_RMNET_STATUS_UP) \
  || ((enRmnetStatus) == RNIC_RMNET_STATUS_DOWN) \
  || ((enRmnetStatus) == RNIC_RMNET_STATUS_SWITCH))

#define RNIC_IP_TYPE_IS_VALID(enIpType)\
    (((enIpType) == RNIC_IP_TYPE_IPV4) \
  || ((enIpType) == RNIC_IP_TYPE_IPV6) \
  || ((enIpType) == RNIC_IP_TYPE_IPV4V6))


/*****************************************************************************
   3 ????????
*****************************************************************************/
/*****************************************************************************
 ??????    : RNIC_MODEM_TYPE_ENUM_UINT8
 ????????  : RNIC????????MODEM??????????
 1.??    ??   : 2014??01??27??
   ??    ??   : m00217266
   ????????   : ????
*****************************************************************************/
enum RNIC_MODEM_TYPE_ENUM
{
    RNIC_MODEM_TYPE_INSIDE,                                                     /* ????modem */
    RNIC_MODEM_TYPE_OUTSIDE,                                                    /* ????modem */

    RNIC_MODEM_TYPE_BUTT
};

typedef unsigned char RNIC_MODEM_TYPE_ENUM_UINT8;

/*****************************************************************************
 ??????    : RNIC_RMNET_STATUS_ENUM_UINT8
 ????????  : RNIC??????????????????????
 1.??    ??   : 2014??01??27??
   ??    ??   : m00217266
   ????????   : ????
*****************************************************************************/
enum RNIC_RMNET_STATUS_ENUM
{
    RNIC_RMNET_STATUS_UP,                                                       /* PDP??????????????up???? */
    RNIC_RMNET_STATUS_DOWN,                                                     /* PDP????????????????down???? */
    RNIC_RMNET_STATUS_SWITCH,                                                   /* ????modem PDP??????????????????switch???? */

    RNIC_RMNET_STATUS_BUTT
};

typedef unsigned char RNIC_RMNET_STATUS_ENUM_UINT8;

/*****************************************************************************
 ??????    : RNIC_IP_TYPE_ENUM_UINT8
 ????????  : RNIC????????????????IP????????
            ipv4v6??????????????????????????ipv4??ipv6 config??????????????????
            ip??????????ipv4??ipv6??
            ipv4v6????????????????????????config??????????????????ip??????ipv4v6
 1.??    ??   : 2014??01??27??
   ??    ??   : m00217266
   ????????   : ????
*****************************************************************************/
enum RNIC_IP_TYPE_ENUM
{
    RNIC_IP_TYPE_IPV4                   = 0x01,
    RNIC_IP_TYPE_IPV6                   = 0x02,
    RNIC_IP_TYPE_IPV4V6                 = 0x03,

    RNIC_IP_TYPE_BUTT                   = 0xFF
};

typedef unsigned char RNIC_IP_TYPE_ENUM_UINT8;


/*****************************************************************************
 ??????    : RNIC_RMNET_CONFIG_STRU
 ????????  : ????????????RNIC_ConfigRmnetStatus????????RNIC??????????????
 1.??    ??   : 2014??01??21??
   ??    ??   : m00217266
   ????????   : ????
*****************************************************************************/
typedef struct
{
    RNIC_MODEM_TYPE_ENUM_UINT8          enModemType;
    unsigned char                       ucRmNetId;
    unsigned short                      usModemId;
    unsigned char                       ucPdnId;
    unsigned char                       ucRabId;
    RNIC_RMNET_STATUS_ENUM_UINT8        enRmnetStatus;
    RNIC_IP_TYPE_ENUM_UINT8             enIpType;
}RNIC_RMNET_CONFIG_STRU;

/*****************************************************************************
   10 ????????
*****************************************************************************/

/* RNIC???????????????????????????????? */
unsigned long RNIC_ConfigRmnetStatus(
    RNIC_RMNET_CONFIG_STRU             *pstConfigInfo
);

/*****************************************************************************
 ?? ?? ??  : RNIC_StartFlowCtrl
 ????????  : ????????????
 ????????  : ucRmNetId : ????ID
 ????????  : ??
 ?? ?? ??  : VOS_OK     - ????????????
             VOS_ERR    - ????????????
 ????????  :
 ????????  :
*****************************************************************************/
unsigned int RNIC_StartFlowCtrl(unsigned char ucRmNetId);


/*****************************************************************************
 ?? ?? ??  : RNIC_StopFlowCtrl
 ????????  : ????????????
 ????????  : ucRmNetId : ????ID
 ????????  : ??
 ?? ?? ??  : VOS_OK     - ????????????
             VOS_ERR    - ????????????
 ????????  :
 ????????  :
*****************************************************************************/
unsigned int RNIC_StopFlowCtrl(unsigned char ucRmNetId);


#pragma pack(0)


#ifdef __cplusplus
#if __cplusplus
        }
#endif
#endif

#endif /* end of RnicConfigInterface.h */
