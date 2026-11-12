/* @header
 * func_800C1138
 * VRAM 0x800C1138 | ROM 0x6D8A8 | size 0x198
 * asm: asm/nonmatchings/code_80090000/func_800C1138.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: D_800E7558 holds four 0xEC-byte records, which func_8009F8BC steps by 0xEC: a 0xDC-byte scene object
 * (Nw2SceneObj in common.h, which keeps its N64 layout on PC, so its address fields hold handles, port.h's
 * PTR_TO_SLOT) followed by the picture's fields. The N64's N names the object's fields by offset: f0 the parent, f8
 * the next sibling, fC the vertices, f10 the display list, f14 the work block (a Nw2SceneWork, whose +0x24 is bias),
 * pad18 + 4 the local matrix. a and b are the addresses of objects (initPairedTransformNodes passes pointers), so they
 * are pointers. The callees are declared with their definitions' types (func_800015AC.c, func_80001544.c, bcopy.c). */
typedef struct {
    Nw2SceneObj obj;
    u8 padDC[8];
    s16 fE4, fE6, fE8, fEA;
} N;
_Static_assert(offsetof(N, fE4) == 0xE4 && sizeof(N) == 0xEC, "a record of D_800E7558 keeps its N64 layout on PC");
extern N D_800E7558[];
extern u8 D_800D5758[], D_800D5768[];
extern u8 *D_800E81F8;
extern s32 D_800E81E4, D_800E79C4;
void guPositionF(void *, f32, f32, f32, f32, f32, f32, f32);
void initializeTransformNode(void *, u8, f32, f32, f32);
void func_800015AC(void *, s8);
void func_80001544(void *);
void *bcopy(const void *, void *, s32);

void func_800C1138(void *a, void *b) {
    u8 m[0x40];
    s32 i;
    N *p;

    guPositionF(m, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
    D_800E81F8 = 0;
    for (i = 0; i < 4; i++) {
        p = &D_800E7558[i];
        D_800E7558[i].fE8 = 0;
        D_800E7558[i].fE6 = 0;
        D_800E7558[i].fEA = 0;
        D_800E7558[i].fE4 = 0x100;
        initializeTransformNode(p, 0, 0.0f, 0.0f, 0.0f);
        p->obj.vtx = PTR_TO_SLOT(D_800D5758);
        p->obj.dl = PTR_TO_SLOT(D_800D5768);
        func_800015AC(p, 1);
        func_80001544(p);
        p->obj.parent = PTR_TO_SLOT(a);
        if (i < 3) {
            p->obj.next = PTR_TO_SLOT(&D_800E7558[i + 1]);
        } else {
            p->obj.next = PTR_TO_SLOT(b);
        }
        bcopy(m, p->obj.local, 0x40);
        ((Nw2SceneWork *)SLOT_TO_PTR(p->obj.work))->bias = 8192.0f;
    }
    D_800E81E4 = 0;
    D_800E79C4 = 0;
}
#else
typedef struct {
    s32 f0;
    u8 pad4[4];
    void *f8;
    void *fC;
    void *f10;
    u8 *f14;
    u8 pad18[0xCC];
    s16 fE4, fE6, fE8, fEA;
} N;
extern N D_800E7558[];
extern u8 D_800D5758[], D_800D5768[];
extern s32 D_800E81F8, D_800E81E4, D_800E79C4;
void guPositionF(void *, f32, f32, f32, f32, f32, f32, f32);
void initializeTransformNode(void *, u8, f32, f32, f32);

void func_800C1138(s32 a, void *b) {
    u8 m[0x40];
    s32 i;
    N *p;

    guPositionF(m, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
    D_800E81F8 = 0;
    for (i = 0; i < 4; i++) {
        p = &D_800E7558[i];
        D_800E7558[i].fE8 = 0;
        D_800E7558[i].fE6 = 0;
        D_800E7558[i].fEA = 0;
        D_800E7558[i].fE4 = 0x100;
        initializeTransformNode(p, 0, 0.0f, 0.0f, 0.0f);
        p->fC = D_800D5758;
        p->f10 = D_800D5768;
        func_800015AC(p, 1);
        func_80001544(p);
        p->f0 = a;
        if (i < 3) {
            p->f8 = &D_800E7558[i + 1];
        } else {
            p->f8 = b;
        }
        bcopy(m, p->pad18 + 4, 0x40);
        *(f32 *)(p->f14 + 0x24) = 8192.0f;
    }
    D_800E81E4 = 0;
    D_800E79C4 = 0;
}
#endif
