/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_error_utils.c                              */
/*                                                    +:+ +:+         +:+     */
/*   By: ducnguye <ducnguye@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 12:00:00 by ducnguye          #+#    #+#             */
/*   Updated: 2025/06/02 12:00:00 by ducnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	send_err(char *err, int status)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(err, 2);
	return (status);
}

int	is_valid_char(char c)
{
	char	*valid_chars;

	valid_chars = "10EPC";
	if (!ft_strchr(valid_chars, c))
		return (0);
	return (1);
}

int	is_valid_path(int *fd, char *filename)
{
	char	*extension;

	*fd = open(filename, O_RDONLY);
	if (*fd == -1)
	{
		ft_putendl_fd(FILE_NOT_EXIST, 2);
		return (0);
	}
	extension = ft_strrchr(filename, '.');
	if (ft_strcmp(extension, ".ber"))
	{
		ft_putendl_fd(FILE_EXT_ERR, 2);
		return (0);
	}
	return (1);
}

void	reset_map(char **grid_map, t_map *map)
{
	t_coord	*ptr;

	mark_plays(grid_map, map->start_coord.x, map->start_coord.y, '0');
	ptr = map->colls_coord;
	while (ptr)
	{
		grid_map[ptr->y][ptr->x] = 'C';
		ptr = ptr->next;
	}
}
