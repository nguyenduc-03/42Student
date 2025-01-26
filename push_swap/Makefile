# Variables
NAME    = push_swap
CC      = gcc
CFLAGS  = -Wall -Werror -Wextra
SRCDIR  = src
OBJDIR  = obj
INCDIR  = inc

# Source files
SRC     = src/error.c \
          src/ft_atoi.c \
          src/is_integer.c \
          src/push_swap.c

# Object files
OBJ     = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Default target
all: $(NAME)

# Rule to compile the program
$(NAME): $(OBJ)
	@echo "Linking $^ -> $@"
	$(CC) $(CFLAGS) -o $@ $^

# Rule to compile source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@echo "Compiling $< -> $@"
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

# Rule to clean object files
clean:
	rm -rf $(OBJDIR)

# Rule to fully clean the build (objects and executable)
fclean: clean
	rm -f $(NAME)

# Rule to recompile the project
re: fclean all

# Phony targets
.PHONY: all clean fclean re