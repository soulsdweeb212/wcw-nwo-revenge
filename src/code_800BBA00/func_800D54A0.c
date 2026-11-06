/* @header
 * func_800D54A0
 * VRAM 0x800D54A0 | ROM 0xC8940 | size 0x6D4
 * asm: asm/nonmatchings/code_800BBA00/func_800D54A0.s
 */
#include "common.h"

extern s32 D_800FABD8;
extern u16 D_800FADD0;
extern const f64 D_800E6D20;
extern u8 D_8007E228[];
extern u8 D_8007EF30[];
extern s16 D_800F97D6;
extern s16 D_800F97D8;
extern s16 D_800F97DA;
extern s16 D_800F97DE;
extern s16 D_800F97E2;
extern u8 D_800F2750[];
extern s32 D_800E3F20[];
extern u8 D_800E3F30[];
extern u32 D_800EB6B8[];

extern s16 D_800EB6D0[4][0x258][6];

typedef struct {
    s8 f0;
    u8 f1;
    s16 f2;
    s16 f4;
    s16 f6;
    s16 f8;
    s16 padA;
    s16 fC;
    s16 padE;
    s16 f10;
} Nw2FrameRec;

extern Nw2FrameRec D_800F97D0;
#define REC ((Nw2FrameRec *)&D_800F97D0)

void packFieldRecords(void *);

void func_800D54A0(void)
{
    s16 i;
    s16 count;

    if (!(D_800FABD8 & 4)) {
        for (i = 0; i < 4; i++) {
            if (D_800F9D10[i].characterId == -1) {
                D_800EB6D0[i][D_800F97D0.f2][4] = -1;
            } else {
                s16 v;
                s32 mask;

                D_800EB6D0[i][D_800F97D0.f2][4] = D_800F9D10[i].animId;
                v = D_800F9D10[i].animFrame - 1;
                if (v < 0)
                    v = 0;
                D_800EB6D0[i][D_800F97D0.f2][5] = v & 0x3FF;
                D_800EB6D0[i][D_800F97D0.f2][0] = D_800F9D10[i].x * D_800E6D20;
                D_800EB6D0[i][D_800F97D0.f2][1] = D_800F9D10[i].z * D_800E6D20;
                D_800EB6D0[i][D_800F97D0.f2][2] = D_800F9D10[i].y * D_800E6D20;
                D_800EB6D0[i][D_800F97D0.f2][3] = D_800F9D10[i].heading;

                mask = 0;
                switch (D_800EB6B8[i]) {
                case 0:
                case 1:
                case 4:
                case 5:
                    break;
                case 2:
                case 3:
                    mask = 0x8000;
                    break;
                case 6:
                    mask = 0x4000;
                    break;
                }
                D_800EB6D0[i][D_800F97D0.f2][5] |= mask;
            }
        }

        packFieldRecords(D_800F2750 + D_800F97D0.f2 * 48);
        D_800F97D0.f2++;
        if (D_800F97D0.f2 >= 0x258)
            D_800F97D0.f2 = 0;
    }

    if (!(D_800FADD0 & 0xF)) {
        if (!(D_800FABD8 & 0x100)) {
            if (D_8007EF30[3] == 0) {
                count = 0;
                for (i = 0; i < 4; i++) {
                    if (D_800F9D10[i].characterId != -1) {
                        if (D_800F9D10[i].flags & WR_FLAG_LEGAL)
                            count++;
                    }
                }

                if ((*(u16 *)(D_8007E228 + 0x58) & 0x100) ||
                    ((*(u16 *)(D_8007E228 + 0x58) & 0x400) && (count < 3))) {
                    for (i = 0; i < 4; i++) {
                        s32 id;
                        s16 frame;

                        if (D_800F9D10[i].characterId == -1)
                            continue;
                        if (!(D_800F9D10[i].flags & WR_FLAG_LEGAL))
                            continue;
                        id = D_800F9D10[i].opponentId;
                        if (!(D_800F9D10[id].flags & WR_FLAG_LEGAL))
                            continue;
                        if (D_800F9D10[i].animFrame != D_800F9D10[i].anim.unk37D[5] + 0xF)
                            continue;
                        if (!(D_800FABD8 & D_800E3F20[i]))
                            continue;

                        D_800FABD8 = D_800E3F20[i] | 1;
                        REC->f0 = i;
                        REC->f1 = D_800F9D10[i].opponentId;
                        REC->f4 = 2;
                        REC->f6 = -0xF;
                        REC->f10 = 1;
                        frame = REC->f2;
                        REC->f8 = frame;
                        REC->fC = frame;
                        break;
                    }
                }
            }
        }
    }

    if (!(D_800FADD0 & 0xF)) {
        if (D_800FABD8 & 1) {
            u16 *p;
            u16 *q;

            D_800FABD8 = (D_800FABD8 & ~1) | 0xFA;
            p = &D_800F97D8;
            *p = *p + D_800F97D6;
            if ((s16)*p >= 0x258)
                *p = *p - 0x258;
            if ((s16)*p < 0)
                *p = *p + 0x258;
            if (D_800FABD8 & 0x100) {
                q = p;
                while ((u32)(D_800EB6D0[(s32)D_800F97D0.f0][(s16)*q][5] & 0x3FF) >= 2) {
                    (*q)--;
                    if ((s16)*q < 0)
                        *q += 0x258;
                }
            }
            D_800F97E2 = 0;
            D_800F97DE = 0xDE;
            D_800F97DA = D_800F97D8;
            D_800F97DE = *(u16 *)(D_800E3F30 + (s8)D_800F97D0.f0 * 2) | 0xDE;
        }
    }
}
