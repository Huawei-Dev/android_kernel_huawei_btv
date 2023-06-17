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

/******************************************************************************

                  ???????? (C), 2001-2011, ????????????????

 ******************************************************************************
  ?? ?? ??   : OmPcVoice.c
  ?? ?? ??   : ????
  ??    ??   : ????
  ????????   : 2010??4??
  ????????   :
  ????????   : pc voice??????
  ????????   :
  ????????   :
  1.??    ??   : 2010??4??
    ??    ??   : ????
    ????????   : ????????

******************************************************************************/

/*****************************************************************************
  1 ??????????
*****************************************************************************/
#include "omringbuffer.h"
#include "omprivate.h"
#include "cpm.h"
#include "CbtCpm.h"
/* HIFI ???? */
#include "HifiOmInterface.h"
#include "PamOamSpecTaskDef.h"
#include "pamappom.h"
#include "CbtPpm.h"
#include "errorlog.h"
#include "OmApi.h"



/*lint -e767 ??????:???? 00128685;??????:???? 51137;????:Log???? */
#define    THIS_FILE_ID        PS_FILE_ID_OM_PC_VOICE_C
/*lint +e767 ??????:???? 00128685;??????:???? 51137; */


/* ??????????????640???????? ?????? V3R3*/
#define OM_PCV_BUF_SIZE                         (320*6*2)
#define OM_PCV_PORT_PCSC                        (3)

#define PAM_PCV_BIT_N(num)                      (0x01 << (num))

/*??????????????*/
#define OM_PCV_HOOK_ENABLE                      (0x010000)
#define OM_PCV_USB_OM_ENABLE                    (0x010400)
#define OM_PCV_OM_MED_ENABLE                    (0x010100)
#define OM_PCV_MED_OM_ENABLE                    (0x010200)

#define OM_PCV_OM_MED_BIT                       (8)
#define OM_PCV_MED_OM_BIT                       (9)
#define OM_PCV_USB_OM_BIT                       (10)

/*EventID:????????*/
#define OM_APP_PCV_EXCEPTION_IND                (0x01)
/*EventID:ringbuf??*/
#define OM_APP_PCV_BUF_FULL_IND                 (0x02)
/*EventID:DSP PLL????*/
#define OM_APP_PCV_DSP_PLL_OFF                  (0x03)
#define OM_APP_PCV_QUNUE_FULL                   (0x04)

/*eventID = 0x05???????????? */
#define OM_APP_PCV_MED_OM_LEN                   (0x20)
#define OM_APP_PCV_OM_USB_RET                   (0x21)
#define OM_APP_PCV_READ_NV_FAIL                 (0x22)
#define OM_APP_PCV_MAX_MSG_NUM                  (50)

/*HOOK????????????????PrimID*/
#define OM_APP_VOICE_HOOK_IND                   (0xf0fe)

/* ????10????????500?? */
#define OM_PCV_RCVDATA_TIMES_IN_10S             (500)

/* ??10??????ERRLOG????????????????????*/
#define OM_PCV_RBUF_FULL_TIMES_IN_10S           (50)

#define OM_PCV_MAIL_BOX_PROTECTWORD_FST         (0x55AA55AA)
#define OM_PCV_MAIL_BOX_PROTECTWORD_SND         (0x5A5A5A5A)


#define OM_PCV_RINGBUF_TO_ADDR(StartAddr) \
    ((VOS_UINT_PTR)&(((OM_PCV_RINGBUFFER_STRU*)(StartAddr))->stRingBuffer.pToBuf))

#define OM_PCV_RINGBUF_FROM_ADDR(StartAddr) \
    ((VOS_UINT_PTR)&(((OM_PCV_RINGBUFFER_STRU*)(StartAddr))->stRingBuffer.pFromBuf))

#define OM_PCV_RINGBUF_BUF_ADDR(StartAddr) \
        ((VOS_UINT_PTR)&(((OM_PCV_RINGBUFFER_STRU*)(StartAddr))->stRingBuffer.buf))

typedef struct
{
    VOS_UINT32                          ulProtectWord1;     /*?????? 0x55AA55AA*/
    VOS_UINT32                          ulProtectWord2;     /*?????? 0x5A5A5A5A*/
    OM_RING                             stRingBuffer;
    VOS_UINT32                          ulProtectWord3;     /*?????? 0x55AA55AA*/
    VOS_UINT32                          ulProtectWord4;     /*?????? 0x5A5A5A5A*/
}OM_PCV_RINGBUFFER_STRU;

typedef struct
{
    VOS_UINT_PTR                        ulMailBoxAddr;      /* ?????????????? */
    VOS_UINT_PTR                        ulBufPhyAddr;       /* ?????????????????? */
    VOS_UINT_PTR                        ulBufVirtAddr;      /* ?????????????????? */
}OM_PCV_ADDR_INFO_STRU;

typedef struct
{
    VOS_UINT32 ulRcvUsbSize;
    VOS_UINT32 ulPutSize;
    VOS_UINT32 ulRcvDspSize;
}OM_PCV_DEBUGGING_INFO_STRU;

typedef struct
{
    VOS_UINT32  ulFrameTick;
    VOS_UINT16  usHookTarget;
    VOS_UINT16  usDataLen;
}OM_PCV_TRANS_IND_STRU;

typedef struct
{
    VOS_UINT32  ulStatus;
    VOS_UINT32  ulPort;
    VOS_UINT32  ulCurrentStatus;
    VOS_UINT32  ulIntSlice;
    VOS_UINT32  ulErrSlice;
}OM_PCV_LOG_STRU;


typedef struct
{
    VOS_UINT32  ulDataErr;              /*??????????????????ERRLOG??????*/
    VOS_UINT32  ulFullErr;              /*??????????????ERRLOG??????    */
    VOS_UINT32  ulRcvNum;               /*????10??????????????????????  */
    VOS_UINT32  ulFullNum;              /*????10??????????????????      */
    VOS_UINT32  ul10sFlag;              /*??????10??????                */
}OM_PCV_ERRLOG_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16  usPrimId;
    VOS_UINT16  usReserve;
    VOS_UINT32  ulStatus;               /* ???????? */
    VOS_UINT32  ulPort;                 /* ??????????????????????2 */
}OM_PCV_COM_CFG_REQ;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16  usPrimId;
    VOS_UINT16  usReserve;
    VOS_UINT32  ulPcvHookFlag;
}OM_PCV_TRACE_CFG_REQ;

/*****************************************************************************
??????    : OM_PCV_UNCACHE_MEM_CTRL
????????  : PCVOICE uncache memory????????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          *pucBuf;         /* ???????????????????? */
    VOS_UINT8                          *pucRealBuf;     /* ?????????????????? */
    VOS_UINT32                          ulBufSize;      /* ???????????????? */
    VOS_UINT32                          ulRsv;          /* Reserve */
}OM_PCV_UNCACHE_MEM_CTRL;

/*****************************************************************************
  2 ????????????
*****************************************************************************/
/*????PC VOICE????????????*/
VOS_UINT32                      g_ulPcvStatus = OM_PCV_CHANNEL_CLOSE;
VOS_UINT8                       g_ucPcvComPort = VOS_NULL_BYTE;
/*PC VOICE(USB->OM->DSP)??????????????*/
OM_PCV_RINGBUFFER_STRU          g_PcvRBufOmToDsp;
/*PC VOICE(DSP->OM->USB)??????????????*/
OM_PCV_RINGBUFFER_STRU          g_PcvRBufDspToOm;

OM_PCV_ADDR_INFO_STRU           g_stPcvOmToDspAddr;

OM_PCV_ADDR_INFO_STRU           g_stPcvDspToOmAddr;

/* ring buffer??????????(????????: USB -> COMM -> VOICE -> PHY -> ????) */
COMM_VOICE_RING_BUFFER_CONTROL_STRU  g_stRingBufferControlTXAddr;

/* ring buffer??????????(????????: USB <- COMM <- VOICE <- PHY <- ????) */
COMM_VOICE_RING_BUFFER_CONTROL_STRU  g_stRingBufferControlRXAddr;

/* the semaphore which be used to wake up PC voice transmit task */
VOS_SEM                         g_ulPcvTransmitSem;

/* ????cs errorlog???????????????????? */
OM_PCV_ERRLOG_STRU              g_stErrLogFlag;
/*????????????????
* ??16??: 0--????????????; 1--????????????
* bit8           ??????8    (OM --> DSP)
* bit9           ??????9    (DSP -->OM)
* bit10          ??????10   (USB-->OM)
*/
VOS_UINT32                      g_ulPcvHookFlag = 0;

OM_PCV_DEBUGGING_INFO_STRU      g_stPcvDebuggingInfo;

VOS_UINT32                      g_ulPcvPortMap[]= {OMRL_UART,
                                                   OMRL_UART,
                                                   OMRL_USB_OM,
                                                   OMRL_USB_AT,
                                                   OMRL_UART,
                                                   OM_PCV_PORT_PCSC
                                                  };

VOS_UINT32                      g_ulUsbHookFrameSN =0;

VOS_UINT32                      g_ulOmHookFrameSN =0;

OM_PCV_LOG_STRU                 g_stPcvLog;

OM_PCV_UNCACHE_MEM_CTRL         g_stPcvUncacheMemCtrl;

//extern VOS_BOOL                 g_GUOmOnCtrlPort;

extern VOS_SEM                  g_ulCbtUsbPseudoSyncSemId;

extern UDI_HANDLE               g_ulCbtPortUDIHandle;

VOS_VOID OM_PcvSendEvent(VOS_UINT16 usEventId, VOS_VOID* pData, VOS_UINT32 ulLen);


/*****************************************************************************
  3 ????????
*****************************************************************************/

/*****************************************************************************
 Function   : OM_Read32Reg
 Description: read 32bit data from DSP & BBP
 Input      : ulRegAddr -- address of DSP & BBP
            : ulRegVal -- 32bit data
 Return     : void
 Other      :
 *****************************************************************************/
VOS_UINT32 OM_Read32Reg( VOS_UINT_PTR ulRegAddr )
{
    if ( 0 != (ulRegAddr & 0x03) )/* not 4byte aligned */
    {
        /*lint -e534*/
        LogPrint1("OM_Read32Reg Address: 0x%p not aligned.\r\n", (VOS_INT32)ulRegAddr);
        /*lint +e534*/
        return 0;
    }

    return *(volatile VOS_UINT32 *)ulRegAddr;
}

/*****************************************************************************
 Function   : OM_Write32Reg
 Description: write 32bit data to DSP & BBP
 Input      : ulRegAddr -- address of DSP & BBP
            : ulRegVal -- 32bit data
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID OM_Write32Reg( VOS_UINT_PTR ulRegAddr, VOS_UINT32 ulRegVal)
{
    if ( 0 != (ulRegAddr & 0x03) )/* not 4byte aligned */
    {
        /*lint -e534*/
        LogPrint1("OM_Write32Reg Address: 0x%p not aligned.\r\n", (VOS_INT32)ulRegAddr);
        /*lint +e534*/
        return;
    }

    *(volatile VOS_UINT32 *)ulRegAddr = ulRegVal;
}

/*****************************************************************************
 Function   : OM_Read16Reg
 Description: read 16bit data from DSP & BBP
 Input      : ulRegAddr -- address of DSP & BBP
            : ulRegVal -- 16bit data
 Return     : void
 Other      :
 *****************************************************************************/
VOS_UINT16 OM_Read16Reg( VOS_UINT_PTR ulRegAddr )
{
    if ( 0 != (ulRegAddr & 0x01) )/* not 2byte aligned */
    {
        /*lint -e534*/
        LogPrint1("OM_Read16Reg Address: 0x%p not aligned.\r\n", (VOS_INT32)ulRegAddr);
        /*lint +e534*/
        return 0;
    }

    return *(volatile VOS_UINT16 *)ulRegAddr;
}

/*****************************************************************************
 Function   : OM_Write16Reg
 Description: write 16bit data to DSP & BBP
 Input      : ulRegAddr -- address of DSP & BBP
            : ulRegVal -- 16bit data
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID OM_Write16Reg( VOS_UINT_PTR ulRegAddr, VOS_UINT16 usRegVal)
{
    if ( 0 != (ulRegAddr & 0x01) )/* not 2byte aligned */
    {
        /*lint -e534*/
        LogPrint1("OM_Write16Reg Address: 0x%p not aligned.\r\n", (VOS_INT32)ulRegAddr);
        /*lint +e534*/
        return;
    }

    *(volatile VOS_UINT16 *)ulRegAddr = usRegVal;
}


/*****************************************************************************
 Prototype       : OM_PcvHookInd
 Description     : ??????????????????
 Input           : pucBuf,      --????????
                   usLen        --????????
                   usBitmap     --??????????????BITMAP
                   ulFrameTick  --????
 Output          : None
 Return Value    : None

 History         : ---
Date         : 2010-04-9
Author       : y00163779
Modification : Created function
 *****************************************************************************/
VOS_VOID OM_PcvHookInd(VOS_UCHAR* pucBuf, VOS_UINT16 usLen, VOS_UINT16 usBit, VOS_UINT32 ulFrameTick)
{
    OM_PCV_TRANS_IND_STRU              *pstOmToAppMsg;
    DIAG_TRANS_IND_STRU                 stPcvIndMsg;

    pstOmToAppMsg = (OM_PCV_TRANS_IND_STRU *)VOS_MemAlloc(ACPU_PID_PCVOICE, DYNAMIC_MEM_PT, sizeof(OM_PCV_TRANS_IND_STRU) + usLen);

    if (VOS_NULL_PTR == pstOmToAppMsg)
    {
        PS_LOG(ACPU_PID_PCVOICE, 0, PS_PRINT_ERROR, "OM_PcvHookInd: VOS_AllocMsg failure.\n");
        return;
    }

    /*lint -e534*/
    VOS_MemCpy((VOS_UINT8*)pstOmToAppMsg + sizeof(OM_PCV_TRANS_IND_STRU), (VOS_VOID*)pucBuf, usLen);
    /*lint +e534*/

    /* ????????bitmap */
    pstOmToAppMsg->usHookTarget   = (VOS_UINT16) PAM_PCV_BIT_N(usBit);
    pstOmToAppMsg->ulFrameTick    = ulFrameTick;
    pstOmToAppMsg->usDataLen      = usLen;

    stPcvIndMsg.ulModule  = DIAG_GEN_MODULE(DIAG_MODEM_0, DIAG_MODE_COMM);
    stPcvIndMsg.ulPid     = ACPU_PID_PCVOICE;
    stPcvIndMsg.ulMsgId   = OM_APP_VOICE_HOOK_IND;
    stPcvIndMsg.ulLength  = usLen + sizeof(OM_PCV_TRANS_IND_STRU);
    stPcvIndMsg.pData     = (VOS_VOID *)pstOmToAppMsg;

    /*lint -e534*/
    (VOS_VOID)DIAG_TransReport(&stPcvIndMsg);

    VOS_MemFree(ACPU_PID_PCVOICE, pstOmToAppMsg);
    /*lint +e534*/

    return;
}


VOS_VOID OM_PcvSendEvent(VOS_UINT16 usEventId, VOS_VOID* pData, VOS_UINT32 ulLen)
{
    DIAG_EVENT_IND_STRU                 stEventInd;

    stEventInd.ulModule = DIAG_GEN_MODULE(DIAG_MODEM_0, DIAG_MODE_COMM);
    stEventInd.ulPid    = ACPU_PID_PCVOICE;
    stEventInd.ulEventId= usEventId;
    stEventInd.ulLength = ulLen;
    stEventInd.pData    = pData;

    /*lint -e534*/
    (VOS_VOID)DIAG_EventReport(&stEventInd);
    /*lint +e534*/

    return;
}


VOS_UINT32 OM_PcvInitRBuf(OM_PCV_RINGBUFFER_STRU *pstRingId, OM_PCV_ADDR_INFO_STRU *pstAddrInfo)
{
    pstRingId->ulProtectWord1 = OM_PCV_MAIL_BOX_PROTECTWORD_FST;
    pstRingId->ulProtectWord2 = OM_PCV_MAIL_BOX_PROTECTWORD_SND;
    pstRingId->ulProtectWord3 = OM_PCV_MAIL_BOX_PROTECTWORD_FST;
    pstRingId->ulProtectWord4 = OM_PCV_MAIL_BOX_PROTECTWORD_SND;

    pstRingId->stRingBuffer.bufSize = OM_PCV_BUF_SIZE;
    pstRingId->stRingBuffer.buf     = (VOS_CHAR*)pstAddrInfo->ulBufPhyAddr;

    OM_RingBufferFlush(&(pstRingId->stRingBuffer));

    /* ??ringbuf????????????AHB */
    /*lint -e534*/
    VOS_MemCpy((VOS_CHAR*)(pstAddrInfo->ulMailBoxAddr),
            (VOS_CHAR*)pstRingId, sizeof(OM_PCV_RINGBUFFER_STRU));
    /*lint +e534*/

    pstRingId->stRingBuffer.buf     = (VOS_CHAR*)pstAddrInfo->ulBufVirtAddr;

    return (VOS_OK);
}


VOS_UINT32 OM_PcvGetRBufOffset(OM_RING_ID pstRingId, VOS_UINT_PTR ulAddr)
{
    /*????AHB ringbuf????????????????*/
    pstRingId->pToBuf   = (VOS_INT)(OM_Read32Reg(OM_PCV_RINGBUF_TO_ADDR(ulAddr)));

    /*????AHB ringbuf????????????????*/
    pstRingId->pFromBuf = (VOS_INT)(OM_Read32Reg(OM_PCV_RINGBUF_FROM_ADDR(ulAddr)));

    if ((pstRingId->pToBuf >= pstRingId->bufSize)
        ||(pstRingId->pFromBuf >= pstRingId->bufSize))
    {
        /*lint -e534*/
        LogPrint2("OM_PcvGetRBufOffset:Offset Err, pToBuf:%d, pFromBuf:%d\r\n",
            pstRingId->pToBuf, pstRingId->pFromBuf);
        /*lint +e534*/

        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 OM_PcvComRecv(VOS_UINT8 *pucData, VOS_UINT32 ulLen)
{
    VOS_UCHAR*  pcSendData;
    VOS_UINT32  ulSlice;
    VOS_UINT16  usSendLen;
    VOS_UINT16  usFreeSize;
    OAM_MNTN_PCV_ERRLOG_EVENT_STRU      stErrLog;


    if((VOS_NULL_PTR == pucData)||(0 == ulLen))
    {
        PS_LOG(ACPU_PID_PCVOICE, 0, PS_PRINT_ERROR, "OM_PCV_ComRecv, no data!\n");
        return VOS_ERR;
    }

    /* ??????????????????????10s????50??????????????????????ERRLOG???????????????????????? */
    g_stErrLogFlag.ulRcvNum++;
    if((0 == g_stErrLogFlag.ulFullErr)
        &&(OM_PCV_RCVDATA_TIMES_IN_10S <= g_stErrLogFlag.ulRcvNum))
    {
        g_stErrLogFlag.ul10sFlag++;

        /* ??????10S,????BUF????????????????????ERRLOG */
        if(1 == g_stErrLogFlag.ul10sFlag)
        {
            g_stErrLogFlag.ulFullNum = 0;
        }

        if(OM_PCV_RBUF_FULL_TIMES_IN_10S < g_stErrLogFlag.ulFullNum)
        {
            g_stErrLogFlag.ulFullErr++;     /*????ERRLOG????*/

            /*lint -e534*/
            MNTN_RecordErrorLog(MNTN_OAM_PCV_QUNUE_FULL_EVENT, (void *)&stErrLog,
                                sizeof(OAM_MNTN_PCV_ERRLOG_EVENT_STRU));
            /*lint +e534*/
        }
        /* ??10s???????? */
        g_stErrLogFlag.ulRcvNum = 0;
        g_stErrLogFlag.ulFullNum = 0;
    }

    g_stPcvDebuggingInfo.ulRcvUsbSize += (VOS_UINT32)ulLen;

    /*??????????????????????????????*/
    if(VOS_NULL != (ulLen&0x01))
    {
        ulSlice = VOS_GetSlice();
        OM_PcvSendEvent(OM_APP_PCV_EXCEPTION_IND, &ulSlice, sizeof(VOS_UINT32));

        /* ??????????????????????ERRLOG */
        if(0 != g_stErrLogFlag.ulDataErr)
        {
            return VOS_ERR;
        }

        /* ??Errorlog?????????????????????????? */
        g_stErrLogFlag.ulDataErr++;
        /*lint -e534*/
        MNTN_RecordErrorLog(MNTN_OAM_PCV_DATA_EXCEPTION_EVENT, (void *)&stErrLog,
                                                sizeof(OAM_MNTN_PCV_ERRLOG_EVENT_STRU));
        /*lint +e534*/

        return VOS_ERR;
    }

    if( OM_PCV_USB_OM_ENABLE == (g_ulPcvHookFlag & OM_PCV_USB_OM_ENABLE) )
    {
        /*Bit10 ????????USB-OM????*/
        OM_PcvHookInd( pucData, (VOS_UINT16)ulLen, OM_PCV_USB_OM_BIT,  g_ulUsbHookFrameSN);
        g_ulUsbHookFrameSN++;
    }

    if ( VOS_ERR == OM_PcvGetRBufOffset(&(g_PcvRBufOmToDsp.stRingBuffer), g_stPcvOmToDspAddr.ulMailBoxAddr) )
    {
        PS_LOG(ACPU_PID_PCVOICE, 0, PS_PRINT_ERROR, "OM_PCV_ComRecv, ring buffer be destroy!\n");
        return VOS_ERR;
    }

    usFreeSize = (VOS_UINT16)OM_RingBufferFreeBytes(&(g_PcvRBufOmToDsp.stRingBuffer));

    /*??????????2 byte????*/
    usFreeSize = usFreeSize & 0xFFFE;
    if(usFreeSize >= (VOS_UINT16)ulLen)
    {
         pcSendData  = (VOS_UCHAR*)pucData;
         usSendLen   = (VOS_UINT16)ulLen ;
         g_stPcvDebuggingInfo.ulPutSize += (VOS_UINT32)usSendLen;
    }
    else
    {
        /*????????????????????ringbuf??????????????*/
        pcSendData = (VOS_UCHAR*)&(pucData[ulLen-usFreeSize]);
        usSendLen  = usFreeSize;
        g_stPcvDebuggingInfo.ulPutSize += (VOS_UINT32)usSendLen;

        /*??????????????????????*/
        OM_PcvSendEvent(OM_APP_PCV_BUF_FULL_IND, &g_stPcvDebuggingInfo, sizeof(g_stPcvDebuggingInfo));

        /* ??Errorlog??????????????????????*/
        g_stErrLogFlag.ulFullNum++;

    }

    /*??????????ringbuffer??*/
    (VOS_VOID)OM_RingBufferPut( &(g_PcvRBufOmToDsp.stRingBuffer), (VOS_CHAR*)pcSendData, (VOS_INT)usSendLen );

    VOS_FlushCpuWriteBuf();

    if( OM_PCV_OM_MED_ENABLE == (g_ulPcvHookFlag & OM_PCV_OM_MED_ENABLE) )
    {
        /*Bit8 ????????OM-MED????*/
        OM_PcvHookInd( (VOS_UCHAR*)pcSendData, usSendLen, OM_PCV_OM_MED_BIT,  g_ulOmHookFrameSN);
        g_ulOmHookFrameSN++;
    }

    /* ????ringbuf???????????????? */
    OM_Write32Reg(OM_PCV_RINGBUF_TO_ADDR(g_stPcvOmToDspAddr.ulMailBoxAddr),
                    (VOS_UINT32)(g_PcvRBufOmToDsp.stRingBuffer.pToBuf));

    return VOS_OK;
}


VOS_UINT32 OM_PcvOpen(VOS_UINT32 ulPort)
{
    if(OM_PCV_CHANNEL_CLOSE != g_ulPcvStatus)
    {
        PS_LOG(ACPU_PID_PCVOICE, 0, PS_PRINT_ERROR, "OM_PcvTransStatus, channel has been created!\n");
        return VOS_ERR;
    }

    /* ?????????? */
    /*lint -e534*/
    OM_PcvInitRBuf(&g_PcvRBufOmToDsp, &g_stPcvOmToDspAddr);
    OM_PcvInitRBuf(&g_PcvRBufDspToOm, &g_stPcvDspToOmAddr);
    /*lint +e534*/

    g_ucPcvComPort = (VOS_UINT8)ulPort;

    /* Add by h59254 for V8R1 OM begin */
    CBTCPM_PortRcvReg(OM_PcvComRecv);
    /* Add by h59254 for V8R1 OM end */

    g_ulPcvStatus = OM_PCV_CHANNEL_OPEN;

    return VOS_OK;

}


VOS_UINT32 OM_PcvSwitch(VOS_UINT32 ulPort)
{

    /* ???????? */
    return VOS_ERR;
}


VOS_VOID OM_PcvReleaseAll(VOS_VOID)
{
    /* ????USB???????? */
    if( VOS_NULL_BYTE != g_ucPcvComPort )
    {
        CBTCPM_PortRcvReg(VOS_NULL_PTR);
    }

    g_ulPcvStatus = OM_PCV_CHANNEL_CLOSE;

    g_ucPcvComPort = VOS_NULL_BYTE;

    /* ERRORLOG ?????? */
    /*lint -e534*/
    VOS_MemSet(&g_stErrLogFlag, 0, sizeof(g_stErrLogFlag));
    /*lint +e534*/
    return;
}


VOS_UINT32 OM_PcvClose(VOS_UINT32 ulPort)
{
    if(OM_PCV_CHANNEL_OPEN != g_ulPcvStatus)
    {
        PS_LOG(ACPU_PID_PCVOICE, 0, PS_PRINT_ERROR, "OM_PcvTransStatus, no opened channel!\n");
        return VOS_ERR;
    }

    if(g_ucPcvComPort != (VOS_UINT8)ulPort)
    {
        PS_LOG(ACPU_PID_PCVOICE, 0, PS_PRINT_ERROR, "OM_PcvTransStatus, port number is wrong!\n");
        return VOS_ERR;
    }

    OM_PcvReleaseAll();

    return VOS_OK;
}


VOS_UINT32 OM_PcvTransStatus(VOS_UINT32 ulStatus, VOS_UINT32 ulPort)
{
    VOS_UINT32 ulRet;

    /* record debugging info */
    g_stPcvLog.ulStatus = ulStatus;
    g_stPcvLog.ulPort = ulPort;
    g_stPcvLog.ulCurrentStatus = g_ulPcvStatus;
    g_stPcvLog.ulErrSlice = VOS_GetSlice();

    switch(ulStatus)
    {
        case OM_PCV_CHANNEL_OPEN:
            ulRet = OM_PcvOpen((VOS_UINT8)g_ulPcvPortMap[ulPort]);
            break;

        case OM_PCV_CHANNEL_CLOSE:
            ulRet =  OM_PcvClose((VOS_UINT8)g_ulPcvPortMap[ulPort]);
            break;

        case OM_PCV_CHANNEL_SWITCH:
            ulRet =  OM_PcvSwitch((VOS_UINT8)g_ulPcvPortMap[ulPort]);
            break;

        default:
            PS_LOG(ACPU_PID_PCVOICE, 0, PS_PRINT_ERROR, "OM_PcvTransStatus, command type is unkown!\n");
            return VOS_ERR;
    }

    if ( VOS_OK != ulRet )
    {
        OM_PcvReleaseAll();

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 ?? ?? ??  : OM_PcvSendData
 ????????  : ??PCVOICE??????????PC??
 ????????  : pucVirAddr:   ????????????????
             pucPhyAddr:   ????????????????
             ulDataLen:    ????????
 ????????  : ??
 ?? ?? ??  : VOS_ERR/VOS_OK
 ????????  :
 ????????  :
 ????????  :
   1.??    ??  : 2011??10??8??
     ??    ??  : g47350
     ????????  : Creat Function
*****************************************************************************/
VOS_UINT32 OM_PcvSendData(VOS_UINT8 *pucVirAddr, VOS_UINT8 *pucPhyAddr,VOS_UINT32 ulDataLen)
{
    VOS_INT32                           lRet;
    ACM_WR_ASYNC_INFO                   stVcom;
    /*VOS_UINT32                          ulInSlice;
    VOS_UINT32                          ulOutSlice;
    VOS_UINT32                          ulWriteSlice;*/

    if ((VOS_NULL_PTR == pucVirAddr) || (VOS_NULL_PTR == pucPhyAddr))
    {
        /* ???????? */
        /*lint -e534*/
        LogPrint("\r\nOM_PcvSendData: Vir or Phy Addr is Null \n");
        /*lint +e534*/

        return VOS_ERR;
    }

    stVcom.pVirAddr = (VOS_CHAR *)pucVirAddr;
    stVcom.pPhyAddr = (VOS_CHAR *)pucPhyAddr;
    stVcom.u32Size  = ulDataLen;
    stVcom.pDrvPriv = VOS_NULL_PTR;

    /*g_stAcpuDebugInfo.astPortInfo[OM_USB_CBT_PORT_HANDLE].ulUSBWriteNum1++;

    ulInSlice = OM_GetSlice();*/

    lRet = mdrv_udi_ioctl(g_ulCbtPortUDIHandle, ACM_IOCTL_WRITE_ASYNC, &stVcom);

    /*g_stAcpuDebugInfo.astPortInfo[OM_USB_CBT_PORT_HANDLE].ulUSBWriteNum2++;*/

    /*ulOutSlice = OM_GetSlice();

    if(ulInSlice > ulOutSlice)
    {
        ulWriteSlice = ulInSlice - ulOutSlice;
    }
    else
    {
        ulWriteSlice = ulOutSlice - ulInSlice;
    }

    if(ulWriteSlice > g_stAcpuDebugInfo.astPortInfo[OM_USB_CBT_PORT_HANDLE].ulUSBWriteMaxTime)
    {
        g_stAcpuDebugInfo.astPortInfo[OM_USB_CBT_PORT_HANDLE].ulUSBWriteMaxTime = ulWriteSlice;
    }*/


    if (MDRV_OK == lRet)     /*????????????*/
    {
        if (VOS_OK != VOS_SmP(g_ulCbtUsbPseudoSyncSemId, 0))
        {
            /*lint -e534*/
            LogPrint1("\r\n OM_PcvSendData: mdrv_udi_ioctl Send Data return Error %d\n", lRet);
            /*lint +e534*/
            return VOS_ERR;
        }

        return VOS_OK;
    }
    else if(MDRV_OK > lRet)    /*????????*/
    {
        /*??????????????UDI??????????????*/
        /*lint -e534*/
        LogPrint1("\r\n OM_PcvSendData: mdrv_udi_ioctl Send Data return Error %d\n", lRet);
        /*lint +e534*/

        /*g_stAcpuDebugInfo.astPortInfo[OM_USB_CBT_PORT_HANDLE].ulUSBWriteErrNum++;
        g_stAcpuDebugInfo.astPortInfo[OM_USB_CBT_PORT_HANDLE].ulUSBWriteErrLen    += ulDataLen;
        g_stAcpuDebugInfo.astPortInfo[OM_USB_CBT_PORT_HANDLE].ulUSBWriteErrValue  = (VOS_UINT32)lRet;
        g_stAcpuDebugInfo.astPortInfo[OM_USB_CBT_PORT_HANDLE].ulUSBWriteErrTime   = OM_GetSlice();*/


        return VOS_ERR; /*??????????????????????NULL????????*/
    }
    else    /*????????????????????*/
    {
        /*??????????????UDI????*/
        /*lint -e534*/
        LogPrint1("\r\n OM_PcvSendData: mdrv_udi_ioctl Send Data return Error %d\n", lRet);
        /*lint +e534*/

        VOS_ProtectionReboot(OAM_USB_SEND_ERROR, (VOS_INT)THIS_FILE_ID, (VOS_INT)__LINE__,
                             (VOS_CHAR *)&lRet, sizeof(VOS_INT32));

        return VOS_ERR;
    }

}



VOS_VOID OM_PcvTransmitTaskEntry( VOS_VOID )
{
    VOS_UINT_PTR                        ulRealAddr;
    VOS_UINT16                          usLen;
    VOS_UINT32                          ulHookFrameSN = 0;
    VOS_INT32                           lRet;

    /*lint -e534*/
    VOS_MemSet((VOS_CHAR *)(&g_stPcvDebuggingInfo), 0x00, sizeof(OM_PCV_DEBUGGING_INFO_STRU));
    /*lint +e534*/

    if ( VOS_OK != VOS_SmBCreate( "PCV", 0, VOS_SEMA4_FIFO, &g_ulPcvTransmitSem))
    {
        PS_LOG(ACPU_PID_PCVOICE, 0, PS_PRINT_ERROR,
            "OM_PcvTransmitTaskEntry: creat sem Err");

        g_ulPcvStatus = OM_PCV_CHANNEL_BUTT;

        return;
    }

    /*????????????????(OM->USB)??????????????????*/
    g_stPcvUncacheMemCtrl.pucBuf = (VOS_UCHAR  *)VOS_UnCacheMemAlloc(OM_PCV_BUF_SIZE, &ulRealAddr);

    if ( VOS_NULL_PTR == g_stPcvUncacheMemCtrl.pucBuf)
    {
        PS_LOG(ACPU_PID_PCVOICE, 0, PS_PRINT_ERROR,
            "OM_PcvTransmitTaskEntry: alloc mem Err");

        g_ulPcvStatus = OM_PCV_CHANNEL_BUTT;
        OM_DRV_CACHEDMAM_ALLOC_ERROR();
        return;
    }

    /* ????????????buffer size */
    g_stPcvUncacheMemCtrl.pucRealBuf    = (VOS_UINT8 *)ulRealAddr;
    g_stPcvUncacheMemCtrl.ulBufSize     = OM_PCV_BUF_SIZE;

    /* ERRORLOG ?????? */
    /*lint -e534*/
    VOS_MemSet(&g_stErrLogFlag, 0, sizeof(g_stErrLogFlag));
    /*lint +e534*/

    for ( ; ; )
    {
        if (VOS_OK != VOS_SmP(g_ulPcvTransmitSem, 0))
        {
            /*lint -e534*/
            LogPrint("OM_PcvTransmitTaskEntry: VOS_SmP Fail.\r\n");
            /*lint +e534*/
            continue;
        }

        /* ???????????????????????????????? */
        if(OM_PCV_CHANNEL_OPEN != g_ulPcvStatus)
        {
            /*lint -e534*/
            LogPrint("OM_PcvTransmitTaskEntry: PLL should not power down. \r\n");
            /*lint +e534*/
            OM_PcvSendEvent(OM_APP_PCV_DSP_PLL_OFF, &g_stPcvLog, sizeof(g_stPcvLog));
            continue;
        }

        /* ?????????????????????? */
        if ( VOS_NULL == (OM_PCV_HOOK_ENABLE & g_ulPcvHookFlag) )
        {
            ulHookFrameSN = 0;
            g_ulUsbHookFrameSN = 0;
            g_ulOmHookFrameSN = 0;
        }

        /* ??AHB????????ringbuf???????? */
        if ( VOS_OK != OM_PcvGetRBufOffset(&(g_PcvRBufDspToOm.stRingBuffer), g_stPcvDspToOmAddr.ulMailBoxAddr) )
        {
           VOS_ProtectionReboot(OAM_UL_R99_AHB_HEAD_ERR, VOS_FILE_ID,
                                __LINE__, (VOS_CHAR*)&g_PcvRBufDspToOm, sizeof(g_PcvRBufDspToOm));
            return;
        }

        usLen = (VOS_UINT16)OM_RingBufferNBytes(&(g_PcvRBufDspToOm.stRingBuffer));

        OM_PcvSendEvent(OM_APP_PCV_MED_OM_LEN, &usLen, sizeof(usLen));

        if( 0 == usLen )    /* ringbuf???????? */
        {
            continue;
        }

        /* ??ringbuf???????????????????????? */
        /*lint -e534*/
        OM_RingBufferGet(&(g_PcvRBufDspToOm.stRingBuffer), (VOS_CHAR *)g_stPcvUncacheMemCtrl.pucBuf, (VOS_INT)usLen);
        /*lint +e534*/

        VOS_FlushCpuWriteBuf();

        /* ????AHB??????ringbuf?????????????????? */
        OM_Write32Reg(OM_PCV_RINGBUF_FROM_ADDR(g_stPcvDspToOmAddr.ulMailBoxAddr),
                        (VOS_UINT32)(g_PcvRBufDspToOm.stRingBuffer.pFromBuf));

        g_stPcvDebuggingInfo.ulRcvDspSize += (VOS_UINT32)usLen;

        /* ??????????????USB???? */
        /*lint -e534*/
        OM_PcvSendData(g_stPcvUncacheMemCtrl.pucBuf, g_stPcvUncacheMemCtrl.pucRealBuf, usLen);
        /*lint +e534*/

        OM_PcvSendEvent(OM_APP_PCV_OM_USB_RET, &lRet, sizeof(lRet));

        if( OM_PCV_MED_OM_ENABLE == (g_ulPcvHookFlag & OM_PCV_MED_OM_ENABLE) )
        {
            /* Bit9????????MED-OM???? */
            OM_PcvHookInd( g_stPcvUncacheMemCtrl.pucBuf, usLen, OM_PCV_MED_OM_BIT,  ulHookFrameSN);
            ulHookFrameSN++;
        }

    }
}

/*****************************************************************************
 Prototype       : OM_PcvIpcIsr
 Description     : PC VOICE IPC Interrupt Process.
 Input           : None
 Output          : None
 Return Value    : None

 History         : ---
    Date         : 2011-10-11
    Author       : g47350
    Modification : Created function
 *****************************************************************************/
VOS_VOID OM_PcvIpcIsr(VOS_VOID)
{
    /* HIFI ?????????????? IPC ???? */
    (VOS_VOID)mdrv_ipc_int_disable((IPC_INT_LEV_E)IPC_ACPU_INT_SRC_HIFI_PC_VOICE_RX_DATA);

    if (OM_PCV_CHANNEL_OPEN == g_ulPcvStatus)
    {
        g_stPcvLog.ulIntSlice = VOS_GetSlice();

        /*????0MS????????????????????????*/
        /*lint -e534*/
        VOS_SmV(g_ulPcvTransmitSem);
        /*lint +e534*/
    }

    (VOS_VOID)mdrv_ipc_int_enable((IPC_INT_LEV_E)IPC_ACPU_INT_SRC_HIFI_PC_VOICE_RX_DATA);
}

/*****************************************************************************
Prototype       : OM_PcvMsgProc
Description     : PCVOICE????????????.
Input           : pMsg - ????????????????.
Output          : None
Return Value    : None

History         : ---
   Date         : 2011-09-29
   Author       : g47350
   Modification : Created function
*****************************************************************************/
VOS_VOID OM_PcvMsgProc(MsgBlock *pMsg)
{
    OM_PCV_COM_CFG_REQ      *pstComCfg;
    OM_PCV_TRACE_CFG_REQ    *pstTraceCfg;

    /* ????NAS VC??????????????????????????() */
    if (WUEPS_PID_VC == pMsg->ulSenderPid)
    {
        pstComCfg = (OM_PCV_COM_CFG_REQ*)pMsg;

        /*lint -e534*/
        OM_PcvTransStatus(pstComCfg->ulStatus, pstComCfg->ulPort);
        /*lint +e534*/
    }
    /* ????HIFI?????????????????????????? */
    else if (DSP_PID_VOICE == pMsg->ulSenderPid)
    {
        pstTraceCfg = (OM_PCV_TRACE_CFG_REQ*)pMsg;

        if (ID_VOICE_OM_SET_HOOK_IND == pstTraceCfg->usPrimId)
        {
            g_ulPcvHookFlag = pstTraceCfg->ulPcvHookFlag;
        }
    }
    else
    {
        ;
    }

    return;
}

/*****************************************************************************
Prototype       : OM_PcvPidInit
Description     : PCVOICE PID??????????
Input           :  ip - ??????????.
Output          :  None
Return Value    : VOS_OK:????????????????

History         : ---
   Date         : 2011-09-29
   Author       : g47350
   Modification : Created function
*****************************************************************************/
VOS_UINT32 OM_PcvPidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    /* HIFI ??????A?????????? */
    switch(ip)
    {
        case VOS_IP_LOAD_CONFIG:
            (VOS_VOID)mdrv_ipc_int_connect((IPC_INT_LEV_E)IPC_ACPU_INT_SRC_HIFI_PC_VOICE_RX_DATA, (VOIDFUNCPTR)OM_PcvIpcIsr, 0);
            (VOS_VOID)mdrv_ipc_int_enable((IPC_INT_LEV_E)IPC_ACPU_INT_SRC_HIFI_PC_VOICE_RX_DATA);
/*lint -e413*/
            g_stPcvDspToOmAddr.ulMailBoxAddr = (VOS_UINT_PTR)mdrv_phy_to_virt(MEM_DDR_MODE, (VOS_VOID *)MAILBOX_QUEUE_ADDR(HIFI, ACPU, MSG));
            g_stPcvOmToDspAddr.ulMailBoxAddr = (VOS_UINT_PTR)mdrv_phy_to_virt(MEM_DDR_MODE, (VOS_VOID *)MAILBOX_QUEUE_ADDR(ACPU, HIFI, MSG));
/*lint +e413*/

            /*????uncache????????????*/
            g_stPcvOmToDspAddr.ulBufVirtAddr = (VOS_UINT_PTR)VOS_UnCacheMemAlloc(OM_PCV_BUF_SIZE, &g_stPcvOmToDspAddr.ulBufPhyAddr);

            g_stPcvDspToOmAddr.ulBufVirtAddr = (VOS_UINT_PTR)VOS_UnCacheMemAlloc(OM_PCV_BUF_SIZE, &g_stPcvDspToOmAddr.ulBufPhyAddr);

            if ( VOS_NULL_PTR == g_stPcvOmToDspAddr.ulBufVirtAddr )
            {
                PS_LOG(ACPU_PID_PCVOICE, 0, PS_PRINT_ERROR,
                    "OM_PcvPidInit, Malloc OmToDsp Buffer fail!");

                OM_DRV_CACHEDMAM_ALLOC_ERROR();
                return VOS_ERR;
            }

            if ( VOS_NULL_PTR == g_stPcvDspToOmAddr.ulBufVirtAddr )
            {
                PS_LOG(ACPU_PID_PCVOICE, 0, PS_PRINT_ERROR,
                    "OM_PcvPidInit, Malloc DspToOm Buffer fail!");

                OM_DRV_CACHEDMAM_ALLOC_ERROR();
                return VOS_ERR;
            }
            return VOS_OK;

        default:
            break;
    }

/* HIFI ?????????? */

    return VOS_OK;
}


/*****************************************************************************
 ?? ?? ??  : COMM_VOICE_GetPcVoiceRingBuffCtrlAddr
 ????????  : ????RingBuff????????????????
 ????????  : enDirection - ????????
 ????????  : ??
 ?? ?? ??  : Ring Buff????????????????(??????)
             ??Ring Buff??????????????????????????VOS_NULL

 ????????  : (1) Ring Buff????????????????????COMM_VOICE_RING_BUFFER_CONTROL_STRU
             (2) Ring Buff????????????????????????COMM??(??????2??, ??????????????????????????)
             (3) COMM????????????????????????????????????????????????RingBuff??????????
*****************************************************************************/
VOS_UINT32 COMM_VOICE_GetPcVoiceRingBuffCtrlAddr(COMM_VOICE_PCVOICE_DATA_DIRECTION_ENUM_UINT32 enDirection)
{
    if (COMM_VOICE_PCVOICE_DATA_DIRECTION_TX == enDirection)
    {
        /* ?????????? */
        /*lint -e534*/
        OM_PcvInitRBuf(&g_PcvRBufOmToDsp, &g_stPcvOmToDspAddr);
        /*lint +e534*/

        return (VOS_UINT32)g_stPcvOmToDspAddr.ulMailBoxAddr;
    }

    if (COMM_VOICE_PCVOICE_DATA_DIRECTION_RX == enDirection)
    {
        /* ?????????? */
        /*lint -e534*/
        OM_PcvInitRBuf(&g_PcvRBufDspToOm, &g_stPcvDspToOmAddr);
        /*lint +e534*/
        return (VOS_UINT32)g_stPcvDspToOmAddr.ulMailBoxAddr;
    }

    PS_LOG(ACPU_PID_PCVOICE, 0, PS_PRINT_ERROR, "COMM_VOICE_GetPcVoiceRingBuffCtrlAddr, Para is error!\n");

    return VOS_NULL;

}

/*****************************************************************************
 ?? ?? ??  : COMM_VOICE_TransferPcVoiceRxData
 ????????  : ????????????????
 ????????  : ??
 ????????  : ??
 ?? ?? ??  : VOS_OK  - ????????
             VOS_ERR - ????????

 ????????  : (1) VOICE??????????????Ring Buff????????????????COMM????????????USB

*****************************************************************************/
VOS_UINT32 COMM_VOICE_TransferPcVoiceRxData(VOS_VOID)
{
    return VOS_OK;
}

/*****************************************************************************
 Prototype       : OM_AcpuFidInit
 Description     : ACPU OM FID' initializtion function
 Input           : None
 Output          : None
 Return Value    : VOS_UINT32

 History         : ---
    Date         : 2011-07-01
    Author       : g47350
    Modification : Created function
 *****************************************************************************/
VOS_UINT32 PCV_AcpuFidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32                          ulRslt;
    APP_VC_NVIM_PC_VOICE_SUPPORT_FLAG_STRU  stPcvConfig;

    switch( ip )
    {
        case VOS_IP_LOAD_CONFIG:
        {
            /*????PcVoice??NV????????*/
            if(NV_OK!= NV_Read(en_NV_Item_PCVOICE_Support_Flg, &stPcvConfig, sizeof(APP_VC_NVIM_PC_VOICE_SUPPORT_FLAG_STRU)))
            {
                stPcvConfig.usPcVoiceSupportFlag =  VOS_FALSE;
            }

            /*????PcVoice??NV??????????1????????????*/
            if(VOS_TRUE == stPcvConfig.usPcVoiceSupportFlag)
            {
                /* ????OM_PCV?????????????? */
                ulRslt = VOS_RegisterSelfTask(ACPU_FID_PCVOICE,
                                             (VOS_TASK_ENTRY_TYPE)OM_PcvTransmitTaskEntry,
                                             VOS_PRIORITY_P2, PCV_TRANS_TASK_STACK_SIZE);
                if ( VOS_NULL_BYTE == ulRslt )
                {
                    return VOS_ERR;
                }

                ulRslt = VOS_RegisterPIDInfo(ACPU_PID_PCVOICE,
                                            (Init_Fun_Type)OM_PcvPidInit,
                                            (Msg_Fun_Type)OM_PcvMsgProc);
                if( VOS_OK != ulRslt )
                {
                    return VOS_ERR;
                }
            }

            ulRslt = VOS_RegisterMsgTaskPrio(ACPU_FID_PCVOICE, VOS_PRIORITY_M2);
            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            break;
        }

        default:
            break;
    }
    return VOS_OK;
}


/*****************************************************************************
 ?? ?? ??  : OM_PcvLogShow
 ????????  : ????????????
 ????????  : ??
 ????????  : ??
 ?? ?? ??  : ??

 ????????  :
   1.??    ??  : 2013??06??18??
     ??    ??  : d00212987
     ????????  : Creat Function
*****************************************************************************/
VOS_VOID OM_PcvLogShow(VOS_VOID)
{
    /*lint -e534*/
    vos_printf("\r\n g_ulPcvStatus is   %d", g_ulPcvStatus);
    vos_printf("\r\n g_ucPcvComPort is  %d\r\n", g_ucPcvComPort);

    vos_printf("\r\n g_stErrLogFlag.ulDataErr =  %d", g_stErrLogFlag.ulDataErr);
    vos_printf("\r\n g_stErrLogFlag.ulFullErr =  %d", g_stErrLogFlag.ulFullErr);
    vos_printf("\r\n g_stErrLogFlag.ulRcvNum  =  %d", g_stErrLogFlag.ulRcvNum);
    vos_printf("\r\n g_stErrLogFlag.ulFullNum =  %d", g_stErrLogFlag.ulFullNum);
    vos_printf("\r\n g_stErrLogFlag.ul10sFlag =  %d\r\n", g_stErrLogFlag.ul10sFlag);

    vos_printf("\r\n g_stPcvDebuggingInfo.ulRcvUsbSize =  %d", g_stPcvDebuggingInfo.ulRcvUsbSize);
    vos_printf("\r\n g_stPcvDebuggingInfo.ulPutSize    =  %d", g_stPcvDebuggingInfo.ulPutSize);
    vos_printf("\r\n g_stErrLogFlag.ulRcvNum           =  %d\r\n", g_stPcvDebuggingInfo.ulRcvDspSize);

    vos_printf("\r\n g_stPcvLog.ulStatus        =  %d", g_stPcvLog.ulStatus);
    vos_printf("\r\n g_stPcvLog.ulPort          =  %d", g_stPcvLog.ulPort);
    vos_printf("\r\n g_stPcvLog.ulCurrentStatus =  %d", g_stPcvLog.ulCurrentStatus);
    vos_printf("\r\n g_stPcvLog.ulIntSlice      =  %d", g_stPcvLog.ulIntSlice);
    vos_printf("\r\n g_stPcvLog.ulErrSlice      =  %d\r\n", g_stPcvLog.ulErrSlice);
    /*lint +e534*/

    return;
}


