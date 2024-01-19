CC = gcc
CFLAGS = -std=c11 -Wall
SRC_DIR = src
BUILD_DIR = build

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

tiny4cpu.exe: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)/*.o
	rm -f tiny4cpu.exe
create:
	$(CC) $(CFLAGS) src/main.c -o tiny4cpu.exe

clean:
	rm *.exe