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
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	int		hearts;

	if (argc != 2)
		write(2, "Usage: ./so_long <map_file>\n", 27);
	map = read_map(argv[1], &width, &height);
	if (!map)
		write(2, "Error: Failed to read map\n", 25);
	validate_map(map, width, height);
	player_x = -1;
	player_y = -1;
	scan_map_vars(map, width, height, &player_x, &player_y, &hearts);
	start_game(map, width, height, player_x, player_y, hearts);
	return (0);
}

