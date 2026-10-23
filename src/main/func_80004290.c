#include "common.h"

s32 func_80022FD0(s32 *);
extern s32 D_800482F0;
extern s8 D_800484F2;

/* Read the controllers using the D_800482F0 work area as the message queue,
 * then clear the D_800484F2 input flag. */
void func_80004290(void) {
    func_80022FD0(&D_800482F0);
    D_800484F2 = 0;
}
