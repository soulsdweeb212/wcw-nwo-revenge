#include "common.h"

/* Sets action/state bits (e->f38) for an entity based on its animation/state id
 * (e->fA) and substate (e->fC), unless the "present" bit 0x200 or the inhibit
 * bit 0x40 in the global flag words is set, or the entity is already tagged
 * (e->f355 == e->id). Values 1/2 encode the two conditions. */
typedef struct {
    s8 id;
    u8 pad1[0x9];
    s16 fA;
    s16 fC;
    u8 pad2[0x12];
    u64 flags;
    u8 pad3[0x10];
    u8 f38;
    u8 pad4[0x31C];
    s8 f355;
} Entity;

extern u8 D_8007E228[];
extern u8 D_8007EF30[];

void func_800D93DC(void *arg0) {
    Entity *e;
    s32 bits;
    e = arg0;
    if (!(*(u16 *)(D_8007E228 + 0x58) & 0x200)) {
        return;
    }
    if (*(u16 *)(D_8007EF30 + 0x170) & 0x40) {
        return;
    }
    if (e->f355 == e->id) {
        return;
    }
    bits = 0;
    switch (e->fA) {
    case 1:
        if (e->flags & 0x80) {
            bits = 1;
        }
        break;
    case 129:
        bits = 2;
        if (e->fC < 2) {
            bits = 1;
        }
        break;
    case 23:
        if (e->fC == 1 && (e->flags & 0x80)) {
            bits = 1;
        }
        break;
    case 3:
        if (e->flags & 0x80) {
            if (e->fC < 4) {
                bits = 1;
            }
        }
        break;
    case 9:
        bits = 1;
        break;
    case 10:
        if (e->fC == 4 || e->fC == 7) {
            bits = 2;
        }
        break;
    }
    e->f38 |= bits;
}
