/* @header
 * initStatePools17B40  (originally func_80017B40)
 * VRAM 0x80017B40 | ROM 0x18740 | size 0x270
 * asm: asm/nonmatchings/main/initStatePools17B40.s
 */
#include "common.h"

/* Initialises the global D_80036F54 state from a config record:
 * copies the config fields into the state header, allocates the shared
 * sub-pool (D_80036F54->f34), a small helper pool (->f30, whose +4 callback
 * is func_80019970 when the config has +0x1C, else func_800180A0), a block of
 * entry records that are initialised and linked into the sub-pool's index
 * array, and finally a free-list of nodes (stride 0x1C) chained through
 * D_80036F54->f2C. All allocations use the config's size/pool argument. */
typedef struct {
    s32 f0;
    void *f4;
    s32 f8;
    s32 fC;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f20;
    s32 f1C;
    s32 f24;
    s32 f28;
    void *f2C;
    void *f30;
    void *f34;
    s32 f38;
    s32 f3C;
    s32 f40;
    s32 f44;
    s32 f48;
    s32 f4C;
} Nw2State17B40;

typedef struct {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    unsigned f10;
    unsigned int f14;
    s32 f18;
    u8 f1C;
} Nw2Cfg17B40;

typedef struct {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    unsigned int f14;
    s32 f18;
    s32 *f1C;
    s32 f20;
} Nw2Sub17B40;

extern Nw2State17B40 *D_80036F54;
extern void func_800180A0(void);
extern void func_80019970(void);
void *func_800202B0(s32, s32, s32, s32, s32);
void func_8002021C(void *, void *);
void func_8001852C(void *, s32, s32);
s32 func_8001A3B0(s32, void *, s32);

void initStatePools17B40(Nw2Cfg17B40 *arg0) {
    void *entryPtr;
    s32 i;
    s32 poolSize;
    s32 tmpF10;
    int tmpF4;
    void *pool;
    void *pool2;
    void *entries;
    void *freeList;
    void *node;
    Nw2Sub17B40 *sub;
    Nw2State17B40 *st;

    poolSize = arg0->f14;
    D_80036F54->f0 = 0;
    tmpF4 = arg0->f4;
    D_80036F54->f1C = 0;
    D_80036F54->f20 = 0;
    D_80036F54->f38 = tmpF4;
    D_80036F54->f40 = arg0->f18;
    D_80036F54->f44 = 0xB8;
    tmpF10 = arg0->f10;
    D_80036F54->f4C = 1;
    D_80036F54->f48 = 0;
    D_80036F54->f24 = tmpF10;
    pool = func_800202B0(0, 0, poolSize, 1, 0x44);
    D_80036F54->f34 = pool;
    ((Nw2Sub17B40 *)pool)->f14 = 0;
    ((Nw2Sub17B40 *)D_80036F54->f34)->f18 = arg0->f4;
    ((Nw2Sub17B40 *)D_80036F54->f34)->f1C = (s32 *)func_800202B0(0, 0, poolSize, arg0->f4, 4);
    pool2 = func_800202B0(0, 0, poolSize, 1, 0x14);
    D_80036F54->f30 = pool2;
    if (arg0->f1C != 0) {
        ((Nw2Sub17B40 *)D_80036F54->f34)->f20 = func_8001A3B0(0, arg0, poolSize);
        ((Nw2Sub17B40 *)D_80036F54->f30)->f4 = (s32)func_80019970;
    } else {
        ((Nw2Sub17B40 *)pool2)->f4 = (s32)func_800180A0;
    }
    D_80036F54->f4 = 0;
    D_80036F54->f8 = 0;
    D_80036F54->f14 = 0;
    D_80036F54->f18 = 0;
    D_80036F54->fC = 0;
    D_80036F54->f10 = 0;
    entries = func_800202B0(0, 0, poolSize, arg0->f4, 0x8C);
    for (i = 0; i < arg0->f4; i++) {
        entryPtr = (void *)((u8 *)entries + i * 0x8C);
        func_8002021C(entryPtr, (u8 *)D_80036F54 + 4);
        ((Nw2Sub17B40 *)entryPtr)->f8 = 0;
        func_8001852C(entryPtr, D_80036F54->f24, poolSize);
        sub = (Nw2Sub17B40 *)D_80036F54->f34;
        {
            s32 idx = sub->f14;
            sub->f14 = idx + 1;
            sub->f1C[idx] = (s32)entryPtr;
        }
    }
    freeList = func_800202B0(0, 0, poolSize, arg0->f8, 0x1C);
    st = D_80036F54;
    st->f2C = NULL;
    for (i = 0; i < arg0->f8; i++) {
        node = (void *)((u8 *)freeList + i * 0x1C);
        *(void **)node = st->f2C;
        st->f2C = node;
    }
    D_80036F54->f28 = poolSize;
}
