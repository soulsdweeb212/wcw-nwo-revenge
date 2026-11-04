/* @header
 * func_800B0774
 * VRAM 0x800B0774 | ROM 0x5CEE4 | size 0x660
 * asm: asm/nonmatchings/code_80090000/func_800B0774.s
 */
#include "common.h"

typedef struct { u8 id; u8 pad1[5]; u16 flags; u8 pad8[8]; u8 *list; } Cup;
typedef struct { s16 f0; s16 id; u8 pad4[0xC]; } Pl;
typedef struct {
    u8 pad0[8];
    u16 mode;
    u8 padA[0x26];
    Cup *cup;
    u8 pad34[0x18];
    Pl pl[4];
    u8 pad8C[0x14E - 0x8C];
    u16 f14E[5];
    u16 f158;
    u16 f15A[5];
    u16 f164;
    u8 pad166[0xC90 - 0x166];
    u16 opp[18];
} Game;

extern Game D_8007EF30;
extern s32 D_80038AA8;
s32 func_8002B528(s32);
s32 func_800B0524(s32);
s32 func_8001C580(void);
void func_800B0654(void);

/* -1 if `id` is this cup's f14E entry, 1 if it is f158 in cup 2, else 0 (always 0 outside mode 0x8000). */
static inline s32 isCupBoss(s32 id) {
    u8 k;
    s32 r;
    if (!(D_8007EF30.mode & 0x8000)) {
        r = 0;
    } else {
        k = D_8007EF30.cup->id;
        if ((D_8007EF30.f14E[k] & 0xFFF) == id) {
            r = -1;
        } else {
            r = 0;
            if (k == 2) {
                if ((D_8007EF30.f158 & 0xFFF) == id) {
                    r = 1;
                }
            }
        }
    }
    return r;
}

/* The values are read before either store, as arguments. */
static inline void setLastPair(s32 a, s32 b) {
    D_8007EF30.opp[16] = a;
    D_8007EF30.opp[17] = b;
}

/* An inline rather than a plain store: the value must be read before the store's address is formed. */
static inline void setLast(s32 v) {
    D_8007EF30.opp[8] = v;
}

void func_800B0774(void) {
    s32 ids[0x40];
    u8 *list;
    s32 n;
    s32 i;
    s32 a, b, x, y, t;
    u8 c;

    list = D_8007EF30.cup->list;
    n = 0;
    if (D_8007EF30.cup->flags & 0x20) {
        if (isCupBoss(D_8007EF30.pl[0].id) && isCupBoss(D_8007EF30.pl[1].id)) {
            setLastPair(D_8007EF30.f15A[D_8007EF30.cup->id], D_8007EF30.f164);
        } else if (isCupBoss(D_8007EF30.pl[0].id) || isCupBoss(D_8007EF30.pl[1].id)) {
            func_800B0654();
        } else {
            setLastPair(D_8007EF30.f14E[D_8007EF30.cup->id], D_8007EF30.f158);
        }
        while ((c = *list) != 0) {
            a = func_8002B528(c);
            b = func_8002B528(list[1]);
            if (func_800B0524(a) && func_800B0524(b)) {
                ids[n] = a;
                ids[n + 1] = b;
                n += 2;
            }
            list += 2;
        }
        n /= 2;
        for (i = 0; i < n; i++) {
            x = func_8001C580() % n * 2;
            y = func_8001C580() % n * 2;
            t = ids[x];
            ids[x] = ids[y];
            ids[y] = t;
            t = ids[x + 1];
            ids[x + 1] = ids[y + 1];
            ids[y + 1] = t;
        }
        for (i = 0; i < 16; i++) {
            D_8007EF30.opp[i] = ids[i];
        }
    } else {
        if (isCupBoss(D_8007EF30.pl[0].id)) {
            setLast(D_8007EF30.f15A[D_8007EF30.cup->id]);
        } else {
            setLast(D_8007EF30.f14E[D_8007EF30.cup->id]);
        }
        i = 1;
        if (D_8007EF30.cup->flags & 0x2000) {
            while ((c = *list) != 0) {
                a = func_8002B528(c);
                if (func_800B0524(a)) {
                    ids[n] = a;
                    n++;
                }
                list++;
            }
        } else {
            for (; i < 0x40; i++) {
                a = func_8002B528(i);
                if (func_800B0524(a)) {
                    ids[n] = a;
                    n++;
                }
            }
        }
        for (i = 0; i < n; i++) {
            s32 j = func_8001C580() % n;
            s32 k = func_8001C580() % n;
            t = ids[j];
            ids[j] = ids[k];
            ids[k] = t;
        }
        for (i = 0; i < 8; i++) {
            D_8007EF30.opp[i] = ids[i];
        }
    }
    /* Empty loops, kept by the compiler (probably debug output compiled out). */
    if (D_8007EF30.cup->flags & 0x20) {
        for (i = 0; i < 18; i += 2) {
        }
    } else {
        for (i = 0; i < 9; i++) {
        }
    }
    D_80038AA8 = 0;
}
