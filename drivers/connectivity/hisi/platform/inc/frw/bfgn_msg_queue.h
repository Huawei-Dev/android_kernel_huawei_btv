#ifndef __BFGN_MSG_QUEUE_H__
#define __BFGN_MSG_QUEUE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "types.h"

#define BFG_MSG_BUTT 0xFFFF

typedef enum
{
    QUEUE_EMPTY                 = 0x00,
    QUEUE_NOT_EMPTY             = 0x01,
    QUEUE_BUTT
}queue_is_empty_enum;
typedef UINT8   queue_is_empty_enum_uint8;

typedef enum
{
    SYS_MSG_NO_SPACE          = 0x00,
    SYS_MSG_SET_SUCC          = 0x01,
    SYS_MSG_BUTT
}msg_set_result_enum;
typedef UINT8   msg_set_result_enum_uint8;

typedef enum
{
    MSG_NOT_AVAILABLE         = 0x00,
    MSG_AVAILABLE             = 0x01,
    MSG_CHECK_BUTT
}msg_check_available_enum;
typedef UINT8 msg_check_available_enum_uint8;

typedef struct node
{
    UINT16              us_msg;
    struct node        *pst_nextnode;
}msg_node_stru;

typedef struct
{
    msg_node_stru    *pst_header;
    msg_node_stru    *pst_tail;
}queue_stru;

typedef struct
{
    queue_stru          st_msg_handle_que;
    queue_stru          st_msg_pool_que;
}queue_group_stru;

typedef void (*MSG_FUNC)(void);

void bfgn_msg_queue_init(queue_stru*         pst_msg_pool_que,
                                  queue_stru*         pst_msg_handle_que,
                                  msg_node_stru       ast_msg_res[],
                                  UINT16              us_msg_res_len);
UINT8 bfgn_post_msg_to_queue(queue_group_stru* pst_msg_queue, UINT16 usMSGNum);
UINT8 bfgn_insert_msg_to_queue(queue_group_stru* pst_msg_queue, UINT16 usMSGNum);
UINT16 bfgn_get_msg(queue_group_stru* pst_msg_queue);
INT8 bfgn_queue_isempty(queue_stru* pst_msg_queue);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of message_queue_handle.h */
