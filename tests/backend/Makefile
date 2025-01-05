CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

SRC_DIR = ../../src/engine/
BIN_DIR = .

TESTS = $(wildcard *_test.c)
TEST_BIN = $(patsubst %.c,$(BIN_DIR)/%,$(TESTS))

all: $(TEST_BIN)

$(BIN_DIR)/%: %.c $(SRC_DIR)/engine.c
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

run: all
	@for test in $(TEST_BIN); do echo "Running $$test"; $$test; done

clean:
	rm -rf $(BIN_DIR)

.PHONY: all run clean
