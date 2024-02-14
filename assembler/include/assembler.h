#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tiny4_types.h"

typedef struct {
  char mnemonic[4];
  u4 opcode;
} Instruction;

extern Instruction instructions[INSTRUCTIONS_COUNT];
bool assemble(const char* file_path);
u4 mnemonic_to_binary(const char* mnemonic);