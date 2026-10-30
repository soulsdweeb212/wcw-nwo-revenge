/* @header
 * func_800C7E6C
 * VRAM 0x800C7E6C | ROM 0xBB30C | size 0x31C
 * asm: asm/nonmatchings/code_800BBA00/func_800C7E6C.s
 */
#include "common.h"

typedef struct {
    s8 f0;
    u8 pad1[3];
    s16 f4;
    s16 f6;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 fE;
    u8 pad10[0x10];
    u64 flags;
    u8 pad28[4];
    u32 f2C;
    u8 pad30[0x28];
    s32 f58;
    u8 pad5C[0x304];
    u16 f360;
    u8 pad362[0x24];
    s16 f386;
} Nw2F5C;

extern void *D_800FAF5C;
extern void *D_800F9B00;
extern s8 D_800FADB8;

void func_800A9290(void *);
void func_800D427C(void *, s16, s32);
s16 func_800BF2FC(void *);
s8 func_800B71F8(void *, s32, s32);
s8 func_800D4198(s16);
void func_800A7C40(void *, s8, s16);
void func_800D4AD0(void *);
void beginEntityActionA8D8C(void *);
void func_800A6C48(void *, s32);
s16 func_800D5438(void *, s32);
void beginPairedEntityActions(void *, s32, void *, s32);

#define SELF ((Nw2F5C *)D_800FAF5C)
#define OTHER ((Nw2F5C *)D_800F9B00)

/* Five-state paired grapple/throw on D_800FAF5C's fC.  State 0 calls
 * func_800A9290 and falls into state 1, which raises flag 0x1000000000 and, when
 * the partner (D_800F9B00) f360 bit0 is set, sends the contact animation
 * OTHER->f8+1 and optionally performs a counter via func_800B71F8(0xC) on a
 * low-range partner (func_800BF2FC < 0x81), setting OTHER->f360 bit1.  State 2
 * animates the impact (OTHER->f8-1, then re-sends 0x44/0x45 for f8 0xF56/0xF58) or
 * the follow-up (SELF->f8+4).  State 3 ends it: for f8 0xF56/0xF58 it sends 0xE8F
 * and copies the partner's heading f58 before advancing, otherwise it finishes
 * with beginEntityActionA8D8C or func_800A6C48(0x2B).  State 4 starts the paired throw
 * (0x53/0x54) and sets f2C to 0x440/0x442 on both actors. */
void func_800C7E6C(void) {
    switch (SELF->fC) {
    case 0:
        func_800A9290(D_800FAF5C);
        SELF->fC++;
        /* fallthrough */
    case 1:
        SELF->flags |= 0x1000000000ULL;
        if (!(OTHER->f360 & 1)) {
            break;
        }
        func_800D427C(D_800FAF5C, (s16)(OTHER->f8 + 1), 6);
        if (!(SELF->flags & 9)) {
            if ((s16)func_800BF2FC(D_800FAF5C) < 0x81) {
                if (func_800B71F8(D_800FAF5C, 0, 0xC)) {
                    OTHER->f360 |= 2;
                }
            }
        }
        SELF->fC++;
        break;
    case 2:
        if (SELF->f4 <= 0) {
            if (OTHER->f360 & 2) {
                func_800D427C(D_800FAF5C, (s16)(OTHER->f8 - 1), 1);
                if (SELF->f8 == 0xF56) {
                    func_800A7C40(D_800FAF5C, D_800FADB8, (func_800D4198(0x2EE) == 0) ? 0x45 : 0x44);
                } else if (SELF->f8 == 0xF58) {
                    func_800A7C40(D_800FAF5C, D_800FADB8, (func_800D4198(0x2EE) == 0) ? 0x45 : 0x44);
                }
            } else {
                func_800D427C(D_800FAF5C, (s16)(SELF->f8 + 4), 0);
            }
            SELF->fC++;
        }
        break;
    case 3:
        if (SELF->f4 <= 0) {
            func_800D4AD0(D_800FAF5C);
            if (SELF->f8 == 0xF56 || SELF->f8 == 0xF58) {
                func_800D427C(D_800FAF5C, 0xE8F, 1);
                SELF->f58 = OTHER->f58;
                SELF->fC++;
            } else if (SELF->f8 < 0xF52) {
                beginEntityActionA8D8C(D_800FAF5C);
            } else {
                func_800A6C48(D_800FAF5C, 0x2B);
            }
        }
        break;
    case 4:
        func_800D427C(D_800FAF5C, (s16)func_800D5438(D_800FAF5C, 0), 1);
        beginPairedEntityActions(D_800FAF5C, 0x53, D_800F9B00, 0x54);
        SELF->f2C = 0x440;
        if (SELF->f386 == 0x45) {
            SELF->f2C = 0x442;
        }
        OTHER->f2C = SELF->f2C;
        break;
    }
}
