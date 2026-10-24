#include "common.h"

typedef struct { s32 f0; u8 pad4[8]; f32 fC; f32 f10; u8 pad14[0x18]; s16 f2C; s16 f2E; void *f30; } Elem;
typedef struct { s16 ob[3]; u16 flag; s16 tc[2]; u8 cn[4]; } Vtx16;
typedef struct { u8 pad0[0xC]; Vtx16 *fC; void *f10; Elem *f14; u8 rest[0xDC - 0x18]; } Slot;
typedef struct { Elem *e[10]; } ElemTab;
extern Slot D_80059D90[];
extern ElemTab D_8005A100[];
extern s8 D_80036D20[4];
extern u8 D_80036D24[4];
extern void *allocateHeap(u32);
extern s32 func_80001544(void *);
extern s32 func_800015AC(void *, s32);
extern void func_8000F710(void *, s32);
extern void buildFadeColorDisplayList(void *);
extern s32 func_8001C580(void);

void func_8000FAF8(s32 idx) {
    Slot *s;
    Elem *e;
    Vtx16 *v;
    void *dl;
    s32 i;
    s16 row;
    u32 j, k;
    s32 x;
    s32 u;

    s = &D_80059D90[idx];
    s->fC = allocateHeap(0x540);
    dl = allocateHeap(0x200);
    s->f10 = dl;
    buildFadeColorDisplayList(dl);
    for (i = 0; i < 6; i++) {
        s->f14 = NULL;
        func_800015AC(s, 0);
        func_80001544(s);
        e = s->f14;
        e->f0 = 1;
        e->f2C = 0x18;
        e->f2E = 0;
        e->f30 = (u8 *)s->fC + i * 0xC0;
        e->fC = -187 + i * 74;
        e->f10 = 180.0f;
        D_8005A100[idx].e[i] = e;
    }
    v = s->fC;
    for (row = 0; row < 7; row++) {
        x = row * 74 - 0xE0;
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 4; k++) {
                v->ob[0] = x;
                u = func_8001C580() % 8 + 0xE0;
                v->tc[0] = (x + u) << 5;
                v->tc[1] = D_80036D20[k] << 5;
                v->cn[0] = D_80036D24[k];
                v->cn[1] = D_80036D24[k];
                v->cn[2] = D_80036D24[k];
                v->cn[3] = 0xFF;
                v++;
            }
        }
    }
    func_8000F710(s->fC, idx);
}
