#pragma once

#include <stdio.h>

#include "tiny4.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void draw_terminal_output(Tiny4 *tiny4);
void clear_terminal();
void reset_font_style();
void sleep_terminal(unsigned int sleep_time_msec);