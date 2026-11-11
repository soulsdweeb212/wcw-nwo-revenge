/* @header
 * func_80096854
 * VRAM 0x80096854 | ROM 0x89CF4 | size 0x46C
 * asm: asm/nonmatchings/ovl2_80090000/func_80096854.s
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
 * addresses as pointers). port_decls.h declares D_800E8438 and D_800E87A8 with that type, and &X[i] steps by whole
 * records. */
typedef Nw2Descr4BA8 Frame;
#else
typedef struct {
    u8 b[0x2C];
} Frame;
#endif

s32 func_8000DEE4(s32);
void func_800907A0(void *a, void *b, s16 x, s16 y, f32 f0, f32 f1, f32 sx, f32 sy, u8 r, u8 g, u8 bl, u8 al);
void func_8009786C(s32);
extern u16 D_800E2B1C[];
extern s16 D_800E2D96[];
extern Sprite D_800E80C8[];
extern Sprite D_800E8280[];
extern Frame D_800E8438[][10];
extern Frame D_800E87A8[][10];
extern s16 D_800E8B18;
extern s16 D_800E8B1A;
extern s16 D_800E8B1C[];
extern s16 D_800E8B20[];
extern s16 D_800F99B6;

void func_80096854(s16 n) {
    s8 d[2];
    u32 i;

    if (D_800F99B6 == 0) {
        if (n >= 1 && n <= 20) {
            if (D_800E8B1A != n) {
                func_8000DEE4(D_800E2D96[n]);
            }
            D_800E8B1A = n;
            D_800E8B18 = 0;
            d[0] = n / 10;
            d[1] = n % 10;
            if (d[0] > 0) {
                for (i = 0; i < 2; i++) {
                    if (D_800E8B20[i] != d[i]) {
                        D_800E8B20[i] = d[i];
                        D_800E8B1C[i] = i;
                        func_800907A0(&D_800E80C8[i], &D_800E8438[i][D_800E8B20[i]], (f32)D_800E2B1C[D_800E8B1C[i]], 0xC,
                                      0.5f, 0.0f, 1.0f, 1.0f, 0xFF, 0xFF, 0xFF, 0);
                        func_800907A0(&D_800E8280[i], &D_800E87A8[i][D_800E8B20[i]], (f32)D_800E2B1C[D_800E8B1C[i]], 0xC,
                                      0.5f, 0.0f, 1.0f, 1.0f, 0xFF, 0, 0, 0);
                    }
#ifdef TARGET_PC
                    /* PC: the objects' work blocks through their handles (see Sprite above). */
                    ((St *)SLOT_TO_PTR(D_800E80C8[i].st))->flags &= ~0x80;
                    ((St *)SLOT_TO_PTR(D_800E8280[i].st))->flags &= ~0x80;
#else
                    D_800E80C8[i].st->flags &= ~0x80;
                    D_800E8280[i].st->flags &= ~0x80;
#endif
                }
            } else {
#ifdef TARGET_PC
                /* PC: as above, the work block through its handle. */
                ((St *)SLOT_TO_PTR(D_800E80C8[0].st))->flags |= 0x80;
                ((St *)SLOT_TO_PTR(D_800E8280[0].st))->flags |= 0x80;
#else
                D_800E80C8[0].st->flags |= 0x80;
                D_800E8280[0].st->flags |= 0x80;
#endif
                if (D_800E8B20[1] != d[1]) {
                    D_800E8B20[1] = d[1];
                    D_800E8B1C[1] = 2;
                    func_800907A0(&D_800E80C8[1], &D_800E8438[1][D_800E8B20[1]], (f32)D_800E2B1C[D_800E8B1C[1]], 0xC,
                                  0.5f, 0.0f, 1.0f, 1.0f, 0xFF, 0xFF, 0xFF, 0);
                    func_800907A0(&D_800E8280[1], &D_800E87A8[1][D_800E8B20[1]], (f32)D_800E2B1C[D_800E8B1C[1]], 0xC,
                                  0.5f, 0.0f, 1.0f, 1.0f, 0xFF, 0, 0, 0);
#ifdef TARGET_PC
                    /* PC: as above, the work block through its handle. */
                    ((St *)SLOT_TO_PTR(D_800E80C8[1].st))->flags &= ~0x80;
                    ((St *)SLOT_TO_PTR(D_800E8280[1].st))->flags &= ~0x80;
#else
                    D_800E80C8[1].st->flags &= ~0x80;
                    D_800E8280[1].st->flags &= ~0x80;
#endif
                }
            }
        }
        func_8009786C(6);
    }
}
