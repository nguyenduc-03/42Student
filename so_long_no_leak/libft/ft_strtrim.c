/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ducnguye <ducnguye@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:00:00 by ducnguye          #+#    #+#             */
/*   Updated: 2025/05/27 15:30:58 by ducnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

size_t	caculate_len(char const *s1, char const *set, size_t end, size_t start)
{
	size_t	len;

	len = 0;
	while (s1[end])
		end++;
	end--;
	while (end > start && is_in_set(s1[end], set))
		end--;
	if (end >= start)
		len = end - start + 1;
	else
		len = 0;
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	len;
	char	*trimmed;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = 0;
	while (s1[start] && is_in_set(s1[start], set))
		start++;
	len = caculate_len(s1, set, end, start);
	trimmed = (char *)malloc(len + 1);
	if (!trimmed)
		return (NULL);
	end = 0;
	while (end < len)
	{
		trimmed[end] = s1[start + end];
		end++;
	}
	trimmed[len] = '\0';
	return (trimmed);
}

/* #include <stdio.h>
int main()
{
	char *s1 = "adbcdfda";
	char *set = "ad";
	printf("Strim: %s\n", ft_strtrim(s1,set));
	return 0;

} */