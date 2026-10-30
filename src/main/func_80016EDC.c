/* @header
 * func_80016EDC
 * VRAM 0x80016EDC | ROM 0x17ADC | size 0x13C
 * asm: asm/nonmatchings/main/func_80016EDC.s
 */
#include "common.h"

extern s32 D_80036F34, D_80036F44, D_80062558;
extern u8 D_8006E370[], D_8006E3E0[];
void func_80000D28(s32, void *, void *);
s32 func_8001C990(void *, void *, s32);
s32 createAudioTask(s32, s32);
void func_80017554(void *);
typedef struct { s16 type, pad; s32 value; } AudioMessage;

void func_80016EDC(void) {
    u8 client[8];
    AudioMessage *msg;
    s32 done = 0;
    s32 type;

    func_80000D28(D_80062558, client, D_8006E370);
    do {
        func_8001C990(D_8006E370, &msg, 1);
        func_8001C990(D_8006E370, 0, 0);
        type = msg->type;
        switch ((s16)type) {
        case 1:
            if (createAudioTask(((s32 *)(D_8006E370 - 0x1C0))[D_80036F34], D_80036F44)) {
                func_8001C990(D_8006E370 + 0x38, &msg, 1);
                D_80036F34 = (D_80036F34 + 1) & 3;
                D_80036F44 = msg->value;
            }
            break;
        case 4:
            break;
        case 10:
            done = 1;
            break;
        }
    } while (!done);
    func_80017554(D_8006E3E0);
}
