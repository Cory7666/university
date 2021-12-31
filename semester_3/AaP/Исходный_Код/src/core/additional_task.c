#include "additional_task.h"

cost_t lists_GetCostForPeriod (const list_obj_t * list, const udate_t * date_min, const udate_t * date_max)
{
    /* Выйти, если не был передан указатель на объект списка */
    if (!list) return -1.0;

    /* Инициализация переменных */
    int date_min_flag = (date_min) ? (1) : (0),
        date_max_flag = (date_max) ? (1) : (0);
    cost_t sum = 0.0;

    /* Поиск подходящих элементов и суммирование */
    for (list_elem_t * e = list->head; e; e = e->next)
        if ( (datecmp(&e->data.date, date_min) * date_min_flag >= 0) && (datecmp(&e->data.date, date_max) * date_max_flag <= 0) )
            sum += e->data.products.cost;

    return sum;
}

weight_t lists_GetWeightForPeriod (const list_obj_t * list, const udate_t * date_min, const udate_t * date_max)
{
    /* Выйти, если не был передан указатель на объект списка */
    if (!list) return -1.0;

    /* Инициализация переменных */
    int date_min_flag = (date_min) ? (1) : (0),
        date_max_flag = (date_max) ? (1) : (0);
    weight_t sum = 0.0;

    /* Поиск подходящих элементов и суммирование */
    for (list_elem_t * e = list->head; e; e = e->next)
        if ( (!date_min_flag || datecmp(&e->data.date, date_min) >= 0) && (!date_max_flag || datecmp(&e->data.date, date_max) <= 0) )
            sum += e->data.products.weight;

    return sum;
}