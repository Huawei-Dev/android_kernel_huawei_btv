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
  1 ??????????
*****************************************************************************/
#include  "PsTypeDef.h"
#include  "PsCommonDef.h"
#include  "MnErrorCode.h"
#include  "MnMsgApi.h"
#include  "MnMsgTs.h"
/* Added by f62575 for V9R1 STK????, 2013-6-26, begin */
#include "TafStdlib.h"
/* Added by f62575 for V9R1 STK????, 2013-6-26, end */



/*****************************************************************************
  2 ????????
*****************************************************************************/
/*lint -e767 ??????:???? 107747;??????:??????65952;????:Log????*/
#define    THIS_FILE_ID        PS_FILE_ID_MNMSG_DECODE_C
/*lint +e767 ??????:???? 107747;??????:sunshaohua*/

/*????????????????????????*/
#define MSG_LONG_MSG_VOLUME                                 255
/*????????UD??????????*/
#define MSG_MAX_NORM_MSG_LEN                                153

/*****************************************************************************
  3 ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucFirstMsgSeqNum;
    VOS_UINT8                           ucMr;
    VOS_UINT16                          usMr;
    VOS_BOOL                            b8bitConcatMsg;
}MN_MSG_CONCENTRATE_MSG_ATTR;

/*****************************************************************************
  4 ??????
*****************************************************************************/
/*****************************************************************************
  5 ????????
*****************************************************************************/
/*lint -e958*/
/* Added by f62575 for AT Project, 2011-10-24, begin */


/* Deleted by s00217060 for VoLTE_PhaseIII  ????, 2013-12-16, begin */
/* MN_BcdToAsciiCode??MN_BcdNumberToAscii??MN_MSG_BcdAddrToAscii??????TafStdlib.c?? */
/* Deleted by s00217060 for VoLTE_PhaseIII  ????, 2013-12-16, end */


/*****************************************************************************
 ?? ?? ??  : MN_MSG_BcdAddrToAscii
 ????????  : ????????,??MN_MSG_BCD_ADDR_STRU??????????????MN_MSG_ASCII_ADDR_STRU????????
 ????????  : pstBcdAddr     - MN_MSG_BCD_ADDR_STRU????????
 ????????  : pstAsciiAddr   - MN_MSG_ASCII_ADDR_STRU????????
 ?? ?? ??  : MN_ERR_NO_ERROR??????????????????????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2008??3??12??
    ??    ??   : fuyingjun
    ????????   : ??????????
  2.??    ??   : 2013??12??23??
    ??    ??   : s00217060
    ????????   : VoLTE_PhaseIII????

*****************************************************************************/
VOS_UINT32 MN_MSG_BcdAddrToAscii(
    MN_MSG_BCD_ADDR_STRU                *pstBcdAddr,
    MN_MSG_ASCII_ADDR_STRU              *pstAsciiAddr
)
{
    VOS_UINT32                          ulRet;

    if ((VOS_NULL_PTR == pstBcdAddr)
     || (VOS_NULL_PTR == pstAsciiAddr))
    {
        MN_WARN_LOG("MN_MSG_BcdAddrToAscii: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    pstAsciiAddr->enNumType = ((pstBcdAddr->addrType >> 4) & 0x07);
    pstAsciiAddr->enNumPlan = (pstBcdAddr->addrType & 0x0f);
    if((pstBcdAddr->aucBcdNum[pstBcdAddr->ucBcdLen - 1] & 0xF0) != 0xF0)
    {
        pstAsciiAddr->ulLen = pstBcdAddr->ucBcdLen * 2;
    }
    else
    {
        pstAsciiAddr->ulLen = (pstBcdAddr->ucBcdLen * 2) - 1;
    }

    if (pstAsciiAddr->ulLen > MN_MAX_ASCII_ADDRESS_NUM)
    {
        MN_WARN_LOG("MN_MSG_BcdAddrToAscii: length of number is invalid.");
        return MN_ERR_INVALIDPARM;
    }

    /* Modified by s00217060 for VoLTE_PhaseIII  ????, 2013-12-23, begin */
    ulRet = TAF_STD_ConvertBcdNumberToAscii(pstBcdAddr->aucBcdNum, pstBcdAddr->ucBcdLen, (VOS_CHAR *)pstAsciiAddr->aucAsciiNum);
    /* Modified by s00217060 for VoLTE_PhaseIII  ????, 2013-12-23, end */
    if (MN_ERR_NO_ERROR == ulRet)
    {
        return MN_ERR_NO_ERROR;
    }
    else
    {
        return MN_ERR_INVALIDPARM;
    }
}

/*****************************************************************************
 ?? ?? ??  : MSG_DecodeTimeStamp
 ????????  : ??????????????????????????Refer to 9.2.3.11
 ????????  : pucTimeStamp TPDU??SCT????????????????
 ????????  : pstTimeStamp ??????????????????
             ulLen TPDU??SCT??????????????TPDU????????
 ?? ?? ??  : ???????? MN_ERR_NO_ERROR????????
                      ????            ????????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2008??1??7??
    ??    ??   : ?????? 62575
    ????????   : ??????????
  2.??    ??   : 2010??04??10??
    ??    ??   : f62575
    ????????   : ????????AT2D18035
                 ??PDU??????SIM??,BALONG??TP-SCTS????????????????????
  3.??    ??   : 2013??12??24??
    ??    ??   : s00217060
    ????????   : VoLTE_PhaseIII????
*****************************************************************************/
LOCAL VOS_UINT32 MSG_DecodeTimeStamp(
    const VOS_UINT8                     *pucTimeStamp,
    MN_MSG_TIMESTAMP_STRU               *pstTimeStamp,
    VOS_UINT32                          *pulLen
)
{
    VOS_BOOL                            bNegativeFlag       = VOS_FALSE;
    VOS_UINT8                           ucTimeZone;
    VOS_UINT8                           ucAbsTimeZone;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucDateInvalidType;

    if ((VOS_NULL_PTR == pucTimeStamp)
     || (VOS_NULL_PTR == pstTimeStamp)
     || (VOS_NULL_PTR == pulLen))
    {
        MN_ERR_LOG("MSG_DecodeTimeStamp: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    MN_MSG_REVERSE_BCD(pstTimeStamp->ucYear, pucTimeStamp[0]);
    MN_MSG_REVERSE_BCD(pstTimeStamp->ucMonth, pucTimeStamp[1]);
    MN_MSG_REVERSE_BCD(pstTimeStamp->ucDay, pucTimeStamp[2]);
    MN_MSG_REVERSE_BCD(pstTimeStamp->ucHour, pucTimeStamp[3]);
    MN_MSG_REVERSE_BCD(pstTimeStamp->ucMinute, pucTimeStamp[4]);
    MN_MSG_REVERSE_BCD(pstTimeStamp->ucSecond, pucTimeStamp[5]);

    ulRet = MN_MSG_ChkDate(pstTimeStamp, &ucDateInvalidType);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MSG_DecodeTimeStamp: Date is invalid.");
    }

    if (0 != (MN_MSG_TIMESTAMP_SIGN_MASK & pucTimeStamp[6]))
    {
        bNegativeFlag = VOS_TRUE;
        /*????????????????BIT3??0*/
        ucAbsTimeZone  = pucTimeStamp[6] ^ MN_MSG_TIMESTAMP_SIGN_MASK;
    }
    else
    {
        ucAbsTimeZone = pucTimeStamp[6];
    }

    /* Modified by s00217060 for VoLTE_PhaseIII  ????, 2013-12-24, begin */
    ulRet = TAF_STD_ConvertBcdToDeciDigit(ucAbsTimeZone, VOS_TRUE, &ucTimeZone);
    /* Modified by s00217060 for VoLTE_PhaseIII  ????, 2013-12-24, end */
    if ((MN_ERR_NO_ERROR != ulRet)
     || (ucTimeZone > MN_MSG_MAX_TIMEZONE_VALUE))
    {
        MN_WARN_LOG("MSG_DecodeTimeStamp: Time zone is invalid.");
    }

    pstTimeStamp->cTimezone = (VOS_INT8)ucTimeZone;
    if (VOS_TRUE == bNegativeFlag)
    {
        pstTimeStamp->cTimezone *= (-1);
    }

    *pulLen = MN_MSG_ABSOLUTE_TIMESTAMP_LEN;
    return MN_ERR_NO_ERROR;
}


/*****************************************************************************
 ?? ?? ??  : MSG_ConvertBcdNumberToAscii
 ????????  : ??BCD????????????????Ascii??????????
 ????????  : pBcdNumber     - BCD????
             ucBcdLen       - BCD??????????
 ????????  : pcAsciiNumber  - ??????????ASCII????(??'\0'????)
 ?? ?? ??  :
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??10??05??
    ??    ??   : f00317170
    ????????   : ??????????
*****************************************************************************/
VOS_UINT32  MSG_ConvertBcdNumberToAscii(
    const VOS_UINT8                    *pucBcdNumber,
    VOS_UINT8                           ucBcdLen,
    VOS_CHAR                           *pcAsciiNumber
)
{
    VOS_CHAR                            cAsciiNumber;
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucLen;
    VOS_UINT8                           ucBcdCode;
    VOS_UINT32                          ulRet;

    if ((VOS_NULL_PTR == pucBcdNumber)
     || (VOS_NULL_PTR == pcAsciiNumber))
    {
        return MN_ERR_NULLPTR;
    }

    /*??????????????????????????0XFF????*/
    while (ucBcdLen > 1)
    {
        if (0xFF == pucBcdNumber[ucBcdLen - 1])
        {
            ucBcdLen--;
        }
        else
        {
            break;
        }
    }

    /*????pucBcdAddress????????????????????????????????????????1111??
    ??????????????????????????????????????*/
    if ((pucBcdNumber[ucBcdLen - 1] & 0xF0) == 0xF0)
    {
        ucLen = (VOS_UINT8)((ucBcdLen * 2) - 1);
    }
    else
    {
        ucLen = (VOS_UINT8)(ucBcdLen * 2);
    }

    /*????????*/

    for (ucLoop = 0; ucLoop < ucLen; ucLoop++)
    {
        /*????????????????????????????????????????????0????????????*/
        if (1 == (ucLoop % 2))
        {
            /*????????????????????????4??????*/
            ucBcdCode = ((pucBcdNumber[(ucLoop / 2)] >> 4) & 0x0F);
        }
        else
        {
            /*????????????????????????4??????*/
            ucBcdCode = (pucBcdNumber[(ucLoop / 2)] & 0x0F);
        }

        /* ??????????????????Ascii??????, ??????????????F????????0?????? */
    	cAsciiNumber = 0;

        ulRet = TAF_STD_ConvertBcdCodeToAscii(ucBcdCode, &cAsciiNumber);
		if (MN_ERR_NO_ERROR != ulRet)
		{
			if (MN_ERR_INVALID_BCD != ulRet)
			{
				return ulRet;
			}

			MN_WARN_LOG("MSG_ConvertBcdNumberToAscii: The BCD number is invalid.");
			cAsciiNumber    = '0';
		}

		pcAsciiNumber[ucLoop] = cAsciiNumber;

	}

    pcAsciiNumber[ucLoop] = '\0';      /*????????????0*/

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 ?? ?? ??  : MN_MSG_DecodeAddress
 ????????  : ????RP-OA RP-DA??????????????????????ASCII??????????
             Refer to 24011 8.2.5.1
 ????????  : pucAddr TP????TPDU????????????????????23040 9.1.2.5 Address fields
                   ??RP??????????Refer to 24011 8.2.5.1
             bRpAddr ??????????????????RP??????????
 ????????  : pstAsciiAddr MN_MSG_ASCII_ADDR_STRU??????????????
             pulLen TP-OA,TP-DA,RP-OA??RP-DA??????????????OCTET??????
 ?? ?? ??  : ???????? MN_ERR_NO_ERROR????????
                      ????            ????????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2008??1??21??
    ??    ??   : ?????? 62575
    ????????   : ??????????
  2.??    ??   : 2012??6??26??
    ??    ??   : ?????? 62575
    ????????   : DTS2012062202118??RP????????????????????????BCD????????TP??????
                 ????7BIT??????????
  3.??    ??   : 2012??7??03??
    ??    ??   : ?????? 62575
    ????????   : DTS2012070200072??????????????????????RP??????????
  4.??    ??   : 2013??6??26??
    ??    ??   : f62575
    ????????   : V9R1 STK????
  5.??    ??   : 2013??12??23??
    ??    ??   : s00217060
    ????????   : VoLTE_PhaseIII????
  6.??    ??   : 2015??10??05??
    ??    ??   : f00317170
    ????????   : DTS2015092902663
*****************************************************************************/
VOS_UINT32 MN_MSG_DecodeAddress(
    const VOS_UINT8                     *pucAddr,
    VOS_BOOL                            bRpAddr,
    MN_MSG_ASCII_ADDR_STRU              *pstAsciiAddr,
    VOS_UINT32                          *pulLen
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulPos               = 0;
    VOS_UINT8                           ucBcdLen;

    if ((VOS_NULL_PTR == pulLen)
     || (VOS_NULL_PTR == pucAddr)
     || (VOS_NULL_PTR == pstAsciiAddr))
    {
        MN_ERR_LOG("MN_MSG_DecodeAddress: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    PS_MEM_SET(pstAsciiAddr, 0x00, sizeof(MN_MSG_ASCII_ADDR_STRU));
    /*3GPP 24011 RP DATA (Network to Mobile Station)*/
    if (VOS_TRUE == bRpAddr)
    {
        /*????????????????????????????????????(1 OCTET)*/
        /*lint -e961*/
        ucBcdLen                = pucAddr[ulPos++];
        /*lint +e961*/
        /*??????????0????????*/
        if (0 == ucBcdLen)
        {
            *pulLen = ulPos;
            return MN_ERR_NO_ERROR;
        }
        ucBcdLen -= 1;

        if ((0 == ucBcdLen)
         || (ucBcdLen > MN_MSG_MAX_BCD_NUM_LEN))
        {
            MN_WARN_LOG("MN_MSG_DecodeAddress:Invalid RP-ADDR.");
            return MN_ERR_CLASS_SMS_INVALID_SCADDR;
        }

        if ((pucAddr[(VOS_ULONG)((ulPos + 1) + (ucBcdLen - (VOS_UINT8)1))] & 0xF0) != 0xF0)
        {
            pstAsciiAddr->ulLen = ucBcdLen * 2;
        }
        else
        {
            pstAsciiAddr->ulLen = (ucBcdLen * 2) - 1;
        }
    }
    else
    {
        /*lint -e961*/
        pstAsciiAddr->ulLen     = pucAddr[ulPos++];
        /*lint +e961*/
        if (0 == pstAsciiAddr->ulLen)
        {
            pstAsciiAddr->enNumPlan = pucAddr[ulPos] &  0x0f;
            pstAsciiAddr->enNumType = (pucAddr[ulPos] >> 4) &  0x07;
            *pulLen = ulPos + 1;
            return MN_ERR_NO_ERROR;
        }

        ucBcdLen                = (VOS_UINT8)((pstAsciiAddr->ulLen + 1)/2);
    }

    if ((0 == ucBcdLen)
     || (ucBcdLen > MN_MSG_MAX_BCD_NUM_LEN))
    {
        MN_WARN_LOG("MN_MSG_DecodeAddress: invalid address length.");
        return MN_ERR_CLASS_SMS_INVALID_ADDRLEN;
    }

    pstAsciiAddr->enNumPlan = pucAddr[ulPos] &  0x0f;
    pstAsciiAddr->enNumType = (pucAddr[ulPos] >> 4) &  0x07;

    /*????????,??????????????????????*/
    ulRet = MN_ChkNumPlan(pstAsciiAddr->enNumPlan);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MN_MSG_DecodeAddress: Numbering plan is invalid");
        return ulRet;
    }
    ulRet = MN_ChkNumType(pstAsciiAddr->enNumType);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MN_MSG_DecodeAddress: Number type is invalid");
        return ulRet;
    }

    ulPos++;
    if ((VOS_TRUE != bRpAddr)
     && (MN_MSG_TON_ALPHANUMERIC == pstAsciiAddr->enNumType))
    {
        /* Modified by f62575 for V9R1 STK????, 2013-6-26, begin */
        ulRet = TAF_STD_UnPack7Bit(&(pucAddr[ulPos]),
                                   pstAsciiAddr->ulLen,
                                   0,
                                   pstAsciiAddr->aucAsciiNum);
        if (VOS_OK != ulRet)
        {
            ulRet = MN_ERR_CLASS_INVALID_TP_ADDRESS;
        }
        else
        {
            ulRet = MN_ERR_NO_ERROR;
        }

        /* Modified by f62575 for V9R1 STK????, 2013-6-26, end */
        pstAsciiAddr->ulLen = (pstAsciiAddr->ulLen * 4)/7;
    }
    else
    {
        /* Modified by s00217060 for VoLTE_PhaseIII  ????, 2013-12-23, begin */
        ulRet = TAF_STD_ConvertBcdNumberToAscii(&(pucAddr[ulPos]),
                                    ucBcdLen,
                                    (VOS_CHAR *)pstAsciiAddr->aucAsciiNum);
        /* Modified by s00217060 for VoLTE_PhaseIII  ????, 2013-12-23, end */
		if (MN_ERR_INVALID_BCD == ulRet)
		{
			ulRet = MSG_ConvertBcdNumberToAscii(&(pucAddr[ulPos]),
                                                    ucBcdLen,
                                                    (VOS_CHAR *)pstAsciiAddr->aucAsciiNum);
		}
    }
    *pulLen = 2 + ucBcdLen;

    return ulRet;
}

/*****************************************************************************
 ?? ?? ??  : MN_MSG_DecodeValidPeriod
 ????????  : ????TPDU??VP??????????????????????????
 ????????  : enVpf ??????????Refer to 9.2.3.3 TP Validity Period Format
             pucValidPeriod TPDU??VP????
 ????????  : pstValidPeriod ??????????????????????????
             pulLen TPDU??VP????????
 ?? ?? ??  : ???????? MN_ERR_NO_ERROR????????
                      ????            ????????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2008??1??7??
    ??    ??   : ?????? 62575
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 MN_MSG_DecodeValidPeriod(
    MN_MSG_VALID_PERIOD_ENUM_U8         enVpf,
    const VOS_UINT8                     *pucValidPeriod,
    MN_MSG_VALID_PERIOD_STRU            *pstValidPeriod,
    VOS_UINT32                          *pulLen
)
{
    VOS_UINT32                          ulRet               = MN_ERR_NO_ERROR;

    if ((VOS_NULL_PTR == pulLen)
     || (VOS_NULL_PTR == pucValidPeriod)
     || (VOS_NULL_PTR == pstValidPeriod))
    {
        MN_ERR_LOG("MN_MSG_DecodeValidPeriod: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    switch (enVpf)
    {
        case MN_MSG_VALID_PERIOD_NONE:
            *pulLen = 0;
            break;
        case MN_MSG_VALID_PERIOD_RELATIVE:
            *pulLen = 1;
            pstValidPeriod->u.ucOtherTime = pucValidPeriod[0];
            /* MN_MSG_DecodeRelatTime(pucValidPeriod[0], &pstValidPeriod->u.stAbsoluteTime); */
            break;
        case MN_MSG_VALID_PERIOD_ABSOLUTE:
            ulRet = MSG_DecodeTimeStamp((VOS_UINT8 *)pucValidPeriod,
                                        &(pstValidPeriod->u.stAbsoluteTime),
                                        pulLen);
            break;
        default:
            MN_WARN_LOG("MN_MSG_DecodeValidPeriod: invalid VP flag.");
            ulRet = MN_ERR_CLASS_SMS_INVALID_VPF;
            break;
    }
    pstValidPeriod->enValidPeriod = enVpf;

    return ulRet;
}

/*****************************************************************************
 ?? ?? ??  : MSG_DecodeUdhConcat8
 ????????  : Decode Concatenated Short Messages IEI, 8-bit reference number,Refer to 23040 9.2.3.24.1
 ????????  : pucUdh Concatenated Short Messages IEI
 ????????  : pstConcatenatedSms Concatenated Short Messages IEI Parameter
 ?? ?? ??  : Concatenated Short Messages IEI Length
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2008??1??12??
    ??    ??   : ?????? 62575
    ????????   : ??????????
  2.??    ??   : 2013??07??222??
    ??    ??   : j00177245
    ????????   : ????Fortify

*****************************************************************************/
LOCAL VOS_UINT8  MSG_DecodeUdhConcat8(
    const VOS_UINT8                     *pucUdh,
    MN_MSG_UDH_CONCAT_8_STRU            *pstConcatenatedSms
)
{
    VOS_UINT8                           ucPos               = 1;
    VOS_UINT8                           ucIeiLen            = 0;

    if ((VOS_NULL_PTR == pucUdh)
     || (VOS_NULL_PTR == pstConcatenatedSms))
    {
        MN_ERR_LOG("MSG_DecodeUdhConcat8: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }
    /*lint -e961*/
    ucIeiLen                        = pucUdh[ucPos++];
    if (MN_MSG_UDH_CONCAT_8_IEL != ucIeiLen)
    {
        MN_WARN_LOG("MSG_DecodeUdhConcat8: invalid IE length.");
        return 0;
    }
    pstConcatenatedSms->ucMr        = pucUdh[ucPos++];
    pstConcatenatedSms->ucTotalNum  = pucUdh[ucPos++];
    pstConcatenatedSms->ucSeqNum    = pucUdh[ucPos++];
    /*lint +e961*/

    ucIeiLen += 2;

    return ucIeiLen;
}


/*****************************************************************************
 ?? ?? ??  : MSG_DecodeUdhConcat16
 ????????  : Decode Concatenated Short Messages IEI, 16-bit reference number, Refer to 23040 9.2.3.24.8
 ????????  : pucUdh Concatenated Short Messages IEI
 ????????  : pstConcatenatedSms Concatenated Short Messages IEI Parameter
 ?? ?? ??  : Concatenated Short Messages IEI Length
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2008??1??12??
    ??    ??   : ?????? 62575
    ????????   : ??????????
  2.??    ??   : 2013??07??222??
    ??    ??   : j00177245
    ????????   : ????Fortify

*****************************************************************************/
LOCAL VOS_UINT8  MSG_DecodeUdhConcat16(
    const VOS_UINT8                     *pucUdh,
    MN_MSG_UDH_CONCAT_16_STRU           *pstConcatenatedSms
)
{
    VOS_UINT8                           ucPos               = 1;
    VOS_UINT8                           ucIeiLen            = 0;

    if ((VOS_NULL_PTR == pucUdh)
     || (VOS_NULL_PTR == pstConcatenatedSms))
    {
        MN_ERR_LOG("MSG_DecodeUdhConcat16: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }
    /*lint -e961*/
    ucIeiLen                        = pucUdh[ucPos++];
    if (MN_MSG_UDH_CONCAT_16_IEL != ucIeiLen)
    {
        MN_WARN_LOG("MSG_DecodeUdhConcat16: invalid IE length.");
        return 0;
    }
    pstConcatenatedSms->usMr        = pucUdh[ucPos++];
    pstConcatenatedSms->usMr        = (VOS_UINT16)(pstConcatenatedSms->usMr << 8) | pucUdh[ucPos++];
    pstConcatenatedSms->ucTotalNum  = pucUdh[ucPos++];
    pstConcatenatedSms->ucSeqNum    = pucUdh[ucPos++];
    /*lint +e961*/

    ucIeiLen += 2;

    return ucIeiLen;
}

/*****************************************************************************
 ?? ?? ??  : MSG_DecodeUdhSpecialSms
 ????????  : Decode Special SMS Message Indication, Refer to 23040 9.2.3.24.2
 ????????  : pucUdh Decode Special SMS Message Indication IEI
 ????????  : pstSpecialSm Decode Special SMS Message Indication IEI Parameter
 ?? ?? ??  : Special SMS Message Indication IEI Length
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2008??1??12??
    ??    ??   : ?????? 62575
    ????????   : ??????????
  2.??    ??   : 2013??07??222??
    ??    ??   : j00177245
    ????????   : ????Fortify

*****************************************************************************/
LOCAL VOS_UINT8 MSG_DecodeUdhSpecialSms(
    const VOS_UINT8                     *pucUdh,
    MN_MSG_UDH_SPECIAL_SMS_STRU         *pstSpecialSms
)
{
    VOS_UINT8                           ucPos               = 1;
    VOS_UINT8                           ucIeiLen            = 0;

    if ((VOS_NULL_PTR == pucUdh)
     || (VOS_NULL_PTR == pstSpecialSms))
    {
        MN_ERR_LOG("MSG_DecodeUdhSpecialSms: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }
    /*lint -e961*/
    ucIeiLen = pucUdh[ucPos++];
    /*lint +e961*/
    if (MN_MSG_UDH_SPECIAL_SM_IEL != ucIeiLen)
    {
        MN_WARN_LOG("MSG_DecodeUdhSpecialSms: invalid IE length.");
        return 0;
    }
    if (0 != (pucUdh[ucPos] & 0x80))
    {
        pstSpecialSms->enMsgWaiting = MN_MSG_MSG_WAITING_STORE;
    }
    else
    {
        pstSpecialSms->enMsgWaiting = MN_MSG_MSG_WAITING_DISCARD;
    }
    pstSpecialSms->enProfileId      = (pucUdh[ucPos] >> 5) & 0x03;
    pstSpecialSms->enExtMsgInd      = (pucUdh[ucPos] >> 2) & 0x07;
    pstSpecialSms->enMsgWaitingKind = pucUdh[ucPos] & 0x03;
    ucPos++;
    /*lint -e961*/
    pstSpecialSms->ucMsgCount       = pucUdh[ucPos++];
    /*lint +e961*/

    ucIeiLen += 2;

    return ucIeiLen;
}

/*****************************************************************************
 ?? ?? ??  : MSG_DecodeUdhAppPort_8
 ????????  : Decode Application Port Addressing 8 bit address Parameter IEI, Refer to 23040 9.2.3.24.3
 ????????  : pucUdh Application Port Addressing 8 bit address Parameter IEI
 ????????  : pstAppPort Application Port Addressing 8 bit address IEI Parameter
 ?? ?? ??  : Application Port Addressing 8 bit address Parameter IEI Length
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2008??1??12??
    ??    ??   : ?????? 62575
    ????????   : ??????????
  2.??    ??   : 2013??07??222??
    ??    ??   : j00177245
    ????????   : ????Fortify

*****************************************************************************/
LOCAL VOS_UINT8 MSG_DecodeUdhAppPort_8(
    const VOS_UINT8                     *pucUdh,
    MN_MSG_UDH_APPPORT_8_STRU           *pstAppPort
)
{
    VOS_UINT8                           ucPos               = 1;
    VOS_UINT8                           ucIeiLen            = 0;

    if ((VOS_NULL_PTR == pucUdh)
     || (VOS_NULL_PTR == pstAppPort))
    {
        MN_ERR_LOG("MSG_DecodeUdhAppPort_8: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }
    /*lint -e961*/
    ucIeiLen                = pucUdh[ucPos++];
    if (MN_MSG_UDH_APPPORT_8_IEL != ucIeiLen)
    {
        MN_WARN_LOG("MSG_DecodeUdhAppPort_8: invalid IE length.");
        return 0;
    }
    pstAppPort->ucDestPort  = pucUdh[ucPos++];
    pstAppPort->ucOrigPort  = pucUdh[ucPos++];
    /*lint +e961*/

    ucIeiLen += 2;

    return ucIeiLen;
}

/*****************************************************************************
 ?? ?? ??  : MSG_DecodeUdhAppPort_16
 ????????  : Decode Application Port Addressing 16 bit address Parameter IEI
 ????????  : pucUdh Application Port Addressing 16 bit address Parameter IEI
 ????????  : pstAppPort Application Port Addressing 16 bit address IEI Parameter
 ?? ?? ??  : Application Port Addressing 16 bit address Parameter IEI Length
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2008??1??12??
    ??    ??   : ?????? 62575
    ????????   : ??????????
  2.??    ??   : 2013??07??222??
    ??    ??   : j00177245
    ????????   : ????Fortify

*****************************************************************************/
LOCAL VOS_UINT8 MSG_DecodeUdhAppPort_16(
    const VOS_UINT8                     *pucUdh,
    MN_MSG_UDH_APPPORT_16_STRU          *pstAppPort
)
{
    /*Refer to 23040 9.2.3.24.4*/
    VOS_UINT8                           ucPos               = 1;
    VOS_UINT8                           ucIeiLen            = 0;

    if ((VOS_NULL_PTR == pucUdh)
     || (VOS_NULL_PTR == pstAppPort))
    {
        MN_ERR_LOG("MSG_DecodeUdhAppPort_16: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }
    /*lint -e961*/
    ucIeiLen = pucUdh[ucPos++];
    if (MN_MSG_UDH_APPPORT_16_IEL != ucIeiLen)
    {
        MN_WARN_LOG("MSG_DecodeUdhAppPort_16: invalid IE length.");
        return 0;
    }
    pstAppPort->usDestPort  = pucUdh[ucPos++];
    pstAppPort->usDestPort  = (VOS_UINT16)(pstAppPort->usDestPort << 8) | pucUdh[ucPos++];
    pstAppPort->usOrigPort  = pucUdh[ucPos++];
    pstAppPort->usOrigPort  = (VOS_UINT16)(pstAppPort->usOrigPort << 8) | pucUdh[ucPos++];
    /*lint +e961*/

    ucIeiLen += 2;

    return ucIeiLen;
}

/*****************************************************************************
 ?? ?? ??  : MSG_DecodeUdhSmscCtrl
 ????????  : ??????SMSC????????
 ????????  : pucUdh         - TPDU??????SMSC????????
 ????????  : pstSmscCtrl    - SMSC????????????????
 ?? ?? ??  : SMSC??????????TPDU????????????,??????OCTET
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2008??1??17??
    ??    ??   : ?????? 62575
    ????????   : ??????????
  2.??    ??   : 2013??07??222??
    ??    ??   : j00177245
    ????????   : ????Fortify

*****************************************************************************/
LOCAL VOS_UINT8 MSG_DecodeUdhSmscCtrl(
    const VOS_UINT8                     *pucUdh,
    MN_MSG_UDH_SMSC_CTRL_STRU           *pstSmscCtrl
)
{
    VOS_UINT8                           ucPos               = 1;
    VOS_UINT8                           ucIeiLen            = 0;

    if ((VOS_NULL_PTR == pucUdh)
     || (VOS_NULL_PTR == pstSmscCtrl))
    {
        MN_ERR_LOG("MSG_DecodeUdhSmscCtrl: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }
    /*lint -e961*/
    ucIeiLen = pucUdh[ucPos++];
    /*lint +e961*/
    if (MN_MSG_UDH_SMSCCTRL_IEL != ucIeiLen)
    {
        MN_WARN_LOG("MSG_DecodeUdhSmscCtrl: invalid IE length.");
        return 0;
    }
    if (0 != (pucUdh[ucPos] & MN_MSG_SMSCCTRL_TRANSACTION_CMPL_REPORT_MASK))
    {
        pstSmscCtrl->stSelectiveStatusReport.bCompletionReport = VOS_TRUE;
    }
    else
    {
        pstSmscCtrl->stSelectiveStatusReport.bCompletionReport = VOS_FALSE;
    }

    if (0 != (pucUdh[ucPos] & MN_MSG_SMSCCTRL_PERMANENT_ERR_REPORT_MASK))
    {
        pstSmscCtrl->stSelectiveStatusReport.bPermErrReport = VOS_TRUE;
    }
    else
    {
        pstSmscCtrl->stSelectiveStatusReport.bPermErrReport = VOS_FALSE;
    }

    if (0 != (pucUdh[ucPos] & MN_MSG_SMSCCTRL_TEMP_ERR_NOT_ATTEMPT_REPORT_MASK))
    {
        pstSmscCtrl->stSelectiveStatusReport.bTempErrNoneAttemptReport = VOS_TRUE;
    }
    else
    {
        pstSmscCtrl->stSelectiveStatusReport.bTempErrNoneAttemptReport = VOS_FALSE;
    }

    if (0 != (pucUdh[ucPos] & MN_MSG_SMSCCTRL_TEMP_ERR_ATTEMPT_REPORT_MASK))
    {
        pstSmscCtrl->stSelectiveStatusReport.bTempErrWithAttemptReport = VOS_TRUE;
    }
    else
    {
        pstSmscCtrl->stSelectiveStatusReport.bTempErrWithAttemptReport = VOS_FALSE;
    }

    if (0 != (pucUdh[ucPos] & MN_MSG_SMSCCTRL_DEACT_STATUS_REPORT_MASK))
    {
        pstSmscCtrl->stSelectiveStatusReport.bActivation = VOS_TRUE;
    }
    else
    {
        pstSmscCtrl->stSelectiveStatusReport.bActivation = VOS_FALSE;
    }

    if (0 != (pucUdh[ucPos] & MN_MSG_SMSCCTRL_ORIGUDH_INCLUDE_MASK))
    {
        pstSmscCtrl->stSelectiveStatusReport.bOrigUdhInclude = VOS_TRUE;
    }
    else
    {
        pstSmscCtrl->stSelectiveStatusReport.bOrigUdhInclude = VOS_FALSE;
    }

    ucIeiLen += 2;

    return ucIeiLen;
}

/*****************************************************************************
 ?? ?? ??  : MSG_DecodeUdhSourceInd
 ????????  : Decode UDH Source Indicator IEI,Refer to 23040 9.2.3.24.6
 ????????  : pucUdh UDH Source Indicator IEI
 ????????  : pstSrcInd UDH Source Indicator IEI IEI Parameter
 ?? ?? ??  : UDH Source Indicator IEI Length
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2008??1??12??
    ??    ??   : ?????? 62575
    ????????   : ??????????
  2.??    ??   : 2013??07??222??
    ??    ??   : j00177245
    ????????   : ????Fortify

*****************************************************************************/
LOCAL VOS_UINT8 MSG_DecodeUdhSourceInd(
    const VOS_UINT8                     *pucUdh,
    MN_MSG_UDH_SOURCE_IND_STRU          *pstSrcInd
)
{
    VOS_UINT8                           ucPos               = 1;
    VOS_UINT8                           ucIeiLen            = 0;

    if ((VOS_NULL_PTR == pucUdh)
     || (VOS_NULL_PTR == pstSrcInd))
    {
        MN_ERR_LOG("MSG_DecodeUdhSourceInd: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }
    /*lint -e961*/
    ucIeiLen                = pucUdh[ucPos++];
    /*lint +e961*/
    if (MN_MSG_UDH_SOURCE_IEL != ucIeiLen)
    {
        MN_WARN_LOG("MSG_DecodeUdhSourceInd: invalid IE length.");
        return 0;
    }
    /*lint -e961*/
    pstSrcInd->enOrgEntity  = pucUdh[ucPos++];
    /*lint +e961*/

    ucIeiLen += 2;

    return ucIeiLen;
}

/*****************************************************************************
 ?? ?? ??  : MSG_DecodeUdhTextFormat
 ????????  : Decode EMS Coding Text Formatting IEI, Refer to 23040 9.2.3.24.10.1.1
 ????????  : pucUdh EMS Coding Text Formatting IEI
 ????????  : pstTextFormat EMS Coding Text Formatting IEI parameter
 ?? ?? ??  : Text Formatting EMS Coding IEI length
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2008??1??12??
    ??    ??   : ?????? 62575
    ????????   : ??????????
  2.??    ??   : 2013??07??222??
    ??    ??   : j00177245
    ????????   : ????Fortify

*****************************************************************************/
LOCAL VOS_UINT8 MSG_DecodeUdhTextFormat(
    const VOS_UINT8                     *pucUdh,
    MN_MSG_UDH_TEXT_FORMAT_STRU         *pstTextFormat
)
{
    VOS_UINT8                           ucPos               = 1;
    VOS_UINT8                           ucIeiLen            = 0;

    if ((VOS_NULL_PTR == pucUdh)
     || (VOS_NULL_PTR == pstTextFormat))
    {
        MN_ERR_LOG("MSG_DecodeUdhTextFormat: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }
    /*lint -e961*/
    ucIeiLen = pucUdh[ucPos++];
    /*lint +e961*/
    if (MN_MSG_UDH_TEXT_FORMATING_IEL != ucIeiLen)
    {
        MN_WARN_LOG("MSG_DecodeUdhTextFormat: invalid IE length.");
        return 0;
    }
    /*lint -e961*/
    pstTextFormat->ucStartPos = pucUdh[ucPos++];
    pstTextFormat->ucLen      = pucUdh[ucPos++];
    /*lint +e961*/
    if (0 != (pucUdh[ucPos] & 0x80))
    {
        pstTextFormat->bStyleStrkthrgh = VOS_TRUE;
    }
    else
    {
        pstTextFormat->bStyleStrkthrgh = VOS_FALSE;
    }
    if (0 != (pucUdh[ucPos] & 0x40))
    {
        pstTextFormat->bStyleUnderlined = VOS_TRUE;
    }
    else
    {
        pstTextFormat->bStyleUnderlined = VOS_FALSE;
    }
    if (0 != (pucUdh[ucPos] & 0x20))
    {
        pstTextFormat->bStyleItalic = VOS_TRUE;
    }
    else
    {
        pstTextFormat->bStyleItalic = VOS_FALSE;
    }
    if (0 != (pucUdh[ucPos] & 0x10))
    {
        pstTextFormat->bStyleBold = VOS_TRUE;
    }
    else
    {
        pstTextFormat->bStyleBold = VOS_FALSE;
    }
    pstTextFormat->enFontSize  = (pucUdh[ucPos] >> 2) & 0x03;
    pstTextFormat->enAlign =  pucUdh[ucPos]       & 0x03;
    ucPos++;

    /*????Color??????????*/
    if (pstTextFormat->ucLen > 1)
    {
        pstTextFormat->stColor.enForegroundColor = (pucUdh[ucPos] & 0x0f);
        pstTextFormat->stColor.enBackgroundColor = ((pucUdh[ucPos] >> 4)& 0x0f);
    }

    ucIeiLen += 2;

    return ucIeiLen;
}

/*****************************************************************************
 ?? ?? ??  : MSG_DecodeUdhPreDefSound
 ????????  : Decode EMS Coding Predefined Sound IEI
 ????????  : pucUdh EMS Coding Predefined Sound IEI
 ????????  : pstPreDftSound EMS Coding Predefined Sound IEI parameter
 ?? ?? ??  : EMS Coding Predefined Sound IEI length
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2008??1??12??
    ??    ??   : ?????? 62575
    ????????   : ??????????
  2.??    ??   : 2013??07??222??
    ??    ??   : j00177245
    ????????   : ????Fortify

*****************************************************************************/
LOCAL VOS_UINT8 MSG_DecodeUdhPreDefSound(
    const VOS_UINT8                     *pucUdh,
    MN_MSG_UDH_PRE_DEF_SOUND_STRU       *pstPreDefSound
)
{
    /*Refer                             to 23040 9.2.3.24.10.1.2*/
    VOS_UINT8                           ucPos               = 1;
    VOS_UINT8                           ucIeiLen            = 0;

    if ((VOS_NULL_PTR == pucUdh)
     || (VOS_NULL_PTR == pstPreDefSound))
    {
        MN_ERR_LOG("MSG_DecodeUdhPreDefSound: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }
    /*lint -e961*/
    ucIeiLen                        = pucUdh[ucPos++];
    if (MN_MSG_UDH_PRE_DEF_SOUND_IEL != ucIeiLen)
    {
        MN_WARN_LOG("MSG_DecodeUdhPreDefSound: invalid IE length.");
        return 0;
    }
    pstPreDefSound->ucPos           = pucUdh[ucPos++];
    pstPreDefSound->ucdNumofSound   = pucUdh[ucPos++];
    /*lint +e961*/
    ucIeiLen += 2;

    return ucIeiLen;
}

/*****************************************************************************
 ?? ?? ??  : MSG_DecodeUdhUserDefSound
 ????????  : Decode EMS Coding User Defined Sound IEI
 ????????  : pucUdh EMS Coding User Defined Sound IEI
 ????????  : pstUserDftSound EMS Coding User Defined Sound IEI parameter
 ?? ?? ??  : EMS Coding User Defined Sound IEI length
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2008??1??17??
    ??    ??   : ?????? 62575
    ????????   : ??????????
  2.??    ??   : 2013??07??222??
    ??    ??   : j00177245
    ????????   : ????Fortify
  3.??    ??   : 2015??12??10??
    ??    ??   : s00217060
    ????????   : DTS2015120405133:??????????????????copy????

*****************************************************************************/
LOCAL VOS_UINT8 MSG_DecodeUdhUserDefSound(
    const VOS_UINT8                     *pucUdh,
    MN_MSG_UDH_USER_DEF_SOUND_STRU      *pstUserDefSound
)
{
    /*Refer to 23040 9.2.3.24.10.1.3*/
    VOS_UINT8                           ucPos               = 1;
    VOS_UINT8                           ucIeiLen            = 0;

    if ((VOS_NULL_PTR == pucUdh)
     || (VOS_NULL_PTR == pstUserDefSound))
    {
        MN_ERR_LOG("MSG_DecodeUdhUserDefSound: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }
    /*lint -e961*/
    ucIeiLen                = pucUdh[ucPos++];
    if (ucIeiLen < MN_MSG_UDH_USER_DEF_SOUND_HEADER_LEN)
    {
        MN_WARN_LOG("MSG_DecodeUdhUserDefSound: invalid IE length.");
        return 0;
    }
    pstUserDefSound->ucPos  = pucUdh[ucPos++];
    /*lint +e961*/
    pstUserDefSound->ucSizeofSound = ucIeiLen - 1;
    if (pstUserDefSound->ucSizeofSound > MN_MSG_UDH_MAX_SOUND_SIZE)
    {
        pstUserDefSound->ucSizeofSound  = MN_MSG_UDH_MAX_SOUND_SIZE;
    }
    PS_MEM_CPY(pstUserDefSound->aucDefSound,
               &(pucUdh[ucPos]),
               pstUserDefSound->ucSizeofSound);
    ucIeiLen += 2;

    return ucIeiLen;
}

/*****************************************************************************
 ?? ?? ??  : MSG_DecodeUdhPreDefAnim
 ????????  : Decode EMS Coding Predefined Animation IEI, Refer to 23040 9.2.3.24.10.1.4
 ????????  : pucUdh EMS Coding Predefined Animation IEI
 ????????  : pstPreDftAnim EMS Coding Predefined Animation IEI parameter
 ?? ?? ??  : EMS Coding Predefined Animation IEI length
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2008??1??17??
    ??    ??   : ?????? 62575
    ????????   : ??????????
  2.??    ??   : 2013??07??222??
    ??    ??   : j00177245
    ????????   : ????Fortify

*****************************************************************************/
LOCAL VOS_UINT8 MSG_DecodeUdhPreDefAnim(
    const VOS_UINT8                     *pucUdh,
    MN_MSG_UDH_PRE_DEF_ANIM_STRU        *pstPreDefAnim
)
{
    VOS_UINT8                           ucPos               = 1;
    VOS_UINT8                           ucIeiLen            = 0;

    if ((VOS_NULL_PTR == pucUdh)
     || (VOS_NULL_PTR == pstPreDefAnim))
    {
        MN_ERR_LOG("MSG_DecodeUdhPreDefAnim: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }
    /*lint -e961*/
    ucIeiLen                    = pucUdh[ucPos++];
    if (MN_MSG_UDH_PRE_DEF_ANIM_IEL != ucIeiLen)
    {
        MN_WARN_LOG("MSG_DecodeUdhPreDefAnim: invalid IE length.");
        return 0;
    }
    pstPreDefAnim->ucPos        = pucUdh[ucPos++];
    pstPreDefAnim->ucNumofAnim  = pucUdh[ucPos++];
    /*lint +e961*/
    ucIeiLen += 2;

    return ucIeiLen;
}

/*****************************************************************************
 ?? ?? ??  : MSG_DecodeUdhLargeAnim
 ????????  : Decode EMS Coding Large Animation IEI, Refer to 23040 9.2.3.24.10.1.5
 ????????  : pucUdh EMS Coding Large Animation IEI
 ????????  : pstLargeAnim EMS Coding Large Animation IEI parameter
 ?? ?? ??  : EMS Coding Large Animation IEI length
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2008??1??17??
    ??    ??   : ?????? 62575
    ????????   : ??????????
  2.??    ??   : 2013??07??222??
    ??    ??   : j00177245
    ????????   : ????Fortify

*****************************************************************************/
LOCAL VOS_UINT8 MSG_DecodeUdhLargeAnim(
    const VOS_UINT8                     *pucUdh,
    MN_MSG_UDH_LARGE_ANIM_STRU          *pstLargeAnim
)
{
    VOS_UINT8                           ucPos               = 1;
    VOS_UINT8                           ucIeiLen            = 0;

    if ((VOS_NULL_PTR == pucUdh)
     || (VOS_NULL_PTR == pstLargeAnim))
    {
        MN_ERR_LOG("MSG_DecodeUdhLargeAnim: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }
    /*lint -e961*/
    ucIeiLen            = pucUdh[ucPos++];
    if (MN_MSG_UDH_LARGE_ANIM_IEL != ucIeiLen)
    {
        MN_WARN_LOG("MSG_DecodeUdhLargeAnim: invalid IE length");
        return 0;
    }
    pstLargeAnim->ucPos = pucUdh[ucPos++];
    /*lint +e961*/


    PS_MEM_CPY(pstLargeAnim->aucData, &(pucUdh[ucPos]), MN_MSG_UDH_LARGE_ANIM_SIZE);

    ucIeiLen += 2;

    return ucIeiLen;
}

/*****************************************************************************
 ?? ?? ??  : MSG_DecodeUdhSmallAnim
 ????????  : Decode EMS Coding Small Animation IEI, Refer to 23040 9.2.3.24.10.1.6
 ????????  : pucUdh EMS Coding Small Animation IEI
 ????????  : pstSmallAnim EMS Coding Small Animation IEI parameter
 ?? ?? ??  : EMS Coding Small Animation IEI length
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2008??1??17??
    ??    ??   : ?????? 62575
    ????????   : ??????????
  2.??    ??   : 2013??07??222??
    ??    ??   : j00177245
    ????????   : ????Fortify

*****************************************************************************/
LOCAL VOS_UINT8 MSG_DecodeUdhSmallAnim(
    const VOS_UINT8                     *pucUdh,
    MN_MSG_UDH_SMALL_ANIM_STRU          *pstSmallAnim
)
{
    VOS_UINT8                           ucPos               = 1;
    VOS_UINT8                           ucIeiLen            = 0;

    if ((VOS_NULL_PTR == pucUdh)
     || (VOS_NULL_PTR == pstSmallAnim))
    {
        MN_ERR_LOG("MSG_DecodeUdhSmallAnim: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }
    /*lint -e961*/
    ucIeiLen            = pucUdh[ucPos++];
    if (MN_MSG_UDH_SMALL_ANIM_IEL != ucIeiLen)
    {
        MN_WARN_LOG("MSG_DecodeUdhSmallAnim: invalid IE length");
        return 0;
    }
    pstSmallAnim->ucPos = pucUdh[ucPos++];
    /*lint +e961*/
    PS_MEM_CPY(pstSmallAnim->aucData, &(pucUdh[ucPos]), MN_MSG_UDH_SMALL_ANIM_SIZE);

    ucIeiLen += 2;

    return ucIeiLen;
}

/*****************************************************************************
 ?? ?? ??  : MSG_DecodeUdhLargePic
 ????????  : Decode EMS Coding Large Picture IEI
 ????????  : pucUdh EMS Coding Large Picture IEI
 ????????  : pstLargePicture EMS Coding Large Picture IEI parameter
 ?? ?? ??  : EMS Coding Large Picture IEI length
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2008??1??17??
    ??    ??   : ?????? 62575
    ????????   : ??????????
  2.??    ??   : 2013??07??222??
    ??    ??   : j00177245
    ????????   : ????Fortify

*****************************************************************************/
LOCAL VOS_UINT8 MSG_DecodeUdhLargePic(
    const VOS_UINT8                     *pucUdh,
    MN_MSG_UDH_LARGE_PIC_STRU           *pstLargePic
)
{
    /*Refer to 23040 9.2.3.24.10.1.7*/
    VOS_UINT8                           ucPos               = 1;
    VOS_UINT8                           ucIeiLen            = 0;

    if ((VOS_NULL_PTR == pucUdh)
     || (VOS_NULL_PTR == pstLargePic))
    {
        MN_ERR_LOG("MSG_DecodeUdhLargePic: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }
    /*lint -e961*/
    ucIeiLen                = pucUdh[ucPos++];
    if  (MN_MSG_UDH_LARGE_PIC_IEL != ucIeiLen)
    {
        MN_WARN_LOG("MSG_DecodeUdhLargePic: invalid IE length");
        return 0;
    }
    pstLargePic->ucPos  = pucUdh[ucPos++];
    /*lint +e961*/
    PS_MEM_CPY(pstLargePic->aucData, &(pucUdh[ucPos]), MN_MSG_UDH_LARGE_PIC_SIZE);

    ucIeiLen += 2;

    return ucIeiLen;
}

/*****************************************************************************
 ?? ?? ??  : MSG_DecodeUdhSmallPic
 ????????  : Decode EMS Coding Small Picture IEI, Refer to 23040 9.2.3.24.10.1.8
 ????????  : pucUdh EMS Coding Small Picture IEI
 ????????  : pstSmallPicture EMS Coding Small Picture IEI parameter
 ?? ?? ??  : EMS Coding Small Picture IEI parameter length
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2008??1??17??
    ??    ??   : ?????? 62575
    ????????   : ??????????
  2.??    ??   : 2013??07??222??
    ??    ??   : j00177245
    ????????   : ????Fortify

*****************************************************************************/
LOCAL VOS_UINT8 MSG_DecodeUdhSmallPic(
    const VOS_UINT8                     *pucUdh,
    MN_MSG_UDH_SMALL_PIC_STRU           *pstSmallPic
)
{
    VOS_UINT8                           ucPos               = 1;
    VOS_UINT8                           ucIeiLen            = 0;

    if ((VOS_NULL_PTR == pucUdh)
     || (VOS_NULL_PTR == pstSmallPic))
    {
        MN_ERR_LOG("MSG_DecodeUdhSmallPic: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }
    /*lint -e961*/
    ucIeiLen            = pucUdh[ucPos++];
    if (MN_MSG_UDH_SMALL_PIC_IEL != ucIeiLen)
    {
        MN_WARN_LOG("MSG_DecodeUdhSmallAnim: invalid IE length");
        return 0;
    }
    pstSmallPic->ucPos  = pucUdh[ucPos++];
    /*lint +e961*/
    PS_MEM_CPY(pstSmallPic->aucData, &(pucUdh[ucPos]), MN_MSG_UDH_SMALL_PIC_SIZE);

    ucIeiLen += 2;

    return ucIeiLen;
}

/*****************************************************************************
 ?? ?? ??  : MSG_DecodeUdhVarPic
 ????????  : Decode EMS Coding Variable Picture IEI
 ????????  : pucUdh EMS Coding Variable Picture IEI
 ????????  : pstVarPic EMS Coding Variable Picture IEI parameter
 ?? ?? ??  : EMS Coding Variable Picture IEI length
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2008??1??17??
    ??    ??   : ?????? 62575
    ????????   : ??????????
  2.??    ??   : 2013??07??222??
    ??    ??   : j00177245
    ????????   : ????Fortify
  3.??    ??   : 2015??12??10??
    ??    ??   : s00217060
    ????????   : DTS2015120405133:??????????????????copy????

*****************************************************************************/
LOCAL VOS_UINT8 MSG_DecodeUdhVarPic(
    const VOS_UINT8                     *pucUdh,
    MN_MSG_UDH_VAR_PIC_STRU             *pstVarPic
)
{
    /*Refer to 23040 9.2.3.24.10.1.9*/
    VOS_UINT8                           ucPos               = 1;
    VOS_UINT8                           ucIeiLen            = 0;
    VOS_UINT32                          ulPduNum;

    if ((VOS_NULL_PTR == pucUdh)
     || (VOS_NULL_PTR == pstVarPic))
    {
        MN_ERR_LOG("MSG_DecodeUdhVarPic: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }
    /*lint -e961*/
    ucIeiLen               = pucUdh[ucPos++];
    if (ucIeiLen < MN_MSG_UDH_VAR_PIC_HEADER_LEN)
    {
        MN_WARN_LOG("MSG_DecodeUdhVarPic: invalid IE length.");
        return 0;
    }
    pstVarPic->ucPos       = pucUdh[ucPos++];
    /*Horizontal dimension of the picture: ????????????????????????????OCTET????1OCTET??????8??????*/
    pstVarPic->ucHorDim    = (VOS_UINT8)(pucUdh[ucPos++] * MN_MSG_PIXELS_IN_A_OCTET);
    pstVarPic->ucVertDim   = pucUdh[ucPos++];
    /*lint +e961*/
    ulPduNum = (pstVarPic->ucHorDim/MN_MSG_PIXELS_IN_A_OCTET) * pstVarPic->ucVertDim;
    if ((ucIeiLen - MN_MSG_UDH_VAR_PIC_HEADER_LEN) != ulPduNum)
    {
        MN_WARN_LOG("MSG_DecodeUdhVarPic: invalid IE length.");
        return 0;
    }
    if (ulPduNum > MN_MSG_UDH_VAR_PIC_SIZE)
    {
        ulPduNum = MN_MSG_UDH_VAR_PIC_SIZE;
    }
    PS_MEM_CPY(pstVarPic->aucData, &(pucUdh[ucPos]), ulPduNum);

    ucIeiLen += 2;

    return ucIeiLen;
}

/*****************************************************************************
 ?? ?? ??  : MSG_DecodeUdhUserPromt
 ????????  : Decode User Prompt Indicator IEI, Refer to 23040 9.2.3.24.10.1.10
 ????????  : pucUdh User Prompt Indicator IEI
 ????????  : pstUserPrompt User Prompt Indicator IEI parameter
 ?? ?? ??  : User Prompt Indicator IEI Length
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2008??1??17??
    ??    ??   : ?????? 62575
    ????????   : ??????????
  2.??    ??   : 2013??07??222??
    ??    ??   : j00177245
    ????????   : ????Fortify

*****************************************************************************/
LOCAL VOS_UINT8 MSG_DecodeUdhUserPrompt(
    const VOS_UINT8                     *pucUdh,
    MN_MSG_UDH_USER_PROMPT_STRU         *pstUserPrompt
)
{
    VOS_UINT8                           ucPos               = 1;
    VOS_UINT8                           ucIeiLen            = 0;

    if ((VOS_NULL_PTR == pucUdh)
     || (VOS_NULL_PTR == pstUserPrompt))
    {
        MN_ERR_LOG("MSG_DecodeUdhUserPrompt: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }
    /*lint -e961*/
    ucIeiLen                        = pucUdh[ucPos++];
    if (MN_MSG_UDH_USER_PROMPT_IEL != ucIeiLen)
    {
        MN_WARN_LOG("MSG_DecodeUdhUserPrompt: invalid IE length.");
        return 0;
    }
    pstUserPrompt->ucNumofObjects   = pucUdh[ucPos++];
    /*lint +e961*/

    ucIeiLen += 2;

    return ucIeiLen;
}

/*****************************************************************************
 ?? ?? ??  : MSG_DecodeUdhRfc822
 ????????  : ????23040 9.2.3.24.10.1.10 User Prompt Indicator, Refer to 23040 9.2.3.24.11
 ????????  : pucUdh     - TPDU RFC 822 E-Mail Header IEI
 ????????  : pstRfc822  - RFC 822 E-Mail Header IEI ????????
 ?? ?? ??  : ????????????IE??????,????OCTET
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2008??1??17??
    ??    ??   : ?????? 62575
    ????????   : ??????????
  2.??    ??   : 2013??07??222??
    ??    ??   : j00177245
    ????????   : ????Fortify

*****************************************************************************/
LOCAL VOS_UINT8 MSG_DecodeUdhRfc822(
    const VOS_UINT8                     *pucUdh,
    MN_MSG_UDH_RFC822_STRU              *pstRfc822
)
{
    VOS_UINT8                           ucPos               = 1;
    VOS_UINT8                           ucIeiLen            = 0;

    if ((VOS_NULL_PTR == pucUdh)
     || (VOS_NULL_PTR == pstRfc822))
    {
        MN_ERR_LOG("MSG_DecodeUdhRfc822: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    /*lint -e961*/
    ucIeiLen                        = pucUdh[ucPos++];
    if (MN_MSG_UDH_RFC822_IEL != ucIeiLen)
    {
        MN_WARN_LOG("MSG_DecodeUdhRfc822: invalid IE length.");
        return 0;
    }
    pstRfc822->ucLen                = pucUdh[ucPos++];
    /*lint +e961*/
    ucIeiLen += 2;

    return ucIeiLen;
}

/*****************************************************************************
 ?? ?? ??  : MSG_DecodeEo
 ????????  : ????????????IE
 ????????  : pucUdh - TPDU??????????????IE
             bFirstSeg  - ??????????????
 ????????  : pstEo  - ????????IE??????????
 ?? ?? ??  : TPDU??????????????IE????????????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2008??3??10??
    ??    ??   : fuyingjun
    ????????   : ??????????
  2.??    ??   : 2013??07??222??
    ??    ??   : j00177245
    ????????   : ????Fortify
  3.??    ??   : 2015??12??10??
    ??    ??   : s00217060
    ????????   : DTS2015120405133:??????????????????copy????

*****************************************************************************/
LOCAL VOS_UINT8  MSG_DecodeEo(
    VOS_BOOL                            bFirstSeg,
    const VOS_UINT8                     *pucUdh,
    MN_MSG_UDH_EO_STRU                  *pstEo
)
{
    VOS_UINT8                           ucPos               = 1;
    VOS_UINT8                           ucIeiLen            = 0;

    if ((VOS_NULL_PTR == pucUdh)
     || (VOS_NULL_PTR == pstEo))
    {
        MN_ERR_LOG("MSG_DecodeEo: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    /*lint -e961*/
    ucIeiLen             = pucUdh[ucPos++];
    pstEo->bFirstSegment = bFirstSeg;
    if (VOS_TRUE == bFirstSeg)
    {
        if (ucIeiLen < MN_MSG_UDH_EO_HEADER_LEN)
        {
            MN_WARN_LOG("MSG_DecodeEo: invalid data length.");
            return 0;
        }
        pstEo->ucRefNum      = pucUdh[ucPos++];
        pstEo->usTotalLen    = pucUdh[ucPos++];
        pstEo->usTotalLen    = (VOS_UINT16)(pstEo->usTotalLen << 8) | pucUdh[ucPos++];
        MSG_GetObjFowardedFlag(pstEo->bObjNotFowarded, pucUdh[ucPos]);
        MSG_GetUserPromptInd(pstEo->bObjHandledAsUserPrompt, pucUdh[ucPos]);
        ucPos++;
        pstEo->enType = pucUdh[ucPos++];
    }
    /*lint +e961*/
    pstEo->usDataLen = (ucIeiLen - ucPos) + 2;

    if (pstEo->usDataLen > MN_MSG_MAX_UDH_LONG_EO_DATA_LEN)
    {
        pstEo->usDataLen = MN_MSG_MAX_UDH_LONG_EO_DATA_LEN;
    }

    PS_MEM_CPY(pstEo->aucData, &pucUdh[ucPos], pstEo->usDataLen);

    ucIeiLen += 2;

    return ucIeiLen;
}

/*****************************************************************************
 ?? ?? ??  : MSG_DecodeReo
 ????????  : ????????????????IE
 ????????  : pucUdh - TPDU??????????????????IE
 ????????  : pstReo - ????????????IE????????
 ?? ?? ??  : TPDU??????????????????IE????????????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2008??3??10??
    ??    ??   : fuyingjun
    ????????   : ??????????
  2.??    ??   : 2013??07??222??
    ??    ??   : j00177245
    ????????   : ????Fortify

*****************************************************************************/
VOS_UINT8 MSG_DecodeReo(
    const VOS_UINT8                     *pucUdh,
    MN_MSG_UDH_REO_STRU                 *pstReo
)
{
    VOS_UINT8                           ucPos               = 1;
    VOS_UINT8                           ucIeiLen            = 0;

    if ((VOS_NULL_PTR == pucUdh)
     || (VOS_NULL_PTR == pstReo))
    {
        MN_ERR_LOG("MSG_DecodeReo: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }
    /*lint -e961*/
    ucIeiLen         = pucUdh[ucPos++];
    if (MN_MSG_UDH_REO_IEL != ucIeiLen)
    {
        MN_WARN_LOG("MSG_DecodeReo: invalid data length.");
        return 0;
    }
    pstReo->ucRefNum = pucUdh[ucPos++];
    pstReo->usPos = pucUdh[ucPos++];
    pstReo->usPos = (VOS_UINT16)(pstReo->usPos << 8) | pucUdh[ucPos++];
    /*lint +e961*/
    ucIeiLen += 2;

    return ucIeiLen;
}

/*****************************************************************************
 ?? ?? ??  : MSG_DecodeCc
 ????????  : ????????????IE
 ????????  : pucUdh - TPDU??????????????IE
 ????????  : pstCc  - ????????IE????????
 ?? ?? ??  : TPDU??????????????IE????????????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2008??3??10??
    ??    ??   : fuyingjun
    ????????   : ??????????
  2.??    ??   : 2013??07??222??
    ??    ??   : j00177245
    ????????   : ????Fortify
  3.??    ??   : 2015??12??10??
    ??    ??   : s00217060
    ????????   : DTS2015120405133:??????????????????copy????

*****************************************************************************/
VOS_UINT8 MSG_DecodeCc(
    VOS_BOOL                            bFirstSeg,
    const VOS_UINT8                     *pucUdh,
    MN_MSG_UDH_CC_STRU                  *pstCc
)
{
    VOS_UINT8                           ucPos               = 1;
    VOS_UINT8                           ucIeiLen            = 0;

    if ((VOS_NULL_PTR == pucUdh)
     || (VOS_NULL_PTR == pstCc))
    {
        MN_ERR_LOG("MSG_DecodeCc: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }
    /*lint -e961*/
    ucIeiLen             = pucUdh[ucPos++];
    if (VOS_TRUE == bFirstSeg)
    {
        pstCc->enCompressionAlgorithm = pucUdh[ucPos++] & 0x0f;
        pstCc->usTotalLen = pucUdh[ucPos++];
        pstCc->usTotalLen = (VOS_UINT16)(pstCc->usTotalLen << 8) | pucUdh[ucPos++];
        if (ucIeiLen < MN_MSG_UDH_CC_HEADER_LEN)
        {
            MN_WARN_LOG("MSG_DecodeCc: invalid data length.");
            return 0;
        }
        pstCc->usDataLen = (ucIeiLen - ucPos) + 2;
    }
    else
    {
        pstCc->usDataLen = ucIeiLen;
    }
    /*lint +e961*/
    if (pstCc->usDataLen > MN_MSG_UDH_MAX_COMPRESSION_DATA_LEN)
    {
        pstCc->usDataLen = MN_MSG_UDH_MAX_COMPRESSION_DATA_LEN;
    }

    PS_MEM_CPY(pstCc->aucData, &pucUdh[ucPos], pstCc->usDataLen);

    ucIeiLen += 2;

    return ucIeiLen;
}

/*****************************************************************************
 ?? ?? ??  : MSG_DecodeObjDistrInd
 ????????  : ????????????????
 ????????  : pucUdh - TPDU??????????????????IE
 ????????  : pstObjDistr    - ????????????IE????????
 ?? ?? ??  : TPDU??????????????????IE????????????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2008??3??10??
    ??    ??   : fuyingjun
    ????????   : ??????????
  2.??    ??   : 2013??07??222??
    ??    ??   : j00177245
    ????????   : ????Fortify

*****************************************************************************/
VOS_UINT8 MSG_DecodeObjDistrInd(
    const VOS_UINT8                     *pucUdh,
    MN_MSG_UDH_OBJ_DISTR_STRU           *pstObjDistr
)
{
    VOS_UINT8                           ucPos               = 1;
    VOS_UINT8                           ucIeiLen            = 0;

    if ((VOS_NULL_PTR == pucUdh)
     || (VOS_NULL_PTR == pstObjDistr))
    {
        MN_ERR_LOG("MSG_DecodeObjDistrInd: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    /*lint -e961*/
    ucIeiLen             = pucUdh[ucPos++];
    if (MN_MSG_UDH_OBJ_DISTR_IND_IEL != ucIeiLen)
    {
        MN_WARN_LOG("MSG_DecodeObjDistrInd: invalid data length.");
        return 0;
    }
    pstObjDistr->ucIeNum = pucUdh[ucPos++];
    MSG_GetObjFowardedFlag(pstObjDistr->bObjNotFowarded, pucUdh[ucPos]);
    /*lint +e961*/

    ucIeiLen += 2;

    return ucIeiLen;
}

/*****************************************************************************
 ?? ?? ??  : MSG_DecodeHyperLinkFormat
 ????????  : ????????????????IE
 ????????  : pucUdh - TPDU??????????????????IE
 ????????  : pstHyperLinkFormat - ????????????IE????????
 ?? ?? ??  : TPDU??????????????????IE????????????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2008??3??10??
    ??    ??   : fuyingjun
    ????????   : ??????????
  2.??    ??   : 2013??07??222??
    ??    ??   : j00177245
    ????????   : ????Fortify

*****************************************************************************/
VOS_UINT8 MSG_DecodeHyperLinkFormat(
    const VOS_UINT8                     *pucUdh,
    MN_MSG_HYPERLINK_FORMAT_STRU        *pstHyperLinkFormat
)
{
    VOS_UINT8                           ucPos               = 1;
    VOS_UINT8                           ucIeiLen            = 0;

    if ((VOS_NULL_PTR == pucUdh)
     || (VOS_NULL_PTR == pstHyperLinkFormat))
    {
        MN_ERR_LOG("MSG_DecodeHyperLinkFormat: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }
    /*lint -e961*/
    ucIeiLen             = pucUdh[ucPos++];
    if (MN_MSG_UDH_HYPERLINK_FORMAT_IEL != ucIeiLen)
    {
        MN_WARN_LOG("MSG_DecodeHyperLinkFormat: invalid data length.");
        return 0;
    }
    pstHyperLinkFormat->usPos = pucUdh[ucPos++];
    pstHyperLinkFormat->usPos = (VOS_UINT16)(pstHyperLinkFormat->usPos << 8) | pucUdh[ucPos++];
    pstHyperLinkFormat->ucHyperLinkTitleLen = pucUdh[ucPos++];
    pstHyperLinkFormat->ucUrlLen = pucUdh[ucPos++];
    /*lint +e961*/
    ucIeiLen += 2;

    return ucIeiLen;
}

/*****************************************************************************
 ?? ?? ??  : MSG_DecodeReplyAddress
 ????????  : ????????????IE
 ????????  : pucUdh - TPDU??????????????IE
 ????????  : pstReplyAddr   - ????????IE????????
 ?? ?? ??  : TPDU??????????????IE????????????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2008??3??10??
    ??    ??   : fuyingjun
    ????????   : ??????????
  2.??    ??   : 2013??07??222??
    ??    ??   : j00177245
    ????????   : ????Fortify

*****************************************************************************/
VOS_UINT8 MSG_DecodeReplyAddress(
    const VOS_UINT8                     *pucUdh,
    MN_MSG_UDH_REPLY_ADDR_STRU          *pstReplyAddr
)
{
    VOS_UINT8                           ucPos               = 1;
    VOS_UINT8                           ucIeiLen            = 0;
    VOS_UINT32                          ulLen;
    VOS_UINT32                          ulRet;

    if ((VOS_NULL_PTR == pucUdh)
     || (VOS_NULL_PTR == pstReplyAddr))
    {
        MN_ERR_LOG("MSG_DecodeReplyAddress: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }
    /*lint -e961*/
    ucIeiLen = pucUdh[ucPos++];
    /*lint +e961*/
    ulRet = MN_MSG_DecodeAddress(&pucUdh[ucPos], VOS_FALSE, &pstReplyAddr->stReplyAddr, &ulLen);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MSG_DecodeReplyAddress: invalid reply address.");
        return 0;
    }

    ucIeiLen += 2;

    return ucIeiLen;
}

/*****************************************************************************
 ?? ?? ??  : MSG_DecodeWvgObj
 ????????  : ????????????????IE
 ????????  : pucUdh - TPDU??????????????????IE
 ????????  : pstWvgObj - ????????????IE????????
 ?? ?? ??  : TPDU??????????????????IE????????????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2008??3??11??
    ??    ??   : fuyingjun
    ????????   : ??????????
  2.??    ??   : 2013??07??222??
    ??    ??   : j00177245
    ????????   : ????Fortify
  3.??    ??   : 2015??12??10??
    ??    ??   : s00217060
    ????????   : DTS2015120405133:??????????????????copy????

*****************************************************************************/
VOS_UINT8 MSG_DecodeWvgObj(
    const VOS_UINT8                     *pucUdh,
    MN_MSG_UDH_WVG_OBJ_STRU             *pstWvgObj
)
{
    VOS_UINT8                           ucPos               = 1;
    VOS_UINT8                           ucIeiLen            = 0;

    if ((VOS_NULL_PTR == pucUdh)
     || (VOS_NULL_PTR == pstWvgObj))
    {
        MN_ERR_LOG("MSG_DecodeWvgObj: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    /*lint -e961*/
    ucIeiLen             = pucUdh[ucPos++];
    pstWvgObj->ucPos     = pucUdh[ucPos++];
    /*lint +e961*/
    if (ucIeiLen < MN_MSG_UDH_WVG_HEADER_LEN)
    {
        MN_WARN_LOG("MSG_DecodeWvgObj: invalid data length.");
        return 0;
    }
    pstWvgObj->ucLen     = ucIeiLen - MN_MSG_UDH_WVG_HEADER_LEN;
    if (pstWvgObj->ucLen > MN_MSG_UDH_MAX_WVG_DATA_LEN)
    {
        pstWvgObj->ucLen = MN_MSG_UDH_MAX_WVG_DATA_LEN;
    }
    PS_MEM_CPY(pstWvgObj->aucData, &pucUdh[ucPos], pstWvgObj->ucLen);

    ucIeiLen += 2;

    return ucIeiLen;
}

/*****************************************************************************
 ?? ?? ??  : MSG_DecodeUdhOther
 ????????  : ????????????????????????IEI
 ????????  : pucUdh     - TPDU??????????????????IE
 ????????  : pstOther   - ????????????IE??????????
 ?? ?? ??  : ????????????IE??????,????OCTET
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2008??1??17??
    ??    ??   : ?????? 62575
    ????????   : ??????????
  2.??    ??   : 2011??2??28??
    ??    ??   : ??????/f62575
    ????????   : ??????TMN??????IE??????????????????IE????????????IE????????
                 ??
  3.??    ??   : 2013??07??222??
    ??    ??   : j00177245
    ????????   : ????Fortify
*****************************************************************************/
LOCAL VOS_UINT8 MSG_DecodeUdhOther(
    const VOS_UINT8                     *pucUdh,
    MN_MSG_UDH_OTHER_STRU               *pstOther
)
{
    VOS_UINT8                           ucPos               = 1;
    VOS_UINT8                           ucIeiLen            = 0;

    if ((VOS_NULL_PTR == pucUdh)
     || (VOS_NULL_PTR == pstOther))
    {
        MN_ERR_LOG("MSG_DecodeUdhOther: Parameter of the function is null.");
        return 0;
    }

    ucIeiLen                        = pucUdh[ucPos];
    if (MN_MSG_UDH_OTHER_SIZE < (ucIeiLen + 2))
    {
        return 0;
    }

    pstOther->ucLen                 = ucIeiLen;
    PS_MEM_CPY(pstOther->aucData, (pucUdh + 2), pstOther->ucLen);

    ucIeiLen += 2;

    return ucIeiLen;
}

/*****************************************************************************
 ?? ?? ??  : MSG_DecodeUdh
 ????????  : ??????????????????????????????????????
 ????????  : pucUhd ????????????
             ulUdhl ????????????
 ????????  : pucNumofHeaders ????????????IE????
             pstUserDataHeader ????????????????????
 ?? ?? ??  : ??????????????????,????OCTET
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2008??1??12??
    ??    ??   : ?????? 62575
    ????????   : ??????????

*****************************************************************************/
LOCAL VOS_UINT32  MSG_DecodeUdh(
    const VOS_UINT8                     *pucUdh,
    VOS_UINT8                           ucUdhl,
    VOS_UINT8                           *pucNumofHeaders,
    MN_MSG_USER_HEADER_TYPE_STRU        *pstUserDataHeader
)
{
    VOS_UINT32                          ulLen               = 0;
    VOS_UINT32                          ulIeiLen;
    VOS_BOOL                            bFirstSeg           = VOS_FALSE;

    if ((VOS_NULL_PTR == pucUdh)
     || (VOS_NULL_PTR == pucNumofHeaders)
     || (VOS_NULL_PTR == pstUserDataHeader))
    {
        MN_ERR_LOG("MSG_DecodeUdh: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    *pucNumofHeaders = 0;
    while (ulLen < ucUdhl)
    {
        if (*pucNumofHeaders >= MN_MSG_MAX_UDH_NUM)
        {
            MN_WARN_LOG("MSG_DecodeUdh: UDH length is overflow.");
            return MN_ERR_CLASS_SMS_INVALID_TPDU;
        }
        pstUserDataHeader->enHeaderID = pucUdh[ulLen];
        switch (pstUserDataHeader->enHeaderID)
        {
            case MN_MSG_UDH_CONCAT_8:
                ulIeiLen = MSG_DecodeUdhConcat8(&pucUdh[ulLen], &pstUserDataHeader->u.stConcat_8);
                if (1 == pstUserDataHeader->u.stConcat_8.ucSeqNum)
                {
                    bFirstSeg = VOS_TRUE;
                }
                break;
            case MN_MSG_UDH_SPECIAL_SM:
                ulIeiLen = MSG_DecodeUdhSpecialSms(&pucUdh[ulLen], &pstUserDataHeader->u.stSpecial_Sms);
                break;
            case MN_MSG_UDH_PORT_8:
                ulIeiLen = MSG_DecodeUdhAppPort_8(&pucUdh[ulLen], &pstUserDataHeader->u.stAppPort_8);
                break;
            case MN_MSG_UDH_PORT_16:
                ulIeiLen = MSG_DecodeUdhAppPort_16(&pucUdh[ulLen], &pstUserDataHeader->u.stAppPort_16);
                break;
            case MN_MSG_UDH_SMSC_CTRL:
                ulIeiLen = MSG_DecodeUdhSmscCtrl(&pucUdh[ulLen], &pstUserDataHeader->u.stSmscCtrl);
                break;
            case MN_MSG_UDH_SOURCE:
                ulIeiLen = MSG_DecodeUdhSourceInd(&pucUdh[ulLen], &pstUserDataHeader->u.stSrcInd);
                break;
            case MN_MSG_UDH_CONCAT_16:
                ulIeiLen = MSG_DecodeUdhConcat16(&pucUdh[ulLen], &pstUserDataHeader->u.stConcat_16);
                if (1 == pstUserDataHeader->u.stConcat_16.ucSeqNum)
                {
                    bFirstSeg = VOS_TRUE;
                }
                break;
            case MN_MSG_UDH_TEXT_FORMATING:
                ulIeiLen = MSG_DecodeUdhTextFormat(&pucUdh[ulLen], &pstUserDataHeader->u.stText_Format);
                break;
            case MN_MSG_UDH_PRE_DEF_SOUND:
                ulIeiLen = MSG_DecodeUdhPreDefSound(&pucUdh[ulLen], &pstUserDataHeader->u.stPreDef_Sound);
                break;
            case MN_MSG_UDH_USER_DEF_SOUND:
                ulIeiLen = MSG_DecodeUdhUserDefSound(&pucUdh[ulLen], &pstUserDataHeader->u.stUserDef_Sound);
                break;
            case MN_MSG_UDH_PRE_DEF_ANIM:
                ulIeiLen = MSG_DecodeUdhPreDefAnim(&pucUdh[ulLen], &pstUserDataHeader->u.stPreDef_Anim);
                break;
            case MN_MSG_UDH_LARGE_ANIM:
                ulIeiLen = MSG_DecodeUdhLargeAnim(&pucUdh[ulLen], &pstUserDataHeader->u.stLarge_Anim);
                break;
            case MN_MSG_UDH_SMALL_ANIM:
                ulIeiLen = MSG_DecodeUdhSmallAnim(&pucUdh[ulLen], &pstUserDataHeader->u.stSmall_Anim);
                break;
            case MN_MSG_UDH_LARGE_PIC:
                ulIeiLen = MSG_DecodeUdhLargePic(&pucUdh[ulLen], &pstUserDataHeader->u.stLarge_Pic);
                break;
            case MN_MSG_UDH_SMALL_PIC:
                ulIeiLen = MSG_DecodeUdhSmallPic(&pucUdh[ulLen], &pstUserDataHeader->u.stSmall_Pic);
                break;
            case MN_MSG_UDH_VAR_PIC:
                ulIeiLen = MSG_DecodeUdhVarPic(&pucUdh[ulLen], &pstUserDataHeader->u.stVar_Pic);
                break;
            case MN_MSG_UDH_USER_PROMPT:
                ulIeiLen = MSG_DecodeUdhUserPrompt(&pucUdh[ulLen], &pstUserDataHeader->u.stUser_Prompt);
                break;
            case MN_MSG_UDH_EO:
                ulIeiLen = MSG_DecodeEo(bFirstSeg, &pucUdh[ulLen], &pstUserDataHeader->u.stEo);
                break;
            case MN_MSG_UDH_REO:
                ulIeiLen = MSG_DecodeReo(&pucUdh[ulLen], &pstUserDataHeader->u.stReo);
                break;
            case MN_MSG_UDH_CC:
                ulIeiLen = MSG_DecodeCc(bFirstSeg, &pucUdh[ulLen], &pstUserDataHeader->u.stCc);
                break;
            case MN_MSG_UDH_OBJ_DISTR_IND:
                ulIeiLen = MSG_DecodeObjDistrInd(&pucUdh[ulLen], &pstUserDataHeader->u.stObjDistr);
                break;
            case MN_MSG_UDH_STD_WVG_OBJ:
            case MN_MSG_UDH_CHAR_SIZE_WVG_OBJ:
                ulIeiLen = MSG_DecodeWvgObj(&pucUdh[ulLen], &pstUserDataHeader->u.stWvgObj);
                break;
            case MN_MSG_UDH_RFC822:
                ulIeiLen = MSG_DecodeUdhRfc822(&pucUdh[ulLen], &pstUserDataHeader->u.stRfc822);
                break;
            case MN_MSG_UDH_HYPERLINK_FORMAT:
                ulIeiLen = MSG_DecodeHyperLinkFormat(&pucUdh[ulLen], &pstUserDataHeader->u.stHyperLinkFormat);
                break;
            case MN_MSG_UDH_REPLY_ADDR:
                ulIeiLen = MSG_DecodeReplyAddress(&pucUdh[ulLen], &pstUserDataHeader->u.stReplyAddr);
                break;
            default:
                ulIeiLen = MSG_DecodeUdhOther(&pucUdh[ulLen], &pstUserDataHeader->u.stOther);
                break;

        }
        if (0 == ulIeiLen)
        {
            return MN_ERR_CLASS_SMS_INVALID_TPDU;
        }
        ulLen += ulIeiLen;
        (*pucNumofHeaders)++;
        pstUserDataHeader++;

    }
    return MN_ERR_NO_ERROR;

}

/*****************************************************************************
 ?? ?? ??  : MN_MSG_UnpackSmWithOutUdh
 ????????  : TP-UDHI????????????????TPDU????????TP-UP
 ????????  : const MN_MSG_DCS_CODE_STRU          *pstDcsInfo
             VOS_UINT8                           *pucUserData
 ????????  : VOS_UINT8                           *pucUnpackedSm
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2010??10??16??
    ??    ??   : ??????/f62575
    ????????   : ??????????
  2.??    ??   : 2011??2??28??
    ??    ??   : ??????/f62575
    ????????   : ??????????????????????????????????????????TP-UDL??????????
                 ????SM????????
  3.??    ??   : 2013??6??26??
    ??    ??   : f62575
    ????????   : V9R1 STK????
  4.??    ??   : 2017??1??23??
    ??    ??   : q00380176
    ????????   : ??????????????MN_MSG_UnpackSmWithOutUhh -> MN_MSG_UnpackSmWithOutUdh,DTS2017011304834
*****************************************************************************/
LOCAL VOS_UINT32 MN_MSG_UnpackSmWithOutUdh(
    const MN_MSG_DCS_CODE_STRU          *pstDcsInfo,
    VOS_UINT8                           *pucUserData,
    VOS_UINT8                           *pucUnpackedSm
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucUdl;
    VOS_UINT32                          ulPos;

    ulPos = 0;
    ucUdl = pucUserData[ulPos];
    ulPos++;
    /*decode SM, Refer to 23040 9.2.3.16*/
    if ((MN_MSG_MSG_CODING_7_BIT == pstDcsInfo->enMsgCoding)
     && (VOS_TRUE != pstDcsInfo->bCompressed))
    {
        /* Modified by f62575 for V9R1 STK????, 2013-6-26, begin */
        ulRet = TAF_STD_UnPack7Bit(&pucUserData[ulPos],
                                   ucUdl,
                                   0,
                                   pucUnpackedSm);

        if (VOS_OK != ulRet)
        {
            ulRet = MN_ERR_CLASS_INVALID_TP_UD;
        }
        else
        {
            ulRet = MN_ERR_NO_ERROR;
        }
        /* Modified by f62575 for V9R1 STK????, 2013-6-26, end */
    }
    else
    {
        PS_MEM_CPY(pucUnpackedSm, &pucUserData[ulPos], ucUdl);
        ulRet = MN_ERR_NO_ERROR;
    }

    return ulRet;

}

/*****************************************************************************
 ?? ?? ??  : MN_MSG_UpackSmWithUdh
 ????????  : ????????????????????????????
 ????????  : const MN_MSG_DCS_CODE_STRU         *pstDcsInfo
             VOS_UINT8                          *pucUserData
             VOS_BOOL                            bLongMsg
 ????????  : VOS_VOID                           *pUserData
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2010??10??16??
    ??    ??   : ??????/f62575
    ????????   : ??????????
  2.??    ??   : 2013??04??17??
    ??    ??   : ??????/f62575
    ????????   : DTS2013041704040, ????TP-UDHL????????????????????
                 ????UDH????????????TPUD??????
  3.??    ??   : 2013??6??26??
    ??    ??   : f62575
    ????????   : V9R1 STK????
*****************************************************************************/
LOCAL VOS_UINT32 MN_MSG_UpackSmWithUdh(
    const MN_MSG_DCS_CODE_STRU         *pstDcsInfo,
    VOS_UINT8                          *pucUserData,
    VOS_BOOL                            bLongMsg,
    VOS_VOID                           *pUserData
)
{
    MN_MSG_USER_DATA_STRU              *pstUserData;
    MN_MSG_LONG_USER_DATA_STRU         *pstLongMsgUserData;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulPos;
    VOS_UINT8                           ucUdhl;
    VOS_UINT8                           ucUdl;
    VOS_UINT8                           ucFillBit;
    VOS_UINT8                           *pucNumofHeaders;
    MN_MSG_USER_HEADER_TYPE_STRU        *pstUserDataHeader;
    VOS_UINT8                           *pucUnpackedSm;
    VOS_UINT32                          *pulLen;

    if (VOS_TRUE == bLongMsg)
    {
        pstLongMsgUserData = (MN_MSG_LONG_USER_DATA_STRU *)pUserData;
        pucNumofHeaders    = &pstLongMsgUserData->ucNumofHeaders;
        pstUserDataHeader  = pstLongMsgUserData->astUserDataHeader;
        pucUnpackedSm      = pstLongMsgUserData->pucOrgData;
        pulLen             = &pstLongMsgUserData->ulLen;
    }
    else
    {
        pstUserData        = (MN_MSG_USER_DATA_STRU *)pUserData;
        pucNumofHeaders    = &pstUserData->ucNumofHeaders;
        pstUserDataHeader  = pstUserData->astUserDataHeader;
        pucUnpackedSm      = pstUserData->aucOrgData;
        pulLen             = &pstUserData->ulLen;
    }

    ulPos   = 0;
    /*lint -e961*/
    ucUdl   = pucUserData[ulPos++];
    ucUdhl  = pucUserData[ulPos++];
    /*lint +e961*/
    ulRet   = MSG_DecodeUdh(&(pucUserData[ulPos]),
                            ucUdhl,
                            pucNumofHeaders,
                            pstUserDataHeader);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return ulRet;
    }

    /*????????????????????UDHL UDH???? */
    ulPos += ucUdhl;

    /*decode SM, Refer to 23040 9.2.3.16*/
    if ((MN_MSG_MSG_CODING_7_BIT == pstDcsInfo->enMsgCoding)
     && (VOS_TRUE != pstDcsInfo->bCompressed))
    {
        ucFillBit = (7 - (((ucUdhl + 1) * 8) % 7)) % 7;
        if (ucUdl < ((((ucUdhl + 1) * 8) + 6)/7))
        {
            MN_WARN_LOG("MN_MSG_UpackSmWithUdh: udhl is invalid.");
            return MN_ERR_CLASS_SMS_MSGLEN_OVERFLOW;
        }
        *pulLen = ucUdl - ((((ucUdhl + 1) * 8) + 6)/7);
        /* Modified by f62575 for V9R1 STK????, 2013-6-26, begin */
        ulRet = TAF_STD_UnPack7Bit(&(pucUserData[ulPos]),
                                   *pulLen,
                                   ucFillBit,
                                   pucUnpackedSm);
        if (VOS_OK != ulRet)
        {
            ulRet = MN_ERR_CLASS_INVALID_TP_UD;
        }
        else
        {
            ulRet = MN_ERR_NO_ERROR;
        }
        /* Modified by f62575 for V9R1 STK????, 2013-6-26, end */
    }
    else
    {

        if ((ucUdhl + 1) > ucUdl)
        {
            return MN_ERR_CLASS_SMS_MSGLEN_OVERFLOW;
        }

        *pulLen = ucUdl - (ucUdhl + 1);

        PS_MEM_CPY(pucUnpackedSm,
                   &(pucUserData[ulPos]),
                   *pulLen);
        ulRet = MN_ERR_NO_ERROR;
    }

    return ulRet;
}

/*****************************************************************************
 ?? ?? ??  : MSG_DecodeUserData_ForUsimMsg
 ????????  : ????????????????(UDL UDHL UDH FILLBIT SM)??
 ????????  : bUserHeader ????????????????????
                            pstDcsInfo  FILLBIT??SM??????????
                            pucUserData TPDU??????????????
 ????????  : pstUserData ??????????????????
 ?? ?? ??  : ???????? MN_ERR_NO_ERROR????????
             ????            ????????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2009??8??7??
    ??    ??   : ?????? 62575
    ????????   : ??????????
  2.??    ??   : 2009??10??28??
    ??    ??   : f62575
    ????????   : AT2D15641, STK????????????????????????????????????
  3.??    ??   : 2010??10??16??
    ??    ??   : ??????/f62575
    ????????   : DTS2010092603490????????????????????UDH??????????????
*****************************************************************************/
LOCAL VOS_UINT32 MSG_DecodeUserData_ForUsimMsg(
    VOS_BOOL                            bUserDataHeaderInd,
    const MN_MSG_DCS_CODE_STRU          *pstDcsInfo,
    VOS_UINT8                           *pucUserData,
    MN_MSG_LONG_USER_DATA_STRU          *pstUserData
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulPos               = 0;
    VOS_UINT8                           ucUdl;

    if ((VOS_NULL_PTR == pstDcsInfo)
     || (VOS_NULL_PTR == pucUserData)
     || (VOS_NULL_PTR == pstUserData))
    {
        MN_ERR_LOG("MSG_DecodeUserData_ForUsimMsg: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    pstUserData->ucNumofHeaders = 0;
    PS_MEM_SET(pstUserData->astUserDataHeader,
                          0x00,
                          (VOS_SIZE_T)(sizeof(MN_MSG_USER_HEADER_TYPE_STRU) * MN_MSG_MAX_UDH_NUM));
    ucUdl  = pucUserData[ulPos];
    if (0 == ucUdl)
    {
        pstUserData->ulLen = 0;
        return MN_ERR_NO_ERROR;
    }

    if (VOS_TRUE == bUserDataHeaderInd)
    {
        ulRet = MN_MSG_UpackSmWithUdh(pstDcsInfo,
                                      &(pucUserData[ulPos]),
                                      VOS_TRUE,
                                      (VOS_VOID *)pstUserData);
    }
    else
    {
        /*decode SM, Refer to 23040 9.2.3.16*/
        pstUserData->ulLen = ucUdl;

        ulRet = MN_MSG_UnpackSmWithOutUdh(pstDcsInfo,
                                          &(pucUserData[ulPos]),
                                          pstUserData->pucOrgData);

    }

    return ulRet;
}

/*****************************************************************************
 ?? ?? ??  : MN_MSG_Decode_UsimMsg
 ????????  : ????????,????(U)SIM????????????TPDU????
 ????????  : pucData         - (U)SIM????????????TPDU????
             ulLen           - (U)SIM????????????TPDU????????
 ????????  : pstLongSubmit   - ????(U)SIM????????????TPDU??????????????????????????
 ?? ?? ??  : VOS_UINT32:??????????????,????????????????????
 ????????  :
 ????????  :

 ????????      :
 12.??    ??   : 2009??10??28??
    ??    ??   : f62575
    ????????   : ????????????AT2D15272, STK????????????????????????????????????
*****************************************************************************/
VOS_UINT32 MN_MSG_Decode_UsimMsg(
    VOS_UINT8                           *pucData,
    VOS_UINT32                          ulLen,
    MN_MSG_SUBMIT_LONG_STRU             *pstLongSubmit
)
{
    VOS_UINT32                          ulRet               = MN_ERR_NO_ERROR;
    VOS_UINT32                          ulPos               = 0;
    VOS_UINT32                          ulDaLen;
    VOS_UINT32                          ulVpLen;
    MN_MSG_LONG_USER_DATA_STRU          *pstLongUserData;

    if ((VOS_NULL_PTR == pucData)
    || (VOS_NULL_PTR == pstLongSubmit))
    {
        MN_ERR_LOG("MN_MSG_Decode_UsimMsg: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    /*b7  b6   b5   b4   b3  b2  b1  b0
      RP  UDHI SRR  VPF      RD  MTI
      0   0    0    2        1   2
      TP MTI TP RD TP VPF TP RP TP UDHI TP SRR*/
    /*TP MTI ignore 23040 9.2.3.1 ????bit0bit1:MIT     0011 0001 */

    /*lint -e961*/
    /*TP RD  23040 9.2.3.25*/
    MSG_GET_TP_RD(pstLongSubmit->bRejectDuplicates, pucData[ulPos]);
    /*TP VPF 23040 9.2.3.3*/
    MSG_GET_TP_VPF(pstLongSubmit->stValidPeriod.enValidPeriod, pucData[ulPos]);
    /*TP RP  23040 9.2.3.17*/
    MSG_GET_TP_RP(pstLongSubmit->bReplayPath, pucData[ulPos]);
    /*TP UDHI23040 9.2.3.23*/
    MSG_GET_TP_UDHI(pstLongSubmit->bUserDataHeaderInd, pucData[ulPos]);
    /*TP SRR 23040 9.2.3.5*/
    MSG_GET_TP_SRR(pstLongSubmit->bStaRptReq, pucData[ulPos]);
    ulPos++;

    /*TP MR*/
    pstLongSubmit->ucMr = pucData[ulPos++];
    /*lint +e961*/

    /*TP DA* Refer to 9.1.2.5*/
    ulRet = MN_MSG_DecodeAddress(&(pucData[ulPos]),
                                 VOS_FALSE,
                                 &(pstLongSubmit->stDestAddr),
                                 &ulDaLen);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MN_MSG_Decode_UsimMsg: Fail to MN_MSG_DecodeAddress.");
        return ulRet;
    }
    ulPos += ulDaLen;

    /*TP PID*/
    /*lint -e961*/
    pstLongSubmit->enPid = pucData[ulPos++];
    /*lint +e961*/

    /*TP DCS 23038 4 */
    ulRet = MN_MSG_DecodeDcs(pucData[ulPos],
                                                  &(pstLongSubmit->stDcs));
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MN_MSG_Decode_UsimMsg: Fail to MN_MSG_DecodeDcs..");
        return ulRet;
    }
    ulPos ++;

    /*TP VP*/
    ulRet = MN_MSG_DecodeValidPeriod(pstLongSubmit->stValidPeriod.enValidPeriod,
                                     &(pucData[ulPos]),
                                     &(pstLongSubmit->stValidPeriod),
                                     & ulVpLen);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MN_MSG_Decode_UsimMsg: Fail to MN_MSG_DecodeValidPeriod.");
        return ulRet;
    }
    ulPos += ulVpLen;

    /*UDL UD*/
    pstLongUserData = &(pstLongSubmit->stLongUserData);
    ulRet = MSG_DecodeUserData_ForUsimMsg(pstLongSubmit->bUserDataHeaderInd,
                                          &(pstLongSubmit->stDcs),
                                          (VOS_UINT8 *)&(pucData[ulPos]),
                                          pstLongUserData);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_NORM_LOG("MN_MSG_Decode_UsimMsg: Fail to MSG_DecodeUserData_ForUsimMsg.");
        return ulRet;
    }

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 ?? ?? ??  : MSG_DecodeUserData
 ????????  : ????????????????(UDL UDHL UDH FILLBIT SM)??
 ????????  : bUserHeader ????????????????????
             pstDcsInfo  FILLBIT??SM??????????
             pstUserData ????????????
 ????????  : pucUserData TPDU??????????????
 ?? ?? ??  : ???????? MN_ERR_NO_ERROR????????
                      ????            ????????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2008??1??16??
    ??    ??   : ?????? 62575
    ????????   : ??????????
  2.??    ??   : 2010??10??16??
    ??    ??   : ??????/f62575
    ????????   : DTS2010092603490????????????????????UDH??????????????
  3.??    ??   : 2013??04??17??
    ??    ??   : ??????/f62575
    ????????   : DTS2013041704040, ????TP-UDHL????????????????????
*****************************************************************************/
LOCAL VOS_UINT32 MSG_DecodeUserData(
    VOS_BOOL                            bUserDataHeaderInd,
    const MN_MSG_DCS_CODE_STRU          *pstDcsInfo,
    VOS_UINT8                           *pucUserData,
    MN_MSG_USER_DATA_STRU               *pstUserData
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulPos               = 0;
    VOS_UINT8                           ucUdl;

    if ((VOS_NULL_PTR == pstDcsInfo)
     || (VOS_NULL_PTR == pucUserData)
     || (VOS_NULL_PTR == pstUserData))
    {
        MN_ERR_LOG("MSG_DecodeUserData: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    ucUdl  = pucUserData[ulPos];
    if (0 == ucUdl)
    {
        pstUserData->ulLen = 0;
        return MN_ERR_NO_ERROR;
    }

    /*UDL??????????????*/
    if ((MN_MSG_MSG_CODING_7_BIT == pstDcsInfo->enMsgCoding)
     && (VOS_TRUE != pstDcsInfo->bCompressed))
    {
        if (ucUdl > MN_MSG_MAX_7_BIT_LEN)
        {
            MN_WARN_LOG("MSG_DecodeUserData: udl is invalid.");
            return MN_ERR_CLASS_SMS_MSGLEN_OVERFLOW;
        }
    }
    else
    {
        if (ucUdl > MN_MSG_MAX_8_BIT_LEN)
        {
            MN_WARN_LOG("MSG_DecodeUserData: udl is invalid.");
            return MN_ERR_CLASS_SMS_MSGLEN_OVERFLOW;
        }
    }

    if (VOS_TRUE == bUserDataHeaderInd)
    {
        ulRet = MN_MSG_UpackSmWithUdh(pstDcsInfo,
                                      &(pucUserData[ulPos]),
                                      VOS_FALSE,
                                      (VOS_VOID *)pstUserData);
        if (MN_ERR_NO_ERROR == ulRet)
        {
            return ulRet;
        }
        else
        {
            PS_MEM_SET(pstUserData, 0, sizeof(MN_MSG_USER_DATA_STRU));
        }
    }

    /*decode SM, Refer to 23040 9.2.3.16*/
    pstUserData->ulLen = ucUdl;

    ulRet = MN_MSG_UnpackSmWithOutUdh(pstDcsInfo,
                                      &(pucUserData[ulPos]),
                                      pstUserData->aucOrgData);


    return ulRet;
}

/*****************************************************************************
 ?? ?? ??  : MSG_DecodeDeliver
 ????????  : ????????,??TPDU??????????????Deliver????????, Refer to 23040 9.2.2.1
 ????????  : pstSmsRawDataInfo  - ??????TPDU????
 ????????  : pstSmsDeliverInfo  - Deliver??????TEXT????
 ?? ?? ??  : VOS_UINT32:??????????????,????????????????????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2007??9??27??
    ??    ??   : z40661
    ????????   : ??????????
*****************************************************************************/
LOCAL VOS_UINT32   MSG_DecodeDeliver(
    const MN_MSG_RAW_TS_DATA_STRU       *pstSmsRawDataInfo,
    MN_MSG_DELIVER_STRU                 *pstSmsDeliverInfo
)
{
    VOS_UINT32                          ulPos               = 0;
    VOS_UINT32                          ulOaLen;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulSctsLen;

    if ((VOS_NULL_PTR == pstSmsRawDataInfo)
     || (VOS_NULL_PTR == pstSmsDeliverInfo))
    {
        MN_ERR_LOG("MSG_DecodeDeliver: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    PS_MEM_SET(pstSmsDeliverInfo, 0x00, sizeof(MN_MSG_DELIVER_STRU));

    /*lint -e961*/
    /*decode fo:TP MTI TP MMS TP RP TP UDHI TP SRI*/
    MSG_GET_TP_MMS(pstSmsDeliverInfo->bMoreMsg, pstSmsRawDataInfo->aucData[ulPos]);
    MSG_GET_TP_RP(pstSmsDeliverInfo->bReplayPath, pstSmsRawDataInfo->aucData[ulPos]);
    MSG_GET_TP_UDHI(pstSmsDeliverInfo->bUserDataHeaderInd, pstSmsRawDataInfo->aucData[ulPos]);
    MSG_GET_TP_SRI(pstSmsDeliverInfo->bStaRptInd, pstSmsRawDataInfo->aucData[ulPos]);
    /*lint +e961*/

    ulPos++;

    /*decode TP OA:*/
    ulRet = MN_MSG_DecodeAddress(&(pstSmsRawDataInfo->aucData[ulPos]),
                                 VOS_FALSE,
                                 &(pstSmsDeliverInfo->stOrigAddr),
                                 &ulOaLen);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return ulRet;
    }
    ulPos += ulOaLen;

    /*decode TP PID*/
    /*lint -e961*/
    pstSmsDeliverInfo->enPid = pstSmsRawDataInfo->aucData[ulPos++];
    /*lint +e961*/

    /*decode TP DCS*/
    ulRet = MN_MSG_DecodeDcs(pstSmsRawDataInfo->aucData[ulPos],
                             &pstSmsDeliverInfo->stDcs);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return ulRet;
    }
    ulPos++;

    /*decode TP SCTS*/
    ulRet = MSG_DecodeTimeStamp((VOS_UINT8 *)&(pstSmsRawDataInfo->aucData[ulPos]),
                                &(pstSmsDeliverInfo->stTimeStamp),
                                &ulSctsLen);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MSG_DecodeDeliver: Invalid SCTS.");
        return ulRet;
    }
    ulPos += ulSctsLen;/*TAF_SMS_SCTS_LEN 7*/

    /*decode TP UDL TP UD*/
    ulRet = MSG_DecodeUserData(pstSmsDeliverInfo->bUserDataHeaderInd,
                               &(pstSmsDeliverInfo->stDcs),
                               (VOS_UINT8 *)&(pstSmsRawDataInfo->aucData[ulPos]),
                               &(pstSmsDeliverInfo->stUserData));

    return ulRet;
}


/*****************************************************************************
 ?? ?? ??  : MSG_DecodeDeliverRptAck
 ????????  : ????????,??TPDU??????????????Deliver Report Ack????????, Refer to 23040 9.2.2.1a SMS DELIVER REPORT type
 ????????  : pstSmsRawDataInfo           - ??????TPDU????
 ????????  : pstSmsDeliverReportAckInfo  - Deliver Report Ack??????TEXT????
 ?? ?? ??  : VOS_UINT32:??????????????,????????????????????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2007??9??27??
    ??    ??   : z40661
    ????????   : ??????????
*****************************************************************************/
LOCAL VOS_UINT32   MSG_DecodeDeliverRptAck(
    const MN_MSG_RAW_TS_DATA_STRU       *pstSmsRawDataInfo,
    MN_MSG_DELIVER_RPT_ACK_STRU         *pstSmsDeliverRptAckInfo
)
{
    VOS_UINT32                          ulPos               = 0;
    VOS_UINT32                          ulRet               = MN_ERR_NO_ERROR;

    if ((VOS_NULL_PTR == pstSmsRawDataInfo)
     || (VOS_NULL_PTR == pstSmsDeliverRptAckInfo))
    {
        MN_ERR_LOG("MSG_DecodeDeliverRptAck: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    PS_MEM_SET(pstSmsDeliverRptAckInfo, 0x00, sizeof(MN_MSG_DELIVER_RPT_ACK_STRU));

    /*lint -e961*/

    /*TP MTI ignore  TP-UDHI  */
    MSG_GET_TP_UDHI(pstSmsDeliverRptAckInfo->bUserDataHeaderInd, pstSmsRawDataInfo->aucData[ulPos++]);

    /*    TP PI  9.2.3.27 BIT   2       1       0             */
    /*                          TP UDL  TP DCS  TP PID        */

    pstSmsDeliverRptAckInfo->ucParaInd  = pstSmsRawDataInfo->aucData[ulPos++];

    /*TP PID*/
    if (0 != (pstSmsDeliverRptAckInfo->ucParaInd & MN_MSG_TP_PID_MASK))
    {
        pstSmsDeliverRptAckInfo->enPid      = pstSmsRawDataInfo->aucData[ulPos++];
    }
    /*lint +e961*/
    /*  TP DCS*/
    if (0 != (pstSmsDeliverRptAckInfo->ucParaInd & MN_MSG_TP_DCS_MASK))
    {
        ulRet = MN_MSG_DecodeDcs(pstSmsRawDataInfo->aucData[ulPos],
                                 &(pstSmsDeliverRptAckInfo->stDcs));
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }
        ulPos++;
    }
    else
    {
        PS_MEM_SET(&(pstSmsDeliverRptAckInfo->stDcs), 0x00,
                    sizeof(pstSmsDeliverRptAckInfo->stDcs));
        pstSmsDeliverRptAckInfo->stDcs.enMsgCoding = MN_MSG_MSG_CODING_7_BIT;
    }

    /*TP UD TP UDL;*/
    if (0 != (pstSmsDeliverRptAckInfo->ucParaInd & MN_MSG_TP_UDL_MASK))
    {
        ulRet = MSG_DecodeUserData(pstSmsDeliverRptAckInfo->bUserDataHeaderInd,
                                   &(pstSmsDeliverRptAckInfo->stDcs),
                                   (VOS_UINT8 *)&(pstSmsRawDataInfo->aucData[ulPos]),
                                   &(pstSmsDeliverRptAckInfo->stUserData));
    }

    return ulRet;

}

/*****************************************************************************
 ?? ?? ??  : MSG_DecodeDeliverRptErr
 ????????  : ????????,??TPDU??????????????Deliver Report Error????????????, Refer to 23040 9.2.2.1a SMS DELIVER REPORT type
 ????????  : pstSmsRawDataInfo             - ??????TPDU????
 ????????  : pstSmsDeliverReportErrorInfo  - Deliver Report Error??????TEXT????
 ?? ?? ??  : VOS_UINT32:??????????????,????????????????????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2007??9??27??
    ??    ??   : z40661
    ????????   : ??????????
*****************************************************************************/
LOCAL VOS_UINT32   MSG_DecodeDeliverRptErr(
    const MN_MSG_RAW_TS_DATA_STRU       *pstSmsRawDataInfo ,
    MN_MSG_DELIVER_RPT_ERR_STRU         *pstSmsDeliverRptErrInfo
)
{
    VOS_UINT32                          ulPos               = 0;
    VOS_UINT32                          ulRet               = MN_ERR_NO_ERROR;

    if ((VOS_NULL_PTR == pstSmsRawDataInfo)
     || (VOS_NULL_PTR == pstSmsDeliverRptErrInfo))
    {
        MN_ERR_LOG("MSG_DecodeDeliverRptErr: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    PS_MEM_SET(pstSmsDeliverRptErrInfo, 0x00, sizeof(MN_MSG_DELIVER_RPT_ERR_STRU));

    /*lint -e961*/

    /*TP MTI ignore  TP-UDHI  */
    MSG_GET_TP_UDHI(pstSmsDeliverRptErrInfo->bUserDataHeaderInd, pstSmsRawDataInfo->aucData[ulPos++]);

    /*TP FCS*/
    pstSmsDeliverRptErrInfo->enFailCause = pstSmsRawDataInfo->aucData[ulPos++];

    /*    TP PI  9.2.3.27 BIT   2       1       0             */
    /*                          TP UDL  TP DCS  TP PID        */
    pstSmsDeliverRptErrInfo->ucParaInd = pstSmsRawDataInfo->aucData[ulPos++];

    /*TP PID*/
    if (0 != (pstSmsDeliverRptErrInfo->ucParaInd & MN_MSG_TP_PID_MASK))
    {
        pstSmsDeliverRptErrInfo->enPid = pstSmsRawDataInfo->aucData[ulPos++];
    }
    /*lint +e961*/
    /*  TP DCS*/
    if (0 != (pstSmsDeliverRptErrInfo->ucParaInd & MN_MSG_TP_DCS_MASK))
    {
        ulRet = MN_MSG_DecodeDcs(pstSmsRawDataInfo->aucData[ulPos],
                                 &pstSmsDeliverRptErrInfo->stDcs);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }
        ulPos++;
    }
    else
    {
        PS_MEM_SET(&(pstSmsDeliverRptErrInfo->stDcs),
                   0x00,
                   sizeof(pstSmsDeliverRptErrInfo->stDcs));
        pstSmsDeliverRptErrInfo->stDcs.enMsgCoding = MN_MSG_MSG_CODING_7_BIT;
    }

    /*TP UD TP UDL;*/
    if (0 != (pstSmsDeliverRptErrInfo->ucParaInd & MN_MSG_TP_UDL_MASK))
    {
        ulRet = MSG_DecodeUserData(pstSmsDeliverRptErrInfo->bUserDataHeaderInd,
                                   &(pstSmsDeliverRptErrInfo->stDcs),
                                   (VOS_UINT8 *)&(pstSmsRawDataInfo->aucData[ulPos]),
                                   &(pstSmsDeliverRptErrInfo->stUserData));
    }

    return ulRet;
}

/*****************************************************************************
 ?? ?? ??  : MSG_DecodeStaRpt
 ????????  : ????????,??TPDU??????????????Status Report????????, Refer to 23040 9.2.2.3 SMS STATUS REPORT type
 ????????  : pstSmsRawDataInfo       - ??????TPDU????
 ????????  : pstSmsStatusReportInfo  - Status Report??????TEXT????
 ?? ?? ??  : VOS_UINT32:??????????????,????????????????????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2007??9??27??
    ??    ??   : z40661
    ????????   : ??????????
*****************************************************************************/
LOCAL VOS_UINT32   MSG_DecodeStaRpt(
    const MN_MSG_RAW_TS_DATA_STRU       *pstSmsRawDataInfo ,
    MN_MSG_STA_RPT_STRU                 *pstSmsStatusRptInfo
)
{
    VOS_UINT32                          ulRet               = MN_ERR_NO_ERROR;
    VOS_UINT32                          ulPos               = 0;
    VOS_UINT32                          ulRaLen;
    VOS_UINT32                          ulSctsLen;
    VOS_UINT32                          ulDtLen;

    if ((VOS_NULL_PTR == pstSmsRawDataInfo)
     || (VOS_NULL_PTR == pstSmsStatusRptInfo))
    {
        MN_ERR_LOG("MSG_DecodeStaRpt: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    PS_MEM_SET(pstSmsStatusRptInfo, 0x00, sizeof(MN_MSG_STA_RPT_STRU));

    /*lint -e961*/
    /*TP MTI ignore TP UDHI TP MMS TP SRQ*/
    MSG_GET_TP_UDHI(pstSmsStatusRptInfo->bUserDataHeaderInd, pstSmsRawDataInfo->aucData[ulPos]);
    MSG_GET_TP_MMS(pstSmsStatusRptInfo->bMoreMsg, pstSmsRawDataInfo->aucData[ulPos]);
    MSG_GET_TP_SRQ(pstSmsStatusRptInfo->bStaRptQualCommand, pstSmsRawDataInfo->aucData[ulPos]);
    ulPos++;

    /*TP MR*/
    pstSmsStatusRptInfo->ucMr = pstSmsRawDataInfo->aucData[ulPos++];
    /*lint +e961*/

    /*TP RA 2 12o*/
    ulRet = MN_MSG_DecodeAddress(&(pstSmsRawDataInfo->aucData[ulPos]),
                                 VOS_FALSE,
                                 &(pstSmsStatusRptInfo->stRecipientAddr),
                                 &ulRaLen);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return ulRet;
    }
    ulPos += ulRaLen;

    /*TP SCTS 7o Parameter identifying time when the SC received the previously sent SMS SUBMIT*/
    ulRet = MSG_DecodeTimeStamp((VOS_UINT8 *)&(pstSmsRawDataInfo->aucData[ulPos]),
                                &(pstSmsStatusRptInfo->stTimeStamp),
                                &ulSctsLen);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return ulRet;
    }
    ulPos += ulSctsLen;

    /*TP DT Parameter identifying the time associated with a particular TP ST outcome*/
    ulRet = MSG_DecodeTimeStamp((VOS_UINT8 *)&(pstSmsRawDataInfo->aucData[ulPos]),
                                &(pstSmsStatusRptInfo->stDischargeTime),
                                &ulDtLen);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return ulRet;
    }
    ulPos += ulDtLen;

    /*TP ST*/
    /*lint -e961*/
    pstSmsStatusRptInfo->enStatus = pstSmsRawDataInfo->aucData[ulPos++];

    if (ulPos >= pstSmsRawDataInfo->ulLen)
    {
        return MN_ERR_NO_ERROR;
    }

    /*    TP PI  9.2.3.27 BIT   2       1       0             */
    /*                          TP UDL  TP DCS  TP PID        */
    pstSmsStatusRptInfo->ucParaInd = pstSmsRawDataInfo->aucData[ulPos++];

    /*TP PID*/
    if (0 != (pstSmsStatusRptInfo->ucParaInd & MN_MSG_TP_PID_MASK))
    {
        pstSmsStatusRptInfo->enPid = pstSmsRawDataInfo->aucData[ulPos++];
    }
    /*lint +e961*/
    /*  TP DCS*/
    if (0 != (pstSmsStatusRptInfo->ucParaInd & MN_MSG_TP_DCS_MASK))
    {
        ulRet = MN_MSG_DecodeDcs(pstSmsRawDataInfo->aucData[ulPos],
                                 &pstSmsStatusRptInfo->stDcs);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            MN_WARN_LOG("MSG_DecodeStaRpt: invalid DCS.");
            return MN_ERR_NO_ERROR;
        }
        ulPos++;
    }
    else
    {
        PS_MEM_SET(&(pstSmsStatusRptInfo->stDcs),
                   0x00,
                   sizeof(pstSmsStatusRptInfo->stDcs));
        pstSmsStatusRptInfo->stDcs.enMsgCoding = MN_MSG_MSG_CODING_7_BIT;
    }

    /*TP UD TP UDL;*/
    if (0 != (pstSmsStatusRptInfo->ucParaInd & MN_MSG_TP_UDL_MASK))
    {
        ulRet = MSG_DecodeUserData(pstSmsStatusRptInfo->bUserDataHeaderInd,
                                   &(pstSmsStatusRptInfo->stDcs),
                                   (VOS_UINT8 *)&(pstSmsRawDataInfo->aucData[ulPos]),
                                   &(pstSmsStatusRptInfo->stUserData));
        if (MN_ERR_NO_ERROR != ulRet)
        {
            MN_WARN_LOG("MSG_DecodeStaRpt: invalid UDL or UD.");
            return MN_ERR_NO_ERROR;
        }
    }

    return ulRet;
}


/*****************************************************************************
 ?? ?? ??  : MSG_DecodeCommand
 ????????  : ????????,??TPDU??????????????Command????????, 23040 9.2.2.4 SMS COMMAND type
 ????????  : pstSmsRawDataInfo  - ??????TPDU????
 ????????  : pstSmsCommandInfo  - Command??????TEXT????
 ?? ?? ??  : VOS_UINT32:??????????????,????????????????????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2007??9??27??
    ??    ??   : z40661
    ????????   : ??????????
*****************************************************************************/
LOCAL VOS_UINT32   MSG_DecodeCommand(
    const MN_MSG_RAW_TS_DATA_STRU       *pstSmsRawDataInfo,
    MN_MSG_COMMAND_STRU                 *pstSmsCommandInfo
)
{
    VOS_UINT32                          ulRet               = MN_ERR_NO_ERROR;
    VOS_UINT32                          ulPos               = 0;
    VOS_UINT32                          ulAddrLen;

    if ((VOS_NULL_PTR == pstSmsRawDataInfo)
     || (VOS_NULL_PTR == pstSmsCommandInfo))
    {
        MN_ERR_LOG("MSG_DecodeCommand: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    PS_MEM_SET(pstSmsCommandInfo, 0x00, sizeof(MN_MSG_COMMAND_STRU));

    /*lint -e961*/
    /*TP MTI TP UDHI TP SRR */
    MSG_GET_TP_UDHI(pstSmsCommandInfo->bUserDataHeaderInd, pstSmsRawDataInfo->aucData[ulPos]);
    MSG_GET_TP_SRR(pstSmsCommandInfo->bStaRptReq, pstSmsRawDataInfo->aucData[ulPos]);
    ulPos++;

    /*TP MR*/
    pstSmsCommandInfo->ucMr = pstSmsRawDataInfo->aucData[ulPos++];

    /*TP PID*/
    pstSmsCommandInfo->enPid = pstSmsRawDataInfo->aucData[ulPos++];

    /*TP CT*/
    pstSmsCommandInfo->enCmdType = pstSmsRawDataInfo->aucData[ulPos++];

    /*TP MN*/
    pstSmsCommandInfo->ucMsgNumber = pstSmsRawDataInfo->aucData[ulPos++];

    /*TP DA*/
    ulRet = MN_MSG_DecodeAddress(&(pstSmsRawDataInfo->aucData[ulPos]),
                                 VOS_FALSE,
                                 &(pstSmsCommandInfo->stDestAddr),
                                 &ulAddrLen);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return ulRet;
    }
    ulPos += ulAddrLen;

    /*TP CDL*/
    pstSmsCommandInfo->ucCommandDataLen = pstSmsRawDataInfo->aucData[ulPos++];
    /*lint +e961*/
    /*TP CD*/
    if (0 == pstSmsCommandInfo->ucCommandDataLen)
    {
        return MN_ERR_NO_ERROR;
    }

    if (pstSmsCommandInfo->ucCommandDataLen > MN_MSG_MAX_COMMAND_DATA_LEN)
    {
        return MN_ERR_CLASS_SMS_MSGLEN_OVERFLOW;
    }
    if (pstSmsCommandInfo->ucCommandDataLen > MN_MSG_MAX_COMMAND_DATA_LEN)
    {
        pstSmsCommandInfo->ucCommandDataLen = MN_MSG_MAX_COMMAND_DATA_LEN;
    }
    PS_MEM_CPY(pstSmsCommandInfo->aucCmdData,
               &pstSmsRawDataInfo->aucData[ulPos],
               pstSmsCommandInfo->ucCommandDataLen);

    return ulRet;
}

/*****************************************************************************
 ?? ?? ??  : MSG_DecodeSubmit
 ????????  : ????????,??TPDU??????????????Submit????????, Refer to 23040 9.2.2.2 SMS SUBMIT type
 ????????  : pstSmsRawDataInfo       - ??????TPDU????
 ????????  : pstSmsSubmitInfo        - Submit??????TEXT????
 ?? ?? ??  : VOS_UINT32:??????????????,????????????????????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2007??9??27??
    ??    ??   : z40661
    ????????   : ??????????
*****************************************************************************/
LOCAL VOS_UINT32   MSG_DecodeSubmit(
    const MN_MSG_RAW_TS_DATA_STRU       *pstSmsRawDataInfo,
    MN_MSG_SUBMIT_STRU                  *pstSmsSubmitInfo
)
{
    VOS_UINT32                          ulRet               = MN_ERR_NO_ERROR;
    VOS_UINT32                          ulPos               = 0;
    VOS_UINT32                          ulDaLen;
    VOS_UINT32                          ulVpLen;

    if ((VOS_NULL_PTR == pstSmsRawDataInfo)
     || (VOS_NULL_PTR == pstSmsSubmitInfo))
    {
        MN_ERR_LOG("MSG_DecodeSubmit: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    PS_MEM_SET(pstSmsSubmitInfo, 0x00, sizeof(MN_MSG_SUBMIT_STRU));
    /*b7  b6   b5   b4   b3  b2  b1  b0
      RP  UDHI SRR  VPF      RD  MTI
      0   0    0    2        1   2
      TP MTI TP RD TP VPF TP RP TP UDHI TP SRR*/
    /*TP MTI ignore 23040 9.2.3.1 ????bit0bit1:MIT     0011 0001 */

    /*lint -e961*/
    /*TP RD  23040 9.2.3.25*/
    MSG_GET_TP_RD(pstSmsSubmitInfo->bRejectDuplicates, pstSmsRawDataInfo->aucData[ulPos]);
    /*TP VPF 23040 9.2.3.3*/
    MSG_GET_TP_VPF(pstSmsSubmitInfo->stValidPeriod.enValidPeriod, pstSmsRawDataInfo->aucData[ulPos]);
    /*TP RP  23040 9.2.3.17*/
    MSG_GET_TP_RP(pstSmsSubmitInfo->bReplayPath, pstSmsRawDataInfo->aucData[ulPos]);
    /*TP UDHI23040 9.2.3.23*/
    MSG_GET_TP_UDHI(pstSmsSubmitInfo->bUserDataHeaderInd, pstSmsRawDataInfo->aucData[ulPos]);
    /*TP SRR 23040 9.2.3.5*/
    MSG_GET_TP_SRR(pstSmsSubmitInfo->bStaRptReq, pstSmsRawDataInfo->aucData[ulPos]);
    ulPos++;

    /*TP MR*/
    pstSmsSubmitInfo->ucMr = pstSmsRawDataInfo->aucData[ulPos++];

    /*TP DA* Refer to 9.1.2.5*/
    ulRet = MN_MSG_DecodeAddress(&(pstSmsRawDataInfo->aucData[ulPos]),
                                 VOS_FALSE,
                                 &(pstSmsSubmitInfo->stDestAddr),
                                 &ulDaLen);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return ulRet;
    }
    ulPos += ulDaLen;

    /*TP PID*/
    pstSmsSubmitInfo->enPid = pstSmsRawDataInfo->aucData[ulPos++];
    /*lint +e961*/

    /*TP DCS 23038 4 */
    ulRet = MN_MSG_DecodeDcs(pstSmsRawDataInfo->aucData[ulPos],
                             &(pstSmsSubmitInfo->stDcs));
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return ulRet;
    }
    ulPos ++;

    /*TP VP*/
    ulRet = MN_MSG_DecodeValidPeriod(pstSmsSubmitInfo->stValidPeriod.enValidPeriod,
                                  &(pstSmsRawDataInfo->aucData[ulPos]),
                                  &(pstSmsSubmitInfo->stValidPeriod),
                                  & ulVpLen);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return ulRet;
    }
    ulPos += ulVpLen;

    /*UDL UD*/
    ulRet = MSG_DecodeUserData(pstSmsSubmitInfo->bUserDataHeaderInd,
                               &(pstSmsSubmitInfo->stDcs),
                               (VOS_UINT8 *)&(pstSmsRawDataInfo->aucData[ulPos]),
                               &(pstSmsSubmitInfo->stUserData));

    return ulRet;
}

/*****************************************************************************
 ?? ?? ??  : MSG_DecodeSubmitRptAck
 ????????  : ????????,??TPDU??????????????Submit Report Ack????????, Refer to 23040 9.2.2.2a SMS SUBMIT REPORT type
 ????????  : pstSmsRawDataInfo           - ??????TPDU????
 ????????  : pstSmsSubmitReportAckInfo   - Submit Report Ack??????TEXT????
 ?? ?? ??  : VOS_UINT32:??????????????,????????????????????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2007??9??27??
    ??    ??   : z40661
    ????????   : ??????????
*****************************************************************************/
LOCAL VOS_UINT32   MSG_DecodeSubmitRptAck(
    const MN_MSG_RAW_TS_DATA_STRU       *pstSmsRawDataInfo ,
    MN_MSG_SUBMIT_RPT_ACK_STRU          *pstSmsSubmitRptAckInfo
)
{
    VOS_UINT32                          ulRet               = MN_ERR_NO_ERROR;
    VOS_UINT32                          ulPos               = 0;
    VOS_UINT32                          ulSctsLen;

    if ((VOS_NULL_PTR == pstSmsRawDataInfo)
     || (VOS_NULL_PTR == pstSmsSubmitRptAckInfo))
    {
        MN_ERR_LOG("MSG_DecodeSubmitRptAck: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    PS_MEM_SET(pstSmsSubmitRptAckInfo, 0x00, sizeof(MN_MSG_SUBMIT_RPT_ACK_STRU));

    /*lint -e961*/
    /*TP MTI ignore TP-UDHI  */
    MSG_GET_TP_UDHI(pstSmsSubmitRptAckInfo->bUserDataHeaderInd, pstSmsRawDataInfo->aucData[ulPos]);
    ulPos++;

    /*    TP PI  9.2.3.27 BIT   2       1       0             */
    /*                          TP UDL  TP DCS  TP PID        */
    pstSmsSubmitRptAckInfo->ucParaInd = pstSmsRawDataInfo->aucData[ulPos++];
    /*lint +e961*/

    /*TP SCTS*/
    ulRet = MSG_DecodeTimeStamp((VOS_UINT8 *)&(pstSmsRawDataInfo->aucData[ulPos]),
                                &(pstSmsSubmitRptAckInfo->stTimeStamp),
                                &ulSctsLen);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return ulRet;
    }
    ulPos += ulSctsLen;

    /*TP PID*/
    if (0 != (pstSmsSubmitRptAckInfo->ucParaInd & MN_MSG_TP_PID_MASK))
    {
        /*lint -e961*/
        pstSmsSubmitRptAckInfo->enPid = pstSmsRawDataInfo->aucData[ulPos++];
        /*lint +e961*/
    }

    /*  TP DCS*/
    if (0 != (pstSmsSubmitRptAckInfo->ucParaInd & MN_MSG_TP_DCS_MASK))
    {
        ulRet = MN_MSG_DecodeDcs(pstSmsRawDataInfo->aucData[ulPos],
                                 &(pstSmsSubmitRptAckInfo->stDcs));
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }
        ulPos ++;
    }
    else
    {
        PS_MEM_SET(&(pstSmsSubmitRptAckInfo->stDcs),
                   0x00,
                   sizeof(pstSmsSubmitRptAckInfo->stDcs));
        pstSmsSubmitRptAckInfo->stDcs.enMsgCoding = MN_MSG_MSG_CODING_7_BIT;
    }

    /*TP UD TP UDL;*/
    if (0 != (pstSmsSubmitRptAckInfo->ucParaInd & MN_MSG_TP_UDL_MASK))
    {
        ulRet = MSG_DecodeUserData(pstSmsSubmitRptAckInfo->bUserDataHeaderInd,
                                   &(pstSmsSubmitRptAckInfo->stDcs),
                                   (VOS_UINT8 *)&(pstSmsRawDataInfo->aucData[ulPos]),
                                   &(pstSmsSubmitRptAckInfo->stUserData));
    }

    return ulRet;
}

/*****************************************************************************
 ?? ?? ??  : MSG_DecodeSubmitRptErr
 ????????  : ????????,??TPDU??????????????Submit Report Error????????, Refer to 23040 9.2.2.2a SMS SUBMIT REPORT type
 ????????  : pstSmsRawDataInfo           - ??????TPDU????
 ????????  : pstSmsSubmitRptErrInfo      - Submit Report Error??????TEXT????
 ?? ?? ??  : VOS_UINT32:??????????????,????????????????????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2007??9??27??
    ??    ??   : z40661
    ????????   : ??????????
*****************************************************************************/
LOCAL VOS_UINT32   MSG_DecodeSubmitRptErr(
    const MN_MSG_RAW_TS_DATA_STRU       *pstSmsRawDataInfo ,
    MN_MSG_SUBMIT_RPT_ERR_STRU          *pstSmsSubmitRptErrInfo
)
{
    VOS_UINT32                          ulRet               = MN_ERR_NO_ERROR;
    VOS_UINT32                          ulPos               = 0;
    VOS_UINT32                          ulSctsLen;

    if ((VOS_NULL_PTR == pstSmsRawDataInfo)
     || (VOS_NULL_PTR == pstSmsSubmitRptErrInfo))
    {
        MN_ERR_LOG("MSG_DecodeSubmitRptErr: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    PS_MEM_SET(pstSmsSubmitRptErrInfo, 0x00, sizeof(MN_MSG_SUBMIT_RPT_ERR_STRU));

    /*lint -e961*/

    /*TP MTI ignore TP-UDHI  */
    MSG_GET_TP_UDHI(pstSmsSubmitRptErrInfo->bUserDataHeaderInd, pstSmsRawDataInfo->aucData[ulPos]);
    ulPos++;

    /*TP FCS*/
    pstSmsSubmitRptErrInfo->enFailCause = pstSmsRawDataInfo->aucData[ulPos++];

    /*    TP PI  9.2.3.27 BIT   2       1       0             */
    /*                          TP UDL  TP DCS  TP PID        */
    pstSmsSubmitRptErrInfo->ucParaInd = pstSmsRawDataInfo->aucData[ulPos++];
    /*lint +e961*/

    /*TP SCTS*/
    ulRet = MSG_DecodeTimeStamp((VOS_UINT8 *)&(pstSmsRawDataInfo->aucData[ulPos]),
                                &(pstSmsSubmitRptErrInfo->stTimeStamp),
                                &ulSctsLen);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return ulRet;
    }
    ulPos += ulSctsLen;

    /*TP PID*/
    if (0 != (pstSmsSubmitRptErrInfo->ucParaInd & MN_MSG_TP_PID_MASK))
    {
        /*lint -e961*/
        pstSmsSubmitRptErrInfo->enPid = pstSmsRawDataInfo->aucData[ulPos++];
        /*lint +e961*/
    }

    /*  TP DCS*/
    if (0 != (pstSmsSubmitRptErrInfo->ucParaInd & MN_MSG_TP_DCS_MASK))
    {
        ulRet = MN_MSG_DecodeDcs(pstSmsRawDataInfo->aucData[ulPos],
                                 &(pstSmsSubmitRptErrInfo->stDcs));
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }
        ulPos ++;
    }
    else
    {
        PS_MEM_SET(&(pstSmsSubmitRptErrInfo->stDcs), 0x00,
                   sizeof(pstSmsSubmitRptErrInfo->stDcs));
        pstSmsSubmitRptErrInfo->stDcs.enMsgCoding = MN_MSG_MSG_CODING_7_BIT;
    }

    /*TP UD TP UDL;*/
    if (0 != (pstSmsSubmitRptErrInfo->ucParaInd & MN_MSG_TP_UDL_MASK))
    {
        ulRet = MSG_DecodeUserData(pstSmsSubmitRptErrInfo->bUserDataHeaderInd,
                                   &(pstSmsSubmitRptErrInfo->stDcs),
                                   (VOS_UINT8 *)&(pstSmsRawDataInfo->aucData[ulPos]),
                                   &(pstSmsSubmitRptErrInfo->stUserData));
    }

    return ulRet;
}

/*****************************************************************************
 ?? ?? ??  : MN_MSG_DecodeDcs
 ????????  : ????????,??Dcs??????????????23038??????????????
 ????????  : ucDcsData             - DCS??????????
 ????????  : pstDcs                - ????23038??????????????
 ?? ?? ??  : VOS_UINT32:??????????????,????????????????????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2007??10??8??
    ??    ??   : z40661
    ????????   : ??????????
  2.??    ??   : 2009-10-28
    ??    ??   : F62575
    ????????   : ????????AT2D15641:DCS????????????????????????????
*****************************************************************************/
VOS_UINT32  MN_MSG_DecodeDcs(
    VOS_UINT8                           ucDcsData,
    MN_MSG_DCS_CODE_STRU                *pstDcs
)
{
    VOS_UINT8                           ucCodingGroup;

    /*????????????????????*/
    if (VOS_NULL_PTR == pstDcs)
    {
        MN_ERR_LOG("MN_MSG_DecodeDcs: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    /*??pstDcsCode??????????????????*/
    pstDcs->bCompressed         = VOS_FALSE;
    pstDcs->bWaitingIndiActive  = VOS_FALSE;
    pstDcs->enMsgClass          = MN_MSG_MSG_CLASS_NONE;
    pstDcs->enMsgCoding         = MN_MSG_MSG_CODING_7_BIT;
    pstDcs->enMsgWaiting        = MN_MSG_MSG_WAITING_NONE;
    pstDcs->enMsgWaitingKind    = MN_MSG_MSG_WAITING_OTHER;
    pstDcs->ucRawDcsData        = ucDcsData;
    pstDcs->bRawDcsValid        = VOS_TRUE;
    /*ucDcsData ??bit 6 bit 7????*/
    ucCodingGroup               = (ucDcsData >> 6) & 0x03;
    switch (ucCodingGroup)
    {
        /*(pattern 00xx xxxx)*/
        case 1:
            /*Message Marked for Automatic Deletion Group*/
            pstDcs->enMsgWaiting = MN_MSG_MSG_WAITING_AUTO_DELETE;
            /* fall through */
        case 0:

            /*lint -e961*/
            /* Bit 5  if set to 0, indicates the text is uncompressed */
            MSG_GET_COMPRESSED(pstDcs->bCompressed, ucDcsData);
            /*lint +e961*/

            /* Bit 3 Bit2 Character set:*/
            MSG_GET_CHARSET(pstDcs->enMsgCoding, ucDcsData);
            /* Bit 4, if set to 0, indicates that bits 1 to 0 are reserved and have no message class*/
            if (0 != (ucDcsData & 0x10)) /*(bit 4)*/
            {
                MSG_GET_MSGCLASS(pstDcs->enMsgClass, ucDcsData);
            }
            /*??????????????*/
            break;
        case 3:
            if ((ucDcsData & 0x30) == 0x30) /*(pattern 1111 xxxx)*/
            {
                pstDcs->enMsgWaiting = MN_MSG_MSG_WAITING_NONE_1111;
                MSG_GET_MSGCODING(pstDcs->enMsgCoding, ucDcsData);
                MSG_GET_MSGCLASS(pstDcs->enMsgClass, ucDcsData);
                /*bit3 ??????0????????????????*/
            }
            else
            {
                /*bit2 ??????0????????????????*/
                /*lint -e961*/
                MSG_GET_INDSENSE(pstDcs->bWaitingIndiActive, ucDcsData);
                MSG_GET_INDTYPE(pstDcs->enMsgWaitingKind, ucDcsData);
                /*lint +e961*/

                if ((ucDcsData & 0x30) == 0x00)/*(pattern 1100 xxxx)*/
                {
                    pstDcs->enMsgWaiting = MN_MSG_MSG_WAITING_DISCARD;
                }
                else
                {
                    pstDcs->enMsgWaiting = MN_MSG_MSG_WAITING_STORE;
                    if ((ucDcsData & 0x30) == 0x20)
                    {
                        pstDcs->enMsgCoding = MN_MSG_MSG_CODING_UCS2;
                    }
                }
            }
            break;
        default:
            MN_WARN_LOG("MN_MSG_DecodeDcs: invalid coding group.");
            return MN_ERR_CLASS_SMS_INVALID_CODING_GRP;
    }

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 ?? ?? ??  : MN_MSG_DecodeRelatTime
 ????????  : ????????,??23040????????????????????RelativeTime????????,????,??????
             ????TP-VPF??Relative Time ????????,??????????????????TP-VP??????????
             ??????
 ????????  : ucRelatTimeData  - ????23040??????????????
 ????????  : pstRelatTime     - RelativeTime??????????
 ?? ?? ??  : VOS_UINT32:??????????????,????????????????????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2007??10??8??
    ??    ??   : z40661
    ????????   : ??????????
*****************************************************************************/
VOS_UINT32  MN_MSG_DecodeRelatTime(
    VOS_UINT8                           ucRelatTimeData,
    MN_MSG_TIMESTAMP_STRU               *pstRelatTime
)
{
    VOS_UINT32                          ulMunite;
    VOS_UINT32                          ulDay;

    if (VOS_NULL_PTR == pstRelatTime)
    {
        MN_ERR_LOG("MN_MSG_DecodeRelatTime: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }
    else
    {
        PS_MEM_SET(pstRelatTime, 0x00, sizeof(MN_MSG_TIMESTAMP_STRU));
    }

    /*0??143????VP+1??* 5 ????????????5??????12????????????
      144??167??12 ????+????VP?C143??*30 ????????12 -> 23.5????
      168??196????VP?C166??*1 ????????????(196 - 166)== 30??
      197??255????VP?C192??*1 ??????????(255-192)*7 == 441??*/
    if (ucRelatTimeData < 144)
    {
        ulMunite                = (ucRelatTimeData + 1) * 5;
        pstRelatTime->ucHour    = (VOS_UINT8)(ulMunite / MN_MSG_MINUTES_IN_AN_HOUR);
        pstRelatTime->ucMinute  = ulMunite % MN_MSG_MINUTES_IN_AN_HOUR;
    }
    else if (ucRelatTimeData < 168)
    {
        ulMunite                = (12 * MN_MSG_MINUTES_IN_AN_HOUR) + ((ucRelatTimeData - 143) * 30);
        pstRelatTime->ucHour    = (VOS_UINT8 )(ulMunite / MN_MSG_MINUTES_IN_AN_HOUR);
        pstRelatTime->ucMinute  = ulMunite % MN_MSG_MINUTES_IN_AN_HOUR;
    }
    else if (ucRelatTimeData < 197)
    {
        pstRelatTime->ucDay = ucRelatTimeData - 166;
    }
    else
    {
        ulDay                   = (ucRelatTimeData - 192) * 7;
        pstRelatTime->ucYear    = (VOS_UINT8)(ulDay / MN_MSG_DAYS_IN_A_YEAR);
        pstRelatTime->ucDay     = (VOS_UINT8)(ulDay % MN_MSG_DAYS_IN_A_YEAR);
        pstRelatTime->ucMonth   = pstRelatTime->ucDay / 30;
        pstRelatTime->ucDay    %= 30;
    }

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 ?? ?? ??  : MN_MSG_Decode
 ????????  : ????????,??TPDU??????????????TEXT????
 ????????  : pstRawData      - ??????TPDU????????????????
 ????????  : pstTsDataInfo   - ??????TEXT????????????????
 ?? ?? ??  : VOS_UINT32:??????????????,????????????????????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2007??9??27??
    ??    ??   : z40661
    ????????   : ??????????
 2.??    ??   : 2009??10??28??
    ??    ??   : f62575
    ????????   : AT2D15641, STK????????????????????????????????????
*****************************************************************************/
VOS_UINT32  MN_MSG_Decode(
    const MN_MSG_RAW_TS_DATA_STRU       *pstRawData ,
    MN_MSG_TS_DATA_INFO_STRU            *pstTsDataInfo
)
{
    VOS_UINT32                          ulRet;

    if ((VOS_NULL_PTR == pstRawData)
     || (VOS_NULL_PTR == pstTsDataInfo))
    {
        MN_ERR_LOG("MN_MSG_Decode: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }
    else
    {
        PS_MEM_SET(pstTsDataInfo, 0x00, sizeof(MN_MSG_TS_DATA_INFO_STRU));
    }

    if (pstRawData->ulLen > MSG_MAX_TPDU_MSG_LEN)
    {
        MN_WARN_LOG("MN_MSG_Decode: Parameter of the function is null.");
        return MN_ERR_CLASS_SMS_MSGLEN_OVERFLOW;
    }

    pstTsDataInfo->enTpduType = pstRawData->enTpduType;

    MN_INFO_LOG1("MN_MSG_Decode: Tpdu type is ", (VOS_INT32)pstRawData->enTpduType);
    switch ( pstRawData->enTpduType )
    {
        case MN_MSG_TPDU_DELIVER:
            ulRet = MSG_DecodeDeliver(pstRawData, &(pstTsDataInfo->u.stDeliver));
            break;

        case MN_MSG_TPDU_DELIVER_RPT_ACK:
            ulRet = MSG_DecodeDeliverRptAck(pstRawData, &(pstTsDataInfo->u.stDeliverRptAck));
            break;

        case MN_MSG_TPDU_DELIVER_RPT_ERR:
            ulRet = MSG_DecodeDeliverRptErr(pstRawData, &(pstTsDataInfo->u.stDeliverRptErr));
            break;

        case MN_MSG_TPDU_STARPT:
            ulRet = MSG_DecodeStaRpt(pstRawData, &(pstTsDataInfo->u.stStaRpt));
            break;

        case MN_MSG_TPDU_COMMAND:
            ulRet = MSG_DecodeCommand(pstRawData, &(pstTsDataInfo->u.stCommand));
            break;

        case MN_MSG_TPDU_SUBMIT:
            ulRet = MSG_DecodeSubmit(pstRawData, &(pstTsDataInfo->u.stSubmit));
            break;

        case MN_MSG_TPDU_SUBMIT_RPT_ACK:
            ulRet = MSG_DecodeSubmitRptAck(pstRawData, &(pstTsDataInfo->u.stSubmitRptAck));
            break;

        case MN_MSG_TPDU_SUBMIT_RPT_ERR:
            ulRet = MSG_DecodeSubmitRptErr(pstRawData, &(pstTsDataInfo->u.stSubmitRptErr));
            break;

        default:
            MN_WARN_LOG("MN_MSG_Decode: invalid pdu type.");
            ulRet = MN_ERR_CLASS_SMS_INVALID_TPDUTYPE;
            break;
    }

    MN_INFO_LOG1("MN_MSG_Decode: result is ", (VOS_INT32)ulRet);
    return ulRet;
}

/*****************************************************************************
 ?? ?? ??  : MSG_GetSpecIdUdhIe
 ????????  : ????????ID????????????IE
 ????????  : enHeaderID - ??????????ID
             ucNumofHeaders - ????????????????????
             pstUserDataHeader - ??????????????????
 ????????  : ??
 ?? ?? ??  : ????????????ID????????????IE????????,
             ??????????????VOS_NULL_PTR
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2008??3??11??
    ??    ??   : fuyingjun
    ????????   : ??????????

*****************************************************************************/
MN_MSG_USER_HEADER_TYPE_STRU  *MSG_GetSpecIdUdhIe(
    VOS_UINT8                           ucNumofHeaders,                         /*number of user header*/
    MN_MSG_USER_HEADER_TYPE_STRU        *pstUserDataHeader,
    MN_MSG_UDH_TYPE_ENUM_U8             enHeaderID
)
{
    VOS_BOOL                            bIeExist            = VOS_FALSE;
    VOS_UINT32                          ulLoop;

    if (VOS_NULL_PTR == pstUserDataHeader)
    {
        MN_ERR_LOG("MSG_GetSpecIdUdhIe: Parameter of the function is null.");
        return VOS_NULL_PTR;
    }

    for (ulLoop = 0; ulLoop < ucNumofHeaders; ulLoop++)
    {
        if (pstUserDataHeader->enHeaderID == enHeaderID)
        {
            bIeExist = VOS_TRUE;
            break;
        }
        pstUserDataHeader++;
    }

    if (VOS_TRUE == bIeExist)
    {
        MN_INFO_LOG("MSG_ConcatenateUdh: ie is exist in long message struct.");
        return pstUserDataHeader;
    }
    else
    {
        return VOS_NULL_PTR;
    }

}

/*****************************************************************************
 ?? ?? ??  : MSG_FillMsgUdhEo
 ????????  : ????????????EO????????????????????????????
 ????????  : pstSmsDeliverInfo  - ????????????????
             pstUserDataHeader  - ??????????????????
 ????????  : pstLongDeliver     - ????????????????
 ?? ?? ??  : ??
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2008??3??6??
    ??    ??   : fuyingjun
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 MSG_FillMsgUdhEo(
    MN_MSG_DELIVER_STRU                 *pstSmsDeliverInfo,
    MN_MSG_USER_HEADER_TYPE_STRU        *pstUserDataHeader,
    MN_MSG_DELIVER_LONG_STRU            *pstLongDeliver
)
{
    MN_MSG_USER_HEADER_TYPE_STRU        *pstLongUserDataHeader;                 /*detail of user header*/
    VOS_UINT16                          usCurrentLen;

    if (VOS_FALSE == pstUserDataHeader->u.stEo.bFirstSegment)
    {
        pstLongUserDataHeader = MSG_GetSpecIdUdhIe(pstLongDeliver->stLongUserData.ucNumofHeaders,
                                                   pstLongDeliver->stLongUserData.astUserDataHeader,
                                                   MN_MSG_UDH_EO);
        if (VOS_NULL_PTR == pstLongUserDataHeader)
        {
            MN_ERR_LOG("MSG_FillMsgUdhEo: The subsequent Extended Object IEs without first Extended Object IE");
            return MN_ERR_INVALIDPARM;
        }

        usCurrentLen = pstLongUserDataHeader->u.stEo.usDataLen;
        if ((usCurrentLen + pstUserDataHeader->u.stEo.usDataLen) > MN_MSG_MAX_UDH_LONG_EO_DATA_LEN)
        {
            MN_WARN_LOG("MSG_FillMsgUdhEo: Extended Object IE length is overflow, Check to get a right length for EO.");
            return MN_ERR_INVALIDPARM;
        }
        PS_MEM_CPY(&pstLongUserDataHeader->u.stEo.aucData[usCurrentLen],
                   pstUserDataHeader->u.stEo.aucData,
                   pstUserDataHeader->u.stEo.usDataLen);
    }

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 ?? ?? ??  : MSG_FillMsgUdhCc
 ????????  : ????????????CC????????????????????????????
 ????????  : pstSmsDeliverInfo  - ????????????????
             pstUserDataHeader  - ??????????????????
 ????????  : pstLongDeliver     - ????????????????
 ?? ?? ??  : ??
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2008??3??6??
    ??    ??   : fuyingjun
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 MSG_FillMsgUdhCc(
    MN_MSG_DELIVER_STRU                 *pstSmsDeliverInfo,
    MN_MSG_USER_HEADER_TYPE_STRU        *pstUserDataHeader,
    MN_MSG_DELIVER_LONG_STRU            *pstLongDeliver
)
{
    MN_MSG_USER_HEADER_TYPE_STRU        *pstLongUserDataHeader;                 /*detail of user header*/
    VOS_UINT16                          usCurrentLen;

    pstLongUserDataHeader = MSG_GetSpecIdUdhIe(pstLongDeliver->stLongUserData.ucNumofHeaders,
                                               pstLongDeliver->stLongUserData.astUserDataHeader,
                                               MN_MSG_UDH_CC);
    if (VOS_NULL_PTR == pstLongUserDataHeader)
    {
        MN_ERR_LOG("MSG_FillMsgUdhCc: invalid Extended Object IE ");
        return MN_ERR_INVALIDPARM;
    }

    usCurrentLen = pstLongUserDataHeader->u.stEo.usDataLen;
    if ((usCurrentLen + pstUserDataHeader->u.stCc.usDataLen) > MN_MSG_UDH_MAX_COMPRESSION_DATA_LEN)
    {
        MN_WARN_LOG("MSG_FillMsgUdhCc: Extended Object IE length is overflow, Check to get a right length for CC.");
        return MN_ERR_INVALIDPARM;
    }

    PS_MEM_CPY(&pstLongUserDataHeader->u.stCc.aucData[usCurrentLen],
               pstUserDataHeader->u.stCc.aucData,
               pstUserDataHeader->u.stCc.usDataLen);

    return MN_ERR_NO_ERROR;
}


/*****************************************************************************
 ?? ?? ??  : MSG_ConcatenateUdh
 ????????  : ????????????????????????????????????????
 ????????  : pstSmsDeliverInfo  - ????????????????
 ????????  : pstLongDeliver     - ????????????????
 ?? ?? ??  : MN_ERR_NO_ERROR    - ????????????
             ????               - ????????????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2008??3??6??
    ??    ??   : fuyingjun
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 MSG_FillLongMsgUdh(
    MN_MSG_DELIVER_STRU                 *pstSmsDeliverInfo,
    MN_MSG_DELIVER_LONG_STRU            *pstLongDeliver
)
{
    MN_MSG_USER_HEADER_TYPE_STRU        *pstUserDataHeader;                     /*detail of user header*/
    MN_MSG_USER_HEADER_TYPE_STRU        *pstLongUserDataHeader;                 /*detail of user header*/
    VOS_UINT32                          ulCurrentIeNum;
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulRet;

    if ((VOS_NULL_PTR == pstSmsDeliverInfo)
     || (VOS_NULL_PTR == pstLongDeliver))
    {
        MN_ERR_LOG("MSG_FillLongMsgUdh: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    /*??????IE??????????????????????*/
    for (ulLoop = 0; ulLoop < pstSmsDeliverInfo->stUserData.ucNumofHeaders; ulLoop++)
    {
        pstUserDataHeader = &pstSmsDeliverInfo->stUserData.astUserDataHeader[ulLoop];
        if ((MN_MSG_UDH_CONCAT_8   == pstUserDataHeader->enHeaderID)
         || (MN_MSG_UDH_CONCAT_16   == pstUserDataHeader->enHeaderID))
        {
            continue;
        }

        if ((MN_MSG_UDH_PORT_8   == pstUserDataHeader->enHeaderID)
         || (MN_MSG_UDH_PORT_16   == pstUserDataHeader->enHeaderID)
         || (MN_MSG_UDH_SPECIAL_SM   == pstUserDataHeader->enHeaderID)
         || (MN_MSG_UDH_PORT_8   == pstUserDataHeader->enHeaderID)
         || (MN_MSG_UDH_PORT_16   == pstUserDataHeader->enHeaderID)
         || (MN_MSG_UDH_SMSC_CTRL   == pstUserDataHeader->enHeaderID)
         || (MN_MSG_UDH_SOURCE   == pstUserDataHeader->enHeaderID)
         || (MN_MSG_UDH_WCMP   == pstUserDataHeader->enHeaderID)
         || (MN_MSG_UDH_EXT_OBJECT_DATA_REQ_CMD   == pstUserDataHeader->enHeaderID)
         || (MN_MSG_UDH_RFC822   == pstUserDataHeader->enHeaderID)
         || (MN_MSG_UDH_HYPERLINK_FORMAT   == pstUserDataHeader->enHeaderID)
         || (MN_MSG_UDH_REPLY_ADDR   == pstUserDataHeader->enHeaderID)
         || (MN_MSG_UDH_ENHANCED_VOICE_MAIL_INF   == pstUserDataHeader->enHeaderID))
        {
            pstLongUserDataHeader = MSG_GetSpecIdUdhIe(pstLongDeliver->stLongUserData.ucNumofHeaders,
                                                       pstLongDeliver->stLongUserData.astUserDataHeader,
                                                       pstUserDataHeader->enHeaderID);
            if (VOS_NULL_PTR != pstLongUserDataHeader)
            {
                continue;
            }
        }

        if (MN_MSG_UDH_EO == pstUserDataHeader->enHeaderID)
        {
            ulRet = MSG_FillMsgUdhEo(pstSmsDeliverInfo,
                                     pstUserDataHeader,
                                     pstLongDeliver);
            if (MN_ERR_NO_ERROR != ulRet)
            {
                return ulRet;
            }

            continue;
        }
        else
        {
            if (MN_MSG_UDH_CC == pstUserDataHeader->enHeaderID)
            {
                ulRet = MSG_FillMsgUdhCc(pstSmsDeliverInfo,
                                         pstUserDataHeader,
                                         pstLongDeliver);
                if (MN_ERR_NO_ERROR != ulRet)
                {
                    return ulRet;
                }

                continue;
            }
        }

        pstLongDeliver->stLongUserData.ucNumofHeaders++;
        if (pstLongDeliver->stLongUserData.ucNumofHeaders > MN_MSG_MAX_UDH_NUM)
        {
            MN_WARN_LOG("MSG_ConcatenateUdh: the number of ie is overflow.");
            return MN_ERR_INVALIDPARM;
        }
        ulCurrentIeNum = pstLongDeliver->stLongUserData.ucNumofHeaders;
        PS_MEM_CPY(&pstLongDeliver->stLongUserData.astUserDataHeader[ulCurrentIeNum - 1],
                   pstUserDataHeader,
                   sizeof(MN_MSG_USER_HEADER_TYPE_STRU));
    }

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 ?? ?? ??  : MSG_FillLongMsg
 ????????  : ????????????????????????????????
 ????????  : ucNum               - ??????????????
             pucQueueMsg         - ??????????
                                   ???? ?????????????? 1
                                   ???? ??????????????????????????
             pstRawData          - ??????????????????
             pstSmsDeliverInfo   - ????????????????
 ????????  : pstDeliver          - ????????????????
 ?? ?? ??  :
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2008??3??11??
    ??    ??   : fuyingjun
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 MSG_FillLongMsg(
    VOS_UINT8                           ucNum,
    const VOS_UINT8                     *pucQueueMsg,
    const MN_MSG_RAW_TS_DATA_STRU       *pstRawData,
    MN_MSG_DELIVER_STRU                 *pstSmsDeliverInfo,
    MN_MSG_DELIVER_LONG_STRU            *pstLongDeliver
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulRet;
    VOS_INT32                           lOffSet;

    if ((VOS_NULL_PTR == pucQueueMsg)
     || (VOS_NULL_PTR == pstRawData)
     || (VOS_NULL_PTR == pstSmsDeliverInfo)
     || (VOS_NULL_PTR == pstLongDeliver))
    {
        MN_ERR_LOG("MSG_FillLongMsg: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    for (ulLoop = 0; ulLoop < ucNum; ulLoop++)
    {
        lOffSet = (pucQueueMsg[ulLoop] - 1);
        MN_INFO_LOG2("MSG_FillLongMsg: ulLoop, lOffSet", (VOS_INT32)ulLoop, lOffSet);
        ulRet = MSG_DecodeDeliver((pstRawData + lOffSet), pstSmsDeliverInfo);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }

        ulRet = MSG_FillLongMsgUdh(pstSmsDeliverInfo, pstLongDeliver);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }
        if (pstSmsDeliverInfo->stUserData.ulLen > MN_MSG_MAX_LEN)
        {
            pstSmsDeliverInfo->stUserData.ulLen = MN_MSG_MAX_LEN;
        }
        PS_MEM_CPY(&pstLongDeliver->stLongUserData.pucOrgData[pstLongDeliver->stLongUserData.ulLen],
                   pstSmsDeliverInfo->stUserData.aucOrgData,
                   pstSmsDeliverInfo->stUserData.ulLen);
        pstLongDeliver->stLongUserData.ulLen += pstSmsDeliverInfo->stUserData.ulLen;

    }

    /*??????????????????????????????????????*/
    pstLongDeliver->bReplayPath          = pstSmsDeliverInfo->bReplayPath;
    if (0 != pstLongDeliver->stLongUserData.ucNumofHeaders)
    {
        pstLongDeliver->bUserDataHeaderInd   = VOS_TRUE;
    }
    pstLongDeliver->bStaRptInd           = pstSmsDeliverInfo->bStaRptInd;
    pstLongDeliver->enPid                = pstSmsDeliverInfo->enPid;
    PS_MEM_CPY(&(pstLongDeliver->stOrigAddr),
               &(pstSmsDeliverInfo->stOrigAddr),
               sizeof(pstLongDeliver->stOrigAddr));
    PS_MEM_CPY(&(pstLongDeliver->stDcs),
               &(pstSmsDeliverInfo->stDcs),
               sizeof(pstLongDeliver->stDcs));/*??*/
    PS_MEM_CPY(&(pstLongDeliver->stTimeStamp),
               &(pstSmsDeliverInfo->stTimeStamp),
               sizeof(pstLongDeliver->stTimeStamp));

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 ?? ?? ??  : MN_MSG_ParseConcatenateMsg
 ????????  : ????
 ????????  : ucNum                  - ??????????????
             pstRawData             - ??????????????????
             pstConcentrateMsgAttr  - ????????????
             pstSmsDeliverInfo      - ????????????????
 ????????  : pucQueueMsg            - ??????????
                                   ???? ?????????????? 1
                                   ???? ??????????????????????????
 ?? ?? ??  : VOS_UINT32:??????????????,????????????????????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2008??7??19??
    ??    ??   : f62575
    ????????   : ??????????
*****************************************************************************/
VOS_UINT32   MN_MSG_ParseConcatenateMsg(
    VOS_UINT8                           ucNum,
    const MN_MSG_RAW_TS_DATA_STRU       *pstRawData,
    MN_MSG_CONCENTRATE_MSG_ATTR         *pstConcentrateMsgAttr,
    MN_MSG_DELIVER_STRU                 *pstSmsDeliverInfo,
    VOS_UINT8                           *pucQueueMsg
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulRet;
    MN_MSG_USER_HEADER_TYPE_STRU        *pstUserHeader;
    VOS_UINT8                           ucTotalNum          = 0;
    VOS_UINT8                           ucSeqNum;

    if (pstConcentrateMsgAttr->ucFirstMsgSeqNum < 1)
    {
        MN_WARN_LOG("MN_MSG_ParseConcatenateMsg: invalid SeqNum. ");
        return MN_ERR_INVALIDPARM;
    }

    pucQueueMsg[pstConcentrateMsgAttr->ucFirstMsgSeqNum - 1] = 1;
    /*????????????????*/
    for (ulLoop = 1; ulLoop < ucNum; ulLoop++)
    {
        ulRet = MSG_DecodeDeliver(pstRawData, pstSmsDeliverInfo);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }

        if (VOS_TRUE == pstConcentrateMsgAttr->b8bitConcatMsg)
        {
            pstUserHeader = MSG_GetSpecIdUdhIe(pstSmsDeliverInfo->stUserData.ucNumofHeaders,
                                               pstSmsDeliverInfo->stUserData.astUserDataHeader,
                                               MN_MSG_UDH_CONCAT_8);
            if (VOS_NULL_PTR == pstUserHeader)
            {
                MN_ERR_LOG("MN_MSG_ParseConcatenateMsg: concatenate message without right concatenate IE. ");
                return MN_ERR_INVALIDPARM;
            }

            if (pstConcentrateMsgAttr->ucMr != pstUserHeader->u.stConcat_8.ucMr)
            {
                MN_WARN_LOG("MN_MSG_ParseConcatenateMsg: the reference number is not constant. ");
                return MN_ERR_INVALIDPARM;
            }
            ucSeqNum = pstUserHeader->u.stConcat_8.ucSeqNum;
            ucTotalNum = pstUserHeader->u.stConcat_8.ucTotalNum;
        }
        else
        {
            pstUserHeader = MSG_GetSpecIdUdhIe(pstSmsDeliverInfo->stUserData.ucNumofHeaders,
                                               pstSmsDeliverInfo->stUserData.astUserDataHeader,
                                               MN_MSG_UDH_CONCAT_16);
            if (VOS_NULL_PTR == pstUserHeader)
            {
                MN_ERR_LOG("MN_MSG_ParseConcatenateMsg: concatenate message without right concatenate IE. ");
                return MN_ERR_INVALIDPARM;
            }

            if (pstConcentrateMsgAttr->usMr != pstUserHeader->u.stConcat_16.usMr)
            {
                MN_WARN_LOG("MN_MSG_ParseConcatenateMsg: the reference number is not constant. ");
                return MN_ERR_INVALIDPARM;
            }
            ucSeqNum = pstUserHeader->u.stConcat_16.ucSeqNum;
            ucTotalNum = pstUserHeader->u.stConcat_16.ucTotalNum;
        }

        if (ucSeqNum > ucTotalNum)
        {
            MN_WARN_LOG("MN_MSG_ParseConcatenateMsg: Sequence number is bigger than Maximum number.");
            return MN_ERR_INVALIDPARM;
        }

        if (0 == ucSeqNum)
        {
            MN_WARN_LOG("MN_MSG_ParseConcatenateMsg: Sequence number is zero.");
            return MN_ERR_INVALIDPARM;
        }

        /*????????????*/
        if (0 != pucQueueMsg[ucSeqNum - 1])
        {
            MN_WARN_LOG("MN_MSG_ParseConcatenateMsg: Repeated message.");
            return MN_ERR_INVALIDPARM;
        }
        pucQueueMsg[ucSeqNum - 1] = (VOS_UINT8)(ulLoop + 1);
        pstRawData++;
    }

    /*????????????*/
    for (ulLoop = 0; ulLoop < ucNum; ulLoop++)
    {
        if (0 == pucQueueMsg[ulLoop])
        {
            MN_WARN_LOG("MN_MSG_ParseConcatenateMsg: incontinuous message.");
            return MN_ERR_INVALIDPARM;
        }
    }

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 ?? ?? ??  : MN_MSG_Concatenate
 ????????  : ????????,????????????????????????????
 ????????  : ucNum               - ??????????????
             pstRawData          - ??????????????????
 ????????  : pstDeliver          - ??????????????
 ?? ?? ??  : VOS_UINT32:??????????????,????????????????????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2007??9??27??
    ??    ??   : f62575
    ????????   : ??????????
????:
    ??????????????????????????????MN_MSG_DELIVER_LONG_STRU????????????
    ??????MN_MSG_DELIVER_LONG_STRU????????????????????????????
*****************************************************************************/
VOS_UINT32   MN_MSG_Concatenate(
    VOS_UINT8                           ucNum,
    const MN_MSG_RAW_TS_DATA_STRU       *pstRawData,
    MN_MSG_DELIVER_LONG_STRU            *pstDeliver
)
{
    VOS_UINT32                          ulRet;
    MN_MSG_DELIVER_STRU                 *pstSmsDeliverInfo = VOS_NULL_PTR;
    MN_MSG_USER_HEADER_TYPE_STRU        *pstUserHeader;
    VOS_BOOL                            b8bitConcatMsg      = VOS_FALSE;
    VOS_BOOL                            b16bitConcatMsg     = VOS_FALSE;
    VOS_UINT8                           ucMr                = 0;
    VOS_UINT16                          usMr                = 0;
    /*Maximum number of short messages in the enhanced concatenated short message*/
    VOS_UINT8                           ucTotalNum          = 0;
    /*Sequence number of the current short message.*/
    VOS_UINT8                           ucSeqNum            = 0;
    /*??????????????????????????????????????????*/
    VOS_UINT8                           aucQueueMsg[MSG_LONG_MSG_VOLUME];
    /*????????????????????????????????????????????*/
    const MN_MSG_RAW_TS_DATA_STRU       *pstTmpMsg;
    MN_MSG_CONCENTRATE_MSG_ATTR         stConcentrateMsgAttr;

    /*????????????????????*/
    if ((VOS_NULL_PTR == pstRawData)
     || (VOS_NULL_PTR == pstDeliver))
    {
        MN_ERR_LOG("MN_MSG_Concatenate: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    if (0 == ucNum)
    {
        MN_WARN_LOG("MN_MSG_Concatenate: Invalid message number. ");
        return MN_ERR_INVALIDPARM;
    }

    pstSmsDeliverInfo = (MN_MSG_DELIVER_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(MN_MSG_DELIVER_STRU));
    if (VOS_NULL_PTR == pstSmsDeliverInfo)
    {
        MN_ERR_LOG("MN_MSG_Concatenate: Fail to Alloc memory.");
        return MN_ERR_NOMEM;
    }

    pstTmpMsg = pstRawData;
    ulRet = MSG_DecodeDeliver(pstTmpMsg, pstSmsDeliverInfo);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pstSmsDeliverInfo);
        return ulRet;
    }

    PS_MEM_SET(aucQueueMsg, 0x00, MSG_LONG_MSG_VOLUME);

    if (VOS_TRUE != pstSmsDeliverInfo->bUserDataHeaderInd)
    {
        MN_NORM_LOG("MN_MSG_Concatenate: No message to Concatenate because of none UDH.");
    }
    else
    {
        pstUserHeader = MSG_GetSpecIdUdhIe(pstSmsDeliverInfo->stUserData.ucNumofHeaders,
                                           pstSmsDeliverInfo->stUserData.astUserDataHeader,
                                           MN_MSG_UDH_CONCAT_8);
        if (VOS_NULL_PTR != pstUserHeader)
        {
            b8bitConcatMsg = VOS_TRUE;
            ucMr = pstUserHeader->u.stConcat_8.ucMr;
            ucSeqNum = pstUserHeader->u.stConcat_8.ucSeqNum;
            ucTotalNum = pstUserHeader->u.stConcat_8.ucTotalNum;
        }
        pstUserHeader = MSG_GetSpecIdUdhIe(pstSmsDeliverInfo->stUserData.ucNumofHeaders,
                                           pstSmsDeliverInfo->stUserData.astUserDataHeader,
                                           MN_MSG_UDH_CONCAT_16);
        if (VOS_NULL_PTR != pstUserHeader)
        {
            b16bitConcatMsg = VOS_TRUE;
            usMr = pstUserHeader->u.stConcat_16.usMr;
            ucSeqNum = pstUserHeader->u.stConcat_16.ucSeqNum;
            ucTotalNum = pstUserHeader->u.stConcat_16.ucTotalNum;
        }

        if (ucTotalNum != ucNum)
        {
            PS_MEM_FREE(WUEPS_PID_TAF, pstSmsDeliverInfo);
            MN_WARN_LOG("MN_MSG_Concatenate: ucTotalNum is not equal to ucNum.");
            return MN_ERR_INVALIDPARM;
        }

    }

    PS_MEM_SET(pstDeliver, 0x00, sizeof(MN_MSG_DELIVER_LONG_STRU));

    if ((VOS_TRUE != b8bitConcatMsg)
     && (VOS_TRUE != b16bitConcatMsg))
    {
        /*????????????????????????IE,????????*/
        if (1 != ucNum)
        {
            MN_WARN_LOG("MN_MSG_Concatenate: concatenate message without concatenate IE. ");
            PS_MEM_FREE(WUEPS_PID_TAF, pstSmsDeliverInfo);
            return MN_ERR_INVALIDPARM;
        }
        else
        {
            PS_MEM_SET(aucQueueMsg, 0x00, MSG_LONG_MSG_VOLUME);
            /*????????????????????????;*/
            aucQueueMsg[0] = 1;
            ulRet = MSG_FillLongMsg(ucNum, aucQueueMsg, pstRawData, pstSmsDeliverInfo, pstDeliver);

            PS_MEM_FREE(WUEPS_PID_TAF, pstSmsDeliverInfo);
            return ulRet;
        }
    }

    /*??????????????????????????????IE,????????*/
    if ((VOS_TRUE == b8bitConcatMsg)
     && (VOS_TRUE == b16bitConcatMsg))
    {
        MN_WARN_LOG("MN_MSG_Concatenate: concatenate IE conflict. ");
        PS_MEM_FREE(WUEPS_PID_TAF, pstSmsDeliverInfo);
        return MN_ERR_INVALIDPARM;
    }

    if ((0 == ucSeqNum)
     || (ucTotalNum != ucNum))
    {
        MN_WARN_LOG("MN_MSG_Concatenate: invalid Sequence number or total number.");
        PS_MEM_FREE(WUEPS_PID_TAF, pstSmsDeliverInfo);
        return MN_ERR_INVALIDPARM;
    }

    pstTmpMsg++;

    stConcentrateMsgAttr.ucMr = ucMr;
    stConcentrateMsgAttr.usMr = usMr;
    stConcentrateMsgAttr.ucFirstMsgSeqNum = ucSeqNum;
    stConcentrateMsgAttr.b8bitConcatMsg = b8bitConcatMsg;
    ulRet = MN_MSG_ParseConcatenateMsg(ucNum,
                                       pstTmpMsg,
                                       &stConcentrateMsgAttr,
                                       pstSmsDeliverInfo,
                                       aucQueueMsg);
    if (MN_ERR_NO_ERROR == ulRet)
    {
        ulRet = MSG_FillLongMsg(ucNum, aucQueueMsg, pstRawData, pstSmsDeliverInfo, pstDeliver);
    }

    PS_MEM_FREE(WUEPS_PID_TAF, pstSmsDeliverInfo);
    return ulRet;


}

/*****************************************************************************
 ?? ?? ??  : MN_MSG_GetAddressFromSubmit
 ????????  : ????????????????????????????????????????
 ????????  : VOS_UINT8                          *pucRpduContent RP-DATA??????????
             VOS_UINT32                          ulRpDataLen    RP-DATA??????
 ????????  : NAS_MNTN_BCD_ADDR_STRU             *pstScAddr,     ??????????????
             NAS_MNTN_BCD_ADDR_STRU             *pstDestAddr    ??????????????
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2010??9??19??
    ??    ??   : ??????/f62575
    ????????   : ??????????

*****************************************************************************/
VOS_VOID MN_MSG_GetAddressFromSubmit(
    VOS_UINT8                          *pucRpduContent,
    VOS_UINT32                          ulRpDataLen,
    NAS_MNTN_ASCII_ADDR_STRU           *pstScAddr,
    NAS_MNTN_ASCII_ADDR_STRU           *pstDestAddr
)
{
    VOS_UINT8                           ucScLen;
    VOS_UINT8                           ucPos;
    VOS_UINT8                           ucMti;
    VOS_UINT32                          ulLen;
    VOS_UINT32                          ulRet;

    ucPos = 0;
    /* ????????????RP???????????? */
    ucPos++;

    /* ????????????RP-MR */
    ucPos++;

    /* ??????????????????RP-OA */
    ucPos++;

    /* ????????????????????RP-DA???????????? */
    ucScLen = pucRpduContent[ucPos];

    ulRet = MN_MSG_DecodeAddress(&pucRpduContent[ucPos],
                                 VOS_TRUE,
                                 (MN_MSG_ASCII_ADDR_STRU *)pstScAddr,
                                 &ulLen);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("NAS_MNTN_GetAddressFromSubmit:Error SC.");
        return;
    }
    /*????????????????????????: BCD?????????????????? */
    ucPos += (ucScLen + 1);

    /* RP-DA??????????RP-DATA???? */
    ucPos++;

    /* ??????????????????????SUBMIT???????????? */
    MSG_GET_TP_MTI(ucMti, pucRpduContent[ucPos]);
    if (MN_MSG_TP_MTI_SUBMIT != ucMti)
    {
        MN_WARN_LOG("NAS_MNTN_GetAddressFromSubmit:Error MsgName");
        return;
    }
    ucPos++;

    /* ??????TP-MR?? */
    ucPos++;

    /* ???????????????????????????????????????? */
    ulRet = MN_MSG_DecodeAddress(&pucRpduContent[ucPos],
                                 VOS_FALSE,
                                 (MN_MSG_ASCII_ADDR_STRU *)pstDestAddr,
                                 &ulLen);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("NAS_MNTN_GetAddressFromSubmit:Error DA.");
        return;
    }

    return;
}

/*****************************************************************************
 ?? ?? ??  : MN_MSG_GetMsgMti
 ????????  : ????????TPDU??MTI
 ????????  : VOS_UINT8 ucFo         ????TPDU????????????????
 ????????  : VOS_UINT8 *pucMti      ????????
 ?? ?? ??  : ??
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??2??26??
    ??    ??   : ??????/f62575
    ????????   : ?????????? DTS2011032106103

*****************************************************************************/
VOS_VOID MN_MSG_GetMsgMti(
    VOS_UINT8                           ucFo,
    VOS_UINT8                          *pucMti
)
{
    MSG_GET_TP_MTI(*pucMti, ucFo);

    return;
}

/*****************************************************************************
 ?? ?? ??  : MN_MSG_GetSubmitInfoForStk
 ????????  : ????STK??????SUBMIT????
 ????????  : VOS_UINT8                           aucTpdu[] SUBMIT??????TPDU

 ????????  : VOS_UINT8                           *pucUserDataLen   SUBMIT??????????????????(7bit??????7??????????????????BYTE??)
             VOS_UINT8                           *pucUdhl  SUBMIT??????????????????????(????????????????1??????)
             MN_MSG_MSG_CODING_ENUM_U8           *penMsgCoding SUBMIT????????????
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??2??26??
    ??    ??   : ??????/f62575
    ????????   : ?????????? DTS2011032106103
  2.??    ??  : 2011??6??1??
    ??    ??  : f62575
    ????????  : DTS2011052703494,STK????????????
*****************************************************************************/
VOS_UINT32 MN_MSG_GetSubmitInfoForStk(
    MN_MSG_TPDU_STRU                   *pstTpdu,
    VOS_UINT8                          *pucUserDataLen,
    VOS_UINT8                          *pucUdhl,
    MN_MSG_MSG_CODING_ENUM_U8          *penMsgCoding,
    VOS_UINT32                         *pulDcsOffset
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulPos;
    VOS_UINT32                          ulDaLen;
    VOS_UINT32                          ulVpLen;
    MN_MSG_SUBMIT_STRU                 *pstSmsSubmitInfo;
    VOS_UINT8                           ucUdl;
    VOS_UINT8                           ucUdhl;

    if ((VOS_NULL_PTR == pstTpdu)
     || (VOS_NULL_PTR == pstTpdu->pucTpdu)
     || (VOS_NULL_PTR == pucUserDataLen)
     || (VOS_NULL_PTR == pucUdhl)
     || (VOS_NULL_PTR == penMsgCoding))
    {
        MN_WARN_LOG("MN_MSG_GetSubmitInfoForStk: NULL PTR. ");
        return MN_ERR_NULLPTR;
    }

    MN_NORM_LOG1("MN_MSG_GetSubmitInfoForStk: pstTpdu->ulLen is ", (VOS_INT32)pstTpdu->ulLen);

    pstSmsSubmitInfo = (MN_MSG_SUBMIT_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF,
                                                sizeof(MN_MSG_SUBMIT_STRU));
    if (VOS_NULL_PTR == pstSmsSubmitInfo)
    {
        MN_WARN_LOG("MN_MSG_GetSubmitInfoForStk: fail to alloc memory. ");
        return MN_ERR_NOMEM;
    }

    PS_MEM_SET(pstSmsSubmitInfo, 0x00, sizeof(MN_MSG_SUBMIT_STRU));

    /*lint -e961*/
    /* FO */
    ulPos = 0;
    MSG_GET_TP_UDHI(pstSmsSubmitInfo->bUserDataHeaderInd, pstTpdu->pucTpdu[ulPos]);
    /*TP VPF 23040 9.2.3.3*/
    MSG_GET_TP_VPF(pstSmsSubmitInfo->stValidPeriod.enValidPeriod, pstTpdu->pucTpdu[ulPos]);
    ulPos++;
    /*lint +e961*/

    /* TP MR */
    ulPos++;

    /* TP DA Refer to 9.1.2.5 */
    ulRet = MN_MSG_DecodeAddress(&(pstTpdu->pucTpdu[ulPos]),
                                 VOS_FALSE,
                                 &(pstSmsSubmitInfo->stDestAddr),
                                 &ulDaLen);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pstSmsSubmitInfo);
        return ulRet;
    }
    ulPos += ulDaLen;

    /*lint -e961*/
    /* TP PID */
    pstSmsSubmitInfo->enPid = pstTpdu->pucTpdu[ulPos++];
    /*lint +e961*/

    *pulDcsOffset = ulPos;

    /* TP DCS 23038 4 */
    ulRet = MN_MSG_DecodeDcs(pstTpdu->pucTpdu[ulPos],
                             &(pstSmsSubmitInfo->stDcs));
    if (MN_ERR_NO_ERROR != ulRet)
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pstSmsSubmitInfo);
        return ulRet;
    }
    ulPos ++;

    /*TP VP*/
    ulRet = MN_MSG_DecodeValidPeriod(pstSmsSubmitInfo->stValidPeriod.enValidPeriod,
                                     &(pstTpdu->pucTpdu[ulPos]),
                                     &(pstSmsSubmitInfo->stValidPeriod),
                                     & ulVpLen);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pstSmsSubmitInfo);
        return ulRet;
    }
    ulPos += ulVpLen;

    ucUdl = pstTpdu->pucTpdu[ulPos];
    ulPos ++;

    if (VOS_TRUE == pstSmsSubmitInfo->bUserDataHeaderInd)
    {
        ucUdhl          = pstTpdu->pucTpdu[ulPos];
        if (MN_MSG_MSG_CODING_7_BIT == pstSmsSubmitInfo->stDcs.enMsgCoding)
        {
            *pucUserDataLen = (VOS_UINT8)(ucUdl - ((((ucUdhl + 1) * 8) + 6)/7));
        }
        else
        {
            *pucUserDataLen = (VOS_UINT8)(ucUdl - (ucUdhl + 1));
        }

        *pucUdhl        = ucUdhl;
    }
    else
    {
        *pucUserDataLen = ucUdl;
        *pucUdhl        = 0;
    }

    *penMsgCoding = pstSmsSubmitInfo->stDcs.enMsgCoding;

    PS_MEM_FREE(WUEPS_PID_TAF, pstSmsSubmitInfo);
    return MN_ERR_NO_ERROR;
}
/*lint +e958*/


