/* @header
 * func_800C38FC
 * VRAM 0x800C38FC | ROM 0xB6D9C | size 0x17C
 * asm: asm/nonmatchings/code_800BBA00/func_800C38FC.s
 */
#include "common.h"

typedef struct {
    u8 pad0[0x10];
    f32 pos[3];
    u8 pad1C[0x8];
} Nw2Body38FC;

typedef struct {
    s8 id;
    u8 pad1;
    s16 f2;
    u8 pad4[0x1C];
    u64 flags;
    u8 pad28[8];
    s32 f30;
    u8 pad34[0x28];
    Nw2Body38FC body;
    u8 pad80[0x351 - 0x80];
    s8 f351;
    u8 pad352[0x3B0 - 0x352];
} Nw2Plr38FC;

extern Nw2Plr38FC D_800F9D10[];
s8 func_800D3B24(void *, void *, f32, s32);
void func_800A6CDC(void *, s32);

void func_800C38FC(Nw2Plr38FC *arg0, s32 arg1, u64 mask, s32 value) {
    s16 i;
    s32 result = value | 0x80000000;

    for (i = 0; i < 4; i++) {
        if (i == arg0->id) continue;
        if (D_800F9D10[i].f2 == -1) continue;
        if ((D_800F9D10[i].flags & 0x80) && !(D_800F9D10[i].flags & mask)) {
            if (func_800D3B24(arg0->body.pad0 + 0x10 - 0x10 + 0x10, D_800F9D10[i].body.pos, 66.0f, 0)) {
                func_800A6CDC(&D_800F9D10[i], 0x62);
                D_800F9D10[i].f30 = result;
                D_800F9D10[i].f351 = arg0->id;
            }
        }
    }
}
