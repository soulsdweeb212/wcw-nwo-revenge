/* @header
 * func_80002CC4
 * VRAM 0x80002CC4 | ROM 0x38C4 | size 0x3D4
 * asm: asm/nonmatchings/main/func_80002CC4.s
 */
#include "common.h"

typedef struct { u32 w0, w1; } Gfx2CC4;
typedef struct { s32 key; } Obj2CC4;
typedef struct { u32 fb0; u32 fb1; } Task2CC4;

extern u32 D_8002EEB0[];
extern u16 D_8002EEC8;
extern s16 D_8002EECA;
extern s32 D_8002EEC0;
extern s32 D_80046800;
extern u8 D_80046768[], D_800467C0[], D_800467E0[];
extern Task2CC4 *D_800467FC;
extern s16 D_80047066;
extern Obj2CC4 *D_80047070[][512];
s32 func_8001C990(void *, void *, s32);
s32 func_8001CAC0(void *, void *, s32);
void func_80002324(s16);
s32 func_80002454(Gfx2CC4 **, s16, s16);
Gfx2CC4 *buildSceneSetupDisplayList(Task2CC4 *, s32);
void submitGraphicsTask(Task2CC4 *, Gfx2CC4 *, s32, s16);
void func_80003098(void);
void func_800032FC(void);
void func_8001C860(void);
void func_80021090(f32);
void func_80021130(s32);

#define HANDLE_MSG()                     \
    switch (*msg[0]) {                   \
    case 1:                              \
        ticks++;                         \
        break;                           \
    case 2:                              \
        count--;                         \
        break;                           \
    case 4:                              \
        count += 32;                     \
        func_80021090(1.0f);             \
        func_80021130(1);                \
        D_8002EEC0 = 1;                  \
        func_800032FC();                 \
        func_80003098();                 \
        break;                           \
    }

void func_80002CC4(void)
{
    s16 *msg[2];
    Task2CC4 *task;
    u16 ticks;
    u16 count;
    s16 index;
    s32 next;
    u16 cur;
    u16 buf;
    u16 bank;
    s32 key;
    u32 fb;

    msg[0] = NULL;
    for (;;) {
        func_8001C990(D_800467C0, NULL, 1);
        task = D_800467FC;
        if (task != NULL) {
            cur = D_8002EEC8;
            buf = (u16)(cur + 1) % 3;
            task->fb0 = D_8002EEB0[cur];
            fb = D_8002EEB0[buf];
            D_8002EEC8 = buf;
            task->fb1 = fb;
            func_80002324(D_8002EECA);
        } else {
            ticks = (D_80046800 == 0);
            while (!ticks) {
                func_8001C990(D_80046768, msg, 1);
                HANDLE_MSG();
            }
        }
        func_8001CAC0(D_800467E0, NULL, 1);
        if (task == NULL) {
            continue;
        }
        while (func_8001C990(D_80046768, msg, 0) != -1) {
            HANDLE_MSG();
        }
        ticks = 0;
        count = 0;
        func_8001C860();
        index = 0;
        do {
            while ((index < D_80047066) & (count < 4)) {
                Gfx2CC4 *gfx;
                bank = D_8002EECA;
                gfx = buildSceneSetupDisplayList(task, index == 0);
                key = D_80047070[(s16)bank][index]->key;
                next = (s16)func_80002454(&gfx, bank, index);
                submitGraphicsTask(task, gfx, next >= D_80047066, key);
                count++;
                index = next;
            }
            func_8001C990(D_80046768, msg, 1);
            HANDLE_MSG();
        } while ((index < D_80047066) | (ticks < 2) || count);
        D_8002EECA ^= 1;
    }
}
