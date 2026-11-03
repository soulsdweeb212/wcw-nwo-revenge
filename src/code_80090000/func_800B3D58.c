/* @header
 * func_800B3D58
 * VRAM 0x800B3D58 | ROM 0x604C8 | size 0x668
 * asm: asm/nonmatchings/code_80090000/func_800B3D58.s
 */
#include "common.h"

typedef struct { s32 f0; u16 f4; u8 f6[4]; u16 fA; u8 fC[4]; } Ent;
typedef struct { u8 pad0[8]; u16 f8; } Pl;
typedef struct { u8 pad0[8]; u16 mode; u8 padA[0x30 - 0xA]; Pl *f30; } Game;
typedef struct { s32 f0[4]; u8 pad10[0x60]; s32 f70[4]; } Cfg2;
typedef struct { u8 pad0[0x688]; s32 ids[4]; } Cfg;

extern Game D_8007EF30;
extern Cfg2 D_8007E8C0;
extern Cfg D_8007E228;
extern s32 D_800EA094[];
extern s32 D_800EA220[][11];
extern Ent D_800EA0D8[];
extern u8 D_800E7C58[][8];
void func_80021C40(void *, void *, s32);
void func_80021F60(void *, s32);
void func_800B34F8(s32, s32);
void func_800BAA64(Ent *, s32);

static inline s32 slotOf(s32 n) {
    return D_8007E8C0.f0[n] ? D_800EA094[D_8007E8C0.f0[n]] : -1;
}

static inline void record(s32 n) {
    Ent *e = &D_800EA0D8[D_800EA094[D_8007E8C0.f0[n]]];

    e->f0 = D_800EA220[n][10];
    func_80021C40(D_800E7C58[D_8007E8C0.f0[n]], e->f6, 4);
    e->f4 = D_8007E228.ids[n] | ((D_8007E8C0.f70[n] & 3) << 12);
    func_80021F60(e->fC, 4);
    e->fA = 0;
}

void func_800B3D58(void) {
    s32 m;

    switch (D_8007EF30.mode & 0xF0) {
    case 0x10:
        if (slotOf(0) >= 0) {
            record(0);
        }
        if (slotOf(1) >= 0) {
            record(1);
        }
        break;
    case 0x20:
        if (slotOf(0) >= 0) {
            func_800B34F8(D_800EA094[D_8007E8C0.f0[0]], 0);
        }
        if (slotOf(2) >= 0) {
            func_800B34F8(D_800EA094[D_8007E8C0.f0[2]], 2);
        }
        break;
    case 0x40:
        if (slotOf(0) >= 0) {
            func_800B34F8(D_800EA094[D_8007E8C0.f0[0]], 0);
        }
        if (slotOf(2) >= 0) {
            record(2);
        }
        break;
    default:
        if (slotOf(0) >= 0) {
            record(0);
        }
        if (slotOf(1) >= 0) {
            record(1);
        }
        if (slotOf(2) >= 0) {
            record(2);
        }
        if (slotOf(3) >= 0) {
            record(3);
        }
        break;
    }
    if (D_8007EF30.mode & 0x8000) {
        m = D_8007EF30.f30->f8;
    } else {
        switch (D_8007EF30.mode & 0xF0) {
        case 0x20:
            m = 1;
            break;
        case 0x80:
            m = 8;
            break;
        case 0x40:
            m = 7;
            break;
        default:
            m = 0;
            break;
        }
    }
    func_800BAA64(D_800EA0D8, (m << 4) | 0xF);
}
