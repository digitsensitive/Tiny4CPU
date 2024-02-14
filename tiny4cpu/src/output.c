#include "output.h"

#define NIBBLE_TO_BINARY_PATTERN "%c%c%c%c"

#define NIBBLE_TO_BINARY(nibble)                                  \
  ((nibble) & 0x08u ? '1' : '0'), ((nibble) & 0x04u ? '1' : '0'), \
      ((nibble) & 0x02u ? '1' : '0'), ((nibble) & 0x01u ? '1' : '0')

void draw_terminal_output(Tiny4* tiny4) {
  printf("\x1B[32;1m=== Tiny4CPU Emulator ===\n");
  reset_font_style();
  printf("Power: %s\n", tiny4->is_running ? "On" : "Off");
  printf("Program Length: %d\n", get_u4_value(&tiny4->program_length));
  printf("PC: %d\n", get_u4_value(&tiny4->program_counter));
  printf("Register X: " NIBBLE_TO_BINARY_PATTERN,
         NIBBLE_TO_BINARY(get_u4_value(&tiny4->R[0])));
  printf("\nRegister Y: " NIBBLE_TO_BINARY_PATTERN,
         NIBBLE_TO_BINARY(get_u4_value(&tiny4->R[1])));
  printf("\nOutput: \x1B[30;1m █ ▁ █ █\n");
  printf("\n");
  reset_font_style();
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

void sleep_terminal(unsigned int sleep_time_msec) {
#ifdef _WIN32
  // Windows: Sleep for 5000 milliseconds (5 seconds)
  Sleep(sleep_time_msec);
#else
  // Unix-like systems: Sleep for 5 seconds
  sleep(sleep_time_msec / 1000);
#endif
}