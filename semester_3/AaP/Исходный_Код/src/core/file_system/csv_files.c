#include "files.h"

int save_as_csv (const list_obj_t * list, const wchar_t * file_name_wcs)
{
    /* Мгновенный выход из подпрограммы, если передан пустой указатель на объект списка */
    if (!list) return FS_NO_LIST_PTR;
    /* Мгновенный выход из подпрограммы, если передан объект списка без данных */
    if (1 > list->_length_) return FS_NO_LIST_DATA;
    
    /* Всё хорошо, продолжить выполнение */



    /* Ввести дополнительные переменные */
    length_t position = 1;  // Порядковый номер элемента в списке
    char file_name_mbs[(wcslen(file_name_wcs) + 1) * sizeof(wchar_t)];  // Имя файла как MBS
    wchar_t date_wcs[20];  // MBS для хранения даты

    /* Перевести из WCS в MBS */
    wcstombs(file_name_mbs, file_name_wcs, sizeof(file_name_mbs));

    /* Открыть файл для записи */
    FILE * f = fopen(file_name_mbs, "w");
    
    /* Разместить заголовок таблицы */
    //fprintf(f, "Порядковый номер%cНомер клетки%cИмя животного%cПорода животного%cАреал обитания животного%cТип продуктов%cВес продуктов%cСтоимость продуктов%cДата\n", CSV_DELIMITER, CSV_DELIMITER, CSV_DELIMITER, CSV_DELIMITER, CSV_DELIMITER, CSV_DELIMITER, CSV_DELIMITER, CSV_DELIMITER);

    /* Сохранение данных в файл */
    for (list_elem_t * e = list->head; e; e = e->next, position++)
    {
        /* Перевод даты в MBS */
        date2wcs(&e->data.date, date_wcs);

        /* Записать данные в файл */
        fprintf(f, "%lu%c%lu%c%ls%c%ls%c%ls%c%ls%c%.3Lf%c%.2Lf%c%ls\n",
            position, CSV_DELIMITER,
            e->data.cage_num, CSV_DELIMITER,
            e->data.animal.name, CSV_DELIMITER,
            e->data.animal.breed, CSV_DELIMITER,
            e->data.animal.areal, CSV_DELIMITER,
            e->data.products.type, CSV_DELIMITER,
            e->data.products.weight, CSV_DELIMITER,
            e->data.products.cost, CSV_DELIMITER,
            date_wcs
        );

        /* Обновить данные в файле */
        fflush(f);
    }

    /* Закрыть файл и выйти из подпрограммы */
    fclose(f);
    return FS_SUCCESS;
}

int read_from_csv (list_obj_t * list, const wchar_t * fileName)
{
    if (is_exist_wcs(fileName) != FS_SUCCESS) return FS_FILE_NO_READ_ACCESS; // Если файл нельзя открыть.

    setlocale(LC_ALL, "");

    // Открытие файла для чтения.
    char fileName_char[(wcslen(fileName) + 1) * sizeof(wchar_t)];
    wcstombs(fileName_char, fileName, wcslen(fileName) * sizeof(wchar_t));
    FILE * f = fopen(fileName_char, "r");

    // Очистка списка, если в нём были какие-то данные
    if (list->head) { lists_DeleteListObject(&list); list = lists_CreateNewListObject(); }
    
    size_t tmp_line_size = 10;
    char *tmp_line = calloc(tmp_line_size, sizeof(char)),  // Содержит строку из файла
         tmp_str[2048],                                    // Содержит обрабатываемое слово
         *pos1 = NULL, *pos2 = NULL;                       // Позиции при обработке строки
    wchar_t tmp_wstr[2048];
    list_data_t d;
    
    while (!feof(f))
    {  
        // Считать строку из файла
        if (getline(&tmp_line, &tmp_line_size, f) < 4) continue;
        if (tmp_line[strlen(tmp_line) - 1] == '\n') tmp_line[strlen(tmp_line) - 1] = '\0';

        memset(&d, 0, sizeof(d));
        memset(tmp_str, 0, sizeof(tmp_str));
        memset(tmp_wstr, 0, sizeof(tmp_wstr));

        // Пропуск порядкового номера
        pos1 = tmp_line; pos2 = strchr(pos1, CSV_DELIMITER);
        pos1 = pos2 + 1;
        
        // Обработка номера вольера
        pos2 = strchr(pos1, CSV_DELIMITER);
        strncpy(tmp_str, pos1, pos2 - pos1); // Копирование фрагмента строки в другую строку
        d.cage_num = atoi(tmp_str);          // Перевод в число и запись в структуру
        pos1 = pos2 + 1;                     // Передвинуть позицию
        
        // Обработка имени животного
        memset(tmp_str, 0, sizeof(tmp_str));
        memset(tmp_wstr, 0, sizeof(tmp_wstr));
        pos2 = strchr(pos1, CSV_DELIMITER);
        strncpy(tmp_str, pos1, pos2 - pos1); // Копирование фрагмента строки в другую строку
        mbstowcs(tmp_wstr, tmp_str, sizeof(tmp_str) * sizeof(wchar_t));  // Перевод из MBS в WCS
        wcscpy(d.animal.name, tmp_wstr);     // Копирование в соответствующее поле
        pos1 = pos2 + 1;                     // Передвинуть позицию

        // Обработка породы животного
        memset(tmp_str, 0, sizeof(tmp_str));
        memset(tmp_wstr, 0, sizeof(tmp_wstr));
        pos2 = strchr(pos1, CSV_DELIMITER);
        strncpy(tmp_str, pos1, pos2 - pos1); // Копирование фрагмента строки в другую строку
        mbstowcs(tmp_wstr, tmp_str, strlen(tmp_str));  // Перевод из MBS в WCS
        wcscpy(d.animal.breed, tmp_wstr);     // Копирование в соответствующее поле
        pos1 = pos2 + 1;                     // Передвинуть позицию

        // Обработка ареала обитания животного
        memset(tmp_str, 0, sizeof(tmp_str));
        memset(tmp_wstr, 0, sizeof(tmp_wstr));
        pos2 = strchr(pos1, CSV_DELIMITER);
        strncpy(tmp_str, pos1, pos2 - pos1); // Копирование фрагмента строки в другую строку
        mbstowcs(tmp_wstr, tmp_str, strlen(tmp_str));  // Перевод из MBS в WCS
        wcscpy(d.animal.areal, tmp_wstr);     // Копирование в соответствующее поле
        pos1 = pos2 + 1;                     // Передвинуть позицию

        // Обработка типа продуктов животного
        memset(tmp_str, 0, sizeof(tmp_str));
        memset(tmp_wstr, 0, sizeof(tmp_wstr));
        pos2 = strchr(pos1, CSV_DELIMITER);
        strncpy(tmp_str, pos1, pos2 - pos1); // Копирование фрагмента строки в другую строку
        mbstowcs(tmp_wstr, tmp_str, strlen(tmp_str));  // Перевод из MBS в WCS
        wcscpy(d.products.type, tmp_wstr);     // Копирование в соответствующее поле
        pos1 = pos2 + 1;                     // Передвинуть позицию

        // Обработка веса продуктов
        memset(tmp_str, 0, sizeof(tmp_str));
        memset(tmp_wstr, 0, sizeof(tmp_wstr));
        pos2 = strchr(pos1, CSV_DELIMITER);
        strncpy(tmp_str, pos1, pos2 - pos1); // Копирование фрагмента строки в другую строку
        d.products.weight = atof(tmp_str);          // Перевод в число и запись в структуру
        pos1 = pos2 + 1;                     // Передвинуть позицию

        // Обработка стоимости продуктов
        memset(tmp_str, 0, sizeof(tmp_str));
        memset(tmp_wstr, 0, sizeof(tmp_wstr));
        pos2 = strchr(pos1, CSV_DELIMITER);
        strncpy(tmp_str, pos1, pos2 - pos1); // Копирование фрагмента строки в другую строку
        d.products.cost = atof(tmp_str);          // Перевод в число и запись в структуру
        pos1 = pos2 + 1;                     // Передвинуть позицию

        // Обработка даты
        memset(tmp_str, 0, sizeof(tmp_str));
        memset(tmp_wstr, 0, sizeof(tmp_wstr));
        strcpy(tmp_str, pos1);               // Копирование фрагмента строки в другую строку
        mbstowcs(tmp_wstr, tmp_str, strlen(tmp_str));  // Перевод из MBS в WCS
        wcs2date(&d.date, tmp_wstr);         // Перевод строки в дату и запись в структуру

        lists_InsertAsListsTail(list, lists_CreateNewElement(&d));
    }

    fclose(f);
    return FS_SUCCESS;
}