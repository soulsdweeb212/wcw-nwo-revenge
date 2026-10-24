#include "common.h"

extern u8 D_8007E228[];
extern u8 D_800F9D30[];
typedef struct { u8 c[0x18]; } Cnt;
extern Cnt D_8007E850[];
extern u8 D_8007E85C[], D_8007E85D[], D_8007E85E[], D_8007E85F[];
extern u8 D_8007E860[], D_8007E861[], D_8007E862[], D_8007E863[], D_8007E864[];
extern u8 D_8007E865[];

void func_800B9D60(s8 *arg0, s8 *arg1, s32 arg2)
{
    s8 t2 = 0;
    s8 i;
    s8 id;
    s32 eoff;
    u64 flags;

    if (*arg1 != -1) {
        do {
            t2 = t2 + 1;
        } while (arg1[t2] != -1);
    }
    if (!(*(u16 *)(D_8007E228 + 0x58) & 0x400)) {
        return;
    }
    while (*arg0 != -1) {
        u32 tq;
        id = *arg0;
        eoff = id * 0x3B0;
        flags = *(u64 *)(D_800F9D30 + eoff);
        if (!(flags & 0x8000)) {
            if (flags & 4) {
                D_8007E850[id].c[2]++;
            } else {
                D_8007E850[id].c[0x16]++;
            }
        }
        if (arg2 & 0x2000) {
            eoff = *arg0 * 0x3B0;
            if (*(u64 *)(D_800F9D30 + eoff) & 4) {
                s32 o = *arg0 * 0x18;
                D_8007E860[o] = D_8007E860[o] + t2;
            } else {
                s32 o = *arg0 * 0x18;
                D_8007E85C[o] = D_8007E85C[o] + t2;
            }
        } else if (arg2 & 0x1000) {
            eoff = *arg0 * 0x3B0;
            if (*(u64 *)(D_800F9D30 + eoff) & 4) {
                s32 o = *arg0 * 0x18;
                D_8007E861[o] = D_8007E861[o] + t2;
            } else {
                s32 o = *arg0 * 0x18;
                D_8007E85D[o] = D_8007E85D[o] + t2;
            }
        } else if (arg2 & 0x8000) {
            eoff = *arg0 * 0x3B0;
            if (*(u64 *)(D_800F9D30 + eoff) & 4) {
                s32 o = *arg0 * 0x18;
                D_8007E862[o] = D_8007E862[o] + t2;
            } else {
                s32 o = *arg0 * 0x18;
                D_8007E85E[o] = D_8007E85E[o] + t2;
            }
        } else if (arg2 & 0x10000) {
            eoff = *arg0 * 0x3B0;
            if (*(u64 *)(D_800F9D30 + eoff) & 4) {
                s32 o = *arg0 * 0x18;
                D_8007E863[o] = D_8007E863[o] + t2;
                eoff = *arg0 * 0x3B0;
                if (*(u64 *)(D_800F9D30 + eoff) & 0x8000) {
                    s32 o2 = *arg0 * 0x18;
                    D_8007E865[o2] = D_8007E865[o2] + t2;
                }
            } else {
                s32 o = *arg0 * 0x18;
                D_8007E85F[o] = D_8007E85F[o] + t2;
                eoff = *arg0 * 0x3B0;
                if (*(u64 *)(D_800F9D30 + eoff) & 0x8000) {
                    s32 o2 = *arg0 * 0x18;
                    D_8007E864[o2] = D_8007E864[o2] + t2;
                }
            }
        }
        tq = (u32)flags & 1;
        if (tq >> 1) {
            D_8007E228[0] = 3;
        }
        eoff = *arg0 * 0x3B0;
        flags = *(u64 *)(D_800F9D30 + eoff);
        if (!(flags & 0x8000)) {
            if (flags & 4) {
                for (i = 0; arg1[i] != -1; i = i + 1) {
                    switch (arg1[i]) {
                    case 0: D_8007E850[*arg0].c[8]++; break;
                    case 1: D_8007E850[*arg0].c[9]++; break;
                    case 2: D_8007E850[*arg0].c[0xA]++; break;
                    case 3: D_8007E850[*arg0].c[0xB]++; break;
                    }
                }
            } else {
                for (i = 0; arg1[i] != -1; i = i + 1) {
                    switch (arg1[i]) {
                    case 0: D_8007E850[*arg0].c[4]++; break;
                    case 1: D_8007E850[*arg0].c[5]++; break;
                    case 2: D_8007E850[*arg0].c[6]++; break;
                    case 3: D_8007E850[*arg0].c[7]++; break;
                    }
                }
            }
        }
        arg0++;
    }
    while (*arg1 != -1) {
        id = *arg1;
        eoff = id * 0x3B0;
        if (*(u64 *)(D_800F9D30 + eoff) & 4) {
            D_8007E850[id].c[3]++;
        } else {
            D_8007E850[id].c[0x17]++;
        }
        arg1++;
    }
}
