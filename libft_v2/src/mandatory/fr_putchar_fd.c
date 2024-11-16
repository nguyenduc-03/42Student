#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/*Outputs the character ’c’ to the given file
descriptor
*/
void ft_putchar_fd(char c, int fd)
{
    write(fd,&c,1);
}
