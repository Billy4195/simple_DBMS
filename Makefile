CC=gcc
CFLAGS=-Iinclude -Wall
TARGET=shell
DEPS=$(wildcard *.h)

SRC_DIR=src
SRC=$(wildcard $(SRC_DIR)/*.c)
OBJ=$(patsubst $(SRC_DIR)/%.c, $(SRC_DIR)/%.o, $(SRC))
DEP_OBJ=$(filter-out src/$(TARGET).o, $(OBJ))

TEST_SRC_DIR=test
TEST_SRC=$(wildcard $(TEST_SRC_DIR)/*_test.c)
TESTS=$(patsubst $(TEST_SRC_DIR)/%_test.c, $(TEST_SRC_DIR)/%_test,$(TEST_SRC))

all: $(TARGET) $(TESTS)

%.o: %.c $(DEPS)
	$(CC) -o $@ $< -c $(CFLAGS)

shell: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

$(TESTS): $(TEST_SRC) $(DEP_OBJ) $(DEPS)
	$(CC) -o $@ $(TEST_SRC) $(DEP_OBJ) $(CFLAGS)

.PHONY: clean

clean:
	rm $(TARGET) $(OBJ) $(TESTS)
