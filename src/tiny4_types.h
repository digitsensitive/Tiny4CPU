#pragma once

#include "stdint.h"

typedef enum { false = 0, true = 1 } bool;
typedef uint8_t u8;

// 4 bits  -> [0-15] or [0x0-0xF]
typedef struct {
  u8 value : 4; /* Using a bit-field to represent 4 bits*/
} u4;

static inline u8 get_u4_value(u4 *u) { return u->value; }

static inline void set_u4_value(u4 *u, uint8_t new_value) {
  u->value = new_value & 0x0F;  // Ensure only the lower 4 bits are set
}

static inline void add_u4_value(u4 *u, uint8_t value) {
  u->value = (u->value + value) & 0x0F;  // Ensure only the lower 4 bits are set
}
