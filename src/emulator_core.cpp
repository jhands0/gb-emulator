#include "../include/emulator_core.h"

#include "../include/cart.h"
#include "../include/cpu.h"
#include "../include/timer.h"
#include "../include/memory_bus.h"
#include "../include/ppu.h"
#include <cstring>


gfx_context* gfx_debug_ctx = nullptr;
gfx_context* gfx_render_ctx = nullptr;

void core_init_gfx_contexts();

uint32_t core_clock_counter = 0;
bool core_quit_requested = false;

int core_init()
{
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
    {
        return -1;
    }

    const char* filename = "../blargg-test-roms/";

    if (!cart_load(filename))
    {
        return -1;
    }

    cart_print_info();

    core_init_gfx_contexts();

    timer_init();

    return 0;
}

void core_run()
{
    memset(memory, 0, MEMORY_SIZE);
    cpu_reset();

    while (!core_quit_requested) 
    {
        cpu_tick();
    }

    
}

void core_shutdown()
{
    SDL_Quit();
}

void core_advance_cpu_clocks(uint8_t clocks)
{
    timer_advance_clocks(clocks);
    core_clock_counter += clocks;

    if (interrupt_enable_ime_delay > 0)
    {
        for (uint8_t c = 0; c < clocks; c++)
        {
            interrupt_enable_ime_delay--;
            if (interrupt_enable_ime_delay == 0)
            {
                interrupt_master_enable = true;
                break;
            }
        }
    }
}

void core_init_gfx_contexts()
{
    const SDL_Color COLOR_BLACK = { 0, 0, 0, 0 };
    gfx_debug_ctx = gfx_init(512, 512, "Debug");
    gfx_clear(gfx_debug_ctx, COLOR_BLACK);
    gfx_update(gfx_debug_ctx);

    gfx_render_ctx = gfx_init(LCD_PIXELS_WIDTH * PPU_RENDER_SCALE, LCD_PIXELS_HEIGHT * PPU_RENDER_SCALE, "GB-Emulator");
    gfx_clear(gfx_render_ctx, COLOR_BLACK);
    gfx_update(gfx_render_ctx);
}
