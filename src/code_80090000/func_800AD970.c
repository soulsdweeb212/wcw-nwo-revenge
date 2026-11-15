/* @header
 * func_800AD970
 * VRAM 0x800AD970 | ROM 0x5A0E0 | size 0x28C
 * asm: asm/nonmatchings/code_80090000/func_800AD970.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: A is a menu and R one of its elements, which hold addresses, so they are common.h's Nw2Menu and Nw2MenuEl,
 * which these views follow (the asserts check): the element list's address before i is 8 bytes on PC. */
typedef struct { u8 pad[0xA]; u16 f; u8 pad2[sizeof(Nw2MenuEl) - 0xC]; } R;
typedef struct { void *items; s16 i; u8 pad2[0xE]; R *r; } A;
_Static_assert(offsetof(R, f) == offsetof(Nw2MenuEl, fA) && sizeof(R) == sizeof(Nw2MenuEl) &&
                   offsetof(A, i) == offsetof(Nw2Menu, cur) && offsetof(A, r) == offsetof(Nw2Menu, el),
               "R and A must follow common.h's Nw2MenuEl and Nw2Menu");
#else
typedef struct { u8 pad[0xA]; u16 f; u8 pad2[0x13C]; } R;
typedef struct { u8 pad[4]; s16 i; u8 pad2[0xE]; R *r; } A;
#endif
extern struct { u8 pad[8]; u16 b; } D_8007EF30;
extern s32 D_800D5F1C;
s16 func_800AAB64(A *, s32);

#define SET(i, n) \
    if (D_800D5F1C < (n)) { \
        r[i].f |= 0x40; \
    } else { \
        r[i].f &= ~0x40; \
    }

#define SET2(i, j, n) \
    if (D_800D5F1C < (n)) { \
        r[i].f |= 0x40; \
        r[j].f |= 0x40; \
    } else { \
        r[i].f &= ~0x40; \
        r[j].f &= ~0x40; \
    }

void func_800AD970(A *a) {
    R *r = a->r;
    switch (D_8007EF30.b & 0xF0) {
    case 0x20:
        if (D_8007EF30.b & 0x8000) {
            SET(0, 2)
        } else {
            SET(0, 4)
            SET(1, 3)
            SET2(2, 3, 2)
        }
        break;
    case 0x40:
        SET(0, 3)
        SET2(1, 2, 2)
        break;
    case 0x80:
        SET(0, 4)
        SET(1, 3)
        SET(2, 2)
        break;
    default:
        SET(0, 2)
        break;
    }
    if (r[a->i].f & 0x40) {
        a->i = func_800AAB64(a, 0x400);
    }
}
