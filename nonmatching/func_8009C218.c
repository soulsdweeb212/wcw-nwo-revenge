/* Raw m2c output for func_8009C218 (0x2A40 bytes, ROM 0x48988), kept as the starting point. It does not compile yet.
 * Jump tables: 17 entries at vram 0x800D60C0 (ROM 0x82830) and 20 at 0x800D6108 (ROM 0x82878). */
? buildTiledTextureDisplayList(s32 **, void *, ?, s32, s32, s32, s32, s32, s32, s32); /* extern */
f32 cosf(f32, s32, void *);                         /* extern */
? emitReactionSprite99B68(s32 **, void *);          /* extern */
? func_8000DEE4(?, ?, ?, s32);                      /* extern */
s32 func_8001C580(s32, s32, ?, ?);                  /* extern */
? func_80091244(s32 **, s16, ?);                    /* extern */
? func_8009126C(s32 **, s32, s32, s32);             /* extern */
? func_8009773C(s32 **, void *, ?, u16, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32); /* extern */
? func_80099748(s32 **, ?, ?, ?);                   /* extern */
? func_8009A02C(s32 **, void *);                    /* extern */
? func_8009B66C(s32 **, void *);                    /* extern */
? func_8009BBFC(s32 **, s32, u16, u16, s32);        /* extern */
? func_8009C010(s32 **, s32, u16, ?);               /* extern */
? func_8009F800(s32 **, s16, s16 *);                /* extern */
void *func_800B600C(u16, ?, ?, ?);                  /* extern */
s32 func_800B64EC(void *, s32, s32 *, s32);         /* extern */
extern ? D_000C95B8;
extern ? D_000C95F0;
extern ? D_000C9620;
extern ? D_000C9840;
extern ? D_800C96D0;
extern ? D_800C9840;
extern ? D_800C9860;
extern f64 D_800D6158;
extern f64 D_800D6160;
extern f64 D_800D6168;
extern s32 D_800DBD60;
extern s16 D_800E74D2;
extern void *D_800E81F8;

void func_8009C218(s32 **arg0, void *arg1, s32 arg2) {
    s32 *sp38;
    s32 **sp44;
    s32 sp4C;
    s32 sp54;
    s32 sp5C;
    s32 sp64;
    s32 sp6C;
    s32 sp74;
    s32 sp7C;
    s32 sp84;
    s32 sp8C;
    s32 sp94;
    s32 sp9C;
    s32 spA4;
    s32 spAC;
    s32 spB4;
    s32 spBC;
    s32 spC4;
    s32 spCC;
    s32 spD4;
    s32 spDC;
    s32 spE4;
    s32 spE8;
    s32 spEC;
    ? *spF0;
    ? *spF4;
    s32 spFC;
    ? *temp_t9;
    ? *var_t8;
    ? *var_t9;
    s16 temp_a1_5;
    s16 temp_fp;
    s16 temp_fp_2;
    s16 var_s2;
    s32 *temp_a0_2;
    s32 *temp_a0_6;
    s32 *temp_a1_11;
    s32 *temp_a2;
    s32 *temp_fp_3;
    s32 *temp_s0;
    s32 *temp_s1_2;
    s32 *temp_t0;
    s32 *temp_v0_15;
    s32 *temp_v0_25;
    s32 *temp_v0_30;
    s32 *temp_v0_3;
    s32 *temp_v0_6;
    s32 *temp_v1_10;
    s32 *temp_v1_12;
    s32 *temp_v1_14;
    s32 *temp_v1_15;
    s32 *temp_v1_16;
    s32 *temp_v1_17;
    s32 *temp_v1_18;
    s32 *temp_v1_19;
    s32 *temp_v1_20;
    s32 *temp_v1_23;
    s32 *temp_v1_25;
    s32 *temp_v1_26;
    s32 *temp_v1_29;
    s32 *temp_v1_2;
    s32 *temp_v1_3;
    s32 *temp_v1_6;
    s32 *temp_v1_7;
    s32 *temp_v1_8;
    s32 *temp_v1_9;
    s32 *var_v1_2;
    s32 temp_a0;
    s32 temp_a0_11;
    s32 temp_a0_12;
    s32 temp_a0_14;
    s32 temp_a0_15;
    s32 temp_a0_3;
    s32 temp_a0_5;
    s32 temp_a0_9;
    s32 temp_a1_13;
    s32 temp_a1_14;
    s32 temp_a1_3;
    s32 temp_a1_7;
    s32 temp_a1_8;
    s32 temp_a2_10;
    s32 temp_a2_2;
    s32 temp_a2_3;
    s32 temp_a2_4;
    s32 temp_a2_5;
    s32 temp_a2_6;
    s32 temp_a2_7;
    s32 temp_a2_8;
    s32 temp_a2_9;
    s32 temp_a3_2;
    s32 temp_a3_3;
    s32 temp_a3_4;
    s32 temp_hi;
    s32 temp_ret;
    s32 temp_ret_2;
    s32 temp_s2;
    s32 temp_s2_2;
    s32 temp_s2_3;
    s32 temp_s3;
    s32 temp_s4;
    s32 temp_s5;
    s32 temp_s5_2;
    s32 temp_s5_3;
    s32 temp_s5_4;
    s32 temp_s5_5;
    s32 temp_s6;
    s32 temp_s6_2;
    s32 temp_s6_3;
    s32 temp_s6_4;
    s32 temp_t4;
    s32 temp_t4_2;
    s32 temp_t5;
    s32 temp_t9_2;
    s32 temp_t9_3;
    s32 temp_t9_4;
    s32 temp_t9_5;
    s32 temp_v0_16;
    s32 temp_v0_22;
    s32 temp_v0_23;
    s32 temp_v0_24;
    s32 temp_v0_26;
    s32 temp_v0_2;
    s32 temp_v0_31;
    s32 temp_v0_32;
    s32 temp_v0_7;
    s32 temp_v1_11;
    s32 temp_v1_24;
    s32 temp_v1_27;
    s32 temp_v1_28;
    s32 var_a0;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_a3;
    s32 var_s0;
    s32 var_s3;
    s32 var_s3_2;
    s32 var_s4;
    s32 var_s4_2;
    s32 var_s5;
    s32 var_s5_2;
    s32 var_t2;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_4;
    s32 var_v0_5;
    s32 var_v0_6;
    s32 var_v0_7;
    s32 var_v0_8;
    s32 var_v0_9;
    s32 var_v1;
    s32 var_v1_3;
    s32 var_v1_4;
    s32 var_v1_5;
    u16 temp_a0_10;
    u16 temp_a0_16;
    u16 temp_a0_7;
    u16 temp_a1_6;
    u16 temp_a1_9;
    u16 temp_a3;
    u16 temp_v0_12;
    u16 temp_v0_13;
    u16 temp_v0_19;
    u16 temp_v1_4;
    u16 temp_v1_5;
    u16 var_s4_3;
    u16 var_t4;
    u16 var_v0_3;
    u32 temp_a0_4;
    u32 temp_a1_10;
    u32 temp_a1_2;
    u32 temp_v0_17;
    u32 temp_v0_18;
    u32 temp_v0_21;
    u32 temp_v0_28;
    u32 temp_v0_29;
    u32 temp_v0_5;
    u32 temp_v0_8;
    u32 temp_v0_9;
    u32 temp_v1_21;
    u32 temp_v1_22;
    u8 temp_a0_13;
    u8 temp_a1_12;
    u8 temp_s1;
    u8 temp_v0_27;
    u8 var_t6;
    void *temp_a0_8;
    void *temp_a1;
    void *temp_a1_4;
    void *temp_v0;
    void *temp_v0_10;
    void *temp_v0_11;
    void *temp_v0_14;
    void *temp_v0_20;
    void *temp_v0_4;
    void *temp_v1;
    void *temp_v1_13;

    sp44 = arg0;
    temp_a1 = arg1->unkDC;
    sp38 = *arg0;
    temp_a0 = temp_a1->unk6 - arg1->unkE6;
    sp4C = temp_a0;
    temp_s1 = temp_a1->unkB;
    if (arg2 != 0) {
        switch (temp_s1) {                          /* switch 1 */
        case 19:                                    /* switch 1 */
            temp_a0_2 = sp38;
            sp38 = temp_a0_2 + 8;
            temp_a0_2->unk0 = 0xFA000000;
            temp_a0_2->unk4 = (s32) (arg1->unkE7 | ~0xFF);
            temp_v1 = arg1->unkDC;
            temp_a3 = temp_v1->unk8;
            temp_a1_2 = 0x1E0 - temp_a3;
            func_8009BBFC(&sp38, (s32) (temp_a1_2 + (temp_a1_2 >> 0x1F)) >> 1, temp_v1->unk6, temp_a3, (s32) temp_v1->unk4);
            break;
        case 4:                                     /* switch 1 */
            if (D_800E74D2 != 0) {
                func_8009F800(&sp38, D_800E74D2, &D_800E74D2 - 6);
            }
            break;
        case 16:                                    /* switch 1 */
        case 17:                                    /* switch 1 */
            if (arg1->unkDC->unkA & 0x200) {

            }
            temp_v1_2 = sp38;
            sp38 = temp_v1_2 + 8;
            temp_v1_2->unk0 = 0xDE000000;
            temp_v1_2->unk4 = &D_000C9620;
            if (temp_s1 == 0x10) {
                func_80099748(&sp38, 0xFF, 0xFF, 0xFF);
            } else {
                func_80099748(&sp38, 0xFF, 0, 0);
            }
            break;
        }
    } else {
        switch (temp_s1) {                          /* switch 2 */
        case 9:                                     /* switch 2 */
        case 10:                                    /* switch 2 */
            if (arg1->unkEA != 0) {
                temp_v0 = func_800B600C(0x28U, 0);
                if (temp_v0 != NULL) {
                    temp_v1_3 = sp38;
                    sp38 = temp_v1_3 + 8;
                    temp_v1_3->unk4 = &D_000C95F0;
                    temp_v1_3->unk0 = 0xDE000000;
                    sp38 = temp_v1_3 + 0x10;
                    temp_v1_3->unkC = &D_000C95B8;
                    temp_v1_3->unk8 = 0xDE000000;
                    sp38 = temp_v1_3 + 0x18;
                    temp_v1_3->unk10 = 0xE3001201;
                    temp_v1_3->unk14 = 0x2000;
                    func_80091244(&sp38, 0xDE000000, 0xE3001201);
                    temp_a2 = sp38;
                    sp38 = temp_a2 + 8;
                    temp_a2->unk0 = 0xFC309661;
                    temp_a2->unk4 = 0x552EFF7F;
                    if (temp_s1 == 9) {
                        sp38 = temp_a2 + 0x10;
                        temp_a2->unk8 = 0xFB000000;
                        sp38 = temp_a2 + 0x18;
                        temp_a2->unk10 = 0xFA000000;
                        temp_a2->unkC = (s32) (arg1->unkE7 | 0xFF000000);
                        temp_a2->unk14 = (s32) (arg1->unkE7 | 0xFFFF0000);
                        var_t2 = func_800B64EC(temp_v0, ((arg1->unkEA % 20) & 0xFFFF) + 0xA, temp_a2);
                        var_t4 = arg1->unkE4;
                        var_a1 = 0;
                        arg1->unkEA = (u16) (arg1->unkEA + 1);
                    } else {
                        temp_a2->unk8 = 0xFB000000;
                        temp_a2->unkC = 0xFF;
                        temp_a2->unk10 = 0xFA000000;
                        temp_a2->unk14 = 0xFFFF00FF;
                        sp38 = temp_a2 + 0x10;
                        sp38 = temp_a2 + 0x18;
                        temp_v1_4 = arg1->unkEA;
                        var_t2 = func_800B64EC(temp_v0, (arg1->unkEA & 7) + 0x1E, temp_a2);
                        var_a1 = (temp_v1_4 >> 8) + 1;
                        temp_v1_5 = temp_v1_4 + 1;
                        arg1->unkEA = temp_v1_5;
                        var_t4 = 0x100;
                        if ((temp_v1_5 & 0xF) == 8) {
                            arg1->unkEA = 0U;
                        }
                    }
                    temp_v1_6 = sp38;
                    sp38 = temp_v1_6 + 8;
                    temp_v1_6->unk0 = 0xFD500000;
                    temp_v1_6->unk4 = (s32) (var_t2 - 0x80000000);
                    sp38 = temp_v1_6 + 0x10;
                    temp_v1_6->unk8 = 0xF5500000;
                    temp_v1_6->unkC = 0x07000000;
                    sp38 = temp_v1_6 + 0x18;
                    temp_v1_6->unk10 = 0xE6000000;
                    temp_v1_6->unk14 = 0;
                    sp38 = temp_v1_6 + 0x20;
                    temp_v1_6->unk18 = 0xF3000000;
                    temp_v1_6->unk1C = 0x073FF200;
                    sp38 = temp_v1_6 + 0x28;
                    temp_v1_6->unk20 = 0xE7000000;
                    temp_v1_6->unk24 = 0;
                    sp38 = temp_v1_6 + 0x30;
                    temp_v1_6->unk28 = 0xF5400800;
                    temp_v1_6->unk2C = 0;
                    sp38 = temp_v1_6 + 0x38;
                    temp_v1_6->unk30 = 0xF2000000;
                    temp_v1_6->unk34 = 0xFC0FC;
                    func_8009C010(&sp38, var_a1, var_t4, 0x073FF200);
                    func_8009126C(&sp38);
                }
            }
            break;
        case 6:                                     /* switch 2 */
            temp_v1_7 = sp38;
            sp38 = temp_v1_7 + 8;
            temp_v1_7->unk4 = &D_000C95F0;
            temp_v1_7->unk0 = 0xDE000000;
            sp38 = temp_v1_7 + 0x10;
            temp_v1_7->unk8 = 0xE3001201;
            temp_v1_7->unkC = 0x2000;
            func_80091244(&sp38, 0xE3001201);
            temp_v1_8 = sp38;
            sp38 = temp_v1_8 + 8;
            temp_v1_8->unk0 = 0xFB000000;
            temp_v1_8->unk4 = 0xFFFF00FF;
            sp38 = temp_v1_8 + 0x10;
            temp_v1_8->unk8 = 0xFA000000;
            temp_v1_8->unkC = -1;
            sp38 = temp_v1_8 + 0x18;
            temp_v1_8->unk10 = 0xDE000000;
            temp_v1_8->unk14 = &D_000C95B8;
            temp_v0_2 = func_800B64EC(D_800E81F8, 1, (s32 *)0xFFFF00FF);
            temp_v1_9 = sp38;
            spFC = 0x02180002;
            sp5C = 0x02140006;
            sp64 = 0x07000206;
            sp6C = 0x04B000F0;
            sp74 = 0x04B003C0;
            sp38 = temp_v1_9 + 8;
            temp_v1_9->unk0 = 0xFD500000;
            temp_v1_9->unk4 = (s32) (temp_v0_2 - 0x80000000);
            sp38 = temp_v1_9 + 0x10;
            temp_v1_9->unk8 = 0xF5500000;
            temp_v1_9->unkC = 0x07018060;
            sp38 = temp_v1_9 + 0x18;
            temp_v1_9->unk10 = 0xE6000000;
            temp_v1_9->unk14 = 0;
            sp38 = temp_v1_9 + 0x20;
            temp_v1_9->unk18 = 0xF3000000;
            temp_v1_9->unk1C = 0x073FF200;
            sp38 = temp_v1_9 + 0x28;
            temp_v1_9->unk20 = 0xE7000000;
            temp_v1_9->unk24 = 0;
            sp38 = temp_v1_9 + 0x30;
            temp_v1_9->unk28 = 0xF5400800;
            temp_v1_9->unk2C = 0x18060;
            sp38 = temp_v1_9 + 0x38;
            temp_v1_9->unk30 = 0xF2000000;
            temp_v1_9->unk34 = 0xFC0FC;
            sp38 = temp_v1_9 + 0x40;
            temp_v1_9->unk38 = 0x02180000;
            temp_v1_9->unk3C = 0xFE7000F0;
            sp38 = temp_v1_9 + 0x48;
            temp_v1_9->unk40 = 0x02180002;
            temp_v1_9->unk44 = 0x078000F0;
            sp38 = temp_v1_9 + 0x50;
            temp_v1_9->unk48 = 0x02180004;
            temp_v1_9->unk4C = 0xFE7003C0;
            sp38 = temp_v1_9 + 0x58;
            temp_v1_9->unk50 = 0x02180006;
            temp_v1_9->unk54 = 0x078003C0;
            sp38 = temp_v1_9 + 0x60;
            temp_v1_9->unk58 = 0x02140000;
            temp_v1_9->unk5C = 0;
            sp38 = temp_v1_9 + 0x68;
            temp_v1_9->unk60 = 0x02140002;
            temp_v1_9->unk64 = 0x08000000;
            sp38 = temp_v1_9 + 0x70;
            temp_v1_9->unk68 = 0x02140004;
            temp_v1_9->unk6C = 0x400;
            sp38 = temp_v1_9 + 0x78;
            temp_v1_9->unk74 = 0x08000400;
            temp_v1_9->unk70 = 0x02140006;
            sp38 = temp_v1_9 + 0x80;
            temp_v1_9->unk7C = 0x604;
            temp_v1_9->unk78 = 0x07000206;
            sp38 = temp_v1_9 + 0x88;
            temp_v1_9->unk80 = 0x02180000;
            temp_v1_9->unk84 = 0x04B000F0;
            sp38 = temp_v1_9 + 0x90;
            temp_v1_9->unk88 = 0x02180002;
            temp_v1_9->unk8C = 0x078000F0;
            sp38 = temp_v1_9 + 0x98;
            temp_v1_9->unk90 = 0x02180004;
            temp_v1_9->unk94 = 0x04B003C0;
            sp38 = temp_v1_9 + 0xA0;
            temp_v1_9->unk98 = 0x02180006;
            temp_v1_9->unk9C = 0x078003C0;
            sp38 = temp_v1_9 + 0xA8;
            temp_v1_9->unkA0 = 0x02140000;
            temp_v1_9->unkA4 = 0;
            sp38 = temp_v1_9 + 0xB0;
            temp_v1_9->unkA8 = 0x02140002;
            temp_v1_9->unkAC = 0x08000000;
            sp38 = temp_v1_9 + 0xB8;
            temp_v1_9->unkB0 = 0x02140004;
            temp_v1_9->unkB4 = 0x400;
            sp38 = temp_v1_9 + 0xC0;
            temp_v1_9->unkB8 = 0x02140006;
            temp_v1_9->unkBC = 0x08000400;
            sp38 = temp_v1_9 + 0xC8;
            temp_v1_9->unkC0 = 0x07000206;
            temp_v1_9->unkC4 = 0x604;
            func_8009126C(&sp38, 0x604, 0x400, 0x08000000);
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
            temp_v0_3 = sp38;
            sp38 = temp_v0_3 + 8;
            temp_v0_3->unk4 = &D_000C95F0;
            temp_v0_3->unk0 = 0xDE000000;
            sp38 = temp_v0_3 + 0x10;
            temp_v0_3->unkC = &D_000C95B8;
            temp_v0_3->unk8 = 0xDE000000;
            sp38 = temp_v0_3 + 0x18;
            temp_v0_3->unk10 = 0x02100000;
            temp_v0_3->unk14 = 0xFF0040;
            sp38 = temp_v0_3 + 0x20;
            temp_v0_3->unk18 = 0x02100002;
            temp_v0_3->unk1C = 0xCF7F40;
            sp38 = temp_v0_3 + 0x28;
            temp_v0_3->unk20 = 0x02100004;
            temp_v0_3->unk24 = 0x7FCF40;
            sp38 = temp_v0_3 + 0x30;
            temp_v0_3->unk28 = 0x02100006;
            temp_v0_3->unk2C = 0xFF40;
            temp_v0_4 = func_800B600C(0x36U, 0, 0xDE000000, 0xFF0040);
            if (temp_v0_4 != NULL) {
                func_80091244(&sp38, 0xFCFF0000);
                temp_v1_10 = sp38;
                sp38 = temp_v1_10 + 8;
                temp_v1_10->unk0 = 0xFC409681;
                temp_v1_10->unk4 = 0x552EFF7F;
                sp38 = temp_v1_10 + 0x10;
                temp_v1_10->unk8 = 0xFB000000;
                temp_v1_10->unkC = 0xFF;
                sp38 = temp_v1_10 + 0x18;
                temp_v1_10->unk10 = 0xFA000000;
                temp_v1_10->unk14 = -1;
                sp38 = temp_v1_10 + 0x20;
                temp_v1_10->unk1C = 0x2000;
                temp_v1_10->unk18 = 0xE3001201;
                sp38 = temp_v1_10 + 0x28;
                temp_v1_10->unk24 = 0xC000;
                temp_v1_10->unk20 = 0xE3001001;
                sp38 = temp_v1_10 + 0x30;
                temp_v1_10->unk28 = 0xFD100000;
                temp_v1_10->unk2C = &D_000C9840;
                sp38 = temp_v1_10 + 0x38;
                temp_v1_10->unk30 = 0xE8000000;
                temp_v1_10->unk34 = 0;
                sp38 = temp_v1_10 + 0x40;
                temp_v1_10->unk3C = 0x07000000;
                temp_v1_10->unk38 = 0xF5000100;
                sp38 = temp_v1_10 + 0x48;
                temp_v1_10->unk40 = 0xE6000000;
                temp_v1_10->unk44 = 0;
                sp38 = temp_v1_10 + 0x50;
                temp_v1_10->unk48 = 0xF0000000;
                temp_v1_10->unk4C = 0x0703C000;
                sp38 = temp_v1_10 + 0x58;
                temp_v1_10->unk50 = 0xE7000000;
                temp_v1_10->unk54 = 0;
                sp38 = temp_v1_10 + 0x60;
                temp_v1_10->unk58 = 0xFD500000;
                temp_v1_10->unk5C = (s32) (temp_v0_4 - 0x80000000);
                sp38 = temp_v1_10 + 0x68;
                temp_v1_10->unk60 = 0xF5500000;
                temp_v1_10->unk64 = 0x07018000;
                sp38 = temp_v1_10 + 0x70;
                temp_v1_10->unk68 = 0xE6000000;
                temp_v1_10->unk6C = 0;
                sp38 = temp_v1_10 + 0x78;
                temp_v1_10->unk70 = 0xF3000000;
                temp_v1_10->unk74 = 0x073FF200;
                sp38 = temp_v1_10 + 0x80;
                temp_v1_10->unk78 = 0xE7000000;
                temp_v1_10->unk7C = 0;
                sp38 = temp_v1_10 + 0x88;
                temp_v1_10->unk80 = 0xF5400800;
                temp_v1_10->unk84 = 0x18000;
                sp38 = temp_v1_10 + 0x90;
                temp_v1_10->unk88 = 0xF2000000;
                temp_v1_10->unk8C = 0xFC0FC;
                var_v0 = func_8001C580(0xE7000000, 0xE6000000, 0xE3001201, 0xF5000100);
                temp_a0_3 = var_v0;
                if (temp_a0_3 < 0) {
                    var_v0 = temp_a0_3 + 0x1F;
                }
                temp_t4 = temp_a0_3 - ((var_v0 >> 5) << 5);
                spEC = temp_t4;
                var_v0_2 = func_8001C580(temp_a0_3);
                temp_v1_11 = var_v0_2;
                if (temp_v1_11 < 0) {
                    var_v0_2 = temp_v1_11 + 0x1F;
                }
                temp_t5 = temp_v1_11 - ((var_v0_2 >> 5) << 5);
                temp_v1_12 = sp38;
                sp38 = temp_v1_12 + 8;
                temp_v1_12->unk0 = 0x02180000;
                temp_v1_12->unk4 = 0;
                sp38 = temp_v1_12 + 0x10;
                temp_v1_12->unkC = 0x07800000;
                temp_v1_12->unk8 = 0x02180002;
                sp38 = temp_v1_12 + 0x18;
                temp_v1_12->unk14 = 0x3C0;
                temp_v1_12->unk10 = 0x02180004;
                sp38 = temp_v1_12 + 0x20;
                temp_v1_12->unk18 = 0x02180006;
                temp_v1_12->unk1C = 0x078003C0;
                sp38 = temp_v1_12 + 0x28;
                temp_a0_4 = (u32) (temp_t5 << 0x15) >> 0x10;
                temp_a2_2 = temp_t4 << 0x15;
                temp_v1_12->unk20 = 0x02140000;
                temp_v1_12->unk24 = (s32) (temp_a0_4 | temp_a2_2);
                temp_a1_3 = (temp_t4 + 0x20) << 0x15;
                sp38 = temp_v1_12 + 0x30;
                temp_v1_12->unk28 = 0x02140002;
                temp_v1_12->unk2C = (s32) (temp_a0_4 | temp_a1_3);
                sp38 = temp_v1_12 + 0x38;
                temp_v0_5 = (u32) ((temp_t5 + 0xF0) << 0x15) >> 0x10;
                temp_v1_12->unk30 = 0x02140004;
                temp_v1_12->unk34 = (s32) (temp_v0_5 | temp_a2_2);
                sp38 = temp_v1_12 + 0x40;
                temp_v1_12->unk3C = (s32) (temp_v0_5 | temp_a1_3);
                temp_v1_12->unk38 = 0x02140006;
                sp38 = temp_v1_12 + 0x48;
                temp_v1_12->unk44 = 0x604;
                temp_v1_12->unk40 = 0x07000206;
                sp38 = temp_v1_12 + 0x50;
                temp_v1_12->unk48 = 0xE3001001;
                temp_v1_12->unk4C = 0x8000;
            }
            temp_v0_6 = sp38;
            sp38 = temp_v0_6 + 8;
            temp_v0_6->unk0 = 0xFCFFFFFF;
            temp_v0_6->unk4 = 0xFFFE793C;
            sp38 = temp_v0_6 + 0x10;
            temp_v0_6->unkC = 0x80;
            temp_v0_6->unk8 = 0xE3001801;
            sp38 = temp_v0_6 + 0x18;
            temp_v0_6->unk10 = 0x02180000;
            temp_v0_6->unk14 = 0;
            sp38 = temp_v0_6 + 0x20;
            temp_v0_6->unk1C = 0x07800000;
            temp_v0_6->unk18 = 0x02180002;
            sp38 = temp_v0_6 + 0x28;
            temp_v0_6->unk24 = 0x3C0;
            temp_v0_6->unk20 = 0x02180004;
            sp38 = temp_v0_6 + 0x30;
            temp_v0_6->unk28 = 0x02180006;
            temp_v0_6->unk2C = 0x078003C0;
            sp38 = temp_v0_6 + 0x38;
            temp_v0_6->unk30 = 0x02140000;
            temp_v0_6->unk34 = 0;
            sp38 = temp_v0_6 + 0x40;
            temp_v0_6->unk3C = 0x08000000;
            temp_v0_6->unk38 = 0x02140002;
            sp38 = temp_v0_6 + 0x48;
            temp_v0_6->unk44 = 0x800;
            temp_v0_6->unk40 = 0x02140004;
            sp38 = temp_v0_6 + 0x50;
            temp_v0_6->unk48 = 0x02140006;
            temp_v0_6->unk4C = 0x08000800;
            sp38 = temp_v0_6 + 0x58;
            temp_v0_6->unk50 = 0x07000206;
            temp_v0_6->unk54 = 0x604;
            var_v0_3 = arg1->unkEA + 1;
block_113:
            arg1->unkEA = var_v0_3;
            break;
        case 11:                                    /* switch 2 */
        case 12:                                    /* switch 2 */
        case 13:                                    /* switch 2 */
        case 14:                                    /* switch 2 */
            if ((s32) temp_s1 >= 0xC) {
                if ((s32) temp_s1 >= 0xE) {
                    if (temp_s1 != 0xE) {
                        goto block_44;
                    }
                    temp_v1_13 = arg1->unkDC;
                    var_s3 = (s32) ((f64) temp_v1_13->unk8 * D_800D6168);
                    var_s4 = (s32) ((f64) temp_v1_13->unk4 * D_800D6168);
                    sp54 = (s32) (((f64) cosf((f32) ((f64) ((((arg1->unkEA * 0x10) + 0x100) & 0x3FF) * 0x168) * D_800D6158), temp_a0, temp_a1) * D_800D6160) + D_800D6160);
                    temp_ret = func_8001C580();
                    temp_a0_5 = ((s32) (0x1E0 - var_s3) / 2) + (temp_ret % 24);
                    var_s5 = temp_a0_5 - 0xC;
                    temp_ret_2 = func_8001C580(temp_a0_5, temp_ret / 24);
                    temp_v0_7 = temp_ret_2;
                    temp_a0_6 = sp38;
                    var_t9 = &D_800C9840;
                    temp_hi = temp_ret_2 / 6;
                    sp38 = temp_a0_6 + 8;
                    temp_a0_6->unk0 = 0xFA000000;
                    temp_a0_6->unk4 = -0xC1;
                    var_s2 = (((s32) (0xF0 - var_s4) / 2) + (temp_v0_7 - (((temp_hi >> 1) - (temp_v0_7 >> 0x1F)) * 0xC))) - 6;
                } else {
                    temp_a1_4 = arg1->unkDC;
                    temp_a0_7 = arg1->unkE4;
                    var_v1 = temp_a1_4->unk8 * temp_a0_7;
                    if (var_v1 < 0) {
                        var_v1 += 0xFF;
                    }
                    var_v0_4 = temp_a1_4->unk6 * temp_a0_7;
                    var_s3 = var_v1 >> 8;
                    if (var_v0_4 < 0) {
                        var_v0_4 += 0xFF;
                    }
                    var_s4 = var_v0_4 >> 8;
                    var_t9 = &D_800C9840;
                    temp_v0_8 = 0x1E0 - var_s3;
                    var_s5 = ((s32) (temp_v0_8 + (temp_v0_8 >> 0x1F)) >> 1) + arg1->unkE0;
                    temp_v0_9 = 0xF0 - var_s4;
                    var_s2 = ((s32) (temp_v0_9 + (temp_v0_9 >> 0x1F)) >> 1) + arg1->unkE2;
                    if (temp_s1 == 0xD) {
                        temp_v1_14 = sp38;
                        sp38 = temp_v1_14 + 8;
                        temp_v1_14->unk0 = 0xFA000000;
                        temp_v1_14->unk4 = 0xFF0000FF;
                    } else {
                        var_v1_2 = sp38;
                        sp38 = var_v1_2 + 8;
                        var_v1_2->unk0 = 0xFA000000;
                        var_v0_5 = -1;
                        goto block_45;
                    }
                }
            } else {
block_44:
                temp_a0_8 = arg1->unkDC;
                var_s2 = arg1->unkE2;
                var_t9 = &D_800C9860;
                var_v1_2 = sp38;
                var_s3 = (s32) temp_a0_8->unk8;
                var_s4 = (s32) temp_a0_8->unk4;
                var_s5 = arg1->unkE0 + 0x14;
                sp38 = var_v1_2 + 8;
                var_v1_2->unk0 = 0xFA000000;
                var_v0_5 = 0xFF;
block_45:
                var_v1_2->unk4 = var_v0_5;
            }
            spF4 = var_t9;
            temp_v0_10 = func_800B600C(arg1->unkDC->unk0, 0);
            if (temp_v0_10 != NULL) {
                temp_v1_15 = sp38;
                sp38 = temp_v1_15 + 8;
                temp_v1_15->unk0 = 0xDE000000;
                temp_v1_15->unk4 = &D_000C95F0;
                sp38 = temp_v1_15 + 0x10;
                temp_v1_15->unk8 = 0xFC309661;
                temp_v1_15->unkC = 0x552EFF7F;
                sp38 = temp_v1_15 + 0x18;
                temp_v1_15->unk10 = 0xFB000000;
                temp_v1_15->unk14 = 0;
                sp38 = temp_v1_15 + 0x20;
                temp_v1_15->unk1C = 0xC000;
                temp_v1_15->unk18 = 0xE3001001;
                sp38 = temp_v1_15 + 0x28;
                temp_v1_15->unk20 = 0xFD100000;
                temp_v1_15->unk24 = (s32) (var_t9 - 0x80000000);
                sp38 = temp_v1_15 + 0x30;
                temp_v1_15->unk28 = 0xE8000000;
                temp_v1_15->unk2C = 0;
                sp38 = temp_v1_15 + 0x38;
                temp_v1_15->unk34 = 0x07000000;
                temp_v1_15->unk30 = 0xF5000100;
                sp38 = temp_v1_15 + 0x40;
                temp_v1_15->unk38 = 0xE6000000;
                temp_v1_15->unk3C = 0;
                sp38 = temp_v1_15 + 0x48;
                temp_v1_15->unk40 = 0xF0000000;
                temp_v1_15->unk44 = 0x0703C000;
                sp38 = temp_v1_15 + 0x50;
                temp_v1_15->unk48 = 0xE7000000;
                temp_v1_15->unk4C = 0;
                buildTiledTextureDisplayList(&sp38, temp_v0_10, 0, var_s5, (s32) var_s2, (s32) arg1->unkDC->unk2, (s32) arg1->unkDC->unk4, var_s3, var_s4, (s32) arg1->unkDC->unk2);
                if (temp_s1 == 0xE) {
                    temp_v0_11 = arg1->unkDC;
                    temp_v1_16 = sp38;
                    var_s3 = (s32) temp_v0_11->unk8;
                    var_s4 = (s32) temp_v0_11->unk4;
                    sp38 = temp_v1_16 + 8;
                    temp_v1_16->unk0 = 0xFA000000;
                    temp_v1_16->unk4 = -0x41;
                    var_s5 = (s32) (0x1E0 - var_s3) / 2;
                    var_s2 = (s16) ((s32) (0xF0 - var_s4) / 2);
                    func_8009773C(&sp38, temp_v0_10, 0, arg1->unkEA, var_s5, (s32) var_s2, (s32) arg1->unkDC->unk2, (s32) arg1->unkDC->unk4, var_s3, var_s4, (s32) arg1->unkDC->unk2, sp54, sp54, sp54);
                    temp_v0_12 = arg1->unkEA;
                    temp_v0_13 = temp_v0_12 + 1;
                    if (temp_v0_12 != 0) {
                        arg1->unkEA = temp_v0_13;
                        if ((u32) (temp_v0_13 & 0xFFFF) >= 0x20U) {
                            arg1->unkEA = 0U;
                        }
                    }
                }
                goto block_55;
            }
            var_s2 = 0xF0;
            if (temp_s1 == 0xB) {
block_55:
                if (temp_s1 == 0xB) {
                    temp_v1_17 = sp38;
                    sp38 = temp_v1_17 + 8;
                    temp_v1_17->unk0 = 0xFA000000;
                    temp_v1_17->unk4 = 0xFF;
                    func_8009BBFC(&sp38, var_s5, (u16) var_s2, (u16) var_s3, var_s4);
                }
            }
            temp_v1_18 = sp38;
            sp38 = temp_v1_18 + 8;
            temp_v1_18->unk0 = 0xE3001001;
            temp_v1_18->unk4 = 0x8000;
            break;
        case 20:                                    /* switch 2 */
        case 20:                                    /* switch 1 */
            func_8009B66C(&sp38, arg1);
            break;
        case 2:                                     /* switch 2 */
        case 3:                                     /* switch 2 */
            if (arg1->unkEA != 0) {
                var_a1_2 = 3;
                if (temp_s1 == 3) {
                    var_a1_2 = 1;
                    var_s5_2 = 0x19;
                    var_s3_2 = 0xA0;
                    var_s4_2 = 0x80;
                } else {
                    var_s5_2 = 0xCF;
                    var_s3_2 = 0x90;
                    var_s4_2 = 0x64;
                }
                temp_t9 = func_800B64EC(D_800E81F8, var_a1_2) + 0x10;
                if (arg1->unkEA == 0x10) {
                    spF4 = temp_t9;
                    func_8000DEE4(0x40B);
                }
                if ((u16) arg1->unkEA < 0x21U) {
                    temp_v1_19 = sp38;
                    temp_v1_19->unk0 = 0xDE000000;
                    temp_v1_19->unk4 = &D_000C95F0;
                    sp38 = temp_v1_19 + 8;
                    sp38 = temp_v1_19 + 0x10;
                    temp_v1_19->unk8 = 0xFA000000;
                    sp38 = temp_v1_19 + 0x18;
                    temp_v1_19->unk10 = 0xFD100000;
                    temp_v1_19->unk14 = (s32) (temp_t9 - 0x80000000);
                    sp38 = temp_v1_19 + 0x20;
                    temp_v1_19->unk18 = 0xE8000000;
                    temp_v1_19->unk1C = 0;
                    sp38 = temp_v1_19 + 0x28;
                    temp_v1_19->unk24 = 0x07000000;
                    temp_v1_19->unk20 = 0xF5000100;
                    sp38 = temp_v1_19 + 0x30;
                    temp_v1_19->unk28 = 0xE6000000;
                    temp_v1_19->unk2C = 0;
                    sp38 = temp_v1_19 + 0x38;
                    temp_v1_19->unk30 = 0xF0000000;
                    temp_v1_19->unk34 = 0x073FC000;
                    sp38 = temp_v1_19 + 0x40;
                    temp_v1_19->unk38 = 0xE7000000;
                    temp_v1_19->unk3C = 0;
                    temp_v1_19->unkC = (s32) (((0x20 - arg1->unkEA) * 8) & 0xFF);
                    buildTiledTextureDisplayList(&sp38, temp_t9 + 0x200, 1, var_s5_2, sp4C, var_s3_2, var_s4_2, var_s3_2, var_s4_2, var_s3_2);
                    var_v0_3 = arg1->unkEA + 1;
                    goto block_113;
                }
            }
            break;
        case 4:                                     /* switch 2 */
            if (arg1->unkEA != 0) {
                temp_v0_14 = func_800B600C(0x28U, 0);
                if (temp_v0_14 != NULL) {
                    var_v0_6 = arg1->unkDC->unk6 * arg1->unkE4;
                    temp_fp = arg1->unkE0;
                    if (var_v0_6 < 0) {
                        var_v0_6 += 0xFF;
                    }
                    temp_a1_5 = arg1->unkE2;
                    temp_v1_20 = sp38;
                    sp4C = (var_v0_6 >> 8) + temp_a1_5;
                    sp38 = temp_v1_20 + 8;
                    temp_v1_20->unk4 = &D_000C95F0;
                    temp_v1_20->unk0 = 0xDE000000;
                    sp38 = temp_v1_20 + 0x10;
                    temp_v1_20->unk8 = 0xE3001201;
                    temp_v1_20->unkC = 0x2000;
                    func_80091244(&sp38, temp_a1_5, 0xE3001201);
                    sp38->unk0 = 0xFB000000;
                    sp38->unk4 = (? *)0xFF0000FF;
                    sp38->unk8 = 0xFA000000;
                    sp38->unkC = (? *)0xFFFF00FF;
                    temp_v0_15 = sp38 + 0x10;
                    sp38 += 8;
                    sp38 = temp_v0_15;
                    if ((u16) arg1->unkEA >= 0x1EU) {
                        arg1->unkEA = 0xAU;
                    }
                    temp_s0 = sp38;
                    temp_s0->unk0 = 0xDE000000;
                    temp_s0->unk4 = &D_000C95B8;
                    temp_s0->unk8 = 0xE7000000;
                    temp_s0->unkC = NULL;
                    temp_s0->unk10 = 0xFD500000;
                    sp38 = temp_s0 + 8;
                    sp38 = temp_s0 + 0x10;
                    sp38 = temp_s0 + 0x18;
                    temp_t0 = sp38;
                    temp_s0->unk14 = (s32) (func_800B64EC(temp_v0_14, arg1->unkEA - 1) - 0x80000000);
                    temp_t0->unk0 = 0xF5500000;
                    temp_t0->unk4 = (? *)0x07000000;
                    temp_t0->unk8 = 0xE6000000;
                    temp_t0->unk10 = 0xF3000000;
                    temp_t0->unkC = NULL;
                    temp_t0->unk14 = 0x073FF200;
                    temp_t0->unk18 = 0xE7000000;
                    temp_t0->unk1C = 0;
                    temp_t0->unk20 = 0xF5400800;
                    temp_t0->unk24 = 0;
                    temp_t0->unk28 = 0xF2000000;
                    temp_t0->unk2C = 0xFC0FC;
                    temp_a1_6 = arg1->unkE4;
                    sp38 = temp_t0 + 8;
                    sp38 = temp_t0 + 0x10;
                    sp38 = temp_t0 + 0x18;
                    sp38 = temp_t0 + 0x20;
                    sp38 = temp_t0 + 0x28;
                    sp38 = temp_t0 + 0x30;
                    temp_v0_16 = temp_a1_6 * 0xC8;
                    var_v1_3 = temp_v0_16;
                    if (temp_v0_16 < 0) {
                        var_v1_3 = temp_v0_16 + 0xFF;
                    }
                    temp_s3 = var_v1_3 >> 8;
                    var_a0 = temp_a1_6 * 0x11D;
                    temp_s4 = (temp_s3 * 0x140) / 480;
                    if (var_a0 < 0) {
                        var_a0 += 0xFF;
                    }
                    temp_s5 = temp_fp + (var_a0 >> 8);
                    var_v0_7 = temp_a1_6 * 0x82;
                    if (var_v0_7 < 0) {
                        var_v0_7 += 0xFF;
                    }
                    temp_a1_7 = temp_s5 << 0x12;
                    temp_a0_9 = (temp_s5 + temp_s3) << 0x12;
                    spFC = 0x07000206;
                    temp_t0->unk30 = 0x02180000;
                    temp_t0->unk38 = 0x02180002;
                    temp_t0->unk40 = 0x02180004;
                    temp_t0->unk48 = 0x02180006;
                    temp_t0->unk50 = 0x02140000;
                    temp_t0->unk54 = 0;
                    temp_t0->unk58 = 0x02140002;
                    temp_t0->unk5C = 0x08000000;
                    temp_t0->unk60 = 0x02140004;
                    temp_t0->unk64 = 0x800;
                    temp_t0->unk68 = 0x02140006;
                    temp_t0->unk6C = 0x08000800;
                    temp_t0->unk70 = 0x07000206;
                    temp_t0->unk74 = 0x604;
                    temp_s2 = sp4C - (((var_v0_7 >> 8) * 0x140) / 480);
                    temp_v1_21 = (u32) (temp_s2 << 0x12) >> 0x10;
                    temp_t0->unk34 = (s32) (temp_v1_21 | temp_a1_7);
                    temp_v0_17 = (u32) ((temp_s2 + temp_s4) << 0x12) >> 0x10;
                    temp_t0->unk3C = (s32) (temp_v1_21 | temp_a0_9);
                    temp_t0->unk44 = (s32) (temp_v0_17 | temp_a1_7);
                    temp_t0->unk4C = (s32) (temp_v0_17 | temp_a0_9);
                    sp38 = temp_t0 + 0x38;
                    sp38 = temp_t0 + 0x40;
                    sp38 = temp_t0 + 0x48;
                    sp38 = temp_t0 + 0x50;
                    sp38 = temp_t0 + 0x58;
                    sp38 = temp_t0 + 0x60;
                    sp38 = temp_t0 + 0x68;
                    sp38 = temp_t0 + 0x70;
                    sp38 = temp_t0 + 0x78;
                    var_v1_4 = arg1->unkE4 * 0x84;
                    temp_s5_2 = temp_fp + 1;
                    if (var_v1_4 < 0) {
                        var_v1_4 += 0xFF;
                    }
                    sp38 = temp_t0 + 0x80;
                    temp_t0->unk78 = 0x02180000;
                    sp38 = temp_t0 + 0x88;
                    temp_t0->unk80 = 0x02180002;
                    sp38 = temp_t0 + 0x90;
                    temp_t0->unk88 = 0x02180004;
                    sp38 = temp_t0 + 0x98;
                    temp_t0->unk90 = 0x02180006;
                    sp38 = temp_t0 + 0xA0;
                    temp_t0->unk98 = 0x02140000;
                    temp_t0->unk9C = 0;
                    sp38 = temp_t0 + 0xA8;
                    temp_t0->unkA0 = 0x02140002;
                    temp_t0->unkA4 = 0x08000000;
                    sp38 = temp_t0 + 0xB0;
                    temp_t0->unkA8 = 0x02140004;
                    temp_t0->unkAC = 0x800;
                    sp38 = temp_t0 + 0xB8;
                    temp_t0->unkB0 = 0x02140006;
                    temp_t0->unkB4 = 0x08000800;
                    temp_a2_3 = temp_s5_2 << 0x12;
                    temp_a1_8 = (temp_s5_2 + temp_s3) << 0x12;
                    sp38 = temp_t0 + 0xC0;
                    temp_t0->unkB8 = spFC;
                    temp_t0->unkBC = 0x604;
                    temp_s2_2 = sp4C - (((var_v1_4 >> 8) * 0x140) / 480);
                    temp_v1_22 = (u32) (temp_s2_2 << 0x12) >> 0x10;
                    temp_t0->unk7C = (s32) (temp_v1_22 | temp_a2_3);
                    temp_v0_18 = (u32) ((temp_s2_2 + temp_s4) << 0x12) >> 0x10;
                    temp_a2_4 = temp_v0_18 | temp_a2_3;
                    temp_t0->unk84 = (s32) (temp_v1_22 | temp_a1_8);
                    temp_t0->unk8C = temp_a2_4;
                    temp_t0->unk94 = (s32) (temp_v0_18 | temp_a1_8);
                    func_8009126C(&sp38, temp_a1_8, temp_a2_4, 0x02180002);
                    var_v0_3 = arg1->unkEA + 1;
                    goto block_113;
                }
            }
            break;
        case 5:                                     /* switch 2 */
            temp_v0_19 = arg1->unkEA;
            if (((temp_v0_19 == 0) | (temp_v0_19 >= 0x10U)) == 0) {
                temp_v0_20 = func_800B600C(0x28U, 0);
                if (temp_v0_20 != NULL) {
                    var_v1_5 = arg1->unkDC->unk6 * arg1->unkE4;
                    temp_fp_2 = arg1->unkE0;
                    if (var_v1_5 < 0) {
                        var_v1_5 += 0xFF;
                    }
                    temp_a0_10 = arg1->unkEA;
                    sp4C = (var_v1_5 >> 8) + arg1->unkE2;
                    if (temp_a0_10 >= 8U) {
                        var_s4_3 = 7;
                        var_s0 = (0x10 - temp_a0_10) << 5;
                    } else {
                        var_s4_3 = temp_a0_10;
                        var_s0 = 0xFF;
                    }
                    temp_v1_23 = sp38;
                    sp38 = temp_v1_23 + 8;
                    temp_v1_23->unk0 = 0xDE000000;
                    temp_v1_23->unk4 = &D_000C95F0;
                    sp38 = temp_v1_23 + 0x10;
                    temp_v1_23->unk8 = 0xE3001201;
                    temp_v1_23->unkC = 0x2000;
                    func_80091244(&sp38, 0xE3001201);
                    temp_s1_2 = sp38;
                    temp_s1_2->unk0 = 0xFA000000;
                    temp_s1_2->unk4 = (? *) ((var_s0 & 0xFF) | 0xFFFF0000);
                    temp_a1_9 = arg1->unkE4;
                    sp38 = temp_s1_2 + 8;
                    temp_v1_24 = temp_a1_9 * 0xC8;
                    var_v0_8 = temp_v1_24;
                    if (temp_v1_24 < 0) {
                        var_v0_8 = temp_v1_24 + 0xFF;
                    }
                    temp_a0_11 = var_v0_8 >> 8;
                    temp_s5_3 = temp_fp_2 + temp_a0_11;
                    var_a3 = temp_a1_9 * 0x64;
                    temp_s2_3 = sp4C - ((temp_a0_11 * 0x140) / 480);
                    if (var_a3 < 0) {
                        var_a3 += 0xFF;
                    }
                    var_v0_9 = temp_a1_9 * 0x12C;
                    if (var_v0_9 < 0) {
                        var_v0_9 += 0xFF;
                    }
                    sp38 = temp_s1_2 + 0x10;
                    temp_s1_2->unk8 = 0xFB000000;
                    temp_s1_2->unkC = -0x7F01;
                    sp38 = temp_s1_2 + 0x18;
                    temp_s1_2->unk10 = 0xFD500000;
                    temp_v1_25 = sp38;
                    temp_a1_10 = (u32) (temp_s2_3 << 0x12) >> 0x10;
                    temp_s1_2->unk14 = (s32) (func_800B64EC(temp_v0_20, var_s4_3 + 0x1D, (s32 *) (temp_a1_9 * 0x19), var_a3) - 0x80000000);
                    sp38 = temp_v1_25 + 8;
                    temp_v1_25->unk0 = 0xF5500000;
                    temp_v1_25->unk4 = 0x07000000;
                    sp38 = temp_v1_25 + 0x10;
                    temp_v1_25->unk8 = 0xE6000000;
                    temp_v1_25->unkC = 0;
                    sp38 = temp_v1_25 + 0x18;
                    temp_v1_25->unk10 = 0xF3000000;
                    temp_v1_25->unk14 = 0x073FF200;
                    sp38 = temp_v1_25 + 0x20;
                    temp_v1_25->unk18 = 0xE7000000;
                    temp_v1_25->unk1C = 0;
                    sp38 = temp_v1_25 + 0x28;
                    temp_v1_25->unk20 = 0xF5400800;
                    temp_v1_25->unk24 = 0;
                    sp38 = temp_v1_25 + 0x30;
                    temp_v1_25->unk28 = 0xF2000000;
                    temp_v1_25->unk2C = 0xFC0FC;
                    sp38 = temp_v1_25 + 0x38;
                    temp_a3_2 = temp_s5_3 << 0x12;
                    temp_v1_25->unk30 = 0x02180000;
                    temp_v1_25->unk34 = (s32) (temp_a1_10 | temp_a3_2);
                    temp_a2_5 = (temp_s5_3 + (var_a3 >> 8)) << 0x12;
                    sp38 = temp_v1_25 + 0x40;
                    temp_v1_25->unk38 = 0x02180002;
                    temp_v1_25->unk3C = (s32) (temp_a1_10 | temp_a2_5);
                    sp38 = temp_v1_25 + 0x48;
                    temp_v0_21 = (u32) ((temp_s2_3 + (((var_v0_9 >> 8) * 0x140) / 480)) << 0x12) >> 0x10;
                    temp_a3_3 = temp_v0_21 | temp_a3_2;
                    temp_a1_11 = temp_v1_25 + 0x50;
                    temp_v1_25->unk40 = 0x02180004;
                    temp_v1_25->unk44 = temp_a3_3;
                    sp38 = temp_a1_11;
                    temp_v1_25->unk4C = (s32) (temp_v0_21 | temp_a2_5);
                    temp_v1_25->unk48 = 0x02180006;
                    sp38 = temp_v1_25 + 0x58;
                    temp_v1_25->unk50 = 0x02140000;
                    temp_v1_25->unk54 = 0x08000000;
                    sp38 = temp_v1_25 + 0x60;
                    temp_v1_25->unk58 = 0x02140002;
                    temp_v1_25->unk5C = 0;
                    sp38 = temp_v1_25 + 0x68;
                    temp_v1_25->unk60 = 0x02140004;
                    temp_v1_25->unk64 = 0x08000800;
                    sp38 = temp_v1_25 + 0x70;
                    temp_v1_25->unk6C = 0x800;
                    temp_v1_25->unk68 = 0x02140006;
                    sp38 = temp_v1_25 + 0x78;
                    temp_v1_25->unk70 = 0x07000206;
                    temp_v1_25->unk74 = 0x604;
                    func_8009126C(&sp38, (s32) temp_a1_11, temp_a2_5, temp_a3_3);
                    var_v0_3 = arg1->unkEA + 1;
                    goto block_113;
                }
            }
            break;
        case 7:                                     /* switch 2 */
            temp_v0_22 = func_800B64EC(D_800E81F8, 0);
            temp_t9_2 = temp_v0_22 + 0x10;
            temp_s6 = temp_v0_22 + 0x30;
            temp_v1_26 = sp38;
            sp38 = temp_v1_26 + 8;
            temp_v1_26->unk0 = 0xDE000000;
            temp_v1_26->unk4 = &D_000C9620;
            sp38 = temp_v1_26 + 0x10;
            temp_v1_26->unk8 = 0xFD100000;
            temp_v1_26->unkC = (s32) (temp_t9_2 - 0x80000000);
            sp38 = temp_v1_26 + 0x18;
            temp_v1_26->unk10 = 0xE8000000;
            temp_v1_26->unk14 = 0;
            sp38 = temp_v1_26 + 0x20;
            temp_v1_26->unk1C = 0x07000000;
            temp_v1_26->unk18 = 0xF5000100;
            sp38 = temp_v1_26 + 0x28;
            temp_v1_26->unk20 = 0xE6000000;
            temp_v1_26->unk24 = 0;
            sp38 = temp_v1_26 + 0x30;
            temp_v1_26->unk28 = 0xF0000000;
            temp_v1_26->unk2C = 0x0703C000;
            sp38 = temp_v1_26 + 0x38;
            temp_v1_26->unk30 = 0xE7000000;
            temp_v1_26->unk34 = 0;
            sp38 = temp_v1_26 + 0x40;
            temp_v1_26->unk38 = 0xFD500000;
            temp_v1_26->unk3C = (s32) (temp_s6 - 0x80000000);
            sp38 = temp_v1_26 + 0x48;
            temp_v1_26->unk40 = 0xF5500000;
            temp_v1_26->unk44 = 0x07000060;
            sp38 = temp_v1_26 + 0x50;
            temp_v1_26->unk48 = 0xE6000000;
            temp_v1_26->unk4C = 0;
            sp38 = temp_v1_26 + 0x58;
            temp_v1_26->unk50 = 0xF3000000;
            temp_v1_26->unk54 = 0x073FF200;
            temp_v1_26->unk64 = 0x60;
            temp_v1_26->unk58 = 0xE7000000;
            temp_v1_26->unk5C = 0;
            temp_v1_26->unk60 = 0xF5400800;
            temp_v1_26->unk68 = 0xF2000000;
            temp_v1_26->unk6C = 0xFC0FC;
            temp_v1_26->unk70 = 0xE4780100;
            temp_v1_26->unk74 = 0;
            temp_v1_26->unk78 = 0xE1000000;
            temp_v1_26->unk80 = 0xF1000000;
            temp_v1_26->unk84 = 0x04000400;
            temp_v1_26->unk88 = 0xE47803C0;
            temp_v1_26->unk8C = 0x2C0;
            temp_v1_26->unk90 = 0xE1000000;
            temp_v1_26->unk7C = (s32) ((arg1->unkEA & 0x3F) << 0x15);
            temp_v1_26->unk98 = 0xF1000000;
            temp_v1_26->unk9C = 0x0400FC00;
            temp_v1_26->unk94 = (s32) (((~arg1->unkEA & 0x3F) << 0x15) | 0x7E0);
            sp38 = temp_v1_26 + 0x60;
            sp38 = temp_v1_26 + 0x68;
            sp38 = temp_v1_26 + 0x70;
            sp38 = temp_v1_26 + 0x78;
            sp38 = temp_v1_26 + 0x80;
            sp38 = temp_v1_26 + 0x88;
            sp38 = temp_v1_26 + 0x90;
            sp38 = temp_v1_26 + 0x98;
            sp38 = temp_v1_26 + 0xA0;
            arg1->unkEA = (u16) (arg1->unkEA + 1);
            break;
        case 8:                                     /* switch 2 */
            temp_v0_23 = func_800B64EC(D_800E81F8, 0);
            temp_t9_3 = temp_v0_23 + 0x10;
            temp_fp_3 = sp38;
            sp7C = 0xFCFFFFFF;
            temp_fp_3->unk4 = &D_000C95B8;
            temp_fp_3->unk0 = 0xDE000000;
            temp_fp_3->unk8 = 0xDE000000;
            temp_fp_3->unkC = &D_000C95F0;
            temp_fp_3->unk10 = 0xFCFFFFFF;
            temp_fp_3->unk14 = 0xFFFCF87C;
            temp_s6_2 = temp_v0_23 + 0x30;
            sp38 = temp_fp_3 + 8;
            sp38 = temp_fp_3 + 0x10;
            sp38 = temp_fp_3 + 0x18;
            if (!(arg1->unkEA & 0x100)) {
                sp84 = 0xF5000100;
                sp8C = 0x0703C000;
                spFC = 0x02140002;
                sp94 = 0x02140004;
                sp9C = 0x02140006;
                spA4 = 0x07000206;
                spAC = 0xFFFCF279;
                temp_fp_3->unk18 = 0x02100000;
                temp_fp_3->unk24 = -1;
                temp_fp_3->unk34 = -1;
                temp_fp_3->unk38 = 0xFD100000;
                temp_fp_3->unk1C = 0;
                temp_fp_3->unk20 = 0x02100002;
                temp_fp_3->unk28 = 0x02100004;
                temp_fp_3->unk2C = 0;
                temp_fp_3->unk30 = 0x02100006;
                temp_fp_3->unk3C = (s32) (temp_t9_3 - 0x80000000);
                temp_fp_3->unk40 = 0xE8000000;
                temp_fp_3->unk44 = 0;
                temp_fp_3->unk4C = 0x07000000;
                temp_fp_3->unk50 = 0xE6000000;
                temp_fp_3->unk54 = 0;
                temp_fp_3->unk48 = 0xF5000100;
                temp_fp_3->unk58 = 0xF0000000;
                temp_fp_3->unk60 = 0xE7000000;
                temp_fp_3->unk64 = 0;
                temp_fp_3->unk5C = 0x0703C000;
                sp38 = temp_fp_3 + 0x20;
                sp38 = temp_fp_3 + 0x28;
                sp38 = temp_fp_3 + 0x30;
                sp38 = temp_fp_3 + 0x38;
                sp38 = temp_fp_3 + 0x40;
                sp38 = temp_fp_3 + 0x48;
                sp38 = temp_fp_3 + 0x50;
                sp38 = temp_fp_3 + 0x58;
                sp38 = temp_fp_3 + 0x60;
                sp38 = temp_fp_3 + 0x68;
                sp38 = temp_fp_3 + 0x70;
                temp_fp_3->unk6C = (s32) (temp_s6_2 - 0x80000000);
                temp_fp_3->unk68 = 0xFD500000;
                sp38 = temp_fp_3 + 0x78;
                temp_fp_3->unk70 = 0xF5500000;
                temp_fp_3->unk74 = 0x07000070;
                sp38 = temp_fp_3 + 0x80;
                temp_fp_3->unk78 = 0xE6000000;
                temp_fp_3->unk7C = 0;
                sp38 = temp_fp_3 + 0x88;
                temp_fp_3->unk80 = 0xF3000000;
                temp_fp_3->unk84 = 0x073FF100;
                sp38 = temp_fp_3 + 0x90;
                temp_fp_3->unk88 = 0xE7000000;
                temp_fp_3->unk8C = 0;
                sp38 = temp_fp_3 + 0x98;
                temp_fp_3->unk94 = 0x70;
                temp_fp_3->unk90 = 0xF5401000;
                sp38 = temp_fp_3 + 0xA0;
                temp_fp_3->unk98 = 0xF2000000;
                temp_fp_3->unk9C = 0x1FC07C;
                sp38 = temp_fp_3 + 0xA8;
                temp_fp_3->unkA0 = 0x02180000;
                sp38 = temp_fp_3 + 0xB0;
                temp_fp_3->unkA8 = 0x02180002;
                sp38 = temp_fp_3 + 0xB8;
                temp_fp_3->unkB0 = 0x02180004;
                temp_t4_2 = ((arg1->unkEA * 2) - 0x3F) & 0x1FF;
                sp38 = temp_fp_3 + 0xC0;
                temp_fp_3->unkB8 = 0x02180006;
                sp38 = temp_fp_3 + 0xC8;
                temp_a2_6 = temp_t4_2 << 0x15;
                temp_fp_3->unkC0 = 0x02140000;
                temp_fp_3->unkC4 = temp_a2_6;
                temp_s5_4 = ((temp_t4_2 - 0x40) * 0x1E0) / 320;
                temp_a0_12 = temp_s5_4 << 0x12;
                temp_fp_3->unkA4 = (s32) (temp_a0_12 | 0x160);
                temp_v0_24 = (temp_s5_4 + 0x60) << 0x12;
                temp_fp_3->unkBC = (s32) (temp_v0_24 | 0x260);
                temp_fp_3->unkAC = (s32) (temp_v0_24 | 0x160);
                temp_fp_3->unkB4 = (s32) (temp_a0_12 | 0x260);
                sp38 = temp_fp_3 + 0xD0;
                temp_v1_27 = temp_t4_2 + 0x40;
                temp_a3_4 = temp_v1_27 & 0x7F;
                temp_v1_28 = temp_v1_27 << 0x15;
                temp_fp_3->unkC8 = 0x02140002;
                temp_fp_3->unkCC = temp_v1_28;
                temp_a2_7 = temp_a2_6 | 0x400;
                sp38 = temp_fp_3 + 0xD8;
                temp_fp_3->unkD0 = 0x02140004;
                temp_fp_3->unkD4 = temp_a2_7;
                sp38 = temp_fp_3 + 0xE0;
                temp_fp_3->unkD8 = 0x02140006;
                temp_fp_3->unkDC = (s32) (temp_v1_28 | 0x400);
                sp38 = temp_fp_3 + 0xE8;
                temp_fp_3->unkE0 = 0x07000206;
                temp_fp_3->unkE4 = 0x604;
                temp_v0_25 = temp_fp_3 + 0xF0;
                sp38 = temp_v0_25;
                temp_fp_3->unkE8 = sp7C;
                temp_fp_3->unkEC = 0xFFFCF279;
                spE8 = temp_a3_4;
                spF0 = &D_800C96D0;
                temp_v0_26 = func_800B64EC(D_800E81F8, 1, (s32 *) temp_a2_7, temp_a3_4);
                temp_t9_4 = temp_v0_26 + 0x10;
                temp_s6_3 = temp_v0_26 + 0x30;
                sp38 = temp_v0_25 + 8;
                temp_v0_25->unk4 = (s32) (temp_t9_4 - 0x80000000);
                temp_fp_3->unkF0 = 0xFD100000;
                sp38 = temp_v0_25 + 0x10;
                temp_v0_25->unk8 = 0xE8000000;
                temp_v0_25->unkC = 0;
                sp38 = temp_v0_25 + 0x18;
                temp_v0_25->unk10 = 0xF5000100;
                temp_v0_25->unk14 = 0x07000000;
                sp38 = temp_v0_25 + 0x20;
                temp_v0_25->unk18 = 0xE6000000;
                temp_v0_25->unk1C = 0;
                sp38 = temp_v0_25 + 0x28;
                temp_v0_25->unk20 = 0xF0000000;
                temp_v0_25->unk24 = 0x0703C000;
                sp38 = temp_v0_25 + 0x30;
                temp_v0_25->unk28 = 0xE7000000;
                temp_v0_25->unk2C = 0;
                sp38 = temp_v0_25 + 0x38;
                temp_v0_25->unk30 = 0xFD500000;
                temp_v0_25->unk34 = (s32) (temp_s6_3 - 0x80000000);
                sp38 = temp_v0_25 + 0x40;
                temp_v0_25->unk38 = 0xF5500000;
                temp_v0_25->unk3C = 0x07000000;
                sp38 = temp_v0_25 + 0x48;
                temp_v0_25->unk40 = 0xE6000000;
                temp_v0_25->unk44 = 0;
                sp38 = temp_v0_25 + 0x50;
                temp_v0_25->unk48 = 0xF3000000;
                temp_v0_25->unk4C = 0x0703F800;
                sp38 = temp_v0_25 + 0x58;
                temp_v0_25->unk50 = 0xE7000000;
                temp_v0_25->unk54 = 0;
                sp38 = temp_v0_25 + 0x60;
                temp_v0_25->unk58 = 0xF5400200;
                temp_v0_25->unk5C = 0;
                sp38 = temp_v0_25 + 0x68;
                temp_v0_25->unk60 = 0xF2000000;
                temp_v0_25->unk64 = 0x3C03C;
                var_t8 = &D_800C96D0;
loop_99:
                temp_v0_27 = var_t8->unk0;
                if (temp_v0_27 != temp_a3_4) {
                    if ((s32) temp_v0_27 >= temp_a3_4) {
                        var_t8 += 2;
                        goto loop_99;
                    }
                    if (temp_a3_4 >= (s32) var_t8->unk2) {
                        var_t8 += 2;
                        goto loop_99;
                    }
                    if (temp_a3_4 < 0x58) {
                        D_800DBD60 = 0;
                    } else if ((D_800DBD60 == 0) & (temp_s5_4 < 0x1E0)) {
                        spE8 = temp_a3_4;
                        spF0 = var_t8;
                        func_8000DEE4(0x40E, 0xF5400200, 0x3C03C, temp_a3_4);
                        D_800DBD60 = 1;
                    }
                    temp_a1_12 = var_t8->unk1;
                    temp_a0_13 = var_t8->unk0;
                    var_t6 = temp_a1_12 + ((s32) ((var_t8->unk3 - temp_a1_12) * (temp_a3_4 - temp_a0_13)) / (s32) (var_t8->unk2 - temp_a0_13));
                } else {
                    var_t6 = var_t8->unk1;
                }
                temp_v1_29 = sp38;
                temp_a1_13 = (temp_s5_4 + 0x54) << 0x12;
                temp_v1_29->unk0 = 0x02180000;
                temp_v0_28 = (u32) ((var_t6 + 0x50) << 0x12) >> 0x10;
                temp_v1_29->unk4 = (? *) (temp_v0_28 | temp_a1_13);
                temp_a0_14 = (temp_s5_4 + 0x6C) << 0x12;
                temp_v1_29->unkC = (? *) (temp_v0_28 | temp_a0_14);
                temp_v0_29 = (u32) ((var_t6 + 0x60) << 0x12) >> 0x10;
                temp_v1_29->unk1C = (s32) (temp_v0_29 | temp_a0_14);
                temp_v1_29->unk20 = 0x02140000;
                temp_v1_29->unk2C = 0x02000000;
                temp_v1_29->unk34 = 0x200;
                temp_v1_29->unk8 = 0x02180002;
                temp_v1_29->unk10 = 0x02180004;
                temp_v1_29->unk14 = (s32) (temp_v0_29 | temp_a1_13);
                temp_v1_29->unk18 = 0x02180006;
                temp_v1_29->unk24 = 0;
                temp_v1_29->unk28 = 0x02140002;
                temp_v1_29->unk30 = 0x02140004;
                temp_v1_29->unk38 = 0x02140006;
                temp_v1_29->unk3C = 0x02000200;
                temp_v1_29->unk40 = 0x07000206;
                temp_v1_29->unk44 = 0x604;
                sp38 = temp_v1_29 + 8;
                sp38 = temp_v1_29 + 0x10;
                sp38 = temp_v1_29 + 0x18;
                sp38 = temp_v1_29 + 0x20;
                sp38 = temp_v1_29 + 0x28;
                sp38 = temp_v1_29 + 0x30;
                sp38 = temp_v1_29 + 0x38;
                sp38 = temp_v1_29 + 0x40;
                sp38 = temp_v1_29 + 0x48;
                arg1->unkEA = (u16) ((arg1->unkEA + 1) & 0xFF);
            } else {
                spB4 = 0x02180002;
                spBC = 0x02180004;
                spC4 = 0x02180006;
                spCC = 0x02140002;
                spD4 = 0x02140004;
                spDC = 0x02140006;
                spE4 = 0x07000206;
                temp_fp_3->unk18 = 0x02100000;
                temp_fp_3->unk1C = -1;
                temp_fp_3->unk24 = -1;
                temp_fp_3->unk2C = -1;
                temp_fp_3->unk34 = -1;
                temp_fp_3->unk38 = 0xFD500000;
                temp_fp_3->unk40 = 0xF5500000;
                temp_fp_3->unk3C = (s32) (temp_s6_2 - 0x80000000);
                temp_fp_3->unk50 = 0xF3000000;
                temp_fp_3->unk20 = 0x02100002;
                temp_fp_3->unk28 = 0x02100004;
                temp_fp_3->unk30 = 0x02100006;
                temp_fp_3->unk44 = 0x07000060;
                temp_fp_3->unk48 = 0xE6000000;
                temp_fp_3->unk4C = 0;
                temp_fp_3->unk54 = 0x073FF100;
                temp_fp_3->unk58 = 0xE7000000;
                temp_fp_3->unk5C = 0;
                temp_fp_3->unk60 = 0xF5401000;
                temp_fp_3->unk64 = 0x60;
                temp_fp_3->unk68 = 0xF2000000;
                temp_fp_3->unk6C = 0x1FC07C;
                sp38 = temp_fp_3 + 0x20;
                sp38 = temp_fp_3 + 0x28;
                sp38 = temp_fp_3 + 0x30;
                sp38 = temp_fp_3 + 0x38;
                sp38 = temp_fp_3 + 0x40;
                sp38 = temp_fp_3 + 0x48;
                sp38 = temp_fp_3 + 0x50;
                sp38 = temp_fp_3 + 0x58;
                sp38 = temp_fp_3 + 0x60;
                sp38 = temp_fp_3 + 0x68;
                sp38 = temp_fp_3 + 0x70;
                sp38 = temp_fp_3 + 0x78;
                temp_fp_3->unk70 = 0x02180000;
                temp_fp_3->unk74 = 0x160;
                sp38 = temp_fp_3 + 0x80;
                temp_fp_3->unk78 = 0x02180002;
                sp38 = temp_fp_3 + 0x88;
                temp_fp_3->unk84 = 0x260;
                temp_fp_3->unk80 = 0x02180004;
                sp38 = temp_fp_3 + 0x90;
                temp_fp_3->unk88 = 0x02180006;
                sp38 = temp_fp_3 + 0x98;
                temp_fp_3->unk90 = 0x02140000;
                temp_fp_3->unk94 = 0;
                sp38 = temp_fp_3 + 0xA0;
                temp_fp_3->unk98 = 0x02140002;
                sp38 = temp_fp_3 + 0xA8;
                temp_fp_3->unkA4 = 0x400;
                temp_fp_3->unkA0 = 0x02140004;
                sp38 = temp_fp_3 + 0xB0;
                temp_fp_3->unkA8 = 0x02140006;
                temp_a2_8 = arg1->unkEA & 0x1F;
                sp38 = temp_fp_3 + 0xB8;
                temp_fp_3->unkB4 = 0x604;
                temp_fp_3->unkB0 = 0x07000206;
                temp_s5_5 = temp_a2_8 * 0x10;
                temp_v0_30 = temp_fp_3 + 0xC0;
                sp38 = temp_v0_30;
                temp_v0_31 = temp_a2_8 << 0x16;
                temp_a2_9 = temp_a2_8 << 0x19;
                temp_fp_3->unkB8 = sp7C;
                temp_fp_3->unk9C = temp_a2_9;
                temp_a2_10 = temp_a2_9 | 0x400;
                temp_fp_3->unkBC = 0xFFFCF279;
                temp_fp_3->unk7C = (s32) (temp_v0_31 | 0x160);
                temp_fp_3->unk8C = (s32) (temp_v0_31 | 0x260);
                temp_fp_3->unkAC = temp_a2_10;
                temp_v0_32 = func_800B64EC(D_800E81F8, 1, (s32 *) temp_a2_10, 0x073FF100);
                temp_t9_5 = temp_v0_32 + 0x10;
                temp_s6_4 = temp_v0_32 + 0x30;
                sp38 = temp_v0_30 + 8;
                temp_fp_3->unkC0 = 0xFD100000;
                temp_v0_30->unk4 = (s32) (temp_t9_5 - 0x80000000);
                sp38 = temp_v0_30 + 0x10;
                temp_v0_30->unk8 = 0xE8000000;
                temp_v0_30->unkC = 0;
                sp38 = temp_v0_30 + 0x18;
                temp_v0_30->unk10 = 0xF5000100;
                temp_v0_30->unk14 = 0x07000000;
                sp38 = temp_v0_30 + 0x20;
                temp_v0_30->unk18 = 0xE6000000;
                temp_v0_30->unk1C = 0;
                sp38 = temp_v0_30 + 0x28;
                temp_v0_30->unk20 = 0xF0000000;
                temp_v0_30->unk24 = 0x0703C000;
                sp38 = temp_v0_30 + 0x30;
                temp_v0_30->unk28 = 0xE7000000;
                temp_v0_30->unk2C = 0;
                sp38 = temp_v0_30 + 0x38;
                temp_v0_30->unk30 = 0xFD500000;
                temp_v0_30->unk34 = (s32) (temp_s6_4 - 0x80000000);
                sp38 = temp_v0_30 + 0x40;
                temp_v0_30->unk38 = 0xF5500000;
                temp_v0_30->unk3C = 0x07000000;
                sp38 = temp_v0_30 + 0x48;
                temp_v0_30->unk40 = 0xE6000000;
                temp_v0_30->unk44 = 0;
                sp38 = temp_v0_30 + 0x50;
                temp_v0_30->unk48 = 0xF3000000;
                temp_v0_30->unk4C = 0x0703F800;
                sp38 = temp_v0_30 + 0x58;
                temp_v0_30->unk50 = 0xE7000000;
                temp_v0_30->unk54 = 0;
                temp_v0_30->unk60 = 0xF2000000;
                temp_a1_14 = (temp_s5_5 - 8) << 0x12;
                temp_v0_30->unk58 = 0xF5400200;
                temp_v0_30->unk5C = 0;
                temp_v0_30->unk64 = 0x3C03C;
                temp_v0_30->unk68 = 0x02180000;
                temp_v0_30->unk6C = (s32) (temp_a1_14 | 0x1C0);
                temp_a0_15 = (temp_s5_5 + 8) << 0x12;
                temp_v0_30->unk70 = 0x02180002;
                temp_v0_30->unk74 = (s32) (temp_a0_15 | 0x1C0);
                temp_v0_30->unk78 = 0x02180004;
                temp_v0_30->unk7C = (s32) (temp_a1_14 | 0x200);
                temp_v0_30->unk80 = 0x02180006;
                temp_v0_30->unk84 = (s32) (temp_a0_15 | 0x200);
                temp_v0_30->unk88 = 0x02140000;
                temp_v0_30->unk8C = 0;
                temp_v0_30->unk90 = 0x02140002;
                temp_v0_30->unk94 = 0x02000000;
                temp_v0_30->unk98 = 0x02140004;
                temp_v0_30->unk9C = 0x200;
                temp_v0_30->unkA0 = 0x02140006;
                temp_v0_30->unkA4 = 0x02000200;
                temp_v0_30->unkA8 = 0x07000206;
                temp_v0_30->unkAC = 0x604;
                sp38 = temp_v0_30 + 0x60;
                sp38 = temp_v0_30 + 0x68;
                sp38 = temp_v0_30 + 0x70;
                sp38 = temp_v0_30 + 0x78;
                sp38 = temp_v0_30 + 0x80;
                sp38 = temp_v0_30 + 0x88;
                sp38 = temp_v0_30 + 0x90;
                sp38 = temp_v0_30 + 0x98;
                sp38 = temp_v0_30 + 0xA0;
                sp38 = temp_v0_30 + 0xA8;
                sp38 = temp_v0_30 + 0xB0;
                temp_a0_16 = arg1->unkEA + 1;
                arg1->unkEA = temp_a0_16;
                var_v0_3 = 0x11F;
                if ((u32) (temp_a0_16 & 0xFFFF) >= 0x11FU) {
                    goto block_113;
                }
            }
            break;
        }
    }
    *sp44 = sp38;
}
