/* @header
 * osSetIntMask  (originally func_8001C740)
 * VRAM 0x8001C740 | ROM 0x1D340 | size 0xA0
 * asm: asm/nonmatchings/main/osSetIntMask.s
 */
/* osSetIntMask: libultra osSetIntMask(OSIntMask im), returns the previous mask. An OSIntMask holds the CPU interrupt
 * enables in its low half (Status IM bits 8..15 + IE bit 0, OS_IM_CPU 0xFF01) and the six RCP (MI) interrupt enables
 * SP/SI/AI/VI/PI/DP in bits 16..21. Reads CP0 Status ($12), __OSGlobalIntMask (the interrupts the OS
 * allows at all) and MI_INTR_MASK_REG (0xA430000C). The returned old mask reports globally-forbidden lines as
 * "enabled" (CPU half always, RCP half only if some MI line is enabled), the standard libultra behaviour so a
 * save/restore pair round-trips. New state: MI_INTR_MASK_REG is written with __osRcpImTable[(im & global & 0x3F0000) >>
 * 16] (__osRcpImTable: 64 u16 halfwords, each the MI_INTR_MASK_REG SET/CLR bit pattern for one 6-bit RCP enable set;
 * the asm forms the byte offset with >> 15 and reads it with lhu), and Status IM = im & global & 0xFF00 (IE is never
 * changed: the global mask is ANDed with 0xFF00 first, and Status keeps its own bit 0). Two NOPs follow the mtc0 for
 * the CP0 hazard. Identical to ultralib src/os/setintmask.s (2.0I). Callers (jal scan of asm/): renderTaskThread,
 * osScAddClient, osScRemoveClient, func_80001260 (0x80401 = VI + IM2 + IE), n_alSynAddPlayer (Fdistort only declares
 * the prototype), mostly as old = osSetIntMask(1) ... osSetIntMask(old) to mask everything but IE around a critical
 * section. Asm because of mfc0/mtc0 on Status; in C those are the getStatus/setStatus inline helpers. */
#ifdef NON_MATCHING
#include "common.h"

extern u32 __OSGlobalIntMask;      /* interrupts the OS lets anyone enable (CPU IM bits 8..15 + IE in the
                             * low half, RCP SP/SI/AI/VI/PI/DP enables in bits 16..21) */
extern u16 __osRcpImTable[];    /* 64 MI_INTR_MASK_REG write values, one per 6-bit RCP enable set */
extern vu32 D_A430000C;     /* MI_INTR_MASK_REG (0x0430000C through KSEG1): reads give the 6 enabled RCP lines,
                             * writes take SET/CLR bit pairs */

/* CP0 Status ($12): IE bit 0, IM0..IM7 bits 8..15. */
static inline u32 getStatus(void) {
    u32 sr;
    __asm__ __volatile__("mfc0 %0, $12" : "=r"(sr));
    return sr;
}
static inline void setStatus(u32 sr) {
    __asm__ __volatile__("mtc0 %0, $12" : : "r"(sr));
}
static inline void cp0Hazard(void) {
    __asm__ __volatile__("nop");
}

s32 osSetIntMask(s32 mask) {
    u32 sr = getStatus();
    u32 globalMask = __OSGlobalIntMask;
    u32 oldMask;
    u32 rcp;
    u32 cpu;

    /* Old mask, CPU half: current IM bits + IE, plus every IM bit the global mask forbids (those report as on). */
    oldMask = sr & 0xFF01;                      /* OS_IM_CPU */
    oldMask |= ~globalMask & 0xFF00;            /* SR_IMASK */

    /* Old mask, RCP half: the enabled MI lines; if any are enabled, also the globally forbidden ones. */
    rcp = D_A430000C;
    if (rcp != 0) {
        rcp |= ~(globalMask >> 16) & 0x3F;
    }
    oldMask |= rcp << 16;

    /* New RCP enables: requested AND allowed, translated through the table into a SET/CLR write. */
    D_A430000C = __osRcpImTable[((u32)mask & 0x3F0000 & globalMask) >> 16];

    /* New CPU enables: requested IM bits AND allowed (globalMask & 0xFF00 has no bit 0, so IE is never
     * set from the argument); Status keeps its own IE and every bit outside IM. */
    cpu = ((u32)mask & 0xFF01) & (globalMask & 0xFF00);
    sr = (sr & 0xFFFF00FF) | cpu;
    setStatus(sr);
    cp0Hazard();
    cp0Hazard();
    return oldMask;
}
#else
/* Hand-written in the original; kept as top-level asm so the bytes match exactly. */
asm(
    ".set noreorder\n"
    ".set noat\n"
    "\n"
    ".globl osSetIntMask\n"
    ".ent osSetIntMask\n"
    "osSetIntMask:\n"
    "mfc0 $t4, $12 /* handwritten instruction */\n"
    "andi $v0, $t4, 0xFF01\n"
    "lui $t0, %hi(__OSGlobalIntMask)\n"
    "addiu $t0, $t0, %lo(__OSGlobalIntMask)\n"
    "lw $t3, 0x0($t0)\n"
    "addiu $at, $zero, -0x1\n"
    "xor $t0, $t3, $at\n"
    "andi $t0, $t0, 0xFF00\n"
    "or $v0, $v0, $t0\n"
    "lui $t2, %hi(D_A430000C)\n"
    "lw $t2, %lo(D_A430000C)($t2)\n"
    "beqz $t2, .L8001C784\n"
    "srl $t1, $t3, 16\n"
    "addiu $at, $zero, -0x1\n"
    "xor $t1, $t1, $at\n"
    "andi $t1, $t1, 0x3F\n"
    "or $t2, $t2, $t1\n"
    ".L8001C784:\n"
    "sll $t2, $t2, 16\n"
    "or $v0, $v0, $t2\n"
    "lui $at, (0x3F0000 >> 16)\n"
    "and $t0, $a0, $at\n"
    "and $t0, $t0, $t3\n"
    "srl $t0, $t0, 15\n"
    "lui $t2, %hi(__osRcpImTable)\n"
    "addu $t2, $t2, $t0\n"
    "lhu $t2, %lo(__osRcpImTable)($t2)\n"
    "lui $at, %hi(D_A430000C)\n"
    "sw $t2, %lo(D_A430000C)($at)\n"
    "andi $t0, $a0, 0xFF01\n"
    "andi $t1, $t3, 0xFF00\n"
    "and $t0, $t0, $t1\n"
    "lui $at, (0xFFFF00FF >> 16)\n"
    "ori $at, $at, (0xFFFF00FF & 0xFFFF)\n"
    "and $t4, $t4, $at\n"
    "or $t4, $t4, $t0\n"
    "mtc0 $t4, $12 /* handwritten instruction */\n"
    "nop\n"
    "nop\n"
    "jr $ra\n"
    "nop\n"
    ".end osSetIntMask\n"
    ".set at\n"
    ".set reorder\n"
    );
#endif
