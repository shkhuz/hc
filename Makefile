PROJECT := hc

SRC_DIR := src
INC_DIR := src

OBJ_DIR := obj

C_FILES := $(shell find $(SRC_DIR) -name "*.c")
ASM_FILES := $(shell find $(SRC_DIR) -name "*.asm")

OBJ_FILES := $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(C_FILES)))
OBJ_FILES += $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(ASM_FILES)))
BIN_FILE := lib$(PROJECT).a

CC := gcc
LD := gcc

CFLAGS := -I$(INC_DIR) -g -std=c99 -pedantic -Wall -Wextra -Wshadow -Wno-write-strings -m64
LDFLAGS :=

$(BIN_FILE): $(OBJ_FILES)
	ar rcs $@ $^

$(OBJ_DIR)/%.c.o: %.c
	@mkdir -p $(OBJ_DIR)/$(dir $^)
	$(CC) -c $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.asm.o: %.asm
	@mkdir -p $(OBJ_DIR)/$(dir $^)
	nasm -felf64 -o $@ $^

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_FILE)

loc:
	find $(SRC_DIR) \
		-name "*.cpp" -or \
		-name "*.hpp" -or \
		-name "*.h" -or \
		-name "*.c" -or \
		-name "*.asm" \
	| xargs cat | wc -l

.PHONY: clean loc
