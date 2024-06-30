#include "__forms__.h"

void tui_draw_form_field (WINDOW * win, int y, int x, const wchar_t * placeholder, const wchar_t * value, int width)
{
    const int value_len       = (int) wcslen (value),
              placeholder_len = (int) wcslen (placeholder);
    size_t curr_width = (value_len) ? (value_len) : (placeholder_len);

    wmove (win, y, x);
    wattron (win, A_UNDERLINE);
    // Если value не содержит текста, ...
    if (value_len < 1)
    {
        // ... то записать placeholder в форму, ...
        wattron(win, A_ITALIC);
        waddnwstr(win, placeholder, width);
        wattroff(win, A_ITALIC);
    }
    else
    {
        // ... иначе вставить в поле value
        wattron(win, A_BOLD);
        waddwstr(win, value);
        wattroff(win, A_BOLD);
    }

    wattroff(win, A_UNDERLINE);

    for (; curr_width < width; curr_width++) waddwstr (win, L"_");

}