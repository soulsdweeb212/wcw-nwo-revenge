/* @header
 * func_800DB4FC
 * VRAM 0x800DB4FC | ROM 0xCE99C | size 0x230
 * asm: asm/nonmatchings/code_800BBA00/func_800DB4FC.s
 */
#include "common.h"

extern u8 D_800F9D10[];
extern u8 D_800F9D30[];
extern u8 D_800F9D34[];

typedef struct {
    u8 pad0[0x386];
    u16 f386;
} Nw2Ent4FC;

typedef struct {
    u8 pad0[0x20];
    u64 flags;
    u8 pad28[0x353 - 0x28];
    s8 f353;
} Nw2Rec4FC;

s32 func_800C2CDC(Nw2Ent4FC *, s32);
s8 tryBeginEntityGrab(void *, Nw2Ent4FC *);
void handleEntityState38To3F(Nw2Ent4FC *, void *);

/* Picks an action index from the entity animation id (f386-0xDA), then finds a
 * linked entity for it. For action 0xB a "searching" flag (0x400000) is raised
 * on the record and entity around the lookup and cleared afterwards. The
 * candidate found is validated with tryBeginEntityGrab and finally bound to the
 * entity by handleEntityState38To3F. Returns 0 if no valid target was found. */
s32 func_800DB4FC(Nw2Ent4FC *e, Nw2Rec4FC *r) {
    s16 anim;
    s16 act;
    s32 action;
    unsigned off;
    register s8 target;

    anim = e->f386 - 0xDA;
    switch (anim) {
    case 3: act = 5; break;
    case 6: case 7: act = 8; break;
    case 13: act = 9; break;
    case 4: act = 6; break;
    case 5: act = 7; break;
    case 0: case 1: act = 0xC; break;
    case 8: case 10: act = 0xA; break;
    case 9: act = 0xB; break;
    case 16:
        act = 0x10;
        break;
    }
    action = act;
    if (action == 0xB) {
        if (r->flags & 0x600000000000ULL) {
            u64 search = 0x400000ULL;
            register sel = r->f353;
            register off = sel * 0x3B0;
            r->flags |= search;
            *(u64 *)(D_800F9D30 + off) |= search;
            target = func_800C2CDC(e, action);
            search = ~0x400000ULL;
            r->flags &= search;
            off = r->f353 * 0x3B0;
            *(u64 *)(D_800F9D30 + off) &= search;
        } else {
            target = func_800C2CDC(e, action);
        }
    } else {
        target = func_800C2CDC(e, action);
    }
    if (target == -1) {
        return 0;
    }
    off = target * 0x3B0;
    if (tryBeginEntityGrab(D_800F9D10 + off, e) != 0) {
        return 0;
    }
    handleEntityState38To3F(e, D_800F9D10 + off);
    return 1;
}
