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

CC     = gcc
CFLAGS = -Wall -Wextra -Werror -Imlx/minilibx -Iincludes

all: $(NAME)

$(NAME): $(OBJ)
	@make -C mlx/minilibx
	$(CC) $(CFLAGS) $^ -Lmlx/minilibx -lmlx -lXext -lX11 -lm -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@make clean -C mlx/minilibx

fclean: clean
	@rm -f $(NAME)
	@make clean -C mlx/minilibx

re: fclean all

.PHONY: all clean fclean re
