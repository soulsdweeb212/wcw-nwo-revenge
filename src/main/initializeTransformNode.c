/* @header
 * initializeTransformNode  (originally func_800014D8)
 * VRAM 0x800014D8 | ROM 0x20D8 | size 0x6C
 * asm: asm/nonmatchings/main/initializeTransformNode.s
 */
#include "common.h"

void func_8001C0F0(void *,f32,f32,f32);
/* Initializes a transform node: stores the node type, clears the link fields
 * at +0..+0x17, sets the local translation, and resets the two 4x4 matrices
 * at +0x5C and +0x9C to identity. The volatile read of z preserves the
 * matching load order. */
void initializeTransformNode(u8 *node,u8 type,f32 x,f32 y,f32 z) {
 f32 value=*(volatile f32 *)&z;
 node[0x18]=type; *(s32 *)(node+0)=0; *(s32 *)(node+4)=0; *(s32 *)(node+8)=0; node[0x19]=0;node[0x1A]=0; *(s32 *)(node+12)=0;*(s32 *)(node+16)=0;*(s32 *)(node+20)=0;
 func_8001C0F0(node+0x1C,x,y,value);initIdentityMatrix4x4(node+0x5C);initIdentityMatrix4x4(node+0x9C);
}
