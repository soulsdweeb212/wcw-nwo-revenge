/* @header
 * func_80003D20
 * VRAM 0x80003D20 | ROM 0x4920 | size 0x158
 * asm: asm/nonmatchings/main/func_80003D20.s
 */
#include "common.h"

/* func_80003D20: controller subsystem bring-up. Points the four per-seat
 * records at their seat descriptors, initialises and starts the controller
 * read queue paired with D_800482F0, runs the controller-presence scan
 * (osContInit) and sends the "detect" message, then clears the
 * per-seat state flags, tears the temporary seats down and returns the scan
 * result. */
#ifdef TARGET_PC
/* PC: the seat records keep the N64's 12 bytes, because the files that read the controller state (func_80003E78, the
 * match's pad readers) reach their fields at N64 offsets. So the first word holds a handle of the seat descriptor's
 * address (docs/port.md, "Shared records on PC"); the developer program's files never read it back. */
typedef struct {
    u32 p;
    s32 f4;
    s32 f8;
} Nw2Rec6E178;
_Static_assert(sizeof(Nw2Rec6E178) == 0xC, "Nw2Rec6E178 keeps the N64's 12 bytes");
#else
typedef struct {
    void *p;
    s32 f4;
    s32 f8;
} Nw2Rec6E178;
#endif

extern Nw2Rec6E178 D_8006E178[4];
extern s32 D_80048310[];
extern u8 D_800482F0[];
extern u8 D_80048308[];
extern u8 D_80048350[];
extern s8 D_800484F0;
extern s8 D_800484F2;
extern u8 D_800484F3;
extern s8 D_800484F4[];
extern s8 D_800484F8[];
extern s8 D_800484FC[];

void osCreateMesgQueue(void *, void *, s32);
void osSetEventMesg(s32, void *, s32);
s32 osContInit(void *, void *, void *);
void osContSetCh(s32);
void func_800042BC(s16);
void __osMotorAccess(void *, s32);
void osContStartReadData(void *);

s32 func_80003D20(void) {
    s32 queue[6];
    s32 msg[2];
    s32 ret;
    u32 i;

    for (i = 0; i < 4; i++) {
#ifdef TARGET_PC
        D_8006E178[i].p = PTR_TO_SLOT(&D_80048310[i]);
#else
        D_8006E178[i].p = &D_80048310[i];
#endif
    }
    osCreateMesgQueue(queue, msg, 1);
    osSetEventMesg(5, queue, 1);
    ret = osContInit(queue, &D_800484F0, D_80048310);
    osContSetCh(4);
    osCreateMesgQueue(&D_800482F0, &D_80048308, 1);
    osSetEventMesg(5, &D_800482F0, 0);
    D_800484F3 = 0;
    for (i = 0; i < 4; i++) {
        func_800042BC((s16)i);
        if ((D_800484F3 >> i) & 1) {
            __osMotorAccess(&D_80048350[i * 0x68], 0);
        }
        D_800484FC[i] = 0;
        D_800484F4[i] = 0;
        D_800484F8[i] = 0;
    }
    osContStartReadData(&D_800482F0);
    D_800484F2 = 0;
    return ret;
}
