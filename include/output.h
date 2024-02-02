#pragma once

#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void draw_terminal_output();
void clear_terminal();
void reset_font_style();
void sleep_terminal();