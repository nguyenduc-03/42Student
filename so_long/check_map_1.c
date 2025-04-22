#include "check_map.h"
#include <unistd.h>
#include <stdlib.h>

/*
** Check that the map is fully enclosed by walls ('1')
*/
static void	check_borders(char **map, int rows, int cols)
{
	int	j;

	j = 0;
	while (j < cols)
	{
		if (map[0][j] != '1' || map[rows - 1][j] != '1')
		{
			write(2, "Error\nMap not surrounded by walls\n", 33);
			exit(1);
		}
		j++;
	}
	j = 1;
	while (j < rows - 1)
	{
		if (map[j][0] != '1' || map[j][cols - 1] != '1')
		{
			write(2, "Error\nMap not surrounded by walls\n", 33);
			exit(1);
		}
		j++;
	}
}

/*
** Validate each map cell and update metadata
*/
static void	check_cell(char c, int i, int j, t_map_meta *meta)
{
	if (c != '0' && c != '1' && c != 'C' && c != 'E' && c != 'P')
	{
		write(2, "Error\nInvalid character in map\n", 30);
		exit(1);
	}
	if (c == 'P')
	{
		meta->p_count++;
		meta->p_row = i;
		meta->p_col = j;
	}
	else if (c == 'E')
		meta->e_count++;
	else if (c == 'C')
		meta->c_count++;
}

/*
** Verify collected counts after scanning
*/
static void	verify_counts(t_map_meta *meta)
{
	if (meta->p_count != 1)
	{
		write(2, "Error\nInvalid number of starting positions\n", 42);
		exit(1);
	}
	if (meta->e_count != 1)
	{
		write(2, "Error\nInvalid number of exits\n", 30);
		exit(1);
	}
	if (meta->c_count < 1)
	{
		write(2, "Error\nNo heart in map\n", 23);
		exit(1);
	}
}

/*
** validate_structure:
** - rows and cols are passed by pointer
** - aggregates map info into a single struct to limit parameters
*/
void	validate_structure(char **map, int *rows, int *cols, t_map_meta *meta)
{
	int	i;
	int	j;

	check_borders(map, *rows, *cols);
	meta->p_count = 0;
	meta->e_count = 0;
	meta->c_count = 0;
	i = 0;
	while (i < *rows)
	{
		j = 0;
		while (j < *cols)
		{
			check_cell(map[i][j], i, j, meta);
			j++;
		}
		i++;
	}
	verify_counts(meta);
}
