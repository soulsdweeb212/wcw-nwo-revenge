#include "common.h"

s32 func_80099748(void **, s32, s32, s32, s32);

/* Append the two-word RDP command (0xE3001001, 0x8000) to the display list owned
 * by *dlp, reserving the space through func_80099748 with an RGB of 0xFF. */
void func_800998A4(void **dlp, s32 arg1) {
    void *p;
    void *cur;
    void *next;

    p = *dlp;
    func_80099748(&p, 0xFF, 0xFF, 0xFF, arg1);
    cur = p;
    next = cur + 8;
    p = next;
    *(s32 *)((s8 *)cur + 0) = 0xE3001001;
    *(s32 *)((s8 *)cur + 4) = 0x8000;
    *dlp = next;
}
