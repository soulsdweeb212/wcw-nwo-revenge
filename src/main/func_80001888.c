#include "common.h"

void calculateObjectVertexCentroid(void *);

/* Walks the node's +0x14 child list and recomputes each child's vertex
 * centroid. */
void func_80001888(void *arg0) {
    void *var_s0;

    var_s0 = *(void **)((u8 *)arg0 + 0x14);
    if (var_s0 != NULL) {
        do {
            calculateObjectVertexCentroid(var_s0);
            var_s0 = *(void **)((u8 *)var_s0 + 8);
        } while (var_s0 != NULL);
    }
}
