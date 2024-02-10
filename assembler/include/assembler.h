#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tiny4_types.h"

/*typedef struct {
  char mnemonic[3];
  u4 opcode;
  u4 operand;
} Instruction;

Instruction instructions[16];*/

bool assemble(const char* file_path);

u4 mnemonice_to_binary(const char* opcode);