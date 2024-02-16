#pragma once

#include "tiny4_types.h"

#define REGISTER_COUNT 2
#define MEMORY_SIZE 256

typedef struct {
  bool is_running;
  unsigned int clock_hertz;
  u4 input;
  u4 output;
  u4 program_length;
  u8 current_opcode;
  u4 program_counter;
  u4 R[REGISTER_COUNT];   /* General purpose registers */
  u4 memory[MEMORY_SIZE]; /* Memory size of 128 bytes */
} Tiny4;

bool initialize(Tiny4 *tiny4, unsigned int clock_in_msec);
bool load_application(Tiny4 *tiny4, const char *path_to_file);
void emulate_cycle(Tiny4 *tiny4);
