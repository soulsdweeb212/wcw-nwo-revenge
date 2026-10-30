/* @header
 * func_80020270
 * VRAM 0x80020270 | ROM 0x20E70 | size 0x34
 * asm: asm/nonmatchings/main/func_80020270.s
 */
#include "common.h"

/* Initialize a four-word record: word0 = arg1 rounded up to the next 16-byte
 * boundary (left unchanged if already aligned), word1 = word0, word2 = arg2,
 * word3 = 0. */
typedef struct {
    s32 start;  /* +0x0: 16-byte-aligned address */
    s32 copy;   /* +0x4: initialized to start */
    s32 value;  /* +0x8: caller value */
    s32 link;   /* +0xC: zeroed */
} Nw2Record20270;

void func_80020270(Nw2Record20270 *record, s32 address, s32 value) {
    s32 pad = 0x10 - (address & 0xF);

    if (pad != 0x10) {
        record->start = (s32)(address + pad);
    } else {
        record->start = address;
    }
    record->value = value;
    record->link = 0;
    record->copy = (s32)record->start;
}
