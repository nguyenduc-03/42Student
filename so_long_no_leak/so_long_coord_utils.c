/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_coord_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:34:11 by edfreder          #+#    #+#             */
/*   Updated: 2025/05/31 23:02:44 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	coord_check(t_coord *coord, char **grid_map, char c)
{
	t_coord	*ptr;

	if (coord)
	{
		ptr = coord;
		while (ptr)
		{
			if (grid_map[ptr->y][ptr->x] != c)
				return (0);
			ptr = ptr->next;
		}
	}
	return (1);
}

t_coord	*coord_lstnew(int x, int y)
{
	t_coord	*new;

	new = malloc(sizeof(t_coord));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->x = x;
	new->y = y;
	return (new);
}

int	save_coord(t_map *map, int x, int y, char c)
{
	t_coord	*new;

	if (c == 'E')
	{
		map->exit_coord.x = x;
		map->exit_coord.y = y;
		map->exit_coord.next = NULL;
		map->exit++;
	}
	else if (c == 'P')
	{
		map->start_coord.x = x;
		map->start_coord.y = y;
		map->start_coord.next = NULL;
		map->start++;
	}
	else if (c == 'C')
	{
		new = coord_lstnew(x, y);
		if (!new)
			return (0);
		coord_addback(&map->colls_coord, new);
		map->colls++;
	}
	return (1);
}

void	coord_addback(t_coord **head, t_coord *new)
{
	t_coord	*ptr;

	if (!(*head))
		*head = new;
	else
	{
		ptr = *head;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
}

void	ft_coord_lstclear(t_coord **coord_lst)
{
	t_coord	*ptr;
	t_coord	*next;

	ptr = *coord_lst;
	while (ptr)
	{
		next = ptr->next;
		free(ptr);
		ptr = next;
	}
	*coord_lst = NULL;
}
