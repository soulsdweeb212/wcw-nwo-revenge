/* @header
 * func_80092554
 * VRAM 0x80092554 | ROM 0x3ECC4 | size 0x25C
 * asm: asm/nonmatchings/code_80090000/func_80092554.s
 */
#include "common.h"

/* func_80092554: emits part-colour commands into the display-list buffer
 * *arg0 for the given part index arg1. Indices >= 0x14 emit four adjacent
 * parts (each loaded 4b texture writes two RGB gradient words, with the fade
 * mask 0x07000000 in the alpha byte) and update the render colour registers
 * for the first part. Indices 0..0x13 emit the single part, set the render
 * mode word and, for even indices below 8, seed a new 0x178-stride effect
 * record with the part's position (arg2/arg3), radius and scale. *arg0 is
 * advanced past the emitted commands. */
extern s32 loadResourceTexture4b(void **, void *, s32);
extern void accumulateColorChannels(s32, s32, s32);
extern u8 updateEntityGrabActionState[];
extern u8 func_800D6658[];
extern u8 func_800DBB80[];

void func_80092554(void **arg0, s32 arg1, s16 arg2, s16 arg3) {
    void *sp10;
    s32 i;
    s32 s0;
    s32 s2;
    s32 s3, s4, s5;
    void *q2;

    sp10 = *arg0;
    if (arg1 >= 0x14) {
        u8 *p = updateEntityGrabActionState + 0x160;
        s32 fpmask;
        s32 s7;
        s0 = arg1 - 0x14;
        i = 0;
        fpmask = 0x07000000;
        s7 = 0x420;
        s5 = 0xC;
        s4 = 0xE;
        s3 = 0xA;
        s2 = 8;
        do {
            if (s0 >= 0 && s0 < p[0xC]) {
                loadResourceTexture4b(&sp10, p, s0);
                q2 = sp10;
                sp10 = (u8 *)q2 + 8;
                ((s32 *)q2)[0] = (s2 & 0xFF) << 16 | (s3 & 0xFF) << 8 | (s4 & 0xFF) | fpmask;
                ((s32 *)q2)[1] = (s2 & 0xFF) << 16 | (s4 & 0xFF) << 8 | (s5 & 0xFF);
                if (i == 0 && s0 == 0) {
                    accumulateColorChannels(0xFF, 0xFF, 0xFF);
                    *(s32 *)(func_800DBB80 + 0x1D4) = s7;
                }
            }
            s5 += 8;
            s4 += 8;
            s3 += 8;
            s2 += 8;
            i += 1;
            s0 -= 2;
        } while (i < 4);
    } else if (arg1 >= 0) {
        if (loadResourceTexture4b(&sp10, updateEntityGrabActionState + 0x180, arg1) != 0) {
            void *q3 = sp10;
            sp10 = (u8 *)q3 + 8;
            ((s32 *)q3)[0] = 0x07000206;
            ((s32 *)q3)[1] = 0x604;
        }
        if (arg1 == 0) {
            *(s32 *)(func_800DBB80 + 0x1D4) = 0x422;
        }
        if ((arg1 < 8) && !(arg1 & 1)) {
            u8 *p;
            s32 a3;
            s32 sh;
            s32 c800, c40, c40b, c100, c3;
            accumulateColorChannels(0xF, 0xF, 0xF);
            sh = arg1 << 6;
            c800 = 0x800;
            c40 = 0x40;
            c40b = 0x40;
            c100 = 0x100;
            c3 = 3;
            a3 = 0;
            p = func_800D6658 + 0x6F8;
            while (a3 < 0x30 && *(s16 *)(p + 0x160) >= 0) {
                a3++;
                p += 0x178;
            }
            if (a3 != 0x30) {
                *(s16 *)(p + 0x170) = sh * 12;
                *(s16 *)(p + 0x160) = 0;
                *(s16 *)(p + 0x166) = c40;
                *(s16 *)(p + 0x162) = c40b;
                *(s16 *)(p + 0x16C) = arg2;
                *(s16 *)(p + 0x16E) = arg3;
                *(s16 *)(p + 0x172) = c800;
                *(s16 *)(p + 0x168) = 0x320;
                *(s16 *)(p + 0x16A) = c3;
                *(s16 *)(p + 0x164) = c100;
                *(s32 *)(p + 0x174) = 0;
            }
        }
    }
    *arg0 = sp10;
}
