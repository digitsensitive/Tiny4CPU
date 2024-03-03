#include "disassembler.h"

#include "defines.h"
#include "helpers.h"

bool disassemble(const char* file_path) {
  /* Files */
  FILE* binary_input_file;
  FILE* assembly_output_file;

  /* Open input file for read (file must exist!) */
  binary_input_file = fopen(file_path, "rb");

  /* Open Output file for write */
  const char* output_file_path = replace_file_extension(file_path, ".t4c");
  assembly_output_file = fopen(output_file_path, "w");

  if (binary_input_file == NULL || assembly_output_file == NULL) {
    fputs("Memory allocation for FILE pointer failed.\n", stderr);
    return false;
  }

  // Get the length of the file
  fseek(binary_input_file, 0, SEEK_END);
  long file_length = ftell(binary_input_file);
  rewind(binary_input_file);

  // Evaluate the file length
  if (file_length > MEMORY_SIZE || file_length % 2 != 0) {
    fputs("The file length is too large or not even!\n", stderr);
    return false;
  }

  // Allocate memory in the range of the file length
  u8* buffer = (u8*)malloc(sizeof(u8) * file_length);
  if (buffer == NULL) {
    fputs("Memory allocation for Buffer failed!\n", stderr);
    return false;
  }

  // Fill the buffer with
  fread(buffer, sizeof(u8), file_length, binary_input_file);

  // Loop over the buffer and write to output file
  for (int i = 0; i < file_length; i++) {
    u4 operand;
    set_u4_value(&operand, buffer[i] & 0x0F);
    unsigned char opcode = (buffer[i] >> 4) & 0x0F;

    for (int j = 0; j < NUM_INSTRUCTIONS; ++j) {
      if (opcode == instructions[j].opcode.value) {
        fprintf(assembly_output_file, "%s ", instructions[j].mnemonic);
        fprintf(assembly_output_file, "#%d\n", operand);
      }
    }
  }

  free((void*)output_file_path);
  free(buffer);
  fclose(binary_input_file);
  fclose(assembly_output_file);

  return true;
}