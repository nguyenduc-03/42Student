#include <libft.h>
//copy char from s, start at index start, max size = len
char *ft_substr(char const *s, unsigned int start, size_t len)
{
    char*  substr = (char *)malloc(len + 1);
    int  i;
    
    i = 0;
    while(len != 0)
    {
        substr[i] =s[start];
        len--;
        i++;
        start++;
    }
    return substr;
}
