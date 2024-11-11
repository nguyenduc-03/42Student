#include <unistd.h>

size_t ft_strlen(const char *str){
    int i = 0;
    while(*str){
        str++;
        i++;
    }
    return i;
}