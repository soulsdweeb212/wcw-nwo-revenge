#include "common.h"

s32 readControllerPakId(void*);
/* If the Pak status has a pending bit (1 or 4), read its ID and clear the retry bit
 * on success; otherwise report status 5. */
s32 func_80025280(s32 *p){s32 r;if(*p&5){r=readControllerPakId(p);if(r==0)*p&=~4;}else r=5;return r;}
