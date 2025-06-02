/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ducnguye <ducnguye@student.42berlin.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 22:47:21 by ducnguye    +#+    #+#             */
/*   Updated: 2025/05/17 22:47:21 by ducnguye    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	char			*tmp;
	unsigned char	tmpc;

	i = 0;
	tmp = (char *)b;
	tmpc = (unsigned char)c;
	while (i < len)
	{
		tmp[i] = tmpc;
		i++;
	}
	return (b);
}
