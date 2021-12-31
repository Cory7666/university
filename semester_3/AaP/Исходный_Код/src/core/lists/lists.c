#include "lists.h"

list_obj_t * lists_CreateNewListObject (void)
{
    return ((list_obj_t *) calloc(sizeof(list_obj_t), 1));
}

void lists_DeleteListObject (list_obj_t ** list)
{
    /* Удаление данных из списка */
    lists_CleanListObject(*list);

    /* Освобождение памяти */
    free(*list);
    *list = NULL;

    return;
}

void lists_CleanListObject (list_obj_t * list)
{
    /* Немедленный выход из подпрограммы, если передан пустой указатель */
    if (!list) return;
    /* Немедленный выход из подпрограммы, если объект не содержит данных */
    if (1 > list->_length_) return;

    list_elem_t *e = list->head;

    /* Циклическое удаление данных из объекта */
    while (e->next) free((e = e->next)->prev);
    free(e);

    /* Обнуление длины списка и идентификатора */
    list->head = NULL;
    list->_length_ = 0;
    list->_last_id_ = 0;

    return;
}

list_elem_t * lists_CreateNewElement (list_data_t * data)
{
    /* Немедленный выход из программы, если данные не были переданы */
    if (!data) return NULL;

    /* Выделить память для нового элемента. Обнулить память */
    list_elem_t * e = malloc(sizeof(list_elem_t));
    memset(e, 0, sizeof(list_elem_t));

    /* Записать данные в элемент */
    memcpy(&e->data, data, sizeof(list_data_t));

    /* Завершить выполнение подпрограммы */
    return e;
}

void lists_InsertAfterElement (list_elem_t * e1, list_elem_t * e2)
{
    /* Немедленные выход, если один из параметров NULL */
    if (!e1 || !e2) return;

    e1->next = e2->next;
    if (e1->next) e1->next->prev = e1;
    e1->prev = e2;
    e2->next = e1;

    return;
}

void lists_DeleteElement (list_elem_t * e)
{
    /* Немедленный выход, если передан пустой указатель */
    if (!e) return;

    /* Вытащить элемент из списка и очитить память */
    list_DetachElement(e);
    free(e);

    return;
}

void list_DetachElement (list_elem_t * e)
{
    /* Выход из подпрограммы, если передан пустой указатель */
    if (!e) return;

    list_elem_t *e_left = e->prev, *e_right = e->next;

    /* Пересвязка */
    if (e_left) e_left->next = e_right;
    if (e_right) e_right->prev = e_left;

    return;
}

void lists_InsertAsListsHead (list_obj_t * list, list_elem_t * e)
{
    /* Немедленный выход, если передан пустой указатель на объект списка */
    if (!list) return;
    /* Немедленно выйти, если не был передан указатель на элемент */
    if (!e) return;

    e->next = list->head;
    if (e->next) e->next->prev = e;
    list->head = e;
    e->prev = NULL;

    /* Обновить Id элемента и длину списка*/
    e->id = list->_last_id_++;
    list->_length_++;

    return;
}

void lists_InsertAsListsTail (list_obj_t * list, list_elem_t * e)
{
    /* Немедленный выход, если передан пустой указатель на объект списка */
    if (!list) return;

    if (1 > list->_length_) lists_InsertAsListsHead (list, e);
    else
    {
        list_elem_t * f = lists_SearchElementByField(list, LIST_POSITION, &list->_length_);
        lists_InsertAfterElement(e, f);
        e->id = list->_last_id_++;
        list->_length_++;
    }

    return;
}

list_elem_t * lists_SearchElementByField (list_obj_t * list, field_num_t field, void * data)
{
    return lists_SearchElementByFieldFromThisElement (list->head, field, data);
}

list_elem_t * lists_SearchElementByFieldFromThisElement (list_elem_t * e, field_num_t field, void * data)
{
    /* Немедленный выход из подпрограммы, если передан пустой указатель на элемент' списка */
    if (!e) return NULL;
    /* Немедленный выход из подпрограммы, если передан некорректный номер поля */
    if ( field < LIST_POSITION || field > LIST_DATE ) return NULL;

    length_t      position_counter = 1;
    short         exit_flag        = 0;

    /* Пытаться найти элемент, пока не будет достигнут конец списка или искомый элемент не будет найден */
    while (e  && !exit_flag)
    {
        switch (field)
        {
            case LIST_POSITION:
                exit_flag = ( *((length_t *) data) == position_counter );
                break;
            case LIST_ID:
                exit_flag = ( *((list_id_t *) data) == e->id );
                break;
            case LIST_CAGE_NUMBER:
                exit_flag = ( *((list_id_t *) data) == e->data.cage_num );
                break;
            case LIST_ANIMAL_AREAL:
                exit_flag = !wcscmp((wchar_t *) data, e->data.animal.areal);
                break;
            case LIST_ANIMAL_BREED:
                exit_flag = !wcscmp((wchar_t *) data, e->data.animal.breed);
                break;
            case LIST_ANIMAL_NAME:
                exit_flag = !wcscmp((wchar_t *) data, e->data.animal.name);
                break;
            case LIST_PRODUCT_TYPE:
                exit_flag = !wcscmp((wchar_t *) data, e->data.products.type);
                break;
            case LIST_PRODUCT_WEIGHT:
                exit_flag = ( *((weight_t *) data) == e->data.products.weight );
                break;
            case LIST_PRODUCT_COST:
                exit_flag = ( *((cost_t *) data) == e->data.products.cost );
                break;
            case LIST_DATE:
                exit_flag = !datecmp((udate_t *) data, &e->data.date);
                break;
        }

        if (exit_flag) break;

        e = e->next; position_counter++;
    }

    return e;
}