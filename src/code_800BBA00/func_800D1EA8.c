#include "common.h"

/* Build a local XZ transform (4 floats) for an entity and apply it to that entity
 * and its partner. func_800D63F0 fills the transform and returns a scale; the
 * source object is either the entity's attachment (func_800D6610, flag 0x1000)
 * or a table entry selected by field +0x3E; func_800D37C0 scales it; finally both
 * entities are translated by the transform. */
void translateEntityXZ(void *, void *);
f32 func_800D63F0(void *, void *, s32);
void *func_800D6610(void *, s16);
void func_800D37C0(void *, f32, void *);
extern void *D_800E3C90[];
void func_800D1EA8(void *entity, void *partner)
{
    f32 xform[4];
    f32 scale;
    scale = func_800D63F0(entity, xform, (*(u16 *)((u8 *)entity + 0x3AC) & 1) * 2);
    if (*(u32 *)((u8 *)entity + 0x3AC) & 0x1000) {
        func_800D37C0(func_800D6610(entity, *(s16 *)((u8 *)entity + 0x3E)), scale, xform);
    } else {
        func_800D37C0(D_800E3C90[*(s16 *)((u8 *)entity + 0x3E)], scale, xform);
    }
    translateEntityXZ(entity, xform);
    translateEntityXZ(partner, xform);
}
