/* @header
 * lookupResourceDescriptor  (originally func_800035B4)
 * VRAM 0x800035B4 | ROM 0x41B4 | size 0xD0
 * asm: asm/nonmatchings/main/func_800035B4.s
 */
#include "common.h"

typedef struct {
    u8 *volatile a;
    u8 *volatile b;
    s32 c;
    s32 d;
} IdInfo;

extern s32 *D_800482E0;
extern s32 *D_800482E4;
extern u8 D_000DAC50[];

/* Look up a resource descriptor for id (valid range 1..0x1DE9; anything else spins
 * forever). The two words of the D_800482E0 entry are offsets into the ROM base
 * D_000DAC50 with bit 0 as a flag (so the low bit is masked off); when that flag is set
 * the descriptor's length field holds (addrB - addrA), otherwise 0. The +0xC field comes
 * from D_800482E4. */
void lookupResourceDescriptor(IdInfo *out, u16 id) {
    IdInfo rec;
    s32 idx;
    s32 w0;
    s32 w1;
    u8 *addrA;
    u8 *addrB;
    s32 *table0;

    if (id < 1 || id >= 0x1DEA) {
        for (;;) {
        }
    }
    id = id - 1;
    idx = id & 0xFFFF;
    table0 = D_800482E0 + idx;
    w0 = *table0;
    rec.a = (u8 *)w0;
    w1 = *(table0 + 1);
    addrA = (u8 *)((w0 & ~1) + (s32)D_000DAC50);
    rec.a = (u8 *)(w0 & ~1);
    rec.a = addrA;
    rec.b = (u8 *)w1;
    addrB = (u8 *)((w1 & ~1) + (s32)D_000DAC50);
    rec.b = (u8 *)(w1 & ~1);
    rec.b = addrB;
    rec.c = D_800482E4[idx];
    rec.d = (w0 & 1) ? (s32)(addrB - addrA) : 0;
    *out = rec;
}
