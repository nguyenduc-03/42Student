# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ducnguye <ducnguyen@student.42berlin.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/17 22:31:25 by ducnguye          #+#    #+#              #
#    Updated: 2025/05/17 22:31:26 by ducnguye         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        := push_swap
CHECKER     := checker

CC          := gcc
CFLAGS      := -Wall -Wextra -Werror
RM          := rm -f

LIBFT_DIR   := libft
LIBFT_LIB   := -L $(LIBFT_DIR) -lft

UTILS_SRCS := \
	algorithm.c \
	ft_add_back.c \
	ft_stack_new.c \
	ft_check_utils.c \
	ft_parse.c \
	solver_utils_ab.c \
	solver_utils_ba.c \
	ft_rotate_and_push.c \
	operations.c \
	operations_2.c \
	operations_3.c \
	ft_check_dup.c \
	ft_check_sorted.c \
	ft_error_print.c \
	ft_free.c \
	lst_utils.c \
	lst_utils_2.c \
	ft_parse_args_quoted.c \
	ft_list_args.c \
	ft_check_args.c \
	ft_sort_big.c \
	ft_sort_three.c \
	ft_rotate_type.c

SRC_PUSH    := push_swap.c $(UTILS_SRCS)
SRC_CHECKER := checker.c checker_utils.c $(UTILS_SRCS)

OBJ_PUSH    := $(SRC_PUSH:.c=.o)
OBJ_CHECKER := $(SRC_CHECKER:.c=.o)

INCLUDES    :=

.PHONY: all bonus clean fclean re

all: $(NAME) $(CHECKER)

$(LIBFT_DIR)/libft.a:
	@$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(LIBFT_DIR)/libft.a $(OBJ_PUSH)
	$(CC) $(CFLAGS) $(OBJ_PUSH) -o $@ $(LIBFT_LIB)

$(CHECKER): $(LIBFT_DIR)/libft.a $(OBJ_CHECKER)
	$(CC) $(CFLAGS) $(OBJ_CHECKER) -o $@ $(LIBFT_LIB)

bonus: $(CHECKER)

clean:
	$(RM) $(OBJ_PUSH) $(OBJ_CHECKER)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME) $(CHECKER)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
