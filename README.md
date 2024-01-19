# Tiny4CPU

![GitHub repo size](https://img.shields.io/github/repo-size/digitsensitive/Tiny4CPU)
![GitHub Release](https://img.shields.io/github/v/release/digitsensitive/Tiny4CPU)

Tiny4CPU is a lightweight and educational 4-bit CPU emulator designed for
simplicity. This project provides a hands-on exploration into the fundamentals
of computer architecture, offering a platform to experiment with assembly
language programming in a compact environment.

Dive into the world of microprocessors with Tiny4CPU and witness the power of
4 bits in action.

<img src="./readme_image.png" alt="Tiny4CPU" style="width: 100%;"/>

## Instructions

Tiny4CPU applications or ROMS are saved as `*.t4` files.

Tiny4CPU has `16 opcodes` (operation code or instruction machine code), which are
all `one byte long` and stored `big-endian`. This means that the
most-significant-byte is saved in memory first (i.e. the lower memory address).

- `Load (LDX)`: 2k - LDX k
  Set X = k.
  Load the nibble value k into the register X.
- `Addition (ADX)`: 3k - ADX k
  Set X = X + k.
  Adds the value of k to the value of register X, then stores the result in X.

## Notes

- 00 - CLS, Clear the display
- 1n - JP addr (n) (set pc to n). This would limit it to only jump to memory between 0 and 15. You might extend this by a factor of 16, means 256 bytes memory size, if you must load register A first with a number between 0 and 15, this number would be saved in a register A in RAM. Then you take the addr n in the bus, which goes to register B in RAM and selects the memory location

  Subtraction (SUB)
  Multiplication (MUL)
  Division (DIV)
  Load from Memory (LD)
  Store to Memory (ST)
  Conditional Branch (BR)
  Jump (JMP)
  Bitwise AND (AND)
  Bitwise OR (OR)
  Bitwise XOR (XOR)
  Shift Left (SHL)
  Shift Right (SHR)
  Compare (CMP)
  Set to 1 if Negative (SETN)
  Set to 1 if Zero (SETZ)
