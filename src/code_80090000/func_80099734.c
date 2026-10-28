#include "common.h"

extern u8 updateEntityAttackState[];
extern u8 applyEntityMovementC8D84[];
extern u8 updateEntityReactionState[];
s32 func_80099734(s32);
s32 func_800B75D4(s32 *, s32, s32);
u8 *func_80028D18(s32);
u8 *func_80029A24(u8 *, s32, s32);

s32 func_80099734(s32 arg0) {
    return *(s32 *)(applyEntityMovementC8D84 + 0x1DC + (arg0 << 2));
}
