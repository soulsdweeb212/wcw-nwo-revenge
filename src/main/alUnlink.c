/* @header
 * alUnlink  (originally func_8002023C)
 * VRAM 0x8002023C | ROM 0x20E3C | size 0x30
 * asm: asm/nonmatchings/main/alUnlink.s
 */
/* SDK: libultra 2.0I, ultralib src/audio/sl.c (same code as the SDK source). */
#include "common.h"

/* Unlink node arg0 from its doubly-linked list (next at +0, prev at +4). */
void alUnlink(void *arg0) {
    void *next;
    void **prev;

    next = *(void **)((s8 *)arg0 + 0);
    if (next != NULL) {
        *(void **)((s8 *)next + 4) = *(void **)((s8 *)arg0 + 4);
    }
    prev = *(void ***)((s8 *)arg0 + 4);
    if (prev != NULL) {
        *prev = *(void **)((s8 *)arg0 + 0);
    }
}
