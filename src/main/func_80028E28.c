/* @header
 * func_80028E28
 * VRAM 0x80028E28 | ROM 0x29A28 | size 0x114
 * asm: asm/nonmatchings/main/func_80028E28.s
 */
#include "common.h"

extern u8 asciiCharTable[];
extern u8 D_80038B40[];
extern u8 D_80038DD0[];
extern u8 D_80038DF0[];
extern u8 *D_80064AD0;
extern s32 *D_80064AD4;

static inline s32 charIndex(u8 c, s32 flag) {
    u8 *tbl = asciiCharTable;
    s32 i = 0;
    if (flag & 0x8000)
        tbl = D_80038B40;
    do {
        if (*tbl == c)
            return i;
        tbl++;
        i++;
    } while (*tbl != 0);
    return 0;
}

static inline u8 *glyphData(s32 n, s32 flag) {
    u8 *rec;
    if (n >= 0) {
        if (flag & 0x8000)
            rec = (u8 *)&D_80064AD4[n * 9];
        else
            rec = D_80064AD0 + n * 15;
    } else {
        rec = D_80038DD0;
        if (flag & 0x8000)
            rec = D_80038DF0;
    }
    return rec;
}

static inline s32 glyphWidth(u8 *rec, s32 flag) {
    s32 left, right, w;
    if (flag & 0x8000) {
        left = rec[0];
        right = rec[1];
        w = right - left;
    } else {
        left = rec[1] >> 4;
        right = rec[1] & 0xF;
        if (right < left)
            return 4;
        w = right - left;
    }
    return w + 1;
}

s32 func_80028E28(u8 *s, s32 flag) {
    u8 *rec;

    if (flag & 0x80) {
        if (flag & 0x8000)
            return 0x18;
        return 0xE;
    }
    rec = glyphData(charIndex(*s, flag) * 2, flag);
    if (rec != NULL)
        return glyphWidth(rec, flag);
    return 4;
}
