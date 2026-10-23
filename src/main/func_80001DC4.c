#include "common.h"

void func_80021C40(void *, void *, s32);
void func_80001DC4(void *);

typedef struct {
    s32 parent;   /* @0x0: parent node, or 0 */
    void *child;  /* @0x4 */
    void *next;   /* @0x8 */
    u8 pad[0x10];
    f32 local[4][4];
    f32 world[4][4];
} Nw2Node1DC4;

/* Recursively recompute world matrices for a scene-graph list: with no parent,
 * copy the local matrix verbatim (func_80021C40); with a parent, multiply the
 * local matrix by the parent's matrix at +0x5C. Then recurse into the child and
 * continue along the sibling list. */
void func_80001DC4(void *arg0)
{
    Nw2Node1DC4 *node = arg0;
    f32 (*m)[4];
    f32 *wp;
    f32 *lp;
    f32 *a;
    u32 i;
    u32 j;
    u32 k;
    f32 sum;

    while (node != NULL) {
        if (node->parent == 0) {
            func_80021C40(node->local, node->world, 0x40);
        } else {
            m = (f32 (*)[4])((u8 *)node->parent + 0x5C);
            i = 0;
            wp = node->world[0];
            lp = node->local[0];
            while (i < 4) {
                a = lp;
                for (j = 0; j < 4; j++) {
                    sum = 0.0f;
                    for (k = 0; k < 4; k++)
                        sum += a[k] * m[k][j];
                    wp[j] = sum;
                }
                wp += 4;
                lp += 4;
                i++;
            }
        }
        if (node->child != NULL)
            func_80001DC4(node->child);
        node = node->next;
    }
}
