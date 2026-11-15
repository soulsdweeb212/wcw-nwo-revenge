/* @header
 * func_800C194C
 * VRAM 0x800C194C | ROM 0x6E0BC | size 0x1D8
 * asm: asm/nonmatchings/code_80090000/func_800C194C.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: the picture sets D_800D4930 hold addresses, so they have their PC layout (common.h's Nw2MenuShot); T names a
 * set's res and max s and m. */
typedef struct { void *pic[4]; u16 n[4]; u16 s; u16 m; u8 f1C[4]; } T;
_Static_assert(offsetof(T, s) == offsetof(Nw2MenuShot, res) && offsetof(T, m) == offsetof(Nw2MenuShot, max) &&
                   sizeof(T) == sizeof(Nw2MenuShot),
               "T follows common.h's Nw2MenuShot");
#else
typedef struct { u8 pad[0xC]; u32 f[4]; } A;
typedef struct { u32 a; u8 pad[0x10]; s16 b; s16 c; u8 pad2[4]; } C;
typedef struct { u8 pad[0x18]; u16 s; u16 m; u8 pad2[4]; } T;
#endif
extern s32 D_80038A98, D_800DF30C, D_800DF308, D_800DF310, D_800E74D8, D_800DF3A8, D_800E79C4;
#ifdef TARGET_PC
/* PC: D_800E81F8 holds the address of a resource, the heap block that func_800B600C (port_decls.h) hands back for
 * resource id t->s, which func_8009A02C and func_8009A878 read as a pointer; an s32 would cut it in half. */
extern s32 D_800DF318, D_800E81E4, D_800DF314;
extern u8 *D_800E81F8;
#else
extern s32 D_800DF318, D_800E81F8, D_800E81E4, D_800DF314;
#endif
#ifdef TARGET_PC
/* PC: the scenes D_800D4ED8 (D_800DF31C is the current one) and the wrestlers' records D_800DF330 hold words that are
 * a number or an address, so they have their PC layouts (common.h's Nw2MenuScene and Nw2MenuSceneCast). */
extern Nw2MenuScene *D_800DF31C;
extern Nw2MenuScene D_800D4ED8[];
extern Nw2MenuSceneCast D_800DF330[];
#else
extern s8 *D_800DF31C;
extern A D_800D4ED8[];
extern C D_800DF330[];
#endif
extern T D_800D4930[];
void func_800C15A0(s32);
void func_800C0BDC(void);
void func_8000E55C(s32, s32, s32);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800B600C */
s32 func_800B600C(s32, s32);
#endif
void func_800C0680(s32);
void func_80099478(s32, s32, s32);

void func_800C194C(s32 a) {
    T *t;
#ifndef TARGET_PC /* on PC the loop below reads the records by field name */
    C *c;
    s16 *q;
    u32 *p;
    u32 m;
    s32 k;
#endif
    s32 i, n, v;
#ifndef TARGET_PC /* as above */
    u32 f;
#endif

    if (D_80038A98 != 0) {
        return;
    }
    if (D_800DF30C != D_800DF308) {
        D_800DF310 = D_800DF308;
        D_800DF30C = D_800DF308;
        func_800C15A0(D_800DF308);
    }
    n = D_800DF310;
#ifdef TARGET_PC
    /* PC: each wrestler's record takes the next scene's cast word; one that holds an address (ID_OR_ADDR_IS_ADDR, the
     * N64's sign bit) starts its keys from the beginning: no key yet, frame 0. */
    if (n != D_800DF308) {
        for (i = 0; i < 4; i++) {
            D_800DF330[i].keys = D_800D4ED8[n].cast[i];
            if (ID_OR_ADDR_IS_ADDR(D_800DF330[i].keys)) {
                D_800DF330[i].idx = -1;
                D_800DF330[i].t = 0;
            }
        }
    }
#else
    if (n != D_800DF308) {
        i = 0;
        c = D_800DF330;
        m = 0x80000000;
        k = -1;
        q = &c->c;
        p = (u32 *)&D_800D4ED8[n];
        for (; i < 4; i++, q += 14, c++) {
            f = p[3];
            p++;
            c->a = f;
            if (f & m) {
                q[-1] = k;
                q[0] = 0;
            }
        }
    }
#endif
    D_800E74D8 = -6;
    if (a != 0) {
        return;
    }
    func_800C0BDC();
    if (D_800DF3A8) {
        func_8000E55C(0xA, 1, 0x50);
    } else {
        func_8000E55C(0, 1, 0x50);
    }
    t = &D_800D4930[D_800E79C4];
    v = D_800DF318;
    if (t->s != 0) {
        D_800E81F8 = func_800B600C(t->s, 0);
    } else {
        D_800E81F8 = 0;
    }
    v = v > 0 ? v : 0;
    if (v >= t->m) {
        v = t->m;
    }
    func_800C0680(v);
    D_800DF318 = v;
    D_800E81E4 = D_800E79C4;
#ifdef TARGET_PC
    /* PC: the scene's first two bytes by name. */
    func_80099478(D_800DF31C->type, 0x20, 0xA);
    func_80099478(D_800DF31C->f1, 0x36, 0xA);
#else
    func_80099478(D_800DF31C[0], 0x20, 0xA);
    func_80099478(D_800DF31C[1], 0x36, 0xA);
#endif
    func_80099478(D_800DF314 - 1, 0x20, 0x19);
}
