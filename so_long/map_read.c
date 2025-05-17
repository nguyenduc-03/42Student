#include "check_map.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

static void	allocate_map(t_map *map)
{
	map->grid = malloc(sizeof(char *) * map->height);
	if (!map->grid)
		exit(EXIT_FAILURE);
}

static void	read_line(int fd, t_map *map, int i)
{
	int		j;
	int		ret;
	char	c;

	map->grid[i] = malloc(map->width + 1);
	if (!map->grid[i])
		exit(EXIT_FAILURE);
	j = 0;
	while (j < map->width)
	{
		ret = read(fd, &c, 1);
		if (ret <= 0)
			exit(EXIT_FAILURE);
		map->grid[i][j] = c;
		j++;
	}
	map->grid[i][j] = '\0';
	ret = read(fd, &c, 1);
	if (ret > 0 && c != '\n')
		exit(EXIT_FAILURE);
}

static void	fill_map(const char *path, t_map *map)
{
	int	fd;
	int	i;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE);
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
