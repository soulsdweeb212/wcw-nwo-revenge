/* @header
 * func_800C0E44
 * VRAM 0x800C0E44 | ROM 0xB42E4 | size 0x458
 * asm: asm/nonmatchings/code_800BBA00/func_800C0E44.s
 */
#include "common.h"

extern s32 D_800F9B0C;
extern u16 D_800FABE6;
void func_800D427C(Wrestler *, s32, s32);
s32 func_800D4D44(Wrestler *, s32, s32);
void func_800D7E80(Wrestler *, s32);
s8 func_800D8D74(Wrestler *, s32);
s8 func_800C2830(Wrestler *);
s8 isEntityActionAllowedC2870(Wrestler *);
void func_800E212C(Wrestler *);
s16 func_800BF2FC(Wrestler *);
void func_800C278C(Wrestler *, f32);
void func_800A7188(Wrestler *);

void func_800C0E44(void) {
    Wrestler *e = D_800FAF5C;
    s32 anim;

    switch (e->step) {
    case 0:
        if (e->flags & WR_FLAG_ON_APRON) {
            e->flags = (e->flags & ~WR_FLAG_ON_APRON) | WR_FLAG_ON_FLOOR;
            func_800D427C(e, 0x1088, 2);
            D_800FAF5C->dirIndex = getXZDirectionQuadrant(&D_800FAF5C->jointA[1].x);
            D_800FAF5C->step = 3;
            break;
        }
        e->flags = (e->flags & ~WR_FLAG_IN_RING) | WR_FLAG_ON_APRON;
        if ((e->flags & 0x8000) || func_800C2830(e) ||
            (!isEntityActionAllowedC2870(D_800FAF5C) && (D_800FAF5C->flags & 3))) {
            D_800FAF5C->stepFlags |= 1;
        } else {
            func_800E212C(D_800FAF5C);
        }
        func_800D427C(D_800FAF5C, (s16)func_800D4D44(D_800FAF5C, 1, D_800F9B0C), 2);
        func_800D7E80(D_800FAF5C, 0);
        D_800FAF5C->step++;
    case 1:
        D_800FAF5C->flags |= 0x1000000000LL;
        if (!func_800D8D74(D_800FAF5C, 0)) {
            break;
        }
        if ((D_800FAF5C->flags & 0x1000000000000LL) && (D_800FAF5C->stepFlags & 1)) {
            func_800D427C(D_800FAF5C, 0x1025, 2);
            D_800FAF5C->step = 3;
            break;
        }
        if (*(u64 *)(D_800FAF5C->profile + 0x38) & 0x4000) {
            anim = 0xF25;
        } else if (func_800BF2FC(D_800FAF5C) < 0x80) {
            anim = 0xF14;
        } else if (*(u64 *)(D_800FAF5C->profile + 0x38) & 0xE000) {
            anim = 0xF17;
        } else {
            anim = 0xF14;
        }
        func_800D427C(D_800FAF5C, anim, 2);
        D_800FAF5C->step++;
        break;
    case 2:
        func_800C278C(e, 2.0f);
        if (D_800FAF5C->animFramesLeft > 0) {
            break;
        }
        if ((D_800FAF5C->flags & 0x8000) || (func_800C2830(D_800FAF5C) && (D_800FABE6 & 8)) ||
            (!isEntityActionAllowedC2870(D_800FAF5C) && (D_800FAF5C->flags & 3))) {
            D_800FAF5C->flags = (D_800FAF5C->flags & ~WR_FLAG_ON_APRON) | WR_FLAG_ON_FLOOR;
            anim = 2;
        } else {
            anim = 1;
        }
        func_800D427C(D_800FAF5C, (s16)(D_800FAF5C->animId + anim), 0);
        D_800FAF5C->step++;
        break;
    case 3:
        func_800C278C(e, 2.0f);
        func_800A7188(D_800FAF5C);
        break;
    }
}
