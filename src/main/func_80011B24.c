/* @header
 * func_80011B24
 * VRAM 0x80011B24 | ROM 0x12724 | size 0x90
 * asm: asm/nonmatchings/main/func_80011B24.s
 */
#include "common.h"

extern u8 D_80059DA8[];

extern u8 D_80059D90[];

void releaseHeapBlock(s32);

#ifndef TARGET_PC /* on PC, D_8005AAAD is the type field of D_8005AAA0[n] (port_decls.h); the label has no PC symbol */
extern u8 D_8005AAAD[];
#endif
extern u8 D_80036DFC[];
extern u8 D_80036E04[];
extern u8 D_80036E0C[];

/* Builds a 16-bit RGBA5551 colour for vertex arg0: looks up its palette index
 * (clamped at 5) and scales the three channel tables, always setting the
 * visibility bit. */
s32 func_80011B24(s32 arg0) {
    s32 idx;
    u32 a;
    u32 b;
    u32 c;
    u32 r;

#ifdef TARGET_PC
    idx = D_8005AAA0[(s16)arg0].type; /* PC: the animation-command record's type by field name */
#else
    idx = D_8005AAAD[((s16)arg0) << 4];
#endif
    if (idx == 6) {
        idx = 5;
    }
    a = D_80036DFC[idx] >> 1;
    if (a != 0) {
        a += 0x40;
    }
    b = D_80036E04[idx] >> 1;
    if (b != 0) {
        b += 0x40;
    }
    c = D_80036E0C[idx] >> 1;
    if (c != 0) {
        c += 0x40;
    }
    r = (a & 0xF8) << 8;
    r |= 1;
    r |= (b & 0xF8) << 3;
    r |= (c & 0xF8) >> 2;
    return r;
}
