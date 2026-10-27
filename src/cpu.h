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
void cpu_rlca();        //0x07

void cpu_add_hl_bc();   //0x09

void cpu_dec_bc();      //0x0B
void cpu_inc_c();       //0x0C
void cpu_dec_c();       //0x0D
void cpu_ld_c_n8();     //0x0E
void cpu_rrca();        //0x0F

void cpu_ld_de_n16();   //0x11

void cpu_inc_de();      //0x13
void cpu_inc_d();       //0x14
void cpu_dec_d();       //0x15
void cpu_ld_d_n8();     //0x16
void cpu_rla();         //0x17

void cpu_add_hl_de();   //0x19

void cpu_dec_de();      //0x1B
void cpu_inc_e();       //0x1C
void cpu_dec_e();       //0x1D
void cpu_ld_e_n8();     //0x1E
void cpu_rra();

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

void cpu_ld_b_b();      //0x40
void cpu_ld_b_c();      //0x41
void cpu_ld_b_d();      //0x42
void cpu_ld_b_e();      //0x43
void cpu_ld_b_h();      //0x44
void cpu_ld_b_l();      //0x45

void cpu_ld_b_a();      //0x47
void cpu_ld_c_b();      //0x48
void cpu_ld_c_c();      //0x49
void cpu_ld_c_d();      //0x4A
void cpu_ld_c_e();      //0x4B
void cpu_ld_c_h();      //0x4C
void cpu_ld_c_l();      //0x4D

void cpu_ld_c_a();      //0x4F
void cpu_ld_d_b();      //0x50
void cpu_ld_d_c();      //0x51
void cpu_ld_d_d();      //0x52
void cpu_ld_d_e();      //0x53
void cpu_ld_d_h();      //0x54
void cpu_ld_d_l();      //0x55

void cpu_ld_d_a();      //0x57
void cpu_ld_e_b();      //0x58
void cpu_ld_e_c();      //0x59
void cpu_ld_e_d();      //0x5A
void cpu_ld_e_e();      //0x5B
void cpu_ld_e_h();      //0x5C
void cpu_ld_e_l();      //0x5D

void cpu_ld_e_a();      //0x5F
void cpu_ld_h_b();      //0x60
void cpu_ld_h_c();      //0x61
void cpu_ld_h_d();      //0x62
void cpu_ld_h_e();      //0x63
void cpu_ld_h_h();      //0x64
void cpu_ld_h_l();      //0x65

void cpu_ld_h_a();      //0x67
void cpu_ld_l_b();      //0x68
void cpu_ld_l_c();      //0x69
void cpu_ld_l_d();      //0x6A
void cpu_ld_l_e();      //0x6B
void cpu_ld_l_h();      //0x6C
void cpu_ld_l_l();      //0x6D

void cpu_ld_l_a();      //0x6F

void cpu_ld_a_b();      //0x78
void cpu_ld_a_c();      //0x79
void cpu_ld_a_d();      //0x7A
void cpu_ld_a_e();      //0x7B
void cpu_ld_a_h();      //0x7C
void cpu_ld_a_l();      //0x7D

void cpu_ld_a_a();      //0x7F
void cpu_add_a_b();     //0x80
void cpu_add_a_c();     //0x81
void cpu_add_a_d();     //0x82
void cpu_add_a_e();     //0x83
void cpu_add_a_h();     //0x84
void cpu_add_a_l();     //0x85

void cpu_adc_a_b();     //0x88
void cpu_adc_a_c();     //0x89
void cpu_adc_a_d();     //0x8A
void cpu_adc_a_e();     //0x8B
void cpu_adc_a_h();     //0x8C
void cpu_adc_a_l();     //0x8D

void cpu_sub_a_b();     //0x90
void cpu_sub_a_c();     //0x91
void cpu_sub_a_d();     //0x92
void cpu_sub_a_e();     //0x93
void cpu_sub_a_h();     //0x94
void cpu_sub_a_l();     //0x95

void cpu_sbc_a_b();     //0x98
void cpu_sbc_a_c();     //0x99
void cpu_sbc_a_d();     //0x9A
void cpu_sbc_a_e();     //0x9B
void cpu_sbc_a_h();     //0x9C
void cpu_sbc_a_l();     //0x9D

void cpu_and_a_b();     //0xA0
void cpu_and_a_c();     //0xA1
void cpu_and_a_d();     //0xA2
void cpu_and_a_e();     //0xA3
void cpu_and_a_h();     //0xA4
void cpu_and_a_l();     //0xA5

void cpu_xor_a_b();     //0xA8
void cpu_xor_a_c();     //0xA9
void cpu_xor_a_d();     //0xAA
void cpu_xor_a_e();     //0xAB
void cpu_xor_a_h();     //0xAC
void cpu_xor_a_l();     //0xAD

void cpu_xor_a();       //0xAF

void cpu_or_a_b();      //0xB0
void cpu_or_a_c();      //0xB1
void cpu_or_a_d();      //0xB2
void cpu_or_a_e();      //0xB3
void cpu_or_a_h();      //0xB4
void cpu_or_a_l();      //0xB5

void cpu_cp_a_b();      //0xB8
void cpu_cp_a_c();      //0xB9
void cpu_cp_a_d();      //0xBA
void cpu_cp_a_e();      //0xBB
void cpu_cp_a_h();      //0xBC
void cpu_cp_a_l();      //0xBD

void cpu_jp_a16();      //0xC3
