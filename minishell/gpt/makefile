# Makefile

NAME = minishell
CC   = cc
CFLAGS = -Wall -Wextra -Werror -I/usr/local/opt/readline/include
LDFLAGS = -L/usr/local/opt/readline/lib
LDLIBS  = -lreadline -lncurses

SRC = minishell.c
OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: clean fclean re
