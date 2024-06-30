#include "tui.h"
#include "../forms/__forms__.h"

void tui_print_element_info_window (WINDOW * win, const int selected_field, const list_elem_t * elem)
{
    if (!elem || !win) return;
    
    const int LABEL_MAX_WIDTH = 26;    // Максимальная ширина ярлыка
    int curr_offset = 1;               // Отступ от начала окна
    wchar_t tmp_wcs[200];              // Строка хранения временного значения


    /* Нарисовать свой ярлык к каждому полю информации и нарисовать соответствующее поле */
    
    memset (tmp_wcs, 0, sizeof(tmp_wcs));
    int2wcs (elem->id, tmp_wcs);
    if (selected_field == 1) wattron (win, TUI_HIGHLIGHT_ITEM_STYLE);
    mvwprintw (win, 0, 0, " Уникальный ID            ");
    tui_draw_form_field (win, curr_offset++, 0, L"НЕТ ЗНАЧЕНИЯ", tmp_wcs, LABEL_MAX_WIDTH);
    if (selected_field == 1) wattroff (win, TUI_HIGHLIGHT_ITEM_STYLE);



    memset (tmp_wcs, 0, sizeof(tmp_wcs));
    int2wcs (elem->data.cage_num, tmp_wcs);
    if (selected_field == 2) wattron (win, TUI_HIGHLIGHT_ITEM_STYLE);
    mvwprintw (win, curr_offset++, 0, " Номер вольера            ");
    tui_draw_form_field (win, curr_offset++, 0, L"НЕТ ЗНАЧЕНИЯ", tmp_wcs, LABEL_MAX_WIDTH);
    if (selected_field == 2) wattroff (win, TUI_HIGHLIGHT_ITEM_STYLE);



    if (selected_field == 3) wattron (win, TUI_HIGHLIGHT_ITEM_STYLE);
    mvwprintw (win, curr_offset++, 0, " Животное. Ареал обитания ");
    tui_draw_form_field (win, curr_offset++, 0, L"НЕТ ЗНАЧЕНИЯ", elem->data.animal.areal, ANIMAL_AREAL_MAX_LEN);
    if (selected_field == 3) wattroff (win, TUI_HIGHLIGHT_ITEM_STYLE);



    if (selected_field == 4) wattron (win, TUI_HIGHLIGHT_ITEM_STYLE);
    mvwprintw (win, curr_offset++, 0, " Животное. Порода         ");
    tui_draw_form_field (win, curr_offset++, 0, L"НЕТ ЗНАЧЕНИЯ", elem->data.animal.breed, ANIMAL_BREED_MAX_LEN);
    if (selected_field == 4) wattroff (win, TUI_HIGHLIGHT_ITEM_STYLE);



    if (selected_field == 5) wattron (win, TUI_HIGHLIGHT_ITEM_STYLE);
    mvwprintw (win, curr_offset++, 0, " Животное. Имя            ");
    tui_draw_form_field (win, curr_offset++, 0, L"НЕТ ЗНАЧЕНИЯ", elem->data.animal.name, ANIMAL_NAME_MAX_LEN);
    if (selected_field == 5) wattroff (win, TUI_HIGHLIGHT_ITEM_STYLE);



    if (selected_field == 6) wattron (win, TUI_HIGHLIGHT_ITEM_STYLE);
    mvwprintw (win, curr_offset++, 0, " Продукты. Тип            ");
    tui_draw_form_field (win, curr_offset++, 0, L"НЕТ ЗНАЧЕНИЯ", elem->data.products.type, PRODUCT_TYPE_MAX_LEN);
    if (selected_field == 6) wattroff (win, TUI_HIGHLIGHT_ITEM_STYLE);


    memset (tmp_wcs, 0, sizeof(tmp_wcs));
    float2wcs (elem->data.products.weight, tmp_wcs);
    if (selected_field == 7) wattron (win, TUI_HIGHLIGHT_ITEM_STYLE);
    mvwprintw (win, curr_offset++, 0, " Продукты. Вес            ");
    tui_draw_form_field (win, curr_offset++, 0, L"НЕТ ЗНАЧЕНИЯ", tmp_wcs, LABEL_MAX_WIDTH);
    if (selected_field == 7) wattroff (win, TUI_HIGHLIGHT_ITEM_STYLE);



    memset (tmp_wcs, 0, sizeof(tmp_wcs));
    float2wcs (elem->data.products.cost, tmp_wcs);
    if (selected_field == 8) wattron (win, TUI_HIGHLIGHT_ITEM_STYLE);
    mvwprintw (win, curr_offset++, 0, " Продукты. Стоимость      ");
    tui_draw_form_field (win, curr_offset++, 0, L"НЕТ ЗНАЧЕНИЯ", tmp_wcs, LABEL_MAX_WIDTH);
    if (selected_field == 8) wattroff (win, TUI_HIGHLIGHT_ITEM_STYLE);



    memset (tmp_wcs, 0, sizeof(tmp_wcs));
    date2wcs (&elem->data.date, tmp_wcs);
    if (selected_field == 9) wattron (win, TUI_HIGHLIGHT_ITEM_STYLE);
    mvwprintw (win, curr_offset++, 0, " Дата поступления         ");
    tui_draw_form_field (win, curr_offset++, 0, L"НЕТ ЗНАЧЕНИЯ", tmp_wcs, LABEL_MAX_WIDTH);
    if (selected_field == 9) wattroff (win, TUI_HIGHLIGHT_ITEM_STYLE);


    return;
}
