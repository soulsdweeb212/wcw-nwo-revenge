/* @header
 * advanceTargetedAction  (originally func_800A64CC)
 * VRAM 0x800A64CC | ROM 0x9996C | size 0x11C
 * asm: asm/nonmatchings/code_8009D7A0/advanceTargetedAction.s
 */
#include "common.h"

extern void *D_800FAF5C;
s32 func_800D2B64(void *, f32, u16, s32);
void func_800D427C(void *, s32, s32);
void func_800D4AD0(void *);
void func_800D2600(void *, s32, f32);

/* Timed-action state machine (sibling of updateTimedAction). On the object
 * D_800EB408: state 0 queues command 0xE7A; state 1 re-evaluates the current
 * target (D_800FAF5C) and, once the action timer at +0x4 expires, runs the
 * completion handler and issues command 0x2B. */
void advanceTargetedAction(void) {
    s8 targetId;
    func_800D2B64(D_800EB408, 1.0f, 0, 2);
    switch (*(s16 *)((u8 *)D_800EB408 + 0xC)) {
    case 0:
        func_800D427C(D_800EB408, 0xE7A, 3);
        (*(s16 *)((u8 *)D_800EB408 + 0xC))++;
        break;
    case 1:
        targetId = func_800D26A0(D_800FAF5C, 0, -1);
        if (targetId != -1 && !(*(u64 *)(D_800F9D30 + targetId * 0x3B0) & 0x400000ULL))
            func_800D2600(D_800FAF5C, -1, 2.0f);
        if (*(s16 *)((u8 *)D_800EB408 + 4) <= 0) {
            func_800D4AD0(D_800EB408);
            func_800A6C48(D_800EB408, 0x2B);
        }
        break;
    }
}
