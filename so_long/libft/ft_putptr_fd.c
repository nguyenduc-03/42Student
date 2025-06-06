/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_fd.c                                     */
/*                                                    +:+ +:+         +:+     */
/*   By: ducnguye <ducnguye@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 12:00:00 by ducnguye          #+#    #+#             */
/*   Updated: 2025/06/02 12:00:00 by ducnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putptr_fd(void *ptr, int fd)
{
	unsigned long	address;
	int				count;
	char			buffer[16];
	int				i;

	if (!ptr)
		return ((ft_putstr_fd("(nil)", fd)));
	address = (unsigned long)ptr;
	count = ft_putstr_fd("0x", fd);
	if (address == 0)
		return (count + ft_putchar_fd('0', fd));
	i = 0;
	while (address != 0)
	{
		buffer[i++] = "0123456789abcdef"[address % 16];
		address /= 16;
	}
	while (--i >= 0)
		count += ft_putchar_fd(buffer[i], fd);
	return (count);
}
