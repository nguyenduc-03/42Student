/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    */
/*                                                    +:+ +:+         +:+     */
/*   By: ducnguye <ducnguye@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 12:00:00 by ducnguye          #+#    #+#             */
/*   Updated: 2025/06/02 12:00:00 by ducnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	process_line(char *line, int *line_len, t_list **lst)
{
	int		curr_len;
	char	*line_copy;
	t_list	*new;

	curr_len = ft_strlen(line);
	while (curr_len > 0 && (line[curr_len - 1] == '\n'
			|| line[curr_len - 1] == '\r'))
		line[--curr_len] = '\0';
	if (!check_rectangule(line_len, &curr_len))
		return (send_err("Not a rectangule.", 0));
	line_copy = ft_strdup(line);
	if (!line_copy)
		return (0);
	new = ft_lstnew(line_copy);
	if (!new)
	{
		free(line_copy);
		return (0);
	}
	ft_lstadd_back(lst, new);
	return (1);
}

int	build_map(t_list **lst, int fd)
{
	char	**lines;
	int		i;
	int		line_len;

	lines = get_map_lines(fd);
	if (!lines)
		return (0);
	line_len = 0;
	i = -1;
	while (lines[++i])
	{
		if (!process_line(lines[i], &line_len, lst))
		{
			while (lines[i])
				free(lines[i++]);
			free(lines);
			ft_lstclear(lst, free);
			return (0);
		}
		free(lines[i]);
	}
	free(lines);
	return (1);
}

int	save_map_info(char *line, int line_index, t_map *map)
{
	int	i;

	i = 0;
	while (line[i + 1])
	{
		if (!i || !line[i + 1])
		{
			if (line[i] != '1')
				return (send_err(MAP_WALL_ERR, 0));
		}
		else if (is_valid_char(line[i]))
		{
			if (!save_coord(map, i, line_index, line[i]))
				return (0);
		}
		else
			return (send_err(MAP_INV_CHR_ERR, 0));
		i++;
	}
	return (1);
}

char	**create_grid(t_list *lst, int height)
{
	char	**grid;
	int		i;
	t_list	*curr;

	grid = malloc(sizeof(char *) * (height + 1));
	if (!grid)
		return (0);
	i = 0;
	curr = lst;
	while (curr)
	{
		grid[i] = ft_strdup(curr->content);
		if (!grid[i])
			return (NULL);
		i++;
		curr = curr->next;
	}
	grid[height] = NULL;
	return (grid);
}

char	**get_grid_map(t_list **lst, t_game *game, int *fd, char *filename)
{
	int		lst_size;
	char	**grid_map;

	if (!is_valid_path(fd, filename))
		return (NULL);
	if (!build_map(lst, *fd))
		return (NULL);
	lst_size = ft_lstsize(*lst);
	if (lst_size < 3)
	{
		send_err(MAP_SIZE_ERR, 0);
		return (NULL);
	}
	grid_map = create_grid(*lst, lst_size);
	if (!grid_map)
		return (NULL);
	if (!check_map(grid_map, &game->map) || !check_plays(grid_map, &game->map))
	{
		clean_grid(grid_map);
		return (NULL);
	}
	reset_map(grid_map, &game->map);
	game->map.width = ft_strlen(grid_map[0]);
	game->map.height = lst_size;
	return (grid_map);
}
