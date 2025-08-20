#ifndef CELL_H
# define CELL_H

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>

# include <readline/readline.h>
# include <readline/history.h>

//colors
#define RST "\033[0m"
#define RED "\033[1;31m"
#define YEL "\033[1;33m"
#define GRN "\033[1;32m"
#define CYN "\033[1;36m"
#define MAG "\033[1;35m"




//functions

int is_whitespace_only(const char *s);

//utils

char	**ft_split(char const *s, char c);
#endif