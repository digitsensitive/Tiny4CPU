#include "assembler.h"

Instruction instructions[INSTRUCTIONS_COUNT] = {
    {"NOP", 0x0u}, {"LDX", 0x1u}, {"LDY", 0x2u}, {"ADX", 0x3u},
    {"ADY", 0x4u}, {"SUX", 0x5u}, {"SUY", 0x6u}, {"NOX", 0x7u},
    {"NOY", 0x8u}, {"STX", 0x9u}, {"STY", 0xAu}, {"JXZ", 0xBu},
    {"JYZ", 0xCu}, {"JCA", 0xDu}, {"JMP", 0xEu}, {"HLT", 0xFu}};

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

  char mnemonic[4];
  unsigned int temp_value;
  u4 operand;

  while (fscanf(assembly_input_file, "%3s %u", mnemonic, &temp_value) == 2) {
    set_u4_value(&operand, temp_value);
    u4 opcode = mnemonic_to_binary(mnemonic);

    // Combine opcode and operand into a single byte
    u8 instruction =
        (get_u4_value(&opcode) << 4) | (get_u4_value(&operand) & 0x0F);

    // Write the combined instruction to the file
    fwrite(&instruction, sizeof(u8), 1, binary_output_file);
  }

  fclose(assembly_input_file);
  fclose(binary_output_file);

  return true;
}

u4 mnemonic_to_binary(const char* mnemonic) {
  for (int i = 0; i < INSTRUCTIONS_COUNT; ++i) {
    if (strcmp(mnemonic, instructions[i].mnemonic) == 0) {
      return instructions[i].opcode;
    }
  }

  printf("Unsupported mnemonic: %s\n", mnemonic);
  return instructions[0].opcode; /* return NOP instruction */
}