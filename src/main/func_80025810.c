#include "common.h"

extern void *g_80038820;
extern s32 D_80065120;
extern s32 D_80070480;
extern s32 D_80070B20;
extern s32 D_80070B24;

s32 func_8001C7E0(s32, s32);
s32 func_8001CE80(s32);
void func_8001C5B0(s32, s32);
s64 func_80028624(u32, u32, u32, u32);
s64 func_80028528(u32, u32, u32, u32);

typedef struct {
    void *next;
    void *prev;
    u64 a;
    u64 b;
    s32 c0;
    s32 c1;
} Node80038820;

void func_80027040(void) {
    Node80038820 *p = g_80038820;
    *(u64 *)&D_80070B20 = 0;
    D_80065120 = 0;
    D_80070480 = 0;
    p->b = 0;
    p->a = 0;
    p->prev = p;
    p->next = p;
    p->c0 = 0;
    p->c1 = 0;
}

/* Start a transfer into the fixed buffer 0x1FC007C0. Polls the controller/PI
 * status at 0xA4800018; if busy (bits 0-1) returns -1. Otherwise latches the
 * source address func_8001CE80(addr) into 0xA4800000 and the destination into
 * 0xA4800004 (channel 0) or 0xA4800010 (channel 1), with direction setup via
 * func_8001C7E0/func_8001C5B0. Returns 0. */
s32 func_80025810(s32 channel, s32 addr) {
    if (*(volatile s32 *)0xA4800018 & 3) {
        return -1;
    }
    if (channel == 1) {
        func_8001C7E0(addr, 0x40);
    }
    *(volatile s32 *)0xA4800000 = func_8001CE80(addr);
    if (channel == 0) {
        *(volatile s32 *)0xA4800004 = 0x1FC007C0;
    } else {
        *(volatile s32 *)0xA4800010 = 0x1FC007C0;
    }
    if (channel == 0) {
        func_8001C5B0(addr, 0x40);
    }
    return 0;
}

s64 func_80028860(u32 a0, u32 a1, u32 a2, u32 a3) {
    if (a2) {
        return func_80028528(a0, a1, a2, a3);
    }
    return func_80028624(a0, a1, a2, a3);
}

s64 func_80028880(u32 a0, u32 a1, u32 a2, u32 a3) {
    if (a2) {
        func_80028528(a0, a1, a2, a3);
        return ((s64)a0 << 32) | (u32)a1;
    }
    func_80028624(a0, a1, a2, a3);
    return ((s64)0 << 32) | (u32)a3;
}
