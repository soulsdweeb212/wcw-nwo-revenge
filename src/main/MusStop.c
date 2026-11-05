/* @header
 * MusStop  (originally func_80013B58)
 * VRAM 0x80013B58 | ROM 0x14758 | size 0xCC
 * asm: asm/nonmatchings/main/MusStop.s
 */
/* SDK: libmus, libmus/src/player.c (+playerinc/player_api.inc.c) (same code as the SDK source). */
#include "common.h"

/* 0x158-byte audio voice record. */
typedef struct { s32 flags; s32 active; u8 pad8[16]; s32 state; u8 pad1C[20]; s32 value; u8 pad34[146]; u16 kind; u8 padC8[144]; } AudioRec;
extern u32 max_channels;
extern AudioRec *mus_channels;

/* Stop/update active audio voices: walk all voice records, selecting a record when its
 * kind is nonzero and (arg0 & 1) is set, or when its kind is zero and (arg0 & 2) is set.
 * A selected record that is active and in state -1 either restarts (flags bit 0 set: value
 * = 1, state = 0, clear flag 0) or is set to value (arg1, or 1 when arg1 is zero) and state
 * arg1. */
void MusStop(s32 arg0, s32 arg1) {
    AudioRec *p;
    s32 value;
    u32 i;
    value=arg1;
    if (arg1 == 0) value = 1;
    p = mus_channels;
    for (i=0;i<max_channels;i++,p++) {
        if (p->kind != 0) {
            if (arg0 & 1) goto process;
        } else if (arg0 & 2) {
process:
            if (p->active != 0 && p->state == -1) {
                if (p->flags & 1) {
                    p->value = 1;
                    p->state = 0;
                    p->flags &= ~1;
                } else {
                    p->value = value;
                    p->state = arg1;
                }
            }
        }
    }
}
