/* @header
 * func_800982C0
 * VRAM 0x800982C0 | ROM 0x44A30 | size 0x30C
 * asm: asm/nonmatchings/code_80090000/func_800982C0.s
 */
#include "common.h"

typedef struct {
    u8 pad0[4];
    void *f4;
    u8 pad8[4];
    s16 fC;
    s16 fE;
    s16 f10;
} Nw2PaletteRec;
#ifdef TARGET_PC
/* PC: the record is the entry of the resource-name cache that func_800B600C returns for a picture (func_8002A2FC made
 * it): f4 is its allocation, the picture's texture, and fC, fE and f10 are the 16-bit sizes at +4, +6 and +8 of
 * reserved. On PC the entry is common.h's Nw2ResourceEntryHashed; with the 8-byte pointer f4 at +8, this view already
 * places its fields there, as the assert checks. */
_Static_assert(offsetof(Nw2PaletteRec, f4) == offsetof(Nw2ResourceEntryHashed, allocation) &&
                   offsetof(Nw2PaletteRec, fC) == offsetof(Nw2ResourceEntryHashed, reserved) + 4 &&
                   offsetof(Nw2PaletteRec, fE) == offsetof(Nw2ResourceEntryHashed, reserved) + 6 &&
                   offsetof(Nw2PaletteRec, f10) == offsetof(Nw2ResourceEntryHashed, reserved) + 8,
               "Nw2PaletteRec must follow Nw2ResourceEntryHashed");
#endif

typedef union {
    Nw2GfxCommand *p;
    f64 d;
} Nw2Out;

void *func_800B600C(s32, s32);
#ifdef TARGET_PC
/* PC: the definitions' types: appendPaletteSetupDisplayList and buildTiledTextureDisplayList (its PC definition) write
 * port.h's 16-byte Gfx, and the latter takes the texture as a pointer. The display lists at 0x800C95F0, 0x800C95B8 and
 * 0x800C9620 by their own addresses (port.h's DL_ADDR turns them into command words; D_C95F0 and the others are their
 * N64 physical addresses, link constants). */
void appendPaletteSetupDisplayList(Gfx **);
void buildTiledTextureDisplayList(Nw2RdpCmd **, void *, s32, s32, s32, s32, s32, s32, s32, s32);
extern u8 D_800C95F0[], D_800C95B8[], D_800C9620[];
#else
void appendPaletteSetupDisplayList(s32 *);
void buildTiledTextureDisplayList(u32 **, void *, s32, s32, s32, s32, s32, s32, s32, s32);
extern u32 D_C95F0;
extern u32 D_C95B8;
#endif

#ifdef TARGET_PC
/* PC: a command is port.h's 16-byte Gfx (common.h's Nw2GfxCommand is the N64's 8 bytes), so the list is a list of Gfx,
 * and the display lists' addresses go into the commands as the whole pointers (port.h's DL_ADDR). The N64 keeps the
 * cursor for buildTiledTextureDisplayList in a union with an f64; on PC it is a Gfx pointer of its own. */
void func_800982C0(Gfx **arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6)
{
    Nw2PaletteRec *rec;
    Gfx *g;
    Gfx *out;
    s32 temp_a3, temp_t5, temp_a0;
    void *temp_a1;
    s32 t0, a2, t1, t2, t3, t4, t6;

    g = *arg0;
    rec = func_800B600C(arg1, (arg5 & 0xFFFF) | 8);
    if (rec != NULL) {
        { Gfx *q = g++; q->w0 = 0xDE000000; q->w1 = DL_ADDR(D_800C95F0); }
        { Gfx *q = g++; q->w0 = 0xDE000000; q->w1 = DL_ADDR(D_800C95B8); }
        appendPaletteSetupDisplayList(&g);
        t6 = arg3;
        out = g;
        temp_a3 = rec->f10;
        temp_a1 = rec->f4;
        temp_t5 = rec->fC;
        temp_a0 = rec->fE;
        if (arg5 & 0x8000) {
            t0 = (temp_a3 * 0x1E0) / 320;
        } else {
            t0 = temp_a3;
        }
        a2 = temp_a0 * 2;
        if (arg6 & 0x10) {
            t0 *= 2;
        } else {
            a2 = temp_a0;
        }
        if (t0 >= 0x196) {
            a2 = (a2 * 0x195) / t0;
            t0 = 0x195;
        }
        if (arg6 & 0x200) {
            t3 = (temp_a0 * arg4) / 255;
            t2 = (a2 * t3) / temp_a0;
            t1 = temp_t5;
            t4 = t0;
            t6 += a2 - t2;
        } else {
            t1 = (temp_t5 * arg4) / 255;
            t3 = temp_a0;
            t2 = a2;
            t4 = (t0 * t1) / temp_t5;
        }
        if (t1 == 0 || t3 == 0 || t4 == 0 || t2 == 0) goto Ldl;
        buildTiledTextureDisplayList(&out, temp_a1, 0, arg2 - (t0 / 2), t6 - (a2 / 2), t1, t3, t4, t2, temp_t5);
        g = out;
Ldl:
        { Gfx *q = g++; q->w0 = 0xDE000000; q->w1 = DL_ADDR(D_800C9620); }
        *arg0 = g;
    }
}
#else
void func_800982C0(u32 **arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6)
{
    Nw2PaletteRec *rec;
    Nw2GfxCommand *g;
    Nw2Out out;
    Nw2GfxCommand **pdl;
    s32 temp_a3, temp_t5, temp_a0;
    void *temp_a1;
    s32 t0, a2, t1, t2, t3, t4, t6;

    g = (Nw2GfxCommand *)*arg0;
    rec = func_800B600C(arg1, (arg5 & 0xFFFF) | 8);
    if (rec != NULL) {
        { Nw2GfxCommand *q = g++; q->w0 = 0xDE000000; q->w1 = (u32)&D_C95F0; }
        { Nw2GfxCommand *q = g++; q->w0 = 0xDE000000; q->w1 = (u32)&D_C95B8; }
        appendPaletteSetupDisplayList((s32 *)&g);
        t6 = arg3;
        out.p = g;
        pdl = &g;
        temp_a3 = rec->f10;
        temp_a1 = rec->f4;
        temp_t5 = rec->fC;
        temp_a0 = rec->fE;
        if (arg5 & 0x8000) {
            t0 = (temp_a3 * 0x1E0) / 320;
        } else {
            t0 = temp_a3;
        }
        a2 = temp_a0 * 2;
        if (arg6 & 0x10) {
            t0 *= 2;
        } else {
            a2 = temp_a0;
        }
        if (t0 >= 0x196) {
            a2 = (a2 * 0x195) / t0;
            t0 = 0x195;
        }
        if (arg6 & 0x200) {
            t3 = (temp_a0 * arg4) / 255;
            t2 = (a2 * t3) / temp_a0;
            t1 = temp_t5;
            t4 = t0;
            t6 += a2 - t2;
        } else {
            t1 = (temp_t5 * arg4) / 255;
            t3 = temp_a0;
            t2 = a2;
            t4 = (t0 * t1) / temp_t5;
        }
        if (t1 == 0 || t3 == 0 || t4 == 0 || t2 == 0) goto Ldl;
        buildTiledTextureDisplayList((u32 **)&out, temp_a1, 0, arg2 - (t0 / 2), t6 - (a2 / 2), t1, t3, t4, t2, temp_t5);
        *pdl = out.p;
Ldl:
        { Nw2GfxCommand *q = g++; q->w0 = 0xDE000000; q->w1 = (u32)&D_C9620; }
        *arg0 = (u32 *)g;
    }
}
#endif
