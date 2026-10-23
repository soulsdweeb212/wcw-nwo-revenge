#include "common.h"

/* stepRecordedFramePlayback: advance one tick of a recorded pose animation.
 * Up to four player slots are active (gated by D_800F9D12[player][0] and the
 * per-player enable mask D_800E3F38[player]).  For each active slot the pose
 * sample at the current frame is decoded and applied; afterwards the four
 * output transforms are rebuilt.  Finally the shared frame timer advances,
 * wrapping into the next frame, and the take loops/rewinds at the end. */

extern s32 D_800FABD8;
extern u16 D_800F99BA, D_800F97DE, D_800F97D8;
extern s16 D_800F97DA, D_800F97DC, D_800F97D4, D_800F97E0, D_800F97E2;
extern s32 D_800E3F38[];
extern const f64 D_800E6D48, D_800E6D50, D_800E6D58;
extern u8 D_800EB6D0[], D_800EB6D2[], D_800EB6D4[], D_800EB6D6[], D_800EB6D8[], D_800EB6DA[];
extern u8 D_800F2750[], D_800F2751[], D_800F2752[], D_800F2754[], D_800F2756[];
extern u8 D_800F2758[], D_800F2759[], D_800F275A[], D_800F275B[];
extern s16 D_800F9D12[][472];

void func_80010200(s16, s16, s32);
void func_8000DB90(s32, s32);
void func_8000946C(s32, s16, s16);
void func_80008CE8(s32, s16, s16, f32 *, s32, s8);
void func_80012364(s16, s8, s8, f32 *);

void stepRecordedFramePlayback(void) {
    s16 player, clipFrame;          /* slot index; clip frame within the take */
    s32 recOffset, poseFlags;       /* byte offset of a sample; pose flag bits */
    u16 poseBits;                   /* raw u16 pose word read back for the call */
    s32 inactive;                   /* slot/pose sentinel (-1 = no recorded pose) */
    s16 *pframe;                    /* points at the shared current-frame counter */
    Nw2PlaybackVec vec;
    Nw2PlaybackOut out;

    if (D_800FABD8 & 8) {
        D_800F99BA = D_800F97DE;
        func_80010200(11, 0, 0);
    } else {
        D_800F99BA = D_800F97DE & 0xFF3F;
    }
    player = 0;
    inactive = -1;
    pframe = &D_800F97DA;
    D_800FABD8 &= ~8;
    for (; player < 4; player++) {
        if (D_800F9D12[player][0] == inactive)
            continue;
        recOffset = (s32)*pframe * 12 + (s32)player * 0x1C20;
        if (*(s16 *)(D_800EB6D8 + recOffset) == inactive) {
            func_8000DB90(player, 0);
            continue;
        }
        func_8000DB90(player, 1);
        if (D_800FABD8 & D_800E3F38[player]) {
            u16 bits;
            recOffset = (s32)*pframe * 12 + (s32)player * 0x1C20;
            bits = *(u16 *)(D_800EB6DA + recOffset);
            clipFrame = bits & 0x3FF;
            if (bits & 1)
                clipFrame = clipFrame - 1;
            func_8000946C(player, *(s16 *)(D_800EB6D8 + recOffset), clipFrame);
        }
        recOffset = (s32)D_800F97DA * 12 + (s32)player * 0x1C20;
        vec.x = (f32)((f64)*(s16 *)(D_800EB6D0 + recOffset) * D_800E6D48);
        vec.z = (f32)((f64)*(s16 *)(D_800EB6D2 + recOffset) * D_800E6D48);
        vec.y = (f32)((f64)*(s16 *)(D_800EB6D4 + recOffset) * D_800E6D48);
        vec.w = *(s16 *)(D_800EB6D6 + recOffset);
        poseBits = *(u16 *)(D_800EB6DA + recOffset);
        clipFrame = poseBits & 0x3FF;
        poseFlags = poseBits & 0xFFFF;
        if (D_800FABD8 & D_800E3F38[player]) {
            if (poseBits & 1)
                clipFrame = clipFrame - 1;
            poseFlags = 0;
        } else if (poseFlags & 0x8000) {
            poseFlags = 2;
        } else {
            poseFlags = -((poseFlags & 0x4000) != 0) & 6;
        }
        {
            s32 slot = player;
            recOffset = (s32)D_800F97DA * 12 + slot * 0x1C20;
            func_80008CE8(slot, *(s16 *)(D_800EB6D8 + recOffset), clipFrame, &vec.x, 0, (s8)poseFlags);
            D_800FABD8 &= ~D_800E3F38[slot];
        }
    }
    for (player = 0; player < 4; player++) {
        recOffset = (s32)player * 12 + (s32)D_800F97DA * 48;
        out.x = (f32)((f64)*(s16 *)(D_800F2752 + recOffset) * D_800E6D50);
        out.y = (f32)((f64)*(s16 *)(D_800F2754 + recOffset) * D_800E6D50);
        out.z = (f32)((f64)*(s16 *)(D_800F2756 + recOffset) * D_800E6D50);
        out.a = (s32)((f64)*(s8 *)(D_800F2758 + recOffset) * D_800E6D58);
        out.b = (s32)((f64)*(s8 *)(D_800F2759 + recOffset) * D_800E6D58);
        out.c = (s32)((f64)*(s8 *)(D_800F275A + recOffset) * D_800E6D58);
        out.d = (s32)((f64)*(s8 *)(D_800F275B + recOffset) * D_800E6D58);
        func_80012364(player, *(s8 *)(D_800F2750 + recOffset), *(s8 *)(D_800F2751 + recOffset), &out.x);
    }
    if (D_800F97E2 == 0)
        D_800FABD8 |= 0x10000;
    else
        D_800FABD8 &= ~0x10000;
    {
        s16 *timer = &D_800F97E2;
        *timer = *timer + 1;
        if (*timer >= D_800F97E0) {
            *timer = 0;
            D_800F97DA = (u16)(D_800F97DA + 1);
        }
    }
    if (D_800F97DA >= 600)
        D_800F97DA = 0;
    if (D_800F97DA == D_800F97DC) {
        D_800F97DA = D_800F97D8;
        if (D_800F97D4 != 9999)
            D_800F97D4 = D_800F97D4 - 1;
        if (D_800F97D4 <= 0) {
            D_800FABD8 = 0;
            D_800F99BA = 0;
            return;
        }
        D_800FABD8 |= 0xF8;
    }
}
