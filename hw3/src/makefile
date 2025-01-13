# Compiler
CC = mpicc

# Compiler flags
CFLAGS = -Wall -O2

# Source files
SRC = ask1.c ask2.c ask3.c

# Executables
EXE = ask1 ask2 ask3

# Default target: build all executables
all: $(EXE)

# Compile ask1.c
ask1: ask1.c
	$(CC) $(CFLAGS) -o $@ $<

# Compile ask2.c
ask2: ask2.c
	$(CC) $(CFLAGS) -o $@ $<

# Compile ask3.c
ask3: ask3.c
	$(CC) $(CFLAGS) -o $@ $<

# Clean up generated files
clean:
	rm -f $(EXE)
