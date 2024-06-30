#ifndef _WCS_CONV_H
#define _WCS_CONV_H

#include <wchar.h>
#include <wctype.h>

/* Преобразовать WCS в целое число */
long long wcs2int (const wchar_t *);

/* Преобразовать WCS в вещественное число */
long double wcs2float (const wchar_t *);

/*
    Преобразовать целое число в WCS (назначение должно вмещать не менее
      20 символов)
*/
void int2wcs (const long long, wchar_t *);

/*
    Преобразовать вещественное число в WCS (назначение должно вмещать не менее
      20 символов)
*/
void float2wcs (const long double, wchar_t *);

/*
 * Нормализовать строку и Изменить размер строки до указанного.
*/
void fitwcs (wchar_t *, const wchar_t *, const int);

#endif // !_WCS_CONV_H