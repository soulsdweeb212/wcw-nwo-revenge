/* @header
 * func_800B0774
 * VRAM 0x800B0774 | ROM 0x5CEE4 | size 0x660
 * asm: asm/nonmatchings/code_80090000/func_800B0774.s
 */
#include "common.h"

#ifdef TARGET_PC
typedef Nw2Cup Cup; /* PC: common.h's layout of a cup, 0x18 bytes */
#else
typedef struct { u8 id; u8 pad1[5]; u16 flags; u8 pad8[8]; u8 *list; } Cup;
#endif
typedef struct { s16 f0; s16 id; u8 pad4[0xC]; } Pl;
typedef struct {
    u8 pad0[8];
    u16 mode;
    u8 padA[0x26];
#ifdef TARGET_PC
    u32 cup; /* PC: a handle (CUP below) */
#else
    Cup *cup;
#endif
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
#ifdef TARGET_PC
/* PC: D_8007EF30 keeps its N64 layout, so its +0x30, the current cup (common.h's Nw2Cup), holds a handle (port.h's
 * PTR_TO_SLOT); CUP is the cup's address. */
#define CUP ((Cup *)SLOT_TO_PTR(D_8007EF30.cup))
#endif
extern s32 D_80038AA8;
#ifdef TARGET_PC
/* PC: the type of func_8002B528's definition, which returns a u16: read as an s32, the PC result's upper bits would
 * be unset. */
u16 func_8002B528(s32);
#else
s32 func_8002B528(s32);
#endif
s32 func_800B0524(s32);
s32 guRandom(void);
void func_800B0654(void);

/* -1 if `id` is this cup's f14E entry, 1 if it is f158 in cup 2, else 0 (always 0 outside mode 0x8000). */
static inline s32 isCupBoss(s32 id) {
    u8 k;
    s32 r;
    if (!(D_8007EF30.mode & 0x8000)) {
        r = 0;
    } else {
#ifdef TARGET_PC
        k = CUP->id;
#else
        k = D_8007EF30.cup->id;
#endif
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

#ifdef TARGET_PC
    list = CUP->list;
#else
    list = D_8007EF30.cup->list;
#endif
    n = 0;
#ifdef TARGET_PC
    if (CUP->flags & 0x20) {
#else
    if (D_8007EF30.cup->flags & 0x20) {
#endif
        if (isCupBoss(D_8007EF30.pl[0].id) && isCupBoss(D_8007EF30.pl[1].id)) {
#ifdef TARGET_PC
            setLastPair(D_8007EF30.f15A[CUP->id], D_8007EF30.f164);
#else
            setLastPair(D_8007EF30.f15A[D_8007EF30.cup->id], D_8007EF30.f164);
#endif
        } else if (isCupBoss(D_8007EF30.pl[0].id) || isCupBoss(D_8007EF30.pl[1].id)) {
            func_800B0654();
        } else {
#ifdef TARGET_PC
            setLastPair(D_8007EF30.f14E[CUP->id], D_8007EF30.f158);
#else
            setLastPair(D_8007EF30.f14E[D_8007EF30.cup->id], D_8007EF30.f158);
#endif
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
            x = guRandom() % n * 2;
            y = guRandom() % n * 2;
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
#ifdef TARGET_PC
            setLast(D_8007EF30.f15A[CUP->id]);
#else
            setLast(D_8007EF30.f15A[D_8007EF30.cup->id]);
#endif
        } else {
#ifdef TARGET_PC
            setLast(D_8007EF30.f14E[CUP->id]);
#else
            setLast(D_8007EF30.f14E[D_8007EF30.cup->id]);
#endif
        }
        i = 1;
#ifdef TARGET_PC
        if (CUP->flags & 0x2000) {
#else
        if (D_8007EF30.cup->flags & 0x2000) {
#endif
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
            s32 j = guRandom() % n;
            s32 k = guRandom() % n;
            t = ids[j];
            ids[j] = ids[k];
            ids[k] = t;
        }
        for (i = 0; i < 8; i++) {
            D_8007EF30.opp[i] = ids[i];
        }
    }
    /* Empty loops, kept by the compiler (probably debug output compiled out). */
#ifdef TARGET_PC
    if (CUP->flags & 0x20) {
#else
    if (D_8007EF30.cup->flags & 0x20) {
#endif
        for (i = 0; i < 18; i += 2) {
        }
    } else {
        for (i = 0; i < 9; i++) {
        }
    }
    D_80038AA8 = 0;
}
