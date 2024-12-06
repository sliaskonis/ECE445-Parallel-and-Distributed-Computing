CC = gcc # you may need to change this, depending on your OS
CFLAGS = -fopenmp -g # you may need to change this, depending on your OS
INCFLAGS =  -I/usr/local/opt/libomp/include/ -lm# you may need to change this, depending on your OS
LDFLAGS = -L/usr/local/opt/libomp/lib/ # you may need to change this, depending on your OS

# directories
SRC_DIR = src

# Source and target files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c) # Find all .c files in SRC_DIR
TARGETS = $(patsubst $(SRC_DIR)/%.c, %, $(SRC_FILES)) # Derive target names

RM = /bin/rm -f

# Default rule
all: $(TARGETS)

%: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCFLAGS) $(LDFLAGS) $< -o $@

clean:
	$(RM) *.o $(TARGETS) $(SRC_DIR)/*.o

# source files
#ASK_1 = $(SRC_DIR)/ask1.c
#ASK_2S = $(SRC_DIR)/ask2_s.c
#ASK_2P = $(SRC_DIR)/ask2_p.c
#ASK_2PA = $(SRC_DIR)/ask2_p_A.c
#
#
# Target executables
#TARGET_1 = ask1
#TARGET_2S = ask2_s
#TARGET_2P = ask2_p
#TARGET_2PA = ask2_p_A
#TARGET_2PB = ask2_p_B
#TARGETS = $(TARGET_1) $(TARGET_2S) $(TARGET_2P) $(TARGET_2PA) $(TARGET_2PB)
# Rules to create each program
#$(TARGET_1): $(SRC_DIR)/$(TARGET_1).o
#	$(CC) $(CFLAGS) $(INCFLAGS) $(LDFLAGS) $(SRC_DIR)/$(TARGET_1).o -o $(TARGET_1)
#$(TARGET_2S): $(SRC_DIR)/$(TARGET_2S).o
#	$(CC) $(CFLAGS) $(INCFLAGS) $(LDFLAGS) $(SRC_DIR)/$(TARGET_2S).o -o $(TARGET_2S)
#$(TARGET_2P): $(SRC_DIR)/$(TARGET_2P).o
#	$(CC) $(CFLAGS) $(INCFLAGS) $(LDFLAGS) $(SRC_DIR)/$(TARGET_2P).o -o $(TARGET_2P)
#$(TARGET_2PA): $(SRC_DIR)/$(TARGET_2PA).o
#	$(CC) $(CFLAGS) $(INCFLAGS) $(LDFLAGS) $(SRC_DIR)/$(TARGET_2PA).o -o $(TARGET_2PA)
#$(TARGET_1): $(SRC_DIR)/$(TARGET_2PB).o
#	$(CC) $(CFLAGS) $(INCFLAGS) $(LDFLAGS) $(SRC_DIR)/$(TARGET_2PB).o -o $(TARGET_2PB)

# Create object files
#$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
#	$(CC) $(CFLAGS) $(INCFLAGS) -c $@ $<

# Clean up executables and object files