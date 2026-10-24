#pragma once
#include <stdint.h>

#define SET_FLAG_ZERO(value)          cpu_registers.f = (cpu_registers.f & ~(1UL << 7)) | ((value) << 7);
#define GET_FLAG_ZERO                 ((cpu_registers.f & (1UL << 7)) >> 7)
#define SET_FLAG_SUBTRACT(value)      cpu_registers.f = (cpu_registers.f & ~(1UL << 6)) | ((value) << 6);
#define GET_FLAG_SUBTRACT             ((cpu_registers.f & (1UL << 6)) >> 6)
#define SET_FLAG_HALF_CARRY(value)    cpu_registers.f = (cpu_registers.f & ~(1UL << 5)) | ((value) << 5);
#define GET_FLAG_HALF_CARRY           ((cpu_registers.f & (1UL << 5)) >> 5)
#define SET_FLAG_CARRY(value)         cpu_registers.f = (cpu_registers.f & ~(1UL << 4)) | ((value) << 4);
#define GET_FLAG_CARRY                ((cpu_registers.f & (1UL << 4)) >> 4)

struct gb_cpu_registers {
    struct {
        union {
            struct {
                uint8_t f; //flags
                uint8_t a; //accumulator
            };
            uint16_t af;
        };
    };
    struct {
        union {
            struct {
                uint8_t c;
                uint8_t b;
            }; 
            uint16_t bc;
        };
    };
    struct {
        union {
            struct {
                uint8_t e;
                uint8_t d;
            }; 
            uint16_t de;
        };
    };
    struct {
        union {
            struct {
                uint8_t l;
                uint8_t h;
            }; 
            uint16_t hl;
        };
    };
    struct {
        union {
            struct {
                uint8_t p;
                uint8_t s;
            }; 
            uint16_t sp; //stack pointer
        };
    };
    uint16_t pc; //program counter
};

typedef void (*cpu_execute_op){};

extern gb_cpu_registers cpu_registers;

void cpu_reset();
void cpu_fetch();
bool cpu_execute();


void cpu_nop();         //0x00
void cpu_ld_bc_n16();   //0x01

void cpu_inc_bc();      //0x03
void cpu_inc_b();       //0x04
void cpu_dec_b();       //0x05
void cpu_ld_b_n8();     //0x06

void cpu_add_hl_bc();   //0x09

void cpu_dec_bc();      //0x0B
void cpu_inc_c();       //0x0C
void cpu_dec_c();       //0x0D
void cpu_ld_c_n8();     //0x0E

void cpu_ld_de_n16();   //0x11

void cpu_inc_de();      //0x13
void cpu_inc_d();       //0x14
void cpu_dec_d();       //0x15
void cpu_ld_d_n8();     //0x16

void cpu_add_hl_de();   //0x19

void cpu_dec_de();      //0x1B
void cpu_inc_e();       //0x1C
void cpu_dec_e();       //0x1D
void cpu_ld_e_n8();     //0x1E

void cpu_ld_hl_n16();   //0x21

void cpu_inc_hl();      //0x23
void cpu_inc_h();       //0x24
void cpu_dec_h();       //0x25
void cpu_ld_h_n8();     //0x26

void cpu_dec_hl();      //0x2B
void cpu_inc_l();       //0x2C
void cpu_dec_l();       //0x2D
void cpu_ld_l_n8();     //0x2E

void cpu_ld_sp_n16();   //0x31

void cpu_inc_sp();      //0x33

void cpu_add_hl_sp();   //0x39

void cpu_dec_sp();      //0x3B
void cpu_inc_a();       //0x3C
void cpu_dex_a();       //0x3D
void cpu_ld_a_n8();     //0x3E

void cpu_xor_a();       //0xAF

void cpu_jp_a16();      //0xC3
