#pragma once

#define MEMORY_SIZE 16
#define NUM_INSTRUCTIONS 10

typedef struct {
  char mnemonic[4];
  u4 opcode;
} Instruction;

Instruction instructions[NUM_INSTRUCTIONS] = {
    {"LDX", 0x0u}, {"LDY", 0x1u}, {"ADX", 0x2u}, {"ADY", 0x3u}, {"SUX", 0x4u},
    {"SUY", 0x5u}, {"OUT", 0x6u}, {"JXZ", 0x7u}, {"JYZ", 0x8u}, {"JMP", 0x9u}};