/* @header
 * updateBodyPartTransforms  (originally func_80009B84)
 * VRAM 0x80009B84 | ROM 0xA784 | size 0x214
 * asm: asm/nonmatchings/main/func_80009B84.s
 */
#include "common.h"

/* Per-body-part transform state: local Euler rotation in degrees at +0x00,
 * local translation at +0x0C, cached previous rotation at +0x18 and cached
 * previous translation at +0x24. */
typedef struct {
    f32 rotX, rotY, rotZ;
    f32 posX, posY, posZ;
    f32 prevRotX, prevRotY, prevRotZ;
    f32 prevPosX, prevPosY, prevPosZ;
    u8 pad[0x4C];
} Nw2PartTransform;

/* Render record for one body part: owner link at +0, world matrix at +0x1C. */
typedef struct {
    void *link;
    u8 pad4[0x18];
    f32 matrix[16];
    u8 tail[0x80];
} Nw2PartRenderRecord;

extern Nw2PartTransform D_80070C40[][23];
extern Nw2PartRenderRecord D_800651A0[][23];
extern u8 D_800738D0[];
extern u8 D_80074E80[];
extern s8 D_800307C0[];
extern s8 D_800307E8[];
extern s8 D_800307FC[];
void func_80007E04(void *, f32, f32, f32);
void multiplyMatrix4x4(void *, void *, void *);
void func_8001B3EC(void *, f32, f32, f32, f32 *, f32 *, f32 *);

/* For each body part of entity arg0: derive its local rotation from its Euler
 * angles and its translation from its parent's offset, build the part's world
 * matrix, and remember the values so the next frame can detect changes. */
void updateBodyPartTransforms(s16 arg0) {
    u32 i;
    for (i = 1; i < 0x14; i++) {
        s16 part = D_800307E8[i];
        Nw2PartRenderRecord *renderRec = &D_800651A0[arg0][part];
        Nw2PartTransform *partTf = &D_80070C40[arg0][part];
        f32 *pos = &partTf->posX;
        s8 parent = D_800307FC[part];
        if (parent != 0) {
            f32 *parentMatrix = (f32 *)(D_800738D0 + (parent << 6));
            s32 dx = D_800307C0[part * 2] - D_800307C0[parent * 2];
            s32 dy = D_800307C0[part * 2 + 1] - D_800307C0[parent * 2 + 1];
            func_8001B3EC(parentMatrix, (f32)dx, (f32)dy, 0, pos, &partTf->posY, &partTf->posZ);
        }
        {
            s32 off = part << 6;
            f32 *matrix = (f32 *)(D_800738D0 + off);
            buildEulerRotationMatrixDegrees((f32 (*)[4])matrix, partTf->rotX, partTf->rotY, partTf->rotZ);
            func_80007E04(matrix, partTf->posX, partTf->posY, partTf->posZ);
            multiplyMatrix4x4((f32 *)(D_80074E80 + off), matrix, &renderRec->matrix[0]);
        }
        partTf->prevPosX = partTf->posX;
        partTf->prevPosY = partTf->posY;
        partTf->prevPosZ = partTf->posZ;
        partTf->prevRotX = partTf->rotX;
        partTf->prevRotY = partTf->rotY;
        partTf->prevRotZ = partTf->rotZ;
    }
}
