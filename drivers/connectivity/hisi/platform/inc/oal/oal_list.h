#ifndef __OAL_LIST_H__
#define __OAL_LIST_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "oal_types.h"
#include "oal_mm.h"
#include "oal_util.h"

#define OAL_LIST_HEAD_INIT(_list_name) {(oal_list_entry_stru *)&(_list_name), (oal_list_entry_stru*)&(_list_name)}

#define OAL_LIST_CREATE_HEAD(_list_name) \
    oal_list_head_stru _list_name = OAL_LIST_HEAD_INIT(_list_name)

#define OAL_LIST_SEARCH_FOR_EACH(_list_pos, _list_head) \
    for (_list_pos = (_list_head)->pst_next; _list_pos != (oal_list_entry_stru *)(_list_head); _list_pos = _list_pos->pst_next)

#define OAL_LIST_GET_ENTRY(_list_ptr, _data_type, _data_member_list_name) \
       ((_data_type *)((oal_int8 *)(_list_ptr)-(oal_uint)(&((_data_type *)0)->_data_member_list_name)))

#define OAL_DLIST_HEAD_INIT(_dlist_name) {&(_dlist_name), &(_dlist_name)}

#define OAL_DLIST_CREATE_HEAD(_dlist_name) \
    oal_dlist_head_stru _dlist_name = OAL_DLIST_HEAD_INIT(_dlist_name)

#define OAL_DLIST_SEARCH_FOR_EACH(_dlist_pos, _dilst_head) \
    for (_dlist_pos = (_dilst_head)->pst_next; _dlist_pos != (_dilst_head); _dlist_pos = _dlist_pos->pst_next)

#define OAL_DLIST_SEARCH_FOR_EACH_SAFE(_dlist_pos, n, _dilst_head) \
    for (_dlist_pos = (_dilst_head)->pst_next, n = _dlist_pos->pst_next; _dlist_pos != (_dilst_head); _dlist_pos = n, n = _dlist_pos->pst_next)

#define OAL_DLIST_GET_ENTRY(_dlist_ptr, _data_type, _data_member_dlist_name) \
        ((_data_type *)((oal_int8 *)(_dlist_ptr)-(oal_uint)(&((_data_type *)0)->_data_member_dlist_name)))

typedef struct tag_oal_list_entry_stru
{
    struct tag_oal_list_entry_stru *pst_next;
}oal_list_entry_stru;

typedef struct
{
    struct tag_oal_list_entry_stru *pst_next;
    struct tag_oal_list_entry_stru *pst_prev;
}oal_list_head_stru;

typedef struct tag_oal_dlist_head_stru
{
    struct tag_oal_dlist_head_stru *pst_next;
    struct tag_oal_dlist_head_stru *pst_prev;
}oal_dlist_head_stru;

OAL_STATIC OAL_INLINE oal_void  oal_list_init_head(oal_list_head_stru *pst_list_head)
{
    pst_list_head->pst_next = (oal_list_entry_stru *)pst_list_head;
    pst_list_head->pst_prev = (oal_list_entry_stru *)pst_list_head;
}

OAL_STATIC OAL_INLINE oal_void  oal_list_add(oal_list_entry_stru *pst_new,
                            oal_list_head_stru *pst_head)
{
    oal_list_entry_stru *pst_tail = pst_head->pst_prev;

    pst_tail->pst_next = pst_new;
    pst_new->pst_next  = (oal_list_entry_stru *)pst_head;
    pst_head->pst_prev = pst_new;
}

OAL_STATIC OAL_INLINE oal_list_entry_stru* oal_list_delete_head(oal_list_head_stru *pst_head)
{
    oal_list_entry_stru *pst_node;

    if (pst_head->pst_next == (oal_list_entry_stru *)pst_head)
    {
        return OAL_PTR_NULL;
    }

    pst_node           = pst_head->pst_next;
    pst_head->pst_next = pst_node->pst_next;

    if (pst_head->pst_next == (oal_list_entry_stru *)pst_head)
    {
        pst_head->pst_prev = pst_head->pst_next;
    }

    pst_node->pst_next = OAL_PTR_NULL;

    return pst_node;
}

OAL_STATIC OAL_INLINE oal_void  oal_list_jion(oal_list_head_stru *pst_head1, oal_list_head_stru *pst_head2)
{
    oal_list_entry_stru *pst_list1_tail;
    oal_list_entry_stru *pst_list2_tail;

    pst_list1_tail              = pst_head1->pst_prev;
    pst_list2_tail              = pst_head2->pst_prev;
    pst_list1_tail->pst_next    = pst_head2->pst_next;
    pst_head1->pst_prev         = pst_head2->pst_prev;
    pst_list2_tail->pst_next    = (oal_list_entry_stru *)pst_head1;

}

OAL_STATIC OAL_INLINE oal_bool_enum_uint8 oal_list_is_empty(oal_list_head_stru *pst_head)
{
    return pst_head->pst_next == (oal_list_entry_stru *)pst_head;
}

OAL_STATIC OAL_INLINE oal_void  oal_dlist_init_head(oal_dlist_head_stru *pst_list)
{
    pst_list->pst_next = pst_list;
    pst_list->pst_prev = pst_list;
}

OAL_STATIC OAL_INLINE oal_void  oal_dlist_add(oal_dlist_head_stru *pst_new,
                            oal_dlist_head_stru *pst_prev,
                            oal_dlist_head_stru *pst_next)
{
    pst_next->pst_prev  = pst_new;
    pst_new->pst_next   = pst_next;
    pst_new->pst_prev   = pst_prev;
    pst_prev->pst_next  = pst_new;
}

OAL_STATIC OAL_INLINE oal_void  oal_dlist_delete(oal_dlist_head_stru *pst_prev, oal_dlist_head_stru *pst_next)
{
    pst_next->pst_prev = pst_prev;
    pst_prev->pst_next = pst_next;
}

OAL_STATIC OAL_INLINE oal_bool_enum_uint8 oal_dlist_is_empty(oal_dlist_head_stru *pst_head)
{
    if (OAL_PTR_NULL == pst_head->pst_next || OAL_PTR_NULL == pst_head->pst_prev)
    {
        return OAL_TRUE;
    }

    return pst_head->pst_next == pst_head;
}

OAL_STATIC OAL_INLINE oal_void  oal_dlist_add_head(oal_dlist_head_stru *pst_new, oal_dlist_head_stru *pst_head)
{
    oal_dlist_add(pst_new, pst_head, pst_head->pst_next);
}

OAL_STATIC OAL_INLINE oal_void  oal_dlist_add_tail(oal_dlist_head_stru *pst_new, oal_dlist_head_stru *pst_head)
{
    oal_dlist_add(pst_new, pst_head->pst_prev, pst_head);
}

OAL_STATIC OAL_INLINE oal_void  oal_dlist_delete_entry(oal_dlist_head_stru *pst_entry)
{
    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_entry->pst_next) || (OAL_PTR_NULL == pst_entry->pst_prev)))
    {
        return;
    }

    oal_dlist_delete(pst_entry->pst_prev, pst_entry->pst_next);
    pst_entry->pst_next = OAL_PTR_NULL;
    pst_entry->pst_prev = OAL_PTR_NULL;
}

OAL_STATIC OAL_INLINE oal_dlist_head_stru* oal_dlist_delete_head(oal_dlist_head_stru *pst_head)
{
    oal_dlist_head_stru *pst_node;

    pst_node = pst_head->pst_next;

    if((pst_node==pst_head) || (OAL_PTR_NULL == pst_node))
    {
        return OAL_PTR_NULL;
    }

    oal_dlist_delete_entry(pst_node);

    return pst_node;
}

OAL_STATIC OAL_INLINE oal_dlist_head_stru* oal_dlist_delete_tail(oal_dlist_head_stru *pst_head)
{
    oal_dlist_head_stru *pst_node;

    pst_node = pst_head->pst_prev;

    OAL_BUG_ON(pst_node==pst_head);
    OAL_BUG_ON(OAL_PTR_NULL == pst_node);

    oal_dlist_delete_entry(pst_node);

    return pst_node;
}

OAL_STATIC OAL_INLINE oal_void  oal_dlist_join_tail(oal_dlist_head_stru *pst_head1, oal_dlist_head_stru *pst_head2)
{
    oal_dlist_head_stru *pst_dlist1_tail;
    oal_dlist_head_stru *pst_dlist2_tail;
    oal_dlist_head_stru *pst_dlist2_first;


    pst_dlist1_tail              = pst_head1->pst_prev;
    pst_dlist2_tail              = pst_head2->pst_prev;
    pst_dlist2_first             = pst_head2->pst_next;
    pst_dlist1_tail->pst_next    = pst_dlist2_first;
    pst_dlist2_first->pst_prev   = pst_dlist1_tail;
    pst_head1->pst_prev          = pst_dlist2_tail;
    pst_dlist2_tail->pst_next    = pst_head1;
}

OAL_STATIC OAL_INLINE oal_void  oal_dlist_join_head(oal_dlist_head_stru *pst_head1, oal_dlist_head_stru *pst_head2)
{
    oal_dlist_head_stru *pst_head2_first;
    oal_dlist_head_stru *pst_head2_tail;
    oal_dlist_head_stru *pst_head1_first;

    if (oal_dlist_is_empty(pst_head2))
    {
        return;
    }

    pst_head2_first     = pst_head2->pst_next;
    pst_head2_tail      = pst_head2->pst_prev;
    pst_head1_first     = pst_head1->pst_next;

    pst_head1->pst_next         = pst_head2_first;
    pst_head2_first->pst_prev   = pst_head1;
    pst_head2_tail->pst_next    = pst_head1_first;
    pst_head1_first->pst_prev   = pst_head2_tail;


}

OAL_STATIC OAL_INLINE oal_void  oal_dlist_remove_head(oal_dlist_head_stru *pst_head1,
                                                              oal_dlist_head_stru *pst_head2,
                                                              oal_dlist_head_stru *pst_last_entry)
{
    pst_head1->pst_next = pst_head2->pst_next;
    pst_head1->pst_prev = pst_last_entry;

    pst_head2->pst_next = pst_last_entry->pst_next;
    if (pst_last_entry->pst_next == pst_head2)
    {
       pst_head2->pst_prev = pst_head2;
    }
    else
    {
       ((oal_dlist_head_stru*)(pst_last_entry->pst_next))->pst_prev = pst_head2;
    }
    pst_last_entry->pst_next = pst_head1;
    if (pst_last_entry->pst_prev == pst_head2)
    {
       pst_last_entry->pst_prev = pst_head1;
    }
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_list.h */
