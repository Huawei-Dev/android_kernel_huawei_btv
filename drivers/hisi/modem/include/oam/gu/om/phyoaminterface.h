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

/******************************************************************************

                  ???????? (C), 2001-2011, ????????????????

 ******************************************************************************
  ?? ?? ??   : phyoaminterface.h
  ?? ?? ??   : ????
  ??    ??   : luoqingquan
  ????????   : 2012??11??14??
  ????????   :
  ????????   : phyoaminterface.h ????????
  ????????   :
  ????????   :
  1.??    ??   : 2012??10??14??
    ??    ??   : luoqingquan
    ????????   : ????????

******************************************************************************/

/*****************************************************************************
  1 ??????????????
*****************************************************************************/
#include "vos.h"


#ifndef __PHYOAMINTERFACE_H__
#define __PHYOAMINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)


/*****************************************************************************
  2 ??????
*****************************************************************************/

/* ??SAR??ulMask???? */
#define UPHY_OAM_SAR_MASK_ANTSTATE          ( 0x1 )
#define UPHY_OAM_SAR_MASK_REDUCTION         ( 0x2 )

/* ????????????,????V9R1????????????????????,??????????1 */
#define UPHY_DYN_CODE_MODULE_BUTT           ( 0x01 )

/* ??????????phytoolinterface.h??UPHY_TOOL_SLEEP_INFO_NUM?????????????? */
#define UPHY_OAM_SLEEP_INFO_NUM             ( 16 )

/*****************************************************************************
  3 ????????
*****************************************************************************/



/*****************************************************************************
 ??????    :UPHY_OAM_MSG_ID_ENUM_UINT16
 ????????  :
 ASN.1???? :
 ????????  :PHY??OAM????????
*****************************************************************************/
enum UPHY_OAM_MSG_ID_ENUM
{
    /* OAM??UPHY_APM?????? */
    ID_OAM_UPHY_ACTIVE_UPHY_REQ             = 0xD200,                   /* _H2ASN_MsgChoice  UPHY_OAM_ACTIVE_UPHY_REQ_STRU */
    ID_UPHY_OAM_ACTIVE_UPHY_CNF             = 0x2D00,                   /* _H2ASN_MsgChoice  UPHY_OAM_ACTIVE_UPHY_CNF_STRU */

    ID_UPHY_OAM_LOAD_NV_REQ                 = 0x2D01,                   /* _H2ASN_MsgChoice  UPHY_OAM_LOAD_NV_REQ_STRU */
    ID_OAM_UPHY_LOAD_NV_CNF                 = 0xD201,                   /* _H2ASN_MsgChoice  UPHY_OAM_LOAD_NV_CNF_STRU */

    ID_OAM_UPHY_GET_NV_ADDR_REQ             = 0xD202,                   /* _H2ASN_MsgChoice  UPHY_OAM_GET_NV_ADDR_REQ_STRU */
    ID_UPHY_OAM_GET_NV_ADDR_IND             = 0x2D02,                   /* _H2ASN_MsgChoice  UPHY_OAM_GET_NV_ADDR_IND_STRU */

    ID_UPHY_OAM_BOOT_INFO_REQ               = 0x2D03,                   /* _H2ASN_MsgChoice  UPHY_OAM_BOOT_INFO_REQ_STRU */
    ID_OAM_UPHY_BOOT_INFO_IND               = 0xD203,                   /* _H2ASN_MsgChoice  UPHY_OAM_BOOT_INFO_IND_STRU */

    /* OAM??UPHY_DRX?????? */
    ID_OAM_UPHY_MASTER_WAKE_CMD             = 0xD220,                   /* _H2ASN_MsgChoice  UPHY_OAM_WAKE_CMD_STRU */
    ID_UPHY_OAM_MASTER_SLEEP_IND            = 0x2D20,                   /* _H2ASN_MsgChoice  UPHY_OAM_SLEEP_IND_STRU */

    ID_OAM_UPHY_SLAVE_WAKE_CMD              = 0xD221,                   /* _H2ASN_MsgChoice  UPHY_OAM_WAKE_CMD_STRU */
    ID_UPHY_OAM_SLAVE_SLEEP_IND             = 0x2D21,                   /* _H2ASN_MsgChoice  UPHY_OAM_SLEEP_IND_STRU */


    /* OAM??W/GPHY??????,????????PID???? */
    ID_OAM_PHY_LOAD_PHY_REQ                 = 0xD240,                   /* _H2ASN_MsgChoice  PHY_OAM_LOAD_PHY_REQ_STRU */
    ID_PHY_OAM_LOAD_PHY_CNF                 = 0x2D40,                   /* _H2ASN_MsgChoice  PHY_OAM_LOAD_PHY_CNF_STRU */

    ID_OAM_PHY_SAR_CTRL_REQ                 = 0xD241,                   /* _H2ASN_MsgChoice  PHY_OAM_SAR_CTRL_REQ_STRU */
    ID_PHY_OAM_SAR_CTRL_CNF                 = 0x2D41,                   /* _H2ASN_MsgChoice  PHY_OAM_SAR_CTRL_CNF_STRU */

    ID_OAM_PHY_SET_WORK_MODE_REQ            = 0xD242,                   /* _H2ASN_MsgChoice  PHY_OAM_SET_WORK_MODE_REQ_STRU */
    ID_PHY_OAM_SET_WORK_MODE_CNF            = 0x2D42,                   /* _H2ASN_MsgChoice  PHY_OAM_SET_WORK_MODE_CNF_STRU */

    /* OAM??GPHY?????? */
    ID_OAM_GPHY_RF_AGING_TEST_REQ           = 0xD280,                   /* _H2ASN_MsgChoice  GPHY_OAM_RF_AGING_TEST_REQ_STRU */
    ID_GPHY_OAM_RF_AGING_TEST_CNF           = 0x2D80,                   /* _H2ASN_MsgChoice  GPHY_OAM_RF_AGING_TEST_CNF_STRU */


    /* OAM??WPHY?????? */
    ID_OAM_WPHY_RF_AGING_TEST_REQ           = 0xD2C0,                   /* _H2ASN_MsgChoice  WPHY_OAM_RF_AGING_TEST_REQ_STRU */
    ID_WPHY_OAM_RF_AGING_TEST_CNF           = 0x2DC0,                   /* _H2ASN_MsgChoice  WPHY_OAM_RF_AGING_TEST_CNF_STRU */

    ID_OAM_WPHY_UPDATE_REG_STATE_REQ        = 0xD2C1,                   /* _H2ASN_MsgChoice  WPHY_OAM_UPDATE_REG_STATE_REQ_STRU */
    ID_WPHY_OAM_UPDATE_REG_STATE_CNF        = 0x2DC1,                   /* _H2ASN_MsgChoice  WPHY_OAM_UPDATE_REG_STATE_CNF_STRU */

    ID_OAM_WPHY_QUERY_SAMPLE_REQ            = 0xD2D1,                   /* _H2ASN_MsgChoice  OAM_WPHY_QUERY_SAMPLE_REQ */
    ID_WPHY_OAM_QUERY_SAMPLE_CNF            = 0x2DD1,                   /* _H2ASN_MsgChoice  WPHY_OAM_QUERY_SAMPLE_CNF */

    ID_PHY_OAM_MSG_ID_BUTT
};
typedef VOS_UINT16 UPHY_OAM_MSG_ID_ENUM_UINT16;



typedef VOS_UINT32 SLEEP_MODE_ENUM_UINT32;


/*****************************************************************************
 ??????    :UPHY_OAM_BUSINESS_TYPE_ENUM_UINT16
 ????????  :
 ASN.1???? :
 ????????  :??????????????????????
*****************************************************************************/
enum UPHY_OAM_BUSINESS_TYPE_ENUM
{
    UPHY_OAM_BUSINESS_TYPE_NORMAL           = 0,                                /* ???????????? */
    UPHY_OAM_BUSINESS_TYPE_CT                  ,                                /* ????CT???? */
    UPHY_OAM_BUSINESS_TYPE_NO_SIG_BT           ,                                /* ??????????BT???? */
    UPHY_OAM_BUSINESS_TYPE_SIG_BT              ,                                /* ????BT???? */

    UPHY_OAM_BUSINESS_TYPE_BUTT
};
typedef VOS_UINT16 UPHY_OAM_BUSINESS_TYPE_ENUM_UINT16;



/*****************************************************************************
 ??????    :UPHY_OAM_WAKE_TYPE_ENUM_UINT32
 ????????  :
 ASN.1???? :
 ????????  :????????????
*****************************************************************************/
enum UPHY_OAM_WAKE_TYPE_ENUM
{
    UPHY_OAM_NORMAL_WAKE                    = 0,
    UPHY_OAM_FORCE_WAKE                     = 1,
    UPHY_OAM_WAKE_TYPE_BUTT
};
typedef VOS_UINT32 UPHY_OAM_WAKE_TYPE_ENUM_UINT32;



/*****************************************************************************
 ??????    :UPHY_OAM_RSLT_ENUM_UINT16
 ????????  :
 ASN.1???? :
 ????????  :UPHY????OAM??CNF??,??????????????????
*****************************************************************************/
enum UPHY_OAM_RSLT_ENUM
{
    UPHY_OAM_RSLT_SUCC                      = 0,
    UPHY_OAM_RSLT_FAIL                      = 1,

    UPHY_OAM_RSLT_BUTT
};
typedef VOS_UINT16 UPHY_OAM_RSLT_ENUM_UINT16;

/*****************************************************************************
 ??????    :UPHY_OAM_BOOL_ENUM_UINT16
 ????????  :
 ASN.1???? :
 ????????  :UPHY????OAM??CNF??,??????????????????
*****************************************************************************/
enum UPHY_OAM_BOOL_ENUM
{
    UPHY_OAM_INVALID                        = 0,
    UPHY_OAM_VALID                          = 1,

    UPHY_OAM_BUTT
};
typedef VOS_UINT16 UPHY_OAM_BOOL_ENUM_UINT16;


/*****************************************************************************
 ??????    :UPHY_OAM_AGING_TEST_CTRL_ENUM_UINT16
 ????????  :
 ASN.1???? :
 ????????  :????????????????
*****************************************************************************/
enum UPHY_OAM_AGING_TEST_CTRL_ENUM
{
    UPHY_OAM_AGING_TEST_ON                  = 0x5555,
    UPHY_OAM_AGING_TEST_OFF                 = 0xaaaa,
    UPHY_OAM_AGING_TEST_BUTT
};
typedef VOS_UINT16 UPHY_OAM_AGING_TEST_CTRL_ENUM_UINT16;


enum PS_REG_UPDATE_STATE_ENUM
{
    PS_REG_STATE_STOP = 0,
    PS_REG_STATE_ACTIVE,
    PS_REG_STATE_BUTT
};
typedef VOS_UINT16  PS_REG_UPDATE_STATE_ENUM_UINT16;


/*****************************************************************************
 ??????    :UPHY_OAM_NV_INDEX_UINT16
 ????????  :
 ASN.1???? :
 ????????  : NV?????? ??????0-15
             ????????????????????index=10
             index8~15??????????????????
             index0~7??????????????????????
*****************************************************************************/
enum UPHY_OAM_NV_INDEX_ENUM
{
    UPHY_OAM_NV_INDEX_FULL_NET  = 10,
    UPHY_OAM_NV_INDEX_BUTT      = 16
};

typedef VOS_UINT16  UPHY_OAM_NV_INDEX_ENUM_UINT16;

/*****************************************************************************
 ??????    :PHY_OM_TRANS_MSG_ID_ENUM_UINT16
 ????????  :
 ASN.1???? :
 ????????  :??????????OM??????????????ID
*****************************************************************************/
enum PHY_OM_TRANS_MSG_ID_ENUM
{
    ID_PHY_OM_TRANS_MSG_ID              = 0x5001,
    ID_PHY_AT_TRANS_MSG_ID              = 0x4201,

    ID_PHY_OM_TRANS_MSG_BUTT

};
typedef VOS_UINT16 PHY_OM_TRANS_MSG_ID_ENUM_UINT16;

/*****************************************************************************
 ??????    :UPHY_OAM_RTT_STATE_ENUM_UINT16
 ????????  :
 ASN.1???? :
 ????????  : ????RTT??????????
*****************************************************************************/
enum UPHY_OAM_RTT_STATE_ENUM
{
    UPHY_OAM_RTT_STATE_IDLE             = 0,
    UPHY_OAM_RTT_STATE_CS                  ,
    UPHY_OAM_RTT_STATE_PS                  ,
    UPHY_OAM_RTT_STATE_BUTT
};
typedef VOS_UINT16 UPHY_OAM_RTT_STATE_ENUM_UINT16;

/*****************************************************************************
  4 ??????????
*****************************************************************************/

/*****************************************************************************
 ??????    : PHY_TOOL_MSG_HEAD_STRU
 ????????  :
 ????????  : ????????????????????????????????????
*****************************************************************************/

typedef struct
{
    PHY_OM_TRANS_MSG_ID_ENUM_UINT16     usTransPrimId;                          /* ????????ID = 0x5001 */
    VOS_UINT16                          usRsv;                                  /* ???? */
}PHY_TOOL_MSG_HEAD_STRU;




/*****************************************************************************
  5 ????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                              usMsgId;                            /* ????ID */
    VOS_UINT8                               aucData[2];                         /* Msg Data*/
}PHY_OAM_MSG_STRU;


/*****************************************************************************
  6 STRUCT????
*****************************************************************************/




/*****************************************************************************
 ??????    : UPHY_OAM_ACTIVE_UPHY_REQ_STRU
 ????????  : ??????????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* ????ID */
    MODEM_ID_ENUM_UINT16                    enModem;                            /* MODEM???? */
    VOS_RATMODE_ENUM_UINT32                 enRatTpye;                          /* ???? */
}UPHY_OAM_ACTIVE_UPHY_REQ_STRU;




/*****************************************************************************
 ??????    : UPHY_OAM_ACTIVE_UPHY_CNF_STRU
 ????????  : ??????????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* ????ID */
    MODEM_ID_ENUM_UINT16                    enModem;                            /* MODEM???? */
    VOS_RATMODE_ENUM_UINT32                 enRatTpye;                          /* ???? */
    UPHY_OAM_RSLT_ENUM_UINT16               enRslt;                             /* ???????? */
    VOS_UINT16                              usRsv;                              /* ???? */
}UPHY_OAM_ACTIVE_UPHY_CNF_STRU;



/*****************************************************************************
 ??????    : UPHY_OAM_LOAD_NV_REQ_STRU
 ????????  : UPHY??OAM????????NV??????,OAM??????????,??NV??????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* ????ID */
    MODEM_ID_ENUM_UINT16                    enModem;                            /* MODEM???? */
    VOS_RATMODE_ENUM_UINT32                 enRatMode;                          /* ???????? */
    VOS_UINT32                              uwNvAddr;
}UPHY_OAM_LOAD_NV_REQ_STRU;




/*****************************************************************************
 ??????    : UPHY_OAM_LOAD_NV_CNF_STRU
 ????????  : OAM????????????,??NV??????,????????CNF
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* ????ID */
    MODEM_ID_ENUM_UINT16                    enModem;                            /* MODEM???? */
    VOS_RATMODE_ENUM_UINT32                 enRatMode;                          /* ???????? */
    UPHY_OAM_RSLT_ENUM_UINT16               enRslt;                             /* ???????? */
    VOS_UINT16                              usRsv;                              /* ???? */
}UPHY_OAM_LOAD_NV_CNF_STRU;




/*****************************************************************************
 ??????    : UPHY_OAM_GET_NV_ADDR_REQ_STRU
 ????????  : OAM????????NV??????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* ????ID */
    MODEM_ID_ENUM_UINT16                    enModem;                            /* MODEM???? */
    VOS_RATMODE_ENUM_UINT32                 enRatMode;                          /* ???????? */
}UPHY_OAM_GET_NV_ADDR_REQ_STRU;



/*****************************************************************************
 ??????    : UPHY_OAM_GET_NV_ADDR_IND_STRU
 ????????  : UPHY??OAM????NV??????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* ????ID */
    MODEM_ID_ENUM_UINT16                    enModem;                            /* MODEM???? */
    VOS_RATMODE_ENUM_UINT32                 enRatMode;                          /* ???????? */
    VOS_UINT32                              uwNvAddr;
}UPHY_OAM_GET_NV_ADDR_IND_STRU;





/*****************************************************************************
 ??????    : UPHY_OAM_BOOT_INFO_REQ_STRU
 ????????  : UPHY??OAM????????,????:
             ulUmtsBandBitMap:W??????????
             ulCQIAddr:CQI????????
             ulAPTAddr:APT????????
             ulETAddr:ET????????
             UPHY_MODULE_ADDR_INFO_STRU:????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* ????ID */
    MODEM_ID_ENUM_UINT16                    enModem;                            /* MODEM???? */
    VOS_RATMODE_ENUM_UINT32                 enRatMode;                          /* ???????? */
}UPHY_OAM_BOOT_INFO_REQ_STRU;




/*****************************************************************************
 ??????    : UPHY_OAM_BOOT_INFO_IND_STRU
 ????????  : OAM????BOOT INFO??????????GPHY
             ulUmtsBandBitMap:W??????????
             ulCQIAddr:CQI????????
             ulAPTAddr:APT????????
             ulETAddr:ET????????
             PHY_MODULE_ADDR_INFO_STRU:????????????
             ??????????,????????,????????????????????,??????????????,????????.
             ????????????????????,????????????,??????????????
*****************************************************************************/

typedef struct
{
    VOS_UINT32                              ulSegSDRamAddr;                         /* ??????????????????SDRAM???????? */
    VOS_UINT32                              ulSegSDRamLength;                       /* ???????????????????? */
    VOS_UINT32                              ulSegTcmAddr;                           /* ??????????????????DSP??????AHB???? */
}UPHY_MODULE_ADDR_INFO_STRU;

typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* ????ID */
    MODEM_ID_ENUM_UINT16                    enModem;                            /* MODEM???? */
    VOS_RATMODE_ENUM_UINT32                 enRatMode;                          /* ???????? */
    VOS_UINT32                              ulUmtsBandBitMap;                   /* ???????????? */
    VOS_UINT32                              ulCQIAddr;                          /* CQI????SDRAM?????????? */
    VOS_UINT32                              ulAPTAddr;                          /* APT??????:????V3R3?????????????? */
    VOS_UINT32                              ulETAddr;                           /* ET??????:????V3R3?????????????? */
    UPHY_MODULE_ADDR_INFO_STRU              astPhyModuleAddrInfo[UPHY_DYN_CODE_MODULE_BUTT];
}UPHY_OAM_BOOT_INFO_IND_STRU;






/*****************************************************************************
 ??????    : UPHY_OAM_WAKE_CMD_STRU
 ????????  : OAM??UPHY_DRX????????:??????????:MODEM/MODE/????/????/????/????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* ????ID */
    MODEM_ID_ENUM_UINT16                    enModem;                            /* MODEM???? */
    VOS_RATMODE_ENUM_UINT32                 enRatMode;                          /* ???????? */
    UPHY_OAM_WAKE_TYPE_ENUM_UINT32          enWakeType;                         /* ???????? */
    VOS_UINT8                               pRecordInfo[4];                     /* ???????????????????? */
}UPHY_OAM_WAKE_CMD_STRU;



/*****************************************************************************
 ??????    : UPHY_OAM_SLEEP_IND_STRU
 ????????  : UPHY_DRX ??OAM??????????????????:MODEM/MODE/????/????/????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* ????ID */
    MODEM_ID_ENUM_UINT16                    enModem;                            /* MODEM???? */
    VOS_RATMODE_ENUM_UINT32                 enRatMode;                          /* ???????? */
    VOS_UINT32                              uwCurSlice;                         /* ????Slice */
    VOS_UINT32                              uwCalSleepLen;                      /* ?????????????? */
    VOS_UINT32                              uwCalCLkSwitchLen;                  /* ?????????????????? */
    VOS_UINT32                              uwExptWakeSlice;                    /* ?????????????? */
    VOS_UINT32                              uwCfgGaugePara;                     /* ?????????????? */
    VOS_UINT32                              uwCfgSleepLen;                      /* ?????????????? */
    VOS_UINT32                              uwCfgClkSwitchLen;                  /* ?????????????????? */
}UPHY_OAM_SLEEP_IND_STRU;





/*****************************************************************************
 ??????    : PHY_OAM_LOAD_PHY_REQ_STRU
 ????????  : OAM????????W/GPHY,????????,????/??????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* ????ID */
    MODEM_ID_ENUM_UINT16                    enModem;                            /* MODEM???? */
    VOS_RATMODE_ENUM_UINT32                 enRatMode;                          /* ???????? */
    UPHY_OAM_BUSINESS_TYPE_ENUM_UINT16      enBusinessType;                     /* ???????????? */
    VOS_UINT16                              usRsv;                              /* ???? */
}PHY_OAM_LOAD_PHY_REQ_STRU;





/*****************************************************************************
 ??????    : PHY_OAM_LOAD_PHY_CNF_STRU
 ????????  : W/GPHY??????LOAD??????????????????CNF
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* ????ID */
    MODEM_ID_ENUM_UINT16                    enModem;                            /* MODEM???? */
    VOS_RATMODE_ENUM_UINT32                 enRatMode;                          /* ???????? */
    UPHY_OAM_RSLT_ENUM_UINT16               enRslt;                             /* ???????? */
    VOS_UINT16                              usRsv;                              /* ???? */
}PHY_OAM_LOAD_PHY_CNF_STRU;



/*****************************************************************************
 ??????    : PHY_OAM_SET_WORK_MODE_REQ_STRU
 ????????  : OAM????SET_WORK_MODE??W/GPHY,????????,????/??????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* ????ID */
    MODEM_ID_ENUM_UINT16                    enModem;                            /* MODEM???? */
    VOS_RATMODE_ENUM_UINT32                 enMasterMode;                       /* ???????? */
    VOS_RATMODE_ENUM_UINT32                 enSlaveMode;                        /* ???????? */
    UPHY_OAM_BUSINESS_TYPE_ENUM_UINT16      enBusinessType;                     /* ???????????? */
    UPHY_OAM_BOOL_ENUM_UINT16               enPhyInitFlag;                      /* ??????????????PHY */
    UPHY_OAM_BOOL_ENUM_UINT16               enNvUpdateFlag;                     /* ????????????NV?? */
    VOS_UINT16                              sRsv;
}PHY_OAM_SET_WORK_MODE_REQ_STRU;



/*****************************************************************************
 ??????    : PHY_OAM_SET_WORK_MODE_CNF_STRU
 ????????  : W/GPHY??????SET_WORK_MODE??????????????????CNF
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* ????ID */
    MODEM_ID_ENUM_UINT16                    enModem;                            /* MODEM???? */
    VOS_RATMODE_ENUM_UINT32                 enRatMode;                          /* ???????? */
    UPHY_OAM_RSLT_ENUM_UINT16               enRslt;                             /* ???????? */
    VOS_UINT16                              usRsv;                              /* ???? */
}PHY_OAM_SET_WORK_MODE_CNF_STRU;



/*****************************************************************************
 ??????    : PHY_OAM_SAR_CTRL_REQ_STRU
 ????????  : OAM??W/GPHY????SAR????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* ????ID */
    VOS_UINT16                              usRsv;                              /* ???? */
    VOS_UINT32                              ulMask;                             /* ???????? */
    VOS_INT32                               lAntenStatus;                       /* ????????????????????mask??PHY_OM_SAR_MASK_ANTSTATE??????????????,????????-1????????????????????*/
    VOS_UINT32                              ulSarReduction;                     /* ????????????,????mask??PHY_OM_SAR_MASK_REDUCTION??,??????????*/
}PHY_OAM_SAR_CTRL_REQ_STRU;




/*****************************************************************************
 ??????    : PHY_OAM_SAR_CTRL_CNF_STRU
 ????????  : W/GPHY??OAM????SAR????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* ????ID */
    UPHY_OAM_RSLT_ENUM_UINT16               enRslt;                             /* ???????? */
}PHY_OAM_SAR_CTRL_CNF_STRU;



/*****************************************************************************
 ??????    : GPHY_OAM_RF_AGING_TEST_REQ_STRU
 ????????  : OAM??GPHY????????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* ????ID */
    VOS_UINT16                              usRsv;                              /* ???? */
    VOS_UINT16                              usFreqNum;                          /* (Band << 12) | Arfcn */
    UPHY_OAM_AGING_TEST_CTRL_ENUM_UINT16    enTxEnable;                         /* ????????????:0x5555-????????;0xAAAA-????????;TSC 0; TxData: ?????? */
    VOS_UINT16                              usModType;                          /* ????????????:0??GMSK????;1??8PSK???????? */
    VOS_UINT16                              usTxPower;                          /* ????????????,??????0.1dBm,GSM??EDGE???? */
    VOS_UINT16                              usSlotCnt;                          /* ??????????????????1~4????????????????????????????DSP????????1~4???????? */
    VOS_UINT16                              usRsv2;
}GPHY_OAM_RF_AGING_TEST_REQ_STRU;



/*****************************************************************************
 ??????    : GPHY_OAM_RF_AGING_TEST_CNF_STRU
 ????????  : OAM??GPHY??????????????????????????CNF
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* ????ID */
    UPHY_OAM_RSLT_ENUM_UINT16               enRslt;                             /* ???????? */
}GPHY_OAM_RF_AGING_TEST_CNF_STRU;



/*****************************************************************************
 ??????    : WPHY_OAM_RF_AGING_TEST_REQ_STRU
 ????????  : OAM??WPHY????????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgID;                                /* ????ID */
    VOS_UINT16                              usRsv;                                  /* ?????? */
    UPHY_OAM_AGING_TEST_CTRL_ENUM_UINT16    enTxOnOff;                              /* ????????????:0x5555-????????;0xAAAA-???????? */
    VOS_UINT16                              usTxBand;                               /* band */
    VOS_UINT16                              usTxChannel;                            /* ???? */
    VOS_UINT16                              usTxPower;                              /* ????????????,??????0.1dBm */
}WPHY_OAM_RF_AGING_TEST_REQ_STRU;


/*****************************************************************************
 ??????    : WPHY_OAM_RF_AGING_TEST_CNF_STRU
 ????????  : OAM??WPHY??????????????????????????CNF
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* ????ID */
    UPHY_OAM_RSLT_ENUM_UINT16               enRslt;                             /* ???????? */
}WPHY_OAM_RF_AGING_TEST_CNF_STRU;



/*****************************************************************************
 ??????    : WPHY_OAM_UPDATE_REG_STATE_REQ_STRU
 ????????  :
 ????????  : ??????????????????????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;
    PS_REG_UPDATE_STATE_ENUM_UINT16         enRegState;                         /* 0??????????????????????, 1???????????????? */
}WPHY_OAM_UPDATE_REG_STATE_REQ_STRU;


/*****************************************************************************
 ??????    : WPHY_OAM_UPDATE_REG_STATE_CNF_STRU
 ????????  :
 ????????  : ??????????????????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* ????ID */
    UPHY_OAM_RSLT_ENUM_UINT16               enRslt;                             /* ???????? */
}WPHY_OAM_UPDATE_REG_STATE_CNF_STRU;

/*****************************************************************************
 ??????    : WPHY_OAM_QUERY_SAMPLE_REQ_STRU
 ????????  : ????ACPU PHY ADDR??????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* ????ID */
    VOS_UINT16                              usRsv;                              /* ?????? */
}WPHY_OAM_QUERY_SAMPLE_REQ_STRU;

/*****************************************************************************
 ??????    : WPHY_OAM_QUERY_SAMPLE_CNF_STRU
 ????????  : ????ACPU PHY ADDR??????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* ????ID */
    VOS_UINT16                              esRslt;                             /* ????????:VOS_TURE:??????????????????VOS_FALSE:???????????????? */
    VOS_UINT32                              ulPhyAddr;                          /* PHY???? */
    VOS_UINT32                              ulPhySize;                          /* PHY???????? */
}WPHY_OAM_QUERY_SAMPLE_CNF_STRU;

/*****************************************************************************
  7 UNION????
*****************************************************************************/


/*****************************************************************************
  8 OTHERS????
*****************************************************************************/


/*****************************************************************************
  9 ????????????
*****************************************************************************/


/*****************************************************************************
  10 ????????
*****************************************************************************/


/*****************************************************************************
 ?? ?? ??  : SLEEP_MasterWakeSlave
 ????????  : GUPHY????????????????????.
 ????????  : MODEM_ID_ENUM_UINT16      enModem   ??????????MODEM
             VOS_RATMODE_ENUM_UINT32   enRatMode ??????????MODE

 ????????  : ??

 ?? ?? ??  : VOS_UINT32
*****************************************************************************/
VOS_UINT32 SLEEP_MasterWakeSlave(
                    SLEEP_MODE_ENUM_UINT32   enRatMode );


/*****************************************************************************
 ?? ?? ??  : SLEEP_AwakeInfoGet
 ????????  : ????????????????
 ????????  : SLEEP_MODE_ENUM_UINT32 enMode  ????????
             VOS_UINT32 uLen                ??????????????,32bit??????
 ????????  : VOS_UINT32 *pstDrxInfo         ????????????????
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2014??3??11??
    ??    ??   : s00207770
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 SLEEP_AwakeInfoGet( SLEEP_MODE_ENUM_UINT32 enMode, VOS_UINT32 *pstAwakeHWInfo, VOS_UINT32 uLen );
VOS_VOID HPA_2GFrameIsr_CB(MODEM_ID_ENUM_UINT16 enModemID);
VOS_VOID HPA_3GFrameIsr_CB(MODEM_ID_ENUM_UINT16 enModemID);
extern UPHY_OAM_RTT_STATE_ENUM_UINT16 UPHY_COMM_GetRttStateInfo( MODEM_ID_ENUM_UINT16 enModemId, VOS_RATMODE_ENUM_UINT32 enRttMode );

VOS_UINT16 UPHY_DSDA_GetGsmSlaveDrxFlag( MODEM_ID_ENUM_UINT16 enModemId );

/*****************************************************************************
 ?? ?? ??  : SLEEP_BBE16CprocResumeProc
 ????????  : OAM??????????????CPROC????resume proc
 ????????  : SLEEP_BBE16_CPROC_RESUME_FUNC pFun
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??9??15??
    ??    ??   : x00306642
    ????????   : ??????????

*****************************************************************************/
typedef VOS_VOID (*SLEEP_BBE16_CPROC_WAKEUP_FUNC)(VOS_VOID* pulPara);

typedef VOS_VOID (*SLEEP_BBE16_CPROC_SLEEP_FUNC)(VOS_VOID* pulPara);

/*****************************************************************************
 ?? ?? ??  : SLEEP_BBE16CprocWakeupProc
 ????????  : OAM??????????????CPROC????Wakeup handler
 ????????  : SLEEP_BBE16_CPROC_WAKEUP_FUNC pFun,
             VOS_RATMODE_ENUM_UINT32 enMode,
             VOS_VOID* pulPara
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

*****************************************************************************/
VOS_VOID SLEEP_BBE16CprocWakeupProc(SLEEP_BBE16_CPROC_WAKEUP_FUNC pFun, VOS_RATMODE_ENUM_UINT32 enMode, VOS_VOID *pulPara);

/*****************************************************************************
 ?? ?? ??  : SLEEP_BBE16CprocSleepProc
 ????????  : OAM??????????????CPROC????Sleep handler
 ????????  : SLEEP_BBE16_CPROC_SLEEP_FUNC pFun,
             VOS_RATMODE_ENUM_UINT32 enMode,
             VOS_VOID* pulPara
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

*****************************************************************************/
VOS_VOID SLEEP_BBE16CprocSleepProc(SLEEP_BBE16_CPROC_SLEEP_FUNC pFun, VOS_RATMODE_ENUM_UINT32 enMode, VOS_VOID *pulPara);

/*****************************************************************************
 ?? ?? ??  : SLEEP_IsSlaveSleep
 ????????  : ??????????????????????????????????
 ????????  : SLEEP_MODE_ENUM_UINT32 enMode  ????????
 ????????  : ??
 ?? ?? ??  : VOS_BOOL   VOS_TRUE    ????????????????????????
                        VOS_FALSE   ??????????????????????????????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??11??30??
    ??    ??   : s00207770
    ????????   : ??????????

*****************************************************************************/
VOS_BOOL SLEEP_IsSlaveSleep(SLEEP_MODE_ENUM_UINT32 enMode);

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif





#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of gphytoolinterface.h */

