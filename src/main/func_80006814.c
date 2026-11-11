/* @header
 * func_80006814
 * VRAM 0x80006814 | ROM 0x7414 | size 0x370
 * asm: asm/nonmatchings/main/func_80006814.s
 */
#include "common.h"

#ifdef TARGET_PC
typedef Gfx Gfx6814; /* on PC a command is port.h's 16-byte Gfx, which func_80006178 also writes */
#else
typedef struct { u32 w0, w1; } Gfx6814;
#endif
typedef struct { u8 w; u8 h; u8 fmt; } Meta6814;
#ifdef TARGET_PC
/* PC: arg1 is a picture pair (common.h's Nw2TexPair): the texture (meta: its 8-byte header, then the texels) and the
 * palette, two 8-byte pointers there, so addr is a pointer at +8. arg0 is a scene object (Nw2SceneObj), which keeps
 * its N64 layout on PC: its display list at +0x10 is a 4-byte handle (port.h's PTR_TO_SLOT), and ready is its flat
 * byte at +0x19. The asserts check that both views follow those records. */
typedef struct { Meta6814 *meta; void *addr; } Tex6814;
typedef struct { u8 pad0[0x10]; u32 dl; u8 pad14[5]; u8 ready; } Obj6814;
_Static_assert(sizeof(Tex6814) == sizeof(Nw2TexPair) && offsetof(Tex6814, meta) == offsetof(Nw2TexPair, img) &&
                   offsetof(Tex6814, addr) == offsetof(Nw2TexPair, pal),
               "Tex6814 must follow Nw2TexPair");
_Static_assert(offsetof(Obj6814, dl) == offsetof(Nw2SceneObj, dl) &&
                   offsetof(Obj6814, ready) == offsetof(Nw2SceneObj, flat),
               "Obj6814 must follow Nw2SceneObj");
#else
typedef struct { Meta6814 *meta; u32 addr; } Tex6814;
typedef struct { u8 pad0[0x10]; Gfx6814 *dl; u8 pad14[5]; u8 ready; } Obj6814;
#endif

void *allocateHeap(s32);
void func_80001544(void *);
void func_800015AC(void *, s32);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_80006178 */
void func_80006178(Gfx6814 **, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32);
#endif

#define GFX_CMD(pkt, a, b) { Gfx6814 *_g = (pkt); _g->w0 = (a); _g->w1 = (b); }

void func_80006814(Obj6814 *arg0, Tex6814 *arg1, f32 arg2, f32 arg3)
{
    Gfx6814 *gfx;

#ifdef TARGET_PC
    /* PC: the object's dl is a handle, 0 for none. The list holds the same 320 commands as on the N64, at
     * sizeof(Gfx) = 16 bytes each; the object keeps the list's handle, and the commands go through the pointer. */
    if (arg0->dl == 0) {
        arg0->dl = PTR_TO_SLOT(allocateHeap(0xA00 / 8 * sizeof(Gfx)));
        func_800015AC(arg0, 0);
        func_80001544(arg0);
        arg0->ready = 1;
    }
    gfx = SLOT_TO_PTR(arg0->dl);
#else
    if (arg0->dl == NULL) {
        arg0->dl = allocateHeap(0xA00);
        func_800015AC(arg0, 0);
        func_80001544(arg0);
        arg0->ready = 1;
    }
    gfx = arg0->dl;
#endif
    if (arg1 != NULL) {
        GFX_CMD(gfx++, 0xE200001C, 0x0F0A7008);
        GFX_CMD(gfx++, 0xFCFFFFFF, 0xFFFCF279);
        GFX_CMD(gfx++, 0xE3001201, 0);
        GFX_CMD(gfx++, 0xE3000C00, 0);
        if (arg1->meta->fmt != 1) {
#ifdef TARGET_PC
            /* PC: the palette's own address, written with DL_ADDR (the N64 writes its physical address). */
            GFX_CMD(gfx++, 0xFD100000, DL_ADDR(arg1->addr));
#else
            GFX_CMD(gfx++, 0xFD100000, arg1->addr - 0x80000000);
#endif
            GFX_CMD(gfx++, 0xE8000000, 0);
            GFX_CMD(gfx++, 0xF5000100, 0x07000000);
            GFX_CMD(gfx++, 0xE6000000, 0);
            GFX_CMD(gfx++, 0xF0000000, 0x0703C000);
            GFX_CMD(gfx++, 0xE7000000, 0);
#ifdef TARGET_PC
            /* PC: func_80006178 writes the texture's address into its commands with DL_ADDR, so it takes the
             * texture's own address: the texels 8 bytes after the header. The N64 code passes that address minus
             * 0x80000000 (the physical address), computed by adding 0x80000008 in 32 bits. */
            func_80006178(&gfx, (u8 *)arg1->meta + 8, 2, 0,
                          arg1->meta->w + 1, arg1->meta->h + 1, 0x40, 0x20, 0, 0,
                          arg1->meta->w + 1, arg1->meta->h + 1, arg2, arg3);
#else
            func_80006178(&gfx, (u8 *)arg1->meta + 0x80000008, 2, 0,
                          arg1->meta->w + 1, arg1->meta->h + 1, 0x40, 0x20, 0, 0,
                          arg1->meta->w + 1, arg1->meta->h + 1, arg2, arg3);
#endif
        } else {
#ifdef TARGET_PC
            /* PC: the palette's own address, as above. */
            GFX_CMD(gfx++, 0xFD100000, DL_ADDR(arg1->addr));
#else
            GFX_CMD(gfx++, 0xFD100000, arg1->addr - 0x80000000);
#endif
            GFX_CMD(gfx++, 0xE8000000, 0);
            GFX_CMD(gfx++, 0xF5000100, 0x07000000);
            GFX_CMD(gfx++, 0xE6000000, 0);
            GFX_CMD(gfx++, 0xF0000000, 0x073FC000);
            GFX_CMD(gfx++, 0xE7000000, 0);
#ifdef TARGET_PC
            /* PC: the texture's own address, as above. */
            func_80006178(&gfx, (u8 *)arg1->meta + 8, 2, 1,
                          arg1->meta->w + 1, arg1->meta->h + 1, 0x20, 0x20, 0, 0,
                          arg1->meta->w + 1, arg1->meta->h + 1, arg2, arg3);
#else
            func_80006178(&gfx, (u8 *)arg1->meta + 0x80000008, 2, 1,
                          arg1->meta->w + 1, arg1->meta->h + 1, 0x20, 0x20, 0, 0,
                          arg1->meta->w + 1, arg1->meta->h + 1, arg2, arg3);
#endif
        }
        GFX_CMD(gfx++, 0xE7000000, 0);
        GFX_CMD(gfx++, 0xE3000C00, 0x80000);
        GFX_CMD(gfx++, 0xE3001201, 0x2000);
    }
    GFX_CMD(gfx++, 0xDF000000, 0);
}
