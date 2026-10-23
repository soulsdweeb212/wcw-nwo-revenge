#include "common.h"

u64 insertTimer(void *);
void programTimerCountdown(u64);
extern void *g_80038820;
typedef struct { s32 z0, z1; u64 f8; u64 f10; s32 f18, f1C; } Node;
#define P ((Node *)arg0)

/* Initialises a timer node arg0 (zeroing its head, storing the two countdown
 * values, the two payload words, registering it and, when it is the active
 * timer, programming the hardware countdown). */
s32 func_80026FA0(void *arg0, s32 a1, u64 arg2, u64 arg3, s32 a6, s32 a7) {
    u64 r;
    P->z0 = 0;
    P->z1 = 0;
    P->f10 = arg2;
    P->f8 = arg3;
    if (arg2 == 0) P->f10 = arg3;
    P->f18 = a6;
    P->f1C = a7;
    r = insertTimer(arg0);
    if (*(void **)g_80038820 == arg0) programTimerCountdown(r);
    return 0;
}
