NAME   = so_long
SRC    = srcs/main.c \
		srcs/game_1.c \
		srcs/game_2.c \
		srcs/check_map.c \
		srcs/map_utils.c \
		srcs/map_read.c \
		srcs/map_validate.c \
		srcs/char_validate.c \
		srcs/path_validate.c

OBJ    = $(SRC:.c=.o)


OBJ    = $(SRC:.c=.o)

CC     = cc
CFLAGS = -Wall -Wextra -Werror -Imlx -Iincludes

all: $(NAME)

$(NAME): $(OBJ)
	@make -C mlx
	$(CC) $(CFLAGS) $^ -Lmlx -lmlx -lXext -lX11 -lm -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@make clean -C mlx

fclean: clean
	@rm -f $(NAME)
	@make clean -C mlx

re: fclean all

.PHONY: all clean fclean re
