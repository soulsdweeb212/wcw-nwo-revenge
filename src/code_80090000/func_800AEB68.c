/* @header
 * func_800AEB68
 * VRAM 0x800AEB68 | ROM 0x5B2D8 | size 0x3C0
 * asm: asm/nonmatchings/code_80090000/func_800AEB68.s
 */
#include "common.h"

typedef struct { s16 f0; s16 id; u8 pad4[0xC]; } Pl;
typedef struct {
    u8 pad0[8];
    u16 mode;
    u8 padA[0x42];
    Pl pl[4];
} Game;

extern Game D_8007EF30;
extern u16 D_8007FBC0[]; /* D_8007EF30 + 0xC90, the roster: its own symbol, or CSE derives it from the pl pointer */
extern s32 D_80038AA8;
extern u8 D_8003A560[];
extern u16 D_8003A4FC[][4];
s32 func_8002B528(s32);
s32 func_800B0EC4(s32);
s32 func_8002B668(s32, s32);
s32 func_8001C580(void);

void func_800AEB68(void) {
    Pl *p = D_8007EF30.pl;
    u16 buf[44]; /* 44: the frame also holds 4 slots for combine's USE insns of the four duplicated loop tests */
    s32 n, k, j, m, cnt, id, a, b;

    if (D_8007EF30.mode & 0x100) {
        for (n = 0; n < 4; n++) {
            D_8007FBC0[n] = p[n].id;
        }
        for (k = 0, cnt = 0x28; n < D_80038AA8; k++) {
            id = func_8002B528(D_8003A560[k]);
            if (func_800B0EC4(id) == 0) {
                do {
                    id = func_8002B528(D_8003A560[cnt]);
                    cnt++;
                    if (id != p[0].id && id != p[1].id && id != p[2].id && id != p[3].id) {
                        break;
                    }
                } while (1);
            } else if (id == p[0].id || id == p[1].id || id == p[2].id || id == p[3].id) {
                continue;
            }
            D_8007FBC0[n++] = id;
        }
    } else {
        for (n = 0, k = 0; n < 4; n++) {
            D_8007FBC0[n] = p[n].id;
        }
        n = 4;
        while (n < D_80038AA8) {
            for (j = 0, cnt = 0; j < D_8003A4FC[k][0]; j++) {
                id = func_8002B668(k, j);
                if (func_800B0EC4(id) && id != p[0].id && id != p[1].id && id != p[2].id && id != p[3].id) {
                    buf[cnt++] = id;
                }
            }
            for (j = 0; j < cnt; j++) {
                a = func_8001C580() % cnt;
                b = func_8001C580() % cnt;
                id = buf[a];
                buf[a] = buf[b];
                buf[b] = id;
            }
            for (j = 0; j < cnt; j++) {
                for (m = 0; m < n; m++) {
                    if (buf[j] == D_8007FBC0[m]) {
                        break;
                    }
                }
                if (m == n) {
                    D_8007FBC0[n++] = buf[j];
                    break;
                }
            }
            k++;
            k %= 9;
        }
    }
}
