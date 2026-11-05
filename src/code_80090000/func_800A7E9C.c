/* @header
 * func_800A7E9C
 * VRAM 0x800A7E9C | ROM 0x5460C | size 0x2A4
 * asm: asm/nonmatchings/code_80090000/func_800A7E9C.s
 */
#include "common.h"

typedef struct { s16 ob[3]; u16 flag; s16 tc[2]; u8 cn[4]; } V;
typedef struct { u32 w0, w1; } G;
typedef struct { u8 pad[0x20]; u16 id; } E;
extern V *D_800E7CB4;
extern u16 D_800C9254;
u32 osVirtualToPhysical(V *);
void func_800B6FE0(G **, s32);

void func_800A7E9C(G **dl, E *e) {
    G *g = *dl;
    G *p;
    G *q;
    V *v;
    s32 x0, x1, y0, y1;
    s32 k = D_800C9254;
    s32 w = 0x80;
    s32 h = 0x20;

    switch (e->id) {
    case 0x1104:
        q = g++;
        q->w0 = 0xDF000000;
        q->w1 = 0;
        *dl = g;
        return;
    case 0x1106: y0 = -6; y1 = 6; x0 = -0x30; x1 = 0; break;
    case 0x1107: y0 = -6; y1 = 6; x0 = -0x18; x1 = 0x18; break;
    case 0x1101: y0 = -6; y1 = 6; x0 = -0x30; x1 = 0x3D; break;
    case 0x1102: y0 = -6; y1 = 6; x0 = -0x57; x1 = 0x16; break;
    case 0x1103: y0 = -6; y1 = 6; x0 = -0x3B; x1 = 0x3B; break;
    case 0x1108: y0 = -0x12; y1 = 6; x0 = -0x3C; x1 = 0x3C; break;
    case 0x1109: y0 = -6; y1 = 6; x0 = -0x3C; x1 = 0x3C; break;
    case 0x1105: y0 = -0x24; y1 = 0x24; x0 = -0x30; x1 = 0x30; break;
    default: y0 = -0xC; y1 = 0xC; x0 = -0x30; x1 = 0x30; break;
    }
    p = g++;
    p->w0 = 0x01004008;
    p->w1 = osVirtualToPhysical(D_800E7CB4);
    v = D_800E7CB4++;
    v->ob[0] = x0 - 2; v->ob[1] = y0 - 2; v->ob[2] = 0; v->flag = 0;
    v->tc[0] = 0; v->tc[1] = 0;
    v->cn[0] = 0xFF; v->cn[1] = 0xFF; v->cn[2] = 0xFF; v->cn[3] = 0xFF;
    v = D_800E7CB4++;
    v->ob[0] = x1 + 2; v->ob[1] = y0 - 2; v->ob[2] = 0; v->flag = 0;
    v->tc[0] = w << 5; v->tc[1] = 0;
    v->cn[0] = 0xFF; v->cn[1] = 0xFF; v->cn[2] = 0xFF; v->cn[3] = 0xFF;
    v = D_800E7CB4++;
    v->ob[0] = x0 - 2; v->ob[1] = y1 + 2; v->ob[2] = 0; v->flag = 0;
    v->tc[0] = 0; v->tc[1] = h << 5;
    v->cn[0] = 0xFF; v->cn[1] = 0xFF; v->cn[2] = 0xFF; v->cn[3] = 0xFF;
    v = D_800E7CB4++;
    v->ob[0] = x1 + 2; v->ob[1] = y1 + 2; v->ob[2] = 0; v->flag = 0;
    v->tc[0] = w << 5; v->tc[1] = h << 5;
    v->cn[0] = 0xFF; v->cn[1] = 0xFF; v->cn[2] = 0xFF; v->cn[3] = 0xFF;
    func_800B6FE0(&g, k);
    *dl = g;
}
