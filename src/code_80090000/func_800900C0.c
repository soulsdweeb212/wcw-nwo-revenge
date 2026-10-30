/* @header
 * func_800900C0
 * VRAM 0x800900C0 | ROM 0x3C830 | size 0x240
 * asm: asm/nonmatchings/code_80090000/func_800900C0.s
 */
#include "common.h"

extern u8 func_800DB348[];
extern u8 func_800D6658[];
extern u8 sceneNodeCallback5AD0[];
extern u8 sceneNodeCallback5C50[];
extern u8 D_C5B90[];
void initializeTransformNode(void *, s32, f32, f32, f32);
void func_800015AC(void *, s32);
void func_80001544(void *);

typedef struct { u32 w0, w1; } Gx;
#define CMD(p, a, b) { Gx *_g = (Gx *)(p); _g->w0 = (a); _g->w1 = (b); }

void func_800900C0(s32 arg0) {
    u8 *p;
    u8 *q;
    s32 i;
    f32 z;
    s16 m;
    Gx *dl;
    u8 pad[0x3c];

    i = 0;
    p = func_800DB348 + 0x88;
    do {
        if (i < 2) {
            initializeTransformNode(p, 0, 0.0f, 0.0f, 0.0f);
        } else {
            initializeTransformNode(p, 6, 0.0f, 0.0f, 0.0f);
        }
        *(void **)(p + 0xC) = sceneNodeCallback5AD0;
        *(void **)(p + 0x10) = sceneNodeCallback5C50;
        func_800015AC(p, 1);
        func_80001544(p);
        if (i == 1) {
            *(f32 *)(*(u8 **)(p + 0x14) + 0x24) = -8192.0f;
        } else {
            *(f32 *)(*(u8 **)(p + 0x14) + 0x24) = 8192.0f;
        }
        *(s32 *)p = arg0;
        if (i < 2) {
            *(u8 **)(p + 8) = p + 0xDC;
        }
        i++;
        p += 0xDC;
    } while (i < 3);

    i = 0;
    q = func_800D6658 + 0x6F8;
    z = 0.0f;
    do {
        initializeTransformNode(q, 6, z, z, z);
        *(void **)(q + 0xC) = sceneNodeCallback5AD0;
        *(void **)(q + 0x10) = sceneNodeCallback5C50;
        func_800015AC(q, 1);
        func_80001544(q);
        *(u8 *)(q + 0x18) = *(u8 *)(q + 0x18) | 0x80;
        *(s32 *)q = arg0;
        if (i < 0x2F) {
            *(u8 **)(q + 8) = q + 0x178;
        }
        i++;
        dl = (Gx *)(q + 0xe0);
        CMD(dl++, 0xe7000000, 0);
        CMD(dl++, 0xfa000000, 0);
        CMD(dl++, 0xde000000, D_C5B90);
        CMD(dl++, 0xdf000000, 0);
        dl = (Gx *)(q + 0x120);
        CMD(dl++, 0xe7000000, 0);
        CMD(dl++, 0xfa000000, 0);
        CMD(dl++, 0xde000000, D_C5B90);
        CMD(dl++, 0xdf000000, 0);
        m = -1;
        *(s16 *)(q + 0x160) = m;
        m = 0;
        *(s16 *)(q + 0x170) = m;
        *(s16 *)(q + 0x162) = 0;
        *(s16 *)(q + 0x166) = 0;
        q += 0x178;
    } while (i < 0x30);
}
