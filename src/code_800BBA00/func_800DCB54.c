#include "common.h"

extern void *D_800FAF5C,*D_800F9B00;extern s32 D_800E3F20[],D_800FABD8;extern s8 D_800FADB8;
void func_800A7C40(void *,s8,s16);void func_800A7D1C(void *,s32);void func_800A7F6C(void *,s32);void beginEntityActionA8D8C(void *);void func_800B68A0(void *,void *,void *);void addEntityHealthDelta(void *,s32);void func_800D427C(void *,s16,s32);void func_800D4AD0(void *);s8 func_800D4CC4(void *);s16 func_800D5438(void *,s32);s32 func_800DACE4(void *,void *);void func_800DB348(void *,void *);s8 func_800DB4FC(void *,void *);void func_800D7E80(void *,s32);s8 func_800D8D74(void *,s32);

/* State-machine driver for one entity action (four phases): phase 0 sets up the
 * animation/duration and arms the action, phase 1 waits for the trigger event,
 * phase 2 clears the shared D_800FABD8 flag bit and falls through into phase 3,
 * which tears the action down when its timer expires and (when the event had
 * fired) chains into the next action. */
void func_800DCB54(void){
    void *ent;
    switch(((Nw2F408*)D_800FAF5C)->fC){
    case 0: /* start: choose animation + duration, arm the action */
        func_800A7C40(D_800FAF5C,D_800FADB8,(-(*(s16*)((u8*)D_800FAF5C+10)!=0x65)&0xDF)|0xDE);
        func_800D427C(D_800FAF5C,func_800D5438(D_800FAF5C,0),3);
        func_800A7F6C(D_800FAF5C,0);
        func_800DACE4(D_800FAF5C,D_800F9B00);
        func_800D7E80(D_800FAF5C,0);
        ((Nw2F408*)D_800FAF5C)->fC++;
        break;
    case 1: /* wait for the trigger event */
        if(func_800D8D74(D_800FAF5C,0))((Nw2F408*)D_800FAF5C)->fC++;
        break;
    case 2: /* event done: clear the global flag bit, then fall into teardown */
        D_800FABD8&=~D_800E3F20[D_800FADB8];
        if(func_800DB4FC(D_800FAF5C,D_800F9B00))((Nw2F408*)D_800FAF5C)->fC++;
    case 3: /* timer expired: tear down, and chain a new action if the event fired */
        func_800DB348(D_800FAF5C,D_800F9B00);
        if(((Nw2F408*)D_800FAF5C)->f4<=0){
            func_800D4AD0(D_800FAF5C);
            ent=D_800FAF5C;
            if(((Nw2F408*)ent)->fC==2){
                func_800A7D1C(ent,0x23);
                func_800B68A0(D_800FAF5C,D_800FAF5C,D_800FAF5C);
                if(func_800D4CC4(ent))addEntityHealthDelta(ent,*(s8*)((u8*)ent+0x3A2));
                beginEntityActionA8D8C(ent);
            }else func_800A6C48(ent,0x2B);
        }
        break;
    }
}
