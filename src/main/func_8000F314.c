/* @header
 * func_8000F314
 * VRAM 0x8000F314 | ROM 0xFF14 | size 0xF4
 * asm: asm/nonmatchings/main/func_8000F314.s
 */
#include "common.h"

extern u8 D_80036D0A;
typedef struct {u8 bytes[0xDC];} F314Record;
extern F314Record D_80056950[];
extern void *D_80058A0C, *D_80058F90, *D_80059520, *D_80059898, *D_80059C10, *D_80059CC8;
void func_80005204(void *, void *);
/* Swaps the arena to the alternate resource set selected by D_80036D0A: binds
 * the shared slot 4 and the two groups of slots (1..3, 5..7) to either the
 * first or second set of buffers, then toggles the selector. */
void func_8000F314(void) {
 u32 i;
 void *a, *b;
 F314Record *base = D_80056950;
 if (D_80036D0A) {
 func_80005204(&base[4],D_80058A0C);
 a=D_80059520; b=D_80059C10;
 } else {
 func_80005204(&base[4],D_80058F90);
 a=D_80059898; b=D_80059CC8;
 }
 for (i=1;i<4;i++) func_80005204(&base[i],a);
 for (i=5;i<8;i++) func_80005204(&base[i],b);
 D_80036D0A ^= 1;
}
