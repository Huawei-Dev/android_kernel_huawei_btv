/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : AtNdisInterface.h header file
  History           :
******************************************************************************/

#ifndef __ATNDISINTERFACE_H__
#define __ATNDISINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif

#include "mdrv.h"
#include "msp_at.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

#ifndef IPV4_ADDR_LEN
#define   IPV4_ADDR_LEN      4
#endif

#ifndef	IPV6_ADDR_LEN
#define   IPV6_ADDR_LEN      16
#endif

#define   MIN_VAL_EPSID      5
#define   MAX_VAL_EPSID      15

#define   NDIS_MSG_ID_BASE                  0x3000
#define   NDIS_MSG_ID_END                   0x3100

#define   MIN_VAL_HANDLE                  (0x5A0000)
#define   MAX_VAL_HANDLE                  (0x5A003F)

#define NDIS_INVALID_HANDLEINDEX          (0x7F)
#define NDIS_INVALID_HANDLE               (0x7FFFFFFF)
#define NDIS_INVALID_RABID                (0x7F)

#define NDIS_INVALID_SPEPORT              (0)

#define   AT_NDIS_IPV4_ADDR_LENGTH          (4)
#define   AT_NDIS_IPV6_ADDR_LENGTH          (16)
#define   AT_NDIS_MAX_PREFIX_NUM_IN_RA      (6)
#define   AT_NDIS_IPV6_IFID_LENGTH          (8)

enum NDIS_MSG_ID_SECTION_ENUM
{
    NDIS_MSG_ID_AT_TO_NDIS_BASE   = NDIS_MSG_ID_BASE,
    NDIS_MSG_ID_NDIS_TO_AT_BASE   = NDIS_MSG_ID_AT_TO_NDIS_BASE + 0x20
};

enum AT_NDIS_MSG_TYPE_ENUM
{
    ID_AT_NDIS_PDNINFO_CFG_REQ               = (NDIS_MSG_ID_AT_TO_NDIS_BASE + 0x01),
    ID_AT_NDIS_PDNINFO_CFG_CNF               = (NDIS_MSG_ID_NDIS_TO_AT_BASE + 0x01),
    ID_AT_NDIS_PDNINFO_REL_REQ               = (NDIS_MSG_ID_AT_TO_NDIS_BASE + 0x02),
    ID_AT_NDIS_PDNINFO_REL_CNF               = (NDIS_MSG_ID_NDIS_TO_AT_BASE + 0x02),
    ID_AT_NDIS_MSG_TYPE_END
};
typedef VOS_UINT32 AT_NDIS_MSG_TYPE_ENUM_UINT32;

enum OM_NDIS_KEY_EVENT_ENUM
{

    NDIS_OM_PDN_INFO_CFG       = 1,
    NDIS_OM_PDN_INFO_REL
};
typedef VOS_UINT32 OM_NDIS_KEY_EVENT_ENUM_UINT32;

enum AT_NDIS_ENUM
{
    AT_NDIS_SUCC                            = 0,
    AT_NDIS_FAIL                            = 1,
    AT_NDIS_BUTT
};
typedef VOS_UINT8   AT_NDIS_RSLT_ENUM_UINT8;

enum AT_NDIS_PDNCFG_CNF_TYPE
{
    AT_NDIS_PDNCFG_CNF_SUCC                       = 0,
    AT_NDIS_PDNCFG_CNF_FAIL                       = 1,
    AT_NDIS_PDNCFG_CNF_IPV4ONLY_SUCC              = 2,
    AT_NDIS_PDNCFG_CNF_IPV6ONLY_SUCC              = 3,
    AT_NDIS_PDNCFG_CNF_BUUT
};
typedef VOS_UINT8   AT_NDIS_PDNCFG_CNF_UINT8;

enum AT_NDIS_DHCP_INFO_TYPE_ENUM
{
    AT_NDIS_DHCP_INFO_TYPE_IPV4         = 0,
    AT_NDIS_DHCP_INFO_TYPE_IPV6         = 1,

    AT_NDIS_DHCP_INFO_TYPE_BUTT
};
typedef VOS_UINT8 AT_NDIS_DHCP_INFO_TYPE_ENUM_UINT8;

typedef struct
{
    VOS_UINT8                           aucIpV4Addr[AT_NDIS_IPV4_ADDR_LENGTH];
}AT_NDIS_IPV4_ADDR_STRU;

typedef struct
{
    VOS_UINT32                          bitOpPdnAddr         :1;
    VOS_UINT32                          bitOpDnsPrim         :1;
    VOS_UINT32                          bitOpDnsSec          :1;
    VOS_UINT32                          bitOpWinsPrim        :1;
    VOS_UINT32                          bitOpWinsSec         :1;
    VOS_UINT32                          bitOpPcscfPrim       :1;
    VOS_UINT32                          bitOpPcscfSec        :1;
    VOS_UINT32                          bitOpSpare           :25;

    AT_NDIS_IPV4_ADDR_STRU              stPDNAddrInfo;
    AT_NDIS_IPV4_ADDR_STRU              stSubnetMask;
    AT_NDIS_IPV4_ADDR_STRU              stGateWayAddrInfo;
    AT_NDIS_IPV4_ADDR_STRU              stDnsPrimAddrInfo;
    AT_NDIS_IPV4_ADDR_STRU              stDnsSecAddrInfo;
    AT_NDIS_IPV4_ADDR_STRU              stWinsPrimAddrInfo;
    AT_NDIS_IPV4_ADDR_STRU              stWinsSecAddrInfo;
    AT_NDIS_IPV4_ADDR_STRU              stPcscfPrimAddrInfo;
    AT_NDIS_IPV4_ADDR_STRU              stPcscfSecAddrInfo;
}AT_NDIS_IPV4_PDN_INFO_STRU;

typedef struct
{
    VOS_UINT8                           ucSerNum;
    VOS_UINT8                           aucReserved[3];

    VOS_UINT8                           aucPriServer[AT_NDIS_IPV6_ADDR_LENGTH];
    VOS_UINT8                           aucSecServer[AT_NDIS_IPV6_ADDR_LENGTH];
}AT_NDIS_IPV6_DNS_SER_STRU;

typedef AT_NDIS_IPV6_DNS_SER_STRU AT_NDIS_IPV6_PCSCF_SER_STRU;

typedef struct
{
    VOS_UINT32                          ulBitL          :1;
    VOS_UINT32                          ulBitA          :1;
    VOS_UINT32                          ulBitPrefixLen  :8;
    VOS_UINT32                          ulBitRsv        :22;

    VOS_UINT32                          ulValidLifeTime;
    VOS_UINT32                          ulPreferredLifeTime;
    VOS_UINT8                           aucPrefix[AT_NDIS_IPV6_ADDR_LENGTH];
}AT_NDIS_IPV6_PREFIX_STRU;

typedef struct
{
    VOS_UINT32                          ulBitOpMtu              :1;
    VOS_UINT32                          ulBitRsv1               :31;

    VOS_UINT32                          ulBitCurHopLimit        :8;
    VOS_UINT32                          ulBitM                  :1;
    VOS_UINT32                          ulBitO                  :1;
    VOS_UINT32                          ulBitRsv2               :22;

    VOS_UINT8                           aucInterfaceId[AT_NDIS_IPV6_IFID_LENGTH];
    VOS_UINT32                          ulMtu;
    VOS_UINT32                          ulPrefixNum;
    AT_NDIS_IPV6_PREFIX_STRU            astPrefixList[AT_NDIS_MAX_PREFIX_NUM_IN_RA];

    AT_NDIS_IPV6_DNS_SER_STRU           stDnsSer;
    AT_NDIS_IPV6_PCSCF_SER_STRU         stPcscfSer;
} AT_NDIS_IPV6_PDN_INFO_STRU;

typedef struct
{
    VOS_UINT32                          bitOpIpv4PdnInfo : 1;
    VOS_UINT32                          bitOpIpv6PdnInfo : 1;
    VOS_UINT32                          bitOpSpare       : 30;

    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                           ucRabId;
    VOS_UINT8                           aucRev[1];

    UDI_HANDLE                          ulHandle;

    AT_NDIS_IPV4_PDN_INFO_STRU          stIpv4PdnInfo;
    AT_NDIS_IPV6_PDN_INFO_STRU          stIpv6PdnInfo;

    VOS_UINT32                          ulMaxRxbps;
    VOS_UINT32                          ulMaxTxbps;

    VOS_INT32                           lSpePort;
    VOS_UINT32                          ulIpfFlag;          
}AT_NDIS_PDNINFO_CFG_REQ_STRU;

typedef struct
{
    MODEM_ID_ENUM_UINT16                  enModemId;
    VOS_UINT8                             ucRabId;
    AT_NDIS_PDNCFG_CNF_UINT8              enResult;
    VOS_UINT8                             ucRabType;
    VOS_UINT8                             aucRsv[3];
}AT_NDIS_PDNINFO_CFG_CNF_STRU;

typedef struct
{
    MODEM_ID_ENUM_UINT16                  enModemId;
    VOS_UINT8                             ucRabId;
    VOS_UINT8                             ucRcv[1];
}AT_NDIS_PDNINFO_REL_REQ_STRU;

typedef struct
{
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                             ucRabId;
    AT_NDIS_RSLT_ENUM_UINT8               enResult;
    VOS_UINT8                             ucRabType;
    VOS_UINT8                           aucRsv[3];
}AT_NDIS_PDNINFO_REL_CNF_STRU;

typedef struct
{
    VOS_UINT8                             aucRev[4];
}AT_NDIS_USBABNORMAL_IND_STRU;

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif
