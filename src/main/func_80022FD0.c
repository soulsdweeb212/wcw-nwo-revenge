#include "common.h"

s32 func_8001C990(s32, void *, s32);
void packControllerReadCommands(void);
s32 func_80025810(s32, void *);
void func_80027744(void);
void func_800277B0(void);
extern u8 D_8006A260[];
extern u8 D_8007BD30;

/* Reads the controllers: if the previous packet is not already buffered it
 * issues the read command and waits on the queue, then retrieves the response.
 * Returns the read result. */
s32 func_80022FD0(s32 arg0) {
    s32 temp_v0;

    func_80027744();
    if (D_8007BD30 != 1) {
        packControllerReadCommands();
        func_80025810(1, D_8006A260);
        func_8001C990(arg0, 0, 1);
    }
    temp_v0 = func_80025810(0, D_8006A260);
    D_8007BD30 = 1;
    func_800277B0();
    return temp_v0;
}
