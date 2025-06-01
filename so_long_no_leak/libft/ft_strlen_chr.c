/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_chr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ducnguye <ducnguye@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 04:36:18 by ducnguye          #+#    #+#             */
/*   Updated: 2025/06/01 04:36:18 by ducnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_chr(const char *s, char c)
{
	int	len;

	len = 0;
	if (!c)
	{
		while (s[len])
			len++;
	}
	else
	{
		while (s[len] && s[len] != c)
			len++;
	}
	return (len);
}
