CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Wpedantic -O2 -Wconversion -Wshadow -Wundef -g -I./include
# ASAN_FLAGS = -fsanitize=address -fstack-protector

# Directories
SRC_DIR = src
INC_DIR = include
TEST_DIR = test
OBJ_DIR = obj
BIN_DIR = bin

# Source files and objects
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TEST_SRC = $(wildcard $(TEST_DIR)/*.c)
TEST_BINS = $(TEST_SRC:$(TEST_DIR)/%.c=$(BIN_DIR)/%)

HEADERS = $(wildcard $(INC_DIR)/*.h)

# Create directories if they don't exist
$(shell mkdir -p $(OBJ_DIR) $(BIN_DIR))

# Default target builds all tests
all: $(TEST_BINS)

# Pattern rule for source object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) $(ASAN_FLAGS) -c $< -o $@

# Pattern rule for test object files
$(OBJ_DIR)/test_%.o: $(TEST_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) $(ASAN_FLAGS) -c $< -o $@

# Pattern rule to build each test executable
$(BIN_DIR)/%: $(TEST_DIR)/%.c $(OBJ)
	$(CC) $(CFLAGS) $(ASAN_FLAGS) $^ -o $@

# Run all tests
test: $(TEST_BINS)
	@for test in $(TEST_BINS) ; do \
		echo "Running $$test..." ; \
		./$$test ; \
	done

# List all available tests
list-tests:
	@echo "Available tests:"
	@for test in $(TEST_BINS) ; do \
		echo "  $${test#$(BIN_DIR)/}" ; \
	done

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean test list-tests
.PRECIOUS: $(OBJ_DIR)/%.o
