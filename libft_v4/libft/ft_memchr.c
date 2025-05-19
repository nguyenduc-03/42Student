/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   $TM_FILENAME                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ducnguye <ducnguyen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:00:00 by ducnguye          #+#    #+#             */
/*   Updated: 2025/05/17 12:01:32 by ducnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	ch;

	ch = (unsigned char)c;
	ptr = (unsigned char *)s;
	while (n--)
	{
		if (*ptr == ch)
			return ((void *)ptr);
		ptr++;
	}
	return (NULL);
}
