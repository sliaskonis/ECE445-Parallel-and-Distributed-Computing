# Compiler
MPICC = mpicc
CC = gcc

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Compiler flags
CFLAGS = -I$(SRC_DIR)
ifdef DEBUG
    CFLAGS += -DDEBUG -g
endif

# Source files
SRC = $(wildcard $(SRC_DIR)/*.c)

# Executables
EXE = $(SRC:$(SRC_DIR)/%.c=$(BIN_DIR)/%)

# Default target: build all executables
all: $(EXE)

# Pattern rule to build executables
$(BIN_DIR)/%: $(SRC_DIR)/%.c | $(BIN_DIR)
	$(MPICC) $(CFLAGS) -o $@ $<

# Special rules for specific files
$(BIN_DIR)/ask4_ser: $(SRC_DIR)/ask4_ser.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $<

# Create output directories
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean up generated files
clean:
	rm -rf $(BIN_DIR)
	rm -rf $(OBJ_DIR)