/* @header
 * func_800C5FBC
 * VRAM 0x800C5FBC | ROM 0xB945C | size 0x21C
 * asm: asm/nonmatchings/code_800BBA00/func_800C5FBC.s
 */
#include "common.h"

typedef struct { u8 pad0[0x370]; u8 duration; u8 pad371[0x15]; s16 animation; u8 pad388[0xF]; s8 part; } EntityC5FBC;
extern f64 D_800E60A8, D_800E60B0;
extern u8 D_800FABE8[], D_800FABEC[], D_800FABEE[];
extern f32 func_800D3890(void *, void *, void *);
/* While the entity's timer (+6) equals its duration byte, maps the current
 * animation to one of eight body parts and accumulates that part's heading
 * (from func_800D3890, plus D_800E60A8) into the per-entity/part table:
 * D_800FABE8 = heading, D_800FABEC = duration (averaged on repeats),
 * D_800FABEE = hit count. Data lives 0x40 bytes (8 parts x 8 bytes) per entity. */
void func_800C5FBC(EntityC5FBC *arg0) {
    f32 angle; s16 anim; s32 slot; s32 part32; s32 slot2; s16 part; s32 shifted; u8 id;
    if (*(s16 *)((u8 *)arg0 + 6) == arg0->duration) {
        anim = arg0->animation; id = *(u8 *)arg0; part = -1;
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
            angle = (f32)((f64)func_800D3890((u8 *)arg0 + 0x4C, (u8 *)arg0 + ((arg0->part * 0x10) + 0x5C), NULL) + D_800E60A8);
            slot = (part32 * 8) + ((s32)(id << 24) >> 18);
            if (*(s16 *)(D_800FABEE + slot) == 0) {
                *(f32 *)(D_800FABE8 + slot) = angle;
                *(s16 *)(D_800FABEC + slot) = arg0->duration;
            } else {
                *(f32 *)(D_800FABE8 + slot) = (f32)((f64)(*(f32 *)(D_800FABE8 + slot) + angle) * D_800E60B0);
                *(s16 *)(D_800FABEC + slot) = (*(s16 *)(D_800FABEC + slot) + arg0->duration) / 2;
            }
            slot2 = ((s32)(part << 16) >> 13) + ((s32)(id << 24) >> 18);
            *(s16 *)(D_800FABEE + slot2) = *(u16 *)(D_800FABEE + slot2) + 1;
        }
    }
}
