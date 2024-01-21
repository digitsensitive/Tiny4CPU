#include <stdio.h>

#include "tiny4.h"

Tiny4 tiny4;

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("usage: tiny4cpu [file]\n");
    return -1;
  }

  /* Initialize Tiny4CPU instance */
  bool init_succeeded = initialize(&tiny4);

  if (init_succeeded) {
    load_application(&tiny4, argv[1]);
  }

  while (tiny4.is_running) {
    emulate_cycle(&tiny4);
  }

  return 0;
}
