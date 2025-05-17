#include "check_map.h"
#include <stdlib.h>

char	**read_map(char *filename, int *width, int *height)
{
	t_map	m;

	read_map_file(filename, &m);
	*width = m.width;
	*height = m.height;
	return (m.grid);
}

void	validate_map(char **grid, int width, int height)
{
	t_map	m;

	m.grid = grid;
	m.width = width;
	m.height = height;
	validate_rectangular(&m);
	validate_borders(&m);
	validate_chars(&m);
	validate_paths(&m);
}
