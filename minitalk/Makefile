NAME 	= minitalk
SERVER	= server
CLIENT	= client

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT		= ./libft/libft.a
LIBFTDIR 	= ./libft

RM = rm -f

SRC_SERVER = server.c
SRC_CLIENT = client.c

OBJ_SERVER = $(SRC_SERVER:.c=.o)
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)

all: $(LIBFT) $(SERVER) $(CLIENT)

$(LIBFT):
	@make -C $(LIBFTDIR)
	@echo "✅ Libft compiled successfully."

$(SERVER): $(LIBFT) $(OBJ_SERVER)
	$(CC) $(CFLAGS) $(OBJ_SERVER) -o $(SERVER) -L$(LIBFTDIR) -lft
	@echo "🚀 Server compiled successfully."

$(CLIENT): $(LIBFT) $(OBJ_CLIENT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) -o $(CLIENT) -L$(LIBFTDIR) -lft
	@echo "🚀 Client compiled successfully."

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_SERVER) $(OBJ_CLIENT)
	@make -C $(LIBFTDIR) clean
	@echo "🧹 Cleaned object files."

fclean: clean
	$(RM) $(SERVER) $(CLIENT)
	@make -C $(LIBFTDIR) fclean
	@echo "🗑️  Full clean done."

re: fclean all

.PHONY: all clean fclean re
