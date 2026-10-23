#include "common.h"

typedef struct {u32 w0,w1;} CmdE230;
typedef struct NodeE230 {s32 type;CmdE230 *(*pull)(void *,void *,s32,void *,CmdE230 *);} NodeE230;
typedef struct {u8 pad[0x14];s32 count;u32 pad18;NodeE230 **children;} MixE230;

/* Emit the mixer node's two header commands (0x020006C0 and 0x02000800, each
 * carrying the doubled sample count) and then recursively pull a command block
 * from each child node. Returns the advanced command pointer. */
CmdE230 *pullAudioMixerChildren(MixE230 *arg0,void *arg1,s32 count,void *arg3,CmdE230 *p){
    volatile u64 pad;
    s32 doubled=count*2;
    s32 i;
    MixE230 *obj=arg0;
    NodeE230 **child;
    NodeE230 **start=obj->children;
    {CmdE230 *q=p++;q->w0=0x020006C0;q->w1=doubled;}
    {CmdE230 *q=p++;q->w0=0x02000800;q->w1=doubled;}
    i=0;
    if(obj->count>0){
        child=start;
        do{
            p=(*child)->pull(*child,arg1,count,arg3,p);
            child++;
            i++;
        }while(i<obj->count);
    }
    return p;
}
