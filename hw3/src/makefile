# Compiler
MPICC = mpicc
CC = gcc

# Compiler flags
CFLAGS = -Wall -O2

# Source files
SRC = ask1.c ask2.c ask3.c

# Executables
EXE = ask1 ask2 ask3 ask4_ser ask4_par

# Default target: build all executables
all: $(EXE)

# Compile ask1.c
ask1: ask1.c
	$(MPICC) $(CFLAGS) -o $@ $<

# Compile ask2.c
ask2: ask2.c
	$(MPICC) $(CFLAGS) -o $@ $< -lm

# Compile ask3.c
ask3: ask3.c
	$(MPICC) $(CFLAGS) -o $@ $<

ask4_ser: ask4_ser.c
	$(CC) $(CFLAGS) -o $@ $<

ask4_par: ask4_par.c
	$(MPICC) $(CFLAGS) -o $@ $<

# Clean up generated files
clean:
	rm -f $(EXE)
