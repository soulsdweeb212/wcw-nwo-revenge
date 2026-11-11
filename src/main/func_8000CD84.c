/* @header
 * func_8000CD84
 * VRAM 0x8000CD84 | ROM 0xD984 | size 0x1E0
 * asm: asm/nonmatchings/main/func_8000CD84.s
 */
#include "common.h"

/* Release all resources for one slot (`index`). Frees the 23 buffered blocks
 * in D_8007C438[index*23..] (zeroing their D_8007C318 counts), resets the
 * per-slot counters D_8006A2A4/D_8007DFB0/D_8007DFBC/D_800566E0 to -1, copies
 * the 23 source strings (D_800651A0 -> D_80073EB0), tears down the slot's
 * effect record if active, resets the second block table and clears the
 * D_8007C3D0 slot. */
void releaseHeapBlock(void *);
void func_8000520C(void *, void *);
void func_80006E2C(void *);
void func_80007B08(void *);
void func_8000D718(void *, void *);
#ifdef TARGET_PC
/* PC: port_decls.h declares D_80050800, D_80070458, D_80073EB0 and D_8007C3D0, so the PC copy of this line leaves them
 * out. */
extern u8 D_800517D0[], D_800651A0[];
#else
extern u8 D_80050800[], D_800517D0[], D_800651A0[], D_80070458[], D_80073EB0[], D_8007C3D0[];
#endif
extern s16 D_800566E0[], D_8006A2A4[], D_8007DFB0[], D_8007DFBC[];
extern s8 D_800706A4[];
extern u16 D_8007C318[];
#ifndef TARGET_PC /* on PC, port_decls.h declares D_8007C438 */
extern void *D_8007C438[];
#endif
void func_8000CD84(s16 index) {
    u16 *count;
    u16 *cbase;
    void **buffer;
    void **bbase;
    u32 i;
#ifdef TARGET_PC
    /* PC: dst walks display records, Nw2Descr4BA8 (common.h), 0x50 bytes each. */
    u8 *src;
    Nw2Descr4BA8 *dst;
#else
    u8 *src, *dst;
#endif
    u32 off;
    i = 0;
    off = (s16)index * 23;
    cbase = D_8007C318;
    count = cbase + off;
#ifdef TARGET_PC
    /* PC: D_8007C438 is a table of 4 x 23 addresses (port_decls.h); the walk below takes it as one row of 92. */
    bbase = &D_8007C438[0][0];
#else
    bbase = D_8007C438;
#endif
    buffer = bbase + off;
    D_8006A2A4[index] = -1;
    D_8007DFBC[index] = -1;
    D_8007DFB0[index] = -1;
    D_800566E0[index] = -1;
    do {
        if (*buffer) { releaseHeapBlock(*buffer); *buffer = 0; *count = 0; }
        count++; i++; buffer++;
    } while (i < 23);
    i = 0;
#ifdef TARGET_PC
    /* PC: the player's slot of 23 display records (port_decls.h). */
    dst = D_80073EB0[index];
#else
    dst = D_80073EB0 + index * 0x3F4;
#endif
    src = D_800651A0 + index * 0x13C4;
#ifdef TARGET_PC
    /* PC: dst steps by one record; src steps by one 0xDC-byte object (Nw2SceneObj keeps its N64 size, common.h). */
    do { func_8000520C(src, dst); dst++; i++; src += sizeof(Nw2SceneObj); } while (i < 23);
#else
    do { func_8000520C(src, dst); dst += 0x2C; i++; src += 0xDC; } while (i < 23);
#endif
#ifdef TARGET_PC
    /* PC: the player's picture pair is a Nw2TexPair (common.h), 16 bytes on PC. */
    if (D_800706A4[index] == 1) func_80006E2C(&D_80070458[index]);
#else
    if (D_800706A4[index] == 1) func_80006E2C(D_80070458 + index * 8);
#endif
#ifdef TARGET_PC
    /* PC: the player's slot of display records of D_80050800 (port_decls.h); the objects keep their N64 size. */
    func_8000D718(D_800517D0 + index * 0x13C4, D_80050800[index]);
#else
    func_8000D718(D_800517D0 + index * 0x13C4, D_80050800 + index * 0x3F4);
#endif
#ifdef TARGET_PC
    /* PC: the player's arena (Nw2MeshArena, 0x20 bytes on PC). */
    func_80007B08(&D_8007C3D0[index]);
#else
    func_80007B08(D_8007C3D0 + index * 16);
#endif
}
