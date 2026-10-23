#include "common.h"

/* Identical to func_8002AD04 (matched), with its names changed by decomp.wtf */
typedef struct {
    u8 **items;
    u16 count;
    u16 pad;
} Tbl;

extern Tbl D_8003A4F8[];
extern u8 D_8003A59C[];

extern s32 func_80099734(s32 key);
extern s32 func_800B600C(s32 id, s32 flags);

/* Fetch the resource selected by `key` with `flags`; the returned handle is
 * discarded here (this only triggers the load). */
void func_80099704(s32 key, s32 flags) {
    func_800B600C(func_80099734(key), flags);
}

s32 func_8002AD34(s32 key, s32 flags) {
    return func_800B600C(func_80099734(key), flags) + 0x19;
}
