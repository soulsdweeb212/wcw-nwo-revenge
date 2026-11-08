/* @header
 * lookupResourceDescriptor  (originally func_800035B4)
 * VRAM 0x800035B4 | ROM 0x41B4 | size 0xD0
 * asm: asm/nonmatchings/main/lookupResourceDescriptor.s
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
 * the descriptor's length field (+0xC) holds (addrB - addrA), otherwise 0. The +0x8
 * field (the size once loaded) comes from D_800482E4. */
#ifdef TARGET_PC
/* PC: writes the 16-byte ResDesc of port.h, with the two ROM addresses as RomAddr instead of pointers, so the callers'
 * 16-byte buffers still fit on a 64-bit PC. D_800482E0 holds the table exactly as it is in ROM, so its words are read
 * big-endian. An invalid id stops the program with a message instead of hanging. */
void lookupResourceDescriptor(void *out, u32 id) {
    ResDesc rec;
    u32 idx, w0, w1;
    if ((u16)id < 1 || (u16)id >= 0x1DEA) {
        port_fatal("lookupResourceDescriptor: id 0x%X out of range (the N64 spins forever)", (u16)id);
    }
    idx = ((u16)id - 1) & 0xFFFF;
    w0 = READ_BE32(D_800482E0 + idx);
    w1 = READ_BE32(D_800482E0 + idx + 1);
    rec.start = (w0 & ~1u) + ROM_RES_BASE;
    rec.end = (w1 & ~1u) + ROM_RES_BASE;
    rec.size = D_800482E4[idx];
    rec.packed = (w0 & 1) ? (s32)(rec.end - rec.start) : 0;
    *(ResDesc *)out = rec;
}
#else
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
#endif
