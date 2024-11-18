/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ducnguye <ducnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:44:34 by ducnguye          #+#    #+#             */
/*   Updated: 2024/11/13 13:59:15 by ducnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t num)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (d == s || num == 0)
		return (dest);
	if (d < s)
	{
		while (num--)
			*d++ = *s++;
	}
	else
	{
		d += num;
		s += num;
		while (num--)
			*(--d) = *(--s);
	}
	return (dest);
}
