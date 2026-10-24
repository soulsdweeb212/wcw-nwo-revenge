#include "common.h"

typedef struct Nw2PiRec { s32 f0, f4, f8, fC, f10, f14, f18, f1C, f20; } Nw2PiRec;
typedef struct Nw2TranxInfo {
    u32 mode;
    u16 type;
    u16 index;
    s32 result;
    u32 devAddr;
    u32 pi;
    u32 seq;
    Nw2PiRec recs[2];
} Nw2TranxInfo;
typedef struct Nw2PiJob {
    u8 pad0[4];
    u8 kind;
    u8 pad5[0xF];
    Nw2TranxInfo info;
} Nw2PiJob;
typedef struct Nw2PiMsg {
    u16 type;
    u16 pad2;
    void *f4;
    s32 f8;
    s32 fC;
    s32 f10;
    Nw2PiJob *job;
} Nw2PiMsg;
typedef struct Nw2PiMgr {
    u8 pad0[8];
    void *qA;
    void *qB;
    void *qC;
    s32 (*cbA)(s32, s32, s32, s32);
    s32 (*cbB)(void *, s32, s32, s32, s32);
} Nw2PiMgr;

void func_8001C990(void *, void *, s32);
void func_8001CAC0(void *, void *, s32);
void func_80028110(s32);
void func_80028160(s32);
void func_800281A0(void);
s32 readPiHandleWord(void *, u32, void *);
s32 writePiHandleWord(void *, u32, u32);

s32 func_80027B40(Nw2PiMgr *mgr)
{
    Nw2PiMsg *msg;
    void *recvB;
    void *recvC;
    u32 readBack;
    Nw2TranxInfo *info;
    Nw2PiRec *rec;
    s32 flag;
    s32 r;

    msg = 0;
    while (1) {
        func_8001C990(mgr->qA, &msg, 1);
        if (msg->job == 0) goto dispatch;
        if (msg->job->kind != 2) goto dispatch;
        if (msg->job->info.mode >= 2) goto dispatch;
        info = &msg->job->info;
        rec = &info->recs[info->index];
        info->result = -1;
        if (info->type != 3) rec->f4 -= rec->fC;
        flag = 0;
        if (info->type == 2) flag = (msg->job->info.mode == 0);
        func_8001C990(mgr->qC, &recvB, 1);
        func_80028110(0x100401);
        writePiHandleWord(msg->job, 0x5000510, info->pi | 0x80000000);
recvLoop:
        func_8001C990(mgr->qB, &recvC, 1);
        info = &msg->job->info;
        rec = &info->recs[info->index];
        if (rec->f0 == 0x1D) {
            writePiHandleWord(msg->job, 0x5000510, info->pi | 0x10000000);
            writePiHandleWord(msg->job, 0x5000510, info->pi);
            readPiHandleWord(msg->job, 0x5000508, &readBack);
            if (readBack & 0x2000000) {
                writePiHandleWord(msg->job, 0x5000510, info->pi | 0x1000000);
            }
            rec->f0 = 4;
            *(vu32 *)0xA4600010 = 2;
            func_80028160(0x100C01);
        }
        func_8001CAC0(msg->f4, msg, 0);
        if (flag == 1) {
            flag = 0;
            if (msg->job->info.recs[0].f0 == 0) goto recvLoop;
        }
        func_8001CAC0(mgr->qC, 0, 0);
        if (msg->job->info.index == 1) func_800281A0();
        continue;
dispatch:
        switch (msg->type) {
        case 11:
            func_8001C990(mgr->qC, &recvB, 1);
            r = mgr->cbA(0, msg->fC, msg->f8, msg->f10);
            break;
        case 12:
            func_8001C990(mgr->qC, &recvB, 1);
            r = mgr->cbA(1, msg->fC, msg->f8, msg->f10);
            break;
        case 15:
            func_8001C990(mgr->qC, &recvB, 1);
            r = mgr->cbB(msg->job, 0, msg->fC, msg->f8, msg->f10);
            break;
        case 16:
            func_8001C990(mgr->qC, &recvB, 1);
            r = mgr->cbB(msg->job, 1, msg->fC, msg->f8, msg->f10);
            break;
        case 10:
            func_8001CAC0(msg->f4, msg, 0);
            r = -1;
            break;
        default:
            r = -1;
            break;
        }
        if (r != 0) continue;
        func_8001C990(mgr->qB, &recvC, 1);
        func_8001CAC0(msg->f4, msg, 0);
        func_8001CAC0(mgr->qC, 0, 0);
    }
}
