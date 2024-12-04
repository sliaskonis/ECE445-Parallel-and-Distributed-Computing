# Compiler and flags
CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -O2

# Directories
SRC_DIR = src
INCLUDE_DIR = include

# Source files
SRCS_NORMS = $(SRC_DIR)/norms.c
SRCS_PROB3 = $(SRC_DIR)/problem3.c
SRCS_PROB4 = $(SRC_DIR)/problem4.c

# Object files
OBJS_NORMS = $(SRCS_NORMS:.c=.o)

# Target executables
TARGET_PROB3 = problem3
TARGET_PROB4 = problem4

# Default rule
all: $(TARGET_PROB3) $(TARGET_PROB4)

# Rules to create each program
$(TARGET_PROB3): $(OBJS_NORMS) $(SRC_DIR)/problem3.o
	$(CC) $(OBJS_NORMS) $(SRC_DIR)/problem3.o -o $(TARGET_PROB3)

$(TARGET_PROB4): $(OBJS_NORMS) $(SRC_DIR)/problem4.o
	$(CC) $(OBJS_NORMS) $(SRC_DIR)/problem4.o -o $(TARGET_PROB4)

# Compile .c files to .o files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE_DIR)/norms.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and executables
clean:
	rm -f $(SRC_DIR)/*.o $(TARGET_PROB3) $(TARGET_PROB4)

# Phony targets
.PHONY: all clean