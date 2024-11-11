# Compiler and flags
CC = gcc
CFLAGS = -Wall -Werror -Wextra

# Automatically gather mandatory and bonus .c files from the src directory
MANDATORY_SRCS = $(wildcard src/mandatory/*.c)
BONUS_SRCS = $(wildcard src/bonus/*.c)

# Test files (all test files in the tests directory)
TEST_SRCS = $(wildcard tests/test_*.c)

# Object files (for both mandatory and bonus)
MANDATORY_OBJS = $(MANDATORY_SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)
TEST_OBJS = $(TEST_SRCS:.c=.o)

# Test executables (for both mandatory and bonus)
MANDATORY_TESTS = $(TEST_SRCS:tests/test_%.c=test_%)
BONUS_TESTS = $(BONUS_SRCS:src/bonus/%.c=test_%)

# Default target to build mandatory tests only
all: $(MANDATORY_TESTS)

# Build each mandatory test executable
$(MANDATORY_TESTS): test_%: tests/test_%.o $(MANDATORY_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Build each bonus test executable (only if BONUS_SRCS is not empty)
$(BONUS_TESTS): test_%: tests/test_%.o $(BONUS_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Build the bonus part explicitly when requested
bonus: $(BONUS_TESTS)

# Run all tests using the script
test: all
	./tests/run_tests.sh

# Clean up generated files
clean:
	rm -f $(MANDATORY_OBJS) $(BONUS_OBJS) $(TEST_OBJS) $(MANDATORY_TESTS) $(BONUS_TESTS)

# Full cleanup
fclean: clean
	rm -f $(MANDATORY_TESTS) $(BONUS_TESTS)

# Rebuild everything (mandatory + bonus)
re: fclean all
