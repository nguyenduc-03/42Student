/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_atoibase.c									  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ducnguye <ducnguye@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/11/27 15:16:48 by ducnguye		  #+#	#+#			 */
/*   Updated: 2024/11/27 15:22:14 by ducnguye		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

int	is_in_base(char *str, char *base)
{
	int	i;

	i = 0;
	while (base[i] && base[i] != *str)
		i++;
	if (base[i] == '\0')
		return (-1);
	return (i);
}

int	ft_is_valid_base(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		if (str[i] == '-' || str[i] == '+'
			|| (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r')))
			return (0);
		j = i + 1;
		while (str[i] && str[j])
		{
			if (str[i] == str[j])
				return (0);
			j++;
		}
		i++;
	}
	return (i);
}

int	ft_atoi_base(char *str, char *base)
{
	int	nb;
	int	sign;
	int	radix;

	nb = 0;
	sign = 1;
	radix = ft_is_valid_base(base);
	if (radix > 1)
	{
		while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
			str++;
		while (*str == '-' || *str == '+')
		{
			if (*str == '-')
				sign *= -1;
			str++;
		}
		while (is_in_base(str, base) >= 0)
		{
			nb = nb * radix + is_in_base(str, base);
			str++;
		}
	}
	return (nb *= sign);
}

/* 
int main()
{

	char *base = "0123456789abcdef";
	char *str = "ff";
	printf("%d\n", ft_atoi_base(str,base));
	return 0;
} */