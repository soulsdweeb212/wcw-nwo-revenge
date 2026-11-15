/* @header
 * func_80013108
 * VRAM 0x80013108 | ROM 0x13D08 | size 0x14C
 * asm: asm/nonmatchings/main/func_80013108.s
 */
#include "common.h"

/* func_80013108: main boot path. It initialises the 0x1E0-byte heap, brings
 * up the audio and controller subsystems, builds the asset size table, then
 * loops forever copying the two boot ROM regions (descriptor pairs at
 * D_80036E40 and D_80036E64, each a Nw2InitRect followed by a Nw2InitBig)
 * into their destinations through func_80000700 and func_8000082C. */
#ifdef TARGET_PC
/* PC: the overlay table's two entries by the labels of their halves (common.h's Nw2InitRect and Nw2InitBig), so that
 * tools/port_data.py turns their words into the PC's byte order: the N64 code reaches each entry's first half as the
 * 16 bytes before D_80036E40 and D_80036E64 (p - 4 below), past those labels' own data. */
extern Nw2InitRect D_80036E30, D_80036E54;
extern Nw2InitBig D_80036E40, D_80036E64;
#else
extern s32 D_80036E40[];
extern s32 D_80036E64[];
#endif
void func_80000700(Nw2InitRect, Nw2InitBig);
void func_8000082C(Nw2InitRect, Nw2InitBig);
void func_80001260(s32);
void func_80003120(void);
void func_80003D20(void);
void initializeAssetSizeTable(void);

void func_80013108(void) {
#ifndef TARGET_PC
    s32 *p;
    s32 *q;
#endif

    func_80001260(0x1E0);
    func_80003120();
    func_80003D20();
    initializeAssetSizeTable();
#ifdef TARGET_PC
    for (;;) { /* PC: the entries by name, as declared above */
        func_80000700(D_80036E30, D_80036E40);
        func_8000082C(D_80036E30, D_80036E40);
        func_80000700(D_80036E54, D_80036E64);
        func_8000082C(D_80036E54, D_80036E64);
    }
#else
    p = D_80036E40;
    q = D_80036E64;
    for (;;) {
        func_80000700(*(Nw2InitRect *)(p - 4), *(Nw2InitBig *)p);
        func_8000082C(*(Nw2InitRect *)(p - 4), *(Nw2InitBig *)p);
        func_80000700(*(Nw2InitRect *)(q - 4), *(Nw2InitBig *)q);
        func_8000082C(*(Nw2InitRect *)(q - 4), *(Nw2InitBig *)q);
    }
#endif
}
