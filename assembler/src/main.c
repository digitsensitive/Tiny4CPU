#include <stdio.h>

#include "../../shared/tiny4_types.h"
#include "assembler.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("usage: assembler [file_path_to_t4c_file]\n");
    return -1;
  }

  bool assembly_successful = assemble(argv[1]);

  if (!assembly_successful) {
    printf("Assembly failed.\n");
    return -1;
  }

  return 0;
}
