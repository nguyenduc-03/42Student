#include "check_map.h"
#include <stdlib.h>
#include <unistd.h>

static void	check_char(t_map *map, int i, int j)
{
	char	c;

	c = map->grid[i][j];
	if (c == 'P')
	{
		if (map->player_x != -1)
			print_error("No player!");
		map->player_x = j;
		map->player_y = i;
	}
	else if (c == 'E')
		map->count_e++;
	else if (c == 'C')
		map->count_c++;
	else if (c != '0' && c != '1')
		{
			write(1,"check_char\n",11);
			exit(EXIT_FAILURE);}
}

static void	scan_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (map->grid[i][j])
		{
			check_char(map, i, j);
			j++;
		}
		i++;
	}
}

void	validate_chars(t_map *map)
{
	map->player_x = -1;
	map->count_c = 0;
	map->count_e = 0;
	scan_map(map);
	printf("player_x %d count_e %d count_c %d\n", map->player_x, map->count_e, map->count_c);
	if (map->player_x < 0 || map->count_e != 1 || map->count_c < 1)
		{
			write(1,"validate_char\n",14);
			exit(EXIT_FAILURE);}
}
