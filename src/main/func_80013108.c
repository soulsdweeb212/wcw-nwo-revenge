#include "common.h"

/* func_80013108: main boot path. It initialises the 0x1E0-byte heap, brings
 * up the audio and controller subsystems, builds the asset size table, then
 * loops forever copying the two boot ROM regions (descriptor pairs at
 * D_80036E40 and D_80036E64, each a Nw2InitRect followed by a Nw2InitBig)
 * into their destinations through func_80000700 and func_8000082C. */
extern s32 D_80036E40[];
extern s32 D_80036E64[];
void func_80000700(Nw2InitRect, Nw2InitBig);
void func_8000082C(Nw2InitRect, Nw2InitBig);
void func_80001260(s32);
void func_80003120(void);
void func_80003D20(void);
void initializeAssetSizeTable(void);

void func_80013108(void) {
    s32 *p;
    s32 *q;

    func_80001260(0x1E0);
    func_80003120();
    func_80003D20();
    initializeAssetSizeTable();
    p = D_80036E40;
    q = D_80036E64;
    for (;;) {
        func_80000700(*(Nw2InitRect *)(p - 4), *(Nw2InitBig *)p);
        func_8000082C(*(Nw2InitRect *)(p - 4), *(Nw2InitBig *)p);
        func_80000700(*(Nw2InitRect *)(q - 4), *(Nw2InitBig *)q);
        func_8000082C(*(Nw2InitRect *)(q - 4), *(Nw2InitBig *)q);
    }
}
