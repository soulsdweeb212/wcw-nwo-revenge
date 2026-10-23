#include "common.h"

extern u8 updateEntityAttackState[];
extern u8 applyEntityMovementC8D84[];
extern u8 updateEntityReactionState[];
s32 func_80099734(s32);
s32 func_800B75D4(s32 *, s32, s32);
u8 *func_80028D18(s32);
u8 *func_80029A24(u8 *, s32, s32);

u8 func_800996A0(s32 arg0) {
    return updateEntityAttackState[0x49C + arg0];
}

s32 func_80099734(s32 arg0) {
    return *(s32 *)(applyEntityMovementC8D84 + 0x1DC + (arg0 << 2));
}

void func_800996B0(s32 *arg0, s32 arg1, s32 arg2) {
    s32 sp10;

    sp10 = *arg0;
    func_800B75D4(&sp10, func_80099734(arg1), arg2);
    *arg0 = sp10;
}

u8 *func_800995EC(u32 arg0) {
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 *var_v1;

    temp_v0 = func_80028D18(4);
    if (temp_v0 == NULL) {
        return updateEntityReactionState + 0x200;
    }
    if (*temp_v0 == 0) {
        var_v1 = func_80029A24(temp_v0, arg0 & 0x3F, 0);
        if ((arg0 >> 0xA) & 0x1F) {
            *var_v1 = 0x28;
            temp_v0_2 = func_80029A24(var_v1 + 1, (arg0 >> 0xC) & 0x3F, 0);
            *temp_v0_2 = 0x29;
            var_v1 = temp_v0_2 + 1;
        }
        *var_v1 = 0;
    }
    return temp_v0;
}
