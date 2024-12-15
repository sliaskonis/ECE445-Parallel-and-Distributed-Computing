# Compiler and flags
CC = gcc # you may need to change this, depending on your OS
CFLAGS = -fopenmp -g # you may need to change this, depending on your OS
INCFLAGS =  -I/usr/local/opt/libomp/include/# you may need to change this, depending on your OS
LDFLAGS = -L/usr/local/opt/libomp/lib/ # you may need to change this, depending on your OS

# directories
SRC_DIR = src
BIN_DIR = bin

RM = /bin/rm -f

# Target executables
TARGET_1 = ask1
TARGET_2S = ask2_serial
TARGET_2PA = ask2_par
TARGET_3 = ask3
TARGETS = $(TARGET_1) $(TARGET_2S) $(TARGET_2PA) $(TARGET_3)

# Default rule
all: $(TARGETS)


# Rules to create each program
$(TARGET_1): $(SRC_DIR)/$(TARGET_1).c  $(BIN_DIR)
	$(CC) $(CFLAGS) $(INCFLAGS) $(LDFLAGS) $(SRC_DIR)/$(TARGET_1).c -o $(BIN_DIR)/$(TARGET_1)
$(TARGET_2S): $(SRC_DIR)/$(TARGET_2S).c  $(BIN_DIR)
	$(CC) $(CFLAGS) $(INCFLAGS) $(LDFLAGS) $(SRC_DIR)/$(TARGET_2S).c -o $(BIN_DIR)/$(TARGET_2S)
$(TARGET_2PA): $(SRC_DIR)/$(TARGET_2PA).c $(BIN_DIR)
	$(CC) $(CFLAGS) $(INCFLAGS) $(LDFLAGS) $(SRC_DIR)/$(TARGET_2PA).c -o $(BIN_DIR)/$(TARGET_2PA)
$(TARGET_3): $(SRC_DIR)/$(TARGET_3).c $(SRC_DIR)/jacobi_par.c $(BIN_DIR)
	$(CC) $(CFLAGS) -lm $(INCFLAGS) $(LDFLAGS) $(SRC_DIR)/$(TARGET_3).c $(SRC_DIR)/jacobi_par.c -o $(BIN_DIR)/$(TARGET_3)

# Binaries directory
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean up executables
clean:
	$(RM) -r $(BIN_DIR)/*