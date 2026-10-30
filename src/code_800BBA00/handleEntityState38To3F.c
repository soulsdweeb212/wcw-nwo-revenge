#include "common.h"

/* Paired-entity action handler for target states 0x38..0x3F (substate = state - 0x38).
 * For the even substates it just raises status bit 0x10 on the target; for the odd
 * substates it raises it on the entity-indexed record table instead. Otherwise it
 * copies the source id into the target, resolves facing via func_800C4610, and selects
 * an animation (func_800A6D80) based on the target flags and state. */
extern u16 D_800FA070[][472];
extern s16 D_800F9D1A[][472];
extern u8 D_800F9D30[];
extern u8 D_800F9D34[];
void func_800E212C(void *);
void func_800A837C(void *);
void func_800A6D80(void *, s32);
void func_800C4610(void *, void *);
void addEntityHealthDelta(void *, s16);
s8 func_800C472C(void *, void *, s32);

#define ReadS16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define ReadU16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define ReadU32(p, o) (*(u32 *)((u8 *)(p) + (o)))
#define ReadFlags(p) (*(u64 *)((u8 *)(p) + 0x20))

void handleEntityState38To3F(u8 *source, u8 *target)
{
    s16 subState;
    s16 i;
    s32 offset;

    source[0x43] = 0;
    subState = ReadU16(target, 0xA) - 0x38;
    switch (subState) {
    case 0: case 4: case 6:
        ReadU16(target, 0x360) |= 0x10;
        return;
    case 1: case 5: case 7:
        D_800FA070[(s8)target[0x353]][0] |= 0x10;
        return;
    }
    target[0x351] = source[0];
    if ((s8)source[0x355] != (s8)target[0])
        target[0x353] = source[0];
    func_800E212C(target);
    func_800A837C(source);
    if (ReadFlags(target) & 0x400000) {
        func_800A6C48(target, 0x57);
        return;
    }
    ReadU32(target, 0x30) = 0x800;
    func_800C4610(source, target);
    if (ReadFlags(target) & 0x8000000)
        ReadU32(target, 0x30) |= 0x1000;
    if (ReadS16(target, 0xA) == 0x17)
        addEntityHealthDelta(target, -10);
    if (ReadFlags(target) & 0x80)
        func_800A6D80(target, 0x62);
    else if (ReadS16(target, 0xA) == 0x74)
        ReadU16(target, 0x360) |= 4;
    else if (ReadS16(target, 0xA) == 0x75) {
        for (i = 0; i < 4; i++) {
            offset = i * 0x3B0;
            if (*(s16 *)((u8 *)D_800F9D1A + offset) == 0x74) {
                if (ReadFlags(target) & 0x8000000)
                    *(u64 *)(D_800F9D30 + offset) |= 0x8000000;
                else
                    *(u64 *)(D_800F9D30 + offset) &= ~0x8000000ULL;
                D_800FA070[i][0] |= 0x10;
                target[0x353] = i;
                target[0x352] = source[0];
                break;
            }
        }
    } else if (!func_800C472C(source, target, 0))
        func_800A6D80(target, 0x28);
}
