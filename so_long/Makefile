NAME = game
SRC = main.c game_1.c game_2.c check_map.c#_1.c check_map_3.c check_map_4.c
OBJ := $(SRC:%.c=%.o)

CC = gcc
CCFLAGS = -Wextra -Wall -Werror -Imlx/minilibx -Iincludes

all: $(NAME)

$(NAME): $(OBJ)
	make -C mlx/minilibx
	$(CC) $(CCFLAGS) $^ -Lmlx/minilibx -lmlx -lXext -lX11 -lm -o $(NAME)

%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make clean -C mlx/minilibx

fclean: clean
	rm -f $(NAME)
	make clean -C mlx/minilibx

re: fclean all

.PHONY: all clean fclean re