/* @header
 * func_80004450
 * VRAM 0x80004450 | ROM 0x5050 | size 0x128
 * asm: asm/nonmatchings/main/func_80004450.s
 */
#include "common.h"

s32 osPfsInitPak(void *,void *,s32);
s32 osPfsFileState(void *,s32,void *);
s32 osPfsRepairId(s32);
s32 osPfsInit(s32,s32,s32);
s32 osPfsReFormat(s32,s32,s32);
s32 osPfsChecker(s32);
s32 osPfsAllocateFile(s32,s32,s32,s32,s32,s32,s32);
s32 osPfsFindFile(s32,s32,s32,s32,s32,s32);
s32 osPfsDeleteFile(s32,s32,s32,s32,s32);
s32 osPfsReadWriteFile(s32,s32,s32,s32,s32,s32);
s32 osPfsGetLabel(s32,s32,s32);
s32 osPfsSetLabel(s32,s32);
s32 osPfsIsPlug(s32,s32);
s32 osPfsFreeBlocks(void *,s32 *);
s32 osPfsNumFiles(s32,s32,s32);
/* Initializes a Controller Pak (pfs/queue/state buffers) and then calls every
 * Pak API once with null/zero arguments - a probe/coverage stub. */
void func_80004450(void) {
    u8 pfs[0x68]; u8 queue[0x18]; u8 state[0x20];
    osPfsInitPak(queue,pfs,0);
    osPfsFileState(pfs,0,state);
    osPfsRepairId(0);
    osPfsInit(0,0,0);
    osPfsReFormat(0,0,0);
    osPfsChecker(0);
    osPfsAllocateFile(0,0,0,0,0,0,0);
    osPfsFindFile(0,0,0,0,0,0);
    osPfsDeleteFile(0,0,0,0,0);
    osPfsReadWriteFile(0,0,0,0,0,0);
    osPfsFileState(0,0,0);
    osPfsGetLabel(0,0,0);
    osPfsSetLabel(0,0);
    osPfsIsPlug(0,0);
    osPfsFreeBlocks(0,0);
    osPfsNumFiles(0,0,0);
}
