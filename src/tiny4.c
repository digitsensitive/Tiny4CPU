#include "tiny4.h"

#include <stdio.h>
#include <stdlib.h>

bool initialize(Tiny4 *tiny4) {
  tiny4->is_running = true;
  tiny4->current_opcode = 0x0;
  set_u4_value(&tiny4->program_counter, 0);
  set_u4_value(&tiny4->input, 0x0);
  set_u4_value(&tiny4->output, 0x0);
  set_u4_value(&tiny4->program_length, 0);

  /* Clear General Purpose Registers */
  for (int i = 0; i < REGISTER_COUNT; ++i) {
    set_u4_value(&tiny4->R[i], 0x0);
  }

  /* Clear Memory */
  for (int i = 0; i < MEMORY_SIZE; ++i) {
    set_u4_value(&tiny4->memory[i], 0x0);
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
    set_u4_value(&tiny4->memory[i * 2], (buffer[i] & 0xF0) >> 4);
    set_u4_value(&tiny4->memory[i * 2 + 1], buffer[i] & 0x0F);
    add_u4_value(&tiny4->program_length, 1);
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

  switch (tiny4->current_opcode & 0xF0) {
    case 0x20:
      // Zero out bits 4-7
      set_u4_value(&tiny4->R[0], tiny4->current_opcode & 0x0F);
      break;
    case 0x30:
      add_u4_value(&tiny4->R[0], tiny4->current_opcode & 0x0F);
      break;
    default:
      printf("Wrong opcode.\n");
      break;
  }

  // Increase program counter by one
  add_u4_value(&tiny4->program_counter, 2);

  if (get_u4_value(&tiny4->program_counter) / 2 >=
      get_u4_value(&tiny4->program_length)) {
    tiny4->is_running = false;
  }
}