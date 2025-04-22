# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ducnguye <ducnguye@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/11 15:13:33 by ducnguye          #+#    #+#              #
#    Updated: 2025/01/11 15:13:34 by ducnguye         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
SRCDIR = src
OBJDIR = obj

SRCS = $(SRCDIR)/ft_printf.c $(SRCDIR)/ft_putchar_fd.c $(SRCDIR)/ft_putstr_fd.c \
		$(SRCDIR)/ft_putnbr_fd.c $(SRCDIR)/ft_putnbr_base_fd.c $(SRCDIR)/ft_putptr_fd.c
OBJS = $(OBJDIR)/ft_printf.o $(OBJDIR)/ft_putchar_fd.o $(OBJDIR)/ft_putstr_fd.o \
		$(OBJDIR)/ft_putnbr_fd.o $(OBJDIR)/ft_putnbr_base_fd.o $(OBJDIR)/ft_putptr_fd.o


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