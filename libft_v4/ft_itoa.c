/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ducnguye <ducnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:12:41 by ducnguye          #+#    #+#             */
/*   Updated: 2024/11/18 17:13:04 by ducnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	calculate_digits(long long n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0) 
		len++;
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*null_case( char *str)
{
	str[0] = '0';
	str[1] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	long long	num;
	int			len;
	int			i;
	char		*str;

	num = n;
	len = calculate_digits(num);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	if (num == 0)
		return (null_case(str));
	i = len - 1;
	if (num < 0)
	{
		str[0] = '-';
		num = -num;
	}
	while (num)
	{
		str[i--] = num % 10 + '0';
		num = num / 10;
	}
	str[len] = '\0';
	return (str);
}
