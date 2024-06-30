#include "__popups__.h"

#include "__popups__.h"
#include "../forms/__forms__.h"

void tui_draw_popup_date (const wchar_t * popup_title, const wchar_t * message, udate_t * date)
{
    mkey_t key = MKEY_NULL;
    int last_curs_state = curs_set(0),
        message_lines_cnt    = -1,                      // Количество строк, занимаемых сообщением
        helper_lines_cnt     =  4,                      // Количество строк, занимаемых помощником
        form_field_lines_cnt = -1,                      // Количество строк, занимаемых формой
        selected_field       = 1;                       // Номер выбранного поля
    
    int tmp_day   = 1,
        tmp_month = 1,
        tmp_year  = 2021;
    
    int win_width = 0.4 * getmaxx(stdscr),
        win_height = 3                                                  // Высота заголовка с границей
            + (message_lines_cnt = get_message_lines_count (message, win_width))  // ...
            + 2                                                         //
            + helper_lines_cnt                                          // ...
            + 1                                                         // Отступ от помощника
            + 1                                                         // Высота формы для даты
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

    /* Отобразить помощника ввода */
    mvwprintw (popup_win, 3 + message_lines_cnt + 1, 1, "Осуществление ввода:");
    mvwprintw (popup_win, 3 + message_lines_cnt + 2, 1, "* ARROW UP/DOWN - Увеличить/Уменьшить значение.");
    mvwprintw (popup_win, 3 + message_lines_cnt + 3, 1, "* ARROW LEFT/RIGHT, TAB - Выбор поля.");
    mvwprintw (popup_win, 3 + message_lines_cnt + 4, 1, "* ENTER - Подтвердить выбор.");

    /* Отрисовать кнопку выхода из попапа */
    wattron(popup_win, TUI_HIGHLIGHT_ITEM_STYLE);
    mvwprintw (popup_win, win_height - 2, (win_width - 18) / 2, " ENTER для выхода ");
    wattroff(popup_win, TUI_HIGHLIGHT_ITEM_STYLE);

    do
    {
        /* Проверить нажатую клавишу */   
        switch (key)
        {
            // Нажат Enter или Первый проход цикла
            case MKEY_ENTER: case MKEY_NULL:
                break;
            
            // Нажата кнопка увеличения значения
            case MKEY_ARROW_UP:
                switch (selected_field)
                {
                    case 1:
                        if (tmp_day < 31)
                            tmp_day++;
                        break;
                    case 2:
                        if (tmp_month < 12)
                            tmp_month++;
                        break;
                    case 3:
                        if (tmp_year < 2100)
                            tmp_year++;
                        break;
                }
                break;
            
            // Нажата кнопка уменьшения значения
            case MKEY_ARROW_DOWN:
                switch (selected_field)
                {
                    case 1:
                        if (tmp_day > 1)
                            tmp_day--;
                        break;
                    case 2:
                        if (tmp_month > 1)
                            tmp_month--;
                        break;
                    case 3:
                        if (tmp_year > 1970)
                            tmp_year--;
                        break;
                }
                break;
            
            // Нажата кнопка перехода к следующему полю
            case MKEY_TAB: case MKEY_ARROW_RIGHT:
                if (selected_field == 4)
                    selected_field = 1;
                else
                    selected_field++;
                break;
            
            // Нажата кнопка перехода к предыдущему полю
            case MKEY_ARROW_LEFT:
                if (selected_field == 1)
                    selected_field = 4;
                else
                    selected_field--;
                break;
        }

        /* Обработать день, если выбран февраль в високосный год */
        if (2 == tmp_month)
        {
            if (tmp_year % 4)
            // Невисокосный год
            {
                if (tmp_day > 28)
                    tmp_day = 28;
            }
            else
            // Високосный од
            {
                if (tmp_day > 29)
                    tmp_day = 29;
            }
        }

        /* Вывести форму на экран */
        mvwprintw (popup_win, win_height - 3, 1, "  /  /    ");

        if (selected_field == 1) wattron(popup_win, TUI_HIGHLIGHT_ITEM_STYLE);
        mvwprintw (popup_win, win_height - 3, 1, "%02d", tmp_day);
        if (selected_field == 1) wattroff(popup_win, TUI_HIGHLIGHT_ITEM_STYLE);

        if (selected_field == 2) wattron(popup_win, TUI_HIGHLIGHT_ITEM_STYLE);
        mvwprintw (popup_win, win_height - 3, 4, "%02d", tmp_month);
        if (selected_field == 2) wattroff(popup_win, TUI_HIGHLIGHT_ITEM_STYLE);

        if (selected_field == 3) wattron(popup_win, TUI_HIGHLIGHT_ITEM_STYLE);
        mvwprintw (popup_win, win_height - 3, 7, "%04d", tmp_year);
        if (selected_field == 3) wattroff(popup_win, TUI_HIGHLIGHT_ITEM_STYLE);

        
        /* Отрисовать кнопку выхода из попапа */
        if (selected_field == 4) wattron(popup_win, TUI_HIGHLIGHT_ITEM_STYLE);
        mvwprintw (popup_win, win_height - 2, (win_width - 18) / 2, " ENTER для выхода ");
        if (selected_field == 4) wattroff(popup_win, TUI_HIGHLIGHT_ITEM_STYLE);
        
        /* Обновить окна/панели */
        update_panels ();
        doupdate ();
    }
    while ((key = getwchar()) != MKEY_ENTER || selected_field != 4);

    /* Записать данные в структуру */
    date->D = tmp_day;
    date->M = tmp_month;
    date->Y = tmp_year;

    /* Удаление всех созданных панелей и окон */
    del_panel (inner_panel_text);
    del_panel (popup_panel);
    delwin (inner_win_text);
    delwin (popup_win);

    /* Установить прошлое значение видимости курсора */
    curs_set(last_curs_state);

    return;
}