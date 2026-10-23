#include "common.h"

typedef struct {
    s32 f0;
    s16 f4;
    s16 f6;
    s32 f8;
    s16 fC;
    s16 fE;
    u8 pad10[0x10];
    u64 flags;
    u8 pad28[0xD];
    u8 f35;
    u8 pad36[0xC];
    s8 f42;
} Nw2A1B94;

s32 func_800D2B64(void *, f32, u16, s32);
void func_800D427C(void *, s32, s32);
void func_800D4AD0(void *);
void beginEntityActionA8D8C(void *);
void func_8000C784(s8);
extern s8 D_800FADB8;
extern s16 D_800E3262[];

#define P ((Nw2A1B94 *)D_800EB408)

/* State machine (state P->fC) that picks an animation action for the entity
 * at D_800EB408 based on its flags (u64 +0x20) and byte at +0x35. */
void func_800A1B94(void) {
    s16 id;
    u8 b;

    func_800D2B64(D_800EB408, 2.0f, 0, 0xFFFFE);
    switch (P->fC) {
    case 0:
        P->flags |= 0x1400000000ULL;
        func_8000C784(D_800FADB8);
        b = P->f35;
        if (b & 4) {
            func_800D427C(D_800EB408, 0x105D, 3);
            P->fC = 2;
        } else if (b & 8) {
            func_800D427C(D_800EB408, D_800E3262[P->f42], 1);
            P->fC++;
        } else {
            if (P->flags & 0x8000000) {
                id = 0x105D;
            } else {
                id = 0x105C;
            }
            func_800D427C(D_800EB408, id, 3);
            P->fC = 2;
        }
        break;
    case 1:
        if (P->flags & 0x200000) {
            id = 0x1062;
        } else {
            id = 0x1061;
        }
        func_800D427C(D_800EB408, id, 6);
        P->fC++;
        break;
    case 2:
        if (P->f4 <= 0) {
            func_800D4AD0(D_800EB408);
            beginEntityActionA8D8C(D_800EB408);
        }
        break;
    }
}
