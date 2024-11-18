/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ducnguye <ducnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:20:53 by ducnguye          #+#    #+#             */
/*   Updated: 2024/11/13 11:23:28 by ducnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	i = 0;
	if (*little == '\0')
		return ((char *)big);
	while (*big != '\0' && len > 0)
	{
		while (big[i] == little[i] && (big[i] != '\0' && i < len))
		{
			i++;
			if (little[i] == '\0')
				return ((char *)big);
		}
		big++;
		len--;
	}
	return (NULL); 
}
