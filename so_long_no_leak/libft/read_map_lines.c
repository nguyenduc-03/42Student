/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_lines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte <jdecorte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:45:42 by jdecorte          #+#    #+#             */
/*   Updated: 2025/06/02 15:45:42 by jdecorte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*read_entire_file(int fd);

char	**get_map_lines(int fd)
{
	char	*content;
	char	**lines;

	content = read_entire_file(fd);
	if (!content)
		return (NULL);
	lines = ft_split(content, '\n');
	free(content);
	return (lines);
}
