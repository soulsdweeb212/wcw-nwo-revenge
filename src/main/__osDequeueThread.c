/* @header
 * __osDequeueThread  (originally func_8001CE40)
 * VRAM 0x8001CE40 | ROM 0x1DA40 | size 0x34
 * asm: asm/nonmatchings/main/__osDequeueThread.s
 */
/* SDK: libultra 2.0I, ultralib src/os/thread.c (same code as the SDK source). */
#include "common.h"

typedef struct Nw2Node {
    struct Nw2Node *next;
} Nw2Node;

/* Unlinks node arg1 from the singly-linked list whose head pointer is *arg0. */
void __osDequeueThread(Nw2Node **arg0, Nw2Node *arg1) {
    Nw2Node **pp;
    Nw2Node *v;

    pp = arg0;
    v = *pp;
    if (v != NULL) {
        do {
            if (v == arg1) {
                *pp = v->next;
                return;
            }
            pp = (Nw2Node **)v;
            v = *pp;
        } while (v != NULL);
    }
}

s32 __osProbeTLB(u32);

extern f64 D_8003B6D0;

typedef struct {
    s32 f0;
    u32 f4;
    s32 f8;
} NwAllocHdr;

void alFilterNew(void *, void *, void *, s32);
void *alHeapDBAlloc(void *, void *, NwAllocHdr *, s32, s32);
void alEnvmixerPull(void);
void alEnvmixerParam(void);
