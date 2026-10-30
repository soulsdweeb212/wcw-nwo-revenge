#include "common.h"

extern u8 func_800DB348[];
extern u8 func_800D6658[];
extern u8 sceneNodeCallback5AD0[];
extern u8 sceneNodeCallback5C50[];
extern u8 D_C5B90[];
void initializeTransformNode(void *, s32, f32, f32, f32);
void func_800015AC(void *, s32);
void func_80001544(void *);

void func_800900C0(s32 arg0) {
    u8 *p;
    u8 *q;
    s32 i;
    s32 c1, c2, c3, c4, c5;
    f32 z;
    s16 m;
    void *cb;
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
    c1 = 0xE7000000;
    c2 = 0xFA000000;
    c3 = 0xDE000000;
    c4 = (s32)D_C5B90;
    c5 = 0xDF000000;
    do {
        initializeTransformNode(q, 6, z, z, z);
        cb = sceneNodeCallback5AD0;
        *(void **)(q + 0xC) = cb;
        cb = sceneNodeCallback5C50;
        *(void **)(q + 0x10) = cb;
        func_800015AC(q, 1);
        func_80001544(q);
        *(u8 *)(q + 0x18) = *(u8 *)(q + 0x18) | 0x80;
        *(s32 *)q = arg0;
        if (i < 0x2F) {
            *(u8 **)(q + 8) = q + 0x178;
        }
        i++;
        *(s32 *)(q + 0xE0) = c1;
        *(s32 *)(q + 0xE4) = 0;
        *(s32 *)(q + 0xE8) = c2;
        *(s32 *)(q + 0xEC) = 0;
        *(s32 *)(q + 0xF0) = c3;
        *(s32 *)(q + 0xF4) = c4;
        *(s32 *)(q + 0xF8) = c5;
        *(s32 *)(q + 0xFC) = 0;
        *(s32 *)(q + 0x120) = c1;
        *(s32 *)(q + 0x124) = 0;
        *(s32 *)(q + 0x128) = c2;
        *(s32 *)(q + 0x12C) = 0;
        *(s32 *)(q + 0x130) = c3;
        *(s32 *)(q + 0x134) = c4;
        *(s32 *)(q + 0x138) = c5;
        *(s32 *)(q + 0x13C) = 0;
        m = -1;
        *(s16 *)(q + 0x160) = m;
        m = 0;
        *(s16 *)(q + 0x170) = m;
        *(s16 *)(q + 0x162) = 0;
        *(s16 *)(q + 0x166) = 0;
        q += 0x178;
    } while (i < 0x30);
}
