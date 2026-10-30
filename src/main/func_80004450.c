/* @header
 * func_80004450
 * VRAM 0x80004450 | ROM 0x5050 | size 0x128
 * asm: asm/nonmatchings/main/func_80004450.s
 */
#include "common.h"

s32 func_80024850(void *,void *,s32);
s32 osPfsFileState(void *,s32,void *);
s32 func_80025280(s32);
s32 func_800215A0(s32,s32,s32);
s32 osPfsReFormat(s32,s32,s32);
s32 osPfsChecker(s32);
s32 osPfsAllocateFile(s32,s32,s32,s32,s32,s32,s32);
s32 findControllerPakFile(s32,s32,s32,s32,s32,s32);
s32 deleteControllerPakFile(s32,s32,s32,s32,s32);
s32 readWriteControllerPakFile(s32,s32,s32,s32,s32,s32);
s32 func_80021640(s32,s32,s32);
s32 func_800254F0(s32,s32);
s32 resetControllers(s32,s32);
s32 getControllerPakFreeBytes(void *,s32 *);
s32 func_80024A40(s32,s32,s32);
/* Initializes a Controller Pak (pfs/queue/state buffers) and then calls every
 * Pak API once with null/zero arguments - a probe/coverage stub. */
void func_80004450(void) {
 u8 pfs[0x68]; u8 queue[0x18]; u8 state[0x20];
 func_80024850(queue,pfs,0);
 osPfsFileState(pfs,0,state);
 func_80025280(0);
 func_800215A0(0,0,0);
 osPfsReFormat(0,0,0);
 osPfsChecker(0);
 osPfsAllocateFile(0,0,0,0,0,0,0);
 findControllerPakFile(0,0,0,0,0,0);
 deleteControllerPakFile(0,0,0,0,0);
 readWriteControllerPakFile(0,0,0,0,0,0);
 osPfsFileState(0,0,0);
 func_80021640(0,0,0);
 func_800254F0(0,0);
 resetControllers(0,0);
 getControllerPakFreeBytes(0,0);
 func_80024A40(0,0,0);
}
