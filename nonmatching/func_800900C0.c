#include "common.h"

typedef struct { u32 w0, w1; } Gw900C0;

typedef struct { u8 pad0[0x24]; f32 v; } Aux900C0;

typedef struct LinkA900C0 {
    struct NodeA900C0 *next;
    void *cb1;
    void *cb2;
    Aux900C0 *f14;
} LinkA900C0;

typedef struct NodeA900C0 {
    s32 f0;
    u8 pad4[4];
    LinkA900C0 link;
    u8 pad18[0xDC - 0x18];
} NodeA900C0;

typedef struct NodeB900C0 {
    s32 f0;
    u8 pad4[4];
    struct NodeB900C0 *next;
    void *cb1;
    void *cb2;
    u8 pad14[4];
    u8 f18;
    u8 pad19[0xE0 - 0x19];
    Gw900C0 dl0[4];
    u8 pad100[0x20];
    Gw900C0 dl1[4];
    u8 pad140[0x20];
    s16 f160, f162, f164, f166, f168, f16A, f16C, f16E, f170, f172;
    u8 pad174[4];
} NodeB900C0;

extern NodeA900C0 D_800DB3D0[];
extern NodeB900C0 D_800D6D50[];
extern u8 sceneNodeCallback5AD0[];
extern u8 sceneNodeCallback5C50[];

void initializeTransformNode(void *, u8, f32, f32, f32);
void func_800015AC(void *, s32);
void func_80001544(void *);

/* Initializes the two scene-node pools: 3 chained nodes at D_800DB3D0 (the third
 * of kind 6, with a +/-8192.0f value in the aux record at +0x14) and 48 chained
 * nodes at D_800D6D50 with two display lists each (E7/FA/DE->D_C5B90/DF). */
void func_800900C0(s32 arg0) {
    s32 i;
    NodeA900C0 *a;
    LinkA900C0 *l;
    NodeB900C0 *b;

    a = D_800DB3D0;
    l = &a->link;
    for (i = 0; i < 3; i++, a++, l++) {
        if (i < 2) {
            initializeTransformNode(a, 0, 0.0f, 0.0f, 0.0f);
        } else {
            initializeTransformNode(a, 6, 0.0f, 0.0f, 0.0f);
        }
        l->cb1 = sceneNodeCallback5AD0;
        l->cb2 = sceneNodeCallback5C50;
        func_800015AC(a, 1);
        func_80001544(a);
        if (i == 1) {
            l->f14->v = -8192.0f;
        } else {
            l->f14->v = 8192.0f;
        }
        a->f0 = arg0;
        if (i < 2) {
            l->next = a + 1;
        }
    }
    b = D_800D6D50;
    for (i = 0; i < 0x30; i++, b++) {
        initializeTransformNode(b, 6, 0.0f, 0.0f, 0.0f);
        b->cb1 = sceneNodeCallback5AD0;
        b->cb2 = sceneNodeCallback5C50;
        func_800015AC(b, 1);
        func_80001544(b);
        b->f18 |= 0x80;
        b->f0 = arg0;
        if (i < 0x2F) {
            b->next = b + 1;
        }
        b->dl0[0].w0 = 0xE7000000;
        b->dl0[0].w1 = 0;
        b->dl0[1].w0 = 0xFA000000;
        b->dl0[1].w1 = 0;
        b->dl0[2].w0 = 0xDE000000;
        b->dl0[2].w1 = (u32)D_C5B90;
        b->dl0[3].w0 = 0xDF000000;
        b->dl0[3].w1 = 0;
        b->dl1[0].w0 = 0xE7000000;
        b->dl1[0].w1 = 0;
        b->dl1[1].w0 = 0xFA000000;
        b->dl1[1].w1 = 0;
        b->dl1[2].w0 = 0xDE000000;
        b->dl1[2].w1 = (u32)D_C5B90;
        b->dl1[3].w0 = 0xDF000000;
        b->dl1[3].w1 = 0;
        b->f160 = -1;
        b->f170 = 0;
        b->f162 = 0;
        b->f166 = 0;
    }
}
