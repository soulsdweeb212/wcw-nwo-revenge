/* @header
 * setAudioRegionParameter  (originally func_80019C80)
 * VRAM 0x80019C80 | ROM 0x1A880 | size 0x1F0
 * asm: asm/nonmatchings/main/setAudioRegionParameter.s
 */
#include "common.h"

typedef struct Sub19C80 {
    s16 f0;
} Sub19C80;

typedef struct {
    s32 f0;
    s32 f4;
    s16 f8;
    s16 fA;
    s16 fC;
    u8 padE[2];
    f32 f10;
    u8 pad14[8];
    f32 f1C;
    Sub19C80 *f20;
    u8 pad24[4];
} Region19C80;

typedef struct {
    u8 pad0[0x20];
    Region19C80 *regions;
} Obj19C80;

typedef struct {
    u8 pad0[0x40];
    s32 f40;
} Ctx19C80;

extern Ctx19C80 *D_80036F54;
void func_8001CEF0(Sub19C80 *);

/* Sets one parameter of one region of an audio object. param 2.. selects the
 * region (param - 2) / 8 and the field (param - 2) % 8; *value is the new value. */
s32 setAudioRegionParameter(Obj19C80 *obj, s32 param, s32 *value) {
    s32 x;
    s32 val;
    s32 sub;
    s32 idx;

    sub = (param - 2) % 8;
    param = (param - 2) / 8;
    val = *value;
    switch (sub) {
    case 0:
        obj->regions[param].f0 = val & ~7;
        break;
    case 1:
        obj->regions[param].f4 = val & ~7;
        break;
    case 3:
        obj->regions[param].f8 = val;
        break;
    case 2:
        obj->regions[param].fA = val;
        break;
    case 4:
        obj->regions[param].fC = val;
        break;
    case 5:
        obj->regions[param].f10 = (f64)((f32)val / 1000.0f) * 2.0 / (f64)D_80036F54->f40;
        break;
    case 6:
        obj->regions[param].f1C = (f64)(f32)val / 173123.404906676 * (f64)(u32)(obj->regions[param].f4 - obj->regions[param].f0);
        break;
    case 7:
        if (obj->regions[param].f20 != NULL) {
            obj->regions[param].f20->f0 = val;
            func_8001CEF0(obj->regions[param].f20);
        }
        break;
    }
    return 0;
}
