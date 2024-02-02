#include "output.h"
#include "tiny4.h"

Tiny4 tiny4;

#ifdef _WIN32
UINT originalCodePage;
#endif

void load_terminal_settings() {
#ifdef _WIN32
  // Only perform this on Windows
  // Get the current console output code page
  originalCodePage = GetConsoleOutputCP();

  // Set the console output code page to UTF-8
  SetConsoleOutputCP(CP_UTF8);
#endif
}

void restore_terminal_settings() {
#ifdef _WIN32
  // Only restore the original console output code page on Windows
  // Restore the original console output code page
  SetConsoleOutputCP(originalCodePage);
#endif
}

int main(int argc, char *argv[]) {
  load_terminal_settings();

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
    clear_terminal();
    draw_terminal_output();
    sleep_terminal();
  }

  restore_terminal_settings();

  return 0;
}
