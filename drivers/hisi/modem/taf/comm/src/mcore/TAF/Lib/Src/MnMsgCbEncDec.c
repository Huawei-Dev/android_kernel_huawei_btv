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

/*****************************************************************************
  1 ??????????????
*****************************************************************************/
#include  "product_config.h"
#include  "PsTypeDef.h"
#include  "PsCommonDef.h"
#include  "MnErrorCode.h"
#include  "MnMsgApi.h"
#include  "mnmsgcbencdec.h"
#include  "MnMsgTs.h"
/* Added by f62575 for V9R1 STK????, 2013-6-26, begin */
#include  "TafStdlib.h"
/* Added by f62575 for V9R1 STK????, 2013-6-26, end */


/*lint -e767*/
#define THIS_FILE_ID                PS_FILE_ID_MNMSG_CB_ENCDEC_C
/*lint +e767 */

/*lint -save -e958 */

/*****************************************************************************
  2 ??????
*****************************************************************************/

#define MSG_CBPAGE_HEADER_LEN                               6

/*****************************************************************************
  3 ????????
*****************************************************************************/


/*****************************************************************************
  4 ????????????
*****************************************************************************/


/*****************************************************************************
  5 ??????????
*****************************************************************************/


/*****************************************************************************
  6 ????????
*****************************************************************************/


/*****************************************************************************
  7 STRUCT????
*****************************************************************************/
typedef struct
{
    MN_MSG_ISO639_LANG_ENUM_U16         enIso639Lang;
    VOS_UINT8                           aucReserve1[1];
    MN_MSG_CBLANG_ENUM_U8               enLang;
}MN_MSG_LANG_CONVERT_STRU;


/*****************************************************************************
  8 UNION????
*****************************************************************************/


/*****************************************************************************
  9 OTHERS????
*****************************************************************************/

LOCAL MN_MSG_LANG_CONVERT_STRU f_astMsgCbLangTable[MN_MSG_MAX_LANG_NUM] =
{
    {MN_MSG_ISO639_LANG_GERMAN,    {0}, MN_MSG_CBLANG_GERMAN},
    {MN_MSG_ISO639_LANG_ENGLISH,   {0}, MN_MSG_CBLANG_ENGLISH},
    {MN_MSG_ISO639_LANG_ITALIAN,   {0}, MN_MSG_CBLANG_ITALIAN},
    {MN_MSG_ISO639_LANG_FRENCH,    {0}, MN_MSG_CBLANG_FRENCH},
    {MN_MSG_ISO639_LANG_SPANISH,   {0}, MN_MSG_CBLANG_SPANISH},
    {MN_MSG_ISO639_LANG_DUTCH,     {0}, MN_MSG_CBLANG_DUTCH},
    {MN_MSG_ISO639_LANG_SWEDISH,   {0}, MN_MSG_CBLANG_SWEDISH},
    {MN_MSG_ISO639_LANG_DANISH,    {0}, MN_MSG_CBLANG_DANISH},
    {MN_MSG_ISO639_LANG_PORTUGUESE,{0}, MN_MSG_CBLANG_PORTUGUESE},
    {MN_MSG_ISO639_LANG_FINNISH,   {0}, MN_MSG_CBLANG_FINNISH},
    {MN_MSG_ISO639_LANG_NORWEGIAN, {0}, MN_MSG_CBLANG_NORWEGIAN},
    {MN_MSG_ISO639_LANG_GREEK,     {0}, MN_MSG_CBLANG_GREEK},
    {MN_MSG_ISO639_LANG_TURKISH,   {0}, MN_MSG_CBLANG_TURKISH},
    {MN_MSG_ISO639_LANG_HUNGARIAN, {0}, MN_MSG_CBLANG_HUNGARIAN},
    {MN_MSG_ISO639_LANG_POLISH,    {0}, MN_MSG_CBLANG_POLISH},
    {MN_MSG_ISO639_LANG_CZECH,     {0}, MN_MSG_CBLANG_CZECH},
    {MN_MSG_ISO639_LANG_HEBREW,    {0}, MN_MSG_CBLANG_HEBREW},
    {MN_MSG_ISO639_LANG_ARABIC,    {0}, MN_MSG_CBLANG_ARABIC},
    {MN_MSG_ISO639_LANG_RUSSIAN,   {0}, MN_MSG_CBLANG_RUSSIAN},
    {MN_MSG_ISO639_LANG_ICELANDIC, {0}, MN_MSG_CBLANG_ICELANDIC}
};


/*****************************************************************************
  10 ????????
*****************************************************************************/

/*****************************************************************************
 ?? ?? ??  : MN_MSG_Iso639LangToDef
 ????????  : ????ISO 639 [12]????????????????????TAF??????????????
 ????????  : enIso639Lang - ISO 639 [12]??????????????????
 ????????  : ??
 ?? ?? ??  : TAF??????????????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2006??12??20??
    ??    ??   : ?????? 62575
    ????????   : ??????????

*****************************************************************************/
MN_MSG_CBLANG_ENUM_U8 MN_MSG_Iso639LangToDef(
    MN_MSG_ISO639_LANG_ENUM_U16         enIso639Lang
)
{
    VOS_UINT8                           ucLoop;
    MN_MSG_CBLANG_ENUM_U8               enLang;

    enLang            = MN_MSG_CBLANG_MAX;
    for (ucLoop = 0; ucLoop < MN_MSG_MAX_LANG_NUM; ucLoop++)
    {
        if (enIso639Lang == f_astMsgCbLangTable[ucLoop].enIso639Lang)
        {
            enLang = f_astMsgCbLangTable[ucLoop].enLang;
            break;
        }
    }

    return enLang;
}

/*****************************************************************************
 ?? ?? ??  : MN_MSG_DecodeDcsIf01
 ????????  : ????DCS??????????????????01
 ????????  : ucDcs:DCS????????
 ????????  : pstDcsInfo:DCS????????????
 ?? ?? ??  : VOS_UINT32 :MN_ERR_NO_ERROR,????????
                         ????:????????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2010??5??14??
    ??    ??   : zhoujun /z40661
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 MN_MSG_DecodeDcsIf01(
    VOS_UINT8                           ucDcs,
    MN_MSG_CBDCS_CODE_STRU              *pstDcsInfo
)
{
    /*
    0000 GSM 7 bit default alphabet; message preceded by language indication.
    The first 3 characters of the message are a two-character representation of the
    language encoded according to ISO 639 [12], followed by a CR character. The
    CR character is then followed by 90 characters of text.
    0001 UCS2; message preceded by language indication
    The message starts with a two GSM 7-bit default alphabet character
    representation of the language encoded according to ISO 639 [12]. This is padded
    to the octet boundary with two bits set to 0 and then followed by 40 characters of
    UCS2-encoded message.
    An MS not supporting UCS2 coding will present the two character language
    identifier followed by improperly interpreted user data.
    */

    VOS_UINT32                          ulRet;

    ulRet                               = MN_ERR_NO_ERROR;
    switch(ucDcs&0x0F)
    {
        /* ??????7 Bit???? language Represetation Occupy 3 7bit,????????????????<CR>,????????????2*/
        case 0:
            pstDcsInfo->enMsgCoding     = MN_MSG_MSG_CODING_7_BIT;
            pstDcsInfo->ucLangIndLen    = 3 - 1;
            break;

        /*??????UCS2 language Represetation Occupy 2 8bit*/
        case 1:
            pstDcsInfo->enMsgCoding     = MN_MSG_MSG_CODING_UCS2;
            pstDcsInfo->ucLangIndLen    = 2;
            break;

        default:
            /*Reserved selection we don't support;*/
            /*????????Trace               ??????????*/
            ulRet = MN_ERR_CLASS_SMS_INVALID_MSG_CODING;
            break;
    }

    return ulRet;
}

/*****************************************************************************
 ?? ?? ??  : MN_MSG_DecodeDcsIf07
 ????????  : ????DCS??????????????????01xx
 ????????  : ucDcs:DCS????????
 ????????  : pstDcsInfo:DCS????????????
 ?? ?? ??  : VOS_UINT32 :MN_ERR_NO_ERROR,????????
                         ????:????????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2010??5??14??
    ??    ??   : zhoujun /z40661
    ????????   : ??????????

*****************************************************************************/
LOCAL VOS_UINT32 MN_MSG_DecodeDcsIf07(
    VOS_UINT8                           ucDcs,
    MN_MSG_CBDCS_CODE_STRU              *pstDcsInfo
)
{

    /*
    General Data Coding indication
    Bits 5..0 indicate the following:
    Bit 5, if set to 0, indicates the text is uncompressed
    Bit 5, if set to 1, indicates the text is compressed using the compression algorithm defined in
    3GPP TS 23.042 [13]
    Bit 4, if set to 0, indicates that bits 1 to 0 are reserved and have no message class meaning
    Bit 4, if set to 1, indicates that bits 1 to 0 have a message class meaning:
    Bit 1 Bit 0 Message Class:
    0 0 Class 0
    0 1 Class 1 Default meaning: ME-specific.
    1 0 Class 2 (U)SIM specific message.
    1 1 Class 3 Default meaning: TE-specific (see 3GPP TS 27.005 [8])
    Bits 3 and 2 indicate the character set being used, as follows:
    Bit 3 Bit 2 Character set:
    0 0 GSM 7 bit default alphabet
    0 1 8 bit data
    1 0 UCS2 (16 bit) [10]
    1 1 Reserved
    */

    VOS_UINT32                          ulRet;

    ulRet                           = MN_ERR_NO_ERROR;

    if ( 0x20 == (ucDcs&0x20 ))
    {
        pstDcsInfo->bCompressed     =  VOS_TRUE;
    }
    else
    {
        pstDcsInfo->bCompressed     =  VOS_FALSE;
    }
    switch((ucDcs&0x0C)>>2) /*bit2,3????????????????*/
    {
        case 0:
            pstDcsInfo->enMsgCoding = MN_MSG_MSG_CODING_7_BIT;
            break;

        case 1:
            pstDcsInfo->enMsgCoding = MN_MSG_MSG_CODING_8_BIT;
            break;

        case 2:
            pstDcsInfo->enMsgCoding = MN_MSG_MSG_CODING_UCS2;
            break;

        default:
            MN_WARN_LOG("MSG_CbDecodeDcs: Invalid message coding.");
            ulRet = MN_ERR_CLASS_SMS_INVALID_MSG_CODING;
            break;
    }

    /*????bit4??????0??????Class??????1??????Class????*/
    if (0 == (ucDcs&0x10))
    {
        pstDcsInfo->enMsgClass      = MN_MSG_MSG_CLASS_NONE;
    }
    else
    {
        pstDcsInfo->enMsgClass      = (MN_MSG_MSG_CLASS_ENUM_U8)(ucDcs&0x3);
    }


    return ulRet;
}


/*****************************************************************************
 ?? ?? ??  : MN_MSG_DecodeDcsIf09
 ????????  : ????DCS????????????????1001
 ????????  : ucDcs:DCS????????
 ????????  : pstDcsInfo:DCS????????????
 ?? ?? ??  : VOS_UINT32 :MN_ERR_NO_ERROR,????????
                         ????:????????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2010??5??14??
    ??    ??   : zhoujun /z40661
    ????????   : ??????????

*****************************************************************************/
LOCAL VOS_UINT32 MN_MSG_DecodeDcsIf09(
    VOS_UINT8                           ucDcs,
    MN_MSG_CBDCS_CODE_STRU              *pstDcsInfo
)
{
    VOS_UINT32                          ulRet;

    ulRet                           = MN_ERR_NO_ERROR;

    switch((ucDcs&0x0C)>>2) /*bit2,3????????????????*/
    {
        case 0:
            pstDcsInfo->enMsgCoding = MN_MSG_MSG_CODING_7_BIT;
            break;
        case 1:
            pstDcsInfo->enMsgCoding = MN_MSG_MSG_CODING_8_BIT;
            break;
        case 2:
            pstDcsInfo->enMsgCoding = MN_MSG_MSG_CODING_UCS2;
            break;
        default:
            MN_WARN_LOG("MSG_CbDecodeDcs: Invalid message coding.");
            ulRet = MN_ERR_CLASS_SMS_INVALID_MSG_CODING;
            break;
    }

    pstDcsInfo->enMsgClass = (MN_MSG_MSG_CLASS_ENUM_U8)(ucDcs&0x3);

    return ulRet;
}

/*****************************************************************************
 ?? ?? ??  : MN_MSG_DecodeDcsIf0F
 ????????  : ????DCS????????????????1111
 ????????  : ??
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2010??5??14??
    ??    ??   : zhoujun /z40661
    ????????   : ??????????

*****************************************************************************/
LOCAL VOS_UINT32 MN_MSG_DecodeDcsIf0F(
    VOS_UINT8                           ucDcs,
    MN_MSG_CBDCS_CODE_STRU              *pstDcsInfo
)
{
    VOS_UINT32                          ulRet;

    ulRet                           = MN_ERR_NO_ERROR;

    if ( 0 == (ucDcs & 0x04 ))
    {
        pstDcsInfo->enMsgCoding     = MN_MSG_MSG_CODING_7_BIT;
    }
    else
    {
        pstDcsInfo->enMsgCoding     = MN_MSG_MSG_CODING_8_BIT;
    }

    switch(ucDcs&0x3)
    {
        case 0:
            pstDcsInfo->enMsgClass  = MN_MSG_MSG_CLASS_NONE;
            break;
        default:
            pstDcsInfo->enMsgClass  = (MN_MSG_MSG_CLASS_ENUM_U8)(ucDcs&0x3);
            break;
    }

    return ulRet;

}

/*****************************************************************************
 ?? ?? ??  : MN_MSG_DecodeCbsDcs
 ????????  : ????????23038 5????CBS????DCS????
 ????????  : ucDcs: ????????????DCS
             pucContent: ??????????????USSD STRING????????
 ????????  : pstDcsInfo:????????DCS????
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2008??1??11??
    ??    ??   : ?????? 62575
    ????????   : ??????????
  2.??    ??   : 2012??8??10??
    ??    ??   : L00171473
    ????????   : DTS2012082204471, TQE????
  3.??    ??   : 2013??6??26??
    ??    ??   : f62575
    ????????   : V9R1 STK??????????????????MN_MSG_DecodeCbsDcs????????????????
                 ??????????pstGsmPage??????ucDcs??pucContent
  4.??    ??   : 2013??6??26??
    ??    ??   : f62575
    ????????   : V9R1 STK????
  5.??    ??   : 2013??10??08??
    ??    ??   : j00174725
    ????????   : TQE
*****************************************************************************/

VOS_UINT32 MN_MSG_DecodeCbsDcs(
    VOS_UINT8                           ucDcs,
    VOS_UINT8                          *pucContent,
    VOS_UINT32                          ulContentLength,
    MN_MSG_CBDCS_CODE_STRU             *pstDcsInfo
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           aucLang[TAF_MSG_CBA_LANG_LENGTH];
    MN_MSG_ISO639_LANG_ENUM_U16         uslang;

    ulRet                           = MN_ERR_NO_ERROR;
    /* Deleted by f62575 for V9R1 STK????, 2013-6-26, begin */
    /* Deleted by f62575 for V9R1 STK????, 2013-6-26, end */
    pstDcsInfo->ucRawDcsData        = ucDcs;
    pstDcsInfo->ucMsgCodingGroup    = (ucDcs >> 4) & 0x0f ;
    pstDcsInfo->enMsgCoding         = MN_MSG_MSG_CODING_7_BIT;
    pstDcsInfo->bCompressed         = VOS_FALSE;
    pstDcsInfo->enMsgLang           = MN_MSG_CBLANG_ENGLISH;
    pstDcsInfo->enMsgClass          = MN_MSG_MSG_CLASS_MAX;
    pstDcsInfo->ucLangIndLen        = 0;
    /* Deleted by f62575 for V9R1 STK????, 2013-6-26, begin */
    /* Deleted by f62575 for V9R1 STK????, 2013-6-26, end */


    PS_MEM_SET(aucLang, 0x00, sizeof(aucLang));


    switch (pstDcsInfo->ucMsgCodingGroup)
    {
        /*????????????0000,0011,0010*/
        case 0x00:
        case 0x02:
        case 0x03:
            pstDcsInfo->enMsgLang = (ucDcs & 0x0f) ;
            break;

        case 0x01: /*????????????0001*/
            /* Added by f62575 for V9R1 STK????, 2013-6-26, begin */
            if (ulContentLength < TAF_MSG_CBA_LANG_LENGTH)
            {
                MN_WARN_LOG("MSG_CbDecodeDcs: Invalid ulContentLength.");
                return MN_ERR_CLASS_SMS_INVALID_MSG_LANG;
            }
            /* Added by f62575 for V9R1 STK????, 2013-6-26, end */

            ulRet = MN_MSG_DecodeDcsIf01(ucDcs,pstDcsInfo);
            if ( MN_ERR_NO_ERROR != ulRet )
            {
                MN_WARN_LOG("MSG_CbDecodeDcs: Invalid Dcs Info.");
            }

            /*????????????????????????????CBS????????LangCode*/
            /* Modified by f62575 for V9R1 STK????, 2013-6-26, begin */
            ulRet = TAF_STD_UnPack7Bit(pucContent, pstDcsInfo->ucLangIndLen, 0, aucLang);
            if (VOS_OK != ulRet)
            {
                MN_WARN_LOG("MSG_CbDecodeDcs: TAF_STD_UnPack7Bit Err.");
            }
            /* Modified by f62575 for V9R1 STK????, 2013-6-26, end */

            uslang = *(MN_MSG_ISO639_LANG_ENUM_U16 *)aucLang;
            pstDcsInfo->enMsgLang = MN_MSG_Iso639LangToDef(uslang);
            break;

        /*????????????01xx  */
        case 0x04:
        case 0x05:
        case 0x06:
        case 0x07:
            ulRet = MN_MSG_DecodeDcsIf07(ucDcs,pstDcsInfo);
            if ( MN_ERR_NO_ERROR != ulRet )
            {
                MN_WARN_LOG("MSG_CbDecodeDcs: Invalid Dcs Info.");
            }
            break;

        case 0x09:/*Refer to 23038-610.doc*/
            ulRet = MN_MSG_DecodeDcsIf09(ucDcs,pstDcsInfo);
            if ( MN_ERR_NO_ERROR != ulRet )
            {
                MN_WARN_LOG("MSG_CbDecodeDcs: Invalid Dcs Info.");
            }
            break;

        case 0x0f:
            ulRet = MN_MSG_DecodeDcsIf0F(ucDcs,pstDcsInfo);
            if ( MN_ERR_NO_ERROR != ulRet )
            {
                MN_WARN_LOG("MSG_CbDecodeDcs: Invalid Dcs Info.");
            }
            break;

        default:
            MN_WARN_LOG("MSG_CbDecodeDcs: Invalid coding group.");
            ulRet = MN_ERR_CLASS_SMS_INVALID_CODING_GRP;
            break;
    }

    if ( MN_MSG_CBLANG_MAX == pstDcsInfo->enMsgLang )
    {
        pstDcsInfo->enMsgLang = MN_MSG_CBLANG_ENGLISH;
    }

    return ulRet;

}

/*****************************************************************************
 ?? ?? ??  : MSG_CbDecodeSn
 ????????  : ????????23038 5????CBS????SN
 ????????  : pstGsmPage:??????CBS??????????
 ????????  : pstSn:????????serial number????
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2008??1??11??
    ??    ??   : ?????? 62575
    ????????   : ??????????

*****************************************************************************/
LOCAL VOS_UINT32 MSG_CbDecodeSn(
    const MN_MSG_CBGSMPAGE_STRU         *pstGsmPage,
    MN_MSG_CBSN_STRU                    *pstSn
)
{
    pstSn->usRawSnData   = pstGsmPage->ucSnHigh;
    pstSn->usRawSnData   = (VOS_UINT16)(pstSn->usRawSnData << 8) | pstGsmPage->ucSnLow;
    pstSn->enGs          = (pstSn->usRawSnData >> 14) & 0x0003;
    pstSn->usMessageCode = (VOS_UINT16)((pstSn->usRawSnData >> 4 ) & 0x03ff);
    pstSn->ucUpdateNumber=  pstSn->usRawSnData        & 0x000f;

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 ?? ?? ??  : MN_MSG_DecodeCbsPage
 ????????  : ????GSM??????????????????, Refer to 23041 9.4.1??23038 5
 ????????  : pstGsmPage  - CBS??????TPDU????
 ????????  : pstPage     - CBS????????????????????????????
 ?? ?? ??  : ??
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2006??12??20??
    ??    ??   : ?????? 62575
    ????????   : ??????????

  2.??    ??   : 2010??7??12??
    ??    ??   : zhoujun /40661
    ????????   : ????????????????????????
  3.??    ??   : 2012??4??5??
    ??    ??   : l00171473
    ????????   : for V7R1C50 CSFB&PPAC&ETWS&ISR
  4.??    ??   : 2012??4??11??
    ??    ??   : l00171473
    ????????   : DTS2012041103201, 7Bit????8Bit????????????
  5.??    ??   : 2013??6??26??
    ??    ??   : f62575
    ????????   : V9R1 STK????
  6.??    ??   : 2013??10??08??
    ??    ??   : j00174725
    ????????   : TQE
  7.??    ??   : 2015??12??10??
    ??    ??   : s00217060
    ????????   : DTS2015120405133:??????????????????copy????
*****************************************************************************/
VOS_UINT32  MN_MSG_DecodeCbmPage(
    const MN_MSG_CBRAW_TS_DATA_STRU     *pstCbRawInfo,
    MN_MSG_CBPAGE_STRU                  *pstCbmPageInfo
)
{
    VOS_UINT32                          ulRet;
    MN_MSG_CBGSMPAGE_STRU               *pstGsmPage;
    VOS_UINT32                          ulDataLen;

    /*????????????????????*/
    if ((VOS_NULL_PTR == pstCbRawInfo)
     || (VOS_NULL_PTR == pstCbmPageInfo))
    {
        MN_ERR_LOG("MN_MSG_DecodeCbmPage: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    pstGsmPage = (MN_MSG_CBGSMPAGE_STRU   *)pstCbRawInfo->aucData;

    /* ????DCS */
    /* Modified by f62575 for V9R1 STK????, 2013-6-26, begin */
    ulRet = MN_MSG_DecodeCbsDcs(pstGsmPage->ucDCS,
                                pstGsmPage->aucContent,
                                TAF_CBA_MAX_CBDATA_LEN,
                                &(pstCbmPageInfo->stDcs));
    /* Modified by f62575 for V9R1 STK????, 2013-6-26, end */
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG1("MN_MSG_DecodeCbmPage:DCS Invalid:ulRet",(VOS_INT32)ulRet);
    }

    /* ????SN */
    ulRet = MSG_CbDecodeSn(pstGsmPage, &(pstCbmPageInfo->stSn));
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG1("MN_MSG_DecodeCbmPage:SN Invalid:ulRet",(VOS_INT32)ulRet);
    }

    /* ????MID */
    pstCbmPageInfo->usMid = pstGsmPage->ucMIdHigh;
    pstCbmPageInfo->usMid = (VOS_UINT16)(pstCbmPageInfo->usMid << 8) | pstGsmPage->ucMIdLow;

    /* page info */
    pstCbmPageInfo->ucPageIndex = pstGsmPage->Pagebit4;
    pstCbmPageInfo->ucPageNum = pstGsmPage->Pagesbit4;

    /* This parameter is coded as two 4-bit fields. The first field (bits 0-3) indicates the binary value of the total number of
    pages in the CBS message and the second field (bits 4-7) indicates binary the page number within that sequence. The
    coding starts at 0001, with 0000 reserved. If a mobile receives the code 0000 in either the first field or the second field
    then it shall treat the CBS message exactly the same as a CBS message with page parameter 0001 0001 (i.e. a single
    page message). */
    if ( ( 0 == pstCbmPageInfo->ucPageIndex )
      || ( 0 == pstCbmPageInfo->ucPageNum ))
    {
        pstCbmPageInfo->ucPageIndex = 1;
        pstCbmPageInfo->ucPageNum   = 1;
    }
    ulDataLen = pstCbRawInfo->ulLen - MSG_CBPAGE_HEADER_LEN;

    /* ?????? 7bit??????????????????8bit */
    if (MN_MSG_MSG_CODING_7_BIT == pstCbmPageInfo->stDcs.enMsgCoding )
    {

        pstCbmPageInfo->stContent.ulLen = (ulDataLen * 8)/7;

        if ( pstCbmPageInfo->stContent.ulLen > TAF_CBA_MAX_RAW_CBDATA_LEN )
        {
            pstCbmPageInfo->stContent.ulLen = TAF_CBA_MAX_RAW_CBDATA_LEN;
        }

        /* Modified by f62575 for V9R1 STK????, 2013-6-26, begin */
        ulRet = TAF_STD_UnPack7Bit(pstGsmPage->aucContent,
                           pstCbmPageInfo->stContent.ulLen,
                           0,
                           pstCbmPageInfo->stContent.aucContent);
        if (VOS_OK != ulRet)
        {
            MN_WARN_LOG("MN_MSG_DecodeCbmPage:TAF_STD_UnPack7Bit fail");
        }
        /* Modified by f62575 for V9R1 STK????, 2013-6-26, end */
    }
    else
    {
        pstCbmPageInfo->stContent.ulLen = ulDataLen;
        if (pstCbmPageInfo->stContent.ulLen > TAF_CBA_MAX_CBDATA_LEN)
        {
            pstCbmPageInfo->stContent.ulLen = TAF_CBA_MAX_CBDATA_LEN;
        }
        PS_MEM_CPY(pstCbmPageInfo->stContent.aucContent,
                   pstGsmPage->aucContent,
                   pstCbmPageInfo->stContent.ulLen);

    }
    return MN_ERR_NO_ERROR;
}

/* Deleted by f62575 for V9R1 STK????, 2013-6-26, begin */
/* Deleted MN_MSG_DecodeCbsDcs */
/* Deleted by f62575 for V9R1 STK????, 2013-6-26, end */

/*lint -restore */





