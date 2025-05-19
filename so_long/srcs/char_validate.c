/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_validate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ducnguye <ducnguye@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:07:52 by ducnguye          #+#    #+#             */
/*   Updated: 2025/05/19 17:07:52 by ducnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_map.h"

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
		print_error("check char");
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
	if (map->player_x < 0 || map->count_e != 1 || map->count_c < 1)
		print_error("validate_chars");
}
