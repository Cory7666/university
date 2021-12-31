#include "__popups__.h"



int tui_draw_popup_select (const wchar_t * popup_title, const wchar_t * message, const menu_t menu)
{
    int menu_item_count = tui_get_menu_item_count(menu);
    int win_width = getmax(0.4 * getmaxx(stdscr), wcslen(menu[0])),
        message_lines_count = get_message_lines_count (message, win_width),
        win_height = 8 + message_lines_count + menu_item_count,
        win_start_x = (getmaxx(stdscr) - win_width) / 2,
        win_start_y = (getmaxy(stdscr) - win_height) / 2;
    int selected_menu_item = 1;
    unsigned int key = MKEY_NULL;
    
    WINDOW * popup_win = newwin(win_height, win_width, win_start_y, win_start_x);
    PANEL *  popup_panel = new_panel(popup_win);

    tui_draw_popup_header(popup_win, popup_title);
    
    /* Создать окно для текста и поместить в окно текст */
    WINDOW * inner_win_text = derwin (popup_win, message_lines_count, win_width - 2, 4, 1);
    PANEL * inner_panel_text = new_panel (inner_win_text);
    mvwprintw(inner_win_text, 0, 0, "%ls", message);

    /* Создание окна для набора кнопок */
    WINDOW * inner_win_buttons = derwin (popup_win, menu_item_count, win_width - 2, win_height - 3 - menu_item_count, 1);
    PANEL * inner_panel_buttons = new_panel(inner_win_buttons);

    do {
        switch (key)
        {
            case MKEY_ARROW_UP:
                if (selected_menu_item > 1)
                    selected_menu_item--;
                break;
            
            case MKEY_ARROW_DOWN:
                if (selected_menu_item < menu_item_count)
                    selected_menu_item++;
                break;
        }

        tui_draw_vmenu(inner_win_buttons, 0, 0, 0, menu, selected_menu_item);

        update_panels();
        doupdate();

        key = getwchar();
    } while (key != MKEY_ENTER);

    /* Удаление окон и панелей */
    del_panel(inner_panel_buttons);
    del_panel(inner_panel_text);
    del_panel(popup_panel);
    delwin(inner_win_buttons);
    delwin(inner_win_text);
    delwin(popup_win);

    return selected_menu_item;
}