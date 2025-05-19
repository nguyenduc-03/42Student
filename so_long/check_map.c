/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ducnguye <ducnguye@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:08:19 by ducnguye          #+#    #+#             */
/*   Updated: 2025/05/19 17:08:19 by ducnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_map.h"
#include <stdlib.h>

char	**read_map(const char *filename, int *width, int *height)
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
