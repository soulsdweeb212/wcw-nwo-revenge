#include "common.h"

/* 0x158-byte audio voice record (only the fields used here are named). */
typedef struct
{
    u8 pad0[0x60];
    s32 f60;
    u8 pad64[0x34];
    s32 f98;
    u8 pad9C[0xBC];
} AudioRec16904;

extern u32 D_800604C8;
extern AudioRec16904 *D_800604D0;

s32 func_80013A48(s32, u8, u8, s32, s32);

/* Handle one audio-script command: read a variable-length id (one byte; if bit 7 is set a
 * second byte completes it), read the two voice bytes at arg0+0xDC/+0xDD, bump the
 * sequence counter at arg0+0x64 around the call to func_80013A48, then for every voice
 * record in D_800604D0 whose +0x60 equals the returned key, copy arg0+0x60/+0x98 into the
 * record's +0x60/+0x98. Returns the advanced script pointer. */
u8 *func_80016904(u8 *arg0, u8 *arg1)
{
    s32 id;
    s32 counter;
    s32 result;
    u32 i;
    u8 a;
    u8 b;
    AudioRec16904 *p;

    id = *arg1++;
    if (id >= 0x80)
    {
        id = ((id & 0x7F) << 8) + *arg1++;
    }
    a = arg0[0xDC];
    counter = *(s32 *)(arg0 + 0x64);
    b = arg0[0xDD];
    *(s32 *)(arg0 + 0x64) = counter + 1;
    result = func_80013A48(id, a, b, 0, counter);
    *(s32 *)(arg0 + 0x64) -= 1;
    if (result != 0)
    {
        p = D_800604D0;
        for (i = 0; i < D_800604C8; i++, p++)
        {
            if (p->f60 == result)
            {
                p->f60 = *(s32 *)(arg0 + 0x60);
                p->f98 = *(s32 *)(arg0 + 0x98);
            }
        }
    }
    return arg1;
}
