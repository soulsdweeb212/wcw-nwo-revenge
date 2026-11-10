/* @header
 * func_800A52CC
 * VRAM 0x800A52CC | ROM 0x9876C | size 0x270
 * asm: asm/nonmatchings/code_8009D7A0/func_800A52CC.s
 */
#include "common.h"

s32 func_800D2BEC(void *, void *, void *, f32, u16, s32);
void func_800CE124(void *, void *, void *);
s32 func_800CE2C8(void *, void *, void *, void *, void *);
void func_800A7C40(void *, s8, s16);
void func_800A7F6C(void *, s32);
void func_800A837C(void *);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D5438 */
s16 func_800D5438(void *, s16);
#endif
void func_800D427C(void *, s16, s32);
void func_800D4AD0(void *);
extern u8 D_800F9B18[];
extern s8 D_800FABE4;
extern s8 D_800FADB8;

void func_800A52CC(void) {
    s16 anim;
    s16 variant;
    u32 flags;
    u8 *m;

    switch (D_800EB408->step) {
    case 0:
        m = D_800F9B18 + D_800FADB8 * 16;
        func_800CE124(D_800EB408, D_800EB40C, m);
        flags = D_800EB408->grappleCtx;
        if (flags & 0x800) {
            anim = 0x8A;
        }
        if (flags & 0x1000) {
            anim = 0x8B;
        }
        if (flags & 0x2000) {
            anim = 0x8C;
        }
        func_800A7C40(D_800EB408, D_800FADB8, anim);
        flags = D_800EB408->grappleCtx;
        if (flags & 0x1800) {
            variant = (flags >> 14) & 1;
        }
        if (flags & 0x2000) {
            variant = (flags >> 6) & 1;
        }
        func_800D427C(D_800EB408, func_800D5438(D_800EB408, variant), 2);
        func_800A7F6C(D_800EB408, 0x41);
        func_800A837C(D_800EB408);
        D_800EB408->step = D_800EB408->step + 1;
    case 1:
        m = D_800F9B18 + D_800FADB8 * 16;
        if ((s8)func_800CE2C8(D_800EB408, D_800EB40C, D_800EB418,
                m, D_800F9B18 + D_800FABE4 * 16)) {
            D_800EB408->step = D_800EB408->step + 1;
        }
        break;
    case 2:
        func_800D2BEC(D_800EB408, &D_800F9D10[D_800EB408->attached[0]],
                &D_800F9D10[D_800EB408->attached[1]], 4.0f, 0, 0xFFFFE);
        if (D_800EB408->animFramesLeft <= 0) {
            u64 *fp = &D_800EB408->flags;
            u64 flags2 = *fp;
            Wrestler *q;
#ifdef TARGET_PC
            /* attached[] is s8: the N64 code stores the low byte of (u8 *)-1 through an s32 cast, that is -1 (none).
             * On PC that cast would cut a 64-bit pointer, so the PC stores -1 itself. */
            D_800EB408->attached[0] = -1;
#else
            m = (u8 *)-1;
            D_800EB408->attached[0] = (s32)m;
#endif
            q = D_800EB408;
            flags2 &= 0xFFFFFFFFBFFFFFFFULL;
            flags2 |= (flags2 & ~flags2);
            *fp = flags2;
#ifdef TARGET_PC
            /* as above: -1, no record */
            q->attached[1] = -1;
#else
            q->attached[1] = (s32)m;
#endif
            func_800D4AD0(D_800EB408);
            func_800A6C48(D_800EB408, 0x2B);
        }
        break;
    }
}
