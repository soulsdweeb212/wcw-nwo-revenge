#include "common.h"

typedef struct {
    u8 pad0[0x14];
    u16 f14;
    u16 f16;
    u16 f18;
    u16 f1A;
} Nw2Cfg948BC;

typedef struct {
    u8 pad0[0x160];
    s16 f160;
    s16 f162;
    s16 f164;
    s16 f166;
    s16 f168;
    s16 f16A;
    s16 f16C;
    s16 f16E;
    s16 f170;
    s16 f172;
    s32 f174;
} Nw2Emit948BC;

extern Nw2Cfg948BC *D_800DB680;
extern Nw2Emit948BC D_800D6D50[];
extern f64 D_800D6008;

f32 sinf(f32);
f32 cosf(f32);

/* Every D_800DB680->f14 ticks, emits one spinning-effect entry into the first
 * free slot of the D_800D6D50 table: the swing/curve offsets come from a sine
 * and cosine of the tick angle scaled by f16 (+/- f18 and f1A), then a fixed
 * 0x480/0x320 quad is tagged with the 5/0x50/0x100/0x30 and 0x480/0x320 ids. */
void func_800948BC(s32 arg0) {
    f32 angle, swing, curve, amp, step;
    s32 slot;
    s32 curveInt, swingInt, angleInt;
    s32 id5, id50, id100, id30;
    Nw2Emit948BC *p;

    if (D_800DB680->f14 != 0 && arg0 % (s32)D_800DB680->f14 == 0) {
        step = (f32)((((arg0 << 3) - arg0 + (arg0 << 4)) & 0x3FF) * 0x168 / 512);
        amp = (f32)D_800DB680->f16;
        angle = (f32)((f64)step * D_800D6008);
        swing = amp * sinf(angle);
        curve = 2.0f * (amp * cosf(angle)) * 0.33333334f;
        if ((arg0 / (s32)D_800DB680->f14) & 1) {
            swing = swing + (f32)D_800DB680->f18;
        } else {
            swing = swing - (f32)D_800DB680->f18;
        }
        swingInt = (s32)swing;
        angleInt = (s32)step;
        id5 = 5;
        id50 = 0x50;
        id100 = 0x100;
        curve = curve + (f32)D_800DB680->f1A;
        curveInt = (s32)curve;
        id30 = 0x30;
        slot = 0;
        p = D_800D6D50;
        while (slot < 0x30) {
            if (p->f160 < 0) {
                break;
            }
            slot++;
            p++;
        }
        if (slot != 0x30) {
            p->f170 = 0x480;
            p->f160 = 0;
            p->f166 = id5;
            p->f162 = id50;
            p->f16C = swingInt;
            p->f16E = curveInt;
            p->f172 = angleInt;
            p->f168 = 0x320;
            p->f16A = id30;
            p->f164 = id100;
            p->f174 = 0;
        }
    }
}
