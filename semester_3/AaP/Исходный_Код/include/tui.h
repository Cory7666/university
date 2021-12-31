#ifndef _TUI_POPUPS_H
#define _TUI_POPUPS_H

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>

#include <ncursesw/ncurses.h>
#include <ncursesw/panel.h>

#include "keyboard_keys.h"
#include "cmp_funcs.h"
#include "checker.h"
#include "lists.h"



#define TUI_HIGHLIGHT_ITEM_STYLE ((A_REVERSE) | (A_BOLD))


#define TUI_ADD_ELEMENT_CACELLED 0b00000
#define TUI_ADD_ELEMENT_FLAG     0b00001
#define TUI_AT_BEGIN_FLAG        0b00100
#define TUI_AT_END_FLAG          0b00000



/* Тип массива из пунктов меню */
typedef wchar_t* menu_t[];



/* Получить количество строк, занимаемых переданным текстом. Также учитываются символы перехода на новую строку */
int get_message_lines_count (const wchar_t *, const int max_width);

/* Получить количество пунктов в меню */
int tui_get_menu_item_count (const menu_t);
/* Отрисовать вертикальное меню в заданном месте с заданным расстоянием между элементами */
void tui_draw_vmenu (WINDOW *, const int, const int, const int, const menu_t, const int);

/* Нарисовать границы и заголовок для окна */
void tui_draw_popup_header (WINDOW *, const wchar_t *);
/* Отобразить окно с обычным текстом */
void tui_draw_popup_text_message (const wchar_t *, const wchar_t *);
/* Отобразить окно с выбором */
int tui_draw_popup_select (const wchar_t *, const wchar_t *, const menu_t);
/* Отобразить окно с формой */
int tui_draw_popup_form (const wchar_t *, const wchar_t *, const wchar_t *, wchar_t *, int, checker_mode_t);
/* Отобразить окно с вводом даты */
void tui_draw_popup_date (const wchar_t *, const wchar_t *, udate_t *);

/* Отобразить окно с редактированием информации */
int  tui_popup_edit_element_data (const wchar_t *, list_data_t *, int);
/* Отобразить окно с информацией об элементе */
void tui_popup_show_only_element (const wchar_t *, const list_elem_t *);

/*
 * Нарисовать таблицу в выбранном окне, отступив от начала списка на num_page страниц.
*/
int tui_draw_table_in_window (WINDOW *, const list_obj_t, const length_t, const int);

void tui_print_element_info_window (WINDOW *, const int, const list_elem_t *);


#endif // ! _TUI_POPUPS_H