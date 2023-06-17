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
#include "PsTypeDef.h"
#include "vos.h"
#include "PsCommonDef.h"
#include "AppVcomDev.h"
#include "AtTypeDef.h"
#include "AtMntn.h"




/*****************************************************************************
    ??????????????????????.C??????????
*****************************************************************************/
/*lint -e767 */
#define    THIS_FILE_ID        PS_FILE_ID_APP_VCOM_DEV_C
/*lint -e767 */

/*****************************************************************************
   2 ????????????
*****************************************************************************/

/* VCOM CTX,????????VCOM??????????*/
APP_VCOM_DEV_CTX_STRU                   g_astVcomCtx[APP_VCOM_MAX_NUM];

APP_VCOM_DEBUG_INFO_STRU                g_stAppVcomDebugInfo;



/* ???????????????????? */
static const struct file_operations     g_stOperations_Fops =
{
    .owner = THIS_MODULE,
    .read  = APP_VCOM_Read,
    .poll  = APP_VCOM_Poll,
    .write = APP_VCOM_Write,
    .open  = APP_VCOM_Open,
    .release = APP_VCOM_Release,
};


/* APPVCOM????????????
APPVCOM ID   ????????  ????           ????AT??CLIENT    ModemId
APPVCOM        4K      RIL(??)               ??         MODEM0
APPVCOM1       4K      RIL(????)             ??         MODEM0
APPVCOM2       4K      ????????              ??         MODEM0
APPVCOM3       8K      ????????(AT SERVER)   ??         MODEM0
APPVCOM4       4K      audio RIL             ??         MODEM0
APPVCOM5       4K      RIL(??)               ??         MODEM1
APPVCOM6       4K      RIL(????)             ??         MODEM1
APPVCOM7       8K      ????????(AT SERVER)   ??         MODEM1
APPVCOM8       4K      ????????/HIDP         ??         MODEM1
APPVCOM9       4K      AGPS                  ??         MODEM0
APPVCOM10      4K      NFC/BIP               ??         MODEM0
APPVCOM11      4K      ISDB                  ??         MODEM0
APPVCOM12      4K      AGPS                  ??         MODEM1
APPVCOM13      4K      RIL(????)             ??         MODEM0
APPVCOM14      4K      RIL(????)             ??         MODEM1
APPVCOM15      4K      NFC                   ??         MODEM1
APPVCOM16      4K      HIDP                  ??         MODEM0
APPVCOM17      4K      AGPS-AP               ??         MODEM0
APPVCOM18      4K      ????                  ??         MODEM0
APPVCOM19      4K      ????                  ??         MODEM0
APPVCOM20      4K      RIL(??)               ??         MODEM2
APPVCOM21      4K      RIL(????)             ??         MODEM2
APPVCOM22      4K      ????????              ??         MODEM2
APPVCOM23      8K      ????????(AT SERVER)   ??         MODEM2
APPVCOM24      4K      AGPS                  ??         MODEM2
APPVCOM25      4K      NFC                   ??         MODEM2
APPVCOM26      4K      RIL(????)             ??         MODEM2
APPVCOM27      2M      CBT                   ??         MODEM0
APPVCOM28      4K      T/L????               ??
APPVCOM29      16K     errlog                ??
APPVCOM30      2M      log 3.5               ??
APPVCOM31      2M      log 3.5               ??
*/
const APP_VCOM_DEV_CONFIG_STRU g_astAppVcomCogfigTab[] =
{
    {APP_VCOM_DEV_NAME_0, APP_VCOM_SEM_NAME_0, 0x1000, 0},                      /* APPVCOM */
    {APP_VCOM_DEV_NAME_1, APP_VCOM_SEM_NAME_1, 0x1000, 0},                      /* APPVCOM1 */
    {APP_VCOM_DEV_NAME_2, APP_VCOM_SEM_NAME_2, 0x1000, 0},                      /* APPVCOM2 */
    {APP_VCOM_DEV_NAME_3, APP_VCOM_SEM_NAME_3, 0x2000, 0},                      /* APPVCOM3 */
    {APP_VCOM_DEV_NAME_4, APP_VCOM_SEM_NAME_4, 0x1000, 0},                      /* APPVCOM4 */
    {APP_VCOM_DEV_NAME_5, APP_VCOM_SEM_NAME_5, 0x1000, 0},                      /* APPVCOM5 */
    {APP_VCOM_DEV_NAME_6, APP_VCOM_SEM_NAME_6, 0x1000, 0},                      /* APPVCOM6 */
    {APP_VCOM_DEV_NAME_7, APP_VCOM_SEM_NAME_7, 0x2000, 0},                      /* APPVCOM7 */
    {APP_VCOM_DEV_NAME_8, APP_VCOM_SEM_NAME_8, 0x1000, 0},                      /* APPVCOM8 */
    {APP_VCOM_DEV_NAME_9, APP_VCOM_SEM_NAME_9, 0x5000, 0},                      /* APPVCOM9 */
    {APP_VCOM_DEV_NAME_10, APP_VCOM_SEM_NAME_10, 0x1000, 0},                    /* APPVCOM10 */
    {APP_VCOM_DEV_NAME_11, APP_VCOM_SEM_NAME_11, 0x1000, 0},                    /* APPVCOM11 */
    {APP_VCOM_DEV_NAME_12, APP_VCOM_SEM_NAME_12, 0x1000, 0},                    /* APPVCOM12 */
    {APP_VCOM_DEV_NAME_13, APP_VCOM_SEM_NAME_13, 0x1000, 0},                    /* APPVCOM13 */
    {APP_VCOM_DEV_NAME_14, APP_VCOM_SEM_NAME_14, 0x1000, 0},                    /* APPVCOM14 */
    {APP_VCOM_DEV_NAME_15, APP_VCOM_SEM_NAME_15, 0x1000, 0},                    /* APPVCOM15 */
    {APP_VCOM_DEV_NAME_16, APP_VCOM_SEM_NAME_16, 0x1000, 0},                    /* APPVCOM16 */
    {APP_VCOM_DEV_NAME_17, APP_VCOM_SEM_NAME_17, 0x1000, 0},                    /* APPVCOM17 */
    {APP_VCOM_DEV_NAME_18, APP_VCOM_SEM_NAME_18, 0x1000, 0},                    /* APPVCOM18 */
    {APP_VCOM_DEV_NAME_19, APP_VCOM_SEM_NAME_19, 0x1000, 0},                    /* APPVCOM19 */
    {APP_VCOM_DEV_NAME_20, APP_VCOM_SEM_NAME_20, 0x1000, 0},                    /* APPVCOM20 */
    {APP_VCOM_DEV_NAME_21, APP_VCOM_SEM_NAME_21, 0x1000, 0},                    /* APPVCOM21 */
    {APP_VCOM_DEV_NAME_22, APP_VCOM_SEM_NAME_22, 0x1000, 0},                    /* APPVCOM22 */
    {APP_VCOM_DEV_NAME_23, APP_VCOM_SEM_NAME_23, 0x2000, 0},                    /* APPVCOM23 */
    {APP_VCOM_DEV_NAME_24, APP_VCOM_SEM_NAME_24, 0x1000, 0},                    /* APPVCOM24 */
    {APP_VCOM_DEV_NAME_25, APP_VCOM_SEM_NAME_25, 0x1000, 0},                    /* APPVCOM25 */
    {APP_VCOM_DEV_NAME_26, APP_VCOM_SEM_NAME_26, 0x1000, 0},                    /* APPVCOM26 */
    {APP_VCOM_DEV_NAME_27, APP_VCOM_SEM_NAME_27, 0x200000, 0},                  /* APPVCOM27 */
    {APP_VCOM_DEV_NAME_28, APP_VCOM_SEM_NAME_28, 0x1000, 0},                    /* APPVCOM28 */
    {APP_VCOM_DEV_NAME_29, APP_VCOM_SEM_NAME_29, 0x8000, 0},                    /* APPVCOM29 */
    {APP_VCOM_DEV_NAME_30, APP_VCOM_SEM_NAME_30, 0x200000, 0},                  /* APPVCOM30 */
    {APP_VCOM_DEV_NAME_31, APP_VCOM_SEM_NAME_31, 0x200000, 0}                   /* APPVCOM31 */
};

APP_VCOM_DEBUG_CFG_STRU              g_stAppVcomDebugCfg;

/*****************************************************************************
   3 ??????????????
*****************************************************************************/

/*****************************************************************************
   4 ????????
*****************************************************************************/
/*****************************************************************************
 ?? ?? ??  : APP_VCOM_GetVcomCtxAddr
 ????????  : ??????????????????????
 ????????  : VOS_UINT8 ucIndex
 ????????  : ??
 ?? ?? ??  : APP_VCOM_DEV_CTX_STRU*
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2012??12??5??
    ??    ??   : z00220246
    ????????   : ??????????

*****************************************************************************/
APP_VCOM_DEV_CTX_STRU* APP_VCOM_GetVcomCtxAddr(VOS_UINT8 ucIndex)
{
    return &(g_astVcomCtx[ucIndex]);
}

/*****************************************************************************
 ?? ?? ??  : APP_VCOM_GetAppVcomDevEntity
 ????????  : ????????VCOM??????????????
 ????????  : VOS_UINT8 ucIndex
 ????????  :
 ?? ?? ??  : ????????VCOM??????????
 ????????  :
 ????????  :

 ????????     :
 1.??    ??   : 2012??12??03??
   ??    ??   : z00220246
   ????????   : ??????????

*****************************************************************************/
APP_VCOM_DEV_ENTITY_STRU* APP_VCOM_GetAppVcomDevEntity(VOS_UINT8 ucIndex)
{
    return (g_astVcomCtx[ucIndex].pstAppVcomDevEntity);
}

/*****************************************************************************
 ?? ?? ??  : APP_VCOM_RegDataCallback
 ????????  : VCOM??????????????????AT??????????????????AT????????????????
 ????????  : VOS_UINT8  ucDevIndex,    SEND_UL_AT_FUNC pFunc
 ????????  : ??
 ?? ?? ??  : VOS_UINT32

 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2012??11??23??
    ??    ??   : z00220246
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 APP_VCOM_RegDataCallback(VOS_UINT8 ucDevIndex, SEND_UL_AT_FUNC pFunc)
{
    APP_VCOM_DEV_CTX_STRU              *pstVcomCtx;

    /* ??????????*/
    if (ucDevIndex >= APP_VCOM_DEV_INDEX_BUTT)
    {
        return VOS_ERR;
    }

    pstVcomCtx = APP_VCOM_GetVcomCtxAddr(ucDevIndex);

    /* ????????????????????*/
    pstVcomCtx->pSendUlAtFunc = pFunc;

    return VOS_OK;
}

/*****************************************************************************
 ?? ?? ??  : APP_VCOM_RegEvtCallback
 ????????  : VCOM????????????????????????????????????????
 ????????  : VOS_UINT8  ucDevIndex,    EVENT_FUNC pFunc
 ????????  : ??
 ?? ?? ??  : VOS_UINT32

 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2012??11??23??
    ??    ??   : z00220246
    ????????   : ??????????

*****************************************************************************/
VOS_UINT32 APP_VCOM_RegEvtCallback(VOS_UINT8 ucDevIndex, EVENT_FUNC pFunc)
{
    APP_VCOM_DEV_CTX_STRU              *pstVcomCtx;

    /* ??????????*/
    if (ucDevIndex >= APP_VCOM_DEV_INDEX_BUTT)
    {
        return VOS_ERR;
    }

    pstVcomCtx = APP_VCOM_GetVcomCtxAddr(ucDevIndex);

    /* ????????????????????*/
    pstVcomCtx->pEventFunc = pFunc;

    return VOS_OK;
}

/*****************************************************************************
 ?? ?? ??  : APP_VCOM_GetIndexFromMajorDevId
 ????????  : ??????????????????????????????????????????
 ????????  : VOS_UINT32 ulMajorDevId
 ????????  : ??
 ?? ?? ??  : VOS_UINT8 ??????????

 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2012??11??23??
    ??    ??   : z00220246
    ????????   : ??????????

*****************************************************************************/
VOS_UINT8 APP_VCOM_GetIndexFromMajorDevId(VOS_UINT ulMajorDevId)
{
    VOS_UINT8                           ucLoop;
    APP_VCOM_DEV_CTX_STRU              *pstVcomCtx;

    for (ucLoop = 0; ucLoop < APP_VCOM_MAX_NUM; ucLoop++)
    {
        pstVcomCtx = APP_VCOM_GetVcomCtxAddr(ucLoop);

        if (pstVcomCtx->ulAppVcomMajorId == ulMajorDevId)
        {
            break;
        }
    }

    return ucLoop;
}

/*****************************************************************************
 ?? ?? ??  : APP_VCOM_InitSpecCtx
 ????????  : ??????VCOM ????????????
 ????????  : VOS_UINT8 ulDevIndex
 ????????  : ??
 ?? ?? ??  : ??
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2012??11??23??
    ??    ??   : z00220246
    ????????   : ??????????

*****************************************************************************/
VOS_VOID  APP_VCOM_InitSpecCtx(VOS_UINT8 ucDevIndex)
{
    APP_VCOM_DEV_CTX_STRU              *pstVcomCtx;

    if (ucDevIndex >= APP_VCOM_MAX_NUM)
    {
        return;
    }

    pstVcomCtx = APP_VCOM_GetVcomCtxAddr(ucDevIndex);

    VOS_MemSet(pstVcomCtx->aucSendSemName, 0, APP_VCOM_SEM_NAME_MAX_LEN);
    VOS_MemSet(pstVcomCtx->aucAppVcomName, 0, APP_VCOM_DEV_NAME_MAX_LEN);

    VOS_MemCpy(pstVcomCtx->aucAppVcomName,
               g_astAppVcomCogfigTab[ucDevIndex].pcAppVcomName,
               VOS_StrLen(g_astAppVcomCogfigTab[ucDevIndex].pcAppVcomName));

    VOS_MemCpy(pstVcomCtx->aucSendSemName,
               g_astAppVcomCogfigTab[ucDevIndex].pcSendSemName,
               VOS_StrLen(g_astAppVcomCogfigTab[ucDevIndex].pcSendSemName));

    pstVcomCtx->ulAppVcomMajorId = APP_VCOM_MAJOR_DEV_ID + ucDevIndex;
}

/*****************************************************************************
 ?? ?? ??  : APP_VCOM_Setup
 ????????  : ??????????????????????????
 ????????  : APP_VCOM_DEV_ENTITY_STRU *pstDev
             VOS_UINT8                 ucIndex
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??10??18??
    ??    ??   : sunshaohua
    ????????   : ??????????

  2.??    ??   : 2012??11??23??
    ??    ??   : z00220246
    ????????   : DSDA Phase I

*****************************************************************************/
VOS_VOID APP_VCOM_Setup(
    APP_VCOM_DEV_ENTITY_STRU *pstDev,
    VOS_UINT8                 ucIndex
)
{
    VOS_INT                             iErr;
    dev_t                               ulDevno;
    static struct class                *pstCom_class;
    APP_VCOM_DEV_CTX_STRU              *pstVcomCtx;

    pstVcomCtx = APP_VCOM_GetVcomCtxAddr(ucIndex);

    ulDevno = MKDEV(pstVcomCtx->ulAppVcomMajorId, ucIndex);

    cdev_init(&pstDev->stAppVcomDev, &g_stOperations_Fops);

    iErr = cdev_add(&pstDev->stAppVcomDev, ulDevno, 1);
    if (iErr)
    {
        APP_VCOM_TRACE_ERR(ucIndex, "APP_VCOM_Setup cdev_add error! ");
        return;
    }

    pstCom_class = class_create(THIS_MODULE, pstVcomCtx->aucAppVcomName);

    device_create(pstCom_class,
                  NULL,
                  MKDEV(pstVcomCtx->ulAppVcomMajorId, ucIndex),
                  "%s",
                  pstVcomCtx->aucAppVcomName);

    return;
}

/*****************************************************************************
 ?? ?? ??  : APP_VCOM_Init
 ????????  : ??????????????
 ????????  : ??
 ????????  : ??
 ?? ?? ??  : VOS_OK    ????
             VOS_ERR   ????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??10??18??
    ??    ??   : sunshaohua
    ????????   : ??????????
  2.??    ??   : 2012??11??23??
    ??    ??   : z00220246
    ????????   : DSDA Phase I
  3.??    ??   : 2013??08??01??
    ??    ??   : j00177245
    ????????   : ????appvcom??????????
  4.??    ??   : 2013??10??25??
    ??    ??   : j00177245
    ????????   : ????appvcom??????????????????
  5.??    ??   : 2014??4??22??
    ??    ??   : A00165503
    ????????   : DTS2014042208020: ??????????????????
*****************************************************************************/
VOS_INT __init APP_VCOM_Init(VOS_VOID)
{
    VOS_INT                             iResult1;
    VOS_INT                             iResult2;
    dev_t                               ulDevno;
    VOS_UINT8                           ucIndex;
    APP_VCOM_DEV_CTX_STRU              *pstVcomCtx;
    APP_VCOM_DEV_ENTITY_STRU           *pstVcomDevp;

    printk("APP_VCOM_Init entry,%u",VOS_GetSlice());

    pstVcomCtx = VOS_NULL_PTR;
    pstVcomDevp  = VOS_NULL_PTR;

    /* ?????????????????????? */
    VOS_MemSet(&g_stAppVcomDebugInfo, 0x0, sizeof(g_stAppVcomDebugInfo));

    VOS_MemSet(&g_stAppVcomDebugCfg, 0x0, sizeof(g_stAppVcomDebugCfg));

    /* ?????????????? */
    for (ucIndex = 0; ucIndex < APP_VCOM_MAX_NUM; ucIndex++)
    {
        /* ?????????????? */
        APP_VCOM_InitSpecCtx(ucIndex);

        /* ???????????????? */
        pstVcomCtx = APP_VCOM_GetVcomCtxAddr(ucIndex);

        /* ??????????????dev_t ???? */
        ulDevno = MKDEV(pstVcomCtx->ulAppVcomMajorId, ucIndex);

        iResult1 = register_chrdev_region(ulDevno, 1, pstVcomCtx->aucAppVcomName);

        /* ???????????????????????? */
        if (iResult1 < 0)
        {
            iResult2 = alloc_chrdev_region(&ulDevno, 0, 1, pstVcomCtx->aucAppVcomName);

            if (iResult2 < 0 )
            {
                return VOS_ERROR;
            }

            pstVcomCtx->ulAppVcomMajorId = MAJOR(ulDevno);
        }

        /* ?????????????????????? */
        pstVcomCtx->pstAppVcomDevEntity = kmalloc(sizeof(APP_VCOM_DEV_ENTITY_STRU) , GFP_KERNEL);

        if (VOS_NULL_PTR == pstVcomCtx->pstAppVcomDevEntity)
        {
            /* ?????????????????????? */
            unregister_chrdev_region(ulDevno, 1);
            APP_VCOM_TRACE_ERR(ucIndex, "APP_VCOM_Init malloc device Entity fail. ");
            return VOS_ERROR;
        }

        /* ???????????????? */
        pstVcomDevp = pstVcomCtx->pstAppVcomDevEntity;

        VOS_MemSet(pstVcomDevp, 0, sizeof(APP_VCOM_DEV_ENTITY_STRU));

        pstVcomDevp->pucAppVcomMem = kmalloc(g_astAppVcomCogfigTab[ucIndex].ulAppVcomMemSize, GFP_KERNEL);

        if (VOS_NULL_PTR == pstVcomDevp->pucAppVcomMem)
        {
            /* ?????????????????????? */
            unregister_chrdev_region(ulDevno, 1);
            APP_VCOM_TRACE_ERR(ucIndex, "APP_VCOM_Init malloc device buff fail. ");
            kfree(pstVcomCtx->pstAppVcomDevEntity);
            pstVcomCtx->pstAppVcomDevEntity = VOS_NULL_PTR;
            return VOS_ERROR;
        }

        init_waitqueue_head(&pstVcomDevp->Read_Wait);
        VOS_MemSet(pstVcomDevp->acWakeLockName, 0x00, APP_VCOM_RD_WAKE_LOCK_NAME_LEN);
        snprintf(pstVcomDevp->acWakeLockName, APP_VCOM_RD_WAKE_LOCK_NAME_LEN, "appvcom%d_rd_wake", ucIndex);
        pstVcomDevp->acWakeLockName[APP_VCOM_RD_WAKE_LOCK_NAME_LEN - 1] = '\0';
        wake_lock_init(&pstVcomDevp->stRdWakeLock, WAKE_LOCK_SUSPEND, pstVcomDevp->acWakeLockName);

        mutex_init(&pstVcomDevp->stMutex);

        APP_VCOM_Setup(pstVcomDevp, ucIndex);

        /* ?????????? */
        sema_init(&pstVcomDevp->stMsgSendSem,1);
        sema_init(&pstVcomDevp->stWrtSem, 1);
    }


    printk("APP_VCOM_Init eixt,%u",VOS_GetSlice());

    return VOS_OK;
}

/*****************************************************************************
 ?? ?? ??  : APP_VCOM_Release
 ????????  : ????????????
 ????????  : ??
 ????????  : ??
 ?? ?? ??  : VOS_OK    ????
             VOS_ERROR   ????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??12??14??
    ??    ??   : sunshaohua
    ????????   : ??????????
*****************************************************************************/
int APP_VCOM_Release(
    struct inode                       *inode,
    struct file                        *filp
)
{
    VOS_UINT                            ulDevMajor;
    VOS_UINT8                           ucIndex;
    APP_VCOM_DEV_CTX_STRU              *pstVcomCtx;

    if (VOS_NULL_PTR == inode || VOS_NULL_PTR == filp)
    {
        return VOS_ERROR;
    }

    /* ???????????? */
    ulDevMajor = imajor(inode);

    /* ???????????????????????????????????????? */
    ucIndex = APP_VCOM_GetIndexFromMajorDevId(ulDevMajor);

    if (ucIndex >= APP_VCOM_MAX_NUM)
    {
        APP_VCOM_TRACE_ERR(ucIndex, "APP_VCOM_Release ucIndex is error. ");
        return VOS_ERROR;
    }

    /* ????VCOM???????? */
    pstVcomCtx = APP_VCOM_GetVcomCtxAddr(ucIndex);

    if (VOS_NULL_PTR == pstVcomCtx->pstAppVcomDevEntity)
    {
        APP_VCOM_TRACE_ERR(ucIndex, "APP_VCOM_Release VcomDevEntity is NULL. ");
        return VOS_ERROR;
    }

    /* ?????????????????????????????????????? */
    filp->private_data = pstVcomCtx->pstAppVcomDevEntity;

    APP_VCOM_TRACE_INFO(ucIndex, "APP_VCOM_Release enter. ");

    if(NULL != pstVcomCtx->pEventFunc)
    {
		(VOS_VOID)(pstVcomCtx->pEventFunc(APP_VCOM_EVT_RELEASE));
    }

    pstVcomCtx->pstAppVcomDevEntity->ulIsDeviceOpen = VOS_FALSE;
    wake_unlock(&pstVcomCtx->pstAppVcomDevEntity->stRdWakeLock);

    return VOS_OK;
}

/*****************************************************************************
 ?? ?? ??  : APP_VCOM_Open
 ????????  : ????????????
 ????????  : ??
 ????????  : ??
 ?? ?? ??  : VOS_OK    ????
             VOS_ERROR   ????
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??12??14??
    ??    ??   : sunshaohua
    ????????   : ??????????
  2.??    ??   : 2012??11??23??
    ??    ??   : z00220246
    ????????   : DSDA Phase I
*****************************************************************************/
int APP_VCOM_Open(
    struct inode                       *inode,
    struct file                        *filp
)
{
    VOS_UINT                            ulDevMajor;
    VOS_UINT8                           ucIndex;
    APP_VCOM_DEV_CTX_STRU              *pstVcomCtx;

    if (VOS_NULL_PTR == inode || VOS_NULL_PTR == filp)
    {
        return VOS_ERROR;
    }

    /* ???????????? */
    ulDevMajor = imajor(inode);

    /* ???????????????????????????????????????? */
    ucIndex = APP_VCOM_GetIndexFromMajorDevId(ulDevMajor);

    if (ucIndex >= APP_VCOM_MAX_NUM)
    {
        APP_VCOM_TRACE_ERR(ucIndex, "APP_VCOM_Open ucIndex is error. ");
        return VOS_ERROR;
    }

    /* ????VCOM???????? */
    pstVcomCtx = APP_VCOM_GetVcomCtxAddr(ucIndex);

    if (VOS_NULL_PTR == pstVcomCtx->pstAppVcomDevEntity)
    {
        APP_VCOM_TRACE_ERR(ucIndex, "APP_VCOM_Open VcomDevEntity is NULL. ");
        return VOS_ERROR;
    }

    /* ?????????????????????????????????????? */
    filp->private_data = pstVcomCtx->pstAppVcomDevEntity;

    APP_VCOM_TRACE_INFO(ucIndex, "APP_VCOM_Open enter. ");

    if(NULL != pstVcomCtx->pEventFunc)
    {
        (VOS_VOID)(pstVcomCtx->pEventFunc(APP_VCOM_EVT_OPEN));
    }

    pstVcomCtx->pstAppVcomDevEntity->ulIsDeviceOpen = VOS_TRUE;

    return VOS_OK;
}

/*****************************************************************************
 ?? ?? ??  : APP_VCOM_Read
 ????????  : ??????????????
 ????????  : struct file *stFilp
             char __user *buf
             size_t       count
             loff_t      *ppos
 ????????  : ??
 ?? ?? ??  : ssize_t
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??10??18??
    ??    ??   : sunshaohua
    ????????   : ??????????
  2.??    ??   : 2012??11??23??
    ??    ??   : z00220246
    ????????   : DSDA Phase I
  3.??    ??   : 2013??08??01??
    ??    ??   : j00177245
    ????????   : ????appvcom??????????
  4.??    ??   : 2013??10??28??
    ??    ??   : f00179208
    ????????   : DTS2013102801414:????????????????????????????VCOM??????0??????????
*****************************************************************************/
ssize_t APP_VCOM_Read(
    struct file                        *stFilp,
    char __user                        *buf,
    size_t                              count,
    loff_t                             *ppos
)
{
    APP_VCOM_DEV_ENTITY_STRU           *pstVcomDev;
    struct cdev                        *pstCdev;
    VOS_UINT                            ulDevMajor;
    VOS_UINT8                           ucIndex;
    APP_VCOM_DEV_CTX_STRU              *pstVcomCtx;

    /* ?????????????????? */
    pstVcomDev = stFilp->private_data;

    /* ???????????????? */
    pstCdev = &(pstVcomDev->stAppVcomDev);
    ulDevMajor = MAJOR(pstCdev->dev);

    /* ???????????????????????????? */
    ucIndex = APP_VCOM_GetIndexFromMajorDevId(ulDevMajor);

    if (ucIndex >= APP_VCOM_MAX_NUM)
    {
        return APP_VCOM_ERROR;
    }

    pstVcomCtx = APP_VCOM_GetVcomCtxAddr(ucIndex);

    APP_VCOM_TRACE_INFO(ucIndex, "APP_VCOM_Read, read count:%d, current_len:%d. ", count, pstVcomDev->current_len);
    APP_VCOM_TRACE_INFO(ucIndex, "APP_VCOM_Read, f_flags:%d. ", stFilp->f_flags);
    APP_VCOM_TRACE_INFO(ucIndex, "APP_VCOM_Read, wait_event 111, flag:%d. ", pstVcomDev->ulReadWakeUpFlg);

    if (stFilp->f_flags & O_NONBLOCK)
    {
        return APP_VCOM_ERROR;
    }

    /*lint -e730 ??????:l60609;??????:z60575;????:??????????????????????????  */
    if (wait_event_interruptible(pstVcomDev->Read_Wait, (pstVcomDev->current_len != 0)))
    {
        return -ERESTARTSYS;
    }
    /*lint +e730 ??????:l60609;??????:z60575;????:??????????????????????????  */

    if (0 == pstVcomDev->current_len)
    {
        g_stAppVcomDebugInfo.ulReadLenErr[ucIndex]++;
    }

    APP_VCOM_TRACE_INFO(ucIndex, "APP_VCOM_Read, wait_event 222,flag:%d. ", pstVcomDev->ulReadWakeUpFlg);

    /* ?????????? */
    down(&pstVcomCtx->pstAppVcomDevEntity->stMsgSendSem);

    if (count > pstVcomDev->current_len)
    {
        count = pstVcomDev->current_len;
    }

    if (copy_to_user(buf, pstVcomDev->pucAppVcomMem, (VOS_ULONG)count))
    {
        APP_VCOM_TRACE_ERR(ucIndex, "APP_VCOM_Read, copy_to_user fail. ");

        /* ?????????? */
        up(&pstVcomCtx->pstAppVcomDevEntity->stMsgSendSem);
        return APP_VCOM_ERROR;
    }

    if ((pstVcomDev->current_len - count) > 0)
    {
        /* FIFO???????? */
        memmove(pstVcomDev->pucAppVcomMem, (pstVcomDev->pucAppVcomMem + count), (pstVcomDev->current_len - count));
        APP_VCOM_TRACE_INFO(ucIndex, "APP_VCOM_Read, FIFO move. ");
    }

    /* ????????????????*/
    pstVcomDev->current_len -= count;

    APP_VCOM_TRACE_INFO(ucIndex, "APP_VCOM_Read, read %d bytes, current_len:%d. ", count, pstVcomDev->current_len);

    if (0 == pstVcomDev->current_len)
    {
        APP_VCOM_TRACE_NORM(ucIndex, "APP_VCOM_Send: read all data. ");
        wake_unlock(&pstVcomDev->stRdWakeLock);
    }

    /* ?????????? */
    up(&pstVcomCtx->pstAppVcomDevEntity->stMsgSendSem);

    return (ssize_t)count;
}

/*****************************************************************************
 ?? ?? ??  : APP_VCOM_Write
 ????????  : ??????????????
 ????????  : struct file       *stFilp
             const char __user *buf
             size_t             count
             loff_t            *ppos
 ????????  : ??
 ?? ?? ??  : ssize_t
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??10??18??
    ??    ??   : sunshaohua
    ????????   : ??????????
  2.??    ??   : 2012??11??23??
    ??    ??   : z00220246
    ????????   : DSDA Phase I
  3.??    ??   : 2013??10??25??
    ??    ??   : j00177245
    ????????  :  ????appvcom??????????????????
  4.??    ??   : 2014??4??22??
    ??    ??   : A00165503
    ????????   : DTS2014042208020: ????APPVCOM9??APPVCOM12??????????
*****************************************************************************/
ssize_t APP_VCOM_Write(
    struct file                        *stFilp,
    const char __user                  *buf,
    size_t                              count,
    loff_t                             *ppos
)
{
    VOS_UINT8                          *pucDataBuf;
    VOS_INT                             iRst;
    APP_VCOM_DEV_ENTITY_STRU           *pstVcomDev;
    struct cdev                        *pstCdev;
    VOS_UINT                            ulDevMajor;
    VOS_UINT8                           ucIndex;
    APP_VCOM_DEV_CTX_STRU              *pstVcomCtx;

    /* ?????????????????? */
    pstVcomDev = stFilp->private_data;

    /* ???????????????? */
    pstCdev = &(pstVcomDev->stAppVcomDev);
    ulDevMajor = MAJOR(pstCdev->dev);

    /* ???????????????????????????? */
    ucIndex = APP_VCOM_GetIndexFromMajorDevId(ulDevMajor);

    if(ucIndex >= APP_VCOM_MAX_NUM)
    {
        APP_VCOM_TRACE_ERR(ucIndex, "APP_VCOM_Write, ucIndex fail. ");
        return APP_VCOM_ERROR;
    }

    if (NULL == buf)
    {
        APP_VCOM_TRACE_ERR(ucIndex, "APP_VCOM_Write, buf is null ");
        return APP_VCOM_ERROR;
    }

    if (count > APP_VCOM_MAX_DATA_LENGTH)
    {
        APP_VCOM_TRACE_ERR(ucIndex, "APP_VCOM_Write, count is %d, to large", count);
        return APP_VCOM_ERROR;
    }

    /* ???????????????? */
    pstVcomCtx = APP_VCOM_GetVcomCtxAddr(ucIndex);

    /* ???????? */
    pucDataBuf = kmalloc(count, GFP_KERNEL);
    if (VOS_NULL_PTR == pucDataBuf )
    {
        APP_VCOM_TRACE_ERR(ucIndex, "APP_VCOM_Write, kmalloc fail. ");

        return APP_VCOM_ERROR;
    }

    /* buffer???? */
    VOS_MemSet(pucDataBuf, 0x00, (VOS_SIZE_T)count);

    if (copy_from_user(pucDataBuf, buf, (VOS_ULONG)count))
    {
        APP_VCOM_TRACE_ERR(ucIndex, "APP_VCOM_Write, copy_from_user fail. ");

        kfree(pucDataBuf);
        return APP_VCOM_ERROR;
    }

    if ((APP_VCOM_DEV_INDEX_9 == ucIndex) || (APP_VCOM_DEV_INDEX_12 == ucIndex))
    {
        down(&pstVcomCtx->pstAppVcomDevEntity->stWrtSem);

        if (VOS_NULL_PTR != pstVcomCtx->pstAppVcomDevEntity->pucWrtBuffer)
        {
            APP_VCOM_TRACE_NORM(ucIndex, "APP_VCOM_Write: free buff. ");

            kfree(pstVcomCtx->pstAppVcomDevEntity->pucWrtBuffer);
            pstVcomCtx->pstAppVcomDevEntity->pucWrtBuffer   = VOS_NULL_PTR;
            pstVcomCtx->pstAppVcomDevEntity->ulWrtBufferLen = 0;
        }

        if (VOS_NULL_PTR == pstVcomCtx->pSendUlAtFunc)
        {
            APP_VCOM_TRACE_NORM(ucIndex, "APP_VCOM_Write: save buff. ");

            pstVcomCtx->pstAppVcomDevEntity->pucWrtBuffer   = pucDataBuf;
            pstVcomCtx->pstAppVcomDevEntity->ulWrtBufferLen = count;
            up(&pstVcomCtx->pstAppVcomDevEntity->stWrtSem);
            return (ssize_t)count;
        }

        up(&pstVcomCtx->pstAppVcomDevEntity->stWrtSem);
    }

    /* ????????????????buf????AT????*/
    if (VOS_NULL_PTR == pstVcomCtx->pSendUlAtFunc)
    {
        APP_VCOM_TRACE_ERR(ucIndex, "APP_VCOM_Write, pSendUlAtFunc is null. ");
        kfree(pucDataBuf);
        return APP_VCOM_ERROR;
    }

    mutex_lock(&pstVcomDev->stMutex);

    iRst = pstVcomCtx->pSendUlAtFunc(ucIndex, pucDataBuf, (VOS_UINT32)count);
    if (VOS_OK != iRst)
    {
        g_stAppVcomDebugInfo.ulAtCallBackErr[ucIndex]++;
        APP_VCOM_TRACE_ERR(ucIndex, "APP_VCOM_Write, AT_RcvFromAppCom fail. ");
        mutex_unlock(&pstVcomDev->stMutex);
        kfree(pucDataBuf);

        return APP_VCOM_ERROR;
    }

    mutex_unlock(&pstVcomDev->stMutex);

    APP_VCOM_TRACE_INFO(ucIndex, "APP_VCOM_Write, write %d bytes, AT_RcvFromAppCom Success.",count);

    /* ???????? */
    kfree(pucDataBuf);

    return (ssize_t)count;
}

/*****************************************************************************
 ?? ?? ??  : APP_VCOM_Poll
 ????????  : ????????POLL
 ????????  : struct file *fp
             struct poll_table_struct *wait
 ????????  : ??
 ?? ?? ??  : 0
             POLLIN | POLLRDNORM
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2013??8??6??
    ??    ??   : A00165503
    ????????   : ??????????
*****************************************************************************/
unsigned int APP_VCOM_Poll(struct file *fp, struct poll_table_struct *wait)
{
    APP_VCOM_DEV_ENTITY_STRU           *pstVcomDev = VOS_NULL_PTR;
    unsigned int                        mask = 0;

    struct cdev                        *pstCdev;
    VOS_UINT                            ulDevMajor;
    VOS_UINT8                           ucIndex;

    pstVcomDev = fp->private_data;

    pstCdev = &(pstVcomDev->stAppVcomDev);
    ulDevMajor = MAJOR(pstCdev->dev);
    ucIndex = APP_VCOM_GetIndexFromMajorDevId(ulDevMajor);

    poll_wait(fp, &pstVcomDev->Read_Wait, wait);

    if (0 != pstVcomDev->current_len)
    {
        mask |= POLLIN | POLLRDNORM;
    }

    APP_VCOM_TRACE_INFO(ucIndex, "APP_VCOM_Poll, mask = %d. ", mask);

    return mask;
}

/*****************************************************************************
 ?? ?? ??  : APP_VCOM_Send
 ????????  : ????AT??????????????????????
 ????????  : APP_VCOM_DEV_INDEX_UINT8 enDevIndex
             VOS_UINT8  *pData
             VOS_UINT32 uslength
 ????????  : ??
 ?? ?? ??  : VOS_UINT32
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2011??12??20??
    ??    ??   : lijun 00171473
    ????????   : ??????????
  2.??    ??   : 2012??11??23??
    ??    ??   : z00220246
    ????????   : DSDA Phase I
  3.??    ??   : 2013??08??01??
    ??    ??   : j00177245
    ????????   : ????appvcom??????????
  4.??    ??   : 2013??10??25??
    ??    ??   : j00177245
    ????????   : ????appvcom??????????????????
  5.??    ??   : 2014??4??22??
    ??    ??   : A00165503
    ????????   : DTS2014042208020: ????APPVCOM9??APPVCOM12??????????
  6.??    ??   : 2016??6??12??
    ??    ??   : l00198894
    ????????   : DTS2016061000456: ??????????????????
*****************************************************************************/
VOS_UINT32  APP_VCOM_Send (
    APP_VCOM_DEV_INDEX_UINT8            enDevIndex,
    VOS_UINT8                          *pData,
    VOS_UINT32                          uslength
)
{
    APP_VCOM_DEV_ENTITY_STRU           *pstVcomDev;
    APP_VCOM_DEV_CTX_STRU              *pstVcomCtx;

    if (enDevIndex >= APP_VCOM_MAX_NUM)
    {
        g_stAppVcomDebugInfo.ulDevIndexErr++;
        APP_VCOM_TRACE_ERR(enDevIndex, "APP_VCOM_Send, enDevIndex is error. ");
        return VOS_ERR;
    }

    pstVcomCtx = APP_VCOM_GetVcomCtxAddr(enDevIndex);
    if (VOS_NULL_PTR == pstVcomCtx)
    {
        APP_VCOM_TRACE_ERR(enDevIndex, "APP_VCOM_Send, pstVcomCtx is null. ");
        return VOS_ERR;
    }

    /* ???????????????? */
    pstVcomDev = APP_VCOM_GetAppVcomDevEntity(enDevIndex);
    if (VOS_NULL_PTR == pstVcomDev)
    {
        g_stAppVcomDebugInfo.ulVcomDevErr[enDevIndex]++;
        APP_VCOM_TRACE_ERR(enDevIndex, "APP_VCOM_Send, pstVcomDev is null. ");
        return VOS_ERR;
    }

    if ((APP_VCOM_DEV_INDEX_9 == enDevIndex) || (APP_VCOM_DEV_INDEX_12 == enDevIndex))
    {
        down(&pstVcomDev->stWrtSem);

        if (VOS_NULL_PTR != pstVcomDev->pucWrtBuffer)
        {
            if (VOS_NULL_PTR != pstVcomCtx->pSendUlAtFunc)
            {
                APP_VCOM_TRACE_NORM(enDevIndex, "APP_VCOM_Send: handle buff. ");

                (VOS_VOID)pstVcomCtx->pSendUlAtFunc(enDevIndex,
                                        pstVcomDev->pucWrtBuffer,
                                        pstVcomDev->ulWrtBufferLen);

                kfree(pstVcomDev->pucWrtBuffer);
                pstVcomDev->pucWrtBuffer   = VOS_NULL_PTR;
                pstVcomDev->ulWrtBufferLen = 0;
            }
        }

        up(&pstVcomDev->stWrtSem);
    }

    APP_VCOM_TRACE_INFO(enDevIndex, "APP_VCOM_Send, uslength:%d, current_len:%d. ", uslength, pstVcomDev->current_len);

    /* ?????????? */
    down(&pstVcomDev->stMsgSendSem);

    /* ???????????????? */
    if (g_astAppVcomCogfigTab[enDevIndex].ulAppVcomMemSize == pstVcomDev->current_len)
    {
        APP_VCOM_TRACE_NORM(enDevIndex, "APP_VCOM_Send: VCOM MEM FULL. ");

        if (VOS_TRUE == pstVcomDev->ulIsDeviceOpen)
        {
            APP_VCOM_ERR_LOG(enDevIndex, "APP_VCOM_Send: VCOM MEM FULL. ");
        }

        g_stAppVcomDebugInfo.ulMemFullErr[enDevIndex]++;

        up(&pstVcomDev->stMsgSendSem);
        return VOS_ERR;
    }

    /* ????????????????Buffer???? */
    if (uslength > (g_astAppVcomCogfigTab[enDevIndex].ulAppVcomMemSize - pstVcomDev->current_len))
    {
        APP_VCOM_TRACE_NORM(enDevIndex, "APP_VCOM_Send: data more than Buffer. ");

        if (VOS_TRUE == pstVcomDev->ulIsDeviceOpen)
        {
            APP_VCOM_ERR_LOG(enDevIndex, "APP_VCOM_Send: VCOM MEM FULL. ");
        }

        uslength = g_astAppVcomCogfigTab[enDevIndex].ulAppVcomMemSize - (VOS_UINT32)pstVcomDev->current_len;
    }

    /* ??????BUFFER */
    memcpy(pstVcomDev->pucAppVcomMem + pstVcomDev->current_len, pData, uslength);
    pstVcomDev->current_len += uslength;

    APP_VCOM_TRACE_INFO(enDevIndex, "APP_VCOM_Send, written %d byte(s), new len: %d. ", uslength, pstVcomDev->current_len);

    APP_VCOM_TRACE_INFO(enDevIndex, "APP_VCOM_Send, IsDeviceOpen: %d. ", pstVcomDev->ulIsDeviceOpen);
    /*lint -e713*/
    if (VOS_TRUE == pstVcomDev->ulIsDeviceOpen)
    {
        wake_lock_timeout(&pstVcomDev->stRdWakeLock, msecs_to_jiffies(APP_VCOM_READ_WAKE_LOCK_LEN));
    }
    /*lint +e713*/

    /* ?????????? */
    up(&pstVcomDev->stMsgSendSem);
    wake_up_interruptible(&pstVcomDev->Read_Wait);

    if (0 == pstVcomDev->current_len)
    {
        g_stAppVcomDebugInfo.ulSendLenErr[enDevIndex]++;
    }

    APP_VCOM_TRACE_INFO(enDevIndex, "APP_VCOM_Send, wakeup. ");
    return VOS_OK;
}

/*****************************************************************************
 ?? ?? ??  : APP_VCOM_ShowDebugInfo
 ????????  : ????appvcom??????????????
 ????????  : ??
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2013??09??21??
    ??    ??   : j00174725
    ????????  : ????????
*****************************************************************************/
VOS_VOID APP_VCOM_ShowDebugInfo(VOS_VOID)
{
    int                                 i;
    (VOS_VOID)vos_printf("App Vcom Debug Info:");
    (VOS_VOID)vos_printf("Index Err: %d\r\n", g_stAppVcomDebugInfo.ulDevIndexErr);

    for (i = 0; i < APP_VCOM_MAX_NUM; i++)
    {
        (VOS_VOID)vos_printf("\r\n");
        (VOS_VOID)vos_printf("AppVcom[%d] Callback Function Return Err Num: %d\r\n", i, g_stAppVcomDebugInfo.ulAtCallBackErr[i]);
        (VOS_VOID)vos_printf("AppVcom[%d] Mem Full Num:                     %d\r\n", i, g_stAppVcomDebugInfo.ulMemFullErr[i]);
        (VOS_VOID)vos_printf("AppVcom[%d] Read Data Length = 0 Num:         %d\r\n", i, g_stAppVcomDebugInfo.ulReadLenErr[i]);
        (VOS_VOID)vos_printf("AppVcom[%d] Send Data Length = 0 Num:         %d\r\n", i, g_stAppVcomDebugInfo.ulSendLenErr[i]);
        (VOS_VOID)vos_printf("AppVcom[%d] Get App Vcom Dev Entity Err Num:  %d\r\n", i, g_stAppVcomDebugInfo.ulVcomDevErr[i]);
    }
}


/*****************************************************************************
 ?? ?? ??  : APP_VCOM_SendDebugNvCfg
 ????????  : ????????VCOM Debug ??????????NV??
 ????????  : VOS_UINT32 ulAppVcomDebugNvCfg
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2014??06??03??
    ??    ??   : n00269697
    ????????   : ??????????
*****************************************************************************/
VOS_VOID APP_VCOM_SendDebugNvCfg(
    VOS_UINT32                          ulPortIdMask,
    VOS_UINT32                          ulDebugLevel
)
{
    g_stAppVcomDebugCfg.ulPortIdMask = ulPortIdMask;
    g_stAppVcomDebugCfg.ulDebugLevel = ulDebugLevel;
}

/*****************************************************************************
 ?? ?? ??  : APP_VCOM_MNTN_LogPrintf
 ????????  : APP VCOM????????LOG????
 ????????  : VOS_CHAR *pcFmt
             ...
 ????????  : ??
 ?? ?? ??  : VOS_VOID
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2014??06??03??
    ??    ??   : N00269697
    ????????   : ??????????
*****************************************************************************/
/*lint -esym(960,69)*/
VOS_VOID APP_VCOM_MNTN_LogPrintf(VOS_CHAR *pcFmt, ...)
{
    VOS_CHAR                            acBuf[APP_VCOM_TRACE_BUF_LEN] = {0};
    VOS_UINT32                          ulPrintLength = 0;

    /* ??????????BUFFER */
    /*lint -e713 -e438 -e507*/
    APP_VCOM_LOG_FORMAT(ulPrintLength, acBuf, APP_VCOM_TRACE_BUF_LEN, pcFmt);
    /*lint +e713 +e438 +e507*/

    printk(KERN_ERR "%s", acBuf);
    return;
}
/*lint +esym(960,69)*/

module_init(APP_VCOM_Init);



