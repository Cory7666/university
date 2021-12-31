#ifndef ___FORMS___H
#define ___FORMS___H

#include <wchar.h>
#include <wctype.h>

#include <ncursesw/ncurses.h>

#include "cmp_funcs.h"
#include "checker.h"

/*
    Нарисовать поле для формы.
*/
void tui_draw_form_field (WINDOW *, int, int, const wchar_t *, const wchar_t *, int);

#endif //! ___FORMS___H