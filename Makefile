CC=gcc
CFLAGS=-I. -Wall
TARGET=shell
DEPS=InputBuffer.h Util.h Command.h
OBJ=InputBuffer.o shell.o Util.o Command.o
TEST_SRC_DIR=test
TEST_SRC=$(wildcard $(TEST_SRC_DIR)/*_test.c)
TESTS=$(patsubst $(TEST_SRC_DIR)/%_test.c, $(TEST_SRC_DIR)/%_test,$(TEST_SRC))

all: $(TARGET) $(TESTS)

%.o: %.c $(DEPS)
	$(CC) -o $@ $< -c $(CFLAGS)

shell: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

$(TESTS): $(TEST_SRC) Command.c Command.h
	$(CC) -o $@ $(TEST_SRC) Command.c $(CFLAGS)

.PHONY: clean

clean:
	rm $(TARGET) $(OBJ) $(TESTS)
