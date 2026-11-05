/* @header
 * osContGetReadData  (originally func_80023058)
 * VRAM 0x80023058 | ROM 0x23C58 | size 0x9C
 * asm: asm/nonmatchings/main/osContGetReadData.s
 */
/* SDK: libultra 2.0I, ultralib src/io/contreaddata.c (same code as the SDK source). */
#include "common.h"

typedef struct {
    u8 b0, b1, b2, b3;
    u16 f4;
    u8 b6, b7;
} Cmd8;

typedef struct {
    u16 f0;
    u8 f2;
    u8 f3;
    u8 f4;
} Rec6;

extern Cmd8 __osContPifRam[];

/* Copy each 8-byte command/controller record from __osContPifRam into a packed
 * 6-byte destination array: the destination's f4 gets the top two bits of the
 * source's b2 shifted down, and when those bits are zero the source's f4/b6/b7
 * are copied to the destination's f0/f2/f3. __osMaxControllers is the record count. */
void osContGetReadData(u16 *out) {
    Rec6 *dst;
    Cmd8 *src;
    s32 i;

    dst = (Rec6 *)out;
    src = __osContPifRam;
    for (i = 0; i < __osMaxControllers; i++, src++, dst = (Rec6 *)((u8 *)dst + 6)) {
        Cmd8 t = *src;
        s32 v = (t.b2 & 0xC0) >> 4;
        dst->f4 = v;
        if (v == 0) {
            dst->f0 = t.f4;
            dst->f2 = t.b6;
            dst->f3 = t.b7;
        }
    }
}
