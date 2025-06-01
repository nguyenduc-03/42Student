NAME = so_long

SRCS = so_long.c so_long_error_utils.c so_long_coord_utils.c so_long_map_check.c \
	   so_long_utils.c so_long_clean_utils.c so_long_game_utils.c

OBJS = ${SRCS:.c=.o}

CC = cc

CFLAGS = -Wall -Werror -Wextra

RM = rm -rf

LIBFT_INCLUDE = -I libft/

LIBFT_LIB = -L libft/. -lft

MINI_LIBX_INCLUDE = -I /usr/include -Imlx

MINI_LIBX_LIB = -L minilibx-linux/. -lmlx

X_11_FLAGS =  -L /usr/lib/X11 -lXext -lX11

all: ${NAME}

.c.o:
	${CC} ${CFLAGS} ${LIBFT_INCLUDE} ${MINI_LIBX_INCLUDE} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	make -C minilibx-linux
	make -C libft bonus
	${CC} ${CFLAGS} ${OBJS} ${LIBFT_LIB} ${MINI_LIBX_LIB} ${X_11_FLAGS} -o ${NAME}

clean:
	make -C minilibx-linux clean
	make -C libft clean
	${RM} ${OBJS}

fclean: clean
	make -C libft fclean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re