#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tiny4_types.h"

#define MAX_LINE_LENGTH 40
#define MAX_LABELS 50
#define MAX_LABEL_LENGTH 20
#define NUM_INSTRUCTIONS 10

typedef struct {
  char mnemonic[4];
  u4 opcode;
} Instruction;

typedef struct {
  char name[MAX_LABEL_LENGTH];
  u8 address;
} Label;

bool assemble(const char* file_path);
