/* @header
 * runMatchPhaseStateMachine  (originally func_800B7CF4)
 * VRAM 0x800B7CF4 | ROM 0xAB194 | size 0x584
 * asm: asm/nonmatchings/code_8009D7A0/func_800B7CF4.s
 */
#include "common.h"

/* runMatchPhaseStateMachine: drives the pre-match/round setup phases through the
 * D_800EB465 state value (0..4).  It resets subsystems, plays the intro frame
 * playback, waits for the countdown, then latches each of the four players'
 * selected link data (ports/links/options) into the D_8007E228 bss block. */

extern s8 D_800EB465, D_800EB464, D_800EB466;
extern s16 D_800EB460, D_800EB462, D_800EB470, D_800EB472, D_800FADD0;
extern u8 D_800FADCE, D_800FADCF, D_800FADB9[];
extern u16 D_800F99BA, D_800E3970[];
extern s32 D_800FABD8;
extern u8 D_8007E8C0[], D_8007E228[], D_8006E178[], D_800FAF84[], D_800F9B58[], D_800F9D20[], D_800FA05C[], D_800FA05D[], D_800FA05E[], D_800FA05F[], D_800FA060[];
void func_800BC7C8(void);
void func_800D548C(void);
void func_800DA8B4(void *, s32, s32);
void func_800B8D04(void);
void func_800B9148(void);
void func_800E1AD8(void);
void D_800BAC30(void);
void func_800BBA00(void);
void func_8009786C(s32);
void stepRecordedFramePlayback(void);
void func_800C0004(void);
s8 func_800B8D8C(void);
s8 func_800B93B0(void);
s8 func_800B9194(void);
s8 func_800B955C(u64);
s8 pickPresentControllerEntity(void);
void func_80097EF4(s32);
#define AU8(n, o) (*(volatile u8 *)((u8 *)&n + (o)))
#define AU16(n, o) (*(volatile u16 *)((u8 *)&n + (o)))
#define AU64(n, o) (*(volatile u64 *)((u8 *)&n + (o)))
#define AB16(b, o) (*(volatile u16 *)((u8 *)(b) + (o)))

void runMatchPhaseStateMachine(void) {
    s16 player;
    s32 outBase = 0;
    switch (D_800EB465) {
    case 0:
        func_800BC7C8();
        D_800EB466 = 0;
        *(s16 *)(D_8007E8C0 + 0x6C) = 0;
        D_800EB460 = 0;
        D_800EB472 = 0;
        D_800FADD0 = 0;
        func_800D548C();
        func_800DA8B4(D_800FAF84, 0, 0);
        func_800DA8B4(D_800F9B58, 0, 0);
        func_800B8D04();
        func_800B9148();
        func_800E1AD8();
        D_800BAC30();
        func_800BBA00();
        D_800EB465++;
        break;
    case 1:
        func_800BBA00();
        if (++D_800EB460 >= 31) {
            D_800FADCE |= 1;
            func_8009786C(9);
            D_800EB465++;
        }
        break;
    case 2:
        if (D_800FABD8 & 2) {
            stepRecordedFramePlayback();
            break;
        }
        func_800C0004();
        func_800BBA00();
        if (func_800B8D8C()) D_800EB465++;
        if (func_800B93B0()) D_800EB465++;
        if (func_800B9194()) D_800EB465++;
        if (func_800B955C(0x2000ULL)) D_800EB465++;
        if (func_800B955C(0x1000ULL)) D_800EB465++;
        if (func_800B955C(0x800ULL)) D_800EB465++;
        break;
    case 3:
        D_800FADCF |= 0x40;
        D_800EB464 = pickPresentControllerEntity();
        func_800BBA00();
        D_800EB462 = 0;
        D_800EB465++;
        break;
    case 4:
        if (D_800FADCF & 0x20)
            D_800F99BA = D_800E3970[D_800EB464] | 0x20;
        if (D_800FABD8 & 2)
            stepRecordedFramePlayback();
        else
            func_800BBA00();
        if (++D_800EB462 == 90)
            func_80097EF4(D_800EB470);
        if (D_800EB462 >= 91) {
            s32 recOffset;
            D_800EB462 = 91;
            for (player = 0; player < 4; player++) {
                recOffset = player * 12;
                if (AB16(D_8006E178 + 6, recOffset) & 0xD000)
                    D_800EB462 = 30000;
            }
        }
        if (D_800EB462 >= 30000) {
            D_800FADCF |= 0x80;
            if (!D_800EB472) {
                for (player = 0; player < 4; player++) {
                    s32 entityOffset = player * 0x3B0;
                    u8 linkValue;
                    outBase = player * 8;
                    AU8(D_8007E228, 0x60 + outBase) = AU16(D_800F9D20, entityOffset);
                    AU8(D_8007E228, 0x61 + outBase) = AU8(D_800FA05C, entityOffset);
                    AU8(D_8007E228, 0x64 + outBase) = AU8(D_800FA05D, entityOffset);
                    AU8(D_8007E228, 0x62 + outBase) = AU8(D_800FA05E, entityOffset);
                    AU8(D_8007E228, 0x63 + outBase) = AU8(D_800FA05F, entityOffset);
                    AU8(D_8007E228, 0x65 + outBase) = AU8(D_800FA060, entityOffset);
                    linkValue = AU8(D_800FADB9, player);
                    AU8(D_8007E228, 0x66 + outBase) = 0;
                    AU8(D_8007E228, 0x67 + outBase) = linkValue;
                    if (AU64(D_800F9D30, entityOffset) & 0x4000000000000ULL)
                        AU8(D_8007E228, 0x66 + outBase) = 2;
                    {
                        s32 playerIdx = (s16)player;
                        s32 entityOff = playerIdx * 0x3B0;
                        if (AU64(D_800F9D30, entityOff) & 0x400000000ULL) {
                            s32 outSlot = playerIdx * 8;
                            AU8(D_8007E228, 0x66 + outSlot) |= 1;
                        }
                    }
                }
            }
        }
        break;
    }
}
