/* @header
 * func_8009F9A0
 * VRAM 0x8009F9A0 | ROM 0x4C110 | size 0x49C
 * asm: asm/nonmatchings/code_80090000/func_8009F9A0.s
 */
#include "common.h"

typedef struct { u8 pad0[0x24]; f32 z; } Pos;
typedef struct {
    void *parent;
    void *child;
    void *next;
    void *dl;
    void *f10;
    Pos *pos;
    u8 kind;
    u8 pad19[3];
    f32 mtx[4][4];
    u8 pad5C[0xDC - 0x5C];
} Node;

typedef struct {
    s16 x, y;
    u16 f4;
    u8 pad6[4];
    u16 fA;
    u8 padC[2];
    u8 idx;
    u8 fF;
    s16 parent;
    u8 pad12[2];
    u16 flags;
} Def;

typedef struct {
    Def *defs;
    u8 pad4;
    u8 n;
    u8 pad6[2];
    u8 cur;
    u8 pad9[3];
} Items;

typedef struct El {
    f32 x, y;
    s16 f8;
    s16 fA;
    u8 fC, fD, fE, fF;
    s16 f10;
    s16 f12;
    s16 f14;
    u8 f16;
    u8 pad17;
    u8 f18, f19;
    s16 f1A;
    f32 f1C;
    u16 f20;
    s16 f22;
    Def *def;
    u8 pad28[0x68 - 0x28];
    Node node;
    struct El *parent;
} El;

typedef struct {
    Items *items;
    s16 cur;
    u8 pad6[2];
    s16 f8;
    u8 padA[2];
    s16 fC;
    s16 fE;
    s16 f10;
    s16 f12;
    El *el;
    u8 pad18[0x58 - 0x18];
    Node node;
    u8 pad134[4];
} Menu;

typedef struct { void *dl; void *addr; s16 n; u8 padA[4]; s16 fE; } VtxSet;
typedef struct { u16 menu; u16 idx; s16 c; u8 pad6[2]; } Tint;

extern Menu D_800E8230[];
extern Items D_800CC8EC[];
extern El *D_800DC730;
extern s16 D_800DC824;
extern VtxSet D_800CB7B8[];
extern u8 D_800CCB80[];
extern s16 D_800CC8A8[6];
extern Tint D_800CC8E4[];

void initializeTransformNode(void *, u8, f32, f32, f32);
void buildScaledRotationTranslationMatrix(void *, f32, f32, f32, f32, f32, f32, f32);
void func_800015AC(void *, s32);
void func_80001544(void *);

void func_8009F9A0(void) {
    s32 i, j;
    Menu *m;
    Items *it;
    El *el;
    Def *d;
    VtxSet *v;
    Tint *e;

    for (i = 0, it = D_800CC8EC, m = D_800E8230; i < 24; i++, it++, m++) {
        m->items = it;
        m->cur = it->cur;
        m->f8 = 0;
        m->f10 = 0;
        m->fC = 0;
        if (i == 0) {
            m->f12 = 0;
            m->fE = 0;
        } else {
            m->fE = 0x88;
            m->f12 = 0x10;
        }
        el = &D_800DC730[D_800DC824];
        m->el = el;
        d = it->defs;
        initializeTransformNode(&m->node, 3, 0.0f, 0.0f, 0.0f);
        m->node.child = &el->node;
        buildScaledRotationTranslationMatrix(m->node.mtx, D_800CC8A8[3], D_800CC8A8[4], D_800CC8A8[5], 1.0f,
                                             D_800CC8A8[0], D_800CC8A8[1], D_800CC8A8[2]);
        for (j = 0; j < it->n; j++, el++, d++) {
            v = &D_800CB7B8[d->idx];
            el->f8 = 0;
            el->fF = 0;
            el->x = d->x;
            el->y = d->y;
            el->f1C = d->f4 * (1.0 / 1024);
            el->f12 = 0;
            el->f10 = 0;
            el->f18 = 0;
            el->f19 = 0;
            el->f16 = 0;
            el->def = d;
            el->f14 = 0xFF;
            el->f20 = d->fA;
            el->f22 = 0;
            el->fC = el->fD = el->fE = (u8)d->flags >> 4;
            el->f1A = 0;
            el->fA = (u8)d->flags << 8;
            if (d->parent != -1) {
                el->parent = &m->el[d->parent];
            } else {
                el->parent = 0;
            }
            initializeTransformNode(&el->node, 3, 0.0f, 0.0f, 0.0f);
            el->node.dl = v->addr;
            el->node.f10 = D_800CCB80;
            func_800015AC(&el->node, v->n);
            func_80001544(&el->node);
            el->node.kind |= 0x80;
            el->node.pos->z = v->fE << 10;
            if (el->def->flags & 0x400) {
                el->node.pos->z -= 3192.0f;
            }
            el->node.parent = &m->node;
            if (j < it->n - 1) {
                el->node.next = &el[1].node;
            }
            D_800DC824++;
        }
    }
    e = D_800CC8E4;
    for (;;) {
        s8 c;

        if (e->menu == 0x17) {
            break;
        }
        el = &D_800E8230[e->menu].el[e->idx];
        c = e->c;
        el->fC = el->fD = el->fE = c;
        switch (el->def->fF & 0xF) {
        case 6:
            el->f10 = c;
            break;
        case 5:
            el->f10 = c << 7;
            break;
        default:
            el->f10 = c << 6;
            break;
        }
        e++;
    }
}
