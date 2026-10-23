#include "common.h"

typedef struct Nw2AimAction {
    u8 pad0[2];
    s16 f2;
    s16 f4;
    u8 pad6[2];
    u16 f8;
    u8 padA[8];
    s16 f12;
    s16 f14;
    s16 f16;
    u8 pad18[0x16];
    u16 f2E;
    u8 pad30[0x2C];
    u32 f5C;
} Nw2AimAction;

typedef struct Nw2AimEntity {
    u8 pad0[0xA];
    u16 fA;
} Nw2AimEntity;

extern Nw2AimAction *D_800FABD0;
extern Nw2AimEntity *D_800F9B60;
extern f64 D_800E5220;
extern f64 D_800E5228;
s8 func_800D4198(s16);

/* Aim/pitch updater for an action record: derives a distance-based scale from
 * f16, scales the aim angle f12 with two double-precision factors, and if the
 * randomised aim test passes writes the pitch constant 0xC030 to f8. Unless the
 * action is already in the steady state f14 == 3, it then resets the aim fields
 * and copies the entity's mode (D_800F9B60 + 0xA) into f2E. */
void func_800AFEC8(void) {
    f32 scale;
    s16 angle;
    Nw2AimAction *action;
    Nw2AimEntity *entity;

    if (D_800FABD0->f16 >= 0x81) {
        scale = 0.9f;
    } else {
        scale = 1.2f;
        if (D_800FABD0->f16 >= 0x41) {
            scale = 1.0f;
        }
    }
    scale = (f32)((f64)scale * D_800E5220);
    angle = D_800FABD0->f12;
    if (angle < 0x2BC) {
        scale = (f32)((f64)scale * D_800E5228);
    }
    if (func_800D4198((s16)(s32)((f32)angle * scale))) {
        D_800FABD0->f8 = 0xC030;
    }
    action = D_800FABD0;
    if (action->f14 != 3) {
        entity = D_800F9B60;
        action->f2 = 0;
        action->f4 = 0;
        action->f2E = entity->fA;
        action->f5C &= ~7;
    }
}
