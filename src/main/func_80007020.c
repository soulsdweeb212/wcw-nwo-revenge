/* @header
 * func_80007020
 * VRAM 0x80007020 | ROM 0x7C20 | size 0x2C8
 * asm: asm/nonmatchings/main/func_80007020.s
 */
#include "common.h"

#ifdef TARGET_PC
typedef Gfx Gfx7020; /* on PC a command is port.h's 16-byte Gfx, which the port hands to Fast3D as it is */
#else
typedef struct { u32 w0, w1; } Gfx7020;
#endif

typedef struct Nw2ResCacheEntry {
    struct Nw2ResCacheEntry *next;
    void *data;
    u16 key;
    u16 refcount;
} Nw2ResCacheEntry;

#ifdef TARGET_PC
/* PC: an Ent7020 is a display record, whose PC layout is Nw2Descr4BA8 (common.h): from fC on its fields are 8-byte
 * pointers, so this view places them by offsetof and has the record's size, and arg0[i] steps by it. dl and dl2 (f10
 * and f14, the material's and the triangles' display lists) are pointers like vtx. The asserts check the view against
 * Nw2Descr4BA8. */
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
} Ent7020;
_Static_assert(offsetof(Ent7020, n) == offsetof(Nw2Descr4BA8, f2) &&
                   offsetof(Ent7020, v0) == offsetof(Nw2Descr4BA8, f3) &&
                   offsetof(Ent7020, vtx) == offsetof(Nw2Descr4BA8, fC) &&
                   offsetof(Ent7020, dl) == offsetof(Nw2Descr4BA8, f10) &&
                   offsetof(Ent7020, dl2) == offsetof(Nw2Descr4BA8, f14) &&
                   offsetof(Ent7020, tex) == offsetof(Nw2Descr4BA8, f18) && sizeof(Ent7020) == sizeof(Nw2Descr4BA8),
               "Ent7020 must follow Nw2Descr4BA8");
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
} Ent7020;
#endif

extern Nw2ResCacheEntry *nw2ResourceCacheHead;

void *allocateHeap(u32);
void func_8000498C(void *, s16);
#ifndef TARGET_PC /* on PC, port.h declares the loader functions */
void lookupResourceDescriptor(s32 *, u32);
void func_80003684(s32 *, u32, void *);
#endif
void func_80004E08(void *, s32, s16);
void buildCiTextureDisplayList(void *, s32);
u32 osVirtualToPhysical(void *);

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

#ifdef TARGET_PC
    /* PC: the list's 2 * arg3 + 8 commands (the N64's (arg3 << 4) + 0x40 bytes), each sizeof(Gfx7020) bytes. */
    buf = allocateHeap((arg3 * 2 + 8) * sizeof(Gfx7020));
#else
    buf = allocateHeap((arg3 << 4) + 0x40);
#endif
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
#ifdef TARGET_PC
                /* PC: the entry holds two 8-byte pointers, so it is sizeof(Nw2ResCacheEntry) = 0x18 bytes, not 0xC. */
                e = allocateHeap(sizeof(Nw2ResCacheEntry));
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
#ifdef TARGET_PC
            /* PC: a command's address word holds the pointer itself (port.h's DL_ADDR), where the N64 writes the
             * physical address of the vertices and of the two display lists. */
            if (arg0[i].vtx != NULL) {
                GFX_CMD(gfx++, 0x01000000 | ((arg0[i].n & 0xFF) << 12) | (((arg0[i].v0 + arg0[i].n) & 0x7F) << 1),
                        DL_ADDR(arg0[i].vtx));
            }
            if (arg0[i].dl != NULL) {
                GFX_CMD(gfx++, 0xDE000000, DL_ADDR(arg0[i].dl));
            } else if (arg0[i].dl2 != NULL) {
                GFX_CMD(gfx++, 0xDE000000, DL_ADDR(arg0[i].dl2));
            }
#else
            if (arg0[i].vtx != NULL) {
                GFX_CMD(gfx++, 0x01000000 | ((arg0[i].n & 0xFF) << 12) | (((arg0[i].v0 + arg0[i].n) & 0x7F) << 1),
                        osVirtualToPhysical(arg0[i].vtx));
            }
            if (arg0[i].dl != 0) {
                GFX_CMD(gfx++, 0xDE000000, arg0[i].dl - 0x80000000);
            } else if (arg0[i].dl2 != 0) {
                GFX_CMD(gfx++, 0xDE000000, arg0[i].dl2 - 0x80000000);
            }
#endif
        }
    }
    GFX_CMD(gfx++, 0xDF000000, 0);
    return buf;
}
