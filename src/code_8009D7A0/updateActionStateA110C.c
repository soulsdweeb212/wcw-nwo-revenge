/* @header
 * updateActionStateA110C  (originally func_800A110C)
 * VRAM 0x800A110C | ROM 0x945AC | size 0x2D0
 * asm: asm/nonmatchings/code_8009D7A0/updateActionStateA110C.s
 */
#include "common.h"

/* D_800EB408 action state machine (cases 0..2) driving D_800EB40C: state 0 picks a
 * follow-up mode from the attachment byte and starts the matching animation; state 1
 * begins the close-range action once the actor's animation frame is inside the window,
 * the target is in range and the timer has elapsed; state 2 runs the finish helper. */
extern void *D_800EB40C;
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

#define Actor ((u8 *)D_800EB408)
#define Target ((u8 *)D_800EB40C)
#define ReadS16(p, n) (*(s16 *)((p) + (n)))
#define ReadS32(p, n) (*(s32 *)((p) + (n)))
#define ReadFlags(p) (*(u64 *)((p) + 0x20))

void updateActionStateA110C(void) {
    u8 x;
    u64 flags;
    s16 mode, anim, frame, state, temp;

    switch (ReadS16(Actor, 12)) {
    case 0:
        mode = *(s8 *)(*(u8 **)(Actor + 0x364) + 15);
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
        ReadS16(Actor, 12)++;
        break;
    case 1:
        frame = ReadS16(Actor, 6);
        if (frame >= Actor[0x370] && Actor[0x371] >= frame && (ReadFlags(Target) & 0x100000ULL)) {
            state = ReadS16(Target, 10);
            if (state != 4 && (state != 3 || ReadS16(Target, 12) != 2)
                && (f64)D_800F9B0C < D_800E4540
                && (u32)(func_800D3550(func_800D3684(ReadS32(Target, 0x58), D_800F9B14)) - 0x100) >= 0x601) {
                if (D_800EB400[D_800FADB8] == 2)
                    *(u16 *)(Target + 0x28) |= 0x200;
                Target[0x351] = (u8)D_800FADB8;
                addEntityHealthDelta(D_800EB408, *(s8 *)(Actor + 0x391));
                func_800A6BE0(D_800EB40C, 0x1A);
                { u8 *b = Target; u8 *a = Actor;
                  ReadFlags(b) |= 0x20000000ULL;
                  func_800A837C(a); }
                ReadS16(Actor, 12)++;
            }
        }
        /* fallthrough */
    case 2:
        func_800A7188(D_800EB408);
        break;
    }
}
