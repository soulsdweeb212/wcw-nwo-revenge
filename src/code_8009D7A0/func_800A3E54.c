#include "common.h"

extern void *D_800EB408;
extern s32 D_800EB40C;
void func_800D4AD0(void *);
void beginEntityActionA8D8C(void *);
void func_800C472C(s32, void *, s32);
s32 func_800D2BEC(void *, void *, void *, f32, u16, s32);
/* Runs boundary correction on the entity and, once its timer expires, tears the
 * action down, restarts the entity action and notifies the linked entity. */
void func_800A3E54(void)
{
  int new_var2;
  void *new_var;
  new_var = D_800EB408;
  do
  {
    new_var2 = 0xFFFFE;
    func_800D2BEC(new_var, (void *) D_800EB40C, 0, 4.0f, 0, new_var2);
    if (((Nw2F408 *) D_800EB408)->f4 <= 0)
    {
      func_800D4AD0(D_800EB408);
      beginEntityActionA8D8C(D_800EB408);
      func_800C472C(D_800EB40C, D_800EB408, 2);
    }
  }
  while (0);
}
