#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"
#include "tiny4_types.h"

typedef struct {
  char mnemonic[4];
  u4 opcode;
} Instruction;

typedef struct {
  char name[MAX_LABEL_LENGTH];
  u8 address;
} Label;

extern Instruction instructions[NUM_INSTRUCTIONS];

bool assemble(const char* file_path);
