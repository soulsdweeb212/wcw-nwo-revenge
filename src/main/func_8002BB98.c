/* @header
 * func_8002BB98
 * VRAM 0x8002BB98 | ROM 0x2C798 | size 0x34
 * asm: asm/nonmatchings/main/func_8002BB98.s
 */
#include "common.h"

extern s32 D_8003A594;

#ifdef TARGET_PC
/* PC: the definition (func_8002B7E0.c) returns the address of the name record, a pointer, which an s32 would cut in
 * half. */
void *func_8002B7E0(s32, u32);
#else
s32 func_8002B7E0(s32, s32);
#endif
void bcopy(void *, void *, s32);
void func_8002BAB8(void);
s32 allocateHeap(s32);

/* Copies the 0x2A-byte name record for group arg0 / variant arg1 into arg2. */
void func_8002BB98(s32 arg0, s32 arg1, void *arg2) {
#ifdef TARGET_PC
    /* PC: the record's address as the pointer the function returns. */
    bcopy(arg2, func_8002B7E0(arg0, arg1), 0x2A);
#else
    bcopy(arg2, (void *)func_8002B7E0(arg0, arg1), 0x2A);
#endif
}
