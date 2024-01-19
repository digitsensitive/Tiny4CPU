#pragma once

#include "tiny4_types.h"

#define REGISTER_COUNT 2
#define MEMORY_SIZE 256

typedef struct {
  bool is_running;
  u8 program_length;
  u8 current_opcode;
  u8 program_counter;
  u8 R[2];        /* General purpose registers */
  u8 memory[256]; /* Memory size of 256 bytes */
} Tiny4;

bool initialize(Tiny4 *tiny4);
bool load_application(Tiny4 *tiny4, const char *path_to_file);
void emulate_cycle(Tiny4 *tiny4);
