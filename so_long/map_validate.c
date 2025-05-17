#include "check_map.h"
#include <stdlib.h>

void	validate_rectangular(t_map *map)
{
	int	len;
	int	i;

	i = 1;
	while (i < map->height)
	{
		len = 0;
		while (map->grid[i][len])
			len++;
		if (len != map->width)
			exit(EXIT_FAILURE);
		i++;
	}
}

void	validate_borders(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->width)
	{
		if (map->grid[0][i] != '1' || map->grid[map->height - 1][i] != '1')
			exit(EXIT_FAILURE);
		i++;
	}
	i = 0;
	while (i < map->height)
	{
		if (map->grid[i][0] != '1' || map->grid[i][map->width - 1] != '1')
			exit(EXIT_FAILURE);
		i++;
	}
}
