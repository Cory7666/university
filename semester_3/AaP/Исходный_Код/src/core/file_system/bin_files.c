#include "files.h"

int save_as_bin (const list_obj_t * list, const wchar_t * file_name_wcs)
{
    /* Мгновенный выход из подпрограммы, если передан пустой указатель на объект списка */
    if (!list) return FS_NO_LIST_PTR;
    /* Мгновенный выход из подпрограммы, если передан объект списка без данных */
    if (1 > list->_length_) return FS_NO_LIST_DATA;

    /* Перевести имя файла из WCS в MBS */
    char file_name_mbs[(wcslen(file_name_wcs) + 1) * sizeof(wchar_t)];
    wcstombs(file_name_mbs, file_name_wcs, wcslen(file_name_wcs) * sizeof(wchar_t));
    FILE * f = fopen(file_name_mbs, "w");
    /* Мгновенно выйти из подпрограммы, если невозможно создать файл */
    if (!f) return FS_FILE_NO_WRITE_ACCESS;

    /* Перебор элементов и запись каждого в файл */
    for (list_elem_t * e = list->head; e; e = e->next)
        fwrite(&(e->data), sizeof(list_data_t), 1, f);

    /* Закрыть файл и выйти */
    fclose(f);
    return FS_SUCCESS;
}

int read_from_bin (list_obj_t * list, const wchar_t * file_name_wcs)
{
    /* Выйти, если файл не существует или к нему нет доступа */
    if (is_exist_wcs(file_name_wcs) != FS_SUCCESS) return FS_FILE_NO_READ_ACCESS;

    /* Перевод имени файла в MBS и открытие файла */
    char file_name_mbs[(wcslen(file_name_wcs) + 1) * sizeof(wchar_t)];
    wcstombs(file_name_mbs, file_name_wcs, wcslen(file_name_wcs) * sizeof(wchar_t));
    FILE * f = fopen(file_name_mbs, "r");

    /* Проверка целостности содержащихся данных */
    size_t currpos = ftell(f); fseek(f, 0, SEEK_END);
    if ( ((ftell(f) - currpos) % sizeof(list_data_t)) != 0 ) { fclose(f); return FS_BROKEN_DATA; }
    fseek(f, currpos, SEEK_SET);

    /* Всё ок, значит можно удалить данные в списке */
    lists_CleanListObject (list);

    /* Поэлементное считывание данных из файла и добавление в объект списка */
    list_data_t d;
    while(fread(&d, sizeof(list_data_t), 1, f)) lists_InsertAsListsTail(list, lists_CreateNewElement(&d));

    /* Закрыть файл и выйти из подпрограммы */
    fclose(f);
    return FS_SUCCESS;
}