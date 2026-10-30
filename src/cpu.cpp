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

void cpu_ld_bc_a()      //0x02
{
    cpu_routine_ld_ptr_8(cpu_registers.bc, cpu_registers.a);
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

void cpu_rlca()         //0x07
{
    core_advance_cpu_clocks(4);
    SET_FLAG_ZERO(0);
    SET_FLAG_SUBTRACT(0);
    SET_FLAG_HALF_CARRY(0);
    SET_FLAG_CARRY((cpu_registers.a & 0x80) != 0);
    cpu_registers.a = (cpu_registers.a << 1) | GET_FLAG_CARRY;
}

void cpu_ld_a16_sp()    //0x08
{
    core_advance_cpu_clocks(4);
    uint16_t temp = memory_bus_read(cpu_registers.pc++);
    core_advance_cpu_clocks(4);
    temp |= ((uint16_t)memory_bus_read(cpu_registers.pc++)) << 8;
    core_advance_cpu_clocks(4);
    memory_bus_write(temp++, (cpu_registers.sp & 0xFF));
    core_advance_cpu_clocks(4);
    memory_bus_write(temp, ((cpu_registers.sp & 0xFF00) >> 8));
    core_advance_cpu_clocks(4);
}

void cpu_add_hl_bc()    //0x09
{
    cpu_routine_add_hl_16(cpu_registers.bc);
}

void cpu_ld_a_bc()      //0x0A
{
    cpu_routine_ld_ptr_16(cpu_registers.a, cpu_registers.bc);
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

void cpu_rrca()         //0x0F
{
    core_advance_cpu_clocks(0);
    SET_FLAG_ZERO(0);
    SET_FLAG_SUBTRACT(0);
    SET_FLAG_HALF_CARRY(0);
    SET_FLAG_CARRY((cpu_registers.a & 0x01) != 0);
    cpu_registers.a = (cpu_registers.a >> 1) | (GET_FLAG_CARRY << 7);
}

void cpu_ld_de_n16()    //0x11
{
    cpu_routine_ld_16(cpu_registers.d, cpu_registers.e);
}

void cpu_ld_de_a()      //0x12
{
    cpu_routine_ld_ptr_8(cpu_registers.de, cpu_registers.a);
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

void cpu_rla()          //0x17
{
    core_advance_cpu_clocks(4);
    SET_FLAG_ZERO(0);
    SET_FLAG_SUBTRACT(0);
    SET_FLAG_HALF_CARRY(0);
    uint8_t temp = GET_FLAG_CARRY;
    SET_FLAG_CARRY((cpu_registers.a & 0x80) != 0);
    cpu_registers.a = (cpu_registers.a << 1) | temp;
}

void cpu_jr_e8()        //0x18
{
    core_advance_cpu_clocks(4);
    uint8_t temp = memory_bus_read(cpu_registers.pc++);
    core_advance_cpu_clocks(4);
    cpu_registers.pc = (cpu_registers.pc + (int8_t)temp) & 0xFFFF;
    core_advance_cpu_clocks(4);
}

void cpu_add_hl_de()    //0x19
{
    cpu_routine_add_hl_16(cpu_registers.de);
}

void cpu_ld_a_hl()      //0x1A
{
    cpu_routine_ld_ptr_16(cpu_registers.a, cpu_registers.hl);
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

void cpu_rra()          //0x1F
{
    core_advance_cpu_clocks(4);
    SET_FLAG_ZERO(0);
    SET_FLAG_SUBTRACT(0);
    SET_FLAG_HALF_CARRY(0);
    uint8_t temp = GET_FLAG_CARRY;
    SET_FLAG_CARRY((cpu_registers.a & 0x01));
    cpu_registers.a = (cpu_registers.a >> 1) | (temp << 7);
}

void cpu_jr_nz_e8()     //0x20
{
    cpu_routine_jr_conditional(GET_FLAG_ZERO == 0);
}

void cpu_ld_hl_n16()    //0x21
{
    cpu_routine_ld_16(cpu_registers.h, cpu_registers.l);
}

void cpu_ldi_hl_a()     //0x22
{
    core_advance_cpu_clocks(4);
    memory_bus_write(cpu_registers.hl, cpu_registers.a);
    cpu_registers.hl = (cpu_registers.hl + 1) & 0xFFFF;
    core_advance_cpu_clocks(4);
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

void cpu_jr_z_e8()      //0x28
{
    cpu_routine_jr_conditional(GET_FLAG_ZERO == 1);
}

void cpu_add_hl_hl()    //0x29
{
    core_advance_cpu_clocks(4);
    SET_FLAG_SUBTRACT(0);
    SET_FLAG_CARRY((cpu_registers.hl & 0x8000) != 0);
    SET_FLAG_HALF_CARRY((cpu_registers.hl & 0x0800) != 0);
    core_advance_cpu_clocks(4);
    cpu_registers.hl = (cpu_registers << 1) & 0xFFFF;
}

void cpu_ldi_a_hl()     //0x2A
{
    core_advance_cpu_clocks(4);
    cpu_registers.a = memory_bus_read(cpu_registers.hl);
    core_advance_cpu_clocks(4);
    cpu_registers.hl = (cpu_registers.hl + 1) & 0xFFFF;
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

void cpu_jr_nc_e8()     //0x30
{
    cpu_routine_jr_conditional(GET_FLAG_CARRY == 0);
}

void cpu_ld_sp_n16()    //0x31
{
    cpu_routine_ld_16(cpu_registers.s, cpu_registers.p);
}

void cpu_ldd_hl_a()     //0x32
{
    core_advance_cpu_clocks(4);
    memory_bus_write(cpu_registers.hl, cpu_registers.a);
    cpu_registers.hl = (cpu_registers.hl - 1) & 0xFFFF;
    core_advance_cpu_clocks(4);
}

void cpu_inc_sp()       //0x33
{
    cpu_routine_inc_16(cpu_registers.sp);
}

void cpu_inc__hl()       //0x34
{
    core_advance_cpu_clocks(4);
    uint32_t temp = memory_bus_read(cpu_registers.hl);
    core_advance_cpu_clocks(4);
    SET_FLAG_SUBTRACT(0);
    SET_FLAG_HALF_CARRY((temp & 0xF) == 0xF);
    temp = (temp + 1) & 0xFF;
    SET_FLAG_ZERO(temp == 0);
    core_advance_cpu_clocks(4);
    memory_bus_write(cpu_registers.hl, temp);
}

void cpu_dec__hl()      //0x35
{
    core_advance_cpu_clocks(4);
    uint32_t temp = memory_bus_read(cpu_registers.hl);
    core_advance_cpu_clocks(4);
    SET_FLAG_SUBTRACT(1);
    SET_FLAG_HALF_CARRY((temp & 0xF) == 0xF);
    temp = (temp - 1) & 0xFF;
    SET_FLAG_ZERO(temp == 0);
    core_advance_cpu_clocks(4);
    memory_bus_write(cpu_registers.hl, temp);
}

void cpu_ld_hl_n8()     //0x36
{
    core_advance_cpu_clocks(4);
    uint8_t temp = memory_bus_read(cpu_registers.pc++);
    core_advance_cpu_clocks(4);
    memory_bus_write(cpu_registers.hl, temp);
    core_advance_cpu_clocks(4);
}

void cpu_jr_c_e8()      //0x38
{
    cpu_routine_jr_conditional(GET_FLAG_CARRY == 1);
}

void cpu_add_hl_sp()    //0x39
{
    cpu_routine_add_hl_16(cpu_registers.sp);
}

void cpu_ldd_a_hl()     //0x3A
{
    core_advance_cpu_clocks(4);
    cpu_registers.a = memory_bus_read(cpu_registers.hl);
    core_advance_cpu_clocks(4);
    cpu_registers.hl = (cpu_registers.hl - 1) & 0xFFFF;
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

void cpu_ld_b_b()       //0x40
{
    core_advance_cpu_clocks(4);
}

void cpu_ld_b_c()       //0x41
{
    core_advance_cpu_clocks(4);
    cpu_registers.b = cpu_registers.c;
}

void cpu_ld_b_d()       //0x42
{
    core_advance_cpu_clocks(4);
    cpu_registers.b = cpu_registers.d;
}

void cpu_ld_b_e()       //0x43
{
    core_advance_cpu_clocks(4);
    cpu_registers.b = cpu_registers.e;
}

void cpu_ld_b_h()       //0x44
{
    core_advance_cpu_clocks(4);
    cpu_registers.b = cpu_registers.h;
}

void cpu_ld_b_l()       //0x45
{
    core_advance_cpu_clocks(4);
    cpu_registers.b = cpu_registers.l;
}

void cpu_ld_b_hl()      //0x46
{
    cpu_routine_ld_ptr_16(cpu_registers.b, cpu_registers.hl);
}

void cpu_ld_b_a()       //0x47
{
    core_advance_cpu_clocks(4);
    cpu_registers.b = cpu_registers.a;
}

void cpu_ld_c_b()       //0x48
{
    core_advance_cpu_clocks(4);
    cpu_registers.c = cpu_registers.b;
}

void cpu_ld_c_c()       //0x49
{
    core_advance_cpu_clocks(4);
}

void cpu_ld_c_d()       //0x4A
{
    core_advance_cpu_clocks(4);
    cpu_registers.c = cpu_registers.d;
}

void cpu_ld_c_e()       //0x4B
{
    core_advance_cpu_clocks(4);
    cpu_registers.c = cpu_registers.e;
}

void cpu_ld_c_h()       //0x4C
{
    core_advance_cpu_clocks(4);
    cpu_registers.c = cpu_registers.h;
}

void cpu_ld_c_l()       //0x4D
{
    core_advance_cpu_clocks(4);
    cpu_registers.c = cpu_registers.l;
}

void cpu_ld_c_hl()      //0x4E
{
    cpu_routine_ld_ptr_16(cpu_registers.c, cpu_registers.hl);
}

void cpu_ld_c_a()       //0x4F
{
    core_advance_cpu_clocks(4);
    cpu_registers.c = cpu_registers.a;
}

void cpu_ld_d_b()       //0x50
{
    core_advance_cpu_clocks(4);
    cpu_registers.d = cpu_registers.b;
}

void cpu_ld_d_c()       //0x51
{
    core_advance_cpu_clocks(4);
    cpu_registers.d = cpu_registers.c;
}

void cpu_ld_d_d()       //0x52
{
    core_advance_cpu_clocks(4);
}

void cpu_ld_d_e()       //0x53
{
    core_advance_cpu_clocks(4);
    cpu_registers.d = cpu_registers.e;
}

void cpu_ld_d_h()       //0x54
{
    core_advance_cpu_clocks(4);
    cpu_registers.d = cpu_registers.h;
}

void cpu_ld_d_l()       //0x55
{
    core_advance_cpu_clocks(4);
    cpu_registers.d = cpu_registers.l;
}

void cpu_ld_d_hl()      //0x56
{
    cpu_routine_ld_ptr_16(cpu_registers.d, cpu_registers.hl);
}

void cpu_ld_d_a()       //0x57
{
    core_advance_cpu_clocks(4);
    cpu_registers.d = cpu_registers.a;
}

void cpu_ld_e_b()       //0x58
{
    core_advance_cpu_clocks(4);
    cpu_registers.e = cpu_registers.b;
}

void cpu_ld_e_c()       //0x59
{
    core_advance_cpu_clocks(4);
    cpu_registers.e = cpu_registers.c;
}

void cpu_ld_e_d()       //0x5A
{
    core_advance_cpu_clocks(4);
    cpu_registers.e = cpu_registers.d;
}

void cpu_ld_e_e()       //0x5B
{
    core_advance_cpu_clocks(4);
}

void cpu_ld_e_h()       //0x5C
{
    core_advance_cpu_clocks(4);
    cpu_registers.e = cpu_registers.h;
}

void cpu_ld_e_l()       //0x5D
{
    core_advance_cpu_clocks(4);
    cpu_registers.e = cpu_registers.l;
}

void cpu_ld_e_hl()      //0x5E
{
    cpu_routine_ld_ptr_16(cpu_registers.e, cpu_registers.hl);
}

void cpu_ld_e_a()       //0x5F
{
    core_advance_cpu_clocks(4);
    cpu_registers.e = cpu_registers.a;
}

void cpu_ld_h_b()       //0x60
{
    core_advance_cpu_clocks(4);
    cpu_registers.h = cpu_registers.b;
}

void cpu_ld_h_c()       //0x61
{
    core_advance_cpu_clocks(4);
    cpu_registers.h = cpu_registers.c;
}

void cpu_ld_h_d()       //0x62
{
    core_advance_cpu_clocks(4);
    cpu_registers.h = cpu_registers.d;
}

void cpu_ld_h_e()       //0x63
{
    core_advance_cpu_clocks(4);
    cpu_registers.h = cpu_registers.e;
}

void cpu_ld_h_h()       //0x64
{
    core_advance_cpu_clocks(4);
}

void cpu_ld_h_l()       //0x65
{
    core_advance_cpu_clocks(4);
    cpu_registers.h = cpu_registers.l;
}

void cpu_ld_h_hl()      //0x66
{
    cpu_routine_ld_ptr_16(cpu_registers.h, cpu_registers.hl);
}

void cpu_ld_h_a()       //0x67
{
    core_advance_cpu_clocks(4);
    cpu_registers.h = cpu_registers.a;
}

void cpu_ld_l_b()       //0x68
{
    core_advance_cpu_clocks(4);
    cpu_registers.l = cpu_registers.b;
}

void cpu_ld_l_c()       //0x69
{
    core_advance_cpu_clocks(4);
    cpu_registers.l = cpu_registers.c;
}

void cpu_ld_l_d()       //0x6A
{
    core_advance_cpu_clocks(4);
    cpu_registers.l = cpu_registers.d;
}

void cpu_ld_l_e()       //0x6B
{
    core_advance_cpu_clocks(4);
    cpu_registers.l = cpu_registers.e;
}

void cpu_ld_l_h()       //0x6C
{
    core_advance_cpu_clocks(4);
    cpu_registers.l = cpu_registers.h;
}

void cpu_ld_l_l()       //0x6D
{
    core_advance_cpu_clocks(4);
}

void cpu_ld_l_hl()      //0x6E
{
    cpu_routine_ld_ptr_16(cpu_registers.l, cpu_registers.hl);
}

void cpu_ld_l_a()       //0x6F
{
    core_advance_cpu_clocks(4);
    cpu_registers.l = cpu_registers.a;
}

void cpu_ld_hl_b()      //0x70
{
    cpu_routine_ld_ptr_8(cpu_registers.hl, cpu_registers.b)
}

void cpu_ld_hl_c()      //0x71
{
    cpu_routine_ld_ptr_8(cpu_registers.hl, cpu_registers.c)
}

void cpu_ld_hl_d()      //0x72
{
    cpu_routine_ld_ptr_8(cpu_registers.hl, cpu_registers.d)
}

void cpu_ld_hl_e()      //0x73
{
    cpu_routine_ld_ptr_8(cpu_registers.hl, cpu_registers.e)
}

void cpu_ld_hl_h()      //0x74
{
    cpu_routine_ld_ptr_8(cpu_registers.hl, cpu_registers.h)
}

void cpu_ld_hl_l()      //0x75
{
    cpu_routine_ld_ptr_8(cpu_registers.hl, cpu_registers.l)
}

void cpu_ld_hl_a()      //0x77
{
    cpu_routine_ld_ptr_8(cpu_registers.hl, cpu_registers.a)
}

void cpu_ld_a_b()       //0x78
{
    core_advance_cpu_clocks(4);
    cpu_registers.a = cpu_registers.b;
}

void cpu_ld_a_c()       //0x79
{
    core_advance_cpu_clocks(4);
    cpu_registers.a = cpu_registers.c;
}

void cpu_ld_a_d()       //0x7A
{
    core_advance_cpu_clocks(4);
    cpu_registers.a = cpu_registers.d;
}

void cpu_ld_a_e()       //0x7B
{
    core_advance_cpu_clocks(4);
    cpu_registers.a = cpu_registers.e;
}

void cpu_ld_a_h()       //0x7C
{
    core_advance_cpu_clocks(4);
    cpu_registers.a = cpu_registers.h;
}

void cpu_ld_a_l()       //0x7D
{
    core_advance_cpu_clocks(4);
    cpu_registers.a = cpu_registers.l
}

void cpu_ld_a_hl()      //0x7E
{
    cpu_routine_ld_ptr_16(cpu_registers.a, cpu_registers.hl);
}

void cpu_ld_a_a()       //0x7F
{
    core_advance_cpu_clocks(4);
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

void cpu_add_a_hl()     //0x86
{
    core_advance_cpu_clocks(4);
    SET_FLAG_SUBTRACT(0);
    uint32_t temp_a = cpu_registers.a;
    uint32_t temp_hl = memory_bus_read(cpu_registers.hl);
    core_advance_cpu_clocks(4);
    SET_FLAG_HALF_CARRY(((temp_a & 0xF) + (temp_hl & 0xF)) > 0xF);
    cpu_registers.a += temp_hl;
    SET_FLAG_ZERO(cpu_registers.a == 0);
    SET_FLAG_CARRY(temp_a > cpu_registers.a);
}

void cpu_add_a_a()      //0x87
{
    core_advance_cpu_clocks(4);
    SET_FLAG_SUBTRACT(0);
    SET_FLAG_HALF_CARRY((cpu_registers.a & (1 << 3)) != 0);
    SET_FLAG_CARRY((cpu_registers.a & (1 << 7)) != 0);
    cpu_registers.a += cpu_registers.a;
    SET_FLAG_ZERO(cpu_registers.a == 0);
}

void cpu_adc_a_b()      //0x88
{
    cpu_routine_adc_a_8(cpu_registers.b);
}

void cpu_adc_a_c()      //0x89
{
    cpu_routine_adc_a_8(cpu_registers.c);
}

void cpu_adc_a_d()      //0x8A
{
    cpu_routine_adc_a_8(cpu_registers.d);
}

void cpu_adc_a_e()      //0x8B
{
    cpu_routine_adc_a_8(cpu_registers.e);
}

void cpu_adc_a_h()      //0x8C
{
    cpu_routine_adc_a_8(cpu_registers.h);
}

void cpu_adc_a_l()      //0x8D
{
    cpu_routine_adc_a_8(cpu_registers.l);
}

void cpu_adc_a_hl()     //0x8E
{
    core_advance_cpu_clocks(4);
    uint32_t temp_hl = memory_bus_read(cpu_registers.hl);
    core_advance_cpu_clocks(4);
    uint32_t temp_a = cpu_registers.a + temp_hl + GET_FLAG_CARRY;
    SET_FLAG_SUBTRACT(0);
    SET_FLAG_HALF_CARRY((((cpu_registers.a & 0xF) + (temp_hl & 0xF)) + GET_FLAG_CARRY) > 0xF);
    SET_FLAG_CARRY(temp_a > 0xFF);
    temp_a &= 0xFF;
    cpu_registers.a = temp_a;
    SET_FLAG_ZERO(temp_a == 0);
}

void cpu_adc_a_a()      //0x8F
{
    core_advance_cpu_clocks(4);
    SET_FLAG_SUBTRACT(0);
    uint32_t temp = (((uint32_t)cpu_registers.a) << 1) + GET_FLAG_CARRY;
    SET_FLAG_HALF_CARRY((cpu_registers.a & 0x08) != 0);
    SET_FLAG_CARRY(temp > 0xFF);
    temp &= 0xFF;
    cpu_registers.a = temp;
    SET_FLAG_ZERO(temp == 0);
}

void cpu_sub_a_b()      //0x90
{
    cpu_routine_sub_a_8(cpu_registers.b);
}

void cpu_sub_a_c()      //0x91
{
    cpu_routine_sub_a_8(cpu_registers.c);
}

void cpu_sub_a_d()      //0x92
{
    cpu_routine_sub_a_8(cpu_registers.d);
}

void cpu_sub_a_e()      //0x93
{
    cpu_routine_sub_a_8(cpu_registers.e);
}

void cpu_sub_a_h()      //0x94
{
    cpu_routine_sub_a_8(cpu_registers.h);
}

void cpu_sub_a_l()      //0x95
{
    cpu_routine_sub_a_8(cpu_registers.l);
}

void cpu_sub_a_hl()     //0x96
{
    core_advance_cpu_clocks(4);
    uint32_t temp = memory_bus_read(cpu_registers.hl);
    core_advance_cpu_clocks(4);
    SET_FLAG_SUBTRACT(1);
    SET_FLAG_HALF_CARRY((cpu_registers.a & 0xF) < (temp & 0xF));
    SET_FLAG_CARRY(temp > cpu_registers.a);
    cpu_registers.a -= temp;
    SET_FLAG_ZERO(cpu_registers.a == 0);
}

void cpu_sub_a_a()          //0x97
{
    core_advance_cpu_clocks(4);
    SET_FLAG_ZERO(1);
    SET_FLAG_SUBTRACT(1);
    SET_FLAG_HALF_CARRY(0);
    SET_FLAG_CARRY(0);
    cpu_registers.a = 0;
}

void cpu_sbc_a_b()      //0x98
{
    cpu_routine_sbc_a_8(cpu_registers.b);
}

void cpu_sbc_a_c()      //0x99
{
    cpu_routine_sbc_a_8(cpu_registers.c);
}

void cpu_sbc_a_d()      //0x9A
{
    cpu_routine_sbc_a_8(cpu_registers.d);
}

void cpu_sbc_a_e()      //0x9B
{
    cpu_routine_sbc_a_8(cpu_registers.e);
}

void cpu_sbc_a_h()      //0x9C
{
    cpu_routine_sbc_a_8(cpu_registers.h);
}

void cpu_sbc_a_l()      //0x9D
{
    cpu_routine_sbc_a_8(cpu_registers.l);
}

void cpu_sbc_a_hl()     //0x9E
{
    core_advance_cpu_clocks(4);
    uint32_t temp_hl = memory_bus_read(cpu_registers.hl);
    core_advance_cpu_clocks(4);
    uint32_t temp_a = cpu_registers.a - (temp_hl + GET_FLAG_CARRY);
    SET_FLAG_CARRY((temp_a & ~0xFF) != 0);
    SET_FLAG_ZERO((temp_a & 0xFF) == 0);
    SET_FLAG_SUBTRACT(1);
    SET_FLAG_HALF_CARRY(((cpu_registers.a ^ temp_hl ^ temp_a) & 0x10) != 0);
    cpu_registers.a = temp_a;
}

void cpu_sbc_a_a()      //0x9F
{
    core_advance_cpu_clocks(4);
    if (GET_FLAG_CARRY)
    {
        cpu_registers.a == 0xFF;
        SET_FLAG_CARRY(1);
        SET_FLAG_HALF_CARRY(1);
        SET_FLAG_ZERO(0);
    }
    else
    {
        cpu_registers.a = 0;
        SET_FLAG_CARRY(0);
        SET_FLAG_HALF_CARRY(0);
        SET_FLAG_ZERO(1);
    }
    SET_FLAG_SUBTRACT(1);
}

void cpu_and_a_b()      //0xA0
{
    cpu_routine_and_a_8(cpu_registers.b);
}

void cpu_and_a_c()      //0xA1
{
    cpu_routine_and_a_8(cpu_registers.c);
}

void cpu_and_a_d()      //0xA2
{
    cpu_routine_and_a_8(cpu_registers.d);
}

void cpu_and_a_e()      //0xA3
{
    cpu_routine_and_a_8(cpu_registers.e);
}

void cpu_and_a_h()      //0xA4
{
    cpu_routine_and_a_8(cpu_registers.h);
}

void cpu_and_a_l()      //0xA5
{
    cpu_routine_and_a_8(cpu_registers.l);
}

void cpu_and_a_hl()     //0xA6
{
    core_advance_cpu_clocks(4);
    SET_FLAG_HALF_CARRY(1);
    SET_FLAG_SUBTRACT(0);
    SET_FLAG_CARRY(0);
    core_advance_cpu_clocks(4);
    cpu_registers.a &= memory_bus_read(cpu_registers.hl);
    SET_FLAG_ZERO(cpu_registers.a == 0);
}

void cpu_and_a_a()      //0xA7
{
    core_advance_cpu_clocks(4);
    SET_FLAG_HALF_CARRY(1);
    SET_FLAG_SUBTRACT(0);
    SET_FLAG_CARRY(0);
    SET_FLAG_ZERO(cpu_registers.a == 0);
}

void cpu_xor_a_b()      //0xA8
{
    cpu_routine_xor_a_8(cpu_registers.b);
}

void cpu_xor_a_c()      //0xA9
{
    cpu_routine_xor_a_8(cpu_registers.c);
}

void cpu_xor_a_d()      //0xAA
{
    cpu_routine_xor_a_8(cpu_registers.d);
}

void cpu_xor_a_e()      //0xAB
{
    cpu_routine_xor_a_8(cpu_registers.e);
}

void cpu_xor_a_h()      //0xAC
{
    cpu_routine_xor_a_8(cpu_registers.h);
}

void cpu_xor_a_l()      //0xAD
{
    cpu_routine_xor_a_8(cpu_registers.l);
}

void cpu_xor_a_hl()     //0xAE
{
    core_advance_cpu_clocks(4);
    SET_FLAG_SUBTRACT(0);
    SET_FLAG_CARRY(0);
    SET_FLAG_HALF_CARRY(0);
    core_advance_cpu_clocks(4);
    cpu_registers.a ^= memory_bus_read(cpu_registers.hl);
    SET_FLAG_ZERO(cpu_registers.a == 0);
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

void cpu_or_a_b()       //0xB0
{
    cpu_routine_or_a_8(cpu_registers.b);
}

void cpu_or_a_c()       //0xB1
{
    cpu_routine_or_a_8(cpu_registers.c);
}

void cpu_or_a_d()       //0xB2
{
    cpu_routine_or_a_8(cpu_registers.d);
}

void cpu_or_a_e()       //0xB3
{
    cpu_routine_or_a_8(cpu_registers.e);
}

void cpu_or_a_h()       //0xB4
{
    cpu_routine_or_a_8(cpu_registers.h);
}

void cpu_or_a_l()       //0xB5
{
    cpu_routine_or_a_8(cpu_registers.l);
}

void cpu_or_a_hl()      //0xB6
{
    core_advance_cpu_clocks(4);
    SET_FLAG_SUBTRACT(0);
    SET_FLAG_CARRY(0);
    SET_FLAG_HALF_CARRY(0);
    core_advance_cpu_clocks(4);
    cpu_registers.a |= memory_bus_read(cpu_registers.hl);
    SET_FLAG_ZERO(cpu_registers.a == 0);
}

void cpu_or_a_a()       //0xB7
{
    core_advance_cpu_clocks(4);
    SET_FLAG_ZERO(cpu_registers.a == 0);
    SET_FLAG_SUBTRACT(0);
    SET_FLAG_HALF_CARRY(0);
    SET_FLAG_CARRY(0);
}

void cpu_cp_a_b()      //0xB8
{
    cpu_routine_cp_a_8(cpu_registers.b);
}

void cpu_cp_a_c()      //0xB9
{
    cpu_routine_cp_a_8(cpu_registers.c);
}

void cpu_cp_a_d()      //0xBA
{
    cpu_routine_cp_a_8(cpu_registers.d);
}

void cpu_cp_a_e()      //0xBB
{
    cpu_routine_cp_a_8(cpu_registers.e);
}

void cpu_cp_a_h()      //0xBC
{
    cpu_routine_cp_a_8(cpu_registers.h);
}

void cpu_cp_a_l()      //0xBD
{
    cpu_routine_cp_a_8(cpu_registers.l);
}

void cpu_cp_a_hl()      //0xBE
{
    core_advance_cpu_clocks(4);
    SET_FLAG_SUBTRACT(1);
    uint32_t temp = memory_bus_read(cpu_registers.hl);
    core_advance_cpu_clocks(4);
    SET_FLAG_HALF_CARRY((cpu_registers.a & 0xF) < (temp & 0xF));
    SET_FLAG_CARRY((uint32_t)cpu_registers.a < temp);
    SET_FLAG_ZERO(cpu_registers.a == temp);
}

void cpu_cp_a_a()       //0xBF
{
    core_advance_cpu_clocks(4);
    SET_FLAG_ZERO(1);
    SET_FLAG_SUBTRACT(1);
    SET_FLAG_HALF_CARRY(0);
    SET_FLAG_CARRY(0);
}

void cpu_ret_nz()       //0xC0
{
    cpu_routine_ret_conditional(GET_FLAG_ZERO == 0);
}

void cpu_pop_bc()       //0xC1
{
    cpu_routine_pop_16(cpu_registers.b. cpu_registers.c);
}

void cpu_jp_nz_a16()    //0xC2
{
    cpu_routine_jp_conditional(GET_FLAG_ZERO == 0);
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

void cpu_call_nz_a16()  //0xC4
{
    cpu_routine_call_conditional(GET_FLAG_ZERO == 0);
}

void cpu_push_bc()      //0xC5
{
    cpu_routine_push_16(cpu_registers.b, cpu_registers.c);
}

void cpu_rst_00()       //0xC7
{
    cpu_routine_rst(0x00);
}

void cpu_ret_z()        //0xC8
{
    cpu_routine_ret_conditional(GET_FLAG_ZERO == 1);
}

void cpu_jp_z_a16()     //0xCA
{
    cpu_routine_jp_conditional(GET_FLAG_ZERO == 1);
}

void cpu_call_z_a16()   //0xCC
{
    cpu_routine_call_conditional(GET_FLAG_ZERO == 1);
}

void cpu_rst_08()       //0xCF
{
    cpu_routine_rst(0x08);
}

void cpu_ret_nc()       //0xD0
{
    cpu_routine_ret_conditional(GET_FLAG_CARRY == 0);
}

void cpu_pop_de()       //0xD1
{
    cpu_routine_pop_16(cpu_registers.d, cpu_registers.e);
}

void cpu_jp_nc_a16()    //0xD2
{
    cpu_routine_jp_conditional(GET_FLAG_CARRY == 0);
}

void cpu_call_nc_a16()  //0xD4
{
    cpu_routine_call_conditional(GET_FLAG_CARRY == 0);
}

void cpu_push_de()      //0xD5
{
    cpu_routine_push_16(cpu_registers.d, cpu_registers.e);
}

void cpu_rst_10()       //0xD7
{
    cpu_routine_rst(0x10);
}

void cpu_ret_c()        //0xD8
{
    cpu_routine_ret_conditional(GET_FLAG_CARRY == 1);
}

void cpu_jp_c_a16()     //0xDA
{
    cpu_routine_jp_conditional(GET_FLAG_CARRY == 1);
}

void cpu_call_c_a16()   //0xDC
{
    cpu_routine_call_conditional(GET_FLAG_CARRY == 1);
}

void cpu_rst_18()       //0xDF
{
    cpu_routine_rst(0x18);
}

void cpu_pop_hl()       //0xE1
{
    cpu_routine_pop_16(cpu_registers.h, cpu_registers.l);
}

void cpu_push_hl()      //0xE5
{
    cpu_routine_push_16(cpu_registers.h, cpu_registers.l);
}

void cpu_rst_20()       //0xE7
{
    cpu_routine_rst(0x20);
}

void cpu_rst_28()       //0xEF
{
    cpu_routine_rst(0x28);
}

void cpu_pop_af()       //0xF1
{
    cpu_routine_pop_16(cpu_registers.a, cpu_registers.f);
}

void cpu_push_af()      //0xF5
{
    cpu_routine_push_16(cpu_registers.a, cpu_registers.f);
}

void cpu_rst_30()       //0xF7
{
    cpu_routine_rst(0x30);
}

void cpu_rst_38()       //0xFF
{
    cpu_routine_rst(0x38);
}