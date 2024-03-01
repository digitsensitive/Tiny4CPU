#include "output.h"

#define NIBBLE_TO_BINARY_PATTERN "%c%c%c%c"

#define NIBBLE_TO_BINARY(nibble)                                  \
  ((nibble) & 0x08u ? '1' : '0'), ((nibble) & 0x04u ? '1' : '0'), \
      ((nibble) & 0x02u ? '1' : '0'), ((nibble) & 0x01u ? '1' : '0')

void draw_terminal_output(Tiny4* tiny4) {
  printf("\x1B[32;1m");
  printf("=================\n");
  printf("Tiny4CPU Emulator\n");
  printf("=================\n");
  reset_font_style();
  printf("Power: %s\n", tiny4->is_running ? "On" : "Off");
  printf("Program Length: %d\n", tiny4->program_length);
  printf("Program Size: %d bytes\n", tiny4->program_length / 2);
  printf("PC: %d\n", get_u4_value(&tiny4->program_counter));
  printf("Clock: %d Hz\n", tiny4->clock_hertz);
  printf("Register X: " NIBBLE_TO_BINARY_PATTERN,
         NIBBLE_TO_BINARY(get_u4_value(&tiny4->register_x)));
  printf("\nRegister Y: " NIBBLE_TO_BINARY_PATTERN,
         NIBBLE_TO_BINARY(get_u4_value(&tiny4->register_y)));
  printf("\n\nOutput:");
  for (int i = 0; i < 16; i++) {
    if (i % 4 == 0) {
      printf("\n");
    }

    if (i == get_u4_value(&tiny4->output)) {
      printf("\x1B[34;1m");
      printf("◼ ");
      reset_font_style();
    } else {
      printf("◻ ");
    }
  }

  printf("\n\n");

  printf("Instruction Memory:\n");
  printf("[OP] Binary    [Hex,    Dec]\n");
  printf("----------------------------\n");
  for (int i = 0; i < tiny4->program_length; i = i + 2) {
    if ((get_u4_value(&tiny4->program_counter) - 2) / 2 == i / 2) {
      printf("\x1B[33;1m");
    }
    printf("[%2d] %c%c%c%c %c%c%c%c [0x%X%X, %2d %2d]\n", i / 2,
           NIBBLE_TO_BINARY(get_u4_value(&tiny4->memory[i])),
           NIBBLE_TO_BINARY(get_u4_value(&tiny4->memory[i + 1])),
           get_u4_value(&tiny4->memory[i]), get_u4_value(&tiny4->memory[i + 1]),
           get_u4_value(&tiny4->memory[i]),
           get_u4_value(&tiny4->memory[i + 1]));
    reset_font_style();
  }
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