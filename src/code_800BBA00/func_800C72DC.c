/* @header
 * func_800C72DC
 * VRAM 0x800C72DC | ROM 0xBA77C | size 0x4B0
 * asm: asm/nonmatchings/code_800BBA00/func_800C72DC.s
 */
#include "common.h"

extern s32 D_800E3CA0[];

void func_800B68A0(void *, void *, void *);
void func_800A7364(void *);
void beginEntityActionA8D8C(void *);
void func_800D427C(void *, s16, s32);
void func_800D4AD0(void *);
void func_800D25D0(void *, f32);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D2B64 */
s32 func_800D2B64(void *, f32, u16, s32);
#endif
s8 func_800C2634(void *, u16);
s8 func_800B71F8(void *, s32, s32);
s16 func_800B6DEC(void *, s32, s32);
#ifdef TARGET_PC
/* func_800C778C takes a second argument, the id it returns when hitInfo has none of the hit class bits 0x10000000,
 * 0x20000000 and 0x40000000; the two calls below leave it out. On the N64, $a1 held a leftover there: the address
 * D_800F9B78 that func_800B68A0 last put in it (when hitInfo bit 31 is clear and step 0 called it), or else whatever
 * the state dispatcher's last call (func_800D7B54) left. Neither is an animation id. The calls run only with hitInfo
 * 0x20000 or 0x80000 set, which func_800C3A78 sets after it has or-ed in a class bit (from move.unk39B, 0 to 5), and
 * which this function's step 0 sets together with one. So the PC passes PC_NO_HIT_CLASS_ID (-1), which is never
 * returned while a class bit is set. If none is set, the N64's leftover only mattered when no later test in step 0
 * replaced it; the check before the animation starts (see below) stops the program in exactly that case. */
#define PC_NO_HIT_CLASS_ID (-1)
s16 func_800C778C(Wrestler *w, s32 arg1);
static s16 pc_hitReactionId(Wrestler *w) {
    return func_800C778C(w, PC_NO_HIT_CLASS_ID);
}
#else
s16 func_800C778C(void *);
#endif

void func_800C72DC(void) {
    s16 s0;
    u32 flags;
    u16 r;
    s32 b;

    switch (D_800FAF5C->step) {
    case 0:
        if ((s32)D_800FAF5C->hitInfo >= 0) {
            func_800B68A0(D_800F9B64, D_800F9B64, D_800FAF5C);
        }
        flags = D_800FAF5C->hitInfo;
        if (flags & 0x800) {
            switch ((s16)(D_800F9B64->moveId - 0xD1)) {
            case 0:
            case 1:
            case 7:
            case 12:
            case 13:
            case 15:
            case 16:
            case 17:
            case 19:
            case 22:
            case 23:
            case 24:
            case 25:
                flags = D_800FAF5C->hitInfo | 0x20000;
                D_800FAF5C->hitInfo = flags;
                if (D_800F9B64->move.flags & 0x40) {
                    D_800FAF5C->hitInfo = flags | 0x20000000;
                    s0 = 0x1058;
                } else {
                    D_800FAF5C->hitInfo = flags | 0x10000000;
                    s0 = 0x1049;
                }
                break;
            case 9:
            case 10:
                s0 = 0x1058;
                D_800FAF5C->hitInfo |= 0x20020000;
                break;
            case 4:
            case 5:
            case 6:
            case 8:
            case 18:
                D_800FAF5C->hitInfo |= 0x90010000;
                func_800A6C48(D_800FAF5C, 0x2F);
                return;
            }
            if (D_800FAF5C->hitInfo & 0x1000) {
                s0++;
            }
            func_800D427C(D_800FAF5C, s0, 3);
            D_800FAF5C->step++;
            return;
        }
        if (flags & 0x8000) {
            switch ((s8)D_800F9B64->move.unk39B) {
            case 0:
                s0 = 0x102E;
                break;
            case 1:
                s0 = 0x1030;
                break;
            case 2:
                s0 = 0x1032;
                break;
            case 3:
                s0 = 0x1034;
                break;
            case 4:
                s0 = 0x1063;
                break;
            case 5:
                s0 = 0x1036;
                break;
            }
        }
        if (D_800FAF5C->hitInfo & 0x20000) {
#ifdef TARGET_PC
            /* the missing second argument: see pc_hitReactionId above */
            s0 = pc_hitReactionId(D_800FAF5C);
#else
            s0 = func_800C778C(D_800FAF5C);
#endif
        }
        if (D_800FAF5C->hitInfo & 0x80000) {
            b = (s8)D_800F9B64->move.unk3A1;
            s0 = b + 0x106D;
            if (b == 0) {
#ifdef TARGET_PC
                /* as above */
                s0 = pc_hitReactionId(D_800FAF5C);
#else
                s0 = func_800C778C(D_800FAF5C);
#endif
            }
        }
        flags = D_800FAF5C->hitInfo;
        if (flags & 0x40000) {
            s0 = (s8)D_800F9B64->move.unk3A1 + 0x1055;
        }
        if (flags & 0x100000) {
            s0 = 0xF00;
        }
        if (flags & 0x200000) {
            s0 = 0xEFE;
        }
        if (flags & 0x4000000) {
            if (func_800B71F8(D_800FAF5C, 0, 0x12)) {
                s0 = 0xEFE;
            } else {
                s0 = 0xF03;
            }
        }
        flags = D_800FAF5C->hitInfo;
        if (flags & 0x8000000) {
            s0 = 0x1056;
        }
        if (flags & 0x2400000) {
            D_800FAF5C->heading = D_800E3CA0[D_800FAF5C->ringSide];
            if (D_800FAF5C->hitInfo & 0x2000000) {
                D_800FAF5C->stateTimer = func_800B6DEC(D_800FAF5C, 0, 0);
                s0 = 0x10B2;
            } else {
                s0 = 0x10AB;
            }
            func_800A7364(D_800FAF5C);
            func_800D427C(D_800FAF5C, s0, 2);
        } else {
            if (flags & 0x1800000) {
                func_800A6C48(D_800FAF5C, 0x62);
                return;
            }
#ifdef TARGET_PC
            /* s0 is final here (apart from the +1 below, which the 0x20000/0x80000 bits rule out). If it still holds
             * func_800C778C's no-class answer, the N64 would have used its leftover $a1 as the id: stop instead. */
            if (s0 == PC_NO_HIT_CLASS_ID) {
                port_fatal("func_800C72DC: hitInfo 0x%08X has no hit class bit; the N64 used a leftover $a1 as the animation id",
                           (unsigned)D_800FAF5C->hitInfo);
            }
#endif
            if (!(flags & 0xE7E0000)) {
                if (flags & 0x1000) {
                    s0++;
                }
            }
            if (s0 == 0xF03) {
                func_800D427C(D_800FAF5C, 0xF03, 0);
            } else {
                func_800D427C(D_800FAF5C, s0, 3);
            }
        }
        D_800FAF5C->step++;
        break;
    case 1:
        if (D_800FAF5C->hitInfo & 0x4000000) {
            goto l7754;
        }
        func_800D25D0(D_800FAF5C, 4.0f);
        if (D_800FAF5C->hitInfo & 0x4000000) {
            goto l7754;
        }
        r = func_800D2B64(D_800FAF5C, 2.0f, 0, 0xFFFFE);
        if (r == 0) {
            goto l7754;
        }
        if (!(D_800FAF5C->flags & 0x40)) {
            goto l7754;
        }
        if (!(D_800FAF5C->hitInfo & 0x80E0000)) {
            goto l7754;
        }
        if (D_800FAF5C->animFrame >= 5) {
            goto l7754;
        }
        if (!func_800C2634(D_800FAF5C, r)) {
            goto l7754;
        }
        func_800A6C48(D_800FAF5C, 0x62);
        break;
l7754:
        if (D_800FAF5C->animFramesLeft > 0) {
            break;
        }
        func_800D4AD0(D_800FAF5C);
        beginEntityActionA8D8C(D_800FAF5C);
        break;
    }
}
