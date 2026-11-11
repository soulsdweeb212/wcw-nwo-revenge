/* @header
 * func_80096CC0
 * VRAM 0x80096CC0 | ROM 0x8A160 | size 0x16C
 * asm: asm/nonmatchings/ovl2_80090000/func_80096CC0.s
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

void func_8009786C(s32);
extern u8 D_8007E228[];
extern Sprite D_800E7950[];
extern s16 D_800E91CC;
extern s16 D_800E91CE;
extern s16 D_800E91D0;
extern s16 D_800F99B6;
extern s16 D_800F9A9C;

void func_80096CC0(s32 btn) {
    s16 s;
    u32 i;

    if (D_800F99B6 == 0) {
        D_800E91CE = 0x1E;
        D_800E91D0 = 0;
        s = -1;
        if (btn & 0x4000) {
            D_800E91CC = 4;
            s = 10;
        } else if (btn & 0x800) {
            D_800E91CC = 6;
            D_800E91CE = 0;
            s = 10;
        } else if (btn & 0x2000) {
            D_800E91CC = 0;
            s = 3;
        } else if (btn & 0x1000) {
            D_800E91CC = 1;
            s = 5;
        } else if (btn & 0x8000) {
            D_800E91CC = 3;
            s = 10;
        } else if (btn & 0xD0000) {
            D_800E91CC = 2;
            s = 7;
        } else if (btn & 0x20000) {
            D_800E91CC = 5;
            s = 7;
        }
        if (s >= 0) {
            func_8009786C(s);
        }
        if (*(u32 *)(D_8007E228 + 0x620) & 0x100000) {
            D_800F99B6 = 1;
            D_800F9A9C = 1;
#ifdef TARGET_PC
            /* PC: the object's work block through its handle (see Sprite above). */
            if (!(((St *)SLOT_TO_PTR(D_800E7950[0].st))->flags & 0x80)) {
#else
            if (!(D_800E7950[0].st->flags & 0x80)) {
#endif
                for (i = 0; i < 5; i++) {
#ifdef TARGET_PC
                    /* PC: as above, the work block through its handle. */
                    ((St *)SLOT_TO_PTR(D_800E7950[i].st))->flags |= 0x80;
#else
                    D_800E7950[i].st->flags |= 0x80;
#endif
                }
            }
        }
    }
}
