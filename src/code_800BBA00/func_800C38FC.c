/* @header
 * func_800C38FC
 * VRAM 0x800C38FC | ROM 0xB6D9C | size 0x17C
 * asm: asm/nonmatchings/code_800BBA00/func_800C38FC.s
 */
#include "common.h"

#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D3B24 */
s8 func_800D3B24(void *, void *, f32, s32);
#endif
void func_800A6CDC(void *, s32);

#ifdef TARGET_PC
/* PC: the callers pass (wrestler, u64 mask, s32 value) and declare it so. On the N64 (o32) a u64 argument starts in an
 * even register, so mask arrives in a2/a3 and a1 carries nothing; the N64 definition names that unused register arg1.
 * On x86-64 each argument takes the next register, so the PC definition has no arg1, and mask and value arrive where
 * the callers put them. */
void func_800C38FC(Wrestler *arg0, u64 mask, s32 value) {
#else
void func_800C38FC(Wrestler *arg0, s32 arg1, u64 mask, s32 value) {
#endif
    s16 i;
    s32 result = value | 0x80000000;

    for (i = 0; i < 4; i++) {
        if (i == arg0->id) continue;
        if (D_800F9D10[i].characterId == -1) continue;
        if ((D_800F9D10[i].flags & 0x80) && !(D_800F9D10[i].flags & mask)) {
            if (func_800D3B24(&arg0->jointA[1], &D_800F9D10[i].jointA[1], 66.0f, 0)) {
                func_800A6CDC(&D_800F9D10[i], 0x62);
                D_800F9D10[i].hitInfo = result;
                D_800F9D10[i].heldById = arg0->id;
            }
        }
    }
}
