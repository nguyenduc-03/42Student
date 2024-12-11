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

/* int	ft_atoi_base(char *str, char *base);
void	ft_string( char *str, ...) // print the string of char
{

}
void	ft_number( char *str, ...); */

int	ft_printf(const char *str, ...)
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

int main()
{
	ft_printf("try: %s%s\n", "hello");
	return 0;
}