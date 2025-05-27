/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ducnguye <ducnguye@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:00:00 by ducnguye          #+#    #+#             */
/*   Updated: 2025/05/27 15:30:58 by ducnguye         ###   ########.fr       */
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
