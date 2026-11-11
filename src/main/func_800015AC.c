/* @header
 * func_800015AC
 * VRAM 0x800015AC | ROM 0x21AC | size 0x60
 * asm: asm/nonmatchings/main/func_800015AC.s
 */
#include "common.h"

void *func_80001694(void);
#ifdef TARGET_PC
/* PC: the type of func_80001888's definition, which returns nothing. */
void func_80001888(void *);
#else
s32 func_80001888(void *);
#endif

/* Attach the object's scratch/work block (allocating it on first use), record the
 * new mode byte at +0x1B, reset the block's +8, point it back at the object at +4,
 * copy the object's +0x10 into the block's +0x34, then refresh the object. */
#ifdef TARGET_PC
/* PC: the object and its work block keep their N64 layout (Nw2SceneObj and Nw2SceneWork in common.h), so their 4-byte
 * address fields hold handles (port.h's PTR_TO_SLOT) instead of addresses. This version stores the handles of the
 * work block and of the object, reads the object's work block back with SLOT_TO_PTR, and copies the handle of the
 * object's display list into the block as it is. */
void func_800015AC(void *object, s8 mode) {
    Nw2SceneObj *obj = object;
    Nw2SceneWork *work;

    work = SLOT_TO_PTR(obj->work);
    if (work == NULL) {
        work = func_80001694();
        obj->work = PTR_TO_SLOT(work);
    }
    obj->vtxCount = mode;
    work->next = 0;
    work->owner = PTR_TO_SLOT(obj);
    work->dl = obj->dl;
    func_80001888(object);
}
#else
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
#endif
