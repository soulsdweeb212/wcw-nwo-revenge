/* @header
 * submitGraphicsTask  (originally func_800028B4)
 * VRAM 0x800028B4 | ROM 0x34B4 | size 0x2EC
 * asm: asm/nonmatchings/main/func_800028B4.s
 */
#include "common.h"

/* Finish the caller's display list, then fill in and dispatch an RSP graphics
 * task into the next of the four rotating task buffers. arg2 adds a full-screen
 * fill (using arg0->clear / arg0->buffer), arg3 selects the microcode/data pair. */
typedef struct { u32 w0, w1; } Nw2Gfx;
typedef struct { s32 id; u32 buffer; u16 f8, clear; } Nw2FrameBuffer;
typedef struct {
    u32 type, flags;
    void *boot; u32 bootSize;
    void *ucode; u32 ucodeSize;
    void *data; u32 dataSize;
    void *stack; u32 stackSize;
    void *output, *outputSize, *dl; u32 dlSize;
    void *yield; u32 yieldSize;
} Nw2OSTask;
extern s16 D_8002EEBC;
extern Nw2Gfx *D_80044590[];
extern void *D_800445A0, *D_800445A4, *D_800445A8;
extern u8 func_8002BC40[], D_8002BD10[], D_8002C970[], D_8002DD00[], D_8003A870[], D_8003AC90[];
void func_8001C7E0(void *, s32);
void func_800005D0(void *);

#define EmitCommand(a, b) { Nw2Gfx *g = dl++; g->w0 = (a); g->w1 = (u32)(b); }

void submitGraphicsTask(Nw2FrameBuffer *arg0, Nw2Gfx *dl, s16 arg2, s16 arg3) {
    u32 *task = (u32 *)((u8 *)D_80044590[D_8002EEBC] + 0x4000);
    Nw2OSTask *t = (Nw2OSTask *)((u8 *)D_80044590[D_8002EEBC] + 0x4010);
    s32 id = arg0->id;
    u32 i;

    if (arg2) {
        EmitCommand(0xE7000000, 0);
        if (arg0->clear) {
            EmitCommand(0xFF1001DF, arg0->buffer - 0x80000000);
            EmitCommand(0xE3000A01, 0x300000);
            EmitCommand(0xE200001C, 0);
            EmitCommand(0xF7000000, 0x10001);
            for (i = 0; i < 60; i++) {
                EmitCommand(0xF677C000 | ((((i + 1) * 4 - 1) & 0x3FF) << 2), (i << 4) & 0xFF0);
            }
            EmitCommand(0xE7000000, 0);
        }
    }
    EmitCommand(0xE9000000, 0);
    EmitCommand(0xDF000000, 0);
    t->type = 1; t->flags = 2;
    t->boot = func_8002BC40; t->bootSize = D_8002BD10 - func_8002BC40;
    t->yieldSize = 0xC00; t->output = D_800445A8; t->outputSize = (u8 *)D_800445A8 + 0x10000; t->yield = D_800445A4;
    if (!arg3) { t->ucode = D_8002C970; t->data = D_8003A870; } else { t->ucode = D_8002DD00; t->data = D_8003AC90; }
    t->ucodeSize = 0x1000; t->dataSize = 0x800; t->stackSize = 0x400; t->stack = D_800445A0;
    t->dl = D_80044590[D_8002EEBC]; t->dlSize = (s16)(dl - D_80044590[D_8002EEBC]) * 8;
    task[0] = 0; if (arg2) task[2] = 0x63; else task[2] = 3; task[3] = id;
    func_8001C7E0(&D_80044590[D_8002EEBC], 0x4078);
    func_800005D0(task);
    D_8002EEBC++; D_8002EEBC %= 4;
}
