#include "common.h"

extern u8 D_80056968[], D_80057048[];
void func_800112BC(s16);
void func_8000F620(s16 arg0) {
 s32 i; u8 *p;
 if(arg0) {
 i=0; p=D_80056968; do { i++; *p &= 0x7F; p+=0xDC; } while(i<8);
 i=0; p=D_80057048; do { i++; *p &= 0x7F; p+=0xDC; } while(i<23);
 } else {
 i=0; p=D_80056968; do { i++; *p |= 0x80; p+=0xDC; } while(i<8);
 i=0; p=D_80057048; do { i++; *p |= 0x80; p+=0xDC; } while(i<23);
 }
 func_800112BC(arg0);
}
