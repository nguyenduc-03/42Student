#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/*Outputs the string ’s’ to the given file descriptor
followed by a newline.

*/
void ft_putendl_fd(char *s, int fd)
{
    if (!s)
        return;
    ft_putstr_fd(s, fd);  
    write(fd, "\n", 1);
}

