/* @header
 * func_80002CC4
 * VRAM 0x80002CC4 | ROM 0x38C4 | size 0x3D4
 * asm: asm/nonmatchings/main/func_80002CC4.s
 */
#include "common.h"

#ifdef TARGET_PC
/* On PC a command is port.h's 16-byte Gfx, as in buildSceneSetupDisplayList, func_80002454 and submitGraphicsTask,
 * which pass the list's end through gfx. */
typedef Gfx Gfx2CC4;
#else
typedef struct { u32 w0, w1; } Gfx2CC4;
#endif
typedef struct { s32 key; } Obj2CC4;
typedef struct { u32 fb0; u32 fb1; } Task2CC4;

#ifndef TARGET_PC /* on PC, port_decls.h declares D_8002EEB0 (the addresses of the three framebuffers) */
extern u32 D_8002EEB0[];
#endif
extern u16 D_8002EEC8;
extern s16 D_8002EECA;
extern s32 D_8002EEC0;
extern s32 D_80046800;
extern u8 D_80046768[], D_800467C0[], D_800467E0[];
#ifndef TARGET_PC /* on PC, port_decls.h declares D_800467FC */
extern Task2CC4 *D_800467FC;
#endif
extern s16 D_80047066;
#ifndef TARGET_PC /* on PC, port_decls.h declares D_80047070 */
extern Obj2CC4 *D_80047070[][512];
#endif
s32 osRecvMesg(void *, void *, s32);
s32 osSendMesg(void *, void *, s32);
void func_80002324(s16);
s32 func_80002454(Gfx2CC4 **, s16, s16);
Gfx2CC4 *buildSceneSetupDisplayList(Task2CC4 *, s32);
void submitGraphicsTask(Task2CC4 *, Gfx2CC4 *, s32, s16);
void func_80003098(void);
void func_800032FC(void);
void osWritebackDCacheAll(void);
void osViSetYScale(f32);
void osViBlack(s32);

#ifdef TARGET_PC
/* PC: a message in the game's queues is 4 bytes (port.h), so each message on D_80046768 is a handle (PTR_TO_SLOT) of
 * the address of an s16 type: the done message of a render-list record (its task's msg, Nw2ScTask in common.h, which
 * func_80001260 sets), or a retrace or reset message of the port's stand-in for the scheduler. The switch reads the
 * type through the address that the handle stands for. */
#define HANDLE_MSG()                       \
    switch (*(s16 *)SLOT_TO_PTR(msg[0])) { \
    case 1:                                \
        ticks++;                           \
        break;                             \
    case 2:                                \
        count--;                           \
        break;                             \
    case 4:                                \
        count += 32;                       \
        osViSetYScale(1.0f);               \
        osViBlack(1);                      \
        D_8002EEC0 = 1;                    \
        func_800032FC();                   \
        func_80003098();                   \
        break;                             \
    }
#else
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
        osViSetYScale(1.0f);             \
        osViBlack(1);                \
        D_8002EEC0 = 1;                  \
        func_800032FC();                 \
        func_80003098();                 \
        break;                           \
    }
#endif

void func_80002CC4(void)
{
#ifdef TARGET_PC
    u32 msg[2]; /* PC: the port's osRecvMesg writes a 4-byte message, a handle (HANDLE_MSG above) */
#else
    s16 *msg[2];
#endif
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

#ifdef TARGET_PC
    msg[0] = 0; /* PC: a handle; 0 stands for NULL */
#else
    msg[0] = NULL;
#endif
    for (;;) {
        osRecvMesg(D_800467C0, NULL, 1);
        task = D_800467FC;
        if (task != NULL) {
            cur = D_8002EEC8;
            buf = (u16)(cur + 1) % 3;
#ifdef TARGET_PC
            /* PC: the frame record keeps its N64 layout, so its two 4-byte fields hold handles of the framebuffers'
             * addresses (port.h's PTR_TO_SLOT); buildSceneSetupDisplayList and submitGraphicsTask turn them back. */
            task->fb0 = PTR_TO_SLOT(D_8002EEB0[cur]);
            fb = PTR_TO_SLOT(D_8002EEB0[buf]);
#else
            task->fb0 = D_8002EEB0[cur];
            fb = D_8002EEB0[buf];
#endif
            D_8002EEC8 = buf;
            task->fb1 = fb;
            func_80002324(D_8002EECA);
        } else {
            ticks = (D_80046800 == 0);
            while (!ticks) {
                osRecvMesg(D_80046768, msg, 1);
                HANDLE_MSG();
            }
        }
        osSendMesg(D_800467E0, NULL, 1);
        if (task == NULL) {
            continue;
        }
        while (osRecvMesg(D_80046768, msg, 0) != -1) {
            HANDLE_MSG();
        }
        ticks = 0;
        count = 0;
        osWritebackDCacheAll();
        index = 0;
        do {
            while ((index < D_80047066) & (count < 4)) {
                Gfx2CC4 *gfx;
                bank = D_8002EECA;
                gfx = buildSceneSetupDisplayList(task, index == 0);
#ifdef TARGET_PC
                /* PC: port_decls.h declares the draw lists as plain pointers (void *); each holds a work block's
                 * address, whose first word (Obj2CC4's key, Nw2SceneWork's kind) is read here. */
                key = ((Obj2CC4 *)D_80047070[(s16)bank][index])->key;
#else
                key = D_80047070[(s16)bank][index]->key;
#endif
                next = (s16)func_80002454(&gfx, bank, index);
                submitGraphicsTask(task, gfx, next >= D_80047066, key);
                count++;
                index = next;
            }
            osRecvMesg(D_80046768, msg, 1);
            HANDLE_MSG();
        } while ((index < D_80047066) | (ticks < 2) || count);
        D_8002EECA ^= 1;
    }
}
#ifdef TARGET_PC
/* PC: the render thread's work for one frame (port.h's port_render_frame). No thread runs func_80002CC4 on PC; at a
 * frame's hand-off the port calls this instead, while the game waits. It does what the loop above does for a frame,
 * without the queues: rotate the framebuffers, take the bank's draw lists (func_80002324), build the frame's tasks one
 * after another and submit each (submitGraphicsTask, whose list reaches the port through func_800005D0), then flip
 * the bank. The N64 keeps up to four tasks in flight and waits for retraces between them; on PC the port copies each
 * task's list as it comes and paces the frames itself. A hand-off without a frame (D_800467FC NULL) draws nothing. */
void port_render_frame(void) {
    Task2CC4 *task = D_800467FC;
    u16 cur;
    u16 buf;
    u16 bank;
    s16 index;
    s32 next;
    s32 key;

    if (task == NULL) {
        return;
    }
    cur = D_8002EEC8;
    buf = (u16)(cur + 1) % 3;
    task->fb0 = PTR_TO_SLOT(D_8002EEB0[cur]);
    task->fb1 = PTR_TO_SLOT(D_8002EEB0[buf]);
    D_8002EEC8 = buf;
    func_80002324(D_8002EECA);
    index = 0;
    while (index < D_80047066) {
        Gfx2CC4 *gfx;

        bank = D_8002EECA;
        gfx = buildSceneSetupDisplayList(task, index == 0);
        key = ((Obj2CC4 *)D_80047070[(s16)bank][index])->key;
        next = (s16)func_80002454(&gfx, bank, index);
        submitGraphicsTask(task, gfx, next >= D_80047066, key);
        index = next;
    }
    D_8002EECA ^= 1;
}
#endif
