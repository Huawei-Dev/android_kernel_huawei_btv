#ifndef __OAM_EXT_IF_H__
#define __OAM_EXT_IF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "platform_spec.h"
#include "oal_types.h"
#include "oal_net.h"
#include "oam_log.h"
#ifdef _PRE_WLAN_DFT_REG
#include "oam_register.h"
#endif
#include "oam_wdk.h"
#include "oam_config.h"
#ifdef _PRE_CONFIG_HW_CHR
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
#include "chr_user.h"
#else
#define CHR_LOG(prio, tag, fmt,...)
#define CHR_EXCEPTION(chr_errno)
#endif
#else
#define CHR_LOG(prio, tag, fmt,...)
#define CHR_EXCEPTION(chr_errno)
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_OAM_EXT_IF_H

#define OAM_WIFI_LOG_PARA_PRESS(vap_id,feature_id,fileid,lev)   ((fileid&0xFFFF)|((feature_id&0xFF)<<16)|((vap_id&0xF)<<24)|((lev&0xF)<<28))

#ifdef _PRE_WLAN_DFT_LOG
#define OAM_EXCP_RECORD(_uc_vap_id, _excp_id)   \
        oam_exception_record(_uc_vap_id, _excp_id)

#define OAM_IO_PRINTK(fmt, ...)      \
        oam_log_console_printk(THIS_FILE_ID, (oal_uint16)__LINE__, OAL_FUNC_NAME, fmt, ##__VA_ARGS__)

#define OAM_INFO_LOG0(_uc_vap_id, _en_feature_id, fmt)   \
        oam_log_print0(OAM_WIFI_LOG_PARA_PRESS(_uc_vap_id,_en_feature_id,THIS_FILE_ID,OAM_LOG_LEVEL_INFO), (oal_uint16)__LINE__, fmt)
#define OAM_INFO_LOG1(_uc_vap_id, _en_feature_id, fmt, p1)   \
        oam_log_print1(OAM_WIFI_LOG_PARA_PRESS(_uc_vap_id,_en_feature_id,THIS_FILE_ID,OAM_LOG_LEVEL_INFO), (oal_uint16)__LINE__, fmt, (oal_uint)p1)
#define OAM_INFO_LOG2(_uc_vap_id, _en_feature_id, fmt, p1, p2)   \
        oam_log_print2(OAM_WIFI_LOG_PARA_PRESS(_uc_vap_id,_en_feature_id,THIS_FILE_ID,OAM_LOG_LEVEL_INFO), (oal_uint16)__LINE__, fmt, (oal_uint)p1, (oal_uint)p2)
#define OAM_INFO_LOG3(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3)   \
        oam_log_print3(OAM_WIFI_LOG_PARA_PRESS(_uc_vap_id,_en_feature_id,THIS_FILE_ID,OAM_LOG_LEVEL_INFO), (oal_uint16)__LINE__, fmt, (oal_uint)p1, (oal_uint)p2, (oal_uint)p3)
#define OAM_INFO_LOG4(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3, p4)   \
        oam_log_print4(OAM_WIFI_LOG_PARA_PRESS(_uc_vap_id,_en_feature_id,THIS_FILE_ID,OAM_LOG_LEVEL_INFO), (oal_uint16)__LINE__, fmt, (oal_uint)p1, (oal_uint)p2, (oal_uint)p3, (oal_uint)p4)

#define OAM_WARNING_LOG0(_uc_vap_id, _en_feature_id, fmt)   \
        oam_log_print0(OAM_WIFI_LOG_PARA_PRESS(_uc_vap_id,_en_feature_id,THIS_FILE_ID,OAM_LOG_LEVEL_WARNING), (oal_uint16)__LINE__, fmt)
#define OAM_WARNING_LOG1(_uc_vap_id, _en_feature_id, fmt, p1)   \
        oam_log_print1(OAM_WIFI_LOG_PARA_PRESS(_uc_vap_id,_en_feature_id,THIS_FILE_ID,OAM_LOG_LEVEL_WARNING), (oal_uint16)__LINE__, fmt, (oal_uint)p1)
#define OAM_WARNING_LOG2(_uc_vap_id, _en_feature_id, fmt, p1, p2)   \
        oam_log_print2(OAM_WIFI_LOG_PARA_PRESS(_uc_vap_id,_en_feature_id,THIS_FILE_ID,OAM_LOG_LEVEL_WARNING), (oal_uint16)__LINE__, fmt, (oal_uint)p1, (oal_uint)p2)
#define OAM_WARNING_LOG3(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3)   \
        oam_log_print3(OAM_WIFI_LOG_PARA_PRESS(_uc_vap_id,_en_feature_id,THIS_FILE_ID,OAM_LOG_LEVEL_WARNING), (oal_uint16)__LINE__, fmt, (oal_uint)p1, (oal_uint)p2, (oal_uint)p3)
#define OAM_WARNING_LOG4(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3, p4)   \
        oam_log_print4(OAM_WIFI_LOG_PARA_PRESS(_uc_vap_id,_en_feature_id,THIS_FILE_ID,OAM_LOG_LEVEL_WARNING), (oal_uint16)__LINE__, fmt, (oal_uint)p1, (oal_uint)p2, (oal_uint)p3, (oal_uint)p4)

#define OAM_ERROR_LOG0(_uc_vap_id, _en_feature_id, fmt)   \
        oam_log_print0(OAM_WIFI_LOG_PARA_PRESS(_uc_vap_id,_en_feature_id,THIS_FILE_ID,OAM_LOG_LEVEL_ERROR), (oal_uint16)__LINE__, fmt)
#define OAM_ERROR_LOG1(_uc_vap_id, _en_feature_id, fmt, p1)   \
        oam_log_print1(OAM_WIFI_LOG_PARA_PRESS(_uc_vap_id,_en_feature_id,THIS_FILE_ID,OAM_LOG_LEVEL_ERROR), (oal_uint16)__LINE__, fmt, (oal_uint)p1)
#define OAM_ERROR_LOG2(_uc_vap_id, _en_feature_id, fmt, p1, p2)   \
        oam_log_print2(OAM_WIFI_LOG_PARA_PRESS(_uc_vap_id,_en_feature_id,THIS_FILE_ID,OAM_LOG_LEVEL_ERROR), (oal_uint16)__LINE__, fmt, (oal_uint)p1, (oal_uint)p2)
#define OAM_ERROR_LOG3(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3)   \
        oam_log_print3(OAM_WIFI_LOG_PARA_PRESS(_uc_vap_id,_en_feature_id,THIS_FILE_ID,OAM_LOG_LEVEL_ERROR), (oal_uint16)__LINE__, fmt, (oal_uint)p1, (oal_uint)p2, (oal_uint)p3)
#define OAM_ERROR_LOG4(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3, p4)   \
        oam_log_print4(OAM_WIFI_LOG_PARA_PRESS(_uc_vap_id,_en_feature_id,THIS_FILE_ID,OAM_LOG_LEVEL_ERROR), (oal_uint16)__LINE__, fmt, (oal_uint)p1, (oal_uint)p2, (oal_uint)p3, (oal_uint)p4)

#else
#define OAM_EXCP_RECORD(_uc_vap_id, _excp_id)
#define OAM_IO_PRINTK(fmt, ...)
#if (defined(_PRE_PRODUCT_ID_HI110X_DEV))
#if 0
//#define OAM_INFO_LOG0(_uc_vap_id, _en_feature_id, fmt)                      OAL_IO_PRINT("[INFO]"fmt"\r\n")
//#define OAM_INFO_LOG1(_uc_vap_id, _en_feature_id, fmt, p1)                  OAL_IO_PRINT("[INFO]"fmt"\r\n", p1)
//#define OAM_INFO_LOG2(_uc_vap_id, _en_feature_id, fmt, p1, p2)              OAL_IO_PRINT("[INFO]"fmt"\r\n", p1, p2)
//#define OAM_INFO_LOG3(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3)          OAL_IO_PRINT("[INFO]"fmt"\r\n", p1, p2, p3)
//#define OAM_INFO_LOG4(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3, p4)      OAL_IO_PRINT("[INFO]"fmt"\r\n", p1, p2, p3, p4)
#define OAM_WARNING_LOG0(_uc_vap_id, _en_feature_id, fmt)                   OAL_IO_PRINT("[WARNING]"fmt"\r\n")
#define OAM_WARNING_LOG1(_uc_vap_id, _en_feature_id, fmt, p1)               OAL_IO_PRINT("[WARNING]"fmt"\r\n", p1)
#define OAM_WARNING_LOG2(_uc_vap_id, _en_feature_id, fmt, p1, p2)           OAL_IO_PRINT("[WARNING]"fmt"\r\n", p1, p2)
#define OAM_WARNING_LOG3(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3)       OAL_IO_PRINT("[WARNING]"fmt"\r\n", p1, p2, p3)
#define OAM_WARNING_LOG4(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3, p4)   OAL_IO_PRINT("[WARNING]"fmt"\r\n", p1, p2, p3, p4)
#define OAM_ERROR_LOG0(_uc_vap_id, _en_feature_id, fmt)                     OAL_IO_PRINT("[ERROR]"fmt"\r\n")
#define OAM_ERROR_LOG1(_uc_vap_id, _en_feature_id, fmt, p1)                 OAL_IO_PRINT("[ERROR]"fmt"\r\n", p1)
#define OAM_ERROR_LOG2(_uc_vap_id, _en_feature_id, fmt, p1, p2)             OAL_IO_PRINT("[ERROR]"fmt"\r\n", p1, p2)
#define OAM_ERROR_LOG3(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3)         OAL_IO_PRINT("[ERROR]"fmt"\r\n", p1, p2, p3)
#define OAM_ERROR_LOG4(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3, p4)     OAL_IO_PRINT("[ERROR]"fmt"\r\n", p1, p2, p3, p4)
#define OAM_INFO_LOG0(_uc_vap_id, _en_feature_id, fmt)
#define OAM_INFO_LOG1(_uc_vap_id, _en_feature_id, fmt, p1)
#define OAM_INFO_LOG2(_uc_vap_id, _en_feature_id, fmt, p1, p2)
#define OAM_INFO_LOG3(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3)
#define OAM_INFO_LOG4(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3, p4)
#else


#define OAM_INFO_LOG0(_uc_vap_id, _en_feature_id, fmt)   \
        oam_log_print0(OAM_WIFI_LOG_PARA_PRESS(_uc_vap_id,_en_feature_id,THIS_FILE_ID,OAM_LOG_LEVEL_INFO), (oal_uint16)__LINE__, NULL)
#define OAM_INFO_LOG1(_uc_vap_id, _en_feature_id, fmt, p1)   \
        oam_log_print1(OAM_WIFI_LOG_PARA_PRESS(_uc_vap_id,_en_feature_id,THIS_FILE_ID,OAM_LOG_LEVEL_INFO), (oal_uint16)__LINE__, NULL, (oal_uint)p1)
#define OAM_INFO_LOG2(_uc_vap_id, _en_feature_id, fmt, p1, p2)   \
        oam_log_print2(OAM_WIFI_LOG_PARA_PRESS(_uc_vap_id,_en_feature_id,THIS_FILE_ID,OAM_LOG_LEVEL_INFO), (oal_uint16)__LINE__, NULL, (oal_uint)p1, (oal_uint)p2)
#define OAM_INFO_LOG3(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3)   \
        oam_log_print3(OAM_WIFI_LOG_PARA_PRESS(_uc_vap_id,_en_feature_id,THIS_FILE_ID,OAM_LOG_LEVEL_INFO), (oal_uint16)__LINE__, NULL, (oal_uint)p1, (oal_uint)p2, (oal_uint)p3)
#define OAM_INFO_LOG4(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3, p4)   \
        oam_log_print4(OAM_WIFI_LOG_PARA_PRESS(_uc_vap_id,_en_feature_id,THIS_FILE_ID,OAM_LOG_LEVEL_INFO), (oal_uint16)__LINE__, NULL, (oal_uint)p1, (oal_uint)p2, (oal_uint)p3, (oal_uint)p4)

#define OAM_WARNING_LOG0(_uc_vap_id, _en_feature_id, fmt)   \
        oam_log_print0(OAM_WIFI_LOG_PARA_PRESS(_uc_vap_id,_en_feature_id,THIS_FILE_ID,OAM_LOG_LEVEL_WARNING), (oal_uint16)__LINE__, NULL)
#define OAM_WARNING_LOG1(_uc_vap_id, _en_feature_id, fmt, p1)   \
        oam_log_print1(OAM_WIFI_LOG_PARA_PRESS(_uc_vap_id,_en_feature_id,THIS_FILE_ID,OAM_LOG_LEVEL_WARNING), (oal_uint16)__LINE__, NULL, (oal_uint)p1)
#define OAM_WARNING_LOG2(_uc_vap_id, _en_feature_id, fmt, p1, p2)   \
        oam_log_print2(OAM_WIFI_LOG_PARA_PRESS(_uc_vap_id,_en_feature_id,THIS_FILE_ID,OAM_LOG_LEVEL_WARNING), (oal_uint16)__LINE__, NULL, (oal_uint)p1, (oal_uint)p2)
#define OAM_WARNING_LOG3(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3)   \
        oam_log_print3(OAM_WIFI_LOG_PARA_PRESS(_uc_vap_id,_en_feature_id,THIS_FILE_ID,OAM_LOG_LEVEL_WARNING), (oal_uint16)__LINE__, NULL, (oal_uint)p1, (oal_uint)p2, (oal_uint)p3)
#define OAM_WARNING_LOG4(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3, p4)   \
        oam_log_print4(OAM_WIFI_LOG_PARA_PRESS(_uc_vap_id,_en_feature_id,THIS_FILE_ID,OAM_LOG_LEVEL_WARNING), (oal_uint16)__LINE__, NULL, (oal_uint)p1, (oal_uint)p2, (oal_uint)p3, (oal_uint)p4)

#define OAM_ERROR_LOG0(_uc_vap_id, _en_feature_id, fmt)   \
        oam_log_print0(OAM_WIFI_LOG_PARA_PRESS(_uc_vap_id,_en_feature_id,THIS_FILE_ID,OAM_LOG_LEVEL_ERROR), (oal_uint16)__LINE__, NULL)
#define OAM_ERROR_LOG1(_uc_vap_id, _en_feature_id, fmt, p1)   \
        oam_log_print1(OAM_WIFI_LOG_PARA_PRESS(_uc_vap_id,_en_feature_id,THIS_FILE_ID,OAM_LOG_LEVEL_ERROR), (oal_uint16)__LINE__, NULL, (oal_uint)p1)
#define OAM_ERROR_LOG2(_uc_vap_id, _en_feature_id, fmt, p1, p2)   \
        oam_log_print2(OAM_WIFI_LOG_PARA_PRESS(_uc_vap_id,_en_feature_id,THIS_FILE_ID,OAM_LOG_LEVEL_ERROR), (oal_uint16)__LINE__, NULL, (oal_uint)p1, (oal_uint)p2)
#define OAM_ERROR_LOG3(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3)   \
        oam_log_print3(OAM_WIFI_LOG_PARA_PRESS(_uc_vap_id,_en_feature_id,THIS_FILE_ID,OAM_LOG_LEVEL_ERROR), (oal_uint16)__LINE__, NULL, (oal_uint)p1, (oal_uint)p2, (oal_uint)p3)
#define OAM_ERROR_LOG4(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3, p4)   \
        oam_log_print4(OAM_WIFI_LOG_PARA_PRESS(_uc_vap_id,_en_feature_id,THIS_FILE_ID,OAM_LOG_LEVEL_ERROR), (oal_uint16)__LINE__, NULL, (oal_uint)p1, (oal_uint)p2, (oal_uint)p3, (oal_uint)p4)

#endif
#else
#define OAM_INFO_LOG0(_uc_vap_id, _en_feature_id, fmt)
#define OAM_INFO_LOG1(_uc_vap_id, _en_feature_id, fmt, p1)
#define OAM_INFO_LOG2(_uc_vap_id, _en_feature_id, fmt, p1, p2)
#define OAM_INFO_LOG3(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3)
#define OAM_INFO_LOG4(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3, p4)
#define OAM_WARNING_LOG0(_uc_vap_id, _en_feature_id, fmt)
#define OAM_WARNING_LOG1(_uc_vap_id, _en_feature_id, fmt, p1)
#define OAM_WARNING_LOG2(_uc_vap_id, _en_feature_id, fmt, p1, p2)
#define OAM_WARNING_LOG3(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3)
#define OAM_WARNING_LOG4(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3, p4)
#define OAM_ERROR_LOG0(_uc_vap_id, _en_feature_id, fmt)
#define OAM_ERROR_LOG1(_uc_vap_id, _en_feature_id, fmt, p1)
#define OAM_ERROR_LOG2(_uc_vap_id, _en_feature_id, fmt, p1, p2)
#define OAM_ERROR_LOG3(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3)
#define OAM_ERROR_LOG4(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3, p4)
#endif
#endif

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
#define OAM_DIFF_LOG0           OAM_INFO_LOG0
#define OAM_DIFF_LOG1           OAM_INFO_LOG1
#define OAM_DIFF_LOG2           OAM_INFO_LOG2
#define OAM_DIFF_LOG3           OAM_INFO_LOG3
#define OAM_DIFF_LOG4           OAM_INFO_LOG4
#else
#define OAM_DIFF_LOG0           OAM_WARNING_LOG0
#define OAM_DIFF_LOG1           OAM_WARNING_LOG1
#define OAM_DIFF_LOG2           OAM_WARNING_LOG2
#define OAM_DIFF_LOG3           OAM_WARNING_LOG3
#define OAM_DIFF_LOG4           OAM_WARNING_LOG4
#endif

#ifdef _PRE_PROFILING_MODE
#define OAM_PROFILING_RX_STATISTIC(_uc_func_idx) oam_profiling_rx_save_data(_uc_func_idx)
#define OAM_PROFILING_TX_STATISTIC(_pst_pointer, _uc_func_idx) oam_profiling_tx_save_data(_pst_pointer, _uc_func_idx)
#define OAM_PROFILING_ALG_STATISTIC(_uc_func_idx) oam_profiling_alg_save_data(_uc_func_idx)
#define OAM_PROFILING_STARTTIME_STATISTIC(_uc_func_idx) oam_profiling_starttime_save_timestamp(_uc_func_idx)
#define OAM_PROFILING_CHSWITCH_STATISTIC(_uc_func_idx) oam_profiling_chswitch_save_timestamp(_uc_func_idx)
#else
#define OAM_PROFILING_RX_STATISTIC(_uc_func_idx)
#define OAM_PROFILING_TX_STATISTIC(_pst_pointer, _uc_func_idx)
#define OAM_PROFILING_ALG_STATISTIC(_uc_func_idx)
#define OAM_PROFILING_STARTTIME_STATISTIC(_uc_func_idx)
#define OAM_PROFILING_CHSWITCH_STATISTIC(_uc_func_idx)
#endif
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
#ifdef _PRE_DEBUG_MODE

#define OAM_STAT_DEV_INCR(_uc_dev_id, _member, _num)do{                           \
            if (_uc_dev_id < WLAN_DEVICE_MAX_NUM_PER_CHIP)                            \
            {                                                                         \
                g_st_stat_info.ast_dev_stat_info[_uc_dev_id].ul_##_member += (_num);  \
            }                                                                         \
        }while(0)

#define OAM_STAT_DEV_ARRAY_INCR(_uc_dev_id, _member, _uc_array_index, _uc_array_max_size)do{            \
            if ((_uc_dev_id < WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC) && (_uc_array_index < _uc_array_max_size)) \
            {                                                                                          \
                g_st_stat_info.ast_dev_stat_info[_uc_dev_id].aul_##_member[_uc_array_index]++;         \
            }                                                                                          \
        }while(0)

#define OAM_STAT_DEV_UPDATE(_uc_dev_id, _member, _uc_q_id, _uc_index, _ul_val)do{  \
            if ((_uc_dev_id < WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC) \
                && (_uc_q_id < OAM_RX_DSCR_QUEUE_CNT) && (_uc_index < OAM_IRQ_FREQ_STAT_MEMORY))               \
            {                                                                                                   \
                g_st_stat_info.ast_dev_stat_info[_uc_dev_id].aul_##_member[_uc_q_id][_uc_index] = (_ul_val); \
            }                                                                                                   \
        }while(0)

#define OAM_STAT_DEV_GET_VAL(_uc_dev_id, _member,_pul_val) do{                             \
            if (_uc_dev_id < WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC)                              \
            {                                                                           \
               *(_pul_val)= g_st_stat_info.ast_dev_stat_info[_uc_dev_id].ul_##_member;      \
            }                                                                           \
        }while(0)

#define OAM_STAT_DEV_SET_VAL(_uc_dev_id, _member, _uc_val)do { \
            if (_uc_dev_id < WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC)                              \
            {                                                                           \
                g_st_stat_info.ast_dev_stat_info[_uc_dev_id].ul_##_member = (_uc_val); \
            }                                                                           \
        }while(0)

#define OAM_STAT_VAP_INCR(_uc_vap_id, _member, _num) do{ \
            if (_uc_vap_id < WLAN_VAP_SUPPOTR_MAX_NUM_SPEC)          \
            {                                                   \
                g_st_stat_info.ast_vap_stat_info[_uc_vap_id].ul_##_member += (_num);   \
            }                                                                               \
        }while(0)

#define OAM_STAT_MGMT_INCR(_uc_vap_id, _uc_mgmt_id, _member) do{  \
            if ((_uc_vap_id < WLAN_VAP_SUPPOTR_MAX_NUM_SPEC) && (_uc_mgmt_id < WLAN_MGMT_SUBTYPE_BUTT))   \
            {                                                                                        \
                g_st_stat_info.ast_vap_stat_info[_uc_vap_id].aul_##_member[_uc_mgmt_id]++;           \
            }                                                                                        \
        }while(0)

#define OAM_STAT_USER_INCR(_uc_user_id, _member, _num) do{                                       \
            if (_uc_user_id < WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC * WLAN_ACTIVE_USER_MAX_NUM)                     \
            {                                                                           \
                g_st_stat_info.ast_user_stat_info[_uc_user_id].ul_##_member += (_num);              \
            }                                                                               \
        }while(0)

#define OAM_STAT_TID_INCR(_uc_user_id, _uc_tid_num, _member, _num) do {\
            if ((_uc_user_id < WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC * WLAN_ACTIVE_USER_MAX_NUM) && (_uc_tid_num < WLAN_TIDNO_BUTT))        \
            {                                                                                       \
                g_st_stat_info.ast_user_stat_info[_uc_user_id].aul_##_member[_uc_tid_num] += (_num);\
            }                                                                                       \
        }while(0)

#define OAM_STAT_GET_STAT_ALL() (&g_st_stat_info)
#else
#define OAM_STAT_DEV_INCR(_uc_dev_id, _member, _num)
#define OAM_STAT_DEV_ARRAY_INCR(_uc_dev_id, _member, _uc_array_index, _uc_array_max_size)
#define OAM_STAT_DEV_UPDATE(_uc_dev_id, _member, _uc_q_id, _uc_index, _ul_val)
#define OAM_STAT_DEV_GET_VAL(_uc_dev_id, _member,_pul_val)
#define OAM_STAT_DEV_SET_VAL(_uc_dev_id, _member, _uc_val)
#define OAM_STAT_VAP_INCR(_uc_vap_id, _member, _num)
#define OAM_STAT_MGMT_INCR(_uc_vap_id, _uc_mgmt_id, _member)
#define OAM_STAT_USER_INCR(_uc_user_id, _member, _num)
#define OAM_STAT_TID_INCR(_uc_user_id, _uc_tid_num, _member, _num)
#define OAM_STAT_GET_STAT_ALL()

#endif
#elif defined(_PRE_PRODUCT_ID_HI110X_HOST)

#define OAM_STAT_DEV_INCR(_uc_dev_id, _member, _num)

#define OAM_STAT_DEV_ARRAY_INCR(_uc_dev_id, _member, _uc_array_index, _uc_array_max_size)

#define OAM_STAT_DEV_UPDATE(_uc_dev_id, _member, _uc_q_id, _uc_index, _ul_val)

#define OAM_STAT_DEV_GET_VAL(_uc_dev_id, _member,_pul_val)

#define OAM_STAT_DEV_SET_VAL(_uc_dev_id, _member, _uc_val)

#define OAM_STAT_VAP_INCR(_uc_vap_id, _member, _num) do{ \
            if (_uc_vap_id < WLAN_VAP_SUPPOTR_MAX_NUM_SPEC)          \
            {                                                   \
                g_st_stat_info.ast_vap_stat_info[_uc_vap_id].ul_##_member += (_num);   \
            }                                                                               \
        }while(0)

#define OAM_STAT_MGMT_INCR(_uc_vap_id, _uc_mgmt_id, _member)

#define OAM_STAT_USER_INCR(_uc_user_id, _member, _num)

#define OAM_STAT_TID_INCR(_uc_user_id, _uc_tid_num, _member, _num)

#define OAM_STAT_GET_STAT_ALL() (&g_st_stat_info)
#else
#ifdef _PRE_DEBUG_MODE

#define OAM_STAT_DEV_INCR(_uc_dev_id, _member, _num)do{                           \
            if (_uc_dev_id < WLAN_DEVICE_MAX_NUM_PER_CHIP)                            \
            {                                                                         \
            }                                                                         \
        }while(0)

#define OAM_STAT_DEV_ARRAY_INCR(_uc_dev_id, _member, _uc_array_index, _uc_array_max_size)do{            \
            if ((_uc_dev_id < WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC) && (_uc_array_index < _uc_array_max_size)) \
            {                                                                                          \
            }                                                                                          \
        }while(0)

#define OAM_STAT_DEV_UPDATE(_uc_dev_id, _member, _uc_q_id, _uc_index, _ul_val)do{  \
            if ((_uc_dev_id < WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC) \
                && (_uc_q_id < OAM_RX_DSCR_QUEUE_CNT) && (_uc_index < OAM_IRQ_FREQ_STAT_MEMORY))               \
            {                                                                                                   \
            }                                                                                                   \
        }while(0)

#define OAM_STAT_DEV_GET_VAL(_uc_dev_id, _member,_pul_val) do{                             \
            if (_uc_dev_id < WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC)                              \
            {                                                                           \
            }                                                                           \
        }while(0)

#define OAM_STAT_DEV_SET_VAL(_uc_dev_id, _member, _uc_val)do { \
            if (_uc_dev_id < WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC)                              \
            {                                                                           \
            }                                                                           \
        }while(0)

#define OAM_STAT_VAP_INCR(_uc_vap_id, _member, _num) do{ \
            if (_uc_vap_id < WLAN_VAP_SUPPOTR_MAX_NUM_SPEC)          \
            {                                                   \
            }                                                                               \
        }while(0)

#define OAM_STAT_MGMT_INCR(_uc_vap_id, _uc_mgmt_id, _member) do{  \
            if ((_uc_vap_id < WLAN_VAP_SUPPOTR_MAX_NUM_SPEC) && (_uc_mgmt_id < WLAN_MGMT_SUBTYPE_BUTT))   \
            {                                                                                        \
            }                                                                                        \
        }while(0)

#define OAM_STAT_USER_INCR(_uc_user_id, _member, _num) do{                                       \
            if (_uc_user_id < WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC * WLAN_ACTIVE_USER_MAX_NUM)                     \
            {                                                                           \
            }                                                                               \
        }while(0)

#define OAM_STAT_TID_INCR(_uc_user_id, _uc_tid_num, _member, _num) do {\
            if ((_uc_user_id < WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC * WLAN_ACTIVE_USER_MAX_NUM) && (_uc_tid_num < WLAN_TIDNO_BUTT))        \
            {                                                                                       \
            }                                                                                       \
        }while(0)

#define OAM_STAT_GET_STAT_ALL()
#else
#define OAM_STAT_DEV_INCR(_uc_dev_id, _member, _num)
#define OAM_STAT_DEV_ARRAY_INCR(_uc_dev_id, _member, _uc_array_index, _uc_array_max_size)
#define OAM_STAT_DEV_UPDATE(_uc_dev_id, _member, _uc_q_id, _uc_index, _ul_val)
#define OAM_STAT_DEV_GET_VAL(_uc_dev_id, _member,_pul_val)
#define OAM_STAT_DEV_SET_VAL(_uc_dev_id, _member, _uc_val)
#define OAM_STAT_VAP_INCR(_uc_vap_id, _member, _num)
#define OAM_STAT_MGMT_INCR(_uc_vap_id, _uc_mgmt_id, _member)
#define OAM_STAT_USER_INCR(_uc_user_id, _member, _num)
#define OAM_STAT_TID_INCR(_uc_user_id, _uc_tid_num, _member, _num)
#define OAM_STAT_GET_STAT_ALL()

#endif

#endif

#ifdef _PRE_DEBUG_MODE
#define OAM_TID_AMPDU_STATS_INCR(_member, _cnt)     ((_member) += (_cnt))
#else
#define OAM_TID_AMPDU_STATS_INCR(_member, _cnt)
#endif

#ifdef _PRE_WIFI_DMT
#define OAM_PRINT_FORMAT_LENGTH     1024
#else
#define OAM_PRINT_FORMAT_LENGTH     256
#endif

#define OAM_FUNC_NAME_MAX_LEN           48
#define OAM_LOG_INFO_MAX_LEN            100
#define OAM_LOG_INFO_IN_MEM_MAX_NUM     5000
#define OAM_LOG_ENTRY_PARA_NUM          4

//#define OAM_SEQ_TRACK_NUM              256
#define OAM_SEQ_TRACK_NUM              128

#define OAM_MAC_ERROR_TYPE_MAX_NUM      25
#define OAM_SOC_IRQ_MAX_NUM             5
#define OAM_PMU_BUCK_IRQ_MAX_NUM        5
#define OAM_MAC_SUB_IRQ_MAX_NUM         11

#define OAM_MEMBLOCK_INFO_STRU_LEN      8

#define OAM_FIRST_THREE_MEMBER_LEN      4

#define OAM_MAX_EVENT_NUM_IN_EVENT_QUEUE 8

#define OAM_RESERVE_SKB_HEADROOM_LEN    8
#define OAM_RESERVE_SKB_TAILROOM_LEN    1
#define OAM_RESERVE_SKB_LEN             (OAM_RESERVE_SKB_HEADROOM_LEN + OAM_RESERVE_SKB_TAILROOM_LEN)

#define OAM_REPORT_MAX_STRING_LEN       (WLAN_SDT_NETBUF_MAX_PAYLOAD - 1)

#define OAM_MAC_ERROR_TYPE_CNT    25
#define OAM_RX_DSCR_QUEUE_CNT     2
#define OAM_IRQ_FREQ_STAT_MEMORY  50

#define OAM_TID_TRACK_NUM         4

#ifdef _PRE_WLAN_DFT_STAT
#define  OAM_PHY_STAT_NODE_ENABLED_MAX_NUM    4
#define  OAM_PHY_STAT_RX_PPDU_CNT             8
#define  OAM_PHY_STAT_ITEM_MIN_IDX            1
#define  OAM_PHY_STAT_ITEM_MAX_IDX            16
#define  OAM_MACHW_STAT_RX_MEMBER_CNT         18
#define  OAM_MACHW_STAT_TX_MEMBER_CNT         8
#define  OAM_PSM_STAT_CNT                     10
#define  OAM_UAPSD_STAT_CNT                   11
#define  OAM_TID_STAT_CNT                     14
#endif

/*data type */
typedef enum
{
    OAM_DATA_TYPE_LOG       = 0x1,
    OAM_DATA_TYPE_OTA       = 0x2,
    OAM_DATA_TYPE_TRACE     = 0x3,
    OAM_DATA_TYPE_EVENT     = 0x4,
    OAM_DATA_TYPE_MEM_RW    = 0x9,
    OAM_DATA_TYPE_REG_RW    = 0x15,
    OAM_DATA_TYPE_CFG       = 0x0b,
    OAM_DATA_TYPE_GVAR_RW   = 0x27,   /* global value read or write */
    OAM_DATA_TYPE_STRING    = 0x28,   /* report string  */
    OAM_DATA_TYPE_DEVICE_LOG = 0x40,
    OAM_DATA_TYPE_BUTT
}oam_data_type_enum;
typedef oal_uint8 oam_data_type_enum_uint8;

typedef enum
{
    OAM_PRIMID_TYPE_PC_TO_DEV_DATA = 1,
    OAM_PRIMID_TYPE_DEV_ACK,
    OAM_PRIMID_TYPE_DEV_ACTIVE_UPLOAD,
    OAM_PRIMID_TYPE_OUTPUT_CONTENT,
    SDT_DRV_PRIMID_TYPE_BUTT
}oam_primid_type_enum;
typedef oal_uint8 oam_primid_type_enum_uint8;

typedef enum
{
    OAM_MODULE_ID_ALL,
    OAM_MODULE_ID_WAL,
    OAM_MODULE_ID_HMAC,
    OAM_MODULE_ID_DMAC,

    OAM_MODULE_ID_MAC,

    OAM_MODULE_ID_HAL,
    OAM_MODULE_ID_OAM,
    OAM_MODULE_ID_OAL,
    OAM_MODULE_ID_FRW,
    OAM_MODULE_ID_ALG,
    OAM_MODULE_ID_BLD,

    OAM_MODULE_ID_ALG_SCHEDULE,
    OAM_MODULE_ID_ALG_AUTORATE,
    OAM_MODULE_ID_ALG_SMARTANT,
    OAM_MODULE_ID_ALG_ACS,
    OAM_MODULE_ID_ALG_DBAC,

#ifdef _PRE_WIFI_DMT
    OAM_MODULE_ID_DMT,
#endif

#ifdef _PRE_WLAN_FEATURE_TXBF
    OAM_MODULE_ID_ALG_TXBF,
#endif

#ifdef _PRE_WLAN_PERFORM_STAT
    OAM_MODULE_ID_PERFORM_STAT,
#endif

    OAM_MODULE_ID_ALG_ANTI_INTF,

    OAM_MODULE_ID_HUT,

    OAM_MODULE_ID_ALG_CCA_OPT,

    OAM_MODULE_ID_BUTT
}oam_module_id_enum;
typedef oal_uint16 oam_module_id_enum_uint16;

typedef enum
{
    OAM_LOG_LEVEL_ERROR     =    1,
    OAM_LOG_LEVEL_WARNING,
    OAM_LOG_LEVEL_INFO,
    OAM_LOG_LEVEL_BUTT
}oam_log_level_enum;
typedef oal_uint8 oam_log_level_enum_uint8;

#define OAM_LOG_DEFAULT_LEVEL           OAM_LOG_LEVEL_WARNING

typedef enum
{
    OAM_CFG_TYPE_MAX_ASOC_USER            = 0,
    OAM_CFG_TYPE_BUTT
}oam_cfg_type_enum;
typedef oal_uint16 oam_cfg_type_enum_uint16;

typedef enum
{
    OAM_OUTPUT_TYPE_CONSOLE  = 0,
    OAM_OUTPUT_TYPE_FS,
    OAM_OUTPUT_TYPE_SDT, 
    OAM_OUTPUT_TYPE_BUTT
}oam_output_type_enum;
typedef oal_uint8 oam_output_type_enum_uint8;

typedef enum
{
    OAM_EVENT_WID_QUERY,
    OAM_EVENT_WID_WRITE,
    OAM_EVENT_INTERNAL,
    OAM_EVENT_VAP_STATE_CHANGE,
    OAM_EVENT_PAUSE_OR_RESUME_TID,
    OAM_EVENT_PAUSE_OR_RESUME_USER,
    OAM_EVENT_VAP_CHANGE_CHANNEL,
    OAM_EVENT_USER_INFO_CHANGE,
    OAM_EVENT_USER_TXRX_PARAM,
    OAM_EVENT_REGISTER = 9,
    OAM_EVENT_TYPE_BUTT
}oam_event_type_enum;
typedef oal_uint16 oam_event_type_enum_uint16;

typedef enum
{
    OAM_OTA_TYPE_RX_DSCR,
    OAM_OTA_TYPE_TX_DSCR,
    OAM_OTA_TYPE_80211_FRAME,
    OAM_OTA_TYPE_BEACON,
    OAM_OTA_TYPE_ETH_FRAME,
    OAM_OTA_TYPE_RX_DMAC_CB,
    OAM_OTA_TYPE_RX_HMAC_CB,
    OAM_OTA_TYPE_TX_CB,
    OAM_OTA_TYPE_TIMER_TRACK,
    OAM_OTA_TYPE_IRQ,
    OAM_OTA_TYPE_TIMER,
    OAM_OTA_TYPE_MEMPOOL,
    OAM_OTA_TYPE_MEMBLOCK,
    OAM_OTA_TYPE_EVENT_QUEUE,
    OAM_OTA_TYPE_MPDU_NUM,
    OAM_OTA_TYPE_PHY_STAT,
    OAM_OTA_TYPE_MACHW_STAT,
    OAM_OTA_TYPE_MGMT_STAT,
    OAM_OTA_TYPE_DBB_ENV_PARAM,
    OAM_OTA_TYPE_USR_QUEUE_STAT,
    OAM_OTA_TYPE_VAP_STAT,
    OAM_OTA_TYPE_USER_THRPUT_PARAM,
    OAM_OTA_TYPE_AMPDU_STAT,
    OAM_OTA_TYPE_HARDWARE_INFO,
    OAM_OTA_TYPE_USER_QUEUE_INFO,

    OAM_OTA_TYPE_HMAC_VAP,
    OAM_OTA_TYPE_DMAC_VAP,
    OAM_OTA_TYPE_HMAC_USER,
    OAM_OTA_TYPE_MAC_USER,
    OAM_OTA_TYPE_DMAC_USER,

    OAM_OTA_TYPE_HMAC_VAP_MEMBER_SIZE,
    OAM_OTA_TYPE_DMAC_VAP_MEMBER_SIZE,

    OAM_OTA_TYPE_DEV_STAT_INFO,
    OAM_OTA_TYPE_VAP_STAT_INFO,
    OAM_OTA_TYPE_USER_STAT_INFO,

    OAM_OTA_TYPE_PHY_BANK1_INFO,
    OAM_OTA_TYPE_PHY_BANK2_INFO,
    OAM_OTA_TYPE_PHY_BANK3_INFO,
    OAM_OTA_TYPE_PHY_BANK4_INFO,
    OAM_OTA_TYPE_MAC_BANK0_INFO,
    OAM_OTA_TYPE_MAC_BANK1_INFO,
    OAM_OTA_TYPE_MAC_BANK2_INFO,
    OAM_OTA_TYPE_MAC_BANK3_INFO,
    OAM_OTA_TYPE_MAC_BANK4_INFO,
    OAM_OTA_TYPE_RF_REG_INFO,
    OAM_OTA_TYPE_SOC_REG_INFO,
    OAM_OTA_TYPE_BUTT
}oam_ota_type_enum;
typedef oal_uint8 oam_ota_type_enum_uint8;

typedef enum
{
    OAM_TIMER_TRACK_TYPE_CREATE = 0,
    OAM_TIMER_TRACK_TYPE_DESTROY,
    OAM_TIMER_TRACK_TYPE_IMMEDIATE_DESTROY,
    OAM_TIMER_TRACK_TYPE_BUTT
}oam_timer_track_type_enum;
typedef oal_uint8 oam_timer_track_type_enum_uint8;

typedef enum
{
    OAM_USER_TRACK_CONTENT_FRAME = 0,
    OAM_USER_TRACK_CONTENT_CB,
    OAM_USER_TRACK_CONTENT_DSCR,
    OAM_USER_TRACK_CONTENT_BUTT
}oam_user_track_content_enum;
typedef oal_uint8 oam_user_track_content_enum_uint8;

typedef enum
{
    OAM_USER_TRACK_FRAME_TYPE_MGMT = 0,
    OAM_USER_TRACK_FRAME_TYPE_DATA,
    OAM_USER_TRACK_FRAME_TYPE_BUTT
}oam_user_track_frame_type_enum;
typedef oal_uint8 oam_user_track_frame_type_enum_uint8;

typedef enum
{
    OAM_USER_INFO_CHANGE_TYPE_ASSOC_STATE = 0,
    OAM_USER_INFO_CHANGE_TYPE_TX_PROTOCOL,
    OAM_USER_INFO_CHANGE_TYPE_RX_PROTOCOL,
    OAM_USER_INFO_CHANGE_TYPE_BUTT
}oam_user_info_change_type_enum;
typedef oal_uint8 oam_user_info_change_type_enum_uint8;

typedef enum
{
    OAM_USER_TXRX_PARAM_TYPE_RSSI = 0,
    OAM_USER_TXRX_PARAM_TYPE_RATE,
    OAM_USER_TXRX_PARAM_TYPE_BUTT
}oam_user_txrx_param_type_enum;
typedef oal_uint8 oam_user_txrx_param_type_enum_uint8;

typedef enum
{
    OAM_STATS_TYPE_DEVICE,
    OAM_STATS_TYPE_VAP,
    OAM_STATS_TYPE_USER,
    OAM_STATS_TYPE_BUTT
}oam_stats_type_enum;
typedef oal_uint8 oam_stats_type_enum_uint8;

typedef enum
{
    OAM_STATS_DEVICE_SUBTYPE_IRQ,
    OAM_STATS_DEVICE_SUBTYPE_TIMER,
    OAM_STATS_DEVICE_SUBTYPE_MEMPOOL,
    OAM_STATS_DEVICE_SUBTYPE_EVENT_QUEUE,
    OAM_STATS_DEVICE_SUBTYPE_BUTT
}oam_stats_device_subtype_enum;
typedef oal_uint8 oam_stats_device_subtype_enum_uint8;

typedef enum
{
    OAM_ALARM_TYPE_MEM_OVER_LEAK,
    OAM_ALARM_TYPE_PKT_RECV_LOST,
    OAM_ALARM_TYPE_PKT_SEND_LOST,
    OAM_ALARM_TYPE_BUTT
}oam_alarm_type_enum;
typedef oal_uint16 oam_alarm_type_enum_uint16;

typedef enum
{
    OAM_MEMBLOCK_INFO_TYPE_UNIFORM,
    OAM_MEMBLOCK_INFO_TYPE_NON_UNIFORM,
    OAM_MEMBLOCK_INFO_TYPE_BUTT
}oam_memblock_info_type_enum;
typedef oal_uint8 oam_memblock_info_type_enum_uint8;

typedef enum
{
    OAM_STRUCT_TYPE_DEVICE,
    OAM_STRUCT_TYPE_HMAC_VAP,
    OAM_STRUCT_TYPE_MAC_VAP,
    OAM_STRUCT_TYPE_DMAC_VAP,
    OAM_STRUCT_TYPE_HMAC_USER,
    OAM_STRUCT_TYPE_MAC_USER,
    OAM_STRUCT_TYPE_DMAC_USER,
    OAM_STRUCT_TYPE_TID,

    OAM_STRUCT_TYPE_BUTT
}oam_struct_type_enum;
typedef oal_uint8 oam_struct_type_enum_uint8;

typedef enum
{
    OAM_PROFILING_SWITCH_OFF,
    OAM_PROFILING_SWITCH_ON,

    OAM_PROFILING_SWITCH_BUTT
}oam_profiling_swith_enum;
typedef oal_uint8 oam_profiling_swith_enum_uint8;

typedef enum
{
    OAM_PROFILING_FUNC_CONFIG_XMIT_START,
    OAM_PROFILING_FUNC_BRIDGE_XMIT_START,
    OAM_PROFILING_FUNC_TX_TO_WLAN,
    OAM_PROFILING_FUNC_DMAC_TX_START,
    OAM_PROFILING_FUNC_TID_ENQUEUE,
    OAM_PROFILING_FUNC_BRIDGE_XMIT_END,
    OAM_PROFILING_FUNC_CONFIG_XMIT_END,

    OAM_PROFILING_FUNC_SCHEDULE_START,
    OAM_PROFILING_FUNC_SCHEDULE,
    OAM_PROFILING_FUNC_SCHEDULE_GET_TID,
    OAM_PROFILING_FUNC_AMPDU_AGGR_PREPARE,
    OAM_PROFILING_FUNC_AMPDU_CALCULATE_MINLEN,
    OAM_PROFILING_FUNC_AMPDU_REMOVE_QUEUE,
    OAM_PROFILING_FUNC_TX_GET_TSF,
    OAM_PROFILING_FUNC_TX_SET_DSCR,
    OAM_PROFILING_FUNC_TX_PUT_DSCR,
    OAM_PROFILING_FUNC_SCHEDULE_END,

    OAM_PROFILING_FUNC_TX_COMP_IRQ_START,
    OAM_PROFILING_FUNC_TX_COMP_IRQ_END,
    OAM_PROFILING_FUNC_TX_COMP_DMAC_START,
    OAM_PROFILING_FUNC_AMPDU_AMPDU_PREPARE,
    OAM_PROFILING_FUNC_AMPDU_UPDATE_MIB,
    OAM_PROFILING_FUNC_AMPDU_TX_COMP_CHECK,
    OAM_PROFILING_FUNC_AMPDU_EXTRACT_BA,
    OAM_PROFILING_FUNC_AMPDU_COMP_ACK,
    OAM_PROFILING_FUNC_AMPDU_COMP_ENQUEUE_RETRY,
    OAM_PROFILING_FUNC_TX_COMP_DMAC_END,

    OAM_PROFILING_TX_FUNC_BUTT
} oam_profiling_tx_func_enum;
typedef oal_uint8 oam_profiling_tx_func_enum_uint8;

typedef enum
{
    OAM_PROFILING_RX,
    OAM_PROFILING_TX,
    OAM_PROFILING_ALG,

    OAM_PROFILING_CHIPSTART,
    OAM_PROFILING_CHSWTICH,

    OAM_PROFILING_BUTT
}oam_profiling_enum;
typedef oal_uint8 oam_profiling_enum_uint8;

typedef enum
{
    OAM_PROFILING_FUNC_RX_COMP_IRQ_START,
    OAM_PROFILING_FUNC_RX_COMP_START,
    OAM_PROFILING_FUNC_RX_COMP_BASE_INFO,
    OAM_PROFILING_FUNC_RX_COMP_ALLOC_EVENT,
    OAM_PROFILING_FUNC_RX_COMP_IRQ_END,


    OAM_PROFILING_FUNC_RX_DMAC_START,
    OAM_PROFILING_FUNC_RX_DMAC_GET_CB_LIST,
    OAM_PROFILING_FUNC_RX_DMAC_HANDLE_MPDU,

    OAM_PROFILING_FUNC_RX_HMAC_START,
    OAM_PROFILING_FUNC_RX_HMAC_BASE_INFO,
    OAM_PROFILING_FUNC_RX_HMAC_TO_LAN,
    OAM_PROFILING_FUNC_RX_HMAC_TO_WLAN,
    OAM_PROFILING_FUNC_RX_HMAC_END,
    OAM_PROFILING_FUNC_RX_DMAC_END,

    OAM_PROFILING_RX_FUNC_BUTT
} oam_profiling_rx_func_enum;
typedef oal_uint8 oam_profiling_rx_func_enum_uint8;

typedef enum
{
    OAM_PROFILING_ALG_START,

#ifdef _PRE_WLAN_FEATURE_AUTORATE
    OAM_PROFILING_AUTORATE_QUERY_RATE_START,
    OAM_PROFILING_AUTORATE_SET_RATE_START,
    OAM_PROFILING_AUTORATE_SET_RATE_END,
    OAM_PROFILING_AUTORATE_QUERY_RATE_END,
    OAM_PROFILING_AUTORATE_UPDATE_RATE_START,
    OAM_PROFILING_AUTORATE_UPDATE_STAT_INFO_START,
    OAM_PROFILING_AUTORATE_UPDATE_STAT_INFO_END,
    OAM_PROFILING_AUTORATE_UPDATE_RATE_END,
    OAM_PROFILING_AUTORATE_SELECT_RATE_START,
    OAM_PROFILING_AUTORATE_NON_PROBE_STATE_PROCESS_START,
    OAM_PROFILING_AUTORATE_NON_PROBE_STATE_PROCESS_END,
    OAM_PROFILING_AUTORATE_PROBE_STATE_PROCESS_START,
    OAM_PROFILING_AUTORATE_PROBE_STATE_PROCESS_END,
    OAM_PROFILING_AUTORATE_SELECT_RATE_END,
#endif

#ifdef _PRE_WLAN_FEATURE_TRAFFIC_CTL
    OAM_PROFILING_TRAFFIC_DOWNLINK_FLOWCTRL_START,
    OAM_PROFILING_TRAFFIC_DOWNLINK_FLOWCTRL_END,
#endif

#ifdef _PRE_WLAN_FEATURE_SCHEDULE
    OAM_PROFILING_SCHEDULE_TX_TID_SCH_START,
    OAM_PROFILING_SCHEDULE_TX_TID_SCH_END,
    OAM_PROFILING_SCHEDULE_UPDATE_TXTID_START,
    OAM_PROFILING_SCHEDULE_UPDATE_TXTID_END,
    OAM_PROFILING_SCHEDULE_TX_COMP_START,
    OAM_PROFILING_SCHEDULE_TX_COMP_END,
#endif

    OAM_PROFILING_ALG_END,
    OAM_PROFILING_ALG_FUNC_BUTT
} oam_profiling_alg_func_enum;
typedef oal_uint8 oam_profiling_alg_func_enum_uint8;

typedef enum
{
    OAM_PROFILING_STARTTIME_SELF_BEGIN,
    OAM_PROFILING_STARTTIME_SELF_END,
    OAM_PROFILING_STARTTIME_SOC_BEGIN,
    OAM_PROFILING_STARTTIME_SOC_END,
    OAM_PROFILING_STARTTIME_MAC_BEGIN,
    OAM_PROFILING_STARTTIME_MAC_END,
    OAM_PROFILING_STARTTIME_PHY_BEGIN,
    OAM_PROFILING_STARTTIME_PHY_END,
    OAM_PROFILING_STARTTIME_ABB_BEGIN,
    OAM_PROFILING_STARTTIME_ABB_END,
    OAM_PROFILING_STARTTIME_RF_BEGIN,
    OAM_PROFILING_STARTTIME_RF_END,

    OAM_PROFILING_RESET_HW_BEGIN,
    OAM_PROFILING_RESET_HW_END,
    OAM_PROFILING_RESET_TOTAL_BEGIN,
    OAM_PROFILING_RESET_TOTAL_END,

    OAM_PROFILING_STARTTIME_FUNC_BUTT
}oam_profiling_starttime_func_enum;
typedef oal_uint8 oam_profiling_starttime_func_enum_uint8;

typedef enum
{
    OAM_PROFILING_CHSWITCH_START,
    OAM_PROFILING_CHSWITCH_END,

    OAM_PROFILING_CHSWITCH_FUNC_BUTT
}oam_profiling_chswitch_func_enum;
typedef oal_uint8 oam_profiling_chswitch_func_enum_uint8;

typedef enum
{
    OAM_SDT_MODE_WRITE = 0,
    OAM_SDT_MODE_READ,

    OAM_SDT_MODE_BUTT
}oam_sdt_rw_mode_enum;
typedef oal_uint8 oam_sdt_rw_mode_enum_uint8;

typedef enum
{
    OAM_SDT_PRINT_BEACON_RXDSCR_TYPE_BEACON = 1,
    OAM_SDT_PRINT_BEACON_RXDSCR_TYPE_RXDSCR,
    OAM_SDT_PRINT_BEACON_RXDSCR_TYPE_BOTH,

    OAM_SDT_PRINT_BEACON_RXDSCR_TYPE_BUTT
}oam_sdt_print_beacon_rxdscr_type_enum;
typedef oal_uint8 oam_sdt_print_beacon_rxdscr_type_enum_uint8;

typedef enum
{
    OAM_OTA_FRAME_DIRECTION_TYPE_TX = 0,
    OAM_OTA_FRAME_DIRECTION_TYPE_RX,

    OAM_OTA_FRAME_DIRECTION_TYPE_BUTT
}oam_ota_frame_direction_type_enum;
typedef oal_uint8 oam_ota_frame_direction_type_enum_uint8;

typedef enum
{
    OAM_NL_CMD_SDT = 0,
    OAM_NL_CMD_HUT,
    OAM_NL_CMD_ALG,
    OAM_NL_CMD_ACS,
    OAM_NL_CMD_DAQ,
    OAM_NL_CMD_REG,
    OAM_NL_CMD_PSTA,

    OAM_NL_CMD_BUTT
}oam_nl_cmd_enum;
typedef oal_uint8 oam_nl_cmd_enum_uint8;

typedef enum
{
    OAM_SF_SCAN                 = 0,
    OAM_SF_AUTH,
    OAM_SF_ASSOC,
    OAM_SF_FRAME_FILTER,
    OAM_SF_WMM,

    OAM_SF_DFS                  = 5,
    OAM_SF_NETWORK_MEASURE,
    OAM_SF_ENTERPRISE_VO,
    OAM_SF_HOTSPOTROAM,
    OAM_SF_NETWROK_ANNOUNCE,

    OAM_SF_NETWORK_MGMT         = 10,
    OAM_SF_NETWORK_PWS,
    OAM_SF_PROXYARP,
    OAM_SF_TDLS,
    OAM_SF_CALIBRATE,

    OAM_SF_EQUIP_TEST           = 15,
    OAM_SF_CRYPTO,
    OAM_SF_WPA,
    OAM_SF_WEP,
    OAM_SF_WPS,

    OAM_SF_PMF                  = 20,
    OAM_SF_WAPI,
    OAM_SF_BA,
    OAM_SF_AMPDU,
    OAM_SF_AMSDU,

    OAM_SF_STABILITY            = 25,
    OAM_SF_TCP_OPT,
    OAM_SF_ACS,
    OAM_SF_AUTORATE,
    OAM_SF_TXBF,

    OAM_SF_DYN_RECV             = 30,                        /* dynamin recv*/
    OAM_SF_VIVO,                            /* video_opt voice_opt */
    OAM_SF_MULTI_USER,
    OAM_SF_MULTI_TRAFFIC,
    OAM_SF_ANTI_INTF,

    OAM_SF_EDCA                 = 35,
    OAM_SF_SMART_ANTENNA,
    OAM_SF_TPC,
    OAM_SF_TX_CHAIN,
    OAM_SF_RSSI,

    OAM_SF_WOW                  = 40,
    OAM_SF_GREEN_AP,
    OAM_SF_PWR,                             /* psm uapsd fastmode */
    OAM_SF_SMPS,
    OAM_SF_TXOP,

    OAM_SF_WIFI_BEACON          = 45,
    OAM_SF_KA_AP,                           /* keep alive ap */
    OAM_SF_MULTI_VAP,
    OAM_SF_2040,                            /* 20m+40m coex*/
    OAM_SF_DBAC,

    OAM_SF_PROXYSTA             = 50,
    OAM_SF_UM,                              /* user managment */
    OAM_SF_P2P,
    OAM_SF_M2U,
    OAM_SF_IRQ,                             /* top half */

    OAM_SF_TX                   = 55,
    OAM_SF_RX,
    OAM_SF_DUG_COEX,
    OAM_SF_CFG,
    OAM_SF_FRW,

    OAM_SF_KEEPALIVE            = 60,
    OAM_SF_COEX,
    OAM_SF_HS20                 = 62,
    OAM_SF_MWO_DET,
    OAM_SF_CCA_OPT,

    OAM_SF_ROAM                 = 65,       /* roam module, #ifdef _PRE_WLAN_FEATURE_ROAM */
    OAM_SF_DFT,
    OAM_SF_DFR,
    OAM_SF_VOWIFI,
    OAM_SF_WMMAC,
    OAM_SF_ANY,                             /* rifs protection shortgi frag datarate countrycode
                                                coustom_security startup_time lsig monitor wds
                                                hidessid */

    OAM_SF_HILINK,

    OAM_SOFTWARE_FEATURE_BUTT
}oam_feature_enum;
typedef oal_uint8   oam_feature_enum_uint8;

typedef enum
{
    OAM_RATELIMIT_TYPE_PRINTK        = 0,
    OAM_RATELIMIT_TYPE_LOG,
    OAM_RATELIMIT_TYPE_DSCR,
    OAM_RATELIMIT_TYPE_FRAME_WLAN,
    OAM_RATELIMIT_TYPE_FRAME_ETH,
    OAM_RATELIMIT_TYPE_CB,
    OAM_RATELIMIT_TYPE_BUTT
}oam_ratelimit_type_enum;
typedef oal_uint8   oam_ratelimit_type_enum_uint8;

#define OAM_EXCP_STATS_TIMEOUT          (5000)
typedef enum
{
    OAM_HAL_MAC_ERROR_PARA_CFG_ERR                  = 0,
    OAM_HAL_MAC_ERROR_RXBUFF_LEN_TOO_SMALL          = 1,
    OAM_HAL_MAC_ERROR_BA_ENTRY_NOT_FOUND            = 2,
    OAM_HAL_MAC_ERROR_PHY_TRLR_TIME_OUT             = 3,
    OAM_HAL_MAC_ERROR_PHY_RX_FIFO_OVERRUN           = 4,
    OAM_HAL_MAC_ERROR_TX_DATAFLOW_BREAK             = 5,
    OAM_HAL_MAC_ERROR_RX_FSM_ST_TIMEOUT             = 6,
    OAM_HAL_MAC_ERROR_TX_FSM_ST_TIMEOUT             = 7,
    OAM_HAL_MAC_ERROR_RX_HANDLER_ST_TIMEOUT         = 8,
    OAM_HAL_MAC_ERROR_TX_HANDLER_ST_TIMEOUT         = 9,
    OAM_HAL_MAC_ERROR_TX_INTR_FIFO_OVERRUN          = 10,
    OAM_HAL_MAC_ERROR_RX_INTR_FIFO_OVERRUN          = 11,
    OAM_HAL_MAC_ERROR_HIRX_INTR_FIFO_OVERRUN        = 12,
    OAM_HAL_MAC_ERROR_RX_Q_EMPTY                    = 13,
    OAM_HAL_MAC_ERROR_HIRX_Q_EMPTY                  = 14,
    OAM_HAL_MAC_ERROR_BUS_RLEN_ERR                  = 15,
    OAM_HAL_MAC_ERROR_BUS_RADDR_ERR                 = 16,
    OAM_HAL_MAC_ERROR_BUS_WLEN_ERR                  = 17,
    OAM_HAL_MAC_ERROR_BUS_WADDR_ERR                 = 18,
    OAM_HAL_MAC_ERROR_TX_ACBK_Q_OVERRUN             = 19,
    OAM_HAL_MAC_ERROR_TX_ACBE_Q_OVERRUN             = 20,
    OAM_HAL_MAC_ERROR_TX_ACVI_Q_OVERRUN             = 21,
    OAM_HAL_MAC_ERROR_TX_ACVO_Q_OVERRUN             = 22,
    OAM_HAL_MAC_ERROR_TX_HIPRI_Q_OVERRUN            = 23,
    OAM_HAL_MAC_ERROR_MATRIX_CALC_TIMEOUT           = 24,
    OAM_HAL_MAC_ERROR_CCA_TIMEOUT                   = 25,
    OAM_HAL_MAC_ERROR_DCOL_DATA_OVERLAP             = 26,
    OAM_HAL_MAC_ERROR_BEACON_MISS                   = 27,
    OAM_HAL_MAC_ERROR_UNKOWN_28                     = 28,
    OAM_HAL_MAC_ERROR_UNKOWN_29                     = 29,
    OAM_HAL_MAC_ERROR_UNKOWN_30                     = 30,
    OAM_HAL_MAC_ERROR_UNKOWN_31                     = 31,

    OAM_HAL_SOC_ERROR_BUCK_OCP                      = 32,
    OAM_HAL_SOC_ERROR_BUCK_SCP,
    OAM_HAL_SOC_ERROR_OCP_RFLDO1,
    OAM_HAL_SOC_ERROR_OCP_RFLDO2,
    OAM_HAL_SOC_ERROR_OCP_CLDO,
    OAM_HAL_SOC_ERROR_RF_OVER_TEMP,
    OAM_HAL_SOC_ERROR_CMU_UNLOCK,
    OAM_HAL_SOC_ERROR_PCIE_SLV_ERR,

    OAM_EXCP_TYPE_BUTT
}oam_excp_type_enum;
typedef oal_uint8   oam_excp_type_enum_uint8;

typedef enum
{
    OAM_EXCP_STATUS_INIT = 0,
    OAM_EXCP_STATUS_REFRESHED,
    OAM_EXCP_STATUS_BUTT
}oam_excp_status_enum;
typedef oal_uint8   oam_excp_status_enum_uint8;

#ifdef _PRE_DEBUG_MODE
extern oal_uint32   g_aul_debug_feature_switch[];

#define             MAX_DEBUG_TYPE_NUM              OAM_DEBUG_TYPE_BUTT
typedef enum
{
    OAM_DEBUG_TYPE_ECHO_REG          = 0,

    OAM_DEBUG_TYPE_BUTT
}oam_debug_type_enum;

#endif

#ifdef _PRE_WLAN_DFT_STAT
typedef enum
{
    OAM_STATS_PHY_NODE_TX_CNT = 1,
    OAM_STATS_PHY_NODE_RX_OK_CNT,
    OAM_STATS_PHY_NODE_SYN_CNT,
    OAM_STATS_PHY_NODE_OFDM_SYN_ERR_CNT,
    OAM_STATS_PHY_NODE_AGC_LOCK_CNT,
    OAM_STATS_PHY_NODE_11B_HDR_ERR_CNT,
    OAM_STATS_PHY_NODE_OFDM_HDR_ERR_CNT,
    OAM_STATS_PHY_NODE_UNSUPPORTED_CNT,
    OAM_STATS_PHY_NODE_CARRIER_LOSE_CNT,
    OAM_STATS_PHY_NODE_LDPC_FAIL_CNT,
    OAM_STATS_PHY_NODE_RX_TIMEOUT_CNT,
    OAM_STATS_PHY_NODE_HI_PIN_UNLOCK_CNT,
    OAM_STATS_PHY_NODE_LO_PIN_UNLOCK_CNT,
    OAM_STATS_PHY_NODE_INIT_BW_LARGER_CNT,
    OAM_STATS_PHY_NODE_INIT_BW_SMALLER_CNT,
    OAM_STATS_PHY_NODE_INIT_BW_EQUAL_CNT,

    OAM_STATS_PHY_NODE_BUTT
}oam_stats_phy_node_idx_enum;
typedef oal_uint8 oam_stats_phy_node_idx_enum_uint8;
#endif

extern oal_uint8 g_auc_bcast_addr[WLAN_MAC_ADDR_LEN];
#define BROADCAST_MACADDR       g_auc_bcast_addr

typedef oal_int32   (* oam_sdt_up_func)(oal_netbuf_stru *pst_netbuf);
typedef oal_int32   (* oam_sdt_report_data_func)(oal_netbuf_stru *pst_netbuf, oam_data_type_enum_uint8 en_type, oam_primid_type_enum_uint8 en_prim);
typedef oal_int32   (* oam_sdt_status_func)(oal_void);

typedef struct
{
    oal_int32       (* p_sdt_report_data_func)(oal_netbuf_stru *pst_netbuf, oam_data_type_enum_uint8 en_type, oam_primid_type_enum_uint8 en_prim);
    oal_int32       (* p_sdt_get_wq_len_func)(oal_void);
}oam_sdt_func_hook_stru;

extern oam_sdt_func_hook_stru       g_st_oam_sdt_func_hook;

typedef struct
{
   oal_int32       (* p_wal_recv_mem_data_func)(oal_uint8 *puc_buf, oal_uint16 us_len);
   oal_int32       (* p_wal_recv_reg_data_func)(oal_uint8 *puc_buf, oal_uint16 us_len);
   oal_int32       (* p_wal_recv_cfg_data_func)(oal_uint8 *puc_buf, oal_uint16 us_len);
   oal_int32       (* p_wal_recv_global_var_func)(oal_uint8 *puc_buf, oal_uint16 us_len);
}oam_wal_func_hook_stru;

extern oam_wal_func_hook_stru       g_st_oam_wal_func_hook;

typedef struct
{
    oal_uint32  ul_offset;
    oal_uint8   uc_lenth;
    oal_uint8   uc_mode;
    oal_uint8   auc_val[4];
    oal_uint8   auc_var_name[4];
}oal_sdt_global_var_stru;

typedef struct
{
    oam_feature_enum_uint8              en_feature_id;
    oam_log_level_enum_uint8            en_log_level;
    oal_switch_enum_uint8               en_switch;
    oal_uint8                           uc_resv;
}oam_cfg_log_level_stru;

typedef struct
{
    oal_uint8    bit_vap_id      :  4;
    oal_uint8    bit_log_level   :  4;
}oam_vap_log_level_stru;

typedef struct
{
    oam_vap_log_level_stru              st_vap_log_level;
    oam_feature_enum_uint8              en_feature_id;
    oal_uint16                          us_resv;
    oal_uint16                          us_file_id;
    oal_uint16                          us_line_num;
    oal_uint32                          ul_tick;
    oal_int32                           al_param[OAM_LOG_ENTRY_PARA_NUM];
}oam_log_info_stru;

typedef struct
{
    oam_log_info_stru                ast_log_info[OAM_LOG_INFO_IN_MEM_MAX_NUM];
    oal_uint16                       us_index;
}oam_log_info_in_mem_stru;

typedef struct
{
    oal_spin_lock_stru              spin_lock;
    oal_switch_enum_uint8           en_ratelimit_switch;
    oal_uint32                      ul_interval;
    oal_uint32                      ul_burst;
    oal_uint32                      ul_printed;
    oal_uint32                      ul_missed;
    oal_uint32                      ul_begin;
}oam_ratelimit_stru;

typedef struct
{
    oal_uint32                      ul_file_id;
    oal_uint32                      ul_line_num;
    oam_timer_track_type_enum_uint8 en_type;
    oal_uint8                       auc_resv[3];
}oam_timer_track_info_stru;

typedef struct
{
    oal_uint16              us_total_mpdu_num_in_device;
    oal_uint16              us_mpdu_num_in_tid0;
    oal_uint16              us_mpdu_num_in_tid1;
    oal_uint16              us_mpdu_num_in_tid2;
    oal_uint16              us_mpdu_num_in_tid3;
    oal_uint16              us_mpdu_num_in_tid4;
    oal_uint16              us_mpdu_num_in_tid5;
    oal_uint16              us_mpdu_num_in_tid6;
    oal_uint16              us_mpdu_num_in_tid7;
    oal_uint8               auc_resv[2];
}oam_report_mpdu_num_stru;

typedef struct
{
    oal_uint32                              ul_tick;
    oam_ota_type_enum_uint8                 en_ota_type;
    oal_uint8                               uc_frame_hdr_len;
    oal_uint16                              us_ota_data_len;
    oal_uint8                               auc_user_macaddr[WLAN_MAC_ADDR_LEN];
    oam_ota_frame_direction_type_enum_uint8 en_frame_direction;
    oal_uint8                               auc_resv[1];
}oam_ota_hdr_stru;

typedef struct
{
    oam_ota_hdr_stru                st_ota_hdr;
    oal_uint8                       auc_ota_data[4];
}oam_ota_stru;

#define OAM_EVENT_INFO_MAX_LEN          48

typedef struct
{
    oal_uint32				         ul_tick;
    oam_event_type_enum_uint16	     en_event_type;
 	oam_module_id_enum_uint16        en_module;
 	oal_uint8                        auc_user_macaddr[WLAN_MAC_ADDR_LEN];
    oal_uint8                        uc_vap_id;
    oal_uint8                        auc_resv[1];
}oam_event_hdr_stru;

typedef struct
{
    oam_event_hdr_stru               st_event_hdr;
	oal_int8                         auc_event_info[OAM_EVENT_INFO_MAX_LEN];
}oam_event_stru;

#define OAM_EVENT_STRU_SIZE         OAL_SIZEOF(oam_event_stru)

typedef struct
{
    oal_uint8                               uc_mem_pool_id;
    oal_uint8                               uc_subpool_id;
    oal_uint8                               auc_resv[2];
    oal_uint16                              us_mem_pool_total_cnt;
    oal_uint16                              us_mem_pool_used_cnt;
    oal_uint16                              us_subpool_total_cnt;
    oal_uint16                              us_subpool_free_cnt;
}oam_stats_mempool_stru;

typedef struct
{
    oal_uint8                               uc_pool_id;
    oal_uint8                               uc_subpool_id;
    oal_uint8                               uc_user_cnt;
    oal_uint8                               auc_resv[1];
    oal_uint32                              ul_file_id;
    oal_uint32                              ul_alloc_line_num;
}oam_memblock_info_stru;

typedef struct
{
    oal_uint8							    en_type;
    oal_uint8                               uc_sub_type;
    oal_uint16                              us_length;
    oal_uint8                               en_pipeline;
    oal_uint8                               uc_chip_id;
    oal_uint8                               uc_device_id;
    oal_uint8                               uc_vap_id;
}oam_event_hdr_info_stru;

typedef struct
{
    oal_uint8                               uc_event_num_in_queue;
    oal_uint8                               auc_resv[3];

    oam_event_hdr_info_stru                 ast_event_hdr_info[OAM_MAX_EVENT_NUM_IN_EVENT_QUEUE];
}oam_event_queue_info_stru;

#ifdef _PRE_DEBUG_MODE_USER_TRACK

typedef struct
{
    oal_uint32                              ul_val_before_change;
    oal_uint32                              ul_val_after_change;
    oam_user_info_change_type_enum_uint8    en_change_type;
    oal_uint8                               auc_resv[3];
}oam_user_info_change_stru;

typedef struct
{
    oal_uint32      ul_best_rate_kbps;
    oal_uint16      us_best_rate_per;
    oal_uint8       uc_best_rate_aggr_num;
    oal_uint8       uc_resv;
}oam_best_rate_stat_stru;

typedef struct
{
    oal_int8                                c_avg_tx_rssi;
    oal_int8                                c_avg_rx_rssi;
    oal_uint16                              us_avg_rx_aggr_num;
    oal_uint32                              ul_avg_tx_rate;
    oal_uint32                              ul_avg_rx_rate;
    oam_best_rate_stat_stru                 ast_best_rate_stat[WLAN_WME_AC_BUTT];
}oam_user_track_thrput_param_stru;

typedef struct
{
    oal_bool_enum_uint8                     en_flg;
    oal_uint8                               auc_resv[1];
    oal_uint16                              us_rx_ampdu_num;
    oal_uint32                              ul_rx_mpdu_in_ampdu;
}oam_user_track_rx_ampdu_stat;
#endif
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)||defined(_PRE_PRODUCT_ID_HI110X_HOST)

typedef struct
{
    oal_uint32  ul_irq_cnt;
    oal_uint32  ul_pmu_err_irq_cnt;
    oal_uint32  ul_rf_over_temp_irq_cnt;
    oal_uint32  ul_unlock_irq_cnt;
    oal_uint32  ul_mac_irq_cnt;
    oal_uint32  ul_pcie_slv_err_irq_cnt;
    oal_uint32  ul_buck_ocp_irq_cnt;
    oal_uint32  ul_buck_scp_irq_cnt;
    oal_uint32  ul_ocp_rfldo1_irq_cnt;
    oal_uint32  ul_ocp_rfldo2_irq_cnt;
    oal_uint32  ul_ocp_cldo_irq_cnt;
    oal_uint32  ul_rx_complete_cnt;
    oal_uint32  ul_tx_complete_cnt;
    oal_uint32  ul_hi_rx_complete_cnt;
    oal_uint32  ul_error_cnt;
    oal_uint32  aul_tbtt_cnt[WLAN_VAP_SUPPORT_MAX_NUM_LIMIT];
    oal_uint32  ul_abort_intr_start;
    oal_uint32  ul_abort_intr_end;
    oal_uint32  ul_radar_detect_cnt;
    oal_uint32  ul_pa_tx_suspended;
    oal_uint32  ul_de_authentication;
    oal_uint32  ul_one_packet;
    oal_uint32  ul_abort_intr_done;
    oal_uint32  ul_ch_statistics_cnt;
    oal_uint32  ul_wow_prep_done;
    oal_uint32  ul_other_int_cnt;
    oal_uint32  aul_mac_error_cnt[OAM_MAC_ERROR_TYPE_CNT];
    oal_uint32  ul_normal_rx_idx;
    oal_uint32  ul_hi_rx_idx;
    oal_uint32  aul_rx_freq[OAM_RX_DSCR_QUEUE_CNT][OAM_IRQ_FREQ_STAT_MEMORY];
    oal_uint32  ul_rx_freq_stop_flag;
    oal_uint32  ul_max_delay;
    oal_uint32  ul_min_delay;
    oal_uint32  ul_delay_sum;
    oal_uint32  ul_timer_start;
}oam_device_stat_info_stru;

typedef struct
{
    oal_uint32  ul_rx_pkt_to_lan;
    oal_uint32  ul_rx_bytes_to_lan;
    oal_uint32  ul_rx_ppdu_dropped;
    oal_uint32  ul_rx_mpdu_total_num;
    oal_uint32  ul_rx_ta_check_dropped;
    oal_uint32  ul_rx_da_check_dropped;
    oal_uint32  ul_rx_phy_perform_dropped;
    oal_uint32  ul_rx_key_search_fail_dropped;
    oal_uint32  ul_rx_tkip_mic_fail_dropped;
    oal_uint32  ul_rx_replay_fail_dropped;
    oal_uint32  ul_rx_11i_check_fail_dropped;
    oal_uint32  ul_rx_wep_check_fail_dropped;
    oal_uint32  ul_rx_alg_process_dropped;
    oal_uint32  ul_rx_null_frame_dropped;
    oal_uint32  ul_rx_abnormal_dropped;
    oal_uint32  ul_rx_mgmt_abnormal_dropped;
    oal_uint32  ul_rx_ack_dropped;
    oal_uint32  ul_rx_pspoll_process_dropped;
    oal_uint32  ul_rx_bar_process_dropped;
    oal_uint32  ul_rx_abnormal_cnt;

    oal_uint32  ul_rx_no_buff_dropped;
    oal_uint32  ul_rx_defrag_process_dropped;
    oal_uint32  ul_rx_de_mic_fail_dropped;
    oal_uint32  ul_rx_portvalid_check_fail_dropped;
    oal_uint32  ul_rx_mcast_cnt;
    oal_uint32  aul_rx_mgmt_num[WLAN_MGMT_SUBTYPE_BUTT];
    oal_uint32  ul_tx_pkt_num_from_lan;
    oal_uint32  ul_tx_bytes_from_lan;
    oal_uint32  ul_tx_abnormal_msdu_dropped;
    oal_uint32  ul_tx_security_check_faild;
    oal_uint32  ul_tx_abnormal_mpdu_dropped;
    oal_uint32  ul_tx_uapsd_process_dropped;
    oal_uint32  ul_tx_psm_process_dropped;
    oal_uint32  ul_tx_alg_process_dropped;
    oal_uint32  ul_tx_mpdu_succ_num;
    oal_uint32  ul_tx_mpdu_fail_num;
    oal_uint32  ul_tx_ampdu_succ_num;
    oal_uint32  ul_tx_ampdu_bytes;
    oal_uint32  ul_tx_mpdu_in_ampdu;
    oal_uint32  ul_tx_ampdu_fail_num;
    oal_uint32  ul_tx_mpdu_fail_in_ampdu;
    oal_uint32  ul_tx_m2u_ucast_cnt;
    oal_uint32  ul_tx_m2u_ucast_droped;
    oal_uint32  ul_tx_m2u_mcast_cnt;
    oal_uint32  ul_tx_m2u_mcast_droped;
    oal_uint32  aul_tx_mgmt_num_sw[WLAN_MGMT_SUBTYPE_BUTT];
    oal_uint32  aul_tx_mgmt_num_hw[WLAN_MGMT_SUBTYPE_BUTT];
}oam_vap_stat_info_stru;

typedef struct
{
    oal_uint32  ul_rx_mpdu_num;
    oal_uint32  ul_rx_mpdu_bytes;
    oal_uint32  aul_tx_mpdu_succ_num[WLAN_TIDNO_BUTT];
    oal_uint32  aul_tx_mpdu_bytes[WLAN_TIDNO_BUTT];
    oal_uint32  aul_tx_mpdu_fail_num[WLAN_TIDNO_BUTT];
    oal_uint32  aul_tx_ampdu_succ_num[WLAN_TIDNO_BUTT];
    oal_uint32  aul_tx_ampdu_bytes[WLAN_TIDNO_BUTT];
    oal_uint32  aul_tx_mpdu_in_ampdu[WLAN_TIDNO_BUTT];
    oal_uint32  aul_tx_ampdu_fail_num[WLAN_TIDNO_BUTT];
    oal_uint32  aul_tx_mpdu_fail_in_ampdu[WLAN_TIDNO_BUTT];
    oal_uint32  ul_tx_ppdu_retries;
}oam_user_stat_info_stru;

typedef struct
{
    oam_device_stat_info_stru               ast_dev_stat_info[WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC];

    oam_vap_stat_info_stru                  ast_vap_stat_info[WLAN_VAP_SUPPORT_MAX_NUM_LIMIT];

    oam_user_stat_info_stru                 ast_user_stat_info[WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC * WLAN_ACTIVE_USER_MAX_NUM];
}oam_stat_info_stru;
#endif


#define OAM_SDT_STAT_INCR(_cnt)             do{g_st_sdt_stat_info._cnt++;} while(0)

enum oam_filter_type_enum
{
    OAM_FLT_PASS = 0,
    OAM_FLT_DROP,
    OAM_FLT_BUTT,
};

typedef struct
{
    oal_uint32      ul_nlk_sd_cnt;
    oal_uint32      ul_nlk_sd_fail;
    oal_uint32      ul_wq_len;
    oal_uint32      ul_filter_cnt;
    oal_bool_enum   en_filter_switch;
	oal_uint8		uc_recv[3];
}oam_sdt_stat_info_stru;
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)||defined(_PRE_PRODUCT_ID_HI110X_HOST)
extern oam_stat_info_stru g_st_stat_info;
#endif
extern oam_sdt_stat_info_stru g_st_sdt_stat_info;

typedef struct
{
    oam_cfg_type_enum_uint16            en_cfg_type;
    oal_int8                           *pc_section;
    oal_int8                           *pc_key;
    oal_int32                           l_val;
}oam_cfg_data_stru;


#ifdef _PRE_DEBUG_MODE
typedef struct
{
    oal_uint32          ul_tx_data_num;
    oal_uint32          ul_tx_mgnt_num;
    oal_uint32          ul_tx_complete_total_num;
    oal_uint32          ul_tx_complete_uh1_num;
    oal_uint32          ul_tx_complete_uh2_num;
    oal_uint32          ul_tx_complete_bh1_num;
    oal_uint32          ul_tx_complete_bh2_num;
    oal_uint32          ul_tx_complete_bh3_num;
}oam_tx_complete_stat_stru;
#endif

typedef struct
{
    oal_uint32              en_status;
    oal_uint32              ul_record_cnt;
}oam_excp_record_stru;

typedef struct
{
    oal_uint32                          en_status;
    oam_excp_record_stru                ast_excp_record_tbl[OAM_EXCP_TYPE_BUTT];
}oam_exception_ctx_stru;

typedef struct
{
    oal_switch_enum_uint8     aen_vap_log_switch[WLAN_VAP_SUPPORT_MAX_NUM_LIMIT];
    oam_log_level_enum_uint8  aen_vap_log_level[WLAN_VAP_SUPPORT_MAX_NUM_LIMIT];
    oam_log_level_enum_uint8  aen_feature_log_level[WLAN_VAP_SUPPORT_MAX_NUM_LIMIT][OAM_SOFTWARE_FEATURE_BUTT];
}oam_vap_log_stru;

#define OAM_RATELIMIT_MAX_INTERVAL                    60
#define OAM_RATELIMIT_MIN_INTERVAL                    1
#define OAM_RATELIMIT_DEFAULT_INTERVAL                5
#define OAM_RATELIMIT_MAX_BURST                       60
#define OAM_RATELIMIT_MIN_BURST                       1
#define OAM_RATELIMIT_DEFAULT_BURST                   10

typedef struct
{
    oal_switch_enum_uint8               en_global_log_switch;
    oam_vap_log_stru                    st_vap_log_info;
    oam_ratelimit_stru                  st_ratelimit[OAM_RATELIMIT_TYPE_BUTT];
}oam_log_ctx_stru;

typedef struct
{
    oal_switch_enum_uint8           en_event_switch;
    oal_uint8                       auc_resv[3];
}oam_event_ctx_stru;

typedef struct
{
    oal_switch_enum_uint8           aen_specific_event_switch[OAM_EVENT_TYPE_BUTT];
    oal_uint8                       auc_resv[1];
}oam_specific_event_ctx_stru;

typedef struct
{
#if 0
    oal_switch_enum_uint8           aen_ota_switch[OAM_OTA_TYPE_BUTT];
#endif
    oam_sdt_print_beacon_rxdscr_type_enum_uint8           en_beacon_switch;
    oal_switch_enum_uint8           en_rx_dscr_switch;
//    oal_uint8                       auc_resv[2];
}oam_ota_ctx_stru;

typedef struct
{
    oal_switch_enum_uint8           en_alarm_switch;
    oal_uint8                       auc_resv[3];
}oam_alarm_ctx_stru;

typedef struct
{
    oal_switch_enum_uint8           en_frame_content_switch;
    oal_switch_enum_uint8           en_frame_cb_switch;
    oal_switch_enum_uint8           en_frame_dscr_switch;
    oal_uint8                       auc_resv[1];
}oam_80211_frame_ctx_stru;

typedef struct
{
    oam_80211_frame_ctx_stru   ast_80211_mcast_mgmt_ctx[OAM_OTA_FRAME_DIRECTION_TYPE_BUTT];
    oam_80211_frame_ctx_stru   ast_80211_mcast_data_ctx[OAM_OTA_FRAME_DIRECTION_TYPE_BUTT];
    oam_80211_frame_ctx_stru   ast_80211_ucast_mgmt_ctx[WLAN_ACTIVE_USER_MAX_NUM * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC + WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC][OAM_OTA_FRAME_DIRECTION_TYPE_BUTT];
    oam_80211_frame_ctx_stru   ast_80211_ucast_data_ctx[WLAN_ACTIVE_USER_MAX_NUM * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC + WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC][OAM_OTA_FRAME_DIRECTION_TYPE_BUTT];
    oam_80211_frame_ctx_stru   aen_80211_probe_switch[OAM_OTA_FRAME_DIRECTION_TYPE_BUTT];
    oal_switch_enum_uint8      aen_eth_data_ctx[WLAN_ACTIVE_USER_MAX_NUM * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC + WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC][OAM_OTA_FRAME_DIRECTION_TYPE_BUTT];
    oal_switch_enum_uint8      en_tx_mcast_dhcp_arp_switch;
    oal_switch_enum_uint8      aen_data_global_switch[OAM_OTA_FRAME_DIRECTION_TYPE_BUTT];
    oal_switch_enum_uint8      aen_user_info_change_switch[WLAN_ACTIVE_USER_MAX_NUM * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC + WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC][OAM_USER_INFO_CHANGE_TYPE_BUTT];
}oam_user_track_ctx_stru;

#define OAM_FILE_PATH_LENGTH            256

typedef struct
{
    oal_uint8                       auc_resv[3];
    oam_output_type_enum_uint8      en_output_type;
    oal_int8                        ac_file_path[OAM_FILE_PATH_LENGTH];

    oam_log_ctx_stru                st_log_ctx;

    oam_event_ctx_stru              ast_event_ctx[WLAN_VAP_SUPPORT_MAX_NUM_LIMIT];

    oam_specific_event_ctx_stru     ast_specific_event_ctx[WLAN_VAP_SUPPORT_MAX_NUM_LIMIT];

    oam_ota_ctx_stru                ast_ota_ctx[WLAN_VAP_SUPPORT_MAX_NUM_LIMIT];

    oam_exception_ctx_stru          st_exception_ctx[WLAN_VAP_SUPPORT_MAX_NUM_LIMIT];

    oam_user_track_ctx_stru         st_user_track_ctx;
}oam_mng_ctx_stru;

#ifdef _PRE_WLAN_DFT_STAT

typedef struct
{
    oal_uint16          us_mac_ch_stats_period_us;
    oal_uint16          us_mac_pri20_free_time_us;
    oal_uint16          us_mac_pri40_free_time_us;
    oal_uint16          us_mac_pri80_free_time_us;
    oal_uint16          us_mac_ch_rx_time_us;
    oal_uint16          us_mac_ch_tx_time_us;

    oal_uint8           uc_phy_ch_estimate_time_ms;
    oal_int8            c_phy_pri20_idle_power_dBm;
    oal_int8            c_phy_pri40_idle_power_dBm;
    oal_int8            c_phy_pri80_idle_power_dBm;

    oal_uint32          aul_beacon_miss_max_num[WLAN_SERVICE_AP_MAX_NUM_PER_DEVICE];
    oal_uint32          ul_non_directed_frame_num;
}oam_stats_dbb_env_param_stru;

typedef struct
{
    oal_uint8           auc_node_idx[OAM_PHY_STAT_NODE_ENABLED_MAX_NUM];
}oam_stats_phy_node_idx_stru;

typedef struct
{
    oal_uint32          aul_user_requested_stat_cnt[OAM_PHY_STAT_NODE_ENABLED_MAX_NUM];
    oal_uint32          aul_phy_stat_rx_ppdu_cnt[OAM_PHY_STAT_RX_PPDU_CNT];
}oam_stats_phy_stat_stru;

typedef struct
{
    oal_uint32 ul_machw_rx_ampdu_count;
    oal_uint32 ul_machw_rx_passed_mpdu_in_ampdu_cnt;
    oal_uint32 ul_machw_rx_failed_mpdu_in_ampdu_cnt;
    oal_uint32 ul_machw_rx_octects_in_ampdu;
    oal_uint32 ul_machw_rx_delimit_fail_count;
    oal_uint32 ul_machw_rx_dup_mpdu_cnt;
    oal_uint32 ul_machw_rx_passed_mpdu_cnt;
    oal_uint32 ul_machw_rx_failed_mpdu_cnt;
    oal_uint32 ul_machw_rx_bcn_cnt;
    oal_uint32 ul_machw_rx_phy_err_mac_passed_cnt;
    oal_uint32 ul_machw_rx_phy_longer_err_cnt;
    oal_uint32 ul_machw_rx_phy_shorter_err_cnt;
    oal_uint32 ul_machw_rx_filtered_cnt;

    oal_uint32 ul_machw_tx_hi_pri_mpdu_cnt;
    oal_uint32 ul_machw_tx_normal_pri_mpdu_cnt;
    oal_uint32 ul_machw_tx_ampdu_count;
    oal_uint32 ul_machw_tx_mpdu_inampdu_count;
    oal_uint32 ul_machw_tx_octects_in_ampdu;
    oal_uint32 ul_machw_tx_bcn_count;
    oal_uint32 ul_machw_tx_normal_pri_retry_cnt;
    oal_uint32 ul_machw_tx_hi_pri_retry_cnt;
}oam_stats_machw_stat_stru;

typedef struct
{
    oal_uint32          ul_machw_stat_tx_bcn_cnt;
    oal_uint32          ul_machw_stat_tx_hi_cnt;
    oal_uint32          aul_sw_rx_mgmt_cnt[WLAN_MGMT_SUBTYPE_BUTT];
    oal_uint32          aul_sw_tx_mgmt_cnt[WLAN_MGMT_SUBTYPE_BUTT];
    oal_uint32          aul_tx_complete_mgmt_cnt[WLAN_MGMT_SUBTYPE_BUTT];
}oam_stats_mgmt_stat_stru;

typedef struct
{
    oal_uint32          aul_uapsd_stat[OAM_UAPSD_STAT_CNT];
    oal_uint32          aul_psm_stat[OAM_PSM_STAT_CNT];
    oal_uint32          aul_tid_stat[WLAN_TID_MAX_NUM][OAM_TID_STAT_CNT];
}oam_stats_usr_queue_stat_stru;

typedef struct
{
    oal_uint32          ul_lan_tx_pkts;
    oal_uint32          ul_lan_tx_bytes;
    oal_uint32          ul_drv_tx_pkts;
    oal_uint32          ul_drv_tx_bytes;
    oal_uint32          ul_hw_tx_pkts;
    oal_uint32          ul_hw_tx_bytes;

    oal_uint32          ul_drv_rx_pkts;
    oal_uint32          ul_drv_rx_bytes;
    oal_uint32          ul_lan_rx_pkts;
    oal_uint32          ul_lan_rx_bytes;
    oal_uint32          ul_app_rx_pkts;
    oal_uint32          ul_app_rx_bytes;

    oal_uint32          ul_lan_tx_rate;
    oal_uint32          ul_drv_tx_rate;
    oal_uint32          ul_hw_tx_rate;
    oal_uint32          ul_drv_rx_rate;
    oal_uint32          ul_lan_rx_rate;
}oam_stats_vap_stat_stru;
#endif

#ifdef _PRE_DEBUG_MODE
typedef struct
{
    oal_uint32          ul_ba_recipient_tid_recv_pkt;
    oal_uint32          ul_ba_recipient_no_ba_session;
    oal_uint32          ul_ba_recipient_recv_ampdu_no_ba;
    oal_uint32          ul_ba_recipient_send_delba_count;
    oal_uint32          ul_ba_recipient_dup_frame_count;
    oal_uint32          ul_ba_recipient_dup_frame_drop_count;
    oal_uint32          ul_ba_recipient_dup_frame_up_count;
    oal_uint32          ul_ba_recipient_direct_up_count;
    oal_uint32          ul_ba_recipient_buffer_frame_count;
    oal_uint32          ul_ba_recipient_buffer_frame_overlap_count;
    oal_uint32          ul_ba_recipient_between_baw_count;
    oal_uint32          ul_ba_recipient_greater_baw_count;
    oal_uint32          ul_ba_recipient_sync_loss_count;
    oal_uint32          ul_ba_recipient_update_hw_baw_count;

}oam_stats_ampdu_stat_stru;
#endif

extern oam_mng_ctx_stru             g_st_oam_mng_ctx;

extern oal_uint32 oam_send_device_data2sdt(oal_uint8* pc_string, oal_uint16 len);
extern oal_int32  oam_main_init(oal_void);
extern oal_void  oam_main_exit(oal_void);
extern oal_uint32  oam_print(oal_int8 *pc_string);
extern oal_uint32  oam_set_file_path(oal_int8 *pc_file_path, oal_uint32 ul_length);
extern oal_uint32  oam_set_output_type(oam_output_type_enum_uint8 en_output_type);
extern oal_uint32  oam_get_output_type(oam_output_type_enum_uint8 *pen_output_type);

extern oal_void oam_exception_stat_handler(oam_msg_moduleid_enum_uint8 en_moduleid, oal_uint8 uc_vap_idx);

extern oal_uint32 oam_log_set_global_switch(oal_switch_enum_uint8 en_log_switch);
extern oal_uint32 oam_log_set_vap_switch(oal_uint8 uc_vap_id,
                                         oal_switch_enum_uint8    en_log_switch);

extern oal_uint32 oam_log_set_ratelimit_param(
                oam_ratelimit_type_enum_uint8  en_ratelimit_type,
                oam_ratelimit_stru *pst_printk_ratelimit);

extern oal_uint32 oam_log_set_feature_level(oal_uint8 uc_vap_id,
                                           oam_feature_enum_uint8   en_feature_id,
                                           oam_log_level_enum_uint8 en_log_level);
extern oal_uint32 oam_get_feature_id(oal_uint8 *puc_feature_name,
                                              oam_feature_enum_uint8 *puc_feature_id);
extern oal_uint32 oam_show_feature_list(oal_void);
extern oal_uint32 oam_log_set_vap_level(oal_uint8 uc_vap_id, oam_log_level_enum_uint8 en_log_level);

extern oal_uint32 oam_log_get_vap_level(oal_uint8 uc_vap_id, oam_log_level_enum_uint8 *pen_log_level);

/*extern  oal_int32 OAL_PRINT_NLOGS(
        const oal_int8* pfunc_local_name,
        oal_uint16      us_file_no,
        oal_uint16      us_line_no,
        void*           pfunc_addr,
        oal_uint8       uc_vap_id,
        oal_uint8       en_feature_id,
        oal_uint8       clog_level,
        oal_int8*       fmt,
        oal_uint p1, oal_uint p2, oal_uint p3, oal_uint p4);*/

extern oal_uint32  oam_log_print0( oal_uint32  ul_para,
                                       oal_uint16  us_line_num,
                                       oal_int8    *pc_string);

extern oal_uint32  oam_log_print1( oal_uint32  ul_para,
                                       oal_uint16  us_line_num,
                                       oal_int8    *pc_string,
                                       oal_uint    l_param1);

extern oal_uint32  oam_log_print2( oal_uint32  ul_para,
                                       oal_uint16  us_line_num,
                                       oal_int8    *pc_string,
                                       oal_uint    l_param1,
                                       oal_uint    l_param2);

extern oal_uint32  oam_log_print3( oal_uint32  ul_para,
                                       oal_uint16  us_line_num,
                                       oal_int8    *pc_string,
                                       oal_uint    l_param1,
                                       oal_uint    l_param2,
                                       oal_uint    l_param3);

extern oal_uint32  oam_log_print4( oal_uint32  ul_para,
                                       oal_uint16  us_line_num,
                                       oal_int8    *pc_string,
                                       oal_uint    l_param1,
                                       oal_uint    l_param2,
                                       oal_uint    l_param3,
                                       oal_uint    l_param4);

extern oal_uint32  oam_log_console_printk(
                oal_uint16                       us_file_no,
                oal_uint16                       us_line_num,
                const oal_int8                  *pc_func_name,
                const oal_int8                  *pc_fmt,
                ...);

extern oal_uint32 oam_exception_record(oal_uint8 uc_vap_id, oam_excp_type_enum_uint8 en_excp_id);

extern oal_uint32  oam_event_set_switch(
                       oal_uint8               uc_vap_id,
                       oal_switch_enum_uint8   en_switch_type);
extern oal_uint32  oam_event_get_switch(
                       oal_uint8              uc_vap_id,
                       oal_switch_enum_uint8 *pen_switch_type);
extern oal_uint32  oam_event_report(
                                    oal_uint8                  *puc_user_macaddr,
                                    oal_uint8                   uc_vap_id,
                                    oam_module_id_enum_uint16   en_mod,
                                    oam_event_type_enum_uint16  en_event_type,
                                    oal_uint8                  *puc_string);
extern oal_uint32  oam_ota_report(oal_uint8   *puc_param_one_addr,
                               oal_uint16   us_param_one_len,
                               oal_uint8   *puc_param_two_addr,
                               oal_uint16   us_param_two_len,
                               oam_ota_type_enum_uint8  en_ota_type);
#if 0
extern oal_uint32  oam_ota_set_switch(
                            oal_uint8                   uc_vap_id,
                            oal_switch_enum_uint8       en_switch_type,
                            oam_ota_type_enum_uint8     en_ota_type);
#endif
extern oal_uint32  oam_ota_set_beacon_switch(
                            oal_uint8                   uc_vap_id,
                            oam_sdt_print_beacon_rxdscr_type_enum_uint8 en_switch_type);
extern oal_switch_enum_uint8  oam_ota_get_beacon_switch(oal_void);
extern oal_uint32  oam_ota_set_rx_dscr_switch(
                            oal_uint8                   uc_vap_id,
                            oam_sdt_print_beacon_rxdscr_type_enum_uint8 en_switch_type);
extern oal_switch_enum_uint8  oam_ota_get_rx_dscr_switch(oal_void);


extern oal_uint32  oam_report_eth_frame(oal_uint8               *puc_user_mac_addr,
                                       oal_uint8               *puc_eth_frame_hdr_addr,
                                       oal_uint16               us_eth_frame_len,
                                       oam_ota_frame_direction_type_enum_uint8 en_eth_frame_direction);
extern oal_uint32 oam_report_dscr(oal_uint8  *puc_user_macaddr,
                               oal_uint8  *puc_dscr_addr,
                               oal_uint16  us_dscr_len,
                               oam_ota_type_enum_uint8  en_ota_type);
extern oal_uint32  oam_report_beacon(
                                    oal_uint8     *puc_beacon_hdr_addr,
                                    oal_uint8      uc_beacon_hdr_len,
                                    oal_uint8     *puc_beacon_body_addr,
                                    oal_uint16     us_beacon_len,
                                    oam_ota_frame_direction_type_enum_uint8 en_beacon_direction);
extern oal_uint32  oam_report_80211_frame(
                        oal_uint8     *puc_user_macaddr,
                        oal_uint8     *puc_mac_hdr_addr,
                        oal_uint8      uc_mac_hdr_len,
                        oal_uint8     *puc_mac_body_addr,
                        oal_uint16     us_mac_frame_len,
                        oam_ota_frame_direction_type_enum_uint8  en_frame_direction);
#if 0
extern oal_switch_enum_uint8 oam_report_get_switch(oam_ota_type_enum_uint8 en_type);
#endif
extern oal_uint32  oam_report_80211_mcast_get_switch(
                                        oam_ota_frame_direction_type_enum_uint8 en_mcast_direction,
                                        oam_user_track_frame_type_enum_uint8    en_frame_type,
                                        oal_switch_enum_uint8                  *pen_frame_switch,
                                        oal_switch_enum_uint8                  *pen_cb_switch,
                                        oal_switch_enum_uint8                  *pen_dscr_switch);
extern oal_uint32  oam_report_80211_ucast_get_switch(
                                        oam_ota_frame_direction_type_enum_uint8 en_ucast_direction,
                                        oam_user_track_frame_type_enum_uint8    en_frame_type,
                                        oal_switch_enum_uint8                  *pen_frame_switch,
                                        oal_switch_enum_uint8                  *pen_cb_switch,
                                        oal_switch_enum_uint8                  *pen_dscr_switch,
                                        oal_uint16                              us_user_idx);
extern oal_uint32  oam_report_80211_probe_get_switch(
                                        oam_ota_frame_direction_type_enum_uint8 en_probereq_direction,
                                        oal_switch_enum_uint8                  *pen_frame_switch,
                                        oal_switch_enum_uint8                  *pen_cb_switch,
                                        oal_switch_enum_uint8                  *pen_dscr_switch);
extern oal_uint32  oam_report_80211_probe_set_switch(
                                        oam_ota_frame_direction_type_enum_uint8 en_probe_direction,
                                        oal_switch_enum_uint8                   en_frame_switch,
                                        oal_switch_enum_uint8                   en_cb_switch,
                                        oal_switch_enum_uint8                   en_dscr_switch);
extern oal_uint32  oam_report_eth_frame_get_switch(
                                 oal_uint16             us_user_idx,
                                 oam_ota_frame_direction_type_enum_uint8 en_eth_direction,
                                 oal_switch_enum_uint8  *pen_eth_switch);
extern oal_uint32  oam_report_netbuf_cb(oal_uint8  *puc_user_mac_addr,
                                       oal_uint8  *puc_netbuf_cb,
                                       oam_ota_type_enum_uint8 en_ota_type);
#if 0
extern oal_uint32  oam_report_timer_track(oal_uint32 ul_file_id,
                                        oal_uint32 ul_line_num,
                                        oam_timer_track_type_enum_uint8 en_type);
#endif
extern oal_uint32  oam_report_mpdu_num(oal_uint8  *puc_user_mac_addr,
                                        oam_report_mpdu_num_stru *pst_mpdu_num);
extern oal_uint32  oam_report_dft_params(oal_uint8  *puc_user_mac_addr,
                                        oal_uint8  *puc_param,
                                        oal_uint16      us_param_len,
                                        oam_ota_type_enum_uint8 en_type);
extern oal_uint32  oam_report_set_all_switch(oal_switch_enum_uint8 en_switch);
extern oal_uint32  oam_report_80211_ucast_set_switch(
                                        oam_ota_frame_direction_type_enum_uint8 en_ucast_direction,
                                        oam_user_track_frame_type_enum_uint8    en_frame_type,
                                        oal_switch_enum_uint8                   en_frame_switch,
                                        oal_switch_enum_uint8                   en_cb_switch,
                                        oal_switch_enum_uint8                   en_dscr_switch,
                                        oal_uint16                              us_user_idx);
extern oal_uint32 oam_report_eth_frame_set_switch(oal_uint16               us_user_idx,
                                                   oal_switch_enum_uint8    en_switch,
                                       oam_ota_frame_direction_type_enum_uint8 en_eth_direction);
extern oal_uint32  oam_report_80211_mcast_set_switch(
                                        oam_ota_frame_direction_type_enum_uint8 en_mcast_direction,
                                        oam_user_track_frame_type_enum_uint8    en_frame_type,
                                        oal_switch_enum_uint8                   en_frame_switch,
                                        oal_switch_enum_uint8                   en_cb_switch,
                                        oal_switch_enum_uint8                   en_dscr_switch);
extern oal_uint32  oam_report_dhcp_arp_set_switch(oal_switch_enum_uint8 en_switch);
extern oal_switch_enum_uint8  oam_report_dhcp_arp_get_switch(oal_void);
extern oal_switch_enum_uint8  oam_report_data_get_global_switch(oam_ota_frame_direction_type_enum_uint8 en_direction);

extern oal_uint32  oam_alarm_set_switch(
                       oal_uint8              uc_vap_id,
                       oal_switch_enum_uint8  en_switch_type);
extern oal_uint32  oam_alarm_get_switch(
                       oal_uint8              uc_vap_id,
                       oal_switch_enum_uint8 *pen_switch_type);
extern oal_uint32  oam_alarm_report(
                       oal_uint8                   uc_vap_id,
                       oal_uint16                  us_file_no,
                       oal_uint32                  ul_file_line_no,
                       oam_module_id_enum_uint16   en_mod,
                       oam_alarm_type_enum_uint16  en_alarm_type);

extern oal_void    oam_sdt_func_fook_register(oam_sdt_func_hook_stru *pfun_st_oam_sdt_hook);
extern oal_void    oam_sdt_func_fook_unregister(oal_void);
extern oal_void    oam_wal_func_fook_register(oam_wal_func_hook_stru *pfun_st_oam_wal_hook);
extern oal_void    oam_wal_func_fook_unregister(oal_void);

extern oal_uint32  oam_event_set_specific_type_switch(
                                oal_uint8                   uc_vap_id,
                                oal_switch_enum_uint8       en_switch_type,
                                oam_event_type_enum_uint16  en_event_type);

extern oal_uint32 oam_report_data2sdt(oal_netbuf_stru *pst_netbuf,
                                       oam_data_type_enum_uint8 en_type,
                                       oam_primid_type_enum_uint8 en_prim);
extern oal_netbuf_stru *oam_alloc_data2sdt(oal_uint16  us_data_len);

#ifdef _PRE_PROFILING_MODE
extern oal_void oam_profiling_rx_save_data(oam_profiling_rx_func_enum_uint8 en_func_index);
extern oal_void oam_profiling_tx_save_data(oal_void *pst_netbuf,oam_profiling_tx_func_enum_uint8 en_func_index);
extern oal_void oam_profiling_alg_save_data(oam_profiling_alg_func_enum_uint8 en_func_index);

#endif

extern oal_uint32  oam_stats_report_timer_info_to_sdt(
                                    oal_uint8 *puc_timer_addr,
                                    oal_uint8  uc_timer_len);
extern oal_uint32  oam_stats_report_event_queue_info_to_sdt(
                                    oal_uint8   *puc_event_queue_addr,
                                    oal_uint16    us_event_queue_info_len);
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)||defined(_PRE_PRODUCT_ID_HI110X_HOST)

extern oal_uint32 oam_stats_report_info_to_sdt(oam_ota_type_enum_uint8 en_ota_type);
extern oal_uint32  oam_report_vap_pkt_stat_to_sdt(oal_uint8 uc_vap_id);
extern oal_void  oam_stats_clear_stat_info(oal_void);
extern oal_uint32  oam_stats_report_usr_info(oal_uint16  us_usr_id);
extern oal_uint32  oam_stats_clear_user_stat_info(oal_uint16   us_usr_id);

extern oal_uint32  oam_stats_clear_vap_stat_info(oal_uint8   uc_vap_id);
#endif


extern oal_uint32  oam_stats_report_mempool_info_to_sdt(
                                        oal_uint8           uc_pool_id,
                                        oal_uint16          us_pool_total_cnt,
                                        oal_uint16          us_pool_used_cnt,
                                        oal_uint8           uc_subpool_id,
                                        oal_uint16          us_subpool_total_cnt,
                                        oal_uint16          us_subpool_free_cnt);
extern oal_uint32  oam_stats_report_memblock_info_to_sdt(oal_uint8  *puc_origin_data,
                                             oal_uint8   uc_user_cnt,
                                             oal_uint8   uc_pool_id,
                                             oal_uint8   uc_subpool_id,
                                             oal_uint16  us_len,
                                             oal_uint32  ul_file_id,
                                             oal_uint32  ul_alloc_line_num);
extern oal_void  oam_stats_report_irq_info_to_sdt(
                                    oal_uint8 *puc_irq_info_addr,
                                    oal_uint16  us_irq_info_len);

extern oal_int32  oam_cfg_get_item_by_id(oam_cfg_type_enum_uint16  en_cfg_type);

extern oal_void    oam_profiling_switch_test_process(oal_uint8  uc_config_type, oal_uint8 uc_config_value);
extern oal_uint32  oam_profiling_compute_time_offset(
                       oal_time_us_stru    st_time_first,
                       oal_time_us_stru    st_time_second,
                       oal_time_us_stru   *pst_time_offset);
extern oal_uint32  oam_profiling_init(oal_void);
extern oal_uint32  oam_profiling_set_switch(oam_profiling_enum_uint8 en_profiling_type, oam_profiling_swith_enum_uint8 en_profiling_switch);

extern oal_void    oam_profiling_rx_save_data(oam_profiling_rx_func_enum_uint8 en_func_index);
extern oal_uint32  oam_profiling_rx_show_offset(oal_void);

extern oal_void    oam_profiling_tx_save_data(
                       oal_void                    *pst_netbuf,
                       oam_profiling_tx_func_enum_uint8    en_func_index);
extern oal_uint32  oam_profiling_tx_show_offset(oal_void);

extern oal_void    oam_profiling_alg_save_data(oam_profiling_alg_func_enum_uint8    en_func_index);
extern oal_uint32  oam_profiling_alg_show_offset(oal_void);

extern oal_void  oam_profiling_starttime_save_timestamp(oam_profiling_starttime_func_enum_uint8 en_func_idx);
extern oal_void  oam_profiling_starttime_show_offset(oal_void);
extern oal_void  oam_profiling_chswitch_save_timestamp(oam_profiling_chswitch_func_enum_uint8 en_func_idx);
extern oal_void  oam_profiling_chswitch_show_offset(oal_void);
extern oal_void oam_print_record_time(oal_void);
extern oal_void oam_record_time(oal_uint32 ul_idx);
//#endif

#ifdef _PRE_DEBUG_MODE
extern oam_tx_complete_stat_stru   g_ast_tx_complete_stat[WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC];
#endif
extern oal_void  oam_netlink_ops_register(oam_nl_cmd_enum_uint8 en_type, oal_uint32 (*p_func)(oal_uint8 *puc_data, oal_uint32 ul_len));
extern oal_void  oam_netlink_ops_unregister(oam_nl_cmd_enum_uint8 en_type);
extern oal_int32  oam_netlink_kernel_send(oal_uint8 *puc_data, oal_uint32 ul_data_len, oam_nl_cmd_enum_uint8 en_type);
extern oal_int32  oam_netlink_kernel_send_ex(oal_uint8 *puc_data_1st, oal_uint8 *puc_data_2nd,
                                             oal_uint32 ul_len_1st, oal_uint32 ul_len_2nd,
                                             oam_nl_cmd_enum_uint8 en_type);

OAL_STATIC OAL_INLINE  oal_switch_enum_uint8 oam_get_log_switch(oal_uint32  ul_para)
{
    oal_uint8                   uc_vap_id       = (ul_para>>24)&0xf;
    oam_feature_enum_uint8      en_feature_id   = (ul_para>>16)&0xff;
    oam_log_level_enum_uint8    en_log_level    = (ul_para>>28)&0xf;

    if (OAL_SWITCH_OFF == g_st_oam_mng_ctx.st_log_ctx.en_global_log_switch)
    {
        return OAL_SWITCH_OFF;
    }
    else if (OAL_SWITCH_OFF == g_st_oam_mng_ctx.st_log_ctx.st_vap_log_info.aen_vap_log_switch[uc_vap_id])
    {
        return OAL_SWITCH_OFF;
    }
	else if (en_log_level > g_st_oam_mng_ctx.st_log_ctx.st_vap_log_info.aen_vap_log_level[uc_vap_id])
    {
	    return OAL_SWITCH_OFF;
    }
    else if (en_log_level > g_st_oam_mng_ctx.st_log_ctx.st_vap_log_info.aen_feature_log_level[uc_vap_id][en_feature_id])
    {
        return OAL_SWITCH_OFF;
    }

    return OAL_SWITCH_ON;
}

OAL_STATIC OAL_INLINE oal_uint32  oam_event_chan_report(oal_uint8 uc_channel_num)
{
    oal_uint8               auc_event[4];

    auc_event[0] = uc_channel_num;

    return oam_event_report(BROADCAST_MACADDR, 0, OAM_MODULE_ID_HAL, OAM_EVENT_VAP_CHANGE_CHANNEL, auc_event);
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oam_ext_if.h */
