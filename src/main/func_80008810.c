/* @header
 * func_80008810
 * VRAM 0x80008810 | ROM 0x9410 | size 0x2E0
 * asm: asm/nonmatchings/main/func_80008810.s
 */
#include "common.h"

typedef struct { u8 b[0x18]; } MQ;
typedef struct {
    s16 f0, f2, f4;
    u8 pad6[0x12];
    s16 f18, f1A;
    u8 pad1C[0x40];
    MQ mq;            /* 5C */
    u8 pad74[0x18];
    void *msg;        /* 8C */
    MQ mqs[2];        /* 90 */
    u8 padC0[0x30];
    void *msgs[2];    /* F0 */
    s16 fF8, fFA;
} Ctl;

extern s32 D_80030830;
extern u16 D_8006A2B0[][2];
#ifndef TARGET_PC /* on PC, port_decls.h declares D_800485A0 */
extern void *D_800485A0[];
#endif
extern s8 D_800485B0[][8];
extern s8 D_800485D0[][8];
extern Ctl D_800706A8[];
extern s8 D_800307C0[];
extern u8 D_80074EC0[][0x40];
#ifndef TARGET_PC /* on PC, port_decls.h declares D_8004859C and D_8007BD38 */
extern s32 D_8004859C;
#endif
extern s16 D_8006E440;
#ifndef TARGET_PC /* as above */
extern void *D_8007BD38;
#endif
void *allocateHeap(u32);
#ifndef TARGET_PC /* on PC, port.h declares the loader functions */
void lookupResourceDescriptor(void *, u16);
void readRomSynchronousChunks(s32, void *, s32);
#endif
void releaseHeapBlock(void *);
#ifndef TARGET_PC /* on PC, port.h declares the loader functions */
void func_80003684(void *, s32, void *);
#endif
void func_80008574(s32);
void guTranslateF(void *, f32, f32, f32);
void osCreateMesgQueue(void *, void *, s32);
#ifdef TARGET_PC
/* PC: osCartRomInit takes nothing and returns the cartridge's PI handle, a pointer (SDK cartrominit.c). The N64
 * declaration takes one argument (the call leaves dst in $a0, which the function never reads) and returns s32, which
 * on PC would cut the handle in half. */
void *osCartRomInit(void);
#else
s32 osCartRomInit(void *);
#endif

void func_80008810(void) {
    s32 sp10[4];
    s32 sp20[4];
    s32 sp30[4];
    u16 *buf;
    u32 n;
    u32 i;
    u32 j;
    MQ *q;
    s8 *px;
    s8 *py;
    u8 *dst;
    u8 *cur;
    s32 k;

    if (D_80030830 != 0) {
        buf = allocateHeap(4);
        for (n = 0; n < 0xFB1; n++) {
            lookupResourceDescriptor(sp10, n + 0xE39);
            readRomSynchronousChunks(sp10[0], buf, 4);
#ifdef TARGET_PC
            /* PC: buf holds the resource's first 4 bytes as the ROM has them (readRomSynchronousChunks does not pass
             * port_res_loaded, which converts whole resources), so its two u16 are big-endian. They are stored in the
             * PC's byte order, so that D_8006A2B0's readers (decodeAnimationMetadata, func_8000946C) need no change. */
            D_8006A2B0[n][0] = READ_BE16(&buf[0]);
            D_8006A2B0[n][1] = READ_BE16(&buf[1]);
#else
            D_8006A2B0[n][0] = buf[0];
            D_8006A2B0[n][1] = buf[1];
#endif
            func_80008574((s16)(n + 0xE39));
        }
#ifdef TARGET_PC
        /* PC: releaseHeapBlock's definition takes a u8 *. */
        releaseHeapBlock((u8 *)buf);
#else
        releaseHeapBlock(buf);
#endif
        D_80030830 = 0;
    }
    lookupResourceDescriptor(sp20, 0x20F);
    D_8007BD38 = allocateHeap(sp20[2]);
    func_80003684(sp30, 0x20F, D_8007BD38);
    for (i = 0; i < 4; i++) {
        D_800485A0[i] = allocateHeap(0x6200);
        D_800706A8[i].f0 = 1;
        D_800706A8[i].f2 = 0;
        D_800706A8[i].f4 = -1;
        D_800706A8[i].f18 = -1;
        D_800706A8[i].f1A = -1;
        osCreateMesgQueue(&D_800706A8[i].mq, &D_800706A8[i].msg, 1);
        q = D_800706A8[i].mqs;
        osCreateMesgQueue(&q[0], &D_800706A8[i].msgs[0], 1);
        osCreateMesgQueue(&q[1], &D_800706A8[i].msgs[1], 1);
        D_800706A8[i].fF8 = 0;
        D_800706A8[i].fFA = 0;
        for (j = 1; j < 8; j++) {
            D_800485B0[i][j] = -1;
            D_800485D0[i][j] = 0;
        }
    }
    i = 1;
    k = 3;
    py = D_800307C0 + k;
    px = D_800307C0 + 2;
    dst = D_80074EC0[0];
    cur = dst;
    do {
        s32 y = *py;
        s32 x = *px;
        py += 2;
        px += 2;
        dst += 0x40;
        i++;
        guTranslateF(cur, -x, -y, 0);
        cur = dst;
    } while (i < 20);
#ifdef TARGET_PC
    /* PC: the handle is kept whole, without the extra argument (see the declaration above). */
    D_8004859C = osCartRomInit();
#else
    D_8004859C = osCartRomInit(dst);
#endif
    D_8006E440 = 1;
}
