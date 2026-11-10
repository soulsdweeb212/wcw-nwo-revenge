/* @header
 * func_800C2CDC
 * VRAM 0x800C2CDC | ROM 0xB617C | size 0x8A0
 * asm: asm/nonmatchings/code_800BBA00/func_800C2CDC.s
 */
#include "common.h"

typedef struct {u32 w[4];} Nw2Vec4U;
extern f32 D_800FADE0[][23],D_800FADE4[][23],D_800FADF4[][23];
extern u32 D_800EB4D8[][4],D_800EB4DC[][4],D_800EB4E0[][4],D_800EB4E4[][4];
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D3B24 */
s8 func_800D3B24(void*,void*,f32,s32);
#endif
void func_800C357C(void*,s16,s8*);
void func_800E2230(void*,void*);
#define OK ((arg0->flags&0x40 && T->flags&0xC0)||(arg0->flags&0x80 && T->flags&0x1C0)||(arg0->flags&0x100 && T->flags&0x100))
#define COPY(A,B) *(Nw2Vec4U*)vec1=*(Nw2Vec4U*)&arg0->A; *(Nw2Vec4U*)vec2=*(Nw2Vec4U*)&arg0->B; break
s32 func_800C2CDC(Wrestler *arg0,s16 arg1){
    s8 list[8];u32 vec1[4];u32 vec2[4];s16 i,j,link;Wrestler *T;f32 r;
    if(arg0->animFrame<arg0->anim.hitStart)goto done;
    if(arg0->anim.hitEnd<arg0->animFrame)goto done;
    func_800C357C(arg0,arg1,list);
    i=0;
    while(list[i]!=-1){
        T=&D_800F9D10[list[i]];
        switch(arg1){
        case 1:case 5:case 6:case 7:case 8:case 9:case 10:case 11:case 12:case 13:case 14:case 15:case 16:case 17:case 18:case 19:case 21:
            if(OK){if(func_800D3B24(&arg0->jointA[1],&T->jointA[1],180.0f,0)){
                    for(j=0;j<3;j++){
                        link=arg0->move.activeJoint[j];
                        switch(link){
                        case 1:case 2:case 3:case 4:case 5:case 8:case 9:case 10:case 15:case 17:case 18:COPY(jointA[link],jointA[link]);
                        case 14:COPY(jointB[14],jointB[13]);
                        case 7:COPY(jointB[7],jointB[6]);
                        case 13:COPY(jointB[13],jointB[15]);
                        case 6:COPY(jointB[6],jointB[8]);
                        case 19:COPY(jointB[19],jointB[16]);
                        case 12:COPY(jointB[12],jointB[11]);
                        case 16:COPY(jointB[16],jointB[17]);
                        case 11:COPY(jointB[11],jointB[9]);
                        }
                        r=D_800FADE0[arg0->id][link]+D_800FADE4[T->id][0];
                        if(func_800D3B24(vec1,&T->jointA[1],r,0))return T->id;
                        if(func_800D3B24(vec2,&T->jointA[1],r,0))return T->id;
                        r=D_800FADE0[arg0->id][link]+D_800FADF4[T->id][0];
                        if(func_800D3B24(vec1,&T->jointA[5],r,0))return T->id;
                        if(func_800D3B24(vec2,&T->jointA[5],r,0))return T->id;
                    }}}break;
        case 3:
            if(OK){if(func_800D3B24(&arg0->jointA[1],&T->jointA[1],180.0f,0)){
                    func_800E2230(arg0,vec1);
                    r=*(f32*)((u8*)vec1+4)+D_800FADE4[T->id][0];
                    if(func_800D3B24(vec1,&T->jointA[1],r,0))return T->id;
                    r=*(f32*)((u8*)vec1+4)+D_800FADF4[T->id][0];
                    if(func_800D3B24(vec1,&T->jointA[5],r,0))return T->id;
                }}break;
        case 4:case 20:return T->id;
        case 2:
            if(T->id==arg0->opponentId){
                if((arg0->flags&T->flags)&0x140)return T->id;
            }
            break;
        }
        i++;
    }
    done:*(Nw2Vec4U*)D_800EB4D8[arg0->id]=*(Nw2Vec4U*)&arg0->jointA[arg0->move.activeJoint[0]];return -1;
}
#undef OK
#undef COPY
