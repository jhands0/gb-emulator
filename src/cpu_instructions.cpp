#include "cpu_instructions.h"
#include "cpu.h"

const struct gb_cpu_instruction instructions[256] = {
    {"NOP", 0, cpu_noop},            //0x00
    {"LD BC, n16", 2, nullptr},     //0x01
    {"LD [BC], A", 0, nullptr},     //0x02
    {"INC BC", 0, nullptr},         //0x03
    {"INC B", 0, nullptr},          //0x04
    {"DEC B", 0, nullptr},          //0x05
    {"LD, B, n8", 1, nullptr},      //0x06
    {"RLCA", 0, nullptr},           //0x07
    {"LD [a16], SP", 2, nullptr},   //0x08
    {"ADD HL, BC", 0, nullptr},     //0x09
    {"LD A, [BC]", 0, nullptr},     //0x0A
    {"DEC BC", 0, nullptr},         //0x0B
    {"INC C", 0, nullptr},          //0x0C
    {"DEC C", 0, nullptr},          //0x0D
    {"LD C, n8", 1, nullptr},       //0x0E
    {"RRCA", 0, nullptr},           //0x0F
    {"STOP n8", 1, nullptr},        //0x10
    {"LD DE, n16", 2, nullptr},     //0x11
    {"LD [DE], A", 0, nullptr},     //0x12
    {"INC DE", 0, nullptr},         //0x13
    {"INC D", 0, nullptr},          //0x14
    {"DEC D", 0, nullptr},          //0x15
    {"LD D, n8", 1, nullptr},       //0x16
    {"RLA", 0, nullptr},            //0x17
    {"JR e8", 1, nullptr},          //0x18
    {"ADD HL, DE", 0, nullptr},     //0x19
    {"LD A, [DE]", 0, nullptr},     //0x1A
    {"DEC DE", 0, nullptr},         //0x1B
    {"INC E", 0, nullptr},          //0x1C
    {"DEC E", 0, nullptr},          //0x1D
    {"LD E, n8", 1, nullptr},       //0x1E
    {"RRA", 0, nullptr},            //0x1F
    {"JR NZ, e8", 1, nullptr},      //0x20
    {"LD HL, n16", 2, nullptr},     //0x21
    {"LD [HL+], A", 0, nullptr},    //0x22
    {"INC HL", 0, nullptr},         //0x23
    {"INC H", 0, nullptr},          //0x24
    {"DEC H", 0, nullptr},          //0x25
    {"LD H, n8", 1, nullptr},       //0x26
    {"DAA", 0, nullptr},            //0x27
    {"JR Z, e8", 1, nullptr},       //0x28
    {"ADD HL, HL", 0, nullptr},     //0x29
    {"ADD A, [HL+]", 0, nullptr},   //0x2A
    {"DEC HL", 0, nullptr},         //0x2B
    {"INC L", 0, nullptr},          //0x2C
    {"DEC L", 0, nullptr},          //0x2D
    {"LD L, n8", 1, nullptr},       //0x2E
    {"CPL", 0, nullptr},            //0x2F
    {"JR NC, e8", 1, nullptr},      //0x30
    {"LD SP, n16", 2, nullptr},     //0x31
    {"LD [HL-], A", 0, nullptr},    //0x32
    {"INC SP", 0, nullptr},         //0x33
    {"INC [HL]", 0, nullptr},       //0x34
    {"DEC [HL]", 0, nullptr},       //0x35
    {"LD [HL], n8", 1, nullptr},    //0x36
    {"SCF", 0, nullptr},            //0x37
    {"JR C, e8", 1, nullptr},       //0x38
    {"ADD HL, SP", 0, nullptr},     //0x39
    {"LD A, [HL-]", 0, nullptr},    //0x3A
    {"DEC SP", 0, nullptr},         //0x3B
    {"INC A", 0, nullptr},          //0x3C
    {"DEC A", 0, nullptr},          //0x3D
    {"LD A, n8", 1, nullptr},       //0x3E
    {"CCF", 0, nullptr},            //0x3F
    {"LD B, B", 0, nullptr},        //0x40
    {"LD B, C", 0, nullptr},        //0x41
    {"LD B, D", 0, nullptr},        //0x42
    {"LD B, E", 0, nullptr},        //0x43
    {"LD B, H", 0, nullptr},        //0x44
    {"LD B, L", 0, nullptr},        //0x45
    {"LD B, [HL]", 0, nullptr},     //0x46
    {"LD B, A", 0, nullptr},        //0x47
    {"LD C, B", 0, nullptr},        //0x48
    {"LD C, C", 0, nullptr},        //0x49
    {"LD C, D", 0, nullptr},        //0x4A
    {"LD C, E", 0, nullptr},        //0x4B
    {"LD C, H", 0, nullptr},        //0x4C
    {"LD C, L", 0, nullptr},        //0x4D
    {"LD C, [HL]", 0, nullptr},     //0x4E
    {"LD C, A", 0, nullptr},        //0x4F
    {"LD D, B", 0, nullptr},        //0x50
    {"LD D, C", 0, nullptr},        //0x51
    {"LD D, D", 0, nullptr},        //0x52
    {"LD D, E", 0, nullptr},        //0x53
    {"LD D, H", 0, nullptr},        //0x54
    {"LD D, L", 0, nullptr},        //0x55
    {"LD D, [HL]", 0, nullptr},     //0x56
    {"LD D, A", 0, nullptr},        //0x57
    {"LD E, B", 0, nullptr},        //0x58
    {"LD E, C", 0, nullptr},        //0x59
    {"LD E, D", 0, nullptr},        //0x5A
    {"LD E, E", 0, nullptr},        //0x5B
    {"LD E, H", 0, nullptr},        //0x5C
    {"LD E, L", 0, nullptr},        //0x5D
    {"LD E, [HL]", 0, nullptr},     //0x5E
    {"LD E, A", 0, nullptr},        //0x5F
    {"LD H, B", 0, nullptr},        //0x60
    {"LD H, C", 0, nullptr},        //0x61
    {"LD H, D", 0, nullptr},        //0x62
    {"LD H, E", 0, nullptr},        //0x63
    {"LD H, H", 0, nullptr},        //0x64
    {"LD H, L", 0, nullptr},        //0x65
    {"LD H, [HL]", 0, nullptr},     //0x66
    {"LD H, A", 0, nullptr},        //0x67
    {"LD L, B", 0, nullptr},        //0x68
    {"LD L, C", 0, nullptr},        //0x69
    {"LD L, D", 0, nullptr},        //0x6A
    {"LD L, E", 0, nullptr},        //0x6B
    {"LD L, H", 0, nullptr},        //0x6C
    {"LD L, L", 0, nullptr},        //0x6D
    {"LD L, [HL]", 0, nullptr},     //0x6E
    {"LD L, A", 0, nullptr},        //0x6F
    {"LD [HL], B", 0, nullptr},     //0x70
    {"LD [HL], C", 0, nullptr},     //0x71
    {"LD [HL], D", 0, nullptr},     //0x72
    {"LD [HL], E", 0, nullptr},     //0x73
    {"LD [HL], H", 0, nullptr},     //0x74
    {"LD [HL], L", 0, nullptr},     //0x75
    {"HALT", 0, nullptr},           //0x76
    {"LD [HL], A", 0, nullptr},     //0x77
    {"LD A, B", 0, nullptr},        //0x78
    {"LD A, C", 0, nullptr},        //0x79
    {"LD A, D", 0, nullptr},        //0x7A
    {"LD A, E", 0, nullptr},        //0x7B
    {"LD A, H", 0, nullptr},        //0x7C
    {"LD A, L", 0, nullptr},        //0x7D
    {"LD A, [HL]", 0, nullptr},     //0x7E
    {"LD A, A", 0, nullptr},        //0x7F
    {"ADD A, B", 0, nullptr},       //0x80
    {"ADD A, C", 0, nullptr},       //0x81
    {"ADD A, D", 0, nullptr},       //0x82
    {"ADD A, E", 0, nullptr},       //0x83
    {"ADD A, H", 0, nullptr},       //0x84
    {"ADD A, L", 0, nullptr},       //0x85
    {"ADD A, [HL]", 0, nullptr},    //0x86
    {"ADD A, A", 0, nullptr},       //0x87
    {"ADC A, B", 0, nullptr},       //0x88
    {"ADC A, C", 0, nullptr},       //0x89
    {"ADC A, D", 0, nullptr},       //0x8A
    {"ADC A, E", 0, nullptr},       //0x8B
    {"ADC A, H", 0, nullptr},       //0x8C
    {"ADC A, L", 0, nullptr},       //0x8D
    {"ADC A, [HL]", 0, nullptr},    //0x8E
    {"ADC A, A", 0, nullptr},       //0x8F
    {"SUB A, B", 0, nullptr},       //0x90
    {"SUB A, C", 0, nullptr},       //0x91
    {"SUB A, D", 0, nullptr},       //0x92
    {"SUB A, E", 0, nullptr},       //0x93
    {"SUB A, H", 0, nullptr},       //0x94
    {"SUB A, L", 0, nullptr},       //0x95
    {"SUB A, [HL]", 0, nullptr},    //0x96
    {"SUB A, A", 0, nullptr},       //0x97
    {"SBC A, B", 0, nullptr},       //0x98
    {"SBC A, C", 0, nullptr},       //0x99
    {"SBC A, D", 0, nullptr},       //0x9A
    {"SBC A, E", 0, nullptr},       //0x9B
    {"SBC A, H", 0, nullptr},       //0x9C
    {"SBC A, L", 0, nullptr},       //0x9D
    {"SBC A, [HL]", 0, nullptr},    //0x9E
    {"SBC A, A", 0, nullptr},       //0x9F
    {"AND A, B", 0, nullptr},       //0xA0
    {"AND A, C", 0, nullptr},       //0xA1
    {"AND A, D", 0, nullptr},       //0xA2
    {"AND A, E", 0, nullptr},       //0xA3
    {"AND A, H", 0, nullptr},       //0xA4
    {"AND A, L", 0, nullptr},       //0xA5
    {"AND A, [HL]", 0, nullptr},    //0xA6
    {"AND A, A", 0, nullptr},       //0xA7
    {"XOR A, B", 0, nullptr},       //0xA8
    {"XOR A, C", 0, nullptr},       //0xA9
    {"XOR A, D", 0, nullptr},       //0xAA
    {"XOR A, E", 0, nullptr},       //0xAB
    {"XOR A, H", 0, nullptr},       //0xAC
    {"XOR A, L", 0, nullptr},       //0xAD
    {"XOR A, [HL]", 0, nullptr},    //0xAE
    {"XOR A, A", 0, cpu_xor_a},       //0xAF
    {"OR A, B", 0, nullptr},        //0xB0
    {"OR A, C", 0, nullptr},        //0xB1
    {"OR A, D", 0, nullptr},        //0xB2
    {"OR A, E", 0, nullptr},        //0xB3
    {"OR A, H", 0, nullptr},        //0xB4
    {"OR A, L", 0, nullptr},        //0xB5
    {"OR A, [HL]", 0, nullptr},     //0xB6
    {"OR A, A", 0, nullptr},        //0xB7
    {"CP A, B", 0, nullptr},        //0xB8
    {"CP A, C", 0, nullptr},        //0xB9
    {"CP A, D", 0, nullptr},        //0xBA
    {"CP A, E", 0, nullptr},        //0xBB
    {"CP A, H", 0, nullptr},        //0xBC
    {"CP A, L", 0, nullptr},        //0xBD
    {"CP A, [HL]", 0, nullptr},     //0xBE
    {"CP A, A", 0, nullptr},        //0xBF
    {"RET NZ", 0, nullptr},         //0xC0
    {"POP BC", 0, nullptr},         //0xC1
    {"JP NZ, a16", 2, nullptr},     //0xC2
    {"JP a16", 2, cpu_jp_a16},         //0xC3
    {"CALL NZ, a16", 2, nullptr},   //0xC4
    {"PUSH BC", 0, nullptr},        //0xC5
    {"ADD A, n8", 1, nullptr},      //0xC6
    {"RST $00", 0, nullptr},        //0xC7
    {"RET Z", 0, nullptr},          //0xC8
    {"RET", 0, nullptr},            //0xC9
    {"JP Z, a16", 2, nullptr},      //0xCA
    {"PREFIX", 0, nullptr},         //0xCB
    {"CALL Z, a16", 2, nullptr},    //0xCC
    {"CALL a16", 2, nullptr},       //0xCD
    {"ADC A, n8", 1, nullptr},      //0xCE
    {"RST $08", 0, nullptr},        //0xCF
    {"RET NC", 0, nullptr},         //0xD0
    {"POP DE", 0, nullptr},         //0xD1
    {"JP NC, a16", 2, nullptr},     //0xD2
    {"???", 0, nullptr},            //0xD3
    {"CALL NC, a16", 2, nullptr},   //0xD4
    {"PUSH DE", 0, nullptr},        //0xD5
    {"SUB A, n8", 1, nullptr},      //0xD6
    {"RST $10", 0, nullptr},        //0xD7
    {"RET C", 0, nullptr},          //0xD8
    {"RETI", 0, nullptr},           //0xD9
    {"JP C, a16", 2, nullptr},      //0xDA
    {"???", 0, nullptr},            //0xDB
    {"CALL C, a16", 2, nullptr},    //0xDC
    {"???", 0, nullptr},            //0xDD
    {"SBC A, n8", 1, nullptr},      //0xDE
    {"RST $18", 0, nullptr},        //0xDF
    {"LDH [a8], A", 1, nullptr},    //0xE0
    {"POP HL", 0, nullptr},         //0xE1
    {"LDH [C], A", 0, nullptr},     //0xE2
    {"???", 0, nullptr},            //0xE3
    {"???", 0, nullptr},            //0xE4
    {"PUSH HL", 0, nullptr},        //0xE5
    {"AND A, n8", 1, nullptr},      //0xE6
    {"RST $20", 0, nullptr},        //0xE7
    {"ADD SP, e8", 1, nullptr},     //0xE8
    {"JP HL", 0, nullptr},          //0xE9
    {"LD [a16], A", 2, nullptr},    //0xEA
    {"???", 0, nullptr},            //0xEB
    {"???", 0, nullptr},            //0xEC
    {"???", 0, nullptr},            //0xED
    {"XOR A, n8", 1, nullptr},      //0xEE
    {"RST $28", 0, nullptr},        //0xEF
    {"LDH A, [a8]", 1, nullptr},    //0xF0
    {"POP AF", 0, nullptr},         //0xF1
    {"LDH A, [C]", 0, nullptr},     //0xF2
    {"DI", 0, nullptr},             //0xF3
    {"???", 0, nullptr},            //0xF4
    {"PUSH AF", 0, nullptr},        //0xF5
    {"OR A, n8", 1, nullptr},       //0xF6
    {"RST $30", 0, nullptr},        //0xF7
    {"LD HL, SP + e8", 1, nullptr}, //0xF8
    {"LD SP, HL", 0, nullptr},      //0xF9
    {"LD A, [a16]", 2, nullptr},    //0xFA
    {"EI", 0, nullptr},             //0xFB
    {"???", 0, nullptr},            //0xFC
    {"???", 0, nullptr},            //0xFD
    {"CP A, n8", 1, nullptr},       //0xFE
    {"RST $38", 0, nullptr},        //0xFF
}