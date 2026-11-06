/* @header
 * func_800D427C
 * VRAM 0x800D427C | ROM 0xC771C | size 0x138
 * asm: asm/nonmatchings/code_800BBA00/func_800D427C.s
 */
#include "common.h"

extern s16 D_800EB680[];
extern s32 D_800EB6B8[];
s32 decodeAnimationMetadata(void *, s16);
/* Start an animation on the wrestler: record the previous animId per slot in
 * D_800EB680, store the new animId, and if it actually changed, decode the new
 * animation's metadata into anim, resolve the 0/0xFF sentinel bytes (hitStart,
 * hitEnd, activeEnd, reversalFrame, cancelFrame, unk37D[5]) to 1 or to
 * anim.frameCount, reset animFrame to 0 and animFramesLeft to anim.frameCount,
 * and store the caller's mode into the per-slot table D_800EB6B8. */
void func_800D427C(Wrestler *w, s16 animId, s32 mode) {
    D_800EB680[w->id] = w->animId;
    w->animId = animId;
    if (animId != D_800EB680[w->id]) {
        D_800EB680[w->id] = animId;
        decodeAnimationMetadata(&w->anim, w->animId);
        if (w->anim.hitStart == 0) {
            w->anim.hitStart = 1;
        }
        if (w->anim.hitStart == 0xFF) {
            w->anim.hitStart = w->anim.frameCount;
        }
        if (w->anim.hitEnd == 0) {
            w->anim.hitEnd = 1;
        }
        if (w->anim.hitEnd == 0xFF) {
            w->anim.hitEnd = w->anim.frameCount;
        }
        if (w->anim.activeEnd == 0xFF) {
            w->anim.activeEnd = w->anim.frameCount;
        }
        if (w->anim.reversalFrame == 0) {
            w->anim.reversalFrame = 1;
        }
        if (w->anim.cancelFrame == 0) {
            w->anim.cancelFrame = 1;
        }
        if (w->anim.unk37D[5] == 0) {
            w->anim.unk37D[5] = w->anim.frameCount;
        }
        w->animFrame = 0;
        w->animFramesLeft = w->anim.frameCount;
        D_800EB6B8[w->id] = mode;
    }
}
