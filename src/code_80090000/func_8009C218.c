/* @header
 * func_8009C218
 * VRAM 0x8009C218 | ROM 0x48988 | size 0x2A40
 * asm: asm/nonmatchings/code_80090000/func_8009C218.s
 */
#include "common.h"

/* Matches (dh.py 0; lk.py identical apart from the two jump-table address words). Started from m2c output,
 * with display-list stores collapsed into G(a, b).
 * Score it against the full 0x2A40 bytes at ROM 0x48988; the repo's .s only lists the first 8 bytes.
 * Own .rodata: jump tables of 17 entries at vram 0x800D60C0 (ROM 0x82830) and 20 at 0x800D6108 (ROM 0x82878);
 * doubles D_800D6158/6160/6168.
 * Placeholders kept only for codegen: `goto end14` in cases 11-14, the out-of-line `found:` block in case 8, and two
 * `do { } while (0)` blocks (cases 2/3 and 5) whose loop notes act as scheduling barriers. */

typedef struct {
    u16 unk0;
    u16 unk2;
    u16 unk4;
    u16 unk6;
    u16 unk8;
    u16 unkA;
    u32 unkC;
} Inner;
typedef struct {
    u8 pad0[0xDC];
    Inner *unkDC;
    s16 unkE0;
    s16 unkE2;
    u16 unkE4;
    s16 unkE6;
    u16 pad;
    u16 unkEA;
} Item;

extern u8 D_C95B8[], D_C95F0[], D_C9620[], D_C9840[], D_800C96D0[], D_800C9840[], D_800C9860[];
extern f64 D_800D6158, D_800D6160, D_800D6168;
extern s32 D_800DBD60;
extern s16 D_800E74D2;
extern s32 D_800E81F8;
s32 func_8001C580(void);
f32 cosf(f32);
f32 sinf(f32);
s32 func_800B600C(s32, s32);
s32 func_800B64EC(s32, s32);

typedef struct { u32 w0, w1; } Gx;
#define G(a, b) { Gx *_g = sp38++; _g->w0 = (u32)(a); _g->w1 = (u32)(b); }

void func_8009C218(Gx **arg0, Item *arg1, s32 arg2) {
    s32 rx;
    s32 ra;
    s32 rd;
    s16 *rp;
    s32 rs0;
    s32 rs1;
    s32 rs2;
    s32 rs3;
    s32 rs4;
    s32 rs5;
    s32 rs6;
    s32 rt4;
    s32 rt5;
    s32 rt6;
    s32 rt9;
    u8 *rt8;
    Gx *sp38;
    s32 sp4C;
    s32 sp54;
    s16 temp_a1_5;
    s32 temp_a0_12;
    s32 temp_a0_14;
    s32 temp_a0_15;
    s32 temp_a0_9;
    s32 temp_a1_13;
    s32 temp_a1_14;
    s32 temp_a1_3;
    s32 temp_a1_7;
    s32 temp_a1_8;
    s32 temp_a2_2;
    s32 temp_a2_3;
    s32 temp_a2_4;
    s32 temp_a2_8;
    s32 temp_a2_9;
    s32 temp_a3_4;
    s32 temp_v0_22;
    s32 temp_v0_23;
    s32 temp_v0_24;
    s32 temp_v0_26;
    s32 temp_v0_2;
    s32 temp_v0_32;
    s32 var_a0;
    s32 var_a1;
    s32 var_a3;
    s32 var_t2;
    s32 var_v0_6;
    s32 var_v0_7;
    s32 frame;
    s32 var_v1_3;
    s32 var_v1_4;
    s32 var_v1_5;
    u16 temp_v0_19;
    u16 temp_v1_4;
    u16 temp_v1_5;
    u32 temp_a0_4;
    u32 temp_a1_2;
    u32 temp_v0_17;
    u32 temp_v0_18;
    u32 temp_v0_28;
    u32 temp_v0_29;
    u32 temp_v0_5;
    u32 temp_v1_21;
    u32 temp_v1_22;
    u8 temp_a0_13;
    u8 temp_a1_12;
    u8 temp_v0_27;
    Inner *temp_a1;
    Inner *temp_v0_11;
    Inner *temp_v1;

    temp_a1 = arg1->unkDC;
    sp38 = *arg0;
    rs6 = temp_a1->unk6 - arg1->unkE6;
    sp4C = rs6;
    rs1 = ((u8 *)&temp_a1->unkA)[1];
    rx = 0;
    if (arg2 != 0) {
        switch (rs1) {                          /* switch 1 */
        case 20:
            func_8009B66C(&sp38, arg1);
            break;
        case 19:                                    /* switch 1 */
            G(0xFA000000, (((u8 *)&arg1->unkE6)[1] | ~0xFF));
            temp_v1 = arg1->unkDC;
            temp_a3_4 = temp_v1->unk8;
            temp_a1_2 = 0x1E0 - temp_a3_4;
            func_8009BBFC(&sp38, (s32) (temp_a1_2 + (temp_a1_2 >> 0x1F)) >> 1, temp_v1->unk6, temp_a3_4, (s32) temp_v1->unk4);
            break;
        case 4:                                     /* switch 1 */
            rp = &D_800E74D2;
            if (*rp != 0) {
                func_8009F800(&sp38, *rp, rp - 3);
            }
            break;
        case 16:                                    /* switch 1 */
        case 17:                                    /* switch 1 */
            rs0 = 0xFF;
            if (arg1->unkDC->unkA & 0x200) {
                rs0 = arg1->unkE6;
            }
            G(0xDE000000, &D_C9620);
            if (rs1 == 0x10) {
                func_80099748(&sp38, 0xFF, 0xFF, 0xFF, rs0);
            } else {
                func_80099748(&sp38, 0xFF, 0, 0, rs0);
            }
            break;
        }
    } else {
        switch (rs1) {                          /* switch 2 */
        case 9:                                     /* switch 2 */
        case 10:                                    /* switch 2 */
            if (arg1->unkEA != 0) {
                rs6 = func_800B600C(0x28U, 0);
                if (rs6 != NULL) {
                    G(0xDE000000, &D_C95F0);
                    G(0xDE000000, &D_C95B8);
                    G(0xE3001201, 0x2000);
                    func_80091244(&sp38);
                    G(0xFC309661, 0x552EFF7F);
                    if (rs1 == 9) {
                        u16 n = arg1->unkEA % 20;
                        G(0xFB000000, (((u8 *)&arg1->unkE6)[1] | 0xFF000000));
                        G(0xFA000000, (((u8 *)&arg1->unkE6)[1] | 0xFFFF0000));
                        var_t2 = func_800B64EC(rs6, n + 0xA);
                        rt4 = arg1->unkE4;
                        var_a1 = 0;
                        arg1->unkEA = (u16) (arg1->unkEA + 1);
                    } else {
                        G(0xFB000000, 0xFF);
                        G(0xFA000000, 0xFFFF00FF);
                        var_t2 = func_800B64EC(rs6, (arg1->unkEA & 7) + 0x1E);
                        temp_v1_4 = arg1->unkEA;
                        var_a1 = (temp_v1_4 >> 8) + 1;
                        temp_v1_5 = temp_v1_4 + 1;
                        arg1->unkEA = temp_v1_5;
                        rt4 = 0x100;
                        if ((temp_v1_5 & 0xF) == 8) {
                            arg1->unkEA = 0U;
                        }
                    }
                    G(0xFD500000, (var_t2 - 0x80000000));
                    G(0xF5500000, 0x07000000);
                    G(0xE6000000, 0);
                    G(0xF3000000, 0x073FF200);
                    G(0xE7000000, 0);
                    G(0xF5400800, 0);
                    G(0xF2000000, 0xFC0FC);
                    func_8009C010(&sp38, var_a1, rt4);
                    func_8009126C(&sp38);
                }
            }
            break;
        case 6:                                     /* switch 2 */
            G(0xDE000000, &D_C95F0);
            G(0xE3001201, 0x2000);
            func_80091244(&sp38);
            G(0xFB000000, 0xFFFF00FF);
            G(0xFA000000, -1);
            G(0xDE000000, &D_C95B8);
            temp_v0_2 = func_800B64EC(D_800E81F8, 1);
            G(0xFD500000, (temp_v0_2 - 0x80000000));
            G(0xF5500000, 0x07018060);
            G(0xE6000000, 0);
            G(0xF3000000, 0x073FF200);
            G(0xE7000000, 0);
            G(0xF5400800, 0x18060);
            G(0xF2000000, 0xFC0FC);
            G(0x02180000, 0xFE7000F0);
            G(0x02180002, 0x078000F0);
            G(0x02180004, 0xFE7003C0);
            G(0x02180006, 0x078003C0);
            G(0x02140000, 0);
            G(0x02140002, 0x08000000);
            G(0x02140004, 0x400);
            G(0x02140006, 0x08000400);
            G(0x07000206, 0x604);
            G(0x02180000, 0x04B000F0);
            G(0x02180002, 0x078000F0);
            G(0x02180004, 0x04B003C0);
            G(0x02180006, 0x078003C0);
            G(0x02140000, 0);
            G(0x02140002, 0x08000000);
            G(0x02140004, 0x400);
            G(0x02140006, 0x08000400);
            G(0x07000206, 0x604);
            func_8009126C(&sp38);
            break;
        case 1:                                     /* switch 2 */
            if (arg1->unkEA != 0) {
                emitReactionSprite99B68(&sp38, arg1);
            }
            break;
        case 18:                                    /* switch 2 */
            if (arg1->unkEA != 0) {
                func_8009A02C(&sp38, arg1);
            }
            break;
        case 15:                                    /* switch 2 */
            G(0xDE000000, &D_C95F0);
            G(0xDE000000, &D_C95B8);
            G(0x02100000, 0xFF0040);
            G(0x02100002, 0xCF7F40);
            G(0x02100004, 0x7FCF40);
            G(0x02100006, 0xFF40);
            rs6 = func_800B600C(0x36U, 0);
            if (rs6 != NULL) {
                func_80091244(&sp38);
                G(0xFC409681, 0x552EFF7F);
                G(0xFB000000, 0xFF);
                G(0xFA000000, -1);
                G(0xE3001201, 0x2000);
                G(0xE3001001, 0xC000);
                G(0xFD100000, &D_C9840);
                G(0xE8000000, 0);
                G(0xF5000100, 0x07000000);
                G(0xE6000000, 0);
                G(0xF0000000, 0x0703C000);
                G(0xE7000000, 0);
                G(0xFD500000, (rs6 - 0x80000000));
                G(0xF5500000, 0x07018000);
                G(0xE6000000, 0);
                G(0xF3000000, 0x073FF200);
                G(0xE7000000, 0);
                G(0xF5400800, 0x18000);
                G(0xF2000000, 0xFC0FC);
                rt4 = func_8001C580() % 32;
                rt5 = func_8001C580() % 32;
                G(0x02180000, 0);
                G(0x02180002, 0x07800000);
                G(0x02180004, 0x3C0);
                G(0x02180006, 0x078003C0);
                temp_a0_4 = (u32) (rt5 << 0x15) >> 0x10;
                temp_a2_2 = rt4 << 0x15;
                G(0x02140000, (temp_a0_4 | temp_a2_2));
                temp_a1_3 = (rt4 + 0x20) << 0x15;
                G(0x02140002, (temp_a0_4 | temp_a1_3));
                temp_v0_5 = (u32) ((rt5 + 0xF0) << 0x15) >> 0x10;
                G(0x02140004, (temp_v0_5 | temp_a2_2));
                G(0x02140006, (temp_v0_5 | temp_a1_3));
                G(0x07000206, 0x604);
                G(0xE3001001, 0x8000);
            }
            G(0xFCFFFFFF, 0xFFFE793C);
            G(0xE3001801, 0x80);
            G(0x02180000, 0);
            G(0x02180002, 0x07800000);
            G(0x02180004, 0x3C0);
            G(0x02180006, 0x078003C0);
            G(0x02140000, 0);
            G(0x02140002, 0x08000000);
            G(0x02140004, 0x800);
            G(0x02140006, 0x08000800);
            G(0x07000206, 0x604);
            arg1->unkEA = arg1->unkEA + 1;
            break;
        case 11:                                    /* switch 2 */
        case 12:                                    /* switch 2 */
        case 13:                                    /* switch 2 */
        case 14:                                    /* switch 2 */
            switch (rs1) {
            case 12:
            case 13:
                rs3 = (arg1->unkDC->unk8 * arg1->unkE4) / 256;
                rs4 = (arg1->unkDC->unk6 * arg1->unkE4) / 256;
                rt9 = (s32)D_800C9840;
                rs5 = (0x1E0 - rs3) / 2 + arg1->unkE0;
                rs2 = (0xF0 - rs4) / 2 + arg1->unkE2;
                if (rs1 == 0xD) {
                    G(0xFA000000, 0xFF0000FF);
                } else {
                    G(0xFA000000, -1);
                }
                break;
            case 14:
                sp54 = (s32) (((f64) cosf((f32) ((f64) ((((arg1->unkEA * 0x10) + 0x100) & 0x3FF) * 0x168) * D_800D6158)) * D_800D6160) + D_800D6160);
                rs3 = arg1->unkDC->unk8 * D_800D6168;
                rs4 = arg1->unkDC->unk4 * D_800D6168;
                rs5 = (0x1E0 - rs3) / 2 + func_8001C580() % 24 - 12;
                rs2 = (0xF0 - rs4) / 2 + func_8001C580() % 12 - 6;
                rt9 = (s32)D_800C9840;
                G(0xFA000000, -0xC1);
                break;
            default:
                rs2 = arg1->unkE2;
                rt9 = (s32)D_800C9860;
                rs3 = arg1->unkDC->unk8;
                rs4 = arg1->unkDC->unk4;
                rs5 = arg1->unkE0 + 0x14;
                G(0xFA000000, 0xFF);
                break;
            }
            rs6 = func_800B600C(arg1->unkDC->unk0, 0);
            if (rs6 != NULL) {
                G(0xDE000000, &D_C95F0);
                G(0xFC309661, 0x552EFF7F);
                G(0xFB000000, 0);
                G(0xE3001001, 0xC000);
                G(0xFD100000, (rt9 - 0x80000000));
                G(0xE8000000, 0);
                G(0xF5000100, 0x07000000);
                G(0xE6000000, 0);
                G(0xF0000000, 0x0703C000);
                G(0xE7000000, 0);
                buildTiledTextureDisplayList(&sp38, rs6, 0, rs5, (s32) rs2, (s32) arg1->unkDC->unk2, (s32) arg1->unkDC->unk4, rs3, rs4, (s32) arg1->unkDC->unk2);
                if (rs1 == 0xE) {
                    temp_v0_11 = arg1->unkDC;
                    rs3 = (s32) temp_v0_11->unk8;
                    rs5 = (s32) (0x1E0 - rs3) / 2;
                    rs4 = (s32) temp_v0_11->unk4;
                    rs2 = (0xF0 - rs4) / 2;
                    G(0xFA000000, -0x41);
                    func_8009773C(&sp38, rs6, 0, arg1->unkEA, rs5, (s32) rs2, (s32) arg1->unkDC->unk2, (s32) arg1->unkDC->unk4, rs3, rs4, (s32) arg1->unkDC->unk2, sp54, sp54, sp54);
                    if (arg1->unkEA != 0) {
                        arg1->unkEA++;
                        if (arg1->unkEA >= 0x20) {
                            arg1->unkEA = 0;
                        }
                    }
                }
            } else {
                rs2 = 0xF0;
                if (rs1 != 0xB) {
                    goto end14;
                }
            }
            if (rs1 == 0xB) {
                G(0xFA000000, 0xFF);
                func_8009BBFC(&sp38, rs5, rs2, rs3, rs4);
            }
end14:
            G(0xE3001001, 0x8000);
            break;
        case 20:                                    /* switch 2 */
            func_8009B66C(&sp38, arg1);
            break;
        case 2:                                     /* switch 2 */
        case 3:                                     /* switch 2 */
            if (arg1->unkEA != 0) {
                if (rs1 == 3) {
                    rd = D_800E81F8;
                    ra = 1;
                    rs5 = rx + 0x19;
                    rs2 = sp4C;
                    rs3 = 0xA0;
                    rs4 = 0x80;
                } else {
                    rd = D_800E81F8;
                    ra = 3;
                    rs5 = rx + 0xCF;
                    rs2 = sp4C;
                    rs3 = 0x90;
                    rs4 = 0x64;
                }
                rt9 = func_800B64EC(rd, ra);
                rt9 += 0x10;
                do { /* placeholder: keeps the unkEA load after rt9 += 0x10 */
                    if (arg1->unkEA == 0x10) {
                        func_8000DEE4(0x40B);
                    }
                } while (0);
                if ((u16) arg1->unkEA < 0x21U) {
                    G(0xDE000000, &D_C95F0);
                    rs0 = (0x20 - arg1->unkEA) * 8;
                    G(0xFA000000, rs0 & 0xFF);
                    G(0xFD100000, (rt9 - 0x80000000));
                    G(0xE8000000, 0);
                    G(0xF5000100, 0x07000000);
                    G(0xE6000000, 0);
                    G(0xF0000000, 0x073FC000);
                    G(0xE7000000, 0);
                    buildTiledTextureDisplayList(&sp38, rt9 + 0x200, 1, rs5, rs2, rs3, rs4, rs3, rs4, rs3);
                    arg1->unkEA = arg1->unkEA + 1;
                    break;
                }
            }
            break;
        case 4:                                     /* switch 2 */
            if (arg1->unkEA != 0) {
                rs6 = func_800B600C(0x28U, 0);
                if (rs6 != NULL) {
                    var_v0_6 = arg1->unkDC->unk6 * arg1->unkE4;
                    rx = arg1->unkE0;
                    if (var_v0_6 < 0) {
                        var_v0_6 += 0xFF;
                    }
                    temp_a1_5 = arg1->unkE2;
                    sp4C = (var_v0_6 >> 8) + temp_a1_5;
                    G(0xDE000000, &D_C95F0);
                    G(0xE3001201, 0x2000);
                    func_80091244(&sp38);
                    G(0xFB000000, 0xFF0000FF);
                    G(0xFA000000, 0xFFFF00FF);
                    if ((u16) arg1->unkEA >= 0x1EU) {
                        arg1->unkEA = 0xAU;
                    }
                    G(0xDE000000, &D_C95B8);
                    G(0xE7000000, NULL);
                    G(0xFD500000, (func_800B64EC(rs6, arg1->unkEA - 1) - 0x80000000));
                    G(0xF5500000, (u8 *)0x07000000);
                    G(0xE6000000, NULL);
                    G(0xF3000000, 0x073FF200);
                    G(0xE7000000, 0);
                    G(0xF5400800, 0);
                    G(0xF2000000, 0xFC0FC);
                    ra = arg1->unkE4;
                    var_v0_7 = ra * 0xC8;
                    var_v1_3 = var_v0_7;
                    if (var_v0_7 < 0) {
                        var_v1_3 = var_v0_7 + 0xFF;
                    }
                    var_a0 = ra * 0x11D;
                    rs3 = var_v1_3 >> 8;
                    rs4 = (rs3 * 0x140) / 480;
                    if (var_a0 < 0) {
                        var_a0 += 0xFF;
                    }
                    rs5 = rx + (var_a0 >> 8);
                    var_v0_7 = ra * 0x82;
                    if (var_v0_7 < 0) {
                        var_v0_7 += 0xFF;
                    }
                    rs2 = sp4C - (((var_v0_7 >> 8) * 0x140) / 480);
                    temp_v1_21 = (u32) (rs2 << 0x12) >> 0x10;
                    temp_a1_7 = rs5 << 0x12;
                    G(0x02180000, (temp_v1_21 | temp_a1_7));
                    temp_a0_9 = (rs5 + rs3) << 0x12;
                    G(0x02180002, (temp_v1_21 | temp_a0_9));
                    temp_v0_17 = (u32) ((rs2 + rs4) << 0x12) >> 0x10;
                    G(0x02180004, (temp_v0_17 | temp_a1_7));
                    G(0x02180006, (temp_v0_17 | temp_a0_9));
                    G(0x02140000, 0);
                    G(0x02140002, 0x08000000);
                    G(0x02140004, 0x800);
                    G(0x02140006, 0x08000800);
                    G(0x07000206, 0x604);
                    var_v1_4 = arg1->unkE4 * 0x84;
                    rs5 = rx + 1;
                    if (var_v1_4 < 0) {
                        var_v1_4 += 0xFF;
                    }
                    rs2 = sp4C - (((var_v1_4 >> 8) * 0x140) / 480);
                    temp_v1_22 = (u32) (rs2 << 0x12) >> 0x10;
                    temp_a2_3 = rs5 << 0x12;
                    G(0x02180000, (temp_v1_22 | temp_a2_3));
                    temp_a1_8 = (rs5 + rs3) << 0x12;
                    G(0x02180002, (temp_v1_22 | temp_a1_8));
                    temp_v0_18 = (u32) ((rs2 + rs4) << 0x12) >> 0x10;
                    temp_a2_4 = temp_v0_18 | temp_a2_3;
                    G(0x02180004, temp_a2_4);
                    G(0x02180006, (temp_v0_18 | temp_a1_8));
                    G(0x02140000, 0);
                    G(0x02140002, 0x08000000);
                    G(0x02140004, 0x800);
                    G(0x02140006, 0x08000800);
                    G(0x07000206, 0x604);
                    func_8009126C(&sp38);
                    arg1->unkEA = arg1->unkEA + 1;
                    break;
                }
            }
            break;
        case 5:                                     /* switch 2 */
            temp_v0_19 = arg1->unkEA;
            if (((temp_v0_19 == 0) | (temp_v0_19 >= 0x10U)) == 0) {
                rs6 = func_800B600C(0x28U, 0);
                if (rs6 != NULL) {
                    var_v1_5 = arg1->unkDC->unk6 * arg1->unkE4;
                    rx = arg1->unkE0;
                    if (var_v1_5 < 0) {
                        var_v1_5 += 0xFF;
                    }
                    var_a3 = arg1->unkEA;
                    sp4C = (var_v1_5 >> 8) + arg1->unkE2;
                    if (var_a3 >= 8U) {
                        frame = 7;
                        rs0 = (0x10 - var_a3) << 5;
                    } else {
                        frame = var_a3;
                        rs0 = 0xFF;
                    }
                    G(0xDE000000, &D_C95F0);
                    G(0xE3001201, 0x2000);
                    func_80091244(&sp38);
                    G(0xFA000000, (u8 *) ((rs0 & 0xFF) | 0xFFFF0000));
                    ra = arg1->unkE4;
                    var_v1_5 = ra * 0xC8;
                    do { /* placeholder: keeps rs5 = rx + var_a3 ahead of the /480 multiply */
                        var_a3 = var_v1_5 / 256;
                    } while (0);
                    rs5 = rx + var_a3;
                    rs2 = sp4C - var_a3 * 0x140 / 480;
                    rs3 = ra * 0x64 / 256;
                    var_v1_5 = ra * 0x12C;
                    rs4 = var_v1_5 / 256 * 0x140 / 480;
                    G(0xFB000000, -0x7F01);
                    G(0xFD500000, (func_800B64EC(rs6, frame + 0x1D) - 0x80000000));
                    G(0xF5500000, 0x07000000);
                    G(0xE6000000, 0);
                    G(0xF3000000, 0x073FF200);
                    G(0xE7000000, 0);
                    G(0xF5400800, 0);
                    G(0xF2000000, 0xFC0FC);
                    G(0x02180000, (u32)(rs2 << 0x12) >> 0x10 | rs5 << 0x12);
                    G(0x02180002, (u32)(rs2 << 0x12) >> 0x10 | (rs5 + rs3) << 0x12);
                    G(0x02180004, (u32)((rs2 + rs4) << 0x12) >> 0x10 | rs5 << 0x12);
                    G(0x02180006, (u32)((rs2 + rs4) << 0x12) >> 0x10 | (rs5 + rs3) << 0x12);
                    G(0x02140000, 0x08000000);
                    G(0x02140002, 0);
                    G(0x02140004, 0x08000800);
                    G(0x02140006, 0x800);
                    G(0x07000206, 0x604);
                    func_8009126C(&sp38);
                    arg1->unkEA = arg1->unkEA + 1;
                    break;
                }
            }
            break;
        case 7:                                     /* switch 2 */
            temp_v0_22 = func_800B64EC(D_800E81F8, 0);
            rt9 = temp_v0_22 + 0x10;
            rs6 = temp_v0_22 + 0x30;
            G(0xDE000000, &D_C9620);
            G(0xFD100000, (rt9 - 0x80000000));
            G(0xE8000000, 0);
            G(0xF5000100, 0x07000000);
            G(0xE6000000, 0);
            G(0xF0000000, 0x0703C000);
            G(0xE7000000, 0);
            G(0xFD500000, (rs6 - 0x80000000));
            G(0xF5500000, 0x07000060);
            G(0xE6000000, 0);
            G(0xF3000000, 0x073FF200);
            G(0xE7000000, 0);
            G(0xF5400800, 0x60);
            G(0xF2000000, 0xFC0FC);
            G(0xE4780100, 0);
            G(0xE1000000, ((arg1->unkEA & 0x3F) << 0x15));
            G(0xF1000000, 0x04000400);
            G(0xE47803C0, 0x2C0);
            G(0xE1000000, (((~arg1->unkEA & 0x3F) << 0x15) | 0x7E0));
            G(0xF1000000, 0x0400FC00);
            arg1->unkEA = (u16) (arg1->unkEA + 1);
            break;
        case 8:                                     /* switch 2 */
            temp_v0_23 = func_800B64EC(D_800E81F8, 0);
            rt9 = temp_v0_23 + 0x10;
            G(0xDE000000, &D_C95B8);
            G(0xDE000000, &D_C95F0);
            G(0xFCFFFFFF, 0xFFFCF87C);
            rs6 = temp_v0_23 + 0x30;
            if (!(arg1->unkEA & 0x100)) {
                G(0x02100000, 0);
                G(0x02100002, -1);
                G(0x02100004, 0);
                G(0x02100006, -1);
                G(0xFD100000, (rt9 - 0x80000000));
                G(0xE8000000, 0);
                G(0xF5000100, 0x07000000);
                G(0xE6000000, 0);
                G(0xF0000000, 0x0703C000);
                G(0xE7000000, 0);
                rt4 = ((arg1->unkEA * 2) - 0x3F) & 0x1FF;
                rs5 = ((rt4 - 0x40) * 0x1E0) / 320;
                G(0xFD500000, (rs6 - 0x80000000));
                G(0xF5500000, 0x07000070);
                G(0xE6000000, 0);
                G(0xF3000000, 0x073FF100);
                G(0xE7000000, 0);
                G(0xF5401000, 0x70);
                G(0xF2000000, 0x1FC07C);
                temp_a0_12 = rs5 << 0x12;
                G(0x02180000, (temp_a0_12 | 0x160));
                temp_v0_24 = (rs5 + 0x60) << 0x12;
                G(0x02180002, (temp_v0_24 | 0x160));
                G(0x02180004, (temp_a0_12 | 0x260));
                G(0x02180006, (temp_v0_24 | 0x260));
                temp_a2_9 = rt4 << 0x15;
                G(0x02140000, temp_a2_9);
                G(0x02140002, (rt4 + 0x40) << 0x15);
                G(0x02140004, temp_a2_9 | 0x400);
                G(0x02140006, ((rt4 + 0x40) << 0x15) | 0x400);
                temp_a3_4 = (rt4 + 0x40) & 0x7F;
                G(0x07000206, 0x604);
                G(0xFCFFFFFF, 0xFFFCF279);
                temp_v0_26 = func_800B64EC(D_800E81F8, 1);
                rt9 = temp_v0_26 + 0x10;
                rs6 = temp_v0_26 + 0x30;
                G(0xFD100000, (rt9 - 0x80000000));
                                G(0xE8000000, 0);
                G(0xF5000100, 0x07000000);
                G(0xE6000000, 0);
                G(0xF0000000, 0x0703C000);
                G(0xE7000000, 0);
                G(0xFD500000, (rs6 - 0x80000000));
                G(0xF5500000, 0x07000000);
                G(0xE6000000, 0);
                G(0xF3000000, 0x0703F800);
                G(0xE7000000, 0);
                G(0xF5400200, 0);
                G(0xF2000000, 0x3C03C);
                for (rt8 = D_800C96D0;; rt8 += 2) {
                    temp_v0_27 = rt8[0];
                    if (temp_v0_27 == temp_a3_4) {
                        goto found;
                    }
                    if ((s32) temp_v0_27 < temp_a3_4 && temp_a3_4 < (s32) rt8[2]) {
                        break;
                    }
                }
                if (temp_a3_4 < 0x58) {
                    D_800DBD60 = 0;
                } else {
                    if (0) {
found:
                        rt6 = rt8[1];
                        goto draw;
                    }
                    if ((D_800DBD60 == 0) & (rs5 < 0x1E0)) {
                        func_8000DEE4(0x40E);
                        D_800DBD60 = 1;
                    }
                }
                temp_a0_13 = rt8[0];
                temp_a1_12 = rt8[1];
                rt6 = temp_a1_12 + ((s32) ((rt8[3] - temp_a1_12) * (temp_a3_4 - temp_a0_13)) / (s32) (rt8[2] - temp_a0_13));
draw:
                temp_v0_28 = (u32) ((rt6 + 0x50) << 0x12) >> 0x10;
                temp_a1_13 = (rs5 + 0x54) << 0x12;
                G(0x02180000, (u8 *) (temp_v0_28 | temp_a1_13));
                temp_a0_14 = (rs5 + 0x6C) << 0x12;
                G(0x02180002, (u8 *) (temp_v0_28 | temp_a0_14));
                temp_v0_29 = (u32) ((rt6 + 0x60) << 0x12) >> 0x10;
                G(0x02180004, (temp_v0_29 | temp_a1_13));
                G(0x02180006, (temp_v0_29 | temp_a0_14));
                G(0x02140000, 0);
                G(0x02140002, 0x02000000);
                G(0x02140004, 0x200);
                G(0x02140006, 0x02000200);
                G(0x07000206, 0x604);
                arg1->unkEA = (u16) ((arg1->unkEA + 1) & 0xFF);
            } else {
                G(0x02100000, -1);
                G(0x02100002, -1);
                G(0x02100004, -1);
                G(0x02100006, -1);
                G(0xFD500000, (rs6 - 0x80000000));
                G(0xF5500000, 0x07000060);
                G(0xE6000000, 0);
                G(0xF3000000, 0x073FF100);
                G(0xE7000000, 0);
                G(0xF5401000, 0x60);
                G(0xF2000000, 0x1FC07C);
                temp_a2_8 = arg1->unkEA & 0x1F;
                G(0x02180000, 0x160);
                G(0x02180002, (temp_a2_8 << 0x16) | 0x160);
                G(0x02180004, 0x260);
                G(0x02180006, (temp_a2_8 << 0x16) | 0x260);
                G(0x02140000, 0);
                G(0x02140002, temp_a2_8 << 0x19);
                G(0x02140004, 0x400);
                G(0x02140006, (temp_a2_8 << 0x19) | 0x400);
                rs5 = temp_a2_8 * 0x10;
                G(0x07000206, 0x604);
                G(0xFCFFFFFF, 0xFFFCF279);
                temp_v0_32 = func_800B64EC(D_800E81F8, 1);
                rt9 = temp_v0_32 + 0x10;
                rs6 = temp_v0_32 + 0x30;
                                G(0xFD100000, (rt9 - 0x80000000));
                G(0xE8000000, 0);
                G(0xF5000100, 0x07000000);
                G(0xE6000000, 0);
                G(0xF0000000, 0x0703C000);
                G(0xE7000000, 0);
                G(0xFD500000, (rs6 - 0x80000000));
                G(0xF5500000, 0x07000000);
                G(0xE6000000, 0);
                G(0xF3000000, 0x0703F800);
                G(0xE7000000, 0);
                G(0xF5400200, 0);
                G(0xF2000000, 0x3C03C);
                temp_a1_14 = (rs5 - 8) << 0x12;
                G(0x02180000, (temp_a1_14 | 0x1C0));
                temp_a0_15 = (rs5 + 8) << 0x12;
                G(0x02180002, (temp_a0_15 | 0x1C0));
                G(0x02180004, (temp_a1_14 | 0x200));
                G(0x02180006, (temp_a0_15 | 0x200));
                G(0x02140000, 0);
                G(0x02140002, 0x02000000);
                G(0x02140004, 0x200);
                G(0x02140006, 0x02000200);
                G(0x07000206, 0x604);
                arg1->unkEA = arg1->unkEA + 1;
                if (arg1->unkEA >= 0x11F) {
                    arg1->unkEA = 0x11F;
                }
            }
            break;
        }
    }
    *arg0 = sp38;
}

