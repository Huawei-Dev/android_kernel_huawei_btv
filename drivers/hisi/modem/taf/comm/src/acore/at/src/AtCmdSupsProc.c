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
#include "ATCmdProc.h"
#include "AtCmdSupsProc.h"
#include "TafSsaApi.h"


/*****************************************************************************
    ??????????????????????.C??????????
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID                 PS_FILE_ID_AT_CMD_SUPS_PROC_C
/*lint +e767*/

/*****************************************************************************
  2 ????????????
*****************************************************************************/
const AT_SS_EVT_FUNC_TBL_STRU           g_astAtSsEvtFuncTbl[] =
{
    /* ????ID */                                /* ???????????? */
    {ID_TAF_SSA_SET_LCS_MOLR_CNF,               AT_RcvSsaSetLcsMolrCnf},
    {ID_TAF_SSA_GET_LCS_MOLR_CNF,               AT_RcvSsaGetLcsMolrCnf},
    {ID_TAF_SSA_LCS_MOLR_NTF,                   AT_RcvSsaLcsMolrNtf},
    {ID_TAF_SSA_SET_LCS_MTLR_CNF,               AT_RcvSsaSetLcsMtlrCnf},
    {ID_TAF_SSA_GET_LCS_MTLR_CNF,               AT_RcvSsaGetLcsMtlrCnf},
    {ID_TAF_SSA_LCS_MTLR_NTF,                   AT_RcvSsaLcsMtlrNtf},
    {ID_TAF_SSA_SET_LCS_MTLRA_CNF,              AT_RcvSsaSetLcsMtlraCnf},
    {ID_TAF_SSA_GET_LCS_MTLRA_CNF,              AT_RcvSsaGetLcsMtlraCnf},
};


/*****************************************************************************
  3 ????????
*****************************************************************************/
/*****************************************************************************
 ?? ?? ??  : AT_ConvertTafSsaErrorCode
 ????????  : AT????????SSA????????????????
 ????????  : VOS_UINT8                           ucIndex
             TAF_ERROR_CODE_ENUM_UINT32          enErrorCode
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??10??20??
    ??    ??   : l00198894
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 AT_ConvertTafSsaErrorCode(
    VOS_UINT8                           ucIndex,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCode)
{
    VOS_UINT32                          ulResult;

    if (TAF_ERR_NO_ERROR == enErrorCode)
    {
        return AT_OK;
    }

    ulResult    = AT_ERROR;

    if ( (enErrorCode >= TAF_ERR_LCS_BASE)
      && (enErrorCode <= TAF_ERR_LCS_UNKNOWN_ERROR) )
    {
        ulResult = enErrorCode - TAF_ERR_LCS_BASE + AT_CMOLRE_ERR_ENUM_BEGIN + 1;
        return ulResult;
    }

    ulResult = At_ChgTafErrorCode(ucIndex, enErrorCode);

    return ulResult;
}

/*****************************************************************************
 ?? ?? ??  : AT_FillCmolrParaEnable
 ????????  : [????????]????+CMOLR????????<enable>
 ????????  : TAF_SSA_LCS_MOLR_PARA_SET_STRU      *pstMolrPara;
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??9??11??
    ??    ??   : l00198894
    ????????   : ??????????

*****************************************************************************/
VOS_VOID AT_FillCmolrParaEnable(
    TAF_SSA_LCS_MOLR_PARA_SET_STRU     *pstMolrPara
)
{
    /* <enable> */
    if ( (0 == gucAtParaIndex)
      || (0 == gastAtParaList[0].usParaLen) )
    {
        pstMolrPara->enEnable = TAF_SSA_LCS_MOLR_ENABLE_TYPE_DISABLE;
    }
    else
    {
        pstMolrPara->enEnable = (VOS_UINT8)gastAtParaList[0].ulParaValue;
    }

    return;
}

/*****************************************************************************
 ?? ?? ??  : AT_FillCmolrParaMethod
 ????????  : [????????]????+CMOLR????????<method>
 ????????  : TAF_SSA_LCS_MOLR_PARA_SET_STRU      *pstMolrPara;
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??9??11??
    ??    ??   : l00198894
    ????????   : ??????????

*****************************************************************************/
VOS_VOID AT_FillCmolrParaMethod(
    TAF_SSA_LCS_MOLR_PARA_SET_STRU     *pstMolrPara
)
{
    if ( (1 >= gucAtParaIndex)
      || (0 == gastAtParaList[1].usParaLen) )
    {
        return;
    }

    /* <method> */
    pstMolrPara->bitOpMethod    = VOS_TRUE;
    pstMolrPara->enMethod       = (VOS_UINT8)gastAtParaList[1].ulParaValue;

    return;
}

/*****************************************************************************
 ?? ?? ??  : AT_FillCmolrParaHorAcc
 ????????  : [????????]????+CMOLR????????<hor-acc-set>??<hor-acc>
 ????????  : TAF_SSA_SET_LCS_MOLR_REQ_STRU      *pstMolrReq;
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
             VOS_OK         -- ????????
             VOS_ERR        -- ????????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??9??11??
    ??    ??   : l00198894
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 AT_FillCmolrParaHorAcc(
    TAF_SSA_LCS_MOLR_PARA_SET_STRU     *pstMolrPara
)
{
    if ( (2 >= gucAtParaIndex)
      || (0 == gastAtParaList[2].usParaLen) )
    {
        return VOS_OK;
    }

    /* <hor-acc-set> */
    pstMolrPara->bitOpHorAccSet = VOS_TRUE;
    pstMolrPara->enHorAccSet    = (VOS_UINT8)gastAtParaList[2].ulParaValue;

    if (LCS_HOR_ACC_SET_PARAM == pstMolrPara->enHorAccSet)
    {
        /* <hor-acc> */
        /* ?????????????????????????????????????????????? */
        if ( (3 >= gucAtParaIndex)
          || (0 == gastAtParaList[3].usParaLen) )
        {
            AT_WARN_LOG("AT_FillCmolrParaPartI: <hor-acc> is required!");
            return VOS_ERR;
        }

        pstMolrPara->ucHorAcc   = (VOS_UINT8)gastAtParaList[3].ulParaValue;
    }

    return VOS_OK;
}

/*****************************************************************************
 ?? ?? ??  : AT_FillCmolrParaVerReq
 ????????  : [????????]????+CMOLR????????<ver-req>??<ver-acc-set>??<ver-acc>
 ????????  : TAF_SSA_LCS_MOLR_PARA_SET_STRU      *pstMolrPara;
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
             VOS_OK         -- ????????
             VOS_ERR        -- ????????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??9??11??
    ??    ??   : l00198894
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 AT_FillCmolrParaVerReq(
    TAF_SSA_LCS_MOLR_PARA_SET_STRU     *pstMolrPara
)
{
    if ( (4 >= gucAtParaIndex)
      || (0 == gastAtParaList[4].usParaLen) )
    {
        return VOS_OK;
    }

    /* <ver-req> */
    pstMolrPara->bitOpVerReq    = VOS_TRUE;
    pstMolrPara->enVerReq       = (VOS_UINT8)gastAtParaList[4].ulParaValue;

    if ( (LCS_VER_REQUESTED != pstMolrPara->enVerReq)
      || (5 >= gucAtParaIndex)
      || (0 == gastAtParaList[5].usParaLen) )
    {
        return VOS_OK;
    }

    /* <ver-acc-set> */
    pstMolrPara->bitOpVerAccSet = VOS_TRUE;
    pstMolrPara->enVerAccSet    = (VOS_UINT8)gastAtParaList[5].ulParaValue;

    if (LCS_VER_ACC_SET_PARAM == pstMolrPara->enVerAccSet)
    {
        /* <ver-acc> */
        /* ?????????????????????????????????????????????? */
        if ( (6 >= gucAtParaIndex)
          || (0 == gastAtParaList[6].usParaLen) )
        {
            AT_WARN_LOG("AT_FillCmolrParaVerReq: <ver-acc> is required!");
            return VOS_ERR;
        }

        pstMolrPara->ucVerAcc   = (VOS_UINT8)gastAtParaList[6].ulParaValue;
    }

    return VOS_OK;
}

/*****************************************************************************
 ?? ?? ??  : AT_FillCmolrParaVelReq
 ????????  : [????????]????+CMOLR????????<vel-req>
 ????????  : TAF_SSA_LCS_MOLR_PARA_SET_STRU      *pstMolrPara;
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??9??11??
    ??    ??   : l00198894
    ????????   : ??????????

*****************************************************************************/
VOS_VOID AT_FillCmolrParaVelReq(
    TAF_SSA_LCS_MOLR_PARA_SET_STRU     *pstMolrPara
)
{
    if ( (7 >= gucAtParaIndex)
      || (0 == gastAtParaList[7].usParaLen))
    {
        return;
    }

    /* <vel-req> */
    pstMolrPara->bitOpVelReq    = VOS_TRUE;
    pstMolrPara->enVelReq       = (VOS_UINT8)gastAtParaList[7].ulParaValue;

    return;
}

/*****************************************************************************
 ?? ?? ??  : AT_FillCmolrParaRepMode
 ????????  : [????????]????+CMOLR????????<rep-mode>
 ????????  : TAF_SSA_SET_LCS_MOLR_REQ_STRU      *pstMolrReq;
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
             VOS_OK         -- ????????
             VOS_ERR        -- ????????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??9??11??
    ??    ??   : l00198894
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 AT_FillCmolrParaRepMode(
    TAF_SSA_LCS_MOLR_PARA_SET_STRU     *pstMolrPara
)
{
    if ( (8 >= gucAtParaIndex)
      || (0 == gastAtParaList[8].usParaLen) )
    {
        return VOS_OK;
    }

    /* <rep-mode> */
    pstMolrPara->bitOpRepMode   = VOS_TRUE;
    pstMolrPara->enRepMode      = (VOS_UINT8)gastAtParaList[8].ulParaValue;

    if (9 >= gucAtParaIndex)
    {
        return VOS_OK;
    }

    /* <timeout> */
    if (0 != gastAtParaList[9].usParaLen)
    {
        pstMolrPara->bitOpTimeout   = VOS_TRUE;
        pstMolrPara->usTimeOut      = (VOS_UINT16)gastAtParaList[9].ulParaValue;
    }

    /* <interval> */
    if (LCS_REP_MODE_PERIODIC_RPT == pstMolrPara->enRepMode)
    {
        if ( (10 < gucAtParaIndex)
          && (0 != gastAtParaList[10].usParaLen) )
        {
            pstMolrPara->bitOpInterval  = VOS_TRUE;
            pstMolrPara->usInterval     = (VOS_UINT16)gastAtParaList[10].ulParaValue;
        }
    }

    if ( (VOS_TRUE == pstMolrPara->bitOpTimeout)
      && (VOS_TRUE == pstMolrPara->bitOpInterval)
      && (pstMolrPara->usInterval < pstMolrPara->usTimeOut) )
    {
        AT_WARN_LOG("AT_FillCmolrParaPartI: <interval> is too short!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 ?? ?? ??  : AT_FillCmolrParaShapeRep
 ????????  : [????????]????+CMOLR????????<shape-rep>
 ????????  : TAF_SSA_LCS_MOLR_PARA_SET_STRU      *pstMolrPara;
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??9??11??
    ??    ??   : l00198894
    ????????   : ??????????

*****************************************************************************/
VOS_VOID AT_FillCmolrParaShapeRep(
    TAF_SSA_LCS_MOLR_PARA_SET_STRU     *pstMolrPara
)
{
    if ( (11 >= gucAtParaIndex)
      || (0 == gastAtParaList[11].usParaLen) )
    {
        return;
    }

    /* <shape-rep> */
    pstMolrPara->bitOpShapeRep  = VOS_TRUE;
    pstMolrPara->ucShapeRep     = (VOS_UINT8)gastAtParaList[11].ulParaValue;

    return;
}

/*****************************************************************************
 ?? ?? ??  : AT_FillCmolrParaPlane
 ????????  : [????????]????+CMOLR????????<plane>
 ????????  : TAF_SSA_LCS_MOLR_PARA_SET_STRU      *pstMolrPara;
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??9??11??
    ??    ??   : l00198894
    ????????   : ??????????

*****************************************************************************/
VOS_VOID AT_FillCmolrParaPlane(
    TAF_SSA_LCS_MOLR_PARA_SET_STRU     *pstMolrPara
)
{
    if ( (12 >= gucAtParaIndex)
      || (0 == gastAtParaList[12].usParaLen) )
    {
        return;
    }

    /* <plane> */
    pstMolrPara->bitOpPlane     = VOS_TRUE;
    pstMolrPara->enPlane        = (VOS_UINT8)gastAtParaList[12].ulParaValue;

    return;
}

/*****************************************************************************
 ?? ?? ??  : AT_Str2NmeaRep
 ????????  : AT??????????????????NMEA????????
 ????????  : VOS_UINT16                          usLength
             VOS_CHAR                           *pcStr
             TAF_SSA_LCS_NMEA_REP_STRU          *pstNmeaRep
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??9??12??
    ??    ??   : l00198894
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 AT_Str2NmeaRep(
    VOS_UINT16                          usLength,
    VOS_CHAR                           *pcStr,
    TAF_SSA_LCS_NMEA_REP_STRU          *pstNmeaRep
)
{
    VOS_UINT32                          ulNum;
    VOS_UINT32                          ulLoop;
    VOS_CHAR                           *pcTemp  = VOS_NULL_PTR;
    VOS_CHAR                            aucSrcStr[AT_PARA_NMEA_MAX_LEN + 1];

    PS_MEM_SET(aucSrcStr, 0, sizeof(aucSrcStr));
    PS_MEM_SET(pstNmeaRep, 0, sizeof(TAF_SSA_LCS_NMEA_REP_STRU));

    if (usLength > AT_PARA_NMEA_MAX_LEN)
    {
        AT_WARN_LOG("AT_Str2NmeaRep: NMEA format string is too long!");
        return VOS_ERR;
    }

    ulNum = (usLength + 1) / (AT_PARA_NMEA_MIN_LEN + 1);

    if (0 == ulNum)
    {
        AT_WARN_LOG("AT_Str2NmeaRep: NMEA format string is too short!");
        return VOS_ERR;
    }

    PS_MEM_CPY(aucSrcStr, pcStr, usLength);
    pcTemp = aucSrcStr;

    for (ulLoop = 0; ulLoop < ulNum; ulLoop++)
    {
        /* $GPGGA */
        if (0 == VOS_MemCmp(pcTemp, AT_PARA_NMEA_GPGGA, AT_PARA_NMEA_MIN_LEN))
        {
            pstNmeaRep->bitGPGGA = VOS_TRUE;
        }
        /* $GPRMC */
        else if (0 == VOS_MemCmp(pcTemp, AT_PARA_NMEA_GPRMC, AT_PARA_NMEA_MIN_LEN))
        {
            pstNmeaRep->bitGPRMC = VOS_TRUE;
        }
        /* $GPGLL */
        else if (0 == VOS_MemCmp(pcTemp, AT_PARA_NMEA_GPGLL, AT_PARA_NMEA_MIN_LEN))
        {
            pstNmeaRep->bitGPGLL = VOS_TRUE;
        }
        else
        {
            AT_WARN_LOG("AT_Str2NmeaRep: NMEA format string is incorrect!");
            return VOS_ERR;
        }

        pcTemp += (AT_PARA_NMEA_MIN_LEN + 1);
    }

    return VOS_OK;
}

/*****************************************************************************
 ?? ?? ??  : AT_FillCmolrParaNmeaRep
 ????????  : [????????]????+CMOLR????<NMEA-rep>
 ????????  : TAF_SSA_SET_LCS_MOLR_REQ_STRU      *pstMolrReq;
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
             VOS_OK         -- ????????
             VOS_ERR        -- ????????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??9??11??
    ??    ??   : l00198894
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 AT_FillCmolrParaNmeaRep(
    TAF_SSA_LCS_MOLR_PARA_SET_STRU     *pstMolrPara
)
{
    if ( (13 >= gucAtParaIndex)
      || (0 == gastAtParaList[13].usParaLen) )
    {
        return VOS_OK;
    }

    /* <NMEA-rep> */
    if ( (TAF_SSA_LCS_MOLR_ENABLE_TYPE_NMEA     == pstMolrPara->enEnable)
      || (TAF_SSA_LCS_MOLR_ENABLE_TYPE_NMEA_GAD == pstMolrPara->enEnable) )
    {
        pstMolrPara->bitOpNmeaRep = VOS_TRUE;
        if (VOS_OK != AT_Str2NmeaRep(gastAtParaList[13].usParaLen,
                                     (VOS_CHAR *)gastAtParaList[13].aucPara,
                                     &(pstMolrPara->stNmeaRep)))
        {
            return VOS_ERR;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 ?? ?? ??  : AT_FillCmolrParaThdPtyAddr
 ????????  : [????????]????+CMOLR????????<third-party-address>
 ????????  : TAF_SSA_SET_LCS_MOLR_REQ_STRU      *pstMolrReq;
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
             VOS_OK         -- ????????
             VOS_ERR        -- ????????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??9??11??
    ??    ??   : l00198894
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 AT_FillCmolrParaThdPtyAddr(
    TAF_SSA_LCS_MOLR_PARA_SET_STRU     *pstMolrPara
)
{
    if ( (14 >= gucAtParaIndex)
      || (0 == gastAtParaList[14].usParaLen) )
    {
        return VOS_OK;
    }

    /* <third-party-address> */
    if (TAF_SSA_LCS_THIRD_PARTY_ADDR_MAX_LEN < gastAtParaList[14].usParaLen)
    {
        AT_WARN_LOG("AT_FillCmolrParaPartIII: <third-party-address> is too long!");
        return VOS_ERR;;
    }

    pstMolrPara->bitOpThirdPartyAddr = VOS_TRUE;
    PS_MEM_CPY(pstMolrPara->acThirdPartyAddr,
               (VOS_CHAR *)gastAtParaList[14].aucPara,
               gastAtParaList[14].usParaLen);

    return VOS_OK;
}

/*****************************************************************************
 ?? ?? ??  : AT_FillCmolrPara
 ????????  : [????????]????+CMOLR????????
 ????????  : TAF_SSA_SET_LCS_MOLR_REQ_STRU      *pstMolrReq;
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
             VOS_OK         -- ????????
             VOS_ERR        -- ????????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??9??11??
    ??    ??   : l00198894
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 AT_FillCmolrPara(
    TAF_SSA_LCS_MOLR_PARA_SET_STRU     *pstMolrPara
)
{
    PS_MEM_SET(pstMolrPara, 0, sizeof(TAF_SSA_LCS_MOLR_PARA_SET_STRU));

    /* +CMOLR=[<enable>[,<method>[,<hor-acc-set>[,<hor-acc>[,<ver-req>
               [,<ver-acc-set>[,<ver-acc>[,<vel-req> [,<rep-mode>[,<timeout>
               [,<interval>[,<shape-rep>[,<plane>[,<NMEA-rep>
               [,<third-party-address>]]]]]]]]]]]]]]]] */

    /* ?????????????????? */
    if (15 < gucAtParaIndex)
    {
        AT_WARN_LOG("AT_FillCmolrPara: too many parameters!");
        return VOS_ERR;
    }

    AT_FillCmolrParaEnable(pstMolrPara);

    AT_FillCmolrParaMethod(pstMolrPara);

    if (VOS_OK != AT_FillCmolrParaHorAcc(pstMolrPara))
    {
        return VOS_ERR;
    }

    if (VOS_OK != AT_FillCmolrParaVerReq(pstMolrPara))
    {
        return VOS_ERR;
    }

    AT_FillCmolrParaVelReq(pstMolrPara);

    if (VOS_OK != AT_FillCmolrParaRepMode(pstMolrPara))
    {
        return VOS_ERR;
    }

    AT_FillCmolrParaShapeRep(pstMolrPara);

    AT_FillCmolrParaPlane(pstMolrPara);

    if (VOS_OK != AT_FillCmolrParaNmeaRep(pstMolrPara))
    {
        return VOS_ERR;
    }

    if (VOS_OK != AT_FillCmolrParaThdPtyAddr(pstMolrPara))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 ?? ?? ??  : AT_SetCmolrPara
 ????????  : +CMOLR????????????????
 ????????  : VOS_UINT8 ucIndex
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??9??9??
    ??    ??   : l00198894
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 AT_SetCmolrPara(VOS_UINT8 ucIndex)
{
    TAF_SSA_LCS_MOLR_PARA_SET_STRU      stMolrPara;

    PS_MEM_SET(&stMolrPara, 0, sizeof(stMolrPara));

    /* ???????? */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        AT_WARN_LOG("AT_SetCmolrPara: Option Type Incrrect!");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (VOS_OK != AT_FillCmolrPara(&stMolrPara))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ???????????? */
    TAF_SSA_SetCmolrInfo(WUEPS_PID_AT,
                         gastAtClientTab[ucIndex].usClientId,
                         gastAtClientTab[ucIndex].opId,
                         &stMolrPara);

    /* ???????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CMOLR_SET;

    /* ???????????????? */
    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 ?? ?? ??  : AT_RcvSsaSetLcsMolrCnf
 ????????  : AT????????TAF??SSA??????????MOLR????????
 ????????  : VOS_UINT8                           ucIndex
             VOS_VOID                           *pEvent
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??10??19??
    ??    ??   : l00198894
    ????????   : ??????????

*****************************************************************************/
VOS_VOID AT_RcvSsaSetLcsMolrCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvent
)
{
    TAF_SSA_SET_LCS_MOLR_CNF_STRU      *pstSetLcsMolrCnf    = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;

    /* ?????????????? */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvSsaSetLcsMolrCnf: WARNING:AT_BROADCAST_INDEX!");
        return;
    }

    /* ??????????????????????AT_CMD_CMOLR_SET */
    if (AT_CMD_CMOLR_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvSsaSetLcsMolrCnf: WARNING:Not AT_CMD_CMOLR_SET!");
        return;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    pstSetLcsMolrCnf    = (TAF_SSA_SET_LCS_MOLR_CNF_STRU *)pEvent;
    ulResult            = AT_ConvertTafSsaErrorCode(ucIndex, pstSetLcsMolrCnf->enResult);

    if (AT_OK != ulResult)
    {
        AT_WARN_LOG("AT_RcvSsaSetLcsMolrCnf: WARNING:Set ^CMOLR Failed!");
    }

    /* ???????? */
    gstAtSendData.usBufLen = 0;
    At_FormatResultData(ucIndex, ulResult);

    return;
}

/*****************************************************************************
 ?? ?? ??  : AT_QryCmolrPara
 ????????  : +CMOLR????????????????
 ????????  : VOS_UINT8 ucIndex
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??9??9??
    ??    ??   : l00198894
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 AT_QryCmolrPara(VOS_UINT8 ucIndex)
{
    /* ???????????? */
    TAF_SSA_GetCmolrInfo(WUEPS_PID_AT,
                         gastAtClientTab[ucIndex].usClientId,
                         gastAtClientTab[ucIndex].opId);

    /* ???????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CMOLR_READ;

    /* ???????????????? */
    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 ?? ?? ??  : AT_RcvSsaGetLcsMolrCnf
 ????????  : AT????????TAF??SSA??????????MOLR????????
 ????????  : VOS_UINT8                           ucIndex
             VOS_VOID                           *pEvent
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??10??19??
    ??    ??   : l00198894
    ????????   : ??????????

*****************************************************************************/
VOS_VOID AT_RcvSsaGetLcsMolrCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvent
)
{
    TAF_SSA_GET_LCS_MOLR_CNF_STRU      *pstGetLcsMolrCnf    = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_BOOL                            bNmeaFlg;
    VOS_UINT16                          usLength;
    VOS_UINT8                           aucTPAStr[LCS_CLIENT_EXID_MAX_LEN + 1];

    /* ?????????????? */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvSsaGetLcsMolrCnf: WARNING:AT_BROADCAST_INDEX!");
        return;
    }

    /* ??????????????????????AT_CMD_CMOLR_READ */
    if (AT_CMD_CMOLR_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvSsaGetLcsMolrCnf: WARNING:Not AT_CMD_CMOLR_READ!");
        return;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    pstGetLcsMolrCnf    = (TAF_SSA_GET_LCS_MOLR_CNF_STRU *)pEvent;
    ulResult            = AT_ConvertTafSsaErrorCode(ucIndex, pstGetLcsMolrCnf->enResult);
    bNmeaFlg            = VOS_FALSE;
    usLength            = 0;

    /* ???????????????????? */
    if (AT_OK == ulResult)
    {
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          "%s: %d,%d,%d,",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          pstGetLcsMolrCnf->enEnable,
                                          pstGetLcsMolrCnf->stMolrPara.enMethod,
                                          pstGetLcsMolrCnf->stMolrPara.enHorAccSet);

        if (LCS_HOR_ACC_SET_PARAM == pstGetLcsMolrCnf->stMolrPara.enHorAccSet)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%d",
                                               pstGetLcsMolrCnf->stMolrPara.ucHorAcc);
        }

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",%d,",
                                           pstGetLcsMolrCnf->stMolrPara.enVerReq);

        if (LCS_VER_REQUESTED == pstGetLcsMolrCnf->stMolrPara.enVerReq)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%d,",
                                               pstGetLcsMolrCnf->stMolrPara.enVerAccSet);

            if (LCS_VER_ACC_SET_PARAM == pstGetLcsMolrCnf->stMolrPara.enVerAccSet)
            {
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "%d",
                                                   pstGetLcsMolrCnf->stMolrPara.ucVerAcc);
            }
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               ",");
        }

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",%d,%d,%d,",
                                           pstGetLcsMolrCnf->stMolrPara.enVelReq,
                                           pstGetLcsMolrCnf->stMolrPara.enRepMode,
                                           pstGetLcsMolrCnf->stMolrPara.usTimeOut);

        if (LCS_REP_MODE_PERIODIC_RPT == pstGetLcsMolrCnf->stMolrPara.enRepMode)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%d",
                                               pstGetLcsMolrCnf->stMolrPara.usInterval);
        }

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",%d,%d,",
                                           pstGetLcsMolrCnf->stMolrPara.u.ucShapeRep,
                                           pstGetLcsMolrCnf->enPlane);

        if ( (TAF_SSA_LCS_MOLR_ENABLE_TYPE_NMEA == pstGetLcsMolrCnf->enEnable)
          || (TAF_SSA_LCS_MOLR_ENABLE_TYPE_NMEA_GAD == pstGetLcsMolrCnf->enEnable) )
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "\"");

            if (VOS_TRUE == pstGetLcsMolrCnf->stNmeaRep.bitGPGGA)
            {
                bNmeaFlg  = VOS_TRUE;
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "%s,",
                                                   AT_PARA_NMEA_GPGGA);
            }

            if (VOS_TRUE == pstGetLcsMolrCnf->stNmeaRep.bitGPRMC)
            {
                bNmeaFlg  = VOS_TRUE;
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "%s,",
                                                   AT_PARA_NMEA_GPRMC);
            }

            if (VOS_TRUE == pstGetLcsMolrCnf->stNmeaRep.bitGPGLL)
            {
                bNmeaFlg  = VOS_TRUE;
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "%s,",
                                                   AT_PARA_NMEA_GPGLL);
            }
            /* ???????????????????? */
            usLength -= 1;

            if (VOS_TRUE == bNmeaFlg)
            {
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "\"");
            }
        }

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",");

        if ( ((LCS_MOLR_METHOD_TRANSFER_TP_ADDR == pstGetLcsMolrCnf->stMolrPara.enMethod)
           || (LCS_MOLR_METHOD_RETRIEVAL_TP_ADDR == pstGetLcsMolrCnf->stMolrPara.enMethod))
          && ((pstGetLcsMolrCnf->stMolrPara.stTPAddr.ucLength > 0)
           && (pstGetLcsMolrCnf->stMolrPara.stTPAddr.ucLength <= LCS_CLIENT_EXID_MAX_LEN)) )
        {
            PS_MEM_SET(aucTPAStr, 0, LCS_CLIENT_EXID_MAX_LEN + 1);
            PS_MEM_CPY(aucTPAStr,
                       pstGetLcsMolrCnf->stMolrPara.stTPAddr.aucValue,
                       pstGetLcsMolrCnf->stMolrPara.stTPAddr.ucLength);

            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "\"%s\"",
                                               aucTPAStr);
        }

    }

    /* ???????? */
    gstAtSendData.usBufLen = usLength;
    At_FormatResultData(ucIndex, ulResult);

    return;
}

/*****************************************************************************
 ?? ?? ??  : AT_TestCmolrPara
 ????????  : +CMOLR????????????????
 ????????  : VOS_UINT8 ucIndex
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??9??9??
    ??    ??   : l00198894
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 AT_TestCmolrPara(VOS_UINT8 ucIndex)
{
    /* ???????????????? */
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                "%s: (0-3),(0-6),(0,1),(0-127),(0,1),(0,1),(0-127),(0-4),"
                                "(0,1),(1-65535),(1-65535),(1-127),(0,1),"
                                /* "\"$GPGSA,$GPGGA,$GPGSV,$GPRMC,$GPVTG,$GPGLL\"," */
                                "\"$GPGGA,$GPRMC,$GPGLL\","
                                "\"<third-party-address>\"",     /* <third-party-address>???????????????? */
                                g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    return AT_OK;
}

/*****************************************************************************
 ?? ?? ??  : AT_RcvSsaLcsMolrNtf
 ????????  : AT????????TAF??SSA??????????MOLR????????
 ????????  : VOS_UINT8                           ucIndex
             VOS_VOID                           *pEvent
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??10??20??
    ??    ??   : l00198894
    ????????   : ??????????

*****************************************************************************/
VOS_VOID AT_RcvSsaLcsMolrNtf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvent
)
{
    TAF_SSA_LCS_MOLR_NTF_STRU          *pstLcsMolrNtf   = VOS_NULL_PTR;
    AT_MODEM_AGPS_CTX_STRU             *pstAgpsCtx      = VOS_NULL_PTR;
    VOS_CHAR                           *pcLocationStr   = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulReturnCodeIndex;
    VOS_UINT16                          usLength;

    /* ?????????????? */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvSsaLcsMolrNtf: WARNING:AT_BROADCAST_INDEX!");
        return;
    }

    pstLcsMolrNtf       = (TAF_SSA_LCS_MOLR_NTF_STRU *)pEvent;
    pstAgpsCtx          = AT_GetModemAgpsCtxAddrFromClientId(gastAtClientTab[ucIndex].usClientId);
    ulResult            = AT_ConvertTafSsaErrorCode(ucIndex, pstLcsMolrNtf->enResult);
    ulReturnCodeIndex   = 0;
    usLength            = 0;

    /* ???????????????????? */
    if (AT_OK == ulResult)
    {
        pcLocationStr = (VOS_CHAR*)PS_MEM_ALLOC(WUEPS_PID_AT, pstLcsMolrNtf->usLocationStrLen + 1);
        if (VOS_NULL_PTR == pcLocationStr)
        {
            AT_ERR_LOG("AT_RcvSsaLcsMolrNtf: Alloc Memory Failed!");
            return;
        }

        VOS_StrNCpy(pcLocationStr, pstLcsMolrNtf->acLocationStr, pstLcsMolrNtf->usLocationStrLen);
        pcLocationStr[pstLcsMolrNtf->usLocationStrLen] = '\0';

        if (TAF_SSA_LCS_MOLR_RPT_NMEA == pstLcsMolrNtf->enRptTypeChoice)
        {
            /* ????+CMOLRN???????? */
            usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                              (VOS_CHAR *)pgucAtSndCodeAddr,
                                              (VOS_CHAR *)pgucAtSndCodeAddr,
                                              "%s%s\"%s\"%s",
                                              gaucAtCrLf,
                                              gastAtStringTab[AT_STRING_CMOLRN].pucText,
                                              pcLocationStr,
                                              gaucAtCrLf);
        }
        else
        {
            /* ????+CMOLRG???????? */
            usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                              (VOS_CHAR *)pgucAtSndCodeAddr,
                                              (VOS_CHAR *)pgucAtSndCodeAddr,
                                              "%s%s%s%s",
                                              gaucAtCrLf,
                                              gastAtStringTab[AT_STRING_CMOLRG].pucText,
                                              pcLocationStr,
                                              gaucAtCrLf);
        }

        PS_MEM_FREE(WUEPS_PID_AT, pcLocationStr);
    }
    else
    {
        if (VOS_OK != AT_GetReturnCodeId(ulResult, &ulReturnCodeIndex))
        {
            AT_ERR_LOG("AT_RcvSsaLcsMolrNtf: result code index is err!");
            return;
        }

        /* ????+CMOLRE?????? */
        if (AT_CMOLRE_NUMERIC == pstAgpsCtx->enCmolreType)
        {
            usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                              (VOS_CHAR *)pgucAtSndCodeAddr,
                                              (VOS_CHAR *)pgucAtSndCodeAddr,
                                              "%s%s%s%s",
                                              gaucAtCrLf,
                                              gastAtStringTab[AT_STRING_CMOLRE].pucText,
                                              (VOS_CHAR *)gastAtReturnCodeTab[ulReturnCodeIndex].Result[0],
                                              gaucAtCrLf);
        }
        else
        {
            usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                              (VOS_CHAR *)pgucAtSndCodeAddr,
                                              (VOS_CHAR *)pgucAtSndCodeAddr,
                                              "%s%s%s%s",
                                              gaucAtCrLf,
                                              gastAtStringTab[AT_STRING_CMOLRE].pucText,
                                              (VOS_CHAR *)gastAtReturnCodeTab[ulReturnCodeIndex].Result[1],
                                              gaucAtCrLf);
        }
    }

    /* ??????????AT???? */
    At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);

    return;
}

/*****************************************************************************
 ?? ?? ??  : AT_SetCmolrePara
 ????????  : +CMOLRE????????????????
 ????????  : VOS_UINT8 ucIndex
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??9??9??
    ??    ??   : l00198894
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 AT_SetCmolrePara(VOS_UINT8 ucIndex)
{
    AT_MODEM_AGPS_CTX_STRU             *pstAgpsCtx = VOS_NULL_PTR;

    pstAgpsCtx = AT_GetModemAgpsCtxAddrFromClientId(gastAtClientTab[ucIndex].usClientId);

    /* ???????? */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        AT_WARN_LOG("AT_SetCmolrePara: Option Type Incrrect!");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ?????????????????? */
    if (1 < gucAtParaIndex)
    {
        AT_WARN_LOG("AT_SetCmolrePara: too many parameters!");
        return AT_TOO_MANY_PARA;
    }

    /* ???????????? */
    if (0 == gastAtParaList[0].usParaLen)
    {
        pstAgpsCtx->enCmolreType = AT_CMOLRE_NUMERIC;
    }
    else
    {
        pstAgpsCtx->enCmolreType = (VOS_UINT8)gastAtParaList[0].ulParaValue;
    }

    /* ????????OK */
    return AT_OK;
}

/*****************************************************************************
 ?? ?? ??  : AT_QryCmolrePara
 ????????  : +CMOLRE????????????????
 ????????  : VOS_UINT8 ucIndex
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??9??9??
    ??    ??   : l00198894
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 AT_QryCmolrePara(VOS_UINT8 ucIndex)
{
    AT_MODEM_AGPS_CTX_STRU             *pstAgpsCtx = VOS_NULL_PTR;

    pstAgpsCtx = AT_GetModemAgpsCtxAddrFromClientId(gastAtClientTab[ucIndex].usClientId);

    /* ???????????? */
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                "%s: %d",
                                g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                pstAgpsCtx->enCmolreType);

    /* ????????OK */
    return AT_OK;
}

/*****************************************************************************
 ?? ?? ??  : AT_SetCmtlrPara
 ????????  : +CMTLR????????????????
 ????????  : VOS_UINT8 ucIndex
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??9??9??
    ??    ??   : l00198894
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 AT_SetCmtlrPara(VOS_UINT8 ucIndex)
{
    TAF_SSA_LCS_MTLR_SUBSCRIBE_ENUM_UINT8   enSubscribe;

    /* ???????? */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        AT_WARN_LOG("AT_SetCmtlrPara: Option Type Incrrect!");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ?????????????????? */
    if (1 < gucAtParaIndex)
    {
        AT_WARN_LOG("AT_SetCmtlrPara: too many parameters!");
        return AT_TOO_MANY_PARA;
    }

    /* ???????????? */
    if (0 == gastAtParaList[0].usParaLen)
    {
        enSubscribe = TAF_SSA_LCS_MOLR_ENABLE_TYPE_DISABLE;
    }
    else
    {
        enSubscribe = (VOS_UINT8)gastAtParaList[0].ulParaValue;
    }
    TAF_SSA_SetCmtlrInfo(WUEPS_PID_AT,
                         gastAtClientTab[ucIndex].usClientId,
                         gastAtClientTab[ucIndex].opId,
                         enSubscribe);

    /* ???????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CMTLR_SET;

    /* ???????????????? */
    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 ?? ?? ??  : AT_RcvSsaSetLcsMtlrCnf
 ????????  : AT????????TAF??SSA??????????MTLR????????
 ????????  : VOS_UINT8                           ucIndex
             VOS_VOID                           *pEvent
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??10??20??
    ??    ??   : l00198894
    ????????   : ??????????

*****************************************************************************/
VOS_VOID AT_RcvSsaSetLcsMtlrCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvent
)
{
    TAF_SSA_SET_LCS_MTLR_CNF_STRU      *pstSetLcsMtlrCnf    = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;

    /* ?????????????? */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvSsaSetLcsMtlrCnf: WARNING:AT_BROADCAST_INDEX!");
        return;
    }

    /* ??????????????????????AT_CMD_CMTLR_SET */
    if (AT_CMD_CMTLR_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvSsaSetLcsMtlrCnf: WARNING:Not AT_CMD_CMTLR_SET!");
        return;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    pstSetLcsMtlrCnf    = (TAF_SSA_SET_LCS_MTLR_CNF_STRU *)pEvent;
    ulResult            = AT_ConvertTafSsaErrorCode(ucIndex, pstSetLcsMtlrCnf->enResult);

    if (AT_OK != ulResult)
    {
        AT_WARN_LOG("AT_RcvSsaSetLcsMtlrCnf: WARNING:Set ^CMTLR Failed!");
    }

    /* ???????? */
    gstAtSendData.usBufLen = 0;
    At_FormatResultData(ucIndex, ulResult);

    return;
}

/*****************************************************************************
 ?? ?? ??  : AT_QryCmtlrPara
 ????????  : +CMTLR????????????????
 ????????  : VOS_UINT8 ucIndex
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??9??9??
    ??    ??   : l00198894
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 AT_QryCmtlrPara(VOS_UINT8 ucIndex)
{
    /* ???????????? */
    TAF_SSA_GetCmtlrInfo(WUEPS_PID_AT,
                         gastAtClientTab[ucIndex].usClientId,
                         gastAtClientTab[ucIndex].opId);

    /* ???????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CMTLR_READ;

    /* ???????????????? */
    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 ?? ?? ??  : AT_RcvSsaGetLcsMtlrCnf
 ????????  : AT????????TAF??SSA??????????MTLR????????
 ????????  : VOS_UINT8                           ucIndex
             VOS_VOID                           *pEvent
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??10??19??
    ??    ??   : l00198894
    ????????   : ??????????

*****************************************************************************/
VOS_VOID AT_RcvSsaGetLcsMtlrCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvent
)
{
    TAF_SSA_GET_LCS_MTLR_CNF_STRU      *pstGetLcsMtlrCnf    = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;

    /* ?????????????? */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvSsaGetLcsMtlrCnf: WARNING:AT_BROADCAST_INDEX!");
        return;
    }

    /* ??????????????????????AT_CMD_CMTLR_READ */
    if (AT_CMD_CMTLR_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvSsaGetLcsMtlrCnf: WARNING:Not AT_CMD_CMTLR_READ!");
        return;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    pstGetLcsMtlrCnf    = (TAF_SSA_GET_LCS_MTLR_CNF_STRU *)pEvent;
    ulResult            = AT_ConvertTafSsaErrorCode(ucIndex, pstGetLcsMtlrCnf->enResult);
    usLength            = 0;

    /* ???????????????????? */
    if (AT_OK == ulResult)
    {
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          "%s: %d",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          pstGetLcsMtlrCnf->enSubscribe);
    }

    /* ???????? */
    gstAtSendData.usBufLen = usLength;
    At_FormatResultData(ucIndex, ulResult);

    return;
}

/*****************************************************************************
 ?? ?? ??  : AT_RcvSsaLcsMtlrNtf
 ????????  : AT????????TAF??SSA??????????MTLR????????????
 ????????  : VOS_UINT8                           ucIndex
             VOS_VOID                           *pEvent
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??10??20??
    ??    ??   : l00198894
    ????????   : ??????????

*****************************************************************************/
VOS_VOID AT_RcvSsaLcsMtlrNtf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvent
)
{
    TAF_SSA_LCS_MTLR_NTF_STRU          *pstLcsMtlrNtf   = VOS_NULL_PTR;
    VOS_UINT32                          ulTmpStrLen;
    VOS_UINT32                          i;
    VOS_UINT16                          usLength;

    /* ?????????????? */
    if (!AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvSsaLcsMtlrNtf: WARNING:Not AT_BROADCAST_INDEX!");
        return;
    }

    pstLcsMtlrNtf       = (TAF_SSA_LCS_MTLR_NTF_STRU *)pEvent;
    usLength            = 0;

    /* +CMTLR: <handle-id>,<notification-type>,<location-type>,
               [<client-external-id>],[<client-name>][,<plane>] */
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s%s%d,%d,%d,",
                                      gaucAtCrLf,
                                      gastAtStringTab[AT_STRING_CMTLR].pucText,
                                      pstLcsMtlrNtf->stMtlrPara.ucHandleId,
                                      pstLcsMtlrNtf->stMtlrPara.enNtfType,
                                      pstLcsMtlrNtf->stMtlrPara.enLocationType);

    if (VOS_TRUE == pstLcsMtlrNtf->stMtlrPara.bitOpClientExId)
    {
        ulTmpStrLen = pstLcsMtlrNtf->stMtlrPara.stClientExId.ucLength <= LCS_CLIENT_EXID_MAX_LEN ?
                        pstLcsMtlrNtf->stMtlrPara.stClientExId.ucLength : LCS_CLIENT_EXID_MAX_LEN;

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                  (VOS_CHAR *)pgucAtSndCodeAddr,
                                  (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                  "\"");

        for (i = 0; i < ulTmpStrLen; i++)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                      "%02X",
                                      pstLcsMtlrNtf->stMtlrPara.stClientExId.aucValue[i]);
        }

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                  (VOS_CHAR *)pgucAtSndCodeAddr,
                                  (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                  "\"");

    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                      ",");

    if (VOS_TRUE == pstLcsMtlrNtf->stMtlrPara.bitOpClientName)
    {
        ulTmpStrLen = pstLcsMtlrNtf->stMtlrPara.stClientName.ucLength <= LCS_CLIENT_NAME_MAX_LEN ?
                        pstLcsMtlrNtf->stMtlrPara.stClientName.ucLength : LCS_CLIENT_NAME_MAX_LEN;

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                  (VOS_CHAR *)pgucAtSndCodeAddr,
                                  (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                  "\"");

        for (i = 0; i < ulTmpStrLen; i++)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                      "%02X",
                                      pstLcsMtlrNtf->stMtlrPara.stClientName.aucValue[i]);
        }

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                  (VOS_CHAR *)pgucAtSndCodeAddr,
                                  (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                  "\"");
    }

    if (VOS_TRUE == pstLcsMtlrNtf->stMtlrPara.bitOpPlane)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          ",%d",
                                          pstLcsMtlrNtf->stMtlrPara.enPlane);
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                      "\r\n");

    /* ??????????AT???? */
    At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);

    return;
}

/*****************************************************************************
 ?? ?? ??  : AT_SetCmtlraPara
 ????????  : +CMTLRA????????????????
 ????????  : VOS_UINT8 ucIndex
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??9??9??
    ??    ??   : l00198894
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 AT_SetCmtlraPara(VOS_UINT8 ucIndex)
{
    TAF_SSA_LCS_MTLRA_PARA_SET_STRU     stCmtlraPara;

    /* ???????? */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        AT_WARN_LOG("AT_SetCmtlraPara: Option Type Incrrect!");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ???????????? */
    if (2 != gucAtParaIndex)
    {
        AT_WARN_LOG("AT_SetCmtlraPara: Incorrect Parameter Num!");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ???????????? */
    PS_MEM_SET(&stCmtlraPara, 0, sizeof(stCmtlraPara));
    stCmtlraPara.enAllow    = (VOS_UINT8)gastAtParaList[0].ulParaValue;
    stCmtlraPara.ucHandleId = (VOS_UINT8)gastAtParaList[1].ulParaValue;

    TAF_SSA_SetCmtlraInfo(WUEPS_PID_AT,
                          gastAtClientTab[ucIndex].usClientId,
                          gastAtClientTab[ucIndex].opId,
                          &stCmtlraPara);

    /* ???????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CMTLRA_SET;

    /* ???????????????? */
    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 ?? ?? ??  : AT_RcvSsaSetLcsMtlraCnf
 ????????  : AT????????TAF??SSA??????????MTLRA????????
 ????????  : VOS_UINT8                           ucIndex
             VOS_VOID                           *pEvent
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??10??20??
    ??    ??   : l00198894
    ????????   : ??????????

*****************************************************************************/
VOS_VOID AT_RcvSsaSetLcsMtlraCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvent
)
{
    TAF_SSA_SET_LCS_MTLRA_CNF_STRU     *pstSetLcsMtlraCnf    = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;

    /* ?????????????? */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvSsaSetLcsMtlraCnf: WARNING:AT_BROADCAST_INDEX!");
        return;
    }

    /* ??????????????????????AT_CMD_CMTLRA_SET */
    if (AT_CMD_CMTLRA_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvSsaSetLcsMtlraCnf: WARNING:Not AT_CMD_CMTLRA_SET!");
        return;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    pstSetLcsMtlraCnf   = (TAF_SSA_SET_LCS_MTLRA_CNF_STRU *)pEvent;
    ulResult            = AT_ConvertTafSsaErrorCode(ucIndex, pstSetLcsMtlraCnf->enResult);

    if (AT_OK != ulResult)
    {
        AT_WARN_LOG("AT_RcvSsaSetLcsMtlraCnf: WARNING:Set ^CMTLRA Failed!");
    }

    /* ???????? */
    gstAtSendData.usBufLen = 0;
    At_FormatResultData(ucIndex, ulResult);

    return;
}

/*****************************************************************************
 ?? ?? ??  : AT_QryCmtlraPara
 ????????  : +CMTLRA????????????????
 ????????  : VOS_UINT8 ucIndex
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??9??9??
    ??    ??   : l00198894
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 AT_QryCmtlraPara(VOS_UINT8 ucIndex)
{
    /* ???????????? */
    TAF_SSA_GetCmtlraInfo(WUEPS_PID_AT,
                          gastAtClientTab[ucIndex].usClientId,
                          gastAtClientTab[ucIndex].opId);

    /* ???????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CMTLRA_READ;

    /* ???????????????? */
    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 ?? ?? ??  : AT_RcvSsaGetLcsMtlraCnf
 ????????  : AT????????TAF??SSA??????????MTLRA????????
 ????????  : VOS_UINT8                           ucIndex
             VOS_VOID                           *pEvent
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??10??19??
    ??    ??   : l00198894
    ????????   : ??????????

*****************************************************************************/
VOS_VOID AT_RcvSsaGetLcsMtlraCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvent
)
{
    TAF_SSA_GET_LCS_MTLRA_CNF_STRU     *pstGetLcsMtlraCnf    = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;
    VOS_UINT8                           i;
    VOS_UINT8                           ucCnt;

    /* ?????????????? */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvSsaGetLcsMtlraCnf: WARNING:AT_BROADCAST_INDEX!");
        return;
    }

    /* ??????????????????????AT_CMD_CMTLRA_READ */
    if (AT_CMD_CMTLRA_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvSsaGetLcsMtlraCnf: WARNING:Not AT_CMD_CMTLRA_READ!");
        return;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    pstGetLcsMtlraCnf   = (TAF_SSA_GET_LCS_MTLRA_CNF_STRU *)pEvent;
    ulResult            = AT_ConvertTafSsaErrorCode(ucIndex, pstGetLcsMtlraCnf->enResult);
    usLength            = 0;

    /* ???????????????????? */
    if (AT_OK == ulResult)
    {
        ucCnt = (pstGetLcsMtlraCnf->ucCnt > TAF_SSA_LCS_MTLR_MAX_NUM) ?
                    TAF_SSA_LCS_MTLR_MAX_NUM : pstGetLcsMtlraCnf->ucCnt;
        for (i = 0;  i < ucCnt; i++)
        {
            if (0 != i)
            {
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   (VOS_CHAR *)gaucAtCrLf);
            }

            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s: %d,%d",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                               pstGetLcsMtlraCnf->aenAllow[i],
                                               pstGetLcsMtlraCnf->aucHandleId[i]);

        }
    }

    /* ???????? */
    gstAtSendData.usBufLen = usLength;
    At_FormatResultData(ucIndex, ulResult);

    return;
}

/*****************************************************************************
 ?? ?? ??  : AT_TestCmtlraPara
 ????????  : +CMTLRA????????????????
 ????????  : VOS_UINT8 ucIndex
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??9??9??
    ??    ??   : l00198894
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 AT_TestCmtlraPara(VOS_UINT8 ucIndex)
{
    /* ???????????????? */
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                "%s: (0,1)",
                                g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    return AT_OK;
}

/*****************************************************************************
 ?? ?? ??  : AT_RcvTafSsaEvt
 ????????  : AT????????TAF??SSA??????????????
 ????????  : TAF_SSA_EVT_STRU                   *pstEvent
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2015??10??19??
    ??    ??   : l00198894
    ????????   : ??????????

*****************************************************************************/
VOS_VOID AT_RcvTafSsaEvt(
    TAF_SSA_EVT_STRU                   *pstEvent
)
{
    MN_AT_IND_EVT_STRU                 *pMsg        = VOS_NULL_PTR;
    TAF_CTRL_STRU                      *pstCtrl     = VOS_NULL_PTR;
    AT_SS_EVT_FUNC                      pEvtFunc    = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          i;

    /* ??????????????????SSA???????? */
    if (0 != pstEvent->ulEvtExt)
    {
        pMsg = (MN_AT_IND_EVT_STRU *)pstEvent;
        At_SsMsgProc(pMsg->aucContent, pMsg->usLen);
        return;
    }

    /* ?????? */
    pstCtrl     = (TAF_CTRL_STRU*)(pstEvent->aucContent);

    if ( AT_FAILURE == At_ClientIdToUserId(pstCtrl->usClientId,
                                           &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvTafSsaEvt: At_ClientIdToUserId FAILURE");
        return;
    }

    /* ?????????????????????????? */
    for (i = 0; i < AT_ARRAY_SIZE(g_astAtSsEvtFuncTbl); i++)
    {
        if ( pstEvent->enEvtId == g_astAtSsEvtFuncTbl[i].enEvtId )
        {
            /* ????ID???? */
            pEvtFunc = g_astAtSsEvtFuncTbl[i].pEvtFunc;
            break;
        }
    }

    /* ?????????????????????? */
    if ( VOS_NULL_PTR != pEvtFunc )
    {
        pEvtFunc(ucIndex, pstEvent->aucContent);
    }
    else
    {
        AT_ERR_LOG1("AT_RcvTafSsaEvt: Unexpected event received! <EvtId>", pstEvent->enEvtId);
    }

    return;
}






