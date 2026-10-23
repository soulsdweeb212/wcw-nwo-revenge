#include "common.h"

extern u8 *D_800FABD0;
extern u8 *D_800FAF80;
extern u8 *D_800FADDC;
extern u8 *D_800FAF58;
extern u8 *D_800F9B60;
extern u8 D_8007E228[];
extern u8 D_8007EF30[];
extern s16 D_800FA822;
extern f64 D_800E4DA0;
extern f64 D_800E4DD0;
extern u8 D_800E3418;
extern u8 D_800E3430;
s8 func_800AB1B0(void);
s8 func_800AB2B4(void);
s8 func_800AB43C(void);
s8 func_800D4198(s16);
void func_800AD958(s32);
void func_800ADA38(void *);

/* Per-frame action dispatcher for the wrestler action record at D_800FABD0.
 * It bails out if the higher-level handlers (func_800AB1B0 / func_800AB2B4)
 * already claimed the frame, or while the game-state gate is closed
 * (D_8007E228 bit0x200 clear or D_8007EF30 bit0x40 set).  It then inspects the
 * paired entity objects (D_800FAF58, and depending on the flags D_800FAF80 or
 * D_800FADDC), rejecting a candidate whose s16 +0x10 is below 0x40, and finally
 * selects the next action id: func_800AD958(id) for direct selections, or
 * func_800ADA38(table) for a threshold-table selection.  The branch on the f32
 * timer at +0x34 (D_800E4DA0 / D_800E4DD0) plus the state field +0x22 is the
 * core of the state machine. */
void func_800AABF8(void) {
    u8 *self, *other, *attachment;
    if (func_800AB1B0())
        return;
    if (func_800AB2B4())
        return;
    if ((*(u16 *)(D_8007E228 + 0x58) & 0x200) && !(*(u16 *)(D_8007EF30 + 0x170) & 0x40)) {
        self = D_800FAF58;
        if (!(*(u64 *)(self + 0x20) & 0x200)) {
            if (*(u64 *)(self + 0x358) & 0x600000000000ULL) {
                if (D_800FA822 == -1) {
                    if (*(u64 *)(self + 0x358) & 0x400000000000ULL) {
                        other = D_800FAF80;
                        goto chkobj;
                    } else {
                        goto dispatch;
                    }
                } else {
                    if (*(s16 *)(D_800FAF80 + 0x10) < 0x40) {
                        func_800AD958(0x15);
                        return;
                    }
                    other = D_800FADDC;
                }
            chkobj:
                if (*(s16 *)(other + 0x10) < 0x40) {
                    func_800AD958(0x15);
                    return;
                }
            }
        }
    }
dispatch:
    if (*(f32 *)(D_800FABD0 + 0x34) < D_800E4DA0) {
        switch ((s16)(*(u16 *)(D_800FABD0 + 0x22) - 2)) {
        case 0:
            if (func_800D4198(*(s16 *)(D_800FABD0 + 0x12))) {
                func_800AD958(4);
                return;
            }
            goto set13;
        case 6:
        case 7:
            if ((*(u16 *)(D_8007E228 + 0x58) & 0x200) &&
                !(*(u16 *)(D_8007EF30 + 0x170) & 0x40) &&
                !(*(u64 *)(D_800FAF58 + 0x20) & 0x200)) {
                func_800ADA38(&D_800E3418);
                return;
            }
            if (func_800AB43C())
                return;
            attachment = *(u8 **)(D_800FAF58 + 0x364);
            if (*(u64 *)(attachment + 0x38) & 0x2000000) {
                if (func_800D4198(0x1F4))
                    func_800AD958(0x30);
                else
                    func_800AD958(0x15);
            } else {
                func_800AD958(0x15);
            }
            return;
        case 4:
        case 8:
            if (func_800D4198(*(s16 *)(D_800FABD0 + 0x12))) {
                func_800AD958(4);
                return;
            }
            break;
        default:
            func_800ADA38(&D_800E3430);
            return;
        }
    set13:
        func_800AD958(0x13);
        return;
    } else {
        if ((*(u16 *)(D_8007E228 + 0x58) & 0x200) &&
            !(*(u16 *)(D_8007EF30 + 0x170) & 0x40) &&
            !(*(u64 *)(D_800FAF58 + 0x20) & 0x200)) {
            func_800ADA38(&D_800E3418);
            return;
        }
        if (func_800AB43C())
            return;
        attachment = *(u8 **)(D_800FAF58 + 0x364);
        if (*(u64 *)(attachment + 0x38) & 0x2000000) {
            if (*(f32 *)(D_800FABD0 + 0x34) < D_800E4DD0) {
                switch (*(s16 *)(D_800FABD0 + 0x22)) {
                case 6:
                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                    if (func_800D4198(0x1F4))
                        func_800AD958(0x30);
                    else
                        func_800AD958(0x15);
                    break;
                default:
                    if (*(u64 *)(D_800F9B60 + 0x20) & 0x1000000000ULL)
                        func_800AD958(0x15);
                    else if (func_800D4198(0x1F4))
                        func_800AD958(0x30);
                    else
                        func_800AD958(0x15);
                    break;
                }
            } else {
                func_800AD958(0x15);
            }
        } else {
            func_800AD958(0x15);
        }
        return;
    }
}
