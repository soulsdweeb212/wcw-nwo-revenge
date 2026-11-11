/* @header
 * func_800085E4
 * VRAM 0x800085E4 | ROM 0x91E4 | size 0x50
 * asm: asm/nonmatchings/main/func_800085E4.s
 */
#include "common.h"

typedef struct { s16 f0; u8 pad[250]; } S85E;

#ifndef TARGET_PC /* on PC this label of the stream record D_800706A8 does not exist: it is read by field name */
extern S85E D_800706AC[];
#endif
#ifndef TARGET_PC /* on PC, port_decls.h declares D_8007BD38 */
extern u8 *D_8007BD38;
#endif

/* Return the high nibble of entity arg0's record byte in the table at D_8007BD38. */
u32 func_800085E4(s32 arg0) {
#ifdef TARGET_PC
    /* PC: the stream's animation id is the field id of its record (Nw2AnimStream, common.h), which the N64 reads
     * through its view S85E at the label D_800706AC, 4 bytes into the record. */
    u32 off = D_800706A8[(s16)arg0].id * 0x24 + 0xFFFDFFFC;

    /* PC: off is (id - 0xE39) * 0x24 in 32 bits. The N64 adds it to the table's address in 32 bits, so an id below
     * 0xE39 (a slot with no animation yet holds -1) reaches back before the table; added to a 64-bit pointer as a u32
     * it would reach 4 GB forward instead. As an s32 it is the same offset from the table as on the N64: the same
     * record for a valid id, and the same distance before the table (not the same bytes) for an id below 0xE39. */
    return D_8007BD38[(s32)off] >> 4;
#else
    u32 off = D_800706AC[(s16)arg0].f0 * 0x24 + 0xFFFDFFFC;
    return D_8007BD38[off] >> 4;
#endif
}
