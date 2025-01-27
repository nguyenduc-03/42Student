NAME = push_swap

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = src/ft_atoi.c src/ft_is_integer.c src/main.c 2 
OBJS = $(SRCS:src/%.c=obj/%.o)

INCLUDE = -I inc/

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) -o $(NAME)

obj/%.o: src/%.c | obj
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

obj:
	mkdir -p obj

clean:
	rm -f obj/*.o

fclean: clean
	rm -f $(NAME)
	rmdir obj

re: fclean all

.PHONY: all clean fclean re
