/* @header
 * n_alSynNew  (originally func_80017B40)
 * VRAM 0x80017B40 | ROM 0x18740 | size 0x270
 * asm: asm/nonmatchings/main/n_alSynNew.s
 */
/* SDK: n_audio, libnaudio/src/n_synthesizer.c (same code as the SDK source). */
#include "common.h"

/* Initialises the global n_syn state from a config record:
 * copies the config fields into the state header, allocates the shared
 * sub-pool (n_syn->f34), a small helper pool (->f30, whose +4 callback
 * is n_alFxPull when the config has +0x1C, else n_alAuxBusPull), a block of
 * entry records that are initialised and linked into the sub-pool's index
 * array, and finally a free-list of nodes (stride 0x1C) chained through
 * n_syn->f2C. All allocations use the config's size/pool argument. */
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

extern Nw2State17B40 *n_syn;
extern void n_alAuxBusPull(void);
extern void n_alFxPull(void);
void *alHeapDBAlloc(s32, s32, s32, s32, s32);
void alLink(void *, void *);
void alN_PVoiceNew(void *, s32, s32);
s32 n_alSynAllocFX(s32, void *, s32);

void n_alSynNew(Nw2Cfg17B40 *arg0) {
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
    n_syn->f0 = 0;
    tmpF4 = arg0->f4;
    n_syn->f1C = 0;
    n_syn->f20 = 0;
    n_syn->f38 = tmpF4;
    n_syn->f40 = arg0->f18;
    n_syn->f44 = 0xB8;
    tmpF10 = arg0->f10;
    n_syn->f4C = 1;
    n_syn->f48 = 0;
    n_syn->f24 = tmpF10;
    pool = alHeapDBAlloc(0, 0, poolSize, 1, 0x44);
    n_syn->f34 = pool;
    ((Nw2Sub17B40 *)pool)->f14 = 0;
    ((Nw2Sub17B40 *)n_syn->f34)->f18 = arg0->f4;
    ((Nw2Sub17B40 *)n_syn->f34)->f1C = (s32 *)alHeapDBAlloc(0, 0, poolSize, arg0->f4, 4);
    pool2 = alHeapDBAlloc(0, 0, poolSize, 1, 0x14);
    n_syn->f30 = pool2;
    if (arg0->f1C != 0) {
        ((Nw2Sub17B40 *)n_syn->f34)->f20 = n_alSynAllocFX(0, arg0, poolSize);
        ((Nw2Sub17B40 *)n_syn->f30)->f4 = (s32)n_alFxPull;
    } else {
        ((Nw2Sub17B40 *)pool2)->f4 = (s32)n_alAuxBusPull;
    }
    n_syn->f4 = 0;
    n_syn->f8 = 0;
    n_syn->f14 = 0;
    n_syn->f18 = 0;
    n_syn->fC = 0;
    n_syn->f10 = 0;
    entries = alHeapDBAlloc(0, 0, poolSize, arg0->f4, 0x8C);
    for (i = 0; i < arg0->f4; i++) {
        entryPtr = (void *)((u8 *)entries + i * 0x8C);
        alLink(entryPtr, (u8 *)n_syn + 4);
        ((Nw2Sub17B40 *)entryPtr)->f8 = 0;
        alN_PVoiceNew(entryPtr, n_syn->f24, poolSize);
        sub = (Nw2Sub17B40 *)n_syn->f34;
        {
            s32 idx = sub->f14;
            sub->f14 = idx + 1;
            sub->f1C[idx] = (s32)entryPtr;
        }
    }
    freeList = alHeapDBAlloc(0, 0, poolSize, arg0->f8, 0x1C);
    st = n_syn;
    st->f2C = NULL;
    for (i = 0; i < arg0->f8; i++) {
        node = (void *)((u8 *)freeList + i * 0x1C);
        *(void **)node = st->f2C;
        st->f2C = node;
    }
    n_syn->f28 = poolSize;
}
