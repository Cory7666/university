#include "date.h"

void date2wcsdp (const udate_t * date, wchar_t * string, const wchar_t delimiter, const wchar_t * pattern)
{
    /* Выйти, если дата не была передана */
    if (!date) return;

    swprintf(string, wcslen(pattern) + 1, pattern, date->D, delimiter, date->M, delimiter, date->Y);
}

void wcs2date (udate_t * date, const wchar_t * string)
{
    /* Выйти, если дата не была передана */
    if (!date) return;

    size_t offset = 0;
    for (; iswspace(string[offset]); offset++);

    date->D = wcs2int(string + offset);
    date->M = wcs2int(string + offset + 3);
    date->Y = wcs2int(string + offset + 6);
}

int datecmp (const udate_t * d1, const udate_t * d2)
{
    /* Выйти, если одна из дат не была передана */
    if (!(d1 && d2)) return 0;

    int result = 0;
    // Сначала сравнить по полю Год
    if (result = cmp_nums(d1->Y, d2->Y))
        return result;
    else
    // Если равны, то сравнить по полю Месяц
        if (result = cmp_nums(d1->M, d2->M))
            return result;
        else
        // Если предыдущие поля равны, сравнить по полю день и незамедлительно вернуть результат
            return cmp_nums(d1->D, d2->D);
}