#include "common.h"

typedef struct { s16 f0; u8 pad[250]; } S85E;

extern S85E D_800706AC[];
extern u8 *D_8007BD38;

/* Return the high nibble of entity arg0's record byte in the table at D_8007BD38. */
u32 func_800085E4(s32 arg0) {
    u32 off = D_800706AC[(s16)arg0].f0 * 0x24 + 0xFFFDFFFC;
    return D_8007BD38[off] >> 4;
}
