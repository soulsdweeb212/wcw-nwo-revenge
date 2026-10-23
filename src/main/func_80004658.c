#include "common.h"

/* machine draft (m2c), tried by autopilot */
#ifndef M2C_DEFINES
#define M2C_DEFINES
typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_ERROR(desc) (0)
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)
#endif

M2C_UNK releaseHeapBlock(M2C_UNK *);                   /* extern */
extern M2C_UNK *nw2ResourceCacheHead;

/* Drop one reference to the resource-cache node whose key (node+4) equals
 * `key`. Walk nw2ResourceCacheHead, decrement the node's refcount (node+0xA);
 * when it reaches zero, unlink it from the list and release both its payload
 * (node+4) and the node itself. */
void func_80004658(s32 key) {
    M2C_UNK *entry;
    M2C_UNK *prev;
    u16 refs;

    entry = nw2ResourceCacheHead;
    prev = NULL;
    if (entry != NULL) {
loop_1:
        if (M2C_FIELD(entry, s32 *, 4) != key) {
            prev = entry;
            entry = M2C_FIELD(entry, M2C_UNK **, 0);
            if (entry != NULL) {
                goto loop_1;
            }
        }
        if (entry != NULL) {
            refs = M2C_FIELD(entry, u16 *, 0xA) - 1;
            M2C_FIELD(entry, u16 *, 0xA) = refs;
            if (!(refs & 0xFFFF)) {
                if (prev == NULL) {
                    nw2ResourceCacheHead = M2C_FIELD(entry, M2C_UNK **, 0);
                } else {
                    *prev = M2C_FIELD(entry, M2C_UNK **, 0);
                }
                releaseHeapBlock(M2C_FIELD(entry, M2C_UNK **, 4));
                releaseHeapBlock(entry);
            }
        }
    }
}
