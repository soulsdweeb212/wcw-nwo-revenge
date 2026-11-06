/* @header
 * updateActionStateA110C  (originally func_800A110C)
 * VRAM 0x800A110C | ROM 0x945AC | size 0x2D0
 * asm: asm/nonmatchings/code_8009D7A0/updateActionStateA110C.s
 */
#include "common.h"

/* D_800EB408 action step machine (cases 0..2) driving the opponent D_800EB40C: step 0
 * picks a follow-up mode from profile byte 15 and starts the matching animation; step 1
 * begins the close-range action once the animation frame is inside the hit window,
 * the opponent is in range and facing away; step 2 runs the finish helper. */
extern f32 D_800F9B0C;
extern f64 D_800E4540;
extern s32 D_800F9B14;
extern s8 D_800FADB8;
extern s16 D_800EB400[];
s8 func_800D4198(s16);
void func_800D427C(void *, s32, s32);
void func_800A7F6C(void *, s32);
void addEntityHealthDelta(void *, s32);
void func_800A6BE0(void *, s32);
void func_800A837C(void *);
void func_800A7188(void *);

void updateActionStateA110C(void) {
    u8 x;
    u64 flags;
    s16 mode, anim, frame, state, temp;

    switch (D_800EB408->step) {
    case 0:
        mode = *(s8 *)(D_800EB408->profile + 15);
        if (mode == 2) mode = 0;
        if (mode >= 3) mode = (func_800D4198(500) == 0);
        D_800EB400[D_800FADB8] = mode;
        switch (mode) {
        case 0: anim = 0xE4C; break;
        case 2: anim = 0xE4E; break;
        case 1: anim = 0xE4D; break;
        }
        func_800D427C(D_800EB408, anim, 3);
        func_800A7F6C(D_800EB408, 0x4C);
        D_800EB408->step++;
        break;
    case 1:
        frame = D_800EB408->animFrame;
        if (frame >= D_800EB408->anim.hitStart && D_800EB408->anim.hitEnd >= frame && (D_800EB40C->flags & 0x100000ULL)) {
            state = D_800EB40C->state;
            if (state != 4 && (state != 3 || D_800EB40C->step != 2)
                && (f64)D_800F9B0C < D_800E4540
                && (u32)(func_800D3550(func_800D3684(D_800EB40C->heading, D_800F9B14)) - 0x100) >= 0x601) {
                if (D_800EB400[D_800FADB8] == 2)
                    D_800EB40C->moveMode |= 0x200;
                D_800EB40C->heldById = D_800FADB8;
                addEntityHealthDelta(D_800EB408, D_800EB408->move.spiritGainSelf);
                func_800A6BE0(D_800EB40C, 0x1A);
                { Wrestler *b = D_800EB40C; Wrestler *a = D_800EB408;
                    b->flags |= 0x20000000ULL;
                    func_800A837C(a); }
                D_800EB408->step++;
            }
        }
        /* fallthrough */
    case 2:
        func_800A7188(D_800EB408);
        break;
    }
}
