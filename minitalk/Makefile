NAME = server client
CC = gcc
CFLAGS = -Wall -Wextra -Werror -D_POSIX_C_SOURCE=199309L
RM = rm -f

all: $(NAME)

server: server.c
	$(CC) $(CFLAGS) -o $@ $^

client: client.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) $(NAME)

re: clean all

.PHONY: all clean re
