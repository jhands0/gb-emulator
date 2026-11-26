#include "../include/memory_bus.h"
#include "../include/cart.h"
#include "../include/cart_type.h"
#include "../include/timer.h"
#include "../include/interrupts.h"
#include "../include/ppu.h"
#include <stdio.h>

uint8_t memory[MEMORY_SIZE];
uint8_t eram[ERAM_SIZE];

uint8_t rom_bank_number = 0;
uint8_t ram_bank_number = 0;
bool ram_enabled = false;
bool rom_ram_mode_select = false;

uint8_t memory_bus_read(const uint16_t addr)
{
    if (addr >= 0x0000 && addr <= 0x3FFF) // Read from ROM bank 00
    {
        return cartridge_data[addr];
    }

    const cart_type_info& cart_info = cart_type_data[cartridge_header->cartridge_type];

    if (addr >= 0x4000 && addr <= 0x7FFF) // Read from ROM bank 01-NN
    {
        if (cart_info.type == CART_TYPE::NO_MBC)
        {
            return cartridge_data[addr];
        }
        else if (cart_info.type == CART_TYPE::MBC1)
        {
            const uint16_t ROM_BANK_SIZE = 0x4000; // 16kb rom bank
            uint8_t rom_bank = rom_bank_number > 0 ? rom_bank_number : 1;
            const uint32_t offset = ROM_BANK_SIZE * (rom_bank - 1);
            return cartridge_data[offset + addr];
        }
    }
    if (addr >= 0x8000 && addr <= 0x9FFF) // VRAM
    {
        if (LCDS_PPU_MODE == LCDS_MODE_3_DRAWING)
        {
            return 0xFF;
        }
        return memory[addr];
    }
    if (addr >= 0xA000 && addr <= 0xBFFF) // External RAM
    {
        if (cart_info.type == CART_TYPE::NO_MBC)
        {
            const uint16_t eram_addr = (addr - 0xA000);
            return eram[eram_addr];
        }
        else if (cart_info.type == CART_TYPE::MBC1)
        {
            const uint16_t bank_offset = ram_bank_number * 0x2000;
            const uint16_t eram_addr = (addr - 0xA000) + bank_offset;
            return eram[eram_addr];
        }
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
        if (LCDS_PPU_MODE == LCDS_MODE_2_OAM_SEARCH || LCDS_PPU_MODE == LCDS_MODE_3_DRAWING)
        {
            return 0xFF;
        }
        return memory[addr];
    }
    if (addr >= 0xFEA0 && addr <= 0xFEFF) // Non usable memory
    {
        if (LCDS_PPU_MODE == LCDS_MODE_3_DRAWING)
        {
            return 0xFF;
        }
        return 0x00;
    }
    if (addr >= 0xFF00 && addr <= 0xFF7F) // I/O Registers
    {
        if (addr == 0xFF00)
        {
            return 0x0F;
        }
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

    return memory[addr]; // Unreachable
}

void memory_bus_write(const uint16_t addr, const uint8_t value)
{
    const cart_type_info& cart_info = cart_type_data[cartridge_header->cartridge_type];
    if (cart_info.type == CART_TYPE::MBC1)
    {
        if (addr >= 0x0000 && addr <= 0x1FFF)
        {
            ram_enabled = (value & 0xF0) == 0x0A;
        }
        if (addr >= 0x2000 && addr <= 0x3FFF)
        {
            rom_bank_number = value & 0b00011111;
            const uint32_t rom_size = 32 * (1 << cartridge_header->rom_size);
            const uint8_t number_of_rom_banks = rom_size / 16;
            rom_bank_number = rom_bank_number % number_of_rom_banks;
        }
        if (addr >= 0x4000 && addr <= 0x5FFF)
        {
            if (rom_ram_mode_select)
            {
                ram_bank_number = value & 0b00000011;
            }
            else
            {
                rom_bank_number = (rom_bank_number & 0b00011111) | ((value & 0b00000011) << 5);
            }
        }
        if (addr >= 0x6000 && addr <= 0x7FFF)
        {
            rom_ram_mode_select = value & 1;
        }
    }

    if (addr >= 0x8000 && addr <= 0x9FFF) // VRAM
    {
        if (LCDS_PPU_MODE == LCDS_MODE_3_DRAWING)
        {
            return;
        }
        memory[addr] = value;
    }
    if (addr >= 0xA000 && addr <= 0xBFFF) // External RAM
    {
        if (cart_info.type == CART_TYPE::NO_MBC)
        {
            eram[addr - 0xA000] = value;
        }
        else if (cart_info.type == CART_TYPE::MBC1)
        {
            const uint16_t RAM_BANK_SIZE = 0x2000; // 8kb ram bank
            const uint32_t offset = RAM_BANK_SIZE * ram_bank_number;
            const uint16_t eram_addr = offset + (addr - 0xA000);
            eram[eram_addr] = value;
        }
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
        if (LCDS_PPU_MODE == LCDS_MODE_2_OAM_SEARCH || LCDS_PPU_MODE == LCDS_MODE_3_DRAWING)
        {
            return;
        }
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
        else if (addr == 0xFF40)
        {
            ppu_on_lcd_control_write(value);
        }
        else if (addr == 0xFF41)
        {
            ppu_on_lcd_status_write(value);
        }
        else if (addr == 0xFF45)
        {
            ppu_on_lyc_write(value);
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
        else if (addr >= 0xFF47 && addr <= 0xFF49)
        {
            memory[addr] = value;
            ppu_on_palette_write(value);
        }
        else
        {
            memory[addr] = value;
        }
    }
    if (addr >= 0xFF80 && addr <= 0xFFFE) // HRAM
    {
        memory[addr] = value;
    }
    if (addr == 0xFFFF) // Interrupt Enable Register
    {
        interrupt_enable_write(value);
    }
    
}
