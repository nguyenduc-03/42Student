#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*Applies the function ’f’ on each character of
the string passed as argument, passing its index
as first argument. Each character is passed by
address to ’f’ to be modified if necessary.
*/
void ft_striteri(char *s, void (*f)(unsigned int, char*))
{
    unsigned int i;

    i = 0;
    if (!s || !f)
        return;
    while(s[i])
    {
        f(i,&s[i]);
        i++;
    }
}

#include <stdio.h>
#include <ctype.h>

void to_upper(unsigned int i, char *c) {
    (void)i; // Ignore the index if not needed
    if (*c >= 'a' && *c <= 'z')
        *c -= 32;
}

int main() {
    char str[] = "hello world!";

    printf("Before: %s\n", str);
    ft_striteri(str, to_upper);
    printf("After:  %s\n", str);

    return 0;
}
