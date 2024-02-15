# Tiny4CPU

WORK IN PROGRESS!

![GitHub repo size](https://img.shields.io/github/repo-size/digitsensitive/Tiny4CPU)
![GitHub Release](https://img.shields.io/github/v/release/digitsensitive/Tiny4CPU)

Tiny4CPU is a lightweight and educational 4-bit CPU emulator designed for
simplicity. This project provides a hands-on exploration into the fundamentals
of computer architecture, offering a platform to experiment with assembly
language programming in a compact environment.

Dive into the world of microprocessors with Tiny4CPU and witness the power of
4 bits in action.

This project was inspired by [yashikota/td4-py](https://github.com/yashikota/td4-py),
which was inspired by [How to Build a CPU by Iku Watanabe](https://www.amazon.co.jp/CPU%E3%81%AE%E5%89%B5%E3%82%8A%E3%81%8B%E3%81%9F-%E6%B8%A1%E6%B3%A2-%E9%83%81/dp/4839909865/ref=asap_bc?ie=UTF8).

<img src="./tiny4cpu.gif" alt="Tiny4CPU" style="width: 100%;"/>

## Features

- 4-bit architecture with its own assembler
- 16-instruction set for data manipulation and control flow
- 2 general-purpose registers and memory space of 16 bytes
- Ability to adjust CPU clock cycles for synchronization in milliseconds
- Assembly language support
- Modular and extensible design
- Comprehensive documentation

## How to write a program for the Tiny4CPU

Tiny4CPU programs are written in T4C Assembly and saved as `*.t4c` files.
Use the Tiny4CPU Assembler to assembly your program to a `*.bin` file.
After that, load your ROM `*.bin` file using the Tiny4CPU executable, including
the file path and the clock time in milliseconds.

Example:

```bash
./assembler .../examples/counter.t4c
./tiny4cpu .../examples/counter.bin 1000
```

Find some examples in the root examples folder.

## Instruction set architecture (ISA)

Tiny4CPU has `16 opcodes` (operation code or instruction machine code), which are
all `one byte long` and stored `big-endian`. This means that the
most-significant-byte is saved in memory first (i.e. the lower memory address).

| Nr. | Mnemonic | Opcode    | Operands | Description                                       |
| --- | -------- | --------- | -------- | ------------------------------------------------- |
| 0   | NOP      | 0000      | 0        | No operation (Do nothing)                         |
| 1   | LDX      | 0001 kkkk | 1        | Load Register X with immediate nibble value k     |
| 2   | LDY      | 0010 kkkk | 1        | Load Register Y with immediate nibble value k     |
| 3   | ADX      | 0011 kkkk | 1        | Add immediate nibble value k to Register X        |
| 4   | ADY      | 0100 kkkk | 1        | Add immediate nibble value k to Register Y        |
| 5   | SUX      | 0101 kkkk | 1        | Subtract immediate nibble value k from Register X |
| 6   | SUY      | 0110 kkkk | 1        | Subtract immediate nibble value k from Register Y |
| 7   | NOX      | 0111      | 0        | Perform bitwise NOT operation on Register X       |
| 8   | NOY      | 1000      | 0        | Perform bitwise NOT operation on Register Y       |
| 9   | STX      | 1001 kkkk | 1        | Store Register X value to memory address k        |
| 10  | STY      | 1010 kkkk | 1        | Store Register Y value to memory address k        |
| 11  | JXZ      | 1011 kkkk | 1        | Jump to memory address k if Register X is zero    |
| 12  | JYZ      | 1100 kkkk | 1        | Jump to memory address k if Register Y is zero    |
| 13  | JCA      | 1101 kkkk | 1        | Jump to memory address if carry flag is set       |
| 14  | JMP      | 1110 kkkk | 1        | Unconditional jump to memory address k            |
| 15  | HLT      | 1111      | 0        | Halt execution                                    |

## References

- [ANSI Escape Code](https://en.wikipedia.org/wiki/ANSI_escape_code)
- [ANSI Escape Sequences, Github](https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797)
- [ASCII Chart](https://en.cppreference.com/w/cpp/language/ascii)
- [DDL4-CPU, A Modular 4-Bit CPU Design by Dave](https://hackaday.io/project/158510/logs)
- [Github project td4-py by yashikota](https://github.com/yashikota/td4-py)
- [Symbl](https://symbl.cc/en)
