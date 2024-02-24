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

const char* replace_file_extension(const char* original_path,
                                   const char* new_extension);
unsigned int binary_string_to_decimal(const char* binary_str);
bool mnemonic_to_binary(const char* mnemonic, u4* opcode);
bool assemble(const char* file_path);
bool parse_labels(const char* file_path);
