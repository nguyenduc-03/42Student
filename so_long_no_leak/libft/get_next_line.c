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
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*clean_all(char *buffer1, char *buffer2, char *buffer3)
{
	if (buffer1)
	{
		free(buffer1);
		buffer1 = NULL;
	}
	if (buffer2)
	{
		free(buffer2);
		buffer2 = NULL;
	}
	if (buffer3)
	{
		free(buffer3);
		buffer3 = NULL;
	}
	return (NULL);
}
char	*build_buffer(char *buffer, char *buffer_res, ssize_t bytes_read)
{
	char	*temp;

	buffer_res[bytes_read] = '\0';
	if (!buffer)
		return (ft_strdup(buffer_res));
	temp = ft_strjoin(buffer, buffer_res);
	free(buffer);
	buffer = temp;
	return (buffer);
}

int	has_new_line(char *buffer_res)
{
	if (!buffer_res)
		return (0);
	while (*buffer_res)
	{
		if (*buffer_res == '\n')
			return (1);
		buffer_res++;
	}
	return (0);
}

char	*read_buffer(int fd, char *buffer)
{
	char	*buffer_res;
	ssize_t	bytes_read;

	bytes_read = 1;
	buffer_res = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer_res)
		return (clean_all(buffer, buffer_res, NULL));
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer_res, BUFFER_SIZE);
		if (bytes_read < 0)
			return (clean_all(buffer, buffer_res, 0));
		if (!bytes_read)
			break ;
		buffer = build_buffer(buffer, buffer_res, bytes_read);
		if (!buffer)
			break ;
		if (has_new_line(buffer_res))
			break ;
	}
	free(buffer_res);
	return (buffer);
}



char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	char		*rem;
	int			nl_i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_buffer(fd, buffer);
	if (!buffer || !buffer[0])
		return (clean_all(buffer, NULL, NULL));
	nl_i = ft_strlen_chr(buffer, '\n');
	if (nl_i < (int)(ft_strlen_chr(buffer, 0) - 1))
	{
		rem = ft_strdup(&buffer[nl_i + 1]);
		line = ft_substr(buffer, 0, nl_i + 1);
		if (!rem || !line)
			return (free(buffer), buffer = NULL, clean_all(0, rem, line));
		free(buffer);
		buffer = rem;
		return (line);
	}
	line = ft_strdup(buffer);
	return (free(buffer), buffer = NULL, line);
}
