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
#include "AtCmdPacketProc.h"
#include "AtDataProc.h"

#include "product_config.h"


/*****************************************************************************
    ??????????????????????.C??????????
*****************************************************************************/
/*lint -e767 -e960*/
#define    THIS_FILE_ID                 PS_FILE_ID_AT_CMD_PACKET_PROC_C
/*lint +e767 +e960*/

/*****************************************************************************
  2 ????????????
*****************************************************************************/


/*****************************************************************************
  3 ????????
*****************************************************************************/

/* Modified by l60609 for V9R1 IPv6&TAF/SM Project, 2013-4-27, begin */
/*****************************************************************************
 ?? ?? ??  : AT_AppConvertPdpStateToConnStatus
 ????????  : ???????????? -> ????????
 ????????  : enPdpState      - ????????
 ????????  : ??
 ?? ?? ??  : AT_APP_DIALING  - ????????????
             AT_APP_DIALED   - ????????????
             AT_APP_UNDIALED - ????????????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2013??3??9??
    ??    ??   : A00165503
    ????????   : ??????????
*****************************************************************************/
AT_APP_CONN_STATE_ENUM_U32 AT_AppConvertPdpStateToConnStatus(
    AT_PDP_STATE_ENUM_U8                enPdpState
)
{
    AT_APP_CONN_STATE_ENUM_U32          enConnStatus;

    switch (enPdpState)
    {
        case AT_PDP_STATE_ACTING:
            enConnStatus = AT_APP_DIALING;
            break;

        case AT_PDP_STATE_ACTED:
        case AT_PDP_STATE_DEACTING:
            enConnStatus = AT_APP_DIALED;
            break;

        case AT_PDP_STATE_IDLE:
        default:
            enConnStatus = AT_APP_UNDIALED;
            break;
    }

    return enConnStatus;
}

/*****************************************************************************
 ?? ?? ??  : AT_SetChdataPara_AppUser
 ????????  : APP??????^CHDATA =<cid>,<datachannel>
 ????????  : VOS_UINT8 ucIndex
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2012??11??2??
    ??    ??   : l60609
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 AT_SetChdataPara_AppUser(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucCid;
    AT_CH_DATA_CHANNEL_ENUM_UINT32      enDataChannelId;
    RNIC_RMNET_ID_ENUM_UINT8            enRnicRmNetId;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    ucCid = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    /* ????CID??PDP????????????????????????????????CID????????????????????????ERROR */
    if ((VOS_TRUE == pstPsModemCtx->astChannelCfg[ucCid].ulUsed)
      && (VOS_TRUE == pstPsModemCtx->astChannelCfg[ucCid].ulRmNetActFlg))
    {
        return AT_ERROR;
    }

    /* ?????????????????????????????????? */
    if (0 == gastAtParaList[1].usParaLen)
    {
        pstPsModemCtx->astChannelCfg[ucCid].ulUsed     = VOS_FALSE;
        pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId  = AT_PS_INVALID_RMNET_ID;
        return AT_OK;
    }

    enDataChannelId = gastAtParaList[1].ulParaValue;

    /* ????????ID */
    ulRslt = AT_PS_GetRnicRmNetIdFromChDataValue(ucIndex, enDataChannelId, &enRnicRmNetId);

    if (VOS_OK != ulRslt)
    {
        return AT_ERROR;
    }

    /* ????????????????<CID>????????????<enRnicRmNetId> */
    for (ucLoop = 1; ucLoop <= TAF_MAX_CID; ucLoop++)
    {
        if ( (ucLoop != ucCid)
          && (VOS_TRUE == pstPsModemCtx->astChannelCfg[ucLoop].ulUsed)
          && (enRnicRmNetId == (RNIC_RMNET_ID_ENUM_UINT8)pstPsModemCtx->astChannelCfg[ucLoop].ulRmNetId))
        {
            /* ??????<CID>????????????<enRnicRmNetId>??????????ERROR */
            return AT_ERROR;
        }
    }

    /* ?????????????????? */
    pstPsModemCtx->astChannelCfg[ucCid].ulUsed     = VOS_TRUE;
    pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId  = enRnicRmNetId;

    return AT_OK;
}

/*****************************************************************************
 ?? ?? ??  : AT_SetChdataPara_HsicUser
 ????????  : HSIC??????????^CHDATA =<cid>,<datachannel>
 ????????  : VOS_UINT8 ucIndex
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2012??11??2??
    ??    ??   : l60609
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 AT_SetChdataPara_HsicUser(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucCid;
    AT_CH_DATA_CHANNEL_ENUM_UINT32      enDataChannelId;
    UDI_DEVICE_ID_E                     enUdiDevId;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    ucCid = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    /* ????CID??PDP????????????????????????????????CID????????????????????????ERROR */
    if ((VOS_TRUE == pstPsModemCtx->astChannelCfg[ucCid].ulUsed)
      && (VOS_TRUE == pstPsModemCtx->astChannelCfg[ucCid].ulRmNetActFlg))
    {
        return AT_ERROR;
    }

    /* ?????????????????????????????????? */
    if (0 == gastAtParaList[1].usParaLen)
    {
        pstPsModemCtx->astChannelCfg[ucCid].ulUsed     = VOS_FALSE;
        pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId  = UDI_INVAL_DEV_ID;
        return AT_OK;
    }

    enDataChannelId = gastAtParaList[1].ulParaValue;

    /* Modified by L47619 for C52 HSIC ACM->NCM Project, 2012/09/06, begin */
    /* ????????????????????????????PS_TRUE????SUPPORT */
    if (BSP_MODULE_SUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_HSIC_NCM))
    {
        if (AT_CH_DATA_CHANNEL_ID_1 == enDataChannelId)
        {
            enUdiDevId = UDI_NCM_HSIC_NCM0_ID;
        }
        else if(AT_CH_DATA_CHANNEL_ID_2 == enDataChannelId)
        {
            enUdiDevId = UDI_NCM_HSIC_NCM1_ID;
        }
        else
        {
            enUdiDevId = UDI_NCM_HSIC_NCM2_ID;
        }
    }
    else
    {
        if (AT_CH_DATA_CHANNEL_ID_1 == enDataChannelId)
        {
            enUdiDevId = UDI_ACM_HSIC_ACM1_ID;
        }
        else if(AT_CH_DATA_CHANNEL_ID_2 == enDataChannelId)
        {
            enUdiDevId = UDI_ACM_HSIC_ACM3_ID;
        }
        else
        {
            enUdiDevId = UDI_ACM_HSIC_ACM5_ID;
        }
    }
    /* Modified by L47619 for C52 HSIC ACM->NCM Project, 2012/09/06, end */

    /* ????????????????<CID>????????????<enUdiDevId> */
    for (ucLoop = 1; ucLoop <= TAF_MAX_CID; ucLoop++)
    {
        if ( (ucLoop != ucCid)
          && (VOS_TRUE == pstPsModemCtx->astChannelCfg[ucLoop].ulUsed)
          && (enUdiDevId == (UDI_DEVICE_ID_E)pstPsModemCtx->astChannelCfg[ucLoop].ulRmNetId))
        {
            /* ??????<CID>????????????<enUdiDevId>??????????ERROR */
            return AT_ERROR;
        }
    }

    /* ?????????????????? */
    pstPsModemCtx->astChannelCfg[ucCid].ulUsed     = VOS_TRUE;
    pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId  = enUdiDevId;

    return AT_OK;
}

/*****************************************************************************
 ?? ?? ??  : AT_SetChdataPara
 ????????  : ^CHDATA =<cid>,<datachannel>
 ????????  : TAF_UINT8 ucIndex
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2012??2??17??
    ??    ??   : L47619
    ????????   : ??????????

  2.??    ??   : 2012??9??10??
    ??    ??   : L60609
    ????????   : AP????????

  3.??    ??   : 2015??5??27??
    ??    ??   : l00198894
    ????????   : TSTS
*****************************************************************************/
VOS_UINT32 AT_SetChdataPara(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucUserIndex;

    /* ???????? */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ???????? */
    if (gucAtParaIndex > 2)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ?????????????? */
    if ((0 == gastAtParaList[0].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ucUserIndex = ucIndex;

    /* PCUI??????????PCUI??????NDISDUP???? */
    if (AT_USBCOM_USER == gastAtClientTab[ucIndex].UserType)
    {
        if (VOS_TRUE == AT_GetPcuiPsCallFlag())
        {
            ucUserIndex = AT_GetPcuiUsertId();
        }
    }

    /* CTRL??????????CTRL??????NDISDUP???? */
    if (AT_CTR_USER == gastAtClientTab[ucIndex].UserType)
    {
        if (VOS_TRUE == AT_GetCtrlPsCallFlag())
        {
            ucUserIndex = AT_GetCtrlUserId();
        }
    }

    /* PCUI2??????????PCUI2??????NDISDUP???? */
    if (AT_PCUI2_USER == gastAtClientTab[ucIndex].UserType)
    {
        if (VOS_TRUE == AT_GetPcui2PsCallFlag())
        {
            ucUserIndex = AT_GetPcui2UserId();
        }
    }

    /* HSIC??MUX?????????? */
    if (VOS_TRUE == AT_IsHsicOrMuxUser(ucUserIndex))
    {
        return AT_SetChdataPara_HsicUser(ucUserIndex);
    }

    /* APP?????????? */
    if (VOS_TRUE == AT_CheckAppUser(ucUserIndex))
    {
        return AT_SetChdataPara_AppUser(ucUserIndex);
    }

    return AT_ERROR;
}

/*****************************************************************************
 ?? ?? ??  : AT_QryChdataPara_AppUser
 ????????  : APP??????AT^CHDATA?
 ????????  : TAF_UINT8 ucIndex
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2012??11??2??
    ??    ??   : l60609
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 AT_QryChdataPara_AppUser(TAF_UINT8 ucIndex)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucNum;
    VOS_UINT16                          usLength;
    AT_CH_DATA_CHANNEL_ENUM_UINT32      enDataChannelId;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    ucNum    = 0;
    usLength = 0;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    /* ???????? */
    for (ucLoop = 1; ucLoop <= TAF_MAX_CID; ucLoop++)
    {
        if ( (VOS_TRUE == pstPsModemCtx->astChannelCfg[ucLoop].ulUsed)
          && (AT_PS_INVALID_RMNET_ID != pstPsModemCtx->astChannelCfg[ucLoop].ulRmNetId) )
        {
            if (0 != ucNum)
            {
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR*)pgucAtSndCodeAddr,(VOS_CHAR*)pgucAtSndCodeAddr + usLength,"%s",gaucAtCrLf);
            }

            /* ^CHDATA:  */
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR*)pgucAtSndCodeAddr,(VOS_CHAR*)pgucAtSndCodeAddr + usLength,"^CHDATA: ");

            /* <cid> */
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR*)pgucAtSndCodeAddr,(VOS_CHAR*)pgucAtSndCodeAddr + usLength,"%d", ucLoop);

            /* <datachannel> */
            ulRslt = AT_PS_GetChDataValueFromRnicRmNetId((RNIC_RMNET_ID_ENUM_UINT8)(pstPsModemCtx->astChannelCfg[ucLoop].ulRmNetId), &enDataChannelId);

            if (VOS_OK != ulRslt)
            {
                return AT_ERROR;
            }

            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR*)pgucAtSndCodeAddr,(VOS_CHAR*)pgucAtSndCodeAddr + usLength,",%d", enDataChannelId);

            ucNum++;
        }
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
 ?? ?? ??  : AT_QryChdataPara_HsicUser
 ????????  : HSIC??????AT^CHDATA?
 ????????  : TAF_UINT8 ucIndex
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2012??11??2??
    ??    ??   : l60609
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 AT_QryChdataPara_HsicUser(TAF_UINT8 ucIndex)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucNum;
    VOS_UINT16                          usLength;
    AT_CH_DATA_CHANNEL_ENUM_UINT32      enDataChannelId;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    ucNum    = 0;
    usLength = 0;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    /* ???????? */
    for (ucLoop = 1; ucLoop <= TAF_MAX_CID; ucLoop++)
    {
        if ( (VOS_TRUE == pstPsModemCtx->astChannelCfg[ucLoop].ulUsed)
          && (UDI_INVAL_DEV_ID != pstPsModemCtx->astChannelCfg[ucLoop].ulRmNetId) )
        {
            if (0 != ucNum)
            {
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR*)pgucAtSndCodeAddr,(VOS_CHAR*)pgucAtSndCodeAddr + usLength,"%s",gaucAtCrLf);
            }

            /* ^CHDATA:  */
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR*)pgucAtSndCodeAddr,(VOS_CHAR*)pgucAtSndCodeAddr + usLength,"^CHDATA: ");

            /* <cid> */
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR*)pgucAtSndCodeAddr,(VOS_CHAR*)pgucAtSndCodeAddr + usLength,"%d", ucLoop);

            /* <datachannel> */
            /* Modified by L47619 for C52 HSIC ACM->NCM Project, 2012/09/06, begin */
            switch ( pstPsModemCtx->astChannelCfg[ucLoop].ulRmNetId)
            {
                case UDI_ACM_HSIC_ACM1_ID:
                case UDI_NCM_HSIC_NCM0_ID:
                    enDataChannelId = AT_CH_DATA_CHANNEL_ID_1;
                    break;
                case UDI_ACM_HSIC_ACM3_ID:
                case UDI_NCM_HSIC_NCM1_ID:
                    enDataChannelId = AT_CH_DATA_CHANNEL_ID_2;
                    break;
                case UDI_ACM_HSIC_ACM5_ID:
                case UDI_NCM_HSIC_NCM2_ID:
                    enDataChannelId = AT_CH_DATA_CHANNEL_ID_3;
                    break;
                default:
                    return AT_ERROR;
            }
            /* Modified by L47619 for C52 HSIC ACM->NCM Project, 2012/09/06, end */
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR*)pgucAtSndCodeAddr,(VOS_CHAR*)pgucAtSndCodeAddr + usLength,",%d", enDataChannelId);

            ucNum++;
        }
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
 ?? ?? ??  : AT_QryChdataPara
 ????????  : AT^CHDATA?
 ????????  : ucIndex - ????????
 ????????  : ??
 ?? ?? ??  :
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2012??02??17??
    ??    ??   : L47619
    ????????   : ??????????

  2.??    ??   : 2012??9??10??
    ??    ??   : L60609
    ????????   : AP????????

  3.??    ??   : 2015??5??27??
    ??    ??   : l00198894
    ????????   : TSTS
*****************************************************************************/
VOS_UINT32 AT_QryChdataPara(TAF_UINT8 ucIndex)
{
    VOS_UINT8                           ucUserId;

    /*????????????????*/
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    ucUserId = ucIndex;

    /* PCUI??????????PCUI??????NDISDUP???? */
    if (AT_USBCOM_USER == gastAtClientTab[ucIndex].UserType)
    {
        if (VOS_TRUE == AT_GetPcuiPsCallFlag())
        {
            ucUserId = AT_GetPcuiUsertId();
        }
    }

    /* CTRL??????????CTRL??????NDISDUP???? */
    if (AT_CTR_USER == gastAtClientTab[ucIndex].UserType)
    {
        if (VOS_TRUE == AT_GetCtrlPsCallFlag())
        {
            ucUserId = AT_GetCtrlUserId();
        }
    }

    /* PCUI2??????????PCUI2??????NDISDUP???? */
    if (AT_PCUI2_USER == gastAtClientTab[ucIndex].UserType)
    {
        if (VOS_TRUE == AT_GetPcui2PsCallFlag())
        {
            ucUserId = AT_GetPcui2UserId();
        }
    }

    /* HSIC??MUX?????????? */
    if (VOS_TRUE == AT_IsHsicOrMuxUser(ucUserId))
    {
        return AT_QryChdataPara_HsicUser(ucUserId);
    }

    /* APP?????????? */
    if (VOS_TRUE == AT_CheckAppUser(ucUserId))
    {
        return AT_QryChdataPara_AppUser(ucUserId);
    }

    return AT_ERROR;
}

/*****************************************************************************
 ?? ?? ??  : AT_TestChdataPara
 ????????  : ^CHDATA????????
 ????????  : VOS_UINT8 ucIndex
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2012??03??20??
    ??    ??   : l00198894
    ????????   : ????????

  2.??    ??   : 2012??8??13??
    ??    ??   : l60609
    ????????   : MUX:????MUX??????????

  3.??    ??   : 2012??9??10??
    ??    ??   : l60609
    ????????   : AP??????????????CHDATA??????????
*****************************************************************************/
VOS_UINT32 AT_TestChdataPara(VOS_UINT8 ucIndex)
{
    /* Modified by l60609 for AP???????? ??2012-09-10 Begin */
    /* ???????? */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    {
        return AT_ERROR;
    }
    /* Modified by l60609 for AP???????? ??2012-09-10 End */

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: %s",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                       CHDATA_TEST_CMD_PARA_STRING);

    return AT_OK;
}

/*****************************************************************************
 ?? ?? ??  : AT_PS_ReportDhcp
 ????????  : ????IPv4??DHCP????
 ????????  : ucIndex --- ????????
 ????????  : ??
 ?? ?? ??  : AT_XXX  --- ATC??????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2012??12??10??
    ??    ??   : Y00213812
    ????????   : C50 IPv6 ????????????
*****************************************************************************/
VOS_UINT32 AT_PS_ReportDhcp(VOS_UINT8 ucIndex)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT16                          usLength;
    VOS_UINT32                          ulSpeed;
    VOS_UINT8                           ucCallId;
    AT_DHCP_PARA_STRU                   stDhcpConfig;

    usLength = 0;

    ucCallId = AT_PS_TransCidToCallId(ucIndex, (VOS_UINT8)gastAtParaList[0].ulParaValue);
    if (VOS_TRUE != AT_PS_IsCallIdValid(ucIndex, ucCallId))
    {
        AT_ERR_LOG("AT_PS_ReportDhcp:ERROR: CallId is invalid!");
        return AT_ERROR;
    }

    pstCallEntity = AT_PS_GetCallEntity(ucIndex, ucCallId);

    if (AT_PDP_STATE_ACTED != pstCallEntity->enIpv4State)
    {
        AT_WARN_LOG("AT_PS_ReportDhcp: PDP is not actived.");
        return AT_ERROR;
    }

    /* ????????????????*/
    if (VOS_ERR == AT_GetDisplayRate(ucIndex, &ulSpeed))
    {
        ulSpeed = AT_DEF_DISPLAY_SPEED;
        AT_WARN_LOG("AT_PS_ReportDhcp: ERROR : AT_GetDisplayRate Error!");
    }

    /* ????DHCP????(??????) */
    AT_GetDhcpPara(&stDhcpConfig, &pstCallEntity->stIpv4DhcpInfo);

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%s: ",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%08X,",stDhcpConfig.stDhcpCfg.ulIPAddr);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%08X,",stDhcpConfig.stDhcpCfg.ulSubNetMask);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%08X,",stDhcpConfig.stDhcpCfg.ulGateWay);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%08X,",stDhcpConfig.stDhcpCfg.ulGateWay);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%08X,",stDhcpConfig.stDhcpCfg.ulPrimDNS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%08X,",stDhcpConfig.stDhcpCfg.ulSndDNS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%d,",ulSpeed);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%d",ulSpeed);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
 Prototype      : At_SetDhcpPara
 Description    : ^DHCP????????
 Input          : ucIndex --- ????????
 Output         :
 Return Value   : AT_XXX  --- ATC??????
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2009-09-01
    Author      : L47619
    Modification: Created function

  2.??    ??   : 2011??10??24??
    ??    ??   : o00132663
    ????????   : AT????????????????????????????????
  3.??    ??   : 2012??03??03??
    ??    ??   : s62952
    ????????   : BalongV300R002 Build????????:????????????AP??????????????
  4.??    ??   : 2012??12??10??
    ??    ??   : Y00213812
    ????????   : C50 IPv6 Project??PDP????????????????????????ERROR??????????
                 CID????
*****************************************************************************/
VOS_UINT32 At_SetDhcpPara(VOS_UINT8 ucIndex)
{
    /* ???????? */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ???????? */
    if (gucAtParaIndex != 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ????????CID??????PDP?????? */
    return AT_PS_ReportDhcp(ucIndex);
}

/*****************************************************************************
 ?? ?? ??  : At_QryDhcpPara_AppUser
 ????????  : APP User????AT^DHCP?
 ????????  : VOS_UINT8 ucIndex
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2012??9??3??
    ??    ??   : l60609
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 At_QryDhcpPara_AppUser(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;
    VOS_UINT32                          ulSpeed;
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity = VOS_NULL_PTR;
    VOS_UINT32                          ulPdpActingFlg;
    VOS_UINT32                          ulPdpDeactingFlg;
    AT_DHCP_PARA_STRU                   stDhcpConfig;

    usLength         = 0;
    pstAppPdpEntity  = AT_APP_GetPdpEntInfoAddr();
    ulPdpActingFlg   = AT_AppCheckIpv4PdpState(AT_PDP_STATE_ACTING);
    ulPdpDeactingFlg = AT_AppCheckIpv4PdpState(AT_PDP_STATE_DEACTING);

    if ( (VOS_TRUE == ulPdpActingFlg)
      || (VOS_TRUE == ulPdpDeactingFlg)
      || ((AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv4State)
       && (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv4v6State)))
    {
        AT_WARN_LOG("At_QryDhcpPara_AppUser: PDP is not active for APP.");
        return AT_ERROR;
    }

    /* ????????????????*/
    if (VOS_ERR == AT_GetDisplayRate(ucIndex, &ulSpeed))
    {
        ulSpeed = AT_DEF_DISPLAY_SPEED;
        AT_WARN_LOG("At_QryDhcpPara_AppUser: ERROR : AT_GetDisplayRate Error!");
    }

    /* ????DHCP????(??????) */
    AT_GetDhcpPara(&stDhcpConfig, &pstAppPdpEntity->stIpv4Dhcp);

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%s: ",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%08X,",stDhcpConfig.stDhcpCfg.ulIPAddr);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%08X,",stDhcpConfig.stDhcpCfg.ulSubNetMask);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%08X,",stDhcpConfig.stDhcpCfg.ulGateWay);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%08X,",stDhcpConfig.stDhcpCfg.ulGateWay);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%08X,",stDhcpConfig.stDhcpCfg.ulPrimDNS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%08X,",stDhcpConfig.stDhcpCfg.ulSndDNS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%d,",ulSpeed);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%d",ulSpeed);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}

/*****************************************************************************
 ?? ?? ??  : At_QryDhcpPara_NdisUser
 ????????  : Ndis User????AT^DHCP?
 ????????  : VOS_UINT8 ucIndex
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2012??9??3??
    ??    ??   : l60609
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 At_QryDhcpPara_NdisUser(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;
    VOS_UINT32                          ulSpeed;
    VOS_UINT32                          ulPdpActingFlg;
    VOS_UINT32                          ulPdpDeactingFlg;
    AT_DHCP_PARA_STRU                   stDhcpConfig;

    /* Modified by S62952 for IPV6, 2011-04-19, begin */
    ulPdpActingFlg      = AT_NdisCheckIpv4PdpState(AT_PDP_STATE_ACTING);
    ulPdpDeactingFlg    = AT_NdisCheckIpv4PdpState(AT_PDP_STATE_DEACTING);
    usLength            = 0;

    if ( (VOS_TRUE == ulPdpActingFlg)
      || (VOS_TRUE == ulPdpDeactingFlg)
      || ((AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv4State)
       && (AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv4v6State)))
    {
        AT_WARN_LOG("At_QryDhcpPara_NdisUser AT_NdisGetState:");
        return AT_ERROR;
    }

    /* ????????????????*/
    if (VOS_ERR == AT_GetDisplayRate(ucIndex, &ulSpeed))
    {
        ulSpeed = AT_DEF_DISPLAY_SPEED;
        AT_ERR_LOG("At_QryDhcpPara_NdisUser : ERROR : AT_GetDisplayRate Error!");
    }

    /* ????DHCP????(??????) */
    AT_NdisGetDhcpPara(&stDhcpConfig);

    usLength =  (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr, "%s: ",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,"%X,",stDhcpConfig.stDhcpCfg.ulIPAddr);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,"%X,",stDhcpConfig.stDhcpCfg.ulSubNetMask);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,"%X,",stDhcpConfig.stDhcpCfg.ulGateWay);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,"%X,",stDhcpConfig.stDhcpCfg.ulGateWay);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,"%X,",stDhcpConfig.stDhcpCfg.ulPrimDNS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,"%X,",stDhcpConfig.stDhcpCfg.ulSndDNS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,"%d,",ulSpeed);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,"%d",ulSpeed);
    /* Modified by S62952 for IPV6, 2011-04-19, end */

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
 ?? ?? ??  : AT_PS_GetDailPortUsrType
 ????????  : ??????????????????????????(????PCUI??????????APPP/NDIS????)
 ????????  : enUsrType    --- ????????
 ????????  : ??
 ?? ?? ??  : AT_USER_TYPE --- ????????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2014??1??13??
    ??    ??   : A00165503
    ????????   : ??????????
*****************************************************************************/
AT_USER_TYPE AT_PS_GetDailPortUsrType(AT_USER_TYPE enUsrType)
{
    VOS_UINT8                          *pucSystemAppConfig = VOS_NULL_PTR;
    AT_USER_TYPE                        enExpUsrType;

    pucSystemAppConfig = AT_GetSystemAppConfigAddr();
    enExpUsrType       = enUsrType;

    if (AT_USBCOM_USER == enUsrType)
    {
        switch (*pucSystemAppConfig)
        {
            case SYSTEM_APP_MP:
                enExpUsrType = AT_NDIS_USER;
                break;

            case SYSTEM_APP_WEBUI:
                enExpUsrType = AT_APP_USER;
                break;

            default:
                break;
        }
    }

    return enExpUsrType;
}

/*****************************************************************************
 ?? ?? ??  : At_QryDhcpPara
 ????????  : <clip>,<netmask>,<gate>,<dhcp>,<pDNS>,<sDNS>,<max_rx_data>,<max_tx_data>
 ????????  : ucIndex --- ????????
 ????????  : ??
 ?? ?? ??  : AT_XXX  --- ATC??????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2010??1??23??
    ??    ??   : sunshaohua
    ????????   : ??????????

  2.??    ??   : 2014??1??13??
    ??    ??   : A00165503
    ????????   : DTS2013100906456: PCUI????????????APP/NDIS??DHCP????
*****************************************************************************/
VOS_UINT32 At_QryDhcpPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;
    AT_USER_TYPE                        enUsrType;

    ulResult  = AT_OK;

    enUsrType = AT_PS_GetDailPortUsrType(gastAtClientTab[ucIndex].UserType);

    switch (enUsrType)
    {
        case AT_NDIS_USER:
            ulResult = At_QryDhcpPara_NdisUser(ucIndex);
            break;

        case AT_APP_USER:
            ulResult = At_QryDhcpPara_AppUser(ucIndex);
            break;

        default:
            break;
    }

    return ulResult;
}

/*****************************************************************************
 ?? ?? ??  : AT_TestDhcpPara
 ????????  : ^DHCP????????
 ????????  : ucIndex
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2012??12??10??
    ??    ??   : Y00213812
    ????????   : C50 IPv6 ????????????

*****************************************************************************/
VOS_UINT32 AT_TestDhcpPara(VOS_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-11)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    return AT_OK;
}

/*****************************************************************************
 ?? ?? ??  : AT_PS_ReportDhcpv6
 ????????  : ????IPv6??DHCP????
 ????????  : ucIndex --- ????????
 ????????  : ??
 ?? ?? ??  : AT_XXX  --- ATC??????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2012??12??10??
    ??    ??   : Y00213812
    ????????   : C50 IPv6 ????????????

  2.??    ??   : 2014??12??8??
    ??    ??   : A00165503
    ????????   : DTS2014103102656: IPv6??????????, ^DHCPV6????????????ERROR
*****************************************************************************/
VOS_UINT32 AT_PS_ReportDhcpv6(TAF_UINT8 ucIndex)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT16                          usLength;
    VOS_UINT32                          ulSpeed;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           aucIpv6AddrStr[TAF_MAX_IPV6_ADDR_COLON_STR_LEN];
    VOS_UINT8                           aucInvalidIpv6Addr[TAF_IPV6_ADDR_LEN];

    usLength = 0;
    PS_MEM_SET(aucIpv6AddrStr, 0x00, (TAF_MAX_IPV6_ADDR_COLON_STR_LEN));
    PS_MEM_SET(aucInvalidIpv6Addr, 0x00, TAF_IPV6_ADDR_LEN);

    ucCallId = AT_PS_TransCidToCallId(ucIndex, (VOS_UINT8)gastAtParaList[0].ulParaValue);
    if (VOS_TRUE != AT_PS_IsCallIdValid(ucIndex, ucCallId))
    {
        AT_ERR_LOG("AT_PS_ReportDhcpv6:ERROR: CallId is invalid!");
        return AT_ERROR;
    }

    pstCallEntity = AT_PS_GetCallEntity(ucIndex, ucCallId);

    if (AT_PDP_STATE_ACTED != pstCallEntity->enIpv6State)
    {
        AT_WARN_LOG("AT_PS_ReportDhcpv6: PDP is not actived.");
        return AT_ERROR;
    }

    if (VOS_TRUE != pstCallEntity->stIpv6RaInfo.bitOpPrefixAddr)
    {
        AT_WARN_LOG("AT_PS_ReportDhcpv6: Prefix address is not received.");
        return AT_ERROR;
    }

    /* ????????????????*/
    if (VOS_ERR == AT_GetDisplayRate(ucIndex, &ulSpeed))
    {
        ulSpeed = AT_DEF_DISPLAY_SPEED;
        AT_WARN_LOG("AT_PS_ReportDhcpv6: ERROR : AT_GetDisplayRate Error!");
    }

    usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr, "%s: ",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    /* ????IPV6???? */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      pstCallEntity->stIpv6DhcpInfo.aucIpv6Addr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, "%s", aucIpv6AddrStr);

    /* ????IPV6????, ??????????0 */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      aucInvalidIpv6Addr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    /* ????IPV6????, ??????????0 */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      aucInvalidIpv6Addr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    /* ????DHCP IPV6, ??????????0 */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      aucInvalidIpv6Addr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    /* ????IPV6 Primary DNS */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      pstCallEntity->stIpv6DhcpInfo.aucIpv6PrimDNS,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    /* ????IPV6 Secondary DNS */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      pstCallEntity->stIpv6DhcpInfo.aucIpv6SecDNS,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    /* ????MAX TX/RX Rate */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%d", ulSpeed);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%d", ulSpeed);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
 ?? ?? ??  : AT_SetDhcpv6Para
 ????????  : ????CID??????IPv6????PDP??????
 ????????  : VOS_UINT8 ucIndex
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2012??12??10??
    ??    ??   : Y00213812
    ????????   : C50 IPv6 ????????????

*****************************************************************************/
VOS_UINT32 AT_SetDhcpv6Para(VOS_UINT8 ucIndex)
{
    /* ???????? */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ???????? */
    if (gucAtParaIndex != 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ????????CID??????PDP?????? */
    return AT_PS_ReportDhcpv6(ucIndex);
}
/*****************************************************************************
 ?? ?? ??  : AT_QryDhcpV6Para_AppUser
 ????????  : APP User????AT^DHCPV6?
 ????????  : VOS_UINT8 ucIndex
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2012??9??3??
    ??    ??   : l60609
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 AT_QryDhcpV6Para_AppUser(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;
    VOS_UINT8                           aucIpv6AddrStr[TAF_MAX_IPV6_ADDR_COLON_STR_LEN];
    VOS_UINT8                           aucInvalidIpv6Addr[TAF_IPV6_ADDR_LEN];
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity = VOS_NULL_PTR;
    VOS_UINT32                          ulPdpActingFlg;
    VOS_UINT32                          ulPdpDeactingFlg;
    VOS_UINT32                          ulSpeed;

    usLength                            = 0;

    PS_MEM_SET(aucInvalidIpv6Addr, 0x00, sizeof(aucInvalidIpv6Addr));

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();

    ulPdpActingFlg   = AT_AppCheckIpv6PdpState(AT_PDP_STATE_ACTING);
    ulPdpDeactingFlg = AT_AppCheckIpv6PdpState(AT_PDP_STATE_DEACTING);

    if ( (VOS_TRUE == ulPdpActingFlg)
      || (VOS_TRUE == ulPdpDeactingFlg)
      || ((AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv6State)
       && (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv4v6State)))
    {
        AT_ERR_LOG("AT_QryDhcpV6Para_AppUser:ERROR: PDP is not active for APP.");
        return AT_ERROR;
    }

    /* ????????????????*/
    if (VOS_ERR == AT_GetDisplayRate(ucIndex, &ulSpeed))
    {
        ulSpeed = AT_DEF_DISPLAY_SPEED;
        AT_WARN_LOG("AT_QryDhcpV6Para_AppUser:WARNING: AT_GetDisplayRate Error!");
    }

    usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr, "%s: ",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    /* ????IPV6???? */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      pstAppPdpEntity->stIpv6Dhcp.aucIpv6Addr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, "%s", aucIpv6AddrStr);

    /* ????IPV6????, ??????????0 */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      aucInvalidIpv6Addr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    /* ????IPV6????, ??????????0 */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      aucInvalidIpv6Addr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    /* ????DHCP IPV6, ??????????0 */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      aucInvalidIpv6Addr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    /* ????IPV6 Primary DNS */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      pstAppPdpEntity->stIpv6Dhcp.aucIpv6PrimDNS,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    /* ????IPV6 Secondary DNS */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      pstAppPdpEntity->stIpv6Dhcp.aucIpv6SecDNS,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    /* ????MAX TX/RX Rate */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength, ",%d", ulSpeed);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength, ",%d", ulSpeed);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
 ?? ?? ??  : AT_QryDhcpV6Para_NdisUser
 ????????  : NDIS User????AT^DHCPV6?
 ????????  : VOS_UINT8 ucIndex
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2012??9??3??
    ??    ??   : l60609
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 AT_QryDhcpV6Para_NdisUser(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;
    VOS_UINT8                           aucIpv6AddrStr[TAF_MAX_IPV6_ADDR_COLON_STR_LEN];
    VOS_UINT8                           aucInvalidIpv6Addr[TAF_IPV6_ADDR_LEN];
    VOS_UINT32                          ulPdpActingFlg;
    VOS_UINT32                          ulPdpDeactingFlg;
    VOS_UINT32                          ulSpeed;

    usLength                            = 0;

    PS_MEM_SET(aucInvalidIpv6Addr, 0x00, sizeof(aucInvalidIpv6Addr));

    ulPdpActingFlg   = AT_NdisCheckIpv6PdpState(AT_PDP_STATE_ACTING);
    ulPdpDeactingFlg = AT_NdisCheckIpv6PdpState(AT_PDP_STATE_DEACTING);

    if ((VOS_TRUE == ulPdpActingFlg)
     || (VOS_TRUE == ulPdpDeactingFlg)
     || ((AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv6State)
      && (AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv4v6State)))
    {
        AT_WARN_LOG("AT_QryDhcpV6Para_NdisUser AT_NdisGetState:");
        return AT_ERROR;
    }

    /* ????????????????*/
    if (VOS_ERR == AT_GetDisplayRate(ucIndex, &ulSpeed))
    {
        ulSpeed = AT_DEF_DISPLAY_SPEED;
        AT_ERR_LOG("AT_QryDhcpV6Para_NdisUser : ERROR : AT_GetDisplayRate Error!");
    }

    usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr, "%s: ",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    /* ????IPV6???? */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      g_stAtNdisDhcpPara.stIpv6Dhcp.aucIpv6Addr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, "%s", aucIpv6AddrStr);

    /* ????IPV6????, ??????????0 */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      aucInvalidIpv6Addr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    /* ????IPV6????, ??????????0 */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      aucInvalidIpv6Addr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    /* ????DHCP IPV6, ??????????0 */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      aucInvalidIpv6Addr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    /* ????IPV6 Primary DNS */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      g_stAtNdisDhcpPara.stIpv6Dhcp.aucIpv6PrimDNS,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s",  aucIpv6AddrStr);

    /* ????IPV6 Secondary DNS */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      g_stAtNdisDhcpPara.stIpv6Dhcp.aucIpv6SecDNS,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s",  aucIpv6AddrStr);

    /* ????MAX TX/RX Rate */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength, ",%d", ulSpeed);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength, ",%d", ulSpeed);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
 ?? ?? ??  : AT_QryDhcpv6Para
 ????????  :
 ????????  : ucIndex - ????????
 ????????  : ??
 ?? ?? ??  : AT_XXX  - ATC??????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??7??21??
    ??    ??   : A00165503
    ????????   : ??????????

  2.??    ??   : 2014??1??13??
    ??    ??   : A00165503
    ????????   : DTS2013100906456: PCUI????????????APP/NDIS??DHCP????
*****************************************************************************/
VOS_UINT32 AT_QryDhcpv6Para(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;
    AT_USER_TYPE                        enUsrType;

    ulResult  = AT_OK;

    enUsrType = AT_PS_GetDailPortUsrType(gastAtClientTab[ucIndex].UserType);

    switch (enUsrType)
    {
        case AT_NDIS_USER:
            ulResult = AT_QryDhcpV6Para_NdisUser(ucIndex);
            break;

        case AT_APP_USER:
            ulResult = AT_QryDhcpV6Para_AppUser(ucIndex);
            break;

        default:
            break;
    }

    return ulResult;
}

/*****************************************************************************
 ?? ?? ??  : AT_TestDhcpv6Para
 ????????  : ^DHCPV6????????
 ????????  : ucIndex
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2012??12??10??
    ??    ??   : Y00213812
    ????????   : C50 IPv6 ????????????

*****************************************************************************/
VOS_UINT32 AT_TestDhcpv6Para(VOS_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-11)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    return AT_OK;
}
/*****************************************************************************
 ?? ?? ??  : AT_PS_ReportApraInfo
 ????????  : ????IPv6??RA????
 ????????  : TAF_UINT8 ucIndex
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2013??4??27??
    ??    ??   : l60609
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 AT_PS_ReportApraInfo(TAF_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;
    VOS_UINT8                           aucIpv6AddrStr[TAF_MAX_IPV6_ADDR_COLON_STR_LEN];
    VOS_UINT8                           aucInvalidIpv6Addr[TAF_IPV6_ADDR_LEN];
    VOS_UINT32                          ulMtuSize;
    VOS_UINT32                          ulPrefixBitLen;
    VOS_UINT32                          ulPreferredLifetime;
    VOS_UINT32                          ulValidLifetime;
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT8                           ucCallId;

    usLength                            = 0;
    PS_MEM_SET(aucInvalidIpv6Addr, 0x00, sizeof(aucInvalidIpv6Addr));
    PS_MEM_SET(aucIpv6AddrStr, 0x00, (TAF_MAX_IPV6_ADDR_COLON_STR_LEN));

    ucCallId = AT_PS_TransCidToCallId(ucIndex, (VOS_UINT8)gastAtParaList[0].ulParaValue);
    if (VOS_TRUE != AT_PS_IsCallIdValid(ucIndex, ucCallId))
    {
        AT_ERR_LOG("AT_PS_ReportApraInfo:ERROR: CallId is invalid!");
        return AT_ERROR;
    }

    pstCallEntity = AT_PS_GetCallEntity(ucIndex, ucCallId);

    if (AT_PDP_STATE_ACTED != pstCallEntity->enIpv6State)
    {
        AT_WARN_LOG("AT_PS_ReportApraInfo: PDP is not actived.");
        return AT_ERROR;
    }

    usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr,
                                       "%s: ",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    /* ????MTU */
    if (VOS_FALSE == pstCallEntity->stIpv6RaInfo.bitOpMtuSize)
    {
        ulMtuSize = 0;
    }
    else
    {
        ulMtuSize = pstCallEntity->stIpv6RaInfo.ulMtuSize;
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                       "%d",
                                       ulMtuSize);
    /* ????Prefix */
    if (VOS_FALSE == pstCallEntity->stIpv6RaInfo.bitOpPrefixAddr)
    {
        ulPrefixBitLen = 0;
        AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                          aucInvalidIpv6Addr,
                                          TAF_IPV6_STR_RFC2373_TOKENS);
    }
    else
    {
        ulPrefixBitLen = pstCallEntity->stIpv6RaInfo.ulPrefixBitLen;
        AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                          pstCallEntity->stIpv6RaInfo.aucPrefixAddr,
                                          TAF_IPV6_STR_RFC2373_TOKENS);
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                       ",\"%s/%d\"",
                                       aucIpv6AddrStr,
                                       ulPrefixBitLen);

    /* ????Preferred Lifetime */
    if (VOS_FALSE == pstCallEntity->stIpv6RaInfo.bitOpPreferredLifetime)
    {
        ulPreferredLifetime = 0;
    }
    else
    {
        ulPreferredLifetime = pstCallEntity->stIpv6RaInfo.ulPreferredLifetime;
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                       ",%u",
                                       ulPreferredLifetime);

    if (VOS_FALSE == pstCallEntity->stIpv6RaInfo.bitOpValidLifetime)
    {
        ulValidLifetime = 0;
    }
    else
    {
        ulValidLifetime = pstCallEntity->stIpv6RaInfo.ulValidLifetime;
    }

    /* ????Valid Lifetime */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                       ",%u",
                                       ulValidLifetime);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
 ?? ?? ??  : AT_SetApRaInfoPara
 ????????  : ????CID??????IPv6 RA????????????????????, ????MTU, ????,??????preferred lifetime??Valid lifetime
 ????????  : VOS_UINT8 ucIndex
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2013??4??25??
    ??    ??   : l60609
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 AT_SetApRaInfoPara(VOS_UINT8 ucIndex)
{
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ???????? */
    if (gucAtParaIndex != 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ????????CID??????PDP?????? */
    return AT_PS_ReportApraInfo(ucIndex);
}

/*****************************************************************************
 ?? ?? ??  : AT_QryApRaInfoPara
 ????????  : ????IPv6 RA????????????????????, ????MTU, ????,
             ??????preferred lifetime??Valid lifetime
 ????????  : ucIndex - ????????
 ????????  : ??
 ?? ?? ??  : AT_XXX  - ATC??????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??7??25??
    ??    ??   : A00165503
    ????????   : ??????????

  2.??    ??   : 2012??5??11??
    ??    ??   : l60609
    ????????   : DTS2012051101376??lifetime??????????%u
*****************************************************************************/
VOS_UINT32 AT_QryApRaInfoPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;
    VOS_UINT8                           aucIpv6AddrStr[TAF_MAX_IPV6_ADDR_COLON_STR_LEN];
    VOS_UINT8                           aucInvalidIpv6Addr[TAF_IPV6_ADDR_LEN];
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;
    AT_IPV6_RA_INFO_STRU               *pstAppRaInfoAddr;
    VOS_UINT32                          ulPdpActingFlg;
    VOS_UINT32                          ulPdpDeactingFlg;
    VOS_UINT32                          ulMtuSize;
    VOS_UINT32                          ulPrefixBitLen;
    VOS_UINT32                          ulPreferredLifetime;
    VOS_UINT32                          ulValidLifetime;

    usLength                            = 0;

    PS_MEM_SET(aucInvalidIpv6Addr, 0x00, sizeof(aucInvalidIpv6Addr));

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();
    pstAppRaInfoAddr                    = AT_APP_GetRaInfoAddr();

    ulPdpActingFlg   = AT_AppCheckIpv6PdpState(AT_PDP_STATE_ACTING);
    ulPdpDeactingFlg = AT_AppCheckIpv6PdpState(AT_PDP_STATE_DEACTING);

    if ( (VOS_TRUE == ulPdpActingFlg)
      || (VOS_TRUE == ulPdpDeactingFlg)
      || ( (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv6State)
        && (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv4v6State) ) )
    {
        AT_ERR_LOG("AT_QryApRaInfoPara:ERROR: PDP is not active for APP.");
        return AT_ERROR;
    }

    usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr,
                                       "%s: ",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    /* ????MTU */
    if (VOS_FALSE == pstAppRaInfoAddr->bitOpMtuSize)
    {
        ulMtuSize = 0;
    }
    else
    {
        ulMtuSize = pstAppRaInfoAddr->ulMtuSize;
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                       "%d",
                                       ulMtuSize);
    /* ????Prefix */
    if (VOS_FALSE == pstAppRaInfoAddr->bitOpPrefixAddr)
    {
        ulPrefixBitLen = 0;
        AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                          aucInvalidIpv6Addr,
                                          TAF_IPV6_STR_RFC2373_TOKENS);
    }
    else
    {
        ulPrefixBitLen = pstAppRaInfoAddr->ulPrefixBitLen;
        AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                          pstAppRaInfoAddr->aucPrefixAddr,
                                          (VOS_UINT8)ulPrefixBitLen/16);
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                       ",\"%s/%d\"",
                                       aucIpv6AddrStr,
                                       ulPrefixBitLen);

    /* ????Preferred Lifetime */
    if (VOS_FALSE == pstAppRaInfoAddr->bitOpPreferredLifetime)
    {
        ulPreferredLifetime = 0;
    }
    else
    {
        ulPreferredLifetime = pstAppRaInfoAddr->ulPreferredLifetime;
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                       ",%u",
                                       ulPreferredLifetime);

    if (VOS_FALSE == pstAppRaInfoAddr->bitOpValidLifetime)
    {
        ulValidLifetime = 0;
    }
    else
    {
        ulValidLifetime = pstAppRaInfoAddr->ulValidLifetime;
    }

    /* ????Valid Lifetime */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                       ",%u",
                                       ulValidLifetime);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
 ?? ?? ??  : AT_TestApRaInfoPara
 ????????  : ^APRAINFO????????
 ????????  : VOS_UINT8 ucIndex
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2013??4??27??
    ??    ??   : l60609
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 AT_TestApRaInfoPara(VOS_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-11)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    return AT_OK;
}


/*****************************************************************************
 ?? ?? ??  : AT_PS_ReportLanAddr
 ????????  : IPv6 ??????LAN????????????
 ????????  : VOS_UINT8 ucIndex
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2013??4??27??
    ??    ??   : l60609
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 AT_PS_ReportLanAddr(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucCallId;
    AT_PS_CALL_ENTITY_STRU             *pstPsCallEntity = VOS_NULL_PTR;
    AT_IPV6_RA_INFO_STRU               *pstIpv6RaInfo;
    VOS_UINT16                          usLength;
    VOS_UINT8                           aucIpv6AddrStr[TAF_MAX_IPV6_ADDR_COLON_STR_LEN];
    VOS_UINT8                           aucInvalidIpv6Addr[TAF_IPV6_ADDR_LEN];

    usLength = 0;
    PS_MEM_SET(aucInvalidIpv6Addr, 0x00, sizeof(aucInvalidIpv6Addr));

    /* ????cid??????????callid */
    ucCallId = AT_PS_TransCidToCallId(ucIndex, (VOS_UINT8)gastAtParaList[0].ulParaValue);

    if (VOS_TRUE != AT_PS_IsCallIdValid(ucIndex, ucCallId))
    {
        AT_ERR_LOG("AT_PS_ReportLanAddr:ERROR: CallId is invalid!");
        return AT_ERROR;
    }

    pstPsCallEntity = AT_PS_GetCallEntity(ucIndex, ucCallId);

    /* ????????????????????error */
    if (AT_PDP_STATE_ACTED != pstPsCallEntity->enIpv6State)
    {
        return AT_ERROR;
    }

    pstIpv6RaInfo = &(pstPsCallEntity->stIpv6RaInfo);

    usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr,
                                       "%s: ",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    if (VOS_FALSE == pstIpv6RaInfo->bitOpLanAddr)
    {
        AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                          aucInvalidIpv6Addr,
                                          TAF_IPV6_STR_RFC2373_TOKENS);
    }
    else
    {
        AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                          pstIpv6RaInfo->aucLanAddr,
                                          TAF_IPV6_STR_RFC2373_TOKENS);
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                       "\"%s\"",
                                       aucIpv6AddrStr);

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                       ",%d",
                                       pstIpv6RaInfo->ulPrefixBitLen);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
 ?? ?? ??  : AT_SetApLanAddrPara
 ????????  : ????CID??????IPv6 ??????LAN????????????
 ????????  : VOS_UINT8 ucIndex
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2013??4??25??
    ??    ??   : l60609
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 AT_SetApLanAddrPara(VOS_UINT8 ucIndex)
{
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ???????? */
    if (gucAtParaIndex != 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ????????CID??????PDP?????? */
    return AT_PS_ReportLanAddr(ucIndex);
}

/*****************************************************************************
 ?? ?? ??  : AT_QryApLanAddrPara
 ????????  : ????IPv6 ??????LAN????????????
 ????????  : ucIndex - ????????
 ????????  : ??
 ?? ?? ??  : AT_XXX  - ATC??????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??7??25??
    ??    ??   : A00165503
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 AT_QryApLanAddrPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;
    VOS_UINT8                           aucIpv6AddrStr[TAF_MAX_IPV6_ADDR_COLON_STR_LEN];
    VOS_UINT8                           aucInvalidIpv6Addr[TAF_IPV6_ADDR_LEN];
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;
    AT_IPV6_RA_INFO_STRU               *pstAppRaInfoAddr;
    VOS_UINT32                          ulPdpActingFlg;
    VOS_UINT32                          ulPdpDeactingFlg;

    usLength                            = 0;
    PS_MEM_SET(aucInvalidIpv6Addr, 0x00, sizeof(aucInvalidIpv6Addr));

    if (AT_APP_USER == gastAtClientTab[ucIndex].UserType)
    {

        pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();
        pstAppRaInfoAddr                    = AT_APP_GetRaInfoAddr();

        ulPdpActingFlg   = AT_AppCheckIpv6PdpState(AT_PDP_STATE_ACTING);
        ulPdpDeactingFlg = AT_AppCheckIpv6PdpState(AT_PDP_STATE_DEACTING);

        if ( (VOS_TRUE == ulPdpActingFlg)
          || (VOS_TRUE == ulPdpDeactingFlg)
          || ( (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv6State)
            && (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv4v6State) ) )
        {
            AT_ERR_LOG("AT_QryApLanAddrPara:ERROR: PDP is not active for APP.");
            return AT_ERROR;
        }

        usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr,
                                           "%s: ",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

        if (VOS_FALSE == pstAppRaInfoAddr->bitOpLanAddr)
        {
            AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                              aucInvalidIpv6Addr,
                                              TAF_IPV6_STR_RFC2373_TOKENS);
        }
        else
        {
            AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                              pstAppRaInfoAddr->aucLanAddr,
                                              TAF_IPV6_STR_RFC2373_TOKENS);
        }

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                           "\"%s\"",
                                           aucIpv6AddrStr);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                           ",%d",
                                           pstAppRaInfoAddr->ulPrefixBitLen);
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
 ?? ?? ??  : AT_TestApLanAddrPara
 ????????  : ^APLANADDR????????
 ????????  : VOS_UINT8 ucIndex
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2013??4??27??
    ??    ??   : l60609
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 AT_TestApLanAddrPara(VOS_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-11)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    return AT_OK;
}


/*****************************************************************************
 ?? ?? ??  : AT_PS_ReportConnSt
 ????????  : ????????????
 ????????  : VOS_UINT8 ucIndex
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2013??4??27??
    ??    ??   : l60609
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 AT_PS_ReportConnSt(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucCallId;
    AT_PS_CALL_ENTITY_STRU             *pstPsCallEntity = VOS_NULL_PTR;
    AT_APP_CONN_STATE_ENUM_U32          enIpv4ConnStatus;
    AT_APP_CONN_STATE_ENUM_U32          enIpv6ConnStatus;
    VOS_UINT16                          usLength;

    usLength = 0;

    /* ????cid??????????callid */
    ucCallId = AT_PS_TransCidToCallId(ucIndex, (VOS_UINT8)gastAtParaList[0].ulParaValue);

    if (VOS_TRUE != AT_PS_IsCallIdValid(ucIndex, ucCallId))
    {
        AT_ERR_LOG("AT_PS_ReportConnSt:ERROR: CallId is invalid!");
        return AT_ERROR;
    }

    pstPsCallEntity = AT_PS_GetCallEntity(ucIndex, ucCallId);

    switch (AT_GetIpv6Capability())
    {
        case AT_IPV6_CAPABILITY_IPV4_ONLY:
            enIpv4ConnStatus = AT_AppConvertPdpStateToConnStatus(pstPsCallEntity->enIpv4State);

            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               "%s: ",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%d,\"IPV4\"",
                                               enIpv4ConnStatus);
            break;

        case AT_IPV6_CAPABILITY_IPV6_ONLY:
            enIpv6ConnStatus = AT_AppConvertPdpStateToConnStatus(pstPsCallEntity->enIpv6State);

            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               "%s: ",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%d,\"IPV6\"",
                                               enIpv6ConnStatus);
            break;

        case AT_IPV6_CAPABILITY_IPV4V6_OVER_ONE_PDP:
        case AT_IPV6_CAPABILITY_IPV4V6_OVER_TWO_PDP:
            enIpv4ConnStatus = AT_AppConvertPdpStateToConnStatus(pstPsCallEntity->enIpv4State);
            enIpv6ConnStatus = AT_AppConvertPdpStateToConnStatus(pstPsCallEntity->enIpv6State);

            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               "%s: ",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%d,\"IPV4\"",
                                               enIpv4ConnStatus);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               ",%d,\"IPV6\"",
                                               enIpv6ConnStatus);
            break;

        default:
            break;
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
 ?? ?? ??  : At_SetApConnStPara
 ????????  : ????cid??????APP????????
 ????????  : VOS_UINT8                           ucIndex
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2013??4??25??
    ??    ??   : l60609
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32  At_SetApConnStPara(
    VOS_UINT8                           ucIndex
)
{
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ???????? */
    if (gucAtParaIndex != 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ????????CID??????PDP?????? */
    return AT_PS_ReportConnSt(ucIndex);
}

/*****************************************************************************
 ?? ?? ??  : At_QryApConnStPara
 ????????  : ????APP????????
 ????????  : TAF_UINT8 ucIndex
 ????????  : ??
 ?? ?? ??  : ????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2010??9??9??
    ??    ??   : s62952
    ????????   : ??????????

  2.??    ??   : 2015??11??4??
    ??    ??   : W00316404
    ????????   : ??????PDP TYPE????????DTS2015110302814??

*****************************************************************************/
VOS_UINT32  At_QryApConnStPara(
    VOS_UINT8                           ucIndex
)
{
    AT_APP_CONN_STATE_ENUM_U32         enIpv4ConnStatus;
    AT_APP_CONN_STATE_ENUM_U32         enIpv6ConnStatus;
    AT_APP_CONN_STATE_ENUM_U32         enIpv4v6ConnStatus;
    VOS_UINT16                         usLength = 0;

    switch (AT_GetIpv6Capability())
    {
        case AT_IPV6_CAPABILITY_IPV4_ONLY:
            enIpv4ConnStatus = AT_AppConvertPdpStateToConnStatus(AT_AppGetPdpState(TAF_PDP_IPV4));

            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               "%s: ",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%d,\"IPV4\"",
                                               enIpv4ConnStatus);
            break;

        case AT_IPV6_CAPABILITY_IPV6_ONLY:
            enIpv6ConnStatus = AT_AppConvertPdpStateToConnStatus(AT_AppGetPdpState(TAF_PDP_IPV6));

            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               "%s: ",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%d,\"IPV6\"",
                                               enIpv6ConnStatus);
            break;

        case AT_IPV6_CAPABILITY_IPV4V6_OVER_ONE_PDP:
            enIpv4v6ConnStatus  = AT_AppConvertPdpStateToConnStatus(AT_AppGetPdpState(TAF_PDP_IPV4V6));

            if (AT_APP_UNDIALED == enIpv4v6ConnStatus)
            {
                enIpv4ConnStatus = AT_AppConvertPdpStateToConnStatus(AT_AppGetPdpState(TAF_PDP_IPV4));
                enIpv6ConnStatus = AT_AppConvertPdpStateToConnStatus(AT_AppGetPdpState(TAF_PDP_IPV6));
            }
            else
            {
                enIpv4ConnStatus = enIpv4v6ConnStatus;
                enIpv6ConnStatus = enIpv4v6ConnStatus;
            }

            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               "%s: ",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%d,\"IPV4\"",
                                               enIpv4ConnStatus);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               ",%d,\"IPV6\"",
                                               enIpv6ConnStatus);
            break;

        case AT_IPV6_CAPABILITY_IPV4V6_OVER_TWO_PDP:
            enIpv4ConnStatus = AT_AppConvertPdpStateToConnStatus(AT_AppGetPdpState(TAF_PDP_IPV4));
            enIpv6ConnStatus = AT_AppConvertPdpStateToConnStatus(AT_AppGetPdpState(TAF_PDP_IPV6));

            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               "%s: ",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%d,\"IPV4\"",
                                               enIpv4ConnStatus);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               ",%d,\"IPV6\"",
                                               enIpv6ConnStatus);
            break;

        default:
            break;
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
 ?? ?? ??  : AT_TestApConnStPara
 ????????  : ^APCONNST????????
 ????????  : VOS_UINT8 ucIndex
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2013??4??27??
    ??    ??   : l60609
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 AT_TestApConnStPara(VOS_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-11)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    return AT_OK;
}

/*****************************************************************************
 ?? ?? ??  : At_SetApThroughputPara
 ????????  : ????CID??????????????
 ????????  : VOS_UINT8                           ucIndex
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2013??4??25??
    ??    ??   : l60609
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 At_SetApThroughputPara(
    VOS_UINT8                           ucIndex
)
{
    AT_RNIC_DSFLOW_IND_STRU            *pstMsg;
    RNIC_RMNET_ID_ENUM_UINT8            enRnicRmNetId;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;
    VOS_UINT8                           ucCid;

    /* ???????? */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ???????? */
    if (gucAtParaIndex != 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ucCid = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    /* ??????????RNIC???? */
    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    enRnicRmNetId = (RNIC_RMNET_ID_ENUM_UINT8)pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId;

    if (enRnicRmNetId >= RNIC_RMNET_ID_BUTT)
    {
        return AT_ERROR;
    }

    /* ????ID_AT_RNIC_DSFLOW_IND???? */
    pstMsg = (AT_RNIC_DSFLOW_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_AT,
                            sizeof(AT_RNIC_DSFLOW_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("At_SetApThroughputPara: alloc msg fail!");
        return AT_ERROR;
    }

    /* ?????????? */
    PS_MEM_SET((VOS_CHAR*)pstMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               (VOS_SIZE_T)(sizeof(AT_RNIC_DSFLOW_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ?????????? */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ACPU_PID_RNIC;
    pstMsg->enMsgId         = ID_AT_RNIC_DSFLOW_IND;
    pstMsg->clientId        = gastAtClientTab[ucIndex].usClientId;
    pstMsg->enRnicRmNetId   = enRnicRmNetId;

    /* ??ID_AT_RNIC_DSFLOW_IND??????RNIC?????????????? */
    if (VOS_OK == PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_APTHROUGH_PUT_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        AT_WARN_LOG("At_SetApThroughputPara: Send msg failed!");
        return AT_ERROR;
    }
}

/*****************************************************************************
 ?? ?? ??  : At_QryApThroughputPara
 ????????  : E5????????????
 ????????  : VOS_UINT8 ucIndex
 ????????  : ??
 ?? ?? ??  : ??????????
 ????????  :
 ????????  :

 ????????      :
 1.??    ??   : 2010??9??9??
   ??    ??   : s62952
   ????????   : ??????????
 2.??    ??   : 2011??12??08??
   ??    ??   : f00179208
   ????????   : PS Project: ??RNIC??????????????

*****************************************************************************/
VOS_UINT32 At_QryApThroughputPara(
    VOS_UINT8                           ucIndex
)
{
    AT_RNIC_DSFLOW_IND_STRU            *pstMsg;

    /* ????ID_AT_RNIC_DSFLOW_IND???? */
    pstMsg = (AT_RNIC_DSFLOW_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_AT,
                            sizeof(AT_RNIC_DSFLOW_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("At_QryApThroughputPara: alloc msg fail!");
        return AT_ERROR;
    }

    /* ?????????? */
    PS_MEM_SET((VOS_CHAR*)pstMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               (VOS_SIZE_T)(sizeof(AT_RNIC_DSFLOW_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ?????????? */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ACPU_PID_RNIC;
    pstMsg->enMsgId         = ID_AT_RNIC_DSFLOW_IND;
    pstMsg->clientId        = gastAtClientTab[ucIndex].usClientId;
    pstMsg->enRnicRmNetId   = RNIC_RMNET_ID_0;

    /* ??ID_AT_RNIC_DSFLOW_IND??????RNIC?????????????? */
    if (VOS_OK == PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_APTHROUGH_PUT_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        AT_WARN_LOG("At_QryApThroughputPara: Send msg failed!");
        return AT_ERROR;
    }
}

/*****************************************************************************
 ?? ?? ??  : AT_TestApThroughputPara
 ????????  : ^APTHROUGHOUT????????
 ????????  : VOS_UINT8 ucIndex
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2013??4??27??
    ??    ??   : l60609
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 AT_TestApThroughputPara(VOS_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-11)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    return AT_OK;
}
/* Modified by l60609 for V9R1 IPv6&TAF/SM Project, 2013-4-27, end */

/*****************************************************************************
 ?? ?? ??  : AT_SetApEndPppPara
 ????????  : APENDPPP????????????????????????????PAD????????PPP????
 ????????  : VOS_UINT8 ucIndex
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2013??7??9??
    ??    ??   : l60609
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 AT_SetApEndPppPara(VOS_UINT8 ucIndex)
{
    return AT_ERROR;
}

/*****************************************************************************
 ?? ?? ??  : AT_SetApDsFlowRptCfgPara
 ????????  : ^APDSFLOWRPTCFG=<enable>[,<threshold>[,<total_threshold>[,<oper>]]]
 ????????  : ucIndex --- ????????
 ????????  : ??
 ?? ?? ??  : AT_XXX  --- ATC??????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??2??2??
    ??    ??   : A00165503
    ????????   : ??????????
*****************************************************************************/
VOS_UINT32 AT_SetApDsFlowRptCfgPara(VOS_UINT8 ucIndex)
{
    TAF_APDSFLOW_RPT_CFG_STRU           stRptCfg;

    /* ???????? */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ???????????????? */
    if ((gucAtParaIndex < 1) || (gucAtParaIndex > 4))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* AT^APDSFLOWRPTCFG=, */
    if (0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ????<enable> */
    stRptCfg.ulRptEnabled = gastAtParaList[0].ulParaValue;

    if (VOS_TRUE == stRptCfg.ulRptEnabled)
    {
        /* AT^APDSFLOWRPTCFG=1 */
        if (1 == gucAtParaIndex)
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }

        /* AT^APDSFLOWRPTCFG=1, */
        if (0 == gastAtParaList[1].usParaLen)
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }

        /* AT^APDSFLOWRPTCFG=1,<threshold> */
        stRptCfg.ulFluxThreshold = gastAtParaList[1].ulParaValue;

        /* AT^APDSFLOWRPTCFG=1,0 */
        if (0 == stRptCfg.ulFluxThreshold)
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }
    }
    else
    {
        /* AT^APDSFLOWRPTCFG=0 */
        stRptCfg.ulFluxThreshold = 0;
    }

    /* ???????????? */
    if (VOS_OK != TAF_PS_SetApDsFlowRptCfg(WUEPS_PID_AT,
                                           AT_PS_BuildExClientId(gastAtClientTab[ucIndex].usClientId),
                                           0,
                                           &stRptCfg))
    {
        return AT_ERROR;
    }

    /* ???????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_APDSFLOWRPTCFG_SET;

    /* ???????????????????? */
    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 ?? ?? ??  : AT_QryApDsFlowRptCfgPara
 ????????  : ^APDSFLOWRPTCFG?
 ????????  : ucIndex --- ????????
 ????????  : ??
 ?? ?? ??  : AT_XXX  --- ATC??????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??2??2??
    ??    ??   : A00165503
    ????????   : ??????????
*****************************************************************************/
VOS_UINT32 AT_QryApDsFlowRptCfgPara(VOS_UINT8 ucIndex)
{
    /* ???????????? */
    if (VOS_OK != TAF_PS_GetApDsFlowRptCfg(WUEPS_PID_AT,
                                           AT_PS_BuildExClientId(gastAtClientTab[ucIndex].usClientId),
                                           0))
    {
        return AT_ERROR;
    }

    /* ???????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_APDSFLOWRPTCFG_QRY;

    /* ???????????????????? */
    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 ?? ?? ??  : AT_SetDsFlowNvWriteCfgPara
 ????????  : ^DSFLOWNVWRCFG=<enable>[,<interval>]
 ????????  : ucIndex --- ????????
 ????????  : ??
 ?? ?? ??  : AT_XXX  --- ATC??????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??2??2??
    ??    ??   : A00165503
    ????????   : ??????????
*****************************************************************************/
VOS_UINT32 AT_SetDsFlowNvWriteCfgPara(VOS_UINT8 ucIndex)
{
    TAF_DSFLOW_NV_WRITE_CFG_STRU        stWriteNvCfg;

    PS_MEM_SET(&stWriteNvCfg, 0x00, sizeof(TAF_DSFLOW_NV_WRITE_CFG_STRU));

    /* ???????? */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ???????????????? */
    if (gucAtParaIndex > 2)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* AT^DSFLOWNVWRCFG= */
    if (0 == gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* AT^DSFLOWNVWRCFG=,<interval> */
    if (0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ????<enable> */
    stWriteNvCfg.ucEnabled          = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    /* ????<interval> */
    if (gucAtParaIndex > 1)
    {
        if (0 != gastAtParaList[1].usParaLen)
        {
            /* AT^DSFLOWNVWRCFG=<enable>,<interval> */
            stWriteNvCfg.ucInterval = (VOS_UINT8)gastAtParaList[1].ulParaValue;
        }
        else
        {
            /* AT^DSFLOWNVWRCFG=<enable>, */
            return AT_CME_INCORRECT_PARAMETERS;
        }
    }
    else
    {
        /* AT^DSFLOWNVWRCFG=<enable> */
        stWriteNvCfg.ucInterval     = TAF_DEFAULT_DSFLOW_NV_WR_INTERVAL;
    }

    /* AT^DSFLOWNVWRCFG=1,0 */
    if ((VOS_TRUE == stWriteNvCfg.ucEnabled) && (0 == stWriteNvCfg.ucInterval))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ???????????? */
    if (VOS_OK != TAF_PS_SetDsFlowNvWriteCfg(WUEPS_PID_AT,
                                             AT_PS_BuildExClientId(gastAtClientTab[ucIndex].usClientId),
                                             0,
                                             &stWriteNvCfg))
    {
        return AT_ERROR;
    }

    /* ???????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DSFLOWNVWRCFG_SET;

    /* ???????????????????? */
    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 ?? ?? ??  : AT_QryDsFlowNvWriteCfgPara
 ????????  : ^DSFLOWNVWRCFG?
 ????????  : ucIndex --- ????????
 ????????  : ??
 ?? ?? ??  : AT_XXX  --- ATC??????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??2??2??
    ??    ??   : A00165503
    ????????   : ??????????
*****************************************************************************/
VOS_UINT32 AT_QryDsFlowNvWriteCfgPara(VOS_UINT8 ucIndex)
{
    /* ???????????? */
    if (VOS_OK != TAF_PS_GetDsFlowNvWriteCfg(WUEPS_PID_AT,
                                             AT_PS_BuildExClientId(gastAtClientTab[ucIndex].usClientId),
                                             0))
    {
        return AT_ERROR;
    }

    /* ???????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DSFLOWNVWRCFG_QRY;

    /* ???????????????????? */
    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 ?? ?? ??  : AT_SetImsPdpCfg
 ????????  : ^IMSPNDPCFG
 ????????  : ucIndex --- ????????
 ????????  : ??
 ?? ?? ??  : AT_XXX  --- ATC??????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??7??29??
    ??    ??   : z00301431
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 AT_SetImsPdpCfg(VOS_UINT8 ucIndex)
{
    TAF_IMS_PDP_CFG_STRU                stImsPdpCfg;

    /* ???????? */
    if (gucAtParaIndex != 2)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ???????? */
    if ((0 == gastAtParaList[0].usParaLen)
     || (0 == gastAtParaList[1].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    PS_MEM_SET(&stImsPdpCfg, 0, sizeof(stImsPdpCfg));

    /* ???????? */
    stImsPdpCfg.ucCid           = (VOS_UINT8)gastAtParaList[0].ulParaValue;
    stImsPdpCfg.ucImsFlag       = (VOS_UINT8)gastAtParaList[1].ulParaValue;

    /* ???????????? */
    if ( VOS_OK != TAF_PS_SetImsPdpCfg(WUEPS_PID_AT,
                                       AT_PS_BuildExClientId(gastAtClientTab[ucIndex].usClientId),
                                       0,
                                       &stImsPdpCfg) )
    {
        return AT_ERROR;
    }

    /* ???????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_IMSPDPCFG_SET;

    /* ???????????????????? */
    return AT_WAIT_ASYNC_RETURN;
}

