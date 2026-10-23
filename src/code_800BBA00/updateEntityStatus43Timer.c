#include "common.h"

extern u8 D_8007EF30[];
extern u8 D_800FABE8[], D_800FABEC[], D_800FABEE[];
extern s16 D_800EB4D0[];
void func_800D2638(void *, u16, f32);
s32 func_800D2B64(void *, f32, u16, s32);

/* True when the entity's +0x20 flags have no low 2 bits set and the global
 * 0x170 bits 0x404 are clear. */
s32 func_800C2830(void *arg0) {
    s32 result = 1;
    if (!(*(u64 *)((u8 *)arg0 + 0x20) & 3)) {
        result = (*(u16 *)(D_8007EF30 + 0x170) & 0x404) == 0;
    }
    return result;
}

/* Plays the entity's entry animation using the 0x300/0xC00 mask from its +0x3E
 * bit 0, temporarily setting the +0x20 flags bit 0x40. */
void func_800C278C(void *arg0, f32 arg1) {
    u16 mask = 0x300;
    u64 flags;
    if (*(u16 *)((u8 *)arg0 + 0x3E) & 1) mask = 0xC00;
    func_800D2638(arg0, mask, 4.0f);
    flags = *(u64 *)((u8 *)arg0 + 0x20);
    *(u64 *)((u8 *)arg0 + 0x20) = flags | 0x40;
    func_800D2B64(arg0, arg1, mask, 0xFFFFE);
    *(u64 *)((u8 *)arg0 + 0x20) = flags;
}

/* Initialises the 8 animation frames of entity-type arg0 to 150.0f / 15 / 0. */
void func_800C2B20(s8 arg0) {
    s16 i;
    for (i = 0; i < 8; i++) {
        *(f32 *)(D_800FABE8 + arg0 * 64 + i * 8) = 150.0f;
        *(s16 *)(D_800FABEC + arg0 * 64 + i * 8) = 15;
        *(s16 *)(D_800FABEE + arg0 * 64 + i * 8) = 0;
    }
}

/* Per-entity timer for entity status 0x43: arg1==0 reloads 60, arg1==1 counts
 * down and clears the +0x43 status when it reaches zero. */
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
