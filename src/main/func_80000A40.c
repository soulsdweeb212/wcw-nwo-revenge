#include "common.h"

/* One-time initialiser for the control block at D_8003DDB8. It uses the
 * D_8003DDC4 word as an initialised marker (magic 0xA8000000): on the first call
 * it fills the byte fields, zeroes D_8003DDC8, clears 0x60 bytes at +8 and calls
 * func_80021A50 on the block header, then returns the block base. */
extern void func_80021F60(void *, s32);
extern void func_80021A50(void *);
extern u8 D_8003DDB8[];
extern u8 D_8003DDBC, D_8003DDBD, D_8003DDBE, D_8003DDBF, D_8003DDC0, D_8003DDC1;
extern s32 D_8003DDC4, D_8003DDC8;

void *func_80000A40(void) {
    u8 *blk = (u8 *)&D_8003DDC4;
    if (*(s32 *)blk != 0xA8000000) {
        D_8003DDBC = 3;
        *(s32 *)blk = 0xA8000000;
        D_8003DDBD = 5;
        D_8003DDC0 = 0xC;
        D_8003DDBE = 0xD;
        D_8003DDBF = 2;
        D_8003DDC1 = 1;
        D_8003DDC8 = 0;
        func_80021F60(blk + 8, 0x60);
        blk -= 0xC;
        func_80021A50(blk);
        if (blk != 0) blk = (u8 *)&D_8003DDB8;
    }
    return (u8 *)&D_8003DDB8;
}
