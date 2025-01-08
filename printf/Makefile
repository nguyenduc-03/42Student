# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Directories
SRCDIR = src
OBJDIR = obj
INCDIR = includes

# Sources and objects
SRC = ft_printf.c ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c ft_putnbr_base_fd.c ft_putptr_fd.c
OBJ = $(SRC:.c=.o)

# Path configuration
SRCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJS = $(addprefix $(OBJDIR)/, $(OBJ))

# Library name
NAME = libftprintf.a

# Default rule
all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

# Clean up object files
clean:
	rm -rf $(OBJDIR)

# Full clean (object files and library)
fclean: clean
	rm -f $(NAME)

# Recompile everything
re: fclean all

# Phony target declarations
.PHONY: all clean fclean re