/* @header
 * func_80096E34
 * VRAM 0x80096E34 | ROM 0x8A2D4 | size 0x130
 * asm: asm/nonmatchings/ovl2_80090000/func_80096E34.s
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

#ifdef TARGET_PC
/* PC: Frame is the game's display record of a picture, whose PC layout is common.h's Nw2Descr4BA8 (0x50 bytes, its
 * addresses as pointers). port_decls.h declares D_800E8CE8 and D_800E8D40 with that type, and &X[i] steps by whole
 * records. */
typedef Nw2Descr4BA8 Frame;
#else
typedef struct {
    u8 b[0x2C];
} Frame;
#endif

void func_800907A0(void *a, void *b, s16 x, s16 y, f32 f0, f32 f1, f32 sx, f32 sy, u8 r, u8 g, u8 bl, u8 al);
extern Sprite D_800E8B28;
extern Sprite D_800E8C08;
extern Frame D_800E8CE8[];
extern Frame D_800E8D40[];
extern s16 D_800E8D98;
extern s16 D_800E8D9A;

void func_80096E34(s16 arg0) {
    if (arg0 < 2) {
        D_800E8D98 = arg0;
#ifdef TARGET_PC
        /* PC: the object's work block through its handle (see Sprite above). */
        if (((St *)SLOT_TO_PTR(D_800E8B28.st))->flags & 0x80) {
#else
        if (D_800E8B28.st->flags & 0x80) {
#endif
            D_800E8D9A = 0;
            func_800907A0(&D_800E8B28, &D_800E8CE8[arg0], 0xF0, 0xA, 0.5f, 0.0f, 1.0f, 1.0f, 0xFF, 0xFF, 0xFF, 0xF);
            func_800907A0(&D_800E8C08, &D_800E8D40[D_800E8D98], 0xF0, 0xA, 0.5f, 0.0f, 1.0f, 1.0f, 0, 0x57, 0xFF, 0);
        }
    }
}
