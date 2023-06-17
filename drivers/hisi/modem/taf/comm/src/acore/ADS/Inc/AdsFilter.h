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

#ifndef __ADSFILTER_H__
#define __ADSFILTER_H__

/*****************************************************************************
  1 ??????????????
*****************************************************************************/
#include "vos.h"
#include "AdsDeviceInterface.h"
#include "hi_list.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 ??????
*****************************************************************************/
#define ADS_FILTER_MAX_LIST_NUM                 (256)
#define ADS_FILTER_DEFAULT_AGING_TIMELEN        (60)
#define ADS_FILTER_SECOND_TRANSFER_JIFFIES      (1000)

#define ADS_FILTER_IPV4_HDR_LEN                 (20)            /* IPv4 ???????? */
#define ADS_FILTER_ICMP_HDR_LEN                 (8)             /* ICMP ???????? */

#define ADS_MAX_IPV4_ADDR_LEN                   (16)            /* IPv4?????????????????? */

#define ADS_IPPROTO_ICMP                        (0x01)          /* ICMP protocol */
#define ADS_IPPROTO_IGMP                        (0x02)          /* IGMP protocol */
#define ADS_IPPROTO_TCP                         (0x06)          /* TCP protocol */
#define ADS_IPPROTO_UDP                         (0x11)          /* UDP protocol */

#define ADS_IP_CE                               (0x8000)        /* Flag: "Congestion" */
#define ADS_IP_DF                               (0x4000)        /* Flag: "Don't Fragment" */
#define ADS_IP_MF                               (0x2000)        /* Flag: "More Fragments" */
#define ADS_IP_OFFSET                           (0x1FFF)        /* "Fragment Offset" part */

/* ICMP??????type?????????? */
#define ADS_ICMP_ECHOREPLY                      (0)             /* Echo Reply           */
#define ADS_ICMP_DEST_UNREACH                   (3)             /* Destination Unreachable  */
#define ADS_ICMP_SOURCE_QUENCH                  (4)             /* Source Quench        */
#define ADS_ICMP_REDIRECT                       (5)             /* Redirect (change route)  */
#define ADS_ICMP_ECHOREQUEST                    (8)             /* Echo Request         */
#define ADS_ICMP_TIME_EXCEEDED                  (11)            /* Time Exceeded        */
#define ADS_ICMP_PARAMETERPROB                  (12)            /* Parameter Problem    */
#define ADS_ICMP_TIMESTAMP                      (13)            /* Timestamp Request    */
#define ADS_ICMP_TIMESTAMPREPLY                 (14)            /* Timestamp Reply      */
#define ADS_ICMP_INFO_REQUEST                   (15)            /* Information Request  */
#define ADS_ICMP_INFO_REPLY                     (16)            /* Information Reply    */
#define ADS_ICMP_ADDRESS                        (17)            /* Address Mask Request */
#define ADS_ICMP_ADDRESSREPLY                   (18)            /* Address Mask Reply   */

/* ?????????????????????????? */
#define ADS_FILTER_ARRAY_SIZE(a)                (sizeof((a)) / sizeof((a[0])))

#define ADS_FILTER_GET_IPV6_ADDR()              (&g_stAdsFilterCtx.unIPv6Addr)
#define ADS_FILTER_GET_LIST(index)              (&(g_stAdsFilterCtx.astLists[index]))
#define ADS_FILTER_GET_AGING_TIME_LEN()         (g_stAdsFilterCtx.ulAgingTimeLen)
#define ADS_FILTER_SET_AGING_TIME_LEN(len)      (g_stAdsFilterCtx.ulAgingTimeLen = (len))

#define ADS_FILTER_GET_DL_ICMP_FUNC_TBL_ADDR(ucType)     (&(g_astAdsFilterDecodeDlIcmpFuncTbl[ucType]))
#define ADS_FILTER_GET_DL_ICMP_FUNC_TBL_SIZE()           (ADS_FILTER_ARRAY_SIZE(g_astAdsFilterDecodeDlIcmpFuncTbl))

/* ?????????????????????? */
#define ADS_FILTER_DBG_GET_STATS_ARRAY_ADDR()            (&g_aulAdsFilterStats[0])
#define ADS_FILTER_DBG_GET_STATS_BY_INDEX(enPktType)     (g_aulAdsFilterStats[enPktType])
#define ADS_FILTER_DBG_STATISTIC(enPktType, n)           (g_aulAdsFilterStats[enPktType] += (n))

#define ADS_FILTER_MALLOC(size)                 ADS_FILTER_HeapAlloc(size)
#define ADS_FILTER_FREE(addr)                   ADS_FILTER_HeapFree(addr)

/* ???????????????????? */
#define ADS_FILTER_IS_AGED(time)\
    ((0 != ADS_FILTER_GET_AGING_TIME_LEN()) \
   &&(time_after_eq(jiffies, (ADS_FILTER_GET_AGING_TIME_LEN() + (time)))))

/* ????IP???????????????????????? ADS_FILTER_IPV4_HEADER_STRU */
#define ADS_FILTER_IS_IPHDR_MATCH(ipheader1, ipheader2)\
    ( ((ipheader1)->ulSrcAddr == (ipheader2)->ulSrcAddr) \
   && ((ipheader1)->ulDstAddr == (ipheader2)->ulDstAddr) \
   && ((ipheader1)->ucProtocol == (ipheader2)->ucProtocol) )

/* ????TCP???????????????????? ADS_FILTER_IPV4_TCP_STRU */
#define ADS_FILTER_IS_TCP_PKT_MATCH(tcppkt1, tcppkt2)\
    ( ((tcppkt1)->usSrcPort == (tcppkt2)->usSrcPort) \
   && ((tcppkt1)->usDstPort == (tcppkt2)->usDstPort) )

/* ????UDP???????????????????? ADS_FILTER_IPV4_UDP_STRU */
#define ADS_FILTER_IS_UDP_PKT_MATCH(udppkt1, udppkt2)\
    ( ((udppkt1)->usSrcPort == (udppkt2)->usSrcPort) \
   && ((udppkt1)->usDstPort == (udppkt2)->usDstPort) )

/* ????ICMP???????????????????? ADS_FILTER_IPV4_ICMP_STRU */
#define ADS_FILTER_IS_ICMP_PKT_MATCH(icmppkt1, icmppkt2)\
    ( ((icmppkt1)->usIdentifier == (icmppkt2)->usIdentifier) \
   && ((icmppkt1)->usSeqNum == (icmppkt2)->usSeqNum) )

/* ???????????????????????????? ADS_FILTER_IPV4_FRAGMENT_STRU */
#define ADS_FILTER_IS_FRAGMENT_MATCH(fragmentpkt1, fragmentpkt2)\
        ( (fragmentpkt1)->usIdentification == (fragmentpkt2)->usIdentification)

/* ????IPV6???????????? ADS_IPV6_ADDR_UN */
#define ADS_FILTER_IS_IPV6_ADDR_IDENTICAL(punIpv6Addr1, punIpv6Addr2) \
    (0 == ( ((punIpv6Addr1)->aulIpAddr[0] ^ (punIpv6Addr2)->aulIpAddr[0]) | \
            ((punIpv6Addr1)->aulIpAddr[1] ^ (punIpv6Addr2)->aulIpAddr[1]) | \
            ((punIpv6Addr1)->aulIpAddr[2] ^ (punIpv6Addr2)->aulIpAddr[2]) | \
            ((punIpv6Addr1)->aulIpAddr[3] ^ (punIpv6Addr2)->aulIpAddr[3]) ) )


/* ????????????????????:
    ????TCP\UCP????????????????????????????8??,
    ????ICMP??????????????????Sequence Num??8??,
    ??????????????(??????)????IP Identification??8?????????? */
#define ADS_FILTER_GET_INDEX(pfilter) \
    ((VOS_UINT8)(VOS_NTOHS(*((VOS_UINT16 *)&((pfilter)->unFilter))) & 0xFF))


/*lint -e778 */
/*lint -e572 */
#ifndef VOS_NTOHL                   /* ??????????????*/
#if VOS_BYTE_ORDER==VOS_BIG_ENDIAN
#define VOS_NTOHL(x)    (x)
#define VOS_HTONL(x)    (x)
#define VOS_NTOHS(x)    (x)
#define VOS_HTONS(x)    (x)
#else
#define VOS_NTOHL(x)    ((((x) & 0x000000ffU) << 24) | \
                         (((x) & 0x0000ff00U) <<  8) | \
                         (((x) & 0x00ff0000U) >>  8) | \
                         (((x) & 0xff000000U) >> 24))

#define VOS_HTONL(x)    ((((x) & 0x000000ffU) << 24) | \
                         (((x) & 0x0000ff00U) <<  8) | \
                         (((x) & 0x00ff0000U) >>  8) | \
                         (((x) & 0xff000000U) >> 24))

#define VOS_NTOHS(x)    ((((x) & 0x00ff) << 8) | \
                         (((x) & 0xff00) >> 8))

#define VOS_HTONS(x)    ((((x) & 0x00ff) << 8) | \
                         (((x) & 0xff00) >> 8))
#endif  /* _BYTE_ORDER==_LITTLE_ENDIAN */
#endif
/*lint -e572 */
/*lint -e778 */


/*****************************************************************************
  3 ????????
*****************************************************************************/
/*****************************************************************************
??????    : ADS_FILTER_PKT_TYPE_ENUM
????????  : ADS??????????????

  1.??    ??   : 2013??6??3??
    ??    ??   : L47619
    ????????   : V3R3 Share-PDP????????
*****************************************************************************/
enum ADS_FILTER_PKT_TYPE_ENUM
{
    ADS_FILTER_PKT_TYPE_TCP,                                /* ????????????TCP */
    ADS_FILTER_PKT_TYPE_UDP,                                /* ????????????UDP */
    ADS_FILTER_PKT_TYPE_ICMP,                               /* ????????????ICMP */
    ADS_FILTER_PKT_TYPE_FRAGMENT,                           /* ??????????????????(??????) */

    ADS_FILTER_PKT_TYPE_BUTT
};
typedef VOS_UINT32 ADS_FILTER_PKT_TYPE_ENUM_UINT32;

/*****************************************************************************
??????    : ADS_FILTER_ORIG_PKT_ENUM
????????  : ADS??????????????????

  1.??    ??   : 2013??6??14??
    ??    ??   : L47619
    ????????   : V3R3 Share-PDP????????
*****************************************************************************/
enum ADS_FILTER_ORIG_PKT_ENUM
{
    ADS_FILTER_ORIG_PKT_UL_IPV4_TCP,                                   /* ????????????????????IPv4 TCP */
    ADS_FILTER_ORIG_PKT_UL_IPV4_UDP,                                   /* ????????????????????IPv4 UDP */
    ADS_FILTER_ORIG_PKT_UL_IPV4_ECHOREQ,                               /* ????????????????????IPv4 ECHO REQ */
    ADS_FILTER_ORIG_PKT_UL_IPV4_NOT_FIRST_FRAGMENT,                    /* ????????????????????IPv4 ??????(??????) */
    ADS_FILTER_ORIG_PKT_UL_IPV4_NOT_SUPPORT,                           /* ????????????????????????????IPv4???? */
    ADS_FILTER_ORIG_PKT_UL_IPV6_PKT,                                   /* ????????????????????IPv6???? */

    ADS_FILTER_ORIG_PKT_DL_IPV4_TCP,                                   /* ????????????????????IPv4 TCP */
    ADS_FILTER_ORIG_PKT_DL_IPV4_UDP,                                   /* ????????????????????IPv4 UDP */
    ADS_FILTER_ORIG_PKT_DL_IPV4_ECHOREPLY,                             /* ????????????????????IPv4 ECHO REPLY */
    ADS_FILTER_ORIG_PKT_DL_IPV4_ICMPERROR,                             /* ????????????????????IPv4 ICMP???????? */
    ADS_FILTER_ORIG_PKT_DL_IPV4_FIRST_FRAGMENT,                        /* ????????????????????IPv4 ??????(????) */
    ADS_FILTER_ORIG_PKT_DL_IPV4_NOT_FIRST_FRAGMENT,                    /* ????????????????????IPv4 ??????(??????) */
    ADS_FILTER_ORIG_PKT_DL_IPV6_PKT,                                   /* ????????????????????IPv6?? */

    ADS_FILTER_ORIG_PKT_BUTT
};
typedef VOS_UINT32 ADS_FILTER_ORIG_PKT_ENUM_UINT32;

/*****************************************************************************
  4 ????????????
*****************************************************************************/


/*****************************************************************************
  5 ??????????
*****************************************************************************/


/*****************************************************************************
  6 ????????
*****************************************************************************/

/*****************************************************************************
  7 UNION????
*****************************************************************************/
/*****************************************************************************
 ????????     : ADS_IPV4_ADDR_UN
 ??????????   : IPV4????
 1.??    ??   : 2013??06??03??
   ??    ??   : L47619
   ????????   : V3R3 Share-PDP????????
*****************************************************************************/
typedef union
{
    VOS_UINT8                           aucIpAddr[ADS_IPV4_ADDR_LEN];
    VOS_UINT32                          ulIpAddr;
} ADS_IPV4_ADDR_UN;

/*****************************************************************************
 ????????     : ADS_IPV6_ADDR_UN
 ??????????   : IPV6????
 1.??    ??   : 2013??06??03??
   ??    ??   : L47619
   ????????   : V3R3 Share-PDP????????
*****************************************************************************/
typedef union
{
    VOS_UINT8                           aucIpAddr[ADS_IPV6_ADDR_LEN];
    VOS_UINT16                          ausIpAddr[ADS_IPV6_ADDR_HALF_LEN];
    VOS_UINT32                          aulIpAddr[ADS_IPV6_ADDR_QUARTER_LEN];
} ADS_IPV6_ADDR_UN;

/*****************************************************************************
  8 STRUCT????
*****************************************************************************/
/*****************************************************************************
 ??????    : ADS_IPV4_HDR_STRU
 ????????  : IPV4????
 1.??    ??   : 2013??06??03??
   ??    ??   : L47619
   ????????   : V3R3 Share-PDP????????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIpHdrLen          : 4;                /* header length */
    VOS_UINT8                           ucIpVersion         : 4;                /* version */
    VOS_UINT8                           ucTypeOfService;                        /* type of service */
    VOS_UINT16                          usTotalLen;                             /* total length */
    VOS_UINT16                          usIdentification;                       /* identification */
    VOS_UINT16                          usFlags_fo;                             /* flags and fragment offset field */
    VOS_UINT8                           ucTTL;                                  /* time to live*/
    VOS_UINT8                           ucProtocol;                             /* protocol */
    VOS_UINT16                          usCheckSum;                             /* checksum */
    ADS_IPV4_ADDR_UN                    unSrcAddr;                              /* source address */
    ADS_IPV4_ADDR_UN                    unDstAddr;                              /* dest address */
} ADS_IPV4_HDR_STRU;

/*****************************************************************************
 ??????    : ADS_IPV6_HDR_STRU
 ????????  : IPV6????
 1.??    ??   : 2013??06??03??
   ??    ??   : L47619
   ????????   : V3R3 Share-PDP????????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPriority          : 4;                /* Priority  */
    VOS_UINT8                           ucIpVersion         : 4;                /* ip version, to be 6 */
    VOS_UINT8                           aucFlowLabel[3];                        /* flow lable */
    VOS_UINT16                          usPayloadLen;                           /* not include ipv6 fixed hdr len 40bytes */
    VOS_UINT8                           ucNextHdr;                              /* for l4 protocol or ext hdr */
    VOS_UINT8                           ucHopLimit;
    ADS_IPV6_ADDR_UN                    unSrcAddr;
    ADS_IPV6_ADDR_UN                    unDstAddr;
} ADS_IPV6_HDR_STRU;

/*****************************************************************************
 ??????    : ADS_UDP_HDR_STRU
 ????????  : UDP????
 1.??    ??   : 2013??06??03??
   ??    ??   : L47619
   ????????   : V3R3 Share-PDP????????
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSrcPort;                              /* ?????? */
    VOS_UINT16                          usDstPort;                              /* ???????? */
    VOS_UINT16                          usLen;                                  /* UDP?????? */
    VOS_UINT16                          usChecksum;                             /* UDP?????? */
} ADS_UDP_HDR_STRU;

/*****************************************************************************
 ??????    : ADS_TCP_HDR_STRU
 ????????  : TCP????
 1.??    ??   : 2013??06??03??
   ??    ??   : L47619
   ????????   : V3R3 Share-PDP????????
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSrcPort;
    VOS_UINT16                          usDstPort;
    VOS_UINT32                          ulSeqNum;
    VOS_UINT32                          ulAckNum;
    VOS_UINT16                          usOffset            : 4;
    VOS_UINT16                          usReserved          : 6;
    VOS_UINT16                          usUrg               : 1;
    VOS_UINT16                          usAck               : 1;
    VOS_UINT16                          usPsh               : 1;
    VOS_UINT16                          usRst               : 1;
    VOS_UINT16                          usSyn               : 1;
    VOS_UINT16                          usFin               : 1;
    VOS_UINT16                          usWindowSize;
    VOS_UINT16                          usCheckSum;
    VOS_UINT16                          usUrgentPoint;
} ADS_TCP_HDR_STRU;

/*****************************************************************************
 ??????    : ADS_ICMP_ECHO_HDR_STRU
 ????????  : ICMP??ECHO????????????????Identifier??Sequence Number??
 1.??    ??   : 2013??06??03??
   ??    ??   : L47619
   ????????   : V3R3 Share-PDP????????
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usIdentifier;
    VOS_UINT16                          usSeqNum;

} ADS_ICMP_ECHO_HDR_STRU;

/*****************************************************************************
 ??????    : ADS_ICMP_ERROR_HDR_STRU
 ????????  : ICMP????????????????Byte 4~Byte 8??
             ????????????????????????type??????3??4??5??11??12
             ????type????????Byte 4~Byte 8????????????????????????????????4??
             ??????????????????????????????????????
             ????????????????????:

   Type = 3  -- Destination Unreachable Message
    0                   1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |     Type      |     Code      |          Checksum             |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                             unused                            |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |      Internet Header + 64 bits of Original Data Datagram      |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

   Type = 4  -- Source Quench Message
    0                   1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |     Type      |     Code      |          Checksum             |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                             unused                            |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |      Internet Header + 64 bits of Original Data Datagram      |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

   Type = 5  -- Redirect Message
    0                   1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |     Type      |     Code      |          Checksum             |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                 Gateway Internet Address                      |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |      Internet Header + 64 bits of Original Data Datagram      |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

   Type = 11 -- Time Exceeded Message
    0                   1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |     Type      |     Code      |          Checksum             |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                             unused                            |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |      Internet Header + 64 bits of Original Data Datagram      |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

   Type = 12 -- Parameter Problem Message
    0                   1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |     Type      |     Code      |          Checksum             |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |    Pointer    |                   unused                      |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |      Internet Header + 64 bits of Original Data Datagram      |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+


 1.??    ??   : 2013??06??03??
   ??    ??   : L47619
   ????????   : V3R3 Share-PDP????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulUnUsed;

} ADS_ICMP_ERROR_HDR_STRU;

/*****************************************************************************
 ??????    : ADS_ICMP_HDR_STRU
 ????????  : ICMP????
 1.??    ??   : 2013??06??03??
   ??    ??   : L47619
   ????????   : V3R3 Share-PDP????????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucType;
    VOS_UINT8                           ucCode;
    VOS_UINT16                          usCheckSum;

    union
    {
        ADS_ICMP_ECHO_HDR_STRU          stIcmpEcho;
        ADS_ICMP_ERROR_HDR_STRU         stIcmpError;
    }unIcmp;

} ADS_ICMP_HDR_STRU;

/*****************************************************************************
 ??????    : ADS_FILTER_IPV4_HEADER_STRU
 ????????  : IPV4??IP????????????????????????????
 1.??    ??   : 2013??06??03??
   ??    ??   : l00198894
   ????????   : V3R3 Share-PDP????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSrcAddr;                              /* source address */
    VOS_UINT32                          ulDstAddr;                              /* dest address */
    VOS_UINT8                           ucProtocol;                             /* protocol */
    VOS_UINT8                           aucReserved[3];                         /* reserved */
} ADS_FILTER_IPV4_HEADER_STRU;

/*****************************************************************************
 ??????    : ADS_FILTER_IPV4_TCP_STRU
 ????????  : IPV4??TCP????????????????
 1.??    ??   : 2013??06??03??
   ??    ??   : L47619
   ????????   : V3R3 Share-PDP????????
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSrcPort;                              /* source port */
    VOS_UINT16                          usDstPort;                              /* dest port */
} ADS_FILTER_IPV4_TCP_STRU;

/*****************************************************************************
 ??????    : ADS_FILTER_IPV4_UDP_STRU
 ????????  : IPV4??UDP????????????????
 1.??    ??   : 2013??06??03??
   ??    ??   : L47619
   ????????   : V3R3 Share-PDP????????
*****************************************************************************/
typedef ADS_FILTER_IPV4_TCP_STRU    ADS_FILTER_IPV4_UDP_STRU;

/*****************************************************************************
 ??????    : ADS_FILTER_IPV4_ICMP_STRU
 ????????  : IPV4??ICMP????????????????
 1.??    ??   : 2013??06??03??
   ??    ??   : L47619
   ????????   : V3R3 Share-PDP????????
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSeqNum;                               /* ICMP????????Sequence number */
    VOS_UINT16                          usIdentifier;                           /* ICMP????????Identifier */
} ADS_FILTER_IPV4_ICMP_STRU;

/*****************************************************************************
 ??????    : ADS_FILTER_IPV4_FRAGMENT_STRU
 ????????  : IPV4????????????????????????????????????????????IP????????
             Identification????????????????
 1.??    ??   : 2013??06??03??
   ??    ??   : L47619
   ????????   : V3R3 Share-PDP????????
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usIdentification;                       /* IP????????identification */
    VOS_UINT8                           aucReserved[2];                         /* reserved */
} ADS_FILTER_IPV4_FRAGMENT_STRU;

/*****************************************************************************
 ??????    : ADS_FILTER_IPV4_INFO_STRU
 ????????  : IPV4??????????????
 1.??    ??   : 2013??06??03??
   ??    ??   : L47619
   ????????   : V3R3 Share-PDP????????
*****************************************************************************/
typedef struct
{
    ADS_FILTER_PKT_TYPE_ENUM_UINT32     enPktType;
    VOS_UINT8                           aucReserved[4];
    unsigned long                       ulTmrCnt;
    ADS_FILTER_IPV4_HEADER_STRU         stIPHeader;

    union
    {
        ADS_FILTER_IPV4_TCP_STRU        stTcpFilter;
        ADS_FILTER_IPV4_UDP_STRU        stUdpFilter;
        ADS_FILTER_IPV4_ICMP_STRU       stIcmpFilter;
        ADS_FILTER_IPV4_FRAGMENT_STRU   stFragmentFilter;
    }unFilter;

}ADS_FILTER_IPV4_INFO_STRU;


/*****************************************************************************
 ??????    : ADS_FILTER_DECODE_DL_ICMP_FUNC
 ????????  : ????ICMP????????????????????????????ICMP type????????????????
              ????????????????
 1.??    ??   : 2013??06??18??
   ??    ??   : l00198894
   ????????   : V3R3 Share-PDP????????
*****************************************************************************/
typedef VOS_UINT32 (*ADS_FILTER_DECODE_DL_ICMP_FUNC)(
    ADS_IPV4_HDR_STRU                  *pstIPv4Hdr,
    ADS_FILTER_IPV4_INFO_STRU          *pstIPv4Filter);

/*lint -e958 -e959 ??????:l60609;????:64bit*/
typedef struct
{
    ADS_FILTER_DECODE_DL_ICMP_FUNC      pFunc;
    ADS_FILTER_ORIG_PKT_ENUM_UINT32     enOrigPktType;
}ADS_FILTER_DECODE_DL_ICMP_FUNC_STRU;
/*lint +e958 +e959 ??????:l60609;*/


/*****************************************************************************
 ??????    : ADS_FILTER_NODE_STRU
 ????????  : ??????????????????????
 1.??    ??   : 2013??06??03??
   ??    ??   : l00198894
   ????????   : V3R3 Share-PDP????????
*****************************************************************************/
typedef struct
{
    ADS_FILTER_IPV4_INFO_STRU           stFilter;
    HI_LIST_S                           stList;
}ADS_FILTER_NODE_STRU;

/*****************************************************************************
 ??????    : ADS_FILTER_CTX_STRU
 ????????  : ADS??????????????????
 1.??    ??   : 2013??06??03??
   ??    ??   : l00198894
   ????????   : V3R3 Share-PDP????????
*****************************************************************************/
typedef struct
{
    HI_LIST_S                           astLists[ADS_FILTER_MAX_LIST_NUM];      /* ADS?????????????? */
    ADS_IPV6_ADDR_UN                    unIPv6Addr;                             /* ADS????????????IPv6???????? */
    VOS_UINT32                          ulAgingTimeLen;                         /* ADS????????????????, ???????? */
    VOS_UINT8                           aucReserved[4];
}ADS_FILTER_CTX_STRU;


/*****************************************************************************
  9 OTHERS????
*****************************************************************************/

/*****************************************************************************
  10 ????????
*****************************************************************************/

VOS_VOID ADS_FILTER_ResetIPv6Addr(VOS_VOID);

VOS_VOID ADS_FILTER_InitListsHead(VOS_VOID);

VOS_VOID ADS_FILTER_InitCtx(VOS_VOID);

VOS_VOID* ADS_FILTER_HeapAlloc(VOS_UINT32 ulSize);

VOS_VOID ADS_FILTER_HeapFree(VOS_VOID *pAddr);

VOS_VOID ADS_FILTER_AddFilter(
    ADS_FILTER_IPV4_INFO_STRU          *pstFilter);

VOS_VOID ADS_FILTER_ResetLists(VOS_VOID);

VOS_VOID ADS_FILTER_Reset(VOS_VOID);

VOS_UINT32 ADS_FILTER_IsInfoMatch(
    ADS_FILTER_IPV4_INFO_STRU          *pstFilter1,
    ADS_FILTER_IPV4_INFO_STRU          *pstFilter2);

VOS_UINT32 ADS_FILTER_Match(
    ADS_FILTER_IPV4_INFO_STRU          *pstFilter);

VOS_VOID ADS_FILTER_SaveIPAddrInfo(
    ADS_FILTER_IP_ADDR_INFO_STRU       *pstFilterIpAddr);

VOS_UINT32 ADS_FILTER_DecodeUlPacket(
    IMM_ZC_STRU                        *pstData,
    ADS_FILTER_IPV4_INFO_STRU          *pstIPv4Filter);

VOS_VOID ADS_FILTER_ProcUlPacket(
    IMM_ZC_STRU                        *pstData,
    ADS_PKT_TYPE_ENUM_UINT8             enIpType);

VOS_VOID ADS_FILTER_DecodeDlIPv4NotFirstFragPacket(
    ADS_IPV4_HDR_STRU                  *pstIPv4Hdr,
    ADS_FILTER_IPV4_INFO_STRU          *pstIPv4Filter);

VOS_UINT32 ADS_FILTER_DecodeDlIPv4EchoReplyPacket(
    ADS_IPV4_HDR_STRU                  *pstIPv4Hdr,
    ADS_FILTER_IPV4_INFO_STRU          *pstIPv4Filter);

VOS_UINT32 ADS_FILTER_DecodeDlIPv4IcmpErrorPacket(
    ADS_IPV4_HDR_STRU                  *pstIPv4Hdr,
    ADS_FILTER_IPV4_INFO_STRU          *pstIPv4Filter);

VOS_VOID ADS_FILTER_DecodeDlIPv4TcpPacket(
    ADS_IPV4_HDR_STRU                  *pstIPv4Hdr,
    ADS_FILTER_IPV4_INFO_STRU          *pstIPv4Filter);

VOS_VOID ADS_FILTER_DecodeDlIPv4UdpPacket(
    ADS_IPV4_HDR_STRU                  *pstIPv4Hdr,
    ADS_FILTER_IPV4_INFO_STRU          *pstIPv4Filter);

VOS_UINT32 ADS_FILTER_DecodeDlIPv4FragPacket(
    ADS_IPV4_HDR_STRU                  *pstIPv4Hdr,
    ADS_FILTER_IPV4_INFO_STRU          *pstIPv4Filter,
    ADS_FILTER_ORIG_PKT_ENUM_UINT32    *penOrigPktType);

VOS_UINT32 ADS_FILTER_DecodeDlIPv4Packet(
    ADS_IPV4_HDR_STRU                  *pstIPv4Hdr,
    ADS_FILTER_IPV4_INFO_STRU          *pstIPv4Filter,
    ADS_FILTER_ORIG_PKT_ENUM_UINT32    *penOrigPktType);

VOS_UINT32 ADS_FILTER_ProcDlIPv4Packet(
    IMM_ZC_STRU                        *pstData);

VOS_UINT32 ADS_FILTER_ProcDlIPv6Packet(
    IMM_ZC_STRU                        *pstData);

VOS_UINT32 ADS_FILTER_ProcDlPacket(
    IMM_ZC_STRU                        *pstData,
    ADS_PKT_TYPE_ENUM_UINT8             enIpType);

VOS_UINT32 ADS_Ipv4AddrItoa(
    VOS_CHAR                           *pcString,
    VOS_UINT8                          *pucNumber);

VOS_VOID ADS_FILTER_ShowStatisticInfo(VOS_VOID);

VOS_VOID ADS_FILTER_ResetStatisticInfo(VOS_VOID);

VOS_VOID ADS_FILTER_ShowFilterLists(VOS_VOID);

VOS_VOID ADS_FILTER_ShowIPv6Addr(VOS_VOID);




#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of AdsFilter.h */
