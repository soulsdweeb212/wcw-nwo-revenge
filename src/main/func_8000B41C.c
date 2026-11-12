/* @header
 * func_8000B41C
 * VRAM 0x8000B41C | ROM 0xC01C | size 0x50
 * asm: asm/nonmatchings/main/func_8000B41C.s
 */
#include "common.h"

extern u16 *D_80031998[];
extern s16 D_8003673C[];
#ifdef TARGET_PC
/* PC: D_80032B44 is a table of addresses: per bank, an array of lists, each list the addresses of s16 tables up to a
 * NULL (tools/port_data.py's TABLES; func_8000C91C and func_8000CFD4 declare it so). On PC an entry of a list is a
 * pointer, 8 bytes, so the count steps through the list by pointers. */
extern void ***D_80032B44[];
#else
extern s32 *D_80032B44[];
#endif

/* Decode part arg0 and count the nonzero words in its D_80032B44 list. */
s16 func_8000B41C(u32 arg0) {
    u32 g = (arg0 >> 8) & 0x1F;
    u32 n = (arg0 & 0x1F) - 1;
#ifdef TARGET_PC
    /* PC: the list as the pointers it holds (see D_80032B44 above). */
    void **p = D_80032B44[g][n];
#else
    s32 *p = D_80032B44[g][n];
#endif
    s16 c = 0;
    if (*p != 0) {
        do {
            p++;
            c++;
        } while (*p != 0);
    }
    return c;
}
