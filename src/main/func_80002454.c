/* @header
 * func_80002454
 * VRAM 0x80002454 | ROM 0x3054 | size 0x210
 * asm: asm/nonmatchings/main/func_80002454.s
 */
#include "common.h"

#ifdef TARGET_PC
typedef Gfx Gfx2454; /* on PC a command is port.h's 16-byte Gfx */
#else
typedef struct { u32 w0, w1; } Gfx2454;
#endif

#ifdef TARGET_PC
/* PC: Obj2454 is a work block, which keeps its N64 layout (Nw2SceneWork in common.h), so its owner (model), next,
 * vertices and display list hold 4-byte handles (port.h's PTR_TO_SLOT), and the code below turns them back with
 * SLOT_TO_PTR. The asserts check the view against Nw2SceneWork. */
typedef struct Obj2454 {
    s32 key;
    u32 model;
    u32 next;
    u8 pad0C[0x20];
    s16 count;
    s16 start;
    u32 vtx;
    u32 dl;
    f32 mtx[4][4][4];
} Obj2454;
_Static_assert(offsetof(Obj2454, model) == offsetof(Nw2SceneWork, owner) &&
                   offsetof(Obj2454, next) == offsetof(Nw2SceneWork, next) &&
                   offsetof(Obj2454, count) == offsetof(Nw2SceneWork, count) &&
                   offsetof(Obj2454, start) == offsetof(Nw2SceneWork, start) &&
                   offsetof(Obj2454, vtx) == offsetof(Nw2SceneWork, vtx) &&
                   offsetof(Obj2454, dl) == offsetof(Nw2SceneWork, dl) &&
                   offsetof(Obj2454, mtx) == offsetof(Nw2SceneWork, mtx),
               "Obj2454 must follow Nw2SceneWork");
#else
typedef struct Obj2454 {
    s32 key;
    void *model;
    struct Obj2454 *next;
    u8 pad0C[0x20];
    s16 count;
    s16 start;
    void *vtx;
    u32 dl;
    f32 mtx[4][4][4];
} Obj2454;
#endif

#ifndef TARGET_PC /* on PC, port_decls.h declares D_80047070 */
extern Obj2454 *D_80047070[][512];
#endif
extern s16 D_80047066;
u32 osVirtualToPhysical(void *);

s16 func_80002454(Gfx2454 **gfx, s16 bank, s16 first)
{
    u32 i;
    s32 key;
    Obj2454 *p;
#ifdef TARGET_PC
    /* PC: addr holds the address of vertices for a command, which a u32 would cut in half. */
    uptr addr;
#else
    u32 addr;
#endif
    u32 n;
    u32 start;

#ifdef TARGET_PC
    /* PC: port_decls.h declares the draw lists as plain pointers (void *); each holds a work block's address. */
    key = ((Obj2454 *)D_80047070[bank][first])->key;
#else
    key = D_80047070[bank][first]->key;
#endif
    for (i = first; i < (u32)D_80047066; i++) {
        p = D_80047070[bank][i];
        if (p->key != key) {
            break;
        }
#ifdef TARGET_PC
        /* PC: the next block is a handle (see Obj2454 above). */
        for (; p != NULL; p = SLOT_TO_PTR(p->next)) {
#else
        for (; p != NULL; p = p->next) {
#endif
            {
                Gfx2454 *g = *gfx;
                *gfx = g + 1;
                g->w0 = 0xDC38000E;
#ifdef TARGET_PC
                /* PC: the matrix's address goes into the command as the whole pointer (port.h's DL_ADDR). */
                g->w1 = DL_ADDR(p->mtx[bank]);
#else
                g->w1 = (u32)p->mtx[bank] - 0x80000000;
#endif
            }
            {
                Gfx2454 *g = *gfx;
                *gfx = g + 1;
                g->w0 = 0xDB0C0000;
                g->w1 = 0x10000;
            }
#ifdef TARGET_PC
            /* PC: the vertices are a handle (see Obj2454 above), 0 for none. Their address goes into the commands as
             * the whole pointer (port.h's DL_ADDR); osVirtualToPhysical returns a u32. A vertex is 16 bytes on both, so
             * the 0x200 bytes added below are 32 vertices on both. */
            if (p->vtx != 0) {
                addr = DL_ADDR(SLOT_TO_PTR(p->vtx));
#else
            if (p->vtx != NULL) {
                addr = osVirtualToPhysical(p->vtx);
#endif
                n = p->count;
                start = p->start;
                while (n > 32) {
                    Gfx2454 *g = *gfx;
                    *gfx = g + 1;
                    g->w0 = 0x01020000 | (((start + 32) & 0x7F) << 1);
                    g->w1 = addr;
                    start += 32;
                    n -= 32;
                    addr += 0x200;
                }
                {
                    Gfx2454 *g = *gfx;
                    *gfx = g + 1;
                    g->w0 = 0x01000000 | ((n & 0xFF) << 12) | (((start + n) & 0x7F) << 1);
                    g->w1 = addr;
                }
            }
        }
#ifdef TARGET_PC
        /* PC: as above, the next block is a handle. */
        for (p = D_80047070[bank][i]; p != NULL; p = SLOT_TO_PTR(p->next)) {
#else
        for (p = D_80047070[bank][i]; p != NULL; p = p->next) {
#endif
            if (p->dl != 0) {
                Gfx2454 *g = *gfx;
                *gfx = g + 1;
                g->w0 = 0xDE000000;
#ifdef TARGET_PC
                /* PC: the display list is a handle; the branch takes its whole address (port.h's DL_ADDR), where the
                 * N64 code writes the physical address. */
                g->w1 = DL_ADDR(SLOT_TO_PTR(p->dl));
#else
                g->w1 = p->dl - 0x80000000;
#endif
            }
        }
    }
    return i;
}
