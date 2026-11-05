/* @header
 * osViSetMode  (originally func_80020ED0)
 * VRAM 0x80020ED0 | ROM 0x21AD0 | size 0x4C
 * asm: asm/nonmatchings/main/osViSetMode.s
 */
/* SDK: libultra 2.0I, ultralib src/io/visetmode.c (same code as the SDK source). */
#include "common.h"

extern s32 __osDisableInt(void);
extern void __osRestoreInt(s32);
extern s32 __osSpGetStatus(void);

/* Pending/current VI context (shared view in context.h as Nw2Obj80038860).
 * +0 flags: ready/feature bits (bit 0x20 toggled by osViBlack);
 * +4 aux; +8 pending mode pointer; +C control word copied from the mode. */
typedef struct {
    volatile s16 flags;
    s32 aux;
    void *volatile mode;
    volatile s32 control;
} S80038860;

extern S80038860 *__osViNext;

/* Install a new VI mode into the pending (__osViNext) VI context: store the
 * mode pointer, mark the context ready, then copy the mode's +4 control word.
 * The context update runs with interrupts disabled. */
void osViSetMode(void *mode) {
    s32 savedMask;
    S80038860 *viNext;
    void *installedMode;

    savedMask = __osDisableInt();
    viNext = __osViNext;
    viNext->mode = mode;
    installedMode = viNext->mode;
    viNext->flags = 1;
    viNext->control = *(s32 *)((u8 *)installedMode + 4);
    __osRestoreInt(savedMask);
}
