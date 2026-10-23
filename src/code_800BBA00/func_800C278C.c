#include "common.h"

extern u8 D_8007EF30[];
extern u8 D_800FABE8[], D_800FABEC[], D_800FABEE[];
extern s16 D_800EB4D0[];
void func_800D2638(void *, u16, f32);
s32 func_800D2B64(void *, f32, u16, s32);

s32 func_800C2830(void *arg0) {
    s32 result = 1;
    if (!(*(u64 *)((u8 *)arg0 + 0x20) & 3)) {
        result = (*(u16 *)(D_8007EF30 + 0x170) & 0x404) == 0;
    }
    return result;
}

/* Begin an action on `entity`: choose a channel mask (0x300, or 0xC00 when the
 * entity's +0x3E bit0 is set), open it at position 4.0 via func_800D2638 with
 * the "active" flag 0x40 set on the +0x20 u64, then run func_800D2B64 with
 * `pitch` and volume 0xFFFFE and restore the previous flags. */
void func_800C278C(void *entity, f32 pitch) {
    u16 mask = 0x300;
    u64 flags;
    if (*(u16 *)((u8 *)entity + 0x3E) & 1) mask = 0xC00;
    func_800D2638(entity, mask, 4.0f);
    flags = *(u64 *)((u8 *)entity + 0x20);
    *(u64 *)((u8 *)entity + 0x20) = flags | 0x40;
    func_800D2B64(entity, pitch, mask, 0xFFFFE);
    *(u64 *)((u8 *)entity + 0x20) = flags;
}

void func_800C2B20(s8 arg0) {
    s16 i;
    for (i = 0; i < 8; i++) {
        *(f32 *)(D_800FABE8 + arg0 * 64 + i * 8) = 150.0f;
        *(s16 *)(D_800FABEC + arg0 * 64 + i * 8) = 15;
        *(s16 *)(D_800FABEE + arg0 * 64 + i * 8) = 0;
    }
}

void updateEntityStatus43Timer(void *arg0, s16 arg1) {
    s16 *timer;
    s16 value;
    switch (arg1) {
    case 0:
        D_800EB4D0[*(s8 *)arg0] = 60;
        return;
    case 1:
        timer = &D_800EB4D0[*(s8 *)arg0];
        value = *timer;
        if (value <= 0) {
            *((s8 *)arg0 + 0x43) = 0;
            return;
        }
        *timer = value - 1;
        return;
    }
}
