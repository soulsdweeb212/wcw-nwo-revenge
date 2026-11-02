/* @header
 * func_800B600C
 * VRAM 0x800B600C | ROM 0x6277C | size 0x1C4
 * asm: asm/nonmatchings/code_80090000/func_800B600C.s
 */
#include "common.h"

typedef struct { s32 a; s32 b; s32 c; s32 d; } N;
extern N D_800E6BA0[];
s32 func_8002A2FC(s32, s32);
void func_8002A5F4(s32);

static inline N *find(s32 id) {
    s32 i = 0;
    N *p = D_800E6BA0;
    for (; i < 0x80; i++) {
        if (p->a == id) {
            break;
        }
        p++;
    }
    return i != 0x80 ? p : 0;
}

static inline N *get(s32 id, u16 t) {
    N *e;

    if (id < 0) {
        id = func_8002A2FC(id, t);
        if (id == 0) {
            return 0;
        }
        e = find(id);
        if (e) {
            return e;
        }
        e = find(-1);
        if (e == 0) {
            func_8002A5F4(id);
            return 0;
        }
        e->a = id;
        e->b = id;
        e->c = 2;
        e->d |= 2;
        return e;
    }
    if (id == 0 || (u32)id >= 0x1DEA) {
        return 0;
    }
    e = find(id);
    if (e) {
        return e;
    }
    e = find(-1);
    if (e == 0) {
        return 0;
    }
    e->a = id;
    e->c = 2;
    e->d |= 1;
    return e;
}

s32 func_800B600C(s32 id, u16 t) {
    N *e;

    if (id == -1) {
        return 0;
    }
    e = get(id, t);
    if (e == 0) {
        return 0;
    }
    if (e->d & 1) {
        return 0;
    }
    e->c++;
    return e->b;
}
