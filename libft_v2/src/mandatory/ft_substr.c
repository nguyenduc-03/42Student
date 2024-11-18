/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ducnguye <ducnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:10:59 by ducnguye          #+#    #+#             */
/*   Updated: 2024/11/18 11:12:54 by ducnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*substr;

	substr = (char *)malloc(len + 1);
	i = 0;
	while (len != 0)
	{
		substr[i] = s[start];
		len--;
		i++;
		start++;
	}
	return (substr);
}
