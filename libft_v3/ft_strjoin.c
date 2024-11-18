/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ducnguye <ducnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:15:29 by ducnguye          #+#    #+#             */
/*   Updated: 2024/11/18 11:21:29 by ducnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_1;
	size_t	len_2;
	int		i;
	char	*strjoin;

	i = 0;
	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	strjoin = (char *)malloc(len_1 + len_2 + 1);
	if (!strjoin)
		return (NULL);
	while (len_1 != 0)
	{
		strjoin[i] = s1[i];
		i++;
		len_1--;
	}
	while (len_2-- != 0)
	{
		strjoin[i] = s2[len_1];
		i++;
		len_1++;
	}
	strjoin[i] = '\0';
	return (strjoin);
}
