/* @header
 * func_80015068
 * VRAM 0x80015068 | ROM 0x15C68 | size 0xB0
 * asm: asm/nonmatchings/main/func_80015068.s
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

/* Recomputes the audio stream's target time (+0x70) from its current/base time
 * and the +0xD2/+0xD4 offsets (or saturates when +0xBA is 0x7FFF), and copies
 * the rate fields into their shadow bytes. */
void func_80015068(Nw15068Obj *p) {
    if (p->fBA != 0x7FFF) {
        if (p->fD2 != 0) {
            p->f70 = p->f58 + ((u32)p->fD2 << 8);
        } else {
            p->f70 = p->f50 - ((u32)p->fD4 << 8);
        }
    } else {
        p->f70 = 0x7FFFFFFF;
    }
    p->fE3 = 1;
    p->fE4 = p->fE0;
    p->fE5 = p->fDF;
}
