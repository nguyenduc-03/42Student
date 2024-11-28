#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#define BUFFER_SIZE 99999

#include <stdlib.h>
#include <unistd.h>

char    *get_next_line(int fd);
size_t  gnl_strlen(const char *str);
char    *gnl_strdup(const char *src, size_t len);
char    *gnl_strjoin(char *s1, char *s2);
int     gnl_has_newline(const char *str);

#endif
