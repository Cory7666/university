#ifndef _FILES_H
#define _FILES_H

#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include "lists.h"

#define CSV_DELIMITER L';'

enum FS_RETURN {
    FS_SUCCESS = 0,          /* Успешное завершение работы */
    FS_FILE_NO_READ_ACCESS,  /* Ошибка: нельзя прочитаться данные из файла */
    FS_FILE_NO_WRITE_ACCESS, /* Ошибка: нельзя записать данные в файл */
    FS_NO_LIST_PTR,          /* Ошибка: передан пустой указатель на список */
    FS_NO_LIST_DATA,         /* Ошибка: передан список без данных */
    FS_BROKEN_DATA           /* Ошибка: данные в файле повреждены */
};

/* Определить, доступен ли файл для чтения (имя файла в виде MBS) */
int is_exist     (const char *);
/* Определить, доступен ли файл для чтения (имя файла в виде WCS) */
int is_exist_wcs (const wchar_t *);

/* Сохранить данные в бинарный файл */
int save_as_bin   (const list_obj_t * list, const wchar_t * file_name_wcs);
/* Считать данные из бинарного файла */
int read_from_bin (list_obj_t * list, const wchar_t * file_name_wcs);

/* Сохранить данные объекта структуры в CSV-файл */
int save_as_csv   (const list_obj_t * list, const wchar_t * file_name_wcs);
/* Считать данные из CSV-файла */
int read_from_csv (list_obj_t * list, const wchar_t * fileName);

#endif // !_FILES_H