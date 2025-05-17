#include "check_map.h"
#include "game.h"
#include <unistd.h>

static void	scan_map_vars(char **map, int *i)
{
	int	x;
	int	y;

	i[4] = 0;
	y = -1;
	while (++y < i[1])
	{
		x = -1;
		while (++x < i[0])
		{
			if (map[y][x] == 'P')
			{
				i[2] = x;
				i[3] = y;
				map[y][x] = '0';
			}
			else if (map[y][x] == 'C')
				i[4]++;
		}
	}
	if (i[2] < 0 || i[3] < 0)
		write(2, "Error: No player start position\n", 33);
}

int	main(int argc, char **argv)
{
	char	**map;
	int		i[5];

	if (argc != 2)
	{
		write(2, "Usage: ./so_long <map_file>\n", 27);
		return (1);
	}
	map = read_map(argv[1], &i[0], &i[1]);
	if (!map)
	{
		write(2, "Error: Failed to read map\n", 25);
		return (1);
	}
	validate_map(map, i[0], i[1]);
	i[2] = -1;
	i[3] = -1;
	scan_map_vars(map, i);
	start_game(map, i);
	return (0);
}
