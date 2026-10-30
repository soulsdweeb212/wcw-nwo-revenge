/* @header
 * func_80006814
 * VRAM 0x80006814 | ROM 0x7414 | size 0x370
 * asm: asm/nonmatchings/main/func_80006814.s
 */
#include "common.h"

typedef struct { u32 w0, w1; } Gfx6814;
typedef struct { u8 w; u8 h; u8 fmt; } Meta6814;
typedef struct { Meta6814 *meta; u32 addr; } Tex6814;
typedef struct { u8 pad0[0x10]; Gfx6814 *dl; u8 pad14[5]; u8 ready; } Obj6814;

void *allocateHeap(s32);
void func_80001544(void *);
void func_800015AC(void *, s32);
void func_80006178(Gfx6814 **, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32);

#define GFX_CMD(pkt, a, b) { Gfx6814 *_g = (pkt); _g->w0 = (a); _g->w1 = (b); }

void func_80006814(Obj6814 *arg0, Tex6814 *arg1, f32 arg2, f32 arg3)
{
    Gfx6814 *gfx;

    if (arg0->dl == NULL) {
        arg0->dl = allocateHeap(0xA00);
        func_800015AC(arg0, 0);
        func_80001544(arg0);
        arg0->ready = 1;
    }
    gfx = arg0->dl;
    if (arg1 != NULL) {
        GFX_CMD(gfx++, 0xE200001C, 0x0F0A7008);
        GFX_CMD(gfx++, 0xFCFFFFFF, 0xFFFCF279);
        GFX_CMD(gfx++, 0xE3001201, 0);
        GFX_CMD(gfx++, 0xE3000C00, 0);
        if (arg1->meta->fmt != 1) {
            GFX_CMD(gfx++, 0xFD100000, arg1->addr - 0x80000000);
            GFX_CMD(gfx++, 0xE8000000, 0);
            GFX_CMD(gfx++, 0xF5000100, 0x07000000);
            GFX_CMD(gfx++, 0xE6000000, 0);
            GFX_CMD(gfx++, 0xF0000000, 0x0703C000);
            GFX_CMD(gfx++, 0xE7000000, 0);
            func_80006178(&gfx, (u8 *)arg1->meta + 0x80000008, 2, 0,
                          arg1->meta->w + 1, arg1->meta->h + 1, 0x40, 0x20, 0, 0,
                          arg1->meta->w + 1, arg1->meta->h + 1, arg2, arg3);
        } else {
            GFX_CMD(gfx++, 0xFD100000, arg1->addr - 0x80000000);
            GFX_CMD(gfx++, 0xE8000000, 0);
            GFX_CMD(gfx++, 0xF5000100, 0x07000000);
            GFX_CMD(gfx++, 0xE6000000, 0);
            GFX_CMD(gfx++, 0xF0000000, 0x073FC000);
            GFX_CMD(gfx++, 0xE7000000, 0);
            func_80006178(&gfx, (u8 *)arg1->meta + 0x80000008, 2, 1,
                          arg1->meta->w + 1, arg1->meta->h + 1, 0x20, 0x20, 0, 0,
                          arg1->meta->w + 1, arg1->meta->h + 1, arg2, arg3);
        }
        GFX_CMD(gfx++, 0xE7000000, 0);
        GFX_CMD(gfx++, 0xE3000C00, 0x80000);
        GFX_CMD(gfx++, 0xE3001201, 0x2000);
    }
    GFX_CMD(gfx++, 0xDF000000, 0);
}
