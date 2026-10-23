#include "common.h"

/* Appends the NUL-terminated string arg1 to the end of arg0. */
u8 *func_80028B80(u8 *arg0, u8 *arg1) {
    u8 *p;

    if (*arg0 != 0) {
        return func_80028B80(arg0 + 1, arg1);
    }
    p = arg0;
loop:
    *p = *arg1;
    if (*arg1 == 0) {
        return arg0;
    }
    arg1++;
    p++;
    goto loop;
}
