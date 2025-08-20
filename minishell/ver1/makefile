# Makefile

NAME = shell
CC   = cc
CFLAGS = -Wall -Wextra -Werror -I/usr/local/opt/readline/include
LDFLAGS = -L/usr/local/opt/readline/lib
LDLIBS  = -lreadline -lncurses
HEADER = cell.h

SRC = main.c ft_split.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS) $(LDLIBS)

%.o: %.c $(HEADER)
	cc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: clean fclean re
