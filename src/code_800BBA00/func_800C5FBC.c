/* @header
 * func_800C5FBC
 * VRAM 0x800C5FBC | ROM 0xB945C | size 0x21C
 * asm: asm/nonmatchings/code_800BBA00/func_800C5FBC.s
 */
#include "common.h"

extern f64 D_800E60A8, D_800E60B0;
extern u8 D_800FABE8[], D_800FABEC[], D_800FABEE[];
extern f32 func_800D3890(void *, void *, void *);
/* On the frame where animFrame equals anim.hitStart, maps moveId to one of eight
 * slots and accumulates into the per-wrestler/slot table the XZ distance (func_800D3890)
 * from the root position to the move's first active joint (jointA[move.activeJoint[0]]),
 * plus D_800E60A8: D_800FABE8 = distance (on repeats: (old + new) * D_800E60B0),
 * D_800FABEC = anim.hitStart (averaged on repeats), D_800FABEE = hit count. Data lives 0x40 bytes
 * (8 slots x 8 bytes) per wrestler. */
void func_800C5FBC(Wrestler *w) {
    f32 dist; s16 anim; s32 slot; s32 part32; s32 slot2; s16 part; s32 shifted; u8 id;
    if (w->animFrame == w->anim.hitStart) {
        anim = w->moveId; id = (u8)w->id; part = -1;
        switch (anim) {
        case 5: part=0; break;
        case 0x9D: part=0; break;
        case 6: part=1; break;
        case 0x9F: part=1; break;
        case 0xA1: part=2; break;
        case 0xA3: part=3; break;
        case 0xA5: part=4; break;
        case 0xAF: part=5; break;
        case 0xB0: part=6; break;
        case 0xAC: part=7; break;
        case 4: part=7; break;
        default: break;
        }
        shifted = part << 16; part32 = shifted >> 16;
        if (part32 != -1) {
            dist = (f32)((f64)func_800D3890(&w->x, &w->jointA[w->move.activeJoint[0]], NULL) + D_800E60A8);
            slot = (part32 * 8) + ((s32)(id << 24) >> 18);
            if (*(s16 *)(D_800FABEE + slot) == 0) {
                *(f32 *)(D_800FABE8 + slot) = dist;
                *(s16 *)(D_800FABEC + slot) = w->anim.hitStart;
            } else {
                *(f32 *)(D_800FABE8 + slot) = (f32)((f64)(*(f32 *)(D_800FABE8 + slot) + dist) * D_800E60B0);
                *(s16 *)(D_800FABEC + slot) = (*(s16 *)(D_800FABEC + slot) + w->anim.hitStart) / 2;
            }
            slot2 = ((s32)(part << 16) >> 13) + ((s32)(id << 24) >> 18);
            *(s16 *)(D_800FABEE + slot2) = *(u16 *)(D_800FABEE + slot2) + 1;
        }
    }
}
