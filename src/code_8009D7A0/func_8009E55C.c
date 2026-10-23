#include "common.h"

extern void *D_800EB408;
extern void func_800D427C(void *, s32, s32);
extern void func_800DECAC(void *, s32, s32, s32);
extern void func_800D4AD0(void *);
extern void func_800A6C48(void *, s32);

void func_8009E55C(void) {
    s16 state = *(s16 *)((u8 *)D_800EB408 + 0xC);
    s32 id;

    switch (state) {
    case 0:
        if (*(u64 *)((u8 *)D_800EB408 + 0x20) & 0x8000000000ULL)
            id = 0x109B;
        else
            id = 0x109C;
        func_800D427C(D_800EB408, id, 0);
        *(u16 *)((u8 *)D_800EB408 + 0xC) = *(u16 *)((u8 *)D_800EB408 + 0xC) + 1;
    case 1:
        if (*(s16 *)((u8 *)D_800EB408 + 4) <= 0) {
            func_800DECAC(D_800EB408, 0, 0, 0);
            func_800D4AD0(D_800EB408);
            func_800A6C48(D_800EB408, 0x2B);
        }
        break;
    }
}
