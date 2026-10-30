/* @header
 * updateEntityModeFlags  (originally func_800D4BFC)
 * VRAM 0x800D4BFC | ROM 0xC809C | size 0xC8
 * asm: asm/nonmatchings/code_800BBA00/updateEntityModeFlags.s
 */
#include "common.h"

/* Set the mode bits (0x1C0) of the entity's +0x20 flag word from its mode byte
 * at +0x36E: 1 -> 0x40, 2 -> 0x100, 3 -> 0x80; other values leave it unchanged. */
void updateEntityModeFlags(void *arg0) {
    switch (*(u8 *)((u8 *)arg0 + 0x36E)) {
    case 1: *(u64 *)((u8 *)arg0 + 0x20) = (*(u64 *)((u8 *)arg0 + 0x20) & ~0x1C0) | 0x40; break;
    case 2: *(u64 *)((u8 *)arg0 + 0x20) = (*(u64 *)((u8 *)arg0 + 0x20) & ~0x1C0) | 0x100; break;
    case 3: *(u64 *)((u8 *)arg0 + 0x20) = (*(u64 *)((u8 *)arg0 + 0x20) & ~0x1C0) | 0x80; break;
    }
}
