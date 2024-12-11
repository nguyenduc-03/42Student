/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   get_next_line.c									:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: codespace <codespace@student.42.fr>		+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/12/09 12:02:26 by codespace		 #+#	#+#			 */
/*   Updated: 2024/12/09 12:10:38 by codespace		###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_line(char **saved)
{
	char	*newline;
	char	*line;
	char	*tmp;

	newline = ft_strchr(*saved, '\n');
	if (newline)
	{
		line = ft_substr(*saved, 0, newline - *saved + 1);
		tmp = ft_strdup(newline + 1);
		free(*saved);
		*saved = tmp;
		if (**saved == '\0')
		{
			free(*saved);
			*saved = NULL;
		}
	}
	else
	{
		line = ft_strdup(*saved);
		free(*saved);
		*saved = NULL;
	}
	return (line);
}

static	ssize_t	read_file(int fd, char **saved)
{
	char	*buffer;
	ssize_t	bytes_read;
	char	*temp;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read >= 0)
	{
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(*saved, buffer);
		*saved = temp;
	}
	free(buffer);
	return (bytes_read);
}

char	*get_next_line(int fd)
{
	static char	*saved[1024];
	ssize_t		bytes_read;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!saved[fd])
		saved[fd] = ft_strdup("");
	bytes_read = 1;
	while (!ft_strchr(saved[fd], '\n') && bytes_read > 0)
		bytes_read = read_file(fd, &saved[fd]);
	if (bytes_read < 0 || (!bytes_read && !*saved[fd]))
	{
		free(saved[fd]);
		saved[fd] = NULL;
		return (NULL);
	}
	line = get_line(&saved[fd]);
	return (line);
}
