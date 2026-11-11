/* @header
 * func_80005014
 * VRAM 0x80005014 | ROM 0x5C14 | size 0x1F0
 * asm: asm/nonmatchings/main/func_80005014.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: Node5014 is a work block (func_8000160C hands them out), which keeps its N64 layout (Nw2SceneWork in common.h),
 * so its owner, next and data (the vertices) hold 4-byte handles (port.h's PTR_TO_SLOT): the code below stores
 * PTR_TO_SLOT(p) there and reads them back with SLOT_TO_PTR. Desc5014 is the display record, whose PC layout is
 * Nw2Descr4BA8 (common.h): the vertices (base, fC) and the two work blocks (nb, f20; na, f24) are pointers there, and
 * the pads put each field at that struct's offset. The asserts check both views. */
typedef struct Node5014 {
    s32 type;
    u32 owner;
    u32 next;
    u8 pad0C[0x20];
    s16 w;
    s16 h;
    u32 data;
} Node5014;
_Static_assert(offsetof(Node5014, type) == offsetof(Nw2SceneWork, kind) &&
                   offsetof(Node5014, owner) == offsetof(Nw2SceneWork, owner) &&
                   offsetof(Node5014, next) == offsetof(Nw2SceneWork, next) &&
                   offsetof(Node5014, w) == offsetof(Nw2SceneWork, count) &&
                   offsetof(Node5014, h) == offsetof(Nw2SceneWork, start) &&
                   offsetof(Node5014, data) == offsetof(Nw2SceneWork, vtx),
               "Node5014 must follow Nw2SceneWork");

typedef struct {
    u8 pad0[2];
    s8 total;
    u8 pad3;
    s8 b;
    s8 a;
    u8 pad6[offsetof(Nw2Descr4BA8, fC) - 6];
    u8 *base;
    u8 pad10[offsetof(Nw2Descr4BA8, f20) - offsetof(Nw2Descr4BA8, f10)];
    Node5014 *nb;
    Node5014 *na;
    u8 pad28[sizeof(Nw2Descr4BA8) - offsetof(Nw2Descr4BA8, f28)];
} Desc5014;
_Static_assert(offsetof(Desc5014, total) == offsetof(Nw2Descr4BA8, f2) && offsetof(Desc5014, b) == 4 &&
                   offsetof(Desc5014, a) == 5 && offsetof(Desc5014, base) == offsetof(Nw2Descr4BA8, fC) &&
                   offsetof(Desc5014, nb) == offsetof(Nw2Descr4BA8, f20) &&
                   offsetof(Desc5014, na) == offsetof(Nw2Descr4BA8, f24) && sizeof(Desc5014) == sizeof(Nw2Descr4BA8),
               "Desc5014 must follow Nw2Descr4BA8");
#else
typedef struct Node5014 {
    s32 type;
    s32 owner;
    struct Node5014 *next;
    u8 pad0C[0x20];
    s16 w;
    s16 h;
    u8 *data;
} Node5014;

typedef struct {
    u8 pad0[2];
    s8 total;
    u8 pad3;
    s8 b;
    s8 a;
    u8 pad6[6];
    u8 *base;
    u8 pad10[0x10];
    Node5014 *nb;
    Node5014 *na;
} Desc5014;
#endif

#ifdef TARGET_PC
/* PC: the types of func_8000160C's definition: it takes the object whose work-block chain gets the new node. */
void *func_8000160C(void *arg0);
#else
extern Node5014 *func_8000160C();
#endif

#ifdef TARGET_PC
/* PC: as on the N64; the vertices go into the block's data as a handle (see Node5014 above). */
static inline void func_80005014_set(Node5014 *n, s16 w, s16 h, u8 *base)
{
    n->type = 1;
    n->w = w;
    n->h = h;
    if (w != 0) {
        n->data = PTR_TO_SLOT(base + h * 16);
    } else {
        n->data = 0;
    }
}
#else
static inline void func_80005014_set(Node5014 *n, s16 w, s16 h, u8 *base)
{
    n->type = 1;
    n->w = w;
    n->h = h;
    if (w != 0) {
        n->data = base + h * 16;
    } else {
        n->data = 0;
    }
}
#endif

#ifdef TARGET_PC
/* PC: the types of port_decls.h's line, with the two views above. obj is the 0xDC-byte object (Nw2SceneObj), whose
 * first work block at +0x14 is a handle. The record's two work blocks (na, nb) are pointers, as func_8000160C returns
 * them; the links between the blocks (next) and the owners the caller passes (two objects) are stored as handles.
 * func_8000160C reads its argument (the object whose work-block chain gets the new block). The N64's first call passes
 * none, but a0 still holds arg0 there (asm: a0 is first changed by the second call's delay slot, which sets it to arg0
 * again), so func_8000160C gets the object, as in the second call; on PC it is passed explicitly. */
void func_80005014(void *obj, void *rec, void *ownerA, void *ownerB)
{
    Desc5014 *arg1 = rec;
    Node5014 *first = SLOT_TO_PTR(((Nw2SceneObj *)obj)->work);
    Node5014 *cur;

    if (arg1->na == NULL) {
        arg1->na = func_8000160C(obj);
    }
    if (arg1->nb == NULL) {
        arg1->nb = func_8000160C(obj);
    }
    cur = first;
    cur->next = 0;
    func_80005014_set(cur, arg1->total - (arg1->a + arg1->b), arg1->a + arg1->b, arg1->base);
    if (arg1->a > 0) {
        cur->next = PTR_TO_SLOT(arg1->na);
        cur = SLOT_TO_PTR(cur->next);
        arg1->na->owner = PTR_TO_SLOT(ownerA);
        func_80005014_set(arg1->na, arg1->a, arg1->b, arg1->base);
    } else {
        func_80005014_set(arg1->na, 0, 0, arg1->base);
    }
    cur->next = 0;
    if (arg1->b > 0) {
        cur->next = PTR_TO_SLOT(arg1->nb);
        cur = SLOT_TO_PTR(cur->next);
        arg1->nb->owner = PTR_TO_SLOT(ownerB);
        func_80005014_set(arg1->nb, arg1->b, 0, arg1->base);
    } else {
        func_80005014_set(arg1->nb, 0, 0, arg1->base);
    }
    cur->next = 0;
}
#else
void func_80005014(u8 *arg0, Desc5014 *arg1, s32 arg2, s32 arg3)
{
    Node5014 *first = *(Node5014 **)(arg0 + 0x14);
    Node5014 *cur;

    if (arg1->na == NULL) {
        arg1->na = func_8000160C();
    }
    if (arg1->nb == NULL) {
        arg1->nb = func_8000160C(arg0);
    }
    cur = first;
    cur->next = NULL;
    func_80005014_set(cur, arg1->total - (arg1->a + arg1->b), arg1->a + arg1->b, arg1->base);
    if (arg1->a > 0) {
        cur->next = arg1->na;
        cur = cur->next;
        arg1->na->owner = arg2;
        func_80005014_set(arg1->na, arg1->a, arg1->b, arg1->base);
    } else {
        func_80005014_set(arg1->na, 0, 0, arg1->base);
    }
    cur->next = NULL;
    if (arg1->b > 0) {
        cur->next = arg1->nb;
        cur = cur->next;
        arg1->nb->owner = arg3;
        func_80005014_set(arg1->nb, arg1->b, 0, arg1->base);
    } else {
        func_80005014_set(arg1->nb, 0, 0, arg1->base);
    }
    cur->next = NULL;
}
#endif
