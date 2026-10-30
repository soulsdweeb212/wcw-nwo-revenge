/* @header
 * func_8001CC50
 * VRAM 0x8001CC50 | ROM 0x1D850 | size 0xC8
 * asm: asm/nonmatchings/main/func_8001CC50.s
 */
#include "common.h"

typedef struct Obj {
    s32 f0;
    s32 f4;
    s32 f8;
    s16 fC;
    s16 fE;
    u16 f10;
} Obj;

extern Obj *D_80037248;
extern Obj *D_80037250;
extern s32 nw2DisableInterrupts(void);
extern void nw2RestoreInterrupts(s32);
extern void func_8001CE40(s32, void *);
extern void func_800266B4(s32, void *);
extern void func_800265AC(void *);

/* Sets a thread's priority (arg0==NULL means the current thread). If it changed,
 * re-queues the thread on its wait queue (unless current or state 1) and
 * preempts the current thread when the runnable queue now outranks it. Runs
 * with interrupts disabled. */
void func_8001CC50(Obj *arg0, s32 arg1) {
    s32 s1 = arg1;
    Obj *s0 = arg0;
    s32 s2 = nw2DisableInterrupts();

    if (s0 == NULL)
        s0 = D_80037250;
    if (s0->f4 != s1) {
        s0->f4 = s1;
        if (s0 != D_80037250 && s0->f10 != 1) {
            func_8001CE40(s0->f8, s0);
            func_800266B4(s0->f8, s0);
        }
        if (D_80037250->f4 < D_80037248->f4) {
            D_80037250->f10 = 2;
            func_800265AC(&D_80037248);
        }
    }
    nw2RestoreInterrupts(s2);
}
