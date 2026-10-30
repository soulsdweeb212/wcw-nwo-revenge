/* @header
 * func_800209E0
 * VRAM 0x800209E0 | ROM 0x215E0 | size 0x94
 * asm: asm/nonmatchings/main/func_800209E0.s
 */
#include "common.h"

typedef s32 M2C_UNK;
M2C_UNK initAudioStream(s32, M2C_UNK, M2C_UNK);       /* extern */
M2C_UNK func_8001F1D0(s32, M2C_UNK, s32);           /* extern */
M2C_UNK func_8001F860(s32, M2C_UNK, s32);           /* extern */

/* Sets up the audio stream for channel arg1: initializes the 0x4C-byte stream
 * record at arg0->f34 + arg1*0x4C, starts it and routes it through the mixer.
 * Returns the stream record address. */
s32 func_800209E0(void *arg0, s16 arg1, M2C_UNK arg2, M2C_UNK arg3) {
    s32 temp_a2;
    s32 temp_s0;

    temp_s0 = arg1 * 0x4C;
    initAudioStream(*(s32 *)((u8 *)arg0 + 0x34) + temp_s0 + 0x20, arg2, arg3);
    temp_a2 = *(s32 *)((u8 *)arg0 + 0x34) + temp_s0;
    func_8001F860(temp_a2 + 0x20, 1, temp_a2);
    func_8001F1D0(*(s32 *)((u8 *)arg0 + 0x30), 2, *(s32 *)((u8 *)arg0 + 0x34) + temp_s0 + 0x20);
    return *(s32 *)((u8 *)arg0 + 0x34) + temp_s0 + 0x20;
}
