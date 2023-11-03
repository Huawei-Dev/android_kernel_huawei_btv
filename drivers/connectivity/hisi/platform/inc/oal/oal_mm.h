#ifndef __OAL_MM_H__
#define __OAL_MM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "oal_types.h"
#include "arch/oal_mm.h"

#define OAL_MEMZERO(_p_buf, _ul_size)          oal_memset((_p_buf), 0, (_ul_size))

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_mm.h */
