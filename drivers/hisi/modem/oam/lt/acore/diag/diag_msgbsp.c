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




#include <mdrv.h>
#include "diag_msgbsp.h"
#include "diag_debug.h"
#include "msp_diag_comm.h"
#include "diag_fs_proc.h"
#include "TafNvInterface.h"

#define    THIS_FILE_ID        MSP_FILE_ID_DIAG_MSGBSP_C


DIAG_BSP_PROC_FUN_STRU g_DiagBspFunc[] = {
    {diag_BspAxiMonDataConfig       ,DIAG_CMD_AXI_DATA_CONFIG   ,0},
    {diag_BspAxiMonConfig           ,DIAG_CMD_AXI_MON_CONFIG    ,0},
    {diag_BspAxiMonTerminate        ,DIAG_CMD_AXI_MON_TERMINATE ,0},
    {diag_BspAxiMonRegConfig        ,DIAG_CMD_AXI_REG_CONFIG    ,0},
    {diag_BspAxiMonDataCtrl         ,DIAG_CMD_AXI_DATA_CTRL     ,0},
    {diag_BspUtraceStart            ,DIAG_CMD_UTRACE_START      ,0},
    {diag_BspUtraceStop             ,DIAG_CMD_UTRACE_TERMINATE  ,0},
    {diag_BspLogProcEntry           ,DIAG_CMD_BSP_LOG_SET       ,0},
    {diag_BspSysviewProc            ,DIAG_CMD_BSP_SYSVIEW_SWT   ,0},
    {diag_BspSysviewProc            ,DIAG_CMD_BSP_CPU_SWT       ,0},
    {diag_FsQueryProc               ,DIAG_CMD_FS_QUERY_DIR      ,0},
    {diag_FsScanProc                ,DIAG_CMD_FS_SCAN_DIR       ,0},
    {diag_FsMkdirProc               ,DIAG_CMD_FS_MAKE_DIR       ,0},
    {diag_FsOpenProc                ,DIAG_CMD_FS_OPEN           ,0},
    {diag_FsImportProc              ,DIAG_CMD_FS_IMPORT         ,0},
    {diag_FsExportProc              ,DIAG_CMD_FS_EXPORT         ,0},
    {diag_FsDeleteProc              ,DIAG_CMD_FS_DELETE         ,0},
    {diag_FsSpaceProc               ,DIAG_CMD_FS_SPACE          ,0},
    {diag_NvRdProc                  ,DIAG_CMD_NV_RD             ,0},
    {diag_GetNvListProc             ,DIAG_CMD_GET_NV_LIST       ,0},
    {diag_NvWrProc                  ,DIAG_CMD_NV_WR             ,0},
    {diag_NvAuthProc                ,DIAG_CMD_NV_AUTH           ,0},
};



static VOS_UINT32 g_ulPrivilegeLevel = DIAG_LEVEL_NORMAL;

VOS_UINT32 g_aulNvAuthIdList[] =
{
    en_NV_Item_IMEI,
    en_NV_Item_USB_Enum_Status,
    en_NV_Item_CustomizeSimLockPlmnInfo,
    en_NV_Item_CardlockStatus,
    en_NV_Item_CustomizeSimLockMaxTimes,
    en_NV_Item_CustomizeService,
    en_NV_Item_PRODUCT_ID,
    en_NV_Item_PREVENT_TEST_IMSI_REG,
    en_NV_Item_AT_SHELL_OPEN_FLAG,
};

/*****************************************************************************
 Function Name   : NvRdProc
 Description     : ????????????????NvProcEntry??????????NV????
 Input           : pstReq ??????????
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.y00228784      2012-11-22  Draft Enact
    2.c64416         2014-11-18  ????????????????
    2.c00326366      2015-06-10  ????????NV??????????

*****************************************************************************/
VOS_UINT32 diag_NvRdProc(VOS_UINT8* pstReq)
{
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    DIAG_CMD_NV_QRY_REQ_STRU* pstNVQryReq = NULL;
    DIAG_CMD_NV_QRY_CNF_STRU* pstNVQryCnf = NULL;
    VOS_UINT32 ulNVLen = 0, i = 0;
    VOS_UINT32 ulTotalSize = 0, ulOffset = 0;
    VOS_UINT8 *pData;
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};
    DIAG_FRAME_INFO_STRU *pstDiagHead = NULL;

    pstDiagHead = (DIAG_FRAME_INFO_STRU*)(pstReq);

    stDiagInfo.ulMsgType = DIAG_MSG_TYPE_BSP;

    pstNVQryReq = (DIAG_CMD_NV_QRY_REQ_STRU*)(pstDiagHead->aucData + sizeof(MSP_DIAG_DATA_REQ_STRU));

    for(i = 0; i < pstNVQryReq->ulCount; i++)
    {
        /*????????ID????NV??????*/
        ret = NV_GetLength(pstNVQryReq->ulNVId[i], &ulNVLen);
        if(ERR_MSP_SUCCESS != ret)
        {
            diag_printf("[%s]:ulNVId=0x%x,ulNVLen=%d!\n",__FUNCTION__, pstNVQryReq->ulNVId[i], ulNVLen);
            return ERR_MSP_FAILURE;
        }

        ulTotalSize += ulNVLen + sizeof(VOS_UINT32) + sizeof(VOS_UINT32); /* NV??????????????(NVID??len????????????) */
    }

    /* DIAG_CMD_NV_QRY_CNF_STRU?????????? */
    ulTotalSize += (sizeof(DIAG_CMD_NV_QRY_CNF_STRU) - sizeof(VOS_UINT32) - sizeof(VOS_UINT32));

    pstNVQryCnf = VOS_MemAlloc(MSP_PID_DIAG_APP_AGENT, DYNAMIC_MEM_PT, ulTotalSize );

    if(NULL  == pstNVQryCnf)
    {
        diag_printf("[%s]:malloc error!\n",__FUNCTION__);
        return ERR_MSP_MALLOC_FAILUE;
    }

    pstNVQryCnf->ulModemid = pstNVQryReq->ulModemid;
    pstNVQryCnf->ulCount   = pstNVQryReq->ulCount;

    pData = (VOS_UINT8*)(&pstNVQryCnf->ulNVId);
    ulOffset = 0;

    for(i = 0; i < pstNVQryReq->ulCount; i++)
    {
        /*????????ID????NV??????*/
        ret = NV_GetLength(pstNVQryReq->ulNVId[i], &ulNVLen);
        if(ERR_MSP_SUCCESS != ret)
        {
            diag_printf("[%s]:ulNVId=0x%x,ulNVLen=%d!\n",__FUNCTION__, pstNVQryReq->ulNVId[i], ulNVLen);
            goto DIAG_ERROR;
        }

        *(VOS_UINT32*)(pData + ulOffset) = pstNVQryReq->ulNVId[i]; /* [false alarm]:????Fortify */
        ulOffset += sizeof(VOS_UINT32);

        *(VOS_UINT32*)(pData + ulOffset) = ulNVLen; /* [false alarm]:????Fortify */
        ulOffset += sizeof(VOS_UINT32);

        ret = NV_ReadEx(pstNVQryReq->ulModemid, pstNVQryReq->ulNVId[i], (pData + ulOffset), ulNVLen);
        if(ret != ERR_MSP_SUCCESS)
        {
            diag_printf("[%s]:NV READ ERR 0x%x,ulNVId=0x%x\n",__FUNCTION__, ret, pstNVQryReq->ulNVId[i]);
            goto DIAG_ERROR;
        }

        ulOffset += ulNVLen;
    }

    DIAG_MSG_COMMON_PROC(stDiagInfo, (*pstNVQryCnf), pstDiagHead);

    pstNVQryCnf->ulRc    = ret;

    ret = DIAG_MsgReport(&stDiagInfo, pstNVQryCnf, ulTotalSize);

    VOS_MemFree(MSP_PID_DIAG_APP_AGENT, pstNVQryCnf);

    return ret;

DIAG_ERROR:
    DIAG_MSG_COMMON_PROC(stDiagInfo, (*pstNVQryCnf), pstDiagHead);

    pstNVQryCnf->ulRc    = ERR_MSP_FAILURE;
    pstNVQryCnf->ulCount = 0;

    ret = DIAG_MsgReport(&stDiagInfo, pstNVQryCnf, sizeof(DIAG_CMD_NV_QRY_CNF_STRU));

    VOS_MemFree(MSP_PID_DIAG_APP_AGENT, pstNVQryCnf);

    return ret;
}


/*****************************************************************************
 Function Name   : diag_GetNvListProc
 Description     : HIMS????NV list??????????????
 Input           : pstReq ??????????
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.c00326366      2012-11-22  Draft Enact

*****************************************************************************/
VOS_UINT32 diag_GetNvListProc(VOS_UINT8* pstReq)
{
    VOS_UINT32 ret, ulNvNum, ulTotalLen;
    DIAG_CMD_NV_LIST_CNF_STRU* pstNVCnf = NULL;
    DIAG_CMD_NV_LIST_CNF_STRU stNVCnf = {0};
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};
    DIAG_FRAME_INFO_STRU *pstDiagHead;

    pstDiagHead = (DIAG_FRAME_INFO_STRU*)(pstReq);

    stDiagInfo.ulMsgType = DIAG_MSG_TYPE_BSP;

    ulNvNum = NV_GetNVIdListNum();
    if (0 == ulNvNum)
    {
        diag_printf("[%s]: ulNvNum=%d!\n",__FUNCTION__, ulNvNum);
        goto DIAG_ERROR;
    }

    /*APP_HEAD + Result + NV nums + NV ID/LEN lists*/
    ulTotalLen = sizeof(DIAG_CMD_NV_LIST_CNF_STRU) + (ulNvNum*sizeof(NV_LIST_INFO_STRU));

    pstNVCnf = (DIAG_CMD_NV_LIST_CNF_STRU*)VOS_MemAlloc(MSP_PID_DIAG_APP_AGENT, DYNAMIC_MEM_PT, ulTotalLen);

    if (VOS_NULL_PTR == pstNVCnf)
    {
        diag_printf("[%s]:malloc error!\n",__FUNCTION__);
        goto DIAG_ERROR;
    }

    /*????????NV????ID??????*/
    ret = NV_GetNVIdList(pstNVCnf->astNvList);
    if (NV_OK != ret)
    {
        VOS_MemFree(MSP_PID_DIAG_APP_AGENT, pstNVCnf);
        goto DIAG_ERROR;
    }

    DIAG_MSG_COMMON_PROC(stDiagInfo, (*pstNVCnf), pstDiagHead);

    pstNVCnf->ulCount    = ulNvNum;
    pstNVCnf->ulRc       = ERR_MSP_SUCCESS;

    ret = DIAG_MsgReport(&stDiagInfo, pstNVCnf, ulTotalLen);

    VOS_MemFree(MSP_PID_DIAG_APP_AGENT, pstNVCnf);

    return ret;

DIAG_ERROR:

    DIAG_MSG_COMMON_PROC(stDiagInfo, stNVCnf, pstDiagHead);

    stNVCnf.ulCount      = 0;
    stNVCnf.ulRc         = ERR_MSP_FAILURE;

    ret = DIAG_MsgReport(&stDiagInfo, &stNVCnf, sizeof(stNVCnf));

    return ret;
}

/*****************************************************************************
 Function Name   : diag_NvAuthProc
 Description     : ??????????????????
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.c00326366      2012-11-22  Draft Enact

*****************************************************************************/
VOS_VOID diag_InitAuthVariable(VOS_VOID)
{
    IMEI_STRU stIMEI;
    VOS_UINT8 aucDefaultIMEI[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    /*????IMEI??????????????????????*/
    if (NV_OK == NV_Read(en_NV_Item_IMEI, (VOS_VOID*)&stIMEI, sizeof(stIMEI)))
    {
        if (0 == VOS_MemCmp((VOS_CHAR*)aucDefaultIMEI, &stIMEI, sizeof(stIMEI)))
        {
            g_ulPrivilegeLevel = DIAG_LEVEL_ADVANCED;
        }
    }

    return;
}

/*****************************************************************************
 Function Name   : diag_NvAuthProc
 Description     : ??????NV??????????????????
 Input           : ulNvId
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.c00326366      2012-11-22  Draft Enact

*****************************************************************************/
VOS_UINT32 diag_IsAuthNv(VOS_UINT32 ulNvId)
{
    VOS_UINT32 i;

    for (i = 0; i < (sizeof(g_aulNvAuthIdList)/sizeof(VOS_UINT32)); i++)
    {
        if (ulNvId == g_aulNvAuthIdList[i])
        {
            if (DIAG_LEVEL_ADVANCED == g_ulPrivilegeLevel)
            {
                return VOS_YES;
            }
            return VOS_NO;
        }
    }

    return VOS_YES;
}


VOS_VOID diag_AuthNvCfg(MsgBlock* pMsgBlock)
{
    DIAG_BSP_NV_AUTH_STRU *pstMsg = (DIAG_BSP_NV_AUTH_STRU *)pMsgBlock;
    g_ulPrivilegeLevel = pstMsg->ulLevel;
}

/*****************************************************************************
 Function Name   : diag_NvWrProc
 Description     : ????????????????NvProcEntry??????????NV????
 Input           : pstReq ??????????
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.y00228784      2012-11-22  Draft Enact
    2.c64416         2014-11-18  ????????????????
    2.c00326366      2015-06-10  ????????NV????????????????????????C??????
                     ????C????????????: 1. ????NV??????????????????DIAG????????????
                                        2. NV????????????C??????????????C??????

*****************************************************************************/
VOS_UINT32 diag_NvWrProc(VOS_UINT8* pstReq)
{
    VOS_UINT32 ret;
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};
    DIAG_CMD_NV_WR_REQ_STRU* pstNVWRReq = NULL;
    DIAG_FRAME_INFO_STRU *pstDiagHead = NULL;
    DIAG_CMD_NV_WR_CNF_STRU stNVWRCnf = {0};
    VOS_UINT32 i = 0;
    VOS_UINT32 ulOffset = 0;
    VOS_UINT32 ulNvid, ulLen;
    VOS_UINT8 *pData;

    pstDiagHead = (DIAG_FRAME_INFO_STRU*)(pstReq);

    pstNVWRReq = (DIAG_CMD_NV_WR_REQ_STRU*)(pstDiagHead->aucData + sizeof(MSP_DIAG_DATA_REQ_STRU));

    stDiagInfo.ulMsgType = DIAG_MSG_TYPE_BSP;

    pData = (VOS_UINT8*)(&pstNVWRReq->ulNVId);

    for(i = 0; i < pstNVWRReq->ulCount; i++)
    {
        ulNvid    = *(VOS_UINT32*)(pData + ulOffset);
        ulOffset += sizeof(VOS_UINT32);

        ulLen     = *(VOS_UINT32*)(pData + ulOffset);
        ulOffset += sizeof(VOS_UINT32);

        if (VOS_YES != diag_IsAuthNv(ulNvid))
        {
            goto DIAG_ERROR2;
        }

        printk(KERN_ERR "NV Write ulNVId=0x%x\n", ulNvid);

        /*????NV??*/
        ret = NV_WriteEx(pstNVWRReq->ulModemid, ulNvid, (pData + ulOffset), ulLen);
        if(ret != ERR_MSP_SUCCESS)
        {
           printk(KERN_ERR "[%s]:NV Write ERR 0x%x,ulNVId=0x%x\n",__FUNCTION__, ret, ulNvid);
           goto DIAG_ERROR2;
        }
        ulOffset += ulLen;
    }

    DIAG_MSG_COMMON_PROC(stDiagInfo, stNVWRCnf, pstDiagHead);

    stNVWRCnf.ulModemid  = pstNVWRReq->ulModemid;
    stNVWRCnf.ulRc       = ret;

    ret = DIAG_MsgReport(&stDiagInfo, &stNVWRCnf, sizeof(stNVWRCnf));

    return ret;

DIAG_ERROR2:

    DIAG_MSG_COMMON_PROC(stDiagInfo, stNVWRCnf, pstDiagHead);

    stNVWRCnf.ulModemid  = pstNVWRReq->ulModemid;
    stNVWRCnf.ulRc       = ERR_MSP_FAILURE;

    ret = DIAG_MsgReport(&stDiagInfo, &stNVWRCnf, sizeof(stNVWRCnf));

    return ret;
}


/*****************************************************************************
 Function Name   : diag_NvAuthProc
 Description     : HIMS????NV??????????????????
 Input           : pstReq ??????????
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.c00326366      2012-11-22  Draft Enact

*****************************************************************************/
VOS_UINT32 diag_NvAuthProc(VOS_UINT8* pstReq)
{
    VOS_UINT32 ulRet;
    MSP_DIAG_CNF_INFO_STRU     stDiagInfo = {0};
    DIAG_FRAME_INFO_STRU *pstDiagHead;

    VOS_UINT32 ulLen;
    DIAG_BSP_MSG_A_TRANS_C_STRU *pstInfo;
    DIAG_BSP_COMM_CNF_STRU stCommCnf;

    pstDiagHead = (DIAG_FRAME_INFO_STRU*)(pstReq);

    stDiagInfo.ulMsgType = DIAG_MSG_TYPE_BSP;

    DIAG_MSG_BSP_ACORE_CFG_PROC(ulLen, pstDiagHead, pstInfo, ulRet);

    return ulRet;

DIAG_ERROR:
    stCommCnf.ulRet = ulRet;
    DIAG_MSG_COMMON_PROC(stDiagInfo, stCommCnf, pstDiagHead);

    ulRet = DIAG_MsgReport(&stDiagInfo, &stCommCnf, sizeof(DIAG_BSP_COMM_CNF_STRU));

    return ulRet;

}


/*****************************************************************************
 Function Name   : diag_BspAxiMonDataConfig
 Description     : ????????????AXI Monitor????????????????
 Input           : pstReq ??????????
                   		ulCmdId ????ID
 Output          : None
 Return          : VOS_UINT32

 History         :

*****************************************************************************/
VOS_UINT32 diag_BspAxiMonDataConfig(VOS_UINT8* pstReq)
{
    VOS_UINT32  ulRet = ERR_MSP_SUCCESS;

    VOS_UINT32 ulLen;
    DIAG_BSP_MSG_A_TRANS_C_STRU *pstInfo;
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};
    DIAG_BSP_COMM_CNF_STRU stAxiCnf;

    DIAG_FRAME_INFO_STRU *pData;
    pData = (DIAG_FRAME_INFO_STRU *)pstReq;


    DIAG_MSG_BSP_ACORE_CFG_PROC(ulLen, pData, pstInfo, ulRet);

    return ulRet;

DIAG_ERROR:
    stAxiCnf.ulRet = ulRet;
    DIAG_MSG_COMMON_PROC(stDiagInfo,stAxiCnf,pData);

    ulRet = DIAG_MsgReport(&stDiagInfo,&stAxiCnf, sizeof(DIAG_BSP_COMM_CNF_STRU));

    return ulRet;



}

/*****************************************************************************
 Function Name   : diag_BspAxiMonConfig
 Description     : ????????????AXI Monitor????????????????
 Input           : pstReq ??????????
                   ulCmdId ????ID
 Output          : None
 Return          : VOS_UINT32

 History         :

*****************************************************************************/
VOS_UINT32 diag_BspAxiMonConfig(VOS_UINT8* pstReq)
{
    VOS_UINT32  ulRet = ERR_MSP_SUCCESS;

    VOS_UINT32 ulLen;
    DIAG_BSP_MSG_A_TRANS_C_STRU *pstInfo;
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};
    DIAG_BSP_COMM_CNF_STRU stAxiCnf;

    DIAG_FRAME_INFO_STRU *pData;
    pData = (DIAG_FRAME_INFO_STRU *)pstReq;

    DIAG_MSG_BSP_ACORE_CFG_PROC(ulLen, pData, pstInfo, ulRet);

    return ulRet;

DIAG_ERROR:
    stAxiCnf.ulRet = ulRet;
    DIAG_MSG_COMMON_PROC(stDiagInfo,stAxiCnf,pData);

    ulRet = DIAG_MsgReport(&stDiagInfo,&stAxiCnf, sizeof(DIAG_BSP_COMM_CNF_STRU));

    return ulRet;

}

/*****************************************************************************
 Function Name   : diag_BspAxiMonTerminate
 Description     : ????????????AXI Monitor????????????????
 Input           : pstReq ??????????
                   ulCmdId ????ID
 Output          : None
 Return          : VOS_UINT32

 History         :

*****************************************************************************/
VOS_UINT32 diag_BspAxiMonTerminate(VOS_UINT8* pstReq)
{
    VOS_UINT32 ulRet = ERR_MSP_SUCCESS;
    DIAG_FRAME_INFO_STRU *pData;

    VOS_UINT32 ulLen;
    DIAG_BSP_MSG_A_TRANS_C_STRU *pstInfo;
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};
    DIAG_BSP_COMM_CNF_STRU stAxiCnf;

    pData = (DIAG_FRAME_INFO_STRU *)pstReq;

    DIAG_MSG_BSP_ACORE_CFG_PROC(ulLen, pData, pstInfo, ulRet);

    return ulRet;

DIAG_ERROR:
    stAxiCnf.ulRet = ulRet;
    DIAG_MSG_COMMON_PROC(stDiagInfo,stAxiCnf,pData);

    ulRet = DIAG_MsgReport(&stDiagInfo,&stAxiCnf, sizeof(DIAG_BSP_COMM_CNF_STRU));

    return ulRet;

}

/*****************************************************************************
 Function Name   : diag_BspAxiMonRegConfig
 Description     : AXI Monitor??????????????????
 Input           : pstReq ??????????
                   ulCmdId ????ID
 Output          : None
 Return          : VOS_UINT32

 History         :

*****************************************************************************/
VOS_UINT32 diag_BspAxiMonRegConfig(VOS_UINT8* pstReq)
{
    VOS_UINT32 ulRet = ERR_MSP_SUCCESS;
    DIAG_FRAME_INFO_STRU *pData;

    VOS_UINT32 ulLen;
    DIAG_BSP_MSG_A_TRANS_C_STRU *pstInfo;
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};
    DIAG_BSP_COMM_CNF_STRU stAxiCnf;

    pData = (DIAG_FRAME_INFO_STRU *)pstReq;


    DIAG_MSG_BSP_ACORE_CFG_PROC(ulLen, pData, pstInfo, ulRet);

    return ulRet;

DIAG_ERROR:
    stAxiCnf.ulRet = ulRet;
    DIAG_MSG_COMMON_PROC(stDiagInfo,stAxiCnf,pData);

    ulRet = DIAG_MsgReport(&stDiagInfo,&stAxiCnf, sizeof(DIAG_BSP_COMM_CNF_STRU));

    return ulRet;

}

/*****************************************************************************
 Function Name   : diag_BspAxiMonDataCtrl
 Description     : AXI Monitor????????????????:????????????????
 Input           : pstReq ??????????
                   ulCmdId ????ID
 Output          : None
 Return          : VOS_UINT32

 History         :

*****************************************************************************/
VOS_UINT32 diag_BspAxiMonDataCtrl(VOS_UINT8* pstReq)
{
    VOS_UINT32 ulRet = ERR_MSP_SUCCESS;
    DIAG_FRAME_INFO_STRU *pData;

    VOS_UINT32 ulLen;
    DIAG_BSP_MSG_A_TRANS_C_STRU *pstInfo;
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};
    DIAG_BSP_COMM_CNF_STRU stAxiCnf;

    pData = (DIAG_FRAME_INFO_STRU *)pstReq;


    DIAG_MSG_BSP_ACORE_CFG_PROC(ulLen, pData, pstInfo, ulRet);

    return ulRet;

DIAG_ERROR:
    stAxiCnf.ulRet = ulRet;
    DIAG_MSG_COMMON_PROC(stDiagInfo,stAxiCnf,pData);

    ulRet = DIAG_MsgReport(&stDiagInfo,&stAxiCnf, sizeof(DIAG_BSP_COMM_CNF_STRU));

    return ulRet;

}

/*****************************************************************************
 Function Name   : diag_BspAxiMonStart
 Description     : AXI Monitor????????????
 Input           : pstReq ??????????
                   ulCmdId ????ID
 Output          : None
 Return          : VOS_UINT32

 History         :

*****************************************************************************/
VOS_UINT32 diag_BspAxiMonStart(VOS_UINT8* pstReq)
{
    VOS_UINT32 ulRet = ERR_MSP_SUCCESS;
    DIAG_FRAME_INFO_STRU *pData;

    VOS_UINT32 ulLen;
    DIAG_BSP_MSG_A_TRANS_C_STRU *pstInfo;
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};
    DIAG_BSP_COMM_CNF_STRU stAxiCnf;
    pData = (DIAG_FRAME_INFO_STRU *)pstReq;

    DIAG_MSG_BSP_ACORE_CFG_PROC(ulLen, pData, pstInfo, ulRet);

    return ulRet;

DIAG_ERROR:
    stAxiCnf.ulRet = ulRet;
    DIAG_MSG_COMMON_PROC(stDiagInfo,stAxiCnf,pData);

    ulRet = DIAG_MsgReport(&stDiagInfo,&stAxiCnf, sizeof(DIAG_BSP_COMM_CNF_STRU));

    return ulRet;

}

/*****************************************************************************
 Function Name   : diag_BspUtraceStart
 Description     : USB Trace????????????
 Input           :VOS_UINT8* pstReq
                VOS_UINT32 ulCmdId
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2013-3-5  Draft Enact

*****************************************************************************/
VOS_UINT32 diag_BspUtraceStart(VOS_UINT8* pstReq)
{
    VOS_UINT32 ulRet = ERR_MSP_SUCCESS;
	DIAG_BSP_COMM_CNF_STRU stUtraceCnf ={0};
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};
    DIAG_FRAME_INFO_STRU *pData;
    pData = (DIAG_FRAME_INFO_STRU *)pstReq;


	stUtraceCnf.ulRet = 0;//DRV_UTRACE_START(((VOS_UINT8*)(pData->aucData)+sizeof(MSP_DIAG_DATA_REQ_STRU)));


    DIAG_MSG_COMMON_PROC(stDiagInfo,stUtraceCnf,pData);


    ulRet = DIAG_MsgReport(&stDiagInfo,&stUtraceCnf, sizeof(DIAG_BSP_COMM_CNF_STRU));
    return ulRet;
}

/*****************************************************************************
 Function Name   : diag_BspUtraceStop
 Description     : USB Trace????????????
 Input           :VOS_UINT8* pstReq
                VOS_UINT32 ulCmdId
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2013-3-5  Draft Enact

*****************************************************************************/
VOS_UINT32 diag_BspUtraceStop(VOS_UINT8* pstReq)
{
    VOS_UINT32 ulRet = ERR_MSP_SUCCESS;
	DIAG_BSP_COMM_CNF_STRU stUtraceCnf ={0};
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};
    DIAG_FRAME_INFO_STRU *pData;
    pData = (DIAG_FRAME_INFO_STRU *)pstReq;


	stUtraceCnf.ulRet = 0;//DRV_UTRACE_TERMINATE(((VOS_UINT8*)(pData->aucData)+sizeof(MSP_DIAG_DATA_REQ_STRU)));

    DIAG_MSG_COMMON_PROC(stDiagInfo,stUtraceCnf,pData);

    ulRet = DIAG_MsgReport(&stDiagInfo,&stUtraceCnf, sizeof(DIAG_BSP_COMM_CNF_STRU));
    return ulRet;
}


/*****************************************************************************
 Function Name   : diag_BspLogProcEntry
 Description     : ????????????DIAG FW????????BSP??????????????????
 Input           : pstReq ??????????
                   		ulCmdId ????ID
 Output          : None
 Return          : VOS_UINT32

 History         :

*****************************************************************************/
VOS_UINT32 diag_BspLogProcEntry(VOS_UINT8* pstReq)
{
    DIAG_BSP_COMM_CNF_STRU  stLogSetCnf  = {0};
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};
    VOS_UINT32 ulRet = ERR_MSP_SUCCESS;
    DIAG_FRAME_INFO_STRU *pData;
    VOS_UINT32 ulLen;
    DIAG_BSP_MSG_A_TRANS_C_STRU *pstInfo;

    pData = (DIAG_FRAME_INFO_STRU *)pstReq;

    stLogSetCnf.ulRet = ulRet;
    DIAG_MSG_BSP_ACORE_CFG_PROC(ulLen, pData, pstInfo, ulRet);
    return ulRet;
DIAG_ERROR:


    DIAG_MSG_COMMON_PROC(stDiagInfo,stLogSetCnf,pData);

    //TODO:
    stLogSetCnf.ulRet = ulRet;

    ulRet = DIAG_MsgReport(&stDiagInfo,&stLogSetCnf, sizeof(DIAG_BSP_COMM_CNF_STRU));

	return ulRet;

}

/*****************************************************************************
 Function Name   : diag_BspSysviewProc
 Description     :
 Input           : pstReq ??????????
                   		ulCmdId ????ID
 Output          : None
 Return          : VOS_UINT32

 History         :

*****************************************************************************/
VOS_UINT32 diag_BspSysviewProc(VOS_UINT8* pstReq)
{
    VOS_UINT32  ulRet = ERR_MSP_SUCCESS;
    VOS_UINT32 ulLen;
    DIAG_BSP_MSG_A_TRANS_C_STRU *pstInfo;

    DIAG_FRAME_INFO_STRU *pData;
    pData = (DIAG_FRAME_INFO_STRU *)pstReq;

    //TODO:

    DIAG_MSG_BSP_ACORE_CFG_PROC(ulLen, pData, pstInfo, ulRet);
    return ulRet;
DIAG_ERROR:
    return ulRet;
    return ulRet;
}


/*****************************************************************************
 Function Name   : diag_BspMsgProc
 Description     : bsp????????????????????????
 Input           : None
 Output          : None
 Return          : None
 History         :

*****************************************************************************/
VOS_UINT32 diag_BspMsgProc(DIAG_FRAME_INFO_STRU *pData)
{
    VOS_UINT32 ulRet = ERR_MSP_INVALID_PARAMETER ;
    VOS_UINT32 i = 0;
    if(DIAG_MSG_TYPE_BSP != pData->stID.pri4b)
    {
        diag_printf("%s Rcv Error Msg Id 0x%x\n",__FUNCTION__,pData->ulCmdId);
        return ulRet;
    }

    for(i = 0; i< sizeof(g_DiagBspFunc)/sizeof(g_DiagBspFunc[0]);i++)
    {
        if(g_DiagBspFunc[i].ulCmdId == pData->ulCmdId)
        {
            g_DiagBspFunc[i].ulReserve ++;
            ulRet = g_DiagBspFunc[i].pFunc((VOS_UINT8*)pData);
            return ulRet;
        }
    }

    return ulRet;
}

VOS_VOID diag_BspShowDebugInfo(VOS_VOID)
{
    VOS_UINT32 i = 0;

    for(i=0;i<sizeof(g_DiagBspFunc)/sizeof(DIAG_BSP_PROC_FUN_STRU);i++)
    {
        diag_printf("Command ID :0x%x ,Ops Num %d\n",g_DiagBspFunc[i].ulCmdId,g_DiagBspFunc[i].ulReserve);
    }
}

/*****************************************************************************
 Function Name   : diag_BspMsgInit
 Description     : MSP dsp??????????
 Input           : None
 Output          : None
 Return          : None
 History         :

*****************************************************************************/
VOS_VOID diag_BspMsgInit(VOS_VOID)
{
    /*????message????????*/
    DIAG_MsgProcReg(DIAG_MSG_TYPE_BSP,diag_BspMsgProc);
}




