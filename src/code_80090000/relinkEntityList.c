/* @header
 * relinkEntityList  (originally func_80091128)
 * VRAM 0x80091128 | ROM 0x3D898 | size 0x11C
 * asm: asm/nonmatchings/code_80090000/relinkEntityList.s
 */
#include "common.h"

typedef struct {u16 active; union {u16 flags; struct {u8 hi,id;} b;} u; u8 pad[12];} Entry911;
extern u8 *D_800DB674, *D_800DB678, *D_800DB67C;
extern Entry911 *D_800DB684;
extern s32 D_800DB688;

/* Rebuild the display-list page chain: walk the page records (stride 0xDC) and
 * their 0x10-byte page descriptors, re-linking consecutive pages that share a
 * sub-id and detaching those flagged 0x4000. The short path (fewer than 6
 * records) links each page straight to the next while it is active. */
void relinkEntityList(void) {
    u8 *p;
    u8 *last;
    s32 count;
    Entry911 *d;
    u8 *base;
    s32 id;
    u8 *q;
    u8 *next;
    s32 i;
    u8 frm[16];
    do { } while (0);
    p = D_800DB674;
    last = 0;
    do { count = D_800DB688; } while (0);
    d = D_800DB684;
    base = *(u8 **)p;
    id = -1;

    if (count >= 6) {
        q = p + 8;
        if (*(u16 *)((u8 *)d + 2)) {
            do { next = p + 0xDC; } while (0);
            d = (Entry911 *)((u8 *)d + 2);
            i = 0;
            do {
                u16 flags = d[i].u.flags;
                if (id != (flags & 255)) {
                    if (!(flags & 0x4000)) {
                        if (last) {
                            *(u8 **)(last + 8) = p;
                            D_800DB67C = p;
                            last = p;
                        } else {
                            last = p;
                            D_800DB678 = p;
                        }
                        *(u8 **)(q - 4) = next;
                    }
                    id = d[i].u.b.id;
                }
                if (last == p) {
                    *(u8 **)p = base;
                } else {
                    *(u8 **)p = last;
                    if (d[i].u.b.id == d[i + 1].u.b.id)
                        *(u8 **)q = next;
                    else
                        *(u8 **)q = 0;
                }
                i++;
                q += 0xDC;
                next += 0xDC;
                p += 0xDC;
            } while (d[i].active);
        }
    } else {
        u8 *v = p + 8;
        if (*(u16 *)((u8 *)d + 2)) {
            d = (Entry911 *)((u8 *)d + 2);
            i = 0;
            do {
                *(s32 *)(v - 4) = 0;
                *(u8 **)p = base;
                if (d[i + 1].active)
                    *(u8 **)v = p + 0xDC;
                else
                    *(u8 **)v = 0;
                i++;
                v += 0xDC;
                p += 0xDC;
            } while (d[i].active);
        }
    }
}
