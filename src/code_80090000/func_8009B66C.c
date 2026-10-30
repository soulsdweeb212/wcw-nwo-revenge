/* @header
 * func_8009B66C
 * VRAM 0x8009B66C | ROM 0x47DDC | size 0x590
 * asm: asm/nonmatchings/code_80090000/func_8009B66C.s
 */
#include "common.h"

typedef struct {u32 w0,w1;} G9B;
typedef struct {s32 id; s16 value; u8 type,pad;} Item9B;
typedef struct {Item9B *item; s16 tick; u8 pad[6];} Entry9B;
typedef struct {u8 pad[0xEA];u16 tick;} State9B;
typedef struct {s32 f0;void *data;s32 f8;s16 w,h,x;} Image9B;
extern Entry9B D_800E79D8[];
extern s32 D_800C94E8;
void appendPaletteSetupDisplayList(void *);
Image9B *func_800B600C(s32,s32);
void func_80096D8C(void *,void *,s32,s32,s32,s32,s32,s32,s32);
void func_8009A878(void *,void *,s32);

#define NW_SHIFTL(v, s, w) ((unsigned int)(((unsigned int)(v) & ((0x01 << (w)) - 1)) << (s)))
#define nwDma1p(pkt, c, s, l, p) { G9B *_g = (G9B *)(pkt); _g->w0 = (NW_SHIFTL((c), 24, 8) | NW_SHIFTL((p), 16, 8) | NW_SHIFTL((l), 0, 16)); _g->w1 = (unsigned int)(s); }
#define nwSPDisplayList(pkt, dl) nwDma1p(pkt, 0xDE, dl, 0, 0)
#define nwSPSetOtherMode(pkt, cmd, sft, len, data) { G9B *_g = (G9B *)(pkt); _g->w0 = (NW_SHIFTL(cmd, 24, 8) | NW_SHIFTL(32 - (sft) - (len), 8, 8) | NW_SHIFTL((len) - 1, 0, 8)); _g->w1 = (unsigned int)(data); }
#define nwDPSetColor(pkt, c, d) { G9B *_g = (G9B *)(pkt); _g->w0 = NW_SHIFTL(c, 24, 8); _g->w1 = (unsigned int)(d); }
#define nwDPNoParam(pkt, cmd) { G9B *_g = (G9B *)(pkt); _g->w0 = NW_SHIFTL(cmd, 24, 8); _g->w1 = 0; }
#define nwSetImage(pkt, cmd, fmt, siz, width, i) { G9B *_g = (G9B *)(pkt); _g->w0 = NW_SHIFTL(cmd, 24, 8) | NW_SHIFTL(fmt, 21, 3) | NW_SHIFTL(siz, 19, 2) | NW_SHIFTL((width) - 1, 0, 12); _g->w1 = (unsigned int)(i); }
#define nwDPSetTile(pkt, fmt, siz, line, tmem, tile, palette, cmt, maskt, shiftt, cms, masks, shifts) { G9B *_g = (G9B *)(pkt); _g->w0 = NW_SHIFTL(0xF5, 24, 8) | NW_SHIFTL(fmt, 21, 3) | NW_SHIFTL(siz, 19, 2) | NW_SHIFTL(line, 9, 9) | NW_SHIFTL(tmem, 0, 9); _g->w1 = NW_SHIFTL(tile, 24, 3) | NW_SHIFTL(palette, 20, 4) | NW_SHIFTL(cmt, 18, 2) | NW_SHIFTL(maskt, 14, 4) | NW_SHIFTL(shiftt, 10, 4) | NW_SHIFTL(cms, 8, 2) | NW_SHIFTL(masks, 4, 4) | NW_SHIFTL(shifts, 0, 4); }
#define nwDPLoadTLUTCmd(pkt, tile, count) { G9B *_g = (G9B *)pkt; _g->w0 = NW_SHIFTL(0xF0, 24, 8); _g->w1 = NW_SHIFTL((tile), 24, 3) | NW_SHIFTL((count), 14, 10); }
#define nwDPLoadTLUT_pal16(pkt, pal, dram) { \
    nwSetImage(pkt, 0xFD, 0, 2, 1, dram); \
    nwDPNoParam(pkt, 0xE8); \
    nwDPSetTile(pkt, 0, 0, 0, (256 + (((pal) & 0xf) * 16)), 7, 0, 0, 0, 0, 0, 0, 0); \
    nwDPNoParam(pkt, 0xE6); \
    nwDPLoadTLUTCmd(pkt, 7, 15); \
    nwDPNoParam(pkt, 0xE7); }
#define nwDPSetPrimColorZ(pkt, z, a) { G9B *_g = (G9B *)(pkt); _g->w0 = NW_SHIFTL(0xFA, 24, 8); _g->w1 = NW_SHIFTL(a, 0, 8) | (z); }

void func_8009B66C(G9B **arg0, State9B *arg1, s32 arg2) {
    G9B *dl;
    s32 y, shade, selected = -1, i, alpha;
    Entry9B *e;
    s16 *tick;
    Image9B *image;
    u32 rgb = 0;

    dl = *arg0;
    nwSPDisplayList(dl++, D_C9620);
    nwSPSetOtherMode(dl++, 0xE3, 12, 2, 0x2000);
    appendPaletteSetupDisplayList(&dl);
    i = 0;
    nwDPSetColor(dl++, 0xFB, 0);
    e = D_800E79D8;
    tick = &e->tick;
    do {
        alpha = 255;
        if (*tick >= 0) {
            y = 239 - *tick / 2;
            if (arg2) {
                switch (e->item->type) {
                case 0:
                    if (y < 32) {
                        if (y < 16) {
                            alpha = (y + 16) * 8;
                            shade = 7;
                        } else {
                            shade = (31 - y) / 2;
                        }
                        if (y >= 0) {
                            selected = e->item->value;
                        }
                        y = 32;
                    } else {
                        shade = 0;
                    }
                    break;
                case 2:
                    if (y < 52) {
                        alpha = 0;
                    } else {
                        shade = 0;
                    }
                    break;
                case 3:
                    if (y < 100) {
                        alpha = y >= 0 ? 255 : 0;
                        y = 100;
                    }
                    shade = 0;
                    break;
                case 4:
                    if (y < 140) {
                        alpha = y >= 0 ? 255 : 0;
                        y = 140;
                    }
                    shade = 0;
                    break;
                }
            } else {
                shade = 8;
                if ((u32)(e->item->type - 3) < 2) {
                    if (y >= 95) {
                        if (y >= 158) {
                            alpha = 0;
                        } else {
                            alpha = (158 - y) * 4;
                        }
                    }
                    if ((e->item->type == 3) & (y < 100)) {
                        if (y < 32) {
                            *tick = 496;
                        }
                        y = 100;
                    } else if ((e->item->type == 4) & (y < 140)) {
                        if (y < 32) {
                            *tick = 496;
                        }
                        y = 140;
                    }
                } else if ((e->item->type == 2) & (y < 52)) {
                    if (y < 0) {
                        alpha = 0;
                    } else if (y < 32) {
                        alpha = y * 8;
                    }
                    y = 52;
                } else {
                    if ((u32)(y - 32) >= 126) {
                        alpha = 0;
                    } else {
                        alpha = (158 - y) * 2;
                    }
                }
            }
            if (alpha) {
                if ((u32)(e->item->type - 1) < 2) {
                    nwDPLoadTLUT_pal16(dl++, 0, D_C9808);
                    nwDPSetPrimColorZ(dl++, rgb, alpha);
                    image = func_800B600C(e->item->id, 0x108);
                } else {
                    nwDPLoadTLUT_pal16(dl++, 0, D_C9788 + shade * 16);
                    nwDPSetPrimColorZ(dl++, rgb, alpha);
                    image = func_800B600C(e->item->id, 0x8102);
                }
                if (image) {
                    func_80096D8C(&dl, image->data, 0, 240 - image->x / 2, y - image->h / 2, image->w, image->h, image->w, image->h);
                }
            }
            if (!arg2) {
                (*tick)++;
                if (*tick >= 512) {
                    *tick = -1;
                }
            }
        }
        i++;
        tick = (s16 *)((u8 *)tick + 12);
        e++;
    } while (i < 32);
    if (!arg2) {
        *arg0 = dl;
        return;
    }
    if (selected == 2) {
        D_800C94E8 = -1;
        selected = -1;
    } else if (selected >= 34) {
        D_800C94E8 = selected;
        selected = -1;
    }
    func_8009A878(&dl, arg1, selected);
    arg1->tick++;
    *arg0 = dl;
}
