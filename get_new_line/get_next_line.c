/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaiduc <thaiduc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:42:01 by thaiduc           #+#    #+#             */
/*   Updated: 2024/12/05 20:16:13 by thaiduc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(char **buffer)
{
	size_t	i;
	char	*line;
	char	*temp;

	i = 0;
	while ((*buffer)[i] && (*buffer)[i] != '\n')
		i++;
	if ((*buffer)[i] == '\n')
		line = gnl_strdup(*buffer, i + 1);
	else
		line = gnl_strdup(*buffer, i);
	if ((*buffer)[i] == '\n')
		temp = gnl_strdup((*buffer) + i + 1, gnl_strlen(*buffer) - i);
	else
		temp = gnl_strdup((*buffer) + i, gnl_strlen(*buffer) - i);
	free(*buffer);
	*buffer = temp;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	char		temp[BUFFER_SIZE + 1];
	ssize_t		bytes_read;

	buffer = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (!gnl_has_newline(buffer))
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		temp[bytes_read] = '\0';
		buffer = gnl_strjoin(buffer, temp);
	}
	if (bytes_read == -1 || (bytes_read == 0 && (!buffer || !buffer[0])))
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	line = extract_line(&buffer);
	return (line);
}
