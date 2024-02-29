#include "assembler.h"

Instruction instructions[NUM_INSTRUCTIONS] = {
    {"NOP", 0x0u}, {"LDX", 0x1u}, {"LDY", 0x2u}, {"ADX", 0x3u},
    {"ADY", 0x4u}, {"SUX", 0x5u}, {"SUY", 0x6u}, {"NOX", 0x7u},
    {"OUT", 0x8u}, {"STX", 0x9u}, {"STY", 0xAu}, {"JXZ", 0xBu},
    {"JYZ", 0xCu}, {"JCA", 0xDu}, {"JMP", 0xEu}, {"HLT", 0xFu}};

Label labels[MAX_LABELS];
unsigned int label_count = 0;

const char* replace_file_extension(const char* original_path,
                                   const char* new_extension) {
  // Find the last dot in the original path
  const char* last_dot = strrchr(original_path, '.');

  // Calculate the length of the extension
  size_t extension_length = strlen(new_extension);

  // Calculate the length of the original path without the extension
  size_t path_length =
      last_dot ? (size_t)(last_dot - original_path) : strlen(original_path);

  // Allocate memory for the new path, new extension and null character
  char* new_path = (char*)malloc(path_length + extension_length + 1);
  if (new_path == NULL) {
    fputs("Memory allocation failed.\n", stderr);
    return NULL;
  }

  // Copy the original path up to the last dot (if it exists)
  if (last_dot) {
    strncpy(new_path, original_path, path_length);
  } else {
    strcpy(new_path, original_path);
  }

  // Append the new extension
  strcpy(new_path + path_length, new_extension);

  return new_path;
}

unsigned int binary_string_to_decimal(const char* binary_str) {
  unsigned int decimal_value = 0;
  int length = strlen(binary_str);

  for (int i = 0; i < length; ++i) {
    decimal_value = decimal_value * 2 + (binary_str[i] - '0');
  }

  return decimal_value;
}

bool mnemonic_to_binary(const char* mnemonic, u4* opcode) {
  for (int i = 0; i < NUM_INSTRUCTIONS; ++i) {
    if (strcmp(mnemonic, instructions[i].mnemonic) == 0) {
      opcode->value = instructions[i].opcode.value;
      return true;
    }
  }

  return false;
}

bool parse_labels(const char* file_path) {
  FILE* assembly_input_file;

  /* Open input file for read (file must exist!) */
  assembly_input_file = fopen(file_path, "r");

  if (assembly_input_file == NULL) {
    fprintf(stderr,
            "Parse labels: Memory allocation for FILE pointer (Filepath: %s) "
            "failed.\n",
            file_path);
    return false;
  }

  char line[MAX_LINE_LENGTH];
  unsigned int address = 0;
  unsigned int current_line = 0;
  while (fgets(line, MAX_LINE_LENGTH, assembly_input_file) != NULL) {
    /* Continue if comment or empty line */
    if (line[0] == ';' || line[0] == '\n') {
      current_line++;
      continue;
    }

    /* Check if the line contains a label */
    if (strchr(line, ':')) {
      const char* label_name = strtok(line, ":");
      strcpy(labels[label_count].name, label_name);
      labels[label_count].address = address;
      label_count++;
    } else {
      /* Increment address depending on the instruction on the line */
      char mnemonic[4];
      if (sscanf(line, "%3s", mnemonic) == 1) {
        for (int i = 0; i < NUM_INSTRUCTIONS; ++i) {
          if (strcmp(mnemonic, instructions[i].mnemonic) == 0) {
            address += 2;
          }
        }
      } else {
        fprintf(stderr,
                "Parse labels: Missing or incorrect Mnemonic at line %d.\n",
                current_line);
        return false;
      }
    }

    current_line++;
  }

  fclose(assembly_input_file);

  return true;
}

bool assemble(const char* file_path) {
  /* Parse labels */
  bool parse_labels_return = parse_labels(file_path);

  if (!parse_labels_return) {
    fputs("Parsing the labels failed.\n", stderr);
    return false;
  }
  /* End parse labels */

  /* Files */
  FILE* assembly_input_file;
  FILE* binary_output_file;

  /* Open input file for read (file must exist!) */
  assembly_input_file = fopen(file_path, "r");

  /* Open Output File as binary file for write */
  const char* output_file_path = replace_file_extension(file_path, ".bin");
  binary_output_file = fopen(output_file_path, "wb");

  if (assembly_input_file == NULL || binary_output_file == NULL) {
    fputs("Memory allocation for FILE pointer failed.\n", stderr);
    return false;
  }

  char line[MAX_LINE_LENGTH];
  unsigned int current_line = 0;
  while (fgets(line, MAX_LINE_LENGTH, assembly_input_file) != NULL) {
    /* Continue if comment or empty line */
    if (line[0] == ';' || line[0] == '\n') {
      current_line++;
      continue;
    }

    /* Continue if line contains a label */
    if (strchr(line, ':')) {
      current_line++;
      continue;
    }

    // Set Mnemonic
    char mnemonic[4];
    u4 opcode;
    if (sscanf(line, "%3s", mnemonic) == 1) {
      bool is_mnemonic_valid = mnemonic_to_binary(mnemonic, &opcode);
      if (!is_mnemonic_valid) {
        fprintf(stderr, "Unsupported mnemonic %s at line %d.\n", mnemonic,
                current_line);
        return false;
      }
    } else {
      fprintf(stderr, "Missing Mnemonic at line %d.\n", current_line);
      return false;
    }

    // Set operand
    u4 operand;
    char sign;
    unsigned int temp_value;
    if (sscanf(line, "%*3s %c", &sign) == 1) {
      switch (sign) {
        case '#':
          char prefix;
          if (sscanf(line, "%*3s %*c%c", &prefix) == 1) {
            if (prefix == '$') {
              /* Hexadecimal immediate addressing mode */
              if (sscanf(line, "%*3s %*c%*c%x", &temp_value) == 1) {
                set_u4_value(&operand, temp_value);
              }
            } else {
              /* Decimal immediate addressing mode */
              if (sscanf(line, "%*3s %*c%u", &temp_value) == 1) {
                set_u4_value(&operand, temp_value);
              }
            }
          }
          break;
        case '%':
          char temp_binary_number[5];
          /* Binary immediate addressing mode */
          if (sscanf(line, "%*3s %*c%4s", temp_binary_number) == 1) {
            temp_value = binary_string_to_decimal(temp_binary_number);
            set_u4_value(&operand, temp_value);
          }
          break;

        default:
          /* Default case means label */
          char current_label[MAX_LABEL_LENGTH];
          if (sscanf(line, "%*3s %s", current_label) == 1) {
            for (int i = 0; i < label_count; i++) {
              if (strcmp(labels[i].name, current_label) == 0) {
                set_u4_value(&operand, labels[i].address);
                break;
              }
            }
          }
      }
    }

    // Combine opcode and operand into a single byte
    u8 instruction =
        (get_u4_value(&opcode) << 4) | (get_u4_value(&operand) & 0x0Fu);

    // Write the combined instruction to the file
    fwrite(&instruction, sizeof(u8), 1, binary_output_file);

    current_line++; /* Increase line count */
  }

  free((void*)output_file_path);
  fclose(assembly_input_file);
  fclose(binary_output_file);

  return true;
}
