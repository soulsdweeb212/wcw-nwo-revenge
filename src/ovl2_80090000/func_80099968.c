/* @header
 * func_80099968
 * VRAM 0x80099968 | ROM 0x8CE08 | size 0x4C4
 * asm: asm/nonmatchings/ovl2_80090000/func_80099968.s
 */
#include "common.h"

typedef struct { u32 w0, w1; } G;
typedef struct {
    u8 pad0[6];
    u16 pressed;
    u8 pad8[4];
} Pad;
typedef struct { s32 flags; } Node;

s16 func_80098960(G **, s32);
void func_80098D54(G **, s32);
s32 func_8000DEE4(s16);
void MusHandleSetReverb(s32, s32);
void func_800B8C94(void);
void func_80003418(s8);
s8 func_80003464(void);

extern Pad D_8006E178[];
extern u8 D_8007E8C0[];
extern u32 D_8007E848;
extern u8 D_8007EF30[];
extern s8 D_800E2F58;
extern s8 D_800E2F59;
extern s8 D_800E2F5A;
extern G *D_800EB1D0;
extern Node *D_800EB1D4;
extern G *D_800EB29C[];
extern s16 D_800EB2A8;
extern s16 D_800EB2AA;
extern s8 D_800EB2AC[];
extern s16 D_800EB2B6;
extern u16 D_800F9AA2;

s16 func_80099968(s16 arg0) {
    G *g;
    s16 close = 0;
    s16 ret = 0;

    g = D_800EB29C[D_800E2F58];
    if (arg0 != 0) {
        D_800EB2B6 = arg0 - 1;
        if (func_80098960(&g, 1) == 0) {
            D_800EB2A8 = 0;
            D_800EB2AA = 0;
        } else {
            if (D_800EB2A8 == 0) {
                if (D_8006E178[arg0 - 1].pressed & 0x800) {
                    do {
                        if (--D_800EB2AA < 0) {
                            D_800EB2AA = 5;
                        }
                    } while (D_800EB2AC[D_800EB2AA] < 0);
                    MusHandleSetReverb(func_8000DEE4(0x409), 0);
                }
                if (D_8006E178[arg0 - 1].pressed & 0x400) {
                    do {
                        if (++D_800EB2AA >= 6) {
                            D_800EB2AA = 0;
                        }
                    } while (D_800EB2AC[D_800EB2AA] < 0);
                    MusHandleSetReverb(func_8000DEE4(0x409), 0);
                }
                if (D_8006E178[arg0 - 1].pressed & 0x8000) {
                    switch (D_800EB2AA) {
                    case 0:
                        ret = 2;
                        break;
                    case 3:
                        D_8007E8C0[0x66F] ^= 1;
                        break;
                    case 4:
                        D_8007E8C0[0x66E] ^= 1;
                        D_800F9AA2 ^= 1;
                        break;
                    case 5:
                        D_8007EF30[3] ^= 1;
                        break;
                    default:
                        D_800EB2A8 = 2;
                        break;
                    }
                    MusHandleSetReverb(func_8000DEE4(0x408), 0);
                }
            } else {
                if (D_8006E178[arg0 - 1].pressed & 0xC00) {
                    D_800EB2A8 = ((D_800EB2A8 - 1) ^ 1) + 1;
                    MusHandleSetReverb(func_8000DEE4(0x409), 0);
                }
                if (D_8006E178[arg0 - 1].pressed & 0x8000) {
                    if (D_800EB2A8 == 1) {
                        ret = D_800EB2AA + 2;
                        func_800B8C94();
                        D_8007E848 = 0;
                        func_80003418(D_800E2F5A);
                    } else {
                        D_800EB2A8 = 0;
                    }
                    MusHandleSetReverb(func_8000DEE4(0x408), 0);
                }
            }
            func_80098D54(&g, 1);
        }
    } else if (D_800E2F59 != 0) {
        close = func_80098960(&g, 0);
    } else {
        func_80098960(&g, 1);
    }
    g->w0 = 0xDF000000;
    g->w1 = 0;
    g++;
    D_800EB1D0 = D_800EB29C[D_800E2F58++];
    D_800E2F58 %= 3;
    if (close) {
        if (!(D_800EB1D4->flags & 0x80)) {
            func_80003418(D_800E2F5A);
        }
        D_800EB1D4->flags |= 0x80;
    } else {
        if (D_800EB1D4->flags & 0x80) {
            D_800E2F5A = func_80003464();
            func_80003418(D_800E2F5A / 2);
            MusHandleSetReverb(func_8000DEE4(0x410), 0);
        }
        D_800EB1D4->flags &= ~0x80;
        if (ret == 0) {
            ret = 1;
        }
    }
    return ret;
}
