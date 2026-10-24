#include "common.h"

typedef struct {
    s8 f0;
    u8 pad1;
    s16 f2;
    u8 pad4[0x1C];
    u64 f20;
    u8 pad28[0x16];
    s16 f3E;
    u8 pad40[0x2C];
    f32 f6C;
    f32 f70;
    f32 f74;
    u8 pad78[0x338];
} EntBED3C;

extern f64 D_800E5858;
extern f64 D_800E5860;
extern EntBED3C D_800F9D10[];

#define OBJ ((EntBED3C *)arg0)

s32 func_800BED3C(u8 *arg0, s32 arg1, u32 mask) {
    s32 a3 = 0;
    s16 i;
    s32 t0;
    s8 ok;

    for (i = 0; i < 4; i++) {
        t0 = 0;
        if (i != OBJ->f0 && i != *(s8 *)arg1 && D_800F9D10[i].f2 != -1 && (D_800F9D10[i].f20 & 0xC0)) {
            switch (OBJ->f3E) {
            case 0:
                if (D_800E5858 < D_800F9D10[i].f74) t0 = 1;
                break;
            case 1:
                if (D_800E5858 < D_800F9D10[i].f6C) t0 = 1;
                break;
            case 2:
                if (D_800F9D10[i].f74 < D_800E5860) t0 = 1;
                break;
            case 3:
                if (D_800F9D10[i].f6C < D_800E5860) t0 = 1;
                break;
            }
            ok = t0;
            if (ok) {
                switch (OBJ->f3E) {
                case 0:
                    if (D_800F9D10[i].f6C < OBJ->f6C) {
                        a3 |= 0x200;
                    } else {
                        a3 |= 0x100;
                    }
                    break;
                case 1:
                    if (D_800F9D10[i].f74 > OBJ->f74) {
                        a3 |= 0x800;
                    } else {
                        a3 |= 0x400;
                    }
                    break;
                case 2:
                    if (D_800F9D10[i].f6C > OBJ->f6C) {
                        a3 |= 0x100;
                    } else {
                        a3 |= 0x200;
                    }
                    break;
                case 3:
                    if (D_800F9D10[i].f74 < OBJ->f74) {
                        a3 |= 0x400;
                    } else {
                        a3 |= 0x800;
                    }
                    break;
                }
            }
        }
    }
    return a3 & 0xFFFF;
}
