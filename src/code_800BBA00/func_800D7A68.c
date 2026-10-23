#include "common.h"

/* Decode the "action group" nibble (bits 8-11) of a packed status word into a
 * small group id: 0x800->1, 0x900->2, 0x100->3, 0x500->4, 0x400->5, 0x600->6,
 * 0x200->7, 0xA00->8, anything else ->0. */
s32 func_800D7A68(s32 status) {
    s32 field = status & 0xF00;
    u16 code = field;

    if (field != 0) {
        if (code == 0x800) {
            return 1;
        }
        if (code == 0x900) {
            return 2;
        }
        if (code == 0x100) {
            return 3;
        }
        if (code == 0x500) {
            return 4;
        }
        if (code == 0x400) {
            return 5;
        }
        if (code == 0x600) {
            return 6;
        }
        if (code == 0x200) {
            return 7;
        }
        if (code == 0xA00) {
            return 8;
        }
    }
    return 0;
}
