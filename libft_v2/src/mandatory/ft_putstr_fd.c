#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/*Outputs the string ’s’ to the given file
descriptor.
*/
void ft_putstr_fd(char *s, int fd)
{
    if (!s)
        return; 
    while(*s)
    {
        write(fd, s, 1);
        s++;
    }
}
