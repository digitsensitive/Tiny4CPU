#include <stdio.h>

#include "../../shared/tiny4_types.h"
#include "assembler.h"

/**
 * @brief Tiny4CPU Assembler
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char *argv[]) {
  printf("\x1B[32;1m");
  printf("==================\n");
  printf("Tiny4CPU Assembler\n");
  printf("==================\n");
  printf("\x1b[0m");

  if (argc != 2) {
    fputs("usage: assembler [file_path_to_t4c_file]\n", stderr);
    return -1;
  }

  bool assembly_successful = assemble(argv[1]);

  if (!assembly_successful) {
    fprintf(stderr, "Assembly of file %s failed.\n", argv[1]);
    return -1;
  }

  printf("Assembly of \x1B[32;3m%s\x1b[0m was successful.\n", argv[1]);
  printf("\n");
  return 0;
}
