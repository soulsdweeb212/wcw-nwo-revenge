/* @header
 * updateEntityAttachmentState  (originally func_800C129C)
 * VRAM 0x800C129C | ROM 0xB473C | size 0x420
 * asm: asm/nonmatchings/code_800BBA00/updateEntityAttachmentState.s
 */
#include "common.h"

/* Entity attachment (held-object) state machine (steps 0..3).
 * Step 0 raises/grabs the attachment: it flips the apron/in-ring zone bits and
 * picks the pickup animation from the character profile's flags (+0x38;
 * func_800BF2FC decides the large-object branch). Step 1 plays it and waits
 * (func_800D8D74), step 2 finishes the raise (scale via func_800C278C) and
 * picks the carry animation, step 3 gently scales the attachment while held. */
extern u16 D_800FABE6;
#ifdef TARGET_PC
/* PC: D_800F9B0C is a float (the distance to the opponent), and func_800D4D44's third parameter is a float (its
 * definition: s32 func_800D4D44(Wrestler *, s16, f32)). The N64 code reads the float's bits as an s32 and passes them
 * in an integer register, where the N64 callee reads them as a float. On the PC an s32 argument would be converted to
 * a float of another value (100.0f's bits would arrive as 1120403456.0f), so the PC declares it f32. */
extern f32 D_800F9B0C;
#else
extern s32 D_800F9B0C;
#endif
s8 isEntityActionAllowedC2870(void *);
s16 func_800BF2FC(void *);
void func_800E212C(void *);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D4D44 */
s32 func_800D4D44(void *, s32, s32);
#endif
void func_800D427C(void *, s16, s32);
void func_800D7E80(void *, s32);
s8 func_800D8D74(void *, s32);
void func_800C278C(void *, f32);
void func_800A7188(void *);

void updateEntityAttachmentState(void) {
    s16 anim;
    Wrestler *ent = D_800FAF5C;

    switch (ent->step) {
    case 0:
        if (ent->flags & WR_FLAG_ON_APRON) {
            ent->flags = (ent->flags & ~WR_FLAG_ON_APRON) | WR_FLAG_IN_RING;
            if (*(u64 *)(ent->profile + 0x38) & 0x4000ULL) {
                anim = 0x1084;
            } else if (!(*(u64 *)(ent->profile + 0x38) & 0x1E000ULL)) {
                anim = 0x1082;
            } else if (func_800BF2FC(ent) >= 0x80) {
                if (*(u64 *)(D_800FAF5C->profile + 0x38) & 0x2000ULL) anim = 0x1083;
                if (*(u64 *)(D_800FAF5C->profile + 0x38) & 0x8000ULL) anim = 0x1085;
                if (*(u64 *)(D_800FAF5C->profile + 0x38) & 0x10000ULL) anim = 0x1086;
            } else {
                anim = 0x1082;
            }
            func_800D427C(D_800FAF5C, anim, 2);
            D_800FAF5C->step = 3;
            return;
        }
        D_800FAF5C->flags = (D_800FAF5C->flags & ~WR_FLAG_ON_FLOOR) | WR_FLAG_ON_APRON;
        if (!isEntityActionAllowedC2870(D_800FAF5C)) func_800E212C(D_800FAF5C);
        func_800D427C(D_800FAF5C, func_800D4D44(D_800FAF5C, 1, D_800F9B0C), 0);
        func_800D7E80(D_800FAF5C, 0);
        D_800FAF5C->step++;
    case 1:
        D_800FAF5C->flags |= 0x1000000000ULL;
        if (func_800D8D74(D_800FAF5C, 0)) {
            if ((D_800FAF5C->flags & 0x1000000000000ULL) && isEntityActionAllowedC2870(D_800FAF5C)) {
                func_800D427C(D_800FAF5C, 0x1024, 2);
                D_800FAF5C->step = 3;
                return;
            }
            func_800D427C(D_800FAF5C, 0xF1A, 2);
            D_800FAF5C->step++;
        }
        break;
    case 2:
        func_800C278C(D_800FAF5C, 6.0f);
        if (D_800FAF5C->animFramesLeft <= 0) {
            anim = 1;
            if (D_800FABE6 & 8) {
                if (isEntityActionAllowedC2870(D_800FAF5C)) {
                    D_800FAF5C->flags = (D_800FAF5C->flags & ~WR_FLAG_ON_APRON) | WR_FLAG_IN_RING;
                    if (*(u64 *)(D_800FAF5C->profile + 0x38) & 0x4000ULL) anim = 0xE;
                    else anim = 2;
                }
            }
            func_800D427C(D_800FAF5C, D_800FAF5C->animId + anim, 0);
            D_800FAF5C->step++;
        }
        break;
    case 3:
        func_800C278C(D_800FAF5C, 6.0f);
        func_800A7188(D_800FAF5C);
        break;
    }
}
