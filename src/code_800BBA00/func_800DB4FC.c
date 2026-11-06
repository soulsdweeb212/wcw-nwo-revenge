/* @header
 * func_800DB4FC
 * VRAM 0x800DB4FC | ROM 0xCE99C | size 0x230
 * asm: asm/nonmatchings/code_800BBA00/func_800DB4FC.s
 */
#include "common.h"

s32 func_800C2CDC(Wrestler *, s32);
s8 tryBeginEntityGrab(void *, Wrestler *);
void handleEntityState38To3F(Wrestler *, void *);

/* Picks an action index from self's move id (moveId-0xDA), then finds a target
 * wrestler for it. For action 0xB a "searching" flag (0x400000) is raised on the
 * opponent and the opponent's opponent around the lookup and cleared afterwards.
 * The candidate found is validated with tryBeginEntityGrab and finally bound to
 * self by handleEntityState38To3F. Returns 0 if no valid target was found. */
s32 func_800DB4FC(Wrestler *self, Wrestler *opponent) {
    s16 anim;
    s16 act;
    s32 action;
    register s8 target;

    anim = (u16)self->moveId - 0xDA;
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
        if (opponent->flags & 0x600000000000ULL) {
            u64 search = 0x400000ULL;
            register sel = opponent->opponentId;
            opponent->flags |= search;
            D_800F9D10[sel].flags |= search;
            target = func_800C2CDC(self, action);
            search = ~0x400000ULL;
            opponent->flags &= search;
            D_800F9D10[opponent->opponentId].flags &= search;
        } else {
            target = func_800C2CDC(self, action);
        }
    } else {
        target = func_800C2CDC(self, action);
    }
    if (target == -1) {
        return 0;
    }
    if (tryBeginEntityGrab(&D_800F9D10[target], self) != 0) {
        return 0;
    }
    handleEntityState38To3F(self, &D_800F9D10[target]);
    return 1;
}
