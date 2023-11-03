#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "frw_main.h"
#include "frw_event_deploy.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_FRW_EVENT_DEPLOY_C

OAL_STATIC frw_ipc_node_stru         g_st_ipc_node[FRW_IPC_CORE_TYPE_BUTT];

OAL_STATIC frw_ipc_msg_queue_stru    g_st_queue_master_to_slave;

OAL_STATIC frw_ipc_msg_queue_stru    g_st_queue_slave_to_master;

OAL_STATIC oal_uint32  frw_ipc_init(oal_void);
OAL_STATIC oal_uint32  frw_ipc_init_master(frw_ipc_node_stru *pst_ipc_node);
OAL_STATIC oal_uint32  frw_ipc_init_slave(frw_ipc_node_stru *pst_ipc_node);
OAL_STATIC oal_uint32  frw_ipc_exit(oal_void);
OAL_STATIC oal_void  frw_ipc_recv(frw_ipc_msg_mem_stru *pst_ipc_mem_msg);
OAL_STATIC oal_uint32  frw_ipc_send(frw_ipc_msg_mem_stru *pst_ipc_mem_msg);
OAL_STATIC oal_uint32  frw_ipc_send_connect_request(oal_void);
OAL_STATIC oal_uint32  frw_ipc_send_connect_response(oal_void);
OAL_STATIC oal_uint32  frw_ipc_send_inter_msg(oal_uint8 uc_msg_type, oal_uint8 *puc_data, oal_uint8 us_len);
OAL_STATIC oal_void  frw_ipc_tx_complete(frw_ipc_msg_mem_stru *pst_msg);
OAL_STATIC oal_uint32  frw_ipc_event_queue_full(oal_void);
OAL_STATIC oal_uint32  frw_ipc_event_queue_empty(oal_void);

OAL_STATIC oal_uint32  frw_event_deploy_pipeline(oal_mem_stru *pst_mem_event, frw_event_deploy_enum_uint8 *en_deploy_result);

OAL_STATIC oal_void  frw_ipc_recv(frw_ipc_msg_mem_stru *pst_ipc_mem_msg)
{
    frw_ipc_msg_header_stru     *pst_header;
    frw_ipc_core_type_enum_uint8 en_type;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_ipc_mem_msg))
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_ipc_recv::OAL_PTR_NULL == pst_ipc_mem_msg}\r\n");
        return;
    }

    pst_header = (frw_ipc_msg_header_stru *)(pst_ipc_mem_msg->puc_data);

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_header
        || pst_header->uc_target_cpuid > FRW_IPC_CORE_NUM_BUTT
        || pst_header->uc_msg_type > FRW_IPC_MSG_TYPE_BUTT))
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{pst_header is incorrect.}");
        return;
    }

    en_type = frw_ipc_get_core_type();

    if (OAL_LIKELY(g_st_ipc_node[en_type].us_seq_num_rx_expect == pst_header->us_seq_number))
    {
        g_st_ipc_node[en_type].us_seq_num_rx_expect++;
    }
    else if(g_st_ipc_node[en_type].us_seq_num_rx_expect < pst_header->us_seq_number)
    {
        g_st_ipc_node[en_type].us_seq_num_rx_expect = pst_header->us_seq_number + 1;

    #ifdef _PRE_DEBUG_MODE
        frw_ipc_log_recv_alarm(&g_st_ipc_node[en_type].st_log,
                               (pst_header->us_seq_number - g_st_ipc_node[en_type].us_seq_num_rx_expect));
    #endif
    }
    else
    {
        g_st_ipc_node[en_type].us_seq_num_rx_expect = pst_header->us_seq_number + 1;
    #ifdef _PRE_DEBUG_MODE
        frw_ipc_log_recv_alarm(&g_st_ipc_node[en_type].st_log,
                               (pst_header->us_seq_number + FRW_IPC_MAX_SEQ_NUMBER - g_st_ipc_node[en_type].us_seq_num_rx_expect + 1));
    #endif
    }

#ifdef _PRE_DEBUG_MODE
    frw_ipc_log_recv(&g_st_ipc_node[en_type].st_log,
                     pst_header->us_seq_number,
                     pst_header->uc_target_cpuid,
                     pst_header->uc_msg_type);
#endif

    switch (pst_header->uc_msg_type)
    {
        case FRW_IPC_MSG_TYPE_EVENT:
            pst_ipc_mem_msg->puc_data += FRW_IPC_MSG_HEADER_LENGTH;
            frw_event_post_event(pst_ipc_mem_msg,OAL_GET_CORE_ID());

            break;

        case FRW_IPC_MSG_TYPE_TX_INT_ENABLE:
            g_st_ipc_node[en_type].en_tx_int_ctl = FRW_IPC_TX_CTRL_ENABLED;

            break;

        case FRW_IPC_MSG_TYPE_TX_INT_DISENABLE:
            g_st_ipc_node[en_type].en_tx_int_ctl = FRW_IPC_TX_CTRL_DISABLED;

            break;

        case FRW_IPC_MSG_TYPE_CONNECT_REQUEST:
            frw_ipc_send_connect_response();

            break;

        case FRW_IPC_MSG_TYPE_CONNECT_RESPONSE:
            g_st_ipc_node[en_type].en_states = FRW_IPC_CORE_STATE_CONNECTED;

            break;

        case FRW_IPC_MSG_TYPE_CONFIG_REQUEST:
        case FRW_IPC_MSG_TYPE_CONFIG_RESPONSE:
        case FRW_IPC_MSG_TYPE_ERROR_NOTICE:
        case FRW_IPC_MSG_TYPE_RESET_REQUEST:
        case FRW_IPC_MSG_TYPE_RESET_RESPONSE:
        case FRW_IPC_MSG_TYPE_OPEN_OAM:
        case FRW_IPC_MSG_TYPE_CLOSE_OAM:
        case FRW_IPC_MSG_TYPE_EXIT_REQUEST:
        case FRW_IPC_MSG_TYPE_EXIT_RESPONSE:
        default:

            break;
    }

    FRW_EVENT_FREE(pst_ipc_mem_msg);
}

OAL_STATIC oal_uint32  frw_ipc_send(frw_ipc_msg_mem_stru *pst_ipc_mem_msg)
{
    oal_uint32                   ul_ret;
    frw_ipc_msg_header_stru     *pst_header;
    frw_ipc_msg_queue_stru      *pst_msg_queue;
    frw_ipc_core_type_enum_uint8 en_type;

    en_type = frw_ipc_get_core_type();
    FRW_IPC_GET_MSG_QUEUE(pst_msg_queue, en_type);

    if (FRW_IPC_CORE_STATE_CONNECTED != g_st_ipc_node[en_type].en_states)
    {
        OAM_WARNING_LOG2(0, OAM_SF_FRW, "{frw_ipc_send::FRW_IPC_CORE_STATE_CONNECTED != g_st_ipc_node[en_type].en_states. en_type:%d, en_states:%d}\r\n", en_type, g_st_ipc_node[en_type].en_states);
        return OAL_FAIL;
    }

    pst_header = (frw_ipc_msg_header_stru *)frw_ipc_get_header(pst_ipc_mem_msg);

    pst_header->us_seq_number   = g_st_ipc_node[en_type].us_seq_num_tx_expect;
    pst_header->uc_target_cpuid = g_st_ipc_node[en_type].en_target_cpuid;
    pst_header->uc_msg_type     = FRW_IPC_MSG_TYPE_EVENT;

    ul_ret = frw_ipc_msg_queue_send(pst_msg_queue,
                                    pst_ipc_mem_msg,
                                    g_st_ipc_node[en_type].en_tx_int_ctl,
                                    g_st_ipc_node[en_type].en_target_cpuid);

    if (OAL_UNLIKELY(OAL_ERR_CODE_IPC_QUEUE_FULL == ul_ret))
    {
    #ifdef _PRE_DEBUG_MODE
        frw_ipc_log_send_alarm(&g_st_ipc_node[en_type].st_log);
    #endif
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_send::frw_ipc_msg_queue_send return err code: %d}", OAL_ERR_CODE_IPC_QUEUE_FULL);
        return ul_ret;
    }

    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_send::frw_ipc_msg_queue_send return err code:%d}", ul_ret);
        return ul_ret;
    }

    g_st_ipc_node[en_type].us_seq_num_tx_expect++;

    pst_ipc_mem_msg->uc_user_cnt++;

#ifdef _PRE_DEBUG_MODE
    frw_ipc_log_send(&g_st_ipc_node[en_type].st_log,
                     pst_header->us_seq_number,
                     pst_header->uc_target_cpuid,
                     pst_header->uc_msg_type);
#endif

    return OAL_SUCC;
}

OAL_STATIC oal_void  frw_ipc_tx_complete(frw_ipc_msg_mem_stru *pst_msg)
{
    /* TBD */
}

OAL_STATIC oal_uint32  frw_ipc_init(oal_void)
{
    oal_uint32   ul_ret;

    if(FRW_IPC_CORE_TYPE_MASTER == frw_ipc_get_core_type())
    {
        ul_ret = frw_ipc_init_master(&g_st_ipc_node[FRW_IPC_CORE_TYPE_MASTER]);
    }
    else
    {
        ul_ret = frw_ipc_init_slave(&g_st_ipc_node[FRW_IPC_CORE_TYPE_SLAVE]);
    }

    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG0(0, OAM_SF_FRW, "{frw ipc init fail.}");
        return ul_ret;
    }

    ul_ret = frw_ipc_send_connect_request();
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG0(0, OAM_SF_FRW, "{frw ipc connect fail.}");
        return ul_ret;
    }

    frw_event_ipc_event_queue_full_register(frw_ipc_event_queue_full);
    frw_event_ipc_event_queue_empty_register(frw_ipc_event_queue_empty);

    return OAL_SUCC;
}

OAL_STATIC oal_uint32  frw_ipc_init_master(frw_ipc_node_stru *pst_ipc_node)
{
    oal_uint32 ul_ret;

    pst_ipc_node->en_cpuid             = FRW_IPC_CORE_ID_MASTER;
    pst_ipc_node->en_target_cpuid      = FRW_IPC_CORE_ID_SLAVE;
    pst_ipc_node->en_cpu_type          = FRW_IPC_CORE_TYPE_MASTER;
    pst_ipc_node->us_seq_num_rx_expect = 0;
    pst_ipc_node->us_seq_num_tx_expect = 0;
    pst_ipc_node->en_states            = FRW_IPC_CORE_STATE_INIT;
    pst_ipc_node->en_tx_int_ctl        = FRW_IPC_TX_CTRL_ENABLED;

    ul_ret = frw_ipc_msg_queue_init(&g_st_queue_master_to_slave,
                                    FRW_IPC_MASTER_TO_SLAVE_QUEUE_MAX_NUM);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_init_master: frw_ipc_msg_queue_init g_st_queue_master_to_slave return err code:%d}", ul_ret);
        return ul_ret;
    }

    ul_ret = frw_ipc_msg_queue_init(&g_st_queue_slave_to_master,
                                    FRW_IPC_SLAVE_TO_MASTER_QUEUE_MAX_NUM);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW,  "{frw_ipc_init_master:: frw_ipc_msg_queue_init g_st_queue_slave_to_master return err code:%d}", ul_ret);
        return ul_ret;
    }

    pst_ipc_node->st_irq_dev.p_irq_intr_func    = frw_ipc_msg_queue_recv;
    pst_ipc_node->st_irq_dev.ul_irq             = OAL_IRQ_NUM;
    pst_ipc_node->st_irq_dev.l_irq_type         = OAL_SA_SHIRQ;
    pst_ipc_node->st_irq_dev.pc_name            = "ipc";
    pst_ipc_node->st_irq_dev.p_drv_arg          = (void *)&g_st_queue_slave_to_master;

    if (OAL_UNLIKELY(0 != oal_irq_setup(&pst_ipc_node->st_irq_dev)))
    {
        OAM_WARNING_LOG0(0, OAM_SF_FRW, "{frw_ipc_msg_queue_setup_irq:: oal_irq_setup fail!}");
        return OAL_FAIL;
    }

    pst_ipc_node->st_ipc_msg_callback.p_rx_complete_func = frw_ipc_recv;
    pst_ipc_node->st_ipc_msg_callback.p_tx_complete_func = frw_ipc_tx_complete;
    ul_ret = frw_ipc_msg_queue_register_callback(&pst_ipc_node->st_ipc_msg_callback);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_init_master: frw_ipc_msg_queue_register_callback return err code:%d}", ul_ret);
        return ul_ret;
    }

#ifdef _PRE_DEBUG_MODE
    ul_ret = frw_ipc_log_init(&pst_ipc_node->st_log);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_init_master: frw_ipc_log_init return err code:%d}", ul_ret);
        return ul_ret;
    }
#endif

    return OAL_SUCC;

}

OAL_STATIC oal_uint32  frw_ipc_init_slave(frw_ipc_node_stru *pst_ipc_node)
{
    oal_uint32 ul_ret;

    pst_ipc_node->en_cpuid             = (oal_uint8)OAL_GET_CORE_ID();
    pst_ipc_node->en_target_cpuid      = FRW_IPC_CORE_ID_MASTER;
    pst_ipc_node->en_cpu_type          = FRW_IPC_CORE_TYPE_SLAVE;
    pst_ipc_node->us_seq_num_rx_expect = 0;
    pst_ipc_node->us_seq_num_tx_expect = 0;
    pst_ipc_node->en_states            = FRW_IPC_CORE_STATE_INIT;
    pst_ipc_node->en_tx_int_ctl        = FRW_IPC_TX_CTRL_ENABLED;

    pst_ipc_node->st_irq_dev.p_irq_intr_func    = frw_ipc_msg_queue_recv;
    pst_ipc_node->st_irq_dev.ul_irq             = OAL_IRQ_NUM;
    pst_ipc_node->st_irq_dev.l_irq_type         = OAL_SA_SHIRQ;
    pst_ipc_node->st_irq_dev.pc_name            = "ipc";
    pst_ipc_node->st_irq_dev.p_drv_arg          = (void *)&g_st_queue_master_to_slave;

    if (OAL_UNLIKELY(0 != oal_irq_setup(&pst_ipc_node->st_irq_dev)))
    {
        OAM_WARNING_LOG0(0, OAM_SF_FRW, "{frw_ipc_msg_queue_setup_irq: oal_irq_setup fail!}");
        return OAL_FAIL;
    }

    pst_ipc_node->st_ipc_msg_callback.p_rx_complete_func = frw_ipc_recv;
    pst_ipc_node->st_ipc_msg_callback.p_tx_complete_func = frw_ipc_tx_complete;
    ul_ret = frw_ipc_msg_queue_register_callback(&pst_ipc_node->st_ipc_msg_callback);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_init_slave:: frw_ipc_msg_queue_register_callback return err code:%d}", ul_ret);
        return ul_ret;
    }

#ifdef _PRE_DEBUG_MODE
    ul_ret = frw_ipc_log_init(&pst_ipc_node->st_log);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_init_slave: frw_ipc_log_init return err code:%d}", ul_ret);
        return ul_ret;
    }
#endif

    return OAL_SUCC;

}

OAL_STATIC oal_uint32  frw_ipc_exit(oal_void)
{
    oal_uint32 ul_ret;
    frw_ipc_core_type_enum_uint8  en_type;

    en_type = frw_ipc_get_core_type();

    g_st_ipc_node[en_type].en_states = FRW_IPC_CORE_STATE_EXIT;

    oal_irq_free(&g_st_ipc_node[en_type].st_irq_dev);

    if (FRW_IPC_CORE_ID_MASTER == en_type)
    {
        ul_ret = frw_ipc_msg_queue_destroy(&g_st_queue_master_to_slave);
        if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
        {
            OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_exit: frw_ipc_msg_queue_destroy g_st_queue_master_to_slave return err code:%d}", ul_ret);
            return ul_ret;
        }

        ul_ret = frw_ipc_msg_queue_destroy(&g_st_queue_slave_to_master);
        if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
        {
            OAM_WARNING_LOG1(0, OAM_SF_FRW, "frw_ipc_exit:: frw_ipc_msg_queue_destroy g_st_queue_slave_to_master return err code:%d", ul_ret);
            return ul_ret;
        }
    }

#ifdef _PRE_DEBUG_MODE
    frw_ipc_log_tx_print(&g_st_ipc_node[en_type].st_log);
    frw_ipc_log_rx_print(&g_st_ipc_node[en_type].st_log);
    ul_ret = frw_ipc_log_exit(&g_st_ipc_node[en_type].st_log);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        return ul_ret;
    }
#endif

    return OAL_SUCC;
}

OAL_STATIC oal_uint32  frw_ipc_send_connect_request(oal_void)
{
    oal_uint32    ul_ret;

    ul_ret = frw_ipc_send_inter_msg(FRW_IPC_MSG_TYPE_CONNECT_REQUEST,
                                    OAL_PTR_NULL,
                                    0);

    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_send_connect_request: frw_ipc_send_inter_msg return %d}", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}

OAL_STATIC oal_uint32  frw_ipc_send_connect_response(oal_void)
{
    oal_uint32    ul_ret;

    ul_ret = frw_ipc_send_inter_msg(FRW_IPC_MSG_TYPE_CONNECT_RESPONSE, OAL_PTR_NULL, 0);

    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_send_connect_response: frw_ipc_send_inter_msg return %d}", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}

OAL_STATIC oal_uint32  frw_ipc_send_inter_msg(oal_uint8  uc_msg_type,
                                                       oal_uint8 *puc_data,
                                                       oal_uint8  us_len)
{
    oal_uint32                   ul_ret;
    frw_ipc_msg_mem_stru        *pst_msg_mem_stru;
    frw_ipc_inter_msg_stru      *pst_ipc_msg;
    frw_ipc_msg_queue_stru      *pst_msg_queue;
    frw_ipc_core_type_enum_uint8 en_type;
    oal_uint8                    ul_length;

    en_type = frw_ipc_get_core_type();
    FRW_IPC_GET_MSG_QUEUE(pst_msg_queue, en_type);

    ul_length = OAL_SIZEOF(frw_ipc_inter_msg_stru) - 4 + us_len;
    pst_msg_mem_stru = FRW_EVENT_ALLOC(ul_length);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_msg_mem_stru))
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_ipc_send_inter_msg: FRW_EVENT_ALLOC fail!}");
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    pst_ipc_msg = (frw_ipc_inter_msg_stru *)frw_ipc_get_header(pst_msg_mem_stru);

    pst_ipc_msg->st_ipc_hdr.us_seq_number   = g_st_ipc_node[en_type].us_seq_num_tx_expect;
    pst_ipc_msg->st_ipc_hdr.uc_target_cpuid = g_st_ipc_node[en_type].en_target_cpuid;
    pst_ipc_msg->st_ipc_hdr.uc_msg_type     = uc_msg_type;
    pst_ipc_msg->ul_length                  = us_len;

    if (us_len > 0)
    {
        oal_memcopy((oal_void *)pst_ipc_msg->auc_data, (oal_void *)puc_data, us_len);
    }

    ul_ret = frw_ipc_msg_queue_send(pst_msg_queue,
                                    pst_msg_mem_stru,
                                    g_st_ipc_node[en_type].en_tx_int_ctl,
                                    g_st_ipc_node[en_type].en_target_cpuid);

    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG0(0, OAM_SF_FRW, "{send inter msg fail.}");
        FRW_EVENT_FREE(pst_msg_mem_stru);
        return ul_ret;
    }

#ifdef _PRE_DEBUG_MODE
    frw_ipc_log_send(&g_st_ipc_node[en_type].st_log,
                      g_st_ipc_node[en_type].us_seq_num_tx_expect,
                      g_st_ipc_node[en_type].en_target_cpuid,
                      uc_msg_type);
#endif

    g_st_ipc_node[en_type].us_seq_num_tx_expect++;

    return OAL_SUCC;
}

oal_uint32  frw_ipc_reset(oal_void)
{
    /* TBD */
    return OAL_SUCC;
}

oal_uint32  frw_ipc_smp_dispatch(oal_void *buf)
{
    /* TBD */

    return OAL_SUCC;
}

oal_uint32  frw_ipc_smp_ordering(oal_void *buf)
{
    /* TBD */

    return OAL_SUCC;
}

OAL_STATIC oal_uint32  frw_ipc_event_queue_full(oal_void)
{
    oal_uint32    ul_ret;

    ul_ret = frw_ipc_send_inter_msg(FRW_IPC_MSG_TYPE_TX_INT_DISENABLE, OAL_PTR_NULL, 0);

    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_event_queue_full: frw_ipc_send_inter_msg return err code:%d}", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}

OAL_STATIC oal_uint32  frw_ipc_event_queue_empty(oal_void)
{
    oal_uint32    ul_ret;

    ul_ret = frw_ipc_send_inter_msg(FRW_IPC_MSG_TYPE_TX_INT_ENABLE, OAL_PTR_NULL, 0);

    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_event_queue_empty: frw_ipc_send_inter_msg return err code:%d}", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}

oal_uint32  frw_event_deploy_init(oal_void)
{
    oal_uint32 ul_ret;

    ul_ret = frw_ipc_init();
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG0(0, OAM_SF_FRW, "{frw event deploy init fail.}");
        return ul_ret;
    }

    frw_event_deploy_register(frw_event_deploy_pipeline);

    return OAL_SUCC;
}

oal_uint32  frw_event_deploy_exit(oal_void)
{
    oal_uint32 ul_ret;

    ul_ret = frw_ipc_exit();
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG0(0, OAM_SF_FRW, "{frw event deploy exit fail.}");
        return ul_ret;
    }

    return OAL_SUCC;
}

OAL_STATIC oal_uint32  frw_event_deploy_pipeline(frw_ipc_msg_mem_stru *pst_ipc_mem_msg,
                                              frw_event_deploy_enum_uint8 *en_deploy_result)
{
    frw_event_hdr_stru *pst_event_hdr;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_ipc_mem_msg) || (OAL_PTR_NULL == en_deploy_result))
    {
        OAM_ERROR_LOG2(0, OAM_SF_FRW, "{frw_event_deploy_pipeline: pst_ipc_mem_msg/en_deploy_result null ptr err:%d, %d}", pst_ipc_mem_msg, en_deploy_result);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event_hdr = (frw_event_hdr_stru *)pst_ipc_mem_msg->puc_data;

    if (FRW_EVENT_PIPELINE_STAGE_0 == pst_event_hdr->en_pipeline)
    {
        (*en_deploy_result) = FRW_EVENT_DEPLOY_NON_IPC;
    }
    else
    {
        (*en_deploy_result) = FRW_EVENT_DEPLOY_IPC;

        frw_ipc_send(pst_ipc_mem_msg);
    }

    return OAL_SUCC;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

