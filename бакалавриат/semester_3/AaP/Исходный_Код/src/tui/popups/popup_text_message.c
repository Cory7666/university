#include "__popups__.h"



void tui_draw_popup_text_message (const wchar_t * popup_title, const wchar_t * message)
{
    int win_width = 0.4 * getmaxx(stdscr),
        message_lines_count = get_message_lines_count (message, win_width),
        win_height = 8 + message_lines_count,
        win_start_x = (getmaxx(stdscr) - win_width) / 2,
        win_start_y = (getmaxy(stdscr) - win_height) / 2;
    
    WINDOW * popup_win = newwin(win_height, win_width, win_start_y, win_start_x);
    PANEL *  popup_panel = new_panel(popup_win);

    tui_draw_popup_header(popup_win, popup_title);
    
    /* Создание окна для текста */
    WINDOW * inner_win = derwin (popup_win, win_height - 8, win_width - 2, 4, 1);
    PANEL * inner_panel = new_panel (inner_win);
    mvwprintw(inner_win, 0, 0, "%ls", message);

    /* Печать кнопки */
    wattron(popup_win, TUI_HIGHLIGHT_ITEM_STYLE);
    mvwprintw(popup_win, win_height - 3, (win_width - 4) / 2, " OK ");
    wattroff(popup_win, TUI_HIGHLIGHT_ITEM_STYLE);

    update_panels();
    doupdate();

    while (getwchar() != MKEY_ENTER);

    /* Удаление окон и панелей */
    del_panel(inner_panel);
    delwin(inner_win);
    del_panel(popup_panel);
    delwin(popup_win);

    return;
}