#include "common.h"

typedef struct Nw2Node17408 {
    struct Nw2Node17408 *next;
    struct Nw2Node17408 *f4;
    u32 pad8;
    u32 fC;
} Nw2Node17408;

extern u32 D_80036F30;
extern u32 D_80036F38;
extern Nw2Node17408 *D_80062524[2];
extern u8 D_80062540[];
s32 func_8001C990(void *, void *, s32);
void func_8002023C(void *);
void func_8002021C(void *, void *);

void func_80017408(void) {
    u32 i;
    u32 tmp[2];
    Nw2Node17408 *node;
    Nw2Node17408 *next;
    Nw2Node17408 *second;

    for (i = 0; i < D_80036F38; i++) {
        func_8001C990(D_80062540, tmp, 0);
    }
    node = D_80062524[0];
    while (node != NULL) {
        next = node->next;
        if (node->fC + 1 < D_80036F30) {
            if (D_80062524[0] == node) {
                D_80062524[0] = next;
            }
            func_8002023C(node);
            second = D_80062524[1];
            if (second != NULL) {
                func_8002021C(node, second);
            } else {
                D_80062524[1] = node;
                node->next = NULL;
                node->f4 = NULL;
            }
        }
        node = next;
    }
    D_80036F38 = 0;
    D_80036F30++;
}
