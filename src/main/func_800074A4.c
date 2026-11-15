/* @header
 * func_800074A4
 * VRAM 0x800074A4 | ROM 0x80A4 | size 0x374
 * asm: asm/nonmatchings/main/func_800074A4.s
 */
#include "common.h"

#ifdef TARGET_PC
typedef Gfx Gfx74A4; /* on PC a command is port.h's 16-byte Gfx, which the port hands to Fast3D as it is */
#else
typedef struct { u32 w0, w1; } Gfx74A4;
#endif

typedef struct Cache74A4 {
    struct Cache74A4 *next;
    void *data;
    u16 key;
    u16 refcount;
} Cache74A4;

#ifdef TARGET_PC
/* PC: an Ent74A4 is a display record, whose PC layout is Nw2Descr4BA8 (common.h): from fC on its fields are 8-byte
 * pointers, so this view places them by offsetof and has the record's size, and arg1[i] steps by it. dl and dl2 (f10
 * and f14, the material's and the triangles' display lists) are pointers like vtx. The asserts check the view against
 * Nw2Descr4BA8, as func_80007020's Ent7020 does. */
typedef struct {
    u8 unk0;
    s8 count;
    s8 n;
    s8 v0;
    u8 pad4[offsetof(Nw2Descr4BA8, fC) - 4];
    void *vtx;
    void *dl;
    void *dl2;
    void *tex;
    u8 pad1C[sizeof(Nw2Descr4BA8) - offsetof(Nw2Descr4BA8, f1C)];
} Ent74A4;
_Static_assert(offsetof(Ent74A4, n) == offsetof(Nw2Descr4BA8, f2) &&
                   offsetof(Ent74A4, v0) == offsetof(Nw2Descr4BA8, f3) &&
                   offsetof(Ent74A4, vtx) == offsetof(Nw2Descr4BA8, fC) &&
                   offsetof(Ent74A4, dl) == offsetof(Nw2Descr4BA8, f10) &&
                   offsetof(Ent74A4, dl2) == offsetof(Nw2Descr4BA8, f14) &&
                   offsetof(Ent74A4, tex) == offsetof(Nw2Descr4BA8, f18) && sizeof(Ent74A4) == sizeof(Nw2Descr4BA8),
               "Ent74A4 must follow Nw2Descr4BA8");
#else
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
#endif

extern Cache74A4 *nw2ResourceCacheHead;

void *allocateHeap(u32);
void releaseHeapBlock(void *);
#ifndef TARGET_PC /* on PC, port.h declares the loader functions */
void lookupResourceDescriptor(s32 *, u32);
void func_80003684(s32 *, u32, void *);
#endif
void func_80004E08(void *, s32, s16);
void buildCiTextureDisplayList(void *, s32);
u32 osVirtualToPhysical(void *);

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
#ifdef TARGET_PC
                /* PC: the entry holds two 8-byte pointers, so it is sizeof(Cache74A4) = 0x18 bytes, not 0xC. */
                e = allocateHeap(sizeof(Cache74A4));
#else
                e = allocateHeap(0xC);
#endif
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
#ifdef TARGET_PC
            /* PC: a command's address word holds the pointer itself (port.h's DL_ADDR), where the N64 writes the
             * physical address of the vertices and of the two display lists. */
            if (arg1[i].vtx != NULL) {
                GFX_CMD(gfx++, 0x01000000 | ((arg1[i].n & 0xFF) << 12) | (((arg1[i].v0 + arg1[i].n) & 0x7F) << 1),
                        DL_ADDR(arg1[i].vtx));
            }
            if (arg1[i].dl != NULL) {
                GFX_CMD(gfx++, 0xDE000000, DL_ADDR(arg1[i].dl));
            } else if (arg1[i].dl2 != NULL) {
                GFX_CMD(gfx++, 0xDE000000, DL_ADDR(arg1[i].dl2));
            }
#else
            if (arg1[i].vtx != NULL) {
                GFX_CMD(gfx++, 0x01000000 | ((arg1[i].n & 0xFF) << 12) | (((arg1[i].v0 + arg1[i].n) & 0x7F) << 1),
                        osVirtualToPhysical(arg1[i].vtx));
            }
            if (arg1[i].dl != 0) {
                GFX_CMD(gfx++, 0xDE000000, arg1[i].dl - 0x80000000);
            } else if (arg1[i].dl2 != 0) {
                GFX_CMD(gfx++, 0xDE000000, arg1[i].dl2 - 0x80000000);
            }
#endif
        }
    }
    GFX_CMD(gfx++, 0xDF000000, 0);
}
