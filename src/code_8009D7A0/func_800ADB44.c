#include "common.h"

typedef struct {
    u8 pad0[0x10];
    s16 f10;
    s16 pad12;
    s16 f14;
    s16 pad16;
    s16 f18;
    u8 pad1A[6];
    u64 f20;
} Nw2AdbEntity;

typedef struct {
    u8 pad0[0x16];
    s16 f16;
    s16 f18;
    s16 f1A;
    u8 pad1C[8];
    s16 f24;
    s16 f26;
    s16 f28;
    u8 pad2A[10];
    f32 f34;
    u8 pad38[4];
    f32 f3C;
    u8 pad40[0x1C];
    u32 f5C;
} Nw2AdbAction;

extern Nw2AdbAction *D_800FABD0;
extern Nw2AdbEntity *D_800F9B60;
extern Nw2AdbEntity *D_800FAF58;
f32 func_800ADE4C(f32, f32);

/* Prepares the D_800FABD0 action record parameters for the pair: computes scaled
 * ratios (func_800ADE4C) from the two entities' f10/f14/f18 and the record's f3C
 * into the record's f16/f24/f18/f26/f1A/f28/f34, clears the f5C flag field
 * 0x1FF0000, and sets a single relationship code into f5C from the pair of u64 f20
 * flags (0x40/0x80) of D_800FAF58 and D_800F9B60. */
void func_800ADB44(void) {
    register u32 bits;
    register f32 k;
    D_800FABD0->f16 = (s16)func_800ADE4C((f32)D_800FAF58->f10, 0.1f);
    D_800FABD0->f24 = (s16)func_800ADE4C((f32)D_800F9B60->f10, 0.3f);
    D_800FABD0->f18 = (s16)(s32)func_800ADE4C((f32)D_800FAF58->f14, 0.1f);
    k = 0.2f;
    D_800FABD0->f26 = (s16)func_800ADE4C((f32)D_800F9B60->f14, k);
    D_800FABD0->f1A = (s16)func_800ADE4C((f32)D_800FAF58->f18, 0.3f);
    D_800FABD0->f28 = (s16)func_800ADE4C((f32)D_800F9B60->f18, 0.3f);
    D_800FABD0->f34 = func_800ADE4C(D_800FABD0->f3C, k);
    D_800FABD0->f5C &= 0xFE00FFFF;
    if (D_800FAF58->f20 & 0x40ULL) {
        if (D_800F9B60->f20 & 0x40ULL) bits = 0x10000;
        else if (D_800F9B60->f20 & 0x80ULL) bits = 0x20000;
        else bits = 0x40000;
    } else if (D_800FAF58->f20 & 0x80ULL) {
        if (D_800F9B60->f20 & 0x40ULL) bits = 0x80000;
        else if (D_800F9B60->f20 & 0x80ULL) bits = 0x100000;
        else bits = 0x200000;
    } else {
        if (D_800F9B60->f20 & 0x40ULL) bits = 0x400000;
        else if (D_800F9B60->f20 & 0x80ULL) bits = 0x800000;
        else bits = 0x1000000;
    }
    D_800FABD0->f5C |= bits;
}
