/* @header
 * func_800175E0
 * VRAM 0x800175E0 | ROM 0x181E0 | size 0x120
 * asm: asm/nonmatchings/main/func_800175E0.s
 */
#include "common.h"

typedef struct AudioNode {
    s32 f0, f4;
    struct AudioNode *next;   /* @0x8 */
    s32 fC, f10;
    s16 f14;
    u16 soundId;      /* @0x16 */
    u16 value;        /* @0x18 */
    s16 mode;         /* @0x1A */
    u8 pad[0x6C];
    s32 duration;     /* @0x88 */
} AudioNode;

typedef struct {
    u16 soundId, value;
    u8 mode;
} AudioDesc;

typedef struct {
    s32 f0, f4;
    s16 command, pad;
    s32 fC, f10;
} AudioPacket;

extern s32 *D_80036F54;
s32 func_80017700(AudioNode **, s16);
AudioPacket *func_80017F18(void);
s32 func_80018C24(void *, s32, void *);

/* Initialise audio node arg0 from descriptor arg1, look up (and attach) the
 * child node for the sound id, then queue the packets that start the node
 * (command 0xB) and run it for its duration (command 0xF). Returns whether a
 * child node was found. */
s32 func_800175E0(AudioNode *arg0, AudioDesc *arg1) {
    AudioNode *child = 0;
    s32 result, time;
    AudioNode *selected;
    AudioPacket *packet;
    arg0->soundId = arg1->soundId; arg0->mode = arg1->mode; arg0->fC = 0;
    arg0->value = arg1->value; arg0->f14 = 0; arg0->next = 0;
    result = func_80017700(&child, (s16)arg1->soundId);
    if (child) {
        if (result) {
            child->duration = 0x200; child->next->next = 0; child->next = arg0; arg0->next = child;
            packet = func_80017F18();
            selected = child; time = D_80036F54[7];
            packet->command = 0xB; packet->fC = 0; packet->f4 = time;
            packet->f10 = selected->duration - 0x40;
            func_80018C24(arg0->next, 3, packet);
            packet = func_80017F18();
            if (packet) {
                s32 time2 = D_80036F54[7];
                s32 value = child->duration;
                packet->command = 0xF; packet->f0 = 0; packet->f4 = time2 + value;
                func_80018C24(arg0->next, 3, packet);
            }
        } else {
            child->duration = 0; child->next = arg0; arg0->next = child;
        }
    }
    return child != 0;
}
