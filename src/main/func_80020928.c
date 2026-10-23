#include "common.h"

typedef struct Nw2ListNode { struct Nw2ListNode *next; u8 pad[0xC]; s32 value; } Nw2ListNode;
void func_8001CEE0(void *, void *, s32);
extern char D_8003B8D0[];
extern char D_8003B8D4[];

/* Scans the linked list at arg0 for the node whose value (relative to arg0's
 * +0x20) is smallest, stores it in *arg1 and returns that node's value. */
s32 func_80020928(void *arg0, void **arg1) {
    s32 var_s1;
    void *var_a0;

    var_s1 = 0x7FFFFFFF;
    if (*(void **)arg0 == NULL) {
        func_8001CEE0(D_8003B8D0, D_8003B8D4, 0x133);
    }
    *arg1 = NULL;
    var_a0 = *(void **)arg0;
    if (var_a0 != NULL) {
        do {
            if ((*(s32 *)((u8 *)var_a0 + 0x10) - *(s32 *)((u8 *)arg0 + 0x20)) < var_s1) {
                *arg1 = var_a0;
                var_s1 = *(s32 *)((u8 *)var_a0 + 0x10) - *(s32 *)((u8 *)arg0 + 0x20);
            }
            var_a0 = *(void **)var_a0;
        } while (var_a0 != NULL);
    }
    return *(s32 *)((u8 *)(*arg1) + 0x10);
}
