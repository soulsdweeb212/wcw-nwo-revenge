#include "common.h"

typedef struct Nw2Node {
    struct Nw2Node *next;
} Nw2Node;

/* Unlinks node arg1 from the singly-linked list whose head pointer is *arg0. */
void func_8001CE40(Nw2Node **arg0, Nw2Node *arg1) {
    Nw2Node **pp;
    Nw2Node *v;

    pp = arg0;
    v = *pp;
    if (v != NULL) {
        do {
            if (v == arg1) {
                *pp = v->next;
                return;
            }
            pp = (Nw2Node **)v;
            v = *pp;
        } while (v != NULL);
    }
}

s32 func_80026B50(u32);

extern f64 D_8003B6D0;

typedef struct {
    s32 f0;
    u32 f4;
    s32 f8;
} NwAllocHdr;

void func_8001F070(void *, void *, void *, s32);
void *func_800202B0(void *, void *, NwAllocHdr *, s32, s32);
void func_8001E340(void);
void func_8001E88C(void);
