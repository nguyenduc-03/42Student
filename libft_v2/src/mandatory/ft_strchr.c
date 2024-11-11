#include <string.h>
   char *ft_strchr(const char *str, int search_char)
{
    while (*str) {
        if (*str == search_char) {
            return (char *)str;
        }
        str++;
    }
    return NULL;  // return NULL if not found
}