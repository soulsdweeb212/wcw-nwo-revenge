/* @header
 * buildObjectChain  (originally func_8000D5F8)
 * VRAM 0x8000D5F8 | ROM 0xE1F8 | size 0x120
 * asm: asm/nonmatchings/main/buildObjectChain.s
 */
#include "common.h"

extern u8 D_80030894[];

#ifdef TARGET_PC
/* PC: MainObj and GenObj are views of the 0xDC-byte objects (Nw2SceneObj in common.h), which keep their N64 layout,
 * so their 4-byte address fields hold handles (port.h's PTR_TO_SLOT): first is object 0's child (+0x4) and sub an
 * object's work block (+0x14). timer is object 19's next (+0x8): clearing it ends the chain. The asserts check the
 * views against Nw2SceneObj. */
typedef struct {
    u8 pad[4];
    u32 first;
    u8 pad2[0x1054];
    s32 timer;
} MainObj;
_Static_assert(offsetof(MainObj, first) == offsetof(Nw2SceneObj, child) &&
                   offsetof(MainObj, timer) == 19 * sizeof(Nw2SceneObj) + offsetof(Nw2SceneObj, next),
               "MainObj must follow Nw2SceneObj");

typedef struct {
    u8 pad[0x14];
    u32 sub;
    u8 flag;
} GenObj;
_Static_assert(offsetof(GenObj, sub) == offsetof(Nw2SceneObj, work) &&
                   offsetof(GenObj, flag) == offsetof(Nw2SceneObj, group),
               "GenObj must follow Nw2SceneObj");
#else
typedef struct {
    u8 pad[4];
    void *first;
    u8 pad2[0x1054];
    s32 timer;
} MainObj;

typedef struct {
    u8 pad[0x14];
    void *sub;
    u8 flag;
} GenObj;
#endif

void func_80004B34(void *, void *, s32, f32, f32, f32);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_80004BA8 */
void func_80004BA8(void *, void *, s32, s32, void *, s32, void *);
#endif
void func_80004F80(void *, s32, s32);
void func_80005CE0(void *);

/* Builds a chain of 19 0xDC-byte objects inside arg0 from the descriptor list
 * at arg1+0x2C: initializes each object and its sub-record, links them to the
 * parent and to each other, gives them a sub-value of 100, sets a flag byte on
 * the ones marked in D_80030894, and clears the main timer. */
void buildObjectChain(MainObj *arg0, void *arg1) {
    u32 i;
    GenObj *p;
    u8 *desc;
    s32 flagv;

    func_80004B34(arg0, arg1, 4, 0.0f, 0.0f, 0.0f);
#ifdef TARGET_PC
    /* PC: first holds the handle of object 1 (see MainObj above). */
    arg0->first = PTR_TO_SLOT((u8 *)arg0 + 0xDC);
#else
    arg0->first = (GenObj *)((u8 *)arg0 + 0xDC);
#endif
    p = (GenObj *)((u8 *)arg0 + 0xDC);
    i = 1;
    flagv = 0x80;
#ifdef TARGET_PC
    /* PC: the descriptors are display records, Nw2Descr4BA8 (common.h), 0x50 bytes each: step by its size. */
    desc = (u8 *)arg1 + sizeof(Nw2Descr4BA8);
#else
    desc = (u8 *)arg1 + 0x2C;
#endif
    do {
        GenObj *next = (GenObj *)((u8 *)p + 0xDC);
        func_80004B34(p, desc, 4, 0.0f, 0.0f, 0.0f);
        func_80004BA8(p, desc, 0, 0x45A, arg0, 0, next);
        func_80004F80(desc, 0x45B, 0x45C);
        func_80005CE0(desc);
#ifdef TARGET_PC
        /* PC: sub holds the handle of the object's work block (see GenObj above); its +0x24 is the depth bias. */
        ((Nw2SceneWork *)SLOT_TO_PTR(p->sub))->bias = 100.0f;
#else
        *(f32 *)((u8 *)p->sub + 0x24) = 100.0f;
#endif
        if (D_80030894[i] == 0) {
            p->flag = flagv;
        }
#ifdef TARGET_PC
        /* PC: as above. */
        desc = (u8 *)desc + sizeof(Nw2Descr4BA8);
#else
        desc = (u8 *)desc + 0x2C;
#endif
        i++;
        p = next;
    } while (i < 0x14);
    arg0->timer = 0;
}
