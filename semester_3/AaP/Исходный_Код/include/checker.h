#ifndef _VERIFICATORS_H
#define _VERIFICATORS_H

#include <wchar.h>
#include <wctype.h>

typedef int checker_mode_t;

#define VMASK_LOWER_CHARS  (0b0000001)
#define VMASK_UPPER_CHARS  (0b0000010)
#define VMASK_ANY_CHAR     (VMASK_LOWER_CHARS | VMASK_UPPER_CHARS)
#define VMASK_DIGITS       (0b0001000)
#define VMASK_SPACES       (0b0010000)
#define VMASK_PUNCTS       (0b0100000)
#define VMASK_ADD_FS_CHARS (0b1000000)

/*
    Проверить соответствие символа маске.
    Вернуть 0, если символ не соответствует маске.
*/
int check_wchar (const wint_t, const checker_mode_t);

#endif //! _VERIFICATORS_H