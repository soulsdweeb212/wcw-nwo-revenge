/* @header
 * func_80007020
 * VRAM 0x80007020 | ROM 0x7C20 | size 0x2C8
 * asm: asm/nonmatchings/main/func_80007020.s
 */
#include "common.h"

typedef struct { u32 w0, w1; } Gfx7020;

typedef struct Nw2ResCacheEntry {
    struct Nw2ResCacheEntry *next;
    void *data;
    u16 key;
    u16 refcount;
} Nw2ResCacheEntry;

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
} Ent7020;

extern Nw2ResCacheEntry *nw2ResourceCacheHead;

void *allocateHeap(u32);
void func_8000498C(void *, s16);
void lookupResourceDescriptor(s32 *, u32);
void func_80003684(s32 *, u32, void *);
void func_80004E08(void *, s32, s16);
void buildCiTextureDisplayList(void *, s32);
u32 func_8001CE80(void *);

#define GFX_CMD(pkt, a, b) { Gfx7020 *_g = (pkt); _g->w0 = (a); _g->w1 = (b); }

Gfx7020 *func_80007020(Ent7020 *arg0, s16 *arg1, u16 *arg2, s16 arg3)
{
    Gfx7020 *buf;
    Gfx7020 *gfx;
    u32 i;
    u16 key;
    Nw2ResCacheEntry *e;
    Nw2ResCacheEntry *prev;
    s32 desc[4];
    s32 info[4];

    buf = allocateHeap((arg3 << 4) + 0x40);
    for (i = 0; i < arg3; i++) {
        func_8000498C(&arg0[i], arg1[i]);
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
            arg0[i].tex = e->data;
            func_80004E08(&arg0[i], 0, arg2[i]);
            buildCiTextureDisplayList(&arg0[i], 1);
        }
    }
    gfx = buf;
    GFX_CMD(gfx++, 0xE200001C, 0x0F0A7008);
    GFX_CMD(gfx++, 0xFCFFFFFF, 0xFFFCF279);
    for (i = 0; i < arg3; i++) {
        if (arg2[i] != 0 && arg0[i].count > 0) {
            if (arg0[i].vtx != NULL) {
                GFX_CMD(gfx++, 0x01000000 | ((arg0[i].n & 0xFF) << 12) | (((arg0[i].v0 + arg0[i].n) & 0x7F) << 1),
                        func_8001CE80(arg0[i].vtx));
            }
            if (arg0[i].dl != 0) {
                GFX_CMD(gfx++, 0xDE000000, arg0[i].dl - 0x80000000);
            } else if (arg0[i].dl2 != 0) {
                GFX_CMD(gfx++, 0xDE000000, arg0[i].dl2 - 0x80000000);
            }
        }
    }
    GFX_CMD(gfx++, 0xDF000000, 0);
    return buf;
}
