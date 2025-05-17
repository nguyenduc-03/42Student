NAME   = game
SRC    = main.c \
         game_1.c \
         game_2.c \
         check_map.c \
         map_utils.c \
         map_read.c \
         map_validate.c \
         char_validate.c \
         path_validate.c

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
