/* @header
 * func_8001E340
 * VRAM 0x8001E340 | ROM 0x1EF40 | size 0x54C
 * asm: asm/nonmatchings/main/func_8001E340.s
 */
#include "common.h"

typedef struct Nw2EnvRec {
    struct Nw2EnvRec *f0;
    s32 f4;
    s16 f8;
    s16 fA;
    s32 fC;
    s16 f10;
    u8 f12;
    u8 f13;
    s32 f14;
    s32 f18;
} Nw2EnvRec;

typedef struct Nw2EnvObj {
    struct Nw2EnvObj *f0;
    s32 f4;
    void (*f8)(void *, s32, s32);
    u8 pad0C[8];
    void *f14;
    s16 f18;
    s16 f1A;
    s16 f1C;
    s16 f1E;
    u16 f20;
    u16 f22;
    u16 f24;
    s16 f26;
    u16 f28;
    u16 f2A;
    s16 f2C;
    u16 f2E;
    s32 f30;
    s32 f34;
    s32 f38;
    Nw2EnvRec *f3C;
    s32 f40;
} Nw2EnvObj;

extern s16 D_800373F0[];
extern void *D_80037510;
extern char D_8003B710[];
extern char D_8003B714[];
void func_8001CEE0(char *, char *, s32);
u32 *func_8001E960(Nw2EnvObj *, u16 *, s16 *, s32, s32, u32 *);
void func_800207E8(void *);
void func_80020854(void *, s32);
f32 func_8001EFE4(f32, s32, s16, u16);

u32 *func_8001E340(Nw2EnvObj *obj, s32 unused, s32 budget, s32 time0, u32 *dl)
{
    s32 prev = time0;
    u16 sp1A = 0;
    u16 sp18 = 0;
    s32 padA, padB;
    Nw2EnvRec *rec;
    s32 diff;

    (void)&sp18;
    (void)&sp1A;
    (void)&padA;
    (void)&padB;
    (void)&prev;
    while (obj->f3C != NULL) {
        diff = obj->f3C->f4 - prev;
        prev = obj->f3C->f4;
        if (budget < diff) {
            break;
        }
        if (diff < 0) {
            func_8001CEE0(D_8003B710, D_8003B714, 0x68);
        }
        if (diff >= 161) {
            func_8001CEE0(D_8003B710, D_8003B714, 0x69);
        }
        switch (obj->f3C->f8) {
        case 13:
            rec = obj->f3C;
            {
                Nw2EnvObj *o = obj;
                if (rec->fA != 0) {
                    o->f8(o, 8, 0);
                }
                o->f8(o, 5, rec->f18);
                o->f8(o, 9, 0);
                o->f38 = 1;
                o->f30 = 0;
                o->f34 = rec->f14;
                o->f1A = (s16)((rec->f10 * rec->f10) >> 15);
                o->f18 = rec->f12;
                o->f20 = ((u16 *)D_800373F0)[rec->f13];
                o->f22 = ((u16 *)D_800373F0)[0x7F - rec->f13];
                if (rec->f14 != 0) {
                    o->f1C = 1;
                    o->f1E = 1;
                } else {
                    o->f1C = (s16)((o->f1A * D_800373F0[o->f18]) >> 15);
                    o->f1E = (s16)((o->f1A * D_800373F0[0x7F - o->f18]) >> 15);
                }
                {
                    Nw2EnvObj *child = o->f0;
                    if (child != NULL) {
                        child->f8(child, 7, rec->fC);
                    }
                }
            }
            break;
        case 11:
        case 12:
        case 16:
            dl = func_8001E960(obj, &sp18, (s16 *)&sp1A, diff, time0, dl);
            if (obj->f30 >= obj->f34) {
                obj->f28 = (u16)((obj->f1A * D_800373F0[obj->f18]) >> 15);
                obj->f2E = (u16)((obj->f1A * D_800373F0[0x7F - obj->f18]) >> 15);
                obj->f30 = obj->f34;
                obj->f1C = obj->f28;
                obj->f1E = obj->f2E;
            } else {
                obj->f1C = (s16)func_8001EFE4((f32)obj->f1C, obj->f30, obj->f26, obj->f24);
                obj->f1E = (s16)func_8001EFE4((f32)obj->f1E, obj->f30, obj->f2C, obj->f2A);
            }
            if (obj->f1C == 0) {
                obj->f1C = 1;
            }
            if (obj->f1E == 0) {
                obj->f1E = 1;
            }
            if (obj->f3C->f8 == 12) {
                obj->f18 = obj->f3C->fC;
            }
            if (obj->f3C->f8 == 11) {
                obj->f30 = 0;
                obj->f1A = (s16)((obj->f3C->fC * obj->f3C->fC) >> 15);
                obj->f34 = *(s32 *)&obj->f3C->f10;
            }
            if (obj->f3C->f8 == 16) {
                obj->f20 = ((u16 *)D_800373F0)[obj->f3C->fC];
                obj->f22 = ((u16 *)D_800373F0)[0x7F - obj->f3C->fC];
            }
            obj->f38 = 1;
            break;
        case 14:
            rec = obj->f3C;
            if (rec->fA != 0) {
                obj->f8(obj, 8, 0);
            }
            obj->f8(obj, 5, rec->fC);
            obj->f8(obj, 9, 0);
            break;
        case 15:
            dl = func_8001E960(obj, &sp18, (s16 *)&sp1A, diff, time0, dl);
            obj->f8(obj, 4, 0);
            break;
        case 0:
            {
                Nw2EnvRec *rr = obj->f3C;
                void *g = D_80037510;
                *(s32 *)((u8 *)rr->fC + 0xD8) = 0;
                func_80020854(g, rr->fC);
            }
            break;
        default:
            dl = func_8001E960(obj, &sp18, (s16 *)&sp1A, diff, time0, dl);
            obj->f8(obj, obj->f3C->f8, obj->f3C->fC);
            break;
        }
        budget -= diff;
        sp1A = (u16)(sp1A + (diff << 1));
        {
            Nw2EnvRec *old = obj->f3C;
            Nw2EnvRec *next = old->f0;
            obj->f3C = next;
            if (next == NULL) {
                obj->f40 = 0;
            }
            func_800207E8(old);
        }
    }
    dl = func_8001E960(obj, &sp18, (s16 *)&sp1A, budget, time0, dl);
    if (obj->f30 > obj->f34) {
        obj->f30 = obj->f34;
    }
    return dl;
}
