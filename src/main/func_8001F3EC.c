/* @header
 * func_8001F3EC
 * VRAM 0x8001F3EC | ROM 0x1FFEC | size 0xC0
 * asm: asm/nonmatchings/main/func_8001F3EC.s
 */
#include "common.h"

typedef struct Obj Obj;
struct Obj {
    Obj *child;                         /* @0x0 */
    s32 f4;
    s32 (*callback)(Obj *, s32, s32);   /* @0x8 */
    s32 pad[3];
    s32 f18, f1c, f20, f24, f28, f2c, f30;
};

/* Object command handler: 1 stores the new child; 4 resets the timers and
 * forwards command 4 to the child; 9 marks the object done and forwards 9; 7
 * stores f18; 8 marks f1c; anything else is forwarded to the child verbatim.
 * Always returns 0. */
s32 func_8001F3EC(Obj *arg0, s32 arg1, s32 arg2) {
    Obj *p = arg0;
    switch (arg1) {
    case 1: arg0->child = (Obj *)arg2; break;
    case 4:
        p->f20 = 0; p->f24 = 1; p->f30 = 0; p->f1c = 0;
        arg0 = arg0->child;
        if (arg0) arg0->callback(arg0, 4, 0);
        break;
    case 9:
        p->f30 = 1;
        arg0 = arg0->child;
        if (arg0) arg0->callback(arg0, 9, 0);
        break;
    case 7: p->f18 = arg2; break;
    case 8: p->f1c = 1; break;
    default:
        arg0 = arg0->child;
        if (arg0) arg0->callback(arg0, arg1, arg2);
        break;
    }
    return 0;
}
