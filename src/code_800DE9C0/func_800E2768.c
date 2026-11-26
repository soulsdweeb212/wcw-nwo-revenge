/* @header
 * func_800E2768
 * VRAM 0x800E2768 | ROM 0xD5C08 | size 0x4C
 * asm: asm/nonmatchings/code_800DE9C0/func_800E2768.s
 */
#include "common.h"

extern s8 D_800F99A0[];
extern u8 D_800F98E2[];

#ifdef TARGET_PC
/* PC: the parameter and return types of the definitions (docs/port.md, "Prototypes on PC"). */
void applyEntityTextureMasks(s16, s16);
#else
void applyEntityTextureMasks(s8, s8);
#endif

/* Re-applies the texture masks (applyEntityTextureMasks(other->id, D_800F99A0[self->id])) when
 * self->anim.unk372[2] is set and animFrame equals anim.unk372[3] + 7. */
void func_800E2768(Wrestler *self, Wrestler *other) {
    if (self->anim.unk372[2] != 0 && self->animFrame == self->anim.unk372[3] + 7) {
        applyEntityTextureMasks(other->id, D_800F99A0[self->id]);
    }
}
