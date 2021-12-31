#include "tui.h"



int tui_get_menu_item_count (const menu_t menu)
{
    int counter = -1;

    if (menu && menu[0]) for (counter = 0; menu[counter]; counter++);

    return counter;
}

void tui_draw_vmenu (WINDOW * win, const int y, const int x, const int offset, const menu_t menu, const int selected_item_pos)
{
    if (!win || !menu) return;

    for (int item_index = 0; menu[item_index]; item_index++)
    {
        if (item_index + 1 == selected_item_pos) wattron(win, TUI_HIGHLIGHT_ITEM_STYLE);
        mvwaddwstr(win, y + item_index * (offset + 1), x, menu[item_index]);
        if (item_index + 1 == selected_item_pos) wattroff(win, TUI_HIGHLIGHT_ITEM_STYLE);
    }
}