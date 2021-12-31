#include "files.h"

int is_exist (const char * file_name)
{
    FILE *f = fopen(file_name, "r");

    /* Файл не существует или прочитать его невозможно */
    if (!f) return FS_FILE_NO_READ_ACCESS;

    /* Файл существует и доступен для чтения */
    fclose(f);
    return FS_SUCCESS;
}

int is_exist_wcs (const wchar_t * file_name_wcs)
{
    char file_name_mbs[(wcslen(file_name_wcs) + 1) * sizeof(wchar_t)];
    wcstombs(file_name_mbs, file_name_wcs, wcslen(file_name_wcs) * sizeof(wchar_t));

    return is_exist(file_name_mbs);
}