/* @header
 * initObjectNodeLists  (originally func_80020340)
 * VRAM 0x80020340 | ROM 0x20F40 | size 0x2CC
 * asm: asm/nonmatchings/main/initObjectNodeLists.s
 */
#include "common.h"

/* Allocate and wire up an object's node lists from its config record: the head/tail
 * list nodes, a per-slot record array (each record owns a chained sub-object), and
 * the free-node list. Records are linked into the object, sub-objects chained together,
 * and the pool handle is stored back on the object. */
void *func_800202B0(s32, s32, s32, s32, s32);
void func_8001D6D8(void *);
void func_8001D620(void *, void *, s32);
void func_8001D67C(void *, void *, s32);
void func_800209E0(void *, s32, void *, s32);
void func_8001F1D0(void *, s32, void *);
void func_8002021C(void *, void *);
void func_8001D4E4(void *, s32, s32);
void func_8001DF00(void *, s32, s32);
void func_8001D594(void *, s32);
void func_8001F3EC(void *, s32, void *);
void func_8001D42C(void *, s32);
void func_8001E88C(void *, s32, void *);
void func_8001E30C(void *, s32, void *);
void func_80020190(void *, s32, void *);

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

void initObjectNodeLists(u8 *object, u8 *config) {
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
    node = func_800202B0(0, 0, pool, 1, 28);
    func_8001D6D8(node);
    P(object, 56) = node;
    P(object, 52) = func_800202B0(0, 0, pool, 1, 76);
    W(object, 64) = 1;
    func_8001D620(P(object, 52), func_800202B0(0, 0, pool, W(config, 4), 4), W(config, 4));
    P(object, 48) = func_800202B0(0, 0, pool, 1, 32);
    func_8001D67C(P(object, 48), func_800202B0(0, 0, pool, W(config, 4), 4), W(config, 4));
    if (config[28]) func_800209E0(object, 0, config, pool);
    else func_8001F1D0(P(object, 48), 2, P(object, 52));
    W(object, 4) = 0;
    W(object, 8) = 0;
    W(object, 20) = 0;
    W(object, 24) = 0;
    W(object, 12) = 0;
    W(object, 16) = 0;
    tmp = func_800202B0(0, 0, pool, W(config, 4), 220);
    for (i = 0; i < W(config, 4); i++) {
        p = (Nw2Rec20340 *)tmp + i;
        func_8002021C(p, object + 4);
        p->f8 = 0;
        qA = &p->subA;
        func_8001D4E4(qA, W(object, 36), pool);
        func_8001DF00(qA, 1, 0);
        r = &p->subB;
        func_8001D594(r, pool);
        func_8001F3EC(r, 1, qA);
        qC = &p->subCbuf;
        func_8001D42C(qC, pool);
        func_8001E88C(qC, 1, r);
        func_8001E30C(P(object, 52), 2, qC);
        p->subC = qC;
    }
    func_80020190(node, 1, P(object, 48));
    tmp2 = func_800202B0(0, 0, pool, W(config, 8), 28);
    P(object, 44) = 0;
    for (i = 0; i < W(config, 8); i++) {
        f = (Nw2Free20340 *)tmp2 + i;
        f->next = P(object, 44);
        P(object, 44) = f;
    }
    W(object, 40) = pool;
}
