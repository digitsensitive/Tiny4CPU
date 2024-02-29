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
- 2 general-purpose registers and memory space of 8 bytes
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

### Instruction Set

Tiny4CPU has `16 opcodes` (operation code, OP or instruction machine code).

| Mnemonic | Binary | OP  | Number of bytes | Description                             |
| -------- | ------ | --- | --------------- | --------------------------------------- |
| NOP      | 0000   | #0  | 1               | No operation (Do nothing)               |
| LDX      | 0001   | #1  |                 |
| LDY      | 0010   | #2  |                 |
| ADX      | 0011   | #3  |                 |
| ADY      | 0100   | #4  |                 |
| SUX      | 0101   | #5  |                 |
| SUY      | 0110   | #6  |                 |
| NOX      | 0111   | #7  |                 |
| OUT      | 1000   | #8  |                 |
| STX      | 1001   | #9  |                 |
| STY      | 1010   | #A  |                 |
| JXZ      | 1011   | #B  |                 |
| JYZ      | 1100   | #C  |                 |
| JCA      | 1101   | #D  |                 |
| JMP      | 1110   | #E  | 3               | Unconditional jump to memory address kk |
| HLT      | 1111   | #F  |                 |

#### Hex and Timing

| Load Register X with immediate nibble value k |
| Load Register Y with immediate nibble value k |
| Add immediate nibble value k to Register X |
| Add immediate nibble value k to Register Y |
| Subtract immediate nibble value k from Register X |
| Subtract immediate nibble value k from Register Y |
| Perform bitwise NOT operation on Register X |
| Perform bitwise NOT operation on Register Y |
| Store Register X value to memory address k |
| Store Register Y value to memory address k |
| Jump to memory address k if Register X is zero |
| Jump to memory address k if Register Y is zero |
| Jump to memory address if carry flag is set |

| Halt execution |

#### Details

##### JMP

Unconditional jump to (memory) address.

###### Format

| 1110 | ADDRESS NIBBLE |
| ---- | -------------- |

###### Function

| PC &#11013; ADDRESS |
| ------------------- |

###### Description

A new address is loaded in the program counter and a jump in the program
sequence occurs. The address specification can only be absolute.

### Registers

| Register | Size (bits) | Description                  |
| -------- | ----------- | ---------------------------- |
| PC       | 4           | Program Counter              |
| IR       | 8           | Instruction Register         |
| IAR      | 8           | Instruction Address Register |
| ACC      | 4           | Accumulator                  |
| MAR      | 4           | Memory Address Register      |
| R0       | 4           | General purpose register     |
| R1       | 4           | General purpose register     |

### Memory

- Mono-directional 8-bit address-bus from the microprocessor unit (MPU) to memory
- The memory layout consists of one Memory Address Register (MAR).
  The MAR is connected to two 2x4 decoder, enabling addressing of up
  to 16 memory locations
- Each memory location holds 4 bits of data, resulting in a total memory size
  of 8 bytes

### Addressing Modes

Addressing refers to the specification of the location of the operand.

#### Absolute (Extended)

| OPCODE | FULL 16-BIT |
| ------ | ----------- |

| OPCODE | ADDRESS |
| ------ | ------- |

### Endianness

- Big-endian: Most-significant-byte is saved in memory first
  (i.e. the lower memory address)

### Clock Frequency

TO BE COMPLETED

## References

- [ANSI Escape Code](https://en.wikipedia.org/wiki/ANSI_escape_code)
- [ANSI Escape Sequences, Github](https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797)
- [ASCII Chart](https://en.cppreference.com/w/cpp/language/ascii)
- [DDL4-CPU, A Modular 4-Bit CPU Design by Dave](https://hackaday.io/project/158510/logs)
- [Github project td4-py by yashikota](https://github.com/yashikota/td4-py)
- [Symbl](https://symbl.cc/en)
