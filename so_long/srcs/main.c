/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ducnguye <ducnguye@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:35:34 by ducnguye          #+#    #+#             */
/*   Updated: 2025/05/19 17:35:34 by ducnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_map.h"
#include "game.h"

void	print_error(const char *msg)
{
	write(2, "Error\n", 6);
	while (*msg)
		write(2, msg++, 1);
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

static void	scan_map_vars(char **map, int dims[2], int info[3])
{
	int	xy[2];

	info[0] = -1;
	info[1] = -1;
	info[2] = 0;
	xy[1] = 0;
	while (xy[1] < dims[1])
	{
		xy[0] = 0;
		while (xy[0] < dims[0])
		{
			if (map[xy[1]][xy[0]] == 'P')
			{
				info[0] = xy[0];
				info[1] = xy[1];
				map[xy[1]][xy[0]] = '0';
			}
			else if (map[xy[1]][xy[0]] == 'C')
				info[2]++;
			xy[0]++;
		}
		xy[1]++;
	}
	if (info[0] < 0 || info[1] < 0)
		print_error("No player position");
}

int	main(int argc, char **argv)
{
	char	**map;
	int		i[5];

	if (argc != 2)
		print_error("Missing map");
	map = read_map(argv[1], &i[0], &i[1]);
	if (!map)
		print_error("Failed to load map");
	validate_map(map, i[0], i[1]);
	i[2] = -1;
	i[3] = -1;
	scan_map_vars(map, i, &i[2]);
	start_game(map, i);
	return (0);
}
