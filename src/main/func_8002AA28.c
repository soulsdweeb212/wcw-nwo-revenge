/* @header
 * func_8002AA28
 * VRAM 0x8002AA28 | ROM 0x2B628 | size 0xD4
 * asm: asm/nonmatchings/main/func_8002AA28.s
 */
#include "common.h"

extern void *D_80064AD0;
extern void *D_80064AD4;
extern void *D_8007FC34;
extern s32 D_8007FC38;
extern void *D_8007FC3C;

#ifdef TARGET_PC
/* PC: the loader writes the 16-byte ResDesc of port.h. With two pointers, the N64 layout below would be 24 bytes on a
 * 64-bit PC, and .size would be read from the wrong place. */
typedef ResDesc Nw2ResDesc;
#else
typedef struct {
    void *p0;
    void *p1;
    s32 size;
    s32 len;
} Nw2ResDesc;
#endif

#ifdef TARGET_PC
/* PC: an entry of the resource-name cache (Nw2ResourceEntryHashed, common.h) is 0x20 bytes, because its key, f0 here,
 * is as wide as a pointer (port.h's ResKey). This view follows it, as the assert checks. */
typedef struct {
    ResKey f0;
    u8 pad[sizeof(Nw2ResourceEntryHashed) - sizeof(ResKey)];
} Nw2Rec18;
_Static_assert(sizeof(Nw2Rec18) == sizeof(Nw2ResourceEntryHashed) && offsetof(Nw2ResourceEntryHashed, key) == 0,
               "Nw2Rec18 must follow the PC layout of the resource-name cache's entries");
#else
typedef struct {
    s32 f0;
    u8 pad[0x14];
} Nw2Rec18;
#endif

#ifndef TARGET_PC /* on PC, port.h declares the loader functions */
void lookupResourceDescriptor(void *, s32);
#endif
void *allocateHeap(s32);
#ifndef TARGET_PC /* on PC, port.h declares the loader functions */
void *func_80003684(void *, s32, void *);
#endif

void func_8002AA28(void)
{
    Nw2ResDesc desc;
    Nw2ResDesc out1;
    Nw2ResDesc out2;
    void *p;
    u8 *base;
    Nw2Rec18 *rp;
    Nw2KeyedBufferEntry *e;
    s32 i;

    lookupResourceDescriptor(&desc, 1);
    p = allocateHeap(desc.size);
    D_80064AD0 = p;
    func_80003684(&out1, 1, p);

    lookupResourceDescriptor(&desc, 2);
    p = allocateHeap(desc.size);
    D_80064AD4 = p;
    func_80003684(&out2, 2, p);

#ifdef TARGET_PC
    /* PC: room for the 128 entries at their PC size (0x18 bytes each on N64), and rp starts at the last of them. */
    base = allocateHeap(128 * sizeof(Nw2Rec18));
    D_8007FC34 = base;
    i = 0x7F;
    rp = (Nw2Rec18 *)base + 0x7F;
#else
    base = allocateHeap(0xC00);
    D_8007FC34 = base;
    i = 0x7F;
    rp = (Nw2Rec18 *)(base + 0xBE8);
#endif
    do {
        rp->f0 = 0;
        i--;
        rp--;
    } while (i >= 0);

    e = allocateHeap(0xB40);
    D_8007FC3C = e;
    i = 0;
    do {
        e[i].key0 = 0;
        e[i].key1 = 0;
        i++;
    } while (i < 0x28);

    D_8007FC38 = 0;
}
