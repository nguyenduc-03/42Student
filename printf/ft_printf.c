#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

/*
• %c Prints a single character.
• %s Prints a string (as defined by the common C convention).
• %p The void * pointer argument has to be printed in hexadecimal format.
• %d Prints a decimal (base 10) number.
• %i Prints an integer in base 10.
• %u Prints an unsigned decimal (base 10) number.
• %x Prints a number in hexadecimal (base 16) lowercase format.
• %X Prints a number in hexadecimal (base 16) uppercase format.
• %% Prints a percent sign.
*/


char *find_symbol(const char *str) //return the array of string whenever hit a %, move it to a new index
{
    int i = 0;
    int j = 0;
    while(*str)
    {
        if(*str == '%')
        { 
            //check for the next letter
            if(*(str + 1) == c ||*(str + 1) == s) 
            {
                           
            }
        }
        
        j++;
        str++;
    }
    return array;
}

int	ft_putstr(const char *s)
{
    int i = 0;
	if (!s)
		return -1;
	while (*s)
	{
		write(1, s, 1);
		s++;
        i++;
	}
    return (i);
}

int ft_p(const char *str, ...)
{
    va_list agruments;

    //a function to go though str and check for %d, and return back   "Hello %s baby %d\n", "David"
    //find_symbol(str);


    va_start(agruments, str);
    int return_value = 0;

    const char *s = va_arg(agruments, const char*);
    //Search though the string, to find %c,%d,%s...
    if(s)
        return_value = ft_putstr(s);
    va_end(agruments);
    return return_value;
    
}


int main()
{
    ft_p("Hi my lady","Hi I undetstand now\n");
    printf("asd%dsda");
    return 0;
}
