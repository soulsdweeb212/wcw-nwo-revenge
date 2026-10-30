/* @header
 * func_8000CD18
 * VRAM 0x8000CD18 | ROM 0xD918 | size 0x6C
 * asm: asm/nonmatchings/main/func_8000CD18.s
 */
#include "common.h"

extern s8 D_800706A4[];
extern s8 D_800485B0[];
extern s8 D_800485D0[];
extern u8 D_800517D0[];

void setIndexedS16Pair(s32, s32, s8, s8);
void func_80001DC4(void *);
void buildEntityPartTransforms(void *, s32, f32, f32);

/* Rebuilds the part transforms of an entity, then recomputes its transform
 * node from the given pose values. */
void func_8000CD18(s32 entityIndex, f32 arg1, f32 arg2) {
    u8 *entity = D_800517D0 + (s16)entityIndex * 0x13C4;

    buildEntityPartTransforms(entity, (s16)entityIndex, arg1, arg2);
    func_80001DC4(entity);
}
