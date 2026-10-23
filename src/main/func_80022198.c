#include "common.h"

typedef struct {
    s32 a, b;
} Nw2Pair;

extern u32 func_80026AF0(void);
extern s32 func_80025480(void *, s32);
extern s32 __osContRamRead(s32, s32, s32, void *);
extern s32 __osContRamWrite(s32, s32, u16, void *, s32);

/* Writes the 0x20-byte relay header (out) to the Controller Pak and verifies it.
 * It invalidates the id (-1), stamps a timestamp (func_80026AF0) and copies two
 * pairs from header, then walks pages: locks each page (func_80025480), reads the
 * page, builds the complemented write buffer, writes and reads it back, advancing
 * until a stable/complement page is found (up to page 0x3E).  It then fills the
 * checksum fields (sum at +0x1C and its complement at +0x1E), writes out to the
 * four data pages via __osContRamWrite and reads page 1 back to confirm. */
s32 func_80022198(void *pfs, void *header, u8 *out) {
    u8 pageBuf[0x20];
    u8 readBuf[0x20];
    s16 pageIdx[4];
    s32 page;
    s32 i;
    s32 status;
    s32 changed;

    *(s32 *)out = -1;
    *(s32 *)(out + 4) = func_80026AF0();
    *(Nw2Pair *)(out + 8) = *(Nw2Pair *)((u8 *)header + 8);
    *(Nw2Pair *)(out + 0x10) = *(Nw2Pair *)((u8 *)header + 0x10);

    page = 0;
    if (*(u8 *)((u8 *)pfs + 0x65) != 0) {
        status = func_80025480(pfs, 0);
        if (status != 0) return status;
    }
    while (1) {
        status = func_80025480(pfs, page & 0xFF);
        if (status != 0) return status;
        status = __osContRamRead(*(s32 *)((u8 *)pfs + 4), *(s32 *)((u8 *)pfs + 8), 0, pageBuf);
        if (status != 0) return status;
        pageBuf[0] = page | 0x80;
        for (i = 1; i < 0x20; i++) {
            pageBuf[i] = ~pageBuf[i];
        }
        status = __osContRamWrite(*(s32 *)((u8 *)pfs + 4), *(s32 *)((u8 *)pfs + 8), 0, pageBuf, 0);
        if (status != 0) return status;
        status = __osContRamRead(*(s32 *)((u8 *)pfs + 4), *(s32 *)((u8 *)pfs + 8), 0, readBuf);
        if (status != 0) return status;
        for (i = 0; i < 0x20; i++) {
            if (readBuf[i] != pageBuf[i]) break;
        }
        if (i == 0x20) {
            if (page > 0) {
                status = func_80025480(pfs, 0);
                if (status != 0) return status;
                status = __osContRamRead(*(s32 *)((u8 *)pfs + 4), *(s32 *)((u8 *)pfs + 8), 0, pageBuf);
                if (status != 0) return status;
                if (pageBuf[0] != 0x80) break;
            }
            page++;
            if (page >= 0x3E) break;
        } else {
            break;
        }
    }

    if (*(u8 *)((u8 *)pfs + 0x65) != 0) {
        status = func_80025480(pfs, 0);
        if (status != 0) return status;
    }
    {
        u16 *p2 = (u16 *)(out + 0x1E);
        u16 *pa = (u16 *)out;
        u16 *p1 = (u16 *)(out + 0x1C);
        changed = page > 0;
        *(u16 *)(out + 0x18) = changed | (*(u16 *)((u8 *)header + 0x18) & 0xFFFE);
        out[0x1A] = page;
        out[0x1B] = *(u8 *)((u8 *)header + 0x1B);
        *p2 = 0;
        *p1 = 0;
        do {
            u16 v = *pa;
            *p1 += v;
            pa += 1;
            *p2 += (u16)~v;
        } while ((u32)pa < (u32)(out + 0x1C));
    }

    pageIdx[0] = 1;
    pageIdx[1] = 3;
    pageIdx[2] = 4;
    pageIdx[3] = 6;
    for (i = 0; i < 4; i++) {
        status = __osContRamWrite(*(s32 *)((u8 *)pfs + 4), *(s32 *)((u8 *)pfs + 8), *(u16 *)((u8 *)pageBuf + 0x40 + i * 2), out, 1);
        if (status != 0) return status;
    }
    status = __osContRamRead(*(s32 *)((u8 *)pfs + 4), *(s32 *)((u8 *)pfs + 8), 1, pageBuf);
    if (status != 0) return status;
    for (i = 0; i < 0x20; i++) {
        if (pageBuf[i] != out[i]) return 0xA;
    }
    return 0;
}
