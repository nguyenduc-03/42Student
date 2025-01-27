NAME = push_swap

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = src/ft_atoi.c src/ft_is_integer.c src/main.c

OBJS = $(SRCS:.c=.o)

INCLUDE = -I inc/

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
