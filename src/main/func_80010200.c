#include "common.h"

typedef struct {
    s16 id;
    s16 count;
    f32 angle;
    f32 start1;
    f32 start2;
    f32 pad10;
    f32 end1;
    f32 end2;
    f32 pad1C;
    f32 d1;
    f32 d2;
} Pose;

extern u8 D_80036D28[];
extern Pose D_8005A1A0[][3];

void func_80010200(s16 id, s16 side, s32 bits)
{
    union { s32 i; f32 f; } cv;
    f32 angle;
    s32 t;
    u32 i;

    t = D_80036D28[side];
    cv.i = bits;
    angle = cv.f;
    if (t < 2) {
        angle = -angle;
    }
    if (angle > 180.0f) {
        angle = 180.0f;
    }
    if (angle < -180.0f) {
        angle = -180.0f;
    }
    switch (id) {
    case 1: {
        Pose *p;
        p = &D_8005A1A0[t][2];
        p->end2 = 0.0f; p->start2 = 0.0f; p->start1 = -5.0f; p->end1 = -10.0f;
        p->angle = angle; p->id = id; p->count = 6;
        p->d2 = (p->end2 - p->start2) / 6.0f;
        p->d1 = (p->end1 - p->start1) / 6.0f;
        break;
    }
    case 2: {
        Pose *p, *q;
        p = &D_8005A1A0[t][2];
        p->end2 = 0.0f; p->start2 = 0.0f; p->start1 = 5.0f; p->end1 = 10.0f;
        p->angle = angle; p->id = id; p->count = 12;
        p->d2 = (p->end2 - p->start2) / 12.0f;
        p->d1 = (p->end1 - p->start1) / 12.0f;
        q = &D_8005A1A0[t][1];
        q->start1 = -5.0f; q->end1 = -10.0f; q->start2 = 0.0f; q->end2 = 0.0f;
        q->angle = angle; q->id = id; q->count = 12;
        q->d1 = (q->end1 - q->start1) / 12.0f;
        q->d2 = (q->end2 - q->start2) / 12.0f;
        break;
    }
    case 3: {
        Pose *p;
        p = &D_8005A1A0[t][0];
        p->end2 = 0.0f; p->start2 = 0.0f; p->start1 = 5.0f; p->end1 = 10.0f;
        p->angle = angle; p->id = id; p->count = 12;
        p->d2 = (p->end2 - p->start2) / 12.0f;
        p->d1 = (p->end1 - p->start1) / 12.0f;
        break;
    }
    case 4: {
        Pose *p, *q;
        p = &D_8005A1A0[t][2];
        p->end2 = 0.0f; p->start2 = 0.0f; p->start1 = 7.5f; p->end1 = 15.0f;
        p->angle = angle; p->id = id; p->count = 10;
        p->d2 = (p->end2 - p->start2) / 10.0f;
        p->d1 = (p->end1 - p->start1) / 10.0f;
        q = &D_8005A1A0[t][1];
        q->start1 = -7.5f; q->end1 = -15.0f; q->start2 = 0.0f; q->end2 = 0.0f;
        q->angle = angle; q->id = id; q->count = 10;
        q->d1 = (q->end1 - q->start1) / 10.0f;
        q->d2 = (q->end2 - q->start2) / 10.0f;
        break;
    }
    case 5: {
        Pose *p, *q;
        p = &D_8005A1A0[t][1];
        p->end2 = 0.0f; p->start2 = 0.0f; p->start1 = 7.5f; p->end1 = 15.0f;
        p->angle = angle; p->id = id; p->count = 10;
        p->d2 = (p->end2 - p->start2) / 10.0f;
        p->d1 = (p->end1 - p->start1) / 10.0f;
        q = &D_8005A1A0[t][0];
        q->start1 = -7.5f; q->end1 = -15.0f; q->start2 = 0.0f; q->end2 = 0.0f;
        q->angle = angle; q->id = id; q->count = 10;
        q->d1 = (q->end1 - q->start1) / 10.0f;
        q->d2 = (q->end2 - q->start2) / 10.0f;
        break;
    }
    case 6: {
        Pose *p, *q, *r;
        p = &D_8005A1A0[t][2];
        p->end1 = 0.0f; p->start1 = 0.0f; p->start2 = 30.0f; p->end2 = 60.0f;
        p->angle = angle; p->id = id; p->count = 12;
        p->d1 = (p->end1 - p->start1) / 12.0f;
        p->d2 = (p->end2 - p->start2) / 12.0f;
        q = &D_8005A1A0[t][1];
        q->end1 = 0.0f; q->start1 = 0.0f; q->start2 = 20.0f; q->end2 = 40.0f;
        q->angle = angle; q->id = id; q->count = 12;
        q->d1 = (q->end1 - q->start1) / 12.0f;
        q->d2 = (q->end2 - q->start2) / 12.0f;
        r = &D_8005A1A0[t][0];
        r->end1 = 0.0f; r->start1 = 0.0f; r->angle = angle; r->end2 = 20.0f; r->start2 = 10.0f;
        r->d1 = (r->end1 - r->start1) / 12.0f;
        r->id = id; r->count = 12;
        r->d2 = (r->end2 - r->start2) / 12.0f;
        break;
    }
    case 7: {
        Pose *p, *q, *r;
        p = &D_8005A1A0[t][2];
        p->end1 = -3.0f; p->start1 = -1.5f; p->start2 = 32.5f; p->end2 = 65.0f;
        p->angle = angle; p->id = id; p->count = 7;
        p->d1 = (p->end1 - p->start1) / 7.0f;
        p->d2 = (p->end2 - p->start2) / 7.0f;
        q = &D_8005A1A0[t][1];
        q->start1 = -1.5f; q->end1 = -3.0f; q->start2 = 20.0f; q->end2 = 40.0f;
        q->angle = angle; q->id = id; q->count = 7;
        q->d1 = (q->end1 - q->start1) / 7.0f;
        q->d2 = (q->end2 - q->start2) / 7.0f;
        r = &D_8005A1A0[t][0];
        r->end1 = 0.0f; r->start1 = 0.0f; r->angle = angle; r->end2 = 20.0f; r->start2 = 10.0f;
        r->d1 = (r->end1 - r->start1) / 7.0f;
        r->id = id; r->count = 7;
        r->d2 = (r->end2 - r->start2) / 7.0f;
        break;
    }
    case 8: {
        Pose *p, *q, *r;
        p = &D_8005A1A0[t][2];
        p->end2 = 0.0f; p->start2 = 0.0f; p->start1 = 5.0f; p->end1 = 10.0f;
        p->angle = angle; p->id = id; p->count = 6;
        p->d2 = (p->end2 - p->start2) / 6.0f;
        p->d1 = (p->end1 - p->start1) / 6.0f;
        q = &D_8005A1A0[t][1];
        q->end1 = 10.0f; q->start1 = 5.0f; q->end2 = 0.0f; q->start2 = 0.0f;
        q->angle = angle; q->id = id; q->count = 6;
        q->d1 = (q->end1 - q->start1) / 6.0f;
        q->d2 = (q->end2 - q->start2) / 6.0f;
        r = &D_8005A1A0[t][0];
        r->start1 = 5.0f; r->end1 = 10.0f; r->angle = angle; r->start2 = 0.0f; r->end2 = 0.0f;
        r->d1 = (r->end1 - r->start1) / 6.0f;
        r->id = id; r->count = 6;
        r->d2 = (r->end2 - r->start2) / 6.0f;
        break;
    }
    case 9: {
        Pose *p, *q, *r, *a, *b, *c;
        s32 u;
        p = &D_8005A1A0[t][2];
        p->end1 = -5.0f; p->start1 = -2.5f; p->end2 = 10.0f; p->start2 = 5.0f;
        p->id = id; p->count = 4; p->angle = -220.0f;
        p->d1 = (p->end1 - p->start1) / 4.0f;
        p->d2 = (p->end2 - p->start2) / 4.0f;
        q = &D_8005A1A0[t][1];
        q->end1 = -5.0f; q->start1 = -2.5f; q->end2 = 10.0f; q->start2 = 5.0f;
        q->angle = -220.0f; q->id = id; q->count = 4;
        q->d1 = (q->end1 - q->start1) / 4.0f;
        q->d2 = (q->end2 - q->start2) / 4.0f;
        r = &D_8005A1A0[t][0];
        r->end1 = -5.0f; r->start1 = -2.5f; r->angle = -220.0f; r->start2 = 5.0f; r->end2 = 10.0f;
        r->d1 = (r->end1 - r->start1) / 4.0f;
        r->id = id; r->count = 4;
        r->d2 = (r->end2 - r->start2) / 4.0f;
        u = (t - 1) & 3;
        a = &D_8005A1A0[u][2];
        a->end1 = -5.0f; a->start1 = -2.5f; a->end2 = 10.0f; a->start2 = 5.0f;
        a->angle = 220.0f; a->id = id; a->count = 4;
        a->d1 = (a->end1 - a->start1) / 4.0f;
        a->d2 = (a->end2 - a->start2) / 4.0f;
        b = &D_8005A1A0[u][1];
        b->end1 = -5.0f; b->start1 = -2.5f; b->end2 = 10.0f; b->start2 = 5.0f;
        b->angle = 220.0f; b->id = id; b->count = 4;
        b->d1 = (b->end1 - b->start1) / 4.0f;
        b->d2 = (b->end2 - b->start2) / 4.0f;
        c = &D_8005A1A0[u][0];
        c->angle = 220.0f; c->start1 = -2.5f; c->start2 = 5.0f; c->end1 = -5.0f;
        c->end2 = 10.0f;
        c->d1 = (c->end1 - c->start1) / 4.0f;
        c->d2 = (c->end2 - c->start2) / 4.0f;
        c->id = id; c->count = 4;
        break;
    }
    case 10:
        for (i = 0; i < 4; i++) {
            Pose *p, *q, *r;
            p = &D_8005A1A0[i][2];
            p->angle = 0.0f; p->id = id; p->count = 4;
            p->end1 = 6.0f; p->start1 = 3.0f; p->end2 = 0.0f; p->start2 = 0.0f;
            p->d1 = (p->end1 - p->start1) / 4.0f;
            p->d2 = (p->end2 - p->start2) / 4.0f;
            q = &D_8005A1A0[i][1];
            q->end1 = 6.0f; q->start1 = 3.0f; q->end2 = 0.0f; q->start2 = 0.0f;
            q->angle = 0.0f; q->id = id; q->count = 4;
            q->d1 = (q->end1 - q->start1) / 4.0f;
            q->d2 = (q->end2 - q->start2) / 4.0f;
            r = &D_8005A1A0[i][0];
            r->end1 = 6.0f; r->start1 = 3.0f; r->angle = 0.0f; r->start2 = 0.0f;
            r->end2 = 0.0f;
            r->d1 = (r->end1 - r->start1) / 4.0f;
            r->id = id; r->count = 4;
            r->d2 = (r->end2 - r->start2) / 4.0f;
        }
        break;
    case 11: {
        Pose *p, *q, *r;
        p = &D_8005A1A0[t][2];
        p->angle = 0.0f; p->start1 = 0.0f; p->start2 = 0.0f; p->end1 = 0.0f;
        p->end2 = 0.0f; p->d1 = 0.0f; p->d2 = 0.0f; p->id = 0; p->count = 0;
        q = &D_8005A1A0[t][1];
        q->angle = 0.0f; q->start1 = 0.0f; q->start2 = 0.0f; q->end1 = 0.0f;
        q->end2 = 0.0f; q->d1 = 0.0f; q->d2 = 0.0f; q->id = 0; q->count = 0;
        r = &D_8005A1A0[t][0];
        r->angle = 0.0f; r->start1 = 0.0f; r->start2 = 0.0f; r->end1 = 0.0f;
        r->end2 = 0.0f; r->d1 = 0.0f; r->d2 = 0.0f; r->id = 0; r->count = 0;
        break;
    }
    }
}
