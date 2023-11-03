#ifndef __OAL_LINUX_CFG80211_H__
#define __OAL_LINUX_CFG80211_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include <net/genetlink.h>
#include <net/cfg80211.h>
#include <linux/nl80211.h>

#define OAL_NLMSG_GOODSIZE      NLMSG_GOODSIZE
#define OAL_ETH_ALEN_SIZE            ETH_ALEN
#define OAL_NLMSG_DEFAULT_SIZE  NLMSG_DEFAULT_SIZE
#define OAL_IEEE80211_MIN_ACTION_SIZE IEEE80211_MIN_ACTION_SIZE

#define OAL_NLA_PUT_U32(skb, attrtype, value)      NLA_PUT_U32(skb, attrtype, value)
#define OAL_NLA_PUT(skb, attrtype, attrlen, data)  NLA_PUT(skb, attrtype, attrlen, data)
#define OAL_NLA_PUT_U16(skb, attrtype, value)      NLA_PUT_U16(skb, attrtype, value)
#define OAL_NLA_PUT_U8(skb, attrtype, value)       NLA_PUT_U8(skb, attrtype, value)
#define OAL_NLA_PUT_FLAG(skb, attrtype)            NLA_PUT_FLAG(skb, attrtype)

typedef enum  rate_info_flags  oal_rate_info_flags;

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_cfg80211.h */
