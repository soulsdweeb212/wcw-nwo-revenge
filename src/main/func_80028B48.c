#include "common.h"

extern u8 D_80038E4C[];

u8 *func_80028B48(s32 arg0) {
    return &D_80038E4C[arg0 & 0xF];
}
