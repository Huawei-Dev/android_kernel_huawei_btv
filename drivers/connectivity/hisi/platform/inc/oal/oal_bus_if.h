#ifndef __OAL_BUS_IF_H__
#define __OAL_BUS_IF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "oal_mem.h"
#include "oal_schedule.h"
#include "oal_util.h"
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
#include "oal_pci_if.h"
#endif

#define OAL_MAX_BAR_NUM          6

typedef struct
{
    oal_uint32       ul_device_id;
    oal_void        *p_dev;
    oal_uint32       ul_irq_num;
    oal_uint8        uc_chip_id;
    oal_uint8        uc_bar_num;
    oal_uint8        auc_resv[2];
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    oal_uint32       aul_mem_start[OAL_WITP_MAX_BARS];
#else
    oal_uint32       aul_mem_start[1];
#endif
    oal_irq_dev_stru st_irq_info;
}oal_bus_dev_stru;

typedef struct
{
    oal_uint8           uc_chip_id;
    oal_uint8        uc_device_num;
    oal_uint8        auc_resv[2];
	oal_pci_dev_stru   *pst_pci_device;
    oal_void           *p_pci_dbi_base;
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    oal_uint32       aul_mem_start[OAL_WITP_MAX_BARS];
#else
    oal_uint32       aul_mem_start[1];
#endif
    oal_bus_dev_stru st_bus_dev[WLAN_DEVICE_MAX_NUM_PER_CHIP];
}oal_bus_chip_stru;

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
extern oal_uint32  oal_bus_exit(oal_bus_dev_stru *pst_bus_dev);
extern oal_void  oal_bus_find_dev_instance(oal_bus_dev_stru **ppst_bus_dev, oal_void *p_dev);
extern oal_uint32  oal_bus_send(oal_bus_dev_stru *pst_bus, oal_mem_stru *pst_msg_input);
extern oal_uint32  oal_bus_register_irq(oal_void *pst, oal_irq_intr_func p_func, oal_uint8 uc_chip_id, oal_uint8 uc_device_id);
extern oal_void oal_bus_unregister_irq(oal_uint8 uc_chip_id, oal_uint8 uc_device_id);
extern oal_void  oal_bus_get_chip_instance(oal_bus_chip_stru **ppst_bus_chip, oal_uint8 uc_index);
#ifdef _PRE_WLAN_FEATURE_SMP_SUPPORT
extern oal_void oal_bus_irq_affinity_init(oal_uint8 uc_chip_id, oal_uint8 uc_device_id, oal_uint32 ul_core_id);
#endif
#endif

extern oal_uint8  oal_bus_get_chip_num(oal_void);
extern oal_uint32  oal_bus_inc_chip_num(oal_void);
extern oal_void oal_bus_init_chip_num(oal_void);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_bus_if.h */
