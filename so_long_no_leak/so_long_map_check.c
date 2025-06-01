/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_map_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:29:17 by edfreder          #+#    #+#             */
/*   Updated: 2025/05/31 22:31:01 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	mark_plays(char **grid_map, int x, int y, char mark)
{
	if (grid_map[y][x] == '1' || grid_map[y][x] == mark
			|| grid_map[y][x] == 'E')
		return ;
	else if (grid_map[y][x] != 'P')
		grid_map[y][x] = mark;
	mark_plays(grid_map, x, y + 1, mark);
	mark_plays(grid_map, x, y - 1, mark);
	mark_plays(grid_map, x - 1, y, mark);
	mark_plays(grid_map, x + 1, y, mark);
}

int	check_plays(char **grid_map, t_map *map)
{
	int	e_x;
	int	e_y;

	mark_plays(grid_map, map->start_coord.x, map->start_coord.y, 'X');
	if (!coord_check(map->colls_coord, grid_map, 'X'))
		return (send_err(MAP_COLLECT_ERR, 0));
	e_x = map->exit_coord.x;
	e_y = map->exit_coord.y;
	if (grid_map[e_y][e_x + 1] != 'X' && grid_map[e_y][e_x - 1] != 'X' &&
	grid_map[e_y + 1][e_x] != 'X' && grid_map[e_y - 1][e_x] != 'X')
		return (send_err(MAP_EXIT_ERR, 0));
	return (1);
}

int	check_rectangule(int *line_len, int *curr_len)
{
	if (!(*line_len))
		*line_len = *curr_len;
	else
	{
		if (*line_len != *curr_len)
			return (0);
	}
	return (1);
}

int	check_walls(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1')
			return (send_err(MAP_WALL_ERR, 0));
		i++;
	}
	return (1);
}

int	check_map(char **grid, t_map *map)
{
	int		i;

	map->colls = 0;
	map->exit = 0;
	map->start = 0;
	map->colls_coord = NULL;
	i = 0;
	while (grid[i])
	{
		if (!i || !grid[i + 1])
		{
			if (!check_walls(grid[i]))
				return (0);
		}
		else
		{
			if (!save_map_info(grid[i], i, map))
				return (0);
		}
		i++;
	}
	if (map->colls <= 0 || map->exit != 1 || map->start != 1)
		return (send_err(MAP_CHR_ERR, 0));
	return (1);
}
