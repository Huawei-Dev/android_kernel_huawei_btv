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

/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : UsimmApi.c
  Author       : zhuli
  Version      : V100R002
  Date         : 2008-5-15
  Description  : ??C??????????---????????????????????
  Function List:
  History      :
 ************************************************************************/


#include "si_pb.h"


#include "AtOamInterface.h"
#include "TafOamInterface.h"


/*****************************************************************************
    ??????????????????????.C??????????
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID PS_FILE_ID_PB_MSG_C
/*lint +e767*/


/*****************************************************************************
    ????????????
*****************************************************************************/

SI_PB_REQ_UINT_STRU             gstPBReqUnit;

/*??????????????????????A ???????????????? C ??????*/
SI_PB_CONTROL_STRU              gstPBCtrlInfo;
SI_PB_CTRL_INFO_ST              gstPBConfigInfo;

SI_PB_CONTENT_STRU              gastPBContent[SI_PB_MAX_NUMBER];
SI_EXT_CONTENT_STRU             gastEXTContent[SI_PB_MAX_NUMBER];
SI_ANR_CONTENT_STRU             gastANRContent[SI_PB_ANRMAX];
SI_EML_CONTENT_STRU             gstEMLContent;
SI_IAP_CONTENT_STRU             gstIAPContent;
SI_PB_INIT_STATE_STRU           gstPBInitState;
VOS_UINT8                       gucPBCStatus = VOS_TRUE;


extern USIMM_CARD_SERVIC_ENUM_UINT32 g_enAcpuCardStatus;

/*****************************************************************************
?? ?? ??  :
????????  :
????????  :
????????  :
?? ?? ??  :

????????  :
1. ??    ??   : 2009??03??12??
    ??    ??   : m00128685
    ????????   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_ErrorProc(VOS_VOID)
{
    USIMM_CARD_SERVIC_ENUM_UINT32       ulCardStatus = USIMM_CARD_SERVIC_BUTT;


    ulCardStatus = (VOS_UINT8)g_enAcpuCardStatus;


    if( PB_LOCKED == gstPBReqUnit.enPBLock )
    {
        PB_WARNING_LOG("SI_PB_ErrorProc: The PB is Locked");

        return TAF_ERR_UNSPECIFIED_ERROR;
    }
    else if((USIMM_CARD_SERVIC_UNAVAILABLE == ulCardStatus)
             || (USIMM_CARD_SERVIC_ABSENT == ulCardStatus))
    {
        PB_WARNING_LOG("SI_PB_ErrorProc: The Card Absent");

        return TAF_ERR_SIM_FAIL;
    }
    else if( USIMM_CARD_SERVIC_SIM_PUK == ulCardStatus )
    {
        PB_WARNING_LOG("SI_PB_ErrorProc: PUK NEED");

        return TAF_ERR_NEED_PUK1;
    }
    else if( USIMM_CARD_SERVIC_SIM_PIN == ulCardStatus )
    {
        PB_WARNING_LOG("SI_PB_ErrorProc: PIN NEED");

        return TAF_ERR_NEED_PIN1;
    }
    else
    {
        return TAF_ERR_NO_ERROR;
    }
}



/*****************************************************************************
?? ?? ??  : SI_PB_ReadEccProc
????????  : ????????Ecc????????
????????  : usIndexNum: ??????????
            usIndexStar:????????????????
????????  : pstCnfData: ??????????
?? ?? ??  : ??
????????  :
1. ??    ??   : 2007??10??15??
    ??    ??   : z00100318
    ????????   : Creat

*****************************************************************************/
VOS_VOID SI_PB_ReadEccProc(VOS_UINT16 usIndexNum,VOS_UINT16 usIndexStar,SI_PB_EVENT_INFO_STRU *pstCnfData)
{
    VOS_UINT32          ulResult;
    VOS_UINT32          ulValidFlag;
    VOS_UINT8           i;
    VOS_UINT8           *pucContent;

    pucContent = gastPBContent[PB_ECC_CONTENT].pContent + ((usIndexStar-1)*gastPBContent[PB_ECC_CONTENT].ucRecordLen);
    ulValidFlag = VOS_FALSE;

    for(i=0; i<usIndexNum; i++)
    {
        pstCnfData->PBEvent.PBReadCnf.PBRecord.Index = i+usIndexStar;

        ulResult = SI_PB_CheckEccValidity(pucContent);

        if(VOS_ERR == ulResult)
        {
            pstCnfData->PBEvent.PBReadCnf.PBRecord.ValidFlag = SI_PB_CONTENT_INVALID;
        }
        else
        {
            pstCnfData->PBEvent.PBReadCnf.PBRecord.ValidFlag = SI_PB_CONTENT_VALID;
            ulValidFlag = VOS_TRUE;

            SI_PB_BcdToAscii(3, pucContent, pstCnfData->PBEvent.PBReadCnf.PBRecord.Number,
                            &pstCnfData->PBEvent.PBReadCnf.PBRecord.NumberLength);/*Ecc??????????????*/

            pstCnfData->PBEvent.PBReadCnf.PBRecord.NumberType = PB_NUMBER_TYPE_NORMAL;

            if(gastPBContent[PB_ECC_CONTENT].ucNameLen != 0)
            {
                SI_PB_DecodePBName(gastPBContent[PB_ECC_CONTENT].ucNameLen,&pucContent[3],
                                &pstCnfData->PBEvent.PBReadCnf.PBRecord.AlphaTagType,
                                &pstCnfData->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength);

                SI_PB_MemSet(sizeof(pstCnfData->PBEvent.PBReadCnf.PBRecord.AlphaTag),0xFF,pstCnfData->PBEvent.PBReadCnf.PBRecord.AlphaTag);

                /*lint -e534*/
                VOS_MemCpy_s(pstCnfData->PBEvent.PBReadCnf.PBRecord.AlphaTag,
                           pstCnfData->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength,
                          &pucContent[3],
                        pstCnfData->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength);
                /*lint +e534*/
            }
            else
            {
                pstCnfData->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength = 0;
            }
        }

        if(i == (usIndexNum-1))
        {
            pstCnfData->PBLastTag = VOS_TRUE;
            pstCnfData->PBError = ((VOS_TRUE == ulValidFlag)?TAF_ERR_NO_ERROR:TAF_ERR_PB_NOT_FOUND);
        }

        /*lint -e534*/
        SI_PBCallback(pstCnfData);
        /*lint +e534*/

        pucContent += gastPBContent[PB_ECC_CONTENT].ucRecordLen;/*????????????????????????*/
    }

    return;
}

/*****************************************************************************
?? ?? ??  : SI_PB_ReadProc
????????  : ????????????????????
????????  : pMsg:??????????????????
????????  : ??
?? ?? ??  : VOS_ERR/VOS_OK
????????  :
1. ??    ??   : 2007??10??15??
    ??    ??   : z00100318
    ????????   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_ReadProc(PBMsgBlock *pMsg)
{
    SI_PB_READ_REQ_STRU         *pstMsg;
    SI_PB_EVENT_INFO_STRU       stCnfData;
    VOS_UINT8                   ucPBoffset;
    VOS_UINT32                  ulResult;
    VOS_UINT16                  usIndexNum;
    VOS_UINT16                  i;
    VOS_UINT8                   *pucContent;
    VOS_UINT32                  ulValidFlag = VOS_FALSE;

    /*lint -e534*/
    VOS_MemSet_s((VOS_UINT8 *)&stCnfData,
                 sizeof(SI_PB_EVENT_INFO_STRU),
                 (VOS_CHAR)0,
                 sizeof(SI_PB_EVENT_INFO_STRU));
    /*lint +e534*/

    pstMsg = (SI_PB_READ_REQ_STRU*)pMsg;

    stCnfData.ClientId    = pstMsg->usClient;

    stCnfData.OpId        =  pstMsg->ucOpID;

    stCnfData.PBEventType = SI_PB_EVENT_READ_CNF;

    stCnfData.Storage     = pstMsg->ulStorage;

    if (PB_ECC == pstMsg->ulStorage)
    {
        stCnfData.PBError = TAF_ERR_NO_ERROR;
    }

    else
    {
        stCnfData.PBError = SI_PB_ErrorProc();
    }

    if (TAF_ERR_NO_ERROR != stCnfData.PBError)
    {
        PB_WARNING_LOG("SI_PB_ReadProc: Proc Error");

        return SI_PBCallback(&stCnfData);
    }

    gstPBReqUnit.enPBLock = PB_LOCKED;

    ulResult = SI_PB_LocateRecord(pstMsg->ulStorage, pstMsg->usIndex1, pstMsg->usIndex2, &ucPBoffset);

    if(VOS_OK != ulResult) /*????????????????????*/
    {
        PB_WARNING_LOG("SI_PB_ReadProc: SI_PB_LocateRecord Return Error");

        stCnfData.PBError = ulResult;

        /*lint -e534*/
        SI_PBCallback(&stCnfData);
        /*lint +e534*/

        return VOS_ERR;
    }

    if(0 == pstMsg->usIndex1)
    {
        usIndexNum       = gastPBContent[ucPBoffset].usTotalNum;

        pstMsg->usIndex1 = 1;/*????????????????*/

        pstMsg->usIndex2 = gastPBContent[ucPBoffset].usTotalNum;
    }
    else
    {
        usIndexNum = (pstMsg->usIndex2 - pstMsg->usIndex1) + 1;/*????????????????????????*/
    }

    stCnfData.PBEvent.PBReadCnf.RecordNum = 1;

    /*????????????????????Balong????????????*/


    if (PB_ECC == pstMsg->ulStorage)
    {
        SI_PB_ReadEccProc(usIndexNum, pstMsg->usIndex1, &stCnfData);

        gstPBReqUnit.enPBLock = PB_UNLOCK;

        return VOS_OK;
    }

    pucContent = gastPBContent[ucPBoffset].pContent + ((pstMsg->usIndex1-1) * gastPBContent[ucPBoffset].ucRecordLen);

    stCnfData.PBLastTag = VOS_FALSE;

    for(i=0; i<usIndexNum; i++)     /*????????????????????????????*/
    {
        /*lint -e534*/
        VOS_MemSet_s((VOS_UINT8 *)&stCnfData.PBEvent.PBReadCnf,
                     sizeof(SI_PB_EVENT_READ_CNF_STRU),
                     0,
                     sizeof(SI_PB_EVENT_READ_CNF_STRU));
        /*lint +e534*/

        SI_PB_TransPBFromate(&gastPBContent[ucPBoffset], (VOS_UINT16)(pstMsg->usIndex1+i), pucContent, &stCnfData.PBEvent.PBReadCnf.PBRecord);

        pucContent += gastPBContent[ucPBoffset].ucRecordLen;/*????????????????????????*/

        if(SI_PB_CONTENT_VALID == SI_PB_GetBitFromBuf(gastPBContent[ucPBoffset].pIndex,pstMsg->usIndex1+i))/*????Index????SI_PB_CONTENT_VALID == stCnfData.PBEvent.PBReadCnf.PBRecord.ValidFlag) */
        {
            ulValidFlag = VOS_TRUE;
        }

        if(i == (usIndexNum-1))
        {
            stCnfData.PBLastTag = VOS_TRUE;
            stCnfData.PBError = ((VOS_TRUE == ulValidFlag)?TAF_ERR_NO_ERROR:TAF_ERR_PB_NOT_FOUND);
        }

        /*lint -e534*/
        SI_PBCallback(&stCnfData); /*????????????*/
        /*lint +e534*/
    }

    return VOS_OK;
}


/*****************************************************************************
?? ?? ??  :SI_PB_SearchHandle
????????  :??????????????????
????????  :pMsg:????????????????
           ucOffset:??????????????????????
????????  :pstCnfData:????????????
?? ?? ??  :TAF_ERR_PB_NOT_FOUND/TAF_ERR_NO_ERROR
????????  :
????????  :
????????  :
1.  ??    ??   : 2009??03??12??
    ??    ??   : H59254
    ????????   : Creat
*****************************************************************************/
VOS_UINT32 SI_PB_SearchHandle(SI_PB_SEARCH_REQ_STRU *pMsg,
                                      SI_PB_EVENT_INFO_STRU *pstCnfData,
                                      VOS_UINT8 ucOffset)
{
    VOS_UINT16  usMatchRecordNum = 0;
    VOS_UINT16  i;

    pstCnfData->PBError     = TAF_ERR_NO_ERROR;
    pstCnfData->PBLastTag   = VOS_FALSE;
    gstPBReqUnit.enPBLock   = PB_LOCKED;

    for( i = 0 ; i < gastPBContent[ucOffset].usTotalNum ; i++ )
    {
        if(VOS_ERR == SI_PB_CheckContentValidity(&gastPBContent[ucOffset],
                        gastPBContent[ucOffset].pContent + (i * gastPBContent[ucOffset].ucRecordLen)))
        {
            continue;
        }
        else if((VOS_OK == VOS_MemCmp(pMsg->aucContent, gastPBContent[ucOffset].pContent + (i * gastPBContent[ucOffset].ucRecordLen), pMsg->ucLength))
            ||(0 == pMsg->ucLength))
        {
            SI_PB_TransPBFromate(&gastPBContent[ucOffset], (VOS_UINT16)(i+1),
                                    gastPBContent[ucOffset].pContent + (i * gastPBContent[ucOffset].ucRecordLen),
                                    &pstCnfData->PBEvent.PBSearchCnf.PBRecord);

            usMatchRecordNum++;
            /*lint -e534*/
            SI_PBCallback(pstCnfData);
            /*lint +e534*/
        }
        else
        {
            continue;
        }
    }

    if(0 == usMatchRecordNum)
    {
        return TAF_ERR_PB_NOT_FOUND;
    }

    pstCnfData->PBLastTag = VOS_TRUE;
    pstCnfData->PBEvent.PBSearchCnf.PBRecord.ValidFlag = SI_PB_CONTENT_INVALID;

    /*lint -e534*/
    SI_PBCallback(pstCnfData);
    /*lint +e534*/

    return TAF_ERR_NO_ERROR;
}

/*****************************************************************************
?? ?? ??  : SI_PB_SearchReq
????????  : Index??????????????????????
????????  :pMsg:????????????????
           ucOffset:??????????????????????
????????  :pstCnfData:????????????
?? ?? ??  :TAF_ERR_PB_NOT_FOUND/TAF_ERR_NO_ERROR
????????  :
????????  :
????????  :
1.  ??    ??   : 2009??04??15??
    ??    ??   : m00128685
    ????????   : Creat
*****************************************************************************/
VOS_UINT32 SI_PB_SearchReq(SI_PB_SEARCH_REQ_STRU *pMsg,
                                   SI_PB_EVENT_INFO_STRU *pstCnfData,
                                   VOS_UINT8 ucOffset)
{
    VOS_UINT8  ucSendReqFlag = PB_REQ_NOT_SEND;
    VOS_UINT8  ucRecord;
    VOS_UINT32 ulResult;
    VOS_UINT16 usFileId;

    if (pMsg->ucLength <= sizeof(gstPBReqUnit.aucXDNContent))
    {
        /*lint -e534*/
        VOS_MemCpy_s(gstPBReqUnit.aucXDNContent, pMsg->ucLength, pMsg->aucContent, pMsg->ucLength);
        /*lint +e534*/
    }
    else
    {
        PB_WARNING_LOG("SI_PB_SearchReq: Text string too long");

        return TAF_ERR_PARA_ERROR;
    }

    gstPBReqUnit.usCurIndex     = 1;

    gstPBReqUnit.usSearchLen    = pMsg->ucLength;

    gstPBReqUnit.usIndex2       = gastPBContent[ucOffset].usTotalNum;

    gstPBReqUnit.enPBEventType  = SI_PB_EVENT_SEARCH_CNF;

    gstPBReqUnit.ucEqualFlag    = VOS_FALSE;

    gstPBReqUnit.enPBStoateType = pMsg->ulStorage;

    while(gstPBReqUnit.usCurIndex <= gstPBReqUnit.usIndex2)
    {
        if (SI_PB_CONTENT_VALID == SI_PB_GetBitFromBuf(gastPBContent[ucOffset].pIndex,
            gstPBReqUnit.usCurIndex))
        {
            ucSendReqFlag = PB_REQ_SEND;
            break;
        }

        gstPBReqUnit.usCurIndex++;
    }

    if (PB_REQ_SEND == ucSendReqFlag)
    {
        if(SI_PB_STORAGE_SM == pMsg->ulStorage)   /*??????ADN????????????????*/
        {
            ulResult = SI_PB_CountADNRecordNum(gstPBReqUnit.usCurIndex, &usFileId, &ucRecord);
        }
        else                                                                    /*??????????????*/
        {
            ulResult = SI_PB_GetXDNFileID(pMsg->ulStorage, &usFileId);

            ucRecord = (VOS_UINT8)gstPBReqUnit.usCurIndex;
        }

        if(VOS_ERR == ulResult)         /*????????????*/
        {
            PB_WARNING_LOG("SI_PB_SearchReq: Get the XDN File ID and Record Number is Error");

            pstCnfData->PBError = TAF_ERR_PARA_ERROR;

            return TAF_ERR_PARA_ERROR;
        }
    }
    else
    {
        pstCnfData->PBLastTag = VOS_TRUE;

        PB_WARNING_LOG("SI_PB_SearchReq: Content not found!");

        return TAF_ERR_PB_NOT_FOUND;
    }

    return TAF_ERR_NO_ERROR;
}


/*****************************************************************************
?? ?? ??  :SI_PB_SearchProc
????????  :??????????????????
????????  :pMsg:????????????????
????????  :??
?? ?? ??  :VOS_OK/VOS_ERR
????????  :
????????  :
????????  :
1.  ??    ??   : 2009??03??12??
    ??    ??   : H59254
    ????????   : Creat
*****************************************************************************/
VOS_UINT32 SI_PB_SearchProc(PBMsgBlock *pMsg)
{
    SI_PB_EVENT_INFO_STRU   stCnfData;
    VOS_UINT32              ulResult;
    VOS_UINT8               ucOffset = 0;

    stCnfData.ClientId              = ((SI_PB_SEARCH_REQ_STRU*)pMsg)->usClient;
    stCnfData.OpId                  = ((SI_PB_SEARCH_REQ_STRU*)pMsg)->ucOpID;
    stCnfData.PBEventType           = SI_PB_EVENT_SEARCH_CNF;
    stCnfData.PBLastTag             = VOS_TRUE;

    if( TAF_ERR_NO_ERROR != (ulResult = SI_PB_ErrorProc()))/*??????????????????????????????*/
    {
        stCnfData.PBError  = ulResult;
        stCnfData.PBLastTag = VOS_TRUE;
        return SI_PBCallback(&stCnfData);/*????????????*/
    }

    if(VOS_OK != SI_PB_FindPBOffset(((SI_PB_SEARCH_REQ_STRU*)pMsg)->ulStorage, &ucOffset))
    {
        stCnfData.PBError  = TAF_ERR_UNSPECIFIED_ERROR;

        return SI_PBCallback(&stCnfData); /*????????????*/
    }

    if( VOS_NULL_PTR == gastPBContent[ucOffset].pContent )
    {
        if(TAF_ERR_NO_ERROR !=
           (ulResult = SI_PB_SearchReq( (SI_PB_SEARCH_REQ_STRU*)pMsg, &stCnfData, ucOffset ) ) )
        {
            stCnfData.PBError  = ulResult;

            /*lint -e534*/
            SI_PBCallback(&stCnfData); /*????????????*/
            /*lint +e534*/
        }

        return VOS_OK;
    }

    if(TAF_ERR_NO_ERROR !=
            (ulResult = SI_PB_SearchHandle( (SI_PB_SEARCH_REQ_STRU*)pMsg, &stCnfData, ucOffset ) ) )
    {
        stCnfData.PBError  = ulResult;

        /*lint -e534*/
        SI_PBCallback(&stCnfData); /*????????????*/
        /*lint +e534*/
    }

    return VOS_OK;
}

/*****************************************************************************
?? ?? ??  : SI_PB_SReadEMLProc
????????  : Email??????????
????????  : usIndex:??????
            usOffset:????????????????
????????  : pstRecord:??????????
?? ?? ??  : VOS_OK/VOS_ERR
????????  :
????????  :
????????  :
1.  ??    ??   : 2009??06??05??
    ??    ??   : m00128685
    ????????   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_SReadEMLProc(VOS_UINT16 usIndex, VOS_UINT16 usOffset, SI_PB_RECORD_STRU *pstRecord)
{
    VOS_UINT32  ulEMLContentOffset;
    VOS_UINT8 *pucEMLContent;
    VOS_UINT8 ucEMLRecordNum;
    VOS_UINT8 ucType2EMLFileCnt;
    VOS_UINT8   i;

    /*Email,????Type1??2????????????USED, ??????????????
    Type1 ????????Index??
    Type2 ????Index??IAP??????????????????????????????????????????*/
    if(0 == gstPBCtrlInfo.ulEMLFileNum)
    {
        PB_WARNING_LOG("SI_PB_SReadEMLProc: No Valid Email Record");
        return VOS_OK;
    }

    if(PB_FILE_TYPE1 == gstPBCtrlInfo.astEMLInfo[0].enEMLType)/*Email??????????*/
    {
        /* ????TYPE1??????????????????????usIndex + usOffset????????EMAIL?????????? */
        if ((usIndex + usOffset) > gstEMLContent.usTotalNum)
        {
            PB_WARNING_LOG("SI_PB_SReadEMLProc: Email Record Index Large than Total Number.");
            return VOS_OK;
        }

        pucEMLContent = gstEMLContent.pContent
            +((usIndex+(usOffset-1))*gstEMLContent.ucRecordLen);
    }
    else
    {
        if(VOS_NULL_PTR == gstIAPContent.pIAPContent)
        {
            PB_ERROR_LOG("SI_PB_SReadEMLProc: IAP Storage NULL");
            return TAF_ERR_PB_STORAGE_OP_FAIL;
        }

        /*Type2 Email??????????gstIAPContent.pIAPContent??????ADN ??????EML????????????*/
        ucEMLRecordNum = gstIAPContent.pIAPContent[(((usIndex+usOffset)-1)*gstIAPContent.ucRecordLen)
                                                    +(gstPBCtrlInfo.astEMLInfo[0].ulEMLTagNum - 1)];

        if (VOS_OK != SI_PB_GetFileCntFromIndex(usIndex + usOffset, &ucType2EMLFileCnt))
        {
            PB_WARNING_LOG("SI_PB_SReadEMLProc: SI_PB_GetFileCntFromIndex Return Error.");
            return VOS_OK;
        }

        if ((gstPBCtrlInfo.astEMLInfo[ucType2EMLFileCnt - 1].ucRecordNum < ucEMLRecordNum)
            || (0xFF == ucEMLRecordNum)||(0 == ucEMLRecordNum))
        {
            PB_INFO_LOG("SI_PB_SReadEMLProc: No Email Record");
            return VOS_OK;
        }

        ulEMLContentOffset = (ucEMLRecordNum - 1)
                        * gstPBCtrlInfo.astEMLInfo[ucType2EMLFileCnt - 1].ucRecordLen;

        /* ????EMAIL?????????????????????????????????????????????????? */
        for (i = 0; i < (ucType2EMLFileCnt - 1); i++)
        {
            ulEMLContentOffset += gstPBCtrlInfo.astEMLInfo[i].ucRecordLen
                        * gstPBCtrlInfo.astEMLInfo[i].ucRecordNum;
        }

        pucEMLContent = gstEMLContent.pContent + ulEMLContentOffset;
    }

    SI_PB_TransEMLFromate(gstEMLContent.ucDataLen, pucEMLContent, pstRecord);

    return VOS_OK;
}

/*****************************************************************************
?? ?? ??  : SI_PB_SReadANRProc
????????  : ANR??????????
????????  : usIndex:??????
            usOffset:????????????????
????????  : pstRecord:??????????
?? ?? ??  : VOS_OK/VOS_ERR
????????  :
????????  :
????????  :
1.  ??    ??   : 2009??06??05??
    ??    ??   : m00128685
    ????????   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_SReadANRProc(VOS_UINT16 usIndex, VOS_UINT16 usOffset, SI_PB_RECORD_STRU *pstRecord)
{
    VOS_UINT32 ulAnrContentOffset;
    VOS_UINT16 i,j;
    VOS_UINT8  *pucANRContent;
    VOS_UINT8  ucType2ANRRecord;
    VOS_UINT8  ucType2ANRFileCnt;

    /*ANR,??????????????????????????USED??????????????????????????????????
    ????????????????????*/
    for(i = 0; i < gstPBCtrlInfo.ulANRStorageNum; i++)
    {
        if(VOS_NULL == gastANRContent[i].pContent)
        {
            PB_ERROR_LOG("SI_PB_SReadANRProc: Storage NULL");
            return TAF_ERR_PB_STORAGE_OP_FAIL;
        }

        /*??????Type2????ANR??????????IAP??????????????????*/
        if(PB_FILE_TYPE2 == gstPBCtrlInfo.astANRInfo[0][i].enANRType)
        {
            if(VOS_NULL == gstIAPContent.pIAPContent)
            {
                PB_ERROR_LOG("SI_PB_SReadANRProc: Storage NULL");
                return TAF_ERR_PB_STORAGE_OP_FAIL;
            }

            ucType2ANRRecord = gstIAPContent.pIAPContent[(((usIndex+usOffset)-1)*gstIAPContent.ucRecordLen)
                                    +(gstPBCtrlInfo.astANRInfo[0][i].ulANRTagNum-1)];

            if (VOS_OK != SI_PB_GetFileCntFromIndex(usIndex + usOffset, &ucType2ANRFileCnt))
            {
                PB_WARNING_LOG("SI_PB_SReadANRProc: SI_PB_GetFileCntFromIndex Return Error.");

                continue;
            }

            /*Index??????Type2 ANR????*/
            if ((gstPBCtrlInfo.astANRInfo[ucType2ANRFileCnt - 1][i].ucRecordNum < ucType2ANRRecord)
                ||(0 == ucType2ANRRecord)||(0xFF == ucType2ANRRecord))
            {
                PB_NORMAL_LOG("SI_PB_SReadANRProc: Empty Type2 ANR Or Invalid");

                continue;
            }

            ulAnrContentOffset = (ucType2ANRRecord - 1)*gastANRContent[i].ucRecordLen;

            for (j = 0; j < (ucType2ANRFileCnt - 1); j++)
            {
                ulAnrContentOffset += gstPBCtrlInfo.astANRInfo[j][i].ucRecordNum
                                        * gstPBCtrlInfo.astANRInfo[j][i].ucRecordLen;
            }

            pucANRContent = gastANRContent[i].pContent + ulAnrContentOffset;
        }
        else
        {
            /* ????TYPE1??????ANR????????????????usIndex + usOffset????????ANR?????????? */
            if ((usIndex + usOffset) > gastANRContent[i].usTotalNum)
            {
                continue;
            }

            pucANRContent = gastANRContent[i].pContent
                            +(((usIndex+usOffset)-1)*gastANRContent[i].ucRecordLen);
        }

        SI_PB_TransANRFromate((VOS_UINT8)i, pucANRContent, pstRecord);
    }

    return VOS_OK;
}

/*****************************************************************************
?? ?? ??  : SI_PB_SReadProc
????????  : ??????????????
????????  : pMsg: ??????????????????????
????????  : ??
?? ?? ??  : VOS_OK/VOS_ERR
????????  :
????????  :
????????  :
1.  ??    ??   : 2009??06??05??
    ??    ??   : m00128685
    ????????   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_SReadProc(PBMsgBlock *pMsg)
{
    SI_PB_READ_REQ_STRU         *pstMsg;
    SI_PB_EVENT_INFO_STRU       stCnfData;
    VOS_UINT8                   ucPBoffset;
    VOS_UINT32                  ulResult;
    VOS_UINT16                  usIndexNum;
    VOS_UINT16                  i;
    VOS_UINT8                   *pucContent;
    VOS_UINT8                   *pucTempContent;
    VOS_UINT32                  ulValidFlag = VOS_FALSE;

    /*lint -e534*/
    VOS_MemSet_s((VOS_UINT8 *)&stCnfData, sizeof(SI_PB_EVENT_INFO_STRU), 0, sizeof(SI_PB_EVENT_INFO_STRU));
    /*lint +e534*/

    pstMsg = (SI_PB_READ_REQ_STRU*)pMsg;

    stCnfData.ClientId    = pstMsg->usClient;

    stCnfData.OpId        =  pstMsg->ucOpID;

    stCnfData.PBEventType = SI_PB_EVENT_SREAD_CNF;

    stCnfData.Storage     = pstMsg->ulStorage;

    if((0 == gstPBConfigInfo.ucSPBFlag)||(SI_PB_STORAGE_SM != pstMsg->ulStorage))
    {
        /*????Operation not allowed*/
        stCnfData.PBError = TAF_ERR_CMD_TYPE_ERROR;

        PB_WARNING_LOG("SI_PB_SReadProc: Proc is Not Allow");

        return SI_PBCallback(&stCnfData);
    }

    stCnfData.PBError = SI_PB_ErrorProc();

    if (TAF_ERR_NO_ERROR != stCnfData.PBError)
    {
        PB_WARNING_LOG("SI_PB_SReadProc: Proc Error");

        return SI_PBCallback(&stCnfData);
    }

    gstPBReqUnit.enPBLock = PB_LOCKED;

    ulResult = SI_PB_LocateRecord(pstMsg->ulStorage, pstMsg->usIndex1, pstMsg->usIndex2, &ucPBoffset);

    if(VOS_OK != ulResult) /*????????????????????*/
    {
        PB_WARNING_LOG("SI_PB_SReadProc: SI_PB_LocateRecord Return Error");

        stCnfData.PBError = ulResult;

        /*lint -e534*/
        SI_PBCallback(&stCnfData);
        /*lint +e534*/

        return VOS_ERR;
    }

    if(0 == pstMsg->usIndex1)
    {
        usIndexNum       = gastPBContent[ucPBoffset].usTotalNum;

        pstMsg->usIndex1 = 1;/*????????????????*/

        pstMsg->usIndex2 = gastPBContent[ucPBoffset].usTotalNum;
    }
    else
    {
        usIndexNum = (pstMsg->usIndex2 - pstMsg->usIndex1) + 1;/*????????????????????????*/
    }

    if(VOS_NULL == gastPBContent[ucPBoffset].pContent)/*ADN????????????*/
    {
        stCnfData.PBError = TAF_ERR_PB_STORAGE_OP_FAIL;

        PB_WARNING_LOG("SI_PB_SReadProc: The ADN Memory Error");

        return SI_PBCallback(&stCnfData);
    }

    pucContent = gastPBContent[ucPBoffset].pContent + ((pstMsg->usIndex1-1) * gastPBContent[ucPBoffset].ucRecordLen);

    stCnfData.PBLastTag = VOS_FALSE;

    for(i=0; i<usIndexNum; i++)     /*????????????????????????????*/
    {
        stCnfData.PBError = VOS_OK;

        /*lint -e534*/
        VOS_MemSet_s((VOS_UINT8 *)&stCnfData.PBEvent.PBReadCnf,
                     sizeof(SI_PB_EVENT_READ_CNF_STRU),
                     0,
                     sizeof(SI_PB_EVENT_READ_CNF_STRU));
        /*lint +e534*/

        stCnfData.PBEvent.PBReadCnf.RecordNum = 1;

        stCnfData.PBEvent.PBReadCnf.PBRecord.Index = (VOS_UINT16)(pstMsg->usIndex1+i);

        /*????????????????????????????*/
        if(SI_PB_CONTENT_INVALID == SI_PB_GetBitFromBuf(gastPBContent[ucPBoffset].pIndex,pstMsg->usIndex1+i))/*??Index??????????????*/
        {
            if(i == (usIndexNum-1))/*????????????????*/
            {
                stCnfData.PBError = ((VOS_TRUE == ulValidFlag)?TAF_ERR_NO_ERROR:TAF_ERR_PB_NOT_FOUND);
                stCnfData.PBLastTag = VOS_TRUE;

                return SI_PBCallback(&stCnfData);
            }
            else
            {
                continue;
            }
        }

        ulValidFlag = VOS_TRUE;

        pucTempContent = pucContent + (i*gastPBContent[ucPBoffset].ucRecordLen);/*????????????????????????*/

        SI_PB_TransPBFromate(&gastPBContent[ucPBoffset], (VOS_UINT16)(pstMsg->usIndex1+i), pucTempContent, &stCnfData.PBEvent.PBReadCnf.PBRecord);

        /*ANR,??????????????????????????USED??????????????????????????????????
        ????????????????????*/
        ulResult = SI_PB_SReadANRProc(pstMsg->usIndex1, i, &stCnfData.PBEvent.PBReadCnf.PBRecord);

        if(VOS_OK != ulResult)
        {
            stCnfData.PBError = ulResult;

            PB_WARNING_LOG("SI_PB_SReadProc: SI_PB_SReadANRProc Return Error");

            return SI_PBCallback(&stCnfData);
        }

        ulResult = SI_PB_SReadEMLProc(pstMsg->usIndex1, i, &stCnfData.PBEvent.PBReadCnf.PBRecord);

        if(VOS_OK != ulResult)
        {
            stCnfData.PBError = ulResult;

            PB_WARNING_LOG("SI_PB_SReadProc: SI_PB_SReadEMLProc Return Error");

            return SI_PBCallback(&stCnfData);
        }

        /*????????????????????????????????????True*/
        if(i == (usIndexNum-1))
        {
            stCnfData.PBLastTag = VOS_TRUE;
        }

        /*lint -e534*/
        SI_PBCallback(&stCnfData); /*????????????*/
        /*lint +e534*/
    }

    return VOS_OK;
}

/*****************************************************************************
?? ?? ??  : SI_PBUpdateGobal
????????  : ????????Ccpu??????????????????????????????????
????????  : Ccpu??????????????
????????  : ??
?? ?? ??  : ??
????????  :
1.  ??    ??   : 2007??10??15??
    ??    ??   :
    ????????   : Creat

*****************************************************************************/
VOS_UINT32 SI_PBUpdateAGlobal(PBMsgBlock *pMsg)
{
    SI_PB_UPDATEGLOBAL_IND_STRU        *pstMsg;

    VOS_UINT32                          i;
    VOS_UINT_PTR                        TempAddr;

    pstMsg = (SI_PB_UPDATEGLOBAL_IND_STRU*)pMsg;

    /*lint -e534*/
    VOS_MemCpy_s(&gstPBCtrlInfo,  sizeof(gstPBCtrlInfo), &pstMsg->stPBCtrlInfo,   sizeof(gstPBCtrlInfo));
    VOS_MemCpy_s(&gstPBConfigInfo,sizeof(gstPBConfigInfo), &pstMsg->stPBConfigInfo, sizeof(gstPBConfigInfo));
    VOS_MemCpy_s(gastPBContent, sizeof(gastPBContent),  pstMsg->astPBContent,   sizeof(gastPBContent));
    VOS_MemCpy_s(gastEXTContent, sizeof(gastEXTContent), pstMsg->astEXTContent,  sizeof(gastEXTContent));
    VOS_MemCpy_s(gastANRContent, sizeof(gastANRContent), pstMsg->astANRContent,  sizeof(gastANRContent));
    VOS_MemCpy_s(&gstEMLContent, sizeof(gstEMLContent), &pstMsg->stEMLContent,   sizeof(gstEMLContent));
    VOS_MemCpy_s(&gstIAPContent, sizeof(gstIAPContent), &pstMsg->stIAPContent,   sizeof(gstIAPContent));
    VOS_MemCpy_s(&gstPBInitState, sizeof(gstPBInitState), &pstMsg->stPBInitState,  sizeof(gstPBInitState));
    /*lint +e534*/

    for (i=0; i<PB_CONTENT_BUTT; i++)
    {
        gastPBContent[i].pContent   = VOS_NULL_PTR;

        TempAddr = pstMsg->astPBContentAddr[i].ulContentAddr;

        gastPBContent[i].pContent   = (VOS_UINT8 *)TempAddr;

        gastPBContent[i].pIndex     = VOS_NULL_PTR;

        TempAddr = pstMsg->astPBContentAddr[i].ulIndexAddr;

        gastPBContent[i].pIndex     = (VOS_UINT8 *)TempAddr;

        if(VOS_NULL_PTR != gastPBContent[i].pContent)
        {
            gastPBContent[i].pContent   = (VOS_UINT8*)mdrv_phy_to_virt(MEM_DDR_MODE, gastPBContent[i].pContent);
        }
        if (VOS_NULL_PTR != gastPBContent[i].pIndex)
        {
            gastPBContent[i].pIndex     = (VOS_UINT8*)mdrv_phy_to_virt(MEM_DDR_MODE, gastPBContent[i].pIndex);
        }
    }

    for (i=0; i<SI_PB_MAX_NUMBER; i++)
    {
        gastEXTContent[i].pExtContent   = VOS_NULL_PTR;

        TempAddr = pstMsg->aulExtContentAddr[i];

        gastEXTContent[i].pExtContent   = (VOS_UINT8 *)TempAddr;

        if(VOS_NULL_PTR != gastEXTContent[i].pExtContent)
        {
            gastEXTContent[i].pExtContent   = (VOS_UINT8*)mdrv_phy_to_virt(MEM_DDR_MODE, gastEXTContent[i].pExtContent);
        }
    }

    for (i=0; i<SI_PB_ANRMAX; i++)
    {
        gastANRContent[i].pContent   = VOS_NULL_PTR;

        TempAddr = pstMsg->aulANRContentAddr[i];

        gastANRContent[i].pContent   = (VOS_UINT8*)TempAddr;

        if(VOS_NULL_PTR != gastANRContent[i].pContent)
        {
            gastANRContent[i].pContent   = (VOS_UINT8*)mdrv_phy_to_virt(MEM_DDR_MODE, gastANRContent[i].pContent);
        }
    }

    gstEMLContent.pContent  = VOS_NULL_PTR;

    TempAddr = pstMsg->ulEMLContentAddr;

    gstEMLContent.pContent      = (VOS_UINT8*)TempAddr;

    if(VOS_NULL_PTR != gstEMLContent.pContent)
    {
        gstEMLContent.pContent  = (VOS_UINT8*)mdrv_phy_to_virt(MEM_DDR_MODE, gstEMLContent.pContent);
    }

    gstIAPContent.pIAPContent   = VOS_NULL_PTR;

    TempAddr = pstMsg->ulIAPContentAddr;

    gstIAPContent.pIAPContent   = (VOS_UINT8*)TempAddr;

    if(VOS_NULL_PTR != gstIAPContent.pIAPContent)
    {
        gstIAPContent.pIAPContent   = (VOS_UINT8*)mdrv_phy_to_virt(MEM_DDR_MODE, gstIAPContent.pIAPContent);
    }

    return VOS_OK;
}

/*****************************************************************************
?? ?? ??  : SI_PBUpdateACurPB
????????  : ????????Ccpu????????????????????????????
????????  : Ccpu??????????????????
????????  : ??
?? ?? ??  : ??
????????  :
????????  :
????????  :
1.  ??    ??   : 2007??10??15??
    ??    ??   :
    ????????   : Creat

*****************************************************************************/
VOS_UINT32 SI_PBUpdateACurPB(PBMsgBlock *pMsg)
{
    SI_PB_SETPB_IND_STRU *pstMsg;

    pstMsg = (SI_PB_SETPB_IND_STRU*)pMsg;

    gstPBCtrlInfo.enPBCurType = pstMsg->enPBCurType;

    return VOS_OK;
}


/*****************************************************************************
?? ?? ??  : SI_PB_InitGlobeVariable
????????  : ??????PB??????????????
????????  : ??
????????  : gstPBCtrlInfo
            gstPBInitState
            gstPBReqUnit
            gastPBContent
?? ?? ??  : ??
????????  : VOS_MemSet
            SI_PB_MemSet
????????  :
????????  :
1.  ??    ??   : 2008??10??15??
    ??    ??   : m00128685
    ????????   : Creat

*****************************************************************************/
VOS_VOID SI_PB_InitGlobeVariable(VOS_VOID)
{
    /*lint -e534*/
    VOS_MemSet_s(&gstPBCtrlInfo, sizeof(gstPBCtrlInfo), 0, sizeof(gstPBCtrlInfo));

    VOS_MemSet_s(&gstPBInitState, sizeof(gstPBInitState), 0, sizeof(gstPBInitState));
    /*lint +e534*/


    /*lint -e534*/
    VOS_MemSet_s(&gastEXTContent[0], SI_PB_MAX_NUMBER * sizeof(SI_EXT_CONTENT_STRU), 0, SI_PB_MAX_NUMBER * sizeof(SI_EXT_CONTENT_STRU));

    VOS_MemSet_s(&gastANRContent[0], SI_PB_ANRMAX * sizeof(SI_ANR_CONTENT_STRU), 0, SI_PB_ANRMAX * sizeof(SI_ANR_CONTENT_STRU));

    VOS_MemSet_s(&gstEMLContent, sizeof(SI_EML_CONTENT_STRU), 0, sizeof(SI_EML_CONTENT_STRU));

    VOS_MemSet_s(&gstPBReqUnit, sizeof(SI_PB_REQ_UINT_STRU), 0, sizeof(SI_PB_REQ_UINT_STRU));
    /*lint +e534*/

    SI_PB_MemSet(sizeof(gstPBCtrlInfo.astADNInfo), 0xFF,(VOS_UINT8 *)gstPBCtrlInfo.astADNInfo);

    gstPBCtrlInfo.enPBCurType = SI_PB_STORAGE_SM;

    /*????????????????????????????????????????*/
    gastPBContent[PB_ECC_CONTENT].enPBType         = PB_ECC;

    gastPBContent[PB_ECC_CONTENT].enActiveStatus   = SI_PB_ACTIVE;

    gastPBContent[PB_ADN_CONTENT].enPBType         = PB_ADN;

    gastPBContent[PB_ADN_CONTENT].enActiveStatus   = SI_PB_ACTIVE;

    gastPBContent[PB_FDN_CONTENT].enPBType         = PB_FDN;

    gastPBContent[PB_FDN_CONTENT].enActiveStatus   = SI_PB_ACTIVE;

    gastPBContent[PB_BDN_CONTENT].enPBType         = PB_BDN;

    gastPBContent[PB_BDN_CONTENT].enActiveStatus   = SI_PB_ACTIVE;

    gastPBContent[PB_MSISDN_CONTENT].enPBType       = PB_MISDN;

    gastPBContent[PB_MSISDN_CONTENT].enActiveStatus = SI_PB_ACTIVE;

    gastPBContent[PB_SDN_CONTENT].enPBType          = PB_SDN;

    gastPBContent[PB_SDN_CONTENT].enActiveStatus    = SI_PB_ACTIVE;


    return;
}

/*****************************************************************************
?? ?? ??  : WuepsPBPidInit
????????  : ??????PB??????????????
????????  : ??
????????  : ??
?? ?? ??  : VOS_OK
????????  : SI_PB_InitGlobeVariable
????????  :
????????  :
1.  ??    ??   : 2008??10??15??
    ??    ??   : m00128685
    ????????   : Creat

*****************************************************************************/
VOS_UINT32 WuepsPBPidInit(enum VOS_INIT_PHASE_DEFINE InitPhrase)
{
    switch (InitPhrase)
    {
        case   VOS_IP_LOAD_CONFIG:
            SI_PB_InitGlobeVariable();
            break;


		default:
            break;
    }
    return VOS_OK;

}


/*****************************************************************************
?? ?? ??  : SI_PB_PidMsgProc
????????  : ????????????????????????
????????  : pstPBMsg - ????????
????????  : ??
?? ?? ??  : ??
????????  :
1.  ??    ??   : 2007??10??15??
    ??    ??   : z00100318
    ????????   : Creat

*****************************************************************************/
SI_PB_PROC_LIST_STRU    gastPBReqProc[] =
{
    {SI_PB_READ_REQ,        SI_PB_ReadProc},        /*??????????*/
    {SI_PB_SEARCH_REQ,      SI_PB_SearchProc},      /*??????????*/
    {SI_PB_SREAD_REQ,       SI_PB_SReadProc},       /*??????????????*/
    {SI_PB_UPDATE_AGOBAL,   SI_PBUpdateAGlobal},    /*????????????*/
    {SI_PB_UPDATE_CURPB,    SI_PBUpdateACurPB},     /*??????????????????*/
};


VOS_VOID SI_PB_PidMsgProc(struct MsgCB *pstPBMsg)
{
    VOS_UINT32 ulResult = VOS_ERR;
    VOS_UINT32 i;

    /*????Ccpu????????USIMM??????????*/
    {
        for(i=0; i<(sizeof(gastPBReqProc)/sizeof(SI_PB_PROC_LIST_STRU)); i++)
        {
            if(gastPBReqProc[i].ulMsgType == ((PBMsgBlock*)pstPBMsg)->ulMsgName)
            {
                ulResult = gastPBReqProc[i].pProcFun((PBMsgBlock*)pstPBMsg); /*????????????*/
                break;
            }
        }
    }

    if(VOS_OK !=  ulResult)
    {
        PB_ERROR_LOG("SI_PB_PidMsgProc:Process Message Error");
    }

    return;
}

/*****************************************************************************
?? ?? ??  : SI_PBCallback
????????  : ????????????
????????  : ??
????????  : ??
?? ?? ??  : VOS_UINT32??????????????????
????????  : ??
????????  : ????????
History     :
1.??    ??  : 2008??10??20??
  ??    ??  : H59254
  ????????  : Create
*****************************************************************************/
extern TAF_VOID At_PbCallBackFunc(SI_PB_EVENT_INFO_STRU  *pEvent);

VOS_UINT32 SI_PBCallback(SI_PB_EVENT_INFO_STRU *pstEvent)
{

    if(pstEvent->PBError != TAF_ERR_NO_ERROR)
    {
        gstPBReqUnit.enPBLock = PB_UNLOCK;/*????*/
    }
    else if((pstEvent->PBEventType != SI_PB_EVENT_READ_CNF)&&
            (pstEvent->PBEventType != SI_PB_EVENT_SREAD_CNF)&&
            (pstEvent->PBEventType != SI_PB_EVENT_SEARCH_CNF))
    {
        gstPBReqUnit.enPBLock = PB_UNLOCK;/*????*/
    }
    else if(pstEvent->PBLastTag == VOS_TRUE)
    {
        gstPBReqUnit.enPBLock = PB_UNLOCK;/*????*/
    }
    else
    {

    }

    At_PbCallBackFunc(pstEvent);


    return VOS_OK;
}


