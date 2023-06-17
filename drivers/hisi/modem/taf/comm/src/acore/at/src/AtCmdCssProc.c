/******************************************************************************

                  ???????? (C), 2001-2011, ????????????????

 ******************************************************************************
  ?? ?? ??   : AtCmdCssProc.c
  ?? ?? ??   : ????
  ??    ??   : l00289540
  ????????   : 2015??09??23??
  ????????   :
  ????????   : CSS????????????
  ????????   :
  ????????   :
  1.??    ??   : 2015??09??23??
    ??    ??   : l00289540
    ????????   : ????????

******************************************************************************/

/*****************************************************************************
  1 ??????????
*****************************************************************************/
#include "AtCmdCssProc.h"
#include "ATCmdProc.h"
#include "PsCommonDef.h"


#define    THIS_FILE_ID                 PS_FILE_ID_AT_CMD_CSS_PROC_C

/*****************************************************************************
  2 ????????????
*****************************************************************************/
/*AT??CSS??????????????????????*/
const AT_CSS_MSG_PRO_FUNC_STRU g_astAtCssMsgTab[] =
{
    /* ????ID */                            /* ???????????? */
    {ID_CSS_AT_MCC_INFO_SET_CNF,              AT_RcvCssMccInfoSetCnf},
    {ID_CSS_AT_MCC_VERSION_INFO_CNF,          AT_RcvCssMccVersionQryCnf},
    {ID_CSS_AT_QUERY_MCC_INFO_NOTIFY,         AT_RcvCssMccNotify},
};

/*****************************************************************************
  3 ????????
*****************************************************************************/
/*****************************************************************************
 ?? ?? ??  : AT_ProcCssMsg
 ????????  : ????????CSS??????????
 ????????  : CssAtInterface_MSG *pstMsg
 ?? ?? ??  : ??
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??9??24??
    ??    ??   : l00289540
    ????????   : ??????????

*****************************************************************************/
VOS_VOID AT_ProcCssMsg(
    CssAtInterface_MSG                 *pstMsg
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulMsgId;
    VOS_UINT32                          ulRst;

    /*??g_astAtProcMsgFromImsaTab??????????????*/
    ulMsgCnt = sizeof(g_astAtCssMsgTab)/sizeof(AT_CSS_MSG_PRO_FUNC_STRU);

    /*??????????????MSG ID*/
    ulMsgId  = pstMsg->stMsgData.ulMsgId;

    /*g_astAtProcMsgFromCssTab??????????????????*/
    for (i = 0; i < ulMsgCnt; i++)
    {
        if (g_astAtCssMsgTab[i].ulMsgId == ulMsgId)
        {
            ulRst = g_astAtCssMsgTab[i].pProcMsgFunc(pstMsg);

            if (VOS_ERR == ulRst)
            {
                AT_ERR_LOG("AT_ProcCssMsg: Msg Proc Err!");
            }

            return;
        }
    }

    /*??????????????????*/
    if (ulMsgCnt == i)
    {
        AT_ERR_LOG("AT_ProcCssMsg: Msg Id is invalid!");
    }

    return;
}

/*****************************************************************************
 ?? ?? ??  : AT_RcvCssMccInfoSetCnf
 ????????  : AT????CSS??????????????????????
 ????????  : ??
 ?? ?? ??  : VOS_UINT32 AT_R
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??9??24??
    ??    ??   : l00289540
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 AT_RcvCssMccInfoSetCnf(
    VOS_VOID                           *pstMsg
)
{
    /* ???????????? */
    CSS_AT_MCC_INFO_SET_CNF_STRU       *pstMccInfoSetCnf    = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulRetVal;

    /* ?????????????? */
    ucIndex          = 0;
    ulRetVal         = VOS_ERR;
    ulResult         = AT_ERROR;
    pstMccInfoSetCnf = (CSS_AT_MCC_INFO_SET_CNF_STRU *)pstMsg;

    /* ????ClientId????ucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstMccInfoSetCnf->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvCssMccInfoSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvCssMccInfoSetCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* ??????????????????????AT_CMD_MCCFREQ_SET */
    if (AT_CMD_MCCFREQ_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvCssMccInfoSetCnf: WARNING:Not AT_CMD_MCCFREQ_SET!");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ???????????????????? */
    if (VOS_OK == pstMccInfoSetCnf->ulResult)
    {
        ulResult    = AT_OK;
        ulRetVal    = VOS_OK;
    }

    gstAtSendData.usBufLen = 0;

    /* ????At_FormatResultData???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return ulRetVal;
}


/*****************************************************************************
 ?? ?? ??  : AT_RcvCssMccVersionQryCnf
 ????????  : AT????CSS????????????????????????????????
 ????????  : ??
 ?? ?? ??  : VOS_UINT32 AT_R
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??9??24??
    ??    ??   : l00289540
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 AT_RcvCssMccVersionQryCnf(
    VOS_VOID                           *pstMsg
)
{
    /* ???????????? */
    CSS_AT_MCC_VERSION_INFO_CNF_STRU   *pstMccVersionInfoCnf    = VOS_NULL_PTR;
    VOS_UINT8                           aucVersionId[MCC_INFO_VERSION_LEN+1] = {0};
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ?????????????? */
    ucIndex     = 0;
    pstMccVersionInfoCnf = (CSS_AT_MCC_VERSION_INFO_CNF_STRU *)pstMsg;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstMccVersionInfoCnf->usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvCssMccVersionQryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvCssMccVersionQryCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* ??????????????????????AT_CMD_MCCFREQ_QRY */
    if ( AT_CMD_MCCFREQ_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        AT_WARN_LOG("AT_RcvCssMccVersionQryCnf: WARNING:Not AT_CMD_MCCFREQ_QRY!");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ????Version String */
    PS_MEM_CPY(aucVersionId, pstMccVersionInfoCnf->aucVersionId, MCC_INFO_VERSION_LEN);

    /* ???????????????????? */
    gstAtSendData.usBufLen= (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   "%s: %s",
                                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                   (VOS_CHAR *)aucVersionId);

    ulResult = AT_OK;

    /* ????At_FormatResultData???????????? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}



/*****************************************************************************
 ?? ?? ??  : AT_RcvCssMccNotify
 ????????  : ^MCC????????????????????????????????:^MCC:Version,[MCC,]MCC
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??9??24??
    ??    ??   : l00289540
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 AT_RcvCssMccNotify(
    VOS_VOID                           *pstMsg
)
{
    /* ???????????? */
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           i;
    VOS_UINT8                           aucMccStr[AT_CSS_MAX_MCC_ID_NUM*AT_MCC_PLUS_COMMA_LENGTH] = {0};
    VOS_UINT8                           aucVersionId[MCC_INFO_VERSION_LEN+1] = {0};
    CSS_AT_QUERY_MCC_INFO_NOTIFY_STRU  *pstCssMccNty    = VOS_NULL_PTR;

    /* ?????????????? */
    ucIndex      = 0;
    pstCssMccNty = (CSS_AT_QUERY_MCC_INFO_NOTIFY_STRU *)pstMsg;

    /* ????ClientId????ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstCssMccNty->usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvCssMccNotify: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* MCC???????? */
    if ((0 == pstCssMccNty->ulMccNum)
     || (AT_CSS_MAX_MCC_ID_NUM < pstCssMccNty->ulMccNum))
    {
        AT_WARN_LOG("AT_RcvCssMccNotify: WARNING:INVALID MCC NUM!");
        return VOS_ERR;
    }

    /* ??????????Ril??MCC?????? */
    for (i = 0; i < pstCssMccNty->ulMccNum; i++)
    {
        aucMccStr[AT_MCC_PLUS_COMMA_LENGTH*i]   = (pstCssMccNty->astMccId[i].aucMcc[0] & 0x0f) + '0';
        aucMccStr[AT_MCC_PLUS_COMMA_LENGTH*i+1] = ((pstCssMccNty->astMccId[i].aucMcc[0] & 0xf0) >> 4) + '0';
        aucMccStr[AT_MCC_PLUS_COMMA_LENGTH*i+2] = (pstCssMccNty->astMccId[i].aucMcc[1] & 0x0f) + '0';
        aucMccStr[AT_MCC_PLUS_COMMA_LENGTH*i+3] = ',';
    }

    /* ???????????? */
    aucMccStr[(VOS_UINT8)(pstCssMccNty->ulMccNum)*AT_MCC_PLUS_COMMA_LENGTH-1] = 0;

    /* ????Version String */
    PS_MEM_CPY(aucVersionId, pstCssMccNty->aucVersionId, MCC_INFO_VERSION_LEN);

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s%s %s,%s%s",
                                                    gaucAtCrLf,
                                                    gastAtStringTab[AT_STRING_MCC].pucText,
                                                    (VOS_CHAR *)aucVersionId,
                                                    (VOS_CHAR *)aucMccStr,
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}




