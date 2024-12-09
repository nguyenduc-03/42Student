# Compiler and flags
CC         = gcc
CFLAGS     = -Wall -Wextra -Werror 
NAME       = get_next_line
SRCS       = get_next_line.c get_next_line_utils.c main.c
OBJS       = $(SRCS:.c=.o)

# Default rule: build the executable
all: $(NAME)

# Compile the executable

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Compile .o files
%.o: %.c get_next_line.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	rm -f $(OBJS)

# Clean object files and the executable
fclean: clean
	rm -f $(NAME)

# Rebuild everything from scratch
re: fclean all

# Run the program with an input file (adjust filename as needed)
run: $(NAME)
	./$(NAME)

# Phony targets to prevent conflicts with actual files
.PHONY: all clean fclean re run
