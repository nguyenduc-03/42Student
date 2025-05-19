/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ducnguye <ducnguye@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:03:29 by ducnguye          #+#    #+#             */
/*   Updated: 2025/05/19 18:03:29 by ducnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_map.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int	get_height(const char *path)
{
	int		fd;
	int		height;
	char	c;
	int		ret;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		print_error("Failed to open file in get_height");
	height = 0;
	ret = read(fd, &c, 1);
	while (ret > 0)
	{
		if (c == '\n')
			height++;
		ret = read(fd, &c, 1);
	}
	if (ret < 0)
		print_error("Read error in get_height");
	close(fd);
	return (height + 1);
}

int	get_width(const char *path)
{
	int		fd;
	int		width;
	char	c;
	int		ret;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		print_error("Failed to open file in get_width");
	width = 0;
	ret = read(fd, &c, 1);
	while (ret > 0 && c != '\n')
	{
		width++;
		ret = read(fd, &c, 1);
	}
	if (ret < 0)
		print_error("Read error in get_width");
	close(fd);
	return (width);
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
}
