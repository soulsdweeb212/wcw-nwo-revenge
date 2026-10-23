#include "common.h"

extern u16 *D_80038A64[];    /* per-bank base table of resource ids */
extern u8 D_80070494[], D_80075468[], D_8007C438[];
extern s16 D_800FACEA[];     /* per-player character id (0xFXX: bank in bits 8-11) */
void func_80003684(void *, u16, void *);

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
            func_80003684(scratchNext2, (u16)(resource + 2), D_8007C438 + 0x180 + i * 0x600);
        }
        i++;
    } while (i < 4);
}
