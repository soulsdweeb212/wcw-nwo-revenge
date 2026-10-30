/* @header
 * func_800AD2C4
 * VRAM 0x800AD2C4 | ROM 0xA0764 | size 0x190
 * asm: asm/nonmatchings/code_8009D7A0/func_800AD2C4.s
 */
#include "common.h"

void func_800A7C40(void *, s8, s16);
void func_800A7F6C(void *, s32);
extern s16 D_800EB458[];

typedef struct {
    s8 id;
    u8 pad1[0x2B];
    u32 flags;
    u8 pad30[0x37C];
    u32 flags2;
} Nw2PlrD2C4;

void func_800AD2C4(Nw2PlrD2C4 *p, Nw2PlrD2C4 *q, u16 mask, s16 mode) {
    s16 anim;
    u32 flags = p->flags;

    if ((flags & 0x200001) == 0x200001) {
        p->flags = flags | 0x80000;
        func_800A7C40(p, p->id, 0x3A);
    } else if ((flags & 1) && ((mask & 0xC000) == 0xC000)) {
        p->flags = flags | 0x80000;
        func_800A7C40(p, q->id, 0x3C);
    } else {
        if (mask & 0x8000) {
            p->flags |= 0x80000;
            if (mask & 0x800) {
                anim = 0x17;
            } else {
                anim = 0x12;
                if (mask & 0x400) {
                    anim = 0x1C;
                }
            }
        } else {
            anim = 0x21;
            if (mask & 0x800) {
                p++;
                p--;
                anim = 0x26;
            }
            if (mask & 0x400) {
                anim = 0x2B;
            }
            if (mask & 0x200) {
                anim = 0x30;
            }
            if (mask & 0x100) {
                anim = 0x35;
            }
            D_800EB458[p->id] = anim;
            func_800A7C40(p, p->id, anim);
            if (p->flags2 & 0x80000) {
                p->flags |= 0x400000;
                goto done;
            }
            if (mode == 1) {
                anim += 2;
            }
        }
        func_800A7C40(p, p->id, anim);
    }
done:
    func_800A7F6C(p, 0);
}
