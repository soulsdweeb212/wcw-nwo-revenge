#include "common.h"

extern u8 D_80038E4C[];

/* Recursive string copy (including the terminating NUL). */
u8 *func_80028B5C(u8 *arg0, u8 *arg1) {
    *arg0 = *arg1;
    if (*arg1 == 0) {
        return arg0;
    }
    return func_80028B5C(arg0 + 1, arg1 + 1);
}
