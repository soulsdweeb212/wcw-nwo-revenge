/* @header
 * func_80097EF4
 * VRAM 0x80097EF4 | ROM 0x8B394 | size 0x3B8
 * asm: asm/nonmatchings/ovl2_80090000/func_80097EF4.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: the icon is common.h's Nw2HudIcon, as port_decls.h declares D_800EB1AC: the picture's pointer at +8 is 8 bytes,
 * so an icon is 0x10 bytes. */
typedef Nw2HudIcon Icon;
#else
typedef struct {
    s16 id;
    s16 scale;
    s16 x;
    s16 y;
    void *tex;
} Icon;
#endif

extern u32 D_8007E848; /* D_8007E228+0x620: present / winner bits */
extern u16 D_8007E280; /* D_8007E228+0x58 */
extern s32 D_8007E8C0[];
extern Icon D_800EB1AC;
extern u8 *D_800EB1B8;
extern s16 D_800EB1BE;
extern s16 D_800F9AFA;

s16 func_8000B3C4(s32);
u8 *func_80028B5C(u8 *, u8 *);
u8 *func_8002AD34(s32, s32);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_8002A2FC, whose key is as wide as a pointer (port.h's ResKey) */
void *func_8002A2FC(u32, u16);
#endif

/* wrestler name for slot i; D_8007E8C0[0x1C + i] is D_8007E8C0+0x70 */
#define NAME(i) func_8002AD34(func_8000B3C4(i), D_8007E8C0[0x1C + (i)])

/* Builds the match result text in D_800EB1B8. Own .rodata (strings) at 0x800E40E0. */
void func_80097EF4(s16 arg0) {
    s16 w;
    s16 l;
    s16 cnt;
    s16 who;
    u32 i;
    u8 *s;

    if (D_800EB1BE < 0) {
        D_800EB1BE = arg0;
        D_800F9AFA = 0;
        w = -1;
        l = -1;
        cnt = 0;
        for (i = 0; i < 4; i++) {
            if (D_8007E848 & (1 << i)) {
                w = i;
            } else if (D_8007E848 & (0x10 << i)) {
                l = i;
                if (D_8007E8C0[i] != 0) {
                    cnt++;
                }
            }
        }
        s = D_800EB1B8;
        if (D_8007E280 & 0x200) {
            if (D_8007E848 & 0x400) {
                s = func_80028B5C(s, "Win on a decision!\n\n#x");
                D_800EB1AC.y -= 30;
            }
            if (w >= 0) {
                if (w == 2 && D_8007E8C0[4] == 2) {
                    s = func_80028B5C(s, NAME(2));
                } else {
                    s = func_80028B5C(s, NAME((s16)(w & ~1)));
                    s = func_80028B5C(s, " &\n\n");
                    if (D_8007E848 & 0x400) {
                        s = func_80028B5C(s, "#x");
                    }
                    s = func_80028B5C(s, NAME((s16)(w | 1)));
                }
            }
            if (!(D_8007E848 & 0x400)) {
                if (w >= 0) {
                    if (w == 2 && D_8007E8C0[4] == 2) {
                        func_80028B5C(s, " Wins!");
                    } else {
                        func_80028B5C(s, " Win!");
                    }
                } else {
                    func_80028B5C(s, "Draw!");
                }
            } else {
                func_80028B5C(s, " ");
            }
        } else {
            if (w >= 0) {
                who = l;
                if (D_8007E8C0[w] != 0 || cnt != 1) {
                    who = w;
                }
                if (D_8007E848 & 0x400) {
                    if (who == w) {
                        s = func_80028B5C(s, "Win on a decision!\n\n#x");
                    } else {
                        s = func_80028B5C(s, "Lose on a decision!\n\n#x\0"); /* ROM .rodata has the extra NUL */
                    }
                }
                s = func_80028B5C(s, NAME(who));
            }
            if (!(D_8007E848 & 0x400)) {
                if (w >= 0) {
                    if (who == w) {
                        func_80028B5C(s, " Wins!");
                    } else {
                        func_80028B5C(s, " Loses!\0"); /* extra NUL as in the ROM */
                    }
                } else {
                    func_80028B5C(s, " Draw!");
                }
            } else {
                func_80028B5C(s, " ");
            }
        }
#ifdef TARGET_PC
        /* PC: the key is the text's address, whole (port.h's RES_KEY_NAME); a u32 would cut it in half. */
        D_800EB1AC.tex = func_8002A2FC(RES_KEY_NAME(D_800EB1B8), 0x8008);
#else
        D_800EB1AC.tex = func_8002A2FC((u32)D_800EB1B8, 0x8008);
#endif
        D_800EB1AC.id = 0;
    }
}
