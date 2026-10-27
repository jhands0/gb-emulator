#pragma once

#include <stdint.h>

constexpr uint32_t MEMORY_SIZE = 64 * 1024

extern uint8_t memory[MEMORY_SIZE];

uint8_t memory_bus_read(const uint16_t addr);
void memory_bus_write(const uint16_t addr, const uint8_t value);