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
#include "AtCmdSimProc.h"
#include "AtEventReport.h"


/*****************************************************************************
    ??????????????????????.C??????????
*****************************************************************************/
/*lint -e767 -e960*/
#define    THIS_FILE_ID                 PS_FILE_ID_AT_CMD_SIM_PROC_C
/*lint +e767 +e960*/

/*****************************************************************************
  2 ????????????
*****************************************************************************/

/*****************************************************************************
  3 ????????????
*****************************************************************************/
extern VOS_UINT32 AT_Hex2AsciiStrLowHalfFirst(
    VOS_UINT32                          ulMaxLength,
    VOS_INT8                            *pcHeadaddr,
    VOS_UINT8                           *pucDst,
    VOS_UINT8                           *pucSrc,
    VOS_UINT16                          usSrcLen
);

/*****************************************************************************
  4 ????????
*****************************************************************************/
/*****************************************************************************
 ?? ?? ??  : At_SetSIMSlotPara
 ????????  : ^SIMSLOT, ????modem??????SIM??????????????SIM????
 ????????  : VOS_UINT8 ucIndex
 ????????  : ??
 ?? ?? ??  : VOS_UINT8
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2013??7??4??
    ??    ??   : s00190137
    ????????   : ??????????

  2.??    ??   : 2015??6??11??
    ??    ??   : l00198894
    ????????   : TSTS

  3.??    ??   : 2015??11??25??
    ??    ??   : l00198894
    ????????   : DTS2015112506652: Dallas????????????????
*****************************************************************************/
VOS_UINT32 At_SetSIMSlotPara(VOS_UINT8 ucIndex)
{
    TAF_NV_SCI_CFG_STRU                 stSCICfg;

    /* ???????? */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ???????? */
    if (gucAtParaIndex > 3)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ???????? */
    if ( (0 == gastAtParaList[0].usParaLen)
       ||(0 == gastAtParaList[1].usParaLen) )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ??????????3??????????????????????????????????2 */
    if (0 == gastAtParaList[2].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ????????Modem?????????????????????? */
    if ( (gastAtParaList[0].ulParaValue == gastAtParaList[1].ulParaValue)
      || (gastAtParaList[0].ulParaValue == gastAtParaList[2].ulParaValue)
      || (gastAtParaList[1].ulParaValue == gastAtParaList[2].ulParaValue) )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ??NV??????????SIM????SCI???? */
    PS_MEM_SET(&stSCICfg, 0, sizeof(stSCICfg));
    if (NV_OK != NV_ReadEx(MODEM_ID_0,
                            ev_NV_Item_SCI_DSDA_CFG,
                            &stSCICfg,
                            sizeof(stSCICfg)))
    {
        AT_ERR_LOG("At_SetSIMSlotPara: ev_NV_Item_SCI_DSDA_CFG read fail!");
        return AT_ERROR;
    }

    /*
         ????????????????????card0????card1??????????NV??????????????????bit????????????????:
         card0: bit[8-10]??????0??????SCI????
             0??????SCI0??????????
             1??????SCI1
             2??????SCI2
             ????????????
         card1:bit[11-13]????1????????SCI????
             0??????SCI0
             1??????SCI1??????????
             2??????SCI2
             ????????????
         card2:bit[14-16]????2????????SCI????
             0??????SCI0
             1??????SCI1
             2??????SCI2??????????
             ????????????
     */
    stSCICfg.bitCard0   = gastAtParaList[0].ulParaValue;
    stSCICfg.bitCard1   = gastAtParaList[1].ulParaValue;

    /* ???????????????????????????????????????????????? */
    stSCICfg.bitCard2   = gastAtParaList[2].ulParaValue;
    stSCICfg.bitCardNum = 3;

    stSCICfg.bitReserved0 = 0;
    stSCICfg.bitReserved1 = 0;


    /* ????????SCI????????NV?? */
    if (NV_OK != NV_WriteEx(MODEM_ID_0,
                            ev_NV_Item_SCI_DSDA_CFG,
                            &stSCICfg,
                            sizeof(stSCICfg)))
    {
        AT_ERR_LOG("At_SetSIMSlotPara: ev_NV_Item_SCI_DSDA_CFG write failed");
        return AT_ERROR;
    }

    return AT_OK;
}

/*****************************************************************************
 ?? ?? ??  : At_QrySIMSlotPara
 ????????  : ????SIM??????????
 ????????  : VOS_UINT8 ucIndex
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2013??7??4??
    ??    ??   : s00190137
    ????????   : ??????????

  2.??    ??   : 2015??6??11??
    ??    ??   : l00198894
    ????????   : TSTS
*****************************************************************************/
VOS_UINT32 At_QrySIMSlotPara(VOS_UINT8 ucIndex)
{
    TAF_NV_SCI_CFG_STRU                 stSCICfg;
    VOS_UINT16                          usLength;

    /*??NV??????????SIM????SCI????*/
    PS_MEM_SET(&stSCICfg, 0, sizeof(stSCICfg));
    if (NV_OK != NV_ReadEx(MODEM_ID_0,
                            ev_NV_Item_SCI_DSDA_CFG,
                            &stSCICfg,
                            sizeof(stSCICfg)))
    {
        AT_ERR_LOG("At_QrySIMSlotPara: ev_NV_Item_SCI_DSDA_CFG read fail!");
        gstAtSendData.usBufLen = 0;
        return AT_ERROR;
    }

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s: %d,%d",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      stSCICfg.bitCard0,
                                      stSCICfg.bitCard1);

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       ",%d",
                                       stSCICfg.bitCard2);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}

/*****************************************************************************
 Prototype      : At_Base16Decode
 Description    : ^HVSDH
 Input          : ucIndex --- ????????
 Output         :
 Return Value   : AT_XXX  --- ATC??????
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2013-03-20
    Author      : g47350
    Modification: Created function
*****************************************************************************/
VOS_UINT32 At_Base16Decode(VOS_CHAR *pcData, VOS_UINT32 ulDataLen, VOS_UINT8* pucDst)
{
    VOS_UINT32 ulLen    = ulDataLen;
    VOS_UINT32 i        = 0;
    VOS_CHAR   n[2] = {0};
    VOS_UINT32 j;

    while(i < ulLen)
    {
        for(j = 0; j < 2; j++)
        {
            if(pcData[(VOS_ULONG)(i+j)] >= '0' && pcData[(VOS_ULONG)(i+j)] <= '9')
            {
                n[(VOS_ULONG)j] = pcData[(VOS_ULONG)(i+j)] - '0';
            }
            else if(pcData[(VOS_ULONG)(i+j)] >= 'a' && pcData[(VOS_ULONG)(i+j)] <= 'f')
            {
                n[(VOS_ULONG)j] = pcData[(VOS_ULONG)(i+j)] - 'a' + 10;
            }
            else if(pcData[(VOS_ULONG)(i+j)] >= 'A' && pcData[(VOS_ULONG)(i+j)] <= 'F')
            {
                n[(VOS_ULONG)j] = pcData[(VOS_ULONG)(i+j)] - 'A' + 10;
            }
            else
            {
                ;
            }
        }

        pucDst[i/2] = (VOS_UINT8)(n[0] * 16 + n[1]);

        i += 2;
    }

    return (ulDataLen/2);
}

/*****************************************************************************
 ?? ?? ??  : At_SetHvsstPara
 ????????  : (AT^HVSST)????/??????(U)SIM??
 ????????  : ucIndex - ????????
 ????????  : ??
 ?? ?? ??  :
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2013??03??18??
    ??    ??   : zhuli
    ????????   : vSIM??????????????
  2.??    ??   : 2014??10??9??
    ??    ??   : zhuli
    ????????   : ??????????????????????????????????
  3.??    ??   : 2015??6??10??
    ??    ??   : l00198894
    ????????   : TSTS
*****************************************************************************/
VOS_UINT32 At_SetHvsstPara(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT32                              ulResult;
    SI_PIH_HVSST_SET_STRU                   stHvSStSet;

    /* ???????????? */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ???????? */
    if (gucAtParaIndex != 2)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ???????? */
    if ( (0 == gastAtParaList[0].usParaLen)
      || (0 == gastAtParaList[1].usParaLen) )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    PS_MEM_SET(&stHvSStSet, 0, sizeof(stHvSStSet));

    stHvSStSet.ucIndex = (VOS_UINT8)gastAtParaList[0].ulParaValue;
    stHvSStSet.enSIMSet = (VOS_UINT8)gastAtParaList[1].ulParaValue;

    ulResult = SI_PIH_HvSstSet(gastAtClientTab[ucIndex].usClientId,
                               gastAtClientTab[ucIndex].opId,
                               &stHvSStSet);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("At_SetHvsstPara: SI_PIH_HvSstSet fail.");
        return AT_ERROR;
    }

    /* ????AT???????????????????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_HVSST_SET;

    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 ?? ?? ??  : At_QryHvsstPara
 ????????  : ^HVSST????????????????
 ????????  : VOS_UINT8 ucIndex
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2013??03??18??
    ??    ??   : zhuli
    ????????   : vSIM??????????????
  2.??    ??   : 2014??10??9??
    ??    ??   : zhuli
    ????????   : ??????????????????????????????????
  3.??    ??   : 2015??6??11??
    ??    ??   : l00198894
    ????????   : TSTS
*****************************************************************************/
VOS_UINT32 At_QryHvsstPara(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT32                          ulResult;

    ulResult = SI_PIH_HvSstQuery(gastAtClientTab[ucIndex].usClientId,
                                 gastAtClientTab[ucIndex].opId);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_QryPortAttribSetPara: SI_PIH_HvSstQuery fail.");
        return AT_ERROR;
    }

    /* ????AT???????????????????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_HVSST_QRY;

    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 ?? ?? ??  : At_HvsstQueryCnf
 ????????  : ^HVSST????????????
 ????????  : SI_PIH_EVENT_INFO_STRU *pstEvent
 ????????  : ??
 ?? ?? ??  : VOS_UINT16
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2013??3??18??
    ??    ??   : z00100318
    ????????   : ??????????

  2.??    ??   : 2015??6??10??
    ??    ??   : l00198894
    ????????   : TSTS
*****************************************************************************/
VOS_UINT16 At_HvsstQueryCnf(
    VOS_UINT8                           ucIndex,
    SI_PIH_EVENT_INFO_STRU             *pstEvent)
{
    VOS_UINT16                          usLength;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRslt;
    TAF_NV_SCI_CFG_STRU                 stSCICfg;
    VOS_UINT32                          ulSlot;
    SI_PIH_SIM_INDEX_ENUM_UINT8         enSimIndex;

    usLength    = 0;
    ulRslt      = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("At_HvsstQueryCnf: Get modem id fail.");
        return usLength;
    }

    /* ??NV??????????SIM????SCI???? */
    PS_MEM_SET(&stSCICfg, 0, sizeof(stSCICfg));
    if (NV_OK != NV_ReadEx(MODEM_ID_0,
                            ev_NV_Item_SCI_DSDA_CFG,
                            &stSCICfg,
                            sizeof(stSCICfg)))
    {
        AT_ERR_LOG("At_HvsstQueryCnf: ev_NV_Item_SCI_DSDA_CFG read fail!");
        return usLength;
    }

    if (MODEM_ID_0 == enModemId)
    {
        ulSlot = stSCICfg.bitCard0;
    }
    else if (MODEM_ID_1 == enModemId)
    {
        ulSlot = stSCICfg.bitCard1;
    }
    else
    {
        ulSlot = stSCICfg.bitCard2;
    }

    if (SI_PIH_SIM_ENABLE == pstEvent->PIHEvent.HVSSTQueryCnf.enVSimState)
    {
        enSimIndex = SI_PIH_SIM_VIRT_SIM1;
    }
    else
    {
        enSimIndex = SI_PIH_SIM_REAL_SIM1;
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s: %d,%d,%d,%d",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                       enSimIndex,
                                       1,
                                       ulSlot,
                                       pstEvent->PIHEvent.HVSSTQueryCnf.enCardUse);

    return usLength;
}

/*****************************************************************************
 ?? ?? ??  : At_SetSciChgPara
 ????????  : ^SCICHG????????
 ????????  : VOS_UINT8 ucIndex
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??  : 2014??10??9??
    ??    ??  : zhuli
    ????????  : ??????????????????????

  2.??    ??   : 2015??6??10??
    ??    ??   : l00198894
    ????????   : TSTS
*****************************************************************************/
VOS_UINT32 At_SetSciChgPara(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT32                          ulResult;

    /* ???????????? */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ???????? */
    if (gucAtParaIndex > 3)
    {
        return AT_TOO_MANY_PARA;
    }

    /* ???????? */
    if ( (0 == gastAtParaList[0].usParaLen)
       ||(0 == gastAtParaList[1].usParaLen) )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ??????????3??????????????????????????????????2 */
    if (0 == gastAtParaList[2].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ????????Modem?????????????????????? */
    if ( (gastAtParaList[0].ulParaValue == gastAtParaList[1].ulParaValue)
      || (gastAtParaList[0].ulParaValue == gastAtParaList[2].ulParaValue)
      || (gastAtParaList[1].ulParaValue == gastAtParaList[2].ulParaValue) )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ulResult = SI_PIH_SciCfgSet(gastAtClientTab[ucIndex].usClientId,
                                gastAtClientTab[ucIndex].opId,
                                gastAtParaList[0].ulParaValue,
                                gastAtParaList[1].ulParaValue,
                                gastAtParaList[2].ulParaValue);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("At_SetSciChgPara: SI_PIH_HvSstSet fail.");
        return AT_CME_PHONE_FAILURE;
    }

    /* ????AT???????????????????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SCICHG_SET;

    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 ?? ?? ??  : At_QryHvsstPara
 ????????  : ^SCICHG????????????????
 ????????  : VOS_UINT8 ucIndex
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??  : 2014??10??9??
    ??    ??  : zhuli
    ????????  : ??????????????????????

  2.??    ??   : 2015??6??10??
    ??    ??   : l00198894
    ????????   : TSTS
*****************************************************************************/
VOS_UINT32 At_QrySciChgPara(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT32                          ulResult;

    ulResult = SI_PIH_SciCfgQuery(gastAtClientTab[ucIndex].usClientId,
                                  gastAtClientTab[ucIndex].opId);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("At_QrySciChgPara: SI_PIH_SciCfgQuery fail.");
        return AT_ERROR;
    }

    /* ????AT???????????????????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SCICHG_QRY;

    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 ?? ?? ??  : At_SciCfgQueryCnf
 ????????  : TSTS
 ????????  : VOS_UINT8                           ucIndex
             SI_PIH_EVENT_INFO_STRU             *pstEvent
 ????????  : ??
 ?? ?? ??  : VOS_UINT16
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??6??11??
    ??    ??   : l00198894
    ????????   : ??????????

*****************************************************************************/
VOS_UINT16 At_SciCfgQueryCnf(
    VOS_UINT8                           ucIndex,
    SI_PIH_EVENT_INFO_STRU             *pstEvent)
{
    VOS_UINT16                          usLength;

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s: %d,%d",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      pstEvent->PIHEvent.SciCfgCnf.enCard0Slot,
                                      pstEvent->PIHEvent.SciCfgCnf.enCard1Slot);

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       ",%d",
                                       pstEvent->PIHEvent.SciCfgCnf.enCard2Slot);

    return usLength;
}

/*****************************************************************************
 Prototype      : At_Hex2Base16
 Description    : ??16????????BASE64????
 Input          : nptr --- ??????
 Output         :
 Return Value   : ????????
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT16 At_Hex2Base16(VOS_UINT32 MaxLength,VOS_CHAR *headaddr,VOS_CHAR *pucDst,VOS_UINT8 *pucSrc,VOS_UINT16 usSrcLen)
{
    VOS_UINT32          i;
    VOS_CHAR            *pcData;

    pcData = pucDst;

    for(i=0; i<usSrcLen; i++)
    {
        At_sprintf((VOS_INT32)MaxLength,headaddr,pcData,"%X",((pucSrc[i]&0xF0)>>4));

        pcData++;

        At_sprintf((VOS_INT32)MaxLength,headaddr,pcData,"%X",(pucSrc[i]&0x0F));

        pcData++;
    }

    return (VOS_UINT16)(usSrcLen*2);
}

/*****************************************************************************
 Prototype      : At_SetHvsDHPara
 Description    : ^HVSDH
 Input          : ucIndex --- ????????
 Output         :
 Return Value   : AT_XXX  --- ATC??????
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2013-03-20
    Author      : g47350
    Modification: Created function
*****************************************************************************/
VOS_UINT32 At_SetHvsDHPara(VOS_UINT8 ucIndex)
{
    VSIM_KEYDATA_STRU                   stKeyData;
    VOS_VOID                           *pOutputData;
    VOS_UINT32                          ulOutputLen;

    /* ???????? */
    if(gucAtParaIndex > 1)
    {
        AT_WARN_LOG("At_SetHvsDHPara: Para too much.");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ?????????????? */
    if ((0 == gastAtParaList[0].usParaLen)
        ||(1 == (gastAtParaList[0].usParaLen%2)))
    {
        AT_WARN_LOG("At_SetHvsDHPara: Para Len Error.");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    pOutputData = PS_MEM_ALLOC(WUEPS_PID_AT, gastAtParaList[0].usParaLen);

    if (VOS_NULL_PTR == pOutputData)
    {
        AT_WARN_LOG("At_SetHvsDHPara: PS_MEM_ALLOC Error.");
        return AT_ERROR;
    }

    /* ???????????????????? */
    ulOutputLen = At_Base16Decode((VOS_CHAR *)gastAtParaList[0].aucPara, gastAtParaList[0].usParaLen, pOutputData);

    /* ?????????????? */
    if (VSIM_KEYLEN_MAX < ulOutputLen)
    {
        PS_MEM_FREE(WUEPS_PID_AT, pOutputData);

        AT_WARN_LOG("At_SetHvsDHPara: Result Data too Long.");

        return AT_CME_INCORRECT_PARAMETERS;
    }

    PS_MEM_CPY(stKeyData.aucKey, pOutputData, ulOutputLen);

    stKeyData.ulKeyLen = ulOutputLen;

    /* ?????????????????? */
    PS_MEM_FREE(WUEPS_PID_AT, pOutputData);

    if(TAF_SUCCESS == SI_PIH_HvsDHSet(gastAtClientTab[ucIndex].usClientId, 0, &stKeyData))
    {
        /* ???????????????? */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_HVSDH_SET;

        return AT_WAIT_ASYNC_RETURN;    /* ???????????????????? */
    }

    AT_WARN_LOG("At_SetHvsDHPara: SI_PIH_HvsDHSet Error.");

    return AT_ERROR;
}

/*****************************************************************************
 Prototype      : At_QryHvsDHPara
 Description    : ^HVSDH
 Input          : ucIndex --- ????????
 Output         :
 Return Value   : AT_XXX  --- ATC??????
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2013-03-20
    Author      : g47350
    Modification: Created function
*****************************************************************************/
VOS_UINT32 At_QryHvsDHPara(VOS_UINT8 ucIndex)
{
    if(AT_SUCCESS == SI_PIH_HvsDHQuery(gastAtClientTab[ucIndex].usClientId, gastAtClientTab[ucIndex].opId))
    {
        /* ???????????????? */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_HVSDH_READ;
        return AT_WAIT_ASYNC_RETURN;    /* ???????????????????? */
    }

    AT_WARN_LOG("At_QryHvsDHPara: SI_PIH_HvsDHQuery fail.");

    return AT_ERROR;
}

/*****************************************************************************
 Prototype      : At_TestHvsDHPara
 Description    : ^HVSDH
 Input          : ucIndex --- ????????
 Output         :
 Return Value   : AT_XXX  --- ATC??????
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2013-03-20
    Author      : g47350
    Modification: Created function
*****************************************************************************/
VOS_UINT32 At_TestHvsDHPara(VOS_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: 1",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    return AT_OK;
}

/*****************************************************************************
 Prototype      : At_QryHvsContPara
 Description    : ^HVSDH
 Input          : ucIndex --- ????????
 Output         :
 Return Value   : AT_XXX  --- ATC??????
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2013-03-20
    Author      : g47350
    Modification: Created function
*****************************************************************************/
VOS_UINT32 At_QryHvsContPara(VOS_UINT8 ucIndex)
{
    if(AT_SUCCESS == SI_PIH_HvsContQuery(gastAtClientTab[ucIndex].usClientId, gastAtClientTab[ucIndex].opId))
    {
        /* ???????????????? */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_HVSCONT_READ;
        return AT_WAIT_ASYNC_RETURN;    /* ???????????????????? */
    }

    return AT_ERROR;
}

/*****************************************************************************
 ?? ?? ??  : At_DealRSFWVsim
 ????????  : (AT^RSFW)????vSIM ????
 ????????  : ucIndex - ????????
 ????????  : ??
 ?? ?? ??  :
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2013??03??18??
    ??    ??   : zhukai
    ????????   : vSIM??????????????
*****************************************************************************/
VOS_UINT32 At_DealRSFWVsim(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulLength = 0;
    SI_PIH_FILEWRITE_DATA_STRU          stFWriteStru;
    VOS_UINT8                           *pucRsfw;
    /* ?????? */
    PS_MEM_SET(&stFWriteStru,0x00,sizeof(stFWriteStru));

    /* index??????total?? */
    if(gastAtParaList[4].ulParaValue > gastAtParaList[3].ulParaValue)
    {
        AT_WARN_LOG("At_DealRSFWVsim: index is greater total.");
        return AT_CME_INVALID_INDEX;
    }

    /* data?????????????????? */
    if(gastAtParaList[5].usParaLen > AT_PARA_MAX_LEN)
    {
        AT_WARN_LOG1("At_DealRSFWVsim: param 5 is too long", gastAtParaList[5].usParaLen);
        return AT_CME_TEXT_STRING_TOO_LONG;
    }

    pucRsfw = (VOS_UINT8*)PS_MEM_ALLOC(WUEPS_PID_AT, gastAtParaList[5].usParaLen);/*??????????????????????*/

    if (VOS_NULL_PTR == pucRsfw )
    {
        AT_WARN_LOG("At_DealRSFWVsim: alloc memory failed.");
        return AT_CME_MEMORY_FAILURE;
    }

    PS_MEM_SET(pucRsfw, 0, gastAtParaList[5].usParaLen);

    ulRet = AtBase64Decode(gastAtParaList[5].aucPara,
                           gastAtParaList[5].usParaLen,
                           pucRsfw,
                           gastAtParaList[5].usParaLen,
                           &ulLength);

    if(b64Result_OK != ulRet)
    {
        PS_MEM_FREE(WUEPS_PID_AT, pucRsfw);

        AT_WARN_LOG("At_DealRSFWVsim: AtBase64Decode failed.");

        return AT_CME_INCORRECT_PARAMETERS;
    }

    stFWriteStru.stFileData.pucData     = pucRsfw;
    stFWriteStru.stFileData.ulDataLen   = ulLength;

    stFWriteStru.ulRef                  = gastAtParaList[2].ulParaValue;
    stFWriteStru.ulTotalNum             = gastAtParaList[3].ulParaValue;
    stFWriteStru.ulIndex                = gastAtParaList[4].ulParaValue;

    stFWriteStru.stFileName.pucData     = (VOS_UINT8*)"VSIM";
    stFWriteStru.stFileName.ulDataLen   = (VOS_UINT32)VOS_StrLen("VSIM");

    ulRet = SI_PIH_AtFileWrite(gastAtClientTab[ucIndex].usClientId, 0, &stFWriteStru);

    if(TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("At_DealRSFWVsim: SI_PIH_AtFileWrite Return Failed.");

        PS_MEM_FREE(WUEPS_PID_AT, pucRsfw);

        return AT_ERROR;
    }

    PS_MEM_FREE(WUEPS_PID_AT, pucRsfw);

    return AT_SUCCESS;
}

/*****************************************************************************
 ?? ?? ??  : At_SetHvpDHPara
 ????????  : AT^HVPDH????????????????
 ????????  : ucIndex
 ????????  : AT??????
 ?? ?? ??  :
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2013??8??27??
    ??    ??   : L47619
    ????????   : V9R1 vSIM????????

*****************************************************************************/
VOS_UINT32 At_SetHvpDHPara(VOS_UINT8 ucIndex)
{
    DRV_AGENT_HVPDH_REQ_STRU            stHvpdhReq;
    VOS_VOID                           *pOutputData;
    VOS_UINT32                          ulOutputLen;
    VOS_UINT32                          ulResult;

    /* ???????? */
    if(gucAtParaIndex > 2)
    {
        AT_WARN_LOG("At_SetHvpDHPara: Para too much.");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ??????????????????????????base16?????????????????????? */
    if ((0 == gastAtParaList[0].usParaLen)
        || (0 == gastAtParaList[1].usParaLen)
        || (1 == (gastAtParaList[1].usParaLen % 2)))
    {
        AT_WARN_LOG("At_SetHvpDHPara: Para Len Error.");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    pOutputData = PS_MEM_ALLOC(WUEPS_PID_AT, gastAtParaList[1].usParaLen);
    if (VOS_NULL_PTR == pOutputData)
    {
        AT_WARN_LOG("At_SetHvpDHPara: PS_MEM_ALLOC Error.");
        return AT_ERROR;
    }

    /* ?????????????? */
    ulOutputLen = At_Base16Decode((VOS_CHAR *)gastAtParaList[1].aucPara, gastAtParaList[1].usParaLen, pOutputData);

    /* ?????????????? */
    if ( (DRV_AGENT_DH_KEY_SERVER_PUBLIC_KEY == gastAtParaList[0].ulParaValue)
       ||(DRV_AGENT_DH_KEY_MODEM_PUBLIC_KEY == gastAtParaList[0].ulParaValue) )
    {
        if (VSIM_DH_PUBIIC_KEY < ulOutputLen)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pOutputData);

            AT_WARN_LOG("At_SetHvpDHPara: public key too Long.");

            return AT_CME_INCORRECT_PARAMETERS;
        }
    }
    else
    {
        if (VSIM_DH_PRIVATE_KEY < ulOutputLen)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pOutputData);

            AT_WARN_LOG("At_SetHvpDHPara: private key too Long.");

            return AT_CME_INCORRECT_PARAMETERS;
        }
    }

    stHvpdhReq.enKeyType = gastAtParaList[0].ulParaValue;
    stHvpdhReq.ulKeyLen  = ulOutputLen;
    PS_MEM_CPY(stHvpdhReq.aucKey, pOutputData, ulOutputLen);

    /* ?????????????????? */
    PS_MEM_FREE(WUEPS_PID_AT, pOutputData);

    /* ??????????????C??, ???????????? */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      DRV_AGENT_HVPDH_REQ,
                                      &stHvpdhReq,
                                      sizeof(stHvpdhReq),
                                      I0_WUEPS_PID_DRV_AGENT);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("At_SetHvpDHPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ????AT???????????????????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_HVPDH_SET;
    return AT_WAIT_ASYNC_RETURN;

}


/*****************************************************************************
 ?? ?? ??  : At_TestHvpDHPara
 ????????  : ^HVPDH????????
 ????????  : VOS_UINT8 ucIndex
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2013??8??27??
    ??    ??   : L47619
    ????????   : V9R1 vSIM????????
*****************************************************************************/
VOS_UINT32 At_TestHvpDHPara(VOS_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "^HVPDH: (0,2)");
    return AT_OK;
}

/*****************************************************************************
 Prototype      : At_HvsContQueryCnf
 Description    : HVSCONT????????
 Input          : pEvent --- ????????
 Output         :
 Return Value   : ??
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2013-03-18
    Author      : g47350
    Modification: Created function
*****************************************************************************/
VOS_UINT16 At_HvsContQueryCnf(SI_PIH_EVENT_INFO_STRU *pstEvent)

{
    VOS_UINT32                          i;
    VOS_UINT32                          j;
    VOS_UINT16                          usLength = 0;
    SI_PIH_CARD_CONTENT_STRU           *pstCardContent;

    pstCardContent = pstEvent->PIHEvent.HvsContCnf.astSimCard;

    for (i = 0; i < SI_PIH_CARD_BUTT; i++)
    {
        if (0 != i)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                        (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                        "%s^HVSCONT:", gaucAtCrLf);
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                        (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                        "^HVSCONT:");
        }

        /* (U)SIM?????????????? */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                    (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                    "%d,",
                                    pstCardContent[i].ucIndex);

        /* ?????????????????? */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                    (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                    "%d,",
                                    pstCardContent[i].ucCardCap);

        /* ???????????? */
        if (VOS_NULL == pstCardContent[i].ucCardType)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                    (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                    ",");
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                    (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                    "%d,",
                                    pstCardContent[i].ucCardType);
        }

        /* IMSI??????????????IMSI??????PLMN?????????? */
        if (0 == VOS_StrLen((VOS_CHAR*)pstCardContent[i].aucImsi))
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                    (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                    "\"\",\"\"");
            continue;
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                    (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                    "\"%s\"",
                                    pstCardContent[i].aucImsi);
        }

        /* HPLMN??EHPLMN */
        for (j = 0; j < pstCardContent[i].usPlmnNum; j++)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       ",\"%X%X%X",
                                       (0x0f & pstCardContent[i].astPlmn[j].ulMCC),
                                       (0x0f00 & pstCardContent[i].astPlmn[j].ulMCC) >> 8,
                                       (0x0f0000 & pstCardContent[i].astPlmn[j].ulMCC) >> 16);

            /* ????MNC?????????????????? */
            if ( 0x0F == ((0x0f0000 & pstCardContent[i].astPlmn[j].ulMNC) >> 16) )
            {
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                "%X%X\"",
                                                (0x0f & pstCardContent[i].astPlmn[j].ulMNC),
                                                (0x0f00 & pstCardContent[i].astPlmn[j].ulMNC) >> 8);
            }
            else
            {
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                "%X%X%X\"",
                                                (0x0f & pstCardContent[i].astPlmn[j].ulMNC),
                                                (0x0f00 & pstCardContent[i].astPlmn[j].ulMNC) >> 8,
                                                (0x0f0000 & pstCardContent[i].astPlmn[j].ulMNC) >> 16);
            }
        }
    }

    return usLength;
}


/*****************************************************************************
 Prototype      : AT_HvsDHQueryCnf
 Description    : HVSDH????????????
 Input          : pstEvent --- ????????
 Output         :
 Return Value   : ????????
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT16 AT_HvsDHQueryCnf(SI_PIH_EVENT_INFO_STRU *pstEvent)
{
    VOS_UINT16 usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"^HVSDH:");

    /* <algrithm>, */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%d,",pstEvent->PIHEvent.HvsDHCnf.enAlgorithm);

    /* <c_pkey>, */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"\"");
    usLength += (VOS_UINT16)At_Hex2Base16(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                pstEvent->PIHEvent.HvsDHCnf.stCkey.aucKey, (VOS_UINT16)pstEvent->PIHEvent.HvsDHCnf.stCkey.ulKeyLen);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"\",");

    /* <s_pkey>, */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"\"");
    if (0 != pstEvent->PIHEvent.HvsDHCnf.stSkey.ulKeyLen)
    {
        usLength += (VOS_UINT16)At_Hex2Base16(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                    pstEvent->PIHEvent.HvsDHCnf.stSkey.aucKey, (VOS_UINT16)pstEvent->PIHEvent.HvsDHCnf.stSkey.ulKeyLen);
    }
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"\"");
    return usLength;
}

/*****************************************************************************
 ?? ?? ??  : At_SetHvteePara
 ????????  : ^HVTEE????????
 ????????  : VOS_UINT8 ucIndex
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??  : 2014??10??9??
    ??    ??  : zhuli
    ????????  : ??????????????????????
*****************************************************************************/
VOS_UINT32 At_SetHvteePara(
    VOS_UINT8                               ucIndex
)
{
    VOS_UINT32                              ulResult;
    SI_PIH_HVTEE_SET_STRU                   stHvteeSet;

    /* ???????? */
    if (gucAtParaIndex > 3)
    {
        AT_WARN_LOG("At_SetHvteePara: Too Much Parameter.");
        return AT_ERROR;
    }

    /* ?????????? */
    if ( (0 == gastAtParaList[0].usParaLen)
       ||(0 == gastAtParaList[1].usParaLen)
       ||(0 == gastAtParaList[2].usParaLen))
    {
        AT_WARN_LOG("At_SetHvteePara: Parameter is not enough.");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    stHvteeSet.bAPNFlag         = gastAtParaList[0].ulParaValue;
    stHvteeSet.bDHParaFlag      = gastAtParaList[1].ulParaValue;
    stHvteeSet.bVSIMDataFlag    = gastAtParaList[2].ulParaValue;

    ulResult = SI_PIH_HvteeSet(gastAtClientTab[ucIndex].usClientId,
                              gastAtClientTab[ucIndex].opId,
                              &stHvteeSet);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("At_SetHvteePara: SI_PIH_HvSstSet fail.");
        return AT_CME_PHONE_FAILURE;
    }

    /* ????AT???????????????????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_HVSST_SET;

    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 ?? ?? ??  : At_TestHvteePara
 ????????  : ^HVTEE????????
 ????????  : VOS_UINT8 ucIndex
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??  : 2014??10??9??
    ??    ??  : zhuli
    ????????  : ??????????????????????
*****************************************************************************/
VOS_UINT32 At_TestHvteePara(
    VOS_UINT8                           ucIndex
)
{
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "^HVTEE: (0,1),(0,1),(0,1)");
    return AT_OK;
}

/*****************************************************************************
 ?? ?? ??  : At_QryHvCheckCardPara
 ????????  : ^HVCHECKCARD ????????
 ????????  : VOS_UINT8 ucIndex
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??  : 2014??10??9??
    ??    ??  : zhuli
    ????????  : ??????????????????????
*****************************************************************************/
VOS_UINT32 At_QryHvCheckCardPara(
    VOS_UINT8                           ucIndex
)
{
    if(AT_SUCCESS == SI_PIH_HvCheckCardQuery(gastAtClientTab[ucIndex].usClientId,
                                            gastAtClientTab[ucIndex].opId))
    {
        /* ???????????????? */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_HVSCONT_READ;

        return AT_WAIT_ASYNC_RETURN;    /* ???????????????????? */
    }

    return AT_ERROR;
}


/*****************************************************************************
 Prototype      : AT_UiccAuthCnf
 Description    : ????????
 Input          : pstEvent --- ????????
 Output         :
 Return Value   : ????????
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT16 AT_UiccAuthCnf(TAF_UINT8 ucIndex, SI_PIH_EVENT_INFO_STRU *pstEvent)
{
    VOS_UINT16 usLength = 0;

    if (AT_CMD_UICCAUTH_SET == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"^UICCAUTH:");

        /* <result> */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%d",pstEvent->PIHEvent.UiccAuthCnf.enStatus);

        if (SI_PIH_AUTH_SUCCESS == pstEvent->PIHEvent.UiccAuthCnf.enStatus)
        {
            /* ,<Res> */
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,",\"");
            usLength += (TAF_UINT16)At_HexAlpha2AsciiString(AT_CMD_MAX_LEN, (TAF_INT8 *)pgucAtSndCodeAddr, (TAF_UINT8 *)pgucAtSndCodeAddr+usLength, &pstEvent->PIHEvent.UiccAuthCnf.stAkaData.aucAuthRes[1], pstEvent->PIHEvent.UiccAuthCnf.stAkaData.aucAuthRes[0]);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"\"");

            if (SI_PIH_UICCAUTH_AKA == pstEvent->PIHEvent.UiccAuthCnf.enAuthType)
            {
                /* ,<ck> */
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,",\"");
                usLength += (TAF_UINT16)At_HexAlpha2AsciiString(AT_CMD_MAX_LEN, (TAF_INT8 *)pgucAtSndCodeAddr, (TAF_UINT8 *)pgucAtSndCodeAddr+usLength, &pstEvent->PIHEvent.UiccAuthCnf.stAkaData.aucCK[1], pstEvent->PIHEvent.UiccAuthCnf.stAkaData.aucCK[0]);
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"\"");

                /* ,<ik> */
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,",\"");
                usLength += (TAF_UINT16)At_HexAlpha2AsciiString(AT_CMD_MAX_LEN, (TAF_INT8 *)pgucAtSndCodeAddr, (TAF_UINT8 *)pgucAtSndCodeAddr+usLength, &pstEvent->PIHEvent.UiccAuthCnf.stAkaData.aucIK[1], pstEvent->PIHEvent.UiccAuthCnf.stAkaData.aucIK[0]);
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"\"");
            }
        }

        if (SI_PIH_AUTH_SYNC == pstEvent->PIHEvent.UiccAuthCnf.enStatus)
        {
            /* ,"","","",<autn> */
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,",\"\",\"\",\"\",\"");
            usLength += (TAF_UINT16)At_HexAlpha2AsciiString(AT_CMD_MAX_LEN, (TAF_INT8 *)pgucAtSndCodeAddr, (TAF_UINT8 *)pgucAtSndCodeAddr+usLength, &pstEvent->PIHEvent.UiccAuthCnf.stAkaData.aucAuts[1], pstEvent->PIHEvent.UiccAuthCnf.stAkaData.aucAuts[0]);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"\"");
        }
    }

    if (AT_CMD_KSNAFAUTH_SET == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"^KSNAFAUTH:");

        /* <status> */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%d",pstEvent->PIHEvent.UiccAuthCnf.enStatus);

        if (VOS_NULL != pstEvent->PIHEvent.UiccAuthCnf.stNAFData.aucKs_ext_NAF[0])
        {
            /* ,<ks_Naf> */
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,",\"");
            usLength += (TAF_UINT16)At_HexAlpha2AsciiString(AT_CMD_MAX_LEN, (TAF_INT8 *)pgucAtSndCodeAddr, (TAF_UINT8 *)pgucAtSndCodeAddr+usLength, &pstEvent->PIHEvent.UiccAuthCnf.stNAFData.aucKs_ext_NAF[1], pstEvent->PIHEvent.UiccAuthCnf.stNAFData.aucKs_ext_NAF[0]);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"\"");
        }
    }

    return usLength;
}

/*****************************************************************************
 Prototype      : AT_UiccAccessFileCnf
 Description    : ????????
 Input          : pstEvent --- ????????
 Output         :
 Return Value   : ????????
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT16 AT_UiccAccessFileCnf(TAF_UINT8 ucIndex, SI_PIH_EVENT_INFO_STRU *pstEvent)
{
    VOS_UINT16      usLength = 0;

    if ((0 != pstEvent->PIHEvent.UiccAcsFileCnf.ulDataLen)
        && (SI_PIH_ACCESS_READ == pstEvent->PIHEvent.UiccAcsFileCnf.enCmdType))
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"^CURSM:");

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"\"");
        usLength += (TAF_UINT16)At_HexAlpha2AsciiString(AT_CMD_MAX_LEN, (TAF_INT8 *)pgucAtSndCodeAddr, (TAF_UINT8 *)pgucAtSndCodeAddr+usLength, pstEvent->PIHEvent.UiccAcsFileCnf.aucCommand, (VOS_UINT16)pstEvent->PIHEvent.UiccAcsFileCnf.ulDataLen);
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"\"");
    }

    return usLength;
}


/*****************************************************************************
 ?? ?? ??  : At_SimHotPlugStatusInd
 ????????  : ^SIMHOTPLUG
 ????????  : TAF_UINT8 ucIndex ????????
 ????????  : ??
 ?? ?? ??  : TAF_UINT32        ATC??????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2016??6??3??
    ??    ??   : d00212987
    ????????   : ??????????
*****************************************************************************/
TAF_UINT16 At_SimHotPlugStatusInd(
    TAF_UINT8                           ucIndex,
    SI_PIH_EVENT_INFO_STRU             *pstEvent
)
{
    VOS_UINT16                          usLength = 0;

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s^SIMHOTPLUG: %d%s",
                                       gaucAtCrLf,
                                       pstEvent->PIHEvent.ulSimHotPlugStatus,
                                       gaucAtCrLf);
    return usLength;
}


