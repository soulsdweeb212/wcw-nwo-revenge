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

typedef struct {
    s16 f0;
    s16 f2;
    s16 f4;
    s16 f6;
    u16 f8;
    u8 padA[0x16];
    u64 flags;
    u8 pad28[0x24];
    f32 fx;
    f32 fy;
    f32 fz;
    s32 f58;
    u8 pad5C[0x2F7];
    s8 f353;
    u8 pad354[0x2E];
    u8 f382;
    u8 pad383[0x2D];
} Nw2Ent;

extern Nw2Ent D_800F9D10[];
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
            if (D_800F9D10[i].f2 == -1) {
                D_800EB6D0[i][D_800F97D0.f2][4] = -1;
            } else {
                s16 v;
                s32 mask;

                D_800EB6D0[i][D_800F97D0.f2][4] = D_800F9D10[i].f8;
                v = D_800F9D10[i].f6 - 1;
                if (v < 0)
                    v = 0;
                D_800EB6D0[i][D_800F97D0.f2][5] = v & 0x3FF;
                D_800EB6D0[i][D_800F97D0.f2][0] = D_800F9D10[i].fx * D_800E6D20;
                D_800EB6D0[i][D_800F97D0.f2][1] = D_800F9D10[i].fz * D_800E6D20;
                D_800EB6D0[i][D_800F97D0.f2][2] = D_800F9D10[i].fy * D_800E6D20;
                D_800EB6D0[i][D_800F97D0.f2][3] = D_800F9D10[i].f58;

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
                    if (D_800F9D10[i].f2 != -1) {
                        if (D_800F9D10[i].flags & 0x200)
                            count++;
                    }
                }

                if ((*(u16 *)(D_8007E228 + 0x58) & 0x100) ||
                    ((*(u16 *)(D_8007E228 + 0x58) & 0x400) && (count < 3))) {
                    for (i = 0; i < 4; i++) {
                        s32 id;
                        s16 frame;

                        if (D_800F9D10[i].f2 == -1)
                            continue;
                        if (!(D_800F9D10[i].flags & 0x200))
                            continue;
                        id = D_800F9D10[i].f353;
                        if (!(D_800F9D10[id].flags & 0x200))
                            continue;
                        if (D_800F9D10[i].f6 != D_800F9D10[i].f382 + 0xF)
                            continue;
                        if (!(D_800FABD8 & D_800E3F20[i]))
                            continue;

                        D_800FABD8 = D_800E3F20[i] | 1;
                        REC->f0 = i;
                        REC->f1 = D_800F9D10[i].f353;
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
