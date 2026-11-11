/* @header
 * func_8009A5F4
 * VRAM 0x8009A5F4 | ROM 0x8DA94 | size 0xA8
 * asm: asm/nonmatchings/ovl2_80090000/func_8009A5F4.s
 */
#include "common.h"

void func_80002C58(void);
void func_8000CD84(s16);
void releaseAllResources1211C(void);
void func_80006D14(void *);
void func_8000E6AC(void);
void func_8000EDE0(void);
void func_80011264(void);
void func_80008AF0(void);
void func_80094424(void);
void func_800984C8(void);
extern u8 D_800706A0[];
extern s16 D_800FACEA[];
#ifndef TARGET_PC /* on PC, port_decls.h declares D_800F99C0 (a Nw2SceneObj) */
extern s32 D_800F99C0;
#endif
extern s16 D_800307A0;

void func_8009A5F4(void) {
    u32 i;
    s32 n = 0;

    func_80002C58();
    for (i = 0; i < 4; i++) {
        func_8000CD84(i);
        D_800706A0[i] = 0;
        /* Placeholder: a dead conditional. n is never read, so flow deletes
           the body but keeps the branch; jump2 then deletes the branch and its
           load, leaving only loop.c's walking pointer over D_800FACEA (s1).
           A body jump.c can turn into a store-flag (n++, n += 2) does not work. */
        if (D_800FACEA[i] >= 0) {
            n *= 3;
        }
    }
    releaseAllResources1211C();
    func_80006D14(&D_800F99C0);
    func_8000E6AC();
    func_8000EDE0();
    func_80011264();
    func_80008AF0();
    func_80094424();
    func_800984C8();
    D_800307A0 = 0;
}
