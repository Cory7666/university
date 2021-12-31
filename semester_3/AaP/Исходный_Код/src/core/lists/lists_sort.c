#include "lists.h"

void lists_SortListByField (list_obj_t * list, const int sort_order, const field_num_t prio_field)
{
    if (!list) return;
    if (2 > list->_length_) return;

    list_elem_t *e1, *e2;
    list_data_t tmp_d; list_id_t tmp_id;

    for (length_t i = 1; i < list->_length_; i++)
    {
        e1 = lists_SearchElementByField(list, LIST_POSITION, &i);
        for (length_t j = i + 1; j < list->_length_ + 1; j++)
        {
            e2 = lists_SearchElementByField(list, LIST_POSITION, &j);

            if (lists_CompareElements(e1, e2, prio_field) * sort_order > 0)
            {
                memcpy(&tmp_d, &e1->data, sizeof(list_data_t)); tmp_id = e1->id;
                
                memcpy(&e1->data, &e2->data, sizeof(list_data_t));
                e1->id = e2->id;

                memcpy(&e2->data, &tmp_d, sizeof(list_data_t));
                e2->id = tmp_id;
            }
        }
    }
}