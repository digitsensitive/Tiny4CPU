#pragma once
#include "stdint.h"

typedef enum { false = 0, true = 1 } bool;

// 4 bits  -> [0-15] or [0x0-0xF]
typedef struct {
  uint8_t value : 4; /* Using a bit-field to represent 4 bits*/
} u4;

typedef uint8_t u8;
