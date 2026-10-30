/* @header
 * func_80027040
 * VRAM 0x80027040 | ROM 0x27C40 | size 0x54
 * asm: asm/nonmatchings/main/func_80027040.s
 */
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

/* Reset the PI DMA queue node and its associated counters. */
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
