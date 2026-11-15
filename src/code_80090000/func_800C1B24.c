/* @header
 * func_800C1B24
 * VRAM 0x800C1B24 | ROM 0x6E294 | size 0x128
 * asm: asm/nonmatchings/code_80090000/func_800C1B24.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: the scenes D_800D4ED8 have their PC layout (common.h's Nw2MenuScene, 0x30 bytes); H is a scene, by its f8 (a)
 * and fA (b). */
typedef struct { u8 pad[8]; s16 a; s16 b; u8 padC[4]; IdOrAddr cast[4]; } H;
_Static_assert(offsetof(H, a) == offsetof(Nw2MenuScene, f8) && offsetof(H, b) == offsetof(Nw2MenuScene, fA) &&
                   offsetof(H, cast) == offsetof(Nw2MenuScene, cast) && sizeof(H) == sizeof(Nw2MenuScene),
               "H follows common.h's Nw2MenuScene");
#else
typedef struct { u8 pad[8]; s16 a; s16 b; } H;
#endif
extern H D_800D4ED8;
extern s32 D_800DF2FC, D_800E74C8, D_800DF3A0, D_800DF30C, D_800DF300, D_800DF304, D_800DF318, D_800DF314, D_800DF310, D_800DF308;
extern H *D_800DF31C;
extern u8 D_8007E228[];
extern s32 D_80038AA4, D_800E79C4, D_800E9F70, D_800E74E8, D_800EA0B4, D_800DF3A8, D_800DF3AC;
#ifdef TARGET_PC
/* PC: D_800DF224 is +4 of the scene object D_800DF220 (its first child), which has no PC symbol: the object keeps its
 * N64 layout (common.h's Nw2SceneObj), so the PC sets the field by name, as a handle. allocateHeap is declared with
 * its definition's type. */
extern void *D_800DF210;
void *allocateHeap(u32);
#else
extern void *D_800DF210, *D_800DF224;
#endif
extern s32 D_800DF218;
extern u8 D_800DF220[];
#ifndef TARGET_PC /* on PC, declared above */
void *allocateHeap(s32);
#endif
void initializeTransformNode(void *, s32, f32, f32, f32);
void *initPairedTransformNodes(void *, void *);
void func_800B807C(s32, s32, s32);

/* z is a one-element array (a one-field struct or an s32/f32 union works too): it gets an SImode
   pseudo, so the arguments are (subreg:SF ...), not REGs. calls.c then does not copy them into an SF
   pseudo, and CSE replaces the folded 0.0f (cost 12) with the cheaper stack-argument slot it just
   stored (cost 4): `sw zero,16(sp); lw a2,16(sp); move a3,a2`. A plain f32 or 0.0f literal gives
   mtc1/mfc1. */
void func_800C1B24(void) {
    f32 z[1];

    D_800DF2FC = 0;
    D_800E74C8 = 0xFF;
    D_800DF218 = 0;
#ifdef TARGET_PC
    /* PC: the display-list buffer holds 0x2000 commands, as on the N64 (0x10000 bytes of 8-byte commands): two halves
     * of 0x1000, one per frame (func_800C1C70), of port.h's 16-byte Gfx. */
    D_800DF210 = allocateHeap(0x2000 * sizeof(Gfx));
#else
    D_800DF210 = allocateHeap(0x10000);
#endif
    z[0] = 0.0f;
    initializeTransformNode(D_800DF220, 0, z[0], z[0], z[0]);
    /* Same address as D_800DF220, spelled as an offset from D_800DF210 so the two call arguments are
       different RTL and CSE does not keep the address in s0 across the first call. */
#ifdef TARGET_PC
    /* PC: D_800DF220 by its own name (on PC it does not follow D_800DF210 at +0x10), and the pair as its child (see
     * above). */
    ((Nw2SceneObj *)D_800DF220)->child = PTR_TO_SLOT(initPairedTransformNodes(D_800DF220, 0));
#else
    D_800DF224 = initPairedTransformNodes((u8 *)&D_800DF210 + 0x10, 0);
#endif
    D_800DF3A0 = -1;
    D_800DF30C = -1;
    D_800DF300 = 0;
    D_800DF304 = 0;
    D_800DF318 = 0;
    D_800DF314 = 0;
    D_800DF310 = 0;
    D_800DF308 = 0;
    D_800DF31C = &D_800D4ED8;
    *(s32 *)(D_8007E228 + 0x60C) = 0;
    D_80038AA4 = 0;
    D_800E79C4 = D_800D4ED8.a;
    D_800E9F70 = D_800D4ED8.b;
    func_800B807C(0x80, 0x80, D_800D4ED8.b);
    D_800E74E8 = 1;
    D_800EA0B4 = 0;
    D_800DF3A8 = 1;
    D_800DF3AC = 0;
}
