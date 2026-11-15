/* @header
 * func_800A1590
 * VRAM 0x800A1590 | ROM 0x4DD00 | size 0xEC
 * asm: asm/nonmatchings/code_80090000/func_800A1590.s
 */
#include "common.h"


#ifdef TARGET_PC
/* PC: the menus D_800E8230 hold addresses, so they are common.h's Nw2Menu, and the N64's labels inside them have no
 * PC symbol: D_800E8288 is D_800E8230[0].obj (each menu's scene object, which keeps its N64 layout and holds handles,
 * port.h's PTR_TO_SLOT: the renderer walks it, func_80001DC4), D_800E8236 is D_800E8230[0].f6, and the N64's
 * `u8 *D_800E8230` reads D_800E8230[0].items, whose byte +4 is f4. */
extern s16 D_800DC824;
extern u8 D_800DC748[];
extern Nw2Menu D_800E8230[];
#else
typedef struct { void *a; s32 b; void *c; u8 pad[0x12C]; } N;
typedef struct { s16 f; u8 pad[0x136]; } M;
extern s16 D_800DC824;
extern s32 D_800DC74C;
extern u8 D_800DC748[];
extern N D_800E8288[];
extern u8 *D_800E8230;
extern M D_800E8236[];
#endif
void func_8009F9A0(void);
void initializeTransformNode(void *, s32, f32, f32, f32);
#ifdef TARGET_PC
/* PC: initPairedTransformNodes returns the address of the first node of its pair (its definition returns a
 * Nw2Node968A0 *), which an s32 would cut in half. */
void *initPairedTransformNodes(void *, void *);
#else
s32 initPairedTransformNodes(void *, void *);
#endif

void func_800A1590(void) {
#ifndef TARGET_PC /* on PC the menus are reached by index (see above) */
    N *n;
#endif
    s32 i, j;
    D_800DC824 = 0;
    func_8009F9A0();
    initializeTransformNode(D_800DC748, 0, 0.0f, 0.0f, 0.0f);
#ifdef TARGET_PC
    /* PC: D_800DC74C is the label of D_800DC748's +4, the child field of that 0xDC-byte object, which keeps its N64
     * layout and holds handles (Nw2SceneObj, common.h: func_80001DC4 walks it from func_800A1C04), so the field gets
     * the pair's handle, by name. */
    ((Nw2SceneObj *)D_800DC748)->child = PTR_TO_SLOT(initPairedTransformNodes(D_800DC748, &D_800E8230[0].obj));
    /* PC: each menu's scene object as a child of D_800DC748 and the next menu's sibling, by name and as handles (see
     * above); the menus' first f6 from their element lists. */
    for (i = 0; i < 0x18; i++) {
        D_800E8230[i].obj.parent = PTR_TO_SLOT(D_800DC748);
        if (i < 0x17) {
            D_800E8230[i].obj.next = PTR_TO_SLOT(&D_800E8230[i + 1].obj);
        }
    }
    D_800E8230[0].f6 = D_800E8230[0].items->f4;
    for (j = 1; j < 0x18; j++) {
        D_800E8230[j].f6 = 0;
    }
#else
    D_800DC74C = initPairedTransformNodes(D_800DC748, D_800E8288);
    for (i = 0, n = &D_800E8288[1]; i < 0x18; i++) {
        D_800E8288[i].a = D_800DC748;
        if (i < 0x17) {
            D_800E8288[i].c = n;
        }
        n++;
    }
    D_800E8236[0].f = D_800E8230[4];
    for (j = 1; j < 0x18; j++) {
        D_800E8236[j].f = 0;
    }
#endif
}
