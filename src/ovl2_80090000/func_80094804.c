/* @header
 * func_80094804
 * VRAM 0x80094804 | ROM 0x87CA4 | size 0xB0
 * asm: asm/nonmatchings/ovl2_80090000/func_80094804.s
 */
#include "common.h"

typedef struct {
    u32 *p;
    s32 n;
} Ptr8;

typedef struct {
    u8 id;
    u8 pad[0xB];
} Rec0C;

extern Rec0C D_800E9D40[];
extern Ptr8 D_800EA0E0[];
extern Ptr8 D_800EA100[];
void lookupResourceDescriptor(u32 *, u32);

void func_80094804(s32 arg0) {
    u32 desc[4];
    u32 *dst;
    u32 *src;
    u32 i;
    u8 n = arg0;

    lookupResourceDescriptor(desc, 0x27E);
    desc[2] -= 8;
    dst = D_800EA0E0[n].p + 2;
    src = D_800EA100[D_800E9D40[n].id >> 1].p + 2;
    for (i = 0; i < desc[2] / 4; i++) {
        *dst++ = *src++;
    }
}
