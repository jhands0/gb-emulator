#pragma once
#include "gfx.h"
#include <stdint.h>

extern gfx_context* gfx_debug_ctx;
extern gfx_context* gfx_render_ctx;

extern uint32_t core_clock_counter;
extern bool interrupt_master_enable;
extern uint8_t interrupt_enable_ime_delay;

int core_init();
void core_run();
void core_on_frame();
void core_shutdown();

void core_advance_cpu_clocks(uint8_t clocks);
