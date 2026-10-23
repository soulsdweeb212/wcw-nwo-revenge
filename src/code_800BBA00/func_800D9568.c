#include "common.h"

extern u8 D_8007E228[], D_8007EF30[];
s8 func_800D9814(void);
/* Try to start action 0x81 on the entity:
 *  - when its state (s16 +0xA) is 1, require the global +0x58 bit 0x200, the
 *    +0x170 bit 0x40 clear and the helper func_800D9814() true;
 *  - otherwise require the +0x58 bit 0x200, entity flag 0x200 clear, and a
 *    matching height state: flag 0x200000000 set with +0x3E == 0, or the flag
 *    clear with +0x3E == 2, then set the +0xC override state to 2.
 * Returns 1 if the action was started, else 0. */
s32 func_800D9568(void *arg0) {
    u8 *entity = arg0;
    if (*(s16 *)(entity + 10) == 1) {
        if ((*(u16 *)(D_8007E228 + 0x58) & 0x200) && !(*(u16 *)(D_8007EF30 + 0x170) & 0x40)) {
            if (func_800D9814()) { func_800A6C48(entity, 0x81); return 1; }
        } return 0;
    }
    if ((*(u16 *)(D_8007E228 + 0x58) & 0x200) && !(*(u64 *)(entity + 0x20) & 0x200)) {
        if (((*(u64 *)(entity + 0x20) & 0x200000000ULL) && *(s16 *)(entity + 0x3E) == 0) ||
            (!(*(u64 *)(entity + 0x20) & 0x200000000ULL) && *(s16 *)(entity + 0x3E) == 2)) {
            func_800A6C48(entity, 0x81); *(s16 *)(entity + 12) = 2; return 1;
        }
    }
    return 0;
}
