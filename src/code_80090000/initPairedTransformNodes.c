#include "common.h"

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
