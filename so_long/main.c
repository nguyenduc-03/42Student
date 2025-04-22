#include "check_map.h"
#include "game.h"
#include <unistd.h>

static void	scan_map_vars(char **map, int width, int height,
				int *px, int *py, int *hearts)
{
	int	x;
	int	y;

	*hearts = 0;
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (map[y][x] == 'P')
			{
				*px = x;
				*py = y;
				map[y][x] = '0';
			}
			else if (map[y][x] == 'C')
				(*hearts)++;
			x++;
		}
		y++;
	}
	if (*px < 0 || *py < 0)
		write(2, "Error: No player start position\n", 33);
}

int	main(int argc, char **argv)
{
	char	**map;
	int		i[5];

	if (argc != 2)
		write(2, "Usage: ./so_long <map_file>\n", 27);
	map = read_map(argv[1], &i[0], &i[1]);
	if (!map)
		write(2, "Error: Failed to read map\n", 25);
	validate_map(map, i[0], i[1]);
	i[2] = -1;
	i[3] = -1;
	scan_map_vars(map, i[0], i[1], &i[2], &i[3], &i[4]);
	start_game(map,i);
	return (0);
}
