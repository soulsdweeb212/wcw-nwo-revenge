#include "common.h"

typedef struct {
    s32 v;
} Nw2WordParam;

extern u8 func_8002670C[];
extern s32 *D_8003724C;
s32 nw2DisableInterrupts(void);
void nw2RestoreInterrupts(s32);

void func_8001C8C0(u8 *o, s32 a1, s32 a2, s32 a3, s32 a4, Nw2WordParam a5) {
    s32 status;
    s32 prev;
    s64 entry;
    s64 v;
    v = (s64)a4 - 0x10;
    entry = a3;
    *(s64 *)(o + 0x100) = (s64)(func_8002670C + 0x17C);
    *(s32 *)(o + 0x118) = 0xFF03;
    *(s32 *)(o + 0x128) = 0x3F;
    *(s32 *)(o + 0x14) = a1;
    *(s32 *)(o + 0) = 0;
    *(s32 *)(o + 8) = 0;
    *(s32 *)(o + 0x11C) = a2;
    *(s64 *)(o + 0x38) = entry;
    *(s32 *)(o + 0x12C) = 0x01000800;
    *(s32 *)(o + 0x18) = 0;
    *(s16 *)(o + 0x10) = 1;
    *(s16 *)(o + 0x12) = 0;
    *(s32 *)(o + 4) = *(s32 *)&a5;
    *(s64 *)(o + 0xF0) = v;
    status = nw2DisableInterrupts();
    prev = (s32)D_8003724C;
    D_8003724C = o;
    *(s32 *)(o + 0xC) = prev;
    nw2RestoreInterrupts(status);
}
