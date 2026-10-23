#include "common.h"

/* Fills a 16-byte primitive record: two s16 fields, two zeroed fields, one s16
 * and a u16, followed by four bytes. */
void func_80007920(void *arg0, s16 arg1, s16 arg2, s16 arg3, u16 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8) {
    *(s16 *)((u8 *)arg0 + 0) = arg1;
    *(s16 *)((u8 *)arg0 + 2) = arg2;
    *(s16 *)((u8 *)arg0 + 4) = 0;
    *(s16 *)((u8 *)arg0 + 6) = 0;
    *(s16 *)((u8 *)arg0 + 8) = arg3;
    *(u16 *)((u8 *)arg0 + 0xA) = arg4;
    *(u8 *)((u8 *)arg0 + 0xC) = arg5;
    *(u8 *)((u8 *)arg0 + 0xD) = arg6;
    *(u8 *)((u8 *)arg0 + 0xE) = arg7;
    *(u8 *)((u8 *)arg0 + 0xF) = arg8;
}
