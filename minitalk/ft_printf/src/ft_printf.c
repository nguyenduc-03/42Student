/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ducnguye <ducnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:48:55 by codespace         #+#    #+#             */
/*   Updated: 2025/01/11 15:06:12 by ducnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_format(va_list args, const char format)
{
	if (format == 'c')
		return (ft_putchar_fd(va_arg(args, int), 1));
	else if (format == 's')
		return (ft_putstr_fd(va_arg(args, char *), 1));
	else if (format == 'd' || format == 'i')
		return (ft_putnbr_fd(va_arg(args, int), 1));
	else if (format == 'u')
		return (ft_putnbr_base_fd(va_arg(args, unsigned int),
				"0123456789", 1));
	else if (format == 'x')
		return (ft_putnbr_base_fd(va_arg(args, unsigned int),
				"0123456789abcdef", 1));
	else if (format == 'X')
		return (ft_putnbr_base_fd(va_arg(args, unsigned int),
				"0123456789ABCDEF", 1));
	else if (format == 'p')
		return (ft_putptr_fd(va_arg(args, void *), 1));
	else if (format == '%')
		return (ft_putchar_fd('%', 1));
	else
		return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			count += print_format(args, *format);
		}
		else
			count += ft_putchar_fd(*format, 1);
		format++;
	}
	va_end(args);
	return (count);
}
