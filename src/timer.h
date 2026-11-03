#pragma once

#include <stdint.h>

struct gb_timer_registers
{
    uint8_t timer_div,
    uint8_t timer_tima,
    uint8_t timer_tma,
    uint8_t timer_tac,
};

extern gb_timer_registers* timer_registers;

void timer_init();
void timer_check_clock_edges(const uint16_t prev_sysclk);
void timer_increase_div(const uint8_t cycles);
void timer_advance_clocks(const uint8_t cycles);
void timer_on_div_write(const uint8_t value);
void timer_tick_time();