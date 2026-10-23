#include "common.h"

typedef struct { u32 w0, w1; } Cmd20090;
typedef struct Save20090 Save20090;
struct Save20090 { s32 f0; Cmd20090 *(*build)(Save20090 *, s32, s32, s32, s32); };
typedef struct { Save20090 *child; u8 pad[0x10]; u32 list; } Obj20090;
extern char D_8003B8A0[], D_8003B8A4[];
void func_8001CEE0(char *, char *, s32);

Cmd20090 *func_80020090(Obj20090 *obj, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    Save20090 *child;
    Cmd20090 *a, *b, *c, *d;

    child = obj->child;
    if (child == 0) func_8001CEE0(D_8003B8A0, D_8003B8A4, 0x22);
    arg4 = child->build(child, arg1, arg2, arg3, arg4);
    a = (Cmd20090 *)arg4; arg4 += 8;
    b = (Cmd20090 *)arg4; arg4 += 8;
    {
        unsigned int c440 = 0x04400580;
        c = (Cmd20090 *)arg4; arg4 += 8;
        d = (Cmd20090 *)arg4; arg4 += 8;
        a->w0 = 0x08000000;
        a->w1 = (arg2 * 2) & 0xFFFF;
        b->w1 = c440;
        b->w0 = 0x0D000000;
        c->w0 = 0x08000000;
        c->w1 = (arg2 * 4) & 0xFFFF;
        d->w0 = 0x06000000;
        d->w1 = obj->list;
        return (Cmd20090 *)arg4;
    }
}
