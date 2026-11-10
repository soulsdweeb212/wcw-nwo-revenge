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

extern Obj2454 *D_80047070[][512];
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

    key = D_80047070[bank][first]->key;
    for (i = first; i < (u32)D_80047066; i++) {
        p = D_80047070[bank][i];
        if (p->key != key) {
            break;
        }
        for (; p != NULL; p = p->next) {
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
            if (p->vtx != NULL) {
#ifdef TARGET_PC
                /* PC: the vertices' address as the whole pointer (port.h's DL_ADDR); osVirtualToPhysical returns a u32.
                 * A vertex is 16 bytes on both, so the 0x200 bytes added below are 32 vertices on both. */
                addr = DL_ADDR(p->vtx);
#else
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
        for (p = D_80047070[bank][i]; p != NULL; p = p->next) {
            if (p->dl != 0) {
                Gfx2454 *g = *gfx;
                *gfx = g + 1;
                g->w0 = 0xDE000000;
                g->w1 = p->dl - 0x80000000;
            }
        }
    }
    return i;
}
