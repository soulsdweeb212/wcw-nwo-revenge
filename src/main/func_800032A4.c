#include "common.h"

s32 func_80014140(s32,s16,s16,s16,s16,s16); extern s32 D_800482D4;
/* Forward five parameters to func_80014140 with the current context D_800482D4;
 * the last argument is truncated to s16. */
void func_800032A4(s16 a,s16 b,s16 c,s16 d,s32 e) { s32 value=*(volatile s32 *)&e; value=(s16)value; func_80014140(D_800482D4,a,b,c,d,value); }
