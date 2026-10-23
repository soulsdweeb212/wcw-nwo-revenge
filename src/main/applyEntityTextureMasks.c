#include "common.h"

extern u16 D_80070B14[];
extern u8 D_80070450[];
extern u8 D_8003090C[], D_80030A0C[], D_80030B0C[], D_80030C0C[];
void applyTextureTransparencyMask(void *, void *, u16);

typedef struct {
    u8 f00[0x2C];
    u8 f2C[0x2C];
    u8 f58[0x3F4 - 0x58];
} Rec;

extern Rec D_80073F34[];

void applyEntityTextureMasks(s16 arg0, s16 arg1) {
    u16 t = D_80070B14[arg1];
    applyTextureTransparencyMask(D_80073F34[arg0].f58, D_8003090C, t);
    applyTextureTransparencyMask(D_80073F34[arg0].f2C, D_80030A0C, t);
    if (D_80070450[arg0] & 0x80) {
        applyTextureTransparencyMask(D_80073F34[arg0].f00, D_80030C0C, t);
    } else {
        applyTextureTransparencyMask(D_80073F34[arg0].f00, D_80030B0C, t);
    }
}
