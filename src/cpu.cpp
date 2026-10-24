#include "cpu.h"
#include "cpu_instructions.h"
#include "cpu_routines.h"
#include "memory_bus.h"
#include "emulator_core"
#include <stdio.h>

gb_cpu_registers cpu_registers;
uint8_t cpu_current_op_code = 0;
uint32_t cpu_instruction_counter = 0;
void *cpu_current_instruction_execute = nullptr;

void cpu_reset()
{
    //Post boot rom register values
    cpu_registers.af = 0x01B0;
	cpu_registers.bc = 0x0013;
	cpu_registers.de = 0x00D8;
	cpu_registers.hl = 0x014D;
	cpu_registers.sp = 0xFFFE;
	cpu_registers.pc = 0x0100;
}

void cpu_fetch()
{
    cpu_current_op_code = memory_bus_read(cpu_registers.pc++);
    const gb_cpu_instruction& instruction = instructions[cpu_current_op_code];
    cpu_current_instruction_execute = instruction.execute;
}

bool cpu_execute()
{
    if (!cpu_current_instruction_execute)
    {
        const gb_cpu_instruction& instruction = instructions[cpu_current_op_code];
        const uint8_t pchi = ((cpu_registers.pc - 1) & 0xFF00) >> 8;
        const uint8_t pclo = ((cpu_registers.pc - 1) & 0xFF);
        printf("Unknown instruction at: %.2X%.2X (%s), count %i\n", pchi, pclo, instruction.disassembly, cpu_instruction_counter);
        return false;
    }
    //Execute instruction
    ((cpu_execute_op)cpu_current_instruction_execute)();
    return true;
}

void cpu_noop()         //0x00
{
    core_advance_cpu_clocks(4);
}

void cpu_ld_bc_n16()    //0x01
{
    cpu_routine_ld_16(cpu_registers.b, cpu_registers.c);
}

void cpu_inc_bc()       //0x03
{
    cpu_routine_inc_16(cpu_registers.bc);
}

void cpu_inc_b()        //0x04
{
    cpu_routine_inc_8(cpu_registers.b);
}

void cpu_dec_b()        //0x05
{
    cpu_routine_dec_8(cpu_registers.b);
}

void cpu_ld_b_n8()      //0x06
{
    cpu_routine_ld_8(cpu_registers.b);
}

void cpu_add_hl_bc()    //0x09
{
    cpu_routine_add_hl_16(cpu_registers.bc);
}

void cpu_dec_bc()       //0x0B
{
    cpu_routine_dec_16(cpu_registers.bc);
}

void cpu_inc_c()        //0x0C
{
    cpu_routine_inc_8(cpu_registers.c);
}

void cpu_dec_c()        //0x0D
{
    cpu_routine_dec_8(cpu_registers.c);
}

void cpu_ld_c_n8()      //0x0E
{
    cpu_routine_ld_8(cpu_registers.c);
}

void cpu_ld_de_n16()    //0x11
{
    cpu_routine_ld_16(cpu_registers.d, cpu_registers.e);
}

void cpu_inc_de()       //0x13
{
    cpu_routine_inc_16(cpu_registers.de);
}

void cpu_inc_d()        //0x14
{
    cpu_routine_inc_8(cpu_registers.d);
}

void cpu_dec_d()        //0x15
{
    cpu_routine_dec_8(cpu_registers.d);
}

void cpu_ld_d_n8()      //0x16
{
    cpu_routine_ld_8(cpu_registers.d);
}

void cpu_add_hl_de()    //0x19
{
    cpu_routine_add_hl_16(cpu_registers.de);
}

void cpu_dec_de()       //0x1B
{
    cpu_routine_dec_16(cpu_registers.de);
}

void cpu_inc_e()        //0x1C
{
    cpu_routine_inc_8(cpu_registers.e);
}

void cpu_dec_e()        //0x1D
{
    cpu_routine_dec_8(cpu_registers.e)
}

void cpu_ld_e_n8()      //0x1E
{
    cpu_routine_ld_8(cpu_registers.e);   
}

void cpu_ld_hl_n16()    //0x21
{
    cpu_routine_ld_16(cpu_registers.h, cpu_registers.l);
}

void cpu_inc_hl()       //0x23
{
    cpu_routine_inc_16(cpu_registers.hl);
}

void cpu_inc_h()        //0x24
{
    cpu_routine_inc_8(cpu_registers.h);
}

void cpu_dec_h()        //0x25
{
    cpu_routine_dec_8(cpu_registers.h);
}

void cpu_ld_h_n8()      //0x26
{
    cpu_routine_ld_8(cpu_registers.h);
}

void cpu_dec_hl()       //0x2B
{
    cpu_routine_dec_16(cpu_registers.hl);
}

void cpu_inc_l()        //0x2C
{
    cpu_routine_inc_8(cpu_registers.l);
}

void cpu_dec_l()        //0x2D
{
    cpu_routine_dec_8(cpu_registers.l);
}

void cpu_ld_l_n8()      //0x2E
{
    cpu_routine_ld_8(cpu_registers.l);
}

void cpu_ld_sp_n16()    //0x31
{
    cpu_routine_ld_16(cpu_registers.s, cpu_registers.p);
}

void cpu_inc_sp()       //0x33
{
    cpu_routine_inc_16(cpu_registers.sp);
}

void cpu_add_hl_sp()    //0x39
{
    cpu_routine_add_hl_16(cpu_registers.sp);
}

void cpu_dec_sp()       //0x3B
{
    cpu_routine_dec_16(cpu_registers.sp);
}

void cpu_inc_a()        //0x3C
{
    cpu_routine_inc_8(cpu_registers.a);
}

void cpu_dec_a()        //0x3D
{
    cpu_routine_dec_8(cpu_registers.a);
}

void cpu_ld_a_n8()      //0x3E
{
    cpu_routine_ld_8(cpu_registers.a);
}

void cpu_add_a_b()      //0x80
{
    cpu_routine_add_a_8(cpu_registers.b);
}

void cpu_add_a_c()      //0x81
{
    cpu_routine_add_a_8(cpu_registers.c);
}

void cpu_add_a_d()      //0x82
{
    cpu_routine_add_a_8(cpu_registers.d);
}

void cpu_add_a_e()      //0x83
{
    cpu_routine_add_a_8(cpu_registers.e);
}

void cpu_add_a_h()      //0x84
{
    cpu_routine_add_a_8(cpu_registers.h);
}

void cpu_add_a_l()      //0x85
{
    cpu_routine_add_a_8(cpu_registers.l);
}

void cpu_xor_a()        //0xAF
{
    cpu_registers.a = 0;
    SET_FLAG_SUBTRACT(0);
    SET_FLAG_CARRY(0);
    SET_FLAG_HALF_CARRY(0);
    SET_FLAG_ZERO(1);
    core_advance_cpu_clocks(4);
}

void cpu_jp_a16()       //0xC3
{
    core_advance_cpu_clocks(4);
    uint32_t temp = memory_bus_read(cpu_registers.pc++);
    cpu_registers.pc &= 0xFFFF; //Correct program counter in case of overflow
    core_advance_cpu_clocks(4);
    temp |= ((uint32_t) memory_bus_read(cpu_registers.pc++)) << 8;
    cpu_registers.pc &= 0xFFFF;
    core_advance_cpu_clocks(4);
    cpu_registers.pc = temp;
    core_advance_cpu_clocks(4);
}