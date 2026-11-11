/* @header
 * loadPlayerResourceSet  (originally func_800B7BC4)
 * VRAM 0x800B7BC4 | ROM 0xAB064 | size 0x130
 * asm: asm/nonmatchings/code_8009D7A0/loadPlayerResourceSet.s
 */
#include "common.h"

extern u16 *D_80038A64[];    /* per-bank base table of resource ids */
#ifdef TARGET_PC
/* PC: port_decls.h declares D_8007C438 (the texture-cache table, void *[4][23]); the animation rows this file loads
 * at its +0x180 on the N64 are the PC variable D_8007C5B8. So the PC copy of this line leaves it out. */
extern u8 D_80070494[], D_80075468[];
#else
extern u8 D_80070494[], D_80075468[], D_8007C438[];
#endif
extern s16 D_800FACEA[];     /* per-player character id (0xFXX: bank in bits 8-11) */
#ifndef TARGET_PC /* on PC, port.h declares the loader functions */
void func_80003684(void *, u16, void *);
#endif

/* For each of the four players, look up the character id, resolve its base
 * resource from the bank table, and load the base and the two following
 * resources into that player's three resource slots. */
void loadPlayerResourceSet(void) {
    u8 scratchBase[16], scratchNext1[16], scratchNext2[16];
    s16 i = 0;
    s16 charId;
    u16 resource;
    s32 resourceIndex;
    do {
        charId = D_800FACEA[i];
        if (charId != -1) {
            resourceIndex = (charId & 0xFF) - 1;
            resource = *(u16 *)((resourceIndex * 2) + (u8 *)D_80038A64[(charId & 0xF00) >> 8]);
            func_80003684(scratchBase, resource, D_80070494 + 0x10C + i * 0x40);
            func_80003684(scratchNext1, (u16)(resource + 1), D_80075468 + 0x10 + i * 0x1A30);
#ifdef TARGET_PC
            /* PC: player i's row of animation ids, D_8007C5B8[i] (port_decls.h); the N64 computes it as
             * D_8007C438 + 0x180 + i * 0x600. */
            func_80003684(scratchNext2, (u16)(resource + 2), D_8007C5B8[i]);
#else
            func_80003684(scratchNext2, (u16)(resource + 2), D_8007C438 + 0x180 + i * 0x600);
#endif
        }
        i++;
    } while (i < 4);
}
