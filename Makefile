CC = gcc
CFLAGS = -I./include -Wall -Wextra
SRC = src/main.c src/lexer.c src/parser.c src/symbol_table.c
OBJ = $(SRC:.c=.o)
BUILD_DIR = build
TARGET = $(BUILD_DIR)/boolean_compiler

all: $(TARGET)

$(TARGET): $(OBJ)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(BUILD_DIR)
