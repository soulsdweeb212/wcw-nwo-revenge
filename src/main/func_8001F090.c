#include "common.h"

typedef struct {u32 w0,w1;} Cmd1F090;
typedef struct Child1F090 Child1F090;
struct Child1F090 {s32 f0;Cmd1F090 *(*draw)(Child1F090 *,s32,s32,s32,Cmd1F090 *);};
typedef struct {s32 pad[5];s32 count;s32 f18;Child1F090 **children;} Group1F090;
Cmd1F090 *func_8001F090(Group1F090 *arg0, s32 arg1, s32 arg2, s32 arg3, Cmd1F090 *dl) {
    Group1F090 *obj = arg0;
    s32 i;
    Child1F090 **list = obj->children;
    { Cmd1F090 *p = dl++; p->w0 = 0x02000440; p->w1 = arg2 * 2; }
    { Cmd1F090 *p = dl++; p->w0 = 0x02000580; p->w1 = arg2 * 2; }
    for (i = 0; i < obj->count; i++) {
        dl = list[i]->draw(list[i], arg1, arg2, arg3, dl);
        { Cmd1F090 *p = dl++; p->w0 = 0x08000000; p->w1 = (arg2 * 2) & 0xffff; }
        { Cmd1F090 *p = dl++; p->w0 = 0x0c007fff; p->w1 = 0x06c00440; }
        { Cmd1F090 *p = dl++; p->w0 = 0x0c007fff; p->w1 = 0x08000580; }
    }
    return dl;
}
