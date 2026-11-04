/* @header
 * func_800BF9B8
 * VRAM 0x800BF9B8 | ROM 0x6C128 | size 0xCC8
 * asm: asm/nonmatchings/code_80090000/func_800BF9B8.s
 */
#include "common.h"

/* The current scene script entry: its type picks the case below. */
typedef struct { s8 type; s8 f1; } Scene;
/* One timeline key: `n` frames long, low two bits of f2 copied to D_800EA0B4. */
typedef struct { u16 n; u16 f2; s16 v[6]; } Key;
/* 0x1C-byte per-player records at D_800DF344; [1].state is D_800DF360. */
typedef struct { s16 state; s16 timer; u8 pad[0x18]; } Pl;
/* 0xEC-byte character records: D_800E7642, D_800E772E and D_800E781A are [0..2].f6. */
typedef struct { s16 f0, f2, f4; u16 f6; u8 pad8[0xEC - 8]; } Ch;

extern s32 D_800E9F70;
extern Key **D_800DF320;
extern s32 D_800DF314, D_800DF318, D_800DF324, D_800DF328;
extern Scene *D_800DF31C;
extern s32 D_800EA0B4, D_800DF3A8, D_800DF3B0, D_800DF304;
extern Ch D_800E763C[];
extern s32 D_800D5744, D_800D5748, D_800D574C, D_800D5750;
extern s32 D_800E74C4, D_800E79BC;
extern s16 D_800E74D2;
extern Pl D_800DF344[];
void func_800C3094(s32, s32, s32, s32, s32, s32);
s32 func_8000DEE4(s32);
void func_8000DF78(s32);
void accumulateColorChannels(s32, s32, s32);

/* Channel 0 (D_800D5744 = playing id, D_800D5748 = handle) and channel 1 (D_800D574C/D_800D5750). */
static inline void playBgm(s32 id) {
    if (D_800D5744 != id) {
        D_800D5744 = id;
        if (D_800D5748 >= 0) {
            func_8000DF78(D_800D5748);
            D_800D5748 = -1;
        }
        D_800D5748 = func_8000DEE4(id);
    }
}

static inline void stopBgm(void) {
    if (D_800D5744 != 0) {
        D_800D5744 = 0;
        if (D_800D5748 >= 0) {
            func_8000DF78(D_800D5748);
            D_800D5748 = -1;
        }
    }
}

static inline void playBgm2(s32 id) {
    if (D_800D574C != id) {
        D_800D574C = id;
        if (D_800D5750 >= 0) {
            func_8000DF78(D_800D5750);
            D_800D5750 = -1;
        }
        D_800D5750 = func_8000DEE4(id);
    }
}

static inline void stopBgm2(void) {
    if (D_800D574C != 0) {
        D_800D574C = 0;
        if (D_800D5750 >= 0) {
            func_8000DF78(D_800D5750);
            D_800D5750 = -1;
        }
    }
}

void func_800BF9B8(void *s) {
    Key *e;
    s32 t, i;
    s32 a, b, j;

    if (D_800E9F70 < 0) {
        func_800C3094(-1, 0, 1000, 0, 0xFF, 0x80);
    } else {
        func_800C3094(-1, 0, 1000, -1000, 0xFF, 0x80);
    }
    e = *D_800DF320;
    t = D_800DF314;
    for (i = 0; e[i].n != 0; i++) {
        if (t < e[i].n) {
            break;
        }
        t -= e[i].n;
    }
    D_800DF328 = i;
    D_800DF324 = t;
    D_800EA0B4 = e[i].f2 & 3;
    switch (D_800DF31C->type) {
    case 0:
        D_800DF3A8 = 0;
        D_800DF318 = D_800DF314;
        if (D_800DF31C->f1 != 0) {
            if (D_800DF314 == 0x40) {
                D_800E763C[1].f6 = 1;
            }
            if (D_800DF314 == 0xA0) {
                D_800E763C[0].f6 = 1;
            }
        }
        break;
    case 1:
        switch (D_800DF328) {
        case 0:
            playBgm(0x416);
            D_800DF318 = 0;
            break;
        case 1:
            break;
        case 2:
            D_800DF318 = D_800DF324;
            break;
        case 3:
            D_800DF318 = D_800DF324 + 0x1F;
            break;
        case 4:
        case 5:
            playBgm(0x415);
            D_800DF318 = 0xF0;
            break;
        case 6:
            D_800DF318 = 0xF0 - D_800DF324;
            if (D_800DF318 < 0xBE) {
                D_800DF318 = 0xBE;
            }
            if (D_800DF324 == 0x50) {
                func_8000DEE4(0x417);
            }
            break;
        }
        break;
    case 2:
        stopBgm();
        if (D_800DF314 == 0x40) {
            func_8000DEE4(0x417);
        }
        if (D_800DF314 == 0x10) {
            D_800E763C[0].f6 = 1;
        }
        break;
    case 3:
        playBgm(0x418);
        if (D_800DF31C->f1 == 0) {
            D_800DF318 = D_800DF324 * 3 / 8;
            if (D_800DF314 == 0x80) {
                D_800E763C[1].f6 = 1;
                func_8000DEE4(0x413);
                playBgm2(0x414);
            }
        } else {
            if (D_800E763C[2].f6 == 0) {
                D_800E763C[2].f6 = 1;
                accumulateColorChannels(0xFF, 0xFF, 0xFF);
                func_8000DEE4(0x40C);
            }
            if (D_800E763C[1].f6 == 0) {
                D_800E763C[1].f6 = 1;
            }
            func_800C3094(-1, 0, 200, 1000, 0xFF, 0x40);
            if (D_800DF314 == 0x28) {
                func_8000DEE4(0x41B);
            }
            D_800DF318 = 0x60;
            D_800EA0B4 = 1;
        }
        break;
    case 4:
        if (D_800E763C[1].f6 == 0) {
            D_800E763C[1].f6 = 1;
        }
        func_800C3094(-1, 0, 200, 1000, 0xFF, 0x40);
        D_800DF318 = 0xE4;
        break;
    case 5:
        stopBgm2();
        if (D_800DF314 == 8) {
            func_8000DEE4(0x41A);
        }
        break;
    case 6:
        if (D_800DF314 == 8) {
            func_8000DEE4(0x41B);
        }
        func_800C3094(-1, 0, 200, 1000, 0xFF, 0x40);
        break;
    case 7:
        func_800C3094(-1, 0, 200, 1000, 0xFF, 0x40);
        break;
    case 8:
        D_800DF3B0 = 4;
        playBgm(0x419);
        playBgm2(0x414);
        if (D_800E763C[1].f6 == 0) {
            D_800E763C[1].f6 = 1;
        }
        func_800C3094(-1, 0, 200, 1000, 0xFF, 0x40);
        D_800DF318 = 0xE4;
        break;
    case 9:
        stopBgm2();
        func_800C3094(-1, 0, 200, -1000, 0xFF, 0x40);
        if (D_800DF314 == 0x14) {
            func_8000DEE4(0x424);
        }
        break;
    case 10:
        stopBgm();
        func_800C3094(-1, 0, 1000, -1000, 0x40, 0x30);
        if ((D_800DF314 & 0x1F) == 0) {
            func_8000DEE4(0x412);
        }
        D_800DF3A8 = 1;
        break;
    case 11:
    case 12:
        D_800DF318 = D_800DF314;
        break;
    case 15:
        if (D_800DF314 < 8) {
            D_800DF318 = D_800DF314 * 32;
        } else {
            D_800DF318 = 0x100;
        }
        break;
    case 41:
        if (D_800DF314 < 8) {
            D_800DF318 = 0;
        } else if (D_800DF314 < 0x10) {
            D_800DF318 = (D_800DF314 - 8) * 32;
        } else {
            D_800DF318 = 0x100;
        }
        break;
    case 20:
        D_800DF3B0 = 0x40;
        if (D_800DF314 < 0x19) {
            D_800DF318 = 0;
        } else if (D_800DF314 < 0x1D) {
            D_800DF318 = (D_800DF314 - 0x19) * 64;
        } else {
            D_800DF318 = 0x100;
        }
        if (D_800DF314 == 0x19) {
            D_800E74C4 = 3;
        }
        func_800C3094(-1, 0, 1000, 0, 0xFF, (0xFF - D_800E74D2) / 4 + 0x40);
        break;
    case 30:
    case 31:
        D_800DF318 = D_800DF314 * 400 / 120;
        break;
    case 34:
        if (D_800DF314 >= 0x38) {
            D_800DF318 = (D_800DF314 - 0x37) * 8;
        }
        break;
    case 35:
        if (D_800DF31C->f1 == 0) {
            D_800DF318 = D_800DF314 * 2 + 0x60;
        } else {
            D_800DF318 = D_800DF314 * 2 + 0x1F2;
            for (j = 1; j < 4; j++) {
                if (D_800DF344[j].state == 1) {
                    if (D_800DF344[j].timer < 0x10) {
                        a = D_800DF344[j].timer * 16;
                        b = D_800DF344[j].timer * 8;
                    } else {
                        a = 0xFF;
                        b = 0x7F;
                    }
                } else if (j == 1 && D_800DF344[1].state == 2) {
                    a = 0xFF;
                    b = 0x7F;
                } else {
                    b = 0;
                    a = 0;
                }
                func_800C3094(j, 0, 1000, -1000, a, b);
            }
        }
        break;
    case 36:
    case 43:
        if (D_800DF314 == 0xF) {
            D_800E763C[0].f6 = 1;
        }
        break;
    case 46:
        if (D_800DF314 >= 0x3D) {
            D_800DF318 = (D_800DF314 - 0x3C) * 8;
        } else {
            D_800DF318 = 0;
        }
        break;
    case 50:
        if (D_800DF314 < 0x4B) {
            func_800C3094(-1, 0, 1000, -1000, 0, 0);
            D_800E79BC = 0xFF;
        } else if (D_800DF314 < 0x69) {
            func_800C3094(-1, 0, 1000, -1000, (D_800DF314 - 0x4B) * 8, (D_800DF314 - 0x4B) * 4);
            D_800E79BC = 0xFF - (D_800DF314 - 0x4B) * 8;
        } else {
            func_800C3094(-1, 0, 1000, -1000, 0xFF, 0x80);
            D_800E79BC = 0;
        }
        break;
    case 51:
        D_800DF318 = D_800DF314;
        func_800C3094(-1, 0, 1000, -1000, 0x40, 0x30);
        if (D_800E763C[1].f6 == 0) {
            D_800E763C[1].f6 = 1;
        }
        if ((D_800DF314 & 0x1F) == 0) {
            func_8000DEE4(0x412);
        }
        break;
    case 52:
        D_800E79BC = 0xFF;
        if (D_800DF31C->f1 == 0) {
            if (D_800DF314 < 0xFD) {
                D_800DF318 = 0;
                if (D_800DF314 == 0x96 || D_800DF314 == 0x87 || D_800DF314 == 0x78) {
                    if (D_800DF314 == 0x96) {
                        D_800E763C[2].f6 = 0x300;
                    } else if (D_800DF314 == 0x87) {
                        D_800E763C[2].f6 = 0x200;
                    } else {
                        D_800E763C[2].f6 = 0x100;
                    }
                    accumulateColorChannels(0xFF, 0xFF, 0xFF);
                }
            } else if (D_800DF314 < 0x131) {
                D_800DF318 = (D_800DF314 - 0x111) * 8;
            } else {
                D_800DF318 = 0xFF;
            }
            if (D_800DF314 < 0x78) {
                func_800C3094(-1, 0, 1000, -1000, 0x40, 0x30);
            } else if (D_800DF314 < 0xFD) {
                func_800C3094(-1, 0, 1000, 0, 0xFF, (0xFF - D_800E74D2) / 4 + 0x40);
            } else {
                func_800C3094(-1, 0, 1000, 0, 0xFF, 0x80);
            }
        } else {
            if (D_800DF314 == 0x4B) {
                func_8000DEE4(0x411);
            }
            if (D_800DF314 < 0x4B) {
                if (D_800E763C[2].f6 == 0) {
                    D_800E763C[2].f6 = 1;
                }
                D_800DF318 = 0;
            } else if (D_800DF314 < 0x53) {
                D_800DF304 = 0;
                D_800E763C[2].f6 = 0;
                D_800DF318 = (D_800DF314 - 0x4B) * 32;
            } else {
                D_800E74C4 = 3;
                D_800DF318 = 0x100;
            }
        }
        break;
    }
}
