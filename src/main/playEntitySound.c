/* @header
 * playEntitySound  (originally func_8000E0CC)
 * VRAM 0x8000E0CC | ROM 0xECCC | size 0x430
 * asm: asm/nonmatchings/main/playEntitySound.s
 */
#include "common.h"

/* Play a sound effect for an entity.
 * For code >= 0x100 the high bits select a sound bank/effect entry from the
 * D_80030xxx tables and the code is remapped; otherwise code is the raw sound
 * id. The entity's distance to the listener sets the volume, and the sound is
 * started or refreshed through func_800032A4, with the special 0x22/0x24 cases
 * driving the D_80056940/D_80056948 hands. */
extern s16 D_80030D38[];
extern s8 D_80030E3C[], D_80030E44[], D_80030E4C[];
extern u8 D_80030E53[], D_8006A2A0[];
extern s32 D_8007E8C0[], D_800566F0[], D_80056940, D_80056948, D_80036738;
extern s16 D_8006A2A4[];
extern s8 D_80075468[];
extern f32 D_80070C50[][713], D_80070D10[][713], D_80070D18[][713];
extern f64 D_8003B1F8, D_8003B200, D_8003B208, D_8003B210, D_8003B218;
void func_8000E8A0(s8, s32, s8, s8);
s16 func_8000335C(s32);
s32 func_800032A4(s16, s16, s32, s32, s32);
s32 func_8000327C(s32);
void func_800056CC(f32 *, f32 *, f32 *);
f32 func_8001A480(f32);
void playEntitySound(s16 entity, s16 code) {
    struct { f32 x, y, z; } p;
    u8 effect;
    s16 sound;
    s32 *handle;
    s32 i;
    s32 *p2;
    s32 id, volume;
    s32 *c2base;
    if (code >= 0x100) {
        code -= 0x100;
        effect = D_80030E53[code];
        if (effect && D_8006A2A0[entity])
            func_8000E8A0((s8)(D_8007E8C0[entity] - 1), D_80030E4C[effect], D_80030E3C[effect], D_80030E44[effect]);
        if (D_80070C50[entity][0] < D_8003B1F8) {
            if (code == 6) code = -1;
            else if ((u16)(code - 0x18) < 6U) code = code < 0x1C ? 8 : 9;
            else code = code == 0xD ? 0 : code;
        }
        if ((u16)(code - 0x2D) < 0x13U) {
            if (code > 0) {
                s16 c2 = D_80030D38[code];
                if (c2 < 0) goto done;
                c2base = D_800566F0;
                handle = c2base + c2;
                if (func_8000335C(*handle) != 1) *handle = func_800032A4(c2, 128, 128, 0, -1);
            } else {
                if (!D_80036738) {
                    D_80036738 = func_8000327C(0x34);
                    for (i = 150, p2 = &D_80056948; i >= 0; i--, p2--) *p2 = 0;
                }
            }
done:
            code = 0;
        }
        sound = D_80030D38[code];
        if ((u16)(code - 0x21) < 2U && func_8000335C(D_800566F0[sound]) == 1) sound = -1;
    } else {
        sound = code;
    }
    id = sound;
    if (id >= 0) {
        func_800056CC(&p.x, &p.y, &p.z);
        p.x -= D_80070D10[entity][0];
        p.z += D_80070D18[entity][0];
        volume = (s32)((D_8003B210 - ((func_8001A480(p.x * p.x + p.z * p.z) - D_8003B200) * D_8003B208)) * D_8003B218);
        volume += 48;
        if (volume > 128) volume = 128;
        if (id < 151) {
            D_800566F0[id] = func_800032A4(id, (s16)volume, 128, 0, -1);
            if (D_8006A2A4[entity] < 0x900) {
                if (id == 0x22 && D_80075468[entity] < 20) {
                    sound = 150;
                    D_80056948 = func_800032A4(150, (s16)volume, 128, 0, -1);
                }
                if (sound == 0x24) D_80056940 = func_800032A4(148, (s16)volume, 128, 0, -1);
            }
        }
    }
}
