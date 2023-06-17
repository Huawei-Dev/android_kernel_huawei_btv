/*
 * 
 * All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses. You may choose this file to be licensed under the terms
 * of the GNU General Public License (GPL) Version 2 or the 2-clause
 * BSD license listed below:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

/******************************************************************************
   ??????????
******************************************************************************/
#include "PPP/Inc/hdlc_software.h"



/*****************************************************************************
   1 ??????????????????????.C??????????
*****************************************************************************/
/*lint -e767 */
#define    THIS_FILE_ID        PS_FILE_ID_HDLC_SOFTWARE_C
/*lint +e767 */

/******************************************************************************
   2 ????????????????
******************************************************************************/
extern struct ppp_mbuf *
async_TtfMemLayerPush(struct link *l, VOS_UINT8 *pHdr, VOS_UINT16 usHdrLen, PPP_ZC_STRU *bp,
                VOS_INT32 pri, VOS_UINT16 *proto);

extern PPP_ZC_STRU *
hdlc_LayerPull(/*struct bundle *b, */struct link *l, PPP_ZC_STRU *bp,
               VOS_UINT16 *proto);

extern PPP_ZC_STRU *
async_Decode(struct async *async, VOS_CHAR c);

extern PPP_ZC_STRU *
acf_LayerPull(/*struct bundle *b, */struct link *l, PPP_ZC_STRU *bp, VOS_UINT16 *proto);

extern PPP_ZC_STRU *proto_LayerPull(/*struct bundle *b, */struct link *l, PPP_ZC_STRU *pstMem,
                VOS_UINT16 *pusProto);

extern struct ppp_mbuf *
proto_LayerPush(/*struct bundle *b, */struct link *l, struct ppp_mbuf *bp,
                VOS_INT32 pri, VOS_UINT16 *proto);
extern struct ppp_mbuf *
acf_LayerPush(/*struct bundle *b, */struct link *l, struct ppp_mbuf *bp,
              VOS_INT32 pri, VOS_UINT16 *proto);

extern struct ppp_mbuf *
async_LayerPush(/*struct bundle *bundle, */struct link *l, struct ppp_mbuf *bp,
                VOS_INT32 pri, VOS_UINT16 *proto);

extern VOS_UINT32 PPP_SendPushedData(VOS_UINT16 usPppId, VOS_UINT8 *pucDataBuf, VOS_UINT16 usLen);


/*****************************************************************************
   3 ????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                  ulUplinkIpDataProcCnt;             /* ????IP?????????????? */
    VOS_UINT32                  ulUplinkPppDataProcCnt;            /* ????????PPP?????????? */

    VOS_UINT32                  ulDownlinkIpDataProcCnt;           /* ????IP?????????????? */
    VOS_UINT32                  ulDownlinkPppDataProcCnt;          /* ????????PPP?????????? */

    VOS_UINT32                  ulMaxCntOnce;                      /* PPP?????????????????????? */
} PPP_HDLC_SOFT_DATA_PROC_STAT_ST;


/*****************************************************************************
   4 ????????????
*****************************************************************************/
PPP_HDLC_SOFT_DATA_PROC_STAT_ST g_PppHdlcSoftStat = {0};


/******************************************************************************
   5 ????????
******************************************************************************/
VOS_VOID PPP_HDLC_SOFT_MntnShowStatInfo(VOS_VOID)
{
    vos_printf("\n================HDLC Software STAT INFO Begin==========================\n");

    vos_printf("????????IP????????????    = %d\n", g_PppHdlcSoftStat.ulUplinkIpDataProcCnt);
    vos_printf("????????PPP????????????   = %d\n", g_PppHdlcSoftStat.ulUplinkPppDataProcCnt);
    vos_printf("????????IP????????????    = %d\n", g_PppHdlcSoftStat.ulDownlinkIpDataProcCnt);
    vos_printf("????????PPP????????????   = %d\n", g_PppHdlcSoftStat.ulDownlinkPppDataProcCnt);
    vos_printf("????????????????????   = %d\n", g_PppHdlcSoftStat.ulMaxCntOnce);

    vos_printf("================HDLC Software STAT INFO End==========================\n");
}

/*lint -e574*/
void link_PushTtfMemPacket(struct link *l, PPP_ZC_STRU *bp, VOS_INT32 pri, VOS_UINT16 proto)
{
    VOS_UINT8   aucPppDataHdr[4];
    VOS_UINT16  usHdrLen=0;


    /*
    * When we ``push'' a packet into the link, it gets processed by the
    * ``push'' function in each layer starting at the top.
    * We never expect the result of a ``push'' to be more than one
    * packet (as we do with ``pull''s).
    */

    if( (pri < 0) || (pri >= LINK_QUEUES(l)) )
    {
        pri = 0;
    }

    /*
    bp = proto_LayerPush(l, bp, pri, &proto);
    bp = acf_LayerPush(l, bp, pri, &proto);
    bp = async_LayerPush(l, bp, pri, &proto);
    */


    /* Address and Control */
    if ( (proto == PROTO_LCP) || (l->lcp.his_acfcomp == 0) )
    {
        aucPppDataHdr[usHdrLen++] = HDLC_ADDR;
        aucPppDataHdr[usHdrLen++] = HDLC_UI;
    }

    /* ???????????????????????? */
    /*??????????????????????????????????*/
    if ( (l->lcp.his_protocomp) && (((VOS_UINT8)(proto >> 8)) == 0))
    {
        aucPppDataHdr[usHdrLen++]   = proto & 0xff;
    }
    else
    {
        aucPppDataHdr[usHdrLen++]   = proto >> 8;
        aucPppDataHdr[usHdrLen++]   = proto & 0xff;
    }

    async_TtfMemLayerPush(l, aucPppDataHdr, usHdrLen, bp, pri, &proto);

} /* link_PushTtfMemPacket */
/*lint +e574*/

void link_PullMemPacket(struct link *l, PPP_ZC_STRU *pstMem)
{
    PPP_ZC_STRU      *pLastMem;
    PPP_ZC_STRU      *pTmpMem;
    VOS_UINT32        ulCnt;
    VOS_UINT16        usProto;
    VOS_UINT16        usLen;
    VOS_UINT8        *pucData;


    /*
    while (VOS_NULL_PTR != pstMem)
    {
    */
        usLen = PPP_ZC_GET_DATA_LEN(pstMem);

        for (ulCnt = 0; ulCnt < usLen; ulCnt++)
        {
            pucData     = PPP_ZC_GET_DATA_PTR(pstMem);
            pLastMem    = async_Decode(&l->async, (VOS_CHAR)(pucData[ulCnt]));

            /* ??????????????PPP????????HDLC->ACF->Protocol?????????????????? */
            if (VOS_NULL_PTR != pLastMem)
            {
                pLastMem    = hdlc_LayerPull(l, pLastMem, &usProto);

                if (VOS_NULL_PTR != pLastMem)
                {
                    pLastMem    = acf_LayerPull(l, pLastMem, &usProto);
                }

                if (VOS_NULL_PTR != pLastMem)
                {
                    pLastMem    = proto_LayerPull(l, pLastMem, &usProto);
                }

                if (VOS_NULL_PTR != pLastMem)
                {
                    /* ??????????????????????????????????????????????????????????????
                       ????????MAC??????????NDIS???? */

                    pTmpMem = pLastMem;

                    pLastMem = PPP_MemCopyAlloc(PPP_ZC_GET_DATA_PTR(pTmpMem),
                                            PPP_ZC_GET_DATA_LEN(pTmpMem),
                                            PPP_ZC_UL_RESERVE_LEN);

                    PPP_MemFree(pTmpMem);
                }

                if (VOS_NULL_PTR != pLastMem)
                {
                    PPP_HDLC_ProcIpModeUlData(/*b, */l, pLastMem, usProto);
                }
            }
        } /* for cnt */

        PPP_MemFree(pstMem);
    /*
    }
    */
}

/*****************************************************************************
 Prototype      : Ppp_FrameEncap
 Description    : ????PPP????????????????????????????????????PPP??????????
                  ??????????????????TE????

 Input          : ---
 Output         : ---??????
 Return Value   : ---
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2006-5-25
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 Ppp_FrameEncap(PPP_ID PppId, PPP_ZC_STRU *pstData)
{
    VOS_UINT16          proto;
    VOS_UINT8           aucProto[2];
    VOS_UINT32          ulRtn;


    /* ????????????????1????2?????? */
    ulRtn   = PPP_MemCutHeadData(&pstData, &aucProto[0], 1);

    if (PS_FAIL == ulRtn)
    {
        PPP_MemFree(pstData);
        return VOS_ERR;
    }

    if ( 0x01 == (aucProto[0] & 0x01) )     /* ??????????LSB??1?????????????????????????????????????? */
    {
        proto = ((VOS_UINT16)(aucProto[0]));
        PPP_LINK(PppId)->lcp.his_protocomp  = 1;
    }
    else
    {
        ulRtn   = PPP_MemCutHeadData(&pstData, &aucProto[1], 1);

        if (PS_FAIL == ulRtn)
        {
            PPP_MemFree(pstData);
            return VOS_ERR;
        }

        proto = ( (((VOS_UINT16)(aucProto[0]))<<8) | (aucProto[1]) );
        PPP_LINK(PppId)->lcp.his_protocomp  = 0;
    }

    if (VOS_NULL_PTR == pstData)
    {
        return VOS_ERR;
    }


    /* ??????????????????????????????IP???????????????????????? */
    link_PushTtfMemPacket(PPP_LINK(PppId), pstData, 0, proto);

    return VOS_OK;
}



/*****************************************************************************
 Prototype      : Ppp_FrameDecap
 Description    : ????PPP??????????????????TE??????????????PPP????????
                  ????????????????????????????

 Input          : ---
 Output         :
 Return Value   : VOS_NULL                       //????
                  ppp_mbuf *bp                   //??????????????????
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2006-5-25
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 Ppp_FrameDecap(PPP_ID PppId, PPP_ZC_STRU *pstMem)
{
    PPP_ZC_STRU      *pLastMem;
    VOS_UINT16        usCnt;
    VOS_UINT16        usProto;
    struct link      *l;
    VOS_UINT16        usLen;


    l     = PPP_LINK(PppId);
    usLen = PPP_ZC_GET_DATA_LEN(pstMem);

    /*
    while (VOS_NULL_PTR != pstMem)
    {
    */
        for (usCnt = 0; usCnt < usLen; usCnt++)
        {
            pLastMem = async_Decode(&l->async, (VOS_CHAR)(PPP_ZC_GET_DATA_PTR(pstMem)[usCnt]));

            if (pLastMem != VOS_NULL_PTR)
            {
                /* ??????????????PPP????????HDLC->ACF??????????
                ????PPP????PDP????????????????????????????????Protocol?????????? */
                pLastMem    = hdlc_LayerPull(l, pLastMem, &usProto);

                if (VOS_NULL_PTR != pLastMem)
                {
                    pLastMem    = acf_LayerPull(l, pLastMem, &usProto);
                }

                if (VOS_NULL_PTR != pLastMem)
                {
                    PPP_HDLC_ProcPppModeUlData(PppId, pLastMem);
                }
            }
        } /* for cnt */

        PPP_MemFree(pstMem);
    /*
    }
    */

    return VOS_OK;
}

/*fanzhibin f49086 add it end*/

PPP_HDLC_RESULT_TYPE_ENUM_UINT32 PPP_HDLC_SOFT_ProcData
(
    PPP_ID usPppId,
    struct link *pstLink,
    PPP_ZC_QUEUE_STRU *pstDataQ
)
{
    PPP_ZC_STRU                        *pstMem;
    VOS_UINT32                          ulDealCnt = 0;
    PPP_DATA_TYPE_ENUM_UINT8            ucDataType;

    for (;;)
    {
        pstMem  = (PPP_ZC_STRU *)PPP_ZC_DEQUEUE_HEAD(pstDataQ);

        /* ???????????????????????? */
        if ( VOS_NULL_PTR == pstMem )
        {
            return PPP_HDLC_RESULT_COMM_FINISH;
        }

        /*??????????(??????????????????????????????????????????????????????)*/
        ucDataType = (PPP_ZC_GET_DATA_APP(pstMem) & 0x00FF);

        switch ( ucDataType )
        {
            case PPP_PULL_PACKET_TYPE:
                g_PppHdlcSoftStat.ulUplinkIpDataProcCnt++;

                link_PullMemPacket(pstLink, pstMem);
                break;
            case PPP_PUSH_PACKET_TYPE:
                g_PppHdlcSoftStat.ulDownlinkIpDataProcCnt++;

                link_PushTtfMemPacket(pstLink, pstMem, 0, PROTO_IP);
                break;
            case PPP_PULL_RAW_DATA_TYPE:
                g_PppHdlcSoftStat.ulUplinkPppDataProcCnt++;

                Ppp_FrameDecap(usPppId, pstMem);
                break;
            case PPP_PUSH_RAW_DATA_TYPE:
                g_PppHdlcSoftStat.ulDownlinkPppDataProcCnt++;

                Ppp_FrameEncap(usPppId, pstMem);
                break;
            default:
                PPP_MemFree(pstMem);
                PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, LOG_LEVEL_WARNING,
                              "PPP_ProcDataNotify, WARNING, ucDataType %d is Abnormal!", ucDataType);
                break;
        }

        /*????*/
        ulDealCnt++;

        if ( ulDealCnt > g_PppHdlcSoftStat.ulMaxCntOnce )
        {
            g_PppHdlcSoftStat.ulMaxCntOnce = ulDealCnt;
        }

        /*????????????????????????????????????????????????????????
          ????????????????PPP_DATA_PROC_NOTIFY????*/
        if ( ulDealCnt >= PPP_ONCE_DEAL_MAX_CNT )
        {
            return PPP_HDLC_RESULT_COMM_CONTINUE;
        }
    } /* for (;;) */
}

/*****************************************************************************
 ?? ?? ??  : PPP_HDLC_SOFT_ProcProtocolPacket
 ????????  : ????????PPP??????????????????
 ????????  : pstLink    -   PPP????????
             pstMbuf    -   PPP??????????????????
             ulPri      -   ??????
             usProto    -   ????????????????
 ????????  : ??
 ?? ?? ??  : ??
 ????????  :
 ????????  :

 ????????      :
  1.??    ??   : 2012??4??10??
    ??    ??   : l00164359
    ????????   : ??????????

*****************************************************************************/
VOS_VOID PPP_HDLC_SOFT_ProcProtocolPacket
(
    struct link     *l,
    struct ppp_mbuf *bp,
    VOS_INT32       pri,
    VOS_UINT16      proto
)
{
    /*
    * When we ``push'' a packet into the link, it gets processed by the
    * ``push'' function in each layer starting at the top.
    * We never expect the result of a ``push'' to be more than one
    * packet (as we do with ``pull''s).
    */
    /*lint  -e574 -e960*/
    if(pri < 0 || pri >= LINK_QUEUES(l))
        pri = 0;
    /*lint  +e574 +e960*/

    bp = proto_LayerPush(l, bp, pri, &proto);
    bp = acf_LayerPush(l, bp, pri, &proto);
    (VOS_VOID)async_LayerPush(l, bp, pri, &proto);


    return;
}



