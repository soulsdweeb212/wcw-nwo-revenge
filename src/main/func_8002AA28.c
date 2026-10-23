#include "common.h"

extern void *D_80064AD0;
extern void *D_80064AD4;
extern void *D_8007FC34;
extern s32 D_8007FC38;
extern void *D_8007FC3C;

typedef struct {
    void *p0;
    void *p1;
    s32 size;
    s32 len;
} Nw2ResDesc;

typedef struct {
    s32 f0;
    u8 pad[0x14];
} Nw2Rec18;

void lookupResourceDescriptor(void *, s32);
void *allocateHeap(s32);
void *func_80003684(void *, s32, void *);

void func_8002AA28(void)
{
    Nw2ResDesc desc;
    Nw2ResDesc out1;
    Nw2ResDesc out2;
    void *p;
    u8 *base;
    Nw2Rec18 *rp;
    Nw2KeyedBufferEntry *e;
    s32 i;

    lookupResourceDescriptor(&desc, 1);
    p = allocateHeap(desc.size);
    D_80064AD0 = p;
    func_80003684(&out1, 1, p);

    lookupResourceDescriptor(&desc, 2);
    p = allocateHeap(desc.size);
    D_80064AD4 = p;
    func_80003684(&out2, 2, p);

    base = allocateHeap(0xC00);
    D_8007FC34 = base;
    i = 0x7F;
    rp = (Nw2Rec18 *)(base + 0xBE8);
    do {
        rp->f0 = 0;
        i--;
        rp--;
    } while (i >= 0);

    e = allocateHeap(0xB40);
    D_8007FC3C = e;
    i = 0;
    do {
        e[i].key0 = 0;
        e[i].key1 = 0;
        i++;
    } while (i < 0x28);

    D_8007FC38 = 0;
}
