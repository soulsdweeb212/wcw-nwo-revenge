#include "common.h"

/* identical to func_8002F05C in WRESTLEMANIA 2000 (matched), with its names changed by decompdecomp */
/* Emit `size` samples of a WObj stream as display-list entries: advance the
 * source until it passes the cursor, then pipe each chunk through the display
 * object's unk4 callback, bumping the read cursor; returns the new write
 * pointer and stores the emitted word count in *countOut. */
typedef struct WObj {
    u8 pad0[8];
    s32 (*unk8)(void *);
    s32 padC;
    s32 unk10;
} WObj;

typedef struct DObj {
    u8 pad0[4];
    s32 (*unk4)(struct DObj *, void *, s32, s32, void *);
    s32 (*unk8)(struct DObj *, s32, s32 *);
} DObj;

typedef struct G {
    s32 unk0;
    u8 pad4[0x18];
    s32 unk1C;
    s32 unk20;
    u8 pad24[0x14];
    DObj *unk38;
    u8 pad3C[0xC];
    s32 unk48;
} G;

extern G *D_80037510;
extern s32 func_80020894(G *arg0, s32 arg1);
extern s32 func_80020928(G *arg0, void **arg1);
extern void func_80020800(G *arg0);

u8 *func_8002060C(u8 *arg0, s32 *arg1, s32 *arg2, s32 arg3) {
    G *g;
    u8 *dst;
    s32 *src;
    s32 remaining;
    s32 tick;
    s32 delta;
    void *obj;
    s16 flag;
    s32 chunk;
    DObj *dobj;

    g = D_80037510;
    remaining = arg3;
    dst = arg0;
    src = arg2;
    flag = 0;
    if (g->unk0 == 0) {
        *arg1 = 0;
    } else {
        tick = func_80020928(g, &obj);
        g->unk1C = tick;
        delta = tick - g->unk20;
        while (delta < remaining) {
            g->unk1C &= ~0xF;
            tick = ((WObj *)obj)->unk8(obj);
            tick = func_80020894(g, tick);
            ((WObj *)obj)->unk10 += tick;
            tick = func_80020928(g, &obj);
            g->unk1C = tick;
            delta = tick - g->unk20;
        }
        g->unk1C &= ~0xF;
        if (remaining > 0) {
            do {
                chunk = g->unk48;
                if (remaining < chunk) {
                    chunk = remaining;
                }
                *(s32 *)(dst + 0) = 0x07000000;
                *(s32 *)(dst + 4) = 0;
                dobj = g->unk38;
                dobj->unk8(dobj, 6, src);
                dst = (u8 *)dobj->unk4(dobj, &flag, chunk, g->unk20, dst + 8);
                remaining -= chunk;
                src += chunk;
                g->unk20 += chunk;
            } while (remaining > 0);
        }
        *arg1 = (dst - arg0) >> 3;
        func_80020800(g);
    }
    return dst;
}
