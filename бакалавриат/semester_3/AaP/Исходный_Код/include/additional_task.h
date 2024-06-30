#ifndef _ADDITIONAL_TASK_H
#define _ADDITIONAL_TASK_H

#include "lists.h"

/* Получить сумму употреблённых продуктов за указанный период */
cost_t lists_GetCostForPeriod     (const list_obj_t *, const udate_t *, const udate_t *);
/* Получить вес употреблённых продуктов за указанный период */
weight_t lists_GetWeightForPeriod (const list_obj_t *, const udate_t *, const udate_t *);

#endif // !_ADDITIONAL_TASK_H