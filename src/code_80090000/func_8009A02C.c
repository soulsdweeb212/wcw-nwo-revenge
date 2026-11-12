/* @header
 * func_8009A02C
 * VRAM 0x8009A02C | ROM 0x4679C | size 0x84C
 * asm: asm/nonmatchings/code_80090000/func_8009A02C.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: a command is port.h's 16-byte Gfx, which func_80091244 and func_8009126C also write on PC, and an address goes
 * into it as the whole pointer (port.h's DL_ADDR; EMITA below). D_C95F0, D_C95B8 and D_C9764 are the N64 physical
 * addresses (link constants) of D_800C95F0, D_800C95B8 and D_800C9764, which the PC names. D_800E81F8 holds the
 * address of the loaded picture pack, which func_800B64EC takes and returns entries of as pointers (its definition is
 * u8 *func_800B64EC(u8 *, s32)); an s32 would cut it in half. */
typedef Gfx GfxA02C;
#else
typedef struct { u32 w0; u32 w1; } GfxA02C;
#endif

extern s16 D_800C972C[12];
extern s16 D_800C974C[], D_800C974E[];
extern s32 D_800C9784;
#ifdef TARGET_PC
/* PC: see GfxA02C above. */
extern u8 *D_800E81F8;
extern u8 D_800C95F0[], D_800C95B8[], D_800C9764[];

u8 *func_800B64EC(u8 *, s32);
#define EMITA(a, ptr) { GfxA02C *_g = p++; _g->w0 = (a); _g->w1 = DL_ADDR(ptr); }
#else
extern s32 D_800E81F8;
extern u8 D_C95F0[], D_C95B8[], D_C9764[];

u8 *func_800B64EC(s32, s32);
#endif
void func_80091244(GfxA02C **);
void func_8009126C(GfxA02C **);

#define EMIT(a, b) { GfxA02C *_g = p++; _g->w0 = (a); _g->w1 = (b); }
#define PACK(x, y) ((((u32)((x) << 18)) >> 16) | ((y) << 18))

void func_8009A02C(GfxA02C **arg0)
{
    GfxA02C *p;
    s32 idx;
    s32 a;
    s32 b;
    u8 *tex;
    u32 tq;

    p = *arg0;
    idx = D_800C9784;
    a = D_800C974C[idx];
    b = D_800C974E[idx];
    D_800C9784 = idx + 2;
    if (idx + 2 >= 0xC) {
        D_800C9784 = 0;
    }
    if (a < 0) {
        return;
    }
#ifdef TARGET_PC
    /* PC: the addresses as whole pointers (EMITA above). */
    EMITA(0xDE000000, D_800C95F0);
    EMITA(0xDE000000, D_800C95B8);
    func_80091244(&p);
    EMITA(0xFD100000, D_800C9764);
#else
    EMIT(0xDE000000, (u32)D_C95F0);
    EMIT(0xDE000000, (u32)D_C95B8);
    func_80091244(&p);
    EMIT(0xFD100000, (u32)D_C9764);
#endif
    EMIT(0xE8000000, 0);
    EMIT(0xF5000100, 0x07000000);
    EMIT(0xE6000000, 0);
    EMIT(0xF0000000, 0x0703C000);
    EMIT(0xE7000000, 0);
    if (a != 0) {
        tex = func_800B64EC(D_800E81F8, a + 2);
        EMIT(0xE7000000, 0);
#ifdef TARGET_PC
        /* PC: the texture's address as the whole pointer (EMITA above). */
        EMITA(0xFD500000, tex);
#else
        EMIT(0xFD500000, (u32)tex - 0x80000000);
#endif
        EMIT(0xF5500000, 0x07000000);
        EMIT(0xE6000000, 0);
        EMIT(0xF3000000, 0x073FF200);
        EMIT(0xE7000000, 0);
        EMIT(0xF5400800, 0);
        EMIT(0xF2000000, 0x000FC0FC);
        EMIT(0xFB000000, 0xFF00);
        EMIT(0x02180000, PACK(D_800C972C[5], D_800C972C[4]));
        EMIT(0x02180002, PACK(D_800C972C[5], D_800C972C[6]));
        EMIT(0x02180004, PACK(D_800C972C[7], D_800C972C[4]));
        EMIT(0x02180006, PACK(D_800C972C[7], D_800C972C[6]));
        EMIT(0x02140000, 0);
        EMIT(0x02140002, 0x08000000);
        EMIT(0x02140004, 0x800);
        EMIT(0x02140006, 0x08000800);
        EMIT(0x07000206, 0x604);
        tex = func_800B64EC(D_800E81F8, b + 2);
        EMIT(0xE7000000, 0);
#ifdef TARGET_PC
        /* PC: the texture's address as the whole pointer (EMITA above). */
        EMITA(0xFD500000, tex);
#else
        EMIT(0xFD500000, (u32)tex - 0x80000000);
#endif
        EMIT(0xF5500000, 0x07000000);
        EMIT(0xE6000000, 0);
        EMIT(0xF3000000, 0x073FF200);
        EMIT(0xE7000000, 0);
        EMIT(0xF5400800, 0);
        EMIT(0xF2000000, 0x000FC0FC);
        EMIT(0xFB000000, 0xFF000000);
        EMIT(0x02180000, PACK(D_800C972C[9], D_800C972C[8]));
        EMIT(0x02180002, PACK(D_800C972C[9], D_800C972C[10]));
        EMIT(0x02180004, PACK(D_800C972C[11], D_800C972C[8]));
        EMIT(0x02180006, PACK(D_800C972C[11], D_800C972C[10]));
        EMIT(0x02140000, 0x800);
        EMIT(0x02140002, 0x08000800);
        EMIT(0x02140004, 0);
        EMIT(0x02140006, 0x08000000);
        EMIT(0x07000206, 0x604);
    } else {
        tex = func_800B64EC(D_800E81F8, 2);
        EMIT(0xFB000000, 0xC0C00000);
#ifdef TARGET_PC
        /* PC: the texture's address as the whole pointer (EMITA above). */
        EMITA(0xFD500000, tex);
#else
        EMIT(0xFD500000, (u32)tex - 0x80000000);
#endif
        EMIT(0xF5500000, 0x07000000);
        EMIT(0xE6000000, 0);
        EMIT(0xF3000000, 0x073FF200);
        EMIT(0xE7000000, 0);
        EMIT(0xF5400800, 0);
        EMIT(0xF2000000, 0x000FC0FC);
        EMIT(0x02180000, PACK(D_800C972C[1], D_800C972C[0]));
        EMIT(0x02180002, PACK(D_800C972C[1], D_800C972C[2]));
        EMIT(0x02180004, PACK(D_800C972C[3], D_800C972C[0]));
        EMIT(0x02180006, PACK(D_800C972C[3], D_800C972C[2]));
        EMIT(0x02140000, 0);
        EMIT(0x02140002, 0x08000000);
        EMIT(0x02140004, 0x800);
        EMIT(0x02140006, 0x08000800);
        EMIT(0x07000206, 0x604);
    }
    if ((tq & 1) >> 1) {
        D_800C9784 = 0;
    }
    func_8009126C(&p);
    *arg0 = p;
}
