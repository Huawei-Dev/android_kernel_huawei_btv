#ifndef __OAL_MEM_H__
#define __OAL_MEM_H__


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "platform_spec.h"
#include "oal_cache.h"
#include "oal_list.h"
#include "oal_schedule.h"
#include "oal_net.h"
#include "oal_util.h"
#include "arch/oal_mem.h"

#if ((_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE) && (_PRE_OS_VERSION == _PRE_OS_VERSION_LINUX))
#include <linux/kallsyms.h>
#endif

#define OAL_MEM_NETBUF_ALLOC(_uc_out_subpool_id,_us_len,_uc_netbuf_priority) \
    oal_netbuf_alloc(_us_len,0, WLAN_MEM_NETBUF_ALIGN)
#ifdef _PRE_DEBUG_MODE
#define OAL_MEM_NETBUF_TRACE(_pst_netbuf, _uc_lock)
#else
#define OAL_MEM_NETBUF_TRACE(_pst_netbuf, _uc_lock)
#endif

#define OAL_MEM_ALLOC(_en_pool_id, _us_len, _uc_lock) \
    oal_mem_alloc(THIS_FILE_ID, __LINE__, _en_pool_id, _us_len, _uc_lock)
#define OAL_MEM_FREE(_p_data, _uc_lock) \
    oal_mem_free(THIS_FILE_ID, __LINE__, _p_data, _uc_lock)

#define OAL_MEM_FREE_ARRAY(_p_data, _num) \
    oal_mem_free_array(THIS_FILE_ID, __LINE__, _p_data, _num)

#define OAL_MEM_INCR_USER(_pst_mem, _uc_lock) \
    oal_mem_incr_user(THIS_FILE_ID, __LINE__, _pst_mem, _uc_lock)

#define OAL_MEM_ALLOC_ENHANCED(_en_pool_id, _us_len, _uc_lock) \
    oal_mem_alloc_enhanced(THIS_FILE_ID, __LINE__, _en_pool_id, _us_len, _uc_lock)

#define OAL_MEM_FREE_ENHANCED(_pst_mem, _uc_lock) \
    oal_mem_free_enhanced(THIS_FILE_ID, __LINE__, _pst_mem, _uc_lock)

#define OAL_MEM_INFO_PRINT(_pool_id)

#ifdef _PRE_DEBUG_MODE
#define OAL_MEM_TRACE(_p_data, _uc_lock) \
    oal_mem_trace(THIS_FILE_ID, __LINE__, _p_data, _uc_lock)

#define OAL_MEM_TRACE_ENHANCED(_pst_mem, _uc_lock) \
    oal_mem_trace_enhanced(THIS_FILE_ID, __LINE__, _pst_mem, _uc_lock)
#else
#define OAL_MEM_TRACE(_p_data, _uc_lock)
#define OAL_MEM_TRACE_ENHANCED(_pst_mem, _uc_lock)
#endif

#define OAL_DOG_TAG    0x5b3a293e

#ifdef _PRE_DEBUG_MODE
#ifdef CONFIG_ARM64
#define OAL_DOG_TAG_SIZE             8
#else
#define OAL_DOG_TAG_SIZE             4
#endif
#define OAL_NETBUF_MAINTAINS_SIZE    24
#else
#define OAL_DOG_TAG_SIZE             0
#define OAL_NETBUF_MAINTAINS_SIZE    0
#endif

#define OAL_NETBUF_DEFAULT_HEADROOM  256
#define OAL_MAX_TX_DSCR_CNT_IN_LIST  100
#define OAL_TX_DSCR_ITEM_NUM         200
#define OAL_TX_DSCR_RCD_TAIL_CNT     20

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
#if(_PRE_OS_VERSION == _PRE_OS_VERSION_LINUX)
#define OAL_MEM_SPRINT_SYMBOL_SIZE    KSYM_SYMBOL_LEN
#else
#define OAL_MEM_SPRINT_SYMBOL_SIZE    1
#endif
#endif

typedef enum
{
    OAL_MEM_POOL_ID_EVENT = 0,
    OAL_MEM_POOL_ID_SHARED_DATA_PKT,
    OAL_MEM_POOL_ID_SHARED_MGMT_PKT,
    OAL_MEM_POOL_ID_LOCAL,
    OAL_MEM_POOL_ID_MIB,
    OAL_MEM_POOL_ID_SHARED_DSCR,

    //OAL_MEM_POOL_ID_NETBUF,
    OAL_MEM_POOL_ID_SDT_NETBUF,

    OAL_MEM_POOL_ID_BUTT
}oal_mem_pool_id_enum;
typedef oal_uint8 oal_mem_pool_id_enum_uint8;

typedef enum
{
    OAL_NETBUF_PRIORITY_LOW     = 0,
    OAL_NETBUF_PRIORITY_MID     = 1,
    OAL_NETBUF_PRIORITY_HIGH    = 2,

    OAL_NETBUF_PRIORITY_BUTT
}oal_netbuf_priority_enum;
typedef oal_uint8 oal_netbuf_priority_enum_uint8;

typedef enum
{
    OAL_NORMAL_NETBUF = 0,
    OAL_MGMT_NETBUF   = 1,
    OAL_OAM_NETBUF    = 2,

    OAL_NETBUF_POOL_ID_BUTT
}oal_netbuf_id_enum;
typedef oal_uint8 oal_netbuf_id_enum_uint8;

#define OAL_MEM_POOL_ID_ALG_LOCAL  OAL_MEM_POOL_ID_LOCAL
#define OAL_MEM_POOL_ID_HI_LOCAL   OAL_MEM_POOL_ID_LOCAL

typedef struct
{
    oal_uint32  (* p_mempool_info_func)(oal_uint8 en_pool_id,
                                        oal_uint16 us_mem_total_cnt,
                                        oal_uint16 us_mem_used_cnt,
                                        oal_uint8  uc_subpool_id,
                                        oal_uint16 us_total_cnt,
                                        oal_uint16 us_free_cnt);
    oal_uint32  (* p_memblock_info_func)(oal_uint8 *puc_origin_data,
                                         oal_uint8                   uc_user_cnt,
                                         oal_mem_pool_id_enum_uint8  en_pool_id,
                                         oal_uint8                   uc_subpool_id,
                                         oal_uint16                  us_len,
                                         oal_uint32                  ul_alloc_file_id,
                                         oal_uint32                  ul_alloc_line_num);

}oal_mempool_info_to_sdt_stru;

typedef struct
{
    oal_uint32   ul_dog_tag;
    oal_uint32   ul_alloc_file_id;
    oal_uint32   ul_alloc_line_num;
    oal_uint32   ul_alloc_time_stamp;
    oal_uint32   ul_trace_file_id;
    oal_uint32   ul_trace_line_num;
    oal_uint32   ul_trace_time_stamp;
}oal_mem_netbuf_info_stru;

struct oal_mem_stru_tag
{
    oal_uint8                  *puc_data;
    oal_uint8                  *puc_origin_data;

    oal_uint16                  us_len;
    oal_uint8                   uc_user_cnt       :4;
    oal_mem_state_enum_uint8    en_mem_state_flag :4;
    oal_mem_pool_id_enum_uint8  en_pool_id        :4;
    oal_uint8                   uc_subpool_id     :4;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_ulong                  ul_return_addr;
#endif

#ifdef _PRE_DEBUG_MODE
    oal_uint32                  ul_alloc_core_id[WLAN_MEM_MAX_USERS_NUM];
    oal_uint32                  ul_alloc_file_id[WLAN_MEM_MAX_USERS_NUM];
    oal_uint32                  ul_alloc_line_num[WLAN_MEM_MAX_USERS_NUM];
    oal_uint32                  ul_alloc_time_stamp[WLAN_MEM_MAX_USERS_NUM];
    oal_uint32                  ul_trace_file_id;
    oal_uint32                  ul_trace_line_num;
    oal_uint32                  ul_trace_time_stamp;
#endif
}oal_cacheline_aligned;
typedef struct oal_mem_stru_tag  oal_mem_stru;

typedef struct
{
    oal_spin_lock_stru    st_spinlock;
    oal_uint16            us_len;
    oal_uint16            us_free_cnt;

    void                **ppst_free_stack;

    oal_uint16            us_total_cnt;
    oal_uint8             auc_resv[2];
} oal_mem_subpool_stru;

typedef struct
{
    oal_uint16              us_max_byte_len;
    oal_uint8               uc_subpool_cnt;
    oal_uint8               uc_resv;

    oal_mem_subpool_stru    ast_subpool_table[WLAN_MEM_MAX_SUBPOOL_NUM];

    oal_uint16              us_mem_used_cnt;
    oal_uint16              us_mem_total_cnt;
    oal_mem_stru           *pst_mem_start_addr;
}oal_mem_pool_stru;

typedef struct
{
    oal_uint16  us_size;
    oal_uint16  us_cnt;
}oal_mem_subpool_cfg_stru;

typedef struct
{
    oal_mem_pool_id_enum_uint8          en_pool_id;
    oal_uint8                           uc_subpool_cnt;

    oal_uint8                           auc_resv[2];

    oal_mem_subpool_cfg_stru  *pst_subpool_cfg_info;
}oal_mem_pool_cfg_stru;

#ifdef _PRE_DEBUG_MODE
typedef struct
{
    oal_uint    ul_released_addr;
    oal_uint32  ul_release_file_id;
    oal_uint32  ul_release_line_num;
    oal_uint32  ul_release_ts;
    oal_uint32  ul_tx_dscr_in_up_intr;
    oal_uint32  ul_up_intr_ts;
    oal_uint32  ul_tx_dscr_in_dn_intr;
    oal_uint32  ul_dn_intr_ts;
    oal_uint32  ul_tx_dscr_in_q[OAL_MAX_TX_DSCR_CNT_IN_LIST];
    oal_uint8   uc_mpdu_num;
    oal_uint8   uc_q_num;
    oal_uint16  bit_dscr_is_overflow  : 1;
    oal_uint16  bit_resv              : 15;
}oal_mempool_tx_dscr_info;

typedef struct
{
    oal_uint     ul_tx_dscr_addr[WLAN_MEM_SHARED_TX_DSCR_CNT1 + WLAN_MEM_SHARED_TX_DSCR_CNT2];
    oal_mempool_tx_dscr_info ast_tx_dscr_info[OAL_TX_DSCR_ITEM_NUM];
    oal_uint16   us_tx_dscr_cnt;
    oal_uint16   us_released_tx_dscr_cnt;
    oal_uint16   us_tx_dscr_cnt_up;
    oal_uint16   us_tx_dscr_cnt_dn;
    oal_uint16   us_rcd_rls_stop_flag;
    oal_uint16   us_rsv;
}oal_mempool_tx_dscr_addr;
#endif

extern oal_void* oal_mem_alloc(
                       oal_uint32                    ul_file_id,
                       oal_uint32                    ul_line_num,
                       oal_mem_pool_id_enum_uint8    en_pool_id,
                       oal_uint16                    us_len,
                       oal_uint8                     uc_lock);
extern oal_uint32  oal_mem_free(oal_uint32 ul_file_id, oal_uint32 ul_line_num, oal_void *pst_mem, oal_uint8 uc_lock);

extern oal_uint32  oal_mem_free_array(
                oal_uint32    ul_file_id,
                oal_uint32    ul_line_num,
                oal_void     *p_data,
                oal_uint8     uc_mem_num);

extern oal_mem_stru* oal_mem_alloc_enhanced(
                oal_uint32                    ul_file_id,
                oal_uint32                    ul_line_num,
                oal_mem_pool_id_enum_uint8    en_pool_id,
                oal_uint16                    us_len,
                oal_uint8                     uc_lock);
extern oal_uint32  oal_mem_free_enhanced(oal_uint32 ul_file_id, oal_uint32 ul_line_num, oal_mem_stru *p_data, oal_uint8 uc_lock);
extern oal_uint32  oal_mem_init_pool(oal_void);
extern oal_uint32  oal_mem_exit(oal_void);
extern oal_uint32  oal_mem_incr_user(
                       oal_uint32      ul_file_id,
                       oal_uint32      ul_line_num,
                       oal_mem_stru   *pst_mem,
                       oal_uint8       uc_lock);
extern oal_void  oal_mem_info(oal_mem_pool_id_enum_uint8 en_pool_id);
extern oal_void  oal_mem_leak(oal_mem_pool_id_enum_uint8 en_pool_id);

extern oal_void  oal_mem_start_stat(oal_void);
extern oal_uint32  oal_mem_end_stat(oal_void);

extern oal_uint32  oal_mem_trace_enhanced(oal_uint32      ul_file_id,
                                          oal_uint32      ul_line_num,
                                          oal_mem_stru   *pst_mem,
                                          oal_uint8       uc_lock);
extern oal_uint32  oal_mem_trace(oal_uint32    ul_file_id,
                                 oal_uint32    ul_line_num,
                                 oal_void     *p_data,
                                 oal_uint8     uc_lock);

#ifdef _PRE_DEBUG_MODE
extern oal_mempool_tx_dscr_addr* oal_mem_get_tx_dscr_addr(oal_void);
extern oal_void oal_mem_stop_rcd_rls(oal_void);
extern oal_uint16 oal_mem_get_stop_flag(oal_void);
#endif

extern oal_mem_pool_stru* oal_mem_get_pool(oal_mem_pool_id_enum_uint8 en_pool_id);

extern oal_mem_pool_cfg_stru* oal_mem_get_pool_cfg_table(oal_mem_pool_id_enum_uint8 en_pool_id);
extern oal_netbuf_stru* oal_mem_sdt_netbuf_alloc(oal_uint16 us_len, oal_uint8 uc_lock);
extern oal_uint32  oal_mem_sdt_netbuf_free(oal_netbuf_stru *pst_netbuf, oal_uint8 uc_lock);
extern oal_netbuf_stru* oal_netbuf_duplicate(oal_netbuf_stru* pst_src_netbuf,
											oal_uint8 uc_out_subpool_id,
											oal_uint32 ul_add_head_room,
											oal_uint32 ul_add_tail_room);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
extern oal_void oal_mem_print_normal_pool_info(oal_mem_pool_id_enum_uint8 en_pool_id);
extern oal_void oal_mem_print_pool_info(oal_void);
extern oal_ulong oal_get_func_return_address(oal_void);
extern oal_void oal_mem_print_funcname(oal_ulong func_addr);
#endif

#define oal_netbuf_duplicate_normal(pst_src_netbuf,ul_add_head_room,ul_add_tail_room) \
                    oal_netbuf_duplicate(pst_src_netbuf,OAL_NORMAL_NETBUF,ul_add_head_room,ul_add_tail_room)

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_mm.h */
