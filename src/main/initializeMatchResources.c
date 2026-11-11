/* @header
 * initializeMatchResources  (originally func_80011BB4)
 * VRAM 0x80011BB4 | ROM 0x127B4 | size 0x568
 * asm: asm/nonmatchings/main/initializeMatchResources.s
 */
#include "common.h"

/* initializeMatchResources: loads the arena/match resource sets through
 * func_80007020, allocates and fills the eight-sprite vertex strip, creates the
 * 26 sprite animation entries, then builds the four player objects
 * (D_8005A3C0) and four secondary objects (D_8005A730), each with three 0x200
 * byte animation buffers. */

extern u16 D_80036D40[], D_80036D44[], D_80036D48[], D_80036D4C[], D_80036D54[], D_80036D5C[], D_80036D64[], D_80036D6C[], D_80036D74[], D_80036D7C[], D_80036D84[], D_80036D8C[], D_80036D90[], D_80036D94[], D_80036D9C[], D_80036DA4[], D_80036DB4[], D_80036DC4[], D_80036DCC[], D_80036DD4[], D_80036DDC[], D_80036DE0[];
#ifndef TARGET_PC /* on PC, port_decls.h declares these as arrays of display records (Nw2Descr4BA8) */
extern u8 D_8005AAE8[], D_8005AB48[], D_8005ABA8[], D_8005AC30[], D_8005ACB8[], D_8005AD40[], D_8005ADC8[], D_8005AE50[], D_8005AEB0[], D_8005AFE8[], D_8005B070[], D_8005B110[];
#endif
#ifndef TARGET_PC /* on PC, port_decls.h declares these as pointers (the display lists func_80007020 returns) */
extern s32 D_8005AAE0, D_8005AB40, D_8005ABA0, D_8005AC2C, D_8005ACB4, D_8005AD3C, D_8005ADC4, D_8005AE4C, D_8005AEA8, D_8005AFE4, D_8005B06C, D_8005B0F8[];
#endif
typedef struct { u8 bytes[16]; } Vtx11B;
#ifndef TARGET_PC /* on PC, port_decls.h declares D_8005B218 */
extern Vtx11B *D_8005B218;
#endif
#ifndef TARGET_PC /* on PC, port_decls.h declares D_8005B220 (Nw2TexPair); its label D_8005B224 has no PC symbol */
extern u8 D_8005B220[];
extern s32 D_8005B224[][2];
#endif
extern u8 D_8005A3C0[], D_8005A730[];
#ifndef TARGET_PC /* on PC, port_decls.h declares D_8005AAA0 (Nw2AnimatedCi4State); its label D_8005AAAC is gone */
extern void *D_8005AAA0[][4];
extern s8 D_8005AAAC[][16];
#endif
extern s8 D_80070478[][2], D_80070479[][2], D_8007E010[][0x5C], D_8007E012[][0x5C], D_8007E013[][0x5C];
extern s32 D_8007E020[][23], D_8007E024[][23], D_8007E028[][23];
extern f32 D_8007E014[][23], D_8007E018[][23], D_8007E01C[][23];
#ifdef TARGET_PC
/* PC: func_80007020 returns the display list it built, a pointer (Gfx7020 *, a type of its own file), and takes the
 * record count as an s16; its pointer parameters stay void * here. */
void *func_80007020(void *, void *, void *, s16);
#else
s32 func_80007020(void *, void *, void *, s8);
#endif
void *allocateHeap(u32);
void func_80007920(void *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_8000670C(void *, s16, s16);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800079D8, which takes the palette as a u16 * */
void func_800079D8(s32, s32);
#endif
void initializeTransformNode(void *, s32, f32, f32, f32);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_80007874, which takes the display list as a pointer */
void func_80007874(void *, void *, s32, s32);
#endif
void func_80001544(void *);

void initializeMatchResources(void) {
    u32 i, j;
    Vtx11B *vert, *vertexBuf;
    D_8005AAE0 = func_80007020(D_8005AAE8, D_80036D40, D_80036D44, 2);
    D_8005AB40 = func_80007020(D_8005AB48, D_80036D40, D_80036D48, 2);
    D_8005ABA0 = func_80007020(D_8005ABA8, D_80036D4C, D_80036D54, 3);
    D_8005AC2C = func_80007020(D_8005AC30, D_80036D5C, D_80036D64, 3);
    D_8005ACB4 = func_80007020(D_8005ACB8, D_80036D6C, D_80036D74, 3);
    D_8005AD3C = func_80007020(D_8005AD40, D_80036D7C, D_80036D84, 3);
    D_8005ADC4 = func_80007020(D_8005ADC8, D_80036D94, D_80036D9C, 3);
    D_8005AE4C = func_80007020(D_8005AE50, D_80036D8C, D_80036D90, 2);
    D_8005AEA8 = func_80007020(D_8005AEB0, D_80036DA4, D_80036DB4, 7);
    D_8005AFE4 = func_80007020(D_8005AFE8, D_80036DC4, D_80036DCC, 3);
    D_8005B06C = func_80007020(D_8005B070, D_80036DC4, D_80036DD4, 3);
    for (i = 0; i < 6; i++)
#ifdef TARGET_PC
        /* PC: D_8005B110 is an array of display records (Nw2Descr4BA8), so record i is D_8005B110[i], not +i * 0x2C. */
        D_8005B0F8[i] = func_80007020(&D_8005B110[i], D_80036DDC, &D_80036DE0[i], 1);
#else
        D_8005B0F8[i] = func_80007020(D_8005B110 + i * 0x2C, D_80036DDC, &D_80036DE0[i], 1);
#endif
    vertexBuf = allocateHeap(0x40);
    D_8005B218 = vertexBuf;
    vert = vertexBuf;
    func_80007920(vert++, -40, -40, 16, 1008, 0, 0, 0, 255);
    func_80007920(vert++, 40, -40, 1007, 1008, 0, 0, 0, 255);
    func_80007920(vert++, -40, 40, 16, 15, 0, 0, 0, 255);
    func_80007920(vert++, 40, 40, 1007, 15, 0, 0, 0, 255);
    for (i = 0; i < 26; i++) {
        if (i < 12)
#ifdef TARGET_PC
            /* PC: D_8005B220 is an array of picture pairs (Nw2TexPair, 16 bytes), so pair i is D_8005B220[i]. */
            func_8000670C(&D_8005B220[i], i + 999, i + 986);
#else
            func_8000670C(D_8005B220 + i * 8, i + 999, i + 986);
#endif
        else
#ifdef TARGET_PC
            func_8000670C(&D_8005B220[i], i + 999, 998); /* PC: as above */
#else
            func_8000670C(D_8005B220 + i * 8, i + 999, 998);
#endif
#ifdef TARGET_PC
        /* PC: the label D_8005B224 is pair i's palette, which the PC reads by name (a pointer). */
        func_800079D8(D_8005B220[i].pal, 1);
#else
        func_800079D8(D_8005B224[i][0], 1);
#endif
    }
    for (i = 0; i < 4; i++) {
        u8 *obj = D_8005A3C0 + i * 0xDC;
        initializeTransformNode(obj, 3, 0.0f, 0.0f, 0.0f);
        func_80007874(obj, D_8005AAE8, D_8005AAE0, 0);
        func_80001544(obj);
#ifdef TARGET_PC
        /* PC: the object's +0x14 holds a handle of its work block (Nw2SceneObj, Nw2SceneWork in common.h); bit 0x80 of
         * the block's kind hides it. */
        ((Nw2SceneWork *)SLOT_TO_PTR(((Nw2SceneObj *)obj)->work))->kind |= 0x80;
#else
        **(s32 **)(obj + 0x14) |= 0x80;
#endif
        D_8007E010[i][0] = 0;
        D_8007E013[i][0] = -1;
        D_8007E012[i][0] = -1;
        D_8007E020[i][0] = 0;
        D_8007E024[i][0] = 0;
        D_8007E028[i][0] = 0;
        D_8007E014[i][0] = 0.0f;
        D_8007E018[i][0] = 0.0f;
        D_8007E01C[i][0] = 0.0f;
#ifdef TARGET_PC
        /* PC: the animation-command record by field name (Nw2AnimatedCi4State); each buffer holds the N64's 0x200 / 8
         * commands, at sizeof(Gfx) bytes each. */
        D_8005AAA0[i].slot = 0;
        for (j = 0; j < 3; j++)
            D_8005AAA0[i].buffers[j] = allocateHeap(0x200 / 8 * sizeof(Gfx));
#else
        D_8005AAAC[i][0] = 0;
        for (j = 0; j < 3; j++)
            D_8005AAA0[i][j] = allocateHeap(0x200);
#endif
    }
    for (i = 0; i < 4; i++) {
        u8 *obj = D_8005A730 + i * 0xDC;
        initializeTransformNode(obj, 3, 0.0f, 0.0f, 0.0f);
        func_80007874(obj, D_8005AAE8, D_8005AAE0, 0);
        func_80001544(obj);
#ifdef TARGET_PC
        ((Nw2SceneWork *)SLOT_TO_PTR(((Nw2SceneObj *)obj)->work))->kind |= 0x80; /* PC: as above */
#else
        **(s32 **)(obj + 0x14) |= 0x80;
#endif
        D_80070478[i][0] = -1;
        D_80070479[i][0] = 2;
    }
}
