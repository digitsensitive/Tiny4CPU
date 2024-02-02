#include "output.h"

void draw_terminal_output() {
  printf("\x1B[32;1mTiny4CPU running ...\n");
  reset_font_style();
  printf("\x1B[32;2m● ● ● ●\n");
  reset_font_style();
  printf("Hello World!");
  fflush(stdout);  // Flush the output to ensure it's displayed immediately
}

void clear_terminal() {
  // Escape sequence to clear the console screen
  printf("\x1b[2J");
  // Move the cursor to the top-left position
  printf("\x1b[H");
}

/* ESC Code Sequence to reset all modes (styles and colors) */
void reset_font_style() { printf("\x1b[0m"); }

void sleep_terminal() {
#ifdef _WIN32
  // Windows: Sleep for 5000 milliseconds (5 seconds)
  Sleep(1000);
#else
  // Unix-like systems: Sleep for 5 seconds
  sleep(1);
#endif
}