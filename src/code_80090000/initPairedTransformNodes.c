/* @header
 * initPairedTransformNodes  (originally func_800968A0)
 * VRAM 0x800968A0 | ROM 0x43010 | size 0x148
 * asm: asm/nonmatchings/code_80090000/initPairedTransformNodes.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: D_800DC570 and D_800DC650 are two 0xDC-byte scene objects (common.h's Nw2SceneObj), which keep their N64 layout
 * on PC, so their address fields hold handles (port.h's PTR_TO_SLOT): the parent, the next sibling, the vertices, the
 * display list and the work block (a Nw2SceneWork, whose +0x24 is bias). The N64 reaches those fields through labels
 * (D_800DC578 to D_800DC584 are +8 to +0x14 of D_800DC570, 0x800DC658 and D_800DC65C to D_800DC664 the same of
 * D_800DC650), which have no PC symbol: the PC sets them by name. D_800C9538 is a display list of the ROM's data, whose
 * PC copy has its name. The callees are declared with their definitions' types (initializeTransformNode.c,
 * func_800015AC.c, func_80001544.c, func_800C1138.c), and the function returns the first object's address as callers
 * declare it (func_800A1590, func_800C1B24). */
extern Nw2SceneObj D_800DC570, D_800DC650;
extern u8 D_800E7558[];
extern Vtx D_800C94F0[];
extern u8 D_800C9538[];
void initializeTransformNode(u8 *, u8, f32, f32, f32);
void func_800015AC(void *, s8);
void func_80001544(void *);
void func_800C1138(void *, void *);

void *initPairedTransformNodes(void *arg0, void *arg1) {
    initializeTransformNode((u8 *)&D_800DC570, 0, 0.0f, 0.0f, 0.0f);
    D_800DC570.next = PTR_TO_SLOT(&D_800DC650);
    D_800DC570.parent = PTR_TO_SLOT(arg0);
    D_800DC570.vtx = PTR_TO_SLOT(D_800C94F0);
    D_800DC570.dl = PTR_TO_SLOT(D_800C9538);
    func_800015AC(&D_800DC570, 1);
    func_80001544(&D_800DC570);
    ((Nw2SceneWork *)SLOT_TO_PTR(D_800DC570.work))->bias = 16384.0f;
    initializeTransformNode((u8 *)&D_800DC650, 5, 0.0f, 0.0f, 0.0f);
    D_800DC650.next = PTR_TO_SLOT(D_800E7558);
    D_800DC650.parent = PTR_TO_SLOT(arg0);
    D_800DC650.vtx = PTR_TO_SLOT(D_800C94F0);
    D_800DC650.dl = PTR_TO_SLOT(D_800C9538);
    func_800015AC(&D_800DC650, 1);
    func_80001544(&D_800DC650);
    ((Nw2SceneWork *)SLOT_TO_PTR(D_800DC650.work))->bias = -16384.0f;
    func_800C1138(arg0, arg1);
    return &D_800DC570;
}
#else
typedef struct {
    void *f0;
    s32 f4;
    void *f8;
    void *fC;
    void *f10;
    void *f14;
} Nw2Node968A0;

extern Nw2Node968A0 D_800DC570;
extern Nw2Node968A0 D_800DC650;
extern void *D_800DC578;
extern void *D_800DC57C;
extern void *D_800DC580;
extern void *D_800DC584;
extern void *D_800DC65C;
extern void *D_800DC660;
extern void *D_800DC664;
extern u8 D_800E7558[];
extern u8 D_800C94F0[];
extern u8 D_800C9538[];

void initializeTransformNode(Nw2Node968A0 *, s32, f32, f32, f32);
void func_800015AC(Nw2Node968A0 *, s32);
void func_80001544(Nw2Node968A0 *);
void func_800C1138(void *, void *);

/* Initializes a pair of sibling transform nodes (D_800DC570/650) sharing the
 * source object arg0 and the same local/callback tables, giving them mirrored
 * 16384/-16384 Y-rotation values, then attaches the pair to arg1. Returns the
 * first node. */
Nw2Node968A0 *initPairedTransformNodes(void *arg0, void *arg1) {
    initializeTransformNode(&D_800DC570, 0, 0.0f, 0.0f, 0.0f);
    D_800DC578 = &D_800DC650;
    D_800DC570.f0 = arg0;
    D_800DC57C = &D_800C94F0;
    D_800DC580 = &D_800C9538;
    func_800015AC(&D_800DC570, 1);
    func_80001544(&D_800DC570);
    *(f32 *)((char *)D_800DC584 + 0x24) = 16384.0f;
    initializeTransformNode(&D_800DC650, 5, 0.0f, 0.0f, 0.0f);
    *(void **)0x800DC658 = &D_800E7558;
    D_800DC650.f0 = arg0;
    D_800DC65C = &D_800C94F0;
    D_800DC660 = &D_800C9538;
    func_800015AC(&D_800DC650, 1);
    func_80001544(&D_800DC650);
    *(f32 *)((char *)D_800DC664 + 0x24) = -16384.0f;
    func_800C1138(arg0, arg1);
    return &D_800DC570;
}
#endif
