/* @header
 * func_80000580
 * VRAM 0x80000580 | ROM 0x1180 | size 0x2C
 * asm: asm/nonmatchings/main/func_80000580.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: the types of osScAddClient's definition (src/main/osScAddClient.c, SDK code that the port replaces with a
 * stand-in): the client record is a pointer; the queue is the s32 that it stores into the client's 4-byte field at
 * +4. */
void osScAddClient(void *, void *, s32);
#else
void osScAddClient(void *, s32, s32);
#endif
extern s32 D_8003DE30;

/* Push a message (arg0, arg1) onto the event list at D_8003DE30. */
#ifdef TARGET_PC
/* PC: the only caller, func_80001260, passes two addresses: the 8-byte client record D_80046760 and the message queue
 * D_80046768 (the N64 code passes both on unchanged, in a1 and a2). An s32 would cut each in half, so the PC definition
 * takes pointers (port_decls.h declares it so). osScAddClient keeps the queue in the client's 4-byte field at +4, so
 * the queue goes there as a 32-bit handle (port.h's PTR_TO_SLOT); the port's stand-ins for osScAddClient and __scMain,
 * which send the retrace messages to that queue, turn it back with SLOT_TO_PTR. */
void func_80000580(void *arg0, void *arg1) {
    osScAddClient(&D_8003DE30, arg0, PTR_TO_SLOT(arg1));
}
#else
void func_80000580(s32 arg0, s32 arg1) {
    osScAddClient(&D_8003DE30, arg0, arg1);
}
#endif
