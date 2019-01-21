CC=gcc
CFLAGS=-I. -Wall
TARGET=shell
DEPS=InputBuffer.h Util.h Command.h
OBJ=InputBuffer.o shell.o Util.o Command.o

all: $(TARGET)

%.o: %.c $(DEPS)
	$(CC) -o $@ $< -c $(CFLAGS)

shell: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm $(TARGET) $(OBJ)
