/* @header
 * func_800C15A0
 * VRAM 0x800C15A0 | ROM 0x6DD10 | size 0x3AC
 * asm: asm/nonmatchings/code_80090000/func_800C15A0.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: the scenes D_800D4ED8, the picture sets D_800D4930 and the camera tracks D_800D4E40 hold addresses, so they have
 * their PC layouts (common.h's Nw2MenuScene, Nw2MenuShot and Nw2MenuSceneTrack), and the code indexes them by those
 * sizes. Bg names a set's res and max f18 and f1A. D_800E763C is +0xE4 of the layers D_800E7558, which keep their N64
 * layout on PC (see func_800C0680), so it reaches the same bytes as on the N64. */
typedef Nw2MenuScene Arena;
typedef struct { void *pic[4]; u16 n[4]; u16 f18; u16 f1A; u8 f1C[4]; } Bg;
_Static_assert(offsetof(Bg, f18) == offsetof(Nw2MenuShot, res) && offsetof(Bg, f1A) == offsetof(Nw2MenuShot, max) &&
                   sizeof(Bg) == sizeof(Nw2MenuShot),
               "Bg follows common.h's Nw2MenuShot");
typedef Nw2MenuSceneTrack Mus;
#else
typedef struct { u16 f0; u16 flags; u16 f4; u16 f6; s16 f8; s16 fA; u8 padC[0x10]; } Arena;
typedef struct { u8 pad0[0x18]; u16 f18; u16 f1A; u8 pad1C[4]; } Bg;
typedef struct { u8 pad0[4]; s16 f4; u16 f6; } Mus;
#endif
typedef struct { s16 f0, f2, f4, f6; u8 pad8[0xEC - 8]; } Ch;

extern Arena D_800D4ED8[];
extern Bg D_800D4930[];
extern Mus D_800D4E40[];
extern Ch D_800E763C[];
extern s32 D_800EA0B4, D_800DF318, D_800DF314, D_800DF308;
extern Arena *D_800DF31C;
extern s32 D_800E79C4;
#ifdef TARGET_PC
/* PC: D_800E81F8 holds the address of a resource, which func_800B600C returns (port_decls.h: the picture's heap block
 * for a resource id, as b->f18 is), so it is a pointer. */
extern u8 *D_800E81F8;
extern s32 D_800E81E4, D_800D5F28;
#else
extern s32 D_800E81F8, D_800E81E4, D_800D5F28;
#endif
extern s32 D_800DF328, D_800DF324;
extern Mus *D_800DF320;
extern s32 D_800E9F70, D_800E7504, D_800E74E8, D_800D28F0, D_800E74C4, D_800E7CD8, D_800D5E80;
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800B600C, which returns an address, as above */
s32 func_800B600C(s32, s32);
#endif
void func_800C0680(s32);
s16 func_8000F6F4(void);
void func_8000F620(s32);
void func_800C1370(s32);
void func_8000DE40(s32);
void func_800B8050(void);
void func_800B807C(s32, s32);
void accumulateColorChannels(s32, s32, s32);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_80010200 */
void func_80010200(s32, s32, f32);
#endif

void func_800C15A0(s32 n) {
    Bg *b;
    Mus *m;
    s32 i, v, x;
    u16 f;

    D_800EA0B4 = 0;
    D_800DF318 = 0;
    D_800DF314 = 0;
    D_800DF308 = n;
    D_800DF31C = &D_800D4ED8[n];
    D_800E79C4 = D_800DF31C->f8;
    for (i = 0; i < 4; i++) {
        if (!(D_800DF31C->flags & 0x100)) {
            D_800E763C[i].f6 = 0;
        }
        D_800E763C[i].f4 = 0;
        D_800E763C[i].f2 = 0;
        D_800E763C[i].f0 = 0x100;
    }
    b = &D_800D4930[D_800E79C4];
    v = 0;
    if (b->f18) {
        D_800E81F8 = func_800B600C(b->f18, 0);
    } else {
        D_800E81F8 = 0;
    }
    if (v < 0) {
        v = 0;
    }
    if (v >= b->f1A) {
        v = b->f1A;
    }
    func_800C0680(v);
    D_800E81E4 = D_800E79C4;
    if (D_800DF31C->flags & 0x80) {
        D_800D5F28 = 0xA0;
    } else {
        D_800D5F28 = 0;
    }
    D_800DF328 = 0;
    D_800DF324 = 0;
    D_800DF320 = &D_800D4E40[D_800DF31C->fA];
    x = D_800DF320->f4;
    if (D_800E9F70 != x) {
        D_800E9F70 = x;
        if (x < 0) {
            if (!func_8000F6F4()) {
                func_8000F620(1);
            }
        } else if (func_8000F6F4()) {
            func_8000F620(0);
        }
        D_800E7504 = 0;
    }
    f = D_800DF320->f6;
    if (f & 1) {
        D_800E74E8 = 0x40;
        D_800D28F0 = 0xA;
    } else {
        if (f & 0x10) {
            D_800E74E8 = 0x200;
        } else {
            D_800E74E8 = 0x100;
        }
        D_800D28F0 = 0x21;
    }
    if (D_800DF320->f6 & 2) {
        D_800E74C4 = -1;
    } else {
        D_800E74C4 = 0;
    }
    m = D_800DF320;
    D_800E7CD8 = 0;
    if (m->f6 & 4) {
        D_800E7CD8 = 1;
    }
    if (m->f6 & 8) {
        D_800E7CD8 |= 2;
    }
    D_800D5E80 = (D_800DF31C->flags & 0x20) != 0;
    func_800C1370(n);
    func_8000DE40((D_800DF31C->flags & 0x10) == 0);
    if (D_800DF31C->f6) {
        func_800B8050();
        func_800B807C(0, D_800DF31C->f6);
    }
    accumulateColorChannels(-1, -1, -1);
    func_80010200(0xB, 0, 0.0f);
    func_80010200(0xB, 1, 0.0f);
    func_80010200(0xB, 2, 0.0f);
    func_80010200(0xB, 3, 0.0f);
}
