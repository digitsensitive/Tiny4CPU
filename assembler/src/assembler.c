#include "assembler.h"

bool assemble(const char* file_path) {
  /* Files */
  FILE* assembly_input_file;
  FILE* binary_output_file;

  /* Open input file for read (file must exist!) */
  assembly_input_file = fopen(file_path, "r");

  /* Open Output File as binary file for write */
  binary_output_file = fopen("counter.t4", "wb");

  if (assembly_input_file == NULL || binary_output_file == NULL) {
    fputs("Memory allocation for FILE pointer failed!\n", stderr);
    return false;
  }

  char mnemonic[3];
  unsigned int temp_value;
  u4 operand;

  while (fscanf(assembly_input_file, "%3s %u", mnemonic, &temp_value) == 2) {
    // Transform
    set_u4_value(&operand, temp_value);

    // Convert opcode to binary
    u4 opcode = mnemonice_to_binary(mnemonic);

    // Combine opcode and operand into a single byte
    unsigned char instruction =
        (get_u4_value(&opcode) << 4) | (get_u4_value(&operand) & 0x0F);

    // Write the combined instruction to the file
    size_t bytes_written =
        fwrite(&instruction, sizeof(unsigned char), 1, binary_output_file);
  }

  fclose(assembly_input_file);
  fclose(binary_output_file);

  return true;
}

u4 mnemonice_to_binary(const char* opcode) {
  u4 value;
  if (strcmp(opcode, "LDX") == 0) {
    set_u4_value(&value, 1);
    return value;
  } else if (strcmp(opcode, "LDY") == 0) {
    set_u4_value(&value, 2);
    return value;
  } else if (strcmp(opcode, "ADX") == 0) {
    set_u4_value(&value, 3);
    return value;
  } else if (strcmp(opcode, "ADY") == 0) {
    set_u4_value(&value, 4);
    return value;
  } else if (strcmp(opcode, "JMP") == 0) {
    set_u4_value(&value, 14);
    return value;
  } else {
    printf("Unsupported opcode: %s\n", opcode);
    set_u4_value(&value, -1);
    return value;
  }
}