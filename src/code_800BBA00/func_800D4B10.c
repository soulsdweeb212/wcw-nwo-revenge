/* @header
 * func_800D4B10
 * VRAM 0x800D4B10 | ROM 0xC7FB0 | size 0xEC
 * asm: asm/nonmatchings/code_800BBA00/func_800D4B10.s
 */
#include "common.h"

/* Applies the entity's facing mode byte (+0x36E): mode 1 faces 0x40 with a 90
 * degree pitch, mode 2 faces 0x100 with zero pitch, mode 3 faces 0x80 with a 90
 * degree pitch. The low three facing flag bits are cleared first. */
void func_800D4B10(void *arg0) {
    switch (*(u8 *)((u8 *)arg0 + 0x36E)) {
    case 1:
        *(u64 *)((u8 *)arg0 + 0x20) = (*(u64 *)((u8 *)arg0 + 0x20) & ~0x1C0) | 0x40;
        *(f32 *)((u8 *)arg0 + 0x50) = 90.0f;
        break;
    case 2:
        *(f32 *)((u8 *)arg0 + 0x50) = 0.0f;
        *(u64 *)((u8 *)arg0 + 0x20) = (*(u64 *)((u8 *)arg0 + 0x20) & ~0x1C0) | 0x100;
        break;
    case 3:
        *(u64 *)((u8 *)arg0 + 0x20) = (*(u64 *)((u8 *)arg0 + 0x20) & ~0x1C0) | 0x80;
        *(f32 *)((u8 *)arg0 + 0x50) = 90.0f;
        break;
    }
}
