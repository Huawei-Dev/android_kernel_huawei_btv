#ifndef __OAL_LINUX_MEM_H__
#define __OAL_LINUX_MEM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define OAL_TX_CB_LEN 48
#define OAL_MAX_CB_LEN  19
#define MAX_MAC_HEAD_LEN            WLAN_MAX_MAC_HDR_LEN

#ifdef CONFIG_ARM64
#define OAL_MEM_INFO_SIZE            8
#else
#define OAL_MEM_INFO_SIZE            4
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_mm.h */

