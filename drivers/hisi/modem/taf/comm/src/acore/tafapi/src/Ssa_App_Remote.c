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
#include "vos.h"
#include "Taf_Tafm_Remote.h"
#include "TafAppSsa.h"
#include "TafApi.h"


/* #include "Ssa_Define.h" */
/* #include "MnComm.h" */
/* #include "Taf_Common.h" */
#include "MnCommApi.h"



/*****************************************************************************
    ??????????????????????.C??????????
*****************************************************************************/
/*lint -e767 ??????:???? 107747;??????:??????65952;????:Log????*/
#define    THIS_FILE_ID        PS_FILE_ID_SSA_APP_REMOTE_C
/*lint +e767 ??????:???? 107747;??????:sunshaohua*/

/*****************************************************************************
 Prototype      : Taf_RegisterSSReq
 Description    : APP/AT????RegisterSS????????????????????????
 Input          : ClientId - APP/AT????
                  OpId     - ????????
                  pPara    - ????????
 Output         : --
 Return Value   : ????????
 Calls          : ---
 Called By      : --

 History        : ---
  1.Date        : 2005-10-15
    Author      : ---
    Modification: Created function
  2.Date        : 2007-10-16
    Author      : F62575
    Modification: ??????A32D13062(????????????????)
  3.Date        : 2013-5-17
    Author      : W000176964
    Modification: SS FDN&Call Control????:????????????PID??TAF
*****************************************************************************/
TAF_UINT32 TAF_RegisterSSReq ( MN_CLIENT_ID_T               ClientId,
                                       MN_OPERATION_ID_T           OpId,
                                       TAF_SS_REGISTERSS_REQ_STRU  *pPara)
{
    return MN_FillAndSndAppReqMsg( ClientId,
                                   OpId,
                                   TAF_MSG_REGISTERSS_MSG,
                                   pPara,
                                   sizeof(TAF_SS_REGISTERSS_REQ_STRU),
                                   I0_WUEPS_PID_TAF);
}


/*****************************************************************************
 Prototype      : Taf_EraseSSReq
 Description    : APP/AT????EraseSS????????????????????????
 Input          : ClientId - APP/AT????
                  OpId     - ????????
                  pPara    - ????????
 Output         : --
 Return Value   : ????????
 Calls          : ---
 Called By      : --

 History        : ---
  1.Date        : 2005-10-15
    Author      : ---
    Modification: Created function
  2.Date        : 2007-10-16
    Author      : F62575
    Modification: ??????A32D13062(????????????????)
  3.Date        : 2013-5-17
    Author      : W000176964
    Modification: SS FDN&Call Control????:????????????PID??TAF
*****************************************************************************/
TAF_UINT32 TAF_EraseSSReq ( MN_CLIENT_ID_T              ClientId,
                                    MN_OPERATION_ID_T          OpId,
                                    TAF_SS_ERASESS_REQ_STRU    *pPara)
{
    return MN_FillAndSndAppReqMsg( ClientId,
                               OpId,
                               TAF_MSG_ERASESS_MSG,
                               pPara,
                               sizeof(TAF_SS_ERASESS_REQ_STRU),
                               I0_WUEPS_PID_TAF);
}

/*****************************************************************************
 Prototype      : Taf_ActivateSSReq
 Description    : APP/AT????ActivateSS????????????????????????
 Input          : ClientId - APP/AT????
                  OpId     - ????????
                  pPara    - ????????
 Output         : --
 Return Value   : ????????
 Calls          : ---
 Called By      : --

 History        : ---
  1.Date        : 2005-10-15
    Author      : ---
    Modification: Created function
  2.Date        : 2007-10-16
    Author      : F62575
    Modification: ??????A32D13062(????????????????)
  3.Date        : 2013-5-17
    Author      : W000176964
    Modification: SS FDN&Call Control????:????????????PID??TAF
*****************************************************************************/
TAF_UINT32 TAF_ActivateSSReq(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    TAF_SS_ACTIVATESS_REQ_STRU         *pPara

)
{
    return MN_FillAndSndAppReqMsg( ClientId,
                                   OpId,
                                   TAF_MSG_ACTIVATESS_MSG,
                                   pPara,
                                   sizeof(TAF_SS_ACTIVATESS_REQ_STRU),
                                   I0_WUEPS_PID_TAF);
}

/*****************************************************************************
 Prototype      : TAF_DeativateSSReq
 Description    : APP/AT????DeactivateSS????????????????????????
 Input          : ClientId - APP/AT????
                  OpId     - ????????
                  pPara    - ????????
 Output         : --
 Return Value   : ????????
 Calls          : ---
 Called By      : --

 History        : ---
  1.Date        : 2005-10-15
    Author      : ---
    Modification: Created function
  2.Date        : 2007-10-16
    Author      : F62575
    Modification: ??????A32D13062(????????????????)
  3.Date        : 2007-11-07
    Author      : F62575
    Modification: ??????A32D13382(????????????????)
  4.Date        : 2013-5-17
    Author      : W000176964
    Modification: SS FDN&Call Control????:????????????PID??TAF
*****************************************************************************/
TAF_UINT32 TAF_DeactivateSSReq ( MN_CLIENT_ID_T                ClientId,
                                         MN_OPERATION_ID_T             OpId,
                                         TAF_SS_DEACTIVATESS_REQ_STRU  *pPara)
{
    return MN_FillAndSndAppReqMsg( ClientId,
                                   OpId,
                                   TAF_MSG_DEACTIVATESS_MSG,
                                   pPara,
                                   sizeof(TAF_SS_DEACTIVATESS_REQ_STRU),
                                   I0_WUEPS_PID_TAF);
}

/*****************************************************************************
 Prototype      : Taf_InterrogateSSReq
 Description    : APP/AT????InterrogateSS????????????????????????
 Input          : ClientId - APP/AT????
                  OpId     - ????????
                  pPara    - ????????
 Output         : --
 Return Value   : ????????
 Calls          : ---
 Called By      : --

 History        : ---
  1.Date        : 2005-10-15
    Author      : ---
    Modification: Created function
  2.Date        : 2007-10-16
    Author      : F62575
    Modification: ??????A32D13062(????????????????)
  3.Date        : 2013-5-17
    Author      : W000176964
    Modification: SS FDN&Call Control????:????????????PID??TAF
*****************************************************************************/
TAF_UINT32 TAF_InterrogateSSReq ( MN_CLIENT_ID_T                    ClientId,
                                           MN_OPERATION_ID_T               OpId,
                                           TAF_SS_INTERROGATESS_REQ_STRU   *pPara)
{
    return MN_FillAndSndAppReqMsg( ClientId,
                                   OpId,
                                   TAF_MSG_INTERROGATESS_MSG,
                                   pPara,
                                   sizeof(TAF_SS_INTERROGATESS_REQ_STRU),
                                   I0_WUEPS_PID_TAF);
}

/*****************************************************************************
 Prototype      : Taf_RegisterPasswordReq
 Description    : APP/AT????RegisterPassword????????????????????????
 Input          : ClientId - APP/AT????
                  OpId     - ????????
                  pPara    - ????????
 Output         : --
 Return Value   : ????????
 Calls          : ---
 Called By      : --

 History        : ---
  1.Date        : 2005-10-15
    Author      : ---
    Modification: Created function
  2.Date        : 2007-10-16
    Author      : F62575
    Modification: ??????A32D13062(????????????????)
  3.Date        : 2013-5-17
    Author      : W000176964
    Modification: SS FDN&Call Control????:????????????PID??TAF
*****************************************************************************/
TAF_UINT32 TAF_RegisterPasswordReq ( MN_CLIENT_ID_T           ClientId,
                                                MN_OPERATION_ID_T       OpId,
                                                TAF_SS_REGPWD_REQ_STRU  *pPara)
{
    return MN_FillAndSndAppReqMsg( ClientId,
                                   OpId,
                                   TAF_MSG_REGPWD_MSG,
                                   pPara,
                                   sizeof(TAF_SS_REGPWD_REQ_STRU),
                                   I0_WUEPS_PID_TAF);
}

/*****************************************************************************
 Prototype      : Taf_ProcessUnstructuredSSReq
 Description    : APP/AT????ProcessUntructuredSS????????????????????????
 Input          : ClientId - APP/AT????
                  OpId     - ????????
                  pPara    - ????????
 Output         : --
 Return Value   : ????????
 Calls          : ---
 Called By      : --

 History        : ---
  1.Date        : 2005-10-15
    Author      : ---
    Modification: Created function
  2.Date        : 2007-10-16
    Author      : F62575
    Modification: ??????A32D13062(????????????????)
  3.Date        : 2008-12-06
    Author      : s62952
    Modification: ??????AT2D07296
  4.Date        : 2013-5-17
    Author      : W000176964
    Modification: SS FDN&Call Control????:????????????PID??TAF
*****************************************************************************/
TAF_UINT32 TAF_ProcessUnstructuredSSReq ( MN_CLIENT_ID_T                   ClientId,
                                                        MN_OPERATION_ID_T              OpId,
                                                        TAF_SS_PROCESS_USS_REQ_STRU    *pPara)
{
    TAF_SS_PROCESS_USS_REQ_STRU    *pstSsReq;

    pstSsReq = pPara;

    if((TAF_SS_7bit_LANGUAGE_UNSPECIFIED == pstSsReq->DatacodingScheme)
        ||(TAF_SS_8bit == pstSsReq->DatacodingScheme)
        ||(TAF_SS_UCS2 == pstSsReq->DatacodingScheme)
        || (TAF_SS_7BIT_DATA_CODING == pstSsReq->DatacodingScheme))
    {
        return MN_FillAndSndAppReqMsg( ClientId,
                                   OpId,
                                   TAF_MSG_PROCESS_USS_MSG,
                                   pstSsReq,
                                   sizeof(TAF_SS_PROCESS_USS_REQ_STRU),
                                   I0_WUEPS_PID_TAF);
    }
    else
    {
        return TAF_FAILURE;
    }
}


/* Deleted by s00217060 for ????????AT??????????????C??, 2013-5-6, begin */
/* Deleted by s00217060 for ????????AT??????????????C??, 2013-5-6, end */


/*****************************************************************************
 Prototype      : Taf_EraseCCEntryReq
 Description    : APP/AT????EraseCCEntry-Request????????????????????????
 Input          : ClientId - APP/AT????
                  OpId     - ????????
                  pPara    - ????????
 Output         : --
 Return Value   : ????????
 Calls          : ---
 Called By      : --

 History        : ---
  1.Date        : 2005-10-15
    Author      : ---
    Modification: Created function
  2.Date        : 2013-5-17
    Author      : W000176964
    Modification: SS FDN&Call Control????:????????????PID??TAF
*****************************************************************************/
VOS_UINT32 TAF_EraseCCEntryReq(MN_CLIENT_ID_T            ClientId,
                                   MN_OPERATION_ID_T                OpId,
                                   TAF_SS_ERASECC_ENTRY_REQ_STRU   *pPara)
{
    return MN_FillAndSndAppReqMsg( ClientId,
                                   OpId,
                                   TAF_MSG_ERASECCENTRY_MSG,
                                   pPara,
                                   sizeof(TAF_SS_ERASECC_ENTRY_REQ_STRU),
                                   I0_WUEPS_PID_TAF);
}


/*****************************************************************************
 Prototype      : TAF_SsReleaseComplete
 Description    : APP/AT????ReleaseComplete????????????????????????????,??????????????????
 Input          : ClientId - APP/AT????
                  OpId     - ????????
                  pPara    - ????????
 Output         : --
 Return Value   : ????????
 Calls          : ---
 Called By      : --

 History        : ---
  1.Date        : 2005-10-15
    Author      : ---
    Modification: Created function
  2.Date        : 2007-10-16
    Author      : F62575
    Modification: ??????A32D13062(????????????????)
  3.Date        : 2013-5-17
    Author      : W000176964
    Modification: SS FDN&Call Control????:????????????PID??TAF
*****************************************************************************/
TAF_UINT32 TAF_SsReleaseComplete ( MN_CLIENT_ID_T      ClientId,
                                             MN_OPERATION_ID_T  OpId)
{
    return MN_FillAndSndAppReqMsg( ClientId,
                                   OpId,
                                   TAF_MSG_RLEASE_MSG,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_TAF);
}


