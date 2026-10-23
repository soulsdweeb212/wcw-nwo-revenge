#include "common.h"

/* runEntityPairAction: nine-state action machine for the actor at D_800FAF5C as
 * it interacts with the partner at D_800F9B00.  It plays the reach/grab
 * animations, resolves the linked target and, once engaged, hands off to
 * updateEntityPairInteraction; states 5..8 handle the finish/throw variants. */

typedef struct {
    s32 f0;
    s16 f4;
    s16 f6;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 fE;
    u8 pad10[6];
    s16 f16;
    u8 pad18[8];
    u64 flags;
    u8 pad28[4];
    u32 f2C;
    u8 pad30[0x341];
    u8 f371;
} Nw2ActionCEC10;

extern Nw2ActionCEC10 *D_800FAF5C;
extern Nw2ActionCEC10 *D_800F9B00;
extern u16 D_800FABE6;
extern f32 D_800F9B0C;
extern s32 D_800F9B14;
extern s8 D_800FADB8;
extern s16 D_800FADBE[];
extern u16 D_800FAF8E[];
extern u8 D_800F9D10[];

void func_800D25D0(Nw2ActionCEC10 *, f32);
s32 func_800D2B64(Nw2ActionCEC10 *, f32, u16, s32);
void func_800D427C(Nw2ActionCEC10 *, s16, s32);
void func_800D4AD0(Nw2ActionCEC10 *);
void func_800D6658(Nw2ActionCEC10 *, Nw2ActionCEC10 *, u16, s32, f32);
void func_800A7240(Nw2ActionCEC10 *, s32, s32, u64);
void func_800A7364(Nw2ActionCEC10 *);
void func_800A7D1C(Nw2ActionCEC10 *, s32);
void beginEntityActionA8D8C(Nw2ActionCEC10 *);
void func_800A7188(Nw2ActionCEC10 *);
void func_800E212C(Nw2ActionCEC10 *);
void func_800B68A0(Nw2ActionCEC10 *, Nw2ActionCEC10 *, Nw2ActionCEC10 *);
s8 func_800CE748(Nw2ActionCEC10 *);
s8 updateEntityPairInteraction(Nw2ActionCEC10 *, void *);
void func_800CF1B8(void *, void *, s32, s32);

void runEntityPairAction(void) {
    switch (D_800FAF5C->fC) {
    case 0:
        D_800FADBE[D_800FADB8] = 0;
        D_800FAF8E[D_800FADB8] = 0;
        D_800FAF5C->fC++;
        /* fall through */
    case 1:
        D_800FAF5C->f2C = 0;
        if (D_800FAF5C->flags & 0x80000ULL)
            D_800FAF5C->f2C = 1;
        D_800FAF5C->fC++;
        /* fall through */
    case 2:
        if (D_800FAF5C->flags & 0x20000000000ULL) {
            if (D_800FAF5C->flags & 0x80ULL)
                D_800FAF5C->flags |= 0x800000000000000ULL;
            func_800D25D0(D_800FAF5C, 4.0f);
            func_800D2B64(D_800FAF5C, 4.0f, 0, 0xFFFFE);
            if (D_800FAF5C->f4 <= 0) {
                D_800FAF5C->flags &= ~0x20000000000ULL;
                if (D_800FAF5C->flags & 0x800000000000000ULL) {
                    func_800A7364(D_800FAF5C);
                    func_800D427C(D_800FAF5C, 0x108D, 2);
                    return;
                }
            }
        }
        if (!(D_800FAF5C->flags & 0x20000000000ULL)) {
            func_800D6658(D_800FAF5C, D_800F9B00, D_800FABE6, 0, D_800F9B0C);
            if (!(D_800FAF5C->flags & 0x80ULL)) {
                s32 animId = D_800F9B14;
                func_800A7240(D_800FAF5C, animId, 0x155, 0x100000000ULL);
            }
        }
        D_800FAF8E[D_800FADB8] |= D_800FABE6 & 0xF00;
        if (D_800FABE6 & 0x8000) {
            if ((s16)(++D_800FADBE[D_800FADB8]) >= 8) {
                D_800FAF5C->f2C |= 2;
                D_800FAF5C->fC++;
                D_800FAF5C->flags |= 0x10000000ULL;
            }
        } else {
            D_800FAF5C->fC++;
            D_800FAF5C->flags |= 0x10000000ULL;
        }
        return;
    case 3:
        func_800E212C(D_800FAF5C);
        func_800CF1B8(D_800FAF5C, D_800F9B00, D_800FAF8E[D_800FADB8], D_800F9B14);
        D_800FAF5C->fC++;
        break;
    case 4: {
        s8 linkedId;
        if (!(D_800FAF5C->f2C & 0x14)) {
            if (D_800FAF5C->f6 <= D_800FAF5C->f371)
                func_800A7240(D_800FAF5C, D_800F9B14, 0x16, 0);
        }
        linkedId = func_800CE748(D_800FAF5C);
        if (linkedId != -1) {
            if (updateEntityPairInteraction(D_800FAF5C, &D_800F9D10[linkedId * 0x3B0]))
                return;
        }
        if (!(D_800FAF5C->flags & 0x80ULL)) {
            if (D_800FAF5C->f8 != 0xEA2)
                func_800D2B64(D_800FAF5C, 1.0f, 0, 2);
            func_800D25D0(D_800FAF5C, 2.0f);
        }
        func_800A7188(D_800FAF5C);
        return;
    }
    case 5:
        func_800D427C(D_800FAF5C, 0xEBC, 3);
        D_800FAF5C->fC++;
        break;
    case 6:
        if (D_800FAF5C->f4 <= 0) {
            func_800A7D1C(D_800FAF5C, 1);
            func_800B68A0(D_800FAF5C, D_800F9B00, D_800FAF5C);
            func_800D4AD0(D_800FAF5C);
            beginEntityActionA8D8C(D_800FAF5C);
        }
        return;
    case 7:
        func_800D427C(D_800FAF5C, 0xE86, 3);
        D_800FAF5C->f2C = 0x408;
        if (D_800FAF5C->flags & 0x80000ULL)
            D_800FAF5C->f2C = 0x40B;
        D_800FAF5C->fC = 4;
        return;
    case 8:
        func_800D427C(D_800FAF5C, 0xE87, 1);
        D_800FAF5C->f2C = 0x420;
        D_800FAF5C->fC = 4;
        return;
    }
}
