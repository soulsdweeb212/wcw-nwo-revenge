#include "common.h"

void *func_80001694(void);
s32 func_80001888(void *);

/* Attach the object's scratch/work block (allocating it on first use), record the
 * new mode byte at +0x1B, reset the block's +8, point it back at the object at +4,
 * copy the object's +0x10 into the block's +0x34, then refresh the object. */
void func_800015AC(void *object, s8 mode) {
    void *work;

    work = *(void **)((s8 *)object + 0x14);
    if (work == NULL) {
        work = func_80001694();
        *(void **)((s8 *)object + 0x14) = work;
    }
    *(s8 *)((s8 *)object + 0x1B) = mode;
    *(s32 *)((s8 *)work + 8) = 0;
    *(void **)((s8 *)work + 4) = object;
    *(s32 *)((s8 *)work + 0x34) = (s32) *(s32 *)((s8 *)object + 0x10);
    func_80001888(object);
}
