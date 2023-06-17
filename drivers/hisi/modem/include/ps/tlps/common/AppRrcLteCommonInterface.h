/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : AppRrcInterface.h
  Description     : AppRrcInterface.h header file
  History         :
     1.XiaoJun 58160       2009-4-29     Draft Enact
	 2.lishangfeng  55206 2011-09-11 DTS2011091100356:????????????????????????????????????Band????????
******************************************************************************/

#ifndef __APPRRCLTECOMMONINTERFACE_H__
#define __APPRRCLTECOMMONINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "vos.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

#define LMAX_NEIGHBOR_CELL_NUM    (16)
#ifndef VOS_MSG_HEADER
#define VOS_MSG_HEADER  VOS_UINT32 uwSenderCpuId;  \
                        VOS_UINT32 uwSenderPid;    \
                        VOS_UINT32 uwReceiverCpuId;\
                        VOS_UINT32 uwReceiverPid;  \
                        VOS_UINT32 uwLength;
#endif
#ifndef APP_MSG_HEADER
#define APP_MSG_HEADER                  VOS_UINT16   usOriginalId;\
                                        VOS_UINT16   usTerminalId;\
                                        VOS_UINT32   ulTimeStamp; \
                                        VOS_UINT32   ulSN;
#endif

enum RRC_OM_GET_CELL_INFO_FLAG_ENUM
{
    EN_GET_SERVICE_CELL_INFO = 0,
    EN_GET_NEIGHBOR_CELL_INFO = 1
};

typedef VOS_UINT32 RRC_OM_GET_CELL_INFO_FLAG_ENUM_UINT32;


/*****************************************************************************
 ??????    : APP_LRRC_GET_NCELL_INFO_REQ_STRU
 ????????  :
 ASN.1???? :
 ????????  : ????????APP????????????????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                       /*_H2ASN_Skip*/
    VOS_UINT32             ulMsgId;        /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32             ulOpId;
    RRC_OM_GET_CELL_INFO_FLAG_ENUM_UINT32   enCellFlag;   /*=0??????????????????=1????????????*/
}APP_LRRC_GET_NCELL_INFO_REQ_STRU;


/*****************************************************************************
 ??????    : LRRC_APP_SRVING_CELL_MEAS_RESULT_STRU
 ????????  :
 ASN.1???? :
 ????????  : ??????????????????????????????????????
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPhyCellId;/* ????id */
    VOS_INT16                           sRsrp;/* RSRP?? */
    VOS_INT16                           sRsrq;/* RSRq?? */
    VOS_INT16                           sRssi;/* RSSI?? */
}LRRC_APP_SRVING_CELL_MEAS_RESULT_STRU;


/*****************************************************************************
 ??????    : LRRC_APP_CELL_INFO_STRU
 ????????  :
 ASN.1???? :
 ????????  : ??????????????????????????????????
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreqInfo;/* ???????????? */
    VOS_UINT16                          enBandInd;/* ???????? */
    LRRC_APP_SRVING_CELL_MEAS_RESULT_STRU     stMeasRslt;
}LRRC_APP_CELL_INFO_STRU;

/*****************************************************************************
 ??????    : LRRC_APP_CELL_MEAS_INFO_STRU
 ????????  :
 ASN.1???? :
 ????????  : ??????????????????????????????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32   ulNCellNumber;
    LRRC_APP_CELL_INFO_STRU stCellMeasInfo[LMAX_NEIGHBOR_CELL_NUM];
}LRRC_APP_CELL_MEAS_INFO_STRU;

typedef LRRC_APP_CELL_MEAS_INFO_STRU LRRC_APP_SRV_CELL_MEAS_INFO_STRU;
typedef LRRC_APP_CELL_MEAS_INFO_STRU LRRC_APP_INTRA_FREQ_NCELL_MEAS_INFO_STRU;
typedef LRRC_APP_CELL_MEAS_INFO_STRU LRRC_APP_INTER_FREQ_NCELL_MEAS_INFO_STRU;


/*****************************************************************************
 ??????    : LRRC_APP_BSIC_INFO_STRU
 ????????  :
 ASN.1???? :
 ????????  : BSC????
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usNcc;
    VOS_UINT16                                              usBcc;
}LRRC_APP_BSIC_INFO_STRU;
/*****************************************************************************
 ??????    : LRRC_GERAN_NCELL_INFO_STRU
 ????????  :
 ASN.1???? :
 ????????  : L????????GSM ????????
*****************************************************************************/

typedef struct
{
    VOS_UINT16    usArfcn;
    VOS_INT16     sRSSI;
    LRRC_APP_BSIC_INFO_STRU     stBSIC;
}LRRC_GERAN_NCELL_INFO_STRU;

/*****************************************************************************
 ??????    : LRRC_UMTS_NCELL_INFO_STRU
 ????????  :
 ASN.1???? :
 ????????  : L????????UMTS??????????????
*****************************************************************************/
typedef struct
{
    VOS_UINT16    usARFCN;
    VOS_UINT16    usPrimaryScramCode;
    VOS_INT16     sCpichRscp;
    VOS_INT16     sCpichEcN0;
}LRRC_UMTS_NCELL_INFO_STRU;

/*****************************************************************************
 ??????    : LRRC_APP_INTER_RAT_UMTS_NCELL_LIST_STRU
 ????????  :
 ASN.1???? :
 ????????  : L????????UMTS????????????
*****************************************************************************/

typedef struct
{
    VOS_UINT32 ulNCellNumber;
    LRRC_UMTS_NCELL_INFO_STRU stUMTSNcellList[LMAX_NEIGHBOR_CELL_NUM];
}LRRC_APP_INTER_RAT_UMTS_NCELL_LIST_STRU;


/*****************************************************************************
 ??????    : LRRC_APP_INTER_RAT_GERAN_NCELL_LIST_STRU
 ????????  :
 ASN.1???? :
 ????????  : L????????GSM ????????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32    ulNCellNumber;
    LRRC_GERAN_NCELL_INFO_STRU stGeranNcellList[LMAX_NEIGHBOR_CELL_NUM];
}LRRC_APP_INTER_RAT_GERAN_NCELL_LIST_STRU;


/*****************************************************************************
 ??????    : LRRC_APP_NCELL_LIST_INFO_STRU
 ????????  :
 ASN.1???? :
 ????????  : ??????????????????????????????????????
*****************************************************************************/
typedef struct
{
    RRC_OM_GET_CELL_INFO_FLAG_ENUM_UINT32      enCellFlag;   /*=0??????????????????=1????????????*/
    LRRC_APP_SRV_CELL_MEAS_INFO_STRU          stSevCellInfo; /*????????????????????????band??Phycial ID,RSRP,RSRQ,RSSI*/
    LRRC_APP_INTRA_FREQ_NCELL_MEAS_INFO_STRU  stIntraFreqNcellList;/* ????????????*/
    LRRC_APP_INTER_FREQ_NCELL_MEAS_INFO_STRU  stInterFreqNcellList;/* ????????????*/
    LRRC_APP_INTER_RAT_UMTS_NCELL_LIST_STRU    stInterRATUMTSNcellList; /* WCDMA/TDSCDMA??????????*/
    LRRC_APP_INTER_RAT_GERAN_NCELL_LIST_STRU  stInterRATGeranNcellList; /* GERAN?????????? */
}LRRC_APP_NCELL_LIST_INFO_STRU;

/*****************************************************************************
 ??????    : LRRC_APP_GET_NCELL_INFO_CNF_STRU
 ????????  :
 ASN.1???? :
 ????????  : ??????????????????????????????????????
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                       /*_H2ASN_Skip*/
    VOS_UINT32             ulMsgId;        /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32             ulOpId;
    VOS_UINT32             enResult;
    LRRC_APP_NCELL_LIST_INFO_STRU stNcellListInfo;
}LRRC_APP_GET_NCELL_INFO_CNF_STRU;




#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of AppRrcInterface.h */
