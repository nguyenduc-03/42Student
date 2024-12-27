/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ducnguye <ducnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:16:50 by ducnguye          #+#    #+#             */
/*   Updated: 2024/11/27 19:18:54 by ducnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

<<<<<<< HEAD
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

*/
int	ft_putstr(const char *s)
=======
/* int	ft_atoi_base(char *str, char *base);
void	ft_string( char *str, ...) // print the string of char
{

}
void	ft_number( char *str, ...); */

int	ft_printf(const char *str, ...)
>>>>>>> refs/remotes/origin/main
{
	va_list	agruments;
	va_start(agruments, str);
	char	option;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			option = str[i + 1];
			if (option == 's')
			{
				ft_putstr_fd (va_arg(agruments, char *), 1);
				i = i + 2;
			}
		}
		else
		{
			write (1, &str[i], 1);
			i++;
		}
	}
	va_end(agruments);
	return (i);
}

<<<<<<< HEAD
int ft_printf(const char *str, ...)
{
    va_list agruments;
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
    ft_printf("Hi my lady","Hi I undetstand now\n");
    printf("asd%dsda");
    return 0;
}
=======
int main()
{
	ft_printf("try: %s%s\n", "hello");
	return 0;
}
>>>>>>> refs/remotes/origin/main
