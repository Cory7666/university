#ifndef _DATE_H
#define _DATE_H

#include <wchar.h>
#include <wctype.h>
#include "wcs_conv.h"
#include "cmp_funcs.h"

/* Тип данных: дата */
typedef struct
{
    int Y,  // Год
        M,  // Месяц
        D;  // День
}
udate_t;

/*
    Конвертировать дату в строку, используя указанный разделитель и заданный
    шаблон.
*/
void date2wcsdp (const udate_t *, wchar_t *, const wchar_t, const wchar_t *);

/*Конвертировать дату в строку */
#define date2wcs(date, string) date2wcsdp(date, string, L'/', L"%02d%lc%02d%lc%04d")
/* Конвертировать дату в строку, используя указанный разделитель */
#define date2wcsd(date, string, delimiter) date2wcsdp(date, string, delimiter, L"%02d%lc%02d%lc%04d")
/* Конвертировать дату в строку, используя указанный шаблон */
#define date2wcsp(date, string, pattern) date2wcsdp(date, string, L'/', pattern)

/* Конвертировать строку в дату */
void wcs2date (udate_t *, const wchar_t *);

/*
    Сравнить две даты.
    Вернуть 0, если даты равны; отрицательное число, если первая дата меньше
      второй; положительное число, если первая дата больше второй.
*/
int datecmp (const udate_t *, const udate_t *);

#endif // !_DATE_H