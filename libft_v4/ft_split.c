/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ducnguye <ducnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:21:34 by ducnguye          #+#    #+#             */
/*   Updated: 2024/11/18 12:22:22 by ducnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*get_word(char const *s, int start, int end)
{
	char	*word;
	int		i;

	word = (char *)malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

static char	**free_array(char **array, int count)
{
	while (--count >= 0)
		free(array[count]);
	free(array);
	return (NULL);
}

static char	**split_words(char const *s, char c, char **array)
{
	int		start;
	int		end;
	int		i;

	start = -1;
	i = 0;
	end = 0;
	while (s[end])
	{
		if (s[end] != c && start == -1)
			start = end;
		if ((s[end] == c || s[end + 1] == '\0') && start != -1)
		{
			if (s[end] == c)
				array[i] = get_word(s, start, end);
			else
				array[i] = get_word(s, start, end + 1);
			if (!array[i++])
				return (free_array(array, i - 1));
			start = -1;
		}
		end++;
	}
	array[i] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;

	if (!s)
		return (NULL);
	array = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	return (split_words(s, c, array));
}

/* #include <stdio.h>

int	main(void)
{
	char const	*s = "  1111 22222 3 3 31 ";
	char		c = ' ';
	char		**result;
	int			i;

	result = ft_split(s, c);
	if (!result)
		return (1);
	i = 0;
	while (result[i])
	{
		printf("Word %d: %s\n", i + 1, result[i]);
		free(result[i]);
		i++;
	}
	free(result);
	return (0);
} */