/* @header
 * func_800B97CC
 * VRAM 0x800B97CC | ROM 0x65F3C | size 0x1A4
 * asm: asm/nonmatchings/code_80090000/func_800B97CC.s
 */
#include "common.h"


typedef struct { u16 a, b, c, d; } R;
extern R D_800D2900[];
#ifdef TARGET_PC
/* PC: D_800DCFD8 is the cartridge request (libultra's OSIoMesg) of the save-memory transfers, which the N64 code fills
 * through labels of its fields (D_800DCFDA its priority, D_800DCFDC its queue, D_800DCFE0 the RAM address, D_800DCFE4
 * the device address, D_800DCFE8 the size). Those labels have no PC symbol, and on PC the request is port.h's
 * PortIoMesg, whose addresses are pointers, so the code fills it by field name. D_800DCFD4 holds the address of the
 * PI handle that func_80000A40 returns, and D_800DCFC4 the address of the queue that func_8000424C returns, so both
 * are pointers. The SDK and game functions are declared with the port's and their definitions' types (the message
 * pointers as void *, as func_80009990 and initializeResourceStream declare them). */
extern PortIoMesg D_800DCFD8;
extern u8 D_800DCFF8[];
extern u8 *D_800DCFB8;
extern void *D_800DCFD4;
extern s32 *D_800DCFC4;
extern s32 D_800DCFBC;
void osInvalDCache(void *, s32);
s32 osEPiStartDma(void *, void *, s32);
s32 osRecvMesg(void *, void *, s32);
s32 *func_8000424C(void);
s32 func_800B947C(void);
void func_80004290(void);

static inline void rd(s32 i) {
    u32 o;
    u32 n;
    u8 *q;
    u32 p;
    s32 sp10;

    o = D_800D2900[i].a;
    n = D_800D2900[i].b;
    q = D_800DCFB8 + o;
    p = o + 0x20;
    osInvalDCache(q, n);
    D_800DCFD8.retQueue = D_800DCFF8;
    D_800DCFD8.pri = 0;
    D_800DCFD8.devAddr = p;
    D_800DCFD8.dramAddr = q;
    D_800DCFD8.size = n;
    while (osEPiStartDma(D_800DCFD4, &D_800DCFD8, 0) != 0) {
    }
    osRecvMesg(D_800DCFF8, &sp10, 1);
}
#else
extern u8 D_800DCFD8[], D_800DCFF8[];
extern u8 D_800DCFDA;
extern u8 *D_800DCFDC, *D_800DCFE0, *D_800DCFB8;
extern s32 D_800DCFD4, D_800DCFE4, D_800DCFE8, D_800DCFBC, D_800DCFC4;

static inline void rd(s32 i) {
    u32 o;
    u32 n;
    u8 *q;
    u32 p;
    s32 sp10;

    o = D_800D2900[i].a;
    n = D_800D2900[i].b;
    q = D_800DCFB8 + o;
    p = o + 0x20;
    osInvalDCache(q, n);
    D_800DCFDC = D_800DCFF8;
    D_800DCFDA = 0;
    D_800DCFE4 = p;
    D_800DCFE0 = q;
    D_800DCFE8 = n;
    while (osEPiStartDma(D_800DCFD4, D_800DCFD8, 0) != 0) {
    }
    osRecvMesg(D_800DCFF8, &sp10, 1);
}
#endif

s32 func_800B97CC(s32 i) {
    if (D_800D2900[i].d != 0) {
        D_800DCFC4 = func_8000424C();
        if ((D_800DCFBC = func_800B947C()) == 0) {
            rd(i);
        }
        func_80004290();
        return D_800DCFBC;
    }
    rd(i);
    return 0;
}
