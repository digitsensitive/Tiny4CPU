#pragma once

#include "tiny4_types.h"

#define REGISTER_COUNT 2
#define MEMORY_SIZE 32

typedef struct {
  bool is_running;
  u4 input;
  u4 output;
  u4 program_length;
  u8 current_opcode;
  u4 program_counter;
  u4 R[REGISTER_COUNT];   /* General purpose registers */
  u4 memory[MEMORY_SIZE]; /* Memory size of 16 bytes */
} Tiny4;

bool initialize(Tiny4 *tiny4);
bool load_application(Tiny4 *tiny4, const char *path_to_file);
void emulate_cycle(Tiny4 *tiny4);
