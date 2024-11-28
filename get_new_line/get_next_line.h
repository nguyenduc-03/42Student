#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024 // Default buffer size if not defined
# endif

# include <stdlib.h>
# include <unistd.h>

// Function prototype
char *get_next_line(int fd);

#endif
