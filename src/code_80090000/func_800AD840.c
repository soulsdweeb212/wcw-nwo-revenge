/* @header
 * func_800AD840
 * VRAM 0x800AD840 | ROM 0x59FB0 | size 0xA4
 * asm: asm/nonmatchings/code_80090000/func_800AD840.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: the menus and their elements hold addresses, so they are common.h's Nw2Menu and Nw2MenuEl, which these views
 * follow (the asserts check). */
typedef struct {
    f32 f0;
    f32 f4;
    u8 pad8[2];
    u16 flags;
    u8 padC[0x16];
    s16 f22;
    u8 pad24[sizeof(Nw2MenuEl) - 0x24];
} El;
_Static_assert(offsetof(El, f4) == offsetof(Nw2MenuEl, y) && offsetof(El, flags) == offsetof(Nw2MenuEl, fA) &&
                   offsetof(El, f22) == offsetof(Nw2MenuEl, f22) && sizeof(El) == sizeof(Nw2MenuEl),
               "El must follow common.h's Nw2MenuEl");
typedef struct { void *items; s16 cur; u8 pad6[0xE]; El *el; u8 pad20[sizeof(Nw2Menu) - 0x20]; } Menu;
_Static_assert(offsetof(Menu, cur) == offsetof(Nw2Menu, cur) && offsetof(Menu, el) == offsetof(Nw2Menu, el) &&
                   sizeof(Menu) == sizeof(Nw2Menu),
               "Menu must follow common.h's Nw2Menu");
#else
typedef struct { f32 f0; f32 f4; u8 pad8[2]; u16 flags; u8 padC[0x16]; s16 f22; u8 pad24[0x148 - 0x24]; } El;
typedef struct { void *items; s16 cur; u8 pad6[0xE]; El *el; u8 pad18[0x138 - 0x18]; } Menu;
#endif
typedef struct {
    u8 pad0[0xE];
    s16 fE;
    s16 f10;
    u8 pad12[2];
    s32 f14;
    u8 pad18[4];
    s32 f1C;
    s32 f20;
    u8 pad24[8];
#ifdef TARGET_PC
    u32 f2C; /* PC: a handle: D_8007EF30 keeps its N64 layout */
#else
    void *f2C;
#endif
} Game;
extern Game D_8007EF30;
extern s32 D_8007FC30;
extern Menu D_800E8230[];
extern u8 lookupSubTables[];
extern s16 D_800E7CB8;
extern s32 D_80038AA8;
void func_800A1550_ovl1(void);
void func_800AD840(void) {
    s32 t;
    func_800A1550_ovl1();
    D_8007EF30.fE = 0;
    D_8007EF30.f10 = 0;
#ifdef TARGET_PC
    D_8007EF30.f2C = PTR_TO_SLOT(lookupSubTables);
#else
    D_8007EF30.f2C = lookupSubTables;
#endif
    D_8007EF30.f20 = 0;
    D_8007EF30.f1C = 0;
    D_800E8230[13].el->f22 = 0;
    D_800E8230[13].cur = 0;
    D_800E8230[14].el->f22 = 0;
    D_8007FC30 = 0;
    D_80038AA8 = 0;
    D_800E7CB8 = 0;
    D_800E8230[14].cur = 0;
    D_8007EF30.f14 &= ~1;
}
