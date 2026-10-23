#include "common.h"

s32 func_8001613C(s32);

/* Enable/disable audio output from whether arg0 is zero. */
void func_8000333C(s32 arg0) {
    func_8001613C((arg0 << 0x10) == 0);
}
