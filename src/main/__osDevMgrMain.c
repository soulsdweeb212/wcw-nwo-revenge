/* @header
 * __osDevMgrMain  (originally func_80027B40)
 * VRAM 0x80027B40 | ROM 0x28740 | size 0x3B8
 * asm: asm/nonmatchings/main/__osDevMgrMain.s
 */
/* SDK: libultra 2.0I, ultralib src/io/devmgr.c (same code as the SDK source). */
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

void osRecvMesg(void *, void *, s32);
void osSendMesg(void *, void *, s32);
void __osResetGlobalIntMask(s32);
void __osSetGlobalIntMask(s32);
void osYieldThread(void);
s32 osEPiRawReadIo(void *, u32, void *);
s32 osEPiRawWriteIo(void *, u32, u32);

s32 __osDevMgrMain(Nw2PiMgr *mgr)
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
        osRecvMesg(mgr->qA, &msg, 1);
        if (msg->job == 0) goto dispatch;
        if (msg->job->kind != 2) goto dispatch;
        if (msg->job->info.mode >= 2) goto dispatch;
        info = &msg->job->info;
        rec = &info->recs[info->index];
        info->result = -1;
        if (info->type != 3) rec->f4 -= rec->fC;
        flag = 0;
        if (info->type == 2) flag = (msg->job->info.mode == 0);
        osRecvMesg(mgr->qC, &recvB, 1);
        __osResetGlobalIntMask(0x100401);
        osEPiRawWriteIo(msg->job, 0x5000510, info->pi | 0x80000000);
recvLoop:
        osRecvMesg(mgr->qB, &recvC, 1);
        info = &msg->job->info;
        rec = &info->recs[info->index];
        if (rec->f0 == 0x1D) {
            osEPiRawWriteIo(msg->job, 0x5000510, info->pi | 0x10000000);
            osEPiRawWriteIo(msg->job, 0x5000510, info->pi);
            osEPiRawReadIo(msg->job, 0x5000508, &readBack);
            if (readBack & 0x2000000) {
                osEPiRawWriteIo(msg->job, 0x5000510, info->pi | 0x1000000);
            }
            rec->f0 = 4;
            *(vu32 *)0xA4600010 = 2;
            __osSetGlobalIntMask(0x100C01);
        }
        osSendMesg(msg->f4, msg, 0);
        if (flag == 1) {
            flag = 0;
            if (msg->job->info.recs[0].f0 == 0) goto recvLoop;
        }
        osSendMesg(mgr->qC, 0, 0);
        if (msg->job->info.index == 1) osYieldThread();
        continue;
dispatch:
        switch (msg->type) {
        case 11:
            osRecvMesg(mgr->qC, &recvB, 1);
            r = mgr->cbA(0, msg->fC, msg->f8, msg->f10);
            break;
        case 12:
            osRecvMesg(mgr->qC, &recvB, 1);
            r = mgr->cbA(1, msg->fC, msg->f8, msg->f10);
            break;
        case 15:
            osRecvMesg(mgr->qC, &recvB, 1);
            r = mgr->cbB(msg->job, 0, msg->fC, msg->f8, msg->f10);
            break;
        case 16:
            osRecvMesg(mgr->qC, &recvB, 1);
            r = mgr->cbB(msg->job, 1, msg->fC, msg->f8, msg->f10);
            break;
        case 10:
            osSendMesg(msg->f4, msg, 0);
            r = -1;
            break;
        default:
            r = -1;
            break;
        }
        if (r != 0) continue;
        osRecvMesg(mgr->qB, &recvC, 1);
        osSendMesg(msg->f4, msg, 0);
        osSendMesg(mgr->qC, 0, 0);
    }
}
