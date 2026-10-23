#include "common.h"

/*
 * Load up to two resources (id1, id2) into obj.  For each id the resource
 * descriptor supplies the size; if the existing buffer is big enough it is
 * reused, otherwise it is freed and a new one allocated.  The descriptor's
 * minimum size is clamped (0x808 / 0x20) before allocating, then the data is
 * copied in.  When the grayscale flag is set the second resource is converted.
 */
typedef struct {
    u8 pad0[0x18];
    void *resource1;
    void *resource2;
} LoadObj;

void lookupResourceDescriptor(void *, u16);
void func_80003684(void *, u16, void *);
void func_80004C90(void *, u16);
void *allocateHeap(u32);
void releaseHeapBlock(void *);
extern u16 D_800307A0;
extern const f64 D_8003B110;

void func_80004E08(LoadObj *obj, s16 id1, s16 id2) {
    s32 desc1[4];
    s32 desc2[4];
    s32 scratch[4];

    if (id1) {
        lookupResourceDescriptor(desc1, id1);
        if (obj->resource1 != 0) {
            if (desc1[2] >= 0x809) {
                releaseHeapBlock(obj->resource1);
                goto alloc1;
            }
        } else {
        alloc1:
            if (desc1[2] < 0x808) {
                desc1[2] = 0x808;
            }
            obj->resource1 = allocateHeap(desc1[2]);
        }
        func_80003684(scratch, id1, obj->resource1);
    }
    if (id2) {
        lookupResourceDescriptor(desc2, id2);
        if (obj->resource2 != 0) {
            if (desc2[2] >= 0x21) {
                releaseHeapBlock(obj->resource2);
                goto alloc2;
            }
        } else {
        alloc2:
            if (desc2[2] < 0x20) {
                desc2[2] = 0x20;
            }
            obj->resource2 = allocateHeap(desc2[2]);
        }
        func_80003684(scratch, id2, obj->resource2);
        if (D_800307A0 == 1) {
            func_80004C90(obj->resource2, (u16)(u32)(desc2[2] * D_8003B110));
        }
    }
}
