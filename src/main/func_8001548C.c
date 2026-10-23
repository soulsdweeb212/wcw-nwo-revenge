#include "common.h"

typedef struct {
    u8 pad0[0x10];
    u64 time;
    u8 pad18[0x98];
    u64 cur;
    u8 padB8[0x25];
    u8 value;     /* @0xDD: current envelope level (0..0x7F) */
    u8 padDE[0x16];
    u8 rate;      /* @0xF4: ramp rate */
    u8 padF5[4];
    u8 acc;       /* @0xF9: fractional accumulator */
    u8 dir;       /* @0xFA: 0 = rising, 1 = falling */
} Nw2Timer1548C;

/* Advance a ramped envelope over the timer's active window: add the fixed-point
 * 0x100 step, accumulate the rate into the fraction, and on each whole step
 * ramp the level up until 0x7F, then back down to 0, reversing direction at
 * each end. Runs until cur reaches time. */
void func_8001548C(void *arg0)
{
    Nw2Timer1548C *p = arg0;
    u32 v;

    do {
        p->cur += 0x100;
        v = p->acc + p->rate;
        if (v < 0x40) {
            p->acc = v;
        } else {
            p->acc = v & 0x3F;
            v >>= 6;
            if (p->dir == 0) {
                u32 val = p->value + v;
                p->value = val;
                if ((val & 0xFF) < 0x80)
                    goto next;
                p->value = 0x7F;
                p->dir = 1;
            } else {
                u32 val = p->value - v;
                p->value = val;
                val &= 0xFF;
                if (val >= 0x80 || val == 0) {
                    p->value = 0;
                    p->dir = 0;
                }
            }
        }
    next:
        ;
    } while (p->time > p->cur);
}
