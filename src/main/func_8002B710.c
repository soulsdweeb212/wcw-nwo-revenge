#include "common.h"

extern u16 lookupIdList[];

/* Return the 1-based position of `id` in the zero-terminated u16 lookupIdList,
 * or 0 when it is not present. */
s32 func_8002B710(s32 id) {
    u16 *entry = lookupIdList;
    s32 index = 0;

    if (*entry == 0) {
        goto fail;
    }
    do {
        if (id == *entry) {
            return index + 1;
        }
        index++;
        entry++;
    } while (*entry != 0);
fail:
    return 0;
}
