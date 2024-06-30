#include "tui.h"

int tui_draw_table_in_window (WINDOW * win, const list_obj_t list_obj, const length_t page_num, const int selected_row)
{
    const int TABLE_TOTAL_WIDTH  = getmaxx(win),  // Итоговая ширина таблицы
              POS_COL_WIDTH      = 4,  // Ширина колонки с порядковым номером
              ID_COL_WIDTH       = 4,  // Ширина колонки с ID
              CAGE_NUM_COL_WIDTH = 7,  // Ширина колонки с Номером вольера
              PRODUCT_WEIGHT_COL_WIDTH = 8,  // Ширина колонки с Весом продукта
              PRODUCT_COST_COL_WIDTH   = 12,  // Ширина колонки со Стоимостью продукта
              DATE_COL_WIDTH     = 11,  // Ширина колонки с Датой
              // Ширина колонки с Информацией о животном (с учётом внутренних границ)
              ANIMAL_TOTAL_COL_WIDTH = getmax(25, (int) (TABLE_TOTAL_WIDTH - POS_COL_WIDTH - ID_COL_WIDTH - CAGE_NUM_COL_WIDTH - DATE_COL_WIDTH - PRODUCT_WEIGHT_COL_WIDTH - PRODUCT_COST_COL_WIDTH - 9) / 4 * 3),
              // Ширина колонки с Типом продукта
              PRODUCT_TYPE_COL_WIDTH   = getmax(3, (int) (TABLE_TOTAL_WIDTH - POS_COL_WIDTH - ID_COL_WIDTH - CAGE_NUM_COL_WIDTH - DATE_COL_WIDTH - PRODUCT_WEIGHT_COL_WIDTH - PRODUCT_COST_COL_WIDTH - 9 - ANIMAL_TOTAL_COL_WIDTH)),
              // Ширина колонки с Информацией о продукте (с учётом внутренних границ)
              PRODUCT_TOTAL_COL_WIDTH = PRODUCT_COST_COL_WIDTH + 1 + PRODUCT_WEIGHT_COL_WIDTH + 1 + PRODUCT_TYPE_COL_WIDTH,
              ANIMAL_NAME_COL_WIDTH = getmax(5, (int) ((ANIMAL_TOTAL_COL_WIDTH - 2) / 3)),  // Ширина колонки с Именем животного
              ANIMAL_ARIAL_COL_WIDTH = getmax(14, (int) ((ANIMAL_TOTAL_COL_WIDTH - 2) / 3)),  // Ширина колонки с Ареалом обитания
              ANIMAL_BREED_COL_WIDTH = getmax(6, ANIMAL_TOTAL_COL_WIDTH - 2 - ANIMAL_NAME_COL_WIDTH - ANIMAL_ARIAL_COL_WIDTH);  // Ширина колонки с Породой животного
    const int DATA_ROWS_CNT = getmaxy(win) - 4 - 1;  // Количество строк с данными в таблице
    int offset_from_header = 0,
        some_counter = 0;
    wchar_t * tmp_wcs = calloc (sizeof(wchar_t), 256);
    
    
    wmove(win, 0, 0);

    /* отрисовать верхнюю границу шапки таблицы */
    waddstr(win, "┌");
    for (int i = 0; i < POS_COL_WIDTH;           i++) waddstr(win, "─"); waddstr(win, "┬");
    for (int i = 0; i < ID_COL_WIDTH;            i++) waddstr(win, "─"); waddstr(win, "┬");
    for (int i = 0; i < CAGE_NUM_COL_WIDTH;      i++) waddstr(win, "─"); waddstr(win, "┬");
    for (int i = 0; i < ANIMAL_TOTAL_COL_WIDTH;  i++) waddstr(win, "─"); waddstr(win, "┬");
    for (int i = 0; i < PRODUCT_TOTAL_COL_WIDTH; i++) waddstr(win, "─"); waddstr(win, "┬");
    for (int i = 0; i < DATE_COL_WIDTH;          i++) waddstr(win, "─");
    waddstr(win, "┐");

    /* Отрисовка шапки, 1 ряд */
    mvwprintw(
        win, 1, 0,
        "│%*ls│%*ls│%*ls│%*ls│%*ls│%*ls│",
        POS_COL_WIDTH, L"  № ",
        ID_COL_WIDTH,  L" ID ",
        CAGE_NUM_COL_WIDTH, L" Номер ",
        ANIMAL_TOTAL_COL_WIDTH, L"Информация о животном",
        PRODUCT_TOTAL_COL_WIDTH, L"Информация о продукте",
        DATE_COL_WIDTH, L"Дата"
    );

    mvwprintw (win, 1, 0, "│ №  | ID | Номер ");

    memset (tmp_wcs, 0, sizeof(wchar_t) * 256);
    fitwcs (tmp_wcs, L"Информация о животном", ANIMAL_TOTAL_COL_WIDTH);
    wprintw (win, "│%ls", tmp_wcs);

    memset (tmp_wcs, 0, sizeof(wchar_t) * 256);
    fitwcs (tmp_wcs, L"Информация о продукте", PRODUCT_TOTAL_COL_WIDTH);
    wprintw (win, "│%ls", tmp_wcs);

    wprintw (win, "│    Дата   │");

    mvwprintw (win, 2, 0, "│    |    |вольера");

    memset (tmp_wcs, 0, sizeof(wchar_t) * 256);
    fitwcs (tmp_wcs, L"Ареал обитания", ANIMAL_ARIAL_COL_WIDTH);
    wprintw (win, "│%ls", tmp_wcs);

    memset (tmp_wcs, 0, sizeof(wchar_t) * 256);
    fitwcs (tmp_wcs, L"Порода", ANIMAL_BREED_COL_WIDTH);
    wprintw (win, "│%ls", tmp_wcs);

    memset (tmp_wcs, 0, sizeof(wchar_t) * 256);
    fitwcs (tmp_wcs, L"Имя", ANIMAL_NAME_COL_WIDTH);
    wprintw (win, "│%ls", tmp_wcs);

    memset (tmp_wcs, 0, sizeof(wchar_t) * 256);
    fitwcs (tmp_wcs, L"Тип", PRODUCT_TYPE_COL_WIDTH);
    wprintw (win, "│%ls", tmp_wcs);

    wprintw (win, "│ Вес, г │Стоимость, P│ кормления │");

    /* Отрисовать нижнюю границу шапки таблицы */
    wmove(win, 3, 0);
    waddstr(win, "├");
    for (int i = 0; i < POS_COL_WIDTH;           i++) waddstr(win, "─"); waddstr(win, "┼");
    for (int i = 0; i < ID_COL_WIDTH;            i++) waddstr(win, "─"); waddstr(win, "┼");
    for (int i = 0; i < CAGE_NUM_COL_WIDTH;      i++) waddstr(win, "─"); waddstr(win, "┼");
    for (int i = 0; i < ANIMAL_ARIAL_COL_WIDTH;  i++) waddstr(win, "─"); waddstr(win, "┼");
    for (int i = 0; i < ANIMAL_BREED_COL_WIDTH;  i++) waddstr(win, "─"); waddstr(win, "┼");
    for (int i = 0; i < ANIMAL_NAME_COL_WIDTH;   i++) waddstr(win, "─"); waddstr(win, "┼");
    for (int i = 0; i < PRODUCT_TYPE_COL_WIDTH;  i++) waddstr(win, "─"); waddstr(win, "┼");
    for (int i = 0; i < PRODUCT_WEIGHT_COL_WIDTH; i++)waddstr(win, "─"); waddstr(win, "┼");
    for (int i = 0; i < PRODUCT_COST_COL_WIDTH;  i++) waddstr(win, "─"); waddstr(win, "┼");
    for (int i = 0; i < DATE_COL_WIDTH;          i++) waddstr(win, "─");
    waddstr(win, "┤");

    /* Получить первый элемент page_num страницы */
    length_t first_element_position = (page_num - 1) * DATA_ROWS_CNT + 1;
    list_elem_t * elem = lists_SearchElementByField(&list_obj, LIST_POSITION, (void *) &first_element_position);

    if (!elem)
    {
        memset (tmp_wcs, 0, sizeof(wchar_t) * 256);
        fitwcs (tmp_wcs, L"Нет данных в списке.", TABLE_TOTAL_WIDTH - 2);
        mvwprintw (win, 4 + offset_from_header++, 0, "│%ls│", tmp_wcs);
    }
    else
    {
        wchar_t date_tmp[40]; memset (date_tmp, 0, sizeof(date_tmp));
        int element_position = first_element_position;

        for (; elem && element_position < first_element_position + DATA_ROWS_CNT; element_position++, elem = elem->next, offset_from_header++)
        {
            date2wcs(&elem->data.date, date_tmp);

            if (offset_from_header + 1 == selected_row) wattron (win, TUI_HIGHLIGHT_ITEM_STYLE);
            
            wmove(win, 4 + offset_from_header, 0);
            wprintw(win, "│%*d", POS_COL_WIDTH, element_position);
            wprintw(win, "│%*lu", ID_COL_WIDTH, elem->id);
            wprintw(win, "│%*lu", CAGE_NUM_COL_WIDTH, elem->data.cage_num);
            
            memset (tmp_wcs, 0, sizeof(wchar_t) * 256);
            fitwcs (tmp_wcs, elem->data.animal.areal, ANIMAL_ARIAL_COL_WIDTH);
            wprintw (win, "│%ls", tmp_wcs);

            memset (tmp_wcs, 0, sizeof(wchar_t) * 256);
            fitwcs (tmp_wcs, elem->data.animal.breed, ANIMAL_BREED_COL_WIDTH);
            wprintw (win, "│%ls", tmp_wcs);

            memset (tmp_wcs, 0, sizeof(wchar_t) * 256);
            fitwcs (tmp_wcs, elem->data.animal.name, ANIMAL_NAME_COL_WIDTH);
            wprintw (win, "│%ls", tmp_wcs);

            memset (tmp_wcs, 0, sizeof(wchar_t) * 256);
            fitwcs (tmp_wcs, elem->data.products.type, PRODUCT_TYPE_COL_WIDTH);
            wprintw (win, "│%ls", tmp_wcs);
            
            wprintw(win, "│%*.2Lf", PRODUCT_WEIGHT_COL_WIDTH, elem->data.products.weight);
            wprintw(win, "│%*.2Lf", PRODUCT_COST_COL_WIDTH, elem->data.products.cost);

            memset (tmp_wcs, 0, sizeof(wchar_t) * 256);
            fitwcs (tmp_wcs, date_tmp, DATE_COL_WIDTH);
            wprintw (win, "│%ls│", tmp_wcs);
            
            if (offset_from_header + 1 == selected_row) wattroff(win, TUI_HIGHLIGHT_ITEM_STYLE);

            some_counter++;
        }
    }

    wmove(win, 4 + offset_from_header++, 0);
    waddstr(win, "└");
    for (int i = 0; i < POS_COL_WIDTH;           i++) waddstr(win, "─"); waddstr(win, "┴");
    for (int i = 0; i < ID_COL_WIDTH;            i++) waddstr(win, "─"); waddstr(win, "┴");
    for (int i = 0; i < CAGE_NUM_COL_WIDTH;      i++) waddstr(win, "─"); waddstr(win, "┴");
    for (int i = 0; i < ANIMAL_ARIAL_COL_WIDTH;  i++) waddstr(win, "─"); waddstr(win, "┴");
    for (int i = 0; i < ANIMAL_BREED_COL_WIDTH;  i++) waddstr(win, "─"); waddstr(win, "┴");
    for (int i = 0; i < ANIMAL_NAME_COL_WIDTH;   i++) waddstr(win, "─"); waddstr(win, "┴");
    for (int i = 0; i < PRODUCT_TYPE_COL_WIDTH;  i++) waddstr(win, "─"); waddstr(win, "┴");
    for (int i = 0; i < PRODUCT_WEIGHT_COL_WIDTH; i++)waddstr(win, "─"); waddstr(win, "┴");
    for (int i = 0; i < PRODUCT_COST_COL_WIDTH;  i++) waddstr(win, "─"); waddstr(win, "┴");
    for (int i = 0; i < DATE_COL_WIDTH;          i++) waddstr(win, "─");
    waddstr(win, "┘");

    free (tmp_wcs);
    return some_counter;
}
