/* @header
 * updateActionVariantState  (originally func_800A2A70)
 * VRAM 0x800A2A70 | ROM 0x95F10 | size 0x238
 * asm: asm/nonmatchings/code_8009D7A0/func_800A2A70.s
 */
#include "common.h"

extern void *D_800EB408;
extern void *D_800EB414;
extern s32 D_800E3CC0[];
extern u16 D_800FABE6;
extern u16 D_800FAF8A;
s32 func_800D2B64(void *, f32, u16, s32);
void func_800A6C48(void *, s32);
void beginEntityActionA8D8C(void *);
void func_800B68A0(void *, void *, void *);
s32 func_800C2634(void *, s32, void *, s32);
void func_800D25D0(void *, f32);
s16 findBoundaryQuadrant(void *, s32, s32);
s32 func_800D3550(s32);
s32 func_800D3684(s32, s32);
void func_800D427C(void *, s16, s32);
void func_800D4AD0(void *);
void func_800D7B54(void *, u16, u16, s32);
s32 func_800E07DC(void *);

/* Two-state action for D_800EB408: state 0 picks one of the 0x103E/0x1040/
 * 0x1042 animation variants from the +0x30 flag bits (bit 0x1000 adds one)
 * and plays it; state 1 runs the 0xFFFFE boundary correction and, when the
 * +0x20 flag 0x40 is set, either starts action 0x14 or, on timer expiry,
 * ends the action. */
void updateActionVariantState(void) {
    s16 anim;
    s16 targetIndex;
    s32 animFlags;
    s32 targetMask;
    switch (((Nw2F408 *)D_800EB408)->fC) {
    case 0:
        if (*(s32 *)((u8 *)D_800EB408 + 0x30) >= 0) {
            func_800B68A0(D_800EB414, D_800EB414, D_800EB408);
        }
        animFlags = *(s32 *)((u8 *)D_800EB408 + 0x30);
        if (animFlags & 0x10000000) anim = 0x103E;
        if (animFlags & 0x20000000) anim = 0x1040;
        if (animFlags & 0x40000000) anim = 0x1042;
        if (animFlags & 0x1000) anim += 1;
        func_800D427C(D_800EB408, anim, 3);
        ((Nw2F408 *)D_800EB408)->fC++;
        return;
    case 1:
        func_800D7B54(D_800EB408, D_800FABE6, D_800FAF8A, 1);
        func_800D25D0(D_800EB408, 4.0f);
        targetMask = func_800D2B64(D_800EB408, 2.0f, 0, 0xFFFFE) & 0xFFFF;
        if (targetMask != 0 && (*(u64 *)((u8 *)D_800EB408 + 0x20) & 0x40ULL)) {
            if (((Nw2F408 *)D_800EB408)->f6 < 0xB && (func_800C2634(D_800EB408, targetMask, D_800EB408, targetMask) << 24) != 0) {
                func_800A6C48(D_800EB408, 0x62);
                return;
            }
            targetIndex = findBoundaryQuadrant(D_800EB408, 0, 0);
            *(s16 *)((u8 *)D_800EB408 + 0x3E) = targetIndex;
            if (targetIndex != -1 && func_800D3550(func_800D3684(D_800E3CC0[targetIndex], *(s32 *)((u8 *)D_800EB408 + 0x58))) < 0x300 && (func_800E07DC(D_800EB408) << 24) != 0) {
                *(s16 *)((u8 *)D_800EB408 + 0x28) = 0;
                func_800A6C48(D_800EB408, 0x14);
                return;
            }
        }
        if (((Nw2F408 *)D_800EB408)->f4 <= 0) {
            func_800D4AD0(D_800EB408);
            beginEntityActionA8D8C(D_800EB408);
        }
        return;
    }
}
