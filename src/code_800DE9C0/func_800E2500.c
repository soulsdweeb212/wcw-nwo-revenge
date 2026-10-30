/* @header
 * func_800E2500
 * VRAM 0x800E2500 | ROM 0xD59A0 | size 0x268
 * asm: asm/nonmatchings/code_800DE9C0/func_800E2500.s
 */
#include "common.h"

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    s32 angle;
} Dir2500;
typedef struct {
    u8 b[0x5C];
} Rec7E010;
typedef struct {
    u8 f0;
    u8 f1;
    s8 f2;
    u8 f3;
    f32 f4;
    f32 f8;
    f32 fC;
    u8 pad10[0xC];
    s32 f1C;
    f32 f20;
    f32 f24;
    f32 f28;
    s32 f2C;
} Slot2500;
extern Rec7E010 D_8007E010[];
extern f64 D_800E7788;
extern f64 D_800E7790;
extern f64 D_800E7798;
extern f64 D_800E77A0;
extern Slot2500 D_800F98E0[];
extern s8 D_800F99A0[];
s8 func_800E2A18(void *);
s32 func_800D3E40(void *, f32 *, s32, f32 *);
void func_800D3890(void *, void *, void *);

static inline void setup2500(u8 *arg0, u8 *arg1, s8 id) {
    f32 sp10[3];
    f32 sp20[3];
    Dir2500 dr;

    D_800F98E0[id].f2 = -1;
    D_800F98E0[id].f1 = D_800F98E0[id].f0;
    sp10[0] = 0.0f;
    sp10[2] = 20.0f;
    func_800D3E40(arg0 + 0x9C, sp10, *(s32 *)(arg0 + 0x58), sp20);
    D_800F98E0[id].f4 = sp20[0];
    D_800F98E0[id].fC = sp20[2];
    D_800F98E0[id].f8 = (*(f32 *)(arg0 + 0xB0) + *(f32 *)(arg1 + 0xB0)) * D_800E7788;
    func_800D3890(arg0 + 0xAC, arg1 + 0xAC, &dr);
    D_800F98E0[id].f1C = dr.angle;
    D_800F98E0[id].f20 = dr.y * D_800E7790;
    D_800F98E0[id].f24 = -(dr.y * D_800E7798);
    D_800F98E0[id].f28 = (*(f32 *)(arg1 + 0xB0) - *(f32 *)(arg0 + 0xB0)) * D_800E77A0;
    D_800F98E0[id].f2C = 0;
    D_8007E010[id].b[0] = 0;
}

s32 func_800E2500(u8 *arg0, u8 *arg1, s16 arg2) {
    s8 id;
    s32 t;

    if (arg2 == 0) {
        if (arg0[0x374] != 0 && *(s16 *)(arg0 + 6) == arg0[0x375]) {
            id = func_800E2A18(arg0);
            if (id != -1) {
                D_800F99A0[*(s8 *)arg0] = id;
                if (arg0[0x374] == 1) {
                    D_800F98E0[id].f0 = 0xC;
                    D_800F98E0[id].f3 = 2;
                } else {
                    D_800F98E0[id].f0 = 0xB;
                    D_800F98E0[id].f3 = 4;
                }
                setup2500(arg0, arg1, id);
                return 1;
            }
        }
        return 0;
    }
    t = arg2;
    return ((t << 16) >> 16) - t;
}
