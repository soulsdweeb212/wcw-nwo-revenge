/* @header
 * func_80096210
 * VRAM 0x80096210 | ROM 0x896B0 | size 0x57C
 * asm: asm/nonmatchings/ovl2_80090000/func_80096210.s
 */
#include "common.h"

typedef struct {
    s32 flags;
} Node;

#ifdef TARGET_PC
/* PC: ObjDC is the game's 0xDC-byte scene object, common.h's Nw2SceneObj, which keeps its N64 layout on PC: the address
 * of its first work block at +0x14 is a 4-byte handle (port.h's PTR_TO_SLOT), and Node is the start of that work block
 * (its kind word, Nw2SceneWork's kind). Code reaches the work block through SLOT_TO_PTR. The asserts check the view
 * against both records. */
typedef struct {
    u8 pad0[0x14];
    u32 node;
    u8 pad18[0xC4];
} ObjDC;
_Static_assert(sizeof(ObjDC) == sizeof(Nw2SceneObj) && offsetof(ObjDC, node) == offsetof(Nw2SceneObj, work) &&
                   offsetof(Node, flags) == offsetof(Nw2SceneWork, kind),
               "ObjDC must follow Nw2SceneObj, and Node Nw2SceneWork");
#else
typedef struct {
    u8 pad0[0x14];
    Node *node;
    u8 pad18[0xC4];
} ObjDC;
#endif

#ifdef TARGET_PC
/* PC: Rec2C is the game's display record of a picture, whose PC layout is common.h's Nw2Descr4BA8 (0x50 bytes, its
 * addresses as pointers). port_decls.h declares D_800E7FB8, D_800E8040, D_800E8438, D_800E87A8, D_800E8F60, D_800E9098,
 * D_800E9398 and D_800E93F0 with that type, and &X[i] steps by whole records. */
typedef Nw2Descr4BA8 Rec2C;
#else
typedef struct {
    u8 data[0x2C];
} Rec2C;
#endif

extern u16 D_800E2B1C[];
extern s16 D_800E2B64[];
extern s16 D_800E2B78[];
extern ObjDC D_800E7DF8;
extern ObjDC D_800E7ED8;
#ifndef TARGET_PC /* on PC these labels, one record before D_800E7FB8 and D_800E8040, have no symbol */
extern Rec2C D_800E7F8C[];
extern Rec2C D_800E8014[];
#endif
extern s16 D_800E80C4;
extern s16 D_800E80C6;
extern ObjDC D_800E80C8[];
extern ObjDC D_800E8280[];
extern Rec2C D_800E8438[][10];
extern Rec2C D_800E87A8[][10];
extern s16 D_800E8B18;
extern s16 D_800E8B1A;
extern s16 D_800E8B1C[];
extern s16 D_800E8B20[];
extern ObjDC D_800E8DA0;
extern ObjDC D_800E8E80;
extern Rec2C D_800E8F60[];
extern Rec2C D_800E9098[];
extern s16 D_800E91CC;
extern s16 D_800E91CE;
extern s16 D_800E91D0;
extern ObjDC D_800E91D8;
extern ObjDC D_800E92B8;
extern Rec2C D_800E9398[];
extern Rec2C D_800E93F0[];
extern s16 D_800E9448;
extern s16 D_800E944A;
s32 func_8000DEE4(s16);
void MusHandleSetReverb(s32, s32);
s32 func_80090A38(ObjDC *, Rec2C *, ObjDC *, Rec2C *, f32, s16, s32);
s32 func_80091108(ObjDC *, Rec2C *, ObjDC *, Rec2C *, f32, s16, s16);
s32 func_80091748(ObjDC *, Rec2C *, ObjDC *, Rec2C *, s16);
s8 func_800D633C(void);

void func_80096210(void) {
    s32 done = 0;
    u32 i;

    if (func_800D633C()) {
#ifdef TARGET_PC
        /* PC: the objects' work blocks through their handles (see ObjDC above). */
        ((Node *)SLOT_TO_PTR(D_800E7DF8.node))->flags |= 0x80;
        ((Node *)SLOT_TO_PTR(D_800E7ED8.node))->flags |= 0x80;
#else
        D_800E7DF8.node->flags |= 0x80;
        D_800E7ED8.node->flags |= 0x80;
#endif
    } else if (D_800E80C4 > 0) {
#ifdef TARGET_PC
        /* PC: as above for the work blocks. The labels D_800E7F8C and D_800E8014 have no symbol; D_800E80C4 is 1 to 3
         * here, so the records are the base arrays' elements D_800E80C4 - 1. */
        ((Node *)SLOT_TO_PTR(D_800E7DF8.node))->flags &= ~0x80;
        ((Node *)SLOT_TO_PTR(D_800E7ED8.node))->flags &= ~0x80;
        if (func_80090A38(&D_800E7DF8, &D_800E7FB8[D_800E80C4 - 1], &D_800E7ED8, &D_800E8040[D_800E80C4 - 1], 10.0f,
                          D_800E80C6, 0) == 0) {
#else
        D_800E7DF8.node->flags &= ~0x80;
        D_800E7ED8.node->flags &= ~0x80;
        if (func_80090A38(&D_800E7DF8, &D_800E7F8C[D_800E80C4], &D_800E7ED8, &D_800E8014[D_800E80C4], 10.0f, D_800E80C6, 0) == 0) {
#endif
            D_800E80C6++;
        } else {
            D_800E80C4 = 0;
        }
    }

    if (func_800D633C()) {
        for (i = 0; i < 2; i++) {
#ifdef TARGET_PC
            /* PC: as above, the work block through its handle. */
            ((Node *)SLOT_TO_PTR(D_800E80C8[i].node))->flags |= 0x80;
            ((Node *)SLOT_TO_PTR(D_800E8280[i].node))->flags |= 0x80;
#else
            D_800E80C8[i].node->flags |= 0x80;
            D_800E8280[i].node->flags |= 0x80;
#endif
        }
    } else {
        if (D_800E8B1A >= 10) {
#ifdef TARGET_PC
            /* PC: as above, the work block through its handle. */
            ((Node *)SLOT_TO_PTR(D_800E80C8[0].node))->flags &= ~0x80;
            ((Node *)SLOT_TO_PTR(D_800E8280[0].node))->flags &= ~0x80;
#else
            D_800E80C8[0].node->flags &= ~0x80;
            D_800E8280[0].node->flags &= ~0x80;
#endif
            func_80091108(&D_800E80C8[0], &D_800E8438[0][D_800E8B20[0]], &D_800E8280[0], &D_800E87A8[0][D_800E8B20[0]], D_800E2B1C[D_800E8B1C[0]], D_800E8B18, D_800E8B1A);
        }
        if (D_800E8B1A > 0) {
#ifdef TARGET_PC
            /* PC: as above, the work block through its handle. */
            ((Node *)SLOT_TO_PTR(D_800E80C8[1].node))->flags &= ~0x80;
            ((Node *)SLOT_TO_PTR(D_800E8280[1].node))->flags &= ~0x80;
#else
            D_800E80C8[1].node->flags &= ~0x80;
            D_800E8280[1].node->flags &= ~0x80;
#endif
            if (func_80091108(&D_800E80C8[1], &D_800E8438[1][D_800E8B20[1]], &D_800E8280[1], &D_800E87A8[1][D_800E8B20[1]], D_800E2B1C[D_800E8B1C[1]], D_800E8B18, D_800E8B1A) == 0) {
                D_800E8B18++;
            } else {
                D_800E8B1A = 0;
                D_800E8B18 = -1;
            }
        }
    }

    if (D_800E91CE > 0) {
        D_800E91CE--;
    } else {
        if ((u16)D_800E91CC < 7) {
#ifdef TARGET_PC
            /* PC: as above, the work block through its handle. */
            ((Node *)SLOT_TO_PTR(D_800E8DA0.node))->flags &= ~0x80;
            ((Node *)SLOT_TO_PTR(D_800E8E80.node))->flags &= ~0x80;
#else
            D_800E8DA0.node->flags &= ~0x80;
            D_800E8E80.node->flags &= ~0x80;
#endif
            done = func_80090A38(&D_800E8DA0, &D_800E8F60[D_800E91CC], &D_800E8E80, &D_800E9098[D_800E91CC], 42.0f, D_800E91D0, 1);
            if (D_800E91D0 == 6 && D_800E2B64[D_800E91CC] > 0) {
                MusHandleSetReverb(func_8000DEE4(D_800E2B64[D_800E91CC]), 30);
            }
        }
        D_800E91D0++;
        if (done) {
#ifdef TARGET_PC
            /* PC: as above, the work block through its handle. */
            ((Node *)SLOT_TO_PTR(D_800E8DA0.node))->flags |= 0x80;
            ((Node *)SLOT_TO_PTR(D_800E8E80.node))->flags |= 0x80;
#else
            D_800E8DA0.node->flags |= 0x80;
            D_800E8E80.node->flags |= 0x80;
#endif
            D_800E91CC = -1;
        }
    }

    if (D_800E9448 >= 0) {
#ifdef TARGET_PC
        /* PC: as above, the work block through its handle. */
        ((Node *)SLOT_TO_PTR(D_800E91D8.node))->flags &= ~0x80;
        ((Node *)SLOT_TO_PTR(D_800E92B8.node))->flags &= ~0x80;
#else
        D_800E91D8.node->flags &= ~0x80;
        D_800E92B8.node->flags &= ~0x80;
#endif
        if (func_80091748(&D_800E91D8, &D_800E9398[D_800E9448], &D_800E92B8, &D_800E93F0[D_800E9448], D_800E944A) == 0) {
            switch (D_800E944A) {
            case 6:
            case 0x4E:
                func_8000DEE4(D_800E2B78[D_800E9448]);
                break;
            }
            D_800E944A++;
        } else {
#ifdef TARGET_PC
            /* PC: as above, the work block through its handle. */
            ((Node *)SLOT_TO_PTR(D_800E91D8.node))->flags |= 0x80;
            ((Node *)SLOT_TO_PTR(D_800E92B8.node))->flags |= 0x80;
#else
            D_800E91D8.node->flags |= 0x80;
            D_800E92B8.node->flags |= 0x80;
#endif
            D_800E9448 = -1;
        }
    }
}
