#include "common.h"

extern u8 D_00CEC610;
extern u8 D_00CE9F00;
extern u8 D_00E3B300;
extern u8 D_00E35070;
extern u8 D_80100000;
extern u8 D_8002FECC;
extern u8 D_80030214;
extern s32 D_800482D0;
extern s32 D_800482D4;
extern s16 D_800482DA;
typedef struct {
    s32 f0; s32 f4; void *f8; s32 fC; void *f10; s32 f14; s32 f18;
    void *f1C; void *f20; void *f24; s32 f28; s32 f2C; s32 f30; s32 f34;
    s32 f38; s32 f3C; s32 f40; s32 f44;
} Nw2AudioInit;
void *allocateHeap(u32);
void readRomSynchronousChunks(void *, void *, s32);
void *func_80000610(void);
void func_80003418(s32);
void initializeAudioSystem(Nw2AudioInit *);
void func_800137F0(s32, s16);
void func_80014004(s32, void *);

void func_80003120(void) {
    s32 size, start;
    void *buf;
    Nw2AudioInit cfg;

    size = (s32)&D_00CEC610;
    start = (s32)&D_00CE9F00;
    size = size - start;
    buf = allocateHeap(size);
    D_800482D0 = (s32)buf;
    readRomSynchronousChunks(&D_00CE9F00, buf, size);

    size = (s32)&D_00E3B300;
    start = (s32)&D_00E35070;
    size = size - start;
    buf = allocateHeap(size);
    D_800482D4 = (s32)buf;
    readRomSynchronousChunks(&D_00E35070, buf, size);

    cfg.f0 = 0;
    cfg.f4 = 0x18;
    cfg.f8 = func_80000610();
    cfg.fC = 0x50;
    cfg.f10 = &D_80100000;
    cfg.f14 = 0x47000;
    cfg.f18 = D_800482D0;
    cfg.f1C = &D_00CEC610;
    cfg.f20 = &D_8002FECC;
    cfg.f24 = &D_80030214;
    cfg.f34 = 0x7080;
    cfg.f30 = 0x100;
    cfg.f38 = 0x1000;
    cfg.f3C = 1;
    cfg.f40 = 0x84;
    cfg.f44 = 0x500;
    initializeAudioSystem(&cfg);

    func_80003418(0x7F);
    D_800482DA = 0x7FFF;
    func_800137F0(1, 0x7FFF);
    func_80014004(D_800482D4, &D_00E3B300);
}
