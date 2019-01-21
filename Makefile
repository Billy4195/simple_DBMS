CC=gcc
CFLAGS=-I. -Wall
TARGET=shell test_Command
DEPS=InputBuffer.h Util.h Command.h
OBJ=InputBuffer.o shell.o Util.o Command.o

all: $(TARGET)

%.o: %.c $(DEPS)
	$(CC) -o $@ $< -c $(CFLAGS)

shell: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

test_Command: test_Command.c Command.c Command.h
	$(CC) -o $@ test_Command.c Command.c $(CFLAGS)

.PHONY: clean

clean:
	rm $(TARGET) $(OBJ)
