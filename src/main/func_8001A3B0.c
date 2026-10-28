#include "common.h"

extern s32 D_80036F54;

typedef struct {
    u8 pad00[0x30];
    u8 *f30;
    u8 *f34;
    u8 pad38[0x0C];
    u8 *f44;
    s32 f48;
} Nw2Obj36F54;

typedef struct {
    u8 pad0[4];
    s32 *(*fn)(s32, s32 *);
} Nw2Tbl36F54;

extern void func_80018140(void *);
extern s32 *func_8001A400(s32, s32 *);

/* Look up the record at D_80036F54->f34 + arg0*4 + 0x24 and return its field. */
s32 func_8001A3B0(s32 arg0) {
    s32 t = (s32)(arg0 << 16) >> 14;
    func_80018140(((Nw2Obj36F54 *)D_80036F54)->f34 + (t + 0x24));
    t = t + (s32)((Nw2Obj36F54 *)D_80036F54)->f34;
    return *(s32 *)(t + 0x24);
}
