#include "common.h"

typedef struct { u32 w0, w1; } Gfx74A4;

typedef struct Cache74A4 {
    struct Cache74A4 *next;
    void *data;
    u16 key;
    u16 refcount;
} Cache74A4;

typedef struct {
    u8 unk0;
    s8 count;
    s8 n;
    s8 v0;
    u8 pad4[8];
    void *vtx;
    u32 dl;
    u32 dl2;
    void *tex;
    u8 pad1C[0x10];
} Ent74A4;

extern Cache74A4 *nw2ResourceCacheHead;

void *allocateHeap(u32);
void releaseHeapBlock(void *);
void lookupResourceDescriptor(s32 *, u32);
void func_80003684(s32 *, u32, void *);
void func_80004E08(void *, s32, s16);
void buildCiTextureDisplayList(void *, s32);
u32 func_8001CE80(void *);

#define GFX_CMD(pkt, a, b) { Gfx74A4 *_g = (pkt); _g->w0 = (a); _g->w1 = (b); }

void func_800074A4(Gfx74A4 *buf, Ent74A4 *arg1, u16 *arg2, s16 arg3)
{
    Gfx74A4 *gfx;
    u32 i;
    u16 key;
    Cache74A4 *e;
    Cache74A4 *prev;
    s32 desc[4];
    s32 info[4];

    for (i = 0; i < arg3; i++) {
        void *data = arg1[i].tex;
        if (data != NULL) {
            Cache74A4 *p = NULL;
            Cache74A4 *c = nw2ResourceCacheHead;
            void *d = data;
            for (; c != NULL; c = c->next) {
                if (c->data == d) {
                    break;
                }
                p = c;
            }
            if (c != NULL && --c->refcount == 0) {
                if (p == NULL) {
                    nw2ResourceCacheHead = c->next;
                } else {
                    p->next = c->next;
                }
                releaseHeapBlock(c->data);
                releaseHeapBlock(c);
            }
            arg1[i].tex = NULL;
        }
    }
    for (i = 0; i < arg3; i++) {
        if (arg2[i] != 0) {
            key = arg2[i] + 1;
            prev = NULL;
            for (e = nw2ResourceCacheHead; e != NULL; e = e->next) {
                if (e->key == key) {
                    break;
                }
                prev = e;
            }
            if (e == NULL) {
                e = allocateHeap(0xC);
                if (prev == NULL) {
                    nw2ResourceCacheHead = e;
                } else {
                    prev->next = e;
                }
                e->next = NULL;
                lookupResourceDescriptor(desc, key);
                e->data = allocateHeap(desc[2]);
                func_80003684(info, key, e->data);
                e->key = key;
                e->refcount = 0;
            }
            e->refcount++;
            arg1[i].tex = e->data;
            func_80004E08(&arg1[i], 0, arg2[i]);
            buildCiTextureDisplayList(&arg1[i], 1);
        }
    }
    gfx = buf;
    GFX_CMD(gfx++, 0xE200001C, 0x0F0A7008);
    GFX_CMD(gfx++, 0xFCFFFFFF, 0xFFFCF279);
    for (i = 0; i < arg3; i++) {
        if (arg2[i] != 0 && arg1[i].count > 0) {
            if (arg1[i].vtx != NULL) {
                GFX_CMD(gfx++, 0x01000000 | ((arg1[i].n & 0xFF) << 12) | (((arg1[i].v0 + arg1[i].n) & 0x7F) << 1),
                        func_8001CE80(arg1[i].vtx));
            }
            if (arg1[i].dl != 0) {
                GFX_CMD(gfx++, 0xDE000000, arg1[i].dl - 0x80000000);
            } else if (arg1[i].dl2 != 0) {
                GFX_CMD(gfx++, 0xDE000000, arg1[i].dl2 - 0x80000000);
            }
        }
    }
    GFX_CMD(gfx++, 0xDF000000, 0);
}
