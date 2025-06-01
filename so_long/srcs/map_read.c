/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ducnguye <ducnguye@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:51:49 by ducnguye          #+#    #+#             */
/*   Updated: 2025/05/19 17:51:49 by ducnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_map.h"

static void	allocate_map(t_map *map)
{
	map->grid = malloc(sizeof(char *) * map->height);
	if (!map->grid)
	{
		free_map(map);
		print_error("Memory allocation failed for map");
	}
}

static void	read_line(int fd, t_map *map, int i)
{
	int		j;
	int		ret;
	char	c;

	map->grid[i] = malloc(map->width + 1);
	if (!map->grid[i])
		print_error("Memory allocation failed for grid row");
	j = 0;
	while (j < map->width)
	{
		ret = read(fd, &c, 1);
		if (ret <= 0)
			print_error("readline1");
		map->grid[i][j] = c;
		j++;
	}
	map->grid[i][j] = '\0';
	ret = read(fd, &c, 1);
	if (ret > 0 && c != '\n')
		print_error("readline2");
}

static void	fill_map(const char *path, t_map *map)
{
	int	fd;
	int	i;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		print_error("Failed to open file in fill_map");
	i = 0;
	while (i < map->height)
	{
		read_line(fd, map, i);
		i++;
	}
	close(fd);
}

void	read_map_file(const char *path, t_map *map)
{
	map->height = get_height(path);
	map->width = get_width(path);
	allocate_map(map);
	fill_map(path, map);
}
