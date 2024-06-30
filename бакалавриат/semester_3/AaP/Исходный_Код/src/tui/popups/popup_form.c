#include "__popups__.h"
#include "../forms/__forms__.h"

int tui_draw_popup_form (const wchar_t * popup_title, const wchar_t * message, const wchar_t * placeholder, wchar_t * value, int max_width, checker_mode_t mode)
{
    if (!mode) mode = VMASK_ANY_CHAR;
    int helper_items_count = 0;
    for (checker_mode_t tmp = mode; tmp; tmp >>= 1) helper_items_count += ((tmp & 1) ? 1 : 0);

    mkey_t key = MKEY_NULL;
    int last_curs_state = curs_set(2),
        message_len          = (int) wcslen(message),   // Длина сообщения
        last_char_pos        = (int) wcslen(value) - 1, // Позичия последнего символа в value
        message_lines_cnt    = -1,                      // Количество строк, занимаемых сообщением
        helper_lines_cnt     =  1 + helper_items_count, // Количество строк, занимаемых помощником
        form_field_lines_cnt = -1;                      // Количество строк, занимаемых формой
    
    int win_width = 0.4 * getmaxx(stdscr),
        win_height = 3                                                  // Высота заголовка с границей
            + (message_lines_cnt = get_message_lines_count (message, win_width))  // ...
            + 2                                                         //
            + helper_lines_cnt                                          // ...
            + 1                                                         // Отступ от помощника
            + (form_field_lines_cnt = max_width / (win_width - 2) + ( (max_width % (win_width - 2)) ? 1 :  0 ))    // ...
            + 2,                                                        // Дополнительное пространство после поля формы
        win_start_x = (getmaxx(stdscr) - win_width) / 2,
        win_start_y = (getmaxy(stdscr) - win_height) / 2;
    
    /* Основное окно popup'a */
    WINDOW * popup_win = newwin(win_height, win_width, win_start_y, win_start_x);
    PANEL *  popup_panel = new_panel(popup_win);

    tui_draw_popup_header(popup_win, popup_title);
    
    /* Создать окно для текста и поместить в окно текст */
    WINDOW * inner_win_text = derwin (popup_win, message_lines_cnt, win_width - 2, 3, 1);
    PANEL * inner_panel_text = new_panel (inner_win_text);
    mvwprintw(inner_win_text, 0, 0, "%ls", message);

   {
       int tmp_helper_counter = 1;

       mvwprintw (popup_win, 3 + message_lines_cnt + tmp_helper_counter++, 1, "Ограничения на ввод:");
       if (mode & VMASK_LOWER_CHARS)
            mvwprintw (popup_win, 3 + message_lines_cnt + tmp_helper_counter++, 1, "* Буквы нижнего регистра.");
        if (mode & VMASK_UPPER_CHARS)
            mvwprintw (popup_win, 3 + message_lines_cnt + tmp_helper_counter++, 1, "* Буквы верхнего регистра.");
        if (mode & VMASK_DIGITS)
            mvwprintw (popup_win, 3 + message_lines_cnt + tmp_helper_counter++, 1, "* Цифры.");
        if (mode & VMASK_PUNCTS)
            mvwprintw (popup_win, 3 + message_lines_cnt + tmp_helper_counter++, 1, "* Точки и запятые.");
        if (mode & VMASK_ADD_FS_CHARS)
            mvwprintw (popup_win, 3 + message_lines_cnt + tmp_helper_counter++, 1, "* \"_\", \"/\", \":\" и \"-\".");
    }

    /* Создать окно для формы */
    WINDOW * inner_win_form = derwin (popup_win, form_field_lines_cnt, win_width - 2, win_height - 3 - form_field_lines_cnt, 1);
    PANEL  * inner_panel_form = new_panel (inner_win_form);

    /* Отрисовать кнопку выхода из попапа */
    wattron(popup_win, TUI_HIGHLIGHT_ITEM_STYLE);
    mvwprintw (popup_win, win_height - 2, (win_width - 18) / 2, " ENTER для выхода ");
    wattroff(popup_win, TUI_HIGHLIGHT_ITEM_STYLE);

    do
    {
        /* Проверить нажатую клавишу */   
        switch (key)
        {
            // Нажат Enter или первый проход цикла
            case MKEY_ENTER: case MKEY_NULL:
                break;
            // Нажато Backspace
            case MKEY_BACKSPACE:
                if (last_char_pos >= 0)
                    value[last_char_pos--] = 0;
                break;
            // Нажатадругая кнопка/комбинация кнопок 
            default:
                if (check_wchar(key, mode) && last_char_pos < max_width - 1)
                    value[++last_char_pos] = key;
                break;
        }

        /* Вывести форму на экран и обновить окна/панели */
        mvwprintw (popup_win, win_height - 4 - form_field_lines_cnt, 1, "Ввод (%3d символов из %3d):", last_char_pos + 1, max_width);
        tui_draw_form_field (inner_win_form, 0, 0, placeholder, value, max_width);
        update_panels ();
        doupdate ();
    }
    while ((key = getwchar()) != MKEY_ENTER);

    /* Удаление всех созданных панелей и окон */
    del_panel (inner_panel_form);
    del_panel (inner_panel_text);
    del_panel (popup_panel);
    delwin (inner_win_form);
    delwin (inner_win_text);
    delwin (popup_win);

    /* Установить прошлое значение видимости курсора */
    curs_set(last_curs_state);

    return last_char_pos + 1;
}