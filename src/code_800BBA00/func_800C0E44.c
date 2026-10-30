/* @header
 * func_800C0E44
 * VRAM 0x800C0E44 | ROM 0xB42E4 | size 0x458
 * asm: asm/nonmatchings/code_800BBA00/func_800C0E44.s
 */
#include "common.h"

typedef struct {
    char pad0[0x38];
    u64 flags;
} Sub0E44;

typedef struct {
    char pad0[4];
    s16 h4;
    char pad6[2];
    s16 h8;
    char padA[2];
    s16 state;
    u16 hE;
    char pad10[0x10];
    u64 flags;
    char pad28[0x16];
    s16 h3E;
    char pad40[0x2C];
    f32 f6C[3];
    char pad78[0x364 - 0x78];
    Sub0E44 *p364;
} Ent0E44;

extern Ent0E44 *D_800FAF5C;
extern s32 D_800F9B0C;
extern u16 D_800FABE6;
void func_800D427C(Ent0E44 *, s32, s32);
s32 func_800D4D44(Ent0E44 *, s32, s32);
void func_800D7E80(Ent0E44 *, s32);
s8 func_800D8D74(Ent0E44 *, s32);
s8 func_800C2830(Ent0E44 *);
s8 isEntityActionAllowedC2870(Ent0E44 *);
void func_800E212C(Ent0E44 *);
s16 func_800BF2FC(Ent0E44 *);
void func_800C278C(Ent0E44 *, f32);
void func_800A7188(Ent0E44 *);

void func_800C0E44(void) {
    Ent0E44 *e = D_800FAF5C;
    s32 anim;

    switch (e->state) {
    case 0:
        if (e->flags & 0x80) {
            e->flags = (e->flags & ~0x80) | 0x100;
            func_800D427C(e, 0x1088, 2);
            D_800FAF5C->h3E = getXZDirectionQuadrant(D_800FAF5C->f6C);
            D_800FAF5C->state = 3;
            break;
        }
        e->flags = (e->flags & ~0x40) | 0x80;
        if ((e->flags & 0x8000) || func_800C2830(e) ||
            (!isEntityActionAllowedC2870(D_800FAF5C) && (D_800FAF5C->flags & 3))) {
            D_800FAF5C->hE |= 1;
        } else {
            func_800E212C(D_800FAF5C);
        }
        func_800D427C(D_800FAF5C, (s16)func_800D4D44(D_800FAF5C, 1, D_800F9B0C), 2);
        func_800D7E80(D_800FAF5C, 0);
        D_800FAF5C->state++;
    case 1:
        D_800FAF5C->flags |= 0x1000000000LL;
        if (!func_800D8D74(D_800FAF5C, 0)) {
            break;
        }
        if ((D_800FAF5C->flags & 0x1000000000000LL) && (D_800FAF5C->hE & 1)) {
            func_800D427C(D_800FAF5C, 0x1025, 2);
            D_800FAF5C->state = 3;
            break;
        }
        if (D_800FAF5C->p364->flags & 0x4000) {
            anim = 0xF25;
        } else if (func_800BF2FC(D_800FAF5C) < 0x80) {
            anim = 0xF14;
        } else if (D_800FAF5C->p364->flags & 0xE000) {
            anim = 0xF17;
        } else {
            anim = 0xF14;
        }
        func_800D427C(D_800FAF5C, anim, 2);
        D_800FAF5C->state++;
        break;
    case 2:
        func_800C278C(e, 2.0f);
        if (D_800FAF5C->h4 > 0) {
            break;
        }
        if ((D_800FAF5C->flags & 0x8000) || (func_800C2830(D_800FAF5C) && (D_800FABE6 & 8)) ||
            (!isEntityActionAllowedC2870(D_800FAF5C) && (D_800FAF5C->flags & 3))) {
            D_800FAF5C->flags = (D_800FAF5C->flags & ~0x80) | 0x100;
            anim = 2;
        } else {
            anim = 1;
        }
        func_800D427C(D_800FAF5C, (s16)(D_800FAF5C->h8 + anim), 0);
        D_800FAF5C->state++;
        break;
    case 3:
        func_800C278C(e, 2.0f);
        func_800A7188(D_800FAF5C);
        break;
    }
}
