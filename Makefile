CC=gcc
CFLAGS=-Iinclude -Wall
TARGET=shell
DEPS=$(wildcard *.h)

SRC_DIR=src
SRC=$(wildcard $(SRC_DIR)/*.c)
OBJ=$(patsubst $(SRC_DIR)/%.c, $(SRC_DIR)/%.o, $(SRC))
DEP_SRC=$(filter-out src/$(TARGET).c, $(SRC))
DEP_OBJ=$(filter-out src/$(TARGET).o, $(OBJ))

CXX=g++
TEST_SRC_DIR=test
TEST_SRC=$(wildcard $(TEST_SRC_DIR)/*_test.c)
TESTS=$(patsubst $(TEST_SRC_DIR)/%_test.c, $(TEST_SRC_DIR)/%_test,$(TEST_SRC))
TEST_FLAGS=-lgtest -pthread -std=c++11

all: $(TARGET) $(TESTS)

%.o: %.c $(DEPS)
	$(CC) -o $@ $< -c $(CFLAGS)

shell: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

check: $(TESTS)
	-./test/all_test
	find test/ -name "*.db" -delete

$(TESTS): $(TEST_SRC) $(DEP_SRC) $(DEPS)
	$(CXX) -o $@ $(TEST_SRC) $(DEP_SRC) $(CFLAGS) $(TEST_FLAGS)

.PHONY: clean check

clean:
	rm $(TARGET) $(OBJ) $(TESTS) $(wildcard test/*.db)
