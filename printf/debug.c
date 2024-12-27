#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

int	ft_putnbr(int n)
{
    int return_value = 0;
    char c;

    if (n == -2147483648)
    {
        write(1, "-2147483648", 12);
        return 11;
    }
    if (n == 0)
    {
        write(1, "0", 1);
        return 1;
    }
    if (n < 0)
    {
        write(1, "-", 1);
        n = -n;
        return_value++;
    }
    if (n >= 10)
        return_value += ft_putnbr(n / 10);
    c = (n % 10) + '0';
    write(1, &c, 1);
    return_value++;
    return return_value;
}

int	ft_putchar(char c)
{
    write(1, &c, 1);
    return 1;
}

int flag_check(const char s, const char *flags)
{
    while (*flags)
    {
        if (s == *flags)
            return 0; // in the flags
        flags++;
    }
    return 1;
}

int	ft_putstr(const char *s)
{
    int i = 0;
    if (!s)
    {	
        write(1, "(null)", 6);
        return 6;
    }
    while (s[i])
    {
        write(1, &s[i], 1);
        i++;
    }
    return (i);
}

int ft_printf(const char *str, ...)
{
    va_list arguments;
    va_start(arguments, str);

    int return_value = 0;
    int i = 0;
    const char *flags = "cspdiuxX%";

    while (str[i])
    {
        if (str[i] == '%')
        {
            if (str[i + 1] == '\0') 
            {
                va_end(arguments);
                return -1; 
            }

            if (!flag_check(str[i + 1], flags))
            {
                if (str[i + 1] == 's')
                    return_value += ft_putstr(va_arg(arguments, const char*));
                else if (str[i + 1] == 'c')
                    return_value += ft_putchar(va_arg(arguments, int));
                else if (str[i + 1] == 'd' || str[i + 1] == 'i')
                    return_value += ft_putnbr(va_arg(arguments, int));
                i++;  // Skip the format specifier character.
            }
            else
            {
                // Handle invalid format specifiers or % followed by an unknown character
                write(1, &str[i], 1);
                return_value++;
            }
        }
        else
        {
            // Print regular characters
            write(1, &str[i], 1);
            return_value++;
        }
        i++;
    }

    // Check if there are no more arguments for format specifiers, print 0 if true
    if (i == 0 || return_value == 0)
    {
        write(1, "0", 1);
        return 1;
    }

    va_end(arguments);
    return return_value;
}

int main()
{
    // Example 1: With arguments, should work as expected
    printf("%d\n", ft_printf("Hi my lady : %i : %d\n ", 125));
    // Example 2: No arguments for the format specifier, should print 0
    printf("%d\n", ft_printf("Hi my lady : %m %q %ü: %d\n ",125));
    // Example 3: printf equivalent for comparison
    printf("%d\n", printf("Hi my lady : %m %q %ü : %d\n ", 125));
    
    return 0;
}
