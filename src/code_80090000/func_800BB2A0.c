/* @header
 * func_800BB2A0
 * VRAM 0x800BB2A0 | ROM 0x67A10 | size 0xB8
 * asm: asm/nonmatchings/code_80090000/func_800BB2A0.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: allocateHeap returns the address of a heap block and func_80000A40 the address of the save's PI handle (their
 * definitions return void *), which an s32 would cut in half. */
void *allocateHeap(u32);
void *func_80000A40(void);
#else
s32 allocateHeap(s32);                                /* extern */
s32 func_80000A40();                                /* extern */
#endif
#ifdef TARGET_PC
void osCreateMesgQueue(void *mq, void *msgs, s32 count); /* PC: the port's type (port.h renames it) */
#else
s32 osCreateMesgQueue(s32 *, s32 *, s32);                       /* extern */
#endif
s32 func_800B8C4C(s32);                               /* extern */
s32 func_800B9268(s32);                                 /* extern */
s32 func_800BAD80();                                  /* extern */
#ifdef TARGET_PC
/* PC: D_80038AAC and D_800DCFB8 hold the address of the 0x2E00-byte save buffer (D_800DCFB8 is a u8 * in the files
 * that read the buffer), and D_800DCFD4 the address of the PI handle (func_800B97CC and others hand it to
 * osEPiStartDma as a pointer): an s32 would cut them in half. */
extern u8 *D_80038AAC;
extern s8 D_80038AB0;
extern s32 D_800D2970;
extern u8 *D_800DCFB8;
extern s32 D_800DCFC0;
extern void *D_800DCFD4;
#else
extern s32 D_80038AAC;
extern s8 D_80038AB0;
extern s32 D_800D2970;
extern s32 D_800DCFB8;
extern s32 D_800DCFC0;
extern s32 D_800DCFD4;
#endif
extern u8 D_800DCFF0[];
extern u8 D_800DCFF8[];

void func_800BB2A0(void) {
#ifdef TARGET_PC
    /* PC: the buffer's address, as a pointer. */
    u8 *temp_v0;
#else
    s32 temp_v0;
#endif
    s32 var_s0;

    D_800DCFC0 = 0;
    D_80038AB0 = 0;
    if (D_80038AAC == 0) {
        temp_v0 = allocateHeap(0x2E00);
        var_s0 = 0;
        D_80038AAC = temp_v0;
        D_800DCFB8 = temp_v0;
        do {
            func_800B8C4C(var_s0);
            var_s0 += 1;
        } while (var_s0 < 4);
        func_800B9268(-1);
    } else {
        D_800DCFB8 = D_80038AAC;
    }
    D_800D2970 = 0;
    D_800DCFD4 = func_80000A40();
    osCreateMesgQueue(&D_800DCFF8, &D_800DCFF0, 1);
    func_800BAD80();
}
