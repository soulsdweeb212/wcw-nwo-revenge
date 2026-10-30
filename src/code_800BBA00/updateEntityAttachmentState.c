/* @header
 * updateEntityAttachmentState  (originally func_800C129C)
 * VRAM 0x800C129C | ROM 0xB473C | size 0x420
 * asm: asm/nonmatchings/code_800BBA00/func_800C129C.s
 */
#include "common.h"

/* Entity attachment (held-object) state machine (states 0..3).
 * State 0 raises/grabs the attachment: it flips the 0x80/0x40 status bits and
 * picks the pickup animation from the attachment's flags (func_800BF2FC
 * decides the large-object branch). State 1 plays it and waits
 * (func_800D8D74), state 2 finishes the raise (scale via func_800C278C) and
 * picks the carry animation, state 3 gently scales the attachment while held. */
typedef struct ATT {
    u8 p[0x38];
    u64 flags;
} ATT;
typedef struct {
    u8 p0[4];
    s16 f4, f6;         /* +0x04 animation countdown */
    u16 f8;             /* +0x08 base animation id */
    s16 fA, fC;         /* +0x0C case selector */
    u8 pE[0x12];
    u64 flags;          /* +0x20 entity status bits */
    u8 p28[0x33C];
    ATT *attachment;    /* +0x360 attached object */
} F5C;
extern F5C *D_800FAF5C;
extern u16 D_800FABE6;
extern s32 D_800F9B0C;
s8 isEntityActionAllowedC2870(void *);
s16 func_800BF2FC(void *);
void func_800E212C(void *);
s32 func_800D4D44(void *, s32, s32);
void func_800D427C(void *, s16, s32);
void func_800D7E80(void *, s32);
s8 func_800D8D74(void *, s32);
void func_800C278C(void *, f32);
void func_800A7188(void *);

void updateEntityAttachmentState(void) {
    s16 anim;
    F5C *ent = D_800FAF5C;

    switch (ent->fC) {
    case 0:
        if (ent->flags & 0x80ULL) {
            ent->flags = (ent->flags & ~0x80ULL) | 0x40ULL;
            if (ent->attachment->flags & 0x4000ULL) {
                anim = 0x1084;
            } else if (!(ent->attachment->flags & 0x1E000ULL)) {
                anim = 0x1082;
            } else if (func_800BF2FC(ent) >= 0x80) {
                if (D_800FAF5C->attachment->flags & 0x2000ULL) anim = 0x1083;
                if (D_800FAF5C->attachment->flags & 0x8000ULL) anim = 0x1085;
                if (D_800FAF5C->attachment->flags & 0x10000ULL) anim = 0x1086;
            } else {
                anim = 0x1082;
            }
            func_800D427C(D_800FAF5C, anim, 2);
            D_800FAF5C->fC = 3;
            return;
        }
        D_800FAF5C->flags = (D_800FAF5C->flags & ~0x100ULL) | 0x80ULL;
        if (!isEntityActionAllowedC2870(D_800FAF5C)) func_800E212C(D_800FAF5C);
        func_800D427C(D_800FAF5C, func_800D4D44(D_800FAF5C, 1, D_800F9B0C), 0);
        func_800D7E80(D_800FAF5C, 0);
        D_800FAF5C->fC++;
    case 1:
        D_800FAF5C->flags |= 0x1000000000ULL;
        if (func_800D8D74(D_800FAF5C, 0)) {
            if ((D_800FAF5C->flags & 0x1000000000000ULL) && isEntityActionAllowedC2870(D_800FAF5C)) {
                func_800D427C(D_800FAF5C, 0x1024, 2);
                D_800FAF5C->fC = 3;
                return;
            }
            func_800D427C(D_800FAF5C, 0xF1A, 2);
            D_800FAF5C->fC++;
        }
        break;
    case 2:
        func_800C278C(D_800FAF5C, 6.0f);
        if (D_800FAF5C->f4 <= 0) {
            anim = 1;
            if (D_800FABE6 & 8) {
                if (isEntityActionAllowedC2870(D_800FAF5C)) {
                    D_800FAF5C->flags = (D_800FAF5C->flags & ~0x80ULL) | 0x40ULL;
                    if (D_800FAF5C->attachment->flags & 0x4000ULL) anim = 0xE;
                    else anim = 2;
                }
            }
            func_800D427C(D_800FAF5C, D_800FAF5C->f8 + anim, 0);
            D_800FAF5C->fC++;
        }
        break;
    case 3:
        func_800C278C(D_800FAF5C, 6.0f);
        func_800A7188(D_800FAF5C);
        break;
    }
}
