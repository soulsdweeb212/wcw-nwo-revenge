/* @header
 * func_8009678C
 * VRAM 0x8009678C | ROM 0x89C2C | size 0xC8
 * asm: asm/nonmatchings/ovl2_80090000/func_8009678C.s
 */
#include "common.h"

typedef struct { s32 flags; } St;

#ifdef TARGET_PC
/* PC: Sprite is the game's 0xDC-byte scene object, common.h's Nw2SceneObj, which keeps its N64 layout on PC: the
 * address of its first work block at +0x14 is a 4-byte handle (port.h's PTR_TO_SLOT), and St is the start of that work
 * block (its kind word, Nw2SceneWork's kind). Code reaches the work block through SLOT_TO_PTR. The asserts check the
 * view against both records. */
typedef struct {
    u8 pad0[0x14];
    u32 st;
    u8 pad18[0xC4];
} Sprite;
_Static_assert(sizeof(Sprite) == sizeof(Nw2SceneObj) && offsetof(Sprite, st) == offsetof(Nw2SceneObj, work) &&
                   offsetof(St, flags) == offsetof(Nw2SceneWork, kind),
               "Sprite must follow Nw2SceneObj, and St Nw2SceneWork");
#else
typedef struct {
    u8 pad0[0x14];
    St *st;
    u8 pad18[0xC4];
} Sprite;
#endif

void func_80097BB4(void);
extern u8 D_8007EF30[];
extern Sprite D_800E80C8[];
extern Sprite D_800E8280[];
extern s16 D_800E8B1A;
extern s16 D_800E8B20[];
extern s8 D_800F99B4;

void func_8009678C(void) {
    s32 n;
    u32 i;

    n = 10;
    if (D_8007EF30[0x1A1] == 1) {
        n = 20;
    }
    if (D_800E8B1A < n) {
        for (i = 0; i < 2; i++) {
            D_800E8B20[i] = -1;
#ifdef TARGET_PC
            /* PC: the objects' work blocks through their handles (see Sprite above). */
            if (!(((St *)SLOT_TO_PTR(D_800E80C8[i].st))->flags & 0x80)) {
                ((St *)SLOT_TO_PTR(D_800E80C8[i].st))->flags |= 0x80;
                ((St *)SLOT_TO_PTR(D_800E8280[i].st))->flags |= 0x80;
#else
            if (!(D_800E80C8[i].st->flags & 0x80)) {
                D_800E80C8[i].st->flags |= 0x80;
                D_800E8280[i].st->flags |= 0x80;
#endif
            }
        }
    }
    D_800E8B1A = 0;
    if (D_800F99B4 == 6) {
        func_80097BB4();
    }
}
