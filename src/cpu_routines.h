#pragma once

#define cpu_routine_ld_16(reg_hi, reg_lo)           \
{                                                   \
    core_advance_cpu_clocks(4);                     \
    reg_lo = memory_bus_read(cpu_registers.pc++);   \
    core_advance_cpu_clocks(4);                     \
    reg_hi = memory_bus_read(cpu_registers.pc++);   \
    core_advance_cpu_clocks(4);                     \
}