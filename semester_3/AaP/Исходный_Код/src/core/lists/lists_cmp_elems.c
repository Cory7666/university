#include "lists.h"

int lists_CompareElementsByOneField (const list_elem_t * e1, const list_elem_t * e2, const field_num_t field)
{
    int result = 0;

    switch (field)
    {
        case LIST_ID:
            result = cmp_nums(e1->id, e2->id);
            break;
        case LIST_CAGE_NUMBER:
            result = cmp_nums(e1->data.cage_num,    e2->data.cage_num);
            break;
        case LIST_ANIMAL_AREAL:
            result = wcscmp(e1->data.animal.areal,  e2->data.animal.areal);
            break;
        case LIST_ANIMAL_BREED:
            result = wcscmp(e1->data.animal.breed,  e2->data.animal.breed);
            break;
        case LIST_ANIMAL_NAME:
            result = wcscmp(e1->data.animal.name,   e2->data.animal.name);
            break;
        case LIST_PRODUCT_TYPE:
            result = wcscmp(e1->data.products.type, e2->data.products.type);
            break;
        case LIST_PRODUCT_COST:
            result = cmp_nums(e1->data.products.cost,   e2->data.products.cost);
            break;
        case LIST_PRODUCT_WEIGHT:
            result = cmp_nums(e1->data.products.weight, e2->data.products.weight);
            break;
        case LIST_DATE:
            result = datecmp(&e1->data.date, &e2->data.date);
            break;
    }

    return result;
}

int lists_CompareElements (const list_elem_t * e1, const list_elem_t * e2, const field_num_t prio_field)
{
    int result = 0;

    /* Завершить подпрогрумму, так как элементы нельзя сравнить по позиции */
    if (LIST_POSITION == prio_field) return 0;

    /* Сравнить по приоритетному полю */
    result = lists_CompareElementsByOneField(e1, e2, prio_field);
    if (result) return result;

    /* Сравнить по остальным полям */
    for (int i = LIST_ID + 1; !result && i <= LIST_DATE; i++)
        if (i != prio_field)
            result = lists_CompareElementsByOneField(e1, e2, i);
    
    /* Вернуть окончательный результат сравнения */
    return result;
}