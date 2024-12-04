CC = gcc # you may need to change this, depending on your OS
CFLAGS = -Xclang -fopenmp # you may need to change this, depending on your OS
INCFLAGS =  -I/usr/local/opt/libomp/include/# you may need to change this, depending on your OS
LDFLAGS = -L/usr/local/opt/libomp/lib/ -lomp # you may need to change this, depending on your OS
RM = /bin/rm -f
EXE = ask1
all: $(EXE)
%: %.c
	$(CC) $(CFLAGS) $(INCFLAGS) $(LDFLAGS) -o $@ $<
%.o: %.c
	$(CC) $(CFLAGS) $(INCFLAGS) -c $@ $<
clean:
	$(RM) *.o $(EXE)
