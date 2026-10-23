#include "common.h"

extern s32 D_80036F54;

typedef struct {
    u8 pad00[0x30];
    u8 *f30;
    u8 *f34;
    u8 pad38[0x0C];
    u8 *f44;
    s32 f48;
} Nw2Obj36F54;

typedef struct {
    u8 pad0[4];
    s32 *(*fn)(s32, s32 *);
} Nw2Tbl36F54;

extern void func_80018140(void *);
extern s32 *func_8001A400(s32, s32 *);

f32 nw2Sqrtf(f32 arg0) {
    return __builtin_sqrtf(arg0);
}

/* Emit the two setup commands, call the current object's function-table entry, then
 * append two more commands; returns the next free command slot. */
s32 *func_8001A400(s32 arg0, s32 *arg1) {
    Nw2Obj36F54 *obj = (Nw2Obj36F54 *)D_80036F54;
    s32 *p;
    s32 *q;
    arg1[0] = 0x020004E0;
    arg1[1] = 0x2E0;
    p = ((Nw2Tbl36F54 *)obj->f30)->fn(arg0, arg1 + 2);
    q = p;
    p = p + 2;
    q[0] = 0x0C007FFF; q[1] = 0x07C004E0;
    p[0] = 0x0C007FFF; p[1] = 0x09300650;
    return p + 2;
}

/* Look up the record at D_80036F54->f34 + arg0*4 + 0x24 and return its field. */
s32 func_8001A3B0(s32 arg0) {
    s32 t = (s32)(arg0 << 16) >> 14;
    func_80018140(((Nw2Obj36F54 *)D_80036F54)->f34 + (t + 0x24));
    t = t + (s32)((Nw2Obj36F54 *)D_80036F54)->f34;
    return *(s32 *)(t + 0x24);
}

/* Emit func_8001A400's commands, then append the 0x0D000000 and 0x062E0000 commands. */
s32 *func_8001A360(s32 arg0, s32 *arg1) {
    Nw2Obj36F54 *obj;
    s32 *p;
    s32 *q;
    p = func_8001A400(arg0, arg1);
    q = p;
    p = p + 2;
    q[0] = 0x0D000000;
    obj = (Nw2Obj36F54 *)D_80036F54;
    p[0] = 0x062E0000;
    p[1] = obj->f48;
    return p + 2;
}
