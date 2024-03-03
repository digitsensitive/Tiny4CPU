#include <stdio.h>

#include "../../shared/tiny4_types.h"
#include "disassembler.h"

int main(int argc, char *argv[]) {
  printf("\x1B[32;1m");
  printf("==================\n");
  printf("Tiny4CPU Disassembler\n");
  printf("==================\n");
  printf("\x1b[0m");

  if (argc != 2) {
    fputs("usage: disassembler [file_path_to_bin_file]\n", stderr);
    return -1;
  }

  bool disassembly_successful = disassemble(argv[1]);

  if (!disassembly_successful) {
    fprintf(stderr, "Disassembly of file %s failed.\n", argv[1]);
    return -1;
  }

  printf("Disassembly of \x1B[32;3m%s\x1b[0m was successful.\n", argv[1]);
  printf("\n");

  return 0;
}