#include "tiny4.h"

#include <stdio.h>
#include <stdlib.h>

bool initialize(Tiny4 *tiny4) {
  tiny4->is_running = true;
  tiny4->current_opcode = 0x0;
  tiny4->program_counter = 0x0;

  /* Clear General Purpose Registers */
  for (int i = 0; i < REGISTER_COUNT; ++i) {
    tiny4->R[i];
  }

  /* Clear Memory */
  for (int i = 0; i < MEMORY_SIZE; ++i) {
    tiny4->memory[i] = 0;
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
  tiny4->program_length = file_length;
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
    tiny4->memory[i] = buffer[i];
  }

  // Close file, free buffer
  fclose(file_pointer);
  free(buffer);

  return true;
}

void emulate_cycle(Tiny4 *tiny4) {
  tiny4->current_opcode = tiny4->memory[tiny4->program_counter];

  printf("PC: %d, Opcode: %d.\n", tiny4->program_counter,
         tiny4->current_opcode);

  switch (tiny4->current_opcode & 0xF0) {
    case 0x20:
      printf("Case 0x20\n");
      // Zero out bits 4-7
      tiny4->R[0] = tiny4->current_opcode & 0x0F;
      break;
    case 0x30:
      printf("Case 0x30\n");
      printf("The value of the X-register is: %d.\n", tiny4->R[0]);
      u8 temp = tiny4->current_opcode & 0x0F;
      printf("temp is: %d.\n", temp & 0x0F);
      tiny4->R[0] += temp;
      printf("The value of the X-register is: %d.\n", tiny4->R[0]);
      break;
    default:
      printf("Wrong opcode.\n");
      break;
  }

  tiny4->program_counter++;

  if (tiny4->program_counter >= tiny4->program_length) {
    tiny4->is_running = false;
  }
}