CC = gcc
CFLAGS = -Wall -Wextra -g
# ASAN_FLAGS = -fsanitize=address -fstack-protector

# Source files and objects
SRC = darray.c
OBJ = $(SRC:.c=.o)
TEST_SRC = test_darray.c
TEST_OBJ = $(TEST_SRC:.c=.o)
HEADERS = darray.h

# Targets
TEST_TARGET = test_darray

# Default builds tests
all: $(TEST_TARGET)

# Pattern rule for object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(ASAN_FLAGS) -c $< -o $@

# Test program
$(TEST_TARGET): $(TEST_OBJ) $(OBJ)
	@echo "Building tests with ASan..."
	$(CC) $(CFLAGS) $(ASAN_FLAGS) -o $@ $^

# Run tests
test: $(TEST_TARGET)
	@echo "Running tests..."
	./$(TEST_TARGET)

# Analysis builds
analyze: $(TEST_TARGET)
	@echo "Building for Valgrind analysis..."
	$(CC) $(CFLAGS) -o $(TEST_TARGET).analyze $(TEST_SRC) $(SRC)

# Valgrind analysis targets
valgrind: analyze
	valgrind --leak-check=full \
		--show-leak-kinds=all \
		--track-origins=yes \
		--verbose \
		./$(TEST_TARGET).analyze

# Show help
help:
	@echo "Available targets:"
	@echo "  all            : Build tests"
	@echo "  $(TEST_TARGET) : Build test program"
	@echo "  test          : Build and run tests"
	@echo "  valgrind      : Build and run with Valgrind"
	@echo "  clean         : Remove all built files"
	@echo "  help          : Show this help message"

clean:
	rm -f $(TEST_TARGET) $(TEST_TARGET).analyze *.o

.PHONY: all clean help test valgrind analyze
