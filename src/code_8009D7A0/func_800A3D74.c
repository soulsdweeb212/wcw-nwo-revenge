#include "common.h"

extern void *D_800EB408;
extern void *D_800EB40C;
s32 func_800D2BEC(void *, void *, void *, f32, u16, s32);
void func_800B68A0(void *, void *, void *);
s8 func_800A83DC(void *, void *);
void func_800D4AD0(void *);
void func_800A6C48(void *, s32);

typedef struct {
    u8 pad0[0x20];
    u64 flags;
    u8 pad28[0x362 - 0x28];
    s8 f362;
} Nw2ActA3D74;

/* Interaction action on D_800EB408 with target D_800EB40C: drive the
 * interaction (flag mask 0xFFFFE); when the entry value is 1 run the connect
 * handler; and once the timer expires and the check succeeds, mark the entity
 * f362 = -1, clear flag 0x40000000 and finish with command 0x2B. */
void func_800A3D74(void) {
    Nw2ActA3D74 *e;

    func_800D2BEC(D_800EB408, D_800EB40C, 0, 4.0f, 0, 0xFFFFE);
    if (*(s16 *)((u8 *)D_800EB408 + 4) == 1) {
        func_800B68A0(D_800EB408, D_800EB408, D_800EB40C);
    }
    if (*(s16 *)((u8 *)D_800EB408 + 4) <= 0 && func_800A83DC(D_800EB408, D_800EB40C) == 0) {
        e = D_800EB408;
        e->f362 = -1;
        e->flags &= ~0x0000000040000000ULL;
        func_800D4AD0(D_800EB408);
        func_800A6C48(D_800EB408, 0x2B);
    }
}
