
#ifndef DONGBOYADVANCE_CPU_H
#define DONGBOYADVANCE_CPU_H
/**
 * CPU header file for the emulated ARM7TDMI 32-bit RISC CPU
 */

#include <unistd.h>
#include <stdbool.h>
#include "logger.h"
#include <stdarg.h>

bool debug;
typedef uint64_t ARM_U_DWORD;
typedef uint32_t ARM_U_WORD;
typedef uint16_t ARM_U_HWORD;
typedef uint8_t ARM_U_BYTE;

typedef int64_t ARM_S_DWORD;
typedef int32_t ARM_S_WORD;
typedef int16_t ARM_S_HWORD;
typedef int8_t ARM_S_BYTE;

/**
 * Important Memory Address Definitions
 */
#define EXCEPTION_BASE  0x00000000
#define GAME_DATA_BEGIN 0x08000000
typedef struct _general_purpose_register {
    ARM_U_WORD data;
} General_Purpose_Register;
/** 
 * Struct containing the 13 general purpose registers R0-R12
 * 
  System/User FIQ       Supervisor Abort     IRQ       Undefined
  --------------------------------------------------------------
  R0          R0        R0         R0        R0        R0
  R1          R1        R1         R1        R1        R1
  R2          R2        R2         R2        R2        R2
  R3          R3        R3         R3        R3        R3
  R4          R4        R4         R4        R4        R4
  R5          R5        R5         R5        R5        R5
  R6          R6        R6         R6        R6        R6
  R7          R7        R7         R7        R7        R7
  --------------------------------------------------------------
  R8          R8_fiq    R8         R8        R8        R8
  R9          R9_fiq    R9         R9        R9        R9
  R10         R10_fiq   R10        R10       R10       R10
  R11         R11_fiq   R11        R11       R11       R11
  R12         R12_fiq   R12        R12       R12       R12
  R13 (SP)    R13_fiq   R13_svc    R13_abt   R13_irq   R13_und
  R14 (LR)    R14_fiq   R14_svc    R14_abt   R14_irq   R14_und
  R15 (PC)    R15       R15        R15       R15       R15
  --------------------------------------------------------------
  CPSR        CPSR      CPSR       CPSR      CPSR      CPSR
  --          SPSR_fiq  SPSR_svc   SPSR_abt  SPSR_irq  SPSR_und
  --------------------------------------------------------------

 */
//TODO Add the special FIQ/Supervisor/IQR/Abort registers
typedef struct _general_purpose_registers {
    General_Purpose_Register registers[13];
} General_Purpose_Registers;


/**
 * 
  Code Suffix Flags         Meaning
  0:   EQ     Z=1           equal (zero) (same)
  1:   NE     Z=0           not equal (nonzero) (not same)
  2:   CS/HS  C=1           unsigned higher or same (carry set)
  3:   CC/LO  C=0           unsigned lower (carry cleared)
  4:   MI     N=1           signed negative (minus)
  5:   PL     N=0           signed positive or zero (plus)
  6:   VS     V=1           signed overflow (V set)
  7:   VC     V=0           signed no overflow (V cleared)
  8:   HI     C=1 and Z=0   unsigned higher
  9:   LS     C=0 or Z=1    unsigned lower or same
  A:   GE     N=V           signed greater or equal
  B:   LT     N<>V          signed less than
  C:   GT     Z=0 and N=V   signed greater than
  D:   LE     Z=1 or N<>V   signed less or equal
  E:   AL     -             always (the "AL" suffix can be omitted)
  F:   NV     -             never (ARMv1,v2 only) (Reserved ARMv3 and up)

 */
typedef union _conditional_flags {
    ARM_U_WORD flags;

    struct {
        ARM_U_WORD EQ: 1;
        ARM_U_WORD NE: 1;
        ARM_U_WORD CS_HS: 1;
        ARM_U_WORD CC_LO: 1;
        ARM_U_WORD MI: 1;
        ARM_U_WORD PL: 1;
        ARM_U_WORD VS: 1;
        ARM_U_WORD VC: 1;
        ARM_U_WORD HI: 1;
        ARM_U_WORD LS: 1;
        ARM_U_WORD GE: 1;
        ARM_U_WORD LT: 1;
        ARM_U_WORD GT: 1;
        ARM_U_WORD LE: 1;
        ARM_U_WORD AL: 1;
        ARM_U_WORD NV: 1;
    };
} Conditional_Flags;


typedef struct _stack_pointer {
    General_Purpose_Register r13;
} Stack_Pointer;

typedef struct _link_register {
    General_Purpose_Register r14;
} Link_Register;

typedef struct _program_counter {
    General_Purpose_Register r15;
} Program_Counter;
/**
 * Current Program Status Register (CPSR)
  Bit   Expl.
  31    N - Sign Flag       (0=Not Signed, 1=Signed)               ;\
  30    Z - Zero Flag       (0=Not Zero, 1=Zero)                   ; Condition
  29    C - Carry Flag      (0=Borrow/No Carry, 1=Carry/No Borrow) ; Code Flags
  28    V - Overflow Flag   (0=No Overflow, 1=Overflow)            ;/
  27    Q - Sticky Overflow (1=Sticky Overflow, ARMv5TE and up only)
  26-8  Reserved            (For future use) - Do not change manually!
  7     I - IRQ disable     (0=Enable, 1=Disable)                     ;\
  6     F - FIQ disable     (0=Enable, 1=Disable)                     ; Control
  5     T - State Bit       (0=ARM, 1=THUMB) - Do not change manually!; Bits
  4-0   M4-M0 - Mode Bits   (See below)                               ;/
 */
typedef union _cpsr {
    ARM_U_WORD status;

    struct {
        ARM_U_WORD Mode_bits: 4;
        ARM_U_WORD T_state_bit: 1;
        ARM_U_WORD F_FIQ_disable: 1;
        ARM_U_WORD I_IQR_disable: 1;
        ARM_U_WORD Reserved: 20;
        /**
        * Bit 27: Sticky Overflow Flag (Q) - ARMv5TE and ARMv5TExP and up only
        * Used by QADD, QSUB, QDADD, QDSUB, SMLAxy, and SMLAWy only.
        * These opcodes set the Q-flag in case of overflows, but leave it unchanged
        * otherwise. The Q-flag can be tested/reset by MSR/MRS opcodes only.
        */
        ARM_U_WORD Q_Sticky_overflow: 1;
        /**
         * Bit 31-28: Condition Code Flags (N,Z,C,V)
         * These bits reflect results of logical or arithmetic instructions.
         * In ARM mode, it is often optionally whether an instruction should modify flags or not,
         * for example, it is possible to execute a SUB instruction that does NOT modify the condition flags.
         * In ARM state, all instructions can be executed conditionally depending on the settings of the flags,
         * such like MOVEQ (Move if Z=1). While In THUMB state, only Branch instructions (jumps) can be made conditionally.
         */
        ARM_U_WORD V_Overflow_flag: 1;
        ARM_U_WORD C_Carry_flag: 1;
        ARM_U_WORD Z_Zero_flag: 1;
        ARM_U_WORD N_Sign_flag: 1;
    };

} CPSR;

/**
 * Saved Program Status Registers (SPSR_<mode>)
   Additionally to above CPSR, five Saved Program Status Registers exist:
   SPSR_fiq, SPSR_svc, SPSR_abt, SPSR_irq, SPSR_und
   Whenever the CPU enters an exception, the current status register (CPSR) is copied to the respective
   SPSR_<mode> register. Note that there is only one SPSR for each mode, so nested exceptions inside of the
   same mode are allowed only if the exception handler saves the content of SPSR in memory.
   For example, for an IRQ exception: IRQ-mode is entered, and CPSR is copied to SPSR_irq.
   If the interrupt handler wants to enable nested IRQs, then it must first push SPSR_irq before doing so.
 */
//TODO Figure out what to put in the struct
typedef struct _spsr {
    General_Purpose_Register spsr;
} SPSR;

/**
 * Mode or entry of the exception
 */
typedef enum {
    _svc, _und, _abt, _iqr, _fiq
} Mode_on_Entry;

typedef enum {
    no_change, set_0, set_1
} Interrupt_Flag_Change;
/**
 * Signals what type of interrupt I believe. Either normal or fast
 */
typedef struct _interrupt_flags {
    Interrupt_Flag_Change I;
    Interrupt_Flag_Change F;
} Interrupt_Flags;
/**
 * Actual exception with its location, priority, mode/entry/, and what interrupt generated it
 */
typedef struct _exception_vector {
    ARM_U_WORD address;
    ARM_U_WORD priority;
    Mode_on_Entry mode_on_entry;
    Interrupt_Flags interrupt_flags;
} Exception_Vector;
/**
 * Exception Vectors
   The following are the exception vectors in memory.
   That is, when an exception arises, CPU is switched into ARM state, and the program counter (PC)
   is loaded by the respective address.

        Address  Prio  Exception                  Mode on Entry      Interrupt Flags
        BASE+00h 1     Reset                      Supervisor (_svc)  I=1, F=1
        BASE+04h 7     Undefined Instruction      Undefined  (_und)  I=1, F=unchanged
        BASE+08h 6     Software Interrupt (SWI)   Supervisor (_svc)  I=1, F=unchanged
        BASE+0Ch 5     Prefetch Abort             Abort      (_abt)  I=1, F=unchanged
        BASE+10h 2     Data Abort                 Abort      (_abt)  I=1, F=unchanged
        BASE+14h ??    Address Exceeds 26bit      Supervisor (_svc)  I=1, F=unchanged
        BASE+18h 4     Normal Interrupt (IRQ)     IRQ        (_irq)  I=1, F=unchanged
        BASE+1Ch 3     Fast Interrupt (FIQ)       FIQ        (_fiq)  I=1, F=1

   BASE is normally 00000000h, but may be optionally FFFF0000h in some ARM CPUs.
   Priority for simultaneously occuring exceptions ranges from Prio=1=Highest to Prio=7=Lowest.
   As there's only space for one ARM opcode at each of the above addresses,
   it'd be usually recommended to deposit a Branch opcode into each vector,
   which'd then redirect to the actual exception handlers address.
 */
typedef struct _exception_vector_table {
    ARM_U_WORD base;
    Exception_Vector Reset;
    Exception_Vector Undefined_Instruction;
    Exception_Vector Software_Interrupt_SWI;
    Exception_Vector Prefect_Abort;
    Exception_Vector Data_Abort;
    Exception_Vector Address_Exceeds_26bit;
    Exception_Vector Normal_Interrupt_IQR;
    Exception_Vector Fast_Interrupt_FIQ;
} Exception_Vector_Table;
Exception_Vector_Table exception_vector_table;

/**
 * Init function for the Exception Vector Table;
 */
void init_exception_vector_table();
/***********************************************
 * Temporary Memory TODO IMPLEMENT ACTUAL MEMORY
 *
 ***********************************************/

#define MAX_MEM  0x10000000
ARM_U_BYTE MEMORY[MAX_MEM];

typedef enum {
    BYTE, HALF_WORD, WORD, DOUBLE_WORD
} Alignment;
typedef Alignment Write_Mode;
typedef Alignment Read_Mode;
ARM_U_WORD fetch_opcode_memory();
void set_memory_range_random(ARM_U_WORD starting_address, ARM_U_WORD size, Write_Mode mode);

void write_memory(ARM_U_WORD address, ARM_U_WORD val, Write_Mode mode);

void view_address(ARM_U_WORD address, Read_Mode mode);

ARM_U_WORD read_memory(ARM_U_WORD, Read_Mode mode);

ARM_U_WORD get_word(ARM_U_WORD address);

ARM_U_WORD get_byte(ARM_U_WORD address);

void clear_all_mem();

/***********************************************
 * Registers begin
 *
 ***********************************************/

General_Purpose_Registers gpr;
Conditional_Flags cond_flags;
CPSR cpsr;
SPSR spsr;
Stack_Pointer sp;
Program_Counter pc;
Link_Register lr;
/***********************************************
 * Registers end
 *
 ***********************************************/
/***********************************************
 * Init routine section begin
 *
 ***********************************************/

void init_cpu();

void init_general_registers();

void init_conditional_flags();
void init_pc();
void init_current_program_status_register();
/***********************************************
 * Init routine section end
 *
 ***********************************************/
/***********************************************
* Register specific functions
*
***********************************************/
void zero_reg(int reg, ...);

void set_reg(ARM_U_WORD reg, ARM_U_WORD value);

void set_pc(ARM_U_WORD address);
void set_lr(ARM_U_WORD address);
ARM_U_WORD get_reg_data(ARM_U_WORD reg);
/**
 * CPSR Functions
 */
void cpsr_clear();

/**
 * General Purpose Register Functions
 */
void gpr_clear();

#endif //DONGBOYADVANCE_CPU_H