#ifndef _LISTS_H
#define _LISTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include "date.h"
#include "cmp_funcs.h"


/* Способы сортировки */
#define SORT_DESCENDING_ORDER (-1)
#define SORT_ASCENDING_ORDER  (1)


/* Условная привязка чисел к полю структуры элемента списка */
enum DATA_FIELDS
{
    LIST_POSITION = 0,    // Позиция элемента в списке
    LIST_ID,              // Id элемента в списке
    LIST_CAGE_NUMBER,     // a.cage_num
    LIST_ANIMAL_AREAL,    // a.animal.areal
    LIST_ANIMAL_BREED,    // a.animal.breed
    LIST_ANIMAL_NAME,     // a.animal.name
    LIST_PRODUCT_TYPE,    // a.products.type
    LIST_PRODUCT_WEIGHT,  // a.products.weight
    LIST_PRODUCT_COST,    // a.products.cost
    LIST_DATE             // a.date
};



/* Максимальные длины массивов в структуре данных */
#define ANIMAL_AREAL_MAX_LEN 32  // Максимальная длина Ареал обитания
#define ANIMAL_BREED_MAX_LEN 32  // Максимальная длина Порода
#define ANIMAL_NAME_MAX_LEN  32  // Максимальная длина Имя животного
#define PRODUCT_TYPE_MAX_LEN 32  // Максимальная длина Тип продукта

/* Максимальное количество цифр в числе */
#define WEIGHT_DGT_CNT   7
#define COST_DGT_CNT     7
#define CAGE_NUM_DGT_CNT 7
#define POSITION_DGT_CNT 4
#define ID_DGT_CNT       4



/* Вспомогательные типы данных */
typedef unsigned short field_num_t;  // Условный номер поля
typedef unsigned long list_id_t;  // ID элемента в списке
typedef unsigned long length_t;   // Длина чего-либо
typedef long double weight_t;     // Вес
typedef long double cost_t;       // Стоимость



/* Тип данных: структура с данными */
typedef struct list_data_t
{
    list_id_t cage_num;                          // Номер вольера.
    
    struct {                                   // Информация о животном.
        wchar_t areal[ANIMAL_AREAL_MAX_LEN + 1];   // Ареал обитания животного.
        wchar_t breed[ANIMAL_BREED_MAX_LEN + 1];   // Порода животного.
        wchar_t name[ANIMAL_NAME_MAX_LEN + 1];     // Имя животного.
    } animal;

    struct {                                   // Информация о продуктах.
        wchar_t  type[PRODUCT_TYPE_MAX_LEN + 1];   // Тип.
        weight_t weight;                           // Вес.
        cost_t   cost;                             // Стоимость.
    } products;

    udate_t date;                               // Дата.
}
list_data_t;



/* Тип данных: элемент списка */
typedef struct list_elem_t
{
    list_id_t id;                 // Уникальный номер элемента в списке
    list_data_t data;             // Хранимые данные

    /* Указатели на следующий и предыдущий элементы списка */
    struct list_elem_t *next, *prev;
}
list_elem_t;



/* Тип данных: объект списка */
typedef struct list_obj_t
{
    list_elem_t *head;

    length_t _length_;
    list_id_t _last_id_;
}
list_obj_t;



/* Создать новый объект списка */
list_obj_t * lists_CreateNewListObject (void);
/* Полное удаление объекта списка из памяти */
void lists_DeleteListObject (list_obj_t **);
/* Удалить все данные из объекта списка */
void lists_CleanListObject (list_obj_t *);
/* Создать элемент списка на основе переданных данных */
list_elem_t * lists_CreateNewElement (list_data_t *);
/* Вставить элемент (первый аргумент) после элемента (второй аргумент) */
void lists_InsertAfterElement (list_elem_t *, list_elem_t *);
/* Удалить элемент (пересвязка делается автоматически) */
void lists_DeleteElement (list_elem_t *);
/* Безопасно извлечь элемент из списка */
void list_DetachElement (list_elem_t *);
/* Вставить элемент в самое начало списка */
void lists_InsertAsListsHead (list_obj_t *, list_elem_t *);
/* Вставить элемент в конец списка */
void lists_InsertAsListsTail (list_obj_t *, list_elem_t *);
/* Поиск элемента в объекте списка по значению поля */
list_elem_t * lists_SearchElementByField (list_obj_t *, field_num_t, void *);
/* Поиск элемента, начиная с текущего и включая в поиск текущий */
list_elem_t * lists_SearchElementByFieldFromThisElement (list_elem_t *, field_num_t, void *);
/* Сравнить элементы по одному полю */
int lists_CompareElementsByOneField (const list_elem_t *, const list_elem_t *, const field_num_t);
/* Сравнить элементы по всем полям (вначале по приоритетному) */
int lists_CompareElements (const list_elem_t *, const list_elem_t *, const field_num_t);
/* Сортировать список по возрастанию или по убыванию по приоритетному полю */
void lists_SortListByField (list_obj_t *, const int, const field_num_t);
/* Получить общую стоимость всех продуктов за определённый период */
cost_t lists_GetCostForPeriod (const list_obj_t *, const udate_t *, const udate_t *);
/* Получить общую массу продуктов за определённый период */
weight_t lists_GetWeightForPeriod (const list_obj_t *, const udate_t *, const udate_t *);



#endif // !_LISTS_H