#include "wcs_conv.h"

long long wcs2int (const wchar_t * string)
{
    /* Немедленно выйти из подпрограммы, если строка не была передана */
    if (string == NULL) return 0;

    size_t offset = 0;  // Отступ от начала строки
    int    sign   = 1;  // Окончательный знак числа
    long long n   = 0;  // Полученное число

    /* Пропустить пробелы перед числом */
    while (iswspace(string[offset])) offset++;

    /* Определиться со знаком числа */
    switch (string[offset])
    {
        case '-': sign = -1;
        case '+': offset++;  break;
    }

    /* Преобразовать оставшёюся часть строки в число */
    while (iswdigit(string[offset]))
        n = n * 10 + (string[offset++] - L'0');
    
    return (n * sign);
}

long double wcs2float (const wchar_t * string)
{
    /* Немедленно выйти из подпрограммы, если не была передана строка */
    if (string == NULL) return 0;

    size_t offset = 0;  // Отступ от начала строки
    int    sign   = 1;  // Итоговый знак числа
    long double n = 0;  // Полученное число

    /* Пропуск пробелов перед числом */
    while (iswspace(string[offset])) offset++;

    /* Определиться со знаком числа */
    switch (string[offset])
    {
        case '-': sign = -1;
        case '+': offset++;  break;
    }

    /* Преобразовать целую часть числа */
    for (; iswdigit(string[offset]); offset++)
        n = n * 10 + ((long double) (string[offset] - L'0'));
    
    /* Встречено не-число */
    switch (string[offset])
    {
        // Продолжить выполнение, если встреченное не-число является
        //   разделителем
        case '.': case ',':
            offset++;
            break;
        // Иначе вернуть полученную целую часть числа
        default:
            return (n * sign);
            break;
    }
    
    int d = 1;

    /* Преобразовать дробную часть числа */
    while (iswdigit(string[offset]))
        n += ((long double) (string[offset++] - '0')) / (d *= 10);
    
    return (n * sign);
}

void int2wcs (const long long number, wchar_t * string)
{
    swprintf(string, 20, L"%lld", number);
}

void float2wcs (const long double number, wchar_t * string)
{
    swprintf(string, 8, L"%Lf", number);
}

void fitwcs (wchar_t * dest, const wchar_t * src, const int max_length)
{
    if (!dest || !src || max_length < 4) return;

    int
        curr_length  = 0,
        src_length   = wcslen (src),
        insert_colon = (src_length - max_length > 0) ? 1 : 0;
    
    wchar_t
        * src_var    = src;
    
    while (*src_var != 0 && max_length > curr_length)
    {
        *dest = (max_length - 4 < curr_length && insert_colon) ? (L'.') : (*src_var);
        
        src_var++;
        dest++;
        curr_length ++;
    }

    while (curr_length < max_length)
        (*(dest++) = L' ') & (curr_length ++);

    return;
}