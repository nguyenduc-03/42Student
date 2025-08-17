# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ducnguye <ducnguye@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/17 13:52:39 by ducnguye          #+#    #+#              #
#    Updated: 2025/08/17 14:33:49 by ducnguye         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = main.c utils.c init.c threads.c monitor.c routine_actions.c
OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror -O3 -pthread
HEADER = philo.h
#SANITIZER = -fsanitize=thread

.PHONY: all clean fclean re debug

all: $(NAME)

$(NAME): $(OBJ)
	cc $(FLAGS) -o $(NAME) $(OBJ) $(SANITIZER)

%.o: %.c $(HEADER)
	cc $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
