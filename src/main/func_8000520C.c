/* @header
 * func_8000520C
 * VRAM 0x8000520C | ROM 0x5E0C | size 0xF8
 * asm: asm/nonmatchings/main/func_8000520C.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: releaseHeapBlock takes the block's address (u8 *arg0, releaseHeapBlock.c); the N64 declaration passes it as an
 * s32, which would cut a 64-bit address in half. */
void releaseHeapBlock(u8 *);
#else
s32 releaseHeapBlock(s32);
#endif
s32 func_800015AC(void *, s32);

typedef struct {
    u8 pad0[0x10];
    s32 f10;   /* @0x10: buffer owned by arg0 */
} Holder520C;

typedef struct {
    u8 active;     /* @0x0: block-in-use flag */
    u8 pad1[0xB];
    s32 fC;        /* @0xC */
    s32 f10;       /* @0x10 */
    s32 f14;       /* @0x14 */
    s32 f18;       /* @0x18 */
    s32 f1C;       /* @0x1C */
    u8 pad20[8];
    s32 f28;       /* @0x28: shared-ownership flag */
} ResBlock520C;

/* If the resource block arg1 is active, deactivate it, free arg0's buffer at
 * +0x10 and clear it, run func_800015AC(arg0, 0), then free each of arg1's
 * buffer pointers (+0xC/+0x10/+0x14/+0x18/+0x1C) and clear it. Pointers whose
 * block has the shared-ownership flag +0x28 set are left alone. */
#ifdef TARGET_PC
/* PC: the types of port_decls.h's line. arg1 is a display record (the record func_8000498C fills; the callers
 * func_8000CD84, func_8000D718 and func_8000EDE0 pair the 0xDC-byte objects with the records of D_80073EB0, D_80050800
 * and D_800583F8). Its PC layout is Nw2Descr4BA8 (common.h): the five buffers are 8-byte pointers from +0x10 on, and
 * +0x28 is the arena pointer f28 rather than an s32 flag. So this version reads arg1 through that struct (rec) by name
 * and frees whole addresses. arg0 is the 0xDC-byte object, which keeps its N64 layout (Nw2SceneObj in common.h), so the
 * buffer at +0x10 (Holder520C's f10, the object's display list) holds a handle (port.h's PTR_TO_SLOT): it is turned
 * back into the address with SLOT_TO_PTR, freed, and cleared to 0. */
void func_8000520C(void *arg0, void *arg1) {
    Nw2SceneObj *obj = arg0;
    Nw2Descr4BA8 *rec = arg1;
    void *temp;

    if (rec->pad0[0] != 0) {
        rec->pad0[0] = 0;
        temp = SLOT_TO_PTR(obj->dl);
        if (temp != NULL) {
            releaseHeapBlock(temp);
            obj->dl = 0;
        }
        func_800015AC(obj, 0);
        temp = rec->fC;
        if (temp != NULL) {
            if (rec->f28 == NULL) {
                releaseHeapBlock(temp);
            }
            rec->fC = NULL;
        }
        temp = rec->f10;
        if (temp != NULL) {
            if (rec->f28 == NULL) {
                releaseHeapBlock(temp);
            }
            rec->f10 = NULL;
        }
        temp = rec->f14;
        if (temp != NULL) {
            if (rec->f28 == NULL) {
                releaseHeapBlock(temp);
            }
            rec->f14 = NULL;
        }
        temp = rec->f18;
        if (temp != NULL) {
            releaseHeapBlock(temp);
            rec->f18 = NULL;
        }
        temp = rec->f1C;
        if (temp != NULL) {
            releaseHeapBlock(temp);
            rec->f1C = NULL;
        }
    }
}
#else
void func_8000520C(Holder520C *arg0, ResBlock520C *arg1) {
    s32 temp;

    if (arg1->active != 0) {
        arg1->active = 0;
        temp = arg0->f10;
        if (temp != 0) {
            releaseHeapBlock(temp);
            arg0->f10 = 0;
        }
        func_800015AC(arg0, 0);
        temp = arg1->fC;
        if (temp != 0) {
            if (arg1->f28 == 0) {
                releaseHeapBlock(temp);
            }
            arg1->fC = 0;
        }
        temp = arg1->f10;
        if (temp != 0) {
            if (arg1->f28 == 0) {
                releaseHeapBlock(temp);
            }
            arg1->f10 = 0;
        }
        temp = arg1->f14;
        if (temp != 0) {
            if (arg1->f28 == 0) {
                releaseHeapBlock(temp);
            }
            arg1->f14 = 0;
        }
        temp = arg1->f18;
        if (temp != 0) {
            releaseHeapBlock(temp);
            arg1->f18 = 0;
        }
        temp = arg1->f1C;
        if (temp != 0) {
            releaseHeapBlock(temp);
            arg1->f1C = 0;
        }
    }
}
#endif
