#pragma once
#include <stdint.h>

extern uint32_t core_clock_counter;
extern bool interrupt_master_enable;
extern uint8_t interrupt_enable_ime_delay;

int core_init();
void core_run();
void core_shutdown();

void core_advance_cpu_clocks(uint8_t clocks);
