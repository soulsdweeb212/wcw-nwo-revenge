/* @header
 * relinkEntityList  (originally func_80091128)
 * VRAM 0x80091128 | ROM 0x3D898 | size 0x11C
 * asm: asm/nonmatchings/code_80090000/relinkEntityList.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: the page records are the scene objects (common.h's Nw2SceneObj), which keep their N64 layout, so their parent
 * (+0), child (+4) and next (+8) are 4-byte handles (port.h's PTR_TO_SLOT) that the PC stores as PTR_TO_SLOT(p); the
 * N64 stores the addresses there. The records walked are the scene's spot list (common.h's Nw2EncSpot, its address in
 * D_800DB684): the N64 reads it from +2, so its "active" halfword is a spot's count and its flags a spot's flags, and
 * the byte it reads at +5 is the flags' low byte, (u8)flags on PC (tools/port_data.py converts the list as 16-bit
 * values). D_800DB674, D_800DB678 and D_800DB67C hold the objects' addresses, so they are pointers. */
extern Nw2SceneObj *D_800DB674, *D_800DB678, *D_800DB67C;
extern Nw2EncSpot *D_800DB684;
extern s32 D_800DB688;

void relinkEntityList(void) {
    Nw2SceneObj *p = D_800DB674;
    Nw2SceneObj *last = NULL;
    Nw2EncSpot *d = D_800DB684;
    u32 base = p->parent;
    s32 id = -1;
    s32 i;

    if (D_800DB688 >= 6) {
        if (d[0].count != 0) {
            i = 0;
            do {
                u16 flags = d[i].flags;
                if (id != (flags & 255)) {
                    if (!(flags & 0x4000)) {
                        if (last != NULL) {
                            last->next = PTR_TO_SLOT(p);
                            D_800DB67C = p;
                            last = p;
                        } else {
                            last = p;
                            D_800DB678 = p;
                        }
                        p->child = PTR_TO_SLOT(p + 1);
                    }
                    id = (u8)d[i].flags;
                }
                if (last == p) {
                    p->parent = base;
                } else {
                    p->parent = PTR_TO_SLOT(last);
                    if ((u8)d[i].flags == (u8)d[i + 1].flags) {
                        p->next = PTR_TO_SLOT(p + 1);
                    } else {
                        p->next = 0;
                    }
                }
                i++;
                p++;
            } while (d[i].count != 0);
        }
    } else {
        if (d[0].count != 0) {
            i = 0;
            do {
                p->child = 0;
                p->parent = base;
                if (d[i + 1].count != 0) {
                    p->next = PTR_TO_SLOT(p + 1);
                } else {
                    p->next = 0;
                }
                i++;
                p++;
            } while (d[i].count != 0);
        }
    }
}
#else
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
#endif
