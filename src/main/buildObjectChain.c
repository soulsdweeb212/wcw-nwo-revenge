#include "common.h"

extern u8 D_80030894[];

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

void func_80004B34(void *, void *, s32, f32, f32, f32);
void func_80004BA8(void *, void *, s32, s32, void *, s32, void *);
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
    arg0->first = (GenObj *)((u8 *)arg0 + 0xDC);
    p = (GenObj *)((u8 *)arg0 + 0xDC);
    i = 1;
    flagv = 0x80;
    desc = (u8 *)arg1 + 0x2C;
    do {
        GenObj *next = (GenObj *)((u8 *)p + 0xDC);
        func_80004B34(p, desc, 4, 0.0f, 0.0f, 0.0f);
        func_80004BA8(p, desc, 0, 0x45A, arg0, 0, next);
        func_80004F80(desc, 0x45B, 0x45C);
        func_80005CE0(desc);
        *(f32 *)((u8 *)p->sub + 0x24) = 100.0f;
        if (D_80030894[i] == 0) {
            p->flag = flagv;
        }
        desc = (u8 *)desc + 0x2C;
        i++;
        p = next;
    } while (i < 0x14);
    arg0->timer = 0;
}
