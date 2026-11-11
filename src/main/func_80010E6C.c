/* @header
 * func_80010E6C
 * VRAM 0x80010E6C | ROM 0x11A6C | size 0x3F8
 * asm: asm/nonmatchings/main/func_80010E6C.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: port_decls.h declares func_8000F710, so the PC copy of this line leaves it out. */
f32 func_80003CF0(f32);void func_8000FDCC(void);
#else
f32 func_80003CF0(f32);void func_8000FDCC(void);void func_8000F710(s32,u32);
#endif
extern const f64 D_8003B2A8,D_8003B2B0,D_8003B2B8,D_8003B2C0,D_8003B2C8;
typedef struct {
    s16 state;
    s16 timer;
    s32 pad4;
    f32 x;
    f32 y;
    s32 pad10;
    f32 vx;
    f32 vy;
    s32 pad1C;
    f32 dx;
    f32 dy;
} Obj10E6C;
typedef struct {
    s32 p;
    char pad[0xD8];
} Grp10E6C;
extern Obj10E6C D_8005A1A0[4][3];
#ifdef TARGET_PC
/* PC: the label D_80059D9C (+0xC of D_80059D90) has no symbol. D_80059D90 holds the four side slots' scene objects
 * (Nw2SceneObj, common.h, 0xDC bytes each), and the PC reads each one's vertices (+0xC) by name. */
extern u8 D_80059D90[];
#else
extern Grp10E6C D_80059D9C[];
#endif

void func_80010E6C(void) {
    u32 i;
    u32 j;
    f32 delta;
    f32 zero;

    func_8000FDCC();
    zero = 0.0f;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            delta = D_8005A1A0[i][j].dx;
            D_8005A1A0[i][j].timer--;
            if (delta != zero) {
                D_8005A1A0[i][j].x += delta;
                if (D_8005A1A0[i][j].timer <= 0) {
                    D_8005A1A0[i][j].vx = -D_8005A1A0[i][j].vx * D_8003B2A8;
                    if (func_80003CF0(D_8005A1A0[i][j].vx) < D_8003B2B0) {
                        D_8005A1A0[i][j].x = zero;
                        D_8005A1A0[i][j].vx = zero;
                        D_8005A1A0[i][j].dx = zero;
                        if (D_8005A1A0[i][j].dy == zero) {
                            D_8005A1A0[i][j].state = 0;
                        }
                    } else {
                        D_8005A1A0[i][j].dx = (D_8005A1A0[i][j].vx - D_8005A1A0[i][j].x) * D_8003B2B8;
                    }
                }
            }
            delta = D_8005A1A0[i][j].dy;
            if (delta != zero) {
                D_8005A1A0[i][j].y += delta;
                if (D_8005A1A0[i][j].timer > 0) {
                    continue;
                }
                if (D_8005A1A0[i][j].state != 7) {
                    D_8005A1A0[i][j].vy = -D_8005A1A0[i][j].vy * D_8003B2A8;
                } else {
                    D_8005A1A0[i][j].vy = -D_8005A1A0[i][j].vy * D_8003B2C0;
                }
                if (func_80003CF0(D_8005A1A0[i][j].vy) < D_8003B2B0) {
                    D_8005A1A0[i][j].y = 0.0f;
                    D_8005A1A0[i][j].vy = 0.0f;
                    D_8005A1A0[i][j].dy = 0.0f;
                    if (D_8005A1A0[i][j].dx == zero) {
                        D_8005A1A0[i][j].state = 0;
                    }
                } else if (D_8005A1A0[i][j].state != 7) {
                    D_8005A1A0[i][j].dy = (D_8005A1A0[i][j].vy - D_8005A1A0[i][j].y) * D_8003B2B8;
                } else {
                    D_8005A1A0[i][j].dy = (D_8005A1A0[i][j].vy - D_8005A1A0[i][j].y) * D_8003B2C8;
                }
            }
            if (D_8005A1A0[i][j].timer <= 0) {
                if (D_8005A1A0[i][j].state != 7) {
                    D_8005A1A0[i][j].timer = 6;
                } else {
                    D_8005A1A0[i][j].timer = 13;
                    if (D_8005A1A0[i][j].vy > zero) {
                        D_8005A1A0[i][j].state = 6;
                    }
                }
            }
        }
#ifdef TARGET_PC
        /* PC: side i's vertices, which func_8000FAF8 allocates: the object keeps the handle (port.h's PTR_TO_SLOT) of
         * the block, and func_8000F710 gets the pointer. */
        func_8000F710((u8 *)SLOT_TO_PTR(((Nw2SceneObj *)D_80059D90)[i].vtx), i);
#else
        func_8000F710(D_80059D9C[i].p, i);
#endif
    }
}
