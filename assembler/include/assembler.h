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
const char* replace_file_extension(const char* original_path,
                                   const char* new_extension);
unsigned int binary_string_to_decimal(const char* binary_str);
bool assemble(const char* file_path);
u4 mnemonic_to_binary(const char* mnemonic);