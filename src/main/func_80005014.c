/* @header
 * func_80005014
 * VRAM 0x80005014 | ROM 0x5C14 | size 0x1F0
 * asm: asm/nonmatchings/main/func_80005014.s
 */
#include "common.h"

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

extern Node5014 *func_8000160C();

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
