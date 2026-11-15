/* @header
 * func_8000082C
 * VRAM 0x8000082C | ROM 0x142C | size 0x28
 * asm: asm/nonmatchings/main/func_8000082C.s
 */
#include "common.h"

void func_80090000(void);
#ifdef TARGET_PC
/* PC: both overlays' entries are compiled in, under two names for the one N64 address 0x80090000 (overlay 1's
 * func_80090000 and overlay 2's func_80090000_ovl2), so the PC calls the entry of the overlay that the record names,
 * the one func_80000700 has just loaded from it. */
void func_80090000_ovl2(void);
void func_8000082C(Nw2InitRect rect, Nw2InitBig regions) {
    (void)regions;
    if (port_overlay_of(rect.srcStart, rect.srcEnd) == 1) {
        func_80090000();
    } else {
        func_80090000_ovl2();
    }
}
#else
/* Memory-region init stub (calls func_80090000). */
void func_8000082C(Nw2InitRect rect, Nw2InitBig regions) { func_80090000(); }
#endif
