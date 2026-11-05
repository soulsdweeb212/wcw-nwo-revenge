/* @header
 * alSynNew  (originally func_80020340)
 * VRAM 0x80020340 | ROM 0x20F40 | size 0x2CC
 * asm: asm/nonmatchings/main/alSynNew.s
 */
/* SDK: libultra 2.0I, ultralib src/audio/synthesizer.c (same code as the SDK source). */
#include "common.h"

/* Allocate and wire up an object's node lists from its config record: the head/tail
 * list nodes, a per-slot record array (each record owns a chained sub-object), and
 * the free-node list. Records are linked into the object, sub-objects chained together,
 * and the pool handle is stored back on the object. */
void *alHeapDBAlloc(s32, s32, s32, s32, s32);
void alSaveNew(void *);
void alAuxBusNew(void *, void *, s32);
void alMainBusNew(void *, void *, s32);
void alSynAllocFX(void *, s32, void *, s32);
void alMainBusParam(void *, s32, void *);
void alLink(void *, void *);
void alLoadNew(void *, s32, s32);
void alLoadParam(void *, s32, s32);
void alResampleNew(void *, s32);
void alResampleParam(void *, s32, void *);
void alEnvmixerNew(void *, s32);
void alEnvmixerParam(void *, s32, void *);
void alAuxBusParam(void *, s32, void *);
void alSaveParam(void *, s32, void *);

typedef struct {
    void *next;
    void *prev;
    s32 f8;
    void *subC;
    u8 subA[0x48];
    u8 subB[0x34];
    u8 subCbuf[0x50];
} Nw2Rec20340;
typedef struct {
    void *next;
    u8 pad[0x18];
} Nw2Free20340;

#define W(p, n) (*(s32 *)((p) + (n)))
#define P(p, n) (*(void **)((p) + (n)))

void alSynNew(u8 *object, u8 *config) {
    Nw2Rec20340 *p;
    Nw2Free20340 *f;
    void *qA, *qC, *r, *tmp, *node, *tmp2;
    s32 pool, i, count, value;

    pool = W(config, 20);
    W(object, 0) = 0;
    count = W(config, 4);
    W(object, 32) = 0;
    W(object, 28) = 0;
    W(object, 60) = count;
    value = W(config, 24);
    W(object, 72) = 160;
    W(object, 68) = value;
    W(object, 36) = W(config, 16);
    node = alHeapDBAlloc(0, 0, pool, 1, 28);
    alSaveNew(node);
    P(object, 56) = node;
    P(object, 52) = alHeapDBAlloc(0, 0, pool, 1, 76);
    W(object, 64) = 1;
    alAuxBusNew(P(object, 52), alHeapDBAlloc(0, 0, pool, W(config, 4), 4), W(config, 4));
    P(object, 48) = alHeapDBAlloc(0, 0, pool, 1, 32);
    alMainBusNew(P(object, 48), alHeapDBAlloc(0, 0, pool, W(config, 4), 4), W(config, 4));
    if (config[28]) alSynAllocFX(object, 0, config, pool);
    else alMainBusParam(P(object, 48), 2, P(object, 52));
    W(object, 4) = 0;
    W(object, 8) = 0;
    W(object, 20) = 0;
    W(object, 24) = 0;
    W(object, 12) = 0;
    W(object, 16) = 0;
    tmp = alHeapDBAlloc(0, 0, pool, W(config, 4), 220);
    for (i = 0; i < W(config, 4); i++) {
        p = (Nw2Rec20340 *)tmp + i;
        alLink(p, object + 4);
        p->f8 = 0;
        qA = &p->subA;
        alLoadNew(qA, W(object, 36), pool);
        alLoadParam(qA, 1, 0);
        r = &p->subB;
        alResampleNew(r, pool);
        alResampleParam(r, 1, qA);
        qC = &p->subCbuf;
        alEnvmixerNew(qC, pool);
        alEnvmixerParam(qC, 1, r);
        alAuxBusParam(P(object, 52), 2, qC);
        p->subC = qC;
    }
    alSaveParam(node, 1, P(object, 48));
    tmp2 = alHeapDBAlloc(0, 0, pool, W(config, 8), 28);
    P(object, 44) = 0;
    for (i = 0; i < W(config, 8); i++) {
        f = (Nw2Free20340 *)tmp2 + i;
        f->next = P(object, 44);
        P(object, 44) = f;
    }
    W(object, 40) = pool;
}
