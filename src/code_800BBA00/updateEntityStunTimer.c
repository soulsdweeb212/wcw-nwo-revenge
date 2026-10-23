#include "common.h"

/* Per-entity stun/recovery timer driver, indexed by the entity id.
 * mode 0 resets the four timers; mode 1 ticks the main timer and steps the
 * entity's 0x14 counter (faster recovery when this entity is 0x100-flagged and
 * the other is not); mode 2 ticks the three sub-timers according to the
 * 0x20000/0x40000/0x80000 status bits, each resetting the counter on expiry;
 * mode 3 shortens sub-timers; mode 4 returns the current 0x80000 timer. */
extern u16 D_800EB498[];
extern u16 D_800EB4A0[];
extern u16 D_800EB4A8[];
extern u16 D_800EB4B0[];

s32 updateEntityStunTimer(u8 *entity, u8 *other, s16 mode) {
    u8 id;
    s16 v;
    s16 h;

    id = entity[0];
    switch (mode) {
    case 0:
        D_800EB498[(s8)id] = 0x78;
        D_800EB4A0[(s8)id] = 0x12C;
        D_800EB4A8[(s8)id] = 0x258;
        D_800EB4B0[(s8)id] = 0x258;
        return 0;
    case 1:
        if (*(u64 *)(entity + 0x20) & 0xE0000ULL) {
            return 0;
        }
        D_800EB4A0[(s8)id] = 0x12C;
        D_800EB4A8[(s8)id] = 0x258;
        D_800EB4B0[(s8)id] = 0x258;
        if ((s16)--D_800EB498[(s8)id] > 0) {
            return 0;
        }
        D_800EB498[(s8)id] = 0x78;
        if ((*(u64 *)(entity + 0x20) & 0x100ULL) && !(*(u64 *)(other + 0x20) & 0x100ULL)) {
            v = *(s16 *)(entity + 0x14) - 8;
            *(s16 *)(entity + 0x14) = v;
            if (v > 0) {
                return 0;
            }
            v = 1;
        } else {
            h = *(s16 *)(entity + 0x14);
            if (h >= 0x33) {
                v = h - 1;
            } else {
                if (h == 0x32) {
                    return 0;
                }
                if (h < 0x1F) {
                    v = h + 3;
                } else {
                    v = h + 2;
                }
            }
        }
        *(s16 *)(entity + 0x14) = v;
        return 0;
    case 2:
        if (*(u64 *)(entity + 0x20) & 0x40000ULL) {
            D_800EB4A0[(s8)id] = 0x12C;
            D_800EB4B0[(s8)id] = 0x258;
            if ((s16)--D_800EB4A8[(s8)id] <= 0) {
                *(s16 *)(entity + 0x14) = 0x46;
                *(u64 *)(entity + 0x20) &= ~0x40000ULL;
            }
        }
        if (*(u64 *)(entity + 0x20) & 0x80000ULL) {
            D_800EB4A0[(s8)id] = 0x12C;
            D_800EB4A8[(s8)id] = 0x258;
            if ((s16)--D_800EB4B0[(s8)id] <= 0) {
                *(s16 *)(entity + 0x14) = 0x32;
                *(u64 *)(entity + 0x20) &= ~0x80000ULL;
            }
        }
        if (*(u64 *)(entity + 0x20) & 0x20000ULL) {
            D_800EB4A8[(s8)id] = 0x258;
            D_800EB4B0[(s8)id] = 0x258;
            if ((s16)--D_800EB4A0[(s8)id] <= 0) {
                *(s16 *)(entity + 0x14) = 0x32;
                *(u64 *)(entity + 0x20) &= ~0x20000ULL;
            }
        }
        return 0;
    case 3:
        if (*(u64 *)(entity + 0x20) & 0x40000ULL) {
            D_800EB4A8[(s8)id] -= 0x3C;
        }
        if (*(u64 *)(entity + 0x20) & 0x80000ULL) {
            D_800EB4B0[(s8)id] -= 0x3C;
        }
        return 0;
    case 4:
        return (s16)D_800EB4B0[(s8)id];
    }
    return 0;
}
