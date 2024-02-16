#include "tiny4.h"

#include <stdio.h>
#include <stdlib.h>

bool initialize(Tiny4 *tiny4, unsigned int clock_in_msec) {
  tiny4->is_running = true;
  tiny4->current_opcode = 0x0u;
  set_u4_value(&tiny4->program_counter, 0);
  set_u4_value(&tiny4->input, 0x0u);
  set_u4_value(&tiny4->output, 0x0u);
  set_u4_value(&tiny4->program_length, 0);
  tiny4->clock_hertz = 1000 / clock_in_msec;

  /* Clear General Purpose Registers */
  for (int i = 0; i < REGISTER_COUNT; ++i) {
    set_u4_value(&tiny4->R[i], 0x0u);
  }

  /* Clear Memory */
  for (int i = 0; i < MEMORY_SIZE; ++i) {
    set_u4_value(&tiny4->memory[i], 0x0u);
  }

  return true;
}

bool load_application(Tiny4 *tiny4, const char *path_to_file) {
  printf("Loading: %s\n", path_to_file);

  FILE *file_pointer = fopen(path_to_file, "rb");

  if (file_pointer == NULL) {
    fputs("Memory allocation for FILE pointer failed!\n", stderr);
    return false;
  }

  // Get the length of the file
  fseek(file_pointer, 0, SEEK_END);
  long file_length = ftell(file_pointer);
  rewind(file_pointer);

  // Allocate memory in the range of the file length
  char *buffer = (char *)malloc(sizeof(char) * file_length);
  if (buffer == NULL) {
    fputs("Memory allocation for Buffer failed!\n", stderr);
    return false;
  }

  // Copy the file into the buffer
  size_t result = fread(buffer, 1, file_length, file_pointer);
  if (result != file_length) {
    fputs("Reading the file failed!\n", stderr);
    return false;
  }

  // Copy buffer to Tiny4 memory
  for (int i = 0; i < file_length; ++i) {
    set_u4_value(&tiny4->memory[i * 2], (buffer[i] & 0xF0u) >> 4);
    set_u4_value(&tiny4->memory[i * 2 + 1], buffer[i] & 0x0Fu);
    add_u4_value(&tiny4->program_length, 2);
  }

  // Close file, free buffer
  fclose(file_pointer);
  free(buffer);

  return true;
}

void emulate_cycle(Tiny4 *tiny4) {
  u8 pc = get_u4_value(&tiny4->program_counter);
  tiny4->current_opcode = get_u4_value(&tiny4->memory[pc]) << 4 |
                          get_u4_value(&tiny4->memory[pc + 1]);

  // Increment program counter before execution
  add_u4_value(&tiny4->program_counter, 2);

  switch (tiny4->current_opcode & 0xF0u) {
    case 0x10u:
      /* LDX */
      set_u4_value(&tiny4->R[0], tiny4->current_opcode & 0x0Fu);
      break;

    case 0x20u:
      /* LDY */
      set_u4_value(&tiny4->R[1], tiny4->current_opcode & 0x0Fu);
      break;

    case 0x30u:
      /* ADX */
      add_u4_value(&tiny4->R[0], tiny4->current_opcode & 0x0Fu);
      break;

    case 0x40u:
      /* ADY */
      add_u4_value(&tiny4->R[1], tiny4->current_opcode & 0x0Fu);
      break;

    case 0x50u:
      /* SUX */
      subtract_u4_value(&tiny4->R[0], tiny4->current_opcode & 0x0Fu);
      break;

    case 0x60u:
      /* SUY */
      subtract_u4_value(&tiny4->R[1], tiny4->current_opcode & 0x0Fu);
      break;

    case 0x70u:
      /* NOX */
      bitwise_not_u4_value(&tiny4->R[0]);
      break;

    case 0x80u:
      /* NOY */
      bitwise_not_u4_value(&tiny4->R[1]);
      break;

    case 0x90u:
      /* STX */
      set_u4_value(&tiny4->memory[tiny4->current_opcode & 0x0Fu],
                   tiny4->R[0].value);
      break;

    case 0xA0u:
      /* STY */
      set_u4_value(&tiny4->memory[tiny4->current_opcode & 0x0Fu],
                   tiny4->R[1].value);
      break;

    case 0xE0u:
      /* JMP */
      set_u4_value(&tiny4->program_counter, tiny4->current_opcode & 0x0Fu);
      break;
    default:
      printf("Wrong opcode.\n");
      break;
  }

  if (get_u4_value(&tiny4->program_counter) >=
      get_u4_value(&tiny4->program_length)) {
    tiny4->is_running = false;
  }
}