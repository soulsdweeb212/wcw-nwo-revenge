/* @header
 * func_800DB348
 * VRAM 0x800DB348 | ROM 0xCE7E8 | size 0x1B4
 * asm: asm/nonmatchings/code_800BBA00/func_800DB348.s
 */
#include "common.h"

typedef struct {
    f32 x, y, z;
    s32 angle;
} Nw2DirRes;

extern u8 D_800F9890[];
extern s16 D_800F9888[];

void func_800D3890(void *, void *, void *);
void func_800D37C0(s32, f32, void *);
void translateEntityXZ(void *, void *);
s32 func_800D2B64(void *, f32, u16, s32);

/* Per-frame movement of self's dive / jump toward the point func_800DACE4 stored (D_800F9890[id]). Sets flag
 * 0x80000000000. While animFrame is inside anim.activeStart..activeEnd: takes the XZ direction from
 * jointA[move.activeJoint[0]] to that point, stores distance / D_800F9888[id] (the frames left) at that heading in
 * moveDelta, moves the body by it (translateEntityXZ), adds moveDelta[1] to y in states 0x6C and 0x6F, and
 * decrements D_800F9888[id]. Then, if unk034 has bit 2 and other is not in state 0x2C step 3, clears unk034 bit
 * 0x10. Once animFrame reaches anim.hitEnd, clears flag 0x80000000000 and WR_FLAG_ON_APRON and runs
 * func_800D2B64(self, 4.0f, 0, 0xFFFFE) (boundary correction of self alone). */
void func_800DB348(Wrestler *self, Wrestler *other) {
    Nw2DirRes dir;
    s32 id;
    u8 flagBits;
    s8 idx;

    self->flags |= 0x80000000000ULL;
    id = (u8)self->id;
    if (self->animFrame < self->anim.activeStart || self->anim.activeEnd < self->animFrame)
        goto skip;
    idx = self->move.activeJoint[0];
    func_800D3890(&self->jointA[idx], D_800F9890 + (s8)id * 0x10, &dir);
    func_800D37C0(dir.angle, dir.y / (f32)D_800F9888[(s8)id], self->moveDelta);
    translateEntityXZ(self, self->moveDelta);
    if (self->state == 0x6C) {
        self->y += self->moveDelta[1];
    } else if (self->state == 0x6F) {
        self->y += self->moveDelta[1];
    }
    ((u16 *)D_800F9888)[(s8)id]--;
skip:
    flagBits = self->unk034;
    if ((flagBits & 2) && (other->state != 0x2C || other->step != 3))
        self->unk034 = flagBits & ~0x10;
    if (self->animFrame < self->anim.hitEnd)
        return;
    self->flags &= ~(0x80000000000ULL | WR_FLAG_ON_APRON);
    func_800D2B64(self, 4.0f, 0, 0xFFFFE);
}
