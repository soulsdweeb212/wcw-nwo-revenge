#include "common.h"

s32 initStatePools17B40(s32);
extern s32 D_80036F50;
extern s32 D_80036F54;

/* Register the root object arg0 and initialize the shared state pools only once. */
void func_80017510(s32 arg0, s32 arg1) {
    if (D_80036F50 == 0) {
        D_80036F50 = arg0;
        if (D_80036F54 == 0) {
            D_80036F54 = arg0;
            initStatePools17B40(arg1);
        }
    }
}
