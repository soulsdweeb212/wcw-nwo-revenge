#include "common.h"

/* Detach an entity from its model part. When the entity (p) holds flag
 * 0x1000000000000, its 0x3000000000000 bits are cleared, the part slot is found
 * through D_800F99A0[entity id], and that part record (stride 0x30) is reset:
 * D_800F98E2 is marked -1 (unbound), func_80012364 is notified with the part's
 * D_800F98E1/D_800F98E4 fields, and bit 1 (or bits 1|8 when the entity's 0x40
 * flag is set) is ORed into the part's D_800F98E3 state byte. */
s32 func_80012364(s8, s32, s8, void *);
extern s8 D_800F99A0[];
extern u8 D_800F98E1[];
extern s8 D_800F98E2[];
extern u8 D_800F98E3[];
extern u8 D_800F98E4[];

typedef struct {
    s8 id;              /* @0x0 */
    u8 pad1[0x1F];
    u64 flags;          /* @0x20 */
} Nw2PartOwner212C;

#define P ((Nw2PartOwner212C *)p)

void func_800E212C(u8 *p) {
    s8 idx;
    s32 off;
    u8 v;
    s8 id;
    if (P->flags & 0x1000000000000ULL) {
        P->flags &= ~0x3000000000000ULL;
        id = P->id;
        idx = D_800F99A0[id];
        off = idx * 0x30;
        D_800F98E2[off] = -1;
        func_80012364(idx, -1, D_800F98E1[off], &D_800F98E4[off]);
        v = D_800F98E3[off];
        D_800F98E3[off] = v | 1;
        if (P->flags & 0x40)
            D_800F98E3[off] = v | 9;
    }
}
