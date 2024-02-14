# Variables
PROGRAM_NAME = assembler

# Directory stucture
SRC_DIR = src
INCLUDE_DIR = include
SHARED_DIR = ../shared
BUILD_DIR = build

# Compiler and flags
CC = gcc
CFLAGS = -std=c11 -Wall -Wno-missing-braces -I$(INCLUDE_DIR) -I$(SHARED_DIR)

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

$(PROGRAM_NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Remove object files in build folder and the executable
clean:
	rm -rf $(BUILD_DIR)/*.o
	rm $(PROGRAM_NAME)
	
# Build the executable
build:
	$(CC) $(CFLAGS) $(SRC_DIR)/main.c -o $(PROGRAM_NAME)