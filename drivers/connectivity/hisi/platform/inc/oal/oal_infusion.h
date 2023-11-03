#ifndef __OAL_INFUSION_H__
#define __OAL_INFUSION_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define OAL_STATIC          static
#ifdef INLINE_TO_FORCEINLINE
#define OAL_INLINE      __forceinline
#else
#define OAL_INLINE          inline
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_ext_if.h */
