#include "memory_bus.h"
#include "cart.h"

uint8_t memory[MEMORY_SIZE];

uint8_t memory_bus_read(const uint16_t addr)
{
    if (addr >= 0x0000 && addr <= 0x3FFF) // Read from ROM bank 00
    {
        return cartridge_data[addr];
    }
    return memory[addr];
}

void memory_bus_write(const uint16_t addr, const uint8_t value)
{
    memory[addr] = value;
}