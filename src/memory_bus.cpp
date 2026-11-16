#include "memory_bus.h"
#include "cart.h"
#include "cart_type.h"
#include "timer.h"
#include "interrupts.h"
#include <stdio.h>

uint8_t memory[MEMORY_SIZE];
uint8_t eram[ERAM_SIZE];

uint8_t memory_bus_read(const uint16_t addr)
{
    if (addr >= 0x0000 && addr <= 0x3FFF) // Read from ROM bank 00
    {
        return cartridge_data[addr];
    }
    if (addr >= 0x4000 && addr <= 0x7FFF) // Read from ROM bank 01-NN
    {
        return cartridge_data[addr];
    }
    if (addr >= 0x8000 && addr <= 0x9FFF) // VRAM
    {
        return memory[addr];
    }
    if (addr >= 0xA000 && addr <= 0xBFFF) // External RAM
    {
        const uint16_t eram_addr = {addr - 0xA000};
        return eram[eram_addr];
    }
    if (addr >= 0xC000 && addr <= 0xCFFF) // Work RAM bank 0
    {
        return memory[addr];
    }
    if (addr >= 0xD000 && addr <= 0xDFFF) // Work RAM bank 1-N
    {
        return memory[addr];
    }
    if (addr >= 0xE000 && addr <= 0xFDFF) // Echo RAM
    {
        return memory[addr - 0x2000];
    }
    if (addr >= 0xFE00 && addr <= 0xFE9F) // Object attribute memory (Sprites)
    {
        return memory[addr];
    }
    if (addr >= 0xFEA0 && addr <= 0xFEFF) // Non usable memory
    {
        return 0x00;
    }
    if (addr >= 0xFF00 && addr <= 0xFF7F) // I/O Registers
    {
        return memory[addr];
    }
    if (addr >= 0xFF80 && addr <= 0xFFFE) // HRAM
    {
        return memory[addr];
    }
    if (addr == 0xFFFF) // Interrupt Enable Register
    {
        return memory[addr];
    }
}

void memory_bus_write(const uint16_t addr, const uint8_t value)
{
    if (addr >= 0x8000 && addr <= 0x9FFF) // VRAM
    {
        memory[addr] = value;
    }
    if (addr >= 0xA000 && addr <= 0xBFFF) // External RAM
    {
        const uint16_t eram_addr = {addr - 0xA000};
        eram[eram_addr] = value
    }
    if (addr >= 0xC000 && addr <= 0xCFFF) // Work RAM bank 0
    {
        memory[addr] = value;
    }
    if (addr >= 0xD000 && addr <= 0xDFFF) // Work RAM bank 1-N
    {
        memory[addr] = value;
    }
    if (addr >= 0xE000 && addr <= 0xFDFF) // Echo RAM
    {
        memory[addr - 0x2000] = value;
    }
    if (addr >= 0xFE00 && addr <= 0xFE9F) // Object attribute memory (OAM) (Sprites)
    {
        memory[addr] = value;
    }
    if (addr >= 0xFEA0 && addr <= 0xFEFF) // Non usable memory
    {
        // Memory is not usable
    }
    if (addr >= 0xFF00 && addr <= 0xFF7F) // I/O Registers
    {
        if (addr == 0xFF02 && value == 0x81) // Blargg test serial output
        {
            char c = memory[0xFF01];
            printf("%c", c);
        }
        else if (addr == 0xFF04) // Timer DIV
        {
            timer_on_div_write(value);
        }
        else if (addr == 0xFF07) // Timer control
        {
            memory[addr] = value & 0b00000111;
        }
        else if (addr == 0xFF0F)
        {
            interrupt_flag_write(value);
        }
        else if (addr == 0xFF46) // OAM direct memory access
        {
            uint16_t source_addr = (value * 0x100);
            const uint16_t dest = 0xFE00;
            for (uint8_t i = 0; i < 160; i++)
            {
                memory[dest + i] = memory_bus_read(source_addr + i);
            }
        }
        else
        {
            memory[addr] = value;
        }
    }
    if (addr >= 0xFF80 && addr <= 0xFFFE) // HRAM
    {
        return memory[addr];
    }
    if (addr == 0xFFFF) // Interrupt Enable Register
    {
        interrupt_enable_write(value);
    }
    
}