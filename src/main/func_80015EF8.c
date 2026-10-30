/* @header
 * func_80015EF8
 * VRAM 0x80015EF8 | ROM 0x16AF8 | size 0x34
 * asm: asm/nonmatchings/main/func_80015EF8.s
 */
#include "common.h"

typedef struct {
    u8 pad0[0x58];
    s32 f58;
    s32 f5C;
    u8 pad60[0x50];
    s32 fB0;
    s32 fB4;
    u8 padB8[0x25];
    u8 fDD;
    u8 padDE[0x1B];
    u8 fF9;
    u8 fFA;
} Nw15468Obj;

typedef struct {
    u8 pad0[0x50];
    u64 f50;
    u64 f58;
    u8 pad60[0x10];
    u64 f70;
    u8 pad78[0x42];
    u16 fBA;
    u8 padBC[0x16];
    u16 fD2;
    u16 fD4;
    u8 padD6[9];
    u8 fDF;
    u8 fE0;
    u8 padE1[2];
    u8 fE3;
    u8 fE4;
    u8 fE5;
} Nw15068Obj;

/* Copy arg2 bytes from arg0 to arg1. */
void func_80015EF8(u8 *arg0, u8 *arg1, s32 arg2) {
    s32 i;

    for (i = arg2 - 1; i != -1; i--) {
        *arg1 = *arg0;
        arg0++;
        arg1++;
    }
}
