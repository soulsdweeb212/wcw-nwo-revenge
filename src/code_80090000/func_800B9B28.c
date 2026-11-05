/* @header
 * func_800B9B28
 * VRAM 0x800B9B28 | ROM 0x66298 | size 0x248
 * asm: asm/nonmatchings/code_80090000/func_800B9B28.s
 */
#include "common.h"

typedef struct { u8 pad[0xA]; u8 ext[4]; u8 name[0x10]; u8 pad2[2]; u8 n[0x30]; } R;
extern R *D_800D2970;
extern u8 D_800D2974[];
extern u8 D_800D2B78, D_800D2B79;
extern s32 D_800DCF50[];
extern s32 D_800DCFBC, D_800DCFC4, D_800DCFC8, D_800DCFCC, D_800DCFD0;
s32 func_8000424C(void);
void func_80004290(void);
s32 func_800B947C(void);
void bzero(void *, s32);
s32 osPfsFreeBlocks(void *, void *);
s32 osPfsNumFiles(void *, s32 *, s32 *);
R *allocateHeap(s32);
s32 osPfsFileState(void *, s32, R *);

static inline u8 *conv(u8 *s, u8 *d, s32 n) {
    s32 j;
    for (j = 0; j < n; j++) {
        d[0] = D_800D2974[*s * 2];
        d[1] = D_800D2974[*s * 2 + 1];
        d += 2;
        s++;
    }
    return d;
}

s32 func_800B9B28(void) {
    R *p;
    s32 i, k;
    u8 *d;
    s32 pad[4];

    D_800DCFC4 = func_8000424C();
    D_800DCFBC = func_800B947C();
    func_80004290();
    if (D_800DCFBC != 0 && D_800DCFBC != 5) {
        D_800DCFCC = 0;
        return D_800DCFBC;
    }
    k = 0;
    D_800DCFC4 = func_8000424C();
    D_800DCFBC = osPfsFreeBlocks(D_800DCF50, &D_800DCFC8);
    D_800DCFBC = osPfsNumFiles(D_800DCF50, &D_800DCFD0, &D_800DCFCC);
    p = D_800D2970 = allocateHeap(D_800DCFCC * 0x50);
    for (i = 0; i < D_800DCFD0; i++) {
        if (osPfsFileState(D_800DCF50, i, p) == 0) {
            d = p->n;
            bzero(d, 0x30);
            d = conv(p->name, d, 0x10);
            if (p->ext[0]) {
                d[0] = D_800D2B78;
                d[1] = D_800D2B79;
                conv(p->ext, d + 2, 4);
            }
            p++;
            k++;
            if (k >= D_800DCFCC) {
                break;
            }
        }
    }
    func_80004290();
    return D_800DCFBC;
}
