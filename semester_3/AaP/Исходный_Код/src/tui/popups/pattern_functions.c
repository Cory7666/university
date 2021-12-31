#include "__popups__.h"



void tui_draw_popup_header (WINDOW * win, const wchar_t * popup_name)
{
    box (win, 0, 0);

    mvwaddstr (win, 2, 0, "├");
    for (size_t i = 0; i < getmaxx(win) - 2; i++)
        waddstr(win, "╌");
    waddstr(win, "┤");

    mvwprintw(win, 1, (getmaxx(win) - getmin(wcslen(popup_name), getmaxx(win) - 2)) / 2, "%ls", popup_name);
}

int get_message_lines_count (const wchar_t * string, const int max_width)
{
    wint_t * curr_symbol = string;  // Символ строки
    int lines_cnt = 0,              // Итоговое количество строк
        char_on_line_counter = 0;   // Количество символов на строке

    for (; (*curr_symbol != L'\0'); curr_symbol++)
    {
        switch (*curr_symbol)
        {
            case L'\0': break;

            case L'\n':
                char_on_line_counter = 0;
                lines_cnt++;
                break;
            
            default:
                char_on_line_counter++;
                if (char_on_line_counter >= max_width)
                {
                    lines_cnt += 1;
                    char_on_line_counter = 0;
                }
                break;
        }
    }

    if (char_on_line_counter % max_width) lines_cnt++;

    return lines_cnt;
}