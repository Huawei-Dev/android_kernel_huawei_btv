#ifndef __OAL_LINUX_TYPES_H__
#define __OAL_LINUX_TYPES_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

typedef signed char             oal_int8;
typedef signed short            oal_int16;
typedef signed int              oal_int32;
typedef signed long long        oal_int64;
typedef unsigned char           oal_uint8;
typedef unsigned short          oal_uint16;
typedef unsigned int            oal_uint32;
typedef unsigned long long      oal_uint64;
typedef void                    oal_void;

#ifdef INLINE_TO_FORCEINLINE
#define OAL_INLINE      __forceinline
#else
#define OAL_INLINE          inline
#endif

#define OAL_STATIC          static

#if defined(_PRE_PC_LINT)
#define OAL_VOLATILE
#else
#define OAL_VOLATILE        volatile
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_types.h */
