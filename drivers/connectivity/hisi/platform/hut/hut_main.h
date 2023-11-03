#ifndef __HUT_MAIN_H__
#define __HUT_MAIN_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "oal_ext_if.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HUT_MAIN_H

#define HUT_ERR_LOG(_uc_vap_id, _puc_string)
#define HUT_ERR_LOG1(_uc_vap_id, _puc_string, _l_para1)
#define HUT_ERR_LOG2(_uc_vap_id, _puc_string, _l_para1, _l_para2)
#define HUT_ERR_LOG3(_uc_vap_id, _puc_string, _l_para1, _l_para2, _l_para3)
#define HUT_ERR_LOG4(_uc_vap_id, _puc_string, _l_para1, _l_para2, _l_para3, _l_para4)
#define HUT_ERR_VAR(_uc_vap_id, _c_fmt, ...)

#define HUT_WARNING_LOG(_uc_vap_id, _puc_string)
#define HUT_WARNING_LOG1(_uc_vap_id, _puc_string, _l_para1)
#define HUT_WARNING_LOG2(_uc_vap_id, _puc_string, _l_para1, _l_para2)
#define HUT_WARNING_LOG3(_uc_vap_id, _puc_string, _l_para1, _l_para2, _l_para3)
#define HUT_WARNING_LOG4(_uc_vap_id, _puc_string, _l_para1, _l_para2, _l_para3, _l_para4)
#define HUT_WARNING_VAR(_uc_vap_id, _c_fmt, ...)

#define HUT_INFO_LOG(_uc_vap_id, _puc_string)
#define HUT_INFO_LOG1(_uc_vap_id, _puc_string, _l_para1)
#define HUT_INFO_LOG2(_uc_vap_id, _puc_string, _l_para1, _l_para2)
#define HUT_INFO_LOG3(_uc_vap_id, _puc_string, _l_para1, _l_para2, _l_para3)
#define HUT_INFO_LOG4(_uc_vap_id, _puc_string, _l_para1, _l_para2, _l_para3, _l_para4)
#define HUT_INFO_VAR(_uc_vap_id, _c_fmt, ...)

typedef struct
{
    oal_uint8 *puc_base_addr_origin;
    oal_uint8 *puc_base_addr_align;
}hut_mem_addr_stru;

typedef struct
{
    oal_uint8    bit_flag : 1,
                 bit_last : 1,
                 bit_resv : 6;
    oal_uint8    uc_num;
    oal_uint16   us_len;
}hut_frag_hdr_stru;

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of hut_main.h */
