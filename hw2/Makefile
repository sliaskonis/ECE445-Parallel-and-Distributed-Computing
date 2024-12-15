# Compiler and flags
CC = clang # you may need to change this, depending on your OS
CFLAGS = -fopenmp -O3 -g -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.2.sdk/# you may need to change this, depending on your OS
INCFLAGS =  -I/opt/homebrew/opt/libomp/include/# you may need to change this, depending on your OS
LDFLAGS = -L/opt/homebrew/opt/libomp/lib # you may need to change this, depending on your OS

# directories
SRC_DIR = src
BIN_DIR = bin

# Source and target files
#SRC_FILES = $(wildcard $(SRC_DIR)/*.c) # Find all .c files in SRC_DIR
#TARGETS = $(patsubst $(SRC_DIR)/%.c, %, $(SRC_FILES)) # Derive target names
#
RM = /bin/rm -f

# Target executables
TARGET_1 = ask1
TARGET_2S = ask2_s
TARGET_2P = ask2_p
TARGET_2PA = ask2_p_A
TARGET_2PB = ask2_p_B
TARGET_3 = ask3
TARGETS = $(TARGET_1) $(TARGET_2S) $(TARGET_2P) $(TARGET_2PA) $(TARGET_2PB) $(TARGET_3)

# Default rule
all: $(TARGETS)


# Rules to create each program
$(TARGET_1): $(SRC_DIR)/$(TARGET_1).c  $(BIN_DIR)
	$(CC) $(CFLAGS) $(INCFLAGS) $(LDFLAGS) $(SRC_DIR)/$(TARGET_1).c -o $(BIN_DIR)/$(TARGET_1)
$(TARGET_2S): $(SRC_DIR)/$(TARGET_2S).c  $(BIN_DIR)
	$(CC) $(CFLAGS) $(INCFLAGS) $(LDFLAGS) $(SRC_DIR)/$(TARGET_2S).c -o $(BIN_DIR)/$(TARGET_2S)
$(TARGET_2P): $(SRC_DIR)/$(TARGET_2P).c $(BIN_DIR)
	$(CC) $(CFLAGS) $(INCFLAGS) $(LDFLAGS) $(SRC_DIR)/$(TARGET_2P).c -o $(BIN_DIR)/$(TARGET_2P)
$(TARGET_2PA): $(SRC_DIR)/$(TARGET_2PA).c $(BIN_DIR)
	$(CC) $(CFLAGS) $(INCFLAGS) $(LDFLAGS) $(SRC_DIR)/$(TARGET_2PA).c -o $(BIN_DIR)/$(TARGET_2PA)
$(TARGET_2PB): $(SRC_DIR)/$(TARGET_2PB).c $(BIN_DIR)
	$(CC) $(CFLAGS) $(INCFLAGS) $(LDFLAGS) $(SRC_DIR)/$(TARGET_2PB).c -o $(BIN_DIR)/$(TARGET_2PB)
$(TARGET_3): $(SRC_DIR)/$(TARGET_3).c $(SRC_DIR)/jacobi_par.c $(BIN_DIR)
	$(CC) $(CFLAGS) -lm $(INCFLAGS) $(LDFLAGS) $(SRC_DIR)/$(TARGET_3).c $(SRC_DIR)/jacobi_par.c -o $(BIN_DIR)/$(TARGET_3)

# Binaries directory
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean up executables
clean:
	$(RM) -r $(BIN_DIR)/*