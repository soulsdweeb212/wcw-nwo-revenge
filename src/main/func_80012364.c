#include "common.h"

typedef struct {void *source;u8 pad4[16];u32 *flags;u8 rest[0xC4];} Render123;
typedef struct {f32 x,y,z;s32 rx,ry,rz,angle;} Pose123;
typedef struct {
    s8 f10;
    s8 n;
    s8 src;
    s8 mode;
    f32 x, y, z;
    s32 rx, ry, rz, rw;
    f32 v30[3];
    f32 pts[4][3];
} Ent;
typedef struct { u8 pad[0xD]; u8 d, e, f; } Col16;
extern Ent D_8007E010[];
extern Col16 D_8005AAA0[];
extern Render123 D_8005A3C0[];
extern u8 D_8006603C[];
extern f32 D_80070CB8[][713],D_8007147C[][713],D_80071480[][713],D_80071484[][713];
extern u8 D_80036E1C[];
extern s16 D_80070B14[];
extern f64 D_8003B308;
extern s32 D_8005AAE0,D_8005AB40,D_8005ABA0,D_8005AC2C,D_8005ACB4,D_8005AD3C,D_8005ADC4,D_8005AE4C,D_8005AEA8,D_8005AFE4,D_8005B06C;
extern u8 D_8005AAE8[],D_8005AB48[],D_8005ABA8[],D_8005AC30[],D_8005ACB8[],D_8005AD40[],D_8005ADC8[],D_8005AE50[],D_8005AEB0[],D_8005AFE8[],D_8005B070[];
void func_80007874(void *,void *,s32,s32);
s32 func_8001C580(void);
s16 func_80011B24(s16);
static inline void setCol(s32 v, s16 i) { D_8005AAA0[i].d = v; D_8005AAA0[i].e = 0; D_8005AAA0[i].f = 0; }
#define E D_8007E010[id]
#define OLD(sym) (sym[E.src][0])
void func_80012364(s16 id,s16 source,s16 mode,Pose123 *pose) {
 s32 changed=0;Render123 *obj=&D_8005A3C0[id];
 s32 ok;
 if(mode!=E.mode) {
 *obj->flags&=~0x80;
 switch(mode) {
 case 4:func_80007874(obj,D_8005AAE8,D_8005AAE0,0);E.n=2;break;
 case 5:func_80007874(obj,D_8005AB48,D_8005AB40,0);E.n=2;break;
 case 6:func_80007874(obj,D_8005ABA8,D_8005ABA0,0);E.n=4;break;
 case 7:func_80007874(obj,D_8005AC30,D_8005AC2C,0);E.n=4;break;
 case 10:func_80007874(obj,D_8005ACB8,D_8005ACB4,0);E.n=4;break;
 case 8:func_80007874(obj,D_8005AD40,D_8005AD3C,0);E.n=4;break;
 case 9:func_80007874(obj,D_8005AE50,D_8005AE4C,0);E.n=4;break;
 case 0:func_80007874(obj,D_8005ADC8,D_8005ADC4,0);E.n=2;break;
 case 3:func_80007874(obj,D_8005AEB0,D_8005AEA8,0);E.n=2;break;
 case 1:func_80007874(obj,D_8005AFE8,D_8005AFE4,0);E.n=2;break;
 case 2:func_80007874(obj,D_8005B070,D_8005B06C,0);E.n=2;break;
 case 11:
 setCol(6, id);
 D_80070B14[id]=func_80011B24(id);E.n=0;break;
 case 12:
 {s32 value=D_80036E1C[func_8001C580()%8];D_8005AAA0[id].e=0;D_8005AAA0[id].f=0;D_8005AAA0[id].d=value;}
 D_80070B14[id]=func_80011B24(id);E.n=0;break;
 default:E.n=0;*obj->flags|=0x80;mode=-1;break;
 }
 changed=1;E.f10=0;E.mode=mode;
 }
 if(source!=E.src) {
 if(source>=0) {
 obj->source=D_8006603C+source*5060;
 E.rw=0;E.rx=0;E.ry=0;E.rz=0;changed=1;
 }else{
 obj->source=0;
 E.rw=(s32)(OLD(D_80070CB8)*D_8003B308);
 E.rx=(s32)(OLD(D_8007147C)*D_8003B308);
 E.ry=(s32)(OLD(D_80071480)*D_8003B308);
 E.rz=(s32)(OLD(D_80071484)*D_8003B308);
 E.x=E.v30[0];E.y=E.v30[1];E.z=E.v30[2];
 if(pose){pose->x=-E.x;pose->y=E.y;pose->z=E.z;pose->rx=E.rx;pose->ry=E.ry;pose->rz=E.rz;pose->angle=E.rw;}
 }
 E.src=source;
 }else if(E.src==-1) {
 if(E.mode!=-1) {
 if(pose){
 E.x=-pose->x;E.y=pose->y;E.z=pose->z;E.rx=pose->rx;E.ry=pose->ry;E.rz=pose->rz;E.rw=pose->angle;
 }
 }
 }
 ok=source>=0;
 if(ok&changed){
 if(E.mode<6){E.x=-20.0f;E.y=-5.0f;E.z=30.0f;}
 else if(E.mode<11){E.x=10.0f;E.y=-5.0f;E.z=40.0f;}
 else{E.x=0;E.y=0;E.z=0;}
 }
}
