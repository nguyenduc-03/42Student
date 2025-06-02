/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_entire_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte <jdecorte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:45:42 by jdecorte          #+#    #+#             */
/*   Updated: 2025/06/02 15:45:42 by jdecorte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 50
#endif

static char	*append_content(char *content, char *buf, int rd)
{
	char	*tmp;

	buf[rd] = '\0';
	tmp = ft_strjoin(content, buf);
	free(content);
	return (tmp);
}

static char	*read_loop(int fd, char *content, char *buf)
{
	int	rd;

	rd = read(fd, buf, BUFFER_SIZE);
	while (rd > 0)
	{
		content = append_content(content, buf, rd);
		if (!content)
			break ;
		rd = read(fd, buf, BUFFER_SIZE);
	}
	if (rd == -1 || !content)
		free(content);
	return (content);
}

char	*read_entire_file(int fd)
{
	char	*content;
	char	*buf;

	content = ft_strdup("");
	buf = malloc(BUFFER_SIZE + 1);
	if (!content || !buf)
	{
		free(content);
		free(buf);
		return (NULL);
	}
	content = read_loop(fd, content, buf);
	free(buf);
	return (content);
}
