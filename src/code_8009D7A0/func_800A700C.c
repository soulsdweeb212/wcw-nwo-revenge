#include "common.h"

extern u8 D_800F9D12[];
extern u8 D_800F9D30[];
extern u8 D_800F9D34[];
extern u8 D_800FA072[];
extern u8 D_800FA073[];

/* Unlinks the entity id at *arg0 from the two partner slots (D_800FA072/73) of
 * each of the four 0x3B0-stride entities: any slot matching the id is cleared to
 * -1 and that entity's 0x40000000 flag is dropped. */
void func_800A700C(void *arg0) {
    s16 i = 0;
    s32 off = 0;
    for (; i < 4; i++) {
        off = i * 0x3B0;
        if (*(s16 *)(D_800F9D12 + off) != -1) {
            if (*(s8 *)(D_800FA072 + off) == *(s8 *)arg0) {
                *(s8 *)(D_800FA072 + off) = -1;
                *(u64 *)(D_800F9D30 + off) &= ~0x40000000ULL;
            }
            if (*(s8 *)(D_800FA073 + off) == *(s8 *)arg0) {
                *(s8 *)(D_800FA073 + off) = -1;
                *(u64 *)(D_800F9D30 + off) &= ~0x40000000ULL;
            }
        }
    }
}
