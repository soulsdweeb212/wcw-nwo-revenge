/* @header
 * getControllerPakFreeBytes  (originally func_80024530)
 * VRAM 0x80024530 | ROM 0x25130 | size 0x10C
 * asm: asm/nonmatchings/main/func_80024530.s
 */
#include "common.h"

s32 __osCheckId(void *);
s32 readWriteControllerPakInode(void *, u16 *, s32, s32);

/* Sum the free 256-byte pages across all banks of controller pak "pak".
 * Returns 0 and stores the byte count (pages * 256) in *out, or a Controller Pak
 * error code: 5 if the pak is not present, otherwise an __osCheckId or
 * inode-read error. */
s32 getControllerPakFreeBytes(u8 *pak, s32 *out) {
    u16 inodeTable[128];
    s32 status;
    u8 bank;
    s32 i;
    s32 start;
    s32 pageCount = 0;
    if (!(*(u32 *)pak & 1)) return 5;
    status = __osCheckId(pak); if (status) return status;
    for (bank = 0; bank < pak[0x64]; bank++) {
        status = readWriteControllerPakInode(pak, inodeTable, 0, bank); if (status) return status;
        start = bank == 0 ? *(s32 *)(pak + 0x60) : 1;
        for (i = start; i < 128; i++) pageCount += (inodeTable[i] == 3);
    }
    *out = pageCount << 8; return 0;
}
