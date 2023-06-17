/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       :   product_nv_def.h
  History         :
******************************************************************************/

#ifndef __PRODUCT_NV_DEF_H__
#define __PRODUCT_NV_DEF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define MAX_SINGLE_GUC_BAND_CHECK_NUM       28
#define MAX_SINGLE_TL_BAND_CHECK_NUM        12
#define MAX_NV_GUC_CHECK_ITEM_NUM           32
#define MAX_NV_TL_CHECK_ITEM_NUM            64

typedef struct
{
    int reserved;
}PRODUCT_MODULE_STRU;

typedef struct
{
    u32 uwGucCrcResult;
    u32 uwTlCrcResult;
    u32 uwGucM2CrcResult;
}NV_CRC_CHECK_RESULT_STRU;

typedef struct
{
    u16 uhwTransmitMode;
    u16 uhwBand;
    u16 uhwEnable;
    u16 uhwValidCount;
    u16 auhwNeedCheckID[MAX_SINGLE_GUC_BAND_CHECK_NUM];
}SINGLE_GUC_BAND_NV_ID_STRU;

typedef struct
{
    u16 uhwTransmitMode;
    u16 uhwBand;
    u16 uhwEnable;
    u16 uhwValidCount;
    u16 auhwNeedCheckID[MAX_SINGLE_TL_BAND_CHECK_NUM];
}SINGLE_TL_BAND_NV_ID_STRU;

typedef struct
{
    SINGLE_GUC_BAND_NV_ID_STRU astNVIDCheckItem[MAX_NV_GUC_CHECK_ITEM_NUM];
}NV_GUC_CHECK_ITEM_STRU;

typedef struct
{
    SINGLE_TL_BAND_NV_ID_STRU astNVIDCheckItem[MAX_NV_TL_CHECK_ITEM_NUM];
}NV_TL_CHECK_ITEM_STRU;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
