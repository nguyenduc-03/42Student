NAME = game
SRC = test6.c
# Add your additional source files here, e.g.:
# $(addprefix src/, main.c utils.c draw.c map_parser.c path_checker.c game_utils.c map_parser_utils.c free.c)
# $(addprefix gnl/, gnl.c gnl_utils.c)
# $(addprefix ft_printf/, ft_print_c.c ft_print_d.c ft_print_p.c ft_print_s.c ft_print_u.c ft_print_x.c ft_printf.c)

OBJ := $(SRC:%.c=%.o)

CC = gcc
CCFLAGS = -Wextra -Wall -Werror -Imlx/minilibx -Iincludes

all: $(NAME)

$(NAME): $(OBJ)
	make -C mlx/minilibx
# Build MiniLibX
	$(CC) $(CCFLAGS) $^ -Lmlx/minilibx -lmlx -lXext -lX11 -lm -o $(NAME)

%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make clean -C mlx/minilibx

fclean: clean
	rm -f $(NAME)
	make fclean -C mlx/

re: fclean all
