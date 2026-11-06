/* @header
 * func_800C3A78
 * VRAM 0x800C3A78 | ROM 0xB6F18 | size 0x778
 * asm: asm/nonmatchings/code_800BBA00/func_800C3A78.s
 */
#include "common.h"

extern s16 D_800E3B14[][8];
extern s16 D_800E3B1C[];
extern s16 D_800E3B64[];
extern s16 D_800E3B74[];
extern s16 D_800E3B78[];
extern s16 D_800E3B7C[];
extern s16 D_800E3B8C[];
extern s16 D_800E3B9C[];
extern s16 D_800E3BA0[];
extern s16 D_800E3BA4[];
extern s16 D_800E3BB4[];
extern s16 D_800E3BC4[];
extern s16 D_800E3BC8[];
extern s16 D_800E3BCC[];
extern s16 D_800E3BE4[];
extern s16 D_800E3BF4[];
extern s16 D_800E3BF8[];
extern s16 D_800E3BFC[];

void func_800A6D80(void *, s32);
void func_800A837C(void *);
s16 func_800BF2FC(void *);
void addEntityHealthDelta(void *, s32);
s8 func_800C41F0(void *, void *);
void func_800C4610(void *, void *);
s8 func_800C472C(void *, void *, s32);
void updateEntityStatus43Timer(void *, s32);
s16 func_800D4148(void);
s8 func_800D4198(s16);
s8 func_800D7B54(void *, s32, s32, s32);
void func_800E212C(void *);

/* src's hit (descriptor arg2) lands on tgt. Nothing happens when tgt has flags 0x600000000000 without
 * 0x0400000000000000. Otherwise src->comboHits is cleared, tgt->heldById = src->id (and tgt->opponentId = src->id
 * unless tgt is src's tag partner), tgt->hitInfo = arg2, func_800E212C(tgt) and func_800C4610(src, tgt) run, and a
 * class bit 0x10000000 / 0x20000000 / 0x40000000 picked by src->move.unk39B is or-ed into hitInfo. Some tgt states
 * are special-cased: 23 takes 10 spirit (addEntityHealthDelta), 64 / 65 / 45..47 may counter through func_800C41F0
 * or ignore the hit, 64 may go to state 0x41, 20 adds hitInfo 0x2000 when frameStatus bit 0 is set. On the apron
 * (WR_FLAG_ON_APRON) a reaction bit is chosen and tgt goes to state 0x28. Otherwise, unless
 * func_800C472C(src, tgt, 0) stuns or knocks it out, tgt->comboHits counts up (at most 4; read signed here),
 * updateEntityStatus43Timer(tgt, 0) reloads its 60-tick timer, more hitInfo bits are derived, and the reaction is
 * either set directly or drawn at random from a table chosen by the hitInfo bits, the health level (func_800BF2FC
 * against D_800E3B1C), flag 0x100000 and tgt->state 0x2D / 0x2E: hitInfo 0x8000, 0x10000 (state 0x2F) or
 * 0x80000 / 0x20000. Every other path ends in state 0x28. */
void func_800C3A78(Wrestler *src, Wrestler *tgt, u32 arg2) {
    u32 bits;
    s16 v;
    s16 i;
    s16 j;
    s16 r;
    s16 *tbl;

    if ((tgt->flags & 0x600000000000ULL) && !(tgt->flags & 0x0400000000000000ULL)) {
        return;
    }
    src->comboHits = 0;
    tgt->heldById = src->id;
    if (src->partnerId != tgt->id) {
        tgt->opponentId = src->id;
    }
    tgt->hitInfo = arg2;
    func_800E212C(tgt);
    func_800C4610(src, tgt);
    switch ((s8)src->move.unk39B) {
    case 0: case 1:
        tgt->hitInfo |= 0x10000000;
        break;
    case 2: case 5:
        tgt->hitInfo |= 0x20000000;
        break;
    case 3: case 4:
        tgt->hitInfo |= 0x40000000;
        break;
    }
    switch (tgt->state) {
    case 23:
        addEntityHealthDelta(tgt, -10);
        break;
    case 64:
        if (!(tgt->flags & 9)) {
            if (tgt->stateTimer < 3 && func_800C41F0(tgt, src)) {
                return;
            }
            if (!(tgt->hitInfo & 0x600) && !(tgt->flags & 0x8000000)) {
                func_800A6C48(tgt, 0x41);
                return;
            }
        }
        break;
    case 65:
        if (!(tgt->flags & 9) && !(tgt->hitInfo & 0x600) && !(tgt->flags & 0x8000000)) {
            return;
        }
        break;
    case 20:
        if (tgt->frameStatus & 1) {
            tgt->hitInfo |= 0x2000;
        }
        break;
    case 45: case 46: case 47:
        if (func_800D7B54(tgt, 0, 0, 2) && func_800C41F0(tgt, src)) {
            return;
        }
        break;
    }
    func_800A837C(src);
    if (tgt->flags & WR_FLAG_ON_APRON) {
        u32 f;
        bits = 0;
        if (tgt->hitInfo & 1) {
            bits = func_800D4198(700) ? 0x400000 : 0x800000;
        }
        if (tgt->hitInfo & 0xE0) {
            bits = func_800D4198(800) ? 0x400000 : 0x800000;
        }
        f = tgt->hitInfo;
        if (f & 0x606) {
            bits = 0x800000;
        }
        if (f & 0x18) {
            bits = 0x1000000;
        }
        if (f & 0x100) {
            bits = 0x800000;
        }
        if (bits == 0) {
            bits = 0x800000;
        }
        tgt->hitInfo = f | bits;
        func_800A6D80(tgt, 0x28);
        return;
    }
    if (func_800C472C(src, tgt, 0)) {
        return;
    }
    tgt->comboHits++;
    if ((s8)tgt->comboHits >= 5) {
        tgt->comboHits = 4;
    }
    updateEntityStatus43Timer(tgt, 0);
    if ((tgt->hitInfo & 0x2010) == 0x2010) {
        tgt->hitInfo |= 0x100000;
    }
    if ((tgt->hitInfo & 0x1008) == 8) {
        tgt->hitInfo |= 0x40000;
    }
    if (tgt->hitInfo & 0x4000) {
        if (tgt->frameStatus & 1) {
            tgt->hitInfo |= 0x4000000;
        } else {
            tgt->hitInfo = (tgt->hitInfo & ~0x4000) | 1;
        }
    }
    if ((tgt->hitInfo & 0x3400) == 0x400) {
        tgt->hitInfo |= 0x8000000;
    }
    {
        u32 f = tgt->hitInfo;
        if (f & 0x4100000) {
            func_800A6D80(tgt, 0x28);
            return;
        }
        if (f & 0x2000) {
            tgt->hitInfo = f | 0x200000;
            func_800A6D80(tgt, 0x28);
            return;
        }
        if (f & 0x8040000) {
            func_800A6D80(tgt, 0x28);
            return;
        }
        if (f & 0x518) {
            if ((f & 0x100) && src->animId == 0x1985) {
                tgt->hitInfo = f | 0x8000;
            } else {
                tgt->hitInfo |= 0x20000;
            }
            func_800A6D80(tgt, 0x28);
            return;
        }
    }
    v = func_800BF2FC(tgt);
    for (i = 0; i < 4; i++) {
        if (v >= D_800E3B1C[i]) {
            break;
        }
    }
    {
        u32 f = tgt->hitInfo;
        if (f & 0x40) {
            tbl = &D_800E3BFC[i * 2];
        } else if (tgt->flags & 0x100000) {
            if (f & 0x202) {
                tbl = &D_800E3B8C[i * 2];
            } else if (f & 4) {
                tbl = D_800E3B9C;
            } else if (f & 1) {
                tbl = &D_800E3B7C[i * 2];
            } else {
                tbl = D_800E3BA0;
            }
        } else if (tgt->state == 0x2E) {
            if (f & 0x202) {
                tbl = &D_800E3BB4[i * 2];
            } else if (f & 4) {
                tbl = D_800E3BC4;
            } else if (f & 1) {
                tbl = &D_800E3BA4[i * 2];
            } else {
                tbl = D_800E3BC8;
            }
        } else if (tgt->state == 0x2D) {
            if (f & 0x202) {
                tbl = &D_800E3BE4[i * 2];
            } else if (f & 4) {
                tbl = D_800E3BF4;
            } else if (f & 1) {
                tbl = &D_800E3BCC[i * 3];
            } else {
                tbl = D_800E3BF8;
            }
        } else {
            if (f & 0x202) {
                tbl = &D_800E3B64[i * 2];
            } else if (f & 4) {
                tbl = D_800E3B74;
            } else if (f & 1) {
                tbl = &D_800E3B14[(s8)tgt->comboHits][i * 2];
            } else {
                tbl = D_800E3B78;
            }
        }
    }
    r = func_800D4148();
    for (j = 0; j < 4; j++) {
        if (tbl[j] >= r) {
            break;
        }
        r -= tbl[j];
    }
    {
        u32 f = tgt->hitInfo;
        if (f & 0x206) {
            j++;
        }
        switch (j) {
        case 0:
            tgt->hitInfo = f | 0x8000;
            break;
        case 1:
            tgt->hitInfo = f | 0x10000;
            func_800A6D80(tgt, 0x2F);
            return;
        case 2:
            if ((f & 0x1002) == 2) {
                tgt->hitInfo = f | 0x80000;
            } else {
                tgt->hitInfo = f | 0x20000;
            }
            break;
        }
    }
    func_800A6D80(tgt, 0x28);
}
